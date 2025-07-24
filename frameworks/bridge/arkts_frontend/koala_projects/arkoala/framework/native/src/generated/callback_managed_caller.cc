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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_AccessibilityCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(isHover);
    argsSerializer.writeAccessibilityHoverEvent(event);
    enqueueCallback(&_buffer);
}
void callManagedAccessibilityCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Boolean isHover, Ark_AccessibilityHoverEvent event)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_AccessibilityCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(isHover);
    argsSerializer.writeAccessibilityHoverEvent(event);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedAccessibilityFocusCallback(Ark_Int32 resourceId, Ark_Boolean isFocus)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = { resourceId, holdManagedCallbackResource,
        releaseManagedCallbackResource };
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer =
        Serializer((KSerializerBuffer) & (_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_AccessibilityFocusCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(isFocus);
    enqueueCallback(&_buffer);
}
void callManagedAccessibilityFocusCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Boolean isFocus)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_AccessibilityFocusCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(isFocus);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedAsyncCallback_Array_TextMenuItem_Array_TextMenuItem(Ark_Int32 resourceId, Array_TextMenuItem menuItems, Callback_Array_TextMenuItem_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_AsyncCallback_Array_TextMenuItem_Array_TextMenuItem);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(menuItems.length);
    for (int i = 0; i < menuItems.length; i++) {
        const Ark_TextMenuItem menuItems_element = menuItems.array[i];
        argsSerializer.writeTextMenuItem(menuItems_element);
    }
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedAsyncCallback_Array_TextMenuItem_Array_TextMenuItemSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Array_TextMenuItem menuItems, Callback_Array_TextMenuItem_Void continuation)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_AsyncCallback_Array_TextMenuItem_Array_TextMenuItem);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(menuItems.length);
    for (int i = 0; i < menuItems.length; i++) {
        const Ark_TextMenuItem menuItems_element = menuItems.array[i];
        argsSerializer.writeTextMenuItem(menuItems_element);
    }
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedAsyncCallback_image_PixelMap_Void(Ark_Int32 resourceId, Ark_PixelMap result)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_AsyncCallback_image_PixelMap_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePixelMap(result);
    enqueueCallback(&_buffer);
}
void callManagedAsyncCallback_image_PixelMap_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_PixelMap result)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_AsyncCallback_image_PixelMap_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePixelMap(result);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedAsyncCallback_TextMenuItem_TextRange_Boolean(Ark_Int32 resourceId, Ark_TextMenuItem menuItem, Ark_TextRange range, Callback_Boolean_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_AsyncCallback_TextMenuItem_TextRange_Boolean);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeTextMenuItem(menuItem);
    argsSerializer.writeTextRange(range);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedAsyncCallback_TextMenuItem_TextRange_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_TextMenuItem menuItem, Ark_TextRange range, Callback_Boolean_Void continuation)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_AsyncCallback_TextMenuItem_TextRange_Boolean);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeTextMenuItem(menuItem);
    argsSerializer.writeTextRange(range);
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_ButtonTriggerClickCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(xPos);
    argsSerializer.writeNumber(yPos);
    enqueueCallback(&_buffer);
}
void callManagedButtonTriggerClickCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number xPos, Ark_Number yPos)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_ButtonTriggerClickCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(xPos);
    argsSerializer.writeNumber(yPos);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Any_Void(Ark_Int32 resourceId, Ark_Object info)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Any_Void);
    argsSerializer.writeInt32(resourceId);
    const Ark_CallbackResource arg0Resource = {info.resource.resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&arg0Resource);
    argsSerializer.writeObject(info);
    enqueueCallback(&_buffer);
}
void callManagedCallback_Any_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Object info)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Any_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeObject(info);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Area_Area_Void(Ark_Int32 resourceId, Ark_Area oldValue, Ark_Area newValue)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Area_Area_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeArea(oldValue);
    argsSerializer.writeArea(newValue);
    enqueueCallback(&_buffer);
}
void callManagedCallback_Area_Area_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Area oldValue, Ark_Area newValue)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Area_Area_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeArea(oldValue);
    argsSerializer.writeArea(newValue);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Array_Number_Void(Ark_Int32 resourceId, Array_Number input)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Array_TextMenuItem_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(value.length);
    for (int i = 0; i < value.length; i++) {
        const Ark_TextMenuItem value_element = value.array[i];
        argsSerializer.writeTextMenuItem(value_element);
    }
    enqueueCallback(&_buffer);
}
void callManagedCallback_Array_TextMenuItem_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Array_TextMenuItem value)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Array_TextMenuItem_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(value.length);
    for (int i = 0; i < value.length; i++) {
        const Ark_TextMenuItem value_element = value.array[i];
        argsSerializer.writeTextMenuItem(value_element);
    }
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Array_TouchTestInfo_TouchResult(Ark_Int32 resourceId, Array_TouchTestInfo value, Callback_TouchResult_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Array_TouchTestInfo_TouchResult);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(value.length);
    for (int i = 0; i < value.length; i++) {
        const Ark_TouchTestInfo value_element = value.array[i];
        argsSerializer.writeTouchTestInfo(value_element);
    }
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedCallback_Array_TouchTestInfo_TouchResultSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Array_TouchTestInfo value, Callback_TouchResult_Void continuation)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Array_TouchTestInfo_TouchResult);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(value.length);
    for (int i = 0; i < value.length; i++) {
        const Ark_TouchTestInfo value_element = value.array[i];
        argsSerializer.writeTouchTestInfo(value_element);
    }
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_AxisEvent_Void(Ark_Int32 resourceId, Ark_AxisEvent parameter)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_AxisEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeAxisEvent(parameter);
    enqueueCallback(&_buffer);
}
void callManagedCallback_AxisEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_AxisEvent parameter)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_AxisEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeAxisEvent(parameter);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Boolean(Ark_Int32 resourceId, Callback_Boolean_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Boolean_HoverEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(isHover);
    argsSerializer.writeHoverEvent(event);
    enqueueCallback(&_buffer);
}
void callManagedCallback_Boolean_HoverEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Boolean isHover, Ark_HoverEvent event)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Boolean_HoverEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(isHover);
    argsSerializer.writeHoverEvent(event);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Boolean_Void(Ark_Int32 resourceId, Ark_Boolean isVisible)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Boolean_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(isVisible);
    enqueueCallback(&_buffer);
}
void callManagedCallback_Boolean_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Boolean isVisible)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Boolean_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(isVisible);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Buffer_Void(Ark_Int32 resourceId, Ark_Buffer value)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Buffer_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBuffer(value);
    enqueueCallback(&_buffer);
}
void callManagedCallback_Buffer_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Buffer value)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_CalendarRequestedData_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeCalendarRequestedData(event);
    enqueueCallback(&_buffer);
}
void callManagedCallback_CalendarRequestedData_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_CalendarRequestedData event)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_CalendarRequestedData_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeCalendarRequestedData(event);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_CalendarSelectedDate_Void(Ark_Int32 resourceId, Ark_CalendarSelectedDate event)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_CalendarSelectedDate_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeCalendarSelectedDate(event);
    enqueueCallback(&_buffer);
}
void callManagedCallback_CalendarSelectedDate_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_CalendarSelectedDate event)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_CalendarSelectedDate_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeCalendarSelectedDate(event);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_ClickEvent_Void(Ark_Int32 resourceId, Ark_ClickEvent event)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_ClickEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeClickEvent(event);
    enqueueCallback(&_buffer);
}
void callManagedCallback_ClickEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_ClickEvent event)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_ClickEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeClickEvent(event);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_ComputedBarAttribute_Void(Ark_Int32 resourceId, Ark_ComputedBarAttribute value)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_ComputedBarAttribute_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeComputedBarAttribute(value);
    enqueueCallback(&_buffer);
}
void callManagedCallback_ComputedBarAttribute_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_ComputedBarAttribute value)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_ComputedBarAttribute_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeComputedBarAttribute(value);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_CopyEvent_Void(Ark_Int32 resourceId, Ark_CopyEvent parameter)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_CopyEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeCopyEvent(parameter);
    enqueueCallback(&_buffer);
}
void callManagedCallback_CopyEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_CopyEvent parameter)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_CopyEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeCopyEvent(parameter);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_CreateItem(Ark_Int32 resourceId, Ark_Int32 index, Callback_Pointer_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_CreateItem);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_CrownEvent_Void(Ark_Int32 resourceId, Ark_CrownEvent parameter)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_CrownEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeCrownEvent(parameter);
    enqueueCallback(&_buffer);
}
void callManagedCallback_CrownEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_CrownEvent parameter)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_CrownEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeCrownEvent(parameter);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_CustomBuilder_Void(Ark_Int32 resourceId, CustomNodeBuilder value)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_CustomBuilder_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeCallbackResource(value.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(value.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(value.callSync));
    enqueueCallback(&_buffer);
}
void callManagedCallback_CustomBuilder_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, CustomNodeBuilder value)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_CustomBuilder_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeCallbackResource(value.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(value.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(value.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_CutEvent_Void(Ark_Int32 resourceId, Ark_CutEvent parameter)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_CutEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeCutEvent(parameter);
    enqueueCallback(&_buffer);
}
void callManagedCallback_CutEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_CutEvent parameter)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_CutEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeCutEvent(parameter);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Date_Void(Ark_Int32 resourceId, Ark_Date parameter)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Date_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt64(parameter);
    enqueueCallback(&_buffer);
}
void callManagedCallback_Date_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Date parameter)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Date_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt64(parameter);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_DatePickerResult_Void(Ark_Int32 resourceId, Ark_DatePickerResult value)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_DatePickerResult_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeDatePickerResult(value);
    enqueueCallback(&_buffer);
}
void callManagedCallback_DatePickerResult_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_DatePickerResult value)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_DatePickerResult_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeDatePickerResult(value);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_DeleteValue_Boolean(Ark_Int32 resourceId, Ark_DeleteValue parameter, Callback_Boolean_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_DeleteValue_Boolean);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeDeleteValue(parameter);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedCallback_DeleteValue_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_DeleteValue parameter, Callback_Boolean_Void continuation)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_DeleteValue_Boolean);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeDeleteValue(parameter);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_DeleteValue_Void(Ark_Int32 resourceId, Ark_DeleteValue parameter)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_DeleteValue_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeDeleteValue(parameter);
    enqueueCallback(&_buffer);
}
void callManagedCallback_DeleteValue_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_DeleteValue parameter)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_DeleteValue_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeDeleteValue(parameter);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_DismissContentCoverAction_Void(Ark_Int32 resourceId, Ark_DismissContentCoverAction parameter)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_DismissContentCoverAction_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeDismissContentCoverAction(parameter);
    enqueueCallback(&_buffer);
}
void callManagedCallback_DismissContentCoverAction_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_DismissContentCoverAction parameter)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_DismissContentCoverAction_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeDismissContentCoverAction(parameter);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_DismissDialogAction_Void(Ark_Int32 resourceId, Ark_DismissDialogAction parameter)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_DismissDialogAction_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeDismissDialogAction(parameter);
    enqueueCallback(&_buffer);
}
void callManagedCallback_DismissDialogAction_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_DismissDialogAction parameter)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_DismissDialogAction_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeDismissDialogAction(parameter);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_DismissPopupAction_Void(Ark_Int32 resourceId, Ark_DismissPopupAction parameter)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_DismissPopupAction_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeDismissPopupAction(parameter);
    enqueueCallback(&_buffer);
}
void callManagedCallback_DismissPopupAction_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_DismissPopupAction parameter)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_DismissPopupAction_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeDismissPopupAction(parameter);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_DismissSheetAction_Void(Ark_Int32 resourceId, Ark_DismissSheetAction parameter)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_DismissSheetAction_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeDismissSheetAction(parameter);
    enqueueCallback(&_buffer);
}
void callManagedCallback_DismissSheetAction_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_DismissSheetAction parameter)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_DismissSheetAction_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeDismissSheetAction(parameter);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_DragEvent_String_Union_CustomBuilder_DragItemInfo(Ark_Int32 resourceId, Ark_DragEvent event, Opt_String extraParams, Callback_Union_CustomBuilder_DragItemInfo_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeDragEvent(event);
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
void callManagedCallback_DragEvent_String_Union_CustomBuilder_DragItemInfoSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_DragEvent event, Opt_String extraParams, Callback_Union_CustomBuilder_DragItemInfo_Void continuation)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeDragEvent(event);
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
void callManagedCallback_DragEvent_String_Void(Ark_Int32 resourceId, Ark_DragEvent event, Opt_String extraParams)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_DragEvent_String_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeDragEvent(event);
    Ark_Int32 extraParams_type = INTEROP_RUNTIME_UNDEFINED;
    extraParams_type = runtimeType(extraParams);
    argsSerializer.writeInt8(extraParams_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (extraParams_type)) {
        const auto extraParams_value = extraParams.value;
        argsSerializer.writeString(extraParams_value);
    }
    enqueueCallback(&_buffer);
}
void callManagedCallback_DragEvent_String_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_DragEvent event, Opt_String extraParams)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_DragEvent_String_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeDragEvent(event);
    Ark_Int32 extraParams_type = INTEROP_RUNTIME_UNDEFINED;
    extraParams_type = runtimeType(extraParams);
    argsSerializer.writeInt8(extraParams_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (extraParams_type)) {
        const auto extraParams_value = extraParams.value;
        argsSerializer.writeString(extraParams_value);
    }
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_EditableTextChangeValue_Boolean(Ark_Int32 resourceId, Ark_EditableTextChangeValue parameter, Callback_Boolean_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_EditableTextChangeValue_Boolean);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeEditableTextChangeValue(parameter);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedCallback_EditableTextChangeValue_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_EditableTextChangeValue parameter, Callback_Boolean_Void continuation)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_EditableTextChangeValue_Boolean);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeEditableTextChangeValue(parameter);
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_EnterKeyType_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_EnterKeyType>(enterKey));
    enqueueCallback(&_buffer);
}
void callManagedCallback_EnterKeyType_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_EnterKeyType enterKey)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Extender_OnFinish);
    argsSerializer.writeInt32(resourceId);
    enqueueCallback(&_buffer);
}
void callManagedCallback_Extender_OnFinishSync(Ark_VMContext vmContext, Ark_Int32 resourceId)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Extender_OnFinish);
    argsSerializer.writeInt32(resourceId);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Extender_OnProgress(Ark_Int32 resourceId, Ark_Float32 value)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Extender_OnProgress);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFloat32(value);
    enqueueCallback(&_buffer);
}
void callManagedCallback_Extender_OnProgressSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Float32 value)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Extender_OnProgress);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFloat32(value);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_FocusAxisEvent_Void(Ark_Int32 resourceId, Ark_FocusAxisEvent parameter)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_FocusAxisEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFocusAxisEvent(parameter);
    enqueueCallback(&_buffer);
}
void callManagedCallback_FocusAxisEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_FocusAxisEvent parameter)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_FocusAxisEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFocusAxisEvent(parameter);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_FormCallbackInfo_Void(Ark_Int32 resourceId, Ark_FormCallbackInfo parameter)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_FormCallbackInfo_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFormCallbackInfo(parameter);
    enqueueCallback(&_buffer);
}
void callManagedCallback_FormCallbackInfo_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_FormCallbackInfo parameter)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_FormCallbackInfo_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFormCallbackInfo(parameter);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_FullscreenInfo_Void(Ark_Int32 resourceId, Ark_FullscreenInfo parameter)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_FullscreenInfo_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFullscreenInfo(parameter);
    enqueueCallback(&_buffer);
}
void callManagedCallback_FullscreenInfo_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_FullscreenInfo parameter)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_FullscreenInfo_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFullscreenInfo(parameter);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_GestureEvent_Void(Ark_Int32 resourceId, Ark_GestureEvent event)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_GestureEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeGestureEvent(event);
    enqueueCallback(&_buffer);
}
void callManagedCallback_GestureEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_GestureEvent event)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_GestureEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeGestureEvent(event);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_GestureInfo_BaseGestureEvent_GestureJudgeResult(Ark_Int32 resourceId, Ark_GestureInfo gestureInfo, Ark_BaseGestureEvent event, Callback_GestureJudgeResult_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeGestureInfo(gestureInfo);
    argsSerializer.writeBaseGestureEvent(event);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedCallback_GestureInfo_BaseGestureEvent_GestureJudgeResultSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_GestureInfo gestureInfo, Ark_BaseGestureEvent event, Callback_GestureJudgeResult_Void continuation)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeGestureInfo(gestureInfo);
    argsSerializer.writeBaseGestureEvent(event);
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_GestureJudgeResult_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_GestureJudgeResult>(value));
    enqueueCallback(&_buffer);
}
void callManagedCallback_GestureJudgeResult_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_GestureJudgeResult value)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_GestureRecognizer_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeGestureRecognizer(value);
    enqueueCallback(&_buffer);
}
void callManagedCallback_GestureRecognizer_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_GestureRecognizer value)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_GestureRecognizer_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeGestureRecognizer(value);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_HitTestMode_Void(Ark_Int32 resourceId, Ark_HitTestMode value)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_HitTestMode_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_HitTestMode>(value));
    enqueueCallback(&_buffer);
}
void callManagedCallback_HitTestMode_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_HitTestMode value)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_HitTestMode_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_HitTestMode>(value));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_HoverEvent_Void(Ark_Int32 resourceId, Ark_HoverEvent parameter)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_HoverEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeHoverEvent(parameter);
    enqueueCallback(&_buffer);
}
void callManagedCallback_HoverEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_HoverEvent parameter)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_HoverEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeHoverEvent(parameter);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_InsertValue_Boolean(Ark_Int32 resourceId, Ark_InsertValue parameter, Callback_Boolean_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_InsertValue_Boolean);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInsertValue(parameter);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedCallback_InsertValue_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_InsertValue parameter, Callback_Boolean_Void continuation)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_InsertValue_Boolean);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInsertValue(parameter);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_InsertValue_Void(Ark_Int32 resourceId, Ark_InsertValue parameter)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_InsertValue_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInsertValue(parameter);
    enqueueCallback(&_buffer);
}
void callManagedCallback_InsertValue_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_InsertValue parameter)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_InsertValue_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInsertValue(parameter);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_ItemDragInfo_Number_Number_Boolean_Void(Ark_Int32 resourceId, Ark_ItemDragInfo event, Ark_Number itemIndex, Ark_Number insertIndex, Ark_Boolean isSuccess)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_ItemDragInfo_Number_Number_Boolean_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeItemDragInfo(event);
    argsSerializer.writeNumber(itemIndex);
    argsSerializer.writeNumber(insertIndex);
    argsSerializer.writeBoolean(isSuccess);
    enqueueCallback(&_buffer);
}
void callManagedCallback_ItemDragInfo_Number_Number_Boolean_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_ItemDragInfo event, Ark_Number itemIndex, Ark_Number insertIndex, Ark_Boolean isSuccess)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_ItemDragInfo_Number_Number_Boolean_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeItemDragInfo(event);
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_ItemDragInfo_Number_Number_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeItemDragInfo(event);
    argsSerializer.writeNumber(itemIndex);
    argsSerializer.writeNumber(insertIndex);
    enqueueCallback(&_buffer);
}
void callManagedCallback_ItemDragInfo_Number_Number_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_ItemDragInfo event, Ark_Number itemIndex, Ark_Number insertIndex)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_ItemDragInfo_Number_Number_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeItemDragInfo(event);
    argsSerializer.writeNumber(itemIndex);
    argsSerializer.writeNumber(insertIndex);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_ItemDragInfo_Number_Void(Ark_Int32 resourceId, Ark_ItemDragInfo event, Ark_Number itemIndex)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_ItemDragInfo_Number_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeItemDragInfo(event);
    argsSerializer.writeNumber(itemIndex);
    enqueueCallback(&_buffer);
}
void callManagedCallback_ItemDragInfo_Number_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_ItemDragInfo event, Ark_Number itemIndex)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_ItemDragInfo_Number_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeItemDragInfo(event);
    argsSerializer.writeNumber(itemIndex);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_ItemDragInfo_Void(Ark_Int32 resourceId, Ark_ItemDragInfo event)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_ItemDragInfo_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeItemDragInfo(event);
    enqueueCallback(&_buffer);
}
void callManagedCallback_ItemDragInfo_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_ItemDragInfo event)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_ItemDragInfo_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeItemDragInfo(event);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_KeyEvent_Boolean(Ark_Int32 resourceId, Ark_KeyEvent parameter, Callback_Boolean_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_KeyEvent_Boolean);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeKeyEvent(parameter);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedCallback_KeyEvent_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_KeyEvent parameter, Callback_Boolean_Void continuation)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_KeyEvent_Boolean);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeKeyEvent(parameter);
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_KeyEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeKeyEvent(event);
    enqueueCallback(&_buffer);
}
void callManagedCallback_KeyEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_KeyEvent event)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_KeyEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeKeyEvent(event);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Literal_Boolean_isVisible_Void(Ark_Int32 resourceId, Ark_Literal_Boolean_isVisible event)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Literal_Boolean_isVisible_Void);
    argsSerializer.writeInt32(resourceId);
    const auto event_isVisible = event.isVisible;
    argsSerializer.writeBoolean(event_isVisible);
    enqueueCallback(&_buffer);
}
void callManagedCallback_Literal_Boolean_isVisible_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Literal_Boolean_isVisible event)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Literal_Boolean_isVisible_Void);
    argsSerializer.writeInt32(resourceId);
    const auto event_isVisible = event.isVisible;
    argsSerializer.writeBoolean(event_isVisible);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Literal_Function_handler_Object_error_Void(Ark_Int32 resourceId, Opt_Literal_Function_handler_Object_error event)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Literal_Function_handler_Object_error_Void);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 event_type = INTEROP_RUNTIME_UNDEFINED;
    event_type = runtimeType(event);
    argsSerializer.writeInt8(event_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (event_type)) {
        const auto event_value = event.value;
        const auto event_value_handler = event_value.handler;
        argsSerializer.writeFunction(event_value_handler);
        const auto event_value_error = event_value.error;
        argsSerializer.writeObject(event_value_error);
    }
    enqueueCallback(&_buffer);
}
void callManagedCallback_Literal_Function_handler_Object_error_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Opt_Literal_Function_handler_Object_error event)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Literal_Function_handler_Object_error_Void);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 event_type = INTEROP_RUNTIME_UNDEFINED;
    event_type = runtimeType(event);
    argsSerializer.writeInt8(event_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (event_type)) {
        const auto event_value = event.value;
        const auto event_value_handler = event_value.handler;
        argsSerializer.writeFunction(event_value_handler);
        const auto event_value_error = event_value.error;
        argsSerializer.writeObject(event_value_error);
    }
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Literal_Number_code__want_Void(Ark_Int32 resourceId, Ark_Literal_Number_code__want parameter)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Literal_Number_code__want_Void);
    argsSerializer.writeInt32(resourceId);
    const auto parameter_code = parameter.code;
    argsSerializer.writeNumber(parameter_code);
    const auto parameter_want = parameter.want;
    Ark_Int32 parameter_want_type = INTEROP_RUNTIME_UNDEFINED;
    parameter_want_type = runtimeType(parameter_want);
    argsSerializer.writeInt8(parameter_want_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (parameter_want_type)) {
        const auto parameter_want_value = parameter_want.value;
        argsSerializer.writeWant(parameter_want_value);
    }
    enqueueCallback(&_buffer);
}
void callManagedCallback_Literal_Number_code__want_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Literal_Number_code__want parameter)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Literal_Number_code__want_Void);
    argsSerializer.writeInt32(resourceId);
    const auto parameter_code = parameter.code;
    argsSerializer.writeNumber(parameter_code);
    const auto parameter_want = parameter.want;
    Ark_Int32 parameter_want_type = INTEROP_RUNTIME_UNDEFINED;
    parameter_want_type = runtimeType(parameter_want);
    argsSerializer.writeInt8(parameter_want_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (parameter_want_type)) {
        const auto parameter_want_value = parameter_want.value;
        argsSerializer.writeWant(parameter_want_value);
    }
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Literal_Number_errcode_String_msg_Void(Ark_Int32 resourceId, Ark_Literal_Number_errcode_String_msg info)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Literal_Number_errcode_String_msg_Void);
    argsSerializer.writeInt32(resourceId);
    const auto info_errcode = info.errcode;
    argsSerializer.writeNumber(info_errcode);
    const auto info_msg = info.msg;
    argsSerializer.writeString(info_msg);
    enqueueCallback(&_buffer);
}
void callManagedCallback_Literal_Number_errcode_String_msg_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Literal_Number_errcode_String_msg info)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Literal_Number_errcode_String_msg_Void);
    argsSerializer.writeInt32(resourceId);
    const auto info_errcode = info.errcode;
    argsSerializer.writeNumber(info_errcode);
    const auto info_msg = info.msg;
    argsSerializer.writeString(info_msg);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Literal_Number_offsetRemain_Void(Ark_Int32 resourceId, Ark_Literal_Number_offsetRemain value)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Literal_Number_offsetRemain_Void);
    argsSerializer.writeInt32(resourceId);
    const auto value_offsetRemain = value.offsetRemain;
    argsSerializer.writeNumber(value_offsetRemain);
    enqueueCallback(&_buffer);
}
void callManagedCallback_Literal_Number_offsetRemain_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Literal_Number_offsetRemain value)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Literal_Number_offsetRemain_Void);
    argsSerializer.writeInt32(resourceId);
    const auto value_offsetRemain = value.offsetRemain;
    argsSerializer.writeNumber(value_offsetRemain);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Literal_Object_detail_Boolean(Ark_Int32 resourceId, Opt_Literal_Object_detail event, Callback_Boolean_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Literal_Object_detail_Boolean);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 event_type = INTEROP_RUNTIME_UNDEFINED;
    event_type = runtimeType(event);
    argsSerializer.writeInt8(event_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (event_type)) {
        const auto event_value = event.value;
        const auto event_value_detail = event_value.detail;
        argsSerializer.writeObject(event_value_detail);
    }
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedCallback_Literal_Object_detail_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Opt_Literal_Object_detail event, Callback_Boolean_Void continuation)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Literal_Object_detail_Boolean);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 event_type = INTEROP_RUNTIME_UNDEFINED;
    event_type = runtimeType(event);
    argsSerializer.writeInt8(event_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (event_type)) {
        const auto event_value = event.value;
        const auto event_value_detail = event_value.detail;
        argsSerializer.writeObject(event_value_detail);
    }
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Literal_String_plainText_Void(Ark_Int32 resourceId, Ark_Literal_String_plainText selectedText)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Literal_String_plainText_Void);
    argsSerializer.writeInt32(resourceId);
    const auto selectedText_plainText = selectedText.plainText;
    argsSerializer.writeString(selectedText_plainText);
    enqueueCallback(&_buffer);
}
void callManagedCallback_Literal_String_plainText_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Literal_String_plainText selectedText)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Literal_String_plainText_Void);
    argsSerializer.writeInt32(resourceId);
    const auto selectedText_plainText = selectedText.plainText;
    argsSerializer.writeString(selectedText_plainText);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Map_String_Object_Void(Ark_Int32 resourceId, Map_String_Object parameter)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Map_String_Object_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(parameter.size);
    for (int32_t i = 0; i < parameter.size; i++) {
        auto parameter_key = parameter.keys[i];
        auto parameter_value = parameter.values[i];
        argsSerializer.writeString(parameter_key);
        argsSerializer.writeObject(parameter_value);
    }
    enqueueCallback(&_buffer);
}
void callManagedCallback_Map_String_Object_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Map_String_Object parameter)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Map_String_Object_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(parameter.size);
    for (int32_t i = 0; i < parameter.size; i++) {
        auto parameter_key = parameter.keys[i];
        auto parameter_value = parameter.values[i];
        argsSerializer.writeString(parameter_key);
        argsSerializer.writeObject(parameter_value);
    }
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_MarqueeState_Void(Ark_Int32 resourceId, Ark_MarqueeState parameter)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_MarqueeState_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_MarqueeState>(parameter));
    enqueueCallback(&_buffer);
}
void callManagedCallback_MarqueeState_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_MarqueeState parameter)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_MarqueeState_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_MarqueeState>(parameter));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_MouseEvent_Void(Ark_Int32 resourceId, Ark_MouseEvent event)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_MouseEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeMouseEvent(event);
    enqueueCallback(&_buffer);
}
void callManagedCallback_MouseEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_MouseEvent event)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_MouseEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeMouseEvent(event);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_NativeEmbedDataInfo_Void(Ark_Int32 resourceId, Ark_NativeEmbedDataInfo event)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_NativeEmbedDataInfo_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNativeEmbedDataInfo(event);
    enqueueCallback(&_buffer);
}
void callManagedCallback_NativeEmbedDataInfo_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NativeEmbedDataInfo event)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_NativeEmbedDataInfo_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNativeEmbedDataInfo(event);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_NativeEmbedTouchInfo_Void(Ark_Int32 resourceId, Ark_NativeEmbedTouchInfo event)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_NativeEmbedTouchInfo_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNativeEmbedTouchInfo(event);
    enqueueCallback(&_buffer);
}
void callManagedCallback_NativeEmbedTouchInfo_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NativeEmbedTouchInfo event)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_NativeEmbedTouchInfo_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNativeEmbedTouchInfo(event);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_NavDestinationActiveReason_Void(Ark_Int32 resourceId, Ark_NavDestinationActiveReason parameter)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_NavDestinationActiveReason_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_NavDestinationActiveReason>(parameter));
    enqueueCallback(&_buffer);
}
void callManagedCallback_NavDestinationActiveReason_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NavDestinationActiveReason parameter)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_NavDestinationActiveReason_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_NavDestinationActiveReason>(parameter));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_NavDestinationContext_Void(Ark_Int32 resourceId, Ark_NavDestinationContext parameter)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_NavDestinationContext_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNavDestinationContext(parameter);
    enqueueCallback(&_buffer);
}
void callManagedCallback_NavDestinationContext_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NavDestinationContext parameter)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_NavDestinationContext_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNavDestinationContext(parameter);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_NavigationMode_Void(Ark_Int32 resourceId, Ark_NavigationMode mode)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_NavigationMode_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_NavigationMode>(mode));
    enqueueCallback(&_buffer);
}
void callManagedCallback_NavigationMode_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NavigationMode mode)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_NavigationTitleMode_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_NavigationTitleMode>(titleMode));
    enqueueCallback(&_buffer);
}
void callManagedCallback_NavigationTitleMode_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NavigationTitleMode titleMode)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_NavigationTransitionProxy_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNavigationTransitionProxy(transitionProxy);
    enqueueCallback(&_buffer);
}
void callManagedCallback_NavigationTransitionProxy_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NavigationTransitionProxy transitionProxy)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_NavigationTransitionProxy_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNavigationTransitionProxy(transitionProxy);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Number_Boolean(Ark_Int32 resourceId, Ark_Number index, Callback_Boolean_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Number_Boolean);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(index);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedCallback_Number_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number index, Callback_Boolean_Void continuation)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Number_Boolean);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(index);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Number_Number_Boolean(Ark_Int32 resourceId, Ark_Number from, Ark_Number to, Callback_Boolean_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Number_Number_Boolean);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(from);
    argsSerializer.writeNumber(to);
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Number_Number_Number_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(start);
    argsSerializer.writeNumber(end);
    argsSerializer.writeNumber(center);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Number_Number_PanelMode_Void(Ark_Int32 resourceId, Ark_Number width, Ark_Number height, Ark_PanelMode mode)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Number_Number_PanelMode_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(width);
    argsSerializer.writeNumber(height);
    argsSerializer.writeInt32(static_cast<Ark_PanelMode>(mode));
    enqueueCallback(&_buffer);
}
void callManagedCallback_Number_Number_PanelMode_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number width, Ark_Number height, Ark_PanelMode mode)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Number_Number_PanelMode_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(width);
    argsSerializer.writeNumber(height);
    argsSerializer.writeInt32(static_cast<Ark_PanelMode>(mode));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Number_Number_Void(Ark_Int32 resourceId, Ark_Number first, Ark_Number last)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Number_Number_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(first);
    argsSerializer.writeNumber(last);
    enqueueCallback(&_buffer);
}
void callManagedCallback_Number_Number_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number first, Ark_Number last)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Number_Number_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(first);
    argsSerializer.writeNumber(last);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Number_ScrollState_Literal_Number_offsetRemain(Ark_Int32 resourceId, Ark_Number offset, Ark_ScrollState state, Callback_Literal_Number_offsetRemain_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Number_ScrollState_Literal_Number_offsetRemain);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(offset);
    argsSerializer.writeInt32(static_cast<Ark_ScrollState>(state));
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedCallback_Number_ScrollState_Literal_Number_offsetRemainSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number offset, Ark_ScrollState state, Callback_Literal_Number_offsetRemain_Void continuation)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Number_ScrollState_Literal_Number_offsetRemain);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(offset);
    argsSerializer.writeInt32(static_cast<Ark_ScrollState>(state));
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Number_SliderChangeMode_Void(Ark_Int32 resourceId, Ark_Number value, Ark_SliderChangeMode mode)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Number_SliderChangeMode_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(value);
    argsSerializer.writeInt32(static_cast<Ark_SliderChangeMode>(mode));
    enqueueCallback(&_buffer);
}
void callManagedCallback_Number_SliderChangeMode_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number value, Ark_SliderChangeMode mode)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Number_SliderChangeMode_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(value);
    argsSerializer.writeInt32(static_cast<Ark_SliderChangeMode>(mode));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Number_String_Void(Ark_Int32 resourceId, Ark_Number index, Ark_String value)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Number_String_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(index);
    argsSerializer.writeString(value);
    enqueueCallback(&_buffer);
}
void callManagedCallback_Number_String_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number index, Ark_String value)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Number_String_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(index);
    argsSerializer.writeString(value);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Number_Tuple_Number_Number(Ark_Int32 resourceId, Ark_Number index, Callback_Tuple_Number_Number_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Number_Tuple_Number_Number_Number_Number);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(index);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Number_Void(Ark_Int32 resourceId, Ark_Number index)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Number_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(index);
    enqueueCallback(&_buffer);
}
void callManagedCallback_Number_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number index)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Number_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(index);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Object_Void(Ark_Int32 resourceId, Ark_Object parameter)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Object_Void);
    argsSerializer.writeInt32(resourceId);
    const Ark_CallbackResource arg0Resource = {parameter.resource.resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&arg0Resource);
    argsSerializer.writeObject(parameter);
    enqueueCallback(&_buffer);
}
void callManagedCallback_Object_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Object parameter)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Object_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeObject(parameter);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_OffsetResult_Void(Ark_Int32 resourceId, Ark_OffsetResult value)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OffsetResult_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOffsetResult(value);
    enqueueCallback(&_buffer);
}
void callManagedCallback_OffsetResult_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OffsetResult value)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_OffsetResult_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOffsetResult(value);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_ScrollResult_Void(Ark_Int32 resourceId, Ark_ScrollResult value)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource __callbackResource = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&__callbackResource);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_ScrollResult_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeScrollResult(value);
    enqueueCallback(&_buffer);
}
void callManagedCallback_ScrollResult_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_ScrollResult value)
{
    uint8_t _buffer[60 * 4];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_ScrollResult_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeScrollResult(value);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_OnAlertEvent_Boolean(Ark_Int32 resourceId, Ark_OnAlertEvent parameter, Callback_Boolean_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnAlertEvent_Boolean);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnAlertEvent(parameter);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedCallback_OnAlertEvent_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnAlertEvent parameter, Callback_Boolean_Void continuation)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_OnAlertEvent_Boolean);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnAlertEvent(parameter);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_OnAudioStateChangedEvent_Void(Ark_Int32 resourceId, Ark_OnAudioStateChangedEvent parameter)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnAudioStateChangedEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnAudioStateChangedEvent(parameter);
    enqueueCallback(&_buffer);
}
void callManagedCallback_OnAudioStateChangedEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnAudioStateChangedEvent parameter)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_OnAudioStateChangedEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnAudioStateChangedEvent(parameter);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_OnBeforeUnloadEvent_Boolean(Ark_Int32 resourceId, Ark_OnBeforeUnloadEvent parameter, Callback_Boolean_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnBeforeUnloadEvent_Boolean);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnBeforeUnloadEvent(parameter);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedCallback_OnBeforeUnloadEvent_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnBeforeUnloadEvent parameter, Callback_Boolean_Void continuation)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_OnBeforeUnloadEvent_Boolean);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnBeforeUnloadEvent(parameter);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_OnClientAuthenticationEvent_Void(Ark_Int32 resourceId, Ark_OnClientAuthenticationEvent parameter)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnClientAuthenticationEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnClientAuthenticationEvent(parameter);
    enqueueCallback(&_buffer);
}
void callManagedCallback_OnClientAuthenticationEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnClientAuthenticationEvent parameter)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_OnClientAuthenticationEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnClientAuthenticationEvent(parameter);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_OnConfirmEvent_Boolean(Ark_Int32 resourceId, Ark_OnConfirmEvent parameter, Callback_Boolean_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnConfirmEvent_Boolean);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnConfirmEvent(parameter);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedCallback_OnConfirmEvent_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnConfirmEvent parameter, Callback_Boolean_Void continuation)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_OnConfirmEvent_Boolean);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnConfirmEvent(parameter);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_OnConsoleEvent_Boolean(Ark_Int32 resourceId, Ark_OnConsoleEvent parameter, Callback_Boolean_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnConsoleEvent_Boolean);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnConsoleEvent(parameter);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedCallback_OnConsoleEvent_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnConsoleEvent parameter, Callback_Boolean_Void continuation)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_OnConsoleEvent_Boolean);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnConsoleEvent(parameter);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_OnContextMenuShowEvent_Boolean(Ark_Int32 resourceId, Ark_OnContextMenuShowEvent parameter, Callback_Boolean_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnContextMenuShowEvent_Boolean);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnContextMenuShowEvent(parameter);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedCallback_OnContextMenuShowEvent_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnContextMenuShowEvent parameter, Callback_Boolean_Void continuation)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_OnContextMenuShowEvent_Boolean);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnContextMenuShowEvent(parameter);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_OnDataResubmittedEvent_Void(Ark_Int32 resourceId, Ark_OnDataResubmittedEvent parameter)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnDataResubmittedEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnDataResubmittedEvent(parameter);
    enqueueCallback(&_buffer);
}
void callManagedCallback_OnDataResubmittedEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnDataResubmittedEvent parameter)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_OnDataResubmittedEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnDataResubmittedEvent(parameter);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_OnDownloadStartEvent_Void(Ark_Int32 resourceId, Ark_OnDownloadStartEvent parameter)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnDownloadStartEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnDownloadStartEvent(parameter);
    enqueueCallback(&_buffer);
}
void callManagedCallback_OnDownloadStartEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnDownloadStartEvent parameter)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_OnDownloadStartEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnDownloadStartEvent(parameter);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_OnErrorReceiveEvent_Void(Ark_Int32 resourceId, Ark_OnErrorReceiveEvent parameter)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnErrorReceiveEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnErrorReceiveEvent(parameter);
    enqueueCallback(&_buffer);
}
void callManagedCallback_OnErrorReceiveEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnErrorReceiveEvent parameter)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_OnErrorReceiveEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnErrorReceiveEvent(parameter);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_OnFaviconReceivedEvent_Void(Ark_Int32 resourceId, Ark_OnFaviconReceivedEvent parameter)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnFaviconReceivedEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnFaviconReceivedEvent(parameter);
    enqueueCallback(&_buffer);
}
void callManagedCallback_OnFaviconReceivedEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnFaviconReceivedEvent parameter)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_OnFaviconReceivedEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnFaviconReceivedEvent(parameter);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_OnFirstContentfulPaintEvent_Void(Ark_Int32 resourceId, Ark_OnFirstContentfulPaintEvent parameter)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnFirstContentfulPaintEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnFirstContentfulPaintEvent(parameter);
    enqueueCallback(&_buffer);
}
void callManagedCallback_OnFirstContentfulPaintEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnFirstContentfulPaintEvent parameter)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_OnFirstContentfulPaintEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnFirstContentfulPaintEvent(parameter);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_OnGeolocationShowEvent_Void(Ark_Int32 resourceId, Ark_OnGeolocationShowEvent parameter)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnGeolocationShowEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnGeolocationShowEvent(parameter);
    enqueueCallback(&_buffer);
}
void callManagedCallback_OnGeolocationShowEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnGeolocationShowEvent parameter)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_OnGeolocationShowEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnGeolocationShowEvent(parameter);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_OnHttpAuthRequestEvent_Boolean(Ark_Int32 resourceId, Ark_OnHttpAuthRequestEvent parameter, Callback_Boolean_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnHttpAuthRequestEvent_Boolean);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnHttpAuthRequestEvent(parameter);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedCallback_OnHttpAuthRequestEvent_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnHttpAuthRequestEvent parameter, Callback_Boolean_Void continuation)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_OnHttpAuthRequestEvent_Boolean);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnHttpAuthRequestEvent(parameter);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_OnHttpErrorReceiveEvent_Void(Ark_Int32 resourceId, Ark_OnHttpErrorReceiveEvent parameter)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnHttpErrorReceiveEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnHttpErrorReceiveEvent(parameter);
    enqueueCallback(&_buffer);
}
void callManagedCallback_OnHttpErrorReceiveEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnHttpErrorReceiveEvent parameter)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_OnHttpErrorReceiveEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnHttpErrorReceiveEvent(parameter);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_OnInterceptRequestEvent_WebResourceResponse(Ark_Int32 resourceId, Ark_OnInterceptRequestEvent parameter, Callback_WebResourceResponse_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnInterceptRequestEvent_WebResourceResponse);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnInterceptRequestEvent(parameter);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedCallback_OnInterceptRequestEvent_WebResourceResponseSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnInterceptRequestEvent parameter, Callback_WebResourceResponse_Void continuation)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_OnInterceptRequestEvent_WebResourceResponse);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnInterceptRequestEvent(parameter);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_OnLoadInterceptEvent_Boolean(Ark_Int32 resourceId, Ark_OnLoadInterceptEvent parameter, Callback_Boolean_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnLoadInterceptEvent_Boolean);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnLoadInterceptEvent(parameter);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedCallback_OnLoadInterceptEvent_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnLoadInterceptEvent parameter, Callback_Boolean_Void continuation)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_OnLoadInterceptEvent_Boolean);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnLoadInterceptEvent(parameter);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_OnOverScrollEvent_Void(Ark_Int32 resourceId, Ark_OnOverScrollEvent parameter)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnOverScrollEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnOverScrollEvent(parameter);
    enqueueCallback(&_buffer);
}
void callManagedCallback_OnOverScrollEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnOverScrollEvent parameter)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_OnOverScrollEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnOverScrollEvent(parameter);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_OnPageBeginEvent_Void(Ark_Int32 resourceId, Ark_OnPageBeginEvent parameter)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnPageBeginEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnPageBeginEvent(parameter);
    enqueueCallback(&_buffer);
}
void callManagedCallback_OnPageBeginEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnPageBeginEvent parameter)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_OnPageBeginEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnPageBeginEvent(parameter);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_OnPageEndEvent_Void(Ark_Int32 resourceId, Ark_OnPageEndEvent parameter)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnPageEndEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnPageEndEvent(parameter);
    enqueueCallback(&_buffer);
}
void callManagedCallback_OnPageEndEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnPageEndEvent parameter)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_OnPageEndEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnPageEndEvent(parameter);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_OnPageVisibleEvent_Void(Ark_Int32 resourceId, Ark_OnPageVisibleEvent parameter)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnPageVisibleEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnPageVisibleEvent(parameter);
    enqueueCallback(&_buffer);
}
void callManagedCallback_OnPageVisibleEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnPageVisibleEvent parameter)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_OnPageVisibleEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnPageVisibleEvent(parameter);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_OnPermissionRequestEvent_Void(Ark_Int32 resourceId, Ark_OnPermissionRequestEvent parameter)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnPermissionRequestEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnPermissionRequestEvent(parameter);
    enqueueCallback(&_buffer);
}
void callManagedCallback_OnPermissionRequestEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnPermissionRequestEvent parameter)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_OnPermissionRequestEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnPermissionRequestEvent(parameter);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_OnProgressChangeEvent_Void(Ark_Int32 resourceId, Ark_OnProgressChangeEvent parameter)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnProgressChangeEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnProgressChangeEvent(parameter);
    enqueueCallback(&_buffer);
}
void callManagedCallback_OnProgressChangeEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnProgressChangeEvent parameter)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_OnProgressChangeEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnProgressChangeEvent(parameter);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_OnPromptEvent_Boolean(Ark_Int32 resourceId, Ark_OnPromptEvent parameter, Callback_Boolean_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnPromptEvent_Boolean);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnPromptEvent(parameter);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedCallback_OnPromptEvent_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnPromptEvent parameter, Callback_Boolean_Void continuation)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_OnPromptEvent_Boolean);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnPromptEvent(parameter);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_OnRefreshAccessedHistoryEvent_Void(Ark_Int32 resourceId, Ark_OnRefreshAccessedHistoryEvent parameter)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnRefreshAccessedHistoryEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnRefreshAccessedHistoryEvent(parameter);
    enqueueCallback(&_buffer);
}
void callManagedCallback_OnRefreshAccessedHistoryEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnRefreshAccessedHistoryEvent parameter)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_OnRefreshAccessedHistoryEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnRefreshAccessedHistoryEvent(parameter);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_OnRenderExitedEvent_Void(Ark_Int32 resourceId, Ark_OnRenderExitedEvent parameter)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnRenderExitedEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnRenderExitedEvent(parameter);
    enqueueCallback(&_buffer);
}
void callManagedCallback_OnRenderExitedEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnRenderExitedEvent parameter)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_OnRenderExitedEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnRenderExitedEvent(parameter);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_OnResourceLoadEvent_Void(Ark_Int32 resourceId, Ark_OnResourceLoadEvent parameter)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnResourceLoadEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnResourceLoadEvent(parameter);
    enqueueCallback(&_buffer);
}
void callManagedCallback_OnResourceLoadEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnResourceLoadEvent parameter)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_OnResourceLoadEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnResourceLoadEvent(parameter);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_OnScaleChangeEvent_Void(Ark_Int32 resourceId, Ark_OnScaleChangeEvent parameter)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnScaleChangeEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnScaleChangeEvent(parameter);
    enqueueCallback(&_buffer);
}
void callManagedCallback_OnScaleChangeEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnScaleChangeEvent parameter)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_OnScaleChangeEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnScaleChangeEvent(parameter);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_OnScreenCaptureRequestEvent_Void(Ark_Int32 resourceId, Ark_OnScreenCaptureRequestEvent parameter)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnScreenCaptureRequestEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnScreenCaptureRequestEvent(parameter);
    enqueueCallback(&_buffer);
}
void callManagedCallback_OnScreenCaptureRequestEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnScreenCaptureRequestEvent parameter)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_OnScreenCaptureRequestEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnScreenCaptureRequestEvent(parameter);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_OnScrollEvent_Void(Ark_Int32 resourceId, Ark_OnScrollEvent parameter)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnScrollEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnScrollEvent(parameter);
    enqueueCallback(&_buffer);
}
void callManagedCallback_OnScrollEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnScrollEvent parameter)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_OnScrollEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnScrollEvent(parameter);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_OnScrollFrameBeginHandlerResult_Void(Ark_Int32 resourceId, Ark_OnScrollFrameBeginHandlerResult value)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnScrollFrameBeginHandlerResult_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnScrollFrameBeginHandlerResult(value);
    enqueueCallback(&_buffer);
}
void callManagedCallback_OnScrollFrameBeginHandlerResult_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnScrollFrameBeginHandlerResult value)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_OnScrollFrameBeginHandlerResult_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnScrollFrameBeginHandlerResult(value);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_OnSearchResultReceiveEvent_Void(Ark_Int32 resourceId, Ark_OnSearchResultReceiveEvent parameter)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnSearchResultReceiveEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnSearchResultReceiveEvent(parameter);
    enqueueCallback(&_buffer);
}
void callManagedCallback_OnSearchResultReceiveEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnSearchResultReceiveEvent parameter)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_OnSearchResultReceiveEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnSearchResultReceiveEvent(parameter);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_OnShowFileSelectorEvent_Boolean(Ark_Int32 resourceId, Ark_OnShowFileSelectorEvent parameter, Callback_Boolean_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnShowFileSelectorEvent_Boolean);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnShowFileSelectorEvent(parameter);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedCallback_OnShowFileSelectorEvent_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnShowFileSelectorEvent parameter, Callback_Boolean_Void continuation)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_OnShowFileSelectorEvent_Boolean);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnShowFileSelectorEvent(parameter);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_OnSslErrorEventReceiveEvent_Void(Ark_Int32 resourceId, Ark_OnSslErrorEventReceiveEvent parameter)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnSslErrorEventReceiveEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnSslErrorEventReceiveEvent(parameter);
    enqueueCallback(&_buffer);
}
void callManagedCallback_OnSslErrorEventReceiveEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnSslErrorEventReceiveEvent parameter)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_OnSslErrorEventReceiveEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnSslErrorEventReceiveEvent(parameter);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_OnTitleReceiveEvent_Void(Ark_Int32 resourceId, Ark_OnTitleReceiveEvent parameter)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnTitleReceiveEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnTitleReceiveEvent(parameter);
    enqueueCallback(&_buffer);
}
void callManagedCallback_OnTitleReceiveEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnTitleReceiveEvent parameter)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_OnTitleReceiveEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnTitleReceiveEvent(parameter);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_OnTouchIconUrlReceivedEvent_Void(Ark_Int32 resourceId, Ark_OnTouchIconUrlReceivedEvent parameter)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnTouchIconUrlReceivedEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnTouchIconUrlReceivedEvent(parameter);
    enqueueCallback(&_buffer);
}
void callManagedCallback_OnTouchIconUrlReceivedEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnTouchIconUrlReceivedEvent parameter)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_OnTouchIconUrlReceivedEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnTouchIconUrlReceivedEvent(parameter);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_OnWindowNewEvent_Void(Ark_Int32 resourceId, Ark_OnWindowNewEvent parameter)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnWindowNewEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnWindowNewEvent(parameter);
    enqueueCallback(&_buffer);
}
void callManagedCallback_OnWindowNewEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnWindowNewEvent parameter)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_OnWindowNewEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnWindowNewEvent(parameter);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Opt_Array_NavDestinationTransition_Void(Ark_Int32 resourceId, Opt_Array_NavDestinationTransition value)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
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
            argsSerializer.writeNavDestinationTransition(value_value_element);
        }
    }
    enqueueCallback(&_buffer);
}
void callManagedCallback_Opt_Array_NavDestinationTransition_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Opt_Array_NavDestinationTransition value)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
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
            argsSerializer.writeNavDestinationTransition(value_value_element);
        }
    }
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Opt_Array_String_Void(Ark_Int32 resourceId, Opt_Array_String error)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
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
void callManagedCallback_Opt_Boolean_Void(Ark_Int32 resourceId, Opt_Boolean select)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Opt_Boolean_Void);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 select_type = INTEROP_RUNTIME_UNDEFINED;
    select_type = runtimeType(select);
    argsSerializer.writeInt8(select_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (select_type)) {
        const auto select_value = select.value;
        argsSerializer.writeBoolean(select_value);
    }
    enqueueCallback(&_buffer);
}
void callManagedCallback_Opt_Boolean_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Opt_Boolean select)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Opt_Boolean_Void);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 select_type = INTEROP_RUNTIME_UNDEFINED;
    select_type = runtimeType(select);
    argsSerializer.writeInt8(select_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (select_type)) {
        const auto select_value = select.value;
        argsSerializer.writeBoolean(select_value);
    }
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Opt_NavigationAnimatedTransition_Void(Ark_Int32 resourceId, Opt_NavigationAnimatedTransition value)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Opt_NavigationAnimatedTransition_Void);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 value_type = INTEROP_RUNTIME_UNDEFINED;
    value_type = runtimeType(value);
    argsSerializer.writeInt8(value_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (value_type)) {
        const auto value_value = value.value;
        argsSerializer.writeNavigationAnimatedTransition(value_value);
    }
    enqueueCallback(&_buffer);
}
void callManagedCallback_Opt_NavigationAnimatedTransition_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Opt_NavigationAnimatedTransition value)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Opt_NavigationAnimatedTransition_Void);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 value_type = INTEROP_RUNTIME_UNDEFINED;
    value_type = runtimeType(value);
    argsSerializer.writeInt8(value_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (value_type)) {
        const auto value_value = value.value;
        argsSerializer.writeNavigationAnimatedTransition(value_value);
    }
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Opt_Number_Void(Ark_Int32 resourceId, Opt_Number selected)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Opt_Number_Void);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 selected_type = INTEROP_RUNTIME_UNDEFINED;
    selected_type = runtimeType(selected);
    argsSerializer.writeInt8(selected_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (selected_type)) {
        const auto selected_value = selected.value;
        argsSerializer.writeNumber(selected_value);
    }
    enqueueCallback(&_buffer);
}
void callManagedCallback_Opt_Number_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Opt_Number selected)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Opt_Number_Void);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 selected_type = INTEROP_RUNTIME_UNDEFINED;
    selected_type = runtimeType(selected);
    argsSerializer.writeInt8(selected_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (selected_type)) {
        const auto selected_value = selected.value;
        argsSerializer.writeNumber(selected_value);
    }
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Opt_PanelMode_Void(Ark_Int32 resourceId, Opt_PanelMode mode)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Opt_PanelMode_Void);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 mode_type = INTEROP_RUNTIME_UNDEFINED;
    mode_type = runtimeType(mode);
    argsSerializer.writeInt8(mode_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (mode_type)) {
        const auto mode_value = mode.value;
        argsSerializer.writeInt32(static_cast<Ark_PanelMode>(mode_value));
    }
    enqueueCallback(&_buffer);
}
void callManagedCallback_Opt_PanelMode_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Opt_PanelMode mode)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Opt_PanelMode_Void);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 mode_type = INTEROP_RUNTIME_UNDEFINED;
    mode_type = runtimeType(mode);
    argsSerializer.writeInt8(mode_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (mode_type)) {
        const auto mode_value = mode.value;
        argsSerializer.writeInt32(static_cast<Ark_PanelMode>(mode_value));
    }
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Opt_ResourceStr_Void(Ark_Int32 resourceId, Opt_ResourceStr value)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Opt_ResourceStr_Void);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 value_type = INTEROP_RUNTIME_UNDEFINED;
    value_type = runtimeType(value);
    argsSerializer.writeInt8(value_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (value_type)) {
        const auto value_value = value.value;
        Ark_Int32 value_value_type = INTEROP_RUNTIME_UNDEFINED;
        value_value_type = value_value.selector;
        if (value_value_type == 0) {
            argsSerializer.writeInt8(0);
            const auto value_value_0 = value_value.value0;
            argsSerializer.writeString(value_value_0);
        }
        else if (value_value_type == 1) {
            argsSerializer.writeInt8(1);
            const auto value_value_1 = value_value.value1;
            argsSerializer.writeResource(value_value_1);
        }
    }
    enqueueCallback(&_buffer);
}
void callManagedCallback_Opt_ResourceStr_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Opt_ResourceStr value)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Opt_ResourceStr_Void);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 value_type = INTEROP_RUNTIME_UNDEFINED;
    value_type = runtimeType(value);
    argsSerializer.writeInt8(value_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (value_type)) {
        const auto value_value = value.value;
        Ark_Int32 value_value_type = INTEROP_RUNTIME_UNDEFINED;
        value_value_type = value_value.selector;
        if (value_value_type == 0) {
            argsSerializer.writeInt8(0);
            const auto value_value_0 = value_value.value0;
            argsSerializer.writeString(value_value_0);
        }
        else if (value_value_type == 1) {
            argsSerializer.writeInt8(1);
            const auto value_value_1 = value_value.value1;
            argsSerializer.writeResource(value_value_1);
        }
    }
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Opt_StyledString_Opt_Array_String_Void(Ark_Int32 resourceId, Opt_StyledString value, Opt_Array_String error)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Opt_StyledString_Opt_Array_String_Void);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 value_type = INTEROP_RUNTIME_UNDEFINED;
    value_type = runtimeType(value);
    argsSerializer.writeInt8(value_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (value_type)) {
        const auto value_value = value.value;
        argsSerializer.writeStyledString(value_value);
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Opt_StyledString_Opt_Array_String_Void);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 value_type = INTEROP_RUNTIME_UNDEFINED;
    value_type = runtimeType(value);
    argsSerializer.writeInt8(value_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (value_type)) {
        const auto value_value = value.value;
        argsSerializer.writeStyledString(value_value);
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Opt_TabContentAnimatedTransition_Void);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 value_type = INTEROP_RUNTIME_UNDEFINED;
    value_type = runtimeType(value);
    argsSerializer.writeInt8(value_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (value_type)) {
        const auto value_value = value.value;
        argsSerializer.writeTabContentAnimatedTransition(value_value);
    }
    enqueueCallback(&_buffer);
}
void callManagedCallback_Opt_TabContentAnimatedTransition_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Opt_TabContentAnimatedTransition value)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Opt_TabContentAnimatedTransition_Void);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 value_type = INTEROP_RUNTIME_UNDEFINED;
    value_type = runtimeType(value);
    argsSerializer.writeInt8(value_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (value_type)) {
        const auto value_value = value.value;
        argsSerializer.writeTabContentAnimatedTransition(value_value);
    }
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Opt_Union_Number_Resource_Void(Ark_Int32 resourceId, Opt_Union_Number_Resource selected)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Opt_Union_Number_Resource_Void);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 selected_type = INTEROP_RUNTIME_UNDEFINED;
    selected_type = runtimeType(selected);
    argsSerializer.writeInt8(selected_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (selected_type)) {
        const auto selected_value = selected.value;
        Ark_Int32 selected_value_type = INTEROP_RUNTIME_UNDEFINED;
        selected_value_type = selected_value.selector;
        if (selected_value_type == 0) {
            argsSerializer.writeInt8(0);
            const auto selected_value_0 = selected_value.value0;
            argsSerializer.writeNumber(selected_value_0);
        }
        else if (selected_value_type == 1) {
            argsSerializer.writeInt8(1);
            const auto selected_value_1 = selected_value.value1;
            argsSerializer.writeResource(selected_value_1);
        }
    }
    enqueueCallback(&_buffer);
}
void callManagedCallback_Opt_Union_Number_Resource_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Opt_Union_Number_Resource selected)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Opt_Union_Number_Resource_Void);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 selected_type = INTEROP_RUNTIME_UNDEFINED;
    selected_type = runtimeType(selected);
    argsSerializer.writeInt8(selected_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (selected_type)) {
        const auto selected_value = selected.value;
        Ark_Int32 selected_value_type = INTEROP_RUNTIME_UNDEFINED;
        selected_value_type = selected_value.selector;
        if (selected_value_type == 0) {
            argsSerializer.writeInt8(0);
            const auto selected_value_0 = selected_value.value0;
            argsSerializer.writeNumber(selected_value_0);
        }
        else if (selected_value_type == 1) {
            argsSerializer.writeInt8(1);
            const auto selected_value_1 = selected_value.value1;
            argsSerializer.writeResource(selected_value_1);
        }
    }
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_PlaybackInfo_Void(Ark_Int32 resourceId, Ark_PlaybackInfo parameter)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_PlaybackInfo_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePlaybackInfo(parameter);
    enqueueCallback(&_buffer);
}
void callManagedCallback_PlaybackInfo_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_PlaybackInfo parameter)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_PlaybackInfo_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePlaybackInfo(parameter);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Pointer_Void(Ark_Int32 resourceId, Ark_NativePointer value)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Pointer_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(value);
    enqueueCallback(&_buffer);
}
void callManagedCallback_Pointer_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NativePointer value)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Pointer_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(value);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_PopInfo_Void(Ark_Int32 resourceId, Ark_PopInfo parameter)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_PopInfo_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePopInfo(parameter);
    enqueueCallback(&_buffer);
}
void callManagedCallback_PopInfo_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_PopInfo parameter)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_PopInfo_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePopInfo(parameter);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_PreDragStatus_Void(Ark_Int32 resourceId, Ark_PreDragStatus parameter)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_PreDragStatus_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_PreDragStatus>(parameter));
    enqueueCallback(&_buffer);
}
void callManagedCallback_PreDragStatus_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_PreDragStatus parameter)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_PreDragStatus_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_PreDragStatus>(parameter));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_PreparedInfo_Void(Ark_Int32 resourceId, Ark_PreparedInfo parameter)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_PreparedInfo_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePreparedInfo(parameter);
    enqueueCallback(&_buffer);
}
void callManagedCallback_PreparedInfo_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_PreparedInfo parameter)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_PreparedInfo_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePreparedInfo(parameter);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_RangeUpdate(Ark_Int32 resourceId, Ark_Int32 index, Ark_NativePointer mark, Ark_Int32 end)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_RangeUpdate);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    argsSerializer.writePointer(mark);
    argsSerializer.writeInt32(end);
    enqueueCallback(&_buffer);
}
void callManagedCallback_RangeUpdateSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 index, Ark_NativePointer mark, Ark_Int32 end)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_RangeUpdate);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    argsSerializer.writePointer(mark);
    argsSerializer.writeInt32(end);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_RefreshStatus_Void(Ark_Int32 resourceId, Ark_RefreshStatus state)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_RefreshStatus_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_RefreshStatus>(state));
    enqueueCallback(&_buffer);
}
void callManagedCallback_RefreshStatus_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_RefreshStatus state)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_RefreshStatus_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_RefreshStatus>(state));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_ResourceStr_Void(Ark_Int32 resourceId, Ark_ResourceStr text)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_ResourceStr_Void);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 text_type = INTEROP_RUNTIME_UNDEFINED;
    text_type = text.selector;
    if (text_type == 0) {
        argsSerializer.writeInt8(0);
        const auto text_0 = text.value0;
        argsSerializer.writeString(text_0);
    }
    else if (text_type == 1) {
        argsSerializer.writeInt8(1);
        const auto text_1 = text.value1;
        argsSerializer.writeResource(text_1);
    }
    enqueueCallback(&_buffer);
}
void callManagedCallback_ResourceStr_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_ResourceStr text)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_ResourceStr_Void);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 text_type = INTEROP_RUNTIME_UNDEFINED;
    text_type = text.selector;
    if (text_type == 0) {
        argsSerializer.writeInt8(0);
        const auto text_0 = text.value0;
        argsSerializer.writeString(text_0);
    }
    else if (text_type == 1) {
        argsSerializer.writeInt8(1);
        const auto text_1 = text.value1;
        argsSerializer.writeResource(text_1);
    }
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_RichEditorChangeValue_Boolean(Ark_Int32 resourceId, Ark_RichEditorChangeValue parameter, Callback_Boolean_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_RichEditorChangeValue_Boolean);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeRichEditorChangeValue(parameter);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedCallback_RichEditorChangeValue_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_RichEditorChangeValue parameter, Callback_Boolean_Void continuation)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_RichEditorChangeValue_Boolean);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeRichEditorChangeValue(parameter);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_RichEditorDeleteValue_Boolean(Ark_Int32 resourceId, Ark_RichEditorDeleteValue parameter, Callback_Boolean_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_RichEditorDeleteValue_Boolean);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeRichEditorDeleteValue(parameter);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedCallback_RichEditorDeleteValue_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_RichEditorDeleteValue parameter, Callback_Boolean_Void continuation)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_RichEditorDeleteValue_Boolean);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeRichEditorDeleteValue(parameter);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_RichEditorInsertValue_Boolean(Ark_Int32 resourceId, Ark_RichEditorInsertValue parameter, Callback_Boolean_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_RichEditorInsertValue_Boolean);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeRichEditorInsertValue(parameter);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedCallback_RichEditorInsertValue_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_RichEditorInsertValue parameter, Callback_Boolean_Void continuation)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_RichEditorInsertValue_Boolean);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeRichEditorInsertValue(parameter);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_RichEditorRange_Void(Ark_Int32 resourceId, Ark_RichEditorRange parameter)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_RichEditorRange_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeRichEditorRange(parameter);
    enqueueCallback(&_buffer);
}
void callManagedCallback_RichEditorRange_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_RichEditorRange parameter)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_RichEditorRange_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeRichEditorRange(parameter);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_RichEditorSelection_Void(Ark_Int32 resourceId, Ark_RichEditorSelection parameter)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_RichEditorSelection_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeRichEditorSelection(parameter);
    enqueueCallback(&_buffer);
}
void callManagedCallback_RichEditorSelection_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_RichEditorSelection parameter)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_RichEditorSelection_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeRichEditorSelection(parameter);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_RichEditorTextSpanResult_Void(Ark_Int32 resourceId, Ark_RichEditorTextSpanResult parameter)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_RichEditorTextSpanResult_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeRichEditorTextSpanResult(parameter);
    enqueueCallback(&_buffer);
}
void callManagedCallback_RichEditorTextSpanResult_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_RichEditorTextSpanResult parameter)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_RichEditorTextSpanResult_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeRichEditorTextSpanResult(parameter);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_SheetDismiss_Void(Ark_Int32 resourceId, Ark_SheetDismiss sheetDismiss)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_SheetDismiss_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeSheetDismiss(sheetDismiss);
    enqueueCallback(&_buffer);
}
void callManagedCallback_SheetDismiss_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_SheetDismiss sheetDismiss)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_SheetDismiss_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeSheetDismiss(sheetDismiss);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_SheetType_Void(Ark_Int32 resourceId, Ark_SheetType parameter)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_SheetType_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_SheetType>(parameter));
    enqueueCallback(&_buffer);
}
void callManagedCallback_SheetType_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_SheetType parameter)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_SheetType_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_SheetType>(parameter));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_SpringBackAction_Void(Ark_Int32 resourceId, Ark_SpringBackAction parameter)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_SpringBackAction_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeSpringBackAction(parameter);
    enqueueCallback(&_buffer);
}
void callManagedCallback_SpringBackAction_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_SpringBackAction parameter)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_SpringBackAction_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeSpringBackAction(parameter);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_StateStylesChange(Ark_Int32 resourceId, Ark_Int32 currentState)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_StateStylesChange);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(currentState);
    enqueueCallback(&_buffer);
}
void callManagedCallback_StateStylesChangeSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 currentState)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_StateStylesChange);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(currentState);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_String_Number_Void(Ark_Int32 resourceId, Ark_String value, Ark_Number index)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_String_Number_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(value);
    argsSerializer.writeNumber(index);
    enqueueCallback(&_buffer);
}
void callManagedCallback_String_Number_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_String value, Ark_Number index)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_String_Number_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(value);
    argsSerializer.writeNumber(index);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_String_Opt_Object_Void(Ark_Int32 resourceId, Ark_String name, Opt_Object param)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_String_Opt_Object_Void);
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
void callManagedCallback_String_Opt_Object_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_String name, Opt_Object param)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_String_Opt_Object_Void);
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
void callManagedCallback_String_PasteEvent_Void(Ark_Int32 resourceId, Ark_String value, Ark_PasteEvent event)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_String_PasteEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(value);
    argsSerializer.writePasteEvent(event);
    enqueueCallback(&_buffer);
}
void callManagedCallback_String_PasteEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_String value, Ark_PasteEvent event)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_String_PasteEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(value);
    argsSerializer.writePasteEvent(event);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_String_Void(Ark_Int32 resourceId, Ark_String breakpoints)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_String_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(breakpoints);
    enqueueCallback(&_buffer);
}
void callManagedCallback_String_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_String breakpoints)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_String_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(breakpoints);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_StyledStringChangeValue_Boolean(Ark_Int32 resourceId, Ark_StyledStringChangeValue parameter, Callback_Boolean_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_StyledStringChangeValue_Boolean);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeStyledStringChangeValue(parameter);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedCallback_StyledStringChangeValue_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_StyledStringChangeValue parameter, Callback_Boolean_Void continuation)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_StyledStringChangeValue_Boolean);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeStyledStringChangeValue(parameter);
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_StyledStringMarshallingValue_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeUserDataSpan(value);
    enqueueCallback(&_buffer);
}
void callManagedCallback_StyledStringMarshallingValue_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_UserDataSpan value)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_StyledStringMarshallingValue_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeUserDataSpan(value);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_SwipeActionState_Void(Ark_Int32 resourceId, Ark_SwipeActionState state)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_SwipeActionState_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_SwipeActionState>(state));
    enqueueCallback(&_buffer);
}
void callManagedCallback_SwipeActionState_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_SwipeActionState state)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_SwipeActionState_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_SwipeActionState>(state));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_SwiperContentTransitionProxy_Void(Ark_Int32 resourceId, Ark_SwiperContentTransitionProxy parameter)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_SwiperContentTransitionProxy_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeSwiperContentTransitionProxy(parameter);
    enqueueCallback(&_buffer);
}
void callManagedCallback_SwiperContentTransitionProxy_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_SwiperContentTransitionProxy parameter)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_SwiperContentTransitionProxy_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeSwiperContentTransitionProxy(parameter);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_TabContentTransitionProxy_Void(Ark_Int32 resourceId, Ark_TabContentTransitionProxy parameter)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_TabContentTransitionProxy_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeTabContentTransitionProxy(parameter);
    enqueueCallback(&_buffer);
}
void callManagedCallback_TabContentTransitionProxy_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_TabContentTransitionProxy parameter)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_TabContentTransitionProxy_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeTabContentTransitionProxy(parameter);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_TerminationInfo_Void(Ark_Int32 resourceId, Ark_TerminationInfo parameter)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_TerminationInfo_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeTerminationInfo(parameter);
    enqueueCallback(&_buffer);
}
void callManagedCallback_TerminationInfo_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_TerminationInfo parameter)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_TerminationInfo_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeTerminationInfo(parameter);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_TextPickerResult_Void(Ark_Int32 resourceId, Ark_TextPickerResult value)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_TextPickerResult_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeTextPickerResult(value);
    enqueueCallback(&_buffer);
}
void callManagedCallback_TextPickerResult_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_TextPickerResult value)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_TextPickerResult_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeTextPickerResult(value);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_TextRange_Void(Ark_Int32 resourceId, Ark_TextRange parameter)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_TextRange_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeTextRange(parameter);
    enqueueCallback(&_buffer);
}
void callManagedCallback_TextRange_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_TextRange parameter)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_TextRange_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeTextRange(parameter);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_TimePickerResult_Void(Ark_Int32 resourceId, Ark_TimePickerResult value)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_TimePickerResult_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeTimePickerResult(value);
    enqueueCallback(&_buffer);
}
void callManagedCallback_TimePickerResult_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_TimePickerResult value)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_TimePickerResult_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeTimePickerResult(value);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_TouchEvent_HitTestMode(Ark_Int32 resourceId, Ark_TouchEvent parameter, Callback_HitTestMode_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_TouchEvent_HitTestMode);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeTouchEvent(parameter);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedCallback_TouchEvent_HitTestModeSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_TouchEvent parameter, Callback_HitTestMode_Void continuation)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_TouchEvent_HitTestMode);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeTouchEvent(parameter);
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_TouchEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeTouchEvent(event);
    enqueueCallback(&_buffer);
}
void callManagedCallback_TouchEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_TouchEvent event)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_TouchEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeTouchEvent(event);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_TouchResult_Void(Ark_Int32 resourceId, Ark_TouchResult value)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_TouchResult_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeTouchResult(value);
    enqueueCallback(&_buffer);
}
void callManagedCallback_TouchResult_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_TouchResult value)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_TouchResult_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeTouchResult(value);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Tuple_Number_Number_Number_Number_Void(Ark_Int32 resourceId, Ark_Tuple_Number_Number_Number_Number value)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Tuple_Number_Number_Void);
    argsSerializer.writeInt32(resourceId);
    const auto value_0 = value.value0;
    argsSerializer.writeNumber(value_0);
    const auto value_1 = value.value1;
    argsSerializer.writeNumber(value_1);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Type_ImageAttribute_onComplete_callback_event_Void(Ark_Int32 resourceId, Opt_Type_ImageAttribute_onComplete_callback_event event)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Type_ImageAttribute_onComplete_callback_event_Void);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 event_type = INTEROP_RUNTIME_UNDEFINED;
    event_type = runtimeType(event);
    argsSerializer.writeInt8(event_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (event_type)) {
        const auto event_value = event.value;
        const auto event_value_width = event_value.width;
        argsSerializer.writeNumber(event_value_width);
        const auto event_value_height = event_value.height;
        argsSerializer.writeNumber(event_value_height);
        const auto event_value_componentWidth = event_value.componentWidth;
        argsSerializer.writeNumber(event_value_componentWidth);
        const auto event_value_componentHeight = event_value.componentHeight;
        argsSerializer.writeNumber(event_value_componentHeight);
        const auto event_value_loadingStatus = event_value.loadingStatus;
        argsSerializer.writeNumber(event_value_loadingStatus);
        const auto event_value_contentWidth = event_value.contentWidth;
        argsSerializer.writeNumber(event_value_contentWidth);
        const auto event_value_contentHeight = event_value.contentHeight;
        argsSerializer.writeNumber(event_value_contentHeight);
        const auto event_value_contentOffsetX = event_value.contentOffsetX;
        argsSerializer.writeNumber(event_value_contentOffsetX);
        const auto event_value_contentOffsetY = event_value.contentOffsetY;
        argsSerializer.writeNumber(event_value_contentOffsetY);
    }
    enqueueCallback(&_buffer);
}
void callManagedCallback_Type_ImageAttribute_onComplete_callback_event_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Opt_Type_ImageAttribute_onComplete_callback_event event)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Type_ImageAttribute_onComplete_callback_event_Void);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 event_type = INTEROP_RUNTIME_UNDEFINED;
    event_type = runtimeType(event);
    argsSerializer.writeInt8(event_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (event_type)) {
        const auto event_value = event.value;
        const auto event_value_width = event_value.width;
        argsSerializer.writeNumber(event_value_width);
        const auto event_value_height = event_value.height;
        argsSerializer.writeNumber(event_value_height);
        const auto event_value_componentWidth = event_value.componentWidth;
        argsSerializer.writeNumber(event_value_componentWidth);
        const auto event_value_componentHeight = event_value.componentHeight;
        argsSerializer.writeNumber(event_value_componentHeight);
        const auto event_value_loadingStatus = event_value.loadingStatus;
        argsSerializer.writeNumber(event_value_loadingStatus);
        const auto event_value_contentWidth = event_value.contentWidth;
        argsSerializer.writeNumber(event_value_contentWidth);
        const auto event_value_contentHeight = event_value.contentHeight;
        argsSerializer.writeNumber(event_value_contentHeight);
        const auto event_value_contentOffsetX = event_value.contentOffsetX;
        argsSerializer.writeNumber(event_value_contentOffsetX);
        const auto event_value_contentOffsetY = event_value.contentOffsetY;
        argsSerializer.writeNumber(event_value_contentOffsetY);
    }
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_UIExtensionProxy_Void(Ark_Int32 resourceId, Ark_UIExtensionProxy parameter)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_UIExtensionProxy_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeUIExtensionProxy(parameter);
    enqueueCallback(&_buffer);
}
void callManagedCallback_UIExtensionProxy_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_UIExtensionProxy parameter)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_UIExtensionProxy_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeUIExtensionProxy(parameter);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Union_CustomBuilder_DragItemInfo_Void(Ark_Int32 resourceId, Ark_Union_CustomBuilder_DragItemInfo value)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
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
        argsSerializer.writeDragItemInfo(value_1);
    }
    enqueueCallback(&_buffer);
}
void callManagedCallback_Union_CustomBuilder_DragItemInfo_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Union_CustomBuilder_DragItemInfo value)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
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
        argsSerializer.writeDragItemInfo(value_1);
    }
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Union_Number_Array_Number_Void(Ark_Int32 resourceId, Ark_Union_Number_Array_Number selected)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Union_Number_Array_Number_Void);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 selected_type = INTEROP_RUNTIME_UNDEFINED;
    selected_type = selected.selector;
    if (selected_type == 0) {
        argsSerializer.writeInt8(0);
        const auto selected_0 = selected.value0;
        argsSerializer.writeNumber(selected_0);
    }
    else if (selected_type == 1) {
        argsSerializer.writeInt8(1);
        const auto selected_1 = selected.value1;
        argsSerializer.writeInt32(selected_1.length);
        for (int i = 0; i < selected_1.length; i++) {
            const Ark_Number selected_1_element = selected_1.array[i];
            argsSerializer.writeNumber(selected_1_element);
        }
    }
    enqueueCallback(&_buffer);
}
void callManagedCallback_Union_Number_Array_Number_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Union_Number_Array_Number selected)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Union_Number_Array_Number_Void);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 selected_type = INTEROP_RUNTIME_UNDEFINED;
    selected_type = selected.selector;
    if (selected_type == 0) {
        argsSerializer.writeInt8(0);
        const auto selected_0 = selected.value0;
        argsSerializer.writeNumber(selected_0);
    }
    else if (selected_type == 1) {
        argsSerializer.writeInt8(1);
        const auto selected_1 = selected.value1;
        argsSerializer.writeInt32(selected_1.length);
        for (int i = 0; i < selected_1.length; i++) {
            const Ark_Number selected_1_element = selected_1.array[i];
            argsSerializer.writeNumber(selected_1_element);
        }
    }
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Union_String_Array_String_Void(Ark_Int32 resourceId, Ark_Union_String_Array_String value)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Union_String_Array_String_Void);
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
    enqueueCallback(&_buffer);
}
void callManagedCallback_Union_String_Array_String_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Union_String_Array_String value)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Union_String_Array_String_Void);
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
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_Void(Ark_Int32 resourceId)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Void);
    argsSerializer.writeInt32(resourceId);
    enqueueCallback(&_buffer);
}
void callManagedCallback_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_Void);
    argsSerializer.writeInt32(resourceId);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_WebKeyboardOptions_Void(Ark_Int32 resourceId, Ark_WebKeyboardOptions value)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_WebKeyboardOptions_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeWebKeyboardOptions(value);
    enqueueCallback(&_buffer);
}
void callManagedCallback_WebKeyboardOptions_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_WebKeyboardOptions value)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_WebKeyboardOptions_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeWebKeyboardOptions(value);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_WebResourceResponse_Void(Ark_Int32 resourceId, Ark_WebResourceResponse value)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_WebResourceResponse_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeWebResourceResponse(value);
    enqueueCallback(&_buffer);
}
void callManagedCallback_WebResourceResponse_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_WebResourceResponse value)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_WebResourceResponse_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeWebResourceResponse(value);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_WithThemeAttribute_Void(Ark_Int32 resourceId, Ark_WithThemeAttribute value)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_WithThemeAttribute_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeWithThemeAttribute(value);
    enqueueCallback(&_buffer);
}
void callManagedCallback_WithThemeAttribute_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_WithThemeAttribute value)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_WithThemeAttribute_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeWithThemeAttribute(value);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_WrappedBuilder_Args_Void(Ark_Int32 resourceId, Ark_CommonConfiguration args)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_WrappedBuilder_Args_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeCommonConfiguration(args);
    enqueueCallback(&_buffer);
}
void callManagedCallback_WrappedBuilder_Args_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_CommonConfiguration args)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_WrappedBuilder_Args_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeCommonConfiguration(args);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedContentDidScrollCallback(Ark_Int32 resourceId, Ark_Number selectedIndex, Ark_Number index, Ark_Number position, Ark_Number mainAxisLength)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_ContentWillScrollCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeSwiperContentWillScrollResult(result);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedContentWillScrollCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_SwiperContentWillScrollResult result, Callback_Boolean_Void continuation)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_ContentWillScrollCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeSwiperContentWillScrollResult(result);
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Context_getGroupDir_Callback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(result);
    enqueueCallback(&_buffer);
}
void callManagedContext_getGroupDir_CallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_String result)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Context_getGroupDir_Callback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(result);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCustomNodeBuilder(Ark_Int32 resourceId, Ark_NativePointer parentNode, Callback_Pointer_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_CustomNodeBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedDrawCallback(Ark_Int32 resourceId, Ark_DrawContext context)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_DrawCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeDrawContext(context);
    enqueueCallback(&_buffer);
}
void callManagedDrawCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_DrawContext context)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_DrawCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeDrawContext(context);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedEditableTextOnChangeCallback(Ark_Int32 resourceId, Ark_String value, Opt_PreviewText previewText, Opt_TextChangeOptions options)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_EditableTextOnChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(value);
    Ark_Int32 previewText_type = INTEROP_RUNTIME_UNDEFINED;
    previewText_type = runtimeType(previewText);
    argsSerializer.writeInt8(previewText_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (previewText_type)) {
        const auto previewText_value = previewText.value;
        argsSerializer.writePreviewText(previewText_value);
    }
    Ark_Int32 options_type = INTEROP_RUNTIME_UNDEFINED;
    options_type = runtimeType(options);
    argsSerializer.writeInt8(options_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (options_type)) {
        const auto options_value = options.value;
        argsSerializer.writeTextChangeOptions(options_value);
    }
    enqueueCallback(&_buffer);
}
void callManagedEditableTextOnChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_String value, Opt_PreviewText previewText, Opt_TextChangeOptions options)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_EditableTextOnChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(value);
    Ark_Int32 previewText_type = INTEROP_RUNTIME_UNDEFINED;
    previewText_type = runtimeType(previewText);
    argsSerializer.writeInt8(previewText_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (previewText_type)) {
        const auto previewText_value = previewText.value;
        argsSerializer.writePreviewText(previewText_value);
    }
    Ark_Int32 options_type = INTEROP_RUNTIME_UNDEFINED;
    options_type = runtimeType(options);
    argsSerializer.writeInt8(options_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (options_type)) {
        const auto options_value = options.value;
        argsSerializer.writeTextChangeOptions(options_value);
    }
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedErrorCallback(Ark_Int32 resourceId, Ark_BusinessError err)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_ErrorCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBusinessError(err);
    enqueueCallback(&_buffer);
}
void callManagedErrorCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_BusinessError err)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_ErrorCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBusinessError(err);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedGestureRecognizerJudgeBeginCallback(Ark_Int32 resourceId, Ark_BaseGestureEvent event, Ark_GestureRecognizer current, Array_GestureRecognizer recognizers, Callback_GestureJudgeResult_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_GestureRecognizerJudgeBeginCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBaseGestureEvent(event);
    argsSerializer.writeGestureRecognizer(current);
    argsSerializer.writeInt32(recognizers.length);
    for (int i = 0; i < recognizers.length; i++) {
        const Ark_GestureRecognizer recognizers_element = recognizers.array[i];
        argsSerializer.writeGestureRecognizer(recognizers_element);
    }
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedGestureRecognizerJudgeBeginCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_BaseGestureEvent event, Ark_GestureRecognizer current, Array_GestureRecognizer recognizers, Callback_GestureJudgeResult_Void continuation)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_GestureRecognizerJudgeBeginCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBaseGestureEvent(event);
    argsSerializer.writeGestureRecognizer(current);
    argsSerializer.writeInt32(recognizers.length);
    for (int i = 0; i < recognizers.length; i++) {
        const Ark_GestureRecognizer recognizers_element = recognizers.array[i];
        argsSerializer.writeGestureRecognizer(recognizers_element);
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_GetItemMainSizeByIndex);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(index);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedGridAttribute_onItemDragStart_event_type(Ark_Int32 resourceId, Ark_ItemDragInfo event, Ark_Number itemIndex, Callback_CustomBuilder_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_GridAttribute_onItemDragStart_event_type);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeItemDragInfo(event);
    argsSerializer.writeNumber(itemIndex);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedGridAttribute_onItemDragStart_event_typeSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_ItemDragInfo event, Ark_Number itemIndex, Callback_CustomBuilder_Void continuation)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_GridAttribute_onItemDragStart_event_type);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeItemDragInfo(event);
    argsSerializer.writeNumber(itemIndex);
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_HoverCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(isHover);
    argsSerializer.writeHoverEvent(event);
    enqueueCallback(&_buffer);
}
void callManagedHoverCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Boolean isHover, Ark_HoverEvent event)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_HoverCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(isHover);
    argsSerializer.writeHoverEvent(event);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedImageCompleteCallback(Ark_Int32 resourceId, Ark_ImageLoadResult result)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_ImageCompleteCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeImageLoadResult(result);
    enqueueCallback(&_buffer);
}
void callManagedImageCompleteCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_ImageLoadResult result)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_ImageCompleteCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeImageLoadResult(result);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedImageErrorCallback(Ark_Int32 resourceId, Ark_ImageError error)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_ImageErrorCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeImageError(error);
    enqueueCallback(&_buffer);
}
void callManagedImageErrorCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_ImageError error)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_ImageErrorCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeImageError(error);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedInterceptionModeCallback(Ark_Int32 resourceId, Ark_NavigationMode mode)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_InterceptionModeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_NavigationMode>(mode));
    enqueueCallback(&_buffer);
}
void callManagedInterceptionModeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NavigationMode mode)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_InterceptionShowCallback);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 from_type = INTEROP_RUNTIME_UNDEFINED;
    from_type = from.selector;
    if (from_type == 0) {
        argsSerializer.writeInt8(0);
        const auto from_0 = from.value0;
        argsSerializer.writeNavDestinationContext(from_0);
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
        argsSerializer.writeNavDestinationContext(to_0);
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_InterceptionShowCallback);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 from_type = INTEROP_RUNTIME_UNDEFINED;
    from_type = from.selector;
    if (from_type == 0) {
        argsSerializer.writeInt8(0);
        const auto from_0 = from.value0;
        argsSerializer.writeNavDestinationContext(from_0);
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
        argsSerializer.writeNavDestinationContext(to_0);
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
void callManagedListAttribute_onItemDragStart_event_type(Ark_Int32 resourceId, Ark_ItemDragInfo event, Ark_Number itemIndex, Callback_CustomBuilder_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_ListAttribute_onItemDragStart_event_type);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeItemDragInfo(event);
    argsSerializer.writeNumber(itemIndex);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedListAttribute_onItemDragStart_event_typeSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_ItemDragInfo event, Ark_Number itemIndex, Callback_CustomBuilder_Void continuation)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_ListAttribute_onItemDragStart_event_type);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeItemDragInfo(event);
    argsSerializer.writeNumber(itemIndex);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedLocationButtonCallback(Ark_Int32 resourceId, Ark_ClickEvent event, Ark_LocationButtonOnClickResult result, Opt_BusinessError error)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_LocationButtonCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeClickEvent(event);
    argsSerializer.writeInt32(static_cast<Ark_LocationButtonOnClickResult>(result));
    Ark_Int32 error_type = INTEROP_RUNTIME_UNDEFINED;
    error_type = runtimeType(error);
    argsSerializer.writeInt8(error_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (error_type)) {
        const auto error_value = error.value;
        argsSerializer.writeBusinessError(error_value);
    }
    enqueueCallback(&_buffer);
}
void callManagedLocationButtonCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_ClickEvent event, Ark_LocationButtonOnClickResult result, Opt_BusinessError error)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_LocationButtonCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeClickEvent(event);
    argsSerializer.writeInt32(static_cast<Ark_LocationButtonOnClickResult>(result));
    Ark_Int32 error_type = INTEROP_RUNTIME_UNDEFINED;
    error_type = runtimeType(error);
    argsSerializer.writeInt8(error_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (error_type)) {
        const auto error_value = error.value;
        argsSerializer.writeBusinessError(error_value);
    }
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedMenuCallback(Ark_Int32 resourceId, Ark_Number start, Ark_Number end)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_MenuCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(start);
    argsSerializer.writeNumber(end);
    enqueueCallback(&_buffer);
}
void callManagedMenuCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number start, Ark_Number end)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_MenuCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(start);
    argsSerializer.writeNumber(end);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedMenuOnAppearCallback(Ark_Int32 resourceId, Ark_Number start, Ark_Number end)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_MenuOnAppearCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(start);
    argsSerializer.writeNumber(end);
    enqueueCallback(&_buffer);
}
void callManagedMenuOnAppearCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number start, Ark_Number end)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_MenuOnAppearCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(start);
    argsSerializer.writeNumber(end);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedNavDestinationTransitionDelegate(Ark_Int32 resourceId, Ark_NavigationOperation operation, Ark_Boolean isEnter, Callback_Opt_Array_NavDestinationTransition_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_NavExtender_OnUpdateStack);
    argsSerializer.writeInt32(resourceId);
    enqueueCallback(&_buffer);
}
void callManagedNavExtender_OnUpdateStackSync(Ark_VMContext vmContext, Ark_Int32 resourceId)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_NavExtender_OnUpdateStack);
    argsSerializer.writeInt32(resourceId);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedNodeContainer_AboutToResizeCallback(Ark_Int32 resourceId, Ark_Size size)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_NodeContainer_AboutToResizeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeSize(size);
    enqueueCallback(&_buffer);
}
void callManagedNodeContainer_AboutToResizeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Size size)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_NodeContainer_AboutToResizeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeSize(size);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnAdsBlockedCallback(Ark_Int32 resourceId, Ark_AdsBlockedDetails details)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnAdsBlockedCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeAdsBlockedDetails(details);
    enqueueCallback(&_buffer);
}
void callManagedOnAdsBlockedCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_AdsBlockedDetails details)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnAdsBlockedCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeAdsBlockedDetails(details);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnAlphabetIndexerPopupSelectCallback(Ark_Int32 resourceId, Ark_Number index)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnAlphabetIndexerPopupSelectCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(index);
    enqueueCallback(&_buffer);
}
void callManagedOnAlphabetIndexerPopupSelectCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number index)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnAlphabetIndexerSelectCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(index);
    enqueueCallback(&_buffer);
}
void callManagedOnAlphabetIndexerSelectCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number index)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnCheckboxChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(value);
    enqueueCallback(&_buffer);
}
void callManagedOnCheckboxChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Boolean value)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnCheckboxGroupChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeCheckboxGroupResult(value);
    enqueueCallback(&_buffer);
}
void callManagedOnCheckboxGroupChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_CheckboxGroupResult value)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnCheckboxGroupChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeCheckboxGroupResult(value);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnContentScrollCallback(Ark_Int32 resourceId, Ark_Number totalOffsetX, Ark_Number totalOffsetY)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnContentScrollCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(totalOffsetX);
    argsSerializer.writeNumber(totalOffsetY);
    enqueueCallback(&_buffer);
}
void callManagedOnContentScrollCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number totalOffsetX, Ark_Number totalOffsetY)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnContentScrollCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(totalOffsetX);
    argsSerializer.writeNumber(totalOffsetY);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnContextMenuHideCallback(Ark_Int32 resourceId)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnContextMenuHideCallback);
    argsSerializer.writeInt32(resourceId);
    enqueueCallback(&_buffer);
}
void callManagedOnContextMenuHideCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnContextMenuHideCallback);
    argsSerializer.writeInt32(resourceId);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnDidChangeCallback(Ark_Int32 resourceId, Ark_TextRange rangeBefore, Ark_TextRange rangeAfter)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnDidChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeTextRange(rangeBefore);
    argsSerializer.writeTextRange(rangeAfter);
    enqueueCallback(&_buffer);
}
void callManagedOnDidChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_TextRange rangeBefore, Ark_TextRange rangeAfter)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnDidChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeTextRange(rangeBefore);
    argsSerializer.writeTextRange(rangeAfter);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnDragEventCallback(Ark_Int32 resourceId, Ark_DragEvent event, Opt_String extraParams)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnDragEventCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeDragEvent(event);
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnDragEventCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeDragEvent(event);
    Ark_Int32 extraParams_type = INTEROP_RUNTIME_UNDEFINED;
    extraParams_type = runtimeType(extraParams);
    argsSerializer.writeInt8(extraParams_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (extraParams_type)) {
        const auto extraParams_value = extraParams.value;
        argsSerializer.writeString(extraParams_value);
    }
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnFirstMeaningfulPaintCallback(Ark_Int32 resourceId, Ark_FirstMeaningfulPaint firstMeaningfulPaint)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnFirstMeaningfulPaintCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFirstMeaningfulPaint(firstMeaningfulPaint);
    enqueueCallback(&_buffer);
}
void callManagedOnFirstMeaningfulPaintCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_FirstMeaningfulPaint firstMeaningfulPaint)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnFirstMeaningfulPaintCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFirstMeaningfulPaint(firstMeaningfulPaint);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnFoldStatusChangeCallback(Ark_Int32 resourceId, Ark_OnFoldStatusChangeInfo event)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnFoldStatusChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnFoldStatusChangeInfo(event);
    enqueueCallback(&_buffer);
}
void callManagedOnFoldStatusChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnFoldStatusChangeInfo event)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnFoldStatusChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeOnFoldStatusChangeInfo(event);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnFullScreenEnterCallback(Ark_Int32 resourceId, Ark_FullScreenEnterEvent event)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnFullScreenEnterCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFullScreenEnterEvent(event);
    enqueueCallback(&_buffer);
}
void callManagedOnFullScreenEnterCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_FullScreenEnterEvent event)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnFullScreenEnterCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFullScreenEnterEvent(event);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnHoverCallback(Ark_Int32 resourceId)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnHoverCallback);
    argsSerializer.writeInt32(resourceId);
    enqueueCallback(&_buffer);
}
void callManagedOnHoverCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnHoverCallback);
    argsSerializer.writeInt32(resourceId);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnHoverStatusChangeCallback(Ark_Int32 resourceId, Ark_HoverEventParam param)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnHoverStatusChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeHoverEventParam(param);
    enqueueCallback(&_buffer);
}
void callManagedOnHoverStatusChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_HoverEventParam param)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnHoverStatusChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeHoverEventParam(param);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnIntelligentTrackingPreventionCallback(Ark_Int32 resourceId, Ark_IntelligentTrackingPreventionDetails details)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnIntelligentTrackingPreventionCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeIntelligentTrackingPreventionDetails(details);
    enqueueCallback(&_buffer);
}
void callManagedOnIntelligentTrackingPreventionCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_IntelligentTrackingPreventionDetails details)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnIntelligentTrackingPreventionCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeIntelligentTrackingPreventionDetails(details);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnLargestContentfulPaintCallback(Ark_Int32 resourceId, Ark_LargestContentfulPaint largestContentfulPaint)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnLargestContentfulPaintCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeLargestContentfulPaint(largestContentfulPaint);
    enqueueCallback(&_buffer);
}
void callManagedOnLargestContentfulPaintCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_LargestContentfulPaint largestContentfulPaint)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnLargestContentfulPaintCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeLargestContentfulPaint(largestContentfulPaint);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnLinearIndicatorChangeCallback(Ark_Int32 resourceId, Ark_Number index, Ark_Number progress)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnLinearIndicatorChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(index);
    argsSerializer.writeNumber(progress);
    enqueueCallback(&_buffer);
}
void callManagedOnLinearIndicatorChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number index, Ark_Number progress)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnLinearIndicatorChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(index);
    argsSerializer.writeNumber(progress);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnMoveHandler(Ark_Int32 resourceId, Ark_Number from, Ark_Number to)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnMoveHandler);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(from);
    argsSerializer.writeNumber(to);
    enqueueCallback(&_buffer);
}
void callManagedOnMoveHandlerSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number from, Ark_Number to)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnMoveHandler);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(from);
    argsSerializer.writeNumber(to);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnNativeEmbedVisibilityChangeCallback(Ark_Int32 resourceId, Ark_NativeEmbedVisibilityInfo nativeEmbedVisibilityInfo)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnNativeEmbedVisibilityChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNativeEmbedVisibilityInfo(nativeEmbedVisibilityInfo);
    enqueueCallback(&_buffer);
}
void callManagedOnNativeEmbedVisibilityChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NativeEmbedVisibilityInfo nativeEmbedVisibilityInfo)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnNativeEmbedVisibilityChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNativeEmbedVisibilityInfo(nativeEmbedVisibilityInfo);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnNativeLoadCallback(Ark_Int32 resourceId, Opt_Object event)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
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
void callManagedOnNavigationEntryCommittedCallback(Ark_Int32 resourceId, Ark_LoadCommittedDetails loadCommittedDetails)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnNavigationEntryCommittedCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeLoadCommittedDetails(loadCommittedDetails);
    enqueueCallback(&_buffer);
}
void callManagedOnNavigationEntryCommittedCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_LoadCommittedDetails loadCommittedDetails)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnNavigationEntryCommittedCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeLoadCommittedDetails(loadCommittedDetails);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnOverrideUrlLoadingCallback(Ark_Int32 resourceId, Ark_WebResourceRequest webResourceRequest, Callback_Boolean_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnOverrideUrlLoadingCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeWebResourceRequest(webResourceRequest);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedOnOverrideUrlLoadingCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_WebResourceRequest webResourceRequest, Callback_Boolean_Void continuation)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnOverrideUrlLoadingCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeWebResourceRequest(webResourceRequest);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnPasteCallback(Ark_Int32 resourceId, Ark_String content, Ark_PasteEvent event)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnPasteCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(content);
    argsSerializer.writePasteEvent(event);
    enqueueCallback(&_buffer);
}
void callManagedOnPasteCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_String content, Ark_PasteEvent event)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnPasteCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(content);
    argsSerializer.writePasteEvent(event);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnRadioChangeCallback(Ark_Int32 resourceId, Ark_Boolean isChecked)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnRadioChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(isChecked);
    enqueueCallback(&_buffer);
}
void callManagedOnRadioChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Boolean isChecked)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnRatingChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(rating);
    enqueueCallback(&_buffer);
}
void callManagedOnRatingChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number rating)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnRatingChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(rating);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnRenderProcessNotRespondingCallback(Ark_Int32 resourceId, Ark_RenderProcessNotRespondingData data)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnRenderProcessNotRespondingCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeRenderProcessNotRespondingData(data);
    enqueueCallback(&_buffer);
}
void callManagedOnRenderProcessNotRespondingCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_RenderProcessNotRespondingData data)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnRenderProcessNotRespondingCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeRenderProcessNotRespondingData(data);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnRenderProcessRespondingCallback(Ark_Int32 resourceId)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnRenderProcessRespondingCallback);
    argsSerializer.writeInt32(resourceId);
    enqueueCallback(&_buffer);
}
void callManagedOnRenderProcessRespondingCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnRenderProcessRespondingCallback);
    argsSerializer.writeInt32(resourceId);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnSafeBrowsingCheckResultCallback(Ark_Int32 resourceId, Ark_ThreatType threatType)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnSafeBrowsingCheckResultCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_ThreatType>(threatType));
    enqueueCallback(&_buffer);
}
void callManagedOnSafeBrowsingCheckResultCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_ThreatType threatType)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnSafeBrowsingCheckResultCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_ThreatType>(threatType));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnWillScrollCallback(Ark_Int32 resourceId, Ark_Number scrollOffset, Ark_ScrollState scrollState, Ark_ScrollSource scrollSource, Callback_ScrollResult_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource __callbackResource = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&__callbackResource);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
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
void callManagedOnWillScrollCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number scrollOffset, Ark_ScrollState scrollState, Ark_ScrollSource scrollSource, Callback_ScrollResult_Void continuation)
{
    uint8_t _buffer[60 * 4];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
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
void callManagedOnScrollCallback(Ark_Int32 resourceId, Ark_Number scrollOffset, Ark_ScrollState scrollState)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnScrollCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(scrollOffset);
    argsSerializer.writeInt32(static_cast<Ark_ScrollState>(scrollState));
    enqueueCallback(&_buffer);
}
void callManagedOnScrollCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number scrollOffset, Ark_ScrollState scrollState)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnScrollEdgeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_Edge>(side));
    enqueueCallback(&_buffer);
}
void callManagedOnScrollEdgeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Edge side)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnScrollVisibleContentChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeVisibleListContentInfo(start);
    argsSerializer.writeVisibleListContentInfo(end);
    enqueueCallback(&_buffer);
}
void callManagedOnScrollVisibleContentChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_VisibleListContentInfo start, Ark_VisibleListContentInfo end)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnScrollVisibleContentChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeVisibleListContentInfo(start);
    argsSerializer.writeVisibleListContentInfo(end);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnSelectCallback(Ark_Int32 resourceId, Ark_Number index, Ark_String selectStr)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnSelectCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(index);
    argsSerializer.writeString(selectStr);
    enqueueCallback(&_buffer);
}
void callManagedOnSelectCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number index, Ark_String selectStr)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnSelectCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(index);
    argsSerializer.writeString(selectStr);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnSslErrorEventCallback(Ark_Int32 resourceId, Ark_SslErrorEvent sslErrorEvent)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnSslErrorEventCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeSslErrorEvent(sslErrorEvent);
    enqueueCallback(&_buffer);
}
void callManagedOnSslErrorEventCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_SslErrorEvent sslErrorEvent)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnSslErrorEventCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeSslErrorEvent(sslErrorEvent);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnSubmitCallback(Ark_Int32 resourceId, Ark_EnterKeyType enterKey, Ark_SubmitEvent event)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnSubmitCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_EnterKeyType>(enterKey));
    argsSerializer.writeSubmitEvent(event);
    enqueueCallback(&_buffer);
}
void callManagedOnSubmitCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_EnterKeyType enterKey, Ark_SubmitEvent event)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnSubmitCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_EnterKeyType>(enterKey));
    argsSerializer.writeSubmitEvent(event);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnSwiperAnimationEndCallback(Ark_Int32 resourceId, Ark_Number index, Ark_SwiperAnimationEvent extraInfo)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnSwiperAnimationEndCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(index);
    argsSerializer.writeSwiperAnimationEvent(extraInfo);
    enqueueCallback(&_buffer);
}
void callManagedOnSwiperAnimationEndCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number index, Ark_SwiperAnimationEvent extraInfo)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnSwiperAnimationEndCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(index);
    argsSerializer.writeSwiperAnimationEvent(extraInfo);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnSwiperAnimationStartCallback(Ark_Int32 resourceId, Ark_Number index, Ark_Number targetIndex, Ark_SwiperAnimationEvent extraInfo)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnSwiperAnimationStartCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(index);
    argsSerializer.writeNumber(targetIndex);
    argsSerializer.writeSwiperAnimationEvent(extraInfo);
    enqueueCallback(&_buffer);
}
void callManagedOnSwiperAnimationStartCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number index, Ark_Number targetIndex, Ark_SwiperAnimationEvent extraInfo)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnSwiperAnimationStartCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(index);
    argsSerializer.writeNumber(targetIndex);
    argsSerializer.writeSwiperAnimationEvent(extraInfo);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnSwiperGestureSwipeCallback(Ark_Int32 resourceId, Ark_Number index, Ark_SwiperAnimationEvent extraInfo)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnSwiperGestureSwipeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(index);
    argsSerializer.writeSwiperAnimationEvent(extraInfo);
    enqueueCallback(&_buffer);
}
void callManagedOnSwiperGestureSwipeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number index, Ark_SwiperAnimationEvent extraInfo)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnSwiperGestureSwipeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(index);
    argsSerializer.writeSwiperAnimationEvent(extraInfo);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnTabsAnimationEndCallback(Ark_Int32 resourceId, Ark_Number index, Ark_TabsAnimationEvent extraInfo)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnTabsAnimationEndCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(index);
    argsSerializer.writeTabsAnimationEvent(extraInfo);
    enqueueCallback(&_buffer);
}
void callManagedOnTabsAnimationEndCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number index, Ark_TabsAnimationEvent extraInfo)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnTabsAnimationEndCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(index);
    argsSerializer.writeTabsAnimationEvent(extraInfo);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnTabsAnimationStartCallback(Ark_Int32 resourceId, Ark_Number index, Ark_Number targetIndex, Ark_TabsAnimationEvent extraInfo)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnTabsAnimationStartCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(index);
    argsSerializer.writeNumber(targetIndex);
    argsSerializer.writeTabsAnimationEvent(extraInfo);
    enqueueCallback(&_buffer);
}
void callManagedOnTabsAnimationStartCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number index, Ark_Number targetIndex, Ark_TabsAnimationEvent extraInfo)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnTabsAnimationStartCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(index);
    argsSerializer.writeNumber(targetIndex);
    argsSerializer.writeTabsAnimationEvent(extraInfo);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnTabsContentWillChangeCallback(Ark_Int32 resourceId, Ark_Number currentIndex, Ark_Number comingIndex, Callback_Boolean_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnTabsGestureSwipeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(index);
    argsSerializer.writeTabsAnimationEvent(extraInfo);
    enqueueCallback(&_buffer);
}
void callManagedOnTabsGestureSwipeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number index, Ark_TabsAnimationEvent extraInfo)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnTabsGestureSwipeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(index);
    argsSerializer.writeTabsAnimationEvent(extraInfo);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnTextPickerChangeCallback(Ark_Int32 resourceId, Ark_Union_String_Array_String selectItem, Ark_Union_Number_Array_Number index)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
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
        const int maxLen = std::min(selectItem_1.length, INT_MAX);
        for (int i = 0; i < maxLen; i++) {
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
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
        const int maxLen = std::min(selectItem_1.length, INT_MAX);
        for (int i = 0; i < maxLen; i++) {
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnTextSelectionChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(selectionStart);
    argsSerializer.writeNumber(selectionEnd);
    enqueueCallback(&_buffer);
}
void callManagedOnTextSelectionChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number selectionStart, Ark_Number selectionEnd)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnTimePickerChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeTimePickerResult(result);
    enqueueCallback(&_buffer);
}
void callManagedOnTimePickerChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_TimePickerResult result)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnTimePickerChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeTimePickerResult(result);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedOnViewportFitChangedCallback(Ark_Int32 resourceId, Ark_ViewportFit viewportFit)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnViewportFitChangedCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_ViewportFit>(viewportFit));
    enqueueCallback(&_buffer);
}
void callManagedOnViewportFitChangedCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_ViewportFit viewportFit)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_OnViewportFitChangedCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_ViewportFit>(viewportFit));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedPageTransitionCallback(Ark_Int32 resourceId, Ark_RouteType type, Ark_Number progress)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_PageTransitionCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_RouteType>(type));
    argsSerializer.writeNumber(progress);
    enqueueCallback(&_buffer);
}
void callManagedPageTransitionCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_RouteType type, Ark_Number progress)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_PasteButtonCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeClickEvent(event);
    argsSerializer.writeInt32(static_cast<Ark_PasteButtonOnClickResult>(result));
    enqueueCallback(&_buffer);
}
void callManagedPasteButtonCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_ClickEvent event, Ark_PasteButtonOnClickResult result, Opt_BusinessError error)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_PasteButtonCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeClickEvent(event);
    argsSerializer.writeInt32(static_cast<Ark_PasteButtonOnClickResult>(result));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedPasteEventCallback(Ark_Int32 resourceId, Opt_PasteEvent event)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_PasteEventCallback);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 event_type = INTEROP_RUNTIME_UNDEFINED;
    event_type = runtimeType(event);
    argsSerializer.writeInt8(event_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (event_type)) {
        const auto event_value = event.value;
        argsSerializer.writePasteEvent(event_value);
    }
    enqueueCallback(&_buffer);
}
void callManagedPasteEventCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Opt_PasteEvent event)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_PasteEventCallback);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 event_type = INTEROP_RUNTIME_UNDEFINED;
    event_type = runtimeType(event);
    argsSerializer.writeInt8(event_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (event_type)) {
        const auto event_value = event.value;
        argsSerializer.writePasteEvent(event_value);
    }
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedPluginErrorCallback(Ark_Int32 resourceId, Ark_PluginErrorData info)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_PluginErrorCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePluginErrorData(info);
    enqueueCallback(&_buffer);
}
void callManagedPluginErrorCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_PluginErrorData info)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_PluginErrorCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePluginErrorData(info);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedPopupStateChangeCallback(Ark_Int32 resourceId, Ark_PopupStateChangeParam event)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_PopupStateChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePopupStateChangeParam(event);
    enqueueCallback(&_buffer);
}
void callManagedPopupStateChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_PopupStateChangeParam event)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_PopupStateChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePopupStateChangeParam(event);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedReceiveCallback(Ark_Int32 resourceId, Map_String_Object data)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_ReceiveCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(data.size);
    for (int32_t i = 0; i < data.size; i++) {
        auto data_key = data.keys[i];
        auto data_value = data.values[i];
        argsSerializer.writeString(data_key);
        argsSerializer.writeObject(data_value);
    }
    enqueueCallback(&_buffer);
}
void callManagedReceiveCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Map_String_Object data)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_ReceiveCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(data.size);
    for (int32_t i = 0; i < data.size; i++) {
        auto data_key = data.keys[i];
        auto data_value = data.values[i];
        argsSerializer.writeString(data_key);
        argsSerializer.writeObject(data_value);
    }
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedRestrictedWorker_onerror_Callback(Ark_Int32 resourceId, Ark_ErrorEvent ev)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_RestrictedWorker_onerror_Callback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeErrorEvent(ev);
    enqueueCallback(&_buffer);
}
void callManagedRestrictedWorker_onerror_CallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_ErrorEvent ev)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_RestrictedWorker_onerror_Callback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeErrorEvent(ev);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedRestrictedWorker_onexit_Callback(Ark_Int32 resourceId, Ark_Number code)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_RestrictedWorker_onexit_Callback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(code);
    enqueueCallback(&_buffer);
}
void callManagedRestrictedWorker_onexit_CallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number code)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_RestrictedWorker_onmessage_Callback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeMessageEvents(event);
    enqueueCallback(&_buffer);
}
void callManagedRestrictedWorker_onmessage_CallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_MessageEvents event)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_RestrictedWorker_onmessage_Callback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeMessageEvents(event);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedReuseIdCallback(Ark_Int32 resourceId, Callback_String_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_SaveButtonCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeClickEvent(event);
    argsSerializer.writeInt32(static_cast<Ark_SaveButtonOnClickResult>(result));
    enqueueCallback(&_buffer);
}
void callManagedSaveButtonCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_ClickEvent event, Ark_SaveButtonOnClickResult result, Opt_BusinessError error)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_SaveButtonCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeClickEvent(event);
    argsSerializer.writeInt32(static_cast<Ark_SaveButtonOnClickResult>(result));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedScrollOnScrollCallback(Ark_Int32 resourceId, Ark_Number xOffset, Ark_Number yOffset, Ark_ScrollState scrollState)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_ScrollOnScrollCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(xOffset);
    argsSerializer.writeNumber(yOffset);
    argsSerializer.writeInt32(static_cast<Ark_ScrollState>(scrollState));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedScrollOnWillScrollCallback(Ark_Int32 resourceId, Ark_Number xOffset, Ark_Number yOffset, Ark_ScrollState scrollState, Ark_ScrollSource scrollSource, Callback_OffsetResult_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
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
void callManagedScrollOnWillScrollCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number xOffset, Ark_Number yOffset, Ark_ScrollState scrollState, Ark_ScrollSource scrollSource, Callback_OffsetResult_Void continuation)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_SearchSubmitCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(searchContent);
    Ark_Int32 event_type = INTEROP_RUNTIME_UNDEFINED;
    event_type = runtimeType(event);
    argsSerializer.writeInt8(event_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (event_type)) {
        const auto event_value = event.value;
        argsSerializer.writeSubmitEvent(event_value);
    }
    enqueueCallback(&_buffer);
}
void callManagedSearchSubmitCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_String searchContent, Opt_SubmitEvent event)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_SearchSubmitCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(searchContent);
    Ark_Int32 event_type = INTEROP_RUNTIME_UNDEFINED;
    event_type = runtimeType(event);
    argsSerializer.writeInt8(event_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (event_type)) {
        const auto event_value = event.value;
        argsSerializer.writeSubmitEvent(event_value);
    }
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedSearchValueCallback(Ark_Int32 resourceId, Ark_String value)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_SearchValueCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(value);
    enqueueCallback(&_buffer);
}
void callManagedSearchValueCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_String value)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_SearchValueCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(value);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedSelectedCallback(Ark_Int32 resourceId, Ark_Boolean selected)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_SelectedCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(selected);
    enqueueCallback(&_buffer);
}
void callManagedSelectedCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Boolean selected)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_SelectedCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(selected);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedShouldBuiltInRecognizerParallelWithCallback(Ark_Int32 resourceId, Ark_GestureRecognizer current, Array_GestureRecognizer others, Callback_GestureRecognizer_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_ShouldBuiltInRecognizerParallelWithCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeGestureRecognizer(current);
    argsSerializer.writeInt32(others.length);
    for (int i = 0; i < others.length; i++) {
        const Ark_GestureRecognizer others_element = others.array[i];
        argsSerializer.writeGestureRecognizer(others_element);
    }
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedShouldBuiltInRecognizerParallelWithCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_GestureRecognizer current, Array_GestureRecognizer others, Callback_GestureRecognizer_Void continuation)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_ShouldBuiltInRecognizerParallelWithCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeGestureRecognizer(current);
    argsSerializer.writeInt32(others.length);
    for (int i = 0; i < others.length; i++) {
        const Ark_GestureRecognizer others_element = others.array[i];
        argsSerializer.writeGestureRecognizer(others_element);
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_SizeChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeSizeOptions(oldValue);
    argsSerializer.writeSizeOptions(newValue);
    enqueueCallback(&_buffer);
}
void callManagedSizeChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_SizeOptions oldValue, Ark_SizeOptions newValue)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_SizeChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeSizeOptions(oldValue);
    argsSerializer.writeSizeOptions(newValue);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedSliderTriggerChangeCallback(Ark_Int32 resourceId, Ark_Number value, Ark_SliderChangeMode mode)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_SliderTriggerChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(value);
    argsSerializer.writeInt32(static_cast<Ark_SliderChangeMode>(mode));
    enqueueCallback(&_buffer);
}
void callManagedSliderTriggerChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number value, Ark_SliderChangeMode mode)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_SliderTriggerChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(value);
    argsSerializer.writeInt32(static_cast<Ark_SliderChangeMode>(mode));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedStepperIndexCallback(Ark_Int32 resourceId, Ark_Number stepperIndex)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_StepperIndexCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(stepperIndex);
    enqueueCallback(&_buffer);
}
void callManagedStepperIndexCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number stepperIndex)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_StepperIndexCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(stepperIndex);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedStyledStringMarshallCallback(Ark_Int32 resourceId, Ark_UserDataSpan marshallableVal, Callback_Buffer_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_StyledStringMarshallCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeUserDataSpan(marshallableVal);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedStyledStringMarshallCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_UserDataSpan marshallableVal, Callback_Buffer_Void continuation)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_StyledStringMarshallCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeUserDataSpan(marshallableVal);
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_SubmitCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_EnterKeyType>(enterKey));
    argsSerializer.writeSubmitEvent(event);
    enqueueCallback(&_buffer);
}
void callManagedSubmitCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_EnterKeyType enterKey, Ark_SubmitEvent event)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_SubmitCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_EnterKeyType>(enterKey));
    argsSerializer.writeSubmitEvent(event);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedTabsCustomContentTransitionCallback(Ark_Int32 resourceId, Ark_Number from, Ark_Number to, Callback_Opt_TabContentAnimatedTransition_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_TextAreaSubmitCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_EnterKeyType>(enterKeyType));
    Ark_Int32 event_type = INTEROP_RUNTIME_UNDEFINED;
    event_type = runtimeType(event);
    argsSerializer.writeInt8(event_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (event_type)) {
        const auto event_value = event.value;
        argsSerializer.writeSubmitEvent(event_value);
    }
    enqueueCallback(&_buffer);
}
void callManagedTextAreaSubmitCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_EnterKeyType enterKeyType, Opt_SubmitEvent event)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_TextAreaSubmitCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_EnterKeyType>(enterKeyType));
    Ark_Int32 event_type = INTEROP_RUNTIME_UNDEFINED;
    event_type = runtimeType(event);
    argsSerializer.writeInt8(event_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (event_type)) {
        const auto event_value = event.value;
        argsSerializer.writeSubmitEvent(event_value);
    }
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedTextFieldValueCallback(Ark_Int32 resourceId, Ark_ResourceStr value)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
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
        argsSerializer.writeResource(value_1);
    }
    enqueueCallback(&_buffer);
}
void callManagedTextFieldValueCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_ResourceStr value)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
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
        argsSerializer.writeResource(value_1);
    }
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedTextPickerEnterSelectedAreaCallback(Ark_Int32 resourceId, Ark_Union_String_Array_String value, Ark_Union_Number_Array_Number index)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
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
        const int maxLen = std::min(value_1.length, INT_MAX);
        for (int i = 0; i < maxLen; i++) {
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
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
void callManagedTextTimerAttribute_onTimer_event_type(Ark_Int32 resourceId, Ark_Int64 utc, Ark_Int64 elapsedTime)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_TextTimerAttribute_onTimer_event_type);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt64(utc);
    argsSerializer.writeInt64(elapsedTime);
    enqueueCallback(&_buffer);
}
void callManagedTextTimerAttribute_onTimer_event_typeSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int64 utc, Ark_Int64 elapsedTime)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_TextTimerAttribute_onTimer_event_type);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt64(utc);
    argsSerializer.writeInt64(elapsedTime);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedTransitionFinishCallback(Ark_Int32 resourceId, Ark_Boolean transitionIn)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_TransitionFinishCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(transitionIn);
    enqueueCallback(&_buffer);
}
void callManagedTransitionFinishCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Boolean transitionIn)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_TransitionFinishCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(transitionIn);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedType_NavigationAttribute_customNavContentTransition_delegate(Ark_Int32 resourceId, Ark_NavContentInfo from, Ark_NavContentInfo to, Ark_NavigationOperation operation, Callback_Opt_NavigationAnimatedTransition_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Type_NavigationAttribute_customNavContentTransition_delegate);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNavContentInfo(from);
    argsSerializer.writeNavContentInfo(to);
    argsSerializer.writeInt32(static_cast<Ark_NavigationOperation>(operation));
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedType_NavigationAttribute_customNavContentTransition_delegateSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NavContentInfo from, Ark_NavContentInfo to, Ark_NavigationOperation operation, Callback_Opt_NavigationAnimatedTransition_Void continuation)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Type_NavigationAttribute_customNavContentTransition_delegate);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNavContentInfo(from);
    argsSerializer.writeNavContentInfo(to);
    argsSerializer.writeInt32(static_cast<Ark_NavigationOperation>(operation));
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedType_TextPickerAttribute_onChange_callback(Ark_Int32 resourceId, Ark_Union_String_Array_String value, Ark_Union_Number_Array_Number index)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Type_TextPickerAttribute_onChange_callback);
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
void callManagedType_TextPickerAttribute_onChange_callbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Union_String_Array_String value, Ark_Union_Number_Array_Number index)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Type_TextPickerAttribute_onChange_callback);
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
void callManagedType_WebAttribute_onFileSelectorShow_callback(Ark_Int32 resourceId, Opt_Literal_Function_callback__Object_fileSelector event)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Type_WebAttribute_onFileSelectorShow_callback);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 event_type = INTEROP_RUNTIME_UNDEFINED;
    event_type = runtimeType(event);
    argsSerializer.writeInt8(event_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (event_type)) {
        const auto event_value = event.value;
        const auto event_value_callback_ = event_value.callback_;
        argsSerializer.writeFunction(event_value_callback_);
        const auto event_value_fileSelector = event_value.fileSelector;
        argsSerializer.writeObject(event_value_fileSelector);
    }
    enqueueCallback(&_buffer);
}
void callManagedType_WebAttribute_onFileSelectorShow_callbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Opt_Literal_Function_callback__Object_fileSelector event)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Type_WebAttribute_onFileSelectorShow_callback);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 event_type = INTEROP_RUNTIME_UNDEFINED;
    event_type = runtimeType(event);
    argsSerializer.writeInt8(event_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (event_type)) {
        const auto event_value = event.value;
        const auto event_value_callback_ = event_value.callback_;
        argsSerializer.writeFunction(event_value_callback_);
        const auto event_value_fileSelector = event_value.fileSelector;
        argsSerializer.writeObject(event_value_fileSelector);
    }
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedType_WebAttribute_onUrlLoadIntercept_callback(Ark_Int32 resourceId, Opt_Literal_Union_String_WebResourceRequest_data event, Callback_Boolean_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Type_WebAttribute_onUrlLoadIntercept_callback);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 event_type = INTEROP_RUNTIME_UNDEFINED;
    event_type = runtimeType(event);
    argsSerializer.writeInt8(event_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (event_type)) {
        const auto event_value = event.value;
        const auto event_value_data = event_value.data;
        Ark_Int32 event_value_data_type = INTEROP_RUNTIME_UNDEFINED;
        event_value_data_type = event_value_data.selector;
        if (event_value_data_type == 0) {
            argsSerializer.writeInt8(0);
            const auto event_value_data_0 = event_value_data.value0;
            argsSerializer.writeString(event_value_data_0);
        }
        else if (event_value_data_type == 1) {
            argsSerializer.writeInt8(1);
            const auto event_value_data_1 = event_value_data.value1;
            argsSerializer.writeWebResourceRequest(event_value_data_1);
        }
    }
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedType_WebAttribute_onUrlLoadIntercept_callbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Opt_Literal_Union_String_WebResourceRequest_data event, Callback_Boolean_Void continuation)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Type_WebAttribute_onUrlLoadIntercept_callback);
    argsSerializer.writeInt32(resourceId);
    Ark_Int32 event_type = INTEROP_RUNTIME_UNDEFINED;
    event_type = runtimeType(event);
    argsSerializer.writeInt8(event_type);
    if ((INTEROP_RUNTIME_UNDEFINED) != (event_type)) {
        const auto event_value = event.value;
        const auto event_value_data = event_value.data;
        Ark_Int32 event_value_data_type = INTEROP_RUNTIME_UNDEFINED;
        event_value_data_type = event_value_data.selector;
        if (event_value_data_type == 0) {
            argsSerializer.writeInt8(0);
            const auto event_value_data_0 = event_value_data.value0;
            argsSerializer.writeString(event_value_data_0);
        }
        else if (event_value_data_type == 1) {
            argsSerializer.writeInt8(1);
            const auto event_value_data_1 = event_value_data.value1;
            argsSerializer.writeWebResourceRequest(event_value_data_1);
        }
    }
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedVisibleAreaChangeCallback(Ark_Int32 resourceId, Ark_Boolean isExpanding, Ark_Number currentRatio)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_VisibleAreaChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(isExpanding);
    argsSerializer.writeNumber(currentRatio);
    enqueueCallback(&_buffer);
}
void callManagedVisibleAreaChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Boolean isExpanding, Ark_Number currentRatio)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
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
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_VoidCallback);
    argsSerializer.writeInt32(resourceId);
    enqueueCallback(&_buffer);
}
void callManagedVoidCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_VoidCallback);
    argsSerializer.writeInt32(resourceId);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedWebKeyboardCallback(Ark_Int32 resourceId, Ark_WebKeyboardCallbackInfo keyboardCallbackInfo, Callback_WebKeyboardOptions_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_WebKeyboardCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeWebKeyboardCallbackInfo(keyboardCallbackInfo);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedWebKeyboardCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_WebKeyboardCallbackInfo keyboardCallbackInfo, Callback_WebKeyboardOptions_Void continuation)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_WebKeyboardCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeWebKeyboardCallbackInfo(keyboardCallbackInfo);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedWithThemeInterface(Ark_Int32 resourceId, Ark_WithThemeOptions options, Callback_WithThemeAttribute_Void continuation)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_WithThemeInterface);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeWithThemeOptions(options);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(&_buffer);
}
void callManagedWithThemeInterfaceSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_WithThemeOptions options, Callback_WithThemeAttribute_Void continuation)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_WithThemeInterface);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeWithThemeOptions(options);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
void callManagedCallback_String_SurfaceRect_Void(Ark_Int32 resourceId, Ark_String surfaceId, Ark_SurfaceRect rect)
{
    CallbackBuffer _buffer = {{}, {}};
    const Ark_CallbackResource _callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    _buffer.resourceHolder.holdCallbackResource(&_callbackResourceSelf);
    Serializer argsSerializer = Serializer((KSerializerBuffer)&(_buffer.buffer), sizeof(_buffer.buffer), &(_buffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_String_SurfaceRect_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(surfaceId);
    argsSerializer.writeSurfaceRect(rect);
    enqueueCallback(&_buffer);
}
void callManagedCallback_String_SurfaceRect_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_String surfaceId, Ark_SurfaceRect rect)
{
    uint8_t _buffer[4096];
    Serializer argsSerializer = Serializer((KSerializerBuffer)&_buffer, sizeof(_buffer), nullptr);
    argsSerializer.writeInt32(Kind_Callback_String_SurfaceRect_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(surfaceId);
    argsSerializer.writeSurfaceRect(rect);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(_buffer), _buffer);
}
Ark_NativePointer getManagedCallbackCaller(CallbackKind kind)
{
    switch (kind) {
        case Kind_AccessibilityCallback: return reinterpret_cast<Ark_NativePointer>(callManagedAccessibilityCallback);
        case Kind_AccessibilityFocusCallback: return reinterpret_cast<Ark_NativePointer>(callManagedAccessibilityFocusCallback);
        case Kind_AsyncCallback_Array_TextMenuItem_Array_TextMenuItem: return reinterpret_cast<Ark_NativePointer>(callManagedAsyncCallback_Array_TextMenuItem_Array_TextMenuItem);
        case Kind_AsyncCallback_image_PixelMap_Void: return reinterpret_cast<Ark_NativePointer>(callManagedAsyncCallback_image_PixelMap_Void);
        case Kind_AsyncCallback_TextMenuItem_TextRange_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedAsyncCallback_TextMenuItem_TextRange_Boolean);
        case Kind_ButtonTriggerClickCallback: return reinterpret_cast<Ark_NativePointer>(callManagedButtonTriggerClickCallback);
        case Kind_Callback_Any_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Any_Void);
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
        case Kind_Callback_CustomBuilder_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_CustomBuilder_Void);
        case Kind_Callback_CutEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_CutEvent_Void);
        case Kind_Callback_Date_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Date_Void);
        case Kind_Callback_DatePickerResult_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_DatePickerResult_Void);
        case Kind_Callback_DeleteValue_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_DeleteValue_Boolean);
        case Kind_Callback_DeleteValue_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_DeleteValue_Void);
        case Kind_Callback_DismissContentCoverAction_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_DismissContentCoverAction_Void);
        case Kind_Callback_DismissDialogAction_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_DismissDialogAction_Void);
        case Kind_Callback_DismissPopupAction_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_DismissPopupAction_Void);
        case Kind_Callback_DismissSheetAction_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_DismissSheetAction_Void);
        case Kind_Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_DragEvent_String_Union_CustomBuilder_DragItemInfo);
        case Kind_Callback_DragEvent_String_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_DragEvent_String_Void);
        case Kind_Callback_EditableTextChangeValue_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_EditableTextChangeValue_Boolean);
        case Kind_Callback_EnterKeyType_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_EnterKeyType_Void);
        case Kind_Callback_Extender_OnFinish: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Extender_OnFinish);
        case Kind_Callback_Extender_OnProgress: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Extender_OnProgress);
        case Kind_Callback_FocusAxisEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_FocusAxisEvent_Void);
        case Kind_Callback_FormCallbackInfo_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_FormCallbackInfo_Void);
        case Kind_Callback_FullscreenInfo_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_FullscreenInfo_Void);
        case Kind_Callback_GestureEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_GestureEvent_Void);
        case Kind_Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_GestureInfo_BaseGestureEvent_GestureJudgeResult);
        case Kind_Callback_GestureJudgeResult_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_GestureJudgeResult_Void);
        case Kind_Callback_GestureRecognizer_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_GestureRecognizer_Void);
        case Kind_Callback_HitTestMode_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_HitTestMode_Void);
        case Kind_Callback_HoverEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_HoverEvent_Void);
        case Kind_Callback_InsertValue_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_InsertValue_Boolean);
        case Kind_Callback_InsertValue_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_InsertValue_Void);
        case Kind_Callback_ItemDragInfo_Number_Number_Boolean_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_ItemDragInfo_Number_Number_Boolean_Void);
        case Kind_Callback_ItemDragInfo_Number_Number_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_ItemDragInfo_Number_Number_Void);
        case Kind_Callback_ItemDragInfo_Number_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_ItemDragInfo_Number_Void);
        case Kind_Callback_ItemDragInfo_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_ItemDragInfo_Void);
        case Kind_Callback_KeyEvent_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_KeyEvent_Boolean);
        case Kind_Callback_KeyEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_KeyEvent_Void);
        case Kind_Callback_Literal_Boolean_isVisible_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Literal_Boolean_isVisible_Void);
        case Kind_Callback_Literal_Function_handler_Object_error_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Literal_Function_handler_Object_error_Void);
        case Kind_Callback_Literal_Number_code__want_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Literal_Number_code__want_Void);
        case Kind_Callback_Literal_Number_errcode_String_msg_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Literal_Number_errcode_String_msg_Void);
        case Kind_Callback_Literal_Number_offsetRemain_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Literal_Number_offsetRemain_Void);
        case Kind_Callback_Literal_Object_detail_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Literal_Object_detail_Boolean);
        case Kind_Callback_Literal_String_plainText_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Literal_String_plainText_Void);
        case Kind_Callback_Map_String_Object_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Map_String_Object_Void);
        case Kind_Callback_MarqueeState_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_MarqueeState_Void);
        case Kind_Callback_MouseEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_MouseEvent_Void);
        case Kind_Callback_NativeEmbedDataInfo_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_NativeEmbedDataInfo_Void);
        case Kind_Callback_NativeEmbedTouchInfo_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_NativeEmbedTouchInfo_Void);
        case Kind_Callback_NavDestinationActiveReason_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_NavDestinationActiveReason_Void);
        case Kind_Callback_NavDestinationContext_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_NavDestinationContext_Void);
        case Kind_Callback_NavigationMode_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_NavigationMode_Void);
        case Kind_Callback_NavigationTitleMode_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_NavigationTitleMode_Void);
        case Kind_Callback_NavigationTransitionProxy_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_NavigationTransitionProxy_Void);
        case Kind_Callback_Number_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Number_Boolean);
        case Kind_Callback_Number_Number_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Number_Number_Boolean);
        case Kind_Callback_Number_Number_ComputedBarAttribute: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Number_Number_ComputedBarAttribute);
        case Kind_Callback_Number_Number_Number_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Number_Number_Number_Void);
        case Kind_Callback_Number_Number_PanelMode_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Number_Number_PanelMode_Void);
        case Kind_Callback_Number_Number_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Number_Number_Void);
        case Kind_Callback_Number_ScrollState_Literal_Number_offsetRemain: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Number_ScrollState_Literal_Number_offsetRemain);
        case Kind_Callback_Number_SliderChangeMode_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Number_SliderChangeMode_Void);
        case Kind_Callback_Number_String_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Number_String_Void);
        case Kind_Callback_Number_Tuple_Number_Number: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Number_Tuple_Number_Number);
        case Kind_Callback_Number_Tuple_Number_Number_Number_Number: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Number_Tuple_Number_Number_Number_Number);
        case Kind_Callback_Number_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Number_Void);
        case Kind_Callback_Object_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Object_Void);
        case Kind_Callback_OffsetResult_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OffsetResult_Void);
        case Kind_Callback_ScrollResult_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_ScrollResult_Void);
        case Kind_Callback_OnAlertEvent_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnAlertEvent_Boolean);
        case Kind_Callback_OnAudioStateChangedEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnAudioStateChangedEvent_Void);
        case Kind_Callback_OnBeforeUnloadEvent_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnBeforeUnloadEvent_Boolean);
        case Kind_Callback_OnClientAuthenticationEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnClientAuthenticationEvent_Void);
        case Kind_Callback_OnConfirmEvent_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnConfirmEvent_Boolean);
        case Kind_Callback_OnConsoleEvent_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnConsoleEvent_Boolean);
        case Kind_Callback_OnContextMenuShowEvent_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnContextMenuShowEvent_Boolean);
        case Kind_Callback_OnDataResubmittedEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnDataResubmittedEvent_Void);
        case Kind_Callback_OnDownloadStartEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnDownloadStartEvent_Void);
        case Kind_Callback_OnErrorReceiveEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnErrorReceiveEvent_Void);
        case Kind_Callback_OnFaviconReceivedEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnFaviconReceivedEvent_Void);
        case Kind_Callback_OnFirstContentfulPaintEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnFirstContentfulPaintEvent_Void);
        case Kind_Callback_OnGeolocationShowEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnGeolocationShowEvent_Void);
        case Kind_Callback_OnHttpAuthRequestEvent_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnHttpAuthRequestEvent_Boolean);
        case Kind_Callback_OnHttpErrorReceiveEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnHttpErrorReceiveEvent_Void);
        case Kind_Callback_OnInterceptRequestEvent_WebResourceResponse: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnInterceptRequestEvent_WebResourceResponse);
        case Kind_Callback_OnLoadInterceptEvent_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnLoadInterceptEvent_Boolean);
        case Kind_Callback_OnOverScrollEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnOverScrollEvent_Void);
        case Kind_Callback_OnPageBeginEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnPageBeginEvent_Void);
        case Kind_Callback_OnPageEndEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnPageEndEvent_Void);
        case Kind_Callback_OnPageVisibleEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnPageVisibleEvent_Void);
        case Kind_Callback_OnPermissionRequestEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnPermissionRequestEvent_Void);
        case Kind_Callback_OnProgressChangeEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnProgressChangeEvent_Void);
        case Kind_Callback_OnPromptEvent_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnPromptEvent_Boolean);
        case Kind_Callback_OnRefreshAccessedHistoryEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnRefreshAccessedHistoryEvent_Void);
        case Kind_Callback_OnRenderExitedEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnRenderExitedEvent_Void);
        case Kind_Callback_OnResourceLoadEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnResourceLoadEvent_Void);
        case Kind_Callback_OnScaleChangeEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnScaleChangeEvent_Void);
        case Kind_Callback_OnScreenCaptureRequestEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnScreenCaptureRequestEvent_Void);
        case Kind_Callback_OnScrollEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnScrollEvent_Void);
        case Kind_Callback_OnScrollFrameBeginHandlerResult_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnScrollFrameBeginHandlerResult_Void);
        case Kind_Callback_OnSearchResultReceiveEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnSearchResultReceiveEvent_Void);
        case Kind_Callback_OnShowFileSelectorEvent_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnShowFileSelectorEvent_Boolean);
        case Kind_Callback_OnSslErrorEventReceiveEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnSslErrorEventReceiveEvent_Void);
        case Kind_Callback_OnTitleReceiveEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnTitleReceiveEvent_Void);
        case Kind_Callback_OnTouchIconUrlReceivedEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnTouchIconUrlReceivedEvent_Void);
        case Kind_Callback_OnWindowNewEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnWindowNewEvent_Void);
        case Kind_Callback_Opt_Array_NavDestinationTransition_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Opt_Array_NavDestinationTransition_Void);
        case Kind_Callback_Opt_Array_String_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Opt_Array_String_Void);
        case Kind_Callback_Opt_Boolean_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Opt_Boolean_Void);
        case Kind_Callback_Opt_NavigationAnimatedTransition_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Opt_NavigationAnimatedTransition_Void);
        case Kind_Callback_Opt_Number_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Opt_Number_Void);
        case Kind_Callback_Opt_PanelMode_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Opt_PanelMode_Void);
        case Kind_Callback_Opt_ResourceStr_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Opt_ResourceStr_Void);
        case Kind_Callback_Opt_StyledString_Opt_Array_String_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Opt_StyledString_Opt_Array_String_Void);
        case Kind_Callback_Opt_TabContentAnimatedTransition_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Opt_TabContentAnimatedTransition_Void);
        case Kind_Callback_Opt_Union_Number_Resource_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Opt_Union_Number_Resource_Void);
        case Kind_Callback_PlaybackInfo_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_PlaybackInfo_Void);
        case Kind_Callback_Pointer_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Pointer_Void);
        case Kind_Callback_PopInfo_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_PopInfo_Void);
        case Kind_Callback_PreDragStatus_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_PreDragStatus_Void);
        case Kind_Callback_PreparedInfo_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_PreparedInfo_Void);
        case Kind_Callback_RangeUpdate: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_RangeUpdate);
        case Kind_Callback_RefreshStatus_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_RefreshStatus_Void);
        case Kind_Callback_ResourceStr_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_ResourceStr_Void);
        case Kind_Callback_RichEditorChangeValue_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_RichEditorChangeValue_Boolean);
        case Kind_Callback_RichEditorDeleteValue_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_RichEditorDeleteValue_Boolean);
        case Kind_Callback_RichEditorInsertValue_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_RichEditorInsertValue_Boolean);
        case Kind_Callback_RichEditorRange_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_RichEditorRange_Void);
        case Kind_Callback_RichEditorSelection_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_RichEditorSelection_Void);
        case Kind_Callback_RichEditorTextSpanResult_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_RichEditorTextSpanResult_Void);
        case Kind_Callback_SheetDismiss_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_SheetDismiss_Void);
        case Kind_Callback_SheetType_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_SheetType_Void);
        case Kind_Callback_SpringBackAction_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_SpringBackAction_Void);
        case Kind_Callback_StateStylesChange: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_StateStylesChange);
        case Kind_Callback_String_Number_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_String_Number_Void);
        case Kind_Callback_String_Opt_Object_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_String_Opt_Object_Void);
        case Kind_Callback_String_PasteEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_String_PasteEvent_Void);
        case Kind_Callback_String_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_String_Void);
        case Kind_Callback_StyledStringChangeValue_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_StyledStringChangeValue_Boolean);
        case Kind_Callback_StyledStringMarshallingValue_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_StyledStringMarshallingValue_Void);
        case Kind_Callback_SwipeActionState_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_SwipeActionState_Void);
        case Kind_Callback_SwiperContentTransitionProxy_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_SwiperContentTransitionProxy_Void);
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
        case Kind_Callback_Type_ImageAttribute_onComplete_callback_event_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Type_ImageAttribute_onComplete_callback_event_Void);
        case Kind_Callback_UIExtensionProxy_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_UIExtensionProxy_Void);
        case Kind_Callback_Union_CustomBuilder_DragItemInfo_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Union_CustomBuilder_DragItemInfo_Void);
        case Kind_Callback_Union_Number_Array_Number_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Union_Number_Array_Number_Void);
        case Kind_Callback_Union_String_Array_String_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Union_String_Array_String_Void);
        case Kind_Callback_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Void);
        case Kind_Callback_WebKeyboardOptions_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_WebKeyboardOptions_Void);
        case Kind_Callback_WebResourceResponse_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_WebResourceResponse_Void);
        case Kind_Callback_WithThemeAttribute_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_WithThemeAttribute_Void);
        case Kind_Callback_WrappedBuilder_Args_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_WrappedBuilder_Args_Void);
        case Kind_ContentDidScrollCallback: return reinterpret_cast<Ark_NativePointer>(callManagedContentDidScrollCallback);
        case Kind_ContentWillScrollCallback: return reinterpret_cast<Ark_NativePointer>(callManagedContentWillScrollCallback);
        case Kind_Context_getGroupDir_Callback: return reinterpret_cast<Ark_NativePointer>(callManagedContext_getGroupDir_Callback);
        case Kind_CustomNodeBuilder: return reinterpret_cast<Ark_NativePointer>(callManagedCustomNodeBuilder);
        case Kind_DrawCallback: return reinterpret_cast<Ark_NativePointer>(callManagedDrawCallback);
        case Kind_EditableTextOnChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedEditableTextOnChangeCallback);
        case Kind_ErrorCallback: return reinterpret_cast<Ark_NativePointer>(callManagedErrorCallback);
        case Kind_GestureRecognizerJudgeBeginCallback: return reinterpret_cast<Ark_NativePointer>(callManagedGestureRecognizerJudgeBeginCallback);
        case Kind_GetItemMainSizeByIndex: return reinterpret_cast<Ark_NativePointer>(callManagedGetItemMainSizeByIndex);
        case Kind_GridAttribute_onItemDragStart_event_type: return reinterpret_cast<Ark_NativePointer>(callManagedGridAttribute_onItemDragStart_event_type);
        case Kind_HoverCallback: return reinterpret_cast<Ark_NativePointer>(callManagedHoverCallback);
        case Kind_ImageCompleteCallback: return reinterpret_cast<Ark_NativePointer>(callManagedImageCompleteCallback);
        case Kind_ImageErrorCallback: return reinterpret_cast<Ark_NativePointer>(callManagedImageErrorCallback);
        case Kind_InterceptionModeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedInterceptionModeCallback);
        case Kind_InterceptionShowCallback: return reinterpret_cast<Ark_NativePointer>(callManagedInterceptionShowCallback);
        case Kind_ListAttribute_onItemDragStart_event_type: return reinterpret_cast<Ark_NativePointer>(callManagedListAttribute_onItemDragStart_event_type);
        case Kind_LocationButtonCallback: return reinterpret_cast<Ark_NativePointer>(callManagedLocationButtonCallback);
        case Kind_MenuCallback: return reinterpret_cast<Ark_NativePointer>(callManagedMenuCallback);
        case Kind_MenuOnAppearCallback: return reinterpret_cast<Ark_NativePointer>(callManagedMenuOnAppearCallback);
        case Kind_NavDestinationTransitionDelegate: return reinterpret_cast<Ark_NativePointer>(callManagedNavDestinationTransitionDelegate);
        case Kind_NavExtender_OnUpdateStack: return reinterpret_cast<Ark_NativePointer>(callManagedNavExtender_OnUpdateStack);
        case Kind_NodeContainer_AboutToResizeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedNodeContainer_AboutToResizeCallback);
        case Kind_OnAdsBlockedCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnAdsBlockedCallback);
        case Kind_OnAlphabetIndexerPopupSelectCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnAlphabetIndexerPopupSelectCallback);
        case Kind_OnAlphabetIndexerRequestPopupDataCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnAlphabetIndexerRequestPopupDataCallback);
        case Kind_OnAlphabetIndexerSelectCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnAlphabetIndexerSelectCallback);
        case Kind_OnCheckboxChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnCheckboxChangeCallback);
        case Kind_OnCheckboxGroupChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnCheckboxGroupChangeCallback);
        case Kind_OnContentScrollCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnContentScrollCallback);
        case Kind_OnContextMenuHideCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnContextMenuHideCallback);
        case Kind_OnDidChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnDidChangeCallback);
        case Kind_OnDragEventCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnDragEventCallback);
        case Kind_OnFirstMeaningfulPaintCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnFirstMeaningfulPaintCallback);
        case Kind_OnFoldStatusChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnFoldStatusChangeCallback);
        case Kind_OnFullScreenEnterCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnFullScreenEnterCallback);
        case Kind_OnHoverCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnHoverCallback);
        case Kind_OnHoverStatusChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnHoverStatusChangeCallback);
        case Kind_OnIntelligentTrackingPreventionCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnIntelligentTrackingPreventionCallback);
        case Kind_OnLargestContentfulPaintCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnLargestContentfulPaintCallback);
        case Kind_OnLinearIndicatorChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnLinearIndicatorChangeCallback);
        case Kind_OnMoveHandler: return reinterpret_cast<Ark_NativePointer>(callManagedOnMoveHandler);
        case Kind_OnNativeEmbedVisibilityChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnNativeEmbedVisibilityChangeCallback);
        case Kind_OnNativeLoadCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnNativeLoadCallback);
        case Kind_OnNavigationEntryCommittedCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnNavigationEntryCommittedCallback);
        case Kind_OnOverrideUrlLoadingCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnOverrideUrlLoadingCallback);
        case Kind_OnPasteCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnPasteCallback);
        case Kind_OnRadioChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnRadioChangeCallback);
        case Kind_OnRatingChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnRatingChangeCallback);
        case Kind_OnRenderProcessNotRespondingCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnRenderProcessNotRespondingCallback);
        case Kind_OnRenderProcessRespondingCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnRenderProcessRespondingCallback);
        case Kind_OnSafeBrowsingCheckResultCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnSafeBrowsingCheckResultCallback);
        case Kind_OnScrollCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnScrollCallback);
        case Kind_OnWillScrollCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnWillScrollCallback);
        case Kind_OnScrollEdgeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnScrollEdgeCallback);
        case Kind_OnScrollFrameBeginCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnScrollFrameBeginCallback);
        case Kind_OnScrollVisibleContentChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnScrollVisibleContentChangeCallback);
        case Kind_OnSelectCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnSelectCallback);
        case Kind_OnSslErrorEventCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnSslErrorEventCallback);
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
        case Kind_OnViewportFitChangedCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnViewportFitChangedCallback);
        case Kind_PageTransitionCallback: return reinterpret_cast<Ark_NativePointer>(callManagedPageTransitionCallback);
        case Kind_PasteButtonCallback: return reinterpret_cast<Ark_NativePointer>(callManagedPasteButtonCallback);
        case Kind_PasteEventCallback: return reinterpret_cast<Ark_NativePointer>(callManagedPasteEventCallback);
        case Kind_PluginErrorCallback: return reinterpret_cast<Ark_NativePointer>(callManagedPluginErrorCallback);
        case Kind_PopupStateChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedPopupStateChangeCallback);
        case Kind_ReceiveCallback: return reinterpret_cast<Ark_NativePointer>(callManagedReceiveCallback);
        case Kind_RestrictedWorker_onerror_Callback: return reinterpret_cast<Ark_NativePointer>(callManagedRestrictedWorker_onerror_Callback);
        case Kind_RestrictedWorker_onexit_Callback: return reinterpret_cast<Ark_NativePointer>(callManagedRestrictedWorker_onexit_Callback);
        case Kind_RestrictedWorker_onmessage_Callback: return reinterpret_cast<Ark_NativePointer>(callManagedRestrictedWorker_onmessage_Callback);
        case Kind_ReuseIdCallback: return reinterpret_cast<Ark_NativePointer>(callManagedReuseIdCallback);
        case Kind_SaveButtonCallback: return reinterpret_cast<Ark_NativePointer>(callManagedSaveButtonCallback);
        case Kind_ScrollOnScrollCallback: return reinterpret_cast<Ark_NativePointer>(callManagedScrollOnScrollCallback);
        case Kind_ScrollOnWillScrollCallback: return reinterpret_cast<Ark_NativePointer>(callManagedScrollOnWillScrollCallback);
        case Kind_SearchSubmitCallback: return reinterpret_cast<Ark_NativePointer>(callManagedSearchSubmitCallback);
        case Kind_SearchValueCallback: return reinterpret_cast<Ark_NativePointer>(callManagedSearchValueCallback);
        case Kind_SelectedCallback: return reinterpret_cast<Ark_NativePointer>(callManagedSelectedCallback);
        case Kind_ShouldBuiltInRecognizerParallelWithCallback: return reinterpret_cast<Ark_NativePointer>(callManagedShouldBuiltInRecognizerParallelWithCallback);
        case Kind_SizeChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedSizeChangeCallback);
        case Kind_SliderTriggerChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedSliderTriggerChangeCallback);
        case Kind_StepperIndexCallback: return reinterpret_cast<Ark_NativePointer>(callManagedStepperIndexCallback);
        case Kind_StyledStringMarshallCallback: return reinterpret_cast<Ark_NativePointer>(callManagedStyledStringMarshallCallback);
        case Kind_StyledStringUnmarshallCallback: return reinterpret_cast<Ark_NativePointer>(callManagedStyledStringUnmarshallCallback);
        case Kind_SubmitCallback: return reinterpret_cast<Ark_NativePointer>(callManagedSubmitCallback);
        case Kind_TabsCustomContentTransitionCallback: return reinterpret_cast<Ark_NativePointer>(callManagedTabsCustomContentTransitionCallback);
        case Kind_TextAreaSubmitCallback: return reinterpret_cast<Ark_NativePointer>(callManagedTextAreaSubmitCallback);
        case Kind_TextFieldValueCallback: return reinterpret_cast<Ark_NativePointer>(callManagedTextFieldValueCallback);
        case Kind_TextPickerEnterSelectedAreaCallback: return reinterpret_cast<Ark_NativePointer>(callManagedTextPickerEnterSelectedAreaCallback);
        case Kind_TextPickerScrollStopCallback: return reinterpret_cast<Ark_NativePointer>(callManagedTextPickerScrollStopCallback);
        case Kind_TextTimerAttribute_onTimer_event_type: return reinterpret_cast<Ark_NativePointer>(callManagedTextTimerAttribute_onTimer_event_type);
        case Kind_TransitionFinishCallback: return reinterpret_cast<Ark_NativePointer>(callManagedTransitionFinishCallback);
        case Kind_Type_NavigationAttribute_customNavContentTransition_delegate: return reinterpret_cast<Ark_NativePointer>(callManagedType_NavigationAttribute_customNavContentTransition_delegate);
        case Kind_Type_TextPickerAttribute_onChange_callback: return reinterpret_cast<Ark_NativePointer>(callManagedType_TextPickerAttribute_onChange_callback);
        case Kind_Type_WebAttribute_onFileSelectorShow_callback: return reinterpret_cast<Ark_NativePointer>(callManagedType_WebAttribute_onFileSelectorShow_callback);
        case Kind_Type_WebAttribute_onUrlLoadIntercept_callback: return reinterpret_cast<Ark_NativePointer>(callManagedType_WebAttribute_onUrlLoadIntercept_callback);
        case Kind_VisibleAreaChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedVisibleAreaChangeCallback);
        case Kind_VoidCallback: return reinterpret_cast<Ark_NativePointer>(callManagedVoidCallback);
        case Kind_WebKeyboardCallback: return reinterpret_cast<Ark_NativePointer>(callManagedWebKeyboardCallback);
        case Kind_WithThemeInterface: return reinterpret_cast<Ark_NativePointer>(callManagedWithThemeInterface);
        case Kind_Callback_String_SurfaceRect_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_String_SurfaceRect_Void);
    }
    return nullptr;
}
Ark_NativePointer getManagedCallbackCallerSync(CallbackKind kind)
{
    switch (kind) {
        case Kind_AccessibilityCallback: return reinterpret_cast<Ark_NativePointer>(callManagedAccessibilityCallbackSync);
        case Kind_AccessibilityFocusCallback: return reinterpret_cast<Ark_NativePointer>(callManagedAccessibilityFocusCallbackSync);
        case Kind_AsyncCallback_Array_TextMenuItem_Array_TextMenuItem: return reinterpret_cast<Ark_NativePointer>(callManagedAsyncCallback_Array_TextMenuItem_Array_TextMenuItemSync);
        case Kind_AsyncCallback_image_PixelMap_Void: return reinterpret_cast<Ark_NativePointer>(callManagedAsyncCallback_image_PixelMap_VoidSync);
        case Kind_AsyncCallback_TextMenuItem_TextRange_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedAsyncCallback_TextMenuItem_TextRange_BooleanSync);
        case Kind_ButtonTriggerClickCallback: return reinterpret_cast<Ark_NativePointer>(callManagedButtonTriggerClickCallbackSync);
        case Kind_Callback_Any_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Any_VoidSync);
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
        case Kind_Callback_CustomBuilder_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_CustomBuilder_VoidSync);
        case Kind_Callback_CutEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_CutEvent_VoidSync);
        case Kind_Callback_Date_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Date_VoidSync);
        case Kind_Callback_DatePickerResult_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_DatePickerResult_VoidSync);
        case Kind_Callback_DeleteValue_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_DeleteValue_BooleanSync);
        case Kind_Callback_DeleteValue_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_DeleteValue_VoidSync);
        case Kind_Callback_DismissContentCoverAction_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_DismissContentCoverAction_VoidSync);
        case Kind_Callback_DismissDialogAction_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_DismissDialogAction_VoidSync);
        case Kind_Callback_DismissPopupAction_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_DismissPopupAction_VoidSync);
        case Kind_Callback_DismissSheetAction_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_DismissSheetAction_VoidSync);
        case Kind_Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_DragEvent_String_Union_CustomBuilder_DragItemInfoSync);
        case Kind_Callback_DragEvent_String_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_DragEvent_String_VoidSync);
        case Kind_Callback_EditableTextChangeValue_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_EditableTextChangeValue_BooleanSync);
        case Kind_Callback_EnterKeyType_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_EnterKeyType_VoidSync);
        case Kind_Callback_Extender_OnFinish: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Extender_OnFinishSync);
        case Kind_Callback_Extender_OnProgress: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Extender_OnProgressSync);
        case Kind_Callback_FocusAxisEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_FocusAxisEvent_VoidSync);
        case Kind_Callback_FormCallbackInfo_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_FormCallbackInfo_VoidSync);
        case Kind_Callback_FullscreenInfo_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_FullscreenInfo_VoidSync);
        case Kind_Callback_GestureEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_GestureEvent_VoidSync);
        case Kind_Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_GestureInfo_BaseGestureEvent_GestureJudgeResultSync);
        case Kind_Callback_GestureJudgeResult_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_GestureJudgeResult_VoidSync);
        case Kind_Callback_GestureRecognizer_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_GestureRecognizer_VoidSync);
        case Kind_Callback_HitTestMode_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_HitTestMode_VoidSync);
        case Kind_Callback_HoverEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_HoverEvent_VoidSync);
        case Kind_Callback_InsertValue_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_InsertValue_BooleanSync);
        case Kind_Callback_InsertValue_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_InsertValue_VoidSync);
        case Kind_Callback_ItemDragInfo_Number_Number_Boolean_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_ItemDragInfo_Number_Number_Boolean_VoidSync);
        case Kind_Callback_ItemDragInfo_Number_Number_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_ItemDragInfo_Number_Number_VoidSync);
        case Kind_Callback_ItemDragInfo_Number_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_ItemDragInfo_Number_VoidSync);
        case Kind_Callback_ItemDragInfo_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_ItemDragInfo_VoidSync);
        case Kind_Callback_KeyEvent_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_KeyEvent_BooleanSync);
        case Kind_Callback_KeyEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_KeyEvent_VoidSync);
        case Kind_Callback_Literal_Boolean_isVisible_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Literal_Boolean_isVisible_VoidSync);
        case Kind_Callback_Literal_Function_handler_Object_error_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Literal_Function_handler_Object_error_VoidSync);
        case Kind_Callback_Literal_Number_code__want_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Literal_Number_code__want_VoidSync);
        case Kind_Callback_Literal_Number_errcode_String_msg_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Literal_Number_errcode_String_msg_VoidSync);
        case Kind_Callback_Literal_Number_offsetRemain_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Literal_Number_offsetRemain_VoidSync);
        case Kind_Callback_Literal_Object_detail_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Literal_Object_detail_BooleanSync);
        case Kind_Callback_Literal_String_plainText_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Literal_String_plainText_VoidSync);
        case Kind_Callback_Map_String_Object_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Map_String_Object_VoidSync);
        case Kind_Callback_MarqueeState_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_MarqueeState_VoidSync);
        case Kind_Callback_MouseEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_MouseEvent_VoidSync);
        case Kind_Callback_NativeEmbedDataInfo_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_NativeEmbedDataInfo_VoidSync);
        case Kind_Callback_NativeEmbedTouchInfo_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_NativeEmbedTouchInfo_VoidSync);
        case Kind_Callback_NavDestinationActiveReason_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_NavDestinationActiveReason_VoidSync);
        case Kind_Callback_NavDestinationContext_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_NavDestinationContext_VoidSync);
        case Kind_Callback_NavigationMode_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_NavigationMode_VoidSync);
        case Kind_Callback_NavigationTitleMode_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_NavigationTitleMode_VoidSync);
        case Kind_Callback_NavigationTransitionProxy_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_NavigationTransitionProxy_VoidSync);
        case Kind_Callback_Number_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Number_BooleanSync);
        case Kind_Callback_Number_Number_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Number_Number_BooleanSync);
        case Kind_Callback_Number_Number_ComputedBarAttribute: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Number_Number_ComputedBarAttributeSync);
        case Kind_Callback_Number_Number_Number_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Number_Number_Number_VoidSync);
        case Kind_Callback_Number_Number_PanelMode_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Number_Number_PanelMode_VoidSync);
        case Kind_Callback_Number_Number_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Number_Number_VoidSync);
        case Kind_Callback_Number_ScrollState_Literal_Number_offsetRemain: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Number_ScrollState_Literal_Number_offsetRemainSync);
        case Kind_Callback_Number_SliderChangeMode_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Number_SliderChangeMode_VoidSync);
        case Kind_Callback_Number_String_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Number_String_VoidSync);
        case Kind_Callback_Number_Tuple_Number_Number: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Number_Tuple_Number_NumberSync);
        case Kind_Callback_Number_Tuple_Number_Number_Number_Number: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Number_Tuple_Number_Number_Number_NumberSync);
        case Kind_Callback_Number_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Number_VoidSync);
        case Kind_Callback_Object_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Object_VoidSync);
        case Kind_Callback_OffsetResult_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OffsetResult_VoidSync);
        case Kind_Callback_ScrollResult_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_ScrollResult_VoidSync);
        case Kind_Callback_OnAlertEvent_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnAlertEvent_BooleanSync);
        case Kind_Callback_OnAudioStateChangedEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnAudioStateChangedEvent_VoidSync);
        case Kind_Callback_OnBeforeUnloadEvent_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnBeforeUnloadEvent_BooleanSync);
        case Kind_Callback_OnClientAuthenticationEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnClientAuthenticationEvent_VoidSync);
        case Kind_Callback_OnConfirmEvent_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnConfirmEvent_BooleanSync);
        case Kind_Callback_OnConsoleEvent_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnConsoleEvent_BooleanSync);
        case Kind_Callback_OnContextMenuShowEvent_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnContextMenuShowEvent_BooleanSync);
        case Kind_Callback_OnDataResubmittedEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnDataResubmittedEvent_VoidSync);
        case Kind_Callback_OnDownloadStartEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnDownloadStartEvent_VoidSync);
        case Kind_Callback_OnErrorReceiveEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnErrorReceiveEvent_VoidSync);
        case Kind_Callback_OnFaviconReceivedEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnFaviconReceivedEvent_VoidSync);
        case Kind_Callback_OnFirstContentfulPaintEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnFirstContentfulPaintEvent_VoidSync);
        case Kind_Callback_OnGeolocationShowEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnGeolocationShowEvent_VoidSync);
        case Kind_Callback_OnHttpAuthRequestEvent_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnHttpAuthRequestEvent_BooleanSync);
        case Kind_Callback_OnHttpErrorReceiveEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnHttpErrorReceiveEvent_VoidSync);
        case Kind_Callback_OnInterceptRequestEvent_WebResourceResponse: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnInterceptRequestEvent_WebResourceResponseSync);
        case Kind_Callback_OnLoadInterceptEvent_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnLoadInterceptEvent_BooleanSync);
        case Kind_Callback_OnOverScrollEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnOverScrollEvent_VoidSync);
        case Kind_Callback_OnPageBeginEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnPageBeginEvent_VoidSync);
        case Kind_Callback_OnPageEndEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnPageEndEvent_VoidSync);
        case Kind_Callback_OnPageVisibleEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnPageVisibleEvent_VoidSync);
        case Kind_Callback_OnPermissionRequestEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnPermissionRequestEvent_VoidSync);
        case Kind_Callback_OnProgressChangeEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnProgressChangeEvent_VoidSync);
        case Kind_Callback_OnPromptEvent_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnPromptEvent_BooleanSync);
        case Kind_Callback_OnRefreshAccessedHistoryEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnRefreshAccessedHistoryEvent_VoidSync);
        case Kind_Callback_OnRenderExitedEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnRenderExitedEvent_VoidSync);
        case Kind_Callback_OnResourceLoadEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnResourceLoadEvent_VoidSync);
        case Kind_Callback_OnScaleChangeEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnScaleChangeEvent_VoidSync);
        case Kind_Callback_OnScreenCaptureRequestEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnScreenCaptureRequestEvent_VoidSync);
        case Kind_Callback_OnScrollEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnScrollEvent_VoidSync);
        case Kind_Callback_OnScrollFrameBeginHandlerResult_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnScrollFrameBeginHandlerResult_VoidSync);
        case Kind_Callback_OnSearchResultReceiveEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnSearchResultReceiveEvent_VoidSync);
        case Kind_Callback_OnShowFileSelectorEvent_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnShowFileSelectorEvent_BooleanSync);
        case Kind_Callback_OnSslErrorEventReceiveEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnSslErrorEventReceiveEvent_VoidSync);
        case Kind_Callback_OnTitleReceiveEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnTitleReceiveEvent_VoidSync);
        case Kind_Callback_OnTouchIconUrlReceivedEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnTouchIconUrlReceivedEvent_VoidSync);
        case Kind_Callback_OnWindowNewEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnWindowNewEvent_VoidSync);
        case Kind_Callback_Opt_Array_NavDestinationTransition_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Opt_Array_NavDestinationTransition_VoidSync);
        case Kind_Callback_Opt_Array_String_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Opt_Array_String_VoidSync);
        case Kind_Callback_Opt_Boolean_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Opt_Boolean_VoidSync);
        case Kind_Callback_Opt_NavigationAnimatedTransition_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Opt_NavigationAnimatedTransition_VoidSync);
        case Kind_Callback_Opt_Number_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Opt_Number_VoidSync);
        case Kind_Callback_Opt_PanelMode_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Opt_PanelMode_VoidSync);
        case Kind_Callback_Opt_ResourceStr_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Opt_ResourceStr_VoidSync);
        case Kind_Callback_Opt_StyledString_Opt_Array_String_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Opt_StyledString_Opt_Array_String_VoidSync);
        case Kind_Callback_Opt_TabContentAnimatedTransition_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Opt_TabContentAnimatedTransition_VoidSync);
        case Kind_Callback_Opt_Union_Number_Resource_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Opt_Union_Number_Resource_VoidSync);
        case Kind_Callback_PlaybackInfo_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_PlaybackInfo_VoidSync);
        case Kind_Callback_Pointer_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Pointer_VoidSync);
        case Kind_Callback_PopInfo_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_PopInfo_VoidSync);
        case Kind_Callback_PreDragStatus_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_PreDragStatus_VoidSync);
        case Kind_Callback_PreparedInfo_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_PreparedInfo_VoidSync);
        case Kind_Callback_RangeUpdate: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_RangeUpdateSync);
        case Kind_Callback_RefreshStatus_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_RefreshStatus_VoidSync);
        case Kind_Callback_ResourceStr_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_ResourceStr_VoidSync);
        case Kind_Callback_RichEditorChangeValue_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_RichEditorChangeValue_BooleanSync);
        case Kind_Callback_RichEditorDeleteValue_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_RichEditorDeleteValue_BooleanSync);
        case Kind_Callback_RichEditorInsertValue_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_RichEditorInsertValue_BooleanSync);
        case Kind_Callback_RichEditorRange_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_RichEditorRange_VoidSync);
        case Kind_Callback_RichEditorSelection_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_RichEditorSelection_VoidSync);
        case Kind_Callback_RichEditorTextSpanResult_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_RichEditorTextSpanResult_VoidSync);
        case Kind_Callback_SheetDismiss_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_SheetDismiss_VoidSync);
        case Kind_Callback_SheetType_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_SheetType_VoidSync);
        case Kind_Callback_SpringBackAction_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_SpringBackAction_VoidSync);
        case Kind_Callback_StateStylesChange: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_StateStylesChangeSync);
        case Kind_Callback_String_Number_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_String_Number_VoidSync);
        case Kind_Callback_String_Opt_Object_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_String_Opt_Object_VoidSync);
        case Kind_Callback_String_PasteEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_String_PasteEvent_VoidSync);
        case Kind_Callback_String_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_String_VoidSync);
        case Kind_Callback_StyledStringChangeValue_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_StyledStringChangeValue_BooleanSync);
        case Kind_Callback_StyledStringMarshallingValue_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_StyledStringMarshallingValue_VoidSync);
        case Kind_Callback_SwipeActionState_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_SwipeActionState_VoidSync);
        case Kind_Callback_SwiperContentTransitionProxy_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_SwiperContentTransitionProxy_VoidSync);
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
        case Kind_Callback_Type_ImageAttribute_onComplete_callback_event_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Type_ImageAttribute_onComplete_callback_event_VoidSync);
        case Kind_Callback_UIExtensionProxy_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_UIExtensionProxy_VoidSync);
        case Kind_Callback_Union_CustomBuilder_DragItemInfo_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Union_CustomBuilder_DragItemInfo_VoidSync);
        case Kind_Callback_Union_Number_Array_Number_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Union_Number_Array_Number_VoidSync);
        case Kind_Callback_Union_String_Array_String_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Union_String_Array_String_VoidSync);
        case Kind_Callback_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_VoidSync);
        case Kind_Callback_WebKeyboardOptions_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_WebKeyboardOptions_VoidSync);
        case Kind_Callback_WebResourceResponse_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_WebResourceResponse_VoidSync);
        case Kind_Callback_WithThemeAttribute_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_WithThemeAttribute_VoidSync);
        case Kind_Callback_WrappedBuilder_Args_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_WrappedBuilder_Args_VoidSync);
        case Kind_ContentDidScrollCallback: return reinterpret_cast<Ark_NativePointer>(callManagedContentDidScrollCallbackSync);
        case Kind_ContentWillScrollCallback: return reinterpret_cast<Ark_NativePointer>(callManagedContentWillScrollCallbackSync);
        case Kind_Context_getGroupDir_Callback: return reinterpret_cast<Ark_NativePointer>(callManagedContext_getGroupDir_CallbackSync);
        case Kind_CustomNodeBuilder: return reinterpret_cast<Ark_NativePointer>(callManagedCustomNodeBuilderSync);
        case Kind_DrawCallback: return reinterpret_cast<Ark_NativePointer>(callManagedDrawCallbackSync);
        case Kind_EditableTextOnChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedEditableTextOnChangeCallbackSync);
        case Kind_ErrorCallback: return reinterpret_cast<Ark_NativePointer>(callManagedErrorCallbackSync);
        case Kind_GestureRecognizerJudgeBeginCallback: return reinterpret_cast<Ark_NativePointer>(callManagedGestureRecognizerJudgeBeginCallbackSync);
        case Kind_GetItemMainSizeByIndex: return reinterpret_cast<Ark_NativePointer>(callManagedGetItemMainSizeByIndexSync);
        case Kind_GridAttribute_onItemDragStart_event_type: return reinterpret_cast<Ark_NativePointer>(callManagedGridAttribute_onItemDragStart_event_typeSync);
        case Kind_HoverCallback: return reinterpret_cast<Ark_NativePointer>(callManagedHoverCallbackSync);
        case Kind_ImageCompleteCallback: return reinterpret_cast<Ark_NativePointer>(callManagedImageCompleteCallbackSync);
        case Kind_ImageErrorCallback: return reinterpret_cast<Ark_NativePointer>(callManagedImageErrorCallbackSync);
        case Kind_InterceptionModeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedInterceptionModeCallbackSync);
        case Kind_InterceptionShowCallback: return reinterpret_cast<Ark_NativePointer>(callManagedInterceptionShowCallbackSync);
        case Kind_ListAttribute_onItemDragStart_event_type: return reinterpret_cast<Ark_NativePointer>(callManagedListAttribute_onItemDragStart_event_typeSync);
        case Kind_LocationButtonCallback: return reinterpret_cast<Ark_NativePointer>(callManagedLocationButtonCallbackSync);
        case Kind_MenuCallback: return reinterpret_cast<Ark_NativePointer>(callManagedMenuCallbackSync);
        case Kind_MenuOnAppearCallback: return reinterpret_cast<Ark_NativePointer>(callManagedMenuOnAppearCallbackSync);
        case Kind_NavDestinationTransitionDelegate: return reinterpret_cast<Ark_NativePointer>(callManagedNavDestinationTransitionDelegateSync);
        case Kind_NavExtender_OnUpdateStack: return reinterpret_cast<Ark_NativePointer>(callManagedNavExtender_OnUpdateStackSync);
        case Kind_NodeContainer_AboutToResizeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedNodeContainer_AboutToResizeCallbackSync);
        case Kind_OnAdsBlockedCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnAdsBlockedCallbackSync);
        case Kind_OnAlphabetIndexerPopupSelectCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnAlphabetIndexerPopupSelectCallbackSync);
        case Kind_OnAlphabetIndexerRequestPopupDataCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnAlphabetIndexerRequestPopupDataCallbackSync);
        case Kind_OnAlphabetIndexerSelectCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnAlphabetIndexerSelectCallbackSync);
        case Kind_OnCheckboxChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnCheckboxChangeCallbackSync);
        case Kind_OnCheckboxGroupChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnCheckboxGroupChangeCallbackSync);
        case Kind_OnContentScrollCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnContentScrollCallbackSync);
        case Kind_OnContextMenuHideCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnContextMenuHideCallbackSync);
        case Kind_OnDidChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnDidChangeCallbackSync);
        case Kind_OnDragEventCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnDragEventCallbackSync);
        case Kind_OnFirstMeaningfulPaintCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnFirstMeaningfulPaintCallbackSync);
        case Kind_OnFoldStatusChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnFoldStatusChangeCallbackSync);
        case Kind_OnFullScreenEnterCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnFullScreenEnterCallbackSync);
        case Kind_OnHoverCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnHoverCallbackSync);
        case Kind_OnHoverStatusChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnHoverStatusChangeCallbackSync);
        case Kind_OnIntelligentTrackingPreventionCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnIntelligentTrackingPreventionCallbackSync);
        case Kind_OnLargestContentfulPaintCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnLargestContentfulPaintCallbackSync);
        case Kind_OnLinearIndicatorChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnLinearIndicatorChangeCallbackSync);
        case Kind_OnMoveHandler: return reinterpret_cast<Ark_NativePointer>(callManagedOnMoveHandlerSync);
        case Kind_OnNativeEmbedVisibilityChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnNativeEmbedVisibilityChangeCallbackSync);
        case Kind_OnNativeLoadCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnNativeLoadCallbackSync);
        case Kind_OnNavigationEntryCommittedCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnNavigationEntryCommittedCallbackSync);
        case Kind_OnOverrideUrlLoadingCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnOverrideUrlLoadingCallbackSync);
        case Kind_OnPasteCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnPasteCallbackSync);
        case Kind_OnRadioChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnRadioChangeCallbackSync);
        case Kind_OnRatingChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnRatingChangeCallbackSync);
        case Kind_OnRenderProcessNotRespondingCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnRenderProcessNotRespondingCallbackSync);
        case Kind_OnRenderProcessRespondingCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnRenderProcessRespondingCallbackSync);
        case Kind_OnSafeBrowsingCheckResultCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnSafeBrowsingCheckResultCallbackSync);
        case Kind_OnScrollCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnScrollCallbackSync);
        case Kind_OnWillScrollCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnWillScrollCallbackSync);
        case Kind_OnScrollEdgeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnScrollEdgeCallbackSync);
        case Kind_OnScrollFrameBeginCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnScrollFrameBeginCallbackSync);
        case Kind_OnScrollVisibleContentChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnScrollVisibleContentChangeCallbackSync);
        case Kind_OnSelectCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnSelectCallbackSync);
        case Kind_OnSslErrorEventCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnSslErrorEventCallbackSync);
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
        case Kind_OnViewportFitChangedCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnViewportFitChangedCallbackSync);
        case Kind_PageTransitionCallback: return reinterpret_cast<Ark_NativePointer>(callManagedPageTransitionCallbackSync);
        case Kind_PasteButtonCallback: return reinterpret_cast<Ark_NativePointer>(callManagedPasteButtonCallbackSync);
        case Kind_PasteEventCallback: return reinterpret_cast<Ark_NativePointer>(callManagedPasteEventCallbackSync);
        case Kind_PluginErrorCallback: return reinterpret_cast<Ark_NativePointer>(callManagedPluginErrorCallbackSync);
        case Kind_PopupStateChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedPopupStateChangeCallbackSync);
        case Kind_ReceiveCallback: return reinterpret_cast<Ark_NativePointer>(callManagedReceiveCallbackSync);
        case Kind_RestrictedWorker_onerror_Callback: return reinterpret_cast<Ark_NativePointer>(callManagedRestrictedWorker_onerror_CallbackSync);
        case Kind_RestrictedWorker_onexit_Callback: return reinterpret_cast<Ark_NativePointer>(callManagedRestrictedWorker_onexit_CallbackSync);
        case Kind_RestrictedWorker_onmessage_Callback: return reinterpret_cast<Ark_NativePointer>(callManagedRestrictedWorker_onmessage_CallbackSync);
        case Kind_ReuseIdCallback: return reinterpret_cast<Ark_NativePointer>(callManagedReuseIdCallbackSync);
        case Kind_SaveButtonCallback: return reinterpret_cast<Ark_NativePointer>(callManagedSaveButtonCallbackSync);
        case Kind_ScrollOnScrollCallback: return reinterpret_cast<Ark_NativePointer>(callManagedScrollOnScrollCallbackSync);
        case Kind_ScrollOnWillScrollCallback: return reinterpret_cast<Ark_NativePointer>(callManagedScrollOnWillScrollCallbackSync);
        case Kind_SearchSubmitCallback: return reinterpret_cast<Ark_NativePointer>(callManagedSearchSubmitCallbackSync);
        case Kind_SearchValueCallback: return reinterpret_cast<Ark_NativePointer>(callManagedSearchValueCallbackSync);
        case Kind_SelectedCallback: return reinterpret_cast<Ark_NativePointer>(callManagedSelectedCallbackSync);
        case Kind_ShouldBuiltInRecognizerParallelWithCallback: return reinterpret_cast<Ark_NativePointer>(callManagedShouldBuiltInRecognizerParallelWithCallbackSync);
        case Kind_SizeChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedSizeChangeCallbackSync);
        case Kind_SliderTriggerChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedSliderTriggerChangeCallbackSync);
        case Kind_StepperIndexCallback: return reinterpret_cast<Ark_NativePointer>(callManagedStepperIndexCallbackSync);
        case Kind_StyledStringMarshallCallback: return reinterpret_cast<Ark_NativePointer>(callManagedStyledStringMarshallCallbackSync);
        case Kind_StyledStringUnmarshallCallback: return reinterpret_cast<Ark_NativePointer>(callManagedStyledStringUnmarshallCallbackSync);
        case Kind_SubmitCallback: return reinterpret_cast<Ark_NativePointer>(callManagedSubmitCallbackSync);
        case Kind_TabsCustomContentTransitionCallback: return reinterpret_cast<Ark_NativePointer>(callManagedTabsCustomContentTransitionCallbackSync);
        case Kind_TextAreaSubmitCallback: return reinterpret_cast<Ark_NativePointer>(callManagedTextAreaSubmitCallbackSync);
        case Kind_TextFieldValueCallback: return reinterpret_cast<Ark_NativePointer>(callManagedTextFieldValueCallbackSync);
        case Kind_TextPickerEnterSelectedAreaCallback: return reinterpret_cast<Ark_NativePointer>(callManagedTextPickerEnterSelectedAreaCallbackSync);
        case Kind_TextPickerScrollStopCallback: return reinterpret_cast<Ark_NativePointer>(callManagedTextPickerScrollStopCallbackSync);
        case Kind_TextTimerAttribute_onTimer_event_type: return reinterpret_cast<Ark_NativePointer>(callManagedTextTimerAttribute_onTimer_event_typeSync);
        case Kind_TransitionFinishCallback: return reinterpret_cast<Ark_NativePointer>(callManagedTransitionFinishCallbackSync);
        case Kind_Type_NavigationAttribute_customNavContentTransition_delegate: return reinterpret_cast<Ark_NativePointer>(callManagedType_NavigationAttribute_customNavContentTransition_delegateSync);
        case Kind_Type_TextPickerAttribute_onChange_callback: return reinterpret_cast<Ark_NativePointer>(callManagedType_TextPickerAttribute_onChange_callbackSync);
        case Kind_Type_WebAttribute_onFileSelectorShow_callback: return reinterpret_cast<Ark_NativePointer>(callManagedType_WebAttribute_onFileSelectorShow_callbackSync);
        case Kind_Type_WebAttribute_onUrlLoadIntercept_callback: return reinterpret_cast<Ark_NativePointer>(callManagedType_WebAttribute_onUrlLoadIntercept_callbackSync);
        case Kind_VisibleAreaChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedVisibleAreaChangeCallbackSync);
        case Kind_VoidCallback: return reinterpret_cast<Ark_NativePointer>(callManagedVoidCallbackSync);
        case Kind_WebKeyboardCallback: return reinterpret_cast<Ark_NativePointer>(callManagedWebKeyboardCallbackSync);
        case Kind_WithThemeInterface: return reinterpret_cast<Ark_NativePointer>(callManagedWithThemeInterfaceSync);
        case Kind_Callback_String_SurfaceRect_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_String_SurfaceRect_VoidSync);
    }
    return nullptr;
}