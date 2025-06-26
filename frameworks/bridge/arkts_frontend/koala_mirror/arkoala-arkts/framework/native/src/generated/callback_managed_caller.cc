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
#include "common-interop.h"
#include "callbacks.h"
#include "arkoala_api_generated.h"

void callManagedAccessibilityCallback(Ark_Int32 resourceId, Ark_Boolean isHover, Ark_AccessibilityHoverEvent event)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_AccessibilityCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(isHover);
    AccessibilityHoverEvent_serializer::write(argsSerializer, event);
    enqueueCallback(&_buffer);
}
void callManagedAccessibilityCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Boolean isHover, Ark_AccessibilityHoverEvent event)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_AccessibilityCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(isHover);
    AccessibilityHoverEvent_serializer::write(argsSerializer, event);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedAccessibilityFocusCallback(Ark_Int32 resourceId, Ark_Boolean isFocus)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_AccessibilityFocusCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(isFocus);
    enqueueCallback(&_buffer);
}
void callManagedAccessibilityFocusCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Boolean isFocus)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_AccessibilityFocusCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(isFocus);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedAsyncCallback_image_PixelMap_Void(Ark_Int32 resourceId, Ark_image_PixelMap result)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_AsyncCallback_image_PixelMap_Void);
    argsSerializer.writeInt32(resourceId);
    image_PixelMap_serializer::write(argsSerializer, result);
    enqueueCallback(&_buffer);
}
void callManagedAsyncCallback_image_PixelMap_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_image_PixelMap result)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_AsyncCallback_image_PixelMap_Void);
    argsSerializer.writeInt32(resourceId);
    image_PixelMap_serializer::write(argsSerializer, result);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedButtonModifierBuilder(Ark_Int32 resourceId, Ark_NativePointer parentNode, Ark_ButtonConfiguration config, Callback_Pointer_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_ButtonModifierBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    ButtonConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedButtonModifierBuilderSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NativePointer parentNode, Ark_ButtonConfiguration config, Callback_Pointer_Void continuation)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_ButtonModifierBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    ButtonConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedButtonTriggerClickCallback(Ark_Int32 resourceId, Ark_Number xPos, Ark_Number yPos)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_ButtonTriggerClickCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(xPos);
    argsSerializer.writeNumber(yPos);
    enqueueCallback(&_buffer);
}
void callManagedButtonTriggerClickCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number xPos, Ark_Number yPos)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_ButtonTriggerClickCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(xPos);
    argsSerializer.writeNumber(yPos);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Area_Area_Void(Ark_Int32 resourceId, Ark_Area oldValue, Ark_Area newValue)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Area_Area_Void);
    argsSerializer.writeInt32(resourceId);
    Area_serializer::write(argsSerializer, oldValue);
    Area_serializer::write(argsSerializer, newValue);
    enqueueCallback(&_buffer);
}
void callManagedCallback_Area_Area_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Area oldValue, Ark_Area newValue)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Area_Area_Void);
    argsSerializer.writeInt32(resourceId);
    Area_serializer::write(argsSerializer, oldValue);
    Area_serializer::write(argsSerializer, newValue);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Array_Number_Void(Ark_Int32 resourceId, Array_Number input)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Array_Number_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(input.length);
    for (int i = 0; i < input.length; i++) {
        const Ark_Number input_element = input.array[i];
        argsSerializer.writeNumber(input_element);
    }
    enqueueCallback(&_buffer);
}
void callManagedCallback_Array_Number_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Array_Number input)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Array_Number_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(input.length);
    for (int i = 0; i < input.length; i++) {
        const Ark_Number input_element = input.array[i];
        argsSerializer.writeNumber(input_element);
    }
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Array_String_Void(Ark_Int32 resourceId, Array_String value)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Array_String_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(value.length);
    for (int i = 0; i < value.length; i++) {
        const Ark_String value_element = value.array[i];
        argsSerializer.writeString(value_element);
    }
    enqueueCallback(&_buffer);
}
void callManagedCallback_Array_String_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Array_String value)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Array_String_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(value.length);
    for (int i = 0; i < value.length; i++) {
        const Ark_String value_element = value.array[i];
        argsSerializer.writeString(value_element);
    }
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Array_TextMenuItem_Void(Ark_Int32 resourceId, Array_TextMenuItem value)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Array_TextMenuItem_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(value.length);
    for (int i = 0; i < value.length; i++) {
        const Ark_TextMenuItem value_element = value.array[i];
        TextMenuItem_serializer::write(argsSerializer, value_element);
    }
    enqueueCallback(&_buffer);
}
void callManagedCallback_Array_TextMenuItem_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Array_TextMenuItem value)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Array_TextMenuItem_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(value.length);
    for (int i = 0; i < value.length; i++) {
        const Ark_TextMenuItem value_element = value.array[i];
        TextMenuItem_serializer::write(argsSerializer, value_element);
    }
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Array_TouchTestInfo_TouchResult(Ark_Int32 resourceId, Array_TouchTestInfo value, Callback_TouchResult_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Array_TouchTestInfo_TouchResult);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(value.length);
    for (int i = 0; i < value.length; i++) {
        const Ark_TouchTestInfo value_element = value.array[i];
        TouchTestInfo_serializer::write(argsSerializer, value_element);
    }
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedCallback_Array_TouchTestInfo_TouchResultSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Array_TouchTestInfo value, Callback_TouchResult_Void continuation)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Array_TouchTestInfo_TouchResult);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(value.length);
    for (int i = 0; i < value.length; i++) {
        const Ark_TouchTestInfo value_element = value.array[i];
        TouchTestInfo_serializer::write(argsSerializer, value_element);
    }
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_AxisEvent_Void(Ark_Int32 resourceId, Ark_AxisEvent value0)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_AxisEvent_Void);
    argsSerializer.writeInt32(resourceId);
    AxisEvent_serializer::write(argsSerializer, value0);
    enqueueCallback(&_buffer);
}
void callManagedCallback_AxisEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_AxisEvent value0)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_AxisEvent_Void);
    argsSerializer.writeInt32(resourceId);
    AxisEvent_serializer::write(argsSerializer, value0);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Boolean(Ark_Int32 resourceId, Callback_Boolean_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Boolean);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedCallback_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Callback_Boolean_Void continuation)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Boolean);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Boolean_HoverEvent_Void(Ark_Int32 resourceId, Ark_Boolean isHover, Ark_HoverEvent event)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Boolean_HoverEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(isHover);
    HoverEvent_serializer::write(argsSerializer, event);
    enqueueCallback(&_buffer);
}
void callManagedCallback_Boolean_HoverEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Boolean isHover, Ark_HoverEvent event)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Boolean_HoverEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(isHover);
    HoverEvent_serializer::write(argsSerializer, event);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Boolean_Void(Ark_Int32 resourceId, Ark_Boolean value0)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Boolean_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(value0);
    enqueueCallback(&_buffer);
}
void callManagedCallback_Boolean_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Boolean value0)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Boolean_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(value0);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Buffer_Void(Ark_Int32 resourceId, Ark_Buffer value)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Buffer_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBuffer(value);
    enqueueCallback(&_buffer);
}
void callManagedCallback_Buffer_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Buffer value)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Buffer_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBuffer(value);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_CalendarRequestedData_Void(Ark_Int32 resourceId, Ark_CalendarRequestedData event)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_CalendarRequestedData_Void);
    argsSerializer.writeInt32(resourceId);
    CalendarRequestedData_serializer::write(argsSerializer, event);
    enqueueCallback(&_buffer);
}
void callManagedCallback_CalendarRequestedData_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_CalendarRequestedData event)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_CalendarRequestedData_Void);
    argsSerializer.writeInt32(resourceId);
    CalendarRequestedData_serializer::write(argsSerializer, event);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_CalendarSelectedDate_Void(Ark_Int32 resourceId, Ark_CalendarSelectedDate event)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_CalendarSelectedDate_Void);
    argsSerializer.writeInt32(resourceId);
    CalendarSelectedDate_serializer::write(argsSerializer, event);
    enqueueCallback(&_buffer);
}
void callManagedCallback_CalendarSelectedDate_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_CalendarSelectedDate event)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_CalendarSelectedDate_Void);
    argsSerializer.writeInt32(resourceId);
    CalendarSelectedDate_serializer::write(argsSerializer, event);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_ClickEvent_Void(Ark_Int32 resourceId, Ark_ClickEvent event)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_ClickEvent_Void);
    argsSerializer.writeInt32(resourceId);
    ClickEvent_serializer::write(argsSerializer, event);
    enqueueCallback(&_buffer);
}
void callManagedCallback_ClickEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_ClickEvent event)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_ClickEvent_Void);
    argsSerializer.writeInt32(resourceId);
    ClickEvent_serializer::write(argsSerializer, event);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_ComputedBarAttribute_Void(Ark_Int32 resourceId, Ark_ComputedBarAttribute value)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_ComputedBarAttribute_Void);
    argsSerializer.writeInt32(resourceId);
    ComputedBarAttribute_serializer::write(argsSerializer, value);
    enqueueCallback(&_buffer);
}
void callManagedCallback_ComputedBarAttribute_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_ComputedBarAttribute value)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_ComputedBarAttribute_Void);
    argsSerializer.writeInt32(resourceId);
    ComputedBarAttribute_serializer::write(argsSerializer, value);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_CopyEvent_Void(Ark_Int32 resourceId, Ark_CopyEvent value0)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_CopyEvent_Void);
    argsSerializer.writeInt32(resourceId);
    CopyEvent_serializer::write(argsSerializer, value0);
    enqueueCallback(&_buffer);
}
void callManagedCallback_CopyEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_CopyEvent value0)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_CopyEvent_Void);
    argsSerializer.writeInt32(resourceId);
    CopyEvent_serializer::write(argsSerializer, value0);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_CreateItem(Ark_Int32 resourceId, Ark_Int32 index, Callback_Pointer_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_CreateItem);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedCallback_CreateItemSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 index, Callback_Pointer_Void continuation)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_CreateItem);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_CrownEvent_Void(Ark_Int32 resourceId, Ark_CrownEvent value0)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_CrownEvent_Void);
    argsSerializer.writeInt32(resourceId);
    CrownEvent_serializer::write(argsSerializer, value0);
    enqueueCallback(&_buffer);
}
void callManagedCallback_CrownEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_CrownEvent value0)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_CrownEvent_Void);
    argsSerializer.writeInt32(resourceId);
    CrownEvent_serializer::write(argsSerializer, value0);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_CustomSpanMeasureInfo_CustomSpanMetrics(Ark_Int32 resourceId, Ark_CustomSpanMeasureInfo measureInfo, Callback_CustomSpanMetrics_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_CustomSpanMeasureInfo_CustomSpanMetrics);
    argsSerializer.writeInt32(resourceId);
    CustomSpanMeasureInfo_serializer::write(argsSerializer, measureInfo);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedCallback_CustomSpanMeasureInfo_CustomSpanMetricsSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_CustomSpanMeasureInfo measureInfo, Callback_CustomSpanMetrics_Void continuation)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_CustomSpanMeasureInfo_CustomSpanMetrics);
    argsSerializer.writeInt32(resourceId);
    CustomSpanMeasureInfo_serializer::write(argsSerializer, measureInfo);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_CustomSpanMetrics_Void(Ark_Int32 resourceId, Ark_CustomSpanMetrics value)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_CustomSpanMetrics_Void);
    argsSerializer.writeInt32(resourceId);
    CustomSpanMetrics_serializer::write(argsSerializer, value);
    enqueueCallback(&_buffer);
}
void callManagedCallback_CustomSpanMetrics_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_CustomSpanMetrics value)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_CustomSpanMetrics_Void);
    argsSerializer.writeInt32(resourceId);
    CustomSpanMetrics_serializer::write(argsSerializer, value);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_CutEvent_Void(Ark_Int32 resourceId, Ark_CutEvent value0)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_CutEvent_Void);
    argsSerializer.writeInt32(resourceId);
    CutEvent_serializer::write(argsSerializer, value0);
    enqueueCallback(&_buffer);
}
void callManagedCallback_CutEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_CutEvent value0)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_CutEvent_Void);
    argsSerializer.writeInt32(resourceId);
    CutEvent_serializer::write(argsSerializer, value0);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Date_Void(Ark_Int32 resourceId, Ark_Date value0)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Date_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt64(value0);
    enqueueCallback(&_buffer);
}
void callManagedCallback_Date_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Date value0)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Date_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt64(value0);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_DeleteValue_Boolean(Ark_Int32 resourceId, Ark_DeleteValue value0, Callback_Boolean_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_DeleteValue_Boolean);
    argsSerializer.writeInt32(resourceId);
    DeleteValue_serializer::write(argsSerializer, value0);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedCallback_DeleteValue_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_DeleteValue value0, Callback_Boolean_Void continuation)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_DeleteValue_Boolean);
    argsSerializer.writeInt32(resourceId);
    DeleteValue_serializer::write(argsSerializer, value0);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_DeleteValue_Void(Ark_Int32 resourceId, Ark_DeleteValue value0)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_DeleteValue_Void);
    argsSerializer.writeInt32(resourceId);
    DeleteValue_serializer::write(argsSerializer, value0);
    enqueueCallback(&_buffer);
}
void callManagedCallback_DeleteValue_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_DeleteValue value0)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_DeleteValue_Void);
    argsSerializer.writeInt32(resourceId);
    DeleteValue_serializer::write(argsSerializer, value0);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_DismissContentCoverAction_Void(Ark_Int32 resourceId, Ark_DismissContentCoverAction value0)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_DismissContentCoverAction_Void);
    argsSerializer.writeInt32(resourceId);
    DismissContentCoverAction_serializer::write(argsSerializer, value0);
    enqueueCallback(&_buffer);
}
void callManagedCallback_DismissContentCoverAction_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_DismissContentCoverAction value0)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_DismissContentCoverAction_Void);
    argsSerializer.writeInt32(resourceId);
    DismissContentCoverAction_serializer::write(argsSerializer, value0);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_DismissDialogAction_Void(Ark_Int32 resourceId, Ark_DismissDialogAction value0)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_DismissDialogAction_Void);
    argsSerializer.writeInt32(resourceId);
    DismissDialogAction_serializer::write(argsSerializer, value0);
    enqueueCallback(&_buffer);
}
void callManagedCallback_DismissDialogAction_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_DismissDialogAction value0)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_DismissDialogAction_Void);
    argsSerializer.writeInt32(resourceId);
    DismissDialogAction_serializer::write(argsSerializer, value0);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_DismissPopupAction_Void(Ark_Int32 resourceId, Ark_DismissPopupAction value0)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_DismissPopupAction_Void);
    argsSerializer.writeInt32(resourceId);
    DismissPopupAction_serializer::write(argsSerializer, value0);
    enqueueCallback(&_buffer);
}
void callManagedCallback_DismissPopupAction_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_DismissPopupAction value0)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_DismissPopupAction_Void);
    argsSerializer.writeInt32(resourceId);
    DismissPopupAction_serializer::write(argsSerializer, value0);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_DismissSheetAction_Void(Ark_Int32 resourceId, Ark_DismissSheetAction value0)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_DismissSheetAction_Void);
    argsSerializer.writeInt32(resourceId);
    DismissSheetAction_serializer::write(argsSerializer, value0);
    enqueueCallback(&_buffer);
}
void callManagedCallback_DismissSheetAction_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_DismissSheetAction value0)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_DismissSheetAction_Void);
    argsSerializer.writeInt32(resourceId);
    DismissSheetAction_serializer::write(argsSerializer, value0);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_DragEvent_Opt_String_Void(Ark_Int32 resourceId, Ark_DragEvent event, Opt_String extraParams)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_DragEvent_Opt_String_Void);
    argsSerializer.writeInt32(resourceId);
    DragEvent_serializer::write(argsSerializer, event);
    Ark_Int32 extraParams_type = INTEROP_RUNTIME_UNDEFINED;
    extraParams_type = runtimeType(extraParams);
    argsSerializer.writeInt8(extraParams_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (extraParams_type)) {
        const auto extraParams_value = extraParams.value;
        argsSerializer.writeString(extraParams_value);
    }
    enqueueCallback(&_buffer);
}
void callManagedCallback_DragEvent_Opt_String_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_DragEvent event, Opt_String extraParams)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_DragEvent_Opt_String_Void);
    argsSerializer.writeInt32(resourceId);
    DragEvent_serializer::write(argsSerializer, event);
    Ark_Int32 extraParams_type = INTEROP_RUNTIME_UNDEFINED;
    extraParams_type = runtimeType(extraParams);
    argsSerializer.writeInt8(extraParams_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (extraParams_type)) {
        const auto extraParams_value = extraParams.value;
        argsSerializer.writeString(extraParams_value);
    }
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_DrawContext_CustomSpanDrawInfo_Void(Ark_Int32 resourceId, Ark_DrawContext context, Ark_CustomSpanDrawInfo drawInfo)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_DrawContext_CustomSpanDrawInfo_Void);
    argsSerializer.writeInt32(resourceId);
    DrawContext_serializer::write(argsSerializer, context);
    CustomSpanDrawInfo_serializer::write(argsSerializer, drawInfo);
    enqueueCallback(&_buffer);
}
void callManagedCallback_DrawContext_CustomSpanDrawInfo_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_DrawContext context, Ark_CustomSpanDrawInfo drawInfo)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_DrawContext_CustomSpanDrawInfo_Void);
    argsSerializer.writeInt32(resourceId);
    DrawContext_serializer::write(argsSerializer, context);
    CustomSpanDrawInfo_serializer::write(argsSerializer, drawInfo);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_DrawContext_Void(Ark_Int32 resourceId, Ark_DrawContext drawContext)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_DrawContext_Void);
    argsSerializer.writeInt32(resourceId);
    DrawContext_serializer::write(argsSerializer, drawContext);
    enqueueCallback(&_buffer);
}
void callManagedCallback_DrawContext_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_DrawContext drawContext)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_DrawContext_Void);
    argsSerializer.writeInt32(resourceId);
    DrawContext_serializer::write(argsSerializer, drawContext);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_EditableTextChangeValue_Boolean(Ark_Int32 resourceId, Ark_EditableTextChangeValue value0, Callback_Boolean_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_EditableTextChangeValue_Boolean);
    argsSerializer.writeInt32(resourceId);
    EditableTextChangeValue_serializer::write(argsSerializer, value0);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedCallback_EditableTextChangeValue_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_EditableTextChangeValue value0, Callback_Boolean_Void continuation)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_EditableTextChangeValue_Boolean);
    argsSerializer.writeInt32(resourceId);
    EditableTextChangeValue_serializer::write(argsSerializer, value0);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_EnterKeyType_Void(Ark_Int32 resourceId, Ark_EnterKeyType enterKey)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_EnterKeyType_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_EnterKeyType>(enterKey));
    enqueueCallback(&_buffer);
}
void callManagedCallback_EnterKeyType_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_EnterKeyType enterKey)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_EnterKeyType_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_EnterKeyType>(enterKey));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Extender_OnFinish(Ark_Int32 resourceId)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Extender_OnFinish);
    argsSerializer.writeInt32(resourceId);
    enqueueCallback(&_buffer);
}
void callManagedCallback_Extender_OnFinishSync(Ark_VMContext vmContext, Ark_Int32 resourceId)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Extender_OnFinish);
    argsSerializer.writeInt32(resourceId);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Extender_OnProgress(Ark_Int32 resourceId, Ark_Float32 value)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Extender_OnProgress);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFloat32(value);
    enqueueCallback(&_buffer);
}
void callManagedCallback_Extender_OnProgressSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Float32 value)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Extender_OnProgress);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFloat32(value);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_FocusAxisEvent_Void(Ark_Int32 resourceId, Ark_FocusAxisEvent value0)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_FocusAxisEvent_Void);
    argsSerializer.writeInt32(resourceId);
    FocusAxisEvent_serializer::write(argsSerializer, value0);
    enqueueCallback(&_buffer);
}
void callManagedCallback_FocusAxisEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_FocusAxisEvent value0)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_FocusAxisEvent_Void);
    argsSerializer.writeInt32(resourceId);
    FocusAxisEvent_serializer::write(argsSerializer, value0);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_FormCallbackInfo_Void(Ark_Int32 resourceId, Ark_FormCallbackInfo value0)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_FormCallbackInfo_Void);
    argsSerializer.writeInt32(resourceId);
    FormCallbackInfo_serializer::write(argsSerializer, value0);
    enqueueCallback(&_buffer);
}
void callManagedCallback_FormCallbackInfo_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_FormCallbackInfo value0)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_FormCallbackInfo_Void);
    argsSerializer.writeInt32(resourceId);
    FormCallbackInfo_serializer::write(argsSerializer, value0);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_FormError_Void(Ark_Int32 resourceId, Ark_FormError value0)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_FormError_Void);
    argsSerializer.writeInt32(resourceId);
    FormError_serializer::write(argsSerializer, value0);
    enqueueCallback(&_buffer);
}
void callManagedCallback_FormError_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_FormError value0)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_FormError_Void);
    argsSerializer.writeInt32(resourceId);
    FormError_serializer::write(argsSerializer, value0);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_FullscreenInfo_Void(Ark_Int32 resourceId, Ark_FullscreenInfo value0)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_FullscreenInfo_Void);
    argsSerializer.writeInt32(resourceId);
    FullscreenInfo_serializer::write(argsSerializer, value0);
    enqueueCallback(&_buffer);
}
void callManagedCallback_FullscreenInfo_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_FullscreenInfo value0)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_FullscreenInfo_Void);
    argsSerializer.writeInt32(resourceId);
    FullscreenInfo_serializer::write(argsSerializer, value0);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_GestureEvent_Void(Ark_Int32 resourceId, Ark_GestureEvent event)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_GestureEvent_Void);
    argsSerializer.writeInt32(resourceId);
    GestureEvent_serializer::write(argsSerializer, event);
    enqueueCallback(&_buffer);
}
void callManagedCallback_GestureEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_GestureEvent event)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_GestureEvent_Void);
    argsSerializer.writeInt32(resourceId);
    GestureEvent_serializer::write(argsSerializer, event);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_GestureInfo_BaseGestureEvent_GestureJudgeResult(Ark_Int32 resourceId, Ark_GestureInfo gestureInfo, Ark_BaseGestureEvent event, Callback_GestureJudgeResult_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult);
    argsSerializer.writeInt32(resourceId);
    GestureInfo_serializer::write(argsSerializer, gestureInfo);
    BaseGestureEvent_serializer::write(argsSerializer, event);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedCallback_GestureInfo_BaseGestureEvent_GestureJudgeResultSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_GestureInfo gestureInfo, Ark_BaseGestureEvent event, Callback_GestureJudgeResult_Void continuation)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult);
    argsSerializer.writeInt32(resourceId);
    GestureInfo_serializer::write(argsSerializer, gestureInfo);
    BaseGestureEvent_serializer::write(argsSerializer, event);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_GestureJudgeResult_Void(Ark_Int32 resourceId, Ark_GestureJudgeResult value)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_GestureJudgeResult_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_GestureJudgeResult>(value));
    enqueueCallback(&_buffer);
}
void callManagedCallback_GestureJudgeResult_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_GestureJudgeResult value)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_GestureJudgeResult_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_GestureJudgeResult>(value));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_GestureRecognizer_Void(Ark_Int32 resourceId, Ark_GestureRecognizer value)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_GestureRecognizer_Void);
    argsSerializer.writeInt32(resourceId);
    GestureRecognizer_serializer::write(argsSerializer, value);
    enqueueCallback(&_buffer);
}
void callManagedCallback_GestureRecognizer_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_GestureRecognizer value)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_GestureRecognizer_Void);
    argsSerializer.writeInt32(resourceId);
    GestureRecognizer_serializer::write(argsSerializer, value);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_HitTestMode_Void(Ark_Int32 resourceId, Ark_HitTestMode value)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_HitTestMode_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_HitTestMode>(value));
    enqueueCallback(&_buffer);
}
void callManagedCallback_HitTestMode_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_HitTestMode value)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_HitTestMode_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_HitTestMode>(value));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_HoverEvent_Void(Ark_Int32 resourceId, Ark_HoverEvent value0)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_HoverEvent_Void);
    argsSerializer.writeInt32(resourceId);
    HoverEvent_serializer::write(argsSerializer, value0);
    enqueueCallback(&_buffer);
}
void callManagedCallback_HoverEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_HoverEvent value0)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_HoverEvent_Void);
    argsSerializer.writeInt32(resourceId);
    HoverEvent_serializer::write(argsSerializer, value0);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_InsertValue_Boolean(Ark_Int32 resourceId, Ark_InsertValue value0, Callback_Boolean_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_InsertValue_Boolean);
    argsSerializer.writeInt32(resourceId);
    InsertValue_serializer::write(argsSerializer, value0);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedCallback_InsertValue_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_InsertValue value0, Callback_Boolean_Void continuation)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_InsertValue_Boolean);
    argsSerializer.writeInt32(resourceId);
    InsertValue_serializer::write(argsSerializer, value0);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_InsertValue_Void(Ark_Int32 resourceId, Ark_InsertValue value0)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_InsertValue_Void);
    argsSerializer.writeInt32(resourceId);
    InsertValue_serializer::write(argsSerializer, value0);
    enqueueCallback(&_buffer);
}
void callManagedCallback_InsertValue_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_InsertValue value0)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_InsertValue_Void);
    argsSerializer.writeInt32(resourceId);
    InsertValue_serializer::write(argsSerializer, value0);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_InteropComponent(Ark_Int32 resourceId, Callback_InteropComponent_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_InteropComponent);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedCallback_InteropComponentSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Callback_InteropComponent_Void continuation)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_InteropComponent);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_InteropComponent_Void(Ark_Int32 resourceId, Ark_InteropComponent value)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_InteropComponent_Void);
    argsSerializer.writeInt32(resourceId);
    InteropComponent_serializer::write(argsSerializer, value);
    enqueueCallback(&_buffer);
}
void callManagedCallback_InteropComponent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_InteropComponent value)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_InteropComponent_Void);
    argsSerializer.writeInt32(resourceId);
    InteropComponent_serializer::write(argsSerializer, value);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_ItemDragInfo_Number_Number_Boolean_Void(Ark_Int32 resourceId, Ark_ItemDragInfo event, Ark_Number itemIndex, Ark_Number insertIndex, Ark_Boolean isSuccess)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_ItemDragInfo_Number_Number_Boolean_Void);
    argsSerializer.writeInt32(resourceId);
    ItemDragInfo_serializer::write(argsSerializer, event);
    argsSerializer.writeNumber(itemIndex);
    argsSerializer.writeNumber(insertIndex);
    argsSerializer.writeBoolean(isSuccess);
    enqueueCallback(&_buffer);
}
void callManagedCallback_ItemDragInfo_Number_Number_Boolean_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_ItemDragInfo event, Ark_Number itemIndex, Ark_Number insertIndex, Ark_Boolean isSuccess)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_ItemDragInfo_Number_Number_Boolean_Void);
    argsSerializer.writeInt32(resourceId);
    ItemDragInfo_serializer::write(argsSerializer, event);
    argsSerializer.writeNumber(itemIndex);
    argsSerializer.writeNumber(insertIndex);
    argsSerializer.writeBoolean(isSuccess);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_ItemDragInfo_Number_Number_Void(Ark_Int32 resourceId, Ark_ItemDragInfo event, Ark_Number itemIndex, Ark_Number insertIndex)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_ItemDragInfo_Number_Number_Void);
    argsSerializer.writeInt32(resourceId);
    ItemDragInfo_serializer::write(argsSerializer, event);
    argsSerializer.writeNumber(itemIndex);
    argsSerializer.writeNumber(insertIndex);
    enqueueCallback(&_buffer);
}
void callManagedCallback_ItemDragInfo_Number_Number_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_ItemDragInfo event, Ark_Number itemIndex, Ark_Number insertIndex)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_ItemDragInfo_Number_Number_Void);
    argsSerializer.writeInt32(resourceId);
    ItemDragInfo_serializer::write(argsSerializer, event);
    argsSerializer.writeNumber(itemIndex);
    argsSerializer.writeNumber(insertIndex);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_ItemDragInfo_Number_Void(Ark_Int32 resourceId, Ark_ItemDragInfo event, Ark_Number itemIndex)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_ItemDragInfo_Number_Void);
    argsSerializer.writeInt32(resourceId);
    ItemDragInfo_serializer::write(argsSerializer, event);
    argsSerializer.writeNumber(itemIndex);
    enqueueCallback(&_buffer);
}
void callManagedCallback_ItemDragInfo_Number_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_ItemDragInfo event, Ark_Number itemIndex)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_ItemDragInfo_Number_Void);
    argsSerializer.writeInt32(resourceId);
    ItemDragInfo_serializer::write(argsSerializer, event);
    argsSerializer.writeNumber(itemIndex);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_ItemDragInfo_Void(Ark_Int32 resourceId, Ark_ItemDragInfo event)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_ItemDragInfo_Void);
    argsSerializer.writeInt32(resourceId);
    ItemDragInfo_serializer::write(argsSerializer, event);
    enqueueCallback(&_buffer);
}
void callManagedCallback_ItemDragInfo_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_ItemDragInfo event)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_ItemDragInfo_Void);
    argsSerializer.writeInt32(resourceId);
    ItemDragInfo_serializer::write(argsSerializer, event);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_KeyEvent_Boolean(Ark_Int32 resourceId, Ark_KeyEvent value0, Callback_Boolean_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_KeyEvent_Boolean);
    argsSerializer.writeInt32(resourceId);
    KeyEvent_serializer::write(argsSerializer, value0);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedCallback_KeyEvent_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_KeyEvent value0, Callback_Boolean_Void continuation)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_KeyEvent_Boolean);
    argsSerializer.writeInt32(resourceId);
    KeyEvent_serializer::write(argsSerializer, value0);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_KeyEvent_Void(Ark_Int32 resourceId, Ark_KeyEvent event)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_KeyEvent_Void);
    argsSerializer.writeInt32(resourceId);
    KeyEvent_serializer::write(argsSerializer, event);
    enqueueCallback(&_buffer);
}
void callManagedCallback_KeyEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_KeyEvent event)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_KeyEvent_Void);
    argsSerializer.writeInt32(resourceId);
    KeyEvent_serializer::write(argsSerializer, event);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Map_String_Object_Void(Ark_Int32 resourceId, Map_String_Object value0)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Map_String_Object_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(value0.size);
    for (int32_t i = 0; i < value0.size; i++) {
        auto value0_key = value0.keys[i];
        auto value0_value = value0.values[i];
        argsSerializer.writeString(value0_key);
        argsSerializer.writeObject(value0_value);
    }
    enqueueCallback(&_buffer);
}
void callManagedCallback_Map_String_Object_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Map_String_Object value0)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Map_String_Object_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(value0.size);
    for (int32_t i = 0; i < value0.size; i++) {
        auto value0_key = value0.keys[i];
        auto value0_value = value0.values[i];
        argsSerializer.writeString(value0_key);
        argsSerializer.writeObject(value0_value);
    }
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_MarqueeState_Void(Ark_Int32 resourceId, Ark_MarqueeState value0)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_MarqueeState_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_MarqueeState>(value0));
    enqueueCallback(&_buffer);
}
void callManagedCallback_MarqueeState_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_MarqueeState value0)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_MarqueeState_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_MarqueeState>(value0));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_MouseEvent_Void(Ark_Int32 resourceId, Ark_MouseEvent event)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_MouseEvent_Void);
    argsSerializer.writeInt32(resourceId);
    MouseEvent_serializer::write(argsSerializer, event);
    enqueueCallback(&_buffer);
}
void callManagedCallback_MouseEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_MouseEvent event)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_MouseEvent_Void);
    argsSerializer.writeInt32(resourceId);
    MouseEvent_serializer::write(argsSerializer, event);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_NavDestinationActiveReason_Void(Ark_Int32 resourceId, Ark_NavDestinationActiveReason value0)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_NavDestinationActiveReason_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_NavDestinationActiveReason>(value0));
    enqueueCallback(&_buffer);
}
void callManagedCallback_NavDestinationActiveReason_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NavDestinationActiveReason value0)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_NavDestinationActiveReason_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_NavDestinationActiveReason>(value0));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_NavDestinationContext_Void(Ark_Int32 resourceId, Ark_NavDestinationContext value0)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_NavDestinationContext_Void);
    argsSerializer.writeInt32(resourceId);
    NavDestinationContext_serializer::write(argsSerializer, value0);
    enqueueCallback(&_buffer);
}
void callManagedCallback_NavDestinationContext_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NavDestinationContext value0)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_NavDestinationContext_Void);
    argsSerializer.writeInt32(resourceId);
    NavDestinationContext_serializer::write(argsSerializer, value0);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_NavigationMode_Void(Ark_Int32 resourceId, Ark_NavigationMode mode)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_NavigationMode_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_NavigationMode>(mode));
    enqueueCallback(&_buffer);
}
void callManagedCallback_NavigationMode_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NavigationMode mode)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_NavigationMode_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_NavigationMode>(mode));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_NavigationTitleMode_Void(Ark_Int32 resourceId, Ark_NavigationTitleMode titleMode)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_NavigationTitleMode_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_NavigationTitleMode>(titleMode));
    enqueueCallback(&_buffer);
}
void callManagedCallback_NavigationTitleMode_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NavigationTitleMode titleMode)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_NavigationTitleMode_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_NavigationTitleMode>(titleMode));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_NavigationTransitionProxy_Void(Ark_Int32 resourceId, Ark_NavigationTransitionProxy transitionProxy)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_NavigationTransitionProxy_Void);
    argsSerializer.writeInt32(resourceId);
    NavigationTransitionProxy_serializer::write(argsSerializer, transitionProxy);
    enqueueCallback(&_buffer);
}
void callManagedCallback_NavigationTransitionProxy_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NavigationTransitionProxy transitionProxy)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_NavigationTransitionProxy_Void);
    argsSerializer.writeInt32(resourceId);
    NavigationTransitionProxy_serializer::write(argsSerializer, transitionProxy);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Number(Ark_Int32 resourceId, Callback_Number_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Number);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedCallback_NumberSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Callback_Number_Void continuation)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Number);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Number_ESObject_Void(Ark_Int32 resourceId, Ark_Number elmtId, Ark_CustomObject instance)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Number_ESObject_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(elmtId);
    argsSerializer.writeCustomObject("object", instance);
    enqueueCallback(&_buffer);
}
void callManagedCallback_Number_ESObject_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number elmtId, Ark_CustomObject instance)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Number_ESObject_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(elmtId);
    argsSerializer.writeCustomObject("object", instance);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Number_Number_Boolean(Ark_Int32 resourceId, Ark_Number from, Ark_Number to, Callback_Boolean_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Number_Number_Boolean);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(from);
    argsSerializer.writeNumber(to);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedCallback_Number_Number_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number from, Ark_Number to, Callback_Boolean_Void continuation)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Number_Number_Boolean);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(from);
    argsSerializer.writeNumber(to);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Number_Number_Boolean_Boolean(Ark_Int32 resourceId, Ark_Number offset, Ark_Number index, Ark_Boolean leadingEdge, Callback_Boolean_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Number_Number_Boolean_Boolean);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(offset);
    argsSerializer.writeNumber(index);
    argsSerializer.writeBoolean(leadingEdge);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedCallback_Number_Number_Boolean_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number offset, Ark_Number index, Ark_Boolean leadingEdge, Callback_Boolean_Void continuation)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Number_Number_Boolean_Boolean);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(offset);
    argsSerializer.writeNumber(index);
    argsSerializer.writeBoolean(leadingEdge);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Number_Number_ComputedBarAttribute(Ark_Int32 resourceId, Ark_Number index, Ark_Number offset, Callback_ComputedBarAttribute_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Number_Number_ComputedBarAttribute);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(index);
    argsSerializer.writeNumber(offset);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedCallback_Number_Number_ComputedBarAttributeSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number index, Ark_Number offset, Callback_ComputedBarAttribute_Void continuation)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Number_Number_ComputedBarAttribute);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(index);
    argsSerializer.writeNumber(offset);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Number_Number_Number_Void(Ark_Int32 resourceId, Ark_Number start, Ark_Number end, Ark_Number center)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Number_Number_Number_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(start);
    argsSerializer.writeNumber(end);
    argsSerializer.writeNumber(center);
    enqueueCallback(&_buffer);
}
void callManagedCallback_Number_Number_Number_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number start, Ark_Number end, Ark_Number center)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Number_Number_Number_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(start);
    argsSerializer.writeNumber(end);
    argsSerializer.writeNumber(center);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Number_Number_Void(Ark_Int32 resourceId, Ark_Number first, Ark_Number last)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Number_Number_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(first);
    argsSerializer.writeNumber(last);
    enqueueCallback(&_buffer);
}
void callManagedCallback_Number_Number_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number first, Ark_Number last)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Number_Number_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(first);
    argsSerializer.writeNumber(last);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Number_SliderChangeMode_Void(Ark_Int32 resourceId, Ark_Number value, Ark_SliderChangeMode mode)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Number_SliderChangeMode_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(value);
    argsSerializer.writeInt32(static_cast<Ark_SliderChangeMode>(mode));
    enqueueCallback(&_buffer);
}
void callManagedCallback_Number_SliderChangeMode_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number value, Ark_SliderChangeMode mode)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Number_SliderChangeMode_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(value);
    argsSerializer.writeInt32(static_cast<Ark_SliderChangeMode>(mode));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Number_Tuple_Number_Number(Ark_Int32 resourceId, Ark_Number index, Callback_Tuple_Number_Number_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Number_Tuple_Number_Number);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(index);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedCallback_Number_Tuple_Number_NumberSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number index, Callback_Tuple_Number_Number_Void continuation)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Number_Tuple_Number_Number);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(index);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Number_Tuple_Number_Number_Number_Number(Ark_Int32 resourceId, Ark_Number index, Callback_Tuple_Number_Number_Number_Number_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Number_Tuple_Number_Number_Number_Number);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(index);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedCallback_Number_Tuple_Number_Number_Number_NumberSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number index, Callback_Tuple_Number_Number_Number_Number_Void continuation)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Number_Tuple_Number_Number_Number_Number);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(index);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Number_Void(Ark_Int32 resourceId, Ark_Number value)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Number_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(value);
    enqueueCallback(&_buffer);
}
void callManagedCallback_Number_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number value)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Number_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(value);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_onMeasureSize_SizeResult(Ark_Int32 resourceId, Ark_GeometryInfo selfLayoutInfo, Array_Measurable children, Ark_ConstraintSizeOptions constraint, Callback_SizeResult_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_onMeasureSize_SizeResult);
    argsSerializer.writeInt32(resourceId);
    GeometryInfo_serializer::write(argsSerializer, selfLayoutInfo);
    argsSerializer.writeInt32(children.length);
    for (int i = 0; i < children.length; i++) {
        const Ark_Measurable children_element = children.array[i];
        Measurable_serializer::write(argsSerializer, children_element);
    }
    ConstraintSizeOptions_serializer::write(argsSerializer, constraint);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedCallback_onMeasureSize_SizeResultSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_GeometryInfo selfLayoutInfo, Array_Measurable children, Ark_ConstraintSizeOptions constraint, Callback_SizeResult_Void continuation)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_onMeasureSize_SizeResult);
    argsSerializer.writeInt32(resourceId);
    GeometryInfo_serializer::write(argsSerializer, selfLayoutInfo);
    argsSerializer.writeInt32(children.length);
    for (int i = 0; i < children.length; i++) {
        const Ark_Measurable children_element = children.array[i];
        Measurable_serializer::write(argsSerializer, children_element);
    }
    ConstraintSizeOptions_serializer::write(argsSerializer, constraint);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_onPlaceChildren_Void(Ark_Int32 resourceId, Ark_GeometryInfo selfLayoutInfo, Array_Layoutable children, Ark_ConstraintSizeOptions constraint)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_onPlaceChildren_Void);
    argsSerializer.writeInt32(resourceId);
    GeometryInfo_serializer::write(argsSerializer, selfLayoutInfo);
    argsSerializer.writeInt32(children.length);
    for (int i = 0; i < children.length; i++) {
        const Ark_Layoutable children_element = children.array[i];
        Layoutable_serializer::write(argsSerializer, children_element);
    }
    ConstraintSizeOptions_serializer::write(argsSerializer, constraint);
    enqueueCallback(&_buffer);
}
void callManagedCallback_onPlaceChildren_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_GeometryInfo selfLayoutInfo, Array_Layoutable children, Ark_ConstraintSizeOptions constraint)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_onPlaceChildren_Void);
    argsSerializer.writeInt32(resourceId);
    GeometryInfo_serializer::write(argsSerializer, selfLayoutInfo);
    argsSerializer.writeInt32(children.length);
    for (int i = 0; i < children.length; i++) {
        const Ark_Layoutable children_element = children.array[i];
        Layoutable_serializer::write(argsSerializer, children_element);
    }
    ConstraintSizeOptions_serializer::write(argsSerializer, constraint);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_OnScrollFrameBeginHandlerResult_Void(Ark_Int32 resourceId, Ark_OnScrollFrameBeginHandlerResult value)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnScrollFrameBeginHandlerResult_Void);
    argsSerializer.writeInt32(resourceId);
    OnScrollFrameBeginHandlerResult_serializer::write(argsSerializer, value);
    enqueueCallback(&_buffer);
}
void callManagedCallback_OnScrollFrameBeginHandlerResult_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnScrollFrameBeginHandlerResult value)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_OnScrollFrameBeginHandlerResult_Void);
    argsSerializer.writeInt32(resourceId);
    OnScrollFrameBeginHandlerResult_serializer::write(argsSerializer, value);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Opt_Array_FontDescriptor_Opt_Array_String_Void(Ark_Int32 resourceId, Opt_Array_CustomObject value, Opt_Array_String error)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Opt_Array_FontDescriptor_Opt_Array_String_Void);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 value_type = INTEROP_RUNTIME_UNDEFINED;
    value_type = runtimeType(value);
    argsSerializer.writeInt8(value_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (value_type)) {
        const auto value_value = value.value;
        argsSerializer.writeInt32(value_value.length);
        for (int i = 0; i < value_value.length; i++) {
            const Ark_CustomObject value_value_element = value_value.array[i];
            argsSerializer.writeCustomObject("object", value_value_element);
        }
    }
    Ark_Int32 error_type = INTEROP_RUNTIME_UNDEFINED;
    error_type = runtimeType(error);
    argsSerializer.writeInt8(error_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (error_type)) {
        const auto error_value = error.value;
        argsSerializer.writeInt32(error_value.length);
        for (int i = 0; i < error_value.length; i++) {
            const Ark_String error_value_element = error_value.array[i];
            argsSerializer.writeString(error_value_element);
        }
    }
    enqueueCallback(&_buffer);
}
void callManagedCallback_Opt_Array_FontDescriptor_Opt_Array_String_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Opt_Array_CustomObject value, Opt_Array_String error)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Opt_Array_FontDescriptor_Opt_Array_String_Void);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 value_type = INTEROP_RUNTIME_UNDEFINED;
    value_type = runtimeType(value);
    argsSerializer.writeInt8(value_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (value_type)) {
        const auto value_value = value.value;
        argsSerializer.writeInt32(value_value.length);
        for (int i = 0; i < value_value.length; i++) {
            const Ark_CustomObject value_value_element = value_value.array[i];
            argsSerializer.writeCustomObject("object", value_value_element);
        }
    }
    Ark_Int32 error_type = INTEROP_RUNTIME_UNDEFINED;
    error_type = runtimeType(error);
    argsSerializer.writeInt8(error_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (error_type)) {
        const auto error_value = error.value;
        argsSerializer.writeInt32(error_value.length);
        for (int i = 0; i < error_value.length; i++) {
            const Ark_String error_value_element = error_value.array[i];
            argsSerializer.writeString(error_value_element);
        }
    }
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Opt_Array_NavDestinationTransition_Void(Ark_Int32 resourceId, Opt_Array_NavDestinationTransition value)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Opt_Array_NavDestinationTransition_Void);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 value_type = INTEROP_RUNTIME_UNDEFINED;
    value_type = runtimeType(value);
    argsSerializer.writeInt8(value_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (value_type)) {
        const auto value_value = value.value;
        argsSerializer.writeInt32(value_value.length);
        for (int i = 0; i < value_value.length; i++) {
            const Ark_NavDestinationTransition value_value_element = value_value.array[i];
            NavDestinationTransition_serializer::write(argsSerializer, value_value_element);
        }
    }
    enqueueCallback(&_buffer);
}
void callManagedCallback_Opt_Array_NavDestinationTransition_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Opt_Array_NavDestinationTransition value)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Opt_Array_NavDestinationTransition_Void);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 value_type = INTEROP_RUNTIME_UNDEFINED;
    value_type = runtimeType(value);
    argsSerializer.writeInt8(value_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (value_type)) {
        const auto value_value = value.value;
        argsSerializer.writeInt32(value_value.length);
        for (int i = 0; i < value_value.length; i++) {
            const Ark_NavDestinationTransition value_value_element = value_value.array[i];
            NavDestinationTransition_serializer::write(argsSerializer, value_value_element);
        }
    }
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Opt_Array_String_Opt_Array_String_Void(Ark_Int32 resourceId, Opt_Array_String value, Opt_Array_String error)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Opt_Array_String_Opt_Array_String_Void);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 value_type = INTEROP_RUNTIME_UNDEFINED;
    value_type = runtimeType(value);
    argsSerializer.writeInt8(value_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (value_type)) {
        const auto value_value = value.value;
        argsSerializer.writeInt32(value_value.length);
        for (int i = 0; i < value_value.length; i++) {
            const Ark_String value_value_element = value_value.array[i];
            argsSerializer.writeString(value_value_element);
        }
    }
    Ark_Int32 error_type = INTEROP_RUNTIME_UNDEFINED;
    error_type = runtimeType(error);
    argsSerializer.writeInt8(error_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (error_type)) {
        const auto error_value = error.value;
        argsSerializer.writeInt32(error_value.length);
        for (int i = 0; i < error_value.length; i++) {
            const Ark_String error_value_element = error_value.array[i];
            argsSerializer.writeString(error_value_element);
        }
    }
    enqueueCallback(&_buffer);
}
void callManagedCallback_Opt_Array_String_Opt_Array_String_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Opt_Array_String value, Opt_Array_String error)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Opt_Array_String_Opt_Array_String_Void);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 value_type = INTEROP_RUNTIME_UNDEFINED;
    value_type = runtimeType(value);
    argsSerializer.writeInt8(value_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (value_type)) {
        const auto value_value = value.value;
        argsSerializer.writeInt32(value_value.length);
        for (int i = 0; i < value_value.length; i++) {
            const Ark_String value_value_element = value_value.array[i];
            argsSerializer.writeString(value_value_element);
        }
    }
    Ark_Int32 error_type = INTEROP_RUNTIME_UNDEFINED;
    error_type = runtimeType(error);
    argsSerializer.writeInt8(error_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (error_type)) {
        const auto error_value = error.value;
        argsSerializer.writeInt32(error_value.length);
        for (int i = 0; i < error_value.length; i++) {
            const Ark_String error_value_element = error_value.array[i];
            argsSerializer.writeString(error_value_element);
        }
    }
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Opt_Array_String_Void(Ark_Int32 resourceId, Opt_Array_String error)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Opt_Array_String_Void);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 error_type = INTEROP_RUNTIME_UNDEFINED;
    error_type = runtimeType(error);
    argsSerializer.writeInt8(error_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (error_type)) {
        const auto error_value = error.value;
        argsSerializer.writeInt32(error_value.length);
        for (int i = 0; i < error_value.length; i++) {
            const Ark_String error_value_element = error_value.array[i];
            argsSerializer.writeString(error_value_element);
        }
    }
    enqueueCallback(&_buffer);
}
void callManagedCallback_Opt_Array_String_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Opt_Array_String error)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Opt_Array_String_Void);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 error_type = INTEROP_RUNTIME_UNDEFINED;
    error_type = runtimeType(error);
    argsSerializer.writeInt8(error_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (error_type)) {
        const auto error_value = error.value;
        argsSerializer.writeInt32(error_value.length);
        for (int i = 0; i < error_value.length; i++) {
            const Ark_String error_value_element = error_value.array[i];
            argsSerializer.writeString(error_value_element);
        }
    }
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Opt_CustomBuilder_Void(Ark_Int32 resourceId, Opt_CustomNodeBuilder value)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Opt_CustomBuilder_Void);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 value_type = INTEROP_RUNTIME_UNDEFINED;
    value_type = runtimeType(value);
    argsSerializer.writeInt8(value_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (value_type)) {
        const auto value_value = value.value;
        argsSerializer.writeCallbackResource(value_value.resource);
        argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(value_value.call));
        argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(value_value.callSync));
    }
    enqueueCallback(&_buffer);
}
void callManagedCallback_Opt_CustomBuilder_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Opt_CustomNodeBuilder value)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Opt_CustomBuilder_Void);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 value_type = INTEROP_RUNTIME_UNDEFINED;
    value_type = runtimeType(value);
    argsSerializer.writeInt8(value_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (value_type)) {
        const auto value_value = value.value;
        argsSerializer.writeCallbackResource(value_value.resource);
        argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(value_value.call));
        argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(value_value.callSync));
    }
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Opt_FontDescriptor_Opt_Array_String_Void(Ark_Int32 resourceId, Opt_CustomObject value, Opt_Array_String error)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Opt_FontDescriptor_Opt_Array_String_Void);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 value_type = INTEROP_RUNTIME_UNDEFINED;
    value_type = runtimeType(value);
    argsSerializer.writeInt8(value_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (value_type)) {
        const auto value_value = value.value;
        argsSerializer.writeCustomObject("object", value_value);
    }
    Ark_Int32 error_type = INTEROP_RUNTIME_UNDEFINED;
    error_type = runtimeType(error);
    argsSerializer.writeInt8(error_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (error_type)) {
        const auto error_value = error.value;
        argsSerializer.writeInt32(error_value.length);
        for (int i = 0; i < error_value.length; i++) {
            const Ark_String error_value_element = error_value.array[i];
            argsSerializer.writeString(error_value_element);
        }
    }
    enqueueCallback(&_buffer);
}
void callManagedCallback_Opt_FontDescriptor_Opt_Array_String_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Opt_CustomObject value, Opt_Array_String error)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Opt_FontDescriptor_Opt_Array_String_Void);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 value_type = INTEROP_RUNTIME_UNDEFINED;
    value_type = runtimeType(value);
    argsSerializer.writeInt8(value_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (value_type)) {
        const auto value_value = value.value;
        argsSerializer.writeCustomObject("object", value_value);
    }
    Ark_Int32 error_type = INTEROP_RUNTIME_UNDEFINED;
    error_type = runtimeType(error);
    argsSerializer.writeInt8(error_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (error_type)) {
        const auto error_value = error.value;
        argsSerializer.writeInt32(error_value.length);
        for (int i = 0; i < error_value.length; i++) {
            const Ark_String error_value_element = error_value.array[i];
            argsSerializer.writeString(error_value_element);
        }
    }
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Opt_NavigationAnimatedTransition_Void(Ark_Int32 resourceId, Opt_NavigationAnimatedTransition value)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Opt_NavigationAnimatedTransition_Void);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 value_type = INTEROP_RUNTIME_UNDEFINED;
    value_type = runtimeType(value);
    argsSerializer.writeInt8(value_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (value_type)) {
        const auto value_value = value.value;
        NavigationAnimatedTransition_serializer::write(argsSerializer, value_value);
    }
    enqueueCallback(&_buffer);
}
void callManagedCallback_Opt_NavigationAnimatedTransition_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Opt_NavigationAnimatedTransition value)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Opt_NavigationAnimatedTransition_Void);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 value_type = INTEROP_RUNTIME_UNDEFINED;
    value_type = runtimeType(value);
    argsSerializer.writeInt8(value_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (value_type)) {
        const auto value_value = value.value;
        NavigationAnimatedTransition_serializer::write(argsSerializer, value_value);
    }
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Opt_OffsetResult_Void(Ark_Int32 resourceId, Opt_OffsetResult value)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Opt_OffsetResult_Void);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 value_type = INTEROP_RUNTIME_UNDEFINED;
    value_type = runtimeType(value);
    argsSerializer.writeInt8(value_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (value_type)) {
        const auto value_value = value.value;
        OffsetResult_serializer::write(argsSerializer, value_value);
    }
    enqueueCallback(&_buffer);
}
void callManagedCallback_Opt_OffsetResult_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Opt_OffsetResult value)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Opt_OffsetResult_Void);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 value_type = INTEROP_RUNTIME_UNDEFINED;
    value_type = runtimeType(value);
    argsSerializer.writeInt8(value_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (value_type)) {
        const auto value_value = value.value;
        OffsetResult_serializer::write(argsSerializer, value_value);
    }
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Opt_Scene_Opt_Array_String_Void(Ark_Int32 resourceId, Opt_Scene value, Opt_Array_String error)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Opt_Scene_Opt_Array_String_Void);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 value_type = INTEROP_RUNTIME_UNDEFINED;
    value_type = runtimeType(value);
    argsSerializer.writeInt8(value_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (value_type)) {
        const auto value_value = value.value;
        Scene_serializer::write(argsSerializer, value_value);
    }
    Ark_Int32 error_type = INTEROP_RUNTIME_UNDEFINED;
    error_type = runtimeType(error);
    argsSerializer.writeInt8(error_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (error_type)) {
        const auto error_value = error.value;
        argsSerializer.writeInt32(error_value.length);
        for (int i = 0; i < error_value.length; i++) {
            const Ark_String error_value_element = error_value.array[i];
            argsSerializer.writeString(error_value_element);
        }
    }
    enqueueCallback(&_buffer);
}
void callManagedCallback_Opt_Scene_Opt_Array_String_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Opt_Scene value, Opt_Array_String error)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Opt_Scene_Opt_Array_String_Void);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 value_type = INTEROP_RUNTIME_UNDEFINED;
    value_type = runtimeType(value);
    argsSerializer.writeInt8(value_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (value_type)) {
        const auto value_value = value.value;
        Scene_serializer::write(argsSerializer, value_value);
    }
    Ark_Int32 error_type = INTEROP_RUNTIME_UNDEFINED;
    error_type = runtimeType(error);
    argsSerializer.writeInt8(error_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (error_type)) {
        const auto error_value = error.value;
        argsSerializer.writeInt32(error_value.length);
        for (int i = 0; i < error_value.length; i++) {
            const Ark_String error_value_element = error_value.array[i];
            argsSerializer.writeString(error_value_element);
        }
    }
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Opt_ScrollResult_Void(Ark_Int32 resourceId, Opt_ScrollResult value)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Opt_ScrollResult_Void);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 value_type = INTEROP_RUNTIME_UNDEFINED;
    value_type = runtimeType(value);
    argsSerializer.writeInt8(value_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (value_type)) {
        const auto value_value = value.value;
        ScrollResult_serializer::write(argsSerializer, value_value);
    }
    enqueueCallback(&_buffer);
}
void callManagedCallback_Opt_ScrollResult_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Opt_ScrollResult value)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Opt_ScrollResult_Void);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 value_type = INTEROP_RUNTIME_UNDEFINED;
    value_type = runtimeType(value);
    argsSerializer.writeInt8(value_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (value_type)) {
        const auto value_value = value.value;
        ScrollResult_serializer::write(argsSerializer, value_value);
    }
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Opt_String_Opt_Array_String_Void(Ark_Int32 resourceId, Opt_String value, Opt_Array_String error)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Opt_String_Opt_Array_String_Void);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 value_type = INTEROP_RUNTIME_UNDEFINED;
    value_type = runtimeType(value);
    argsSerializer.writeInt8(value_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (value_type)) {
        const auto value_value = value.value;
        argsSerializer.writeString(value_value);
    }
    Ark_Int32 error_type = INTEROP_RUNTIME_UNDEFINED;
    error_type = runtimeType(error);
    argsSerializer.writeInt8(error_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (error_type)) {
        const auto error_value = error.value;
        argsSerializer.writeInt32(error_value.length);
        for (int i = 0; i < error_value.length; i++) {
            const Ark_String error_value_element = error_value.array[i];
            argsSerializer.writeString(error_value_element);
        }
    }
    enqueueCallback(&_buffer);
}
void callManagedCallback_Opt_String_Opt_Array_String_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Opt_String value, Opt_Array_String error)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Opt_String_Opt_Array_String_Void);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 value_type = INTEROP_RUNTIME_UNDEFINED;
    value_type = runtimeType(value);
    argsSerializer.writeInt8(value_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (value_type)) {
        const auto value_value = value.value;
        argsSerializer.writeString(value_value);
    }
    Ark_Int32 error_type = INTEROP_RUNTIME_UNDEFINED;
    error_type = runtimeType(error);
    argsSerializer.writeInt8(error_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (error_type)) {
        const auto error_value = error.value;
        argsSerializer.writeInt32(error_value.length);
        for (int i = 0; i < error_value.length; i++) {
            const Ark_String error_value_element = error_value.array[i];
            argsSerializer.writeString(error_value_element);
        }
    }
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Opt_StyledString_Opt_Array_String_Void(Ark_Int32 resourceId, Opt_StyledString value, Opt_Array_String error)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Opt_StyledString_Opt_Array_String_Void);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 value_type = INTEROP_RUNTIME_UNDEFINED;
    value_type = runtimeType(value);
    argsSerializer.writeInt8(value_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (value_type)) {
        const auto value_value = value.value;
        StyledString_serializer::write(argsSerializer, value_value);
    }
    Ark_Int32 error_type = INTEROP_RUNTIME_UNDEFINED;
    error_type = runtimeType(error);
    argsSerializer.writeInt8(error_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (error_type)) {
        const auto error_value = error.value;
        argsSerializer.writeInt32(error_value.length);
        for (int i = 0; i < error_value.length; i++) {
            const Ark_String error_value_element = error_value.array[i];
            argsSerializer.writeString(error_value_element);
        }
    }
    enqueueCallback(&_buffer);
}
void callManagedCallback_Opt_StyledString_Opt_Array_String_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Opt_StyledString value, Opt_Array_String error)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Opt_StyledString_Opt_Array_String_Void);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 value_type = INTEROP_RUNTIME_UNDEFINED;
    value_type = runtimeType(value);
    argsSerializer.writeInt8(value_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (value_type)) {
        const auto value_value = value.value;
        StyledString_serializer::write(argsSerializer, value_value);
    }
    Ark_Int32 error_type = INTEROP_RUNTIME_UNDEFINED;
    error_type = runtimeType(error);
    argsSerializer.writeInt8(error_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (error_type)) {
        const auto error_value = error.value;
        argsSerializer.writeInt32(error_value.length);
        for (int i = 0; i < error_value.length; i++) {
            const Ark_String error_value_element = error_value.array[i];
            argsSerializer.writeString(error_value_element);
        }
    }
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Opt_TabContentAnimatedTransition_Void(Ark_Int32 resourceId, Opt_TabContentAnimatedTransition value)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Opt_TabContentAnimatedTransition_Void);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 value_type = INTEROP_RUNTIME_UNDEFINED;
    value_type = runtimeType(value);
    argsSerializer.writeInt8(value_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (value_type)) {
        const auto value_value = value.value;
        TabContentAnimatedTransition_serializer::write(argsSerializer, value_value);
    }
    enqueueCallback(&_buffer);
}
void callManagedCallback_Opt_TabContentAnimatedTransition_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Opt_TabContentAnimatedTransition value)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Opt_TabContentAnimatedTransition_Void);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 value_type = INTEROP_RUNTIME_UNDEFINED;
    value_type = runtimeType(value);
    argsSerializer.writeInt8(value_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (value_type)) {
        const auto value_value = value.value;
        TabContentAnimatedTransition_serializer::write(argsSerializer, value_value);
    }
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_PlaybackInfo_Void(Ark_Int32 resourceId, Ark_PlaybackInfo value0)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_PlaybackInfo_Void);
    argsSerializer.writeInt32(resourceId);
    PlaybackInfo_serializer::write(argsSerializer, value0);
    enqueueCallback(&_buffer);
}
void callManagedCallback_PlaybackInfo_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_PlaybackInfo value0)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_PlaybackInfo_Void);
    argsSerializer.writeInt32(resourceId);
    PlaybackInfo_serializer::write(argsSerializer, value0);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Pointer_Void(Ark_Int32 resourceId, Ark_NativePointer value)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Pointer_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(value);
    enqueueCallback(&_buffer);
}
void callManagedCallback_Pointer_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NativePointer value)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Pointer_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(value);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_PopInfo_Void(Ark_Int32 resourceId, Ark_PopInfo value0)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_PopInfo_Void);
    argsSerializer.writeInt32(resourceId);
    PopInfo_serializer::write(argsSerializer, value0);
    enqueueCallback(&_buffer);
}
void callManagedCallback_PopInfo_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_PopInfo value0)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_PopInfo_Void);
    argsSerializer.writeInt32(resourceId);
    PopInfo_serializer::write(argsSerializer, value0);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_PreDragStatus_Void(Ark_Int32 resourceId, Ark_PreDragStatus value0)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_PreDragStatus_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_PreDragStatus>(value0));
    enqueueCallback(&_buffer);
}
void callManagedCallback_PreDragStatus_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_PreDragStatus value0)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_PreDragStatus_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_PreDragStatus>(value0));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_PreparedInfo_Void(Ark_Int32 resourceId, Ark_PreparedInfo value0)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_PreparedInfo_Void);
    argsSerializer.writeInt32(resourceId);
    PreparedInfo_serializer::write(argsSerializer, value0);
    enqueueCallback(&_buffer);
}
void callManagedCallback_PreparedInfo_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_PreparedInfo value0)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_PreparedInfo_Void);
    argsSerializer.writeInt32(resourceId);
    PreparedInfo_serializer::write(argsSerializer, value0);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_RangeUpdate(Ark_Int32 resourceId, Ark_Int32 start, Ark_Int32 end)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_RangeUpdate);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(start);
    argsSerializer.writeInt32(end);
    enqueueCallback(&_buffer);
}
void callManagedCallback_RangeUpdateSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 start, Ark_Int32 end)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_RangeUpdate);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(start);
    argsSerializer.writeInt32(end);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_RefreshStatus_Void(Ark_Int32 resourceId, Ark_RefreshStatus state)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_RefreshStatus_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_RefreshStatus>(state));
    enqueueCallback(&_buffer);
}
void callManagedCallback_RefreshStatus_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_RefreshStatus state)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_RefreshStatus_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_RefreshStatus>(state));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_RichEditorChangeValue_Boolean(Ark_Int32 resourceId, Ark_RichEditorChangeValue value0, Callback_Boolean_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_RichEditorChangeValue_Boolean);
    argsSerializer.writeInt32(resourceId);
    RichEditorChangeValue_serializer::write(argsSerializer, value0);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedCallback_RichEditorChangeValue_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_RichEditorChangeValue value0, Callback_Boolean_Void continuation)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_RichEditorChangeValue_Boolean);
    argsSerializer.writeInt32(resourceId);
    RichEditorChangeValue_serializer::write(argsSerializer, value0);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_RichEditorDeleteValue_Boolean(Ark_Int32 resourceId, Ark_RichEditorDeleteValue value0, Callback_Boolean_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_RichEditorDeleteValue_Boolean);
    argsSerializer.writeInt32(resourceId);
    RichEditorDeleteValue_serializer::write(argsSerializer, value0);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedCallback_RichEditorDeleteValue_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_RichEditorDeleteValue value0, Callback_Boolean_Void continuation)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_RichEditorDeleteValue_Boolean);
    argsSerializer.writeInt32(resourceId);
    RichEditorDeleteValue_serializer::write(argsSerializer, value0);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_RichEditorInsertValue_Boolean(Ark_Int32 resourceId, Ark_RichEditorInsertValue value0, Callback_Boolean_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_RichEditorInsertValue_Boolean);
    argsSerializer.writeInt32(resourceId);
    RichEditorInsertValue_serializer::write(argsSerializer, value0);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedCallback_RichEditorInsertValue_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_RichEditorInsertValue value0, Callback_Boolean_Void continuation)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_RichEditorInsertValue_Boolean);
    argsSerializer.writeInt32(resourceId);
    RichEditorInsertValue_serializer::write(argsSerializer, value0);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_RichEditorRange_Void(Ark_Int32 resourceId, Ark_RichEditorRange value0)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_RichEditorRange_Void);
    argsSerializer.writeInt32(resourceId);
    RichEditorRange_serializer::write(argsSerializer, value0);
    enqueueCallback(&_buffer);
}
void callManagedCallback_RichEditorRange_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_RichEditorRange value0)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_RichEditorRange_Void);
    argsSerializer.writeInt32(resourceId);
    RichEditorRange_serializer::write(argsSerializer, value0);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_RichEditorSelection_Void(Ark_Int32 resourceId, Ark_RichEditorSelection value0)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_RichEditorSelection_Void);
    argsSerializer.writeInt32(resourceId);
    RichEditorSelection_serializer::write(argsSerializer, value0);
    enqueueCallback(&_buffer);
}
void callManagedCallback_RichEditorSelection_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_RichEditorSelection value0)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_RichEditorSelection_Void);
    argsSerializer.writeInt32(resourceId);
    RichEditorSelection_serializer::write(argsSerializer, value0);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_RichEditorTextSpanResult_Void(Ark_Int32 resourceId, Ark_RichEditorTextSpanResult value0)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_RichEditorTextSpanResult_Void);
    argsSerializer.writeInt32(resourceId);
    RichEditorTextSpanResult_serializer::write(argsSerializer, value0);
    enqueueCallback(&_buffer);
}
void callManagedCallback_RichEditorTextSpanResult_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_RichEditorTextSpanResult value0)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_RichEditorTextSpanResult_Void);
    argsSerializer.writeInt32(resourceId);
    RichEditorTextSpanResult_serializer::write(argsSerializer, value0);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_RotationGesture(Ark_Int32 resourceId, Callback_RotationGesture_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_RotationGesture);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedCallback_RotationGestureSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Callback_RotationGesture_Void continuation)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_RotationGesture);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_RotationGesture_Void(Ark_Int32 resourceId, Ark_RotationGesture value)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_RotationGesture_Void);
    argsSerializer.writeInt32(resourceId);
    RotationGesture_serializer::write(argsSerializer, value);
    enqueueCallback(&_buffer);
}
void callManagedCallback_RotationGesture_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_RotationGesture value)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_RotationGesture_Void);
    argsSerializer.writeInt32(resourceId);
    RotationGesture_serializer::write(argsSerializer, value);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_SheetDismiss_Void(Ark_Int32 resourceId, Ark_SheetDismiss sheetDismiss)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_SheetDismiss_Void);
    argsSerializer.writeInt32(resourceId);
    SheetDismiss_serializer::write(argsSerializer, sheetDismiss);
    enqueueCallback(&_buffer);
}
void callManagedCallback_SheetDismiss_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_SheetDismiss sheetDismiss)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_SheetDismiss_Void);
    argsSerializer.writeInt32(resourceId);
    SheetDismiss_serializer::write(argsSerializer, sheetDismiss);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_SheetType_Void(Ark_Int32 resourceId, Ark_SheetType value0)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_SheetType_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_SheetType>(value0));
    enqueueCallback(&_buffer);
}
void callManagedCallback_SheetType_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_SheetType value0)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_SheetType_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_SheetType>(value0));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_SizeResult_Void(Ark_Int32 resourceId, Ark_SizeResult value)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_SizeResult_Void);
    argsSerializer.writeInt32(resourceId);
    SizeResult_serializer::write(argsSerializer, value);
    enqueueCallback(&_buffer);
}
void callManagedCallback_SizeResult_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_SizeResult value)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_SizeResult_Void);
    argsSerializer.writeInt32(resourceId);
    SizeResult_serializer::write(argsSerializer, value);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_SpringBackAction_Void(Ark_Int32 resourceId, Ark_SpringBackAction value0)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_SpringBackAction_Void);
    argsSerializer.writeInt32(resourceId);
    SpringBackAction_serializer::write(argsSerializer, value0);
    enqueueCallback(&_buffer);
}
void callManagedCallback_SpringBackAction_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_SpringBackAction value0)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_SpringBackAction_Void);
    argsSerializer.writeInt32(resourceId);
    SpringBackAction_serializer::write(argsSerializer, value0);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_StateStylesChange(Ark_Int32 resourceId, Ark_Int32 currentState)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_StateStylesChange);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(currentState);
    enqueueCallback(&_buffer);
}
void callManagedCallback_StateStylesChangeSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 currentState)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_StateStylesChange);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(currentState);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_String_PasteEvent_Void(Ark_Int32 resourceId, Ark_String value, Ark_PasteEvent event)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_String_PasteEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(value);
    PasteEvent_serializer::write(argsSerializer, event);
    enqueueCallback(&_buffer);
}
void callManagedCallback_String_PasteEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_String value, Ark_PasteEvent event)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_String_PasteEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(value);
    PasteEvent_serializer::write(argsSerializer, event);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_String_SurfaceRect_Void(Ark_Int32 resourceId, Ark_String surfaceId, Ark_SurfaceRect rect)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_String_SurfaceRect_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(surfaceId);
    SurfaceRect_serializer::write(argsSerializer, rect);
    enqueueCallback(&_buffer);
}
void callManagedCallback_String_SurfaceRect_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_String surfaceId, Ark_SurfaceRect rect)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_String_SurfaceRect_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(surfaceId);
    SurfaceRect_serializer::write(argsSerializer, rect);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_String_Void(Ark_Int32 resourceId, Ark_String breakpoints)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_String_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(breakpoints);
    enqueueCallback(&_buffer);
}
void callManagedCallback_String_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_String breakpoints)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_String_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(breakpoints);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_StyledStringChangeValue_Boolean(Ark_Int32 resourceId, Ark_StyledStringChangeValue value0, Callback_Boolean_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_StyledStringChangeValue_Boolean);
    argsSerializer.writeInt32(resourceId);
    StyledStringChangeValue_serializer::write(argsSerializer, value0);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedCallback_StyledStringChangeValue_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_StyledStringChangeValue value0, Callback_Boolean_Void continuation)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_StyledStringChangeValue_Boolean);
    argsSerializer.writeInt32(resourceId);
    StyledStringChangeValue_serializer::write(argsSerializer, value0);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_StyledStringMarshallingValue_Void(Ark_Int32 resourceId, Ark_UserDataSpan value)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_StyledStringMarshallingValue_Void);
    argsSerializer.writeInt32(resourceId);
    UserDataSpan_serializer::write(argsSerializer, value);
    enqueueCallback(&_buffer);
}
void callManagedCallback_StyledStringMarshallingValue_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_UserDataSpan value)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_StyledStringMarshallingValue_Void);
    argsSerializer.writeInt32(resourceId);
    UserDataSpan_serializer::write(argsSerializer, value);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_SwipeActionState_Void(Ark_Int32 resourceId, Ark_SwipeActionState state)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_SwipeActionState_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_SwipeActionState>(state));
    enqueueCallback(&_buffer);
}
void callManagedCallback_SwipeActionState_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_SwipeActionState state)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_SwipeActionState_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_SwipeActionState>(state));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_SwipeGesture(Ark_Int32 resourceId, Callback_SwipeGesture_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_SwipeGesture);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedCallback_SwipeGestureSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Callback_SwipeGesture_Void continuation)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_SwipeGesture);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_SwipeGesture_Void(Ark_Int32 resourceId, Ark_SwipeGesture value)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_SwipeGesture_Void);
    argsSerializer.writeInt32(resourceId);
    SwipeGesture_serializer::write(argsSerializer, value);
    enqueueCallback(&_buffer);
}
void callManagedCallback_SwipeGesture_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_SwipeGesture value)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_SwipeGesture_Void);
    argsSerializer.writeInt32(resourceId);
    SwipeGesture_serializer::write(argsSerializer, value);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_SwiperContentTransitionProxy_Void(Ark_Int32 resourceId, Ark_SwiperContentTransitionProxy value0)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_SwiperContentTransitionProxy_Void);
    argsSerializer.writeInt32(resourceId);
    SwiperContentTransitionProxy_serializer::write(argsSerializer, value0);
    enqueueCallback(&_buffer);
}
void callManagedCallback_SwiperContentTransitionProxy_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_SwiperContentTransitionProxy value0)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_SwiperContentTransitionProxy_Void);
    argsSerializer.writeInt32(resourceId);
    SwiperContentTransitionProxy_serializer::write(argsSerializer, value0);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_T(Ark_Int32 resourceId, Callback_T_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_T);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedCallback_TSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Callback_T_Void continuation)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_T);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_T_Number_String(Ark_Int32 resourceId, Ark_CustomObject item, Ark_Number index, Callback_String_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_T_Number_String);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeCustomObject("T", item);
    argsSerializer.writeNumber(index);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedCallback_T_Number_StringSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_CustomObject item, Ark_Number index, Callback_String_Void continuation)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_T_Number_String);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeCustomObject("T", item);
    argsSerializer.writeNumber(index);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_T_Number_Void(Ark_Int32 resourceId, Ark_CustomObject item, Ark_Number index)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_T_Number_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeCustomObject("T", item);
    argsSerializer.writeNumber(index);
    enqueueCallback(&_buffer);
}
void callManagedCallback_T_Number_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_CustomObject item, Ark_Number index)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_T_Number_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeCustomObject("T", item);
    argsSerializer.writeNumber(index);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_T_Void(Ark_Int32 resourceId, Ark_CustomObject instance)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_T_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeCustomObject("T", instance);
    enqueueCallback(&_buffer);
}
void callManagedCallback_T_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_CustomObject instance)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_T_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeCustomObject("T", instance);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_TabContentTransitionProxy_Void(Ark_Int32 resourceId, Ark_TabContentTransitionProxy value0)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_TabContentTransitionProxy_Void);
    argsSerializer.writeInt32(resourceId);
    TabContentTransitionProxy_serializer::write(argsSerializer, value0);
    enqueueCallback(&_buffer);
}
void callManagedCallback_TabContentTransitionProxy_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_TabContentTransitionProxy value0)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_TabContentTransitionProxy_Void);
    argsSerializer.writeInt32(resourceId);
    TabContentTransitionProxy_serializer::write(argsSerializer, value0);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_TerminationInfo_Void(Ark_Int32 resourceId, Ark_TerminationInfo value0)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_TerminationInfo_Void);
    argsSerializer.writeInt32(resourceId);
    TerminationInfo_serializer::write(argsSerializer, value0);
    enqueueCallback(&_buffer);
}
void callManagedCallback_TerminationInfo_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_TerminationInfo value0)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_TerminationInfo_Void);
    argsSerializer.writeInt32(resourceId);
    TerminationInfo_serializer::write(argsSerializer, value0);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_TextPickerResult_Void(Ark_Int32 resourceId, Ark_TextPickerResult value)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_TextPickerResult_Void);
    argsSerializer.writeInt32(resourceId);
    TextPickerResult_serializer::write(argsSerializer, value);
    enqueueCallback(&_buffer);
}
void callManagedCallback_TextPickerResult_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_TextPickerResult value)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_TextPickerResult_Void);
    argsSerializer.writeInt32(resourceId);
    TextPickerResult_serializer::write(argsSerializer, value);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_TextRange_Void(Ark_Int32 resourceId, Ark_TextRange value0)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_TextRange_Void);
    argsSerializer.writeInt32(resourceId);
    TextRange_serializer::write(argsSerializer, value0);
    enqueueCallback(&_buffer);
}
void callManagedCallback_TextRange_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_TextRange value0)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_TextRange_Void);
    argsSerializer.writeInt32(resourceId);
    TextRange_serializer::write(argsSerializer, value0);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_TimePickerResult_Void(Ark_Int32 resourceId, Ark_TimePickerResult value0)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_TimePickerResult_Void);
    argsSerializer.writeInt32(resourceId);
    TimePickerResult_serializer::write(argsSerializer, value0);
    enqueueCallback(&_buffer);
}
void callManagedCallback_TimePickerResult_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_TimePickerResult value0)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_TimePickerResult_Void);
    argsSerializer.writeInt32(resourceId);
    TimePickerResult_serializer::write(argsSerializer, value0);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_TouchEvent_HitTestMode(Ark_Int32 resourceId, Ark_TouchEvent value0, Callback_HitTestMode_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_TouchEvent_HitTestMode);
    argsSerializer.writeInt32(resourceId);
    TouchEvent_serializer::write(argsSerializer, value0);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedCallback_TouchEvent_HitTestModeSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_TouchEvent value0, Callback_HitTestMode_Void continuation)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_TouchEvent_HitTestMode);
    argsSerializer.writeInt32(resourceId);
    TouchEvent_serializer::write(argsSerializer, value0);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_TouchEvent_Void(Ark_Int32 resourceId, Ark_TouchEvent event)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_TouchEvent_Void);
    argsSerializer.writeInt32(resourceId);
    TouchEvent_serializer::write(argsSerializer, event);
    enqueueCallback(&_buffer);
}
void callManagedCallback_TouchEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_TouchEvent event)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_TouchEvent_Void);
    argsSerializer.writeInt32(resourceId);
    TouchEvent_serializer::write(argsSerializer, event);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_TouchResult_Void(Ark_Int32 resourceId, Ark_TouchResult value)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_TouchResult_Void);
    argsSerializer.writeInt32(resourceId);
    TouchResult_serializer::write(argsSerializer, value);
    enqueueCallback(&_buffer);
}
void callManagedCallback_TouchResult_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_TouchResult value)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_TouchResult_Void);
    argsSerializer.writeInt32(resourceId);
    TouchResult_serializer::write(argsSerializer, value);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Tuple_Number_Number_Number_Number_Void(Ark_Int32 resourceId, Ark_Tuple_Number_Number_Number_Number value)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Tuple_Number_Number_Number_Number_Void);
    argsSerializer.writeInt32(resourceId);
    const auto value_0 = value.value0;
    argsSerializer.writeNumber(value_0);
    const auto value_1 = value.value1;
    argsSerializer.writeNumber(value_1);
    const auto value_2 = value.value2;
    argsSerializer.writeNumber(value_2);
    const auto value_3 = value.value3;
    argsSerializer.writeNumber(value_3);
    enqueueCallback(&_buffer);
}
void callManagedCallback_Tuple_Number_Number_Number_Number_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Tuple_Number_Number_Number_Number value)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Tuple_Number_Number_Number_Number_Void);
    argsSerializer.writeInt32(resourceId);
    const auto value_0 = value.value0;
    argsSerializer.writeNumber(value_0);
    const auto value_1 = value.value1;
    argsSerializer.writeNumber(value_1);
    const auto value_2 = value.value2;
    argsSerializer.writeNumber(value_2);
    const auto value_3 = value.value3;
    argsSerializer.writeNumber(value_3);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Tuple_Number_Number_Void(Ark_Int32 resourceId, Ark_Tuple_Number_Number value)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Tuple_Number_Number_Void);
    argsSerializer.writeInt32(resourceId);
    const auto value_0 = value.value0;
    argsSerializer.writeNumber(value_0);
    const auto value_1 = value.value1;
    argsSerializer.writeNumber(value_1);
    enqueueCallback(&_buffer);
}
void callManagedCallback_Tuple_Number_Number_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Tuple_Number_Number value)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Tuple_Number_Number_Void);
    argsSerializer.writeInt32(resourceId);
    const auto value_0 = value.value0;
    argsSerializer.writeNumber(value_0);
    const auto value_1 = value.value1;
    argsSerializer.writeNumber(value_1);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_UIExtensionProxy_Void(Ark_Int32 resourceId, Ark_UIExtensionProxy value0)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_UIExtensionProxy_Void);
    argsSerializer.writeInt32(resourceId);
    UIExtensionProxy_serializer::write(argsSerializer, value0);
    enqueueCallback(&_buffer);
}
void callManagedCallback_UIExtensionProxy_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_UIExtensionProxy value0)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_UIExtensionProxy_Void);
    argsSerializer.writeInt32(resourceId);
    UIExtensionProxy_serializer::write(argsSerializer, value0);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Union_CustomBuilder_DragItemInfo_Void(Ark_Int32 resourceId, Ark_Union_CustomBuilder_DragItemInfo value)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Union_CustomBuilder_DragItemInfo_Void);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 value_type = INTEROP_RUNTIME_UNDEFINED;
    value_type = value.selector;
    if (value_type == 0) {
        argsSerializer.writeInt8(0);
        const auto value_0 = value.value0;
        argsSerializer.writeCallbackResource(value_0.resource);
        argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(value_0.call));
        argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(value_0.callSync));
    }
    else if (value_type == 1) {
        argsSerializer.writeInt8(1);
        const auto value_1 = value.value1;
        DragItemInfo_serializer::write(argsSerializer, value_1);
    }
    enqueueCallback(&_buffer);
}
void callManagedCallback_Union_CustomBuilder_DragItemInfo_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Union_CustomBuilder_DragItemInfo value)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Union_CustomBuilder_DragItemInfo_Void);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 value_type = INTEROP_RUNTIME_UNDEFINED;
    value_type = value.selector;
    if (value_type == 0) {
        argsSerializer.writeInt8(0);
        const auto value_0 = value.value0;
        argsSerializer.writeCallbackResource(value_0.resource);
        argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(value_0.call));
        argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(value_0.callSync));
    }
    else if (value_type == 1) {
        argsSerializer.writeInt8(1);
        const auto value_1 = value.value1;
        DragItemInfo_serializer::write(argsSerializer, value_1);
    }
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Union_Object_Undefined_Void(Ark_Int32 resourceId, Opt_Object value0)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Union_Object_Undefined_Void);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 value0_type = INTEROP_RUNTIME_UNDEFINED;
    value0_type = runtimeType(value0);
    argsSerializer.writeInt8(value0_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (value0_type)) {
        const auto value0_value = value0.value;
        argsSerializer.writeObject(value0_value);
    }
    enqueueCallback(&_buffer);
}
void callManagedCallback_Union_Object_Undefined_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Opt_Object value0)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Union_Object_Undefined_Void);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 value0_type = INTEROP_RUNTIME_UNDEFINED;
    value0_type = runtimeType(value0);
    argsSerializer.writeInt8(value0_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (value0_type)) {
        const auto value0_value = value0.value;
        argsSerializer.writeObject(value0_value);
    }
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Void(Ark_Int32 resourceId)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Void);
    argsSerializer.writeInt32(resourceId);
    enqueueCallback(&_buffer);
}
void callManagedCallback_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Void);
    argsSerializer.writeInt32(resourceId);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCheckBoxModifierBuilder(Ark_Int32 resourceId, Ark_NativePointer parentNode, Ark_CheckBoxConfiguration config, Callback_Pointer_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_CheckBoxModifierBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    CheckBoxConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedCheckBoxModifierBuilderSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NativePointer parentNode, Ark_CheckBoxConfiguration config, Callback_Pointer_Void continuation)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_CheckBoxModifierBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    CheckBoxConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedContentDidScrollCallback(Ark_Int32 resourceId, Ark_Number selectedIndex, Ark_Number index, Ark_Number position, Ark_Number mainAxisLength)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_ContentDidScrollCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(selectedIndex);
    argsSerializer.writeNumber(index);
    argsSerializer.writeNumber(position);
    argsSerializer.writeNumber(mainAxisLength);
    enqueueCallback(&_buffer);
}
void callManagedContentDidScrollCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number selectedIndex, Ark_Number index, Ark_Number position, Ark_Number mainAxisLength)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_ContentDidScrollCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(selectedIndex);
    argsSerializer.writeNumber(index);
    argsSerializer.writeNumber(position);
    argsSerializer.writeNumber(mainAxisLength);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedContentWillScrollCallback(Ark_Int32 resourceId, Ark_SwiperContentWillScrollResult result, Callback_Boolean_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_ContentWillScrollCallback);
    argsSerializer.writeInt32(resourceId);
    SwiperContentWillScrollResult_serializer::write(argsSerializer, result);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedContentWillScrollCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_SwiperContentWillScrollResult result, Callback_Boolean_Void continuation)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_ContentWillScrollCallback);
    argsSerializer.writeInt32(resourceId);
    SwiperContentWillScrollResult_serializer::write(argsSerializer, result);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedContext_getGroupDir_Callback(Ark_Int32 resourceId, Ark_String result)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Context_getGroupDir_Callback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(result);
    enqueueCallback(&_buffer);
}
void callManagedContext_getGroupDir_CallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_String result)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Context_getGroupDir_Callback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(result);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCustomBuilderT(Ark_Int32 resourceId, Ark_CustomObject t)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_CustomBuilderT);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeCustomObject("object", t);
    enqueueCallback(&_buffer);
}
void callManagedCustomBuilderTSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_CustomObject t)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_CustomBuilderT);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeCustomObject("object", t);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCustomNodeBuilder(Ark_Int32 resourceId, Ark_NativePointer parentNode, Callback_Pointer_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_CustomNodeBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedCustomNodeBuilderSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NativePointer parentNode, Callback_Pointer_Void continuation)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_CustomNodeBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCustomStyles(Ark_Int32 resourceId, Ark_String instance)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_CustomStyles);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(instance);
    enqueueCallback(&_buffer);
}
void callManagedCustomStylesSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_String instance)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_CustomStyles);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(instance);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedDataPanelModifierBuilder(Ark_Int32 resourceId, Ark_NativePointer parentNode, Ark_DataPanelConfiguration config, Callback_Pointer_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_DataPanelModifierBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    DataPanelConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedDataPanelModifierBuilderSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NativePointer parentNode, Ark_DataPanelConfiguration config, Callback_Pointer_Void continuation)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_DataPanelModifierBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    DataPanelConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedEditableTextOnChangeCallback(Ark_Int32 resourceId, Ark_String value, Opt_PreviewText previewText, Opt_TextChangeOptions options)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_EditableTextOnChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(value);
    Ark_Int32 previewText_type = INTEROP_RUNTIME_UNDEFINED;
    previewText_type = runtimeType(previewText);
    argsSerializer.writeInt8(previewText_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (previewText_type)) {
        const auto previewText_value = previewText.value;
        PreviewText_serializer::write(argsSerializer, previewText_value);
    }
    Ark_Int32 options_type = INTEROP_RUNTIME_UNDEFINED;
    options_type = runtimeType(options);
    argsSerializer.writeInt8(options_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (options_type)) {
        const auto options_value = options.value;
        TextChangeOptions_serializer::write(argsSerializer, options_value);
    }
    enqueueCallback(&_buffer);
}
void callManagedEditableTextOnChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_String value, Opt_PreviewText previewText, Opt_TextChangeOptions options)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_EditableTextOnChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(value);
    Ark_Int32 previewText_type = INTEROP_RUNTIME_UNDEFINED;
    previewText_type = runtimeType(previewText);
    argsSerializer.writeInt8(previewText_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (previewText_type)) {
        const auto previewText_value = previewText.value;
        PreviewText_serializer::write(argsSerializer, previewText_value);
    }
    Ark_Int32 options_type = INTEROP_RUNTIME_UNDEFINED;
    options_type = runtimeType(options);
    argsSerializer.writeInt8(options_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (options_type)) {
        const auto options_value = options.value;
        TextChangeOptions_serializer::write(argsSerializer, options_value);
    }
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedErrorCallback(Ark_Int32 resourceId, Ark_BusinessError error)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_ErrorCallback);
    argsSerializer.writeInt32(resourceId);
    BusinessError_serializer::write(argsSerializer, error);
    enqueueCallback(&_buffer);
}
void callManagedErrorCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_BusinessError error)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_ErrorCallback);
    argsSerializer.writeInt32(resourceId);
    BusinessError_serializer::write(argsSerializer, error);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedGaugeModifierBuilder(Ark_Int32 resourceId, Ark_NativePointer parentNode, Ark_GaugeConfiguration config, Callback_Pointer_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_GaugeModifierBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    GaugeConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedGaugeModifierBuilderSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NativePointer parentNode, Ark_GaugeConfiguration config, Callback_Pointer_Void continuation)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_GaugeModifierBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    GaugeConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedGestureRecognizerJudgeBeginCallback(Ark_Int32 resourceId, Ark_BaseGestureEvent event, Ark_GestureRecognizer current, Array_GestureRecognizer recognizers, Callback_GestureJudgeResult_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_GestureRecognizerJudgeBeginCallback);
    argsSerializer.writeInt32(resourceId);
    BaseGestureEvent_serializer::write(argsSerializer, event);
    GestureRecognizer_serializer::write(argsSerializer, current);
    argsSerializer.writeInt32(recognizers.length);
    for (int i = 0; i < recognizers.length; i++) {
        const Ark_GestureRecognizer recognizers_element = recognizers.array[i];
        GestureRecognizer_serializer::write(argsSerializer, recognizers_element);
    }
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedGestureRecognizerJudgeBeginCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_BaseGestureEvent event, Ark_GestureRecognizer current, Array_GestureRecognizer recognizers, Callback_GestureJudgeResult_Void continuation)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_GestureRecognizerJudgeBeginCallback);
    argsSerializer.writeInt32(resourceId);
    BaseGestureEvent_serializer::write(argsSerializer, event);
    GestureRecognizer_serializer::write(argsSerializer, current);
    argsSerializer.writeInt32(recognizers.length);
    for (int i = 0; i < recognizers.length; i++) {
        const Ark_GestureRecognizer recognizers_element = recognizers.array[i];
        GestureRecognizer_serializer::write(argsSerializer, recognizers_element);
    }
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedGetItemMainSizeByIndex(Ark_Int32 resourceId, Ark_Number index, Callback_Number_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_GetItemMainSizeByIndex);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(index);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedGetItemMainSizeByIndexSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number index, Callback_Number_Void continuation)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_GetItemMainSizeByIndex);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(index);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedHoverCallback(Ark_Int32 resourceId, Ark_Boolean isHover, Ark_HoverEvent event)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_HoverCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(isHover);
    HoverEvent_serializer::write(argsSerializer, event);
    enqueueCallback(&_buffer);
}
void callManagedHoverCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Boolean isHover, Ark_HoverEvent event)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_HoverCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(isHover);
    HoverEvent_serializer::write(argsSerializer, event);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedImageCompleteCallback(Ark_Int32 resourceId, Ark_ImageLoadResult result)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_ImageCompleteCallback);
    argsSerializer.writeInt32(resourceId);
    ImageLoadResult_serializer::write(argsSerializer, result);
    enqueueCallback(&_buffer);
}
void callManagedImageCompleteCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_ImageLoadResult result)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_ImageCompleteCallback);
    argsSerializer.writeInt32(resourceId);
    ImageLoadResult_serializer::write(argsSerializer, result);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedImageErrorCallback(Ark_Int32 resourceId, Ark_ImageError error)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_ImageErrorCallback);
    argsSerializer.writeInt32(resourceId);
    ImageError_serializer::write(argsSerializer, error);
    enqueueCallback(&_buffer);
}
void callManagedImageErrorCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_ImageError error)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_ImageErrorCallback);
    argsSerializer.writeInt32(resourceId);
    ImageError_serializer::write(argsSerializer, error);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedImageOnCompleteCallback(Ark_Int32 resourceId, Opt_ImageCompleteEvent loadEvent)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_ImageOnCompleteCallback);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 loadEvent_type = INTEROP_RUNTIME_UNDEFINED;
    loadEvent_type = runtimeType(loadEvent);
    argsSerializer.writeInt8(loadEvent_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (loadEvent_type)) {
        const auto loadEvent_value = loadEvent.value;
        ImageCompleteEvent_serializer::write(argsSerializer, loadEvent_value);
    }
    enqueueCallback(&_buffer);
}
void callManagedImageOnCompleteCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Opt_ImageCompleteEvent loadEvent)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_ImageOnCompleteCallback);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 loadEvent_type = INTEROP_RUNTIME_UNDEFINED;
    loadEvent_type = runtimeType(loadEvent);
    argsSerializer.writeInt8(loadEvent_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (loadEvent_type)) {
        const auto loadEvent_value = loadEvent.value;
        ImageCompleteEvent_serializer::write(argsSerializer, loadEvent_value);
    }
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedInterceptionModeCallback(Ark_Int32 resourceId, Ark_NavigationMode mode)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_InterceptionModeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_NavigationMode>(mode));
    enqueueCallback(&_buffer);
}
void callManagedInterceptionModeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NavigationMode mode)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_InterceptionModeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_NavigationMode>(mode));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedInterceptionShowCallback(Ark_Int32 resourceId, Ark_Union_NavDestinationContext_NavBar from, Ark_Union_NavDestinationContext_NavBar to, Ark_NavigationOperation operation, Ark_Boolean isAnimated)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_InterceptionShowCallback);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 from_type = INTEROP_RUNTIME_UNDEFINED;
    from_type = from.selector;
    if (from_type == 0) {
        argsSerializer.writeInt8(0);
        const auto from_0 = from.value0;
        NavDestinationContext_serializer::write(argsSerializer, from_0);
    }
    else if (from_type == 1) {
        argsSerializer.writeInt8(1);
        const auto from_1 = from.value1;
        argsSerializer.writeString(from_1);
    }
    Ark_Int32 to_type = INTEROP_RUNTIME_UNDEFINED;
    to_type = to.selector;
    if (to_type == 0) {
        argsSerializer.writeInt8(0);
        const auto to_0 = to.value0;
        NavDestinationContext_serializer::write(argsSerializer, to_0);
    }
    else if (to_type == 1) {
        argsSerializer.writeInt8(1);
        const auto to_1 = to.value1;
        argsSerializer.writeString(to_1);
    }
    argsSerializer.writeInt32(static_cast<Ark_NavigationOperation>(operation));
    argsSerializer.writeBoolean(isAnimated);
    enqueueCallback(&_buffer);
}
void callManagedInterceptionShowCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Union_NavDestinationContext_NavBar from, Ark_Union_NavDestinationContext_NavBar to, Ark_NavigationOperation operation, Ark_Boolean isAnimated)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_InterceptionShowCallback);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 from_type = INTEROP_RUNTIME_UNDEFINED;
    from_type = from.selector;
    if (from_type == 0) {
        argsSerializer.writeInt8(0);
        const auto from_0 = from.value0;
        NavDestinationContext_serializer::write(argsSerializer, from_0);
    }
    else if (from_type == 1) {
        argsSerializer.writeInt8(1);
        const auto from_1 = from.value1;
        argsSerializer.writeString(from_1);
    }
    Ark_Int32 to_type = INTEROP_RUNTIME_UNDEFINED;
    to_type = to.selector;
    if (to_type == 0) {
        argsSerializer.writeInt8(0);
        const auto to_0 = to.value0;
        NavDestinationContext_serializer::write(argsSerializer, to_0);
    }
    else if (to_type == 1) {
        argsSerializer.writeInt8(1);
        const auto to_1 = to.value1;
        argsSerializer.writeString(to_1);
    }
    argsSerializer.writeInt32(static_cast<Ark_NavigationOperation>(operation));
    argsSerializer.writeBoolean(isAnimated);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedLoadingProgressModifierBuilder(Ark_Int32 resourceId, Ark_NativePointer parentNode, Ark_LoadingProgressConfiguration config, Callback_Pointer_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_LoadingProgressModifierBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    LoadingProgressConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedLoadingProgressModifierBuilderSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NativePointer parentNode, Ark_LoadingProgressConfiguration config, Callback_Pointer_Void continuation)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_LoadingProgressModifierBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    LoadingProgressConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedMenuCallback(Ark_Int32 resourceId, Ark_Number start, Ark_Number end)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_MenuCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(start);
    argsSerializer.writeNumber(end);
    enqueueCallback(&_buffer);
}
void callManagedMenuCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number start, Ark_Number end)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_MenuCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(start);
    argsSerializer.writeNumber(end);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedMenuItemModifierBuilder(Ark_Int32 resourceId, Ark_NativePointer parentNode, Ark_MenuItemConfiguration config, Callback_Pointer_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_MenuItemModifierBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    MenuItemConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedMenuItemModifierBuilderSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NativePointer parentNode, Ark_MenuItemConfiguration config, Callback_Pointer_Void continuation)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_MenuItemModifierBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    MenuItemConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedMenuOnAppearCallback(Ark_Int32 resourceId, Ark_Number start, Ark_Number end)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_MenuOnAppearCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(start);
    argsSerializer.writeNumber(end);
    enqueueCallback(&_buffer);
}
void callManagedMenuOnAppearCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number start, Ark_Number end)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_MenuOnAppearCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(start);
    argsSerializer.writeNumber(end);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedModifierKeyStateGetter(Ark_Int32 resourceId, Array_String keys, Callback_Boolean_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_ModifierKeyStateGetter);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(keys.length);
    for (int i = 0; i < keys.length; i++) {
        const Ark_String keys_element = keys.array[i];
        argsSerializer.writeString(keys_element);
    }
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedModifierKeyStateGetterSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Array_String keys, Callback_Boolean_Void continuation)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_ModifierKeyStateGetter);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(keys.length);
    for (int i = 0; i < keys.length; i++) {
        const Ark_String keys_element = keys.array[i];
        argsSerializer.writeString(keys_element);
    }
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedNavDestinationTransitionDelegate(Ark_Int32 resourceId, Ark_NavigationOperation operation, Ark_Boolean isEnter, Callback_Opt_Array_NavDestinationTransition_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_NavDestinationTransitionDelegate);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_NavigationOperation>(operation));
    argsSerializer.writeBoolean(isEnter);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedNavDestinationTransitionDelegateSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NavigationOperation operation, Ark_Boolean isEnter, Callback_Opt_Array_NavDestinationTransition_Void continuation)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_NavDestinationTransitionDelegate);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_NavigationOperation>(operation));
    argsSerializer.writeBoolean(isEnter);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedNavExtender_OnUpdateStack(Ark_Int32 resourceId)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_NavExtender_OnUpdateStack);
    argsSerializer.writeInt32(resourceId);
    enqueueCallback(&_buffer);
}
void callManagedNavExtender_OnUpdateStackSync(Ark_VMContext vmContext, Ark_Int32 resourceId)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_NavExtender_OnUpdateStack);
    argsSerializer.writeInt32(resourceId);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnAlphabetIndexerPopupSelectCallback(Ark_Int32 resourceId, Ark_Number index)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnAlphabetIndexerPopupSelectCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(index);
    enqueueCallback(&_buffer);
}
void callManagedOnAlphabetIndexerPopupSelectCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number index)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnAlphabetIndexerPopupSelectCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(index);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnAlphabetIndexerRequestPopupDataCallback(Ark_Int32 resourceId, Ark_Number index, Callback_Array_String_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnAlphabetIndexerRequestPopupDataCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(index);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedOnAlphabetIndexerRequestPopupDataCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number index, Callback_Array_String_Void continuation)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnAlphabetIndexerRequestPopupDataCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(index);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnAlphabetIndexerSelectCallback(Ark_Int32 resourceId, Ark_Number index)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnAlphabetIndexerSelectCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(index);
    enqueueCallback(&_buffer);
}
void callManagedOnAlphabetIndexerSelectCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number index)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnAlphabetIndexerSelectCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(index);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnCheckboxChangeCallback(Ark_Int32 resourceId, Ark_Boolean value)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnCheckboxChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(value);
    enqueueCallback(&_buffer);
}
void callManagedOnCheckboxChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Boolean value)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnCheckboxChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(value);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnCheckboxGroupChangeCallback(Ark_Int32 resourceId, Ark_CheckboxGroupResult value)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnCheckboxGroupChangeCallback);
    argsSerializer.writeInt32(resourceId);
    CheckboxGroupResult_serializer::write(argsSerializer, value);
    enqueueCallback(&_buffer);
}
void callManagedOnCheckboxGroupChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_CheckboxGroupResult value)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnCheckboxGroupChangeCallback);
    argsSerializer.writeInt32(resourceId);
    CheckboxGroupResult_serializer::write(argsSerializer, value);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnContentScrollCallback(Ark_Int32 resourceId, Ark_Number totalOffsetX, Ark_Number totalOffsetY)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnContentScrollCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(totalOffsetX);
    argsSerializer.writeNumber(totalOffsetY);
    enqueueCallback(&_buffer);
}
void callManagedOnContentScrollCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number totalOffsetX, Ark_Number totalOffsetY)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnContentScrollCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(totalOffsetX);
    argsSerializer.writeNumber(totalOffsetY);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnCreateMenuCallback(Ark_Int32 resourceId, Array_TextMenuItem menuItems, Callback_Array_TextMenuItem_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnCreateMenuCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(menuItems.length);
    for (int i = 0; i < menuItems.length; i++) {
        const Ark_TextMenuItem menuItems_element = menuItems.array[i];
        TextMenuItem_serializer::write(argsSerializer, menuItems_element);
    }
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedOnCreateMenuCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Array_TextMenuItem menuItems, Callback_Array_TextMenuItem_Void continuation)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnCreateMenuCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(menuItems.length);
    for (int i = 0; i < menuItems.length; i++) {
        const Ark_TextMenuItem menuItems_element = menuItems.array[i];
        TextMenuItem_serializer::write(argsSerializer, menuItems_element);
    }
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnDidChangeCallback(Ark_Int32 resourceId, Ark_TextRange rangeBefore, Ark_TextRange rangeAfter)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnDidChangeCallback);
    argsSerializer.writeInt32(resourceId);
    TextRange_serializer::write(argsSerializer, rangeBefore);
    TextRange_serializer::write(argsSerializer, rangeAfter);
    enqueueCallback(&_buffer);
}
void callManagedOnDidChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_TextRange rangeBefore, Ark_TextRange rangeAfter)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnDidChangeCallback);
    argsSerializer.writeInt32(resourceId);
    TextRange_serializer::write(argsSerializer, rangeBefore);
    TextRange_serializer::write(argsSerializer, rangeAfter);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnDragEventCallback(Ark_Int32 resourceId, Ark_DragEvent event, Opt_String extraParams)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnDragEventCallback);
    argsSerializer.writeInt32(resourceId);
    DragEvent_serializer::write(argsSerializer, event);
    Ark_Int32 extraParams_type = INTEROP_RUNTIME_UNDEFINED;
    extraParams_type = runtimeType(extraParams);
    argsSerializer.writeInt8(extraParams_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (extraParams_type)) {
        const auto extraParams_value = extraParams.value;
        argsSerializer.writeString(extraParams_value);
    }
    enqueueCallback(&_buffer);
}
void callManagedOnDragEventCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_DragEvent event, Opt_String extraParams)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnDragEventCallback);
    argsSerializer.writeInt32(resourceId);
    DragEvent_serializer::write(argsSerializer, event);
    Ark_Int32 extraParams_type = INTEROP_RUNTIME_UNDEFINED;
    extraParams_type = runtimeType(extraParams);
    argsSerializer.writeInt8(extraParams_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (extraParams_type)) {
        const auto extraParams_value = extraParams.value;
        argsSerializer.writeString(extraParams_value);
    }
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnFoldStatusChangeCallback(Ark_Int32 resourceId, Ark_OnFoldStatusChangeInfo event)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnFoldStatusChangeCallback);
    argsSerializer.writeInt32(resourceId);
    OnFoldStatusChangeInfo_serializer::write(argsSerializer, event);
    enqueueCallback(&_buffer);
}
void callManagedOnFoldStatusChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnFoldStatusChangeInfo event)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnFoldStatusChangeCallback);
    argsSerializer.writeInt32(resourceId);
    OnFoldStatusChangeInfo_serializer::write(argsSerializer, event);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnHoverCallback(Ark_Int32 resourceId, Ark_Boolean status, Ark_HoverEvent event)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnHoverCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(status);
    HoverEvent_serializer::write(argsSerializer, event);
    enqueueCallback(&_buffer);
}
void callManagedOnHoverCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Boolean status, Ark_HoverEvent event)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnHoverCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(status);
    HoverEvent_serializer::write(argsSerializer, event);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnHoverStatusChangeCallback(Ark_Int32 resourceId, Ark_HoverEventParam param)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnHoverStatusChangeCallback);
    argsSerializer.writeInt32(resourceId);
    HoverEventParam_serializer::write(argsSerializer, param);
    enqueueCallback(&_buffer);
}
void callManagedOnHoverStatusChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_HoverEventParam param)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnHoverStatusChangeCallback);
    argsSerializer.writeInt32(resourceId);
    HoverEventParam_serializer::write(argsSerializer, param);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnItemDragStartCallback(Ark_Int32 resourceId, Ark_ItemDragInfo event, Ark_Number itemIndex, Callback_Opt_CustomBuilder_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnItemDragStartCallback);
    argsSerializer.writeInt32(resourceId);
    ItemDragInfo_serializer::write(argsSerializer, event);
    argsSerializer.writeNumber(itemIndex);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedOnItemDragStartCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_ItemDragInfo event, Ark_Number itemIndex, Callback_Opt_CustomBuilder_Void continuation)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnItemDragStartCallback);
    argsSerializer.writeInt32(resourceId);
    ItemDragInfo_serializer::write(argsSerializer, event);
    argsSerializer.writeNumber(itemIndex);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnLinearIndicatorChangeCallback(Ark_Int32 resourceId, Ark_Number index, Ark_Number progress)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnLinearIndicatorChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(index);
    argsSerializer.writeNumber(progress);
    enqueueCallback(&_buffer);
}
void callManagedOnLinearIndicatorChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number index, Ark_Number progress)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnLinearIndicatorChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(index);
    argsSerializer.writeNumber(progress);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnMenuItemClickCallback(Ark_Int32 resourceId, Ark_TextMenuItem menuItem, Ark_TextRange range, Callback_Boolean_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnMenuItemClickCallback);
    argsSerializer.writeInt32(resourceId);
    TextMenuItem_serializer::write(argsSerializer, menuItem);
    TextRange_serializer::write(argsSerializer, range);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedOnMenuItemClickCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_TextMenuItem menuItem, Ark_TextRange range, Callback_Boolean_Void continuation)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnMenuItemClickCallback);
    argsSerializer.writeInt32(resourceId);
    TextMenuItem_serializer::write(argsSerializer, menuItem);
    TextRange_serializer::write(argsSerializer, range);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnMoveHandler(Ark_Int32 resourceId, Ark_Number from, Ark_Number to)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnMoveHandler);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(from);
    argsSerializer.writeNumber(to);
    enqueueCallback(&_buffer);
}
void callManagedOnMoveHandlerSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number from, Ark_Number to)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnMoveHandler);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(from);
    argsSerializer.writeNumber(to);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnNativeLoadCallback(Ark_Int32 resourceId, Opt_Object event)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnNativeLoadCallback);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 event_type = INTEROP_RUNTIME_UNDEFINED;
    event_type = runtimeType(event);
    argsSerializer.writeInt8(event_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (event_type)) {
        const auto event_value = event.value;
        argsSerializer.writeObject(event_value);
    }
    enqueueCallback(&_buffer);
}
void callManagedOnNativeLoadCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Opt_Object event)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnNativeLoadCallback);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 event_type = INTEROP_RUNTIME_UNDEFINED;
    event_type = runtimeType(event);
    argsSerializer.writeInt8(event_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (event_type)) {
        const auto event_value = event.value;
        argsSerializer.writeObject(event_value);
    }
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnPasteCallback(Ark_Int32 resourceId, Ark_String content, Ark_PasteEvent event)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnPasteCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(content);
    PasteEvent_serializer::write(argsSerializer, event);
    enqueueCallback(&_buffer);
}
void callManagedOnPasteCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_String content, Ark_PasteEvent event)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnPasteCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(content);
    PasteEvent_serializer::write(argsSerializer, event);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnRadioChangeCallback(Ark_Int32 resourceId, Ark_Boolean isChecked)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnRadioChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(isChecked);
    enqueueCallback(&_buffer);
}
void callManagedOnRadioChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Boolean isChecked)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnRadioChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(isChecked);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnRatingChangeCallback(Ark_Int32 resourceId, Ark_Number rating)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnRatingChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(rating);
    enqueueCallback(&_buffer);
}
void callManagedOnRatingChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number rating)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnRatingChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(rating);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnScrollCallback(Ark_Int32 resourceId, Ark_Number scrollOffset, Ark_ScrollState scrollState)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnScrollCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(scrollOffset);
    argsSerializer.writeInt32(static_cast<Ark_ScrollState>(scrollState));
    enqueueCallback(&_buffer);
}
void callManagedOnScrollCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number scrollOffset, Ark_ScrollState scrollState)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnScrollCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(scrollOffset);
    argsSerializer.writeInt32(static_cast<Ark_ScrollState>(scrollState));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnScrollEdgeCallback(Ark_Int32 resourceId, Ark_Edge side)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnScrollEdgeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_Edge>(side));
    enqueueCallback(&_buffer);
}
void callManagedOnScrollEdgeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Edge side)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnScrollEdgeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_Edge>(side));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnScrollFrameBeginCallback(Ark_Int32 resourceId, Ark_Number offset, Ark_ScrollState state, Callback_OnScrollFrameBeginHandlerResult_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnScrollFrameBeginCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(offset);
    argsSerializer.writeInt32(static_cast<Ark_ScrollState>(state));
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedOnScrollFrameBeginCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number offset, Ark_ScrollState state, Callback_OnScrollFrameBeginHandlerResult_Void continuation)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnScrollFrameBeginCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(offset);
    argsSerializer.writeInt32(static_cast<Ark_ScrollState>(state));
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnScrollVisibleContentChangeCallback(Ark_Int32 resourceId, Ark_VisibleListContentInfo start, Ark_VisibleListContentInfo end)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnScrollVisibleContentChangeCallback);
    argsSerializer.writeInt32(resourceId);
    VisibleListContentInfo_serializer::write(argsSerializer, start);
    VisibleListContentInfo_serializer::write(argsSerializer, end);
    enqueueCallback(&_buffer);
}
void callManagedOnScrollVisibleContentChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_VisibleListContentInfo start, Ark_VisibleListContentInfo end)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnScrollVisibleContentChangeCallback);
    argsSerializer.writeInt32(resourceId);
    VisibleListContentInfo_serializer::write(argsSerializer, start);
    VisibleListContentInfo_serializer::write(argsSerializer, end);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnSelectCallback(Ark_Int32 resourceId, Ark_Number index, Ark_String selectStr)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnSelectCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(index);
    argsSerializer.writeString(selectStr);
    enqueueCallback(&_buffer);
}
void callManagedOnSelectCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number index, Ark_String selectStr)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnSelectCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(index);
    argsSerializer.writeString(selectStr);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnSubmitCallback(Ark_Int32 resourceId, Ark_EnterKeyType enterKey, Ark_SubmitEvent event)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnSubmitCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_EnterKeyType>(enterKey));
    SubmitEvent_serializer::write(argsSerializer, event);
    enqueueCallback(&_buffer);
}
void callManagedOnSubmitCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_EnterKeyType enterKey, Ark_SubmitEvent event)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnSubmitCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_EnterKeyType>(enterKey));
    SubmitEvent_serializer::write(argsSerializer, event);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnSwiperAnimationEndCallback(Ark_Int32 resourceId, Ark_Number index, Ark_SwiperAnimationEvent extraInfo)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnSwiperAnimationEndCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(index);
    SwiperAnimationEvent_serializer::write(argsSerializer, extraInfo);
    enqueueCallback(&_buffer);
}
void callManagedOnSwiperAnimationEndCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number index, Ark_SwiperAnimationEvent extraInfo)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnSwiperAnimationEndCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(index);
    SwiperAnimationEvent_serializer::write(argsSerializer, extraInfo);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnSwiperAnimationStartCallback(Ark_Int32 resourceId, Ark_Number index, Ark_Number targetIndex, Ark_SwiperAnimationEvent extraInfo)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnSwiperAnimationStartCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(index);
    argsSerializer.writeNumber(targetIndex);
    SwiperAnimationEvent_serializer::write(argsSerializer, extraInfo);
    enqueueCallback(&_buffer);
}
void callManagedOnSwiperAnimationStartCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number index, Ark_Number targetIndex, Ark_SwiperAnimationEvent extraInfo)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnSwiperAnimationStartCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(index);
    argsSerializer.writeNumber(targetIndex);
    SwiperAnimationEvent_serializer::write(argsSerializer, extraInfo);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnSwiperGestureSwipeCallback(Ark_Int32 resourceId, Ark_Number index, Ark_SwiperAnimationEvent extraInfo)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnSwiperGestureSwipeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(index);
    SwiperAnimationEvent_serializer::write(argsSerializer, extraInfo);
    enqueueCallback(&_buffer);
}
void callManagedOnSwiperGestureSwipeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number index, Ark_SwiperAnimationEvent extraInfo)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnSwiperGestureSwipeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(index);
    SwiperAnimationEvent_serializer::write(argsSerializer, extraInfo);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnTabsAnimationEndCallback(Ark_Int32 resourceId, Ark_Number index, Ark_TabsAnimationEvent extraInfo)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnTabsAnimationEndCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(index);
    TabsAnimationEvent_serializer::write(argsSerializer, extraInfo);
    enqueueCallback(&_buffer);
}
void callManagedOnTabsAnimationEndCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number index, Ark_TabsAnimationEvent extraInfo)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnTabsAnimationEndCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(index);
    TabsAnimationEvent_serializer::write(argsSerializer, extraInfo);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnTabsAnimationStartCallback(Ark_Int32 resourceId, Ark_Number index, Ark_Number targetIndex, Ark_TabsAnimationEvent extraInfo)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnTabsAnimationStartCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(index);
    argsSerializer.writeNumber(targetIndex);
    TabsAnimationEvent_serializer::write(argsSerializer, extraInfo);
    enqueueCallback(&_buffer);
}
void callManagedOnTabsAnimationStartCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number index, Ark_Number targetIndex, Ark_TabsAnimationEvent extraInfo)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnTabsAnimationStartCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(index);
    argsSerializer.writeNumber(targetIndex);
    TabsAnimationEvent_serializer::write(argsSerializer, extraInfo);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnTabsContentWillChangeCallback(Ark_Int32 resourceId, Ark_Number currentIndex, Ark_Number comingIndex, Callback_Boolean_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnTabsContentWillChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(currentIndex);
    argsSerializer.writeNumber(comingIndex);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedOnTabsContentWillChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number currentIndex, Ark_Number comingIndex, Callback_Boolean_Void continuation)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnTabsContentWillChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(currentIndex);
    argsSerializer.writeNumber(comingIndex);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnTabsGestureSwipeCallback(Ark_Int32 resourceId, Ark_Number index, Ark_TabsAnimationEvent extraInfo)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnTabsGestureSwipeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(index);
    TabsAnimationEvent_serializer::write(argsSerializer, extraInfo);
    enqueueCallback(&_buffer);
}
void callManagedOnTabsGestureSwipeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number index, Ark_TabsAnimationEvent extraInfo)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnTabsGestureSwipeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(index);
    TabsAnimationEvent_serializer::write(argsSerializer, extraInfo);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnTextPickerChangeCallback(Ark_Int32 resourceId, Ark_Union_String_Array_String selectItem, Ark_Union_Number_Array_Number index)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnTextPickerChangeCallback);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 selectItem_type = INTEROP_RUNTIME_UNDEFINED;
    selectItem_type = selectItem.selector;
    if (selectItem_type == 0) {
        argsSerializer.writeInt8(0);
        const auto selectItem_0 = selectItem.value0;
        argsSerializer.writeString(selectItem_0);
    }
    else if (selectItem_type == 1) {
        argsSerializer.writeInt8(1);
        const auto selectItem_1 = selectItem.value1;
        argsSerializer.writeInt32(selectItem_1.length);
        for (int i = 0; i < selectItem_1.length; i++) {
            const Ark_String selectItem_1_element = selectItem_1.array[i];
            argsSerializer.writeString(selectItem_1_element);
        }
    }
    Ark_Int32 index_type = INTEROP_RUNTIME_UNDEFINED;
    index_type = index.selector;
    if (index_type == 0) {
        argsSerializer.writeInt8(0);
        const auto index_0 = index.value0;
        argsSerializer.writeNumber(index_0);
    }
    else if (index_type == 1) {
        argsSerializer.writeInt8(1);
        const auto index_1 = index.value1;
        argsSerializer.writeInt32(index_1.length);
        for (int i = 0; i < index_1.length; i++) {
            const Ark_Number index_1_element = index_1.array[i];
            argsSerializer.writeNumber(index_1_element);
        }
    }
    enqueueCallback(&_buffer);
}
void callManagedOnTextPickerChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Union_String_Array_String selectItem, Ark_Union_Number_Array_Number index)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnTextPickerChangeCallback);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 selectItem_type = INTEROP_RUNTIME_UNDEFINED;
    selectItem_type = selectItem.selector;
    if (selectItem_type == 0) {
        argsSerializer.writeInt8(0);
        const auto selectItem_0 = selectItem.value0;
        argsSerializer.writeString(selectItem_0);
    }
    else if (selectItem_type == 1) {
        argsSerializer.writeInt8(1);
        const auto selectItem_1 = selectItem.value1;
        argsSerializer.writeInt32(selectItem_1.length);
        for (int i = 0; i < selectItem_1.length; i++) {
            const Ark_String selectItem_1_element = selectItem_1.array[i];
            argsSerializer.writeString(selectItem_1_element);
        }
    }
    Ark_Int32 index_type = INTEROP_RUNTIME_UNDEFINED;
    index_type = index.selector;
    if (index_type == 0) {
        argsSerializer.writeInt8(0);
        const auto index_0 = index.value0;
        argsSerializer.writeNumber(index_0);
    }
    else if (index_type == 1) {
        argsSerializer.writeInt8(1);
        const auto index_1 = index.value1;
        argsSerializer.writeInt32(index_1.length);
        for (int i = 0; i < index_1.length; i++) {
            const Ark_Number index_1_element = index_1.array[i];
            argsSerializer.writeNumber(index_1_element);
        }
    }
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnTextSelectionChangeCallback(Ark_Int32 resourceId, Ark_Number selectionStart, Ark_Number selectionEnd)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnTextSelectionChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(selectionStart);
    argsSerializer.writeNumber(selectionEnd);
    enqueueCallback(&_buffer);
}
void callManagedOnTextSelectionChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number selectionStart, Ark_Number selectionEnd)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnTextSelectionChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(selectionStart);
    argsSerializer.writeNumber(selectionEnd);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnTimePickerChangeCallback(Ark_Int32 resourceId, Ark_TimePickerResult result)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnTimePickerChangeCallback);
    argsSerializer.writeInt32(resourceId);
    TimePickerResult_serializer::write(argsSerializer, result);
    enqueueCallback(&_buffer);
}
void callManagedOnTimePickerChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_TimePickerResult result)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnTimePickerChangeCallback);
    argsSerializer.writeInt32(resourceId);
    TimePickerResult_serializer::write(argsSerializer, result);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnWillScrollCallback(Ark_Int32 resourceId, Ark_Number scrollOffset, Ark_ScrollState scrollState, Ark_ScrollSource scrollSource, Callback_Opt_ScrollResult_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnWillScrollCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(scrollOffset);
    argsSerializer.writeInt32(static_cast<Ark_ScrollState>(scrollState));
    argsSerializer.writeInt32(static_cast<Ark_ScrollSource>(scrollSource));
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedOnWillScrollCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number scrollOffset, Ark_ScrollState scrollState, Ark_ScrollSource scrollSource, Callback_Opt_ScrollResult_Void continuation)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnWillScrollCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(scrollOffset);
    argsSerializer.writeInt32(static_cast<Ark_ScrollState>(scrollState));
    argsSerializer.writeInt32(static_cast<Ark_ScrollSource>(scrollSource));
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedPageMapBuilder(Ark_Int32 resourceId, Ark_String name, Opt_Object param)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_PageMapBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(name);
    Ark_Int32 param_type = INTEROP_RUNTIME_UNDEFINED;
    param_type = runtimeType(param);
    argsSerializer.writeInt8(param_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (param_type)) {
        const auto param_value = param.value;
        argsSerializer.writeObject(param_value);
    }
    enqueueCallback(&_buffer);
}
void callManagedPageMapBuilderSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_String name, Opt_Object param)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_PageMapBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(name);
    Ark_Int32 param_type = INTEROP_RUNTIME_UNDEFINED;
    param_type = runtimeType(param);
    argsSerializer.writeInt8(param_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (param_type)) {
        const auto param_value = param.value;
        argsSerializer.writeObject(param_value);
    }
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedPageTransitionCallback(Ark_Int32 resourceId, Ark_RouteType type, Ark_Number progress)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_PageTransitionCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_RouteType>(type));
    argsSerializer.writeNumber(progress);
    enqueueCallback(&_buffer);
}
void callManagedPageTransitionCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_RouteType type, Ark_Number progress)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_PageTransitionCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_RouteType>(type));
    argsSerializer.writeNumber(progress);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedPasteButtonCallback(Ark_Int32 resourceId, Ark_ClickEvent event, Ark_PasteButtonOnClickResult result, Opt_BusinessError error)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_PasteButtonCallback);
    argsSerializer.writeInt32(resourceId);
    ClickEvent_serializer::write(argsSerializer, event);
    argsSerializer.writeInt32(static_cast<Ark_PasteButtonOnClickResult>(result));
    Ark_Int32 error_type = INTEROP_RUNTIME_UNDEFINED;
    error_type = runtimeType(error);
    argsSerializer.writeInt8(error_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (error_type)) {
        const auto error_value = error.value;
        BusinessError_serializer::write(argsSerializer, error_value);
    }
    enqueueCallback(&_buffer);
}
void callManagedPasteButtonCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_ClickEvent event, Ark_PasteButtonOnClickResult result, Opt_BusinessError error)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_PasteButtonCallback);
    argsSerializer.writeInt32(resourceId);
    ClickEvent_serializer::write(argsSerializer, event);
    argsSerializer.writeInt32(static_cast<Ark_PasteButtonOnClickResult>(result));
    Ark_Int32 error_type = INTEROP_RUNTIME_UNDEFINED;
    error_type = runtimeType(error);
    argsSerializer.writeInt8(error_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (error_type)) {
        const auto error_value = error.value;
        BusinessError_serializer::write(argsSerializer, error_value);
    }
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedPasteEventCallback(Ark_Int32 resourceId, Opt_PasteEvent event)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_PasteEventCallback);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 event_type = INTEROP_RUNTIME_UNDEFINED;
    event_type = runtimeType(event);
    argsSerializer.writeInt8(event_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (event_type)) {
        const auto event_value = event.value;
        PasteEvent_serializer::write(argsSerializer, event_value);
    }
    enqueueCallback(&_buffer);
}
void callManagedPasteEventCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Opt_PasteEvent event)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_PasteEventCallback);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 event_type = INTEROP_RUNTIME_UNDEFINED;
    event_type = runtimeType(event);
    argsSerializer.writeInt8(event_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (event_type)) {
        const auto event_value = event.value;
        PasteEvent_serializer::write(argsSerializer, event_value);
    }
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedPluginErrorCallback(Ark_Int32 resourceId, Ark_PluginErrorData info)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_PluginErrorCallback);
    argsSerializer.writeInt32(resourceId);
    PluginErrorData_serializer::write(argsSerializer, info);
    enqueueCallback(&_buffer);
}
void callManagedPluginErrorCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_PluginErrorData info)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_PluginErrorCallback);
    argsSerializer.writeInt32(resourceId);
    PluginErrorData_serializer::write(argsSerializer, info);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedPopupStateChangeCallback(Ark_Int32 resourceId, Ark_PopupStateChangeParam event)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_PopupStateChangeCallback);
    argsSerializer.writeInt32(resourceId);
    PopupStateChangeParam_serializer::write(argsSerializer, event);
    enqueueCallback(&_buffer);
}
void callManagedPopupStateChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_PopupStateChangeParam event)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_PopupStateChangeCallback);
    argsSerializer.writeInt32(resourceId);
    PopupStateChangeParam_serializer::write(argsSerializer, event);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedProgressModifierBuilder(Ark_Int32 resourceId, Ark_NativePointer parentNode, Ark_ProgressConfiguration config, Callback_Pointer_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_ProgressModifierBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    ProgressConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedProgressModifierBuilderSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NativePointer parentNode, Ark_ProgressConfiguration config, Callback_Pointer_Void continuation)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_ProgressModifierBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    ProgressConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedRadioModifierBuilder(Ark_Int32 resourceId, Ark_NativePointer parentNode, Ark_RadioConfiguration config, Callback_Pointer_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_RadioModifierBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    RadioConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedRadioModifierBuilderSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NativePointer parentNode, Ark_RadioConfiguration config, Callback_Pointer_Void continuation)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_RadioModifierBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    RadioConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedRatingModifierBuilder(Ark_Int32 resourceId, Ark_NativePointer parentNode, Ark_RatingConfiguration config, Callback_Pointer_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_RatingModifierBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    RatingConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedRatingModifierBuilderSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NativePointer parentNode, Ark_RatingConfiguration config, Callback_Pointer_Void continuation)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_RatingModifierBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    RatingConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedRestrictedWorker_onerror_Callback(Ark_Int32 resourceId, Ark_ErrorEvent ev)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_RestrictedWorker_onerror_Callback);
    argsSerializer.writeInt32(resourceId);
    ErrorEvent_serializer::write(argsSerializer, ev);
    enqueueCallback(&_buffer);
}
void callManagedRestrictedWorker_onerror_CallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_ErrorEvent ev)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_RestrictedWorker_onerror_Callback);
    argsSerializer.writeInt32(resourceId);
    ErrorEvent_serializer::write(argsSerializer, ev);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedRestrictedWorker_onexit_Callback(Ark_Int32 resourceId, Ark_Number code)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_RestrictedWorker_onexit_Callback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(code);
    enqueueCallback(&_buffer);
}
void callManagedRestrictedWorker_onexit_CallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number code)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_RestrictedWorker_onexit_Callback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(code);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedRestrictedWorker_onmessage_Callback(Ark_Int32 resourceId, Ark_MessageEvents event)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_RestrictedWorker_onmessage_Callback);
    argsSerializer.writeInt32(resourceId);
    MessageEvents_serializer::write(argsSerializer, event);
    enqueueCallback(&_buffer);
}
void callManagedRestrictedWorker_onmessage_CallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_MessageEvents event)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_RestrictedWorker_onmessage_Callback);
    argsSerializer.writeInt32(resourceId);
    MessageEvents_serializer::write(argsSerializer, event);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedReuseIdCallback(Ark_Int32 resourceId, Callback_String_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_ReuseIdCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedReuseIdCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Callback_String_Void continuation)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_ReuseIdCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedSaveButtonCallback(Ark_Int32 resourceId, Ark_ClickEvent event, Ark_SaveButtonOnClickResult result, Opt_BusinessError error)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_SaveButtonCallback);
    argsSerializer.writeInt32(resourceId);
    ClickEvent_serializer::write(argsSerializer, event);
    argsSerializer.writeInt32(static_cast<Ark_SaveButtonOnClickResult>(result));
    Ark_Int32 error_type = INTEROP_RUNTIME_UNDEFINED;
    error_type = runtimeType(error);
    argsSerializer.writeInt8(error_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (error_type)) {
        const auto error_value = error.value;
        BusinessError_serializer::write(argsSerializer, error_value);
    }
    enqueueCallback(&_buffer);
}
void callManagedSaveButtonCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_ClickEvent event, Ark_SaveButtonOnClickResult result, Opt_BusinessError error)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_SaveButtonCallback);
    argsSerializer.writeInt32(resourceId);
    ClickEvent_serializer::write(argsSerializer, event);
    argsSerializer.writeInt32(static_cast<Ark_SaveButtonOnClickResult>(result));
    Ark_Int32 error_type = INTEROP_RUNTIME_UNDEFINED;
    error_type = runtimeType(error);
    argsSerializer.writeInt8(error_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (error_type)) {
        const auto error_value = error.value;
        BusinessError_serializer::write(argsSerializer, error_value);
    }
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedScrollOnScrollCallback(Ark_Int32 resourceId, Ark_Number xOffset, Ark_Number yOffset, Ark_ScrollState scrollState)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_ScrollOnScrollCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(xOffset);
    argsSerializer.writeNumber(yOffset);
    argsSerializer.writeInt32(static_cast<Ark_ScrollState>(scrollState));
    enqueueCallback(&_buffer);
}
void callManagedScrollOnScrollCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number xOffset, Ark_Number yOffset, Ark_ScrollState scrollState)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_ScrollOnScrollCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(xOffset);
    argsSerializer.writeNumber(yOffset);
    argsSerializer.writeInt32(static_cast<Ark_ScrollState>(scrollState));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedScrollOnWillScrollCallback(Ark_Int32 resourceId, Ark_Number xOffset, Ark_Number yOffset, Ark_ScrollState scrollState, Ark_ScrollSource scrollSource, Callback_Opt_OffsetResult_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_ScrollOnWillScrollCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(xOffset);
    argsSerializer.writeNumber(yOffset);
    argsSerializer.writeInt32(static_cast<Ark_ScrollState>(scrollState));
    argsSerializer.writeInt32(static_cast<Ark_ScrollSource>(scrollSource));
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedScrollOnWillScrollCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number xOffset, Ark_Number yOffset, Ark_ScrollState scrollState, Ark_ScrollSource scrollSource, Callback_Opt_OffsetResult_Void continuation)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_ScrollOnWillScrollCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(xOffset);
    argsSerializer.writeNumber(yOffset);
    argsSerializer.writeInt32(static_cast<Ark_ScrollState>(scrollState));
    argsSerializer.writeInt32(static_cast<Ark_ScrollSource>(scrollSource));
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedSearchSubmitCallback(Ark_Int32 resourceId, Ark_String searchContent, Opt_SubmitEvent event)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_SearchSubmitCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(searchContent);
    Ark_Int32 event_type = INTEROP_RUNTIME_UNDEFINED;
    event_type = runtimeType(event);
    argsSerializer.writeInt8(event_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (event_type)) {
        const auto event_value = event.value;
        SubmitEvent_serializer::write(argsSerializer, event_value);
    }
    enqueueCallback(&_buffer);
}
void callManagedSearchSubmitCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_String searchContent, Opt_SubmitEvent event)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_SearchSubmitCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(searchContent);
    Ark_Int32 event_type = INTEROP_RUNTIME_UNDEFINED;
    event_type = runtimeType(event);
    argsSerializer.writeInt8(event_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (event_type)) {
        const auto event_value = event.value;
        SubmitEvent_serializer::write(argsSerializer, event_value);
    }
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedSearchValueCallback(Ark_Int32 resourceId, Ark_String value)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_SearchValueCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(value);
    enqueueCallback(&_buffer);
}
void callManagedSearchValueCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_String value)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_SearchValueCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(value);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedShouldBuiltInRecognizerParallelWithCallback(Ark_Int32 resourceId, Ark_GestureRecognizer current, Array_GestureRecognizer others, Callback_GestureRecognizer_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_ShouldBuiltInRecognizerParallelWithCallback);
    argsSerializer.writeInt32(resourceId);
    GestureRecognizer_serializer::write(argsSerializer, current);
    argsSerializer.writeInt32(others.length);
    for (int i = 0; i < others.length; i++) {
        const Ark_GestureRecognizer others_element = others.array[i];
        GestureRecognizer_serializer::write(argsSerializer, others_element);
    }
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedShouldBuiltInRecognizerParallelWithCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_GestureRecognizer current, Array_GestureRecognizer others, Callback_GestureRecognizer_Void continuation)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_ShouldBuiltInRecognizerParallelWithCallback);
    argsSerializer.writeInt32(resourceId);
    GestureRecognizer_serializer::write(argsSerializer, current);
    argsSerializer.writeInt32(others.length);
    for (int i = 0; i < others.length; i++) {
        const Ark_GestureRecognizer others_element = others.array[i];
        GestureRecognizer_serializer::write(argsSerializer, others_element);
    }
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedSizeChangeCallback(Ark_Int32 resourceId, Ark_SizeOptions oldValue, Ark_SizeOptions newValue)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_SizeChangeCallback);
    argsSerializer.writeInt32(resourceId);
    SizeOptions_serializer::write(argsSerializer, oldValue);
    SizeOptions_serializer::write(argsSerializer, newValue);
    enqueueCallback(&_buffer);
}
void callManagedSizeChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_SizeOptions oldValue, Ark_SizeOptions newValue)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_SizeChangeCallback);
    argsSerializer.writeInt32(resourceId);
    SizeOptions_serializer::write(argsSerializer, oldValue);
    SizeOptions_serializer::write(argsSerializer, newValue);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedSliderModifierBuilder(Ark_Int32 resourceId, Ark_NativePointer parentNode, Ark_SliderConfiguration config, Callback_Pointer_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_SliderModifierBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    SliderConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedSliderModifierBuilderSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NativePointer parentNode, Ark_SliderConfiguration config, Callback_Pointer_Void continuation)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_SliderModifierBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    SliderConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedSliderTriggerChangeCallback(Ark_Int32 resourceId, Ark_Number value, Ark_SliderChangeMode mode)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_SliderTriggerChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(value);
    argsSerializer.writeInt32(static_cast<Ark_SliderChangeMode>(mode));
    enqueueCallback(&_buffer);
}
void callManagedSliderTriggerChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number value, Ark_SliderChangeMode mode)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_SliderTriggerChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(value);
    argsSerializer.writeInt32(static_cast<Ark_SliderChangeMode>(mode));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedStyledStringMarshallCallback(Ark_Int32 resourceId, Ark_UserDataSpan marshallableVal, Callback_Buffer_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_StyledStringMarshallCallback);
    argsSerializer.writeInt32(resourceId);
    UserDataSpan_serializer::write(argsSerializer, marshallableVal);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedStyledStringMarshallCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_UserDataSpan marshallableVal, Callback_Buffer_Void continuation)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_StyledStringMarshallCallback);
    argsSerializer.writeInt32(resourceId);
    UserDataSpan_serializer::write(argsSerializer, marshallableVal);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedStyledStringUnmarshallCallback(Ark_Int32 resourceId, Ark_Buffer buf, Callback_StyledStringMarshallingValue_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_StyledStringUnmarshallCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBuffer(buf);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedStyledStringUnmarshallCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Buffer buf, Callback_StyledStringMarshallingValue_Void continuation)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_StyledStringUnmarshallCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBuffer(buf);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedSubmitCallback(Ark_Int32 resourceId, Ark_EnterKeyType enterKey, Ark_SubmitEvent event)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_SubmitCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_EnterKeyType>(enterKey));
    SubmitEvent_serializer::write(argsSerializer, event);
    enqueueCallback(&_buffer);
}
void callManagedSubmitCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_EnterKeyType enterKey, Ark_SubmitEvent event)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_SubmitCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_EnterKeyType>(enterKey));
    SubmitEvent_serializer::write(argsSerializer, event);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedTabsCustomContentTransitionCallback(Ark_Int32 resourceId, Ark_Number from, Ark_Number to, Callback_Opt_TabContentAnimatedTransition_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_TabsCustomContentTransitionCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(from);
    argsSerializer.writeNumber(to);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedTabsCustomContentTransitionCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number from, Ark_Number to, Callback_Opt_TabContentAnimatedTransition_Void continuation)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_TabsCustomContentTransitionCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(from);
    argsSerializer.writeNumber(to);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedTextAreaSubmitCallback(Ark_Int32 resourceId, Ark_EnterKeyType enterKeyType, Opt_SubmitEvent event)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_TextAreaSubmitCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_EnterKeyType>(enterKeyType));
    Ark_Int32 event_type = INTEROP_RUNTIME_UNDEFINED;
    event_type = runtimeType(event);
    argsSerializer.writeInt8(event_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (event_type)) {
        const auto event_value = event.value;
        SubmitEvent_serializer::write(argsSerializer, event_value);
    }
    enqueueCallback(&_buffer);
}
void callManagedTextAreaSubmitCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_EnterKeyType enterKeyType, Opt_SubmitEvent event)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_TextAreaSubmitCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_EnterKeyType>(enterKeyType));
    Ark_Int32 event_type = INTEROP_RUNTIME_UNDEFINED;
    event_type = runtimeType(event);
    argsSerializer.writeInt8(event_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (event_type)) {
        const auto event_value = event.value;
        SubmitEvent_serializer::write(argsSerializer, event_value);
    }
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedTextClockModifierBuilder(Ark_Int32 resourceId, Ark_NativePointer parentNode, Ark_TextClockConfiguration config, Callback_Pointer_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_TextClockModifierBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    TextClockConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedTextClockModifierBuilderSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NativePointer parentNode, Ark_TextClockConfiguration config, Callback_Pointer_Void continuation)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_TextClockModifierBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    TextClockConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedTextFieldValueCallback(Ark_Int32 resourceId, Ark_ResourceStr value)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_TextFieldValueCallback);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 value_type = INTEROP_RUNTIME_UNDEFINED;
    value_type = value.selector;
    if (value_type == 0) {
        argsSerializer.writeInt8(0);
        const auto value_0 = value.value0;
        argsSerializer.writeString(value_0);
    }
    else if (value_type == 1) {
        argsSerializer.writeInt8(1);
        const auto value_1 = value.value1;
        Resource_serializer::write(argsSerializer, value_1);
    }
    enqueueCallback(&_buffer);
}
void callManagedTextFieldValueCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_ResourceStr value)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_TextFieldValueCallback);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 value_type = INTEROP_RUNTIME_UNDEFINED;
    value_type = value.selector;
    if (value_type == 0) {
        argsSerializer.writeInt8(0);
        const auto value_0 = value.value0;
        argsSerializer.writeString(value_0);
    }
    else if (value_type == 1) {
        argsSerializer.writeInt8(1);
        const auto value_1 = value.value1;
        Resource_serializer::write(argsSerializer, value_1);
    }
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedTextPickerEnterSelectedAreaCallback(Ark_Int32 resourceId, Ark_Union_String_Array_String value, Ark_Union_Number_Array_Number index)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_TextPickerEnterSelectedAreaCallback);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 value_type = INTEROP_RUNTIME_UNDEFINED;
    value_type = value.selector;
    if (value_type == 0) {
        argsSerializer.writeInt8(0);
        const auto value_0 = value.value0;
        argsSerializer.writeString(value_0);
    }
    else if (value_type == 1) {
        argsSerializer.writeInt8(1);
        const auto value_1 = value.value1;
        argsSerializer.writeInt32(value_1.length);
        for (int i = 0; i < value_1.length; i++) {
            const Ark_String value_1_element = value_1.array[i];
            argsSerializer.writeString(value_1_element);
        }
    }
    Ark_Int32 index_type = INTEROP_RUNTIME_UNDEFINED;
    index_type = index.selector;
    if (index_type == 0) {
        argsSerializer.writeInt8(0);
        const auto index_0 = index.value0;
        argsSerializer.writeNumber(index_0);
    }
    else if (index_type == 1) {
        argsSerializer.writeInt8(1);
        const auto index_1 = index.value1;
        argsSerializer.writeInt32(index_1.length);
        for (int i = 0; i < index_1.length; i++) {
            const Ark_Number index_1_element = index_1.array[i];
            argsSerializer.writeNumber(index_1_element);
        }
    }
    enqueueCallback(&_buffer);
}
void callManagedTextPickerEnterSelectedAreaCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Union_String_Array_String value, Ark_Union_Number_Array_Number index)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_TextPickerEnterSelectedAreaCallback);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 value_type = INTEROP_RUNTIME_UNDEFINED;
    value_type = value.selector;
    if (value_type == 0) {
        argsSerializer.writeInt8(0);
        const auto value_0 = value.value0;
        argsSerializer.writeString(value_0);
    }
    else if (value_type == 1) {
        argsSerializer.writeInt8(1);
        const auto value_1 = value.value1;
        argsSerializer.writeInt32(value_1.length);
        for (int i = 0; i < value_1.length; i++) {
            const Ark_String value_1_element = value_1.array[i];
            argsSerializer.writeString(value_1_element);
        }
    }
    Ark_Int32 index_type = INTEROP_RUNTIME_UNDEFINED;
    index_type = index.selector;
    if (index_type == 0) {
        argsSerializer.writeInt8(0);
        const auto index_0 = index.value0;
        argsSerializer.writeNumber(index_0);
    }
    else if (index_type == 1) {
        argsSerializer.writeInt8(1);
        const auto index_1 = index.value1;
        argsSerializer.writeInt32(index_1.length);
        for (int i = 0; i < index_1.length; i++) {
            const Ark_Number index_1_element = index_1.array[i];
            argsSerializer.writeNumber(index_1_element);
        }
    }
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedTextPickerScrollStopCallback(Ark_Int32 resourceId, Ark_Union_String_Array_String value, Ark_Union_Number_Array_Number index)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_TextPickerScrollStopCallback);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 value_type = INTEROP_RUNTIME_UNDEFINED;
    value_type = value.selector;
    if (value_type == 0) {
        argsSerializer.writeInt8(0);
        const auto value_0 = value.value0;
        argsSerializer.writeString(value_0);
    }
    else if (value_type == 1) {
        argsSerializer.writeInt8(1);
        const auto value_1 = value.value1;
        argsSerializer.writeInt32(value_1.length);
        for (int i = 0; i < value_1.length; i++) {
            const Ark_String value_1_element = value_1.array[i];
            argsSerializer.writeString(value_1_element);
        }
    }
    Ark_Int32 index_type = INTEROP_RUNTIME_UNDEFINED;
    index_type = index.selector;
    if (index_type == 0) {
        argsSerializer.writeInt8(0);
        const auto index_0 = index.value0;
        argsSerializer.writeNumber(index_0);
    }
    else if (index_type == 1) {
        argsSerializer.writeInt8(1);
        const auto index_1 = index.value1;
        argsSerializer.writeInt32(index_1.length);
        for (int i = 0; i < index_1.length; i++) {
            const Ark_Number index_1_element = index_1.array[i];
            argsSerializer.writeNumber(index_1_element);
        }
    }
    enqueueCallback(&_buffer);
}
void callManagedTextPickerScrollStopCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Union_String_Array_String value, Ark_Union_Number_Array_Number index)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_TextPickerScrollStopCallback);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 value_type = INTEROP_RUNTIME_UNDEFINED;
    value_type = value.selector;
    if (value_type == 0) {
        argsSerializer.writeInt8(0);
        const auto value_0 = value.value0;
        argsSerializer.writeString(value_0);
    }
    else if (value_type == 1) {
        argsSerializer.writeInt8(1);
        const auto value_1 = value.value1;
        argsSerializer.writeInt32(value_1.length);
        for (int i = 0; i < value_1.length; i++) {
            const Ark_String value_1_element = value_1.array[i];
            argsSerializer.writeString(value_1_element);
        }
    }
    Ark_Int32 index_type = INTEROP_RUNTIME_UNDEFINED;
    index_type = index.selector;
    if (index_type == 0) {
        argsSerializer.writeInt8(0);
        const auto index_0 = index.value0;
        argsSerializer.writeNumber(index_0);
    }
    else if (index_type == 1) {
        argsSerializer.writeInt8(1);
        const auto index_1 = index.value1;
        argsSerializer.writeInt32(index_1.length);
        for (int i = 0; i < index_1.length; i++) {
            const Ark_Number index_1_element = index_1.array[i];
            argsSerializer.writeNumber(index_1_element);
        }
    }
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedTextTimerModifierBuilder(Ark_Int32 resourceId, Ark_NativePointer parentNode, Ark_TextTimerConfiguration config, Callback_Pointer_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_TextTimerModifierBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    TextTimerConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedTextTimerModifierBuilderSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NativePointer parentNode, Ark_TextTimerConfiguration config, Callback_Pointer_Void continuation)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_TextTimerModifierBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    TextTimerConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedToggleModifierBuilder(Ark_Int32 resourceId, Ark_NativePointer parentNode, Ark_ToggleConfiguration config, Callback_Pointer_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_ToggleModifierBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    ToggleConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedToggleModifierBuilderSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NativePointer parentNode, Ark_ToggleConfiguration config, Callback_Pointer_Void continuation)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_ToggleModifierBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    ToggleConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedTransitionFinishCallback(Ark_Int32 resourceId, Ark_Boolean transitionIn)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_TransitionFinishCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(transitionIn);
    enqueueCallback(&_buffer);
}
void callManagedTransitionFinishCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Boolean transitionIn)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_TransitionFinishCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(transitionIn);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedType_CommonMethod_onDragStart(Ark_Int32 resourceId, Ark_DragEvent event, Opt_String extraParams, Callback_Union_CustomBuilder_DragItemInfo_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Type_CommonMethod_onDragStart);
    argsSerializer.writeInt32(resourceId);
    DragEvent_serializer::write(argsSerializer, event);
    Ark_Int32 extraParams_type = INTEROP_RUNTIME_UNDEFINED;
    extraParams_type = runtimeType(extraParams);
    argsSerializer.writeInt8(extraParams_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (extraParams_type)) {
        const auto extraParams_value = extraParams.value;
        argsSerializer.writeString(extraParams_value);
    }
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedType_CommonMethod_onDragStartSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_DragEvent event, Opt_String extraParams, Callback_Union_CustomBuilder_DragItemInfo_Void continuation)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Type_CommonMethod_onDragStart);
    argsSerializer.writeInt32(resourceId);
    DragEvent_serializer::write(argsSerializer, event);
    Ark_Int32 extraParams_type = INTEROP_RUNTIME_UNDEFINED;
    extraParams_type = runtimeType(extraParams);
    argsSerializer.writeInt8(extraParams_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (extraParams_type)) {
        const auto extraParams_value = extraParams.value;
        argsSerializer.writeString(extraParams_value);
    }
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedType_NavigationAttribute_customNavContentTransition(Ark_Int32 resourceId, Ark_NavContentInfo from, Ark_NavContentInfo to, Ark_NavigationOperation operation, Callback_Opt_NavigationAnimatedTransition_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Type_NavigationAttribute_customNavContentTransition);
    argsSerializer.writeInt32(resourceId);
    NavContentInfo_serializer::write(argsSerializer, from);
    NavContentInfo_serializer::write(argsSerializer, to);
    argsSerializer.writeInt32(static_cast<Ark_NavigationOperation>(operation));
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedType_NavigationAttribute_customNavContentTransitionSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NavContentInfo from, Ark_NavContentInfo to, Ark_NavigationOperation operation, Callback_Opt_NavigationAnimatedTransition_Void continuation)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Type_NavigationAttribute_customNavContentTransition);
    argsSerializer.writeInt32(resourceId);
    NavContentInfo_serializer::write(argsSerializer, from);
    NavContentInfo_serializer::write(argsSerializer, to);
    argsSerializer.writeInt32(static_cast<Ark_NavigationOperation>(operation));
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedUpdateTransitionCallback(Ark_Int32 resourceId, Ark_Number progress)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_UpdateTransitionCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(progress);
    enqueueCallback(&_buffer);
}
void callManagedUpdateTransitionCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number progress)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_UpdateTransitionCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(progress);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedVisibleAreaChangeCallback(Ark_Int32 resourceId, Ark_Boolean isExpanding, Ark_Number currentRatio)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_VisibleAreaChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(isExpanding);
    argsSerializer.writeNumber(currentRatio);
    enqueueCallback(&_buffer);
}
void callManagedVisibleAreaChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Boolean isExpanding, Ark_Number currentRatio)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_VisibleAreaChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(isExpanding);
    argsSerializer.writeNumber(currentRatio);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedVoidCallback(Ark_Int32 resourceId)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_VoidCallback);
    argsSerializer.writeInt32(resourceId);
    enqueueCallback(&_buffer);
}
void callManagedVoidCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId)
{
    uint8_t _buffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_VoidCallback);
    argsSerializer.writeInt32(resourceId);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
