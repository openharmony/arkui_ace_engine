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
#define KOALA_INTEROP_MODULE NotSpecifiedInteropModule
#include "callback_kind.h"
#include "Serializers.h"
#include "callbacks.h"
#include "common-interop.h"
#include "arkoala_api_generated.h"
void deserializeAndCallAccessibilityCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean isHover, const Ark_AccessibilityHoverEvent event)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Boolean isHover = thisDeserializer.readBoolean();
    Ark_AccessibilityHoverEvent event = static_cast<Ark_AccessibilityHoverEvent>(AccessibilityHoverEvent_serializer::read(thisDeserializer));
    _call(_resourceId, isHover, event);
}
void deserializeAndCallSyncAccessibilityCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isHover, const Ark_AccessibilityHoverEvent event)>(thisDeserializer.readPointer());
    Ark_Boolean isHover = thisDeserializer.readBoolean();
    Ark_AccessibilityHoverEvent event = static_cast<Ark_AccessibilityHoverEvent>(AccessibilityHoverEvent_serializer::read(thisDeserializer));
    _callSync(vmContext, _resourceId, isHover, event);
}
void deserializeAndCallAccessibilityFocusCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean isFocus)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Boolean isFocus = thisDeserializer.readBoolean();
    _call(_resourceId, isFocus);
}
void deserializeAndCallSyncAccessibilityFocusCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isFocus)>(thisDeserializer.readPointer());
    Ark_Boolean isFocus = thisDeserializer.readBoolean();
    _callSync(vmContext, _resourceId, isFocus);
}
void deserializeAndCallAsyncCallback_image_PixelMap_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_image_PixelMap result)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_image_PixelMap result = static_cast<Ark_image_PixelMap>(image_PixelMap_serializer::read(thisDeserializer));
    _call(_resourceId, result);
}
void deserializeAndCallSyncAsyncCallback_image_PixelMap_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_image_PixelMap result)>(thisDeserializer.readPointer());
    Ark_image_PixelMap result = static_cast<Ark_image_PixelMap>(image_PixelMap_serializer::read(thisDeserializer));
    _callSync(vmContext, _resourceId, result);
}
void deserializeAndCallButtonModifierBuilder(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Ark_ButtonConfiguration config, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_ButtonConfiguration config = ButtonConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Pointer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Pointer_Void))))};
    _call(_resourceId, parentNode, config, _continuation);
}
void deserializeAndCallSyncButtonModifierBuilder(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Ark_ButtonConfiguration config, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointer());
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_ButtonConfiguration config = ButtonConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Pointer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Pointer_Void))))};
    _callSync(vmContext, _resourceId, parentNode, config, _continuation);
}
void deserializeAndCallButtonTriggerClickCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number xPos, const Ark_Number yPos)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number xPos = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number yPos = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _call(_resourceId, xPos, yPos);
}
void deserializeAndCallSyncButtonTriggerClickCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number xPos, const Ark_Number yPos)>(thisDeserializer.readPointer());
    Ark_Number xPos = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number yPos = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _callSync(vmContext, _resourceId, xPos, yPos);
}
void deserializeAndCallCallback_Area_Area_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Area oldValue, const Ark_Area newValue)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Area oldValue = Area_serializer::read(thisDeserializer);
    Ark_Area newValue = Area_serializer::read(thisDeserializer);
    _call(_resourceId, oldValue, newValue);
}
void deserializeAndCallSyncCallback_Area_Area_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Area oldValue, const Ark_Area newValue)>(thisDeserializer.readPointer());
    Ark_Area oldValue = Area_serializer::read(thisDeserializer);
    Ark_Area newValue = Area_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, oldValue, newValue);
}
void deserializeAndCallCallback_Array_Number_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
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
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
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
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
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
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
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
void deserializeAndCallCallback_Array_TextMenuItem_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Array_TextMenuItem value)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    const Ark_Int32 value_buf_length = thisDeserializer.readInt32();
    Array_TextMenuItem value_buf = {};
    thisDeserializer.resizeArray<std::decay<decltype(value_buf)>::type,
        std::decay<decltype(*value_buf.array)>::type>(&value_buf, value_buf_length);
    for (int value_buf_i = 0; value_buf_i < value_buf_length; value_buf_i++) {
        value_buf.array[value_buf_i] = TextMenuItem_serializer::read(thisDeserializer);
    }
    Array_TextMenuItem value = value_buf;
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_Array_TextMenuItem_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Array_TextMenuItem value)>(thisDeserializer.readPointer());
    const Ark_Int32 value_buf_length = thisDeserializer.readInt32();
    Array_TextMenuItem value_buf = {};
    thisDeserializer.resizeArray<std::decay<decltype(value_buf)>::type,
        std::decay<decltype(*value_buf.array)>::type>(&value_buf, value_buf_length);
    for (int value_buf_i = 0; value_buf_i < value_buf_length; value_buf_i++) {
        value_buf.array[value_buf_i] = TextMenuItem_serializer::read(thisDeserializer);
    }
    Array_TextMenuItem value = value_buf;
    _callSync(vmContext, _resourceId, value);
}
void deserializeAndCallCallback_Array_TouchTestInfo_TouchResult(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Array_TouchTestInfo value, const Callback_TouchResult_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    const Ark_Int32 value_buf_length = thisDeserializer.readInt32();
    Array_TouchTestInfo value_buf = {};
    thisDeserializer.resizeArray<std::decay<decltype(value_buf)>::type,
        std::decay<decltype(*value_buf.array)>::type>(&value_buf, value_buf_length);
    for (int value_buf_i = 0; value_buf_i < value_buf_length; value_buf_i++) {
        value_buf.array[value_buf_i] = TouchTestInfo_serializer::read(thisDeserializer);
    }
    Array_TouchTestInfo value = value_buf;
    Callback_TouchResult_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_TouchResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_TouchResult_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_TouchResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_TouchResult_Void))))};
    _call(_resourceId, value, _continuation);
}
void deserializeAndCallSyncCallback_Array_TouchTestInfo_TouchResult(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Array_TouchTestInfo value, const Callback_TouchResult_Void continuation)>(thisDeserializer.readPointer());
    const Ark_Int32 value_buf_length = thisDeserializer.readInt32();
    Array_TouchTestInfo value_buf = {};
    thisDeserializer.resizeArray<std::decay<decltype(value_buf)>::type,
        std::decay<decltype(*value_buf.array)>::type>(&value_buf, value_buf_length);
    for (int value_buf_i = 0; value_buf_i < value_buf_length; value_buf_i++) {
        value_buf.array[value_buf_i] = TouchTestInfo_serializer::read(thisDeserializer);
    }
    Array_TouchTestInfo value = value_buf;
    Callback_TouchResult_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_TouchResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_TouchResult_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_TouchResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_TouchResult_Void))))};
    _callSync(vmContext, _resourceId, value, _continuation);
}
void deserializeAndCallCallback_AxisEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_AxisEvent value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_AxisEvent value0 = static_cast<Ark_AxisEvent>(AxisEvent_serializer::read(thisDeserializer));
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_AxisEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_AxisEvent value0)>(thisDeserializer.readPointer());
    Ark_AxisEvent value0 = static_cast<Ark_AxisEvent>(AxisEvent_serializer::read(thisDeserializer));
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, _continuation);
}
void deserializeAndCallSyncCallback_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _callSync(vmContext, _resourceId, _continuation);
}
void deserializeAndCallCallback_Boolean_HoverEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean isHover, const Ark_HoverEvent event)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Boolean isHover = thisDeserializer.readBoolean();
    Ark_HoverEvent event = static_cast<Ark_HoverEvent>(HoverEvent_serializer::read(thisDeserializer));
    _call(_resourceId, isHover, event);
}
void deserializeAndCallSyncCallback_Boolean_HoverEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isHover, const Ark_HoverEvent event)>(thisDeserializer.readPointer());
    Ark_Boolean isHover = thisDeserializer.readBoolean();
    Ark_HoverEvent event = static_cast<Ark_HoverEvent>(HoverEvent_serializer::read(thisDeserializer));
    _callSync(vmContext, _resourceId, isHover, event);
}
void deserializeAndCallCallback_Boolean_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Boolean value0 = thisDeserializer.readBoolean();
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_Boolean_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointer());
    Ark_Boolean value0 = thisDeserializer.readBoolean();
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_Buffer_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Buffer value)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Buffer value = static_cast<Ark_Buffer>(thisDeserializer.readBuffer());
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_Buffer_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Buffer value)>(thisDeserializer.readPointer());
    Ark_Buffer value = static_cast<Ark_Buffer>(thisDeserializer.readBuffer());
    _callSync(vmContext, _resourceId, value);
}
void deserializeAndCallCallback_ClickEvent_LocationButtonOnClickResult_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_ClickEvent event, Ark_LocationButtonOnClickResult result)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_ClickEvent event = static_cast<Ark_ClickEvent>(ClickEvent_serializer::read(thisDeserializer));
    Ark_LocationButtonOnClickResult result = static_cast<Ark_LocationButtonOnClickResult>(thisDeserializer.readInt32());
    _call(_resourceId, event, result);
}
void deserializeAndCallSyncCallback_ClickEvent_LocationButtonOnClickResult_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_ClickEvent event, Ark_LocationButtonOnClickResult result)>(thisDeserializer.readPointer());
    Ark_ClickEvent event = static_cast<Ark_ClickEvent>(ClickEvent_serializer::read(thisDeserializer));
    Ark_LocationButtonOnClickResult result = static_cast<Ark_LocationButtonOnClickResult>(thisDeserializer.readInt32());
    _callSync(vmContext, _resourceId, event, result);
}
void deserializeAndCallCallback_ClickEvent_PasteButtonOnClickResult_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_ClickEvent event, Ark_PasteButtonOnClickResult result)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_ClickEvent event = static_cast<Ark_ClickEvent>(ClickEvent_serializer::read(thisDeserializer));
    Ark_PasteButtonOnClickResult result = static_cast<Ark_PasteButtonOnClickResult>(thisDeserializer.readInt32());
    _call(_resourceId, event, result);
}
void deserializeAndCallSyncCallback_ClickEvent_PasteButtonOnClickResult_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_ClickEvent event, Ark_PasteButtonOnClickResult result)>(thisDeserializer.readPointer());
    Ark_ClickEvent event = static_cast<Ark_ClickEvent>(ClickEvent_serializer::read(thisDeserializer));
    Ark_PasteButtonOnClickResult result = static_cast<Ark_PasteButtonOnClickResult>(thisDeserializer.readInt32());
    _callSync(vmContext, _resourceId, event, result);
}
void deserializeAndCallCallback_ClickEvent_SaveButtonOnClickResult_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_ClickEvent event, Ark_SaveButtonOnClickResult result)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_ClickEvent event = static_cast<Ark_ClickEvent>(ClickEvent_serializer::read(thisDeserializer));
    Ark_SaveButtonOnClickResult result = static_cast<Ark_SaveButtonOnClickResult>(thisDeserializer.readInt32());
    _call(_resourceId, event, result);
}
void deserializeAndCallSyncCallback_ClickEvent_SaveButtonOnClickResult_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_ClickEvent event, Ark_SaveButtonOnClickResult result)>(thisDeserializer.readPointer());
    Ark_ClickEvent event = static_cast<Ark_ClickEvent>(ClickEvent_serializer::read(thisDeserializer));
    Ark_SaveButtonOnClickResult result = static_cast<Ark_SaveButtonOnClickResult>(thisDeserializer.readInt32());
    _callSync(vmContext, _resourceId, event, result);
}
void deserializeAndCallCallback_ClickEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_ClickEvent event)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_ClickEvent event = static_cast<Ark_ClickEvent>(ClickEvent_serializer::read(thisDeserializer));
    _call(_resourceId, event);
}
void deserializeAndCallSyncCallback_ClickEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_ClickEvent event)>(thisDeserializer.readPointer());
    Ark_ClickEvent event = static_cast<Ark_ClickEvent>(ClickEvent_serializer::read(thisDeserializer));
    _callSync(vmContext, _resourceId, event);
}
void deserializeAndCallCallback_CompatibleComponentInfo_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_CompatibleComponentInfo value)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_CompatibleComponentInfo value = CompatibleComponentInfo_serializer::read(thisDeserializer);
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_CompatibleComponentInfo_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_CompatibleComponentInfo value)>(thisDeserializer.readPointer());
    Ark_CompatibleComponentInfo value = CompatibleComponentInfo_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, value);
}
void deserializeAndCallCallback_ComputedBarAttribute_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_ComputedBarAttribute value)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_ComputedBarAttribute value = ComputedBarAttribute_serializer::read(thisDeserializer);
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_ComputedBarAttribute_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_ComputedBarAttribute value)>(thisDeserializer.readPointer());
    Ark_ComputedBarAttribute value = ComputedBarAttribute_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, value);
}
void deserializeAndCallCallback_CopyEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_CopyEvent value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_CopyEvent value0 = CopyEvent_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_CopyEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_CopyEvent value0)>(thisDeserializer.readPointer());
    Ark_CopyEvent value0 = CopyEvent_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_CreateItem(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Int32 index, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Int32 index = thisDeserializer.readInt32();
    Callback_Pointer_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Pointer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Pointer_Void))))};
    _call(_resourceId, index, _continuation);
}
void deserializeAndCallSyncCallback_CreateItem(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int32 index, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointer());
    Ark_Int32 index = thisDeserializer.readInt32();
    Callback_Pointer_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Pointer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Pointer_Void))))};
    _callSync(vmContext, _resourceId, index, _continuation);
}
void deserializeAndCallCallback_CrownEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_CrownEvent value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_CrownEvent value0 = CrownEvent_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_CrownEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_CrownEvent value0)>(thisDeserializer.readPointer());
    Ark_CrownEvent value0 = CrownEvent_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_CustomSpanMeasureInfo_CustomSpanMetrics(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_CustomSpanMeasureInfo measureInfo, const Callback_CustomSpanMetrics_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_CustomSpanMeasureInfo measureInfo = CustomSpanMeasureInfo_serializer::read(thisDeserializer);
    Callback_CustomSpanMetrics_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_CustomSpanMetrics value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_CustomSpanMetrics_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_CustomSpanMetrics value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_CustomSpanMetrics_Void))))};
    _call(_resourceId, measureInfo, _continuation);
}
void deserializeAndCallSyncCallback_CustomSpanMeasureInfo_CustomSpanMetrics(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_CustomSpanMeasureInfo measureInfo, const Callback_CustomSpanMetrics_Void continuation)>(thisDeserializer.readPointer());
    Ark_CustomSpanMeasureInfo measureInfo = CustomSpanMeasureInfo_serializer::read(thisDeserializer);
    Callback_CustomSpanMetrics_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_CustomSpanMetrics value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_CustomSpanMetrics_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_CustomSpanMetrics value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_CustomSpanMetrics_Void))))};
    _callSync(vmContext, _resourceId, measureInfo, _continuation);
}
void deserializeAndCallCallback_CustomSpanMetrics_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_CustomSpanMetrics value)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_CustomSpanMetrics value = CustomSpanMetrics_serializer::read(thisDeserializer);
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_CustomSpanMetrics_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_CustomSpanMetrics value)>(thisDeserializer.readPointer());
    Ark_CustomSpanMetrics value = CustomSpanMetrics_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, value);
}
void deserializeAndCallCallback_CutEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_CutEvent value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_CutEvent value0 = CutEvent_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_CutEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_CutEvent value0)>(thisDeserializer.readPointer());
    Ark_CutEvent value0 = CutEvent_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_Date_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Date value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Date value0 = thisDeserializer.readInt64();
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_Date_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Date value0)>(thisDeserializer.readPointer());
    Ark_Date value0 = thisDeserializer.readInt64();
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_DeleteValue_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_DeleteValue value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_DeleteValue value0 = DeleteValue_serializer::read(thisDeserializer);
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, value0, _continuation);
}
void deserializeAndCallSyncCallback_DeleteValue_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_DeleteValue value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    Ark_DeleteValue value0 = DeleteValue_serializer::read(thisDeserializer);
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _callSync(vmContext, _resourceId, value0, _continuation);
}
void deserializeAndCallCallback_DeleteValue_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_DeleteValue value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_DeleteValue value0 = DeleteValue_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_DeleteValue_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_DeleteValue value0)>(thisDeserializer.readPointer());
    Ark_DeleteValue value0 = DeleteValue_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_DismissContentCoverAction_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_DismissContentCoverAction value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_DismissContentCoverAction value0 = DismissContentCoverAction_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_DismissContentCoverAction_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_DismissContentCoverAction value0)>(thisDeserializer.readPointer());
    Ark_DismissContentCoverAction value0 = DismissContentCoverAction_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_DismissDialogAction_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_DismissDialogAction value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_DismissDialogAction value0 = static_cast<Ark_DismissDialogAction>(DismissDialogAction_serializer::read(thisDeserializer));
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_DismissDialogAction_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_DismissDialogAction value0)>(thisDeserializer.readPointer());
    Ark_DismissDialogAction value0 = static_cast<Ark_DismissDialogAction>(DismissDialogAction_serializer::read(thisDeserializer));
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_DismissPopupAction_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_DismissPopupAction value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_DismissPopupAction value0 = static_cast<Ark_DismissPopupAction>(DismissPopupAction_serializer::read(thisDeserializer));
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_DismissPopupAction_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_DismissPopupAction value0)>(thisDeserializer.readPointer());
    Ark_DismissPopupAction value0 = static_cast<Ark_DismissPopupAction>(DismissPopupAction_serializer::read(thisDeserializer));
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_DismissSheetAction_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_DismissSheetAction value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_DismissSheetAction value0 = DismissSheetAction_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_DismissSheetAction_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_DismissSheetAction value0)>(thisDeserializer.readPointer());
    Ark_DismissSheetAction value0 = DismissSheetAction_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_DragEvent_Opt_String_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_DragEvent event, const Opt_String extraParams)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_DragEvent event = static_cast<Ark_DragEvent>(DragEvent_serializer::read(thisDeserializer));
    const auto extraParams_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_String extraParams_buf = {};
    extraParams_buf.tag = extraParams_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((extraParams_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        extraParams_buf.value = static_cast<Ark_String>(thisDeserializer.readString());
    }
    Opt_String extraParams = extraParams_buf;
    _call(_resourceId, event, extraParams);
}
void deserializeAndCallSyncCallback_DragEvent_Opt_String_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_DragEvent event, const Opt_String extraParams)>(thisDeserializer.readPointer());
    Ark_DragEvent event = static_cast<Ark_DragEvent>(DragEvent_serializer::read(thisDeserializer));
    const auto extraParams_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_String extraParams_buf = {};
    extraParams_buf.tag = extraParams_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((extraParams_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        extraParams_buf.value = static_cast<Ark_String>(thisDeserializer.readString());
    }
    Opt_String extraParams = extraParams_buf;
    _callSync(vmContext, _resourceId, event, extraParams);
}
void deserializeAndCallCallback_DrawContext_CustomSpanDrawInfo_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_DrawContext context, const Ark_CustomSpanDrawInfo drawInfo)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_DrawContext context = static_cast<Ark_DrawContext>(DrawContext_serializer::read(thisDeserializer));
    Ark_CustomSpanDrawInfo drawInfo = CustomSpanDrawInfo_serializer::read(thisDeserializer);
    _call(_resourceId, context, drawInfo);
}
void deserializeAndCallSyncCallback_DrawContext_CustomSpanDrawInfo_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_DrawContext context, const Ark_CustomSpanDrawInfo drawInfo)>(thisDeserializer.readPointer());
    Ark_DrawContext context = static_cast<Ark_DrawContext>(DrawContext_serializer::read(thisDeserializer));
    Ark_CustomSpanDrawInfo drawInfo = CustomSpanDrawInfo_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, context, drawInfo);
}
void deserializeAndCallCallback_DrawContext_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_DrawContext drawContext)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_DrawContext drawContext = static_cast<Ark_DrawContext>(DrawContext_serializer::read(thisDeserializer));
    _call(_resourceId, drawContext);
}
void deserializeAndCallSyncCallback_DrawContext_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_DrawContext drawContext)>(thisDeserializer.readPointer());
    Ark_DrawContext drawContext = static_cast<Ark_DrawContext>(DrawContext_serializer::read(thisDeserializer));
    _callSync(vmContext, _resourceId, drawContext);
}
void deserializeAndCallCallback_EditableTextChangeValue_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_EditableTextChangeValue value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_EditableTextChangeValue value0 = EditableTextChangeValue_serializer::read(thisDeserializer);
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, value0, _continuation);
}
void deserializeAndCallSyncCallback_EditableTextChangeValue_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_EditableTextChangeValue value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    Ark_EditableTextChangeValue value0 = EditableTextChangeValue_serializer::read(thisDeserializer);
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _callSync(vmContext, _resourceId, value0, _continuation);
}
void deserializeAndCallCallback_EnterKeyType_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_EnterKeyType enterKey)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_EnterKeyType enterKey = static_cast<Ark_EnterKeyType>(thisDeserializer.readInt32());
    _call(_resourceId, enterKey);
}
void deserializeAndCallSyncCallback_EnterKeyType_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_EnterKeyType enterKey)>(thisDeserializer.readPointer());
    Ark_EnterKeyType enterKey = static_cast<Ark_EnterKeyType>(thisDeserializer.readInt32());
    _callSync(vmContext, _resourceId, enterKey);
}
void deserializeAndCallCallback_ErrorInformation_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_ErrorInformation value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_ErrorInformation value0 = ErrorInformation_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_ErrorInformation_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_ErrorInformation value0)>(thisDeserializer.readPointer());
    Ark_ErrorInformation value0 = ErrorInformation_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_Extender_OnFinish(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    _call(_resourceId);
}
void deserializeAndCallSyncCallback_Extender_OnFinish(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId)>(thisDeserializer.readPointer());
    _callSync(vmContext, _resourceId);
}
void deserializeAndCallCallback_Extender_OnProgress(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Float32 value)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Float32 value = thisDeserializer.readFloat32();
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_Extender_OnProgress(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Float32 value)>(thisDeserializer.readPointer());
    Ark_Float32 value = thisDeserializer.readFloat32();
    _callSync(vmContext, _resourceId, value);
}
void deserializeAndCallCallback_FocusAxisEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_FocusAxisEvent value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_FocusAxisEvent value0 = static_cast<Ark_FocusAxisEvent>(FocusAxisEvent_serializer::read(thisDeserializer));
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_FocusAxisEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_FocusAxisEvent value0)>(thisDeserializer.readPointer());
    Ark_FocusAxisEvent value0 = static_cast<Ark_FocusAxisEvent>(FocusAxisEvent_serializer::read(thisDeserializer));
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_FormCallbackInfo_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_FormCallbackInfo value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_FormCallbackInfo value0 = FormCallbackInfo_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_FormCallbackInfo_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_FormCallbackInfo value0)>(thisDeserializer.readPointer());
    Ark_FormCallbackInfo value0 = FormCallbackInfo_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_FullscreenInfo_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_FullscreenInfo value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_FullscreenInfo value0 = FullscreenInfo_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_FullscreenInfo_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_FullscreenInfo value0)>(thisDeserializer.readPointer());
    Ark_FullscreenInfo value0 = FullscreenInfo_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_GestureEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_GestureEvent event)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_GestureEvent event = static_cast<Ark_GestureEvent>(GestureEvent_serializer::read(thisDeserializer));
    _call(_resourceId, event);
}
void deserializeAndCallSyncCallback_GestureEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_GestureEvent event)>(thisDeserializer.readPointer());
    Ark_GestureEvent event = static_cast<Ark_GestureEvent>(GestureEvent_serializer::read(thisDeserializer));
    _callSync(vmContext, _resourceId, event);
}
void deserializeAndCallCallback_GestureInfo_BaseGestureEvent_GestureJudgeResult(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_GestureInfo gestureInfo, const Ark_BaseGestureEvent event, const Callback_GestureJudgeResult_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_GestureInfo gestureInfo = GestureInfo_serializer::read(thisDeserializer);
    Ark_BaseGestureEvent event = static_cast<Ark_BaseGestureEvent>(BaseGestureEvent_serializer::read(thisDeserializer));
    Callback_GestureJudgeResult_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_GestureJudgeResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_GestureJudgeResult_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_GestureJudgeResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_GestureJudgeResult_Void))))};
    _call(_resourceId, gestureInfo, event, _continuation);
}
void deserializeAndCallSyncCallback_GestureInfo_BaseGestureEvent_GestureJudgeResult(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_GestureInfo gestureInfo, const Ark_BaseGestureEvent event, const Callback_GestureJudgeResult_Void continuation)>(thisDeserializer.readPointer());
    Ark_GestureInfo gestureInfo = GestureInfo_serializer::read(thisDeserializer);
    Ark_BaseGestureEvent event = static_cast<Ark_BaseGestureEvent>(BaseGestureEvent_serializer::read(thisDeserializer));
    Callback_GestureJudgeResult_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_GestureJudgeResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_GestureJudgeResult_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_GestureJudgeResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_GestureJudgeResult_Void))))};
    _callSync(vmContext, _resourceId, gestureInfo, event, _continuation);
}
void deserializeAndCallCallback_GestureJudgeResult_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_GestureJudgeResult value)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_GestureJudgeResult value = static_cast<Ark_GestureJudgeResult>(thisDeserializer.readInt32());
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_GestureJudgeResult_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_GestureJudgeResult value)>(thisDeserializer.readPointer());
    Ark_GestureJudgeResult value = static_cast<Ark_GestureJudgeResult>(thisDeserializer.readInt32());
    _callSync(vmContext, _resourceId, value);
}
void deserializeAndCallCallback_GestureRecognizer_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_GestureRecognizer value)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_GestureRecognizer value = static_cast<Ark_GestureRecognizer>(GestureRecognizer_serializer::read(thisDeserializer));
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_GestureRecognizer_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_GestureRecognizer value)>(thisDeserializer.readPointer());
    Ark_GestureRecognizer value = static_cast<Ark_GestureRecognizer>(GestureRecognizer_serializer::read(thisDeserializer));
    _callSync(vmContext, _resourceId, value);
}
void deserializeAndCallCallback_HitTestMode_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_HitTestMode value)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_HitTestMode value = static_cast<Ark_HitTestMode>(thisDeserializer.readInt32());
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_HitTestMode_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_HitTestMode value)>(thisDeserializer.readPointer());
    Ark_HitTestMode value = static_cast<Ark_HitTestMode>(thisDeserializer.readInt32());
    _callSync(vmContext, _resourceId, value);
}
void deserializeAndCallCallback_HoverEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_HoverEvent value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_HoverEvent value0 = static_cast<Ark_HoverEvent>(HoverEvent_serializer::read(thisDeserializer));
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_HoverEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_HoverEvent value0)>(thisDeserializer.readPointer());
    Ark_HoverEvent value0 = static_cast<Ark_HoverEvent>(HoverEvent_serializer::read(thisDeserializer));
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_InsertValue_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_InsertValue value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_InsertValue value0 = InsertValue_serializer::read(thisDeserializer);
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, value0, _continuation);
}
void deserializeAndCallSyncCallback_InsertValue_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_InsertValue value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    Ark_InsertValue value0 = InsertValue_serializer::read(thisDeserializer);
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _callSync(vmContext, _resourceId, value0, _continuation);
}
void deserializeAndCallCallback_InsertValue_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_InsertValue value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_InsertValue value0 = InsertValue_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_InsertValue_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_InsertValue value0)>(thisDeserializer.readPointer());
    Ark_InsertValue value0 = InsertValue_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_ItemDragInfo_Number_Number_Boolean_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_ItemDragInfo event, const Ark_Number itemIndex, const Ark_Number insertIndex, const Ark_Boolean isSuccess)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_ItemDragInfo event = ItemDragInfo_serializer::read(thisDeserializer);
    Ark_Number itemIndex = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number insertIndex = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Boolean isSuccess = thisDeserializer.readBoolean();
    _call(_resourceId, event, itemIndex, insertIndex, isSuccess);
}
void deserializeAndCallSyncCallback_ItemDragInfo_Number_Number_Boolean_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_ItemDragInfo event, const Ark_Number itemIndex, const Ark_Number insertIndex, const Ark_Boolean isSuccess)>(thisDeserializer.readPointer());
    Ark_ItemDragInfo event = ItemDragInfo_serializer::read(thisDeserializer);
    Ark_Number itemIndex = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number insertIndex = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Boolean isSuccess = thisDeserializer.readBoolean();
    _callSync(vmContext, _resourceId, event, itemIndex, insertIndex, isSuccess);
}
void deserializeAndCallCallback_ItemDragInfo_Number_Number_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_ItemDragInfo event, const Ark_Number itemIndex, const Ark_Number insertIndex)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_ItemDragInfo event = ItemDragInfo_serializer::read(thisDeserializer);
    Ark_Number itemIndex = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number insertIndex = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _call(_resourceId, event, itemIndex, insertIndex);
}
void deserializeAndCallSyncCallback_ItemDragInfo_Number_Number_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_ItemDragInfo event, const Ark_Number itemIndex, const Ark_Number insertIndex)>(thisDeserializer.readPointer());
    Ark_ItemDragInfo event = ItemDragInfo_serializer::read(thisDeserializer);
    Ark_Number itemIndex = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number insertIndex = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _callSync(vmContext, _resourceId, event, itemIndex, insertIndex);
}
void deserializeAndCallCallback_ItemDragInfo_Number_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_ItemDragInfo event, const Ark_Number itemIndex)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_ItemDragInfo event = ItemDragInfo_serializer::read(thisDeserializer);
    Ark_Number itemIndex = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _call(_resourceId, event, itemIndex);
}
void deserializeAndCallSyncCallback_ItemDragInfo_Number_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_ItemDragInfo event, const Ark_Number itemIndex)>(thisDeserializer.readPointer());
    Ark_ItemDragInfo event = ItemDragInfo_serializer::read(thisDeserializer);
    Ark_Number itemIndex = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _callSync(vmContext, _resourceId, event, itemIndex);
}
void deserializeAndCallCallback_ItemDragInfo_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_ItemDragInfo event)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_ItemDragInfo event = ItemDragInfo_serializer::read(thisDeserializer);
    _call(_resourceId, event);
}
void deserializeAndCallSyncCallback_ItemDragInfo_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_ItemDragInfo event)>(thisDeserializer.readPointer());
    Ark_ItemDragInfo event = ItemDragInfo_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, event);
}
void deserializeAndCallCallback_KeyEvent_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_KeyEvent value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_KeyEvent value0 = static_cast<Ark_KeyEvent>(KeyEvent_serializer::read(thisDeserializer));
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, value0, _continuation);
}
void deserializeAndCallSyncCallback_KeyEvent_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_KeyEvent value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    Ark_KeyEvent value0 = static_cast<Ark_KeyEvent>(KeyEvent_serializer::read(thisDeserializer));
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _callSync(vmContext, _resourceId, value0, _continuation);
}
void deserializeAndCallCallback_KeyEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_KeyEvent event)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_KeyEvent event = static_cast<Ark_KeyEvent>(KeyEvent_serializer::read(thisDeserializer));
    _call(_resourceId, event);
}
void deserializeAndCallSyncCallback_KeyEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_KeyEvent event)>(thisDeserializer.readPointer());
    Ark_KeyEvent event = static_cast<Ark_KeyEvent>(KeyEvent_serializer::read(thisDeserializer));
    _callSync(vmContext, _resourceId, event);
}
void deserializeAndCallCallback_Map_String_Object_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Map_String_Object value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    const Ark_Int32 value0_buf_size = thisDeserializer.readInt32();
    Map_String_Object value0_buf = {};
    thisDeserializer.resizeMap<Map_String_Object, Ark_String, Ark_Object>(&value0_buf, value0_buf_size);
    for (int value0_buf_i = 0; value0_buf_i < value0_buf_size; value0_buf_i++) {
        const Ark_String value0_buf_key = static_cast<Ark_String>(thisDeserializer.readString());
        const Ark_Object value0_buf_value = static_cast<Ark_Object>(thisDeserializer.readObject());
        value0_buf.keys[value0_buf_i] = value0_buf_key;
        value0_buf.values[value0_buf_i] = value0_buf_value;
    }
    Map_String_Object value0 = value0_buf;
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_Map_String_Object_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Map_String_Object value0)>(thisDeserializer.readPointer());
    const Ark_Int32 value0_buf_size = thisDeserializer.readInt32();
    Map_String_Object value0_buf = {};
    thisDeserializer.resizeMap<Map_String_Object, Ark_String, Ark_Object>(&value0_buf, value0_buf_size);
    for (int value0_buf_i = 0; value0_buf_i < value0_buf_size; value0_buf_i++) {
        const Ark_String value0_buf_key = static_cast<Ark_String>(thisDeserializer.readString());
        const Ark_Object value0_buf_value = static_cast<Ark_Object>(thisDeserializer.readObject());
        value0_buf.keys[value0_buf_i] = value0_buf_key;
        value0_buf.values[value0_buf_i] = value0_buf_value;
    }
    Map_String_Object value0 = value0_buf;
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_MarqueeState_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_MarqueeState value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_MarqueeState value0 = static_cast<Ark_MarqueeState>(thisDeserializer.readInt32());
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_MarqueeState_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_MarqueeState value0)>(thisDeserializer.readPointer());
    Ark_MarqueeState value0 = static_cast<Ark_MarqueeState>(thisDeserializer.readInt32());
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_MouseEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_MouseEvent event)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_MouseEvent event = static_cast<Ark_MouseEvent>(MouseEvent_serializer::read(thisDeserializer));
    _call(_resourceId, event);
}
void deserializeAndCallSyncCallback_MouseEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_MouseEvent event)>(thisDeserializer.readPointer());
    Ark_MouseEvent event = static_cast<Ark_MouseEvent>(MouseEvent_serializer::read(thisDeserializer));
    _callSync(vmContext, _resourceId, event);
}
void deserializeAndCallCallback_NativeEmbedDataInfo_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativeEmbedDataInfo event)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_NativeEmbedDataInfo event = NativeEmbedDataInfo_serializer::read(thisDeserializer);
    _call(_resourceId, event);
}
void deserializeAndCallSyncCallback_NativeEmbedDataInfo_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativeEmbedDataInfo event)>(thisDeserializer.readPointer());
    Ark_NativeEmbedDataInfo event = NativeEmbedDataInfo_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, event);
}
void deserializeAndCallCallback_NativeEmbedTouchInfo_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativeEmbedTouchInfo event)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_NativeEmbedTouchInfo event = NativeEmbedTouchInfo_serializer::read(thisDeserializer);
    _call(_resourceId, event);
}
void deserializeAndCallSyncCallback_NativeEmbedTouchInfo_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativeEmbedTouchInfo event)>(thisDeserializer.readPointer());
    Ark_NativeEmbedTouchInfo event = NativeEmbedTouchInfo_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, event);
}
void deserializeAndCallCallback_NavDestinationActiveReason_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_NavDestinationActiveReason value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_NavDestinationActiveReason value0 = static_cast<Ark_NavDestinationActiveReason>(thisDeserializer.readInt32());
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_NavDestinationActiveReason_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_NavDestinationActiveReason value0)>(thisDeserializer.readPointer());
    Ark_NavDestinationActiveReason value0 = static_cast<Ark_NavDestinationActiveReason>(thisDeserializer.readInt32());
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_NavDestinationContext_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NavDestinationContext value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_NavDestinationContext value0 = static_cast<Ark_NavDestinationContext>(NavDestinationContext_serializer::read(thisDeserializer));
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_NavDestinationContext_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NavDestinationContext value0)>(thisDeserializer.readPointer());
    Ark_NavDestinationContext value0 = static_cast<Ark_NavDestinationContext>(NavDestinationContext_serializer::read(thisDeserializer));
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_NavigationMode_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_NavigationMode mode)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_NavigationMode mode = static_cast<Ark_NavigationMode>(thisDeserializer.readInt32());
    _call(_resourceId, mode);
}
void deserializeAndCallSyncCallback_NavigationMode_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_NavigationMode mode)>(thisDeserializer.readPointer());
    Ark_NavigationMode mode = static_cast<Ark_NavigationMode>(thisDeserializer.readInt32());
    _callSync(vmContext, _resourceId, mode);
}
void deserializeAndCallCallback_NavigationTitleMode_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_NavigationTitleMode titleMode)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_NavigationTitleMode titleMode = static_cast<Ark_NavigationTitleMode>(thisDeserializer.readInt32());
    _call(_resourceId, titleMode);
}
void deserializeAndCallSyncCallback_NavigationTitleMode_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_NavigationTitleMode titleMode)>(thisDeserializer.readPointer());
    Ark_NavigationTitleMode titleMode = static_cast<Ark_NavigationTitleMode>(thisDeserializer.readInt32());
    _callSync(vmContext, _resourceId, titleMode);
}
void deserializeAndCallCallback_NavigationTransitionProxy_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NavigationTransitionProxy transitionProxy)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_NavigationTransitionProxy transitionProxy = static_cast<Ark_NavigationTransitionProxy>(NavigationTransitionProxy_serializer::read(thisDeserializer));
    _call(_resourceId, transitionProxy);
}
void deserializeAndCallSyncCallback_NavigationTransitionProxy_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NavigationTransitionProxy transitionProxy)>(thisDeserializer.readPointer());
    Ark_NavigationTransitionProxy transitionProxy = static_cast<Ark_NavigationTransitionProxy>(NavigationTransitionProxy_serializer::read(thisDeserializer));
    _callSync(vmContext, _resourceId, transitionProxy);
}
void deserializeAndCallCallback_Number_Number_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number from, const Ark_Number to, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number from = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number to = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, from, to, _continuation);
}
void deserializeAndCallSyncCallback_Number_Number_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number from, const Ark_Number to, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    Ark_Number from = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number to = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _callSync(vmContext, _resourceId, from, to, _continuation);
}
void deserializeAndCallCallback_Number_Number_Boolean_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number offset, const Ark_Number index, const Ark_Boolean leadingEdge, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number offset = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Boolean leadingEdge = thisDeserializer.readBoolean();
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, offset, index, leadingEdge, _continuation);
}
void deserializeAndCallSyncCallback_Number_Number_Boolean_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number offset, const Ark_Number index, const Ark_Boolean leadingEdge, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    Ark_Number offset = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Boolean leadingEdge = thisDeserializer.readBoolean();
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _callSync(vmContext, _resourceId, offset, index, leadingEdge, _continuation);
}
void deserializeAndCallCallback_Number_Number_ComputedBarAttribute(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
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
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
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
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
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
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number start, const Ark_Number end, const Ark_Number center)>(thisDeserializer.readPointer());
    Ark_Number start = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number end = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number center = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _callSync(vmContext, _resourceId, start, end, center);
}
void deserializeAndCallCallback_Number_Number_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number first, const Ark_Number last)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number first = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number last = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _call(_resourceId, first, last);
}
void deserializeAndCallSyncCallback_Number_Number_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number first, const Ark_Number last)>(thisDeserializer.readPointer());
    Ark_Number first = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number last = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _callSync(vmContext, _resourceId, first, last);
}
void deserializeAndCallCallback_Number_SliderChangeMode_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number value, Ark_SliderChangeMode mode)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number value = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_SliderChangeMode mode = static_cast<Ark_SliderChangeMode>(thisDeserializer.readInt32());
    _call(_resourceId, value, mode);
}
void deserializeAndCallSyncCallback_Number_SliderChangeMode_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number value, Ark_SliderChangeMode mode)>(thisDeserializer.readPointer());
    Ark_Number value = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_SliderChangeMode mode = static_cast<Ark_SliderChangeMode>(thisDeserializer.readInt32());
    _callSync(vmContext, _resourceId, value, mode);
}
void deserializeAndCallCallback_Number_Tuple_Number_Number(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number index, const Callback_Tuple_Number_Number_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Callback_Tuple_Number_Number_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Tuple_Number_Number value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Tuple_Number_Number_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Tuple_Number_Number value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Tuple_Number_Number_Void))))};
    _call(_resourceId, index, _continuation);
}
void deserializeAndCallSyncCallback_Number_Tuple_Number_Number(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number index, const Callback_Tuple_Number_Number_Void continuation)>(thisDeserializer.readPointer());
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Callback_Tuple_Number_Number_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Tuple_Number_Number value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Tuple_Number_Number_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Tuple_Number_Number value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Tuple_Number_Number_Void))))};
    _callSync(vmContext, _resourceId, index, _continuation);
}
void deserializeAndCallCallback_Number_Tuple_Number_Number_Number_Number(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number index, const Callback_Tuple_Number_Number_Number_Number_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Callback_Tuple_Number_Number_Number_Number_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Tuple_Number_Number_Number_Number value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Tuple_Number_Number_Number_Number_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Tuple_Number_Number_Number_Number value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Tuple_Number_Number_Number_Number_Void))))};
    _call(_resourceId, index, _continuation);
}
void deserializeAndCallSyncCallback_Number_Tuple_Number_Number_Number_Number(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number index, const Callback_Tuple_Number_Number_Number_Number_Void continuation)>(thisDeserializer.readPointer());
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Callback_Tuple_Number_Number_Number_Number_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Tuple_Number_Number_Number_Number value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Tuple_Number_Number_Number_Number_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Tuple_Number_Number_Number_Number value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Tuple_Number_Number_Number_Number_Void))))};
    _callSync(vmContext, _resourceId, index, _continuation);
}
void deserializeAndCallCallback_Number_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number value0 = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_Number_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number value0)>(thisDeserializer.readPointer());
    Ark_Number value0 = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_Object_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Object value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Object value0 = static_cast<Ark_Object>(thisDeserializer.readObject());
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_Object_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Object value0)>(thisDeserializer.readPointer());
    Ark_Object value0 = static_cast<Ark_Object>(thisDeserializer.readObject());
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_OnAlertEvent_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnAlertEvent value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnAlertEvent value0 = OnAlertEvent_serializer::read(thisDeserializer);
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, value0, _continuation);
}
void deserializeAndCallSyncCallback_OnAlertEvent_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnAlertEvent value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    Ark_OnAlertEvent value0 = OnAlertEvent_serializer::read(thisDeserializer);
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _callSync(vmContext, _resourceId, value0, _continuation);
}
void deserializeAndCallCallback_OnAudioStateChangedEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnAudioStateChangedEvent value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnAudioStateChangedEvent value0 = OnAudioStateChangedEvent_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_OnAudioStateChangedEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnAudioStateChangedEvent value0)>(thisDeserializer.readPointer());
    Ark_OnAudioStateChangedEvent value0 = OnAudioStateChangedEvent_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_OnBeforeUnloadEvent_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnBeforeUnloadEvent value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnBeforeUnloadEvent value0 = OnBeforeUnloadEvent_serializer::read(thisDeserializer);
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, value0, _continuation);
}
void deserializeAndCallSyncCallback_OnBeforeUnloadEvent_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnBeforeUnloadEvent value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    Ark_OnBeforeUnloadEvent value0 = OnBeforeUnloadEvent_serializer::read(thisDeserializer);
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _callSync(vmContext, _resourceId, value0, _continuation);
}
void deserializeAndCallCallback_OnClientAuthenticationEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnClientAuthenticationEvent value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnClientAuthenticationEvent value0 = OnClientAuthenticationEvent_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_OnClientAuthenticationEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnClientAuthenticationEvent value0)>(thisDeserializer.readPointer());
    Ark_OnClientAuthenticationEvent value0 = OnClientAuthenticationEvent_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_OnConfirmEvent_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnConfirmEvent value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnConfirmEvent value0 = OnConfirmEvent_serializer::read(thisDeserializer);
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, value0, _continuation);
}
void deserializeAndCallSyncCallback_OnConfirmEvent_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnConfirmEvent value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    Ark_OnConfirmEvent value0 = OnConfirmEvent_serializer::read(thisDeserializer);
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _callSync(vmContext, _resourceId, value0, _continuation);
}
void deserializeAndCallCallback_OnConsoleEvent_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnConsoleEvent value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnConsoleEvent value0 = OnConsoleEvent_serializer::read(thisDeserializer);
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, value0, _continuation);
}
void deserializeAndCallSyncCallback_OnConsoleEvent_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnConsoleEvent value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    Ark_OnConsoleEvent value0 = OnConsoleEvent_serializer::read(thisDeserializer);
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _callSync(vmContext, _resourceId, value0, _continuation);
}
void deserializeAndCallCallback_OnContextMenuShowEvent_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnContextMenuShowEvent value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnContextMenuShowEvent value0 = OnContextMenuShowEvent_serializer::read(thisDeserializer);
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, value0, _continuation);
}
void deserializeAndCallSyncCallback_OnContextMenuShowEvent_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnContextMenuShowEvent value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    Ark_OnContextMenuShowEvent value0 = OnContextMenuShowEvent_serializer::read(thisDeserializer);
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _callSync(vmContext, _resourceId, value0, _continuation);
}
void deserializeAndCallCallback_OnDataResubmittedEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnDataResubmittedEvent value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnDataResubmittedEvent value0 = OnDataResubmittedEvent_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_OnDataResubmittedEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnDataResubmittedEvent value0)>(thisDeserializer.readPointer());
    Ark_OnDataResubmittedEvent value0 = OnDataResubmittedEvent_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_OnDownloadStartEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnDownloadStartEvent value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnDownloadStartEvent value0 = OnDownloadStartEvent_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_OnDownloadStartEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnDownloadStartEvent value0)>(thisDeserializer.readPointer());
    Ark_OnDownloadStartEvent value0 = OnDownloadStartEvent_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_OnErrorReceiveEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnErrorReceiveEvent value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnErrorReceiveEvent value0 = OnErrorReceiveEvent_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_OnErrorReceiveEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnErrorReceiveEvent value0)>(thisDeserializer.readPointer());
    Ark_OnErrorReceiveEvent value0 = OnErrorReceiveEvent_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_OnFaviconReceivedEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnFaviconReceivedEvent value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnFaviconReceivedEvent value0 = OnFaviconReceivedEvent_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_OnFaviconReceivedEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnFaviconReceivedEvent value0)>(thisDeserializer.readPointer());
    Ark_OnFaviconReceivedEvent value0 = OnFaviconReceivedEvent_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_OnFirstContentfulPaintEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnFirstContentfulPaintEvent value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnFirstContentfulPaintEvent value0 = OnFirstContentfulPaintEvent_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_OnFirstContentfulPaintEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnFirstContentfulPaintEvent value0)>(thisDeserializer.readPointer());
    Ark_OnFirstContentfulPaintEvent value0 = OnFirstContentfulPaintEvent_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_OnGeolocationShowEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnGeolocationShowEvent value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnGeolocationShowEvent value0 = OnGeolocationShowEvent_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_OnGeolocationShowEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnGeolocationShowEvent value0)>(thisDeserializer.readPointer());
    Ark_OnGeolocationShowEvent value0 = OnGeolocationShowEvent_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_OnHttpAuthRequestEvent_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnHttpAuthRequestEvent value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnHttpAuthRequestEvent value0 = OnHttpAuthRequestEvent_serializer::read(thisDeserializer);
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, value0, _continuation);
}
void deserializeAndCallSyncCallback_OnHttpAuthRequestEvent_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnHttpAuthRequestEvent value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    Ark_OnHttpAuthRequestEvent value0 = OnHttpAuthRequestEvent_serializer::read(thisDeserializer);
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _callSync(vmContext, _resourceId, value0, _continuation);
}
void deserializeAndCallCallback_OnHttpErrorReceiveEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnHttpErrorReceiveEvent value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnHttpErrorReceiveEvent value0 = OnHttpErrorReceiveEvent_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_OnHttpErrorReceiveEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnHttpErrorReceiveEvent value0)>(thisDeserializer.readPointer());
    Ark_OnHttpErrorReceiveEvent value0 = OnHttpErrorReceiveEvent_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_OnInterceptRequestEvent_WebResourceResponse(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnInterceptRequestEvent value0, const Callback_WebResourceResponse_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnInterceptRequestEvent value0 = OnInterceptRequestEvent_serializer::read(thisDeserializer);
    Callback_WebResourceResponse_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_WebResourceResponse value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_WebResourceResponse_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_WebResourceResponse value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_WebResourceResponse_Void))))};
    _call(_resourceId, value0, _continuation);
}
void deserializeAndCallSyncCallback_OnInterceptRequestEvent_WebResourceResponse(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnInterceptRequestEvent value0, const Callback_WebResourceResponse_Void continuation)>(thisDeserializer.readPointer());
    Ark_OnInterceptRequestEvent value0 = OnInterceptRequestEvent_serializer::read(thisDeserializer);
    Callback_WebResourceResponse_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_WebResourceResponse value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_WebResourceResponse_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_WebResourceResponse value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_WebResourceResponse_Void))))};
    _callSync(vmContext, _resourceId, value0, _continuation);
}
void deserializeAndCallCallback_OnLoadInterceptEvent_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnLoadInterceptEvent value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnLoadInterceptEvent value0 = OnLoadInterceptEvent_serializer::read(thisDeserializer);
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, value0, _continuation);
}
void deserializeAndCallSyncCallback_OnLoadInterceptEvent_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnLoadInterceptEvent value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    Ark_OnLoadInterceptEvent value0 = OnLoadInterceptEvent_serializer::read(thisDeserializer);
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _callSync(vmContext, _resourceId, value0, _continuation);
}
void deserializeAndCallCallback_onMeasureSize_SizeResult(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_GeometryInfo selfLayoutInfo, const Array_Measurable children, const Ark_ConstraintSizeOptions constraint, const Callback_SizeResult_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_GeometryInfo selfLayoutInfo = GeometryInfo_serializer::read(thisDeserializer);
    const Ark_Int32 children_buf_length = thisDeserializer.readInt32();
    Array_Measurable children_buf = {};
    thisDeserializer.resizeArray<std::decay<decltype(children_buf)>::type,
        std::decay<decltype(*children_buf.array)>::type>(&children_buf, children_buf_length);
    for (int children_buf_i = 0; children_buf_i < children_buf_length; children_buf_i++) {
        children_buf.array[children_buf_i] = static_cast<Ark_Measurable>(Measurable_serializer::read(thisDeserializer));
    }
    Array_Measurable children = children_buf;
    Ark_ConstraintSizeOptions constraint = ConstraintSizeOptions_serializer::read(thisDeserializer);
    Callback_SizeResult_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_SizeResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_SizeResult_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_SizeResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_SizeResult_Void))))};
    _call(_resourceId, selfLayoutInfo, children, constraint, _continuation);
}
void deserializeAndCallSyncCallback_onMeasureSize_SizeResult(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_GeometryInfo selfLayoutInfo, const Array_Measurable children, const Ark_ConstraintSizeOptions constraint, const Callback_SizeResult_Void continuation)>(thisDeserializer.readPointer());
    Ark_GeometryInfo selfLayoutInfo = GeometryInfo_serializer::read(thisDeserializer);
    const Ark_Int32 children_buf_length = thisDeserializer.readInt32();
    Array_Measurable children_buf = {};
    thisDeserializer.resizeArray<std::decay<decltype(children_buf)>::type,
        std::decay<decltype(*children_buf.array)>::type>(&children_buf, children_buf_length);
    for (int children_buf_i = 0; children_buf_i < children_buf_length; children_buf_i++) {
        children_buf.array[children_buf_i] = static_cast<Ark_Measurable>(Measurable_serializer::read(thisDeserializer));
    }
    Array_Measurable children = children_buf;
    Ark_ConstraintSizeOptions constraint = ConstraintSizeOptions_serializer::read(thisDeserializer);
    Callback_SizeResult_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_SizeResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_SizeResult_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_SizeResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_SizeResult_Void))))};
    _callSync(vmContext, _resourceId, selfLayoutInfo, children, constraint, _continuation);
}
void deserializeAndCallCallback_OnOverScrollEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnOverScrollEvent value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnOverScrollEvent value0 = OnOverScrollEvent_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_OnOverScrollEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnOverScrollEvent value0)>(thisDeserializer.readPointer());
    Ark_OnOverScrollEvent value0 = OnOverScrollEvent_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_OnPageBeginEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnPageBeginEvent value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnPageBeginEvent value0 = OnPageBeginEvent_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_OnPageBeginEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnPageBeginEvent value0)>(thisDeserializer.readPointer());
    Ark_OnPageBeginEvent value0 = OnPageBeginEvent_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_OnPageEndEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnPageEndEvent value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnPageEndEvent value0 = OnPageEndEvent_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_OnPageEndEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnPageEndEvent value0)>(thisDeserializer.readPointer());
    Ark_OnPageEndEvent value0 = OnPageEndEvent_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_OnPageVisibleEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnPageVisibleEvent value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnPageVisibleEvent value0 = OnPageVisibleEvent_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_OnPageVisibleEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnPageVisibleEvent value0)>(thisDeserializer.readPointer());
    Ark_OnPageVisibleEvent value0 = OnPageVisibleEvent_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_OnPermissionRequestEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnPermissionRequestEvent value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnPermissionRequestEvent value0 = OnPermissionRequestEvent_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_OnPermissionRequestEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnPermissionRequestEvent value0)>(thisDeserializer.readPointer());
    Ark_OnPermissionRequestEvent value0 = OnPermissionRequestEvent_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_onPlaceChildren_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_GeometryInfo selfLayoutInfo, const Array_Layoutable children, const Ark_ConstraintSizeOptions constraint)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_GeometryInfo selfLayoutInfo = GeometryInfo_serializer::read(thisDeserializer);
    const Ark_Int32 children_buf_length = thisDeserializer.readInt32();
    Array_Layoutable children_buf = {};
    thisDeserializer.resizeArray<std::decay<decltype(children_buf)>::type,
        std::decay<decltype(*children_buf.array)>::type>(&children_buf, children_buf_length);
    for (int children_buf_i = 0; children_buf_i < children_buf_length; children_buf_i++) {
        children_buf.array[children_buf_i] = static_cast<Ark_Layoutable>(Layoutable_serializer::read(thisDeserializer));
    }
    Array_Layoutable children = children_buf;
    Ark_ConstraintSizeOptions constraint = ConstraintSizeOptions_serializer::read(thisDeserializer);
    _call(_resourceId, selfLayoutInfo, children, constraint);
}
void deserializeAndCallSyncCallback_onPlaceChildren_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_GeometryInfo selfLayoutInfo, const Array_Layoutable children, const Ark_ConstraintSizeOptions constraint)>(thisDeserializer.readPointer());
    Ark_GeometryInfo selfLayoutInfo = GeometryInfo_serializer::read(thisDeserializer);
    const Ark_Int32 children_buf_length = thisDeserializer.readInt32();
    Array_Layoutable children_buf = {};
    thisDeserializer.resizeArray<std::decay<decltype(children_buf)>::type,
        std::decay<decltype(*children_buf.array)>::type>(&children_buf, children_buf_length);
    for (int children_buf_i = 0; children_buf_i < children_buf_length; children_buf_i++) {
        children_buf.array[children_buf_i] = static_cast<Ark_Layoutable>(Layoutable_serializer::read(thisDeserializer));
    }
    Array_Layoutable children = children_buf;
    Ark_ConstraintSizeOptions constraint = ConstraintSizeOptions_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, selfLayoutInfo, children, constraint);
}
void deserializeAndCallCallback_OnProgressChangeEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnProgressChangeEvent value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnProgressChangeEvent value0 = OnProgressChangeEvent_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_OnProgressChangeEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnProgressChangeEvent value0)>(thisDeserializer.readPointer());
    Ark_OnProgressChangeEvent value0 = OnProgressChangeEvent_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_OnPromptEvent_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnPromptEvent value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnPromptEvent value0 = OnPromptEvent_serializer::read(thisDeserializer);
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, value0, _continuation);
}
void deserializeAndCallSyncCallback_OnPromptEvent_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnPromptEvent value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    Ark_OnPromptEvent value0 = OnPromptEvent_serializer::read(thisDeserializer);
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _callSync(vmContext, _resourceId, value0, _continuation);
}
void deserializeAndCallCallback_OnRefreshAccessedHistoryEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnRefreshAccessedHistoryEvent value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnRefreshAccessedHistoryEvent value0 = OnRefreshAccessedHistoryEvent_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_OnRefreshAccessedHistoryEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnRefreshAccessedHistoryEvent value0)>(thisDeserializer.readPointer());
    Ark_OnRefreshAccessedHistoryEvent value0 = OnRefreshAccessedHistoryEvent_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_OnRenderExitedEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnRenderExitedEvent value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnRenderExitedEvent value0 = OnRenderExitedEvent_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_OnRenderExitedEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnRenderExitedEvent value0)>(thisDeserializer.readPointer());
    Ark_OnRenderExitedEvent value0 = OnRenderExitedEvent_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_OnResourceLoadEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnResourceLoadEvent value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnResourceLoadEvent value0 = OnResourceLoadEvent_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_OnResourceLoadEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnResourceLoadEvent value0)>(thisDeserializer.readPointer());
    Ark_OnResourceLoadEvent value0 = OnResourceLoadEvent_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_OnScaleChangeEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnScaleChangeEvent value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnScaleChangeEvent value0 = OnScaleChangeEvent_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_OnScaleChangeEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnScaleChangeEvent value0)>(thisDeserializer.readPointer());
    Ark_OnScaleChangeEvent value0 = OnScaleChangeEvent_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_OnScreenCaptureRequestEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnScreenCaptureRequestEvent value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnScreenCaptureRequestEvent value0 = OnScreenCaptureRequestEvent_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_OnScreenCaptureRequestEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnScreenCaptureRequestEvent value0)>(thisDeserializer.readPointer());
    Ark_OnScreenCaptureRequestEvent value0 = OnScreenCaptureRequestEvent_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_OnScrollEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnScrollEvent value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnScrollEvent value0 = OnScrollEvent_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_OnScrollEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnScrollEvent value0)>(thisDeserializer.readPointer());
    Ark_OnScrollEvent value0 = OnScrollEvent_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_OnScrollFrameBeginHandlerResult_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnScrollFrameBeginHandlerResult value)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnScrollFrameBeginHandlerResult value = OnScrollFrameBeginHandlerResult_serializer::read(thisDeserializer);
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_OnScrollFrameBeginHandlerResult_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnScrollFrameBeginHandlerResult value)>(thisDeserializer.readPointer());
    Ark_OnScrollFrameBeginHandlerResult value = OnScrollFrameBeginHandlerResult_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, value);
}
void deserializeAndCallCallback_OnSearchResultReceiveEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnSearchResultReceiveEvent value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnSearchResultReceiveEvent value0 = OnSearchResultReceiveEvent_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_OnSearchResultReceiveEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnSearchResultReceiveEvent value0)>(thisDeserializer.readPointer());
    Ark_OnSearchResultReceiveEvent value0 = OnSearchResultReceiveEvent_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_OnShowFileSelectorEvent_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnShowFileSelectorEvent value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnShowFileSelectorEvent value0 = OnShowFileSelectorEvent_serializer::read(thisDeserializer);
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, value0, _continuation);
}
void deserializeAndCallSyncCallback_OnShowFileSelectorEvent_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnShowFileSelectorEvent value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    Ark_OnShowFileSelectorEvent value0 = OnShowFileSelectorEvent_serializer::read(thisDeserializer);
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _callSync(vmContext, _resourceId, value0, _continuation);
}
void deserializeAndCallCallback_OnSslErrorEventReceiveEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnSslErrorEventReceiveEvent value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnSslErrorEventReceiveEvent value0 = OnSslErrorEventReceiveEvent_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_OnSslErrorEventReceiveEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnSslErrorEventReceiveEvent value0)>(thisDeserializer.readPointer());
    Ark_OnSslErrorEventReceiveEvent value0 = OnSslErrorEventReceiveEvent_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_OnTitleReceiveEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnTitleReceiveEvent value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnTitleReceiveEvent value0 = OnTitleReceiveEvent_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_OnTitleReceiveEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnTitleReceiveEvent value0)>(thisDeserializer.readPointer());
    Ark_OnTitleReceiveEvent value0 = OnTitleReceiveEvent_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_OnTouchIconUrlReceivedEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnTouchIconUrlReceivedEvent value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnTouchIconUrlReceivedEvent value0 = OnTouchIconUrlReceivedEvent_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_OnTouchIconUrlReceivedEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnTouchIconUrlReceivedEvent value0)>(thisDeserializer.readPointer());
    Ark_OnTouchIconUrlReceivedEvent value0 = OnTouchIconUrlReceivedEvent_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_OnWindowNewEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnWindowNewEvent value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnWindowNewEvent value0 = OnWindowNewEvent_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_OnWindowNewEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnWindowNewEvent value0)>(thisDeserializer.readPointer());
    Ark_OnWindowNewEvent value0 = OnWindowNewEvent_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_Opt_Array_FontDescriptor_Opt_Array_String_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_Array_CustomObject value, const Opt_Array_String error)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    const auto value_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Array_CustomObject value_buf = {};
    value_buf.tag = value_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((value_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        const Ark_Int32 value_buf__length = thisDeserializer.readInt32();
        Array_CustomObject value_buf_ = {};
        thisDeserializer.resizeArray<std::decay<decltype(value_buf_)>::type,
        std::decay<decltype(*value_buf_.array)>::type>(&value_buf_, value_buf__length);
        for (int value_buf__i = 0; value_buf__i < value_buf__length; value_buf__i++) {
            value_buf_.array[value_buf__i] = static_cast<Ark_CustomObject>(thisDeserializer.readCustomObject("object"));
        }
        value_buf.value = value_buf_;
    }
    Opt_Array_CustomObject value = value_buf;
    const auto error_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Array_String error_buf = {};
    error_buf.tag = error_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((error_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
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
void deserializeAndCallSyncCallback_Opt_Array_FontDescriptor_Opt_Array_String_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_Array_CustomObject value, const Opt_Array_String error)>(thisDeserializer.readPointer());
    const auto value_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Array_CustomObject value_buf = {};
    value_buf.tag = value_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((value_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        const Ark_Int32 value_buf__length = thisDeserializer.readInt32();
        Array_CustomObject value_buf_ = {};
        thisDeserializer.resizeArray<std::decay<decltype(value_buf_)>::type,
        std::decay<decltype(*value_buf_.array)>::type>(&value_buf_, value_buf__length);
        for (int value_buf__i = 0; value_buf__i < value_buf__length; value_buf__i++) {
            value_buf_.array[value_buf__i] = static_cast<Ark_CustomObject>(thisDeserializer.readCustomObject("object"));
        }
        value_buf.value = value_buf_;
    }
    Opt_Array_CustomObject value = value_buf;
    const auto error_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Array_String error_buf = {};
    error_buf.tag = error_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((error_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
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
void deserializeAndCallCallback_Opt_Array_NavDestinationTransition_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_Array_NavDestinationTransition value)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    const auto value_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Array_NavDestinationTransition value_buf = {};
    value_buf.tag = value_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((value_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        const Ark_Int32 value_buf__length = thisDeserializer.readInt32();
        Array_NavDestinationTransition value_buf_ = {};
        thisDeserializer.resizeArray<std::decay<decltype(value_buf_)>::type,
        std::decay<decltype(*value_buf_.array)>::type>(&value_buf_, value_buf__length);
        for (int value_buf__i = 0; value_buf__i < value_buf__length; value_buf__i++) {
            value_buf_.array[value_buf__i] = NavDestinationTransition_serializer::read(thisDeserializer);
        }
        value_buf.value = value_buf_;
    }
    Opt_Array_NavDestinationTransition value = value_buf;
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_Opt_Array_NavDestinationTransition_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_Array_NavDestinationTransition value)>(thisDeserializer.readPointer());
    const auto value_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Array_NavDestinationTransition value_buf = {};
    value_buf.tag = value_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((value_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        const Ark_Int32 value_buf__length = thisDeserializer.readInt32();
        Array_NavDestinationTransition value_buf_ = {};
        thisDeserializer.resizeArray<std::decay<decltype(value_buf_)>::type,
        std::decay<decltype(*value_buf_.array)>::type>(&value_buf_, value_buf__length);
        for (int value_buf__i = 0; value_buf__i < value_buf__length; value_buf__i++) {
            value_buf_.array[value_buf__i] = NavDestinationTransition_serializer::read(thisDeserializer);
        }
        value_buf.value = value_buf_;
    }
    Opt_Array_NavDestinationTransition value = value_buf;
    _callSync(vmContext, _resourceId, value);
}
void deserializeAndCallCallback_Opt_Array_String_Opt_Array_String_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_Array_String value, const Opt_Array_String error)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    const auto value_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Array_String value_buf = {};
    value_buf.tag = value_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((value_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        const Ark_Int32 value_buf__length = thisDeserializer.readInt32();
        Array_String value_buf_ = {};
        thisDeserializer.resizeArray<std::decay<decltype(value_buf_)>::type,
        std::decay<decltype(*value_buf_.array)>::type>(&value_buf_, value_buf__length);
        for (int value_buf__i = 0; value_buf__i < value_buf__length; value_buf__i++) {
            value_buf_.array[value_buf__i] = static_cast<Ark_String>(thisDeserializer.readString());
        }
        value_buf.value = value_buf_;
    }
    Opt_Array_String value = value_buf;
    const auto error_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Array_String error_buf = {};
    error_buf.tag = error_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((error_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
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
void deserializeAndCallSyncCallback_Opt_Array_String_Opt_Array_String_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_Array_String value, const Opt_Array_String error)>(thisDeserializer.readPointer());
    const auto value_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Array_String value_buf = {};
    value_buf.tag = value_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((value_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        const Ark_Int32 value_buf__length = thisDeserializer.readInt32();
        Array_String value_buf_ = {};
        thisDeserializer.resizeArray<std::decay<decltype(value_buf_)>::type,
        std::decay<decltype(*value_buf_.array)>::type>(&value_buf_, value_buf__length);
        for (int value_buf__i = 0; value_buf__i < value_buf__length; value_buf__i++) {
            value_buf_.array[value_buf__i] = static_cast<Ark_String>(thisDeserializer.readString());
        }
        value_buf.value = value_buf_;
    }
    Opt_Array_String value = value_buf;
    const auto error_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Array_String error_buf = {};
    error_buf.tag = error_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((error_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
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
void deserializeAndCallCallback_Opt_Array_String_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_Array_String error)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    const auto error_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Array_String error_buf = {};
    error_buf.tag = error_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((error_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
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
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_Array_String error)>(thisDeserializer.readPointer());
    const auto error_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Array_String error_buf = {};
    error_buf.tag = error_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((error_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
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
void deserializeAndCallCallback_Opt_Boolean_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_Boolean select)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    const auto select_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Boolean select_buf = {};
    select_buf.tag = select_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((select_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        select_buf.value = thisDeserializer.readBoolean();
    }
    Opt_Boolean select = select_buf;
    _call(_resourceId, select);
}
void deserializeAndCallSyncCallback_Opt_Boolean_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_Boolean select)>(thisDeserializer.readPointer());
    const auto select_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Boolean select_buf = {};
    select_buf.tag = select_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((select_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        select_buf.value = thisDeserializer.readBoolean();
    }
    Opt_Boolean select = select_buf;
    _callSync(vmContext, _resourceId, select);
}
void deserializeAndCallCallback_Opt_CustomBuilder_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_CustomNodeBuilder value)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    const auto value_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_CustomNodeBuilder value_buf = {};
    value_buf.tag = value_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((value_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        value_buf.value = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_CustomNodeBuilder)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_CustomNodeBuilder))))};
    }
    Opt_CustomNodeBuilder value = value_buf;
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_Opt_CustomBuilder_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_CustomNodeBuilder value)>(thisDeserializer.readPointer());
    const auto value_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_CustomNodeBuilder value_buf = {};
    value_buf.tag = value_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((value_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        value_buf.value = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_CustomNodeBuilder)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_CustomNodeBuilder))))};
    }
    Opt_CustomNodeBuilder value = value_buf;
    _callSync(vmContext, _resourceId, value);
}
void deserializeAndCallCallback_Opt_FontDescriptor_Opt_Array_String_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_CustomObject value, const Opt_Array_String error)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    const auto value_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_CustomObject value_buf = {};
    value_buf.tag = value_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((value_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        value_buf.value = static_cast<Ark_CustomObject>(thisDeserializer.readCustomObject("object"));
    }
    Opt_CustomObject value = value_buf;
    const auto error_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Array_String error_buf = {};
    error_buf.tag = error_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((error_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
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
void deserializeAndCallSyncCallback_Opt_FontDescriptor_Opt_Array_String_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_CustomObject value, const Opt_Array_String error)>(thisDeserializer.readPointer());
    const auto value_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_CustomObject value_buf = {};
    value_buf.tag = value_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((value_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        value_buf.value = static_cast<Ark_CustomObject>(thisDeserializer.readCustomObject("object"));
    }
    Opt_CustomObject value = value_buf;
    const auto error_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Array_String error_buf = {};
    error_buf.tag = error_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((error_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
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
void deserializeAndCallCallback_Opt_NavigationAnimatedTransition_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_NavigationAnimatedTransition value)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    const auto value_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_NavigationAnimatedTransition value_buf = {};
    value_buf.tag = value_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((value_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        value_buf.value = NavigationAnimatedTransition_serializer::read(thisDeserializer);
    }
    Opt_NavigationAnimatedTransition value = value_buf;
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_Opt_NavigationAnimatedTransition_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_NavigationAnimatedTransition value)>(thisDeserializer.readPointer());
    const auto value_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_NavigationAnimatedTransition value_buf = {};
    value_buf.tag = value_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((value_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        value_buf.value = NavigationAnimatedTransition_serializer::read(thisDeserializer);
    }
    Opt_NavigationAnimatedTransition value = value_buf;
    _callSync(vmContext, _resourceId, value);
}
void deserializeAndCallCallback_Opt_Number_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_Number selected)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    const auto selected_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Number selected_buf = {};
    selected_buf.tag = selected_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((selected_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        selected_buf.value = static_cast<Ark_Number>(thisDeserializer.readNumber());
    }
    Opt_Number selected = selected_buf;
    _call(_resourceId, selected);
}
void deserializeAndCallSyncCallback_Opt_Number_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_Number selected)>(thisDeserializer.readPointer());
    const auto selected_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Number selected_buf = {};
    selected_buf.tag = selected_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((selected_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        selected_buf.value = static_cast<Ark_Number>(thisDeserializer.readNumber());
    }
    Opt_Number selected = selected_buf;
    _callSync(vmContext, _resourceId, selected);
}
void deserializeAndCallCallback_Opt_Object_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_Object value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    const auto value0_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Object value0_buf = {};
    value0_buf.tag = value0_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((value0_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        value0_buf.value = static_cast<Ark_Object>(thisDeserializer.readObject());
    }
    Opt_Object value0 = value0_buf;
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_Opt_Object_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_Object value0)>(thisDeserializer.readPointer());
    const auto value0_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Object value0_buf = {};
    value0_buf.tag = value0_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((value0_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        value0_buf.value = static_cast<Ark_Object>(thisDeserializer.readObject());
    }
    Opt_Object value0 = value0_buf;
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_Opt_OffsetResult_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_OffsetResult value)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    const auto value_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_OffsetResult value_buf = {};
    value_buf.tag = value_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((value_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        value_buf.value = OffsetResult_serializer::read(thisDeserializer);
    }
    Opt_OffsetResult value = value_buf;
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_Opt_OffsetResult_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_OffsetResult value)>(thisDeserializer.readPointer());
    const auto value_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_OffsetResult value_buf = {};
    value_buf.tag = value_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((value_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        value_buf.value = OffsetResult_serializer::read(thisDeserializer);
    }
    Opt_OffsetResult value = value_buf;
    _callSync(vmContext, _resourceId, value);
}
void deserializeAndCallCallback_Opt_Scene_Opt_Array_String_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_Scene value, const Opt_Array_String error)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    const auto value_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Scene value_buf = {};
    value_buf.tag = value_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((value_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        value_buf.value = static_cast<Ark_Scene>(Scene_serializer::read(thisDeserializer));
    }
    Opt_Scene value = value_buf;
    const auto error_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Array_String error_buf = {};
    error_buf.tag = error_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((error_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
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
void deserializeAndCallSyncCallback_Opt_Scene_Opt_Array_String_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_Scene value, const Opt_Array_String error)>(thisDeserializer.readPointer());
    const auto value_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Scene value_buf = {};
    value_buf.tag = value_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((value_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        value_buf.value = static_cast<Ark_Scene>(Scene_serializer::read(thisDeserializer));
    }
    Opt_Scene value = value_buf;
    const auto error_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Array_String error_buf = {};
    error_buf.tag = error_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((error_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
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
void deserializeAndCallCallback_Opt_ScrollResult_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_ScrollResult value)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    const auto value_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_ScrollResult value_buf = {};
    value_buf.tag = value_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((value_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        value_buf.value = static_cast<Ark_ScrollResult>(ScrollResult_serializer::read(thisDeserializer));
    }
    Opt_ScrollResult value = value_buf;
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_Opt_ScrollResult_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_ScrollResult value)>(thisDeserializer.readPointer());
    const auto value_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_ScrollResult value_buf = {};
    value_buf.tag = value_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((value_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        value_buf.value = static_cast<Ark_ScrollResult>(ScrollResult_serializer::read(thisDeserializer));
    }
    Opt_ScrollResult value = value_buf;
    _callSync(vmContext, _resourceId, value);
}
void deserializeAndCallCallback_Opt_String_Opt_Array_String_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_String value, const Opt_Array_String error)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    const auto value_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_String value_buf = {};
    value_buf.tag = value_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((value_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        value_buf.value = static_cast<Ark_String>(thisDeserializer.readString());
    }
    Opt_String value = value_buf;
    const auto error_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Array_String error_buf = {};
    error_buf.tag = error_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((error_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
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
void deserializeAndCallSyncCallback_Opt_String_Opt_Array_String_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_String value, const Opt_Array_String error)>(thisDeserializer.readPointer());
    const auto value_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_String value_buf = {};
    value_buf.tag = value_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((value_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        value_buf.value = static_cast<Ark_String>(thisDeserializer.readString());
    }
    Opt_String value = value_buf;
    const auto error_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Array_String error_buf = {};
    error_buf.tag = error_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((error_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
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
void deserializeAndCallCallback_Opt_StyledString_Opt_Array_String_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_StyledString value, const Opt_Array_String error)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    const auto value_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_StyledString value_buf = {};
    value_buf.tag = value_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((value_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        value_buf.value = static_cast<Ark_StyledString>(StyledString_serializer::read(thisDeserializer));
    }
    Opt_StyledString value = value_buf;
    const auto error_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Array_String error_buf = {};
    error_buf.tag = error_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((error_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
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
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_StyledString value, const Opt_Array_String error)>(thisDeserializer.readPointer());
    const auto value_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_StyledString value_buf = {};
    value_buf.tag = value_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((value_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        value_buf.value = static_cast<Ark_StyledString>(StyledString_serializer::read(thisDeserializer));
    }
    Opt_StyledString value = value_buf;
    const auto error_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Array_String error_buf = {};
    error_buf.tag = error_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((error_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
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
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_TabContentAnimatedTransition value)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    const auto value_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_TabContentAnimatedTransition value_buf = {};
    value_buf.tag = value_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((value_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        value_buf.value = TabContentAnimatedTransition_serializer::read(thisDeserializer);
    }
    Opt_TabContentAnimatedTransition value = value_buf;
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_Opt_TabContentAnimatedTransition_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_TabContentAnimatedTransition value)>(thisDeserializer.readPointer());
    const auto value_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_TabContentAnimatedTransition value_buf = {};
    value_buf.tag = value_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((value_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        value_buf.value = TabContentAnimatedTransition_serializer::read(thisDeserializer);
    }
    Opt_TabContentAnimatedTransition value = value_buf;
    _callSync(vmContext, _resourceId, value);
}
void deserializeAndCallCallback_Opt_Union_Number_Resource_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_Union_Number_Resource selected)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    const auto selected_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Union_Number_Resource selected_buf = {};
    selected_buf.tag = selected_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((selected_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        const Ark_Int8 selected_buf__selector = thisDeserializer.readInt8();
        Ark_Union_Number_Resource selected_buf_ = {};
        selected_buf_.selector = selected_buf__selector;
        if (selected_buf__selector == 0) {
            selected_buf_.selector = 0;
            selected_buf_.value0 = static_cast<Ark_Number>(thisDeserializer.readNumber());
        }
        else if (selected_buf__selector == 1) {
            selected_buf_.selector = 1;
            selected_buf_.value1 = Resource_serializer::read(thisDeserializer);
        }
        else {
            INTEROP_FATAL("One of the branches for selected_buf_ has to be chosen through deserialisation.");
        }
        selected_buf.value = static_cast<Ark_Union_Number_Resource>(selected_buf_);
    }
    Opt_Union_Number_Resource selected = selected_buf;
    _call(_resourceId, selected);
}
void deserializeAndCallSyncCallback_Opt_Union_Number_Resource_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_Union_Number_Resource selected)>(thisDeserializer.readPointer());
    const auto selected_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Union_Number_Resource selected_buf = {};
    selected_buf.tag = selected_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((selected_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        const Ark_Int8 selected_buf__selector = thisDeserializer.readInt8();
        Ark_Union_Number_Resource selected_buf_ = {};
        selected_buf_.selector = selected_buf__selector;
        if (selected_buf__selector == 0) {
            selected_buf_.selector = 0;
            selected_buf_.value0 = static_cast<Ark_Number>(thisDeserializer.readNumber());
        }
        else if (selected_buf__selector == 1) {
            selected_buf_.selector = 1;
            selected_buf_.value1 = Resource_serializer::read(thisDeserializer);
        }
        else {
            INTEROP_FATAL("One of the branches for selected_buf_ has to be chosen through deserialisation.");
        }
        selected_buf.value = static_cast<Ark_Union_Number_Resource>(selected_buf_);
    }
    Opt_Union_Number_Resource selected = selected_buf;
    _callSync(vmContext, _resourceId, selected);
}
void deserializeAndCallCallback_Opt_Union_ResourceStr_String_Resource_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_Union_ResourceStr_String_Resource value)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    const auto value_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Union_ResourceStr_String_Resource value_buf = {};
    value_buf.tag = value_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((value_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        const Ark_Int8 value_buf__selector = thisDeserializer.readInt8();
        Ark_Union_ResourceStr_String_Resource value_buf_ = {};
        value_buf_.selector = value_buf__selector;
        if (value_buf__selector == 0) {
            value_buf_.selector = 0;
            const Ark_Int8 value_buf__u_selector = thisDeserializer.readInt8();
            Ark_ResourceStr value_buf__u = {};
            value_buf__u.selector = value_buf__u_selector;
            if (value_buf__u_selector == 0) {
                value_buf__u.selector = 0;
                value_buf__u.value0 = static_cast<Ark_String>(thisDeserializer.readString());
            }
            else if (value_buf__u_selector == 1) {
                value_buf__u.selector = 1;
                value_buf__u.value1 = Resource_serializer::read(thisDeserializer);
            }
            else {
                INTEROP_FATAL("One of the branches for value_buf__u has to be chosen through deserialisation.");
            }
            value_buf_.value0 = static_cast<Ark_ResourceStr>(value_buf__u);
        }
        else if (value_buf__selector == 1) {
            value_buf_.selector = 1;
            value_buf_.value1 = static_cast<Ark_String>(thisDeserializer.readString());
        }
        else if (value_buf__selector == 2) {
            value_buf_.selector = 2;
            value_buf_.value2 = Resource_serializer::read(thisDeserializer);
        }
        else {
            INTEROP_FATAL("One of the branches for value_buf_ has to be chosen through deserialisation.");
        }
        value_buf.value = static_cast<Ark_Union_ResourceStr_String_Resource>(value_buf_);
    }
    Opt_Union_ResourceStr_String_Resource value = value_buf;
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_Opt_Union_ResourceStr_String_Resource_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_Union_ResourceStr_String_Resource value)>(thisDeserializer.readPointer());
    const auto value_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Union_ResourceStr_String_Resource value_buf = {};
    value_buf.tag = value_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((value_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        const Ark_Int8 value_buf__selector = thisDeserializer.readInt8();
        Ark_Union_ResourceStr_String_Resource value_buf_ = {};
        value_buf_.selector = value_buf__selector;
        if (value_buf__selector == 0) {
            value_buf_.selector = 0;
            const Ark_Int8 value_buf__u_selector = thisDeserializer.readInt8();
            Ark_ResourceStr value_buf__u = {};
            value_buf__u.selector = value_buf__u_selector;
            if (value_buf__u_selector == 0) {
                value_buf__u.selector = 0;
                value_buf__u.value0 = static_cast<Ark_String>(thisDeserializer.readString());
            }
            else if (value_buf__u_selector == 1) {
                value_buf__u.selector = 1;
                value_buf__u.value1 = Resource_serializer::read(thisDeserializer);
            }
            else {
                INTEROP_FATAL("One of the branches for value_buf__u has to be chosen through deserialisation.");
            }
            value_buf_.value0 = static_cast<Ark_ResourceStr>(value_buf__u);
        }
        else if (value_buf__selector == 1) {
            value_buf_.selector = 1;
            value_buf_.value1 = static_cast<Ark_String>(thisDeserializer.readString());
        }
        else if (value_buf__selector == 2) {
            value_buf_.selector = 2;
            value_buf_.value2 = Resource_serializer::read(thisDeserializer);
        }
        else {
            INTEROP_FATAL("One of the branches for value_buf_ has to be chosen through deserialisation.");
        }
        value_buf.value = static_cast<Ark_Union_ResourceStr_String_Resource>(value_buf_);
    }
    Opt_Union_ResourceStr_String_Resource value = value_buf;
    _callSync(vmContext, _resourceId, value);
}
void deserializeAndCallCallback_PlaybackInfo_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_PlaybackInfo value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_PlaybackInfo value0 = PlaybackInfo_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_PlaybackInfo_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_PlaybackInfo value0)>(thisDeserializer.readPointer());
    Ark_PlaybackInfo value0 = PlaybackInfo_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_Pointer_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_NativePointer value = thisDeserializer.readPointer();
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_Pointer_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointer());
    Ark_NativePointer value = thisDeserializer.readPointer();
    _callSync(vmContext, _resourceId, value);
}
void deserializeAndCallCallback_PopInfo_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_PopInfo value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_PopInfo value0 = PopInfo_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_PopInfo_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_PopInfo value0)>(thisDeserializer.readPointer());
    Ark_PopInfo value0 = PopInfo_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_PreDragStatus_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_PreDragStatus value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_PreDragStatus value0 = static_cast<Ark_PreDragStatus>(thisDeserializer.readInt32());
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_PreDragStatus_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_PreDragStatus value0)>(thisDeserializer.readPointer());
    Ark_PreDragStatus value0 = static_cast<Ark_PreDragStatus>(thisDeserializer.readInt32());
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_PreparedInfo_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_PreparedInfo value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_PreparedInfo value0 = PreparedInfo_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_PreparedInfo_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_PreparedInfo value0)>(thisDeserializer.readPointer());
    Ark_PreparedInfo value0 = PreparedInfo_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_RangeUpdate(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Int32 start, const Ark_Int32 end)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Int32 start = thisDeserializer.readInt32();
    Ark_Int32 end = thisDeserializer.readInt32();
    _call(_resourceId, start, end);
}
void deserializeAndCallSyncCallback_RangeUpdate(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int32 start, const Ark_Int32 end)>(thisDeserializer.readPointer());
    Ark_Int32 start = thisDeserializer.readInt32();
    Ark_Int32 end = thisDeserializer.readInt32();
    _callSync(vmContext, _resourceId, start, end);
}
void deserializeAndCallCallback_RefreshStatus_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_RefreshStatus state)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_RefreshStatus state = static_cast<Ark_RefreshStatus>(thisDeserializer.readInt32());
    _call(_resourceId, state);
}
void deserializeAndCallSyncCallback_RefreshStatus_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_RefreshStatus state)>(thisDeserializer.readPointer());
    Ark_RefreshStatus state = static_cast<Ark_RefreshStatus>(thisDeserializer.readInt32());
    _callSync(vmContext, _resourceId, state);
}
void deserializeAndCallCallback_RichEditorChangeValue_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_RichEditorChangeValue value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_RichEditorChangeValue value0 = RichEditorChangeValue_serializer::read(thisDeserializer);
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, value0, _continuation);
}
void deserializeAndCallSyncCallback_RichEditorChangeValue_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_RichEditorChangeValue value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    Ark_RichEditorChangeValue value0 = RichEditorChangeValue_serializer::read(thisDeserializer);
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _callSync(vmContext, _resourceId, value0, _continuation);
}
void deserializeAndCallCallback_RichEditorDeleteValue_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_RichEditorDeleteValue value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_RichEditorDeleteValue value0 = RichEditorDeleteValue_serializer::read(thisDeserializer);
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, value0, _continuation);
}
void deserializeAndCallSyncCallback_RichEditorDeleteValue_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_RichEditorDeleteValue value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    Ark_RichEditorDeleteValue value0 = RichEditorDeleteValue_serializer::read(thisDeserializer);
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _callSync(vmContext, _resourceId, value0, _continuation);
}
void deserializeAndCallCallback_RichEditorInsertValue_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_RichEditorInsertValue value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_RichEditorInsertValue value0 = RichEditorInsertValue_serializer::read(thisDeserializer);
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, value0, _continuation);
}
void deserializeAndCallSyncCallback_RichEditorInsertValue_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_RichEditorInsertValue value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    Ark_RichEditorInsertValue value0 = RichEditorInsertValue_serializer::read(thisDeserializer);
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _callSync(vmContext, _resourceId, value0, _continuation);
}
void deserializeAndCallCallback_RichEditorRange_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_RichEditorRange value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_RichEditorRange value0 = RichEditorRange_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_RichEditorRange_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_RichEditorRange value0)>(thisDeserializer.readPointer());
    Ark_RichEditorRange value0 = RichEditorRange_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_RichEditorSelection_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_RichEditorSelection value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_RichEditorSelection value0 = RichEditorSelection_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_RichEditorSelection_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_RichEditorSelection value0)>(thisDeserializer.readPointer());
    Ark_RichEditorSelection value0 = RichEditorSelection_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_RichEditorTextSpanResult_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_RichEditorTextSpanResult value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_RichEditorTextSpanResult value0 = RichEditorTextSpanResult_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_RichEditorTextSpanResult_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_RichEditorTextSpanResult value0)>(thisDeserializer.readPointer());
    Ark_RichEditorTextSpanResult value0 = RichEditorTextSpanResult_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_RotationGesture(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Callback_RotationGesture_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Callback_RotationGesture_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_RotationGesture value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_RotationGesture_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_RotationGesture value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_RotationGesture_Void))))};
    _call(_resourceId, _continuation);
}
void deserializeAndCallSyncCallback_RotationGesture(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Callback_RotationGesture_Void continuation)>(thisDeserializer.readPointer());
    Callback_RotationGesture_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_RotationGesture value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_RotationGesture_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_RotationGesture value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_RotationGesture_Void))))};
    _callSync(vmContext, _resourceId, _continuation);
}
void deserializeAndCallCallback_RotationGesture_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_RotationGesture value)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_RotationGesture value = static_cast<Ark_RotationGesture>(RotationGesture_serializer::read(thisDeserializer));
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_RotationGesture_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_RotationGesture value)>(thisDeserializer.readPointer());
    Ark_RotationGesture value = static_cast<Ark_RotationGesture>(RotationGesture_serializer::read(thisDeserializer));
    _callSync(vmContext, _resourceId, value);
}
void deserializeAndCallCallback_SheetDismiss_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_SheetDismiss sheetDismiss)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_SheetDismiss sheetDismiss = SheetDismiss_serializer::read(thisDeserializer);
    _call(_resourceId, sheetDismiss);
}
void deserializeAndCallSyncCallback_SheetDismiss_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_SheetDismiss sheetDismiss)>(thisDeserializer.readPointer());
    Ark_SheetDismiss sheetDismiss = SheetDismiss_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, sheetDismiss);
}
void deserializeAndCallCallback_SheetType_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_SheetType value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_SheetType value0 = static_cast<Ark_SheetType>(thisDeserializer.readInt32());
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_SheetType_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_SheetType value0)>(thisDeserializer.readPointer());
    Ark_SheetType value0 = static_cast<Ark_SheetType>(thisDeserializer.readInt32());
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_SizeResult_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_SizeResult value)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_SizeResult value = SizeResult_serializer::read(thisDeserializer);
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_SizeResult_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_SizeResult value)>(thisDeserializer.readPointer());
    Ark_SizeResult value = SizeResult_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, value);
}
void deserializeAndCallCallback_SpringBackAction_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_SpringBackAction value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_SpringBackAction value0 = SpringBackAction_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_SpringBackAction_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_SpringBackAction value0)>(thisDeserializer.readPointer());
    Ark_SpringBackAction value0 = SpringBackAction_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_StateStylesChange(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Int32 currentState)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Int32 currentState = thisDeserializer.readInt32();
    _call(_resourceId, currentState);
}
void deserializeAndCallSyncCallback_StateStylesChange(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int32 currentState)>(thisDeserializer.readPointer());
    Ark_Int32 currentState = thisDeserializer.readInt32();
    _callSync(vmContext, _resourceId, currentState);
}
void deserializeAndCallCallback_String_PasteEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_String value, const Ark_PasteEvent event)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_String value = static_cast<Ark_String>(thisDeserializer.readString());
    Ark_PasteEvent event = PasteEvent_serializer::read(thisDeserializer);
    _call(_resourceId, value, event);
}
void deserializeAndCallSyncCallback_String_PasteEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_String value, const Ark_PasteEvent event)>(thisDeserializer.readPointer());
    Ark_String value = static_cast<Ark_String>(thisDeserializer.readString());
    Ark_PasteEvent event = PasteEvent_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, value, event);
}
void deserializeAndCallCallback_String_SurfaceRect_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_String surfaceId, const Ark_SurfaceRect rect)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_String surfaceId = static_cast<Ark_String>(thisDeserializer.readString());
    Ark_SurfaceRect rect = SurfaceRect_serializer::read(thisDeserializer);
    _call(_resourceId, surfaceId, rect);
}
void deserializeAndCallSyncCallback_String_SurfaceRect_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_String surfaceId, const Ark_SurfaceRect rect)>(thisDeserializer.readPointer());
    Ark_String surfaceId = static_cast<Ark_String>(thisDeserializer.readString());
    Ark_SurfaceRect rect = SurfaceRect_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, surfaceId, rect);
}
void deserializeAndCallCallback_String_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_String breakpoints)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_String breakpoints = static_cast<Ark_String>(thisDeserializer.readString());
    _call(_resourceId, breakpoints);
}
void deserializeAndCallSyncCallback_String_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_String breakpoints)>(thisDeserializer.readPointer());
    Ark_String breakpoints = static_cast<Ark_String>(thisDeserializer.readString());
    _callSync(vmContext, _resourceId, breakpoints);
}
void deserializeAndCallCallback_StyledStringChangeValue_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_StyledStringChangeValue value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_StyledStringChangeValue value0 = StyledStringChangeValue_serializer::read(thisDeserializer);
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, value0, _continuation);
}
void deserializeAndCallSyncCallback_StyledStringChangeValue_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_StyledStringChangeValue value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    Ark_StyledStringChangeValue value0 = StyledStringChangeValue_serializer::read(thisDeserializer);
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _callSync(vmContext, _resourceId, value0, _continuation);
}
void deserializeAndCallCallback_StyledStringMarshallingValue_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_UserDataSpan value)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_UserDataSpan value = static_cast<Ark_UserDataSpan>(UserDataSpan_serializer::read(thisDeserializer));
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_StyledStringMarshallingValue_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_UserDataSpan value)>(thisDeserializer.readPointer());
    Ark_UserDataSpan value = static_cast<Ark_UserDataSpan>(UserDataSpan_serializer::read(thisDeserializer));
    _callSync(vmContext, _resourceId, value);
}
void deserializeAndCallCallback_SwipeActionState_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_SwipeActionState state)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_SwipeActionState state = static_cast<Ark_SwipeActionState>(thisDeserializer.readInt32());
    _call(_resourceId, state);
}
void deserializeAndCallSyncCallback_SwipeActionState_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_SwipeActionState state)>(thisDeserializer.readPointer());
    Ark_SwipeActionState state = static_cast<Ark_SwipeActionState>(thisDeserializer.readInt32());
    _callSync(vmContext, _resourceId, state);
}
void deserializeAndCallCallback_SwipeGesture(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Callback_SwipeGesture_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Callback_SwipeGesture_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_SwipeGesture value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_SwipeGesture_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_SwipeGesture value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_SwipeGesture_Void))))};
    _call(_resourceId, _continuation);
}
void deserializeAndCallSyncCallback_SwipeGesture(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Callback_SwipeGesture_Void continuation)>(thisDeserializer.readPointer());
    Callback_SwipeGesture_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_SwipeGesture value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_SwipeGesture_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_SwipeGesture value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_SwipeGesture_Void))))};
    _callSync(vmContext, _resourceId, _continuation);
}
void deserializeAndCallCallback_SwipeGesture_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_SwipeGesture value)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_SwipeGesture value = static_cast<Ark_SwipeGesture>(SwipeGesture_serializer::read(thisDeserializer));
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_SwipeGesture_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_SwipeGesture value)>(thisDeserializer.readPointer());
    Ark_SwipeGesture value = static_cast<Ark_SwipeGesture>(SwipeGesture_serializer::read(thisDeserializer));
    _callSync(vmContext, _resourceId, value);
}
void deserializeAndCallCallback_SwiperContentTransitionProxy_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_SwiperContentTransitionProxy value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_SwiperContentTransitionProxy value0 = static_cast<Ark_SwiperContentTransitionProxy>(SwiperContentTransitionProxy_serializer::read(thisDeserializer));
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_SwiperContentTransitionProxy_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_SwiperContentTransitionProxy value0)>(thisDeserializer.readPointer());
    Ark_SwiperContentTransitionProxy value0 = static_cast<Ark_SwiperContentTransitionProxy>(SwiperContentTransitionProxy_serializer::read(thisDeserializer));
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_TabContentTransitionProxy_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_TabContentTransitionProxy value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_TabContentTransitionProxy value0 = static_cast<Ark_TabContentTransitionProxy>(TabContentTransitionProxy_serializer::read(thisDeserializer));
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_TabContentTransitionProxy_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_TabContentTransitionProxy value0)>(thisDeserializer.readPointer());
    Ark_TabContentTransitionProxy value0 = static_cast<Ark_TabContentTransitionProxy>(TabContentTransitionProxy_serializer::read(thisDeserializer));
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_TerminationInfo_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_TerminationInfo value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_TerminationInfo value0 = TerminationInfo_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_TerminationInfo_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_TerminationInfo value0)>(thisDeserializer.readPointer());
    Ark_TerminationInfo value0 = TerminationInfo_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_TextPickerResult_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_TextPickerResult value)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_TextPickerResult value = TextPickerResult_serializer::read(thisDeserializer);
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_TextPickerResult_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_TextPickerResult value)>(thisDeserializer.readPointer());
    Ark_TextPickerResult value = TextPickerResult_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, value);
}
void deserializeAndCallCallback_TextRange_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_TextRange value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_TextRange value0 = TextRange_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_TextRange_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_TextRange value0)>(thisDeserializer.readPointer());
    Ark_TextRange value0 = TextRange_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_TimePickerResult_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_TimePickerResult value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_TimePickerResult value0 = TimePickerResult_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_TimePickerResult_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_TimePickerResult value0)>(thisDeserializer.readPointer());
    Ark_TimePickerResult value0 = TimePickerResult_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_TouchEvent_HitTestMode(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_TouchEvent value0, const Callback_HitTestMode_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_TouchEvent value0 = static_cast<Ark_TouchEvent>(TouchEvent_serializer::read(thisDeserializer));
    Callback_HitTestMode_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_HitTestMode value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_HitTestMode_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_HitTestMode value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_HitTestMode_Void))))};
    _call(_resourceId, value0, _continuation);
}
void deserializeAndCallSyncCallback_TouchEvent_HitTestMode(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_TouchEvent value0, const Callback_HitTestMode_Void continuation)>(thisDeserializer.readPointer());
    Ark_TouchEvent value0 = static_cast<Ark_TouchEvent>(TouchEvent_serializer::read(thisDeserializer));
    Callback_HitTestMode_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_HitTestMode value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_HitTestMode_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_HitTestMode value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_HitTestMode_Void))))};
    _callSync(vmContext, _resourceId, value0, _continuation);
}
void deserializeAndCallCallback_TouchEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_TouchEvent event)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_TouchEvent event = static_cast<Ark_TouchEvent>(TouchEvent_serializer::read(thisDeserializer));
    _call(_resourceId, event);
}
void deserializeAndCallSyncCallback_TouchEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_TouchEvent event)>(thisDeserializer.readPointer());
    Ark_TouchEvent event = static_cast<Ark_TouchEvent>(TouchEvent_serializer::read(thisDeserializer));
    _callSync(vmContext, _resourceId, event);
}
void deserializeAndCallCallback_TouchResult_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_TouchResult value)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_TouchResult value = TouchResult_serializer::read(thisDeserializer);
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_TouchResult_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_TouchResult value)>(thisDeserializer.readPointer());
    Ark_TouchResult value = TouchResult_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, value);
}
void deserializeAndCallCallback_Tuple_Number_Number_Number_Number_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
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
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
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
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
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
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Tuple_Number_Number value)>(thisDeserializer.readPointer());
    Ark_Tuple_Number_Number value_buf = {};
    value_buf.value0 = static_cast<Ark_Number>(thisDeserializer.readNumber());
    value_buf.value1 = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Tuple_Number_Number value = value_buf;
    _callSync(vmContext, _resourceId, value);
}
void deserializeAndCallCallback_UIExtensionProxy_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_UIExtensionProxy value0)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_UIExtensionProxy value0 = static_cast<Ark_UIExtensionProxy>(UIExtensionProxy_serializer::read(thisDeserializer));
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_UIExtensionProxy_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_UIExtensionProxy value0)>(thisDeserializer.readPointer());
    Ark_UIExtensionProxy value0 = static_cast<Ark_UIExtensionProxy>(UIExtensionProxy_serializer::read(thisDeserializer));
    _callSync(vmContext, _resourceId, value0);
}
void deserializeAndCallCallback_Union_CustomBuilder_DragItemInfo_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
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
        value_buf.value1 = DragItemInfo_serializer::read(thisDeserializer);
    }
    else {
        INTEROP_FATAL("One of the branches for value_buf has to be chosen through deserialisation.");
    }
    Ark_Union_CustomBuilder_DragItemInfo value = static_cast<Ark_Union_CustomBuilder_DragItemInfo>(value_buf);
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_Union_CustomBuilder_DragItemInfo_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
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
        value_buf.value1 = DragItemInfo_serializer::read(thisDeserializer);
    }
    else {
        INTEROP_FATAL("One of the branches for value_buf has to be chosen through deserialisation.");
    }
    Ark_Union_CustomBuilder_DragItemInfo value = static_cast<Ark_Union_CustomBuilder_DragItemInfo>(value_buf);
    _callSync(vmContext, _resourceId, value);
}
void deserializeAndCallCallback_Union_Number_Array_Number_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
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
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
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
void deserializeAndCallCallback_Union_ResourceStr_Array_ResourceStr_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Union_ResourceStr_Array_ResourceStr value)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    const Ark_Int8 value_buf_selector = thisDeserializer.readInt8();
    Ark_Union_ResourceStr_Array_ResourceStr value_buf = {};
    value_buf.selector = value_buf_selector;
    if (value_buf_selector == 0) {
        value_buf.selector = 0;
        const Ark_Int8 value_buf_u_selector = thisDeserializer.readInt8();
        Ark_ResourceStr value_buf_u = {};
        value_buf_u.selector = value_buf_u_selector;
        if (value_buf_u_selector == 0) {
            value_buf_u.selector = 0;
            value_buf_u.value0 = static_cast<Ark_String>(thisDeserializer.readString());
        }
        else if (value_buf_u_selector == 1) {
            value_buf_u.selector = 1;
            value_buf_u.value1 = Resource_serializer::read(thisDeserializer);
        }
        else {
            INTEROP_FATAL("One of the branches for value_buf_u has to be chosen through deserialisation.");
        }
        value_buf.value0 = static_cast<Ark_ResourceStr>(value_buf_u);
    }
    else if (value_buf_selector == 1) {
        value_buf.selector = 1;
        const Ark_Int32 value_buf_u_length = thisDeserializer.readInt32();
        Array_ResourceStr value_buf_u = {};
        thisDeserializer.resizeArray<std::decay<decltype(value_buf_u)>::type,
        std::decay<decltype(*value_buf_u.array)>::type>(&value_buf_u, value_buf_u_length);
        for (int value_buf_u_i = 0; value_buf_u_i < value_buf_u_length; value_buf_u_i++) {
            const Ark_Int8 value_buf_u_buf_selector = thisDeserializer.readInt8();
            Ark_ResourceStr value_buf_u_buf = {};
            value_buf_u_buf.selector = value_buf_u_buf_selector;
            if (value_buf_u_buf_selector == 0) {
                value_buf_u_buf.selector = 0;
                value_buf_u_buf.value0 = static_cast<Ark_String>(thisDeserializer.readString());
            }
            else if (value_buf_u_buf_selector == 1) {
                value_buf_u_buf.selector = 1;
                value_buf_u_buf.value1 = Resource_serializer::read(thisDeserializer);
            }
            else {
                INTEROP_FATAL("One of the branches for value_buf_u_buf has to be chosen through deserialisation.");
            }
            value_buf_u.array[value_buf_u_i] = static_cast<Ark_ResourceStr>(value_buf_u_buf);
        }
        value_buf.value1 = value_buf_u;
    }
    else {
        INTEROP_FATAL("One of the branches for value_buf has to be chosen through deserialisation.");
    }
    Ark_Union_ResourceStr_Array_ResourceStr value = static_cast<Ark_Union_ResourceStr_Array_ResourceStr>(value_buf);
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_Union_ResourceStr_Array_ResourceStr_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Union_ResourceStr_Array_ResourceStr value)>(thisDeserializer.readPointer());
    const Ark_Int8 value_buf_selector = thisDeserializer.readInt8();
    Ark_Union_ResourceStr_Array_ResourceStr value_buf = {};
    value_buf.selector = value_buf_selector;
    if (value_buf_selector == 0) {
        value_buf.selector = 0;
        const Ark_Int8 value_buf_u_selector = thisDeserializer.readInt8();
        Ark_ResourceStr value_buf_u = {};
        value_buf_u.selector = value_buf_u_selector;
        if (value_buf_u_selector == 0) {
            value_buf_u.selector = 0;
            value_buf_u.value0 = static_cast<Ark_String>(thisDeserializer.readString());
        }
        else if (value_buf_u_selector == 1) {
            value_buf_u.selector = 1;
            value_buf_u.value1 = Resource_serializer::read(thisDeserializer);
        }
        else {
            INTEROP_FATAL("One of the branches for value_buf_u has to be chosen through deserialisation.");
        }
        value_buf.value0 = static_cast<Ark_ResourceStr>(value_buf_u);
    }
    else if (value_buf_selector == 1) {
        value_buf.selector = 1;
        const Ark_Int32 value_buf_u_length = thisDeserializer.readInt32();
        Array_ResourceStr value_buf_u = {};
        thisDeserializer.resizeArray<std::decay<decltype(value_buf_u)>::type,
        std::decay<decltype(*value_buf_u.array)>::type>(&value_buf_u, value_buf_u_length);
        for (int value_buf_u_i = 0; value_buf_u_i < value_buf_u_length; value_buf_u_i++) {
            const Ark_Int8 value_buf_u_buf_selector = thisDeserializer.readInt8();
            Ark_ResourceStr value_buf_u_buf = {};
            value_buf_u_buf.selector = value_buf_u_buf_selector;
            if (value_buf_u_buf_selector == 0) {
                value_buf_u_buf.selector = 0;
                value_buf_u_buf.value0 = static_cast<Ark_String>(thisDeserializer.readString());
            }
            else if (value_buf_u_buf_selector == 1) {
                value_buf_u_buf.selector = 1;
                value_buf_u_buf.value1 = Resource_serializer::read(thisDeserializer);
            }
            else {
                INTEROP_FATAL("One of the branches for value_buf_u_buf has to be chosen through deserialisation.");
            }
            value_buf_u.array[value_buf_u_i] = static_cast<Ark_ResourceStr>(value_buf_u_buf);
        }
        value_buf.value1 = value_buf_u;
    }
    else {
        INTEROP_FATAL("One of the branches for value_buf has to be chosen through deserialisation.");
    }
    Ark_Union_ResourceStr_Array_ResourceStr value = static_cast<Ark_Union_ResourceStr_Array_ResourceStr>(value_buf);
    _callSync(vmContext, _resourceId, value);
}
void deserializeAndCallCallback_Union_ResourceStr_Resource_String_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Union_ResourceStr_Resource_String text)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    const Ark_Int8 text_buf_selector = thisDeserializer.readInt8();
    Ark_Union_ResourceStr_Resource_String text_buf = {};
    text_buf.selector = text_buf_selector;
    if (text_buf_selector == 0) {
        text_buf.selector = 0;
        const Ark_Int8 text_buf_u_selector = thisDeserializer.readInt8();
        Ark_ResourceStr text_buf_u = {};
        text_buf_u.selector = text_buf_u_selector;
        if (text_buf_u_selector == 0) {
            text_buf_u.selector = 0;
            text_buf_u.value0 = static_cast<Ark_String>(thisDeserializer.readString());
        }
        else if (text_buf_u_selector == 1) {
            text_buf_u.selector = 1;
            text_buf_u.value1 = Resource_serializer::read(thisDeserializer);
        }
        else {
            INTEROP_FATAL("One of the branches for text_buf_u has to be chosen through deserialisation.");
        }
        text_buf.value0 = static_cast<Ark_ResourceStr>(text_buf_u);
    }
    else if (text_buf_selector == 1) {
        text_buf.selector = 1;
        text_buf.value1 = Resource_serializer::read(thisDeserializer);
    }
    else if (text_buf_selector == 2) {
        text_buf.selector = 2;
        text_buf.value2 = static_cast<Ark_String>(thisDeserializer.readString());
    }
    else {
        INTEROP_FATAL("One of the branches for text_buf has to be chosen through deserialisation.");
    }
    Ark_Union_ResourceStr_Resource_String text = static_cast<Ark_Union_ResourceStr_Resource_String>(text_buf);
    _call(_resourceId, text);
}
void deserializeAndCallSyncCallback_Union_ResourceStr_Resource_String_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Union_ResourceStr_Resource_String text)>(thisDeserializer.readPointer());
    const Ark_Int8 text_buf_selector = thisDeserializer.readInt8();
    Ark_Union_ResourceStr_Resource_String text_buf = {};
    text_buf.selector = text_buf_selector;
    if (text_buf_selector == 0) {
        text_buf.selector = 0;
        const Ark_Int8 text_buf_u_selector = thisDeserializer.readInt8();
        Ark_ResourceStr text_buf_u = {};
        text_buf_u.selector = text_buf_u_selector;
        if (text_buf_u_selector == 0) {
            text_buf_u.selector = 0;
            text_buf_u.value0 = static_cast<Ark_String>(thisDeserializer.readString());
        }
        else if (text_buf_u_selector == 1) {
            text_buf_u.selector = 1;
            text_buf_u.value1 = Resource_serializer::read(thisDeserializer);
        }
        else {
            INTEROP_FATAL("One of the branches for text_buf_u has to be chosen through deserialisation.");
        }
        text_buf.value0 = static_cast<Ark_ResourceStr>(text_buf_u);
    }
    else if (text_buf_selector == 1) {
        text_buf.selector = 1;
        text_buf.value1 = Resource_serializer::read(thisDeserializer);
    }
    else if (text_buf_selector == 2) {
        text_buf.selector = 2;
        text_buf.value2 = static_cast<Ark_String>(thisDeserializer.readString());
    }
    else {
        INTEROP_FATAL("One of the branches for text_buf has to be chosen through deserialisation.");
    }
    Ark_Union_ResourceStr_Resource_String text = static_cast<Ark_Union_ResourceStr_Resource_String>(text_buf);
    _callSync(vmContext, _resourceId, text);
}
void deserializeAndCallCallback_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    _call(_resourceId);
}
void deserializeAndCallSyncCallback_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId)>(thisDeserializer.readPointer());
    _callSync(vmContext, _resourceId);
}
void deserializeAndCallCallback_WebKeyboardOptions_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_WebKeyboardOptions value)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_WebKeyboardOptions value = WebKeyboardOptions_serializer::read(thisDeserializer);
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_WebKeyboardOptions_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_WebKeyboardOptions value)>(thisDeserializer.readPointer());
    Ark_WebKeyboardOptions value = WebKeyboardOptions_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, value);
}
void deserializeAndCallCallback_WebResourceResponse_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_WebResourceResponse value)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_WebResourceResponse value = static_cast<Ark_WebResourceResponse>(WebResourceResponse_serializer::read(thisDeserializer));
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_WebResourceResponse_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_WebResourceResponse value)>(thisDeserializer.readPointer());
    Ark_WebResourceResponse value = static_cast<Ark_WebResourceResponse>(WebResourceResponse_serializer::read(thisDeserializer));
    _callSync(vmContext, _resourceId, value);
}
void deserializeAndCallCheckBoxModifierBuilder(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Ark_CheckBoxConfiguration config, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_CheckBoxConfiguration config = CheckBoxConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Pointer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Pointer_Void))))};
    _call(_resourceId, parentNode, config, _continuation);
}
void deserializeAndCallSyncCheckBoxModifierBuilder(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Ark_CheckBoxConfiguration config, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointer());
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_CheckBoxConfiguration config = CheckBoxConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Pointer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Pointer_Void))))};
    _callSync(vmContext, _resourceId, parentNode, config, _continuation);
}
void deserializeAndCallCompatibleInitCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Callback_CompatibleComponentInfo_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Callback_CompatibleComponentInfo_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_CompatibleComponentInfo value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_CompatibleComponentInfo_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_CompatibleComponentInfo value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_CompatibleComponentInfo_Void))))};
    _call(_resourceId, _continuation);
}
void deserializeAndCallSyncCompatibleInitCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Callback_CompatibleComponentInfo_Void continuation)>(thisDeserializer.readPointer());
    Callback_CompatibleComponentInfo_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_CompatibleComponentInfo value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_CompatibleComponentInfo_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_CompatibleComponentInfo value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_CompatibleComponentInfo_Void))))};
    _callSync(vmContext, _resourceId, _continuation);
}
void deserializeAndCallCompatibleUpdateCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_CustomObject component)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_CustomObject component = static_cast<Ark_CustomObject>(thisDeserializer.readCustomObject("object"));
    _call(_resourceId, component);
}
void deserializeAndCallSyncCompatibleUpdateCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_CustomObject component)>(thisDeserializer.readPointer());
    Ark_CustomObject component = static_cast<Ark_CustomObject>(thisDeserializer.readCustomObject("object"));
    _callSync(vmContext, _resourceId, component);
}
void deserializeAndCallContentDidScrollCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
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
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number selectedIndex, const Ark_Number index, const Ark_Number position, const Ark_Number mainAxisLength)>(thisDeserializer.readPointer());
    Ark_Number selectedIndex = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number position = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number mainAxisLength = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _callSync(vmContext, _resourceId, selectedIndex, index, position, mainAxisLength);
}
void deserializeAndCallContentWillScrollCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_SwiperContentWillScrollResult result, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_SwiperContentWillScrollResult result = SwiperContentWillScrollResult_serializer::read(thisDeserializer);
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, result, _continuation);
}
void deserializeAndCallSyncContentWillScrollCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_SwiperContentWillScrollResult result, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    Ark_SwiperContentWillScrollResult result = SwiperContentWillScrollResult_serializer::read(thisDeserializer);
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _callSync(vmContext, _resourceId, result, _continuation);
}
void deserializeAndCallContext_getGroupDir_Callback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_String result)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_String result = static_cast<Ark_String>(thisDeserializer.readString());
    _call(_resourceId, result);
}
void deserializeAndCallSyncContext_getGroupDir_Callback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_String result)>(thisDeserializer.readPointer());
    Ark_String result = static_cast<Ark_String>(thisDeserializer.readString());
    _callSync(vmContext, _resourceId, result);
}
void deserializeAndCallCustomNodeBuilder(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Callback_Pointer_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Pointer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Pointer_Void))))};
    _call(_resourceId, parentNode, _continuation);
}
void deserializeAndCallSyncCustomNodeBuilder(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointer());
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Callback_Pointer_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Pointer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Pointer_Void))))};
    _callSync(vmContext, _resourceId, parentNode, _continuation);
}
void deserializeAndCallCustomStyles(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_String instance)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_String instance = static_cast<Ark_String>(thisDeserializer.readString());
    _call(_resourceId, instance);
}
void deserializeAndCallSyncCustomStyles(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_String instance)>(thisDeserializer.readPointer());
    Ark_String instance = static_cast<Ark_String>(thisDeserializer.readString());
    _callSync(vmContext, _resourceId, instance);
}
void deserializeAndCallDataPanelModifierBuilder(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Ark_DataPanelConfiguration config, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_DataPanelConfiguration config = DataPanelConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Pointer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Pointer_Void))))};
    _call(_resourceId, parentNode, config, _continuation);
}
void deserializeAndCallSyncDataPanelModifierBuilder(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Ark_DataPanelConfiguration config, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointer());
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_DataPanelConfiguration config = DataPanelConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Pointer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Pointer_Void))))};
    _callSync(vmContext, _resourceId, parentNode, config, _continuation);
}
void deserializeAndCallEditableTextOnChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_String value, const Opt_PreviewText previewText, const Opt_TextChangeOptions options)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_String value = static_cast<Ark_String>(thisDeserializer.readString());
    const auto previewText_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_PreviewText previewText_buf = {};
    previewText_buf.tag = previewText_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((previewText_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        previewText_buf.value = PreviewText_serializer::read(thisDeserializer);
    }
    Opt_PreviewText previewText = previewText_buf;
    const auto options_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_TextChangeOptions options_buf = {};
    options_buf.tag = options_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((options_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        options_buf.value = TextChangeOptions_serializer::read(thisDeserializer);
    }
    Opt_TextChangeOptions options = options_buf;
    _call(_resourceId, value, previewText, options);
}
void deserializeAndCallSyncEditableTextOnChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_String value, const Opt_PreviewText previewText, const Opt_TextChangeOptions options)>(thisDeserializer.readPointer());
    Ark_String value = static_cast<Ark_String>(thisDeserializer.readString());
    const auto previewText_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_PreviewText previewText_buf = {};
    previewText_buf.tag = previewText_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((previewText_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        previewText_buf.value = PreviewText_serializer::read(thisDeserializer);
    }
    Opt_PreviewText previewText = previewText_buf;
    const auto options_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_TextChangeOptions options_buf = {};
    options_buf.tag = options_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((options_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        options_buf.value = TextChangeOptions_serializer::read(thisDeserializer);
    }
    Opt_TextChangeOptions options = options_buf;
    _callSync(vmContext, _resourceId, value, previewText, options);
}
void deserializeAndCallErrorCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_BusinessError error)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_BusinessError error = BusinessError_serializer::read(thisDeserializer);
    _call(_resourceId, error);
}
void deserializeAndCallSyncErrorCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_BusinessError error)>(thisDeserializer.readPointer());
    Ark_BusinessError error = BusinessError_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, error);
}
void deserializeAndCallGaugeModifierBuilder(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Ark_GaugeConfiguration config, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_GaugeConfiguration config = GaugeConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Pointer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Pointer_Void))))};
    _call(_resourceId, parentNode, config, _continuation);
}
void deserializeAndCallSyncGaugeModifierBuilder(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Ark_GaugeConfiguration config, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointer());
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_GaugeConfiguration config = GaugeConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Pointer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Pointer_Void))))};
    _callSync(vmContext, _resourceId, parentNode, config, _continuation);
}
void deserializeAndCallGestureRecognizerJudgeBeginCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_BaseGestureEvent event, const Ark_GestureRecognizer current, const Array_GestureRecognizer recognizers, const Callback_GestureJudgeResult_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_BaseGestureEvent event = static_cast<Ark_BaseGestureEvent>(BaseGestureEvent_serializer::read(thisDeserializer));
    Ark_GestureRecognizer current = static_cast<Ark_GestureRecognizer>(GestureRecognizer_serializer::read(thisDeserializer));
    const Ark_Int32 recognizers_buf_length = thisDeserializer.readInt32();
    Array_GestureRecognizer recognizers_buf = {};
    thisDeserializer.resizeArray<std::decay<decltype(recognizers_buf)>::type,
        std::decay<decltype(*recognizers_buf.array)>::type>(&recognizers_buf, recognizers_buf_length);
    for (int recognizers_buf_i = 0; recognizers_buf_i < recognizers_buf_length; recognizers_buf_i++) {
        recognizers_buf.array[recognizers_buf_i] = static_cast<Ark_GestureRecognizer>(GestureRecognizer_serializer::read(thisDeserializer));
    }
    Array_GestureRecognizer recognizers = recognizers_buf;
    Callback_GestureJudgeResult_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_GestureJudgeResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_GestureJudgeResult_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_GestureJudgeResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_GestureJudgeResult_Void))))};
    _call(_resourceId, event, current, recognizers, _continuation);
}
void deserializeAndCallSyncGestureRecognizerJudgeBeginCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_BaseGestureEvent event, const Ark_GestureRecognizer current, const Array_GestureRecognizer recognizers, const Callback_GestureJudgeResult_Void continuation)>(thisDeserializer.readPointer());
    Ark_BaseGestureEvent event = static_cast<Ark_BaseGestureEvent>(BaseGestureEvent_serializer::read(thisDeserializer));
    Ark_GestureRecognizer current = static_cast<Ark_GestureRecognizer>(GestureRecognizer_serializer::read(thisDeserializer));
    const Ark_Int32 recognizers_buf_length = thisDeserializer.readInt32();
    Array_GestureRecognizer recognizers_buf = {};
    thisDeserializer.resizeArray<std::decay<decltype(recognizers_buf)>::type,
        std::decay<decltype(*recognizers_buf.array)>::type>(&recognizers_buf, recognizers_buf_length);
    for (int recognizers_buf_i = 0; recognizers_buf_i < recognizers_buf_length; recognizers_buf_i++) {
        recognizers_buf.array[recognizers_buf_i] = static_cast<Ark_GestureRecognizer>(GestureRecognizer_serializer::read(thisDeserializer));
    }
    Array_GestureRecognizer recognizers = recognizers_buf;
    Callback_GestureJudgeResult_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_GestureJudgeResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_GestureJudgeResult_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_GestureJudgeResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_GestureJudgeResult_Void))))};
    _callSync(vmContext, _resourceId, event, current, recognizers, _continuation);
}
void deserializeAndCallGetItemMainSizeByIndex(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number index, const Callback_Number_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Callback_Number_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Number_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Number_Void))))};
    _call(_resourceId, index, _continuation);
}
void deserializeAndCallSyncGetItemMainSizeByIndex(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number index, const Callback_Number_Void continuation)>(thisDeserializer.readPointer());
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Callback_Number_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Number_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Number_Void))))};
    _callSync(vmContext, _resourceId, index, _continuation);
}
void deserializeAndCallHoverCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean isHover, const Ark_HoverEvent event)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Boolean isHover = thisDeserializer.readBoolean();
    Ark_HoverEvent event = static_cast<Ark_HoverEvent>(HoverEvent_serializer::read(thisDeserializer));
    _call(_resourceId, isHover, event);
}
void deserializeAndCallSyncHoverCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isHover, const Ark_HoverEvent event)>(thisDeserializer.readPointer());
    Ark_Boolean isHover = thisDeserializer.readBoolean();
    Ark_HoverEvent event = static_cast<Ark_HoverEvent>(HoverEvent_serializer::read(thisDeserializer));
    _callSync(vmContext, _resourceId, isHover, event);
}
void deserializeAndCallImageCompleteCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_ImageLoadResult result)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_ImageLoadResult result = ImageLoadResult_serializer::read(thisDeserializer);
    _call(_resourceId, result);
}
void deserializeAndCallSyncImageCompleteCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_ImageLoadResult result)>(thisDeserializer.readPointer());
    Ark_ImageLoadResult result = ImageLoadResult_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, result);
}
void deserializeAndCallImageErrorCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_ImageError error)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_ImageError error = ImageError_serializer::read(thisDeserializer);
    _call(_resourceId, error);
}
void deserializeAndCallSyncImageErrorCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_ImageError error)>(thisDeserializer.readPointer());
    Ark_ImageError error = ImageError_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, error);
}
void deserializeAndCallImageOnCompleteCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_ImageCompleteEvent loadEvent)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    const auto loadEvent_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_ImageCompleteEvent loadEvent_buf = {};
    loadEvent_buf.tag = loadEvent_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((loadEvent_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        loadEvent_buf.value = ImageCompleteEvent_serializer::read(thisDeserializer);
    }
    Opt_ImageCompleteEvent loadEvent = loadEvent_buf;
    _call(_resourceId, loadEvent);
}
void deserializeAndCallSyncImageOnCompleteCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_ImageCompleteEvent loadEvent)>(thisDeserializer.readPointer());
    const auto loadEvent_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_ImageCompleteEvent loadEvent_buf = {};
    loadEvent_buf.tag = loadEvent_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((loadEvent_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        loadEvent_buf.value = ImageCompleteEvent_serializer::read(thisDeserializer);
    }
    Opt_ImageCompleteEvent loadEvent = loadEvent_buf;
    _callSync(vmContext, _resourceId, loadEvent);
}
void deserializeAndCallInterceptionModeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_NavigationMode mode)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_NavigationMode mode = static_cast<Ark_NavigationMode>(thisDeserializer.readInt32());
    _call(_resourceId, mode);
}
void deserializeAndCallSyncInterceptionModeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_NavigationMode mode)>(thisDeserializer.readPointer());
    Ark_NavigationMode mode = static_cast<Ark_NavigationMode>(thisDeserializer.readInt32());
    _callSync(vmContext, _resourceId, mode);
}
void deserializeAndCallInterceptionShowCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Union_NavDestinationContext_NavBar from, const Ark_Union_NavDestinationContext_NavBar to, Ark_NavigationOperation operation, const Ark_Boolean isAnimated)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    const Ark_Int8 from_buf_selector = thisDeserializer.readInt8();
    Ark_Union_NavDestinationContext_NavBar from_buf = {};
    from_buf.selector = from_buf_selector;
    if (from_buf_selector == 0) {
        from_buf.selector = 0;
        from_buf.value0 = static_cast<Ark_NavDestinationContext>(NavDestinationContext_serializer::read(thisDeserializer));
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
        to_buf.value0 = static_cast<Ark_NavDestinationContext>(NavDestinationContext_serializer::read(thisDeserializer));
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
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Union_NavDestinationContext_NavBar from, const Ark_Union_NavDestinationContext_NavBar to, Ark_NavigationOperation operation, const Ark_Boolean isAnimated)>(thisDeserializer.readPointer());
    const Ark_Int8 from_buf_selector = thisDeserializer.readInt8();
    Ark_Union_NavDestinationContext_NavBar from_buf = {};
    from_buf.selector = from_buf_selector;
    if (from_buf_selector == 0) {
        from_buf.selector = 0;
        from_buf.value0 = static_cast<Ark_NavDestinationContext>(NavDestinationContext_serializer::read(thisDeserializer));
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
        to_buf.value0 = static_cast<Ark_NavDestinationContext>(NavDestinationContext_serializer::read(thisDeserializer));
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
void deserializeAndCallLoadingProgressModifierBuilder(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Ark_LoadingProgressConfiguration config, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_LoadingProgressConfiguration config = LoadingProgressConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Pointer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Pointer_Void))))};
    _call(_resourceId, parentNode, config, _continuation);
}
void deserializeAndCallSyncLoadingProgressModifierBuilder(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Ark_LoadingProgressConfiguration config, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointer());
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_LoadingProgressConfiguration config = LoadingProgressConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Pointer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Pointer_Void))))};
    _callSync(vmContext, _resourceId, parentNode, config, _continuation);
}
void deserializeAndCallMenuCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number start, const Ark_Number end)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number start = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number end = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _call(_resourceId, start, end);
}
void deserializeAndCallSyncMenuCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number start, const Ark_Number end)>(thisDeserializer.readPointer());
    Ark_Number start = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number end = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _callSync(vmContext, _resourceId, start, end);
}
void deserializeAndCallMenuItemModifierBuilder(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Ark_MenuItemConfiguration config, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_MenuItemConfiguration config = MenuItemConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Pointer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Pointer_Void))))};
    _call(_resourceId, parentNode, config, _continuation);
}
void deserializeAndCallSyncMenuItemModifierBuilder(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Ark_MenuItemConfiguration config, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointer());
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_MenuItemConfiguration config = MenuItemConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Pointer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Pointer_Void))))};
    _callSync(vmContext, _resourceId, parentNode, config, _continuation);
}
void deserializeAndCallMenuOnAppearCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number start, const Ark_Number end)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number start = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number end = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _call(_resourceId, start, end);
}
void deserializeAndCallSyncMenuOnAppearCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number start, const Ark_Number end)>(thisDeserializer.readPointer());
    Ark_Number start = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number end = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _callSync(vmContext, _resourceId, start, end);
}
void deserializeAndCallModifierKeyStateGetter(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Array_String keys, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    const Ark_Int32 keys_buf_length = thisDeserializer.readInt32();
    Array_String keys_buf = {};
    thisDeserializer.resizeArray<std::decay<decltype(keys_buf)>::type,
        std::decay<decltype(*keys_buf.array)>::type>(&keys_buf, keys_buf_length);
    for (int keys_buf_i = 0; keys_buf_i < keys_buf_length; keys_buf_i++) {
        keys_buf.array[keys_buf_i] = static_cast<Ark_String>(thisDeserializer.readString());
    }
    Array_String keys = keys_buf;
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, keys, _continuation);
}
void deserializeAndCallSyncModifierKeyStateGetter(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Array_String keys, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    const Ark_Int32 keys_buf_length = thisDeserializer.readInt32();
    Array_String keys_buf = {};
    thisDeserializer.resizeArray<std::decay<decltype(keys_buf)>::type,
        std::decay<decltype(*keys_buf.array)>::type>(&keys_buf, keys_buf_length);
    for (int keys_buf_i = 0; keys_buf_i < keys_buf_length; keys_buf_i++) {
        keys_buf.array[keys_buf_i] = static_cast<Ark_String>(thisDeserializer.readString());
    }
    Array_String keys = keys_buf;
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _callSync(vmContext, _resourceId, keys, _continuation);
}
void deserializeAndCallNavDestinationTransitionDelegate(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_NavigationOperation operation, const Ark_Boolean isEnter, const Callback_Opt_Array_NavDestinationTransition_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_NavigationOperation operation = static_cast<Ark_NavigationOperation>(thisDeserializer.readInt32());
    Ark_Boolean isEnter = thisDeserializer.readBoolean();
    Callback_Opt_Array_NavDestinationTransition_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_Array_NavDestinationTransition value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Opt_Array_NavDestinationTransition_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_Array_NavDestinationTransition value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Opt_Array_NavDestinationTransition_Void))))};
    _call(_resourceId, operation, isEnter, _continuation);
}
void deserializeAndCallSyncNavDestinationTransitionDelegate(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_NavigationOperation operation, const Ark_Boolean isEnter, const Callback_Opt_Array_NavDestinationTransition_Void continuation)>(thisDeserializer.readPointer());
    Ark_NavigationOperation operation = static_cast<Ark_NavigationOperation>(thisDeserializer.readInt32());
    Ark_Boolean isEnter = thisDeserializer.readBoolean();
    Callback_Opt_Array_NavDestinationTransition_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_Array_NavDestinationTransition value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Opt_Array_NavDestinationTransition_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_Array_NavDestinationTransition value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Opt_Array_NavDestinationTransition_Void))))};
    _callSync(vmContext, _resourceId, operation, isEnter, _continuation);
}
void deserializeAndCallNavExtender_OnUpdateStack(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    _call(_resourceId);
}
void deserializeAndCallSyncNavExtender_OnUpdateStack(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId)>(thisDeserializer.readPointer());
    _callSync(vmContext, _resourceId);
}
void deserializeAndCallOnAdsBlockedCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_AdsBlockedDetails details)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_AdsBlockedDetails details = AdsBlockedDetails_serializer::read(thisDeserializer);
    _call(_resourceId, details);
}
void deserializeAndCallSyncOnAdsBlockedCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_AdsBlockedDetails details)>(thisDeserializer.readPointer());
    Ark_AdsBlockedDetails details = AdsBlockedDetails_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, details);
}
void deserializeAndCallOnAlphabetIndexerPopupSelectCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number index)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _call(_resourceId, index);
}
void deserializeAndCallSyncOnAlphabetIndexerPopupSelectCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number index)>(thisDeserializer.readPointer());
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _callSync(vmContext, _resourceId, index);
}
void deserializeAndCallOnAlphabetIndexerRequestPopupDataCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number index, const Callback_Array_String_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Callback_Array_String_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Array_String value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Array_String_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Array_String value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Array_String_Void))))};
    _call(_resourceId, index, _continuation);
}
void deserializeAndCallSyncOnAlphabetIndexerRequestPopupDataCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number index, const Callback_Array_String_Void continuation)>(thisDeserializer.readPointer());
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Callback_Array_String_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Array_String value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Array_String_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Array_String value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Array_String_Void))))};
    _callSync(vmContext, _resourceId, index, _continuation);
}
void deserializeAndCallOnAlphabetIndexerSelectCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number index)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _call(_resourceId, index);
}
void deserializeAndCallSyncOnAlphabetIndexerSelectCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number index)>(thisDeserializer.readPointer());
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _callSync(vmContext, _resourceId, index);
}
void deserializeAndCallOnCheckboxChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Boolean value = thisDeserializer.readBoolean();
    _call(_resourceId, value);
}
void deserializeAndCallSyncOnCheckboxChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value)>(thisDeserializer.readPointer());
    Ark_Boolean value = thisDeserializer.readBoolean();
    _callSync(vmContext, _resourceId, value);
}
void deserializeAndCallOnCheckboxGroupChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_CheckboxGroupResult value)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_CheckboxGroupResult value = CheckboxGroupResult_serializer::read(thisDeserializer);
    _call(_resourceId, value);
}
void deserializeAndCallSyncOnCheckboxGroupChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_CheckboxGroupResult value)>(thisDeserializer.readPointer());
    Ark_CheckboxGroupResult value = CheckboxGroupResult_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, value);
}
void deserializeAndCallOnContentScrollCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number totalOffsetX, const Ark_Number totalOffsetY)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number totalOffsetX = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number totalOffsetY = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _call(_resourceId, totalOffsetX, totalOffsetY);
}
void deserializeAndCallSyncOnContentScrollCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number totalOffsetX, const Ark_Number totalOffsetY)>(thisDeserializer.readPointer());
    Ark_Number totalOffsetX = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number totalOffsetY = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _callSync(vmContext, _resourceId, totalOffsetX, totalOffsetY);
}
void deserializeAndCallOnContextMenuHideCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    _call(_resourceId);
}
void deserializeAndCallSyncOnContextMenuHideCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId)>(thisDeserializer.readPointer());
    _callSync(vmContext, _resourceId);
}
void deserializeAndCallOnCreateMenuCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Array_TextMenuItem menuItems, const Callback_Array_TextMenuItem_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    const Ark_Int32 menuItems_buf_length = thisDeserializer.readInt32();
    Array_TextMenuItem menuItems_buf = {};
    thisDeserializer.resizeArray<std::decay<decltype(menuItems_buf)>::type,
        std::decay<decltype(*menuItems_buf.array)>::type>(&menuItems_buf, menuItems_buf_length);
    for (int menuItems_buf_i = 0; menuItems_buf_i < menuItems_buf_length; menuItems_buf_i++) {
        menuItems_buf.array[menuItems_buf_i] = TextMenuItem_serializer::read(thisDeserializer);
    }
    Array_TextMenuItem menuItems = menuItems_buf;
    Callback_Array_TextMenuItem_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Array_TextMenuItem value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Array_TextMenuItem_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Array_TextMenuItem value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Array_TextMenuItem_Void))))};
    _call(_resourceId, menuItems, _continuation);
}
void deserializeAndCallSyncOnCreateMenuCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Array_TextMenuItem menuItems, const Callback_Array_TextMenuItem_Void continuation)>(thisDeserializer.readPointer());
    const Ark_Int32 menuItems_buf_length = thisDeserializer.readInt32();
    Array_TextMenuItem menuItems_buf = {};
    thisDeserializer.resizeArray<std::decay<decltype(menuItems_buf)>::type,
        std::decay<decltype(*menuItems_buf.array)>::type>(&menuItems_buf, menuItems_buf_length);
    for (int menuItems_buf_i = 0; menuItems_buf_i < menuItems_buf_length; menuItems_buf_i++) {
        menuItems_buf.array[menuItems_buf_i] = TextMenuItem_serializer::read(thisDeserializer);
    }
    Array_TextMenuItem menuItems = menuItems_buf;
    Callback_Array_TextMenuItem_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Array_TextMenuItem value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Array_TextMenuItem_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Array_TextMenuItem value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Array_TextMenuItem_Void))))};
    _callSync(vmContext, _resourceId, menuItems, _continuation);
}
void deserializeAndCallOnDidChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_TextRange rangeBefore, const Ark_TextRange rangeAfter)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_TextRange rangeBefore = TextRange_serializer::read(thisDeserializer);
    Ark_TextRange rangeAfter = TextRange_serializer::read(thisDeserializer);
    _call(_resourceId, rangeBefore, rangeAfter);
}
void deserializeAndCallSyncOnDidChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_TextRange rangeBefore, const Ark_TextRange rangeAfter)>(thisDeserializer.readPointer());
    Ark_TextRange rangeBefore = TextRange_serializer::read(thisDeserializer);
    Ark_TextRange rangeAfter = TextRange_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, rangeBefore, rangeAfter);
}
void deserializeAndCallOnDragEventCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_DragEvent event, const Opt_String extraParams)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_DragEvent event = static_cast<Ark_DragEvent>(DragEvent_serializer::read(thisDeserializer));
    const auto extraParams_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_String extraParams_buf = {};
    extraParams_buf.tag = extraParams_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((extraParams_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        extraParams_buf.value = static_cast<Ark_String>(thisDeserializer.readString());
    }
    Opt_String extraParams = extraParams_buf;
    _call(_resourceId, event, extraParams);
}
void deserializeAndCallSyncOnDragEventCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_DragEvent event, const Opt_String extraParams)>(thisDeserializer.readPointer());
    Ark_DragEvent event = static_cast<Ark_DragEvent>(DragEvent_serializer::read(thisDeserializer));
    const auto extraParams_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_String extraParams_buf = {};
    extraParams_buf.tag = extraParams_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((extraParams_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        extraParams_buf.value = static_cast<Ark_String>(thisDeserializer.readString());
    }
    Opt_String extraParams = extraParams_buf;
    _callSync(vmContext, _resourceId, event, extraParams);
}
void deserializeAndCallOnFirstMeaningfulPaintCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_FirstMeaningfulPaint firstMeaningfulPaint)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_FirstMeaningfulPaint firstMeaningfulPaint = FirstMeaningfulPaint_serializer::read(thisDeserializer);
    _call(_resourceId, firstMeaningfulPaint);
}
void deserializeAndCallSyncOnFirstMeaningfulPaintCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_FirstMeaningfulPaint firstMeaningfulPaint)>(thisDeserializer.readPointer());
    Ark_FirstMeaningfulPaint firstMeaningfulPaint = FirstMeaningfulPaint_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, firstMeaningfulPaint);
}
void deserializeAndCallOnFoldStatusChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnFoldStatusChangeInfo event)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_OnFoldStatusChangeInfo event = OnFoldStatusChangeInfo_serializer::read(thisDeserializer);
    _call(_resourceId, event);
}
void deserializeAndCallSyncOnFoldStatusChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnFoldStatusChangeInfo event)>(thisDeserializer.readPointer());
    Ark_OnFoldStatusChangeInfo event = OnFoldStatusChangeInfo_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, event);
}
void deserializeAndCallOnFullScreenEnterCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_FullScreenEnterEvent event)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_FullScreenEnterEvent event = FullScreenEnterEvent_serializer::read(thisDeserializer);
    _call(_resourceId, event);
}
void deserializeAndCallSyncOnFullScreenEnterCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_FullScreenEnterEvent event)>(thisDeserializer.readPointer());
    Ark_FullScreenEnterEvent event = FullScreenEnterEvent_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, event);
}
void deserializeAndCallOnHoverCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean status, const Ark_HoverEvent event)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Boolean status = thisDeserializer.readBoolean();
    Ark_HoverEvent event = static_cast<Ark_HoverEvent>(HoverEvent_serializer::read(thisDeserializer));
    _call(_resourceId, status, event);
}
void deserializeAndCallSyncOnHoverCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean status, const Ark_HoverEvent event)>(thisDeserializer.readPointer());
    Ark_Boolean status = thisDeserializer.readBoolean();
    Ark_HoverEvent event = static_cast<Ark_HoverEvent>(HoverEvent_serializer::read(thisDeserializer));
    _callSync(vmContext, _resourceId, status, event);
}
void deserializeAndCallOnHoverStatusChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_HoverEventParam param)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_HoverEventParam param = HoverEventParam_serializer::read(thisDeserializer);
    _call(_resourceId, param);
}
void deserializeAndCallSyncOnHoverStatusChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_HoverEventParam param)>(thisDeserializer.readPointer());
    Ark_HoverEventParam param = HoverEventParam_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, param);
}
void deserializeAndCallOnIntelligentTrackingPreventionCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_IntelligentTrackingPreventionDetails details)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_IntelligentTrackingPreventionDetails details = IntelligentTrackingPreventionDetails_serializer::read(thisDeserializer);
    _call(_resourceId, details);
}
void deserializeAndCallSyncOnIntelligentTrackingPreventionCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_IntelligentTrackingPreventionDetails details)>(thisDeserializer.readPointer());
    Ark_IntelligentTrackingPreventionDetails details = IntelligentTrackingPreventionDetails_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, details);
}
void deserializeAndCallOnItemDragStartCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_ItemDragInfo event, const Ark_Number itemIndex, const Callback_Opt_CustomBuilder_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_ItemDragInfo event = ItemDragInfo_serializer::read(thisDeserializer);
    Ark_Number itemIndex = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Callback_Opt_CustomBuilder_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_CustomNodeBuilder value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Opt_CustomBuilder_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_CustomNodeBuilder value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Opt_CustomBuilder_Void))))};
    _call(_resourceId, event, itemIndex, _continuation);
}
void deserializeAndCallSyncOnItemDragStartCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_ItemDragInfo event, const Ark_Number itemIndex, const Callback_Opt_CustomBuilder_Void continuation)>(thisDeserializer.readPointer());
    Ark_ItemDragInfo event = ItemDragInfo_serializer::read(thisDeserializer);
    Ark_Number itemIndex = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Callback_Opt_CustomBuilder_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_CustomNodeBuilder value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Opt_CustomBuilder_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_CustomNodeBuilder value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Opt_CustomBuilder_Void))))};
    _callSync(vmContext, _resourceId, event, itemIndex, _continuation);
}
void deserializeAndCallOnLargestContentfulPaintCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_LargestContentfulPaint largestContentfulPaint)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_LargestContentfulPaint largestContentfulPaint = LargestContentfulPaint_serializer::read(thisDeserializer);
    _call(_resourceId, largestContentfulPaint);
}
void deserializeAndCallSyncOnLargestContentfulPaintCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_LargestContentfulPaint largestContentfulPaint)>(thisDeserializer.readPointer());
    Ark_LargestContentfulPaint largestContentfulPaint = LargestContentfulPaint_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, largestContentfulPaint);
}
void deserializeAndCallOnLinearIndicatorChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number index, const Ark_Number progress)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number progress = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _call(_resourceId, index, progress);
}
void deserializeAndCallSyncOnLinearIndicatorChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number index, const Ark_Number progress)>(thisDeserializer.readPointer());
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number progress = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _callSync(vmContext, _resourceId, index, progress);
}
void deserializeAndCallOnMenuItemClickCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_TextMenuItem menuItem, const Ark_TextRange range, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_TextMenuItem menuItem = TextMenuItem_serializer::read(thisDeserializer);
    Ark_TextRange range = TextRange_serializer::read(thisDeserializer);
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, menuItem, range, _continuation);
}
void deserializeAndCallSyncOnMenuItemClickCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_TextMenuItem menuItem, const Ark_TextRange range, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    Ark_TextMenuItem menuItem = TextMenuItem_serializer::read(thisDeserializer);
    Ark_TextRange range = TextRange_serializer::read(thisDeserializer);
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _callSync(vmContext, _resourceId, menuItem, range, _continuation);
}
void deserializeAndCallOnMoveHandler(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number from, const Ark_Number to)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number from = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number to = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _call(_resourceId, from, to);
}
void deserializeAndCallSyncOnMoveHandler(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number from, const Ark_Number to)>(thisDeserializer.readPointer());
    Ark_Number from = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number to = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _callSync(vmContext, _resourceId, from, to);
}
void deserializeAndCallOnNativeEmbedVisibilityChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativeEmbedVisibilityInfo nativeEmbedVisibilityInfo)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_NativeEmbedVisibilityInfo nativeEmbedVisibilityInfo = NativeEmbedVisibilityInfo_serializer::read(thisDeserializer);
    _call(_resourceId, nativeEmbedVisibilityInfo);
}
void deserializeAndCallSyncOnNativeEmbedVisibilityChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativeEmbedVisibilityInfo nativeEmbedVisibilityInfo)>(thisDeserializer.readPointer());
    Ark_NativeEmbedVisibilityInfo nativeEmbedVisibilityInfo = NativeEmbedVisibilityInfo_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, nativeEmbedVisibilityInfo);
}
void deserializeAndCallOnNativeLoadCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_Object event)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    const auto event_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Object event_buf = {};
    event_buf.tag = event_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((event_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        event_buf.value = static_cast<Ark_Object>(thisDeserializer.readObject());
    }
    Opt_Object event = event_buf;
    _call(_resourceId, event);
}
void deserializeAndCallSyncOnNativeLoadCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_Object event)>(thisDeserializer.readPointer());
    const auto event_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Object event_buf = {};
    event_buf.tag = event_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((event_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        event_buf.value = static_cast<Ark_Object>(thisDeserializer.readObject());
    }
    Opt_Object event = event_buf;
    _callSync(vmContext, _resourceId, event);
}
void deserializeAndCallOnNavigationEntryCommittedCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_LoadCommittedDetails loadCommittedDetails)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_LoadCommittedDetails loadCommittedDetails = LoadCommittedDetails_serializer::read(thisDeserializer);
    _call(_resourceId, loadCommittedDetails);
}
void deserializeAndCallSyncOnNavigationEntryCommittedCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_LoadCommittedDetails loadCommittedDetails)>(thisDeserializer.readPointer());
    Ark_LoadCommittedDetails loadCommittedDetails = LoadCommittedDetails_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, loadCommittedDetails);
}
void deserializeAndCallOnOverrideUrlLoadingCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_WebResourceRequest webResourceRequest, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_WebResourceRequest webResourceRequest = static_cast<Ark_WebResourceRequest>(WebResourceRequest_serializer::read(thisDeserializer));
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, webResourceRequest, _continuation);
}
void deserializeAndCallSyncOnOverrideUrlLoadingCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_WebResourceRequest webResourceRequest, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    Ark_WebResourceRequest webResourceRequest = static_cast<Ark_WebResourceRequest>(WebResourceRequest_serializer::read(thisDeserializer));
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _callSync(vmContext, _resourceId, webResourceRequest, _continuation);
}
void deserializeAndCallOnPasteCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_String content, const Ark_PasteEvent event)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_String content = static_cast<Ark_String>(thisDeserializer.readString());
    Ark_PasteEvent event = PasteEvent_serializer::read(thisDeserializer);
    _call(_resourceId, content, event);
}
void deserializeAndCallSyncOnPasteCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_String content, const Ark_PasteEvent event)>(thisDeserializer.readPointer());
    Ark_String content = static_cast<Ark_String>(thisDeserializer.readString());
    Ark_PasteEvent event = PasteEvent_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, content, event);
}
void deserializeAndCallOnRadioChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean isChecked)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Boolean isChecked = thisDeserializer.readBoolean();
    _call(_resourceId, isChecked);
}
void deserializeAndCallSyncOnRadioChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isChecked)>(thisDeserializer.readPointer());
    Ark_Boolean isChecked = thisDeserializer.readBoolean();
    _callSync(vmContext, _resourceId, isChecked);
}
void deserializeAndCallOnRatingChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number rating)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number rating = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _call(_resourceId, rating);
}
void deserializeAndCallSyncOnRatingChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number rating)>(thisDeserializer.readPointer());
    Ark_Number rating = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _callSync(vmContext, _resourceId, rating);
}
void deserializeAndCallOnRenderProcessNotRespondingCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_RenderProcessNotRespondingData data)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_RenderProcessNotRespondingData data = RenderProcessNotRespondingData_serializer::read(thisDeserializer);
    _call(_resourceId, data);
}
void deserializeAndCallSyncOnRenderProcessNotRespondingCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_RenderProcessNotRespondingData data)>(thisDeserializer.readPointer());
    Ark_RenderProcessNotRespondingData data = RenderProcessNotRespondingData_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, data);
}
void deserializeAndCallOnRenderProcessRespondingCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    _call(_resourceId);
}
void deserializeAndCallSyncOnRenderProcessRespondingCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId)>(thisDeserializer.readPointer());
    _callSync(vmContext, _resourceId);
}
void deserializeAndCallOnSafeBrowsingCheckResultCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_ThreatType threatType)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_ThreatType threatType = static_cast<Ark_ThreatType>(thisDeserializer.readInt32());
    _call(_resourceId, threatType);
}
void deserializeAndCallSyncOnSafeBrowsingCheckResultCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_ThreatType threatType)>(thisDeserializer.readPointer());
    Ark_ThreatType threatType = static_cast<Ark_ThreatType>(thisDeserializer.readInt32());
    _callSync(vmContext, _resourceId, threatType);
}
void deserializeAndCallOnScrollCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number scrollOffset, Ark_ScrollState scrollState)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number scrollOffset = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_ScrollState scrollState = static_cast<Ark_ScrollState>(thisDeserializer.readInt32());
    _call(_resourceId, scrollOffset, scrollState);
}
void deserializeAndCallSyncOnScrollCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number scrollOffset, Ark_ScrollState scrollState)>(thisDeserializer.readPointer());
    Ark_Number scrollOffset = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_ScrollState scrollState = static_cast<Ark_ScrollState>(thisDeserializer.readInt32());
    _callSync(vmContext, _resourceId, scrollOffset, scrollState);
}
void deserializeAndCallOnScrollEdgeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_Edge side)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Edge side = static_cast<Ark_Edge>(thisDeserializer.readInt32());
    _call(_resourceId, side);
}
void deserializeAndCallSyncOnScrollEdgeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_Edge side)>(thisDeserializer.readPointer());
    Ark_Edge side = static_cast<Ark_Edge>(thisDeserializer.readInt32());
    _callSync(vmContext, _resourceId, side);
}
void deserializeAndCallOnScrollFrameBeginCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
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
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
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
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_VisibleListContentInfo start, const Ark_VisibleListContentInfo end)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_VisibleListContentInfo start = VisibleListContentInfo_serializer::read(thisDeserializer);
    Ark_VisibleListContentInfo end = VisibleListContentInfo_serializer::read(thisDeserializer);
    _call(_resourceId, start, end);
}
void deserializeAndCallSyncOnScrollVisibleContentChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_VisibleListContentInfo start, const Ark_VisibleListContentInfo end)>(thisDeserializer.readPointer());
    Ark_VisibleListContentInfo start = VisibleListContentInfo_serializer::read(thisDeserializer);
    Ark_VisibleListContentInfo end = VisibleListContentInfo_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, start, end);
}
void deserializeAndCallOnSelectCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number index, const Ark_String selectStr)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_String selectStr = static_cast<Ark_String>(thisDeserializer.readString());
    _call(_resourceId, index, selectStr);
}
void deserializeAndCallSyncOnSelectCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number index, const Ark_String selectStr)>(thisDeserializer.readPointer());
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_String selectStr = static_cast<Ark_String>(thisDeserializer.readString());
    _callSync(vmContext, _resourceId, index, selectStr);
}
void deserializeAndCallOnSslErrorEventCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_SslErrorEvent sslErrorEvent)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_SslErrorEvent sslErrorEvent = SslErrorEvent_serializer::read(thisDeserializer);
    _call(_resourceId, sslErrorEvent);
}
void deserializeAndCallSyncOnSslErrorEventCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_SslErrorEvent sslErrorEvent)>(thisDeserializer.readPointer());
    Ark_SslErrorEvent sslErrorEvent = SslErrorEvent_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, sslErrorEvent);
}
void deserializeAndCallOnSubmitCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_EnterKeyType enterKey, const Ark_SubmitEvent event)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_EnterKeyType enterKey = static_cast<Ark_EnterKeyType>(thisDeserializer.readInt32());
    Ark_SubmitEvent event = static_cast<Ark_SubmitEvent>(SubmitEvent_serializer::read(thisDeserializer));
    _call(_resourceId, enterKey, event);
}
void deserializeAndCallSyncOnSubmitCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_EnterKeyType enterKey, const Ark_SubmitEvent event)>(thisDeserializer.readPointer());
    Ark_EnterKeyType enterKey = static_cast<Ark_EnterKeyType>(thisDeserializer.readInt32());
    Ark_SubmitEvent event = static_cast<Ark_SubmitEvent>(SubmitEvent_serializer::read(thisDeserializer));
    _callSync(vmContext, _resourceId, enterKey, event);
}
void deserializeAndCallOnSwiperAnimationEndCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number index, const Ark_SwiperAnimationEvent extraInfo)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_SwiperAnimationEvent extraInfo = SwiperAnimationEvent_serializer::read(thisDeserializer);
    _call(_resourceId, index, extraInfo);
}
void deserializeAndCallSyncOnSwiperAnimationEndCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number index, const Ark_SwiperAnimationEvent extraInfo)>(thisDeserializer.readPointer());
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_SwiperAnimationEvent extraInfo = SwiperAnimationEvent_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, index, extraInfo);
}
void deserializeAndCallOnSwiperAnimationStartCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number index, const Ark_Number targetIndex, const Ark_SwiperAnimationEvent extraInfo)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number targetIndex = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_SwiperAnimationEvent extraInfo = SwiperAnimationEvent_serializer::read(thisDeserializer);
    _call(_resourceId, index, targetIndex, extraInfo);
}
void deserializeAndCallSyncOnSwiperAnimationStartCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number index, const Ark_Number targetIndex, const Ark_SwiperAnimationEvent extraInfo)>(thisDeserializer.readPointer());
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number targetIndex = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_SwiperAnimationEvent extraInfo = SwiperAnimationEvent_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, index, targetIndex, extraInfo);
}
void deserializeAndCallOnSwiperGestureSwipeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number index, const Ark_SwiperAnimationEvent extraInfo)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_SwiperAnimationEvent extraInfo = SwiperAnimationEvent_serializer::read(thisDeserializer);
    _call(_resourceId, index, extraInfo);
}
void deserializeAndCallSyncOnSwiperGestureSwipeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number index, const Ark_SwiperAnimationEvent extraInfo)>(thisDeserializer.readPointer());
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_SwiperAnimationEvent extraInfo = SwiperAnimationEvent_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, index, extraInfo);
}
void deserializeAndCallOnTabsAnimationEndCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number index, const Ark_TabsAnimationEvent extraInfo)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_TabsAnimationEvent extraInfo = TabsAnimationEvent_serializer::read(thisDeserializer);
    _call(_resourceId, index, extraInfo);
}
void deserializeAndCallSyncOnTabsAnimationEndCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number index, const Ark_TabsAnimationEvent extraInfo)>(thisDeserializer.readPointer());
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_TabsAnimationEvent extraInfo = TabsAnimationEvent_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, index, extraInfo);
}
void deserializeAndCallOnTabsAnimationStartCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number index, const Ark_Number targetIndex, const Ark_TabsAnimationEvent extraInfo)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number targetIndex = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_TabsAnimationEvent extraInfo = TabsAnimationEvent_serializer::read(thisDeserializer);
    _call(_resourceId, index, targetIndex, extraInfo);
}
void deserializeAndCallSyncOnTabsAnimationStartCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number index, const Ark_Number targetIndex, const Ark_TabsAnimationEvent extraInfo)>(thisDeserializer.readPointer());
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number targetIndex = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_TabsAnimationEvent extraInfo = TabsAnimationEvent_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, index, targetIndex, extraInfo);
}
void deserializeAndCallOnTabsContentWillChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number currentIndex, const Ark_Number comingIndex, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number currentIndex = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number comingIndex = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, currentIndex, comingIndex, _continuation);
}
void deserializeAndCallSyncOnTabsContentWillChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number currentIndex, const Ark_Number comingIndex, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointer());
    Ark_Number currentIndex = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number comingIndex = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Callback_Boolean_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _callSync(vmContext, _resourceId, currentIndex, comingIndex, _continuation);
}
void deserializeAndCallOnTabsGestureSwipeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number index, const Ark_TabsAnimationEvent extraInfo)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_TabsAnimationEvent extraInfo = TabsAnimationEvent_serializer::read(thisDeserializer);
    _call(_resourceId, index, extraInfo);
}
void deserializeAndCallSyncOnTabsGestureSwipeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number index, const Ark_TabsAnimationEvent extraInfo)>(thisDeserializer.readPointer());
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_TabsAnimationEvent extraInfo = TabsAnimationEvent_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, index, extraInfo);
}
void deserializeAndCallOnTextPickerChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Union_String_Array_String selectItem, const Ark_Union_Number_Array_Number index)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    const Ark_Int8 selectItem_buf_selector = thisDeserializer.readInt8();
    Ark_Union_String_Array_String selectItem_buf = {};
    selectItem_buf.selector = selectItem_buf_selector;
    if (selectItem_buf_selector == 0) {
        selectItem_buf.selector = 0;
        selectItem_buf.value0 = static_cast<Ark_String>(thisDeserializer.readString());
    }
    else if (selectItem_buf_selector == 1) {
        selectItem_buf.selector = 1;
        const Ark_Int32 selectItem_buf_u_length = thisDeserializer.readInt32();
        Array_String selectItem_buf_u = {};
        thisDeserializer.resizeArray<std::decay<decltype(selectItem_buf_u)>::type,
        std::decay<decltype(*selectItem_buf_u.array)>::type>(&selectItem_buf_u, selectItem_buf_u_length);
        for (int selectItem_buf_u_i = 0; selectItem_buf_u_i < selectItem_buf_u_length; selectItem_buf_u_i++) {
            selectItem_buf_u.array[selectItem_buf_u_i] = static_cast<Ark_String>(thisDeserializer.readString());
        }
        selectItem_buf.value1 = selectItem_buf_u;
    }
    else {
        INTEROP_FATAL("One of the branches for selectItem_buf has to be chosen through deserialisation.");
    }
    Ark_Union_String_Array_String selectItem = static_cast<Ark_Union_String_Array_String>(selectItem_buf);
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
    _call(_resourceId, selectItem, index);
}
void deserializeAndCallSyncOnTextPickerChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Union_String_Array_String selectItem, const Ark_Union_Number_Array_Number index)>(thisDeserializer.readPointer());
    const Ark_Int8 selectItem_buf_selector = thisDeserializer.readInt8();
    Ark_Union_String_Array_String selectItem_buf = {};
    selectItem_buf.selector = selectItem_buf_selector;
    if (selectItem_buf_selector == 0) {
        selectItem_buf.selector = 0;
        selectItem_buf.value0 = static_cast<Ark_String>(thisDeserializer.readString());
    }
    else if (selectItem_buf_selector == 1) {
        selectItem_buf.selector = 1;
        const Ark_Int32 selectItem_buf_u_length = thisDeserializer.readInt32();
        Array_String selectItem_buf_u = {};
        thisDeserializer.resizeArray<std::decay<decltype(selectItem_buf_u)>::type,
        std::decay<decltype(*selectItem_buf_u.array)>::type>(&selectItem_buf_u, selectItem_buf_u_length);
        for (int selectItem_buf_u_i = 0; selectItem_buf_u_i < selectItem_buf_u_length; selectItem_buf_u_i++) {
            selectItem_buf_u.array[selectItem_buf_u_i] = static_cast<Ark_String>(thisDeserializer.readString());
        }
        selectItem_buf.value1 = selectItem_buf_u;
    }
    else {
        INTEROP_FATAL("One of the branches for selectItem_buf has to be chosen through deserialisation.");
    }
    Ark_Union_String_Array_String selectItem = static_cast<Ark_Union_String_Array_String>(selectItem_buf);
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
    _callSync(vmContext, _resourceId, selectItem, index);
}
void deserializeAndCallOnTextSelectionChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number selectionStart, const Ark_Number selectionEnd)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number selectionStart = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number selectionEnd = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _call(_resourceId, selectionStart, selectionEnd);
}
void deserializeAndCallSyncOnTextSelectionChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number selectionStart, const Ark_Number selectionEnd)>(thisDeserializer.readPointer());
    Ark_Number selectionStart = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number selectionEnd = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _callSync(vmContext, _resourceId, selectionStart, selectionEnd);
}
void deserializeAndCallOnTimePickerChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_TimePickerResult result)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_TimePickerResult result = TimePickerResult_serializer::read(thisDeserializer);
    _call(_resourceId, result);
}
void deserializeAndCallSyncOnTimePickerChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_TimePickerResult result)>(thisDeserializer.readPointer());
    Ark_TimePickerResult result = TimePickerResult_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, result);
}
void deserializeAndCallOnViewportFitChangedCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_ViewportFit viewportFit)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_ViewportFit viewportFit = static_cast<Ark_ViewportFit>(thisDeserializer.readInt32());
    _call(_resourceId, viewportFit);
}
void deserializeAndCallSyncOnViewportFitChangedCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_ViewportFit viewportFit)>(thisDeserializer.readPointer());
    Ark_ViewportFit viewportFit = static_cast<Ark_ViewportFit>(thisDeserializer.readInt32());
    _callSync(vmContext, _resourceId, viewportFit);
}
void deserializeAndCallOnWillScrollCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number scrollOffset, Ark_ScrollState scrollState, Ark_ScrollSource scrollSource, const Callback_Opt_ScrollResult_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number scrollOffset = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_ScrollState scrollState = static_cast<Ark_ScrollState>(thisDeserializer.readInt32());
    Ark_ScrollSource scrollSource = static_cast<Ark_ScrollSource>(thisDeserializer.readInt32());
    Callback_Opt_ScrollResult_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_ScrollResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Opt_ScrollResult_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_ScrollResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Opt_ScrollResult_Void))))};
    _call(_resourceId, scrollOffset, scrollState, scrollSource, _continuation);
}
void deserializeAndCallSyncOnWillScrollCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number scrollOffset, Ark_ScrollState scrollState, Ark_ScrollSource scrollSource, const Callback_Opt_ScrollResult_Void continuation)>(thisDeserializer.readPointer());
    Ark_Number scrollOffset = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_ScrollState scrollState = static_cast<Ark_ScrollState>(thisDeserializer.readInt32());
    Ark_ScrollSource scrollSource = static_cast<Ark_ScrollSource>(thisDeserializer.readInt32());
    Callback_Opt_ScrollResult_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_ScrollResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Opt_ScrollResult_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_ScrollResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Opt_ScrollResult_Void))))};
    _callSync(vmContext, _resourceId, scrollOffset, scrollState, scrollSource, _continuation);
}
void deserializeAndCallPageMapBuilder(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_String name, const Opt_Object param)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_String name = static_cast<Ark_String>(thisDeserializer.readString());
    const auto param_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Object param_buf = {};
    param_buf.tag = param_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((param_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        param_buf.value = static_cast<Ark_Object>(thisDeserializer.readObject());
    }
    Opt_Object param = param_buf;
    _call(_resourceId, name, param);
}
void deserializeAndCallSyncPageMapBuilder(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_String name, const Opt_Object param)>(thisDeserializer.readPointer());
    Ark_String name = static_cast<Ark_String>(thisDeserializer.readString());
    const auto param_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Object param_buf = {};
    param_buf.tag = param_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((param_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        param_buf.value = static_cast<Ark_Object>(thisDeserializer.readObject());
    }
    Opt_Object param = param_buf;
    _callSync(vmContext, _resourceId, name, param);
}
void deserializeAndCallPageTransitionCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_RouteType type, const Ark_Number progress)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_RouteType type = static_cast<Ark_RouteType>(thisDeserializer.readInt32());
    Ark_Number progress = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _call(_resourceId, type, progress);
}
void deserializeAndCallSyncPageTransitionCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_RouteType type, const Ark_Number progress)>(thisDeserializer.readPointer());
    Ark_RouteType type = static_cast<Ark_RouteType>(thisDeserializer.readInt32());
    Ark_Number progress = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _callSync(vmContext, _resourceId, type, progress);
}
void deserializeAndCallPasteEventCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_PasteEvent event)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    const auto event_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_PasteEvent event_buf = {};
    event_buf.tag = event_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((event_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        event_buf.value = PasteEvent_serializer::read(thisDeserializer);
    }
    Opt_PasteEvent event = event_buf;
    _call(_resourceId, event);
}
void deserializeAndCallSyncPasteEventCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_PasteEvent event)>(thisDeserializer.readPointer());
    const auto event_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_PasteEvent event_buf = {};
    event_buf.tag = event_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((event_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        event_buf.value = PasteEvent_serializer::read(thisDeserializer);
    }
    Opt_PasteEvent event = event_buf;
    _callSync(vmContext, _resourceId, event);
}
void deserializeAndCallPluginErrorCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_PluginErrorData info)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_PluginErrorData info = PluginErrorData_serializer::read(thisDeserializer);
    _call(_resourceId, info);
}
void deserializeAndCallSyncPluginErrorCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_PluginErrorData info)>(thisDeserializer.readPointer());
    Ark_PluginErrorData info = PluginErrorData_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, info);
}
void deserializeAndCallPopupStateChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_PopupStateChangeParam event)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_PopupStateChangeParam event = PopupStateChangeParam_serializer::read(thisDeserializer);
    _call(_resourceId, event);
}
void deserializeAndCallSyncPopupStateChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_PopupStateChangeParam event)>(thisDeserializer.readPointer());
    Ark_PopupStateChangeParam event = PopupStateChangeParam_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, event);
}
void deserializeAndCallProgressModifierBuilder(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Ark_ProgressConfiguration config, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_ProgressConfiguration config = ProgressConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Pointer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Pointer_Void))))};
    _call(_resourceId, parentNode, config, _continuation);
}
void deserializeAndCallSyncProgressModifierBuilder(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Ark_ProgressConfiguration config, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointer());
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_ProgressConfiguration config = ProgressConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Pointer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Pointer_Void))))};
    _callSync(vmContext, _resourceId, parentNode, config, _continuation);
}
void deserializeAndCallRadioModifierBuilder(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Ark_RadioConfiguration config, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_RadioConfiguration config = RadioConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Pointer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Pointer_Void))))};
    _call(_resourceId, parentNode, config, _continuation);
}
void deserializeAndCallSyncRadioModifierBuilder(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Ark_RadioConfiguration config, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointer());
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_RadioConfiguration config = RadioConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Pointer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Pointer_Void))))};
    _callSync(vmContext, _resourceId, parentNode, config, _continuation);
}
void deserializeAndCallRatingModifierBuilder(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Ark_RatingConfiguration config, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_RatingConfiguration config = RatingConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Pointer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Pointer_Void))))};
    _call(_resourceId, parentNode, config, _continuation);
}
void deserializeAndCallSyncRatingModifierBuilder(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Ark_RatingConfiguration config, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointer());
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_RatingConfiguration config = RatingConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Pointer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Pointer_Void))))};
    _callSync(vmContext, _resourceId, parentNode, config, _continuation);
}
void deserializeAndCallRestrictedWorker_onerror_Callback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_ErrorEvent ev)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_ErrorEvent ev = ErrorEvent_serializer::read(thisDeserializer);
    _call(_resourceId, ev);
}
void deserializeAndCallSyncRestrictedWorker_onerror_Callback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_ErrorEvent ev)>(thisDeserializer.readPointer());
    Ark_ErrorEvent ev = ErrorEvent_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, ev);
}
void deserializeAndCallRestrictedWorker_onexit_Callback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number code)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number code = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _call(_resourceId, code);
}
void deserializeAndCallSyncRestrictedWorker_onexit_Callback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number code)>(thisDeserializer.readPointer());
    Ark_Number code = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _callSync(vmContext, _resourceId, code);
}
void deserializeAndCallRestrictedWorker_onmessage_Callback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_MessageEvents event)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_MessageEvents event = MessageEvents_serializer::read(thisDeserializer);
    _call(_resourceId, event);
}
void deserializeAndCallSyncRestrictedWorker_onmessage_Callback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_MessageEvents event)>(thisDeserializer.readPointer());
    Ark_MessageEvents event = MessageEvents_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, event);
}
void deserializeAndCallReuseIdCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Callback_String_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Callback_String_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_String breakpoints)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_String_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_String breakpoints)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_String_Void))))};
    _call(_resourceId, _continuation);
}
void deserializeAndCallSyncReuseIdCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Callback_String_Void continuation)>(thisDeserializer.readPointer());
    Callback_String_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_String breakpoints)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_String_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_String breakpoints)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_String_Void))))};
    _callSync(vmContext, _resourceId, _continuation);
}
void deserializeAndCallScrollOnScrollCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
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
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
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
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number xOffset, const Ark_Number yOffset, Ark_ScrollState scrollState, Ark_ScrollSource scrollSource, const Callback_Opt_OffsetResult_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number xOffset = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number yOffset = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_ScrollState scrollState = static_cast<Ark_ScrollState>(thisDeserializer.readInt32());
    Ark_ScrollSource scrollSource = static_cast<Ark_ScrollSource>(thisDeserializer.readInt32());
    Callback_Opt_OffsetResult_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_OffsetResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Opt_OffsetResult_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_OffsetResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Opt_OffsetResult_Void))))};
    _call(_resourceId, xOffset, yOffset, scrollState, scrollSource, _continuation);
}
void deserializeAndCallSyncScrollOnWillScrollCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number xOffset, const Ark_Number yOffset, Ark_ScrollState scrollState, Ark_ScrollSource scrollSource, const Callback_Opt_OffsetResult_Void continuation)>(thisDeserializer.readPointer());
    Ark_Number xOffset = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number yOffset = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_ScrollState scrollState = static_cast<Ark_ScrollState>(thisDeserializer.readInt32());
    Ark_ScrollSource scrollSource = static_cast<Ark_ScrollSource>(thisDeserializer.readInt32());
    Callback_Opt_OffsetResult_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_OffsetResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Opt_OffsetResult_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_OffsetResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Opt_OffsetResult_Void))))};
    _callSync(vmContext, _resourceId, xOffset, yOffset, scrollState, scrollSource, _continuation);
}
void deserializeAndCallSearchSubmitCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_String searchContent, const Opt_SubmitEvent event)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_String searchContent = static_cast<Ark_String>(thisDeserializer.readString());
    const auto event_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_SubmitEvent event_buf = {};
    event_buf.tag = event_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((event_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        event_buf.value = static_cast<Ark_SubmitEvent>(SubmitEvent_serializer::read(thisDeserializer));
    }
    Opt_SubmitEvent event = event_buf;
    _call(_resourceId, searchContent, event);
}
void deserializeAndCallSyncSearchSubmitCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_String searchContent, const Opt_SubmitEvent event)>(thisDeserializer.readPointer());
    Ark_String searchContent = static_cast<Ark_String>(thisDeserializer.readString());
    const auto event_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_SubmitEvent event_buf = {};
    event_buf.tag = event_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((event_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        event_buf.value = static_cast<Ark_SubmitEvent>(SubmitEvent_serializer::read(thisDeserializer));
    }
    Opt_SubmitEvent event = event_buf;
    _callSync(vmContext, _resourceId, searchContent, event);
}
void deserializeAndCallSearchValueCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_String value)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_String value = static_cast<Ark_String>(thisDeserializer.readString());
    _call(_resourceId, value);
}
void deserializeAndCallSyncSearchValueCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_String value)>(thisDeserializer.readPointer());
    Ark_String value = static_cast<Ark_String>(thisDeserializer.readString());
    _callSync(vmContext, _resourceId, value);
}
void deserializeAndCallShouldBuiltInRecognizerParallelWithCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_GestureRecognizer current, const Array_GestureRecognizer others, const Callback_GestureRecognizer_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_GestureRecognizer current = static_cast<Ark_GestureRecognizer>(GestureRecognizer_serializer::read(thisDeserializer));
    const Ark_Int32 others_buf_length = thisDeserializer.readInt32();
    Array_GestureRecognizer others_buf = {};
    thisDeserializer.resizeArray<std::decay<decltype(others_buf)>::type,
        std::decay<decltype(*others_buf.array)>::type>(&others_buf, others_buf_length);
    for (int others_buf_i = 0; others_buf_i < others_buf_length; others_buf_i++) {
        others_buf.array[others_buf_i] = static_cast<Ark_GestureRecognizer>(GestureRecognizer_serializer::read(thisDeserializer));
    }
    Array_GestureRecognizer others = others_buf;
    Callback_GestureRecognizer_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_GestureRecognizer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_GestureRecognizer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_GestureRecognizer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_GestureRecognizer_Void))))};
    _call(_resourceId, current, others, _continuation);
}
void deserializeAndCallSyncShouldBuiltInRecognizerParallelWithCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_GestureRecognizer current, const Array_GestureRecognizer others, const Callback_GestureRecognizer_Void continuation)>(thisDeserializer.readPointer());
    Ark_GestureRecognizer current = static_cast<Ark_GestureRecognizer>(GestureRecognizer_serializer::read(thisDeserializer));
    const Ark_Int32 others_buf_length = thisDeserializer.readInt32();
    Array_GestureRecognizer others_buf = {};
    thisDeserializer.resizeArray<std::decay<decltype(others_buf)>::type,
        std::decay<decltype(*others_buf.array)>::type>(&others_buf, others_buf_length);
    for (int others_buf_i = 0; others_buf_i < others_buf_length; others_buf_i++) {
        others_buf.array[others_buf_i] = static_cast<Ark_GestureRecognizer>(GestureRecognizer_serializer::read(thisDeserializer));
    }
    Array_GestureRecognizer others = others_buf;
    Callback_GestureRecognizer_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_GestureRecognizer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_GestureRecognizer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_GestureRecognizer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_GestureRecognizer_Void))))};
    _callSync(vmContext, _resourceId, current, others, _continuation);
}
void deserializeAndCallSizeChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_SizeOptions oldValue, const Ark_SizeOptions newValue)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_SizeOptions oldValue = SizeOptions_serializer::read(thisDeserializer);
    Ark_SizeOptions newValue = SizeOptions_serializer::read(thisDeserializer);
    _call(_resourceId, oldValue, newValue);
}
void deserializeAndCallSyncSizeChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_SizeOptions oldValue, const Ark_SizeOptions newValue)>(thisDeserializer.readPointer());
    Ark_SizeOptions oldValue = SizeOptions_serializer::read(thisDeserializer);
    Ark_SizeOptions newValue = SizeOptions_serializer::read(thisDeserializer);
    _callSync(vmContext, _resourceId, oldValue, newValue);
}
void deserializeAndCallSliderModifierBuilder(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Ark_SliderConfiguration config, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_SliderConfiguration config = SliderConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Pointer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Pointer_Void))))};
    _call(_resourceId, parentNode, config, _continuation);
}
void deserializeAndCallSyncSliderModifierBuilder(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Ark_SliderConfiguration config, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointer());
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_SliderConfiguration config = SliderConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Pointer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Pointer_Void))))};
    _callSync(vmContext, _resourceId, parentNode, config, _continuation);
}
void deserializeAndCallSliderTriggerChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number value, Ark_SliderChangeMode mode)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number value = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_SliderChangeMode mode = static_cast<Ark_SliderChangeMode>(thisDeserializer.readInt32());
    _call(_resourceId, value, mode);
}
void deserializeAndCallSyncSliderTriggerChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number value, Ark_SliderChangeMode mode)>(thisDeserializer.readPointer());
    Ark_Number value = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_SliderChangeMode mode = static_cast<Ark_SliderChangeMode>(thisDeserializer.readInt32());
    _callSync(vmContext, _resourceId, value, mode);
}
void deserializeAndCallStyledStringMarshallCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_UserDataSpan marshallableVal, const Callback_Buffer_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_UserDataSpan marshallableVal = static_cast<Ark_UserDataSpan>(UserDataSpan_serializer::read(thisDeserializer));
    Callback_Buffer_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Buffer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Buffer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Buffer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Buffer_Void))))};
    _call(_resourceId, marshallableVal, _continuation);
}
void deserializeAndCallSyncStyledStringMarshallCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_UserDataSpan marshallableVal, const Callback_Buffer_Void continuation)>(thisDeserializer.readPointer());
    Ark_UserDataSpan marshallableVal = static_cast<Ark_UserDataSpan>(UserDataSpan_serializer::read(thisDeserializer));
    Callback_Buffer_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Buffer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Buffer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Buffer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Buffer_Void))))};
    _callSync(vmContext, _resourceId, marshallableVal, _continuation);
}
void deserializeAndCallStyledStringUnmarshallCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Buffer buf, const Callback_StyledStringMarshallingValue_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Buffer buf = static_cast<Ark_Buffer>(thisDeserializer.readBuffer());
    Callback_StyledStringMarshallingValue_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_UserDataSpan value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_StyledStringMarshallingValue_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_UserDataSpan value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_StyledStringMarshallingValue_Void))))};
    _call(_resourceId, buf, _continuation);
}
void deserializeAndCallSyncStyledStringUnmarshallCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Buffer buf, const Callback_StyledStringMarshallingValue_Void continuation)>(thisDeserializer.readPointer());
    Ark_Buffer buf = static_cast<Ark_Buffer>(thisDeserializer.readBuffer());
    Callback_StyledStringMarshallingValue_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_UserDataSpan value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_StyledStringMarshallingValue_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_UserDataSpan value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_StyledStringMarshallingValue_Void))))};
    _callSync(vmContext, _resourceId, buf, _continuation);
}
void deserializeAndCallSubmitCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_EnterKeyType enterKey, const Ark_SubmitEvent event)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_EnterKeyType enterKey = static_cast<Ark_EnterKeyType>(thisDeserializer.readInt32());
    Ark_SubmitEvent event = static_cast<Ark_SubmitEvent>(SubmitEvent_serializer::read(thisDeserializer));
    _call(_resourceId, enterKey, event);
}
void deserializeAndCallSyncSubmitCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_EnterKeyType enterKey, const Ark_SubmitEvent event)>(thisDeserializer.readPointer());
    Ark_EnterKeyType enterKey = static_cast<Ark_EnterKeyType>(thisDeserializer.readInt32());
    Ark_SubmitEvent event = static_cast<Ark_SubmitEvent>(SubmitEvent_serializer::read(thisDeserializer));
    _callSync(vmContext, _resourceId, enterKey, event);
}
void deserializeAndCallTabsCustomContentTransitionCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
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
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
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
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_EnterKeyType enterKeyType, const Opt_SubmitEvent event)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_EnterKeyType enterKeyType = static_cast<Ark_EnterKeyType>(thisDeserializer.readInt32());
    const auto event_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_SubmitEvent event_buf = {};
    event_buf.tag = event_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((event_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        event_buf.value = static_cast<Ark_SubmitEvent>(SubmitEvent_serializer::read(thisDeserializer));
    }
    Opt_SubmitEvent event = event_buf;
    _call(_resourceId, enterKeyType, event);
}
void deserializeAndCallSyncTextAreaSubmitCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_EnterKeyType enterKeyType, const Opt_SubmitEvent event)>(thisDeserializer.readPointer());
    Ark_EnterKeyType enterKeyType = static_cast<Ark_EnterKeyType>(thisDeserializer.readInt32());
    const auto event_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_SubmitEvent event_buf = {};
    event_buf.tag = event_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((event_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        event_buf.value = static_cast<Ark_SubmitEvent>(SubmitEvent_serializer::read(thisDeserializer));
    }
    Opt_SubmitEvent event = event_buf;
    _callSync(vmContext, _resourceId, enterKeyType, event);
}
void deserializeAndCallTextClockModifierBuilder(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Ark_TextClockConfiguration config, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_TextClockConfiguration config = TextClockConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Pointer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Pointer_Void))))};
    _call(_resourceId, parentNode, config, _continuation);
}
void deserializeAndCallSyncTextClockModifierBuilder(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Ark_TextClockConfiguration config, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointer());
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_TextClockConfiguration config = TextClockConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Pointer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Pointer_Void))))};
    _callSync(vmContext, _resourceId, parentNode, config, _continuation);
}
void deserializeAndCallTextFieldValueCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
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
        value_buf.value1 = Resource_serializer::read(thisDeserializer);
    }
    else {
        INTEROP_FATAL("One of the branches for value_buf has to be chosen through deserialisation.");
    }
    Ark_ResourceStr value = static_cast<Ark_ResourceStr>(value_buf);
    _call(_resourceId, value);
}
void deserializeAndCallSyncTextFieldValueCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
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
        value_buf.value1 = Resource_serializer::read(thisDeserializer);
    }
    else {
        INTEROP_FATAL("One of the branches for value_buf has to be chosen through deserialisation.");
    }
    Ark_ResourceStr value = static_cast<Ark_ResourceStr>(value_buf);
    _callSync(vmContext, _resourceId, value);
}
void deserializeAndCallTextPickerEnterSelectedAreaCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
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
void deserializeAndCallSyncTextPickerEnterSelectedAreaCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
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
void deserializeAndCallTextPickerScrollStopCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
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
void deserializeAndCallSyncTextPickerScrollStopCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
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
void deserializeAndCallTextTimerModifierBuilder(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Ark_TextTimerConfiguration config, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_TextTimerConfiguration config = TextTimerConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Pointer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Pointer_Void))))};
    _call(_resourceId, parentNode, config, _continuation);
}
void deserializeAndCallSyncTextTimerModifierBuilder(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Ark_TextTimerConfiguration config, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointer());
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_TextTimerConfiguration config = TextTimerConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Pointer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Pointer_Void))))};
    _callSync(vmContext, _resourceId, parentNode, config, _continuation);
}
void deserializeAndCallToggleModifierBuilder(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Ark_ToggleConfiguration config, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_ToggleConfiguration config = ToggleConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Pointer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Pointer_Void))))};
    _call(_resourceId, parentNode, config, _continuation);
}
void deserializeAndCallSyncToggleModifierBuilder(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Ark_ToggleConfiguration config, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointer());
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_ToggleConfiguration config = ToggleConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Pointer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Pointer_Void))))};
    _callSync(vmContext, _resourceId, parentNode, config, _continuation);
}
void deserializeAndCallTransitionFinishCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean transitionIn)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Boolean transitionIn = thisDeserializer.readBoolean();
    _call(_resourceId, transitionIn);
}
void deserializeAndCallSyncTransitionFinishCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean transitionIn)>(thisDeserializer.readPointer());
    Ark_Boolean transitionIn = thisDeserializer.readBoolean();
    _callSync(vmContext, _resourceId, transitionIn);
}
void deserializeAndCallType_CommonMethod_onDragStart(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_DragEvent event, const Opt_String extraParams, const Callback_Union_CustomBuilder_DragItemInfo_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_DragEvent event = static_cast<Ark_DragEvent>(DragEvent_serializer::read(thisDeserializer));
    const auto extraParams_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_String extraParams_buf = {};
    extraParams_buf.tag = extraParams_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((extraParams_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        extraParams_buf.value = static_cast<Ark_String>(thisDeserializer.readString());
    }
    Opt_String extraParams = extraParams_buf;
    Callback_Union_CustomBuilder_DragItemInfo_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Union_CustomBuilder_DragItemInfo value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Union_CustomBuilder_DragItemInfo_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Union_CustomBuilder_DragItemInfo value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Union_CustomBuilder_DragItemInfo_Void))))};
    _call(_resourceId, event, extraParams, _continuation);
}
void deserializeAndCallSyncType_CommonMethod_onDragStart(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_DragEvent event, const Opt_String extraParams, const Callback_Union_CustomBuilder_DragItemInfo_Void continuation)>(thisDeserializer.readPointer());
    Ark_DragEvent event = static_cast<Ark_DragEvent>(DragEvent_serializer::read(thisDeserializer));
    const auto extraParams_buf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_String extraParams_buf = {};
    extraParams_buf.tag = extraParams_buf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((extraParams_buf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        extraParams_buf.value = static_cast<Ark_String>(thisDeserializer.readString());
    }
    Opt_String extraParams = extraParams_buf;
    Callback_Union_CustomBuilder_DragItemInfo_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Union_CustomBuilder_DragItemInfo value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Union_CustomBuilder_DragItemInfo_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Union_CustomBuilder_DragItemInfo value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Union_CustomBuilder_DragItemInfo_Void))))};
    _callSync(vmContext, _resourceId, event, extraParams, _continuation);
}
void deserializeAndCallType_NavigationAttribute_customNavContentTransition(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NavContentInfo from, const Ark_NavContentInfo to, Ark_NavigationOperation operation, const Callback_Opt_NavigationAnimatedTransition_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_NavContentInfo from = NavContentInfo_serializer::read(thisDeserializer);
    Ark_NavContentInfo to = NavContentInfo_serializer::read(thisDeserializer);
    Ark_NavigationOperation operation = static_cast<Ark_NavigationOperation>(thisDeserializer.readInt32());
    Callback_Opt_NavigationAnimatedTransition_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_NavigationAnimatedTransition value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Opt_NavigationAnimatedTransition_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_NavigationAnimatedTransition value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Opt_NavigationAnimatedTransition_Void))))};
    _call(_resourceId, from, to, operation, _continuation);
}
void deserializeAndCallSyncType_NavigationAttribute_customNavContentTransition(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NavContentInfo from, const Ark_NavContentInfo to, Ark_NavigationOperation operation, const Callback_Opt_NavigationAnimatedTransition_Void continuation)>(thisDeserializer.readPointer());
    Ark_NavContentInfo from = NavContentInfo_serializer::read(thisDeserializer);
    Ark_NavContentInfo to = NavContentInfo_serializer::read(thisDeserializer);
    Ark_NavigationOperation operation = static_cast<Ark_NavigationOperation>(thisDeserializer.readInt32());
    Callback_Opt_NavigationAnimatedTransition_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_NavigationAnimatedTransition value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Opt_NavigationAnimatedTransition_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_NavigationAnimatedTransition value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Opt_NavigationAnimatedTransition_Void))))};
    _callSync(vmContext, _resourceId, from, to, operation, _continuation);
}
void deserializeAndCallUpdateTransitionCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number progress)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Number progress = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _call(_resourceId, progress);
}
void deserializeAndCallSyncUpdateTransitionCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number progress)>(thisDeserializer.readPointer());
    Ark_Number progress = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _callSync(vmContext, _resourceId, progress);
}
void deserializeAndCallVisibleAreaChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean isExpanding, const Ark_Number currentRatio)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_Boolean isExpanding = thisDeserializer.readBoolean();
    Ark_Number currentRatio = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _call(_resourceId, isExpanding, currentRatio);
}
void deserializeAndCallSyncVisibleAreaChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isExpanding, const Ark_Number currentRatio)>(thisDeserializer.readPointer());
    Ark_Boolean isExpanding = thisDeserializer.readBoolean();
    Ark_Number currentRatio = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _callSync(vmContext, _resourceId, isExpanding, currentRatio);
}
void deserializeAndCallVoidCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    _call(_resourceId);
}
void deserializeAndCallSyncVoidCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId)>(thisDeserializer.readPointer());
    _callSync(vmContext, _resourceId);
}
void deserializeAndCallWebKeyboardCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_WebKeyboardCallbackInfo keyboardCallbackInfo, const Callback_WebKeyboardOptions_Void continuation)>(thisDeserializer.readPointer());
    thisDeserializer.readPointer();
    Ark_WebKeyboardCallbackInfo keyboardCallbackInfo = WebKeyboardCallbackInfo_serializer::read(thisDeserializer);
    Callback_WebKeyboardOptions_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_WebKeyboardOptions value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_WebKeyboardOptions_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_WebKeyboardOptions value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_WebKeyboardOptions_Void))))};
    _call(_resourceId, keyboardCallbackInfo, _continuation);
}
void deserializeAndCallSyncWebKeyboardCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto _callSync = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_WebKeyboardCallbackInfo keyboardCallbackInfo, const Callback_WebKeyboardOptions_Void continuation)>(thisDeserializer.readPointer());
    Ark_WebKeyboardCallbackInfo keyboardCallbackInfo = WebKeyboardCallbackInfo_serializer::read(thisDeserializer);
    Callback_WebKeyboardOptions_Void _continuation = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_WebKeyboardOptions value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_WebKeyboardOptions_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_WebKeyboardOptions value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_WebKeyboardOptions_Void))))};
    _callSync(vmContext, _resourceId, keyboardCallbackInfo, _continuation);
}
void deserializeAndCallCallback(Ark_Int32 kind, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    switch (static_cast<CallbackKind>(kind)) {
        case Kind_AccessibilityCallback: return deserializeAndCallAccessibilityCallback(thisArray, thisLength);
        case Kind_AccessibilityFocusCallback: return deserializeAndCallAccessibilityFocusCallback(thisArray, thisLength);
        case Kind_AsyncCallback_image_PixelMap_Void: return deserializeAndCallAsyncCallback_image_PixelMap_Void(thisArray, thisLength);
        case Kind_ButtonModifierBuilder: return deserializeAndCallButtonModifierBuilder(thisArray, thisLength);
        case Kind_ButtonTriggerClickCallback: return deserializeAndCallButtonTriggerClickCallback(thisArray, thisLength);
        case Kind_Callback_Area_Area_Void: return deserializeAndCallCallback_Area_Area_Void(thisArray, thisLength);
        case Kind_Callback_Array_Number_Void: return deserializeAndCallCallback_Array_Number_Void(thisArray, thisLength);
        case Kind_Callback_Array_String_Void: return deserializeAndCallCallback_Array_String_Void(thisArray, thisLength);
        case Kind_Callback_Array_TextMenuItem_Void: return deserializeAndCallCallback_Array_TextMenuItem_Void(thisArray, thisLength);
        case Kind_Callback_Array_TouchTestInfo_TouchResult: return deserializeAndCallCallback_Array_TouchTestInfo_TouchResult(thisArray, thisLength);
        case Kind_Callback_AxisEvent_Void: return deserializeAndCallCallback_AxisEvent_Void(thisArray, thisLength);
        case Kind_Callback_Boolean: return deserializeAndCallCallback_Boolean(thisArray, thisLength);
        case Kind_Callback_Boolean_HoverEvent_Void: return deserializeAndCallCallback_Boolean_HoverEvent_Void(thisArray, thisLength);
        case Kind_Callback_Boolean_Void: return deserializeAndCallCallback_Boolean_Void(thisArray, thisLength);
        case Kind_Callback_Buffer_Void: return deserializeAndCallCallback_Buffer_Void(thisArray, thisLength);
        case Kind_Callback_ClickEvent_LocationButtonOnClickResult_Void: return deserializeAndCallCallback_ClickEvent_LocationButtonOnClickResult_Void(thisArray, thisLength);
        case Kind_Callback_ClickEvent_PasteButtonOnClickResult_Void: return deserializeAndCallCallback_ClickEvent_PasteButtonOnClickResult_Void(thisArray, thisLength);
        case Kind_Callback_ClickEvent_SaveButtonOnClickResult_Void: return deserializeAndCallCallback_ClickEvent_SaveButtonOnClickResult_Void(thisArray, thisLength);
        case Kind_Callback_ClickEvent_Void: return deserializeAndCallCallback_ClickEvent_Void(thisArray, thisLength);
        case Kind_Callback_CompatibleComponentInfo_Void: return deserializeAndCallCallback_CompatibleComponentInfo_Void(thisArray, thisLength);
        case Kind_Callback_ComputedBarAttribute_Void: return deserializeAndCallCallback_ComputedBarAttribute_Void(thisArray, thisLength);
        case Kind_Callback_CopyEvent_Void: return deserializeAndCallCallback_CopyEvent_Void(thisArray, thisLength);
        case Kind_Callback_CreateItem: return deserializeAndCallCallback_CreateItem(thisArray, thisLength);
        case Kind_Callback_CrownEvent_Void: return deserializeAndCallCallback_CrownEvent_Void(thisArray, thisLength);
        case Kind_Callback_CustomSpanMeasureInfo_CustomSpanMetrics: return deserializeAndCallCallback_CustomSpanMeasureInfo_CustomSpanMetrics(thisArray, thisLength);
        case Kind_Callback_CustomSpanMetrics_Void: return deserializeAndCallCallback_CustomSpanMetrics_Void(thisArray, thisLength);
        case Kind_Callback_CutEvent_Void: return deserializeAndCallCallback_CutEvent_Void(thisArray, thisLength);
        case Kind_Callback_Date_Void: return deserializeAndCallCallback_Date_Void(thisArray, thisLength);
        case Kind_Callback_DeleteValue_Boolean: return deserializeAndCallCallback_DeleteValue_Boolean(thisArray, thisLength);
        case Kind_Callback_DeleteValue_Void: return deserializeAndCallCallback_DeleteValue_Void(thisArray, thisLength);
        case Kind_Callback_DismissContentCoverAction_Void: return deserializeAndCallCallback_DismissContentCoverAction_Void(thisArray, thisLength);
        case Kind_Callback_DismissDialogAction_Void: return deserializeAndCallCallback_DismissDialogAction_Void(thisArray, thisLength);
        case Kind_Callback_DismissPopupAction_Void: return deserializeAndCallCallback_DismissPopupAction_Void(thisArray, thisLength);
        case Kind_Callback_DismissSheetAction_Void: return deserializeAndCallCallback_DismissSheetAction_Void(thisArray, thisLength);
        case Kind_Callback_DragEvent_Opt_String_Void: return deserializeAndCallCallback_DragEvent_Opt_String_Void(thisArray, thisLength);
        case Kind_Callback_DrawContext_CustomSpanDrawInfo_Void: return deserializeAndCallCallback_DrawContext_CustomSpanDrawInfo_Void(thisArray, thisLength);
        case Kind_Callback_DrawContext_Void: return deserializeAndCallCallback_DrawContext_Void(thisArray, thisLength);
        case Kind_Callback_EditableTextChangeValue_Boolean: return deserializeAndCallCallback_EditableTextChangeValue_Boolean(thisArray, thisLength);
        case Kind_Callback_EnterKeyType_Void: return deserializeAndCallCallback_EnterKeyType_Void(thisArray, thisLength);
        case Kind_Callback_ErrorInformation_Void: return deserializeAndCallCallback_ErrorInformation_Void(thisArray, thisLength);
        case Kind_Callback_Extender_OnFinish: return deserializeAndCallCallback_Extender_OnFinish(thisArray, thisLength);
        case Kind_Callback_Extender_OnProgress: return deserializeAndCallCallback_Extender_OnProgress(thisArray, thisLength);
        case Kind_Callback_FocusAxisEvent_Void: return deserializeAndCallCallback_FocusAxisEvent_Void(thisArray, thisLength);
        case Kind_Callback_FormCallbackInfo_Void: return deserializeAndCallCallback_FormCallbackInfo_Void(thisArray, thisLength);
        case Kind_Callback_FullscreenInfo_Void: return deserializeAndCallCallback_FullscreenInfo_Void(thisArray, thisLength);
        case Kind_Callback_GestureEvent_Void: return deserializeAndCallCallback_GestureEvent_Void(thisArray, thisLength);
        case Kind_Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult: return deserializeAndCallCallback_GestureInfo_BaseGestureEvent_GestureJudgeResult(thisArray, thisLength);
        case Kind_Callback_GestureJudgeResult_Void: return deserializeAndCallCallback_GestureJudgeResult_Void(thisArray, thisLength);
        case Kind_Callback_GestureRecognizer_Void: return deserializeAndCallCallback_GestureRecognizer_Void(thisArray, thisLength);
        case Kind_Callback_HitTestMode_Void: return deserializeAndCallCallback_HitTestMode_Void(thisArray, thisLength);
        case Kind_Callback_HoverEvent_Void: return deserializeAndCallCallback_HoverEvent_Void(thisArray, thisLength);
        case Kind_Callback_InsertValue_Boolean: return deserializeAndCallCallback_InsertValue_Boolean(thisArray, thisLength);
        case Kind_Callback_InsertValue_Void: return deserializeAndCallCallback_InsertValue_Void(thisArray, thisLength);
        case Kind_Callback_ItemDragInfo_Number_Number_Boolean_Void: return deserializeAndCallCallback_ItemDragInfo_Number_Number_Boolean_Void(thisArray, thisLength);
        case Kind_Callback_ItemDragInfo_Number_Number_Void: return deserializeAndCallCallback_ItemDragInfo_Number_Number_Void(thisArray, thisLength);
        case Kind_Callback_ItemDragInfo_Number_Void: return deserializeAndCallCallback_ItemDragInfo_Number_Void(thisArray, thisLength);
        case Kind_Callback_ItemDragInfo_Void: return deserializeAndCallCallback_ItemDragInfo_Void(thisArray, thisLength);
        case Kind_Callback_KeyEvent_Boolean: return deserializeAndCallCallback_KeyEvent_Boolean(thisArray, thisLength);
        case Kind_Callback_KeyEvent_Void: return deserializeAndCallCallback_KeyEvent_Void(thisArray, thisLength);
        case Kind_Callback_Map_String_Object_Void: return deserializeAndCallCallback_Map_String_Object_Void(thisArray, thisLength);
        case Kind_Callback_MarqueeState_Void: return deserializeAndCallCallback_MarqueeState_Void(thisArray, thisLength);
        case Kind_Callback_MouseEvent_Void: return deserializeAndCallCallback_MouseEvent_Void(thisArray, thisLength);
        case Kind_Callback_NativeEmbedDataInfo_Void: return deserializeAndCallCallback_NativeEmbedDataInfo_Void(thisArray, thisLength);
        case Kind_Callback_NativeEmbedTouchInfo_Void: return deserializeAndCallCallback_NativeEmbedTouchInfo_Void(thisArray, thisLength);
        case Kind_Callback_NavDestinationActiveReason_Void: return deserializeAndCallCallback_NavDestinationActiveReason_Void(thisArray, thisLength);
        case Kind_Callback_NavDestinationContext_Void: return deserializeAndCallCallback_NavDestinationContext_Void(thisArray, thisLength);
        case Kind_Callback_NavigationMode_Void: return deserializeAndCallCallback_NavigationMode_Void(thisArray, thisLength);
        case Kind_Callback_NavigationTitleMode_Void: return deserializeAndCallCallback_NavigationTitleMode_Void(thisArray, thisLength);
        case Kind_Callback_NavigationTransitionProxy_Void: return deserializeAndCallCallback_NavigationTransitionProxy_Void(thisArray, thisLength);
        case Kind_Callback_Number_Number_Boolean: return deserializeAndCallCallback_Number_Number_Boolean(thisArray, thisLength);
        case Kind_Callback_Number_Number_Boolean_Boolean: return deserializeAndCallCallback_Number_Number_Boolean_Boolean(thisArray, thisLength);
        case Kind_Callback_Number_Number_ComputedBarAttribute: return deserializeAndCallCallback_Number_Number_ComputedBarAttribute(thisArray, thisLength);
        case Kind_Callback_Number_Number_Number_Void: return deserializeAndCallCallback_Number_Number_Number_Void(thisArray, thisLength);
        case Kind_Callback_Number_Number_Void: return deserializeAndCallCallback_Number_Number_Void(thisArray, thisLength);
        case Kind_Callback_Number_SliderChangeMode_Void: return deserializeAndCallCallback_Number_SliderChangeMode_Void(thisArray, thisLength);
        case Kind_Callback_Number_Tuple_Number_Number: return deserializeAndCallCallback_Number_Tuple_Number_Number(thisArray, thisLength);
        case Kind_Callback_Number_Tuple_Number_Number_Number_Number: return deserializeAndCallCallback_Number_Tuple_Number_Number_Number_Number(thisArray, thisLength);
        case Kind_Callback_Number_Void: return deserializeAndCallCallback_Number_Void(thisArray, thisLength);
        case Kind_Callback_Object_Void: return deserializeAndCallCallback_Object_Void(thisArray, thisLength);
        case Kind_Callback_OnAlertEvent_Boolean: return deserializeAndCallCallback_OnAlertEvent_Boolean(thisArray, thisLength);
        case Kind_Callback_OnAudioStateChangedEvent_Void: return deserializeAndCallCallback_OnAudioStateChangedEvent_Void(thisArray, thisLength);
        case Kind_Callback_OnBeforeUnloadEvent_Boolean: return deserializeAndCallCallback_OnBeforeUnloadEvent_Boolean(thisArray, thisLength);
        case Kind_Callback_OnClientAuthenticationEvent_Void: return deserializeAndCallCallback_OnClientAuthenticationEvent_Void(thisArray, thisLength);
        case Kind_Callback_OnConfirmEvent_Boolean: return deserializeAndCallCallback_OnConfirmEvent_Boolean(thisArray, thisLength);
        case Kind_Callback_OnConsoleEvent_Boolean: return deserializeAndCallCallback_OnConsoleEvent_Boolean(thisArray, thisLength);
        case Kind_Callback_OnContextMenuShowEvent_Boolean: return deserializeAndCallCallback_OnContextMenuShowEvent_Boolean(thisArray, thisLength);
        case Kind_Callback_OnDataResubmittedEvent_Void: return deserializeAndCallCallback_OnDataResubmittedEvent_Void(thisArray, thisLength);
        case Kind_Callback_OnDownloadStartEvent_Void: return deserializeAndCallCallback_OnDownloadStartEvent_Void(thisArray, thisLength);
        case Kind_Callback_OnErrorReceiveEvent_Void: return deserializeAndCallCallback_OnErrorReceiveEvent_Void(thisArray, thisLength);
        case Kind_Callback_OnFaviconReceivedEvent_Void: return deserializeAndCallCallback_OnFaviconReceivedEvent_Void(thisArray, thisLength);
        case Kind_Callback_OnFirstContentfulPaintEvent_Void: return deserializeAndCallCallback_OnFirstContentfulPaintEvent_Void(thisArray, thisLength);
        case Kind_Callback_OnGeolocationShowEvent_Void: return deserializeAndCallCallback_OnGeolocationShowEvent_Void(thisArray, thisLength);
        case Kind_Callback_OnHttpAuthRequestEvent_Boolean: return deserializeAndCallCallback_OnHttpAuthRequestEvent_Boolean(thisArray, thisLength);
        case Kind_Callback_OnHttpErrorReceiveEvent_Void: return deserializeAndCallCallback_OnHttpErrorReceiveEvent_Void(thisArray, thisLength);
        case Kind_Callback_OnInterceptRequestEvent_WebResourceResponse: return deserializeAndCallCallback_OnInterceptRequestEvent_WebResourceResponse(thisArray, thisLength);
        case Kind_Callback_OnLoadInterceptEvent_Boolean: return deserializeAndCallCallback_OnLoadInterceptEvent_Boolean(thisArray, thisLength);
        case Kind_Callback_onMeasureSize_SizeResult: return deserializeAndCallCallback_onMeasureSize_SizeResult(thisArray, thisLength);
        case Kind_Callback_OnOverScrollEvent_Void: return deserializeAndCallCallback_OnOverScrollEvent_Void(thisArray, thisLength);
        case Kind_Callback_OnPageBeginEvent_Void: return deserializeAndCallCallback_OnPageBeginEvent_Void(thisArray, thisLength);
        case Kind_Callback_OnPageEndEvent_Void: return deserializeAndCallCallback_OnPageEndEvent_Void(thisArray, thisLength);
        case Kind_Callback_OnPageVisibleEvent_Void: return deserializeAndCallCallback_OnPageVisibleEvent_Void(thisArray, thisLength);
        case Kind_Callback_OnPermissionRequestEvent_Void: return deserializeAndCallCallback_OnPermissionRequestEvent_Void(thisArray, thisLength);
        case Kind_Callback_onPlaceChildren_Void: return deserializeAndCallCallback_onPlaceChildren_Void(thisArray, thisLength);
        case Kind_Callback_OnProgressChangeEvent_Void: return deserializeAndCallCallback_OnProgressChangeEvent_Void(thisArray, thisLength);
        case Kind_Callback_OnPromptEvent_Boolean: return deserializeAndCallCallback_OnPromptEvent_Boolean(thisArray, thisLength);
        case Kind_Callback_OnRefreshAccessedHistoryEvent_Void: return deserializeAndCallCallback_OnRefreshAccessedHistoryEvent_Void(thisArray, thisLength);
        case Kind_Callback_OnRenderExitedEvent_Void: return deserializeAndCallCallback_OnRenderExitedEvent_Void(thisArray, thisLength);
        case Kind_Callback_OnResourceLoadEvent_Void: return deserializeAndCallCallback_OnResourceLoadEvent_Void(thisArray, thisLength);
        case Kind_Callback_OnScaleChangeEvent_Void: return deserializeAndCallCallback_OnScaleChangeEvent_Void(thisArray, thisLength);
        case Kind_Callback_OnScreenCaptureRequestEvent_Void: return deserializeAndCallCallback_OnScreenCaptureRequestEvent_Void(thisArray, thisLength);
        case Kind_Callback_OnScrollEvent_Void: return deserializeAndCallCallback_OnScrollEvent_Void(thisArray, thisLength);
        case Kind_Callback_OnScrollFrameBeginHandlerResult_Void: return deserializeAndCallCallback_OnScrollFrameBeginHandlerResult_Void(thisArray, thisLength);
        case Kind_Callback_OnSearchResultReceiveEvent_Void: return deserializeAndCallCallback_OnSearchResultReceiveEvent_Void(thisArray, thisLength);
        case Kind_Callback_OnShowFileSelectorEvent_Boolean: return deserializeAndCallCallback_OnShowFileSelectorEvent_Boolean(thisArray, thisLength);
        case Kind_Callback_OnSslErrorEventReceiveEvent_Void: return deserializeAndCallCallback_OnSslErrorEventReceiveEvent_Void(thisArray, thisLength);
        case Kind_Callback_OnTitleReceiveEvent_Void: return deserializeAndCallCallback_OnTitleReceiveEvent_Void(thisArray, thisLength);
        case Kind_Callback_OnTouchIconUrlReceivedEvent_Void: return deserializeAndCallCallback_OnTouchIconUrlReceivedEvent_Void(thisArray, thisLength);
        case Kind_Callback_OnWindowNewEvent_Void: return deserializeAndCallCallback_OnWindowNewEvent_Void(thisArray, thisLength);
        case Kind_Callback_Opt_Array_FontDescriptor_Opt_Array_String_Void: return deserializeAndCallCallback_Opt_Array_FontDescriptor_Opt_Array_String_Void(thisArray, thisLength);
        case Kind_Callback_Opt_Array_NavDestinationTransition_Void: return deserializeAndCallCallback_Opt_Array_NavDestinationTransition_Void(thisArray, thisLength);
        case Kind_Callback_Opt_Array_String_Opt_Array_String_Void: return deserializeAndCallCallback_Opt_Array_String_Opt_Array_String_Void(thisArray, thisLength);
        case Kind_Callback_Opt_Array_String_Void: return deserializeAndCallCallback_Opt_Array_String_Void(thisArray, thisLength);
        case Kind_Callback_Opt_Boolean_Void: return deserializeAndCallCallback_Opt_Boolean_Void(thisArray, thisLength);
        case Kind_Callback_Opt_CustomBuilder_Void: return deserializeAndCallCallback_Opt_CustomBuilder_Void(thisArray, thisLength);
        case Kind_Callback_Opt_FontDescriptor_Opt_Array_String_Void: return deserializeAndCallCallback_Opt_FontDescriptor_Opt_Array_String_Void(thisArray, thisLength);
        case Kind_Callback_Opt_NavigationAnimatedTransition_Void: return deserializeAndCallCallback_Opt_NavigationAnimatedTransition_Void(thisArray, thisLength);
        case Kind_Callback_Opt_Number_Void: return deserializeAndCallCallback_Opt_Number_Void(thisArray, thisLength);
        case Kind_Callback_Opt_Object_Void: return deserializeAndCallCallback_Opt_Object_Void(thisArray, thisLength);
        case Kind_Callback_Opt_OffsetResult_Void: return deserializeAndCallCallback_Opt_OffsetResult_Void(thisArray, thisLength);
        case Kind_Callback_Opt_Scene_Opt_Array_String_Void: return deserializeAndCallCallback_Opt_Scene_Opt_Array_String_Void(thisArray, thisLength);
        case Kind_Callback_Opt_ScrollResult_Void: return deserializeAndCallCallback_Opt_ScrollResult_Void(thisArray, thisLength);
        case Kind_Callback_Opt_String_Opt_Array_String_Void: return deserializeAndCallCallback_Opt_String_Opt_Array_String_Void(thisArray, thisLength);
        case Kind_Callback_Opt_StyledString_Opt_Array_String_Void: return deserializeAndCallCallback_Opt_StyledString_Opt_Array_String_Void(thisArray, thisLength);
        case Kind_Callback_Opt_TabContentAnimatedTransition_Void: return deserializeAndCallCallback_Opt_TabContentAnimatedTransition_Void(thisArray, thisLength);
        case Kind_Callback_Opt_Union_Number_Resource_Void: return deserializeAndCallCallback_Opt_Union_Number_Resource_Void(thisArray, thisLength);
        case Kind_Callback_Opt_Union_ResourceStr_String_Resource_Void: return deserializeAndCallCallback_Opt_Union_ResourceStr_String_Resource_Void(thisArray, thisLength);
        case Kind_Callback_PlaybackInfo_Void: return deserializeAndCallCallback_PlaybackInfo_Void(thisArray, thisLength);
        case Kind_Callback_Pointer_Void: return deserializeAndCallCallback_Pointer_Void(thisArray, thisLength);
        case Kind_Callback_PopInfo_Void: return deserializeAndCallCallback_PopInfo_Void(thisArray, thisLength);
        case Kind_Callback_PreDragStatus_Void: return deserializeAndCallCallback_PreDragStatus_Void(thisArray, thisLength);
        case Kind_Callback_PreparedInfo_Void: return deserializeAndCallCallback_PreparedInfo_Void(thisArray, thisLength);
        case Kind_Callback_RangeUpdate: return deserializeAndCallCallback_RangeUpdate(thisArray, thisLength);
        case Kind_Callback_RefreshStatus_Void: return deserializeAndCallCallback_RefreshStatus_Void(thisArray, thisLength);
        case Kind_Callback_RichEditorChangeValue_Boolean: return deserializeAndCallCallback_RichEditorChangeValue_Boolean(thisArray, thisLength);
        case Kind_Callback_RichEditorDeleteValue_Boolean: return deserializeAndCallCallback_RichEditorDeleteValue_Boolean(thisArray, thisLength);
        case Kind_Callback_RichEditorInsertValue_Boolean: return deserializeAndCallCallback_RichEditorInsertValue_Boolean(thisArray, thisLength);
        case Kind_Callback_RichEditorRange_Void: return deserializeAndCallCallback_RichEditorRange_Void(thisArray, thisLength);
        case Kind_Callback_RichEditorSelection_Void: return deserializeAndCallCallback_RichEditorSelection_Void(thisArray, thisLength);
        case Kind_Callback_RichEditorTextSpanResult_Void: return deserializeAndCallCallback_RichEditorTextSpanResult_Void(thisArray, thisLength);
        case Kind_Callback_RotationGesture: return deserializeAndCallCallback_RotationGesture(thisArray, thisLength);
        case Kind_Callback_RotationGesture_Void: return deserializeAndCallCallback_RotationGesture_Void(thisArray, thisLength);
        case Kind_Callback_SheetDismiss_Void: return deserializeAndCallCallback_SheetDismiss_Void(thisArray, thisLength);
        case Kind_Callback_SheetType_Void: return deserializeAndCallCallback_SheetType_Void(thisArray, thisLength);
        case Kind_Callback_SizeResult_Void: return deserializeAndCallCallback_SizeResult_Void(thisArray, thisLength);
        case Kind_Callback_SpringBackAction_Void: return deserializeAndCallCallback_SpringBackAction_Void(thisArray, thisLength);
        case Kind_Callback_StateStylesChange: return deserializeAndCallCallback_StateStylesChange(thisArray, thisLength);
        case Kind_Callback_String_PasteEvent_Void: return deserializeAndCallCallback_String_PasteEvent_Void(thisArray, thisLength);
        case Kind_Callback_String_SurfaceRect_Void: return deserializeAndCallCallback_String_SurfaceRect_Void(thisArray, thisLength);
        case Kind_Callback_String_Void: return deserializeAndCallCallback_String_Void(thisArray, thisLength);
        case Kind_Callback_StyledStringChangeValue_Boolean: return deserializeAndCallCallback_StyledStringChangeValue_Boolean(thisArray, thisLength);
        case Kind_Callback_StyledStringMarshallingValue_Void: return deserializeAndCallCallback_StyledStringMarshallingValue_Void(thisArray, thisLength);
        case Kind_Callback_SwipeActionState_Void: return deserializeAndCallCallback_SwipeActionState_Void(thisArray, thisLength);
        case Kind_Callback_SwipeGesture: return deserializeAndCallCallback_SwipeGesture(thisArray, thisLength);
        case Kind_Callback_SwipeGesture_Void: return deserializeAndCallCallback_SwipeGesture_Void(thisArray, thisLength);
        case Kind_Callback_SwiperContentTransitionProxy_Void: return deserializeAndCallCallback_SwiperContentTransitionProxy_Void(thisArray, thisLength);
        case Kind_Callback_TabContentTransitionProxy_Void: return deserializeAndCallCallback_TabContentTransitionProxy_Void(thisArray, thisLength);
        case Kind_Callback_TerminationInfo_Void: return deserializeAndCallCallback_TerminationInfo_Void(thisArray, thisLength);
        case Kind_Callback_TextPickerResult_Void: return deserializeAndCallCallback_TextPickerResult_Void(thisArray, thisLength);
        case Kind_Callback_TextRange_Void: return deserializeAndCallCallback_TextRange_Void(thisArray, thisLength);
        case Kind_Callback_TimePickerResult_Void: return deserializeAndCallCallback_TimePickerResult_Void(thisArray, thisLength);
        case Kind_Callback_TouchEvent_HitTestMode: return deserializeAndCallCallback_TouchEvent_HitTestMode(thisArray, thisLength);
        case Kind_Callback_TouchEvent_Void: return deserializeAndCallCallback_TouchEvent_Void(thisArray, thisLength);
        case Kind_Callback_TouchResult_Void: return deserializeAndCallCallback_TouchResult_Void(thisArray, thisLength);
        case Kind_Callback_Tuple_Number_Number_Number_Number_Void: return deserializeAndCallCallback_Tuple_Number_Number_Number_Number_Void(thisArray, thisLength);
        case Kind_Callback_Tuple_Number_Number_Void: return deserializeAndCallCallback_Tuple_Number_Number_Void(thisArray, thisLength);
        case Kind_Callback_UIExtensionProxy_Void: return deserializeAndCallCallback_UIExtensionProxy_Void(thisArray, thisLength);
        case Kind_Callback_Union_CustomBuilder_DragItemInfo_Void: return deserializeAndCallCallback_Union_CustomBuilder_DragItemInfo_Void(thisArray, thisLength);
        case Kind_Callback_Union_Number_Array_Number_Void: return deserializeAndCallCallback_Union_Number_Array_Number_Void(thisArray, thisLength);
        case Kind_Callback_Union_ResourceStr_Array_ResourceStr_Void: return deserializeAndCallCallback_Union_ResourceStr_Array_ResourceStr_Void(thisArray, thisLength);
        case Kind_Callback_Union_ResourceStr_Resource_String_Void: return deserializeAndCallCallback_Union_ResourceStr_Resource_String_Void(thisArray, thisLength);
        case Kind_Callback_Void: return deserializeAndCallCallback_Void(thisArray, thisLength);
        case Kind_Callback_WebKeyboardOptions_Void: return deserializeAndCallCallback_WebKeyboardOptions_Void(thisArray, thisLength);
        case Kind_Callback_WebResourceResponse_Void: return deserializeAndCallCallback_WebResourceResponse_Void(thisArray, thisLength);
        case Kind_CheckBoxModifierBuilder: return deserializeAndCallCheckBoxModifierBuilder(thisArray, thisLength);
        case Kind_CompatibleInitCallback: return deserializeAndCallCompatibleInitCallback(thisArray, thisLength);
        case Kind_CompatibleUpdateCallback: return deserializeAndCallCompatibleUpdateCallback(thisArray, thisLength);
        case Kind_ContentDidScrollCallback: return deserializeAndCallContentDidScrollCallback(thisArray, thisLength);
        case Kind_ContentWillScrollCallback: return deserializeAndCallContentWillScrollCallback(thisArray, thisLength);
        case Kind_Context_getGroupDir_Callback: return deserializeAndCallContext_getGroupDir_Callback(thisArray, thisLength);
        case Kind_CustomNodeBuilder: return deserializeAndCallCustomNodeBuilder(thisArray, thisLength);
        case Kind_CustomStyles: return deserializeAndCallCustomStyles(thisArray, thisLength);
        case Kind_DataPanelModifierBuilder: return deserializeAndCallDataPanelModifierBuilder(thisArray, thisLength);
        case Kind_EditableTextOnChangeCallback: return deserializeAndCallEditableTextOnChangeCallback(thisArray, thisLength);
        case Kind_ErrorCallback: return deserializeAndCallErrorCallback(thisArray, thisLength);
        case Kind_GaugeModifierBuilder: return deserializeAndCallGaugeModifierBuilder(thisArray, thisLength);
        case Kind_GestureRecognizerJudgeBeginCallback: return deserializeAndCallGestureRecognizerJudgeBeginCallback(thisArray, thisLength);
        case Kind_GetItemMainSizeByIndex: return deserializeAndCallGetItemMainSizeByIndex(thisArray, thisLength);
        case Kind_HoverCallback: return deserializeAndCallHoverCallback(thisArray, thisLength);
        case Kind_ImageCompleteCallback: return deserializeAndCallImageCompleteCallback(thisArray, thisLength);
        case Kind_ImageErrorCallback: return deserializeAndCallImageErrorCallback(thisArray, thisLength);
        case Kind_ImageOnCompleteCallback: return deserializeAndCallImageOnCompleteCallback(thisArray, thisLength);
        case Kind_InterceptionModeCallback: return deserializeAndCallInterceptionModeCallback(thisArray, thisLength);
        case Kind_InterceptionShowCallback: return deserializeAndCallInterceptionShowCallback(thisArray, thisLength);
        case Kind_LoadingProgressModifierBuilder: return deserializeAndCallLoadingProgressModifierBuilder(thisArray, thisLength);
        case Kind_MenuCallback: return deserializeAndCallMenuCallback(thisArray, thisLength);
        case Kind_MenuItemModifierBuilder: return deserializeAndCallMenuItemModifierBuilder(thisArray, thisLength);
        case Kind_MenuOnAppearCallback: return deserializeAndCallMenuOnAppearCallback(thisArray, thisLength);
        case Kind_ModifierKeyStateGetter: return deserializeAndCallModifierKeyStateGetter(thisArray, thisLength);
        case Kind_NavDestinationTransitionDelegate: return deserializeAndCallNavDestinationTransitionDelegate(thisArray, thisLength);
        case Kind_NavExtender_OnUpdateStack: return deserializeAndCallNavExtender_OnUpdateStack(thisArray, thisLength);
        case Kind_OnAdsBlockedCallback: return deserializeAndCallOnAdsBlockedCallback(thisArray, thisLength);
        case Kind_OnAlphabetIndexerPopupSelectCallback: return deserializeAndCallOnAlphabetIndexerPopupSelectCallback(thisArray, thisLength);
        case Kind_OnAlphabetIndexerRequestPopupDataCallback: return deserializeAndCallOnAlphabetIndexerRequestPopupDataCallback(thisArray, thisLength);
        case Kind_OnAlphabetIndexerSelectCallback: return deserializeAndCallOnAlphabetIndexerSelectCallback(thisArray, thisLength);
        case Kind_OnCheckboxChangeCallback: return deserializeAndCallOnCheckboxChangeCallback(thisArray, thisLength);
        case Kind_OnCheckboxGroupChangeCallback: return deserializeAndCallOnCheckboxGroupChangeCallback(thisArray, thisLength);
        case Kind_OnContentScrollCallback: return deserializeAndCallOnContentScrollCallback(thisArray, thisLength);
        case Kind_OnContextMenuHideCallback: return deserializeAndCallOnContextMenuHideCallback(thisArray, thisLength);
        case Kind_OnCreateMenuCallback: return deserializeAndCallOnCreateMenuCallback(thisArray, thisLength);
        case Kind_OnDidChangeCallback: return deserializeAndCallOnDidChangeCallback(thisArray, thisLength);
        case Kind_OnDragEventCallback: return deserializeAndCallOnDragEventCallback(thisArray, thisLength);
        case Kind_OnFirstMeaningfulPaintCallback: return deserializeAndCallOnFirstMeaningfulPaintCallback(thisArray, thisLength);
        case Kind_OnFoldStatusChangeCallback: return deserializeAndCallOnFoldStatusChangeCallback(thisArray, thisLength);
        case Kind_OnFullScreenEnterCallback: return deserializeAndCallOnFullScreenEnterCallback(thisArray, thisLength);
        case Kind_OnHoverCallback: return deserializeAndCallOnHoverCallback(thisArray, thisLength);
        case Kind_OnHoverStatusChangeCallback: return deserializeAndCallOnHoverStatusChangeCallback(thisArray, thisLength);
        case Kind_OnIntelligentTrackingPreventionCallback: return deserializeAndCallOnIntelligentTrackingPreventionCallback(thisArray, thisLength);
        case Kind_OnItemDragStartCallback: return deserializeAndCallOnItemDragStartCallback(thisArray, thisLength);
        case Kind_OnLargestContentfulPaintCallback: return deserializeAndCallOnLargestContentfulPaintCallback(thisArray, thisLength);
        case Kind_OnLinearIndicatorChangeCallback: return deserializeAndCallOnLinearIndicatorChangeCallback(thisArray, thisLength);
        case Kind_OnMenuItemClickCallback: return deserializeAndCallOnMenuItemClickCallback(thisArray, thisLength);
        case Kind_OnMoveHandler: return deserializeAndCallOnMoveHandler(thisArray, thisLength);
        case Kind_OnNativeEmbedVisibilityChangeCallback: return deserializeAndCallOnNativeEmbedVisibilityChangeCallback(thisArray, thisLength);
        case Kind_OnNativeLoadCallback: return deserializeAndCallOnNativeLoadCallback(thisArray, thisLength);
        case Kind_OnNavigationEntryCommittedCallback: return deserializeAndCallOnNavigationEntryCommittedCallback(thisArray, thisLength);
        case Kind_OnOverrideUrlLoadingCallback: return deserializeAndCallOnOverrideUrlLoadingCallback(thisArray, thisLength);
        case Kind_OnPasteCallback: return deserializeAndCallOnPasteCallback(thisArray, thisLength);
        case Kind_OnRadioChangeCallback: return deserializeAndCallOnRadioChangeCallback(thisArray, thisLength);
        case Kind_OnRatingChangeCallback: return deserializeAndCallOnRatingChangeCallback(thisArray, thisLength);
        case Kind_OnRenderProcessNotRespondingCallback: return deserializeAndCallOnRenderProcessNotRespondingCallback(thisArray, thisLength);
        case Kind_OnRenderProcessRespondingCallback: return deserializeAndCallOnRenderProcessRespondingCallback(thisArray, thisLength);
        case Kind_OnSafeBrowsingCheckResultCallback: return deserializeAndCallOnSafeBrowsingCheckResultCallback(thisArray, thisLength);
        case Kind_OnScrollCallback: return deserializeAndCallOnScrollCallback(thisArray, thisLength);
        case Kind_OnScrollEdgeCallback: return deserializeAndCallOnScrollEdgeCallback(thisArray, thisLength);
        case Kind_OnScrollFrameBeginCallback: return deserializeAndCallOnScrollFrameBeginCallback(thisArray, thisLength);
        case Kind_OnScrollVisibleContentChangeCallback: return deserializeAndCallOnScrollVisibleContentChangeCallback(thisArray, thisLength);
        case Kind_OnSelectCallback: return deserializeAndCallOnSelectCallback(thisArray, thisLength);
        case Kind_OnSslErrorEventCallback: return deserializeAndCallOnSslErrorEventCallback(thisArray, thisLength);
        case Kind_OnSubmitCallback: return deserializeAndCallOnSubmitCallback(thisArray, thisLength);
        case Kind_OnSwiperAnimationEndCallback: return deserializeAndCallOnSwiperAnimationEndCallback(thisArray, thisLength);
        case Kind_OnSwiperAnimationStartCallback: return deserializeAndCallOnSwiperAnimationStartCallback(thisArray, thisLength);
        case Kind_OnSwiperGestureSwipeCallback: return deserializeAndCallOnSwiperGestureSwipeCallback(thisArray, thisLength);
        case Kind_OnTabsAnimationEndCallback: return deserializeAndCallOnTabsAnimationEndCallback(thisArray, thisLength);
        case Kind_OnTabsAnimationStartCallback: return deserializeAndCallOnTabsAnimationStartCallback(thisArray, thisLength);
        case Kind_OnTabsContentWillChangeCallback: return deserializeAndCallOnTabsContentWillChangeCallback(thisArray, thisLength);
        case Kind_OnTabsGestureSwipeCallback: return deserializeAndCallOnTabsGestureSwipeCallback(thisArray, thisLength);
        case Kind_OnTextPickerChangeCallback: return deserializeAndCallOnTextPickerChangeCallback(thisArray, thisLength);
        case Kind_OnTextSelectionChangeCallback: return deserializeAndCallOnTextSelectionChangeCallback(thisArray, thisLength);
        case Kind_OnTimePickerChangeCallback: return deserializeAndCallOnTimePickerChangeCallback(thisArray, thisLength);
        case Kind_OnViewportFitChangedCallback: return deserializeAndCallOnViewportFitChangedCallback(thisArray, thisLength);
        case Kind_OnWillScrollCallback: return deserializeAndCallOnWillScrollCallback(thisArray, thisLength);
        case Kind_PageMapBuilder: return deserializeAndCallPageMapBuilder(thisArray, thisLength);
        case Kind_PageTransitionCallback: return deserializeAndCallPageTransitionCallback(thisArray, thisLength);
        case Kind_PasteEventCallback: return deserializeAndCallPasteEventCallback(thisArray, thisLength);
        case Kind_PluginErrorCallback: return deserializeAndCallPluginErrorCallback(thisArray, thisLength);
        case Kind_PopupStateChangeCallback: return deserializeAndCallPopupStateChangeCallback(thisArray, thisLength);
        case Kind_ProgressModifierBuilder: return deserializeAndCallProgressModifierBuilder(thisArray, thisLength);
        case Kind_RadioModifierBuilder: return deserializeAndCallRadioModifierBuilder(thisArray, thisLength);
        case Kind_RatingModifierBuilder: return deserializeAndCallRatingModifierBuilder(thisArray, thisLength);
        case Kind_RestrictedWorker_onerror_Callback: return deserializeAndCallRestrictedWorker_onerror_Callback(thisArray, thisLength);
        case Kind_RestrictedWorker_onexit_Callback: return deserializeAndCallRestrictedWorker_onexit_Callback(thisArray, thisLength);
        case Kind_RestrictedWorker_onmessage_Callback: return deserializeAndCallRestrictedWorker_onmessage_Callback(thisArray, thisLength);
        case Kind_ReuseIdCallback: return deserializeAndCallReuseIdCallback(thisArray, thisLength);
        case Kind_ScrollOnScrollCallback: return deserializeAndCallScrollOnScrollCallback(thisArray, thisLength);
        case Kind_ScrollOnWillScrollCallback: return deserializeAndCallScrollOnWillScrollCallback(thisArray, thisLength);
        case Kind_SearchSubmitCallback: return deserializeAndCallSearchSubmitCallback(thisArray, thisLength);
        case Kind_SearchValueCallback: return deserializeAndCallSearchValueCallback(thisArray, thisLength);
        case Kind_ShouldBuiltInRecognizerParallelWithCallback: return deserializeAndCallShouldBuiltInRecognizerParallelWithCallback(thisArray, thisLength);
        case Kind_SizeChangeCallback: return deserializeAndCallSizeChangeCallback(thisArray, thisLength);
        case Kind_SliderModifierBuilder: return deserializeAndCallSliderModifierBuilder(thisArray, thisLength);
        case Kind_SliderTriggerChangeCallback: return deserializeAndCallSliderTriggerChangeCallback(thisArray, thisLength);
        case Kind_StyledStringMarshallCallback: return deserializeAndCallStyledStringMarshallCallback(thisArray, thisLength);
        case Kind_StyledStringUnmarshallCallback: return deserializeAndCallStyledStringUnmarshallCallback(thisArray, thisLength);
        case Kind_SubmitCallback: return deserializeAndCallSubmitCallback(thisArray, thisLength);
        case Kind_TabsCustomContentTransitionCallback: return deserializeAndCallTabsCustomContentTransitionCallback(thisArray, thisLength);
        case Kind_TextAreaSubmitCallback: return deserializeAndCallTextAreaSubmitCallback(thisArray, thisLength);
        case Kind_TextClockModifierBuilder: return deserializeAndCallTextClockModifierBuilder(thisArray, thisLength);
        case Kind_TextFieldValueCallback: return deserializeAndCallTextFieldValueCallback(thisArray, thisLength);
        case Kind_TextPickerEnterSelectedAreaCallback: return deserializeAndCallTextPickerEnterSelectedAreaCallback(thisArray, thisLength);
        case Kind_TextPickerScrollStopCallback: return deserializeAndCallTextPickerScrollStopCallback(thisArray, thisLength);
        case Kind_TextTimerModifierBuilder: return deserializeAndCallTextTimerModifierBuilder(thisArray, thisLength);
        case Kind_ToggleModifierBuilder: return deserializeAndCallToggleModifierBuilder(thisArray, thisLength);
        case Kind_TransitionFinishCallback: return deserializeAndCallTransitionFinishCallback(thisArray, thisLength);
        case Kind_Type_CommonMethod_onDragStart: return deserializeAndCallType_CommonMethod_onDragStart(thisArray, thisLength);
        case Kind_Type_NavigationAttribute_customNavContentTransition: return deserializeAndCallType_NavigationAttribute_customNavContentTransition(thisArray, thisLength);
        case Kind_UpdateTransitionCallback: return deserializeAndCallUpdateTransitionCallback(thisArray, thisLength);
        case Kind_VisibleAreaChangeCallback: return deserializeAndCallVisibleAreaChangeCallback(thisArray, thisLength);
        case Kind_VoidCallback: return deserializeAndCallVoidCallback(thisArray, thisLength);
        case Kind_WebKeyboardCallback: return deserializeAndCallWebKeyboardCallback(thisArray, thisLength);
    }
    printf("Unknown callback kind\n");
}
KOALA_EXECUTE(deserializeAndCallCallback, setCallbackCaller(static_cast<Callback_Caller_t>(deserializeAndCallCallback)))
void deserializeAndCallCallbackSync(Ark_VMContext vmContext, Ark_Int32 kind, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    switch (kind) {
        case Kind_AccessibilityCallback: return deserializeAndCallSyncAccessibilityCallback(vmContext, thisArray, thisLength);
        case Kind_AccessibilityFocusCallback: return deserializeAndCallSyncAccessibilityFocusCallback(vmContext, thisArray, thisLength);
        case Kind_AsyncCallback_image_PixelMap_Void: return deserializeAndCallSyncAsyncCallback_image_PixelMap_Void(vmContext, thisArray, thisLength);
        case Kind_ButtonModifierBuilder: return deserializeAndCallSyncButtonModifierBuilder(vmContext, thisArray, thisLength);
        case Kind_ButtonTriggerClickCallback: return deserializeAndCallSyncButtonTriggerClickCallback(vmContext, thisArray, thisLength);
        case Kind_Callback_Area_Area_Void: return deserializeAndCallSyncCallback_Area_Area_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Array_Number_Void: return deserializeAndCallSyncCallback_Array_Number_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Array_String_Void: return deserializeAndCallSyncCallback_Array_String_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Array_TextMenuItem_Void: return deserializeAndCallSyncCallback_Array_TextMenuItem_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Array_TouchTestInfo_TouchResult: return deserializeAndCallSyncCallback_Array_TouchTestInfo_TouchResult(vmContext, thisArray, thisLength);
        case Kind_Callback_AxisEvent_Void: return deserializeAndCallSyncCallback_AxisEvent_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Boolean: return deserializeAndCallSyncCallback_Boolean(vmContext, thisArray, thisLength);
        case Kind_Callback_Boolean_HoverEvent_Void: return deserializeAndCallSyncCallback_Boolean_HoverEvent_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Boolean_Void: return deserializeAndCallSyncCallback_Boolean_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Buffer_Void: return deserializeAndCallSyncCallback_Buffer_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_ClickEvent_LocationButtonOnClickResult_Void: return deserializeAndCallSyncCallback_ClickEvent_LocationButtonOnClickResult_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_ClickEvent_PasteButtonOnClickResult_Void: return deserializeAndCallSyncCallback_ClickEvent_PasteButtonOnClickResult_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_ClickEvent_SaveButtonOnClickResult_Void: return deserializeAndCallSyncCallback_ClickEvent_SaveButtonOnClickResult_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_ClickEvent_Void: return deserializeAndCallSyncCallback_ClickEvent_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_CompatibleComponentInfo_Void: return deserializeAndCallSyncCallback_CompatibleComponentInfo_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_ComputedBarAttribute_Void: return deserializeAndCallSyncCallback_ComputedBarAttribute_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_CopyEvent_Void: return deserializeAndCallSyncCallback_CopyEvent_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_CreateItem: return deserializeAndCallSyncCallback_CreateItem(vmContext, thisArray, thisLength);
        case Kind_Callback_CrownEvent_Void: return deserializeAndCallSyncCallback_CrownEvent_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_CustomSpanMeasureInfo_CustomSpanMetrics: return deserializeAndCallSyncCallback_CustomSpanMeasureInfo_CustomSpanMetrics(vmContext, thisArray, thisLength);
        case Kind_Callback_CustomSpanMetrics_Void: return deserializeAndCallSyncCallback_CustomSpanMetrics_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_CutEvent_Void: return deserializeAndCallSyncCallback_CutEvent_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Date_Void: return deserializeAndCallSyncCallback_Date_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_DeleteValue_Boolean: return deserializeAndCallSyncCallback_DeleteValue_Boolean(vmContext, thisArray, thisLength);
        case Kind_Callback_DeleteValue_Void: return deserializeAndCallSyncCallback_DeleteValue_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_DismissContentCoverAction_Void: return deserializeAndCallSyncCallback_DismissContentCoverAction_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_DismissDialogAction_Void: return deserializeAndCallSyncCallback_DismissDialogAction_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_DismissPopupAction_Void: return deserializeAndCallSyncCallback_DismissPopupAction_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_DismissSheetAction_Void: return deserializeAndCallSyncCallback_DismissSheetAction_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_DragEvent_Opt_String_Void: return deserializeAndCallSyncCallback_DragEvent_Opt_String_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_DrawContext_CustomSpanDrawInfo_Void: return deserializeAndCallSyncCallback_DrawContext_CustomSpanDrawInfo_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_DrawContext_Void: return deserializeAndCallSyncCallback_DrawContext_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_EditableTextChangeValue_Boolean: return deserializeAndCallSyncCallback_EditableTextChangeValue_Boolean(vmContext, thisArray, thisLength);
        case Kind_Callback_EnterKeyType_Void: return deserializeAndCallSyncCallback_EnterKeyType_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_ErrorInformation_Void: return deserializeAndCallSyncCallback_ErrorInformation_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Extender_OnFinish: return deserializeAndCallSyncCallback_Extender_OnFinish(vmContext, thisArray, thisLength);
        case Kind_Callback_Extender_OnProgress: return deserializeAndCallSyncCallback_Extender_OnProgress(vmContext, thisArray, thisLength);
        case Kind_Callback_FocusAxisEvent_Void: return deserializeAndCallSyncCallback_FocusAxisEvent_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_FormCallbackInfo_Void: return deserializeAndCallSyncCallback_FormCallbackInfo_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_FullscreenInfo_Void: return deserializeAndCallSyncCallback_FullscreenInfo_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_GestureEvent_Void: return deserializeAndCallSyncCallback_GestureEvent_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult: return deserializeAndCallSyncCallback_GestureInfo_BaseGestureEvent_GestureJudgeResult(vmContext, thisArray, thisLength);
        case Kind_Callback_GestureJudgeResult_Void: return deserializeAndCallSyncCallback_GestureJudgeResult_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_GestureRecognizer_Void: return deserializeAndCallSyncCallback_GestureRecognizer_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_HitTestMode_Void: return deserializeAndCallSyncCallback_HitTestMode_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_HoverEvent_Void: return deserializeAndCallSyncCallback_HoverEvent_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_InsertValue_Boolean: return deserializeAndCallSyncCallback_InsertValue_Boolean(vmContext, thisArray, thisLength);
        case Kind_Callback_InsertValue_Void: return deserializeAndCallSyncCallback_InsertValue_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_ItemDragInfo_Number_Number_Boolean_Void: return deserializeAndCallSyncCallback_ItemDragInfo_Number_Number_Boolean_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_ItemDragInfo_Number_Number_Void: return deserializeAndCallSyncCallback_ItemDragInfo_Number_Number_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_ItemDragInfo_Number_Void: return deserializeAndCallSyncCallback_ItemDragInfo_Number_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_ItemDragInfo_Void: return deserializeAndCallSyncCallback_ItemDragInfo_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_KeyEvent_Boolean: return deserializeAndCallSyncCallback_KeyEvent_Boolean(vmContext, thisArray, thisLength);
        case Kind_Callback_KeyEvent_Void: return deserializeAndCallSyncCallback_KeyEvent_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Map_String_Object_Void: return deserializeAndCallSyncCallback_Map_String_Object_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_MarqueeState_Void: return deserializeAndCallSyncCallback_MarqueeState_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_MouseEvent_Void: return deserializeAndCallSyncCallback_MouseEvent_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_NativeEmbedDataInfo_Void: return deserializeAndCallSyncCallback_NativeEmbedDataInfo_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_NativeEmbedTouchInfo_Void: return deserializeAndCallSyncCallback_NativeEmbedTouchInfo_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_NavDestinationActiveReason_Void: return deserializeAndCallSyncCallback_NavDestinationActiveReason_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_NavDestinationContext_Void: return deserializeAndCallSyncCallback_NavDestinationContext_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_NavigationMode_Void: return deserializeAndCallSyncCallback_NavigationMode_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_NavigationTitleMode_Void: return deserializeAndCallSyncCallback_NavigationTitleMode_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_NavigationTransitionProxy_Void: return deserializeAndCallSyncCallback_NavigationTransitionProxy_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Number_Number_Boolean: return deserializeAndCallSyncCallback_Number_Number_Boolean(vmContext, thisArray, thisLength);
        case Kind_Callback_Number_Number_Boolean_Boolean: return deserializeAndCallSyncCallback_Number_Number_Boolean_Boolean(vmContext, thisArray, thisLength);
        case Kind_Callback_Number_Number_ComputedBarAttribute: return deserializeAndCallSyncCallback_Number_Number_ComputedBarAttribute(vmContext, thisArray, thisLength);
        case Kind_Callback_Number_Number_Number_Void: return deserializeAndCallSyncCallback_Number_Number_Number_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Number_Number_Void: return deserializeAndCallSyncCallback_Number_Number_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Number_SliderChangeMode_Void: return deserializeAndCallSyncCallback_Number_SliderChangeMode_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Number_Tuple_Number_Number: return deserializeAndCallSyncCallback_Number_Tuple_Number_Number(vmContext, thisArray, thisLength);
        case Kind_Callback_Number_Tuple_Number_Number_Number_Number: return deserializeAndCallSyncCallback_Number_Tuple_Number_Number_Number_Number(vmContext, thisArray, thisLength);
        case Kind_Callback_Number_Void: return deserializeAndCallSyncCallback_Number_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Object_Void: return deserializeAndCallSyncCallback_Object_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_OnAlertEvent_Boolean: return deserializeAndCallSyncCallback_OnAlertEvent_Boolean(vmContext, thisArray, thisLength);
        case Kind_Callback_OnAudioStateChangedEvent_Void: return deserializeAndCallSyncCallback_OnAudioStateChangedEvent_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_OnBeforeUnloadEvent_Boolean: return deserializeAndCallSyncCallback_OnBeforeUnloadEvent_Boolean(vmContext, thisArray, thisLength);
        case Kind_Callback_OnClientAuthenticationEvent_Void: return deserializeAndCallSyncCallback_OnClientAuthenticationEvent_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_OnConfirmEvent_Boolean: return deserializeAndCallSyncCallback_OnConfirmEvent_Boolean(vmContext, thisArray, thisLength);
        case Kind_Callback_OnConsoleEvent_Boolean: return deserializeAndCallSyncCallback_OnConsoleEvent_Boolean(vmContext, thisArray, thisLength);
        case Kind_Callback_OnContextMenuShowEvent_Boolean: return deserializeAndCallSyncCallback_OnContextMenuShowEvent_Boolean(vmContext, thisArray, thisLength);
        case Kind_Callback_OnDataResubmittedEvent_Void: return deserializeAndCallSyncCallback_OnDataResubmittedEvent_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_OnDownloadStartEvent_Void: return deserializeAndCallSyncCallback_OnDownloadStartEvent_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_OnErrorReceiveEvent_Void: return deserializeAndCallSyncCallback_OnErrorReceiveEvent_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_OnFaviconReceivedEvent_Void: return deserializeAndCallSyncCallback_OnFaviconReceivedEvent_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_OnFirstContentfulPaintEvent_Void: return deserializeAndCallSyncCallback_OnFirstContentfulPaintEvent_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_OnGeolocationShowEvent_Void: return deserializeAndCallSyncCallback_OnGeolocationShowEvent_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_OnHttpAuthRequestEvent_Boolean: return deserializeAndCallSyncCallback_OnHttpAuthRequestEvent_Boolean(vmContext, thisArray, thisLength);
        case Kind_Callback_OnHttpErrorReceiveEvent_Void: return deserializeAndCallSyncCallback_OnHttpErrorReceiveEvent_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_OnInterceptRequestEvent_WebResourceResponse: return deserializeAndCallSyncCallback_OnInterceptRequestEvent_WebResourceResponse(vmContext, thisArray, thisLength);
        case Kind_Callback_OnLoadInterceptEvent_Boolean: return deserializeAndCallSyncCallback_OnLoadInterceptEvent_Boolean(vmContext, thisArray, thisLength);
        case Kind_Callback_onMeasureSize_SizeResult: return deserializeAndCallSyncCallback_onMeasureSize_SizeResult(vmContext, thisArray, thisLength);
        case Kind_Callback_OnOverScrollEvent_Void: return deserializeAndCallSyncCallback_OnOverScrollEvent_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_OnPageBeginEvent_Void: return deserializeAndCallSyncCallback_OnPageBeginEvent_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_OnPageEndEvent_Void: return deserializeAndCallSyncCallback_OnPageEndEvent_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_OnPageVisibleEvent_Void: return deserializeAndCallSyncCallback_OnPageVisibleEvent_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_OnPermissionRequestEvent_Void: return deserializeAndCallSyncCallback_OnPermissionRequestEvent_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_onPlaceChildren_Void: return deserializeAndCallSyncCallback_onPlaceChildren_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_OnProgressChangeEvent_Void: return deserializeAndCallSyncCallback_OnProgressChangeEvent_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_OnPromptEvent_Boolean: return deserializeAndCallSyncCallback_OnPromptEvent_Boolean(vmContext, thisArray, thisLength);
        case Kind_Callback_OnRefreshAccessedHistoryEvent_Void: return deserializeAndCallSyncCallback_OnRefreshAccessedHistoryEvent_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_OnRenderExitedEvent_Void: return deserializeAndCallSyncCallback_OnRenderExitedEvent_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_OnResourceLoadEvent_Void: return deserializeAndCallSyncCallback_OnResourceLoadEvent_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_OnScaleChangeEvent_Void: return deserializeAndCallSyncCallback_OnScaleChangeEvent_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_OnScreenCaptureRequestEvent_Void: return deserializeAndCallSyncCallback_OnScreenCaptureRequestEvent_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_OnScrollEvent_Void: return deserializeAndCallSyncCallback_OnScrollEvent_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_OnScrollFrameBeginHandlerResult_Void: return deserializeAndCallSyncCallback_OnScrollFrameBeginHandlerResult_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_OnSearchResultReceiveEvent_Void: return deserializeAndCallSyncCallback_OnSearchResultReceiveEvent_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_OnShowFileSelectorEvent_Boolean: return deserializeAndCallSyncCallback_OnShowFileSelectorEvent_Boolean(vmContext, thisArray, thisLength);
        case Kind_Callback_OnSslErrorEventReceiveEvent_Void: return deserializeAndCallSyncCallback_OnSslErrorEventReceiveEvent_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_OnTitleReceiveEvent_Void: return deserializeAndCallSyncCallback_OnTitleReceiveEvent_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_OnTouchIconUrlReceivedEvent_Void: return deserializeAndCallSyncCallback_OnTouchIconUrlReceivedEvent_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_OnWindowNewEvent_Void: return deserializeAndCallSyncCallback_OnWindowNewEvent_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Opt_Array_FontDescriptor_Opt_Array_String_Void: return deserializeAndCallSyncCallback_Opt_Array_FontDescriptor_Opt_Array_String_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Opt_Array_NavDestinationTransition_Void: return deserializeAndCallSyncCallback_Opt_Array_NavDestinationTransition_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Opt_Array_String_Opt_Array_String_Void: return deserializeAndCallSyncCallback_Opt_Array_String_Opt_Array_String_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Opt_Array_String_Void: return deserializeAndCallSyncCallback_Opt_Array_String_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Opt_Boolean_Void: return deserializeAndCallSyncCallback_Opt_Boolean_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Opt_CustomBuilder_Void: return deserializeAndCallSyncCallback_Opt_CustomBuilder_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Opt_FontDescriptor_Opt_Array_String_Void: return deserializeAndCallSyncCallback_Opt_FontDescriptor_Opt_Array_String_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Opt_NavigationAnimatedTransition_Void: return deserializeAndCallSyncCallback_Opt_NavigationAnimatedTransition_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Opt_Number_Void: return deserializeAndCallSyncCallback_Opt_Number_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Opt_Object_Void: return deserializeAndCallSyncCallback_Opt_Object_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Opt_OffsetResult_Void: return deserializeAndCallSyncCallback_Opt_OffsetResult_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Opt_Scene_Opt_Array_String_Void: return deserializeAndCallSyncCallback_Opt_Scene_Opt_Array_String_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Opt_ScrollResult_Void: return deserializeAndCallSyncCallback_Opt_ScrollResult_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Opt_String_Opt_Array_String_Void: return deserializeAndCallSyncCallback_Opt_String_Opt_Array_String_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Opt_StyledString_Opt_Array_String_Void: return deserializeAndCallSyncCallback_Opt_StyledString_Opt_Array_String_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Opt_TabContentAnimatedTransition_Void: return deserializeAndCallSyncCallback_Opt_TabContentAnimatedTransition_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Opt_Union_Number_Resource_Void: return deserializeAndCallSyncCallback_Opt_Union_Number_Resource_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Opt_Union_ResourceStr_String_Resource_Void: return deserializeAndCallSyncCallback_Opt_Union_ResourceStr_String_Resource_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_PlaybackInfo_Void: return deserializeAndCallSyncCallback_PlaybackInfo_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Pointer_Void: return deserializeAndCallSyncCallback_Pointer_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_PopInfo_Void: return deserializeAndCallSyncCallback_PopInfo_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_PreDragStatus_Void: return deserializeAndCallSyncCallback_PreDragStatus_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_PreparedInfo_Void: return deserializeAndCallSyncCallback_PreparedInfo_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_RangeUpdate: return deserializeAndCallSyncCallback_RangeUpdate(vmContext, thisArray, thisLength);
        case Kind_Callback_RefreshStatus_Void: return deserializeAndCallSyncCallback_RefreshStatus_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_RichEditorChangeValue_Boolean: return deserializeAndCallSyncCallback_RichEditorChangeValue_Boolean(vmContext, thisArray, thisLength);
        case Kind_Callback_RichEditorDeleteValue_Boolean: return deserializeAndCallSyncCallback_RichEditorDeleteValue_Boolean(vmContext, thisArray, thisLength);
        case Kind_Callback_RichEditorInsertValue_Boolean: return deserializeAndCallSyncCallback_RichEditorInsertValue_Boolean(vmContext, thisArray, thisLength);
        case Kind_Callback_RichEditorRange_Void: return deserializeAndCallSyncCallback_RichEditorRange_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_RichEditorSelection_Void: return deserializeAndCallSyncCallback_RichEditorSelection_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_RichEditorTextSpanResult_Void: return deserializeAndCallSyncCallback_RichEditorTextSpanResult_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_RotationGesture: return deserializeAndCallSyncCallback_RotationGesture(vmContext, thisArray, thisLength);
        case Kind_Callback_RotationGesture_Void: return deserializeAndCallSyncCallback_RotationGesture_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_SheetDismiss_Void: return deserializeAndCallSyncCallback_SheetDismiss_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_SheetType_Void: return deserializeAndCallSyncCallback_SheetType_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_SizeResult_Void: return deserializeAndCallSyncCallback_SizeResult_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_SpringBackAction_Void: return deserializeAndCallSyncCallback_SpringBackAction_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_StateStylesChange: return deserializeAndCallSyncCallback_StateStylesChange(vmContext, thisArray, thisLength);
        case Kind_Callback_String_PasteEvent_Void: return deserializeAndCallSyncCallback_String_PasteEvent_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_String_SurfaceRect_Void: return deserializeAndCallSyncCallback_String_SurfaceRect_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_String_Void: return deserializeAndCallSyncCallback_String_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_StyledStringChangeValue_Boolean: return deserializeAndCallSyncCallback_StyledStringChangeValue_Boolean(vmContext, thisArray, thisLength);
        case Kind_Callback_StyledStringMarshallingValue_Void: return deserializeAndCallSyncCallback_StyledStringMarshallingValue_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_SwipeActionState_Void: return deserializeAndCallSyncCallback_SwipeActionState_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_SwipeGesture: return deserializeAndCallSyncCallback_SwipeGesture(vmContext, thisArray, thisLength);
        case Kind_Callback_SwipeGesture_Void: return deserializeAndCallSyncCallback_SwipeGesture_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_SwiperContentTransitionProxy_Void: return deserializeAndCallSyncCallback_SwiperContentTransitionProxy_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_TabContentTransitionProxy_Void: return deserializeAndCallSyncCallback_TabContentTransitionProxy_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_TerminationInfo_Void: return deserializeAndCallSyncCallback_TerminationInfo_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_TextPickerResult_Void: return deserializeAndCallSyncCallback_TextPickerResult_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_TextRange_Void: return deserializeAndCallSyncCallback_TextRange_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_TimePickerResult_Void: return deserializeAndCallSyncCallback_TimePickerResult_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_TouchEvent_HitTestMode: return deserializeAndCallSyncCallback_TouchEvent_HitTestMode(vmContext, thisArray, thisLength);
        case Kind_Callback_TouchEvent_Void: return deserializeAndCallSyncCallback_TouchEvent_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_TouchResult_Void: return deserializeAndCallSyncCallback_TouchResult_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Tuple_Number_Number_Number_Number_Void: return deserializeAndCallSyncCallback_Tuple_Number_Number_Number_Number_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Tuple_Number_Number_Void: return deserializeAndCallSyncCallback_Tuple_Number_Number_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_UIExtensionProxy_Void: return deserializeAndCallSyncCallback_UIExtensionProxy_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Union_CustomBuilder_DragItemInfo_Void: return deserializeAndCallSyncCallback_Union_CustomBuilder_DragItemInfo_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Union_Number_Array_Number_Void: return deserializeAndCallSyncCallback_Union_Number_Array_Number_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Union_ResourceStr_Array_ResourceStr_Void: return deserializeAndCallSyncCallback_Union_ResourceStr_Array_ResourceStr_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Union_ResourceStr_Resource_String_Void: return deserializeAndCallSyncCallback_Union_ResourceStr_Resource_String_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Void: return deserializeAndCallSyncCallback_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_WebKeyboardOptions_Void: return deserializeAndCallSyncCallback_WebKeyboardOptions_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_WebResourceResponse_Void: return deserializeAndCallSyncCallback_WebResourceResponse_Void(vmContext, thisArray, thisLength);
        case Kind_CheckBoxModifierBuilder: return deserializeAndCallSyncCheckBoxModifierBuilder(vmContext, thisArray, thisLength);
        case Kind_CompatibleInitCallback: return deserializeAndCallSyncCompatibleInitCallback(vmContext, thisArray, thisLength);
        case Kind_CompatibleUpdateCallback: return deserializeAndCallSyncCompatibleUpdateCallback(vmContext, thisArray, thisLength);
        case Kind_ContentDidScrollCallback: return deserializeAndCallSyncContentDidScrollCallback(vmContext, thisArray, thisLength);
        case Kind_ContentWillScrollCallback: return deserializeAndCallSyncContentWillScrollCallback(vmContext, thisArray, thisLength);
        case Kind_Context_getGroupDir_Callback: return deserializeAndCallSyncContext_getGroupDir_Callback(vmContext, thisArray, thisLength);
        case Kind_CustomNodeBuilder: return deserializeAndCallSyncCustomNodeBuilder(vmContext, thisArray, thisLength);
        case Kind_CustomStyles: return deserializeAndCallSyncCustomStyles(vmContext, thisArray, thisLength);
        case Kind_DataPanelModifierBuilder: return deserializeAndCallSyncDataPanelModifierBuilder(vmContext, thisArray, thisLength);
        case Kind_EditableTextOnChangeCallback: return deserializeAndCallSyncEditableTextOnChangeCallback(vmContext, thisArray, thisLength);
        case Kind_ErrorCallback: return deserializeAndCallSyncErrorCallback(vmContext, thisArray, thisLength);
        case Kind_GaugeModifierBuilder: return deserializeAndCallSyncGaugeModifierBuilder(vmContext, thisArray, thisLength);
        case Kind_GestureRecognizerJudgeBeginCallback: return deserializeAndCallSyncGestureRecognizerJudgeBeginCallback(vmContext, thisArray, thisLength);
        case Kind_GetItemMainSizeByIndex: return deserializeAndCallSyncGetItemMainSizeByIndex(vmContext, thisArray, thisLength);
        case Kind_HoverCallback: return deserializeAndCallSyncHoverCallback(vmContext, thisArray, thisLength);
        case Kind_ImageCompleteCallback: return deserializeAndCallSyncImageCompleteCallback(vmContext, thisArray, thisLength);
        case Kind_ImageErrorCallback: return deserializeAndCallSyncImageErrorCallback(vmContext, thisArray, thisLength);
        case Kind_ImageOnCompleteCallback: return deserializeAndCallSyncImageOnCompleteCallback(vmContext, thisArray, thisLength);
        case Kind_InterceptionModeCallback: return deserializeAndCallSyncInterceptionModeCallback(vmContext, thisArray, thisLength);
        case Kind_InterceptionShowCallback: return deserializeAndCallSyncInterceptionShowCallback(vmContext, thisArray, thisLength);
        case Kind_LoadingProgressModifierBuilder: return deserializeAndCallSyncLoadingProgressModifierBuilder(vmContext, thisArray, thisLength);
        case Kind_MenuCallback: return deserializeAndCallSyncMenuCallback(vmContext, thisArray, thisLength);
        case Kind_MenuItemModifierBuilder: return deserializeAndCallSyncMenuItemModifierBuilder(vmContext, thisArray, thisLength);
        case Kind_MenuOnAppearCallback: return deserializeAndCallSyncMenuOnAppearCallback(vmContext, thisArray, thisLength);
        case Kind_ModifierKeyStateGetter: return deserializeAndCallSyncModifierKeyStateGetter(vmContext, thisArray, thisLength);
        case Kind_NavDestinationTransitionDelegate: return deserializeAndCallSyncNavDestinationTransitionDelegate(vmContext, thisArray, thisLength);
        case Kind_NavExtender_OnUpdateStack: return deserializeAndCallSyncNavExtender_OnUpdateStack(vmContext, thisArray, thisLength);
        case Kind_OnAdsBlockedCallback: return deserializeAndCallSyncOnAdsBlockedCallback(vmContext, thisArray, thisLength);
        case Kind_OnAlphabetIndexerPopupSelectCallback: return deserializeAndCallSyncOnAlphabetIndexerPopupSelectCallback(vmContext, thisArray, thisLength);
        case Kind_OnAlphabetIndexerRequestPopupDataCallback: return deserializeAndCallSyncOnAlphabetIndexerRequestPopupDataCallback(vmContext, thisArray, thisLength);
        case Kind_OnAlphabetIndexerSelectCallback: return deserializeAndCallSyncOnAlphabetIndexerSelectCallback(vmContext, thisArray, thisLength);
        case Kind_OnCheckboxChangeCallback: return deserializeAndCallSyncOnCheckboxChangeCallback(vmContext, thisArray, thisLength);
        case Kind_OnCheckboxGroupChangeCallback: return deserializeAndCallSyncOnCheckboxGroupChangeCallback(vmContext, thisArray, thisLength);
        case Kind_OnContentScrollCallback: return deserializeAndCallSyncOnContentScrollCallback(vmContext, thisArray, thisLength);
        case Kind_OnContextMenuHideCallback: return deserializeAndCallSyncOnContextMenuHideCallback(vmContext, thisArray, thisLength);
        case Kind_OnCreateMenuCallback: return deserializeAndCallSyncOnCreateMenuCallback(vmContext, thisArray, thisLength);
        case Kind_OnDidChangeCallback: return deserializeAndCallSyncOnDidChangeCallback(vmContext, thisArray, thisLength);
        case Kind_OnDragEventCallback: return deserializeAndCallSyncOnDragEventCallback(vmContext, thisArray, thisLength);
        case Kind_OnFirstMeaningfulPaintCallback: return deserializeAndCallSyncOnFirstMeaningfulPaintCallback(vmContext, thisArray, thisLength);
        case Kind_OnFoldStatusChangeCallback: return deserializeAndCallSyncOnFoldStatusChangeCallback(vmContext, thisArray, thisLength);
        case Kind_OnFullScreenEnterCallback: return deserializeAndCallSyncOnFullScreenEnterCallback(vmContext, thisArray, thisLength);
        case Kind_OnHoverCallback: return deserializeAndCallSyncOnHoverCallback(vmContext, thisArray, thisLength);
        case Kind_OnHoverStatusChangeCallback: return deserializeAndCallSyncOnHoverStatusChangeCallback(vmContext, thisArray, thisLength);
        case Kind_OnIntelligentTrackingPreventionCallback: return deserializeAndCallSyncOnIntelligentTrackingPreventionCallback(vmContext, thisArray, thisLength);
        case Kind_OnItemDragStartCallback: return deserializeAndCallSyncOnItemDragStartCallback(vmContext, thisArray, thisLength);
        case Kind_OnLargestContentfulPaintCallback: return deserializeAndCallSyncOnLargestContentfulPaintCallback(vmContext, thisArray, thisLength);
        case Kind_OnLinearIndicatorChangeCallback: return deserializeAndCallSyncOnLinearIndicatorChangeCallback(vmContext, thisArray, thisLength);
        case Kind_OnMenuItemClickCallback: return deserializeAndCallSyncOnMenuItemClickCallback(vmContext, thisArray, thisLength);
        case Kind_OnMoveHandler: return deserializeAndCallSyncOnMoveHandler(vmContext, thisArray, thisLength);
        case Kind_OnNativeEmbedVisibilityChangeCallback: return deserializeAndCallSyncOnNativeEmbedVisibilityChangeCallback(vmContext, thisArray, thisLength);
        case Kind_OnNativeLoadCallback: return deserializeAndCallSyncOnNativeLoadCallback(vmContext, thisArray, thisLength);
        case Kind_OnNavigationEntryCommittedCallback: return deserializeAndCallSyncOnNavigationEntryCommittedCallback(vmContext, thisArray, thisLength);
        case Kind_OnOverrideUrlLoadingCallback: return deserializeAndCallSyncOnOverrideUrlLoadingCallback(vmContext, thisArray, thisLength);
        case Kind_OnPasteCallback: return deserializeAndCallSyncOnPasteCallback(vmContext, thisArray, thisLength);
        case Kind_OnRadioChangeCallback: return deserializeAndCallSyncOnRadioChangeCallback(vmContext, thisArray, thisLength);
        case Kind_OnRatingChangeCallback: return deserializeAndCallSyncOnRatingChangeCallback(vmContext, thisArray, thisLength);
        case Kind_OnRenderProcessNotRespondingCallback: return deserializeAndCallSyncOnRenderProcessNotRespondingCallback(vmContext, thisArray, thisLength);
        case Kind_OnRenderProcessRespondingCallback: return deserializeAndCallSyncOnRenderProcessRespondingCallback(vmContext, thisArray, thisLength);
        case Kind_OnSafeBrowsingCheckResultCallback: return deserializeAndCallSyncOnSafeBrowsingCheckResultCallback(vmContext, thisArray, thisLength);
        case Kind_OnScrollCallback: return deserializeAndCallSyncOnScrollCallback(vmContext, thisArray, thisLength);
        case Kind_OnScrollEdgeCallback: return deserializeAndCallSyncOnScrollEdgeCallback(vmContext, thisArray, thisLength);
        case Kind_OnScrollFrameBeginCallback: return deserializeAndCallSyncOnScrollFrameBeginCallback(vmContext, thisArray, thisLength);
        case Kind_OnScrollVisibleContentChangeCallback: return deserializeAndCallSyncOnScrollVisibleContentChangeCallback(vmContext, thisArray, thisLength);
        case Kind_OnSelectCallback: return deserializeAndCallSyncOnSelectCallback(vmContext, thisArray, thisLength);
        case Kind_OnSslErrorEventCallback: return deserializeAndCallSyncOnSslErrorEventCallback(vmContext, thisArray, thisLength);
        case Kind_OnSubmitCallback: return deserializeAndCallSyncOnSubmitCallback(vmContext, thisArray, thisLength);
        case Kind_OnSwiperAnimationEndCallback: return deserializeAndCallSyncOnSwiperAnimationEndCallback(vmContext, thisArray, thisLength);
        case Kind_OnSwiperAnimationStartCallback: return deserializeAndCallSyncOnSwiperAnimationStartCallback(vmContext, thisArray, thisLength);
        case Kind_OnSwiperGestureSwipeCallback: return deserializeAndCallSyncOnSwiperGestureSwipeCallback(vmContext, thisArray, thisLength);
        case Kind_OnTabsAnimationEndCallback: return deserializeAndCallSyncOnTabsAnimationEndCallback(vmContext, thisArray, thisLength);
        case Kind_OnTabsAnimationStartCallback: return deserializeAndCallSyncOnTabsAnimationStartCallback(vmContext, thisArray, thisLength);
        case Kind_OnTabsContentWillChangeCallback: return deserializeAndCallSyncOnTabsContentWillChangeCallback(vmContext, thisArray, thisLength);
        case Kind_OnTabsGestureSwipeCallback: return deserializeAndCallSyncOnTabsGestureSwipeCallback(vmContext, thisArray, thisLength);
        case Kind_OnTextPickerChangeCallback: return deserializeAndCallSyncOnTextPickerChangeCallback(vmContext, thisArray, thisLength);
        case Kind_OnTextSelectionChangeCallback: return deserializeAndCallSyncOnTextSelectionChangeCallback(vmContext, thisArray, thisLength);
        case Kind_OnTimePickerChangeCallback: return deserializeAndCallSyncOnTimePickerChangeCallback(vmContext, thisArray, thisLength);
        case Kind_OnViewportFitChangedCallback: return deserializeAndCallSyncOnViewportFitChangedCallback(vmContext, thisArray, thisLength);
        case Kind_OnWillScrollCallback: return deserializeAndCallSyncOnWillScrollCallback(vmContext, thisArray, thisLength);
        case Kind_PageMapBuilder: return deserializeAndCallSyncPageMapBuilder(vmContext, thisArray, thisLength);
        case Kind_PageTransitionCallback: return deserializeAndCallSyncPageTransitionCallback(vmContext, thisArray, thisLength);
        case Kind_PasteEventCallback: return deserializeAndCallSyncPasteEventCallback(vmContext, thisArray, thisLength);
        case Kind_PluginErrorCallback: return deserializeAndCallSyncPluginErrorCallback(vmContext, thisArray, thisLength);
        case Kind_PopupStateChangeCallback: return deserializeAndCallSyncPopupStateChangeCallback(vmContext, thisArray, thisLength);
        case Kind_ProgressModifierBuilder: return deserializeAndCallSyncProgressModifierBuilder(vmContext, thisArray, thisLength);
        case Kind_RadioModifierBuilder: return deserializeAndCallSyncRadioModifierBuilder(vmContext, thisArray, thisLength);
        case Kind_RatingModifierBuilder: return deserializeAndCallSyncRatingModifierBuilder(vmContext, thisArray, thisLength);
        case Kind_RestrictedWorker_onerror_Callback: return deserializeAndCallSyncRestrictedWorker_onerror_Callback(vmContext, thisArray, thisLength);
        case Kind_RestrictedWorker_onexit_Callback: return deserializeAndCallSyncRestrictedWorker_onexit_Callback(vmContext, thisArray, thisLength);
        case Kind_RestrictedWorker_onmessage_Callback: return deserializeAndCallSyncRestrictedWorker_onmessage_Callback(vmContext, thisArray, thisLength);
        case Kind_ReuseIdCallback: return deserializeAndCallSyncReuseIdCallback(vmContext, thisArray, thisLength);
        case Kind_ScrollOnScrollCallback: return deserializeAndCallSyncScrollOnScrollCallback(vmContext, thisArray, thisLength);
        case Kind_ScrollOnWillScrollCallback: return deserializeAndCallSyncScrollOnWillScrollCallback(vmContext, thisArray, thisLength);
        case Kind_SearchSubmitCallback: return deserializeAndCallSyncSearchSubmitCallback(vmContext, thisArray, thisLength);
        case Kind_SearchValueCallback: return deserializeAndCallSyncSearchValueCallback(vmContext, thisArray, thisLength);
        case Kind_ShouldBuiltInRecognizerParallelWithCallback: return deserializeAndCallSyncShouldBuiltInRecognizerParallelWithCallback(vmContext, thisArray, thisLength);
        case Kind_SizeChangeCallback: return deserializeAndCallSyncSizeChangeCallback(vmContext, thisArray, thisLength);
        case Kind_SliderModifierBuilder: return deserializeAndCallSyncSliderModifierBuilder(vmContext, thisArray, thisLength);
        case Kind_SliderTriggerChangeCallback: return deserializeAndCallSyncSliderTriggerChangeCallback(vmContext, thisArray, thisLength);
        case Kind_StyledStringMarshallCallback: return deserializeAndCallSyncStyledStringMarshallCallback(vmContext, thisArray, thisLength);
        case Kind_StyledStringUnmarshallCallback: return deserializeAndCallSyncStyledStringUnmarshallCallback(vmContext, thisArray, thisLength);
        case Kind_SubmitCallback: return deserializeAndCallSyncSubmitCallback(vmContext, thisArray, thisLength);
        case Kind_TabsCustomContentTransitionCallback: return deserializeAndCallSyncTabsCustomContentTransitionCallback(vmContext, thisArray, thisLength);
        case Kind_TextAreaSubmitCallback: return deserializeAndCallSyncTextAreaSubmitCallback(vmContext, thisArray, thisLength);
        case Kind_TextClockModifierBuilder: return deserializeAndCallSyncTextClockModifierBuilder(vmContext, thisArray, thisLength);
        case Kind_TextFieldValueCallback: return deserializeAndCallSyncTextFieldValueCallback(vmContext, thisArray, thisLength);
        case Kind_TextPickerEnterSelectedAreaCallback: return deserializeAndCallSyncTextPickerEnterSelectedAreaCallback(vmContext, thisArray, thisLength);
        case Kind_TextPickerScrollStopCallback: return deserializeAndCallSyncTextPickerScrollStopCallback(vmContext, thisArray, thisLength);
        case Kind_TextTimerModifierBuilder: return deserializeAndCallSyncTextTimerModifierBuilder(vmContext, thisArray, thisLength);
        case Kind_ToggleModifierBuilder: return deserializeAndCallSyncToggleModifierBuilder(vmContext, thisArray, thisLength);
        case Kind_TransitionFinishCallback: return deserializeAndCallSyncTransitionFinishCallback(vmContext, thisArray, thisLength);
        case Kind_Type_CommonMethod_onDragStart: return deserializeAndCallSyncType_CommonMethod_onDragStart(vmContext, thisArray, thisLength);
        case Kind_Type_NavigationAttribute_customNavContentTransition: return deserializeAndCallSyncType_NavigationAttribute_customNavContentTransition(vmContext, thisArray, thisLength);
        case Kind_UpdateTransitionCallback: return deserializeAndCallSyncUpdateTransitionCallback(vmContext, thisArray, thisLength);
        case Kind_VisibleAreaChangeCallback: return deserializeAndCallSyncVisibleAreaChangeCallback(vmContext, thisArray, thisLength);
        case Kind_VoidCallback: return deserializeAndCallSyncVoidCallback(vmContext, thisArray, thisLength);
        case Kind_WebKeyboardCallback: return deserializeAndCallSyncWebKeyboardCallback(vmContext, thisArray, thisLength);
    }
    printf("Unknown callback kind\n");
}
KOALA_EXECUTE(deserializeAndCallCallbackSync, setCallbackCallerSync(static_cast<Callback_Caller_Sync_t>(deserializeAndCallCallbackSync)))