Ark_NativePointer getManagedCallbackCaller(CallbackKind kind)
{
    switch (kind) {
        case Kind_AccessibilityCallback: return reinterpret_cast<Ark_NativePointer>(callManagedAccessibilityCallback);
        case Kind_AccessibilityFocusCallback: return reinterpret_cast<Ark_NativePointer>(callManagedAccessibilityFocusCallback);
        case Kind_AsyncCallback_image_PixelMap_Void: return reinterpret_cast<Ark_NativePointer>(callManagedAsyncCallback_image_PixelMap_Void);
        case Kind_ButtonModifierBuilder: return reinterpret_cast<Ark_NativePointer>(callManagedButtonModifierBuilder);
        case Kind_ButtonTriggerClickCallback: return reinterpret_cast<Ark_NativePointer>(callManagedButtonTriggerClickCallback);
        case Kind_Callback_Area_Area_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Area_Area_Void);
        case Kind_Callback_Array_Number_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Array_Number_Void);
        case Kind_Callback_Array_String_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Array_String_Void);
        case Kind_Callback_Array_TextMenuItem_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Array_TextMenuItem_Void);
        case Kind_Callback_Array_TouchTestInfo_TouchResult: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Array_TouchTestInfo_TouchResult);
        case Kind_Callback_AxisEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_AxisEvent_Void);
        case Kind_Callback_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Boolean);
        case Kind_Callback_Boolean_HoverEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Boolean_HoverEvent_Void);
        case Kind_Callback_Boolean_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Boolean_Void);
        case Kind_Callback_Buffer_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Buffer_Void);
        case Kind_Callback_CalendarRequestedData_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_CalendarRequestedData_Void);
        case Kind_Callback_CalendarSelectedDate_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_CalendarSelectedDate_Void);
        case Kind_Callback_ClickEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_ClickEvent_Void);
        case Kind_Callback_ComputedBarAttribute_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_ComputedBarAttribute_Void);
        case Kind_Callback_CopyEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_CopyEvent_Void);
        case Kind_Callback_CreateItem: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_CreateItem);
        case Kind_Callback_CrownEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_CrownEvent_Void);
        case Kind_Callback_CustomSpanMeasureInfo_CustomSpanMetrics: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_CustomSpanMeasureInfo_CustomSpanMetrics);
        case Kind_Callback_CustomSpanMetrics_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_CustomSpanMetrics_Void);
        case Kind_Callback_CutEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_CutEvent_Void);
        case Kind_Callback_Date_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Date_Void);
        case Kind_Callback_DeleteValue_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_DeleteValue_Boolean);
        case Kind_Callback_DeleteValue_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_DeleteValue_Void);
        case Kind_Callback_DismissContentCoverAction_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_DismissContentCoverAction_Void);
        case Kind_Callback_DismissDialogAction_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_DismissDialogAction_Void);
        case Kind_Callback_DismissPopupAction_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_DismissPopupAction_Void);
        case Kind_Callback_DismissSheetAction_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_DismissSheetAction_Void);
        case Kind_Callback_DragEvent_Opt_String_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_DragEvent_Opt_String_Void);
        case Kind_Callback_DrawContext_CustomSpanDrawInfo_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_DrawContext_CustomSpanDrawInfo_Void);
        case Kind_Callback_DrawContext_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_DrawContext_Void);
        case Kind_Callback_EditableTextChangeValue_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_EditableTextChangeValue_Boolean);
        case Kind_Callback_EnterKeyType_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_EnterKeyType_Void);
        case Kind_Callback_Extender_OnFinish: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Extender_OnFinish);
        case Kind_Callback_Extender_OnProgress: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Extender_OnProgress);
        case Kind_Callback_FocusAxisEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_FocusAxisEvent_Void);
        case Kind_Callback_FormCallbackInfo_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_FormCallbackInfo_Void);
        case Kind_Callback_FormError_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_FormError_Void);
        case Kind_Callback_FullscreenInfo_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_FullscreenInfo_Void);
        case Kind_Callback_GestureEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_GestureEvent_Void);
        case Kind_Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_GestureInfo_BaseGestureEvent_GestureJudgeResult);
        case Kind_Callback_GestureJudgeResult_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_GestureJudgeResult_Void);
        case Kind_Callback_GestureRecognizer_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_GestureRecognizer_Void);
        case Kind_Callback_HitTestMode_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_HitTestMode_Void);
        case Kind_Callback_HoverEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_HoverEvent_Void);
        case Kind_Callback_InsertValue_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_InsertValue_Boolean);
        case Kind_Callback_InsertValue_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_InsertValue_Void);
        case Kind_Callback_InteropComponent: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_InteropComponent);
        case Kind_Callback_InteropComponent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_InteropComponent_Void);
        case Kind_Callback_ItemDragInfo_Number_Number_Boolean_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_ItemDragInfo_Number_Number_Boolean_Void);
        case Kind_Callback_ItemDragInfo_Number_Number_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_ItemDragInfo_Number_Number_Void);
        case Kind_Callback_ItemDragInfo_Number_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_ItemDragInfo_Number_Void);
        case Kind_Callback_ItemDragInfo_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_ItemDragInfo_Void);
        case Kind_Callback_KeyEvent_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_KeyEvent_Boolean);
        case Kind_Callback_KeyEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_KeyEvent_Void);
        case Kind_Callback_Map_String_Object_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Map_String_Object_Void);
        case Kind_Callback_MarqueeState_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_MarqueeState_Void);
        case Kind_Callback_MouseEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_MouseEvent_Void);
        case Kind_Callback_NavDestinationActiveReason_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_NavDestinationActiveReason_Void);
        case Kind_Callback_NavDestinationContext_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_NavDestinationContext_Void);
        case Kind_Callback_NavigationMode_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_NavigationMode_Void);
        case Kind_Callback_NavigationTitleMode_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_NavigationTitleMode_Void);
        case Kind_Callback_NavigationTransitionProxy_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_NavigationTransitionProxy_Void);
        case Kind_Callback_Number: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Number);
        case Kind_Callback_Number_ESObject_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Number_ESObject_Void);
        case Kind_Callback_Number_Number_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Number_Number_Boolean);
        case Kind_Callback_Number_Number_Boolean_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Number_Number_Boolean_Boolean);
        case Kind_Callback_Number_Number_ComputedBarAttribute: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Number_Number_ComputedBarAttribute);
        case Kind_Callback_Number_Number_Number_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Number_Number_Number_Void);
        case Kind_Callback_Number_Number_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Number_Number_Void);
        case Kind_Callback_Number_SliderChangeMode_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Number_SliderChangeMode_Void);
        case Kind_Callback_Number_Tuple_Number_Number: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Number_Tuple_Number_Number);
        case Kind_Callback_Number_Tuple_Number_Number_Number_Number: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Number_Tuple_Number_Number_Number_Number);
        case Kind_Callback_Number_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Number_Void);
        case Kind_Callback_onMeasureSize_SizeResult: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_onMeasureSize_SizeResult);
        case Kind_Callback_onPlaceChildren_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_onPlaceChildren_Void);
        case Kind_Callback_OnScrollFrameBeginHandlerResult_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnScrollFrameBeginHandlerResult_Void);
        case Kind_Callback_Opt_Array_FontDescriptor_Opt_Array_String_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Opt_Array_FontDescriptor_Opt_Array_String_Void);
        case Kind_Callback_Opt_Array_NavDestinationTransition_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Opt_Array_NavDestinationTransition_Void);
        case Kind_Callback_Opt_Array_String_Opt_Array_String_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Opt_Array_String_Opt_Array_String_Void);
        case Kind_Callback_Opt_Array_String_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Opt_Array_String_Void);
        case Kind_Callback_Opt_CustomBuilder_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Opt_CustomBuilder_Void);
        case Kind_Callback_Opt_FontDescriptor_Opt_Array_String_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Opt_FontDescriptor_Opt_Array_String_Void);
        case Kind_Callback_Opt_NavigationAnimatedTransition_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Opt_NavigationAnimatedTransition_Void);
        case Kind_Callback_Opt_OffsetResult_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Opt_OffsetResult_Void);
        case Kind_Callback_Opt_Scene_Opt_Array_String_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Opt_Scene_Opt_Array_String_Void);
        case Kind_Callback_Opt_ScrollResult_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Opt_ScrollResult_Void);
        case Kind_Callback_Opt_String_Opt_Array_String_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Opt_String_Opt_Array_String_Void);
        case Kind_Callback_Opt_StyledString_Opt_Array_String_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Opt_StyledString_Opt_Array_String_Void);
        case Kind_Callback_Opt_TabContentAnimatedTransition_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Opt_TabContentAnimatedTransition_Void);
        case Kind_Callback_PlaybackInfo_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_PlaybackInfo_Void);
        case Kind_Callback_Pointer_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Pointer_Void);
        case Kind_Callback_PopInfo_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_PopInfo_Void);
        case Kind_Callback_PreDragStatus_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_PreDragStatus_Void);
        case Kind_Callback_PreparedInfo_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_PreparedInfo_Void);
        case Kind_Callback_RangeUpdate: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_RangeUpdate);
        case Kind_Callback_RefreshStatus_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_RefreshStatus_Void);
        case Kind_Callback_RichEditorChangeValue_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_RichEditorChangeValue_Boolean);
        case Kind_Callback_RichEditorDeleteValue_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_RichEditorDeleteValue_Boolean);
        case Kind_Callback_RichEditorInsertValue_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_RichEditorInsertValue_Boolean);
        case Kind_Callback_RichEditorRange_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_RichEditorRange_Void);
        case Kind_Callback_RichEditorSelection_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_RichEditorSelection_Void);
        case Kind_Callback_RichEditorTextSpanResult_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_RichEditorTextSpanResult_Void);
        case Kind_Callback_RotationGesture: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_RotationGesture);
        case Kind_Callback_RotationGesture_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_RotationGesture_Void);
        case Kind_Callback_SheetDismiss_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_SheetDismiss_Void);
        case Kind_Callback_SheetType_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_SheetType_Void);
        case Kind_Callback_SizeResult_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_SizeResult_Void);
        case Kind_Callback_SpringBackAction_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_SpringBackAction_Void);
        case Kind_Callback_StateStylesChange: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_StateStylesChange);
        case Kind_Callback_String_PasteEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_String_PasteEvent_Void);
        case Kind_Callback_String_SurfaceRect_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_String_SurfaceRect_Void);
        case Kind_Callback_String_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_String_Void);
        case Kind_Callback_StyledStringChangeValue_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_StyledStringChangeValue_Boolean);
        case Kind_Callback_StyledStringMarshallingValue_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_StyledStringMarshallingValue_Void);
        case Kind_Callback_SwipeActionState_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_SwipeActionState_Void);
        case Kind_Callback_SwipeGesture: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_SwipeGesture);
        case Kind_Callback_SwipeGesture_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_SwipeGesture_Void);
        case Kind_Callback_SwiperContentTransitionProxy_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_SwiperContentTransitionProxy_Void);
        case Kind_Callback_T: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_T);
        case Kind_Callback_T_Number_String: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_T_Number_String);
        case Kind_Callback_T_Number_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_T_Number_Void);
        case Kind_Callback_T_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_T_Void);
        case Kind_Callback_TabContentTransitionProxy_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_TabContentTransitionProxy_Void);
        case Kind_Callback_TerminationInfo_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_TerminationInfo_Void);
        case Kind_Callback_TextPickerResult_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_TextPickerResult_Void);
        case Kind_Callback_TextRange_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_TextRange_Void);
        case Kind_Callback_TimePickerResult_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_TimePickerResult_Void);
        case Kind_Callback_TouchEvent_HitTestMode: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_TouchEvent_HitTestMode);
        case Kind_Callback_TouchEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_TouchEvent_Void);
        case Kind_Callback_TouchResult_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_TouchResult_Void);
        case Kind_Callback_Tuple_Number_Number_Number_Number_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Tuple_Number_Number_Number_Number_Void);
        case Kind_Callback_Tuple_Number_Number_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Tuple_Number_Number_Void);
        case Kind_Callback_UIExtensionProxy_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_UIExtensionProxy_Void);
        case Kind_Callback_Union_CustomBuilder_DragItemInfo_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Union_CustomBuilder_DragItemInfo_Void);
        case Kind_Callback_Union_Object_Undefined_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Union_Object_Undefined_Void);
        case Kind_Callback_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Void);
        case Kind_CheckBoxModifierBuilder: return reinterpret_cast<Ark_NativePointer>(callManagedCheckBoxModifierBuilder);
        case Kind_ContentDidScrollCallback: return reinterpret_cast<Ark_NativePointer>(callManagedContentDidScrollCallback);
        case Kind_ContentWillScrollCallback: return reinterpret_cast<Ark_NativePointer>(callManagedContentWillScrollCallback);
        case Kind_Context_getGroupDir_Callback: return reinterpret_cast<Ark_NativePointer>(callManagedContext_getGroupDir_Callback);
        case Kind_CustomBuilderT: return reinterpret_cast<Ark_NativePointer>(callManagedCustomBuilderT);
        case Kind_CustomNodeBuilder: return reinterpret_cast<Ark_NativePointer>(callManagedCustomNodeBuilder);
        case Kind_CustomStyles: return reinterpret_cast<Ark_NativePointer>(callManagedCustomStyles);
        case Kind_DataPanelModifierBuilder: return reinterpret_cast<Ark_NativePointer>(callManagedDataPanelModifierBuilder);
        case Kind_EditableTextOnChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedEditableTextOnChangeCallback);
        case Kind_ErrorCallback: return reinterpret_cast<Ark_NativePointer>(callManagedErrorCallback);
        case Kind_GaugeModifierBuilder: return reinterpret_cast<Ark_NativePointer>(callManagedGaugeModifierBuilder);
        case Kind_GestureRecognizerJudgeBeginCallback: return reinterpret_cast<Ark_NativePointer>(callManagedGestureRecognizerJudgeBeginCallback);
        case Kind_GetItemMainSizeByIndex: return reinterpret_cast<Ark_NativePointer>(callManagedGetItemMainSizeByIndex);
        case Kind_HoverCallback: return reinterpret_cast<Ark_NativePointer>(callManagedHoverCallback);
        case Kind_ImageCompleteCallback: return reinterpret_cast<Ark_NativePointer>(callManagedImageCompleteCallback);
        case Kind_ImageErrorCallback: return reinterpret_cast<Ark_NativePointer>(callManagedImageErrorCallback);
        case Kind_ImageOnCompleteCallback: return reinterpret_cast<Ark_NativePointer>(callManagedImageOnCompleteCallback);
        case Kind_InterceptionModeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedInterceptionModeCallback);
        case Kind_InterceptionShowCallback: return reinterpret_cast<Ark_NativePointer>(callManagedInterceptionShowCallback);
        case Kind_LoadingProgressModifierBuilder: return reinterpret_cast<Ark_NativePointer>(callManagedLoadingProgressModifierBuilder);
        case Kind_MenuCallback: return reinterpret_cast<Ark_NativePointer>(callManagedMenuCallback);
        case Kind_MenuItemModifierBuilder: return reinterpret_cast<Ark_NativePointer>(callManagedMenuItemModifierBuilder);
        case Kind_MenuOnAppearCallback: return reinterpret_cast<Ark_NativePointer>(callManagedMenuOnAppearCallback);
        case Kind_ModifierKeyStateGetter: return reinterpret_cast<Ark_NativePointer>(callManagedModifierKeyStateGetter);
        case Kind_NavDestinationTransitionDelegate: return reinterpret_cast<Ark_NativePointer>(callManagedNavDestinationTransitionDelegate);
        case Kind_NavExtender_OnUpdateStack: return reinterpret_cast<Ark_NativePointer>(callManagedNavExtender_OnUpdateStack);
        case Kind_OnAlphabetIndexerPopupSelectCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnAlphabetIndexerPopupSelectCallback);
        case Kind_OnAlphabetIndexerRequestPopupDataCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnAlphabetIndexerRequestPopupDataCallback);
        case Kind_OnAlphabetIndexerSelectCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnAlphabetIndexerSelectCallback);
        case Kind_OnCheckboxChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnCheckboxChangeCallback);
        case Kind_OnCheckboxGroupChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnCheckboxGroupChangeCallback);
        case Kind_OnContentScrollCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnContentScrollCallback);
        case Kind_OnCreateMenuCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnCreateMenuCallback);
        case Kind_OnDidChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnDidChangeCallback);
        case Kind_OnDragEventCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnDragEventCallback);
        case Kind_OnFoldStatusChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnFoldStatusChangeCallback);
        case Kind_OnHoverCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnHoverCallback);
        case Kind_OnHoverStatusChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnHoverStatusChangeCallback);
        case Kind_OnItemDragStartCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnItemDragStartCallback);
        case Kind_OnLinearIndicatorChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnLinearIndicatorChangeCallback);
        case Kind_OnMenuItemClickCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnMenuItemClickCallback);
        case Kind_OnMoveHandler: return reinterpret_cast<Ark_NativePointer>(callManagedOnMoveHandler);
        case Kind_OnNativeLoadCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnNativeLoadCallback);
        case Kind_OnPasteCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnPasteCallback);
        case Kind_OnRadioChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnRadioChangeCallback);
        case Kind_OnRatingChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnRatingChangeCallback);
        case Kind_OnScrollCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnScrollCallback);
        case Kind_OnScrollEdgeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnScrollEdgeCallback);
        case Kind_OnScrollFrameBeginCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnScrollFrameBeginCallback);
        case Kind_OnScrollVisibleContentChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnScrollVisibleContentChangeCallback);
        case Kind_OnSelectCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnSelectCallback);
        case Kind_OnSubmitCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnSubmitCallback);
        case Kind_OnSwiperAnimationEndCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnSwiperAnimationEndCallback);
        case Kind_OnSwiperAnimationStartCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnSwiperAnimationStartCallback);
        case Kind_OnSwiperGestureSwipeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnSwiperGestureSwipeCallback);
        case Kind_OnTabsAnimationEndCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnTabsAnimationEndCallback);
        case Kind_OnTabsAnimationStartCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnTabsAnimationStartCallback);
        case Kind_OnTabsContentWillChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnTabsContentWillChangeCallback);
        case Kind_OnTabsGestureSwipeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnTabsGestureSwipeCallback);
        case Kind_OnTextPickerChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnTextPickerChangeCallback);
        case Kind_OnTextSelectionChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnTextSelectionChangeCallback);
        case Kind_OnTimePickerChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnTimePickerChangeCallback);
        case Kind_OnWillScrollCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnWillScrollCallback);
        case Kind_PageMapBuilder: return reinterpret_cast<Ark_NativePointer>(callManagedPageMapBuilder);
        case Kind_PageTransitionCallback: return reinterpret_cast<Ark_NativePointer>(callManagedPageTransitionCallback);
        case Kind_PasteButtonCallback: return reinterpret_cast<Ark_NativePointer>(callManagedPasteButtonCallback);
        case Kind_PasteEventCallback: return reinterpret_cast<Ark_NativePointer>(callManagedPasteEventCallback);
        case Kind_PluginErrorCallback: return reinterpret_cast<Ark_NativePointer>(callManagedPluginErrorCallback);
        case Kind_PopupStateChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedPopupStateChangeCallback);
        case Kind_ProgressModifierBuilder: return reinterpret_cast<Ark_NativePointer>(callManagedProgressModifierBuilder);
        case Kind_RadioModifierBuilder: return reinterpret_cast<Ark_NativePointer>(callManagedRadioModifierBuilder);
        case Kind_RatingModifierBuilder: return reinterpret_cast<Ark_NativePointer>(callManagedRatingModifierBuilder);
        case Kind_RestrictedWorker_onerror_Callback: return reinterpret_cast<Ark_NativePointer>(callManagedRestrictedWorker_onerror_Callback);
        case Kind_RestrictedWorker_onexit_Callback: return reinterpret_cast<Ark_NativePointer>(callManagedRestrictedWorker_onexit_Callback);
        case Kind_RestrictedWorker_onmessage_Callback: return reinterpret_cast<Ark_NativePointer>(callManagedRestrictedWorker_onmessage_Callback);
        case Kind_ReuseIdCallback: return reinterpret_cast<Ark_NativePointer>(callManagedReuseIdCallback);
        case Kind_SaveButtonCallback: return reinterpret_cast<Ark_NativePointer>(callManagedSaveButtonCallback);
        case Kind_ScrollOnScrollCallback: return reinterpret_cast<Ark_NativePointer>(callManagedScrollOnScrollCallback);
        case Kind_ScrollOnWillScrollCallback: return reinterpret_cast<Ark_NativePointer>(callManagedScrollOnWillScrollCallback);
        case Kind_SearchSubmitCallback: return reinterpret_cast<Ark_NativePointer>(callManagedSearchSubmitCallback);
        case Kind_SearchValueCallback: return reinterpret_cast<Ark_NativePointer>(callManagedSearchValueCallback);
        case Kind_ShouldBuiltInRecognizerParallelWithCallback: return reinterpret_cast<Ark_NativePointer>(callManagedShouldBuiltInRecognizerParallelWithCallback);
        case Kind_SizeChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedSizeChangeCallback);
        case Kind_SliderModifierBuilder: return reinterpret_cast<Ark_NativePointer>(callManagedSliderModifierBuilder);
        case Kind_SliderTriggerChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedSliderTriggerChangeCallback);
        case Kind_StyledStringMarshallCallback: return reinterpret_cast<Ark_NativePointer>(callManagedStyledStringMarshallCallback);
        case Kind_StyledStringUnmarshallCallback: return reinterpret_cast<Ark_NativePointer>(callManagedStyledStringUnmarshallCallback);
        case Kind_SubmitCallback: return reinterpret_cast<Ark_NativePointer>(callManagedSubmitCallback);
        case Kind_TabsCustomContentTransitionCallback: return reinterpret_cast<Ark_NativePointer>(callManagedTabsCustomContentTransitionCallback);
        case Kind_TextAreaSubmitCallback: return reinterpret_cast<Ark_NativePointer>(callManagedTextAreaSubmitCallback);
        case Kind_TextClockModifierBuilder: return reinterpret_cast<Ark_NativePointer>(callManagedTextClockModifierBuilder);
        case Kind_TextFieldValueCallback: return reinterpret_cast<Ark_NativePointer>(callManagedTextFieldValueCallback);
        case Kind_TextPickerEnterSelectedAreaCallback: return reinterpret_cast<Ark_NativePointer>(callManagedTextPickerEnterSelectedAreaCallback);
        case Kind_TextPickerScrollStopCallback: return reinterpret_cast<Ark_NativePointer>(callManagedTextPickerScrollStopCallback);
        case Kind_TextTimerModifierBuilder: return reinterpret_cast<Ark_NativePointer>(callManagedTextTimerModifierBuilder);
        case Kind_ToggleModifierBuilder: return reinterpret_cast<Ark_NativePointer>(callManagedToggleModifierBuilder);
        case Kind_TransitionFinishCallback: return reinterpret_cast<Ark_NativePointer>(callManagedTransitionFinishCallback);
        case Kind_Type_CommonMethod_onDragStart: return reinterpret_cast<Ark_NativePointer>(callManagedType_CommonMethod_onDragStart);
        case Kind_Type_NavigationAttribute_customNavContentTransition: return reinterpret_cast<Ark_NativePointer>(callManagedType_NavigationAttribute_customNavContentTransition);
        case Kind_UpdateTransitionCallback: return reinterpret_cast<Ark_NativePointer>(callManagedUpdateTransitionCallback);
        case Kind_VisibleAreaChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedVisibleAreaChangeCallback);
        case Kind_VoidCallback: return reinterpret_cast<Ark_NativePointer>(callManagedVoidCallback);
    }
    return nullptr;
}
Ark_NativePointer getManagedCallbackCallerSync(CallbackKind kind)
{
    switch (kind) {
        case Kind_AccessibilityCallback: return reinterpret_cast<Ark_NativePointer>(callManagedAccessibilityCallbackSync);
        case Kind_AccessibilityFocusCallback: return reinterpret_cast<Ark_NativePointer>(callManagedAccessibilityFocusCallbackSync);
        case Kind_AsyncCallback_image_PixelMap_Void: return reinterpret_cast<Ark_NativePointer>(callManagedAsyncCallback_image_PixelMap_VoidSync);
        case Kind_ButtonModifierBuilder: return reinterpret_cast<Ark_NativePointer>(callManagedButtonModifierBuilderSync);
        case Kind_ButtonTriggerClickCallback: return reinterpret_cast<Ark_NativePointer>(callManagedButtonTriggerClickCallbackSync);
        case Kind_Callback_Area_Area_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Area_Area_VoidSync);
        case Kind_Callback_Array_Number_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Array_Number_VoidSync);
        case Kind_Callback_Array_String_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Array_String_VoidSync);
        case Kind_Callback_Array_TextMenuItem_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Array_TextMenuItem_VoidSync);
        case Kind_Callback_Array_TouchTestInfo_TouchResult: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Array_TouchTestInfo_TouchResultSync);
        case Kind_Callback_AxisEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_AxisEvent_VoidSync);
        case Kind_Callback_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_BooleanSync);
        case Kind_Callback_Boolean_HoverEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Boolean_HoverEvent_VoidSync);
        case Kind_Callback_Boolean_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Boolean_VoidSync);
        case Kind_Callback_Buffer_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Buffer_VoidSync);
        case Kind_Callback_CalendarRequestedData_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_CalendarRequestedData_VoidSync);
        case Kind_Callback_CalendarSelectedDate_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_CalendarSelectedDate_VoidSync);
        case Kind_Callback_ClickEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_ClickEvent_VoidSync);
        case Kind_Callback_ComputedBarAttribute_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_ComputedBarAttribute_VoidSync);
        case Kind_Callback_CopyEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_CopyEvent_VoidSync);
        case Kind_Callback_CreateItem: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_CreateItemSync);
        case Kind_Callback_CrownEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_CrownEvent_VoidSync);
        case Kind_Callback_CustomSpanMeasureInfo_CustomSpanMetrics: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_CustomSpanMeasureInfo_CustomSpanMetricsSync);
        case Kind_Callback_CustomSpanMetrics_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_CustomSpanMetrics_VoidSync);
        case Kind_Callback_CutEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_CutEvent_VoidSync);
        case Kind_Callback_Date_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Date_VoidSync);
        case Kind_Callback_DeleteValue_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_DeleteValue_BooleanSync);
        case Kind_Callback_DeleteValue_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_DeleteValue_VoidSync);
        case Kind_Callback_DismissContentCoverAction_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_DismissContentCoverAction_VoidSync);
        case Kind_Callback_DismissDialogAction_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_DismissDialogAction_VoidSync);
        case Kind_Callback_DismissPopupAction_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_DismissPopupAction_VoidSync);
        case Kind_Callback_DismissSheetAction_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_DismissSheetAction_VoidSync);
        case Kind_Callback_DragEvent_Opt_String_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_DragEvent_Opt_String_VoidSync);
        case Kind_Callback_DrawContext_CustomSpanDrawInfo_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_DrawContext_CustomSpanDrawInfo_VoidSync);
        case Kind_Callback_DrawContext_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_DrawContext_VoidSync);
        case Kind_Callback_EditableTextChangeValue_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_EditableTextChangeValue_BooleanSync);
        case Kind_Callback_EnterKeyType_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_EnterKeyType_VoidSync);
        case Kind_Callback_Extender_OnFinish: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Extender_OnFinishSync);
        case Kind_Callback_Extender_OnProgress: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Extender_OnProgressSync);
        case Kind_Callback_FocusAxisEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_FocusAxisEvent_VoidSync);
        case Kind_Callback_FormCallbackInfo_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_FormCallbackInfo_VoidSync);
        case Kind_Callback_FormError_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_FormError_VoidSync);
        case Kind_Callback_FullscreenInfo_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_FullscreenInfo_VoidSync);
        case Kind_Callback_GestureEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_GestureEvent_VoidSync);
        case Kind_Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_GestureInfo_BaseGestureEvent_GestureJudgeResultSync);
        case Kind_Callback_GestureJudgeResult_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_GestureJudgeResult_VoidSync);
        case Kind_Callback_GestureRecognizer_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_GestureRecognizer_VoidSync);
        case Kind_Callback_HitTestMode_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_HitTestMode_VoidSync);
        case Kind_Callback_HoverEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_HoverEvent_VoidSync);
        case Kind_Callback_InsertValue_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_InsertValue_BooleanSync);
        case Kind_Callback_InsertValue_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_InsertValue_VoidSync);
        case Kind_Callback_InteropComponent: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_InteropComponentSync);
        case Kind_Callback_InteropComponent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_InteropComponent_VoidSync);
        case Kind_Callback_ItemDragInfo_Number_Number_Boolean_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_ItemDragInfo_Number_Number_Boolean_VoidSync);
        case Kind_Callback_ItemDragInfo_Number_Number_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_ItemDragInfo_Number_Number_VoidSync);
        case Kind_Callback_ItemDragInfo_Number_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_ItemDragInfo_Number_VoidSync);
        case Kind_Callback_ItemDragInfo_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_ItemDragInfo_VoidSync);
        case Kind_Callback_KeyEvent_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_KeyEvent_BooleanSync);
        case Kind_Callback_KeyEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_KeyEvent_VoidSync);
        case Kind_Callback_Map_String_Object_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Map_String_Object_VoidSync);
        case Kind_Callback_MarqueeState_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_MarqueeState_VoidSync);
        case Kind_Callback_MouseEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_MouseEvent_VoidSync);
        case Kind_Callback_NavDestinationActiveReason_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_NavDestinationActiveReason_VoidSync);
        case Kind_Callback_NavDestinationContext_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_NavDestinationContext_VoidSync);
        case Kind_Callback_NavigationMode_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_NavigationMode_VoidSync);
        case Kind_Callback_NavigationTitleMode_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_NavigationTitleMode_VoidSync);
        case Kind_Callback_NavigationTransitionProxy_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_NavigationTransitionProxy_VoidSync);
        case Kind_Callback_Number: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_NumberSync);
        case Kind_Callback_Number_ESObject_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Number_ESObject_VoidSync);
        case Kind_Callback_Number_Number_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Number_Number_BooleanSync);
        case Kind_Callback_Number_Number_Boolean_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Number_Number_Boolean_BooleanSync);
        case Kind_Callback_Number_Number_ComputedBarAttribute: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Number_Number_ComputedBarAttributeSync);
        case Kind_Callback_Number_Number_Number_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Number_Number_Number_VoidSync);
        case Kind_Callback_Number_Number_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Number_Number_VoidSync);
        case Kind_Callback_Number_SliderChangeMode_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Number_SliderChangeMode_VoidSync);
        case Kind_Callback_Number_Tuple_Number_Number: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Number_Tuple_Number_NumberSync);
        case Kind_Callback_Number_Tuple_Number_Number_Number_Number: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Number_Tuple_Number_Number_Number_NumberSync);
        case Kind_Callback_Number_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Number_VoidSync);
        case Kind_Callback_onMeasureSize_SizeResult: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_onMeasureSize_SizeResultSync);
        case Kind_Callback_onPlaceChildren_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_onPlaceChildren_VoidSync);
        case Kind_Callback_OnScrollFrameBeginHandlerResult_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnScrollFrameBeginHandlerResult_VoidSync);
        case Kind_Callback_Opt_Array_FontDescriptor_Opt_Array_String_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Opt_Array_FontDescriptor_Opt_Array_String_VoidSync);
        case Kind_Callback_Opt_Array_NavDestinationTransition_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Opt_Array_NavDestinationTransition_VoidSync);
        case Kind_Callback_Opt_Array_String_Opt_Array_String_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Opt_Array_String_Opt_Array_String_VoidSync);
        case Kind_Callback_Opt_Array_String_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Opt_Array_String_VoidSync);
        case Kind_Callback_Opt_CustomBuilder_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Opt_CustomBuilder_VoidSync);
        case Kind_Callback_Opt_FontDescriptor_Opt_Array_String_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Opt_FontDescriptor_Opt_Array_String_VoidSync);
        case Kind_Callback_Opt_NavigationAnimatedTransition_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Opt_NavigationAnimatedTransition_VoidSync);
        case Kind_Callback_Opt_OffsetResult_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Opt_OffsetResult_VoidSync);
        case Kind_Callback_Opt_Scene_Opt_Array_String_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Opt_Scene_Opt_Array_String_VoidSync);
        case Kind_Callback_Opt_ScrollResult_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Opt_ScrollResult_VoidSync);
        case Kind_Callback_Opt_String_Opt_Array_String_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Opt_String_Opt_Array_String_VoidSync);
        case Kind_Callback_Opt_StyledString_Opt_Array_String_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Opt_StyledString_Opt_Array_String_VoidSync);
        case Kind_Callback_Opt_TabContentAnimatedTransition_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Opt_TabContentAnimatedTransition_VoidSync);
        case Kind_Callback_PlaybackInfo_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_PlaybackInfo_VoidSync);
        case Kind_Callback_Pointer_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Pointer_VoidSync);
        case Kind_Callback_PopInfo_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_PopInfo_VoidSync);
        case Kind_Callback_PreDragStatus_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_PreDragStatus_VoidSync);
        case Kind_Callback_PreparedInfo_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_PreparedInfo_VoidSync);
        case Kind_Callback_RangeUpdate: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_RangeUpdateSync);
        case Kind_Callback_RefreshStatus_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_RefreshStatus_VoidSync);
        case Kind_Callback_RichEditorChangeValue_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_RichEditorChangeValue_BooleanSync);
        case Kind_Callback_RichEditorDeleteValue_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_RichEditorDeleteValue_BooleanSync);
        case Kind_Callback_RichEditorInsertValue_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_RichEditorInsertValue_BooleanSync);
        case Kind_Callback_RichEditorRange_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_RichEditorRange_VoidSync);
        case Kind_Callback_RichEditorSelection_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_RichEditorSelection_VoidSync);
        case Kind_Callback_RichEditorTextSpanResult_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_RichEditorTextSpanResult_VoidSync);
        case Kind_Callback_RotationGesture: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_RotationGestureSync);
        case Kind_Callback_RotationGesture_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_RotationGesture_VoidSync);
        case Kind_Callback_SheetDismiss_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_SheetDismiss_VoidSync);
        case Kind_Callback_SheetType_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_SheetType_VoidSync);
        case Kind_Callback_SizeResult_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_SizeResult_VoidSync);
        case Kind_Callback_SpringBackAction_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_SpringBackAction_VoidSync);
        case Kind_Callback_StateStylesChange: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_StateStylesChangeSync);
        case Kind_Callback_String_PasteEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_String_PasteEvent_VoidSync);
        case Kind_Callback_String_SurfaceRect_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_String_SurfaceRect_VoidSync);
        case Kind_Callback_String_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_String_VoidSync);
        case Kind_Callback_StyledStringChangeValue_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_StyledStringChangeValue_BooleanSync);
        case Kind_Callback_StyledStringMarshallingValue_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_StyledStringMarshallingValue_VoidSync);
        case Kind_Callback_SwipeActionState_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_SwipeActionState_VoidSync);
        case Kind_Callback_SwipeGesture: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_SwipeGestureSync);
        case Kind_Callback_SwipeGesture_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_SwipeGesture_VoidSync);
        case Kind_Callback_SwiperContentTransitionProxy_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_SwiperContentTransitionProxy_VoidSync);
        case Kind_Callback_T: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_TSync);
        case Kind_Callback_T_Number_String: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_T_Number_StringSync);
        case Kind_Callback_T_Number_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_T_Number_VoidSync);
        case Kind_Callback_T_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_T_VoidSync);
        case Kind_Callback_TabContentTransitionProxy_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_TabContentTransitionProxy_VoidSync);
        case Kind_Callback_TerminationInfo_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_TerminationInfo_VoidSync);
        case Kind_Callback_TextPickerResult_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_TextPickerResult_VoidSync);
        case Kind_Callback_TextRange_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_TextRange_VoidSync);
        case Kind_Callback_TimePickerResult_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_TimePickerResult_VoidSync);
        case Kind_Callback_TouchEvent_HitTestMode: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_TouchEvent_HitTestModeSync);
        case Kind_Callback_TouchEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_TouchEvent_VoidSync);
        case Kind_Callback_TouchResult_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_TouchResult_VoidSync);
        case Kind_Callback_Tuple_Number_Number_Number_Number_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Tuple_Number_Number_Number_Number_VoidSync);
        case Kind_Callback_Tuple_Number_Number_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Tuple_Number_Number_VoidSync);
        case Kind_Callback_UIExtensionProxy_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_UIExtensionProxy_VoidSync);
        case Kind_Callback_Union_CustomBuilder_DragItemInfo_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Union_CustomBuilder_DragItemInfo_VoidSync);
        case Kind_Callback_Union_Object_Undefined_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Union_Object_Undefined_VoidSync);
        case Kind_Callback_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_VoidSync);
        case Kind_CheckBoxModifierBuilder: return reinterpret_cast<Ark_NativePointer>(callManagedCheckBoxModifierBuilderSync);
        case Kind_ContentDidScrollCallback: return reinterpret_cast<Ark_NativePointer>(callManagedContentDidScrollCallbackSync);
        case Kind_ContentWillScrollCallback: return reinterpret_cast<Ark_NativePointer>(callManagedContentWillScrollCallbackSync);
        case Kind_Context_getGroupDir_Callback: return reinterpret_cast<Ark_NativePointer>(callManagedContext_getGroupDir_CallbackSync);
        case Kind_CustomBuilderT: return reinterpret_cast<Ark_NativePointer>(callManagedCustomBuilderTSync);
        case Kind_CustomNodeBuilder: return reinterpret_cast<Ark_NativePointer>(callManagedCustomNodeBuilderSync);
        case Kind_CustomStyles: return reinterpret_cast<Ark_NativePointer>(callManagedCustomStylesSync);
        case Kind_DataPanelModifierBuilder: return reinterpret_cast<Ark_NativePointer>(callManagedDataPanelModifierBuilderSync);
        case Kind_EditableTextOnChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedEditableTextOnChangeCallbackSync);
        case Kind_ErrorCallback: return reinterpret_cast<Ark_NativePointer>(callManagedErrorCallbackSync);
        case Kind_GaugeModifierBuilder: return reinterpret_cast<Ark_NativePointer>(callManagedGaugeModifierBuilderSync);
        case Kind_GestureRecognizerJudgeBeginCallback: return reinterpret_cast<Ark_NativePointer>(callManagedGestureRecognizerJudgeBeginCallbackSync);
        case Kind_GetItemMainSizeByIndex: return reinterpret_cast<Ark_NativePointer>(callManagedGetItemMainSizeByIndexSync);
        case Kind_HoverCallback: return reinterpret_cast<Ark_NativePointer>(callManagedHoverCallbackSync);
        case Kind_ImageCompleteCallback: return reinterpret_cast<Ark_NativePointer>(callManagedImageCompleteCallbackSync);
        case Kind_ImageErrorCallback: return reinterpret_cast<Ark_NativePointer>(callManagedImageErrorCallbackSync);
        case Kind_ImageOnCompleteCallback: return reinterpret_cast<Ark_NativePointer>(callManagedImageOnCompleteCallbackSync);
        case Kind_InterceptionModeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedInterceptionModeCallbackSync);
        case Kind_InterceptionShowCallback: return reinterpret_cast<Ark_NativePointer>(callManagedInterceptionShowCallbackSync);
        case Kind_LoadingProgressModifierBuilder: return reinterpret_cast<Ark_NativePointer>(callManagedLoadingProgressModifierBuilderSync);
        case Kind_MenuCallback: return reinterpret_cast<Ark_NativePointer>(callManagedMenuCallbackSync);
        case Kind_MenuItemModifierBuilder: return reinterpret_cast<Ark_NativePointer>(callManagedMenuItemModifierBuilderSync);
        case Kind_MenuOnAppearCallback: return reinterpret_cast<Ark_NativePointer>(callManagedMenuOnAppearCallbackSync);
        case Kind_ModifierKeyStateGetter: return reinterpret_cast<Ark_NativePointer>(callManagedModifierKeyStateGetterSync);
        case Kind_NavDestinationTransitionDelegate: return reinterpret_cast<Ark_NativePointer>(callManagedNavDestinationTransitionDelegateSync);
        case Kind_NavExtender_OnUpdateStack: return reinterpret_cast<Ark_NativePointer>(callManagedNavExtender_OnUpdateStackSync);
        case Kind_OnAlphabetIndexerPopupSelectCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnAlphabetIndexerPopupSelectCallbackSync);
        case Kind_OnAlphabetIndexerRequestPopupDataCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnAlphabetIndexerRequestPopupDataCallbackSync);
        case Kind_OnAlphabetIndexerSelectCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnAlphabetIndexerSelectCallbackSync);
        case Kind_OnCheckboxChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnCheckboxChangeCallbackSync);
        case Kind_OnCheckboxGroupChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnCheckboxGroupChangeCallbackSync);
        case Kind_OnContentScrollCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnContentScrollCallbackSync);
        case Kind_OnCreateMenuCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnCreateMenuCallbackSync);
        case Kind_OnDidChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnDidChangeCallbackSync);
        case Kind_OnDragEventCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnDragEventCallbackSync);
        case Kind_OnFoldStatusChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnFoldStatusChangeCallbackSync);
        case Kind_OnHoverCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnHoverCallbackSync);
        case Kind_OnHoverStatusChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnHoverStatusChangeCallbackSync);
        case Kind_OnItemDragStartCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnItemDragStartCallbackSync);
        case Kind_OnLinearIndicatorChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnLinearIndicatorChangeCallbackSync);
        case Kind_OnMenuItemClickCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnMenuItemClickCallbackSync);
        case Kind_OnMoveHandler: return reinterpret_cast<Ark_NativePointer>(callManagedOnMoveHandlerSync);
        case Kind_OnNativeLoadCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnNativeLoadCallbackSync);
        case Kind_OnPasteCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnPasteCallbackSync);
        case Kind_OnRadioChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnRadioChangeCallbackSync);
        case Kind_OnRatingChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnRatingChangeCallbackSync);
        case Kind_OnScrollCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnScrollCallbackSync);
        case Kind_OnScrollEdgeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnScrollEdgeCallbackSync);
        case Kind_OnScrollFrameBeginCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnScrollFrameBeginCallbackSync);
        case Kind_OnScrollVisibleContentChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnScrollVisibleContentChangeCallbackSync);
        case Kind_OnSelectCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnSelectCallbackSync);
        case Kind_OnSubmitCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnSubmitCallbackSync);
        case Kind_OnSwiperAnimationEndCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnSwiperAnimationEndCallbackSync);
        case Kind_OnSwiperAnimationStartCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnSwiperAnimationStartCallbackSync);
        case Kind_OnSwiperGestureSwipeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnSwiperGestureSwipeCallbackSync);
        case Kind_OnTabsAnimationEndCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnTabsAnimationEndCallbackSync);
        case Kind_OnTabsAnimationStartCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnTabsAnimationStartCallbackSync);
        case Kind_OnTabsContentWillChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnTabsContentWillChangeCallbackSync);
        case Kind_OnTabsGestureSwipeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnTabsGestureSwipeCallbackSync);
        case Kind_OnTextPickerChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnTextPickerChangeCallbackSync);
        case Kind_OnTextSelectionChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnTextSelectionChangeCallbackSync);
        case Kind_OnTimePickerChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnTimePickerChangeCallbackSync);
        case Kind_OnWillScrollCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnWillScrollCallbackSync);
        case Kind_PageMapBuilder: return reinterpret_cast<Ark_NativePointer>(callManagedPageMapBuilderSync);
        case Kind_PageTransitionCallback: return reinterpret_cast<Ark_NativePointer>(callManagedPageTransitionCallbackSync);
        case Kind_PasteButtonCallback: return reinterpret_cast<Ark_NativePointer>(callManagedPasteButtonCallbackSync);
        case Kind_PasteEventCallback: return reinterpret_cast<Ark_NativePointer>(callManagedPasteEventCallbackSync);
        case Kind_PluginErrorCallback: return reinterpret_cast<Ark_NativePointer>(callManagedPluginErrorCallbackSync);
        case Kind_PopupStateChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedPopupStateChangeCallbackSync);
        case Kind_ProgressModifierBuilder: return reinterpret_cast<Ark_NativePointer>(callManagedProgressModifierBuilderSync);
        case Kind_RadioModifierBuilder: return reinterpret_cast<Ark_NativePointer>(callManagedRadioModifierBuilderSync);
        case Kind_RatingModifierBuilder: return reinterpret_cast<Ark_NativePointer>(callManagedRatingModifierBuilderSync);
        case Kind_RestrictedWorker_onerror_Callback: return reinterpret_cast<Ark_NativePointer>(callManagedRestrictedWorker_onerror_CallbackSync);
        case Kind_RestrictedWorker_onexit_Callback: return reinterpret_cast<Ark_NativePointer>(callManagedRestrictedWorker_onexit_CallbackSync);
        case Kind_RestrictedWorker_onmessage_Callback: return reinterpret_cast<Ark_NativePointer>(callManagedRestrictedWorker_onmessage_CallbackSync);
        case Kind_ReuseIdCallback: return reinterpret_cast<Ark_NativePointer>(callManagedReuseIdCallbackSync);
        case Kind_SaveButtonCallback: return reinterpret_cast<Ark_NativePointer>(callManagedSaveButtonCallbackSync);
        case Kind_ScrollOnScrollCallback: return reinterpret_cast<Ark_NativePointer>(callManagedScrollOnScrollCallbackSync);
        case Kind_ScrollOnWillScrollCallback: return reinterpret_cast<Ark_NativePointer>(callManagedScrollOnWillScrollCallbackSync);
        case Kind_SearchSubmitCallback: return reinterpret_cast<Ark_NativePointer>(callManagedSearchSubmitCallbackSync);
        case Kind_SearchValueCallback: return reinterpret_cast<Ark_NativePointer>(callManagedSearchValueCallbackSync);
        case Kind_ShouldBuiltInRecognizerParallelWithCallback: return reinterpret_cast<Ark_NativePointer>(callManagedShouldBuiltInRecognizerParallelWithCallbackSync);
        case Kind_SizeChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedSizeChangeCallbackSync);
        case Kind_SliderModifierBuilder: return reinterpret_cast<Ark_NativePointer>(callManagedSliderModifierBuilderSync);
        case Kind_SliderTriggerChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedSliderTriggerChangeCallbackSync);
        case Kind_StyledStringMarshallCallback: return reinterpret_cast<Ark_NativePointer>(callManagedStyledStringMarshallCallbackSync);
        case Kind_StyledStringUnmarshallCallback: return reinterpret_cast<Ark_NativePointer>(callManagedStyledStringUnmarshallCallbackSync);
        case Kind_SubmitCallback: return reinterpret_cast<Ark_NativePointer>(callManagedSubmitCallbackSync);
        case Kind_TabsCustomContentTransitionCallback: return reinterpret_cast<Ark_NativePointer>(callManagedTabsCustomContentTransitionCallbackSync);
        case Kind_TextAreaSubmitCallback: return reinterpret_cast<Ark_NativePointer>(callManagedTextAreaSubmitCallbackSync);
        case Kind_TextClockModifierBuilder: return reinterpret_cast<Ark_NativePointer>(callManagedTextClockModifierBuilderSync);
        case Kind_TextFieldValueCallback: return reinterpret_cast<Ark_NativePointer>(callManagedTextFieldValueCallbackSync);
        case Kind_TextPickerEnterSelectedAreaCallback: return reinterpret_cast<Ark_NativePointer>(callManagedTextPickerEnterSelectedAreaCallbackSync);
        case Kind_TextPickerScrollStopCallback: return reinterpret_cast<Ark_NativePointer>(callManagedTextPickerScrollStopCallbackSync);
        case Kind_TextTimerModifierBuilder: return reinterpret_cast<Ark_NativePointer>(callManagedTextTimerModifierBuilderSync);
        case Kind_ToggleModifierBuilder: return reinterpret_cast<Ark_NativePointer>(callManagedToggleModifierBuilderSync);
        case Kind_TransitionFinishCallback: return reinterpret_cast<Ark_NativePointer>(callManagedTransitionFinishCallbackSync);
        case Kind_Type_CommonMethod_onDragStart: return reinterpret_cast<Ark_NativePointer>(callManagedType_CommonMethod_onDragStartSync);
        case Kind_Type_NavigationAttribute_customNavContentTransition: return reinterpret_cast<Ark_NativePointer>(callManagedType_NavigationAttribute_customNavContentTransitionSync);
        case Kind_UpdateTransitionCallback: return reinterpret_cast<Ark_NativePointer>(callManagedUpdateTransitionCallbackSync);
        case Kind_VisibleAreaChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedVisibleAreaChangeCallbackSync);
        case Kind_VoidCallback: return reinterpret_cast<Ark_NativePointer>(callManagedVoidCallbackSync);
    }
    return nullptr;
}