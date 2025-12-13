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

void callManagedAccessibilityActionInterceptCallback(Ark_Int32 resourceId, Ark_AccessibilityAction action, Callback_AccessibilityActionInterceptResult_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_AccessibilityActionInterceptCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_AccessibilityAction>(action));
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedAccessibilityActionInterceptCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_AccessibilityAction action, Callback_AccessibilityActionInterceptResult_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_AccessibilityActionInterceptCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_AccessibilityAction>(action));
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedAccessibilityCallback(Ark_Int32 resourceId, Ark_Boolean isHover, Ark_AccessibilityHoverEvent event)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_AccessibilityCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(isHover);
    AccessibilityHoverEvent_serializer::write(argsSerializer, event);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedAccessibilityCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Boolean isHover, Ark_AccessibilityHoverEvent event)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_AccessibilityCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(isHover);
    AccessibilityHoverEvent_serializer::write(argsSerializer, event);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedAccessibilityTransparentCallback(Ark_Int32 resourceId, Ark_TouchEvent event)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_AccessibilityTransparentCallback);
    argsSerializer.writeInt32(resourceId);
    TouchEvent_serializer::write(argsSerializer, event);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedAccessibilityTransparentCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_TouchEvent event)
{
    uint8_t dataBuffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&dataBuffer, sizeof(dataBuffer), nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_AccessibilityTransparentCallback);
    argsSerializer.writeInt32(resourceId);
    TouchEvent_serializer::write(argsSerializer, event);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(dataBuffer), dataBuffer);
}
void callManagedAccessibilityFocusCallback(Ark_Int32 resourceId, Ark_Boolean isFocus)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_AccessibilityFocusCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(isFocus);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedAccessibilityFocusCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Boolean isFocus)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_AccessibilityFocusCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(isFocus);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedArcScrollIndexHandler(Ark_Int32 resourceId, Ark_Int32 start, Ark_Int32 end, Ark_Int32 center)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_ArcScrollIndexHandler);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(start);
    argsSerializer.writeInt32(end);
    argsSerializer.writeInt32(center);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedArcScrollIndexHandlerSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 start, Ark_Int32 end, Ark_Int32 center)
{
    uint8_t dataBuffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&dataBuffer, sizeof(dataBuffer), nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_ArcScrollIndexHandler);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(start);
    argsSerializer.writeInt32(end);
    argsSerializer.writeInt32(center);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(dataBuffer), dataBuffer);
}
void callManagedAsyncCallback_image_PixelMap_Void(Ark_Int32 resourceId, Ark_image_PixelMap result)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_AsyncCallback_image_PixelMap_Void);
    argsSerializer.writeInt32(resourceId);
    image_PixelMap_serializer::write(argsSerializer, result);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedAsyncCallback_image_PixelMap_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_image_PixelMap result)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_AsyncCallback_image_PixelMap_Void);
    argsSerializer.writeInt32(resourceId);
    image_PixelMap_serializer::write(argsSerializer, result);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedAsyncCallback_Void(Ark_Int32 resourceId, Opt_BusinessError err, Opt_void data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_AsyncCallback_Void);
    argsSerializer.writeInt32(resourceId);
    if (runtimeType(err) != INTEROP_RUNTIME_UNDEFINED) {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto errTmpValue = err.value;
        BusinessError_serializer::write(argsSerializer, errTmpValue);
    } else {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    enqueueCallback(10, &callbackBuffer);
}
void callManagedAsyncCallback_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Opt_BusinessError err, Opt_void data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_AsyncCallback_Void);
    argsSerializer.writeInt32(resourceId);
    if (runtimeType(err) != INTEROP_RUNTIME_UNDEFINED) {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto errTmpValue = err.value;
        BusinessError_serializer::write(argsSerializer, errTmpValue);
    } else {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedButtonModifierBuilder(Ark_Int32 resourceId, Ark_NativePointer parentNode, Ark_ButtonConfiguration config, Callback_Pointer_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_ButtonModifierBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    ButtonConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedButtonModifierBuilderSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NativePointer parentNode, Ark_ButtonConfiguration config, Callback_Pointer_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_ButtonModifierBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    ButtonConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedButtonTriggerClickCallback(Ark_Int32 resourceId, Ark_Float64 xPos, Ark_Float64 yPos)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_ButtonTriggerClickCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFloat64(xPos);
    argsSerializer.writeFloat64(yPos);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedButtonTriggerClickCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Float64 xPos, Ark_Float64 yPos)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_ButtonTriggerClickCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFloat64(xPos);
    argsSerializer.writeFloat64(yPos);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_AccessibilityActionInterceptResult_Void(Ark_Int32 resourceId, Ark_AccessibilityActionInterceptResult value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_AccessibilityActionInterceptResult_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_AccessibilityActionInterceptResult>(value));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_AccessibilityActionInterceptResult_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_AccessibilityActionInterceptResult value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_AccessibilityActionInterceptResult_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_AccessibilityActionInterceptResult>(value));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_Area_Area_Void(Ark_Int32 resourceId, Ark_Area oldValue, Ark_Area newValue)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Area_Area_Void);
    argsSerializer.writeInt32(resourceId);
    Area_serializer::write(argsSerializer, oldValue);
    Area_serializer::write(argsSerializer, newValue);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_Area_Area_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Area oldValue, Ark_Area newValue)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_Area_Area_Void);
    argsSerializer.writeInt32(resourceId);
    Area_serializer::write(argsSerializer, oldValue);
    Area_serializer::write(argsSerializer, newValue);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_Array_I32_Void(Ark_Int32 resourceId, Array_Int32 input)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Array_I32_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(input.length);
    for (int inputCounterI = 0; inputCounterI < input.length; inputCounterI++) {
        const Ark_Int32 inputTmpElement = input.array[inputCounterI];
        argsSerializer.writeInt32(inputTmpElement);
    }
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_Array_I32_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Array_Int32 input)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_Array_I32_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(input.length);
    for (int inputCounterI = 0; inputCounterI < input.length; inputCounterI++) {
        const Ark_Int32 inputTmpElement = input.array[inputCounterI];
        argsSerializer.writeInt32(inputTmpElement);
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_Array_String_Void(Ark_Int32 resourceId, Array_String value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Array_String_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(value.length);
    for (int valueCounterI = 0; valueCounterI < value.length; valueCounterI++) {
        const Ark_String valueTmpElement = value.array[valueCounterI];
        argsSerializer.writeString(valueTmpElement);
    }
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_Array_String_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Array_String value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_Array_String_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(value.length);
    for (int valueCounterI = 0; valueCounterI < value.length; valueCounterI++) {
        const Ark_String valueTmpElement = value.array[valueCounterI];
        argsSerializer.writeString(valueTmpElement);
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_Array_TextMenuItem_Void(Ark_Int32 resourceId, Array_TextMenuItem value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Array_TextMenuItem_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(value.length);
    for (int valueCounterI = 0; valueCounterI < value.length; valueCounterI++) {
        const Ark_TextMenuItem valueTmpElement = value.array[valueCounterI];
        TextMenuItem_serializer::write(argsSerializer, valueTmpElement);
    }
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_Array_TextMenuItem_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Array_TextMenuItem value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_Array_TextMenuItem_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(value.length);
    for (int valueCounterI = 0; valueCounterI < value.length; valueCounterI++) {
        const Ark_TextMenuItem valueTmpElement = value.array[valueCounterI];
        TextMenuItem_serializer::write(argsSerializer, valueTmpElement);
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_Array_TouchTestInfo_TouchResult(Ark_Int32 resourceId, Array_TouchTestInfo value, Callback_TouchResult_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Array_TouchTestInfo_TouchResult);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(value.length);
    for (int valueCounterI = 0; valueCounterI < value.length; valueCounterI++) {
        const Ark_TouchTestInfo valueTmpElement = value.array[valueCounterI];
        TouchTestInfo_serializer::write(argsSerializer, valueTmpElement);
    }
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_Array_TouchTestInfo_TouchResultSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Array_TouchTestInfo value, Callback_TouchResult_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_Array_TouchTestInfo_TouchResult);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(value.length);
    for (int valueCounterI = 0; valueCounterI < value.length; valueCounterI++) {
        const Ark_TouchTestInfo valueTmpElement = value.array[valueCounterI];
        TouchTestInfo_serializer::write(argsSerializer, valueTmpElement);
    }
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_AxisEvent_Void(Ark_Int32 resourceId, Ark_AxisEvent value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_AxisEvent_Void);
    argsSerializer.writeInt32(resourceId);
    AxisEvent_serializer::write(argsSerializer, value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_AxisEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_AxisEvent value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_AxisEvent_Void);
    argsSerializer.writeInt32(resourceId);
    AxisEvent_serializer::write(argsSerializer, value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_Boolean(Ark_Int32 resourceId, Callback_Boolean_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Boolean);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Callback_Boolean_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_Boolean);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_Boolean_HoverEvent_Void(Ark_Int32 resourceId, Ark_Boolean isHover, Ark_HoverEvent event)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Boolean_HoverEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(isHover);
    HoverEvent_serializer::write(argsSerializer, event);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_Boolean_HoverEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Boolean isHover, Ark_HoverEvent event)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_Boolean_HoverEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(isHover);
    HoverEvent_serializer::write(argsSerializer, event);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_Boolean_Void(Ark_Int32 resourceId, Ark_Boolean value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Boolean_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_Boolean_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Boolean value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_Boolean_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_Buffer_Void(Ark_Int32 resourceId, Ark_Buffer value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Buffer_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBuffer(value);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_Buffer_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Buffer value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_Buffer_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBuffer(value);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_ClickEvent_Void(Ark_Int32 resourceId, Ark_ClickEvent event)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_ClickEvent_Void);
    argsSerializer.writeInt32(resourceId);
    ClickEvent_serializer::write(argsSerializer, event);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_ClickEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_ClickEvent event)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_ClickEvent_Void);
    argsSerializer.writeInt32(resourceId);
    ClickEvent_serializer::write(argsSerializer, event);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_ComputedBarAttribute_Void(Ark_Int32 resourceId, Ark_ComputedBarAttribute value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_ComputedBarAttribute_Void);
    argsSerializer.writeInt32(resourceId);
    ComputedBarAttribute_serializer::write(argsSerializer, value);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_ComputedBarAttribute_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_ComputedBarAttribute value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_ComputedBarAttribute_Void);
    argsSerializer.writeInt32(resourceId);
    ComputedBarAttribute_serializer::write(argsSerializer, value);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_CopyEvent_Void(Ark_Int32 resourceId, Ark_CopyEvent value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_CopyEvent_Void);
    argsSerializer.writeInt32(resourceId);
    CopyEvent_serializer::write(argsSerializer, value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_CopyEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_CopyEvent value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_CopyEvent_Void);
    argsSerializer.writeInt32(resourceId);
    CopyEvent_serializer::write(argsSerializer, value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_CreateItem(Ark_Int32 resourceId, Ark_Int32 index, Callback_Pointer_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_CreateItem);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_CreateItemSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 index, Callback_Pointer_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_CreateItem);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_CrownEvent_Void(Ark_Int32 resourceId, Ark_CrownEvent value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_CrownEvent_Void);
    argsSerializer.writeInt32(resourceId);
    CrownEvent_serializer::write(argsSerializer, value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_CrownEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_CrownEvent value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_CrownEvent_Void);
    argsSerializer.writeInt32(resourceId);
    CrownEvent_serializer::write(argsSerializer, value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_CustomSpanMeasureInfo_CustomSpanMetrics(Ark_Int32 resourceId, Ark_CustomSpanMeasureInfo measureInfo, Callback_CustomSpanMetrics_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_CustomSpanMeasureInfo_CustomSpanMetrics);
    argsSerializer.writeInt32(resourceId);
    CustomSpanMeasureInfo_serializer::write(argsSerializer, measureInfo);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_CustomSpanMeasureInfo_CustomSpanMetricsSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_CustomSpanMeasureInfo measureInfo, Callback_CustomSpanMetrics_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_CustomSpanMeasureInfo_CustomSpanMetrics);
    argsSerializer.writeInt32(resourceId);
    CustomSpanMeasureInfo_serializer::write(argsSerializer, measureInfo);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_CustomSpanMetrics_Void(Ark_Int32 resourceId, Ark_CustomSpanMetrics value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_CustomSpanMetrics_Void);
    argsSerializer.writeInt32(resourceId);
    CustomSpanMetrics_serializer::write(argsSerializer, value);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_CustomSpanMetrics_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_CustomSpanMetrics value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_CustomSpanMetrics_Void);
    argsSerializer.writeInt32(resourceId);
    CustomSpanMetrics_serializer::write(argsSerializer, value);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_CutEvent_Void(Ark_Int32 resourceId, Ark_CutEvent value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_CutEvent_Void);
    argsSerializer.writeInt32(resourceId);
    CutEvent_serializer::write(argsSerializer, value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_CutEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_CutEvent value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_CutEvent_Void);
    argsSerializer.writeInt32(resourceId);
    CutEvent_serializer::write(argsSerializer, value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_Date_Void(Ark_Int32 resourceId, Ark_Date value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Date_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt64(value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_Date_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Date value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_Date_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt64(value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_DeleteValue_Boolean(Ark_Int32 resourceId, Ark_DeleteValue value0, Callback_Boolean_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_DeleteValue_Boolean);
    argsSerializer.writeInt32(resourceId);
    DeleteValue_serializer::write(argsSerializer, value0);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_DeleteValue_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_DeleteValue value0, Callback_Boolean_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_DeleteValue_Boolean);
    argsSerializer.writeInt32(resourceId);
    DeleteValue_serializer::write(argsSerializer, value0);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_DeleteValue_Void(Ark_Int32 resourceId, Ark_DeleteValue value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_DeleteValue_Void);
    argsSerializer.writeInt32(resourceId);
    DeleteValue_serializer::write(argsSerializer, value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_DeleteValue_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_DeleteValue value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_DeleteValue_Void);
    argsSerializer.writeInt32(resourceId);
    DeleteValue_serializer::write(argsSerializer, value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_DismissContentCoverAction_Void(Ark_Int32 resourceId, Ark_DismissContentCoverAction value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_DismissContentCoverAction_Void);
    argsSerializer.writeInt32(resourceId);
    DismissContentCoverAction_serializer::write(argsSerializer, value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_DismissContentCoverAction_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_DismissContentCoverAction value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_DismissContentCoverAction_Void);
    argsSerializer.writeInt32(resourceId);
    DismissContentCoverAction_serializer::write(argsSerializer, value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_DismissDialogAction_Void(Ark_Int32 resourceId, Ark_DismissDialogAction value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_DismissDialogAction_Void);
    argsSerializer.writeInt32(resourceId);
    DismissDialogAction_serializer::write(argsSerializer, value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_DismissDialogAction_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_DismissDialogAction value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_DismissDialogAction_Void);
    argsSerializer.writeInt32(resourceId);
    DismissDialogAction_serializer::write(argsSerializer, value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_DismissPopupAction_Void(Ark_Int32 resourceId, Ark_DismissPopupAction value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_DismissPopupAction_Void);
    argsSerializer.writeInt32(resourceId);
    DismissPopupAction_serializer::write(argsSerializer, value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_DismissPopupAction_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_DismissPopupAction value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_DismissPopupAction_Void);
    argsSerializer.writeInt32(resourceId);
    DismissPopupAction_serializer::write(argsSerializer, value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_DismissSheetAction_Void(Ark_Int32 resourceId, Ark_DismissSheetAction value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_DismissSheetAction_Void);
    argsSerializer.writeInt32(resourceId);
    DismissSheetAction_serializer::write(argsSerializer, value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_DismissSheetAction_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_DismissSheetAction value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_DismissSheetAction_Void);
    argsSerializer.writeInt32(resourceId);
    DismissSheetAction_serializer::write(argsSerializer, value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_DragEvent_Opt_String_Void(Ark_Int32 resourceId, Ark_DragEvent event, Opt_String extraParams)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_DragEvent_Opt_String_Void);
    argsSerializer.writeInt32(resourceId);
    DragEvent_serializer::write(argsSerializer, event);
    if (runtimeType(extraParams) != INTEROP_RUNTIME_UNDEFINED) {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto extraParamsTmpValue = extraParams.value;
        argsSerializer.writeString(extraParamsTmpValue);
    } else {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_DragEvent_Opt_String_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_DragEvent event, Opt_String extraParams)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_DragEvent_Opt_String_Void);
    argsSerializer.writeInt32(resourceId);
    DragEvent_serializer::write(argsSerializer, event);
    if (runtimeType(extraParams) != INTEROP_RUNTIME_UNDEFINED) {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto extraParamsTmpValue = extraParams.value;
        argsSerializer.writeString(extraParamsTmpValue);
    } else {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_DrawContext_CustomSpanDrawInfo_Void(Ark_Int32 resourceId, Ark_DrawContext context, Ark_CustomSpanDrawInfo drawInfo)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_DrawContext_CustomSpanDrawInfo_Void);
    argsSerializer.writeInt32(resourceId);
    DrawContext_serializer::write(argsSerializer, context);
    CustomSpanDrawInfo_serializer::write(argsSerializer, drawInfo);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_DrawContext_CustomSpanDrawInfo_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_DrawContext context, Ark_CustomSpanDrawInfo drawInfo)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_DrawContext_CustomSpanDrawInfo_Void);
    argsSerializer.writeInt32(resourceId);
    DrawContext_serializer::write(argsSerializer, context);
    CustomSpanDrawInfo_serializer::write(argsSerializer, drawInfo);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_DrawContext_Void(Ark_Int32 resourceId, Ark_DrawContext drawContext)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_DrawContext_Void);
    argsSerializer.writeInt32(resourceId);
    DrawContext_serializer::write(argsSerializer, drawContext);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_DrawContext_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_DrawContext drawContext)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_DrawContext_Void);
    argsSerializer.writeInt32(resourceId);
    DrawContext_serializer::write(argsSerializer, drawContext);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_EditableTextChangeValue_Boolean(Ark_Int32 resourceId, Ark_EditableTextChangeValue value0, Callback_Boolean_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_EditableTextChangeValue_Boolean);
    argsSerializer.writeInt32(resourceId);
    EditableTextChangeValue_serializer::write(argsSerializer, value0);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_EditableTextChangeValue_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_EditableTextChangeValue value0, Callback_Boolean_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_EditableTextChangeValue_Boolean);
    argsSerializer.writeInt32(resourceId);
    EditableTextChangeValue_serializer::write(argsSerializer, value0);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_ErrorInformation_Void(Ark_Int32 resourceId, Ark_ErrorInformation value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_ErrorInformation_Void);
    argsSerializer.writeInt32(resourceId);
    ErrorInformation_serializer::write(argsSerializer, value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_ErrorInformation_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_ErrorInformation value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_ErrorInformation_Void);
    argsSerializer.writeInt32(resourceId);
    ErrorInformation_serializer::write(argsSerializer, value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_Extender_OnFinish(Ark_Int32 resourceId)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Extender_OnFinish);
    argsSerializer.writeInt32(resourceId);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_Extender_OnFinishSync(Ark_VMContext vmContext, Ark_Int32 resourceId)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_Extender_OnFinish);
    argsSerializer.writeInt32(resourceId);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_Extender_OnProgress(Ark_Int32 resourceId, Ark_Float32 value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Extender_OnProgress);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFloat32(value);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_Extender_OnProgressSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Float32 value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_Extender_OnProgress);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFloat32(value);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_F64_F64_Void(Ark_Int32 resourceId, Ark_Float64 totalOffsetX, Ark_Float64 totalOffsetY)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_F64_F64_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFloat64(totalOffsetX);
    argsSerializer.writeFloat64(totalOffsetY);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_F64_F64_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Float64 totalOffsetX, Ark_Float64 totalOffsetY)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_F64_F64_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFloat64(totalOffsetX);
    argsSerializer.writeFloat64(totalOffsetY);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_F64_Void(Ark_Int32 resourceId, Ark_Float64 offset)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_F64_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFloat64(offset);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_F64_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Float64 offset)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_F64_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFloat64(offset);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_F64_SliderChangeMode_Void(Ark_Int32 resourceId, Ark_Float64 value, Ark_SliderChangeMode mode)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_F64_SliderChangeMode_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFloat64(value);
    argsSerializer.writeInt32(static_cast<Ark_SliderChangeMode>(mode));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_F64_SliderChangeMode_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Float64 value, Ark_SliderChangeMode mode)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_F64_SliderChangeMode_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFloat64(value);
    argsSerializer.writeInt32(static_cast<Ark_SliderChangeMode>(mode));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_FocusAxisEvent_Void(Ark_Int32 resourceId, Ark_FocusAxisEvent value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_FocusAxisEvent_Void);
    argsSerializer.writeInt32(resourceId);
    FocusAxisEvent_serializer::write(argsSerializer, value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_FocusAxisEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_FocusAxisEvent value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_FocusAxisEvent_Void);
    argsSerializer.writeInt32(resourceId);
    FocusAxisEvent_serializer::write(argsSerializer, value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_FormCallbackInfo_Void(Ark_Int32 resourceId, Ark_FormCallbackInfo value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_FormCallbackInfo_Void);
    argsSerializer.writeInt32(resourceId);
    FormCallbackInfo_serializer::write(argsSerializer, value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_FormCallbackInfo_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_FormCallbackInfo value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_FormCallbackInfo_Void);
    argsSerializer.writeInt32(resourceId);
    FormCallbackInfo_serializer::write(argsSerializer, value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_FullscreenInfo_Void(Ark_Int32 resourceId, Ark_FullscreenInfo value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_FullscreenInfo_Void);
    argsSerializer.writeInt32(resourceId);
    FullscreenInfo_serializer::write(argsSerializer, value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_FullscreenInfo_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_FullscreenInfo value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_FullscreenInfo_Void);
    argsSerializer.writeInt32(resourceId);
    FullscreenInfo_serializer::write(argsSerializer, value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_GestureEvent_Void(Ark_Int32 resourceId, Ark_GestureEvent value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_GestureEvent_Void);
    argsSerializer.writeInt32(resourceId);
    GestureEvent_serializer::write(argsSerializer, value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_GestureEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_GestureEvent value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_GestureEvent_Void);
    argsSerializer.writeInt32(resourceId);
    GestureEvent_serializer::write(argsSerializer, value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_GestureInfo_BaseGestureEvent_GestureJudgeResult(Ark_Int32 resourceId, Ark_GestureInfo gestureInfo, Ark_BaseGestureEvent event, Callback_GestureJudgeResult_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult);
    argsSerializer.writeInt32(resourceId);
    GestureInfo_serializer::write(argsSerializer, gestureInfo);
    BaseGestureEvent_serializer::write(argsSerializer, event);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_GestureInfo_BaseGestureEvent_GestureJudgeResultSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_GestureInfo gestureInfo, Ark_BaseGestureEvent event, Callback_GestureJudgeResult_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult);
    argsSerializer.writeInt32(resourceId);
    GestureInfo_serializer::write(argsSerializer, gestureInfo);
    BaseGestureEvent_serializer::write(argsSerializer, event);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_GestureJudgeResult_Void(Ark_Int32 resourceId, Ark_GestureJudgeResult value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_GestureJudgeResult_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_GestureJudgeResult>(value));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_GestureJudgeResult_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_GestureJudgeResult value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_GestureJudgeResult_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_GestureJudgeResult>(value));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_GestureRecognizer_Void(Ark_Int32 resourceId, Ark_GestureRecognizer value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_GestureRecognizer_Void);
    argsSerializer.writeInt32(resourceId);
    GestureRecognizer_serializer::write(argsSerializer, value);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_GestureRecognizer_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_GestureRecognizer value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_GestureRecognizer_Void);
    argsSerializer.writeInt32(resourceId);
    GestureRecognizer_serializer::write(argsSerializer, value);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_HitTestMode_Void(Ark_Int32 resourceId, Ark_HitTestMode value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_HitTestMode_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_HitTestMode>(value));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_HitTestMode_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_HitTestMode value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_HitTestMode_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_HitTestMode>(value));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_HoverEvent_Void(Ark_Int32 resourceId, Ark_HoverEvent value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_HoverEvent_Void);
    argsSerializer.writeInt32(resourceId);
    HoverEvent_serializer::write(argsSerializer, value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_HoverEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_HoverEvent value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_HoverEvent_Void);
    argsSerializer.writeInt32(resourceId);
    HoverEvent_serializer::write(argsSerializer, value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_I32_F64_ComputedBarAttribute(Ark_Int32 resourceId, Ark_Int32 index, Ark_Float64 offset, Callback_ComputedBarAttribute_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_I32_F64_ComputedBarAttribute);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    argsSerializer.writeFloat64(offset);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_I32_F64_ComputedBarAttributeSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 index, Ark_Float64 offset, Callback_ComputedBarAttribute_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_I32_F64_ComputedBarAttribute);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    argsSerializer.writeFloat64(offset);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_I32_I32_Boolean(Ark_Int32 resourceId, Ark_Int32 from, Ark_Int32 to, Callback_Boolean_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_I32_I32_Boolean);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(from);
    argsSerializer.writeInt32(to);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_I32_I32_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 from, Ark_Int32 to, Callback_Boolean_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_I32_I32_Boolean);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(from);
    argsSerializer.writeInt32(to);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_I32_I32_I32_Void(Ark_Int32 resourceId, Ark_Int32 start, Ark_Int32 end, Ark_Int32 center)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_I32_I32_I32_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(start);
    argsSerializer.writeInt32(end);
    argsSerializer.writeInt32(center);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_I32_I32_I32_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 start, Ark_Int32 end, Ark_Int32 center)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_I32_I32_I32_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(start);
    argsSerializer.writeInt32(end);
    argsSerializer.writeInt32(center);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_I32_I32_Void(Ark_Int32 resourceId, Ark_Int32 first, Ark_Int32 last)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_I32_I32_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(first);
    argsSerializer.writeInt32(last);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_I32_I32_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 first, Ark_Int32 last)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_I32_I32_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(first);
    argsSerializer.writeInt32(last);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_I32_Tuple_I32_I32(Ark_Int32 resourceId, Ark_Int32 index, Callback_Tuple_I32_I32_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_I32_Tuple_I32_I32);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_I32_Tuple_I32_I32Sync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 index, Callback_Tuple_I32_I32_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_I32_Tuple_I32_I32);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_I32_Tuple_I32_I32_I32_I32(Ark_Int32 resourceId, Ark_Int32 index, Callback_Tuple_I32_I32_I32_I32_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_I32_Tuple_I32_I32_I32_I32);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_I32_Tuple_I32_I32_I32_I32Sync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 index, Callback_Tuple_I32_I32_I32_I32_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_I32_Tuple_I32_I32_I32_I32);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_I64_Void(Ark_Int32 resourceId, Ark_Int64 value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_I64_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt64(value);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_I64_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int64 value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_I64_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt64(value);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_I32_Void(Ark_Int32 resourceId, Ark_Int32 value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_I32_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_I32_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_I32_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_InsertValue_Boolean(Ark_Int32 resourceId, Ark_InsertValue value0, Callback_Boolean_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_InsertValue_Boolean);
    argsSerializer.writeInt32(resourceId);
    InsertValue_serializer::write(argsSerializer, value0);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_InsertValue_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_InsertValue value0, Callback_Boolean_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_InsertValue_Boolean);
    argsSerializer.writeInt32(resourceId);
    InsertValue_serializer::write(argsSerializer, value0);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_InsertValue_Void(Ark_Int32 resourceId, Ark_InsertValue value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_InsertValue_Void);
    argsSerializer.writeInt32(resourceId);
    InsertValue_serializer::write(argsSerializer, value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_InsertValue_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_InsertValue value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_InsertValue_Void);
    argsSerializer.writeInt32(resourceId);
    InsertValue_serializer::write(argsSerializer, value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_ItemDragInfo_I32_I32_Boolean_Void(Ark_Int32 resourceId, Ark_ItemDragInfo event, Ark_Int32 itemIndex, Ark_Int32 insertIndex, Ark_Boolean isSuccess)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_ItemDragInfo_I32_I32_Boolean_Void);
    argsSerializer.writeInt32(resourceId);
    ItemDragInfo_serializer::write(argsSerializer, event);
    argsSerializer.writeInt32(itemIndex);
    argsSerializer.writeInt32(insertIndex);
    argsSerializer.writeBoolean(isSuccess);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_ItemDragInfo_I32_I32_Boolean_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_ItemDragInfo event, Ark_Int32 itemIndex, Ark_Int32 insertIndex, Ark_Boolean isSuccess)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_ItemDragInfo_I32_I32_Boolean_Void);
    argsSerializer.writeInt32(resourceId);
    ItemDragInfo_serializer::write(argsSerializer, event);
    argsSerializer.writeInt32(itemIndex);
    argsSerializer.writeInt32(insertIndex);
    argsSerializer.writeBoolean(isSuccess);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_ItemDragInfo_I32_I32_Void(Ark_Int32 resourceId, Ark_ItemDragInfo event, Ark_Int32 itemIndex, Ark_Int32 insertIndex)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_ItemDragInfo_I32_I32_Void);
    argsSerializer.writeInt32(resourceId);
    ItemDragInfo_serializer::write(argsSerializer, event);
    argsSerializer.writeInt32(itemIndex);
    argsSerializer.writeInt32(insertIndex);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_ItemDragInfo_I32_I32_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_ItemDragInfo event, Ark_Int32 itemIndex, Ark_Int32 insertIndex)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_ItemDragInfo_I32_I32_Void);
    argsSerializer.writeInt32(resourceId);
    ItemDragInfo_serializer::write(argsSerializer, event);
    argsSerializer.writeInt32(itemIndex);
    argsSerializer.writeInt32(insertIndex);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_ItemDragInfo_I32_Void(Ark_Int32 resourceId, Ark_ItemDragInfo event, Ark_Int32 itemIndex)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_ItemDragInfo_I32_Void);
    argsSerializer.writeInt32(resourceId);
    ItemDragInfo_serializer::write(argsSerializer, event);
    argsSerializer.writeInt32(itemIndex);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_ItemDragInfo_I32_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_ItemDragInfo event, Ark_Int32 itemIndex)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_ItemDragInfo_I32_Void);
    argsSerializer.writeInt32(resourceId);
    ItemDragInfo_serializer::write(argsSerializer, event);
    argsSerializer.writeInt32(itemIndex);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_ItemDragInfo_Void(Ark_Int32 resourceId, Ark_ItemDragInfo event)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_ItemDragInfo_Void);
    argsSerializer.writeInt32(resourceId);
    ItemDragInfo_serializer::write(argsSerializer, event);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_ItemDragInfo_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_ItemDragInfo event)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_ItemDragInfo_Void);
    argsSerializer.writeInt32(resourceId);
    ItemDragInfo_serializer::write(argsSerializer, event);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_KeyEvent_Boolean(Ark_Int32 resourceId, Ark_KeyEvent value0, Callback_Boolean_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_KeyEvent_Boolean);
    argsSerializer.writeInt32(resourceId);
    KeyEvent_serializer::write(argsSerializer, value0);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_KeyEvent_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_KeyEvent value0, Callback_Boolean_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_KeyEvent_Boolean);
    argsSerializer.writeInt32(resourceId);
    KeyEvent_serializer::write(argsSerializer, value0);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_KeyEvent_Void(Ark_Int32 resourceId, Ark_KeyEvent event)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_KeyEvent_Void);
    argsSerializer.writeInt32(resourceId);
    KeyEvent_serializer::write(argsSerializer, event);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_KeyEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_KeyEvent event)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_KeyEvent_Void);
    argsSerializer.writeInt32(resourceId);
    KeyEvent_serializer::write(argsSerializer, event);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_Long_Void(Ark_Int32 resourceId, Ark_Int64 value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Long_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt64(value);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_Long_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int64 value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_Long_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt64(value);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_Map_String_RecordData_Void(Ark_Int32 resourceId, Map_String_Opt_Object value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Map_String_RecordData_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(value0.size);
    for (int32_t i = 0; i < value0.size; i++) {
        auto value0KeyVar = value0.keys[i];
        auto value0ValueVar = value0.values[i];
        argsSerializer.writeString(value0KeyVar);
        if (runtimeType(value0ValueVar) != INTEROP_RUNTIME_UNDEFINED) {
            argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
            const auto value0ValueVarTmpValue = value0ValueVar.value;
            argsSerializer.writeObject(value0ValueVarTmpValue);
        } else {
            argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
        }
    }
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_Map_String_RecordData_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Map_String_Opt_Object value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_Map_String_RecordData_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(value0.size);
    for (int32_t i = 0; i < value0.size; i++) {
        auto value0KeyVar = value0.keys[i];
        auto value0ValueVar = value0.values[i];
        argsSerializer.writeString(value0KeyVar);
        if (runtimeType(value0ValueVar) != INTEROP_RUNTIME_UNDEFINED) {
            argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
            const auto value0ValueVarTmpValue = value0ValueVar.value;
            argsSerializer.writeObject(value0ValueVarTmpValue);
        } else {
            argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
        }
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_MarqueeState_Void(Ark_Int32 resourceId, Ark_MarqueeState value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_MarqueeState_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_MarqueeState>(value0));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_MarqueeState_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_MarqueeState value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_MarqueeState_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_MarqueeState>(value0));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_MouseEvent_Void(Ark_Int32 resourceId, Ark_MouseEvent event)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_MouseEvent_Void);
    argsSerializer.writeInt32(resourceId);
    MouseEvent_serializer::write(argsSerializer, event);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_MouseEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_MouseEvent event)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_MouseEvent_Void);
    argsSerializer.writeInt32(resourceId);
    MouseEvent_serializer::write(argsSerializer, event);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_NativeEmbedDataInfo_Void(Ark_Int32 resourceId, Ark_NativeEmbedDataInfo event)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_NativeEmbedDataInfo_Void);
    argsSerializer.writeInt32(resourceId);
    NativeEmbedDataInfo_serializer::write(argsSerializer, event);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_NativeEmbedDataInfo_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NativeEmbedDataInfo event)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_NativeEmbedDataInfo_Void);
    argsSerializer.writeInt32(resourceId);
    NativeEmbedDataInfo_serializer::write(argsSerializer, event);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_NativeEmbedTouchInfo_Void(Ark_Int32 resourceId, Ark_NativeEmbedTouchInfo event)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_NativeEmbedTouchInfo_Void);
    argsSerializer.writeInt32(resourceId);
    NativeEmbedTouchInfo_serializer::write(argsSerializer, event);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_NativeEmbedTouchInfo_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NativeEmbedTouchInfo event)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_NativeEmbedTouchInfo_Void);
    argsSerializer.writeInt32(resourceId);
    NativeEmbedTouchInfo_serializer::write(argsSerializer, event);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_NativeXComponentPointer_Void(Ark_Int32 resourceId, Ark_Int64 value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_NativeXComponentPointer_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt64(value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_NativeXComponentPointer_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int64 value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_NativeXComponentPointer_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt64(value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_NavDestinationActiveReason_Void(Ark_Int32 resourceId, Ark_NavDestinationActiveReason value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_NavDestinationActiveReason_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_NavDestinationActiveReason>(value0));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_NavDestinationActiveReason_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NavDestinationActiveReason value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_NavDestinationActiveReason_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_NavDestinationActiveReason>(value0));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_NavDestinationContext_Void(Ark_Int32 resourceId, Ark_NavDestinationContext value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_NavDestinationContext_Void);
    argsSerializer.writeInt32(resourceId);
    NavDestinationContext_serializer::write(argsSerializer, value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_NavDestinationContext_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NavDestinationContext value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_NavDestinationContext_Void);
    argsSerializer.writeInt32(resourceId);
    NavDestinationContext_serializer::write(argsSerializer, value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_NavigationMode_Void(Ark_Int32 resourceId, Ark_NavigationMode mode)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_NavigationMode_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_NavigationMode>(mode));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_NavigationMode_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NavigationMode mode)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_NavigationMode_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_NavigationMode>(mode));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_NavigationTitleMode_Void(Ark_Int32 resourceId, Ark_NavigationTitleMode titleMode)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_NavigationTitleMode_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_NavigationTitleMode>(titleMode));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_NavigationTitleMode_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NavigationTitleMode titleMode)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_NavigationTitleMode_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_NavigationTitleMode>(titleMode));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_NavigationTransitionProxy_Void(Ark_Int32 resourceId, Ark_NavigationTransitionProxy transitionProxy)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_NavigationTransitionProxy_Void);
    argsSerializer.writeInt32(resourceId);
    NavigationTransitionProxy_serializer::write(argsSerializer, transitionProxy);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_NavigationTransitionProxy_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NavigationTransitionProxy transitionProxy)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_NavigationTransitionProxy_Void);
    argsSerializer.writeInt32(resourceId);
    NavigationTransitionProxy_serializer::write(argsSerializer, transitionProxy);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_Number_Number_Void(Ark_Int32 resourceId, Ark_Number prevIndex, Ark_Number index)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Number_Number_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(prevIndex);
    argsSerializer.writeNumber(index);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_Number_Number_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number prevIndex, Ark_Number index)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_Number_Number_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(prevIndex);
    argsSerializer.writeNumber(index);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}

void callManagedCallback_Number_Void(Ark_Int32 resourceId, Ark_Number value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Number_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(value);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_Number_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_Number_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(value);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_Object_Void(Ark_Int32 resourceId, Ark_Object value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Object_Void);
    argsSerializer.writeInt32(resourceId);
    const Ark_CallbackResource arg0Resource = {value0.resource.resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&arg0Resource);
    argsSerializer.writeObject(value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_Object_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Object value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_Object_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeObject(value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_OnAlertEvent_Boolean(Ark_Int32 resourceId, Ark_OnAlertEvent value0, Callback_Boolean_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnAlertEvent_Boolean);
    argsSerializer.writeInt32(resourceId);
    OnAlertEvent_serializer::write(argsSerializer, value0);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_OnAlertEvent_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnAlertEvent value0, Callback_Boolean_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_OnAlertEvent_Boolean);
    argsSerializer.writeInt32(resourceId);
    OnAlertEvent_serializer::write(argsSerializer, value0);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_OnAudioStateChangedEvent_Void(Ark_Int32 resourceId, Ark_OnAudioStateChangedEvent value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnAudioStateChangedEvent_Void);
    argsSerializer.writeInt32(resourceId);
    OnAudioStateChangedEvent_serializer::write(argsSerializer, value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_OnAudioStateChangedEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnAudioStateChangedEvent value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_OnAudioStateChangedEvent_Void);
    argsSerializer.writeInt32(resourceId);
    OnAudioStateChangedEvent_serializer::write(argsSerializer, value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_OnBeforeUnloadEvent_Boolean(Ark_Int32 resourceId, Ark_OnBeforeUnloadEvent value0, Callback_Boolean_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnBeforeUnloadEvent_Boolean);
    argsSerializer.writeInt32(resourceId);
    OnBeforeUnloadEvent_serializer::write(argsSerializer, value0);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_OnBeforeUnloadEvent_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnBeforeUnloadEvent value0, Callback_Boolean_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_OnBeforeUnloadEvent_Boolean);
    argsSerializer.writeInt32(resourceId);
    OnBeforeUnloadEvent_serializer::write(argsSerializer, value0);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_OnClientAuthenticationEvent_Void(Ark_Int32 resourceId, Ark_OnClientAuthenticationEvent value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnClientAuthenticationEvent_Void);
    argsSerializer.writeInt32(resourceId);
    OnClientAuthenticationEvent_serializer::write(argsSerializer, value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_OnClientAuthenticationEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnClientAuthenticationEvent value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_OnClientAuthenticationEvent_Void);
    argsSerializer.writeInt32(resourceId);
    OnClientAuthenticationEvent_serializer::write(argsSerializer, value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_OnConfirmEvent_Boolean(Ark_Int32 resourceId, Ark_OnConfirmEvent value0, Callback_Boolean_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnConfirmEvent_Boolean);
    argsSerializer.writeInt32(resourceId);
    OnConfirmEvent_serializer::write(argsSerializer, value0);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_OnConfirmEvent_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnConfirmEvent value0, Callback_Boolean_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_OnConfirmEvent_Boolean);
    argsSerializer.writeInt32(resourceId);
    OnConfirmEvent_serializer::write(argsSerializer, value0);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_OnConsoleEvent_Boolean(Ark_Int32 resourceId, Ark_OnConsoleEvent value0, Callback_Boolean_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnConsoleEvent_Boolean);
    argsSerializer.writeInt32(resourceId);
    OnConsoleEvent_serializer::write(argsSerializer, value0);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_OnConsoleEvent_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnConsoleEvent value0, Callback_Boolean_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_OnConsoleEvent_Boolean);
    argsSerializer.writeInt32(resourceId);
    OnConsoleEvent_serializer::write(argsSerializer, value0);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_OnContextMenuShowEvent_Boolean(Ark_Int32 resourceId, Ark_OnContextMenuShowEvent value0, Callback_Boolean_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnContextMenuShowEvent_Boolean);
    argsSerializer.writeInt32(resourceId);
    OnContextMenuShowEvent_serializer::write(argsSerializer, value0);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_OnContextMenuShowEvent_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnContextMenuShowEvent value0, Callback_Boolean_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_OnContextMenuShowEvent_Boolean);
    argsSerializer.writeInt32(resourceId);
    OnContextMenuShowEvent_serializer::write(argsSerializer, value0);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_OnDataResubmittedEvent_Void(Ark_Int32 resourceId, Ark_OnDataResubmittedEvent value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnDataResubmittedEvent_Void);
    argsSerializer.writeInt32(resourceId);
    OnDataResubmittedEvent_serializer::write(argsSerializer, value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_OnDataResubmittedEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnDataResubmittedEvent value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_OnDataResubmittedEvent_Void);
    argsSerializer.writeInt32(resourceId);
    OnDataResubmittedEvent_serializer::write(argsSerializer, value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_OnDestory_Void(Ark_Int32 resourceId, Ark_Int64 nodeId)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnDestory_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt64(nodeId);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_OnDestory_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int64 nodeId)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_OnDestory_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt64(nodeId);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_OnDownloadStartEvent_Void(Ark_Int32 resourceId, Ark_OnDownloadStartEvent value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnDownloadStartEvent_Void);
    argsSerializer.writeInt32(resourceId);
    OnDownloadStartEvent_serializer::write(argsSerializer, value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_OnDownloadStartEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnDownloadStartEvent value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_OnDownloadStartEvent_Void);
    argsSerializer.writeInt32(resourceId);
    OnDownloadStartEvent_serializer::write(argsSerializer, value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_OnErrorReceiveEvent_Void(Ark_Int32 resourceId, Ark_OnErrorReceiveEvent value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnErrorReceiveEvent_Void);
    argsSerializer.writeInt32(resourceId);
    OnErrorReceiveEvent_serializer::write(argsSerializer, value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_OnErrorReceiveEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnErrorReceiveEvent value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_OnErrorReceiveEvent_Void);
    argsSerializer.writeInt32(resourceId);
    OnErrorReceiveEvent_serializer::write(argsSerializer, value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_OnFaviconReceivedEvent_Void(Ark_Int32 resourceId, Ark_OnFaviconReceivedEvent value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnFaviconReceivedEvent_Void);
    argsSerializer.writeInt32(resourceId);
    OnFaviconReceivedEvent_serializer::write(argsSerializer, value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_OnFaviconReceivedEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnFaviconReceivedEvent value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_OnFaviconReceivedEvent_Void);
    argsSerializer.writeInt32(resourceId);
    OnFaviconReceivedEvent_serializer::write(argsSerializer, value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_OnFirstContentfulPaintEvent_Void(Ark_Int32 resourceId, Ark_OnFirstContentfulPaintEvent value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnFirstContentfulPaintEvent_Void);
    argsSerializer.writeInt32(resourceId);
    OnFirstContentfulPaintEvent_serializer::write(argsSerializer, value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_OnFirstContentfulPaintEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnFirstContentfulPaintEvent value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_OnFirstContentfulPaintEvent_Void);
    argsSerializer.writeInt32(resourceId);
    OnFirstContentfulPaintEvent_serializer::write(argsSerializer, value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_OnGeolocationShowEvent_Void(Ark_Int32 resourceId, Ark_OnGeolocationShowEvent value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnGeolocationShowEvent_Void);
    argsSerializer.writeInt32(resourceId);
    OnGeolocationShowEvent_serializer::write(argsSerializer, value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_OnGeolocationShowEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnGeolocationShowEvent value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_OnGeolocationShowEvent_Void);
    argsSerializer.writeInt32(resourceId);
    OnGeolocationShowEvent_serializer::write(argsSerializer, value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_OnHttpAuthRequestEvent_Boolean(Ark_Int32 resourceId, Ark_OnHttpAuthRequestEvent value0, Callback_Boolean_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnHttpAuthRequestEvent_Boolean);
    argsSerializer.writeInt32(resourceId);
    OnHttpAuthRequestEvent_serializer::write(argsSerializer, value0);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_OnHttpAuthRequestEvent_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnHttpAuthRequestEvent value0, Callback_Boolean_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_OnHttpAuthRequestEvent_Boolean);
    argsSerializer.writeInt32(resourceId);
    OnHttpAuthRequestEvent_serializer::write(argsSerializer, value0);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_OnHttpErrorReceiveEvent_Void(Ark_Int32 resourceId, Ark_OnHttpErrorReceiveEvent value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnHttpErrorReceiveEvent_Void);
    argsSerializer.writeInt32(resourceId);
    OnHttpErrorReceiveEvent_serializer::write(argsSerializer, value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_OnHttpErrorReceiveEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnHttpErrorReceiveEvent value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_OnHttpErrorReceiveEvent_Void);
    argsSerializer.writeInt32(resourceId);
    OnHttpErrorReceiveEvent_serializer::write(argsSerializer, value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_OnLoadFinishedEvent_Void(Ark_Int32 resourceId, Ark_OnLoadFinishedEvent value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnLoadFinishedEvent_Void);
    argsSerializer.writeInt32(resourceId);
    OnLoadFinishedEvent_serializer::write(argsSerializer, value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_OnLoadFinishedEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnLoadFinishedEvent value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_OnLoadFinishedEvent_Void);
    argsSerializer.writeInt32(resourceId);
    OnLoadFinishedEvent_serializer::write(argsSerializer, value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_OnLoadInterceptEvent_Boolean(Ark_Int32 resourceId, Ark_OnLoadInterceptEvent value0, Callback_Boolean_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnLoadInterceptEvent_Boolean);
    argsSerializer.writeInt32(resourceId);
    OnLoadInterceptEvent_serializer::write(argsSerializer, value0);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_OnLoadInterceptEvent_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnLoadInterceptEvent value0, Callback_Boolean_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_OnLoadInterceptEvent_Boolean);
    argsSerializer.writeInt32(resourceId);
    OnLoadInterceptEvent_serializer::write(argsSerializer, value0);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_OnLoadStartedEvent_Void(Ark_Int32 resourceId, Ark_OnLoadStartedEvent value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnLoadStartedEvent_Void);
    argsSerializer.writeInt32(resourceId);
    OnLoadStartedEvent_serializer::write(argsSerializer, value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_OnLoadStartedEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnLoadStartedEvent value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_OnLoadStartedEvent_Void);
    argsSerializer.writeInt32(resourceId);
    OnLoadStartedEvent_serializer::write(argsSerializer, value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_Opt_WebResourceResponse_Void(Ark_Int32 resourceId, Opt_WebResourceResponse value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Opt_WebResourceResponse_Void);
    argsSerializer.writeInt32(resourceId);
    if (runtimeType(value) != INTEROP_RUNTIME_UNDEFINED) {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto valueTmpValue = value.value;
        WebResourceResponse_serializer::write(argsSerializer, valueTmpValue);
    } else {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_Opt_WebResourceResponse_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Opt_WebResourceResponse value)
{
    uint8_t dataBuffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&dataBuffer, sizeof(dataBuffer), nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_Opt_WebResourceResponse_Void);
    argsSerializer.writeInt32(resourceId);
    if (runtimeType(value) != INTEROP_RUNTIME_UNDEFINED) {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto valueTmpValue = value.value;
        WebResourceResponse_serializer::write(argsSerializer, valueTmpValue);
    } else {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(dataBuffer), dataBuffer);
}
void callManagedCallback_onMeasureSize_SizeResult(Ark_Int32 resourceId, Ark_GeometryInfo selfLayoutInfo, Array_Measurable children, Ark_ConstraintSizeOptions constraint, Callback_SizeResult_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_onMeasureSize_SizeResult);
    argsSerializer.writeInt32(resourceId);
    GeometryInfo_serializer::write(argsSerializer, selfLayoutInfo);
    argsSerializer.writeInt32(children.length);
    for (int childrenCounterI = 0; childrenCounterI < children.length; childrenCounterI++) {
        const Ark_Measurable childrenTmpElement = children.array[childrenCounterI];
        Measurable_serializer::write(argsSerializer, childrenTmpElement);
    }
    ConstraintSizeOptions_serializer::write(argsSerializer, constraint);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_onMeasureSize_SizeResultSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_GeometryInfo selfLayoutInfo, Array_Measurable children, Ark_ConstraintSizeOptions constraint, Callback_SizeResult_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_onMeasureSize_SizeResult);
    argsSerializer.writeInt32(resourceId);
    GeometryInfo_serializer::write(argsSerializer, selfLayoutInfo);
    argsSerializer.writeInt32(children.length);
    for (int childrenCounterI = 0; childrenCounterI < children.length; childrenCounterI++) {
        const Ark_Measurable childrenTmpElement = children.array[childrenCounterI];
        Measurable_serializer::write(argsSerializer, childrenTmpElement);
    }
    ConstraintSizeOptions_serializer::write(argsSerializer, constraint);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_OnMoveFromTo(Ark_Int32 resourceId, Ark_Int32 from, Ark_Int32 to)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnMoveFromTo);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(from);
    argsSerializer.writeInt32(to);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_OnMoveFromToSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 from, Ark_Int32 to)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_OnMoveFromTo);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(from);
    argsSerializer.writeInt32(to);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_OnOverScrollEvent_Void(Ark_Int32 resourceId, Ark_OnOverScrollEvent value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnOverScrollEvent_Void);
    argsSerializer.writeInt32(resourceId);
    OnOverScrollEvent_serializer::write(argsSerializer, value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_OnOverScrollEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnOverScrollEvent value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_OnOverScrollEvent_Void);
    argsSerializer.writeInt32(resourceId);
    OnOverScrollEvent_serializer::write(argsSerializer, value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_OnPageBeginEvent_Void(Ark_Int32 resourceId, Ark_OnPageBeginEvent value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnPageBeginEvent_Void);
    argsSerializer.writeInt32(resourceId);
    OnPageBeginEvent_serializer::write(argsSerializer, value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_OnPageBeginEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnPageBeginEvent value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_OnPageBeginEvent_Void);
    argsSerializer.writeInt32(resourceId);
    OnPageBeginEvent_serializer::write(argsSerializer, value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_OnPageEndEvent_Void(Ark_Int32 resourceId, Ark_OnPageEndEvent value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnPageEndEvent_Void);
    argsSerializer.writeInt32(resourceId);
    OnPageEndEvent_serializer::write(argsSerializer, value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_OnPageEndEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnPageEndEvent value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_OnPageEndEvent_Void);
    argsSerializer.writeInt32(resourceId);
    OnPageEndEvent_serializer::write(argsSerializer, value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_OnPageVisibleEvent_Void(Ark_Int32 resourceId, Ark_OnPageVisibleEvent value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnPageVisibleEvent_Void);
    argsSerializer.writeInt32(resourceId);
    OnPageVisibleEvent_serializer::write(argsSerializer, value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_OnPageVisibleEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnPageVisibleEvent value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_OnPageVisibleEvent_Void);
    argsSerializer.writeInt32(resourceId);
    OnPageVisibleEvent_serializer::write(argsSerializer, value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_OnPdfLoadEvent_Void(Ark_Int32 resourceId, Ark_OnPdfLoadEvent value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnPdfLoadEvent_Void);
    argsSerializer.writeInt32(resourceId);
    OnPdfLoadEvent_serializer::write(argsSerializer, value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_OnPdfLoadEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnPdfLoadEvent value0)
{
    uint8_t dataBuffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&dataBuffer, sizeof(dataBuffer), nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_OnPdfLoadEvent_Void);
    argsSerializer.writeInt32(resourceId);
    OnPdfLoadEvent_serializer::write(argsSerializer, value0);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(dataBuffer), dataBuffer);
}
void callManagedCallback_OnPdfScrollEvent_Void(Ark_Int32 resourceId, Ark_OnPdfScrollEvent value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnPdfScrollEvent_Void);
    argsSerializer.writeInt32(resourceId);
    OnPdfScrollEvent_serializer::write(argsSerializer, value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_OnPdfScrollEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnPdfScrollEvent value0)
{
    uint8_t dataBuffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&dataBuffer, sizeof(dataBuffer), nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_OnPdfScrollEvent_Void);
    argsSerializer.writeInt32(resourceId);
    OnPdfScrollEvent_serializer::write(argsSerializer, value0);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(dataBuffer), dataBuffer);
}
void callManagedCallback_OnPermissionRequestEvent_Void(Ark_Int32 resourceId, Ark_OnPermissionRequestEvent value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnPermissionRequestEvent_Void);
    argsSerializer.writeInt32(resourceId);
    OnPermissionRequestEvent_serializer::write(argsSerializer, value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_OnPermissionRequestEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnPermissionRequestEvent value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_OnPermissionRequestEvent_Void);
    argsSerializer.writeInt32(resourceId);
    OnPermissionRequestEvent_serializer::write(argsSerializer, value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_onPlaceChildren_Void(Ark_Int32 resourceId, Ark_GeometryInfo selfLayoutInfo, Array_Layoutable children, Ark_ConstraintSizeOptions constraint)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_onPlaceChildren_Void);
    argsSerializer.writeInt32(resourceId);
    GeometryInfo_serializer::write(argsSerializer, selfLayoutInfo);
    argsSerializer.writeInt32(children.length);
    for (int childrenCounterI = 0; childrenCounterI < children.length; childrenCounterI++) {
        const Ark_Layoutable childrenTmpElement = children.array[childrenCounterI];
        Layoutable_serializer::write(argsSerializer, childrenTmpElement);
    }
    ConstraintSizeOptions_serializer::write(argsSerializer, constraint);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_onPlaceChildren_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_GeometryInfo selfLayoutInfo, Array_Layoutable children, Ark_ConstraintSizeOptions constraint)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_onPlaceChildren_Void);
    argsSerializer.writeInt32(resourceId);
    GeometryInfo_serializer::write(argsSerializer, selfLayoutInfo);
    argsSerializer.writeInt32(children.length);
    for (int childrenCounterI = 0; childrenCounterI < children.length; childrenCounterI++) {
        const Ark_Layoutable childrenTmpElement = children.array[childrenCounterI];
        Layoutable_serializer::write(argsSerializer, childrenTmpElement);
    }
    ConstraintSizeOptions_serializer::write(argsSerializer, constraint);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_OnProgressChangeEvent_Void(Ark_Int32 resourceId, Ark_OnProgressChangeEvent value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnProgressChangeEvent_Void);
    argsSerializer.writeInt32(resourceId);
    OnProgressChangeEvent_serializer::write(argsSerializer, value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_OnProgressChangeEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnProgressChangeEvent value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_OnProgressChangeEvent_Void);
    argsSerializer.writeInt32(resourceId);
    OnProgressChangeEvent_serializer::write(argsSerializer, value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_OnPromptEvent_Boolean(Ark_Int32 resourceId, Ark_OnPromptEvent value0, Callback_Boolean_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnPromptEvent_Boolean);
    argsSerializer.writeInt32(resourceId);
    OnPromptEvent_serializer::write(argsSerializer, value0);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_OnPromptEvent_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnPromptEvent value0, Callback_Boolean_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_OnPromptEvent_Boolean);
    argsSerializer.writeInt32(resourceId);
    OnPromptEvent_serializer::write(argsSerializer, value0);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_OnRefreshAccessedHistoryEvent_Void(Ark_Int32 resourceId, Ark_OnRefreshAccessedHistoryEvent value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnRefreshAccessedHistoryEvent_Void);
    argsSerializer.writeInt32(resourceId);
    OnRefreshAccessedHistoryEvent_serializer::write(argsSerializer, value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_OnRefreshAccessedHistoryEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnRefreshAccessedHistoryEvent value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_OnRefreshAccessedHistoryEvent_Void);
    argsSerializer.writeInt32(resourceId);
    OnRefreshAccessedHistoryEvent_serializer::write(argsSerializer, value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_OnRenderExitedEvent_Void(Ark_Int32 resourceId, Ark_OnRenderExitedEvent value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnRenderExitedEvent_Void);
    argsSerializer.writeInt32(resourceId);
    OnRenderExitedEvent_serializer::write(argsSerializer, value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_OnRenderExitedEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnRenderExitedEvent value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_OnRenderExitedEvent_Void);
    argsSerializer.writeInt32(resourceId);
    OnRenderExitedEvent_serializer::write(argsSerializer, value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_OnResourceLoadEvent_Void(Ark_Int32 resourceId, Ark_OnResourceLoadEvent value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnResourceLoadEvent_Void);
    argsSerializer.writeInt32(resourceId);
    OnResourceLoadEvent_serializer::write(argsSerializer, value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_OnResourceLoadEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnResourceLoadEvent value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_OnResourceLoadEvent_Void);
    argsSerializer.writeInt32(resourceId);
    OnResourceLoadEvent_serializer::write(argsSerializer, value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_OnScaleChangeEvent_Void(Ark_Int32 resourceId, Ark_OnScaleChangeEvent value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnScaleChangeEvent_Void);
    argsSerializer.writeInt32(resourceId);
    OnScaleChangeEvent_serializer::write(argsSerializer, value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_OnScaleChangeEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnScaleChangeEvent value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_OnScaleChangeEvent_Void);
    argsSerializer.writeInt32(resourceId);
    OnScaleChangeEvent_serializer::write(argsSerializer, value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_OnScreenCaptureRequestEvent_Void(Ark_Int32 resourceId, Ark_OnScreenCaptureRequestEvent value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnScreenCaptureRequestEvent_Void);
    argsSerializer.writeInt32(resourceId);
    OnScreenCaptureRequestEvent_serializer::write(argsSerializer, value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_OnScreenCaptureRequestEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnScreenCaptureRequestEvent value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_OnScreenCaptureRequestEvent_Void);
    argsSerializer.writeInt32(resourceId);
    OnScreenCaptureRequestEvent_serializer::write(argsSerializer, value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_OnScrollEvent_Void(Ark_Int32 resourceId, Ark_OnScrollEvent value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnScrollEvent_Void);
    argsSerializer.writeInt32(resourceId);
    OnScrollEvent_serializer::write(argsSerializer, value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_OnScrollEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnScrollEvent value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_OnScrollEvent_Void);
    argsSerializer.writeInt32(resourceId);
    OnScrollEvent_serializer::write(argsSerializer, value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_OnScrollFrameBeginHandlerResult_Void(Ark_Int32 resourceId, Ark_OnScrollFrameBeginHandlerResult value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnScrollFrameBeginHandlerResult_Void);
    argsSerializer.writeInt32(resourceId);
    OnScrollFrameBeginHandlerResult_serializer::write(argsSerializer, value);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_OnScrollFrameBeginHandlerResult_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnScrollFrameBeginHandlerResult value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_OnScrollFrameBeginHandlerResult_Void);
    argsSerializer.writeInt32(resourceId);
    OnScrollFrameBeginHandlerResult_serializer::write(argsSerializer, value);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_OnSearchResultReceiveEvent_Void(Ark_Int32 resourceId, Ark_OnSearchResultReceiveEvent value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnSearchResultReceiveEvent_Void);
    argsSerializer.writeInt32(resourceId);
    OnSearchResultReceiveEvent_serializer::write(argsSerializer, value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_OnSearchResultReceiveEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnSearchResultReceiveEvent value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_OnSearchResultReceiveEvent_Void);
    argsSerializer.writeInt32(resourceId);
    OnSearchResultReceiveEvent_serializer::write(argsSerializer, value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_OnShowFileSelectorEvent_Boolean(Ark_Int32 resourceId, Ark_OnShowFileSelectorEvent value0, Callback_Boolean_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnShowFileSelectorEvent_Boolean);
    argsSerializer.writeInt32(resourceId);
    OnShowFileSelectorEvent_serializer::write(argsSerializer, value0);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_OnShowFileSelectorEvent_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnShowFileSelectorEvent value0, Callback_Boolean_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_OnShowFileSelectorEvent_Boolean);
    argsSerializer.writeInt32(resourceId);
    OnShowFileSelectorEvent_serializer::write(argsSerializer, value0);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_OnSslErrorEventReceiveEvent_Void(Ark_Int32 resourceId, Ark_OnSslErrorEventReceiveEvent value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnSslErrorEventReceiveEvent_Void);
    argsSerializer.writeInt32(resourceId);
    OnSslErrorEventReceiveEvent_serializer::write(argsSerializer, value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_OnSslErrorEventReceiveEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnSslErrorEventReceiveEvent value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_OnSslErrorEventReceiveEvent_Void);
    argsSerializer.writeInt32(resourceId);
    OnSslErrorEventReceiveEvent_serializer::write(argsSerializer, value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_OnTitleReceiveEvent_Void(Ark_Int32 resourceId, Ark_OnTitleReceiveEvent value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnTitleReceiveEvent_Void);
    argsSerializer.writeInt32(resourceId);
    OnTitleReceiveEvent_serializer::write(argsSerializer, value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_OnTitleReceiveEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnTitleReceiveEvent value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_OnTitleReceiveEvent_Void);
    argsSerializer.writeInt32(resourceId);
    OnTitleReceiveEvent_serializer::write(argsSerializer, value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_OnTouchIconUrlReceivedEvent_Void(Ark_Int32 resourceId, Ark_OnTouchIconUrlReceivedEvent value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnTouchIconUrlReceivedEvent_Void);
    argsSerializer.writeInt32(resourceId);
    OnTouchIconUrlReceivedEvent_serializer::write(argsSerializer, value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_OnTouchIconUrlReceivedEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnTouchIconUrlReceivedEvent value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_OnTouchIconUrlReceivedEvent_Void);
    argsSerializer.writeInt32(resourceId);
    OnTouchIconUrlReceivedEvent_serializer::write(argsSerializer, value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_OnWindowNewEvent_Void(Ark_Int32 resourceId, Ark_OnWindowNewEvent value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_OnWindowNewEvent_Void);
    argsSerializer.writeInt32(resourceId);
    OnWindowNewEvent_serializer::write(argsSerializer, value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_OnWindowNewEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnWindowNewEvent value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_OnWindowNewEvent_Void);
    argsSerializer.writeInt32(resourceId);
    OnWindowNewEvent_serializer::write(argsSerializer, value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_Opt_Array_NavDestinationTransition_Void(Ark_Int32 resourceId, Opt_Array_NavDestinationTransition value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Opt_Array_NavDestinationTransition_Void);
    argsSerializer.writeInt32(resourceId);
    if (runtimeType(value) != INTEROP_RUNTIME_UNDEFINED) {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto valueTmpValue = value.value;
        argsSerializer.writeInt32(valueTmpValue.length);
        for (int valueTmpValueCounterI = 0; valueTmpValueCounterI < valueTmpValue.length; valueTmpValueCounterI++) {
            const Ark_NavDestinationTransition valueTmpValueTmpElement = valueTmpValue.array[valueTmpValueCounterI];
            NavDestinationTransition_serializer::write(argsSerializer, valueTmpValueTmpElement);
        }
    } else {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_Opt_Array_NavDestinationTransition_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Opt_Array_NavDestinationTransition value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_Opt_Array_NavDestinationTransition_Void);
    argsSerializer.writeInt32(resourceId);
    if (runtimeType(value) != INTEROP_RUNTIME_UNDEFINED) {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto valueTmpValue = value.value;
        argsSerializer.writeInt32(valueTmpValue.length);
        for (int valueTmpValueCounterI = 0; valueTmpValueCounterI < valueTmpValue.length; valueTmpValueCounterI++) {
            const Ark_NavDestinationTransition valueTmpValueTmpElement = valueTmpValue.array[valueTmpValueCounterI];
            NavDestinationTransition_serializer::write(argsSerializer, valueTmpValueTmpElement);
        }
    } else {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_Opt_Array_String_Void(Ark_Int32 resourceId, Opt_Array_String error)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Opt_Array_String_Void);
    argsSerializer.writeInt32(resourceId);
    if (runtimeType(error) != INTEROP_RUNTIME_UNDEFINED) {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto errorTmpValue = error.value;
        argsSerializer.writeInt32(errorTmpValue.length);
        for (int errorTmpValueCounterI = 0; errorTmpValueCounterI < errorTmpValue.length; errorTmpValueCounterI++) {
            const Ark_String errorTmpValueTmpElement = errorTmpValue.array[errorTmpValueCounterI];
            argsSerializer.writeString(errorTmpValueTmpElement);
        }
    } else {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_Opt_Array_String_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Opt_Array_String error)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_Opt_Array_String_Void);
    argsSerializer.writeInt32(resourceId);
    if (runtimeType(error) != INTEROP_RUNTIME_UNDEFINED) {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto errorTmpValue = error.value;
        argsSerializer.writeInt32(errorTmpValue.length);
        for (int errorTmpValueCounterI = 0; errorTmpValueCounterI < errorTmpValue.length; errorTmpValueCounterI++) {
            const Ark_String errorTmpValueTmpElement = errorTmpValue.array[errorTmpValueCounterI];
            argsSerializer.writeString(errorTmpValueTmpElement);
        }
    } else {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_Opt_CustomBuilder_Void(Ark_Int32 resourceId, Opt_CustomNodeBuilder value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Opt_CustomBuilder_Void);
    argsSerializer.writeInt32(resourceId);
    if (runtimeType(value) != INTEROP_RUNTIME_UNDEFINED) {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto valueTmpValue = value.value;
        argsSerializer.writeCallbackResource(valueTmpValue.resource);
        argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(valueTmpValue.call));
        argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(valueTmpValue.callSync));
    } else {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_Opt_CustomBuilder_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Opt_CustomNodeBuilder value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_Opt_CustomBuilder_Void);
    argsSerializer.writeInt32(resourceId);
    if (runtimeType(value) != INTEROP_RUNTIME_UNDEFINED) {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto valueTmpValue = value.value;
        argsSerializer.writeCallbackResource(valueTmpValue.resource);
        argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(valueTmpValue.call));
        argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(valueTmpValue.callSync));
    } else {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_Opt_NavigationAnimatedTransition_Void(Ark_Int32 resourceId, Opt_NavigationAnimatedTransition value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Opt_NavigationAnimatedTransition_Void);
    argsSerializer.writeInt32(resourceId);
    if (runtimeType(value) != INTEROP_RUNTIME_UNDEFINED) {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto valueTmpValue = value.value;
        NavigationAnimatedTransition_serializer::write(argsSerializer, valueTmpValue);
    } else {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_Opt_NavigationAnimatedTransition_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Opt_NavigationAnimatedTransition value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_Opt_NavigationAnimatedTransition_Void);
    argsSerializer.writeInt32(resourceId);
    if (runtimeType(value) != INTEROP_RUNTIME_UNDEFINED) {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto valueTmpValue = value.value;
        NavigationAnimatedTransition_serializer::write(argsSerializer, valueTmpValue);
    } else {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_Opt_OffsetResult_Void(Ark_Int32 resourceId, Opt_OffsetResult value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Opt_OffsetResult_Void);
    argsSerializer.writeInt32(resourceId);
    if (runtimeType(value) != INTEROP_RUNTIME_UNDEFINED) {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto valueTmpValue = value.value;
        OffsetResult_serializer::write(argsSerializer, valueTmpValue);
    } else {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_Opt_OffsetResult_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Opt_OffsetResult value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_Opt_OffsetResult_Void);
    argsSerializer.writeInt32(resourceId);
    if (runtimeType(value) != INTEROP_RUNTIME_UNDEFINED) {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto valueTmpValue = value.value;
        OffsetResult_serializer::write(argsSerializer, valueTmpValue);
    } else {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_Opt_ScrollResult_Void(Ark_Int32 resourceId, Opt_ScrollResult value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Opt_ScrollResult_Void);
    argsSerializer.writeInt32(resourceId);
    if (runtimeType(value) != INTEROP_RUNTIME_UNDEFINED) {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto valueTmpValue = value.value;
        ScrollResult_serializer::write(argsSerializer, valueTmpValue);
    } else {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_Opt_ScrollResult_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Opt_ScrollResult value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_Opt_ScrollResult_Void);
    argsSerializer.writeInt32(resourceId);
    if (runtimeType(value) != INTEROP_RUNTIME_UNDEFINED) {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto valueTmpValue = value.value;
        ScrollResult_serializer::write(argsSerializer, valueTmpValue);
    } else {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_Opt_StyledString_Opt_Array_String_Void(Ark_Int32 resourceId, Opt_StyledString value, Opt_Array_String error)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Opt_StyledString_Opt_Array_String_Void);
    argsSerializer.writeInt32(resourceId);
    if (runtimeType(value) != INTEROP_RUNTIME_UNDEFINED) {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto valueTmpValue = value.value;
        StyledString_serializer::write(argsSerializer, valueTmpValue);
    } else {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    if (runtimeType(error) != INTEROP_RUNTIME_UNDEFINED) {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto errorTmpValue = error.value;
        argsSerializer.writeInt32(errorTmpValue.length);
        for (int errorTmpValueCounterI = 0; errorTmpValueCounterI < errorTmpValue.length; errorTmpValueCounterI++) {
            const Ark_String errorTmpValueTmpElement = errorTmpValue.array[errorTmpValueCounterI];
            argsSerializer.writeString(errorTmpValueTmpElement);
        }
    } else {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_Opt_StyledString_Opt_Array_String_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Opt_StyledString value, Opt_Array_String error)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_Opt_StyledString_Opt_Array_String_Void);
    argsSerializer.writeInt32(resourceId);
    if (runtimeType(value) != INTEROP_RUNTIME_UNDEFINED) {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto valueTmpValue = value.value;
        StyledString_serializer::write(argsSerializer, valueTmpValue);
    } else {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    if (runtimeType(error) != INTEROP_RUNTIME_UNDEFINED) {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto errorTmpValue = error.value;
        argsSerializer.writeInt32(errorTmpValue.length);
        for (int errorTmpValueCounterI = 0; errorTmpValueCounterI < errorTmpValue.length; errorTmpValueCounterI++) {
            const Ark_String errorTmpValueTmpElement = errorTmpValue.array[errorTmpValueCounterI];
            argsSerializer.writeString(errorTmpValueTmpElement);
        }
    } else {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_Opt_TabContentAnimatedTransition_Void(Ark_Int32 resourceId, Opt_TabContentAnimatedTransition value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Opt_TabContentAnimatedTransition_Void);
    argsSerializer.writeInt32(resourceId);
    if (runtimeType(value) != INTEROP_RUNTIME_UNDEFINED) {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto valueTmpValue = value.value;
        TabContentAnimatedTransition_serializer::write(argsSerializer, valueTmpValue);
    } else {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_Opt_TabContentAnimatedTransition_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Opt_TabContentAnimatedTransition value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_Opt_TabContentAnimatedTransition_Void);
    argsSerializer.writeInt32(resourceId);
    if (runtimeType(value) != INTEROP_RUNTIME_UNDEFINED) {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto valueTmpValue = value.value;
        TabContentAnimatedTransition_serializer::write(argsSerializer, valueTmpValue);
    } else {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_PlaybackInfo_Void(Ark_Int32 resourceId, Ark_PlaybackInfo value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_PlaybackInfo_Void);
    argsSerializer.writeInt32(resourceId);
    PlaybackInfo_serializer::write(argsSerializer, value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_PlaybackInfo_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_PlaybackInfo value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_PlaybackInfo_Void);
    argsSerializer.writeInt32(resourceId);
    PlaybackInfo_serializer::write(argsSerializer, value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_Pointer_Void(Ark_Int32 resourceId, Ark_NativePointer value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Pointer_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(value);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_Pointer_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NativePointer value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_Pointer_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(value);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_PopInfo_Void(Ark_Int32 resourceId, Ark_PopInfo value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_PopInfo_Void);
    argsSerializer.writeInt32(resourceId);
    PopInfo_serializer::write(argsSerializer, value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_PopInfo_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_PopInfo value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_PopInfo_Void);
    argsSerializer.writeInt32(resourceId);
    PopInfo_serializer::write(argsSerializer, value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_PreDragStatus_Void(Ark_Int32 resourceId, Ark_PreDragStatus value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_PreDragStatus_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_PreDragStatus>(value0));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_PreDragStatus_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_PreDragStatus value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_PreDragStatus_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_PreDragStatus>(value0));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_PreparedInfo_Void(Ark_Int32 resourceId, Ark_PreparedInfo value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_PreparedInfo_Void);
    argsSerializer.writeInt32(resourceId);
    PreparedInfo_serializer::write(argsSerializer, value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_PreparedInfo_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_PreparedInfo value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_PreparedInfo_Void);
    argsSerializer.writeInt32(resourceId);
    PreparedInfo_serializer::write(argsSerializer, value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_RangeUpdate(Ark_Int32 resourceId, Ark_Int32 start, Ark_Int32 end, Ark_Int32 cacheStart, Ark_Int32 cacheEnd, Ark_Boolean isLoop)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_RangeUpdate);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(start);
    argsSerializer.writeInt32(end);
    argsSerializer.writeInt32(cacheStart);
    argsSerializer.writeInt32(cacheEnd);
    argsSerializer.writeBoolean(isLoop);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_RangeUpdateSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 start, Ark_Int32 end, Ark_Int32 cacheStart, Ark_Int32 cacheEnd, Ark_Boolean isLoop)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_RangeUpdate);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(start);
    argsSerializer.writeInt32(end);
    argsSerializer.writeInt32(cacheStart);
    argsSerializer.writeInt32(cacheEnd);
    argsSerializer.writeBoolean(isLoop);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_RefreshStatus_Void(Ark_Int32 resourceId, Ark_RefreshStatus state)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_RefreshStatus_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_RefreshStatus>(state));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_RefreshStatus_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_RefreshStatus state)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_RefreshStatus_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_RefreshStatus>(state));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_RichEditorChangeValue_Boolean(Ark_Int32 resourceId, Ark_RichEditorChangeValue value0, Callback_Boolean_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_RichEditorChangeValue_Boolean);
    argsSerializer.writeInt32(resourceId);
    RichEditorChangeValue_serializer::write(argsSerializer, value0);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_RichEditorChangeValue_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_RichEditorChangeValue value0, Callback_Boolean_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_RichEditorChangeValue_Boolean);
    argsSerializer.writeInt32(resourceId);
    RichEditorChangeValue_serializer::write(argsSerializer, value0);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_RichEditorDeleteValue_Boolean(Ark_Int32 resourceId, Ark_RichEditorDeleteValue value0, Callback_Boolean_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_RichEditorDeleteValue_Boolean);
    argsSerializer.writeInt32(resourceId);
    RichEditorDeleteValue_serializer::write(argsSerializer, value0);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_RichEditorDeleteValue_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_RichEditorDeleteValue value0, Callback_Boolean_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_RichEditorDeleteValue_Boolean);
    argsSerializer.writeInt32(resourceId);
    RichEditorDeleteValue_serializer::write(argsSerializer, value0);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_RichEditorInsertValue_Boolean(Ark_Int32 resourceId, Ark_RichEditorInsertValue value0, Callback_Boolean_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_RichEditorInsertValue_Boolean);
    argsSerializer.writeInt32(resourceId);
    RichEditorInsertValue_serializer::write(argsSerializer, value0);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_RichEditorInsertValue_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_RichEditorInsertValue value0, Callback_Boolean_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_RichEditorInsertValue_Boolean);
    argsSerializer.writeInt32(resourceId);
    RichEditorInsertValue_serializer::write(argsSerializer, value0);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_RichEditorRange_Void(Ark_Int32 resourceId, Ark_RichEditorRange value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_RichEditorRange_Void);
    argsSerializer.writeInt32(resourceId);
    RichEditorRange_serializer::write(argsSerializer, value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_RichEditorRange_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_RichEditorRange value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_RichEditorRange_Void);
    argsSerializer.writeInt32(resourceId);
    RichEditorRange_serializer::write(argsSerializer, value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_RichEditorSelection_Void(Ark_Int32 resourceId, Ark_RichEditorSelection value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_RichEditorSelection_Void);
    argsSerializer.writeInt32(resourceId);
    RichEditorSelection_serializer::write(argsSerializer, value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_RichEditorSelection_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_RichEditorSelection value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_RichEditorSelection_Void);
    argsSerializer.writeInt32(resourceId);
    RichEditorSelection_serializer::write(argsSerializer, value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_RichEditorTextSpanResult_Void(Ark_Int32 resourceId, Ark_RichEditorTextSpanResult value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_RichEditorTextSpanResult_Void);
    argsSerializer.writeInt32(resourceId);
    RichEditorTextSpanResult_serializer::write(argsSerializer, value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_RichEditorTextSpanResult_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_RichEditorTextSpanResult value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_RichEditorTextSpanResult_Void);
    argsSerializer.writeInt32(resourceId);
    RichEditorTextSpanResult_serializer::write(argsSerializer, value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_RouterCallbackInfo_Void(Ark_Int32 resourceId, Ark_RouterCallbackInfo value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_RouterCallbackInfo_Void);
    argsSerializer.writeInt32(resourceId);
    RouterCallbackInfo_serializer::write(argsSerializer, value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_RouterCallbackInfo_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_RouterCallbackInfo value0)
{
    uint8_t dataBuffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&dataBuffer, sizeof(dataBuffer), nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_RouterCallbackInfo_Void);
    argsSerializer.writeInt32(resourceId);
    RouterCallbackInfo_serializer::write(argsSerializer, value0);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(dataBuffer), dataBuffer);
}
void callManagedCallback_SheetDismiss_Void(Ark_Int32 resourceId, Ark_SheetDismiss sheetDismiss)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_SheetDismiss_Void);
    argsSerializer.writeInt32(resourceId);
    SheetDismiss_serializer::write(argsSerializer, sheetDismiss);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_SheetDismiss_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_SheetDismiss sheetDismiss)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_SheetDismiss_Void);
    argsSerializer.writeInt32(resourceId);
    SheetDismiss_serializer::write(argsSerializer, sheetDismiss);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_SheetType_Void(Ark_Int32 resourceId, Ark_SheetType value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_SheetType_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_SheetType>(value0));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_SheetType_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_SheetType value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_SheetType_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_SheetType>(value0));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_Size_Void(Ark_Int32 resourceId, Ark_Size size)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Size_Void);
    argsSerializer.writeInt32(resourceId);
    Size_serializer::write(argsSerializer, size);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_Size_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Size size)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_Size_Void);
    argsSerializer.writeInt32(resourceId);
    Size_serializer::write(argsSerializer, size);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_SizeResult_Void(Ark_Int32 resourceId, Ark_SizeResult value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_SizeResult_Void);
    argsSerializer.writeInt32(resourceId);
    SizeResult_serializer::write(argsSerializer, value);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_SizeResult_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_SizeResult value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_SizeResult_Void);
    argsSerializer.writeInt32(resourceId);
    SizeResult_serializer::write(argsSerializer, value);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_SpringBackAction_Void(Ark_Int32 resourceId, Ark_SpringBackAction value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_SpringBackAction_Void);
    argsSerializer.writeInt32(resourceId);
    SpringBackAction_serializer::write(argsSerializer, value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_SpringBackAction_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_SpringBackAction value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_SpringBackAction_Void);
    argsSerializer.writeInt32(resourceId);
    SpringBackAction_serializer::write(argsSerializer, value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_StateStylesChange(Ark_Int32 resourceId, Ark_Int32 currentState)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_StateStylesChange);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(currentState);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_StateStylesChangeSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 currentState)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_StateStylesChange);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(currentState);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_String_PasteEvent_Void(Ark_Int32 resourceId, Ark_String value, Ark_PasteEvent event)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_String_PasteEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(value);
    PasteEvent_serializer::write(argsSerializer, event);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_String_PasteEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_String value, Ark_PasteEvent event)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_String_PasteEvent_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(value);
    PasteEvent_serializer::write(argsSerializer, event);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_String_SurfaceRect_Void(Ark_Int32 resourceId, Ark_String surfaceId, Ark_SurfaceRect rect)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_String_SurfaceRect_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(surfaceId);
    SurfaceRect_serializer::write(argsSerializer, rect);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_String_SurfaceRect_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_String surfaceId, Ark_SurfaceRect rect)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_String_SurfaceRect_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(surfaceId);
    SurfaceRect_serializer::write(argsSerializer, rect);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_String_Void(Ark_Int32 resourceId, Ark_String breakpoints)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_String_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(breakpoints);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_String_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_String breakpoints)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_String_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(breakpoints);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_StyledStringChangeValue_Boolean(Ark_Int32 resourceId, Ark_StyledStringChangeValue value0, Callback_Boolean_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_StyledStringChangeValue_Boolean);
    argsSerializer.writeInt32(resourceId);
    StyledStringChangeValue_serializer::write(argsSerializer, value0);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_StyledStringChangeValue_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_StyledStringChangeValue value0, Callback_Boolean_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_StyledStringChangeValue_Boolean);
    argsSerializer.writeInt32(resourceId);
    StyledStringChangeValue_serializer::write(argsSerializer, value0);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_StyledStringMarshallingValue_Void(Ark_Int32 resourceId, Ark_UserDataSpan value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_StyledStringMarshallingValue_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeObject(value);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_StyledStringMarshallingValue_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_UserDataSpan value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_StyledStringMarshallingValue_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeObject(value);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_SwipeActionState_Void(Ark_Int32 resourceId, Ark_SwipeActionState state)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_SwipeActionState_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_SwipeActionState>(state));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_SwipeActionState_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_SwipeActionState state)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_SwipeActionState_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_SwipeActionState>(state));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_SwiperContentTransitionProxy_Void(Ark_Int32 resourceId, Ark_SwiperContentTransitionProxy value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_SwiperContentTransitionProxy_Void);
    argsSerializer.writeInt32(resourceId);
    SwiperContentTransitionProxy_serializer::write(argsSerializer, value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_SwiperContentTransitionProxy_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_SwiperContentTransitionProxy value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_SwiperContentTransitionProxy_Void);
    argsSerializer.writeInt32(resourceId);
    SwiperContentTransitionProxy_serializer::write(argsSerializer, value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_T_Void_Arkui_Component_Units_Length(Ark_Int32 resourceId, Ark_Length value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_T_Void_Arkui_Component_Units_Length);
    argsSerializer.writeInt32(resourceId);
    if (value0.selector == 0) {
        argsSerializer.writeInt8(0);
        const auto value0ForIdx0 = value0.value0;
        argsSerializer.writeString(value0ForIdx0);
    } else if (value0.selector == 1) {
        argsSerializer.writeInt8(1);
        const auto value0ForIdx1 = value0.value1;
        argsSerializer.writeFloat64(value0ForIdx1);
    } else if (value0.selector == 2) {
        argsSerializer.writeInt8(2);
        const auto value0ForIdx2 = value0.value2;
        Resource_serializer::write(argsSerializer, value0ForIdx2);
    }
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_T_Void_Arkui_Component_Units_LengthSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Length value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_T_Void_Arkui_Component_Units_Length);
    argsSerializer.writeInt32(resourceId);
    if (value0.selector == 0) {
        argsSerializer.writeInt8(0);
        const auto value0ForIdx0 = value0.value0;
        argsSerializer.writeString(value0ForIdx0);
    } else if (value0.selector == 1) {
        argsSerializer.writeInt8(1);
        const auto value0ForIdx1 = value0.value1;
        argsSerializer.writeFloat64(value0ForIdx1);
    } else if (value0.selector == 2) {
        argsSerializer.writeInt8(2);
        const auto value0ForIdx2 = value0.value2;
        Resource_serializer::write(argsSerializer, value0ForIdx2);
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_T_Void_Arkui_Component_Units_ResourceStr(Ark_Int32 resourceId, Ark_ResourceStr value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_T_Void_Arkui_Component_Units_ResourceStr);
    argsSerializer.writeInt32(resourceId);
    if (value0.selector == 0) {
        argsSerializer.writeInt8(0);
        const auto value0ForIdx0 = value0.value0;
        argsSerializer.writeString(value0ForIdx0);
    } else if (value0.selector == 1) {
        argsSerializer.writeInt8(1);
        const auto value0ForIdx1 = value0.value1;
        Resource_serializer::write(argsSerializer, value0ForIdx1);
    }
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_T_Void_Arkui_Component_Units_ResourceStrSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_ResourceStr value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_T_Void_Arkui_Component_Units_ResourceStr);
    argsSerializer.writeInt32(resourceId);
    if (value0.selector == 0) {
        argsSerializer.writeInt8(0);
        const auto value0ForIdx0 = value0.value0;
        argsSerializer.writeString(value0ForIdx0);
    } else if (value0.selector == 1) {
        argsSerializer.writeInt8(1);
        const auto value0ForIdx1 = value0.value1;
        Resource_serializer::write(argsSerializer, value0ForIdx1);
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_T_Void_Array_Arkui_Component_Units_ResourceStr(Ark_Int32 resourceId, Array_ResourceStr value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_T_Void_Array_Arkui_Component_Units_ResourceStr);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(value0.length);
    for (int value0CounterI = 0; value0CounterI < value0.length; value0CounterI++) {
        const Ark_ResourceStr value0TmpElement = value0.array[value0CounterI];
        if (value0TmpElement.selector == 0) {
            argsSerializer.writeInt8(0);
            const auto value0TmpElementForIdx0 = value0TmpElement.value0;
            argsSerializer.writeString(value0TmpElementForIdx0);
        } else if (value0TmpElement.selector == 1) {
            argsSerializer.writeInt8(1);
            const auto value0TmpElementForIdx1 = value0TmpElement.value1;
            Resource_serializer::write(argsSerializer, value0TmpElementForIdx1);
        }
    }
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_T_Void_Array_Arkui_Component_Units_ResourceStrSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Array_ResourceStr value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_T_Void_Array_Arkui_Component_Units_ResourceStr);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(value0.length);
    for (int value0CounterI = 0; value0CounterI < value0.length; value0CounterI++) {
        const Ark_ResourceStr value0TmpElement = value0.array[value0CounterI];
        if (value0TmpElement.selector == 0) {
            argsSerializer.writeInt8(0);
            const auto value0TmpElementForIdx0 = value0TmpElement.value0;
            argsSerializer.writeString(value0TmpElementForIdx0);
        } else if (value0TmpElement.selector == 1) {
            argsSerializer.writeInt8(1);
            const auto value0TmpElementForIdx1 = value0TmpElement.value1;
            Resource_serializer::write(argsSerializer, value0TmpElementForIdx1);
        }
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_T_Void_Array_Global_Resource_Resource(Ark_Int32 resourceId, Array_Resource value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_T_Void_Array_Global_Resource_Resource);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(value0.length);
    for (int value0CounterI = 0; value0CounterI < value0.length; value0CounterI++) {
        const Ark_Resource value0TmpElement = value0.array[value0CounterI];
        Resource_serializer::write(argsSerializer, value0TmpElement);
    }
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_T_Void_Array_Global_Resource_ResourceSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Array_Resource value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_T_Void_Array_Global_Resource_Resource);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(value0.length);
    for (int value0CounterI = 0; value0CounterI < value0.length; value0CounterI++) {
        const Ark_Resource value0TmpElement = value0.array[value0CounterI];
        Resource_serializer::write(argsSerializer, value0TmpElement);
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_T_Void_Array_I32(Ark_Int32 resourceId, Array_Int32 value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_T_Void_Array_I32);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(value0.length);
    for (int value0CounterI = 0; value0CounterI < value0.length; value0CounterI++) {
        const Ark_Int32 value0TmpElement = value0.array[value0CounterI];
        argsSerializer.writeInt32(value0TmpElement);
    }
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_T_Void_Array_I32Sync(Ark_VMContext vmContext, Ark_Int32 resourceId, Array_Int32 value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_T_Void_Array_I32);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(value0.length);
    for (int value0CounterI = 0; value0CounterI < value0.length; value0CounterI++) {
        const Ark_Int32 value0TmpElement = value0.array[value0CounterI];
        argsSerializer.writeInt32(value0TmpElement);
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_T_Void_Array_String(Ark_Int32 resourceId, Array_String value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_T_Void_Array_String);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(value0.length);
    for (int value0CounterI = 0; value0CounterI < value0.length; value0CounterI++) {
        const Ark_String value0TmpElement = value0.array[value0CounterI];
        argsSerializer.writeString(value0TmpElement);
    }
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_T_Void_Array_StringSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Array_String value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_T_Void_Array_String);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(value0.length);
    for (int value0CounterI = 0; value0CounterI < value0.length; value0CounterI++) {
        const Ark_String value0TmpElement = value0.array[value0CounterI];
        argsSerializer.writeString(value0TmpElement);
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_T_Void_Boolean(Ark_Int32 resourceId, Ark_Boolean value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_T_Void_Boolean);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_T_Void_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Boolean value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_T_Void_Boolean);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_T_Void_Date(Ark_Int32 resourceId, Ark_Date value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_T_Void_Date);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt64(value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_T_Void_DateSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Date value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_T_Void_Date);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt64(value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_T_Void_F64(Ark_Int32 resourceId, Ark_Float64 value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_T_Void_F64);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFloat64(value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_T_Void_F64Sync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Float64 value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_T_Void_F64);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFloat64(value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_T_Void_Global_Resource_Resource(Ark_Int32 resourceId, Ark_Resource value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_T_Void_Global_Resource_Resource);
    argsSerializer.writeInt32(resourceId);
    Resource_serializer::write(argsSerializer, value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_T_Void_Global_Resource_ResourceSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Resource value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_T_Void_Global_Resource_Resource);
    argsSerializer.writeInt32(resourceId);
    Resource_serializer::write(argsSerializer, value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_T_Void_I32(Ark_Int32 resourceId, Ark_Int32 value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_T_Void_I32);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_T_Void_I32Sync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_T_Void_I32);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_T_Void_Number(Ark_Int32 resourceId, Ark_Number value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_T_Void_Number);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_T_Void_NumberSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_T_Void_Number);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_T_Void_String(Ark_Int32 resourceId, Ark_String value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_T_Void_String);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_T_Void_StringSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_String value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_T_Void_String);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_TabContentTransitionProxy_Void(Ark_Int32 resourceId, Ark_TabContentTransitionProxy value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_TabContentTransitionProxy_Void);
    argsSerializer.writeInt32(resourceId);
    TabContentTransitionProxy_serializer::write(argsSerializer, value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_TabContentTransitionProxy_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_TabContentTransitionProxy value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_TabContentTransitionProxy_Void);
    argsSerializer.writeInt32(resourceId);
    TabContentTransitionProxy_serializer::write(argsSerializer, value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_TerminationInfo_Void(Ark_Int32 resourceId, Ark_TerminationInfo value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_TerminationInfo_Void);
    argsSerializer.writeInt32(resourceId);
    TerminationInfo_serializer::write(argsSerializer, value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_TerminationInfo_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_TerminationInfo value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_TerminationInfo_Void);
    argsSerializer.writeInt32(resourceId);
    TerminationInfo_serializer::write(argsSerializer, value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_TextPickerResult_Void(Ark_Int32 resourceId, Ark_TextPickerResult value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_TextPickerResult_Void);
    argsSerializer.writeInt32(resourceId);
    TextPickerResult_serializer::write(argsSerializer, value);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_TextPickerResult_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_TextPickerResult value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_TextPickerResult_Void);
    argsSerializer.writeInt32(resourceId);
    TextPickerResult_serializer::write(argsSerializer, value);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_TextRange_Void(Ark_Int32 resourceId, Ark_TextRange value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_TextRange_Void);
    argsSerializer.writeInt32(resourceId);
    TextRange_serializer::write(argsSerializer, value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_TextRange_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_TextRange value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_TextRange_Void);
    argsSerializer.writeInt32(resourceId);
    TextRange_serializer::write(argsSerializer, value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_TimePickerResult_Void(Ark_Int32 resourceId, Ark_TimePickerResult value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_TimePickerResult_Void);
    argsSerializer.writeInt32(resourceId);
    TimePickerResult_serializer::write(argsSerializer, value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_TimePickerResult_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_TimePickerResult value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_TimePickerResult_Void);
    argsSerializer.writeInt32(resourceId);
    TimePickerResult_serializer::write(argsSerializer, value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_TouchEvent_HitTestMode(Ark_Int32 resourceId, Ark_TouchEvent value0, Callback_HitTestMode_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_TouchEvent_HitTestMode);
    argsSerializer.writeInt32(resourceId);
    TouchEvent_serializer::write(argsSerializer, value0);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_TouchEvent_HitTestModeSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_TouchEvent value0, Callback_HitTestMode_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_TouchEvent_HitTestMode);
    argsSerializer.writeInt32(resourceId);
    TouchEvent_serializer::write(argsSerializer, value0);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_TouchEvent_Void(Ark_Int32 resourceId, Ark_TouchEvent event)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_TouchEvent_Void);
    argsSerializer.writeInt32(resourceId);
    TouchEvent_serializer::write(argsSerializer, event);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_TouchEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_TouchEvent event)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_TouchEvent_Void);
    argsSerializer.writeInt32(resourceId);
    TouchEvent_serializer::write(argsSerializer, event);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_TouchResult_Void(Ark_Int32 resourceId, Ark_TouchResult value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_TouchResult_Void);
    argsSerializer.writeInt32(resourceId);
    TouchResult_serializer::write(argsSerializer, value);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_TouchResult_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_TouchResult value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_TouchResult_Void);
    argsSerializer.writeInt32(resourceId);
    TouchResult_serializer::write(argsSerializer, value);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_Tuple_I32_I32_I32_I32_Void(Ark_Int32 resourceId, Ark_Tuple_I32_I32_I32_I32 value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Tuple_I32_I32_I32_I32_Void);
    argsSerializer.writeInt32(resourceId);
    const auto value_0 = value.value0;
    argsSerializer.writeInt32(value_0);
    const auto value_1 = value.value1;
    argsSerializer.writeInt32(value_1);
    const auto value_2 = value.value2;
    argsSerializer.writeInt32(value_2);
    const auto value_3 = value.value3;
    argsSerializer.writeInt32(value_3);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_Tuple_I32_I32_I32_I32_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Tuple_I32_I32_I32_I32 value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_Tuple_I32_I32_I32_I32_Void);
    argsSerializer.writeInt32(resourceId);
    const auto value_0 = value.value0;
    argsSerializer.writeInt32(value_0);
    const auto value_1 = value.value1;
    argsSerializer.writeInt32(value_1);
    const auto value_2 = value.value2;
    argsSerializer.writeInt32(value_2);
    const auto value_3 = value.value3;
    argsSerializer.writeInt32(value_3);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_Tuple_I32_I32_Void(Ark_Int32 resourceId, Ark_Tuple_I32_I32 value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Tuple_I32_I32_Void);
    argsSerializer.writeInt32(resourceId);
    const auto value_0 = value.value0;
    argsSerializer.writeInt32(value_0);
    const auto value_1 = value.value1;
    argsSerializer.writeInt32(value_1);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_Tuple_I32_I32_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Tuple_I32_I32 value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_Tuple_I32_I32_Void);
    argsSerializer.writeInt32(resourceId);
    const auto value_0 = value.value0;
    argsSerializer.writeInt32(value_0);
    const auto value_1 = value.value1;
    argsSerializer.writeInt32(value_1);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_UIExtensionProxy_Void(Ark_Int32 resourceId, Ark_UIExtensionProxy value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_UIExtensionProxy_Void);
    argsSerializer.writeInt32(resourceId);
    UIExtensionProxy_serializer::write(argsSerializer, value0);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_UIExtensionProxy_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_UIExtensionProxy value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_UIExtensionProxy_Void);
    argsSerializer.writeInt32(resourceId);
    UIExtensionProxy_serializer::write(argsSerializer, value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_Union_CustomBuilder_DragItemInfo_Void(Ark_Int32 resourceId, Ark_Union_CustomBuilder_DragItemInfo value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Union_CustomBuilder_DragItemInfo_Void);
    argsSerializer.writeInt32(resourceId);
    if (value.selector == 0) {
        argsSerializer.writeInt8(0);
        const auto valueForIdx0 = value.value0;
        argsSerializer.writeCallbackResource(valueForIdx0.resource);
        argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(valueForIdx0.call));
        argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(valueForIdx0.callSync));
    } else if (value.selector == 1) {
        argsSerializer.writeInt8(1);
        const auto valueForIdx1 = value.value1;
        DragItemInfo_serializer::write(argsSerializer, valueForIdx1);
    }
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_Union_CustomBuilder_DragItemInfo_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Union_CustomBuilder_DragItemInfo value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_Union_CustomBuilder_DragItemInfo_Void);
    argsSerializer.writeInt32(resourceId);
    if (value.selector == 0) {
        argsSerializer.writeInt8(0);
        const auto valueForIdx0 = value.value0;
        argsSerializer.writeCallbackResource(valueForIdx0.resource);
        argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(valueForIdx0.call));
        argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(valueForIdx0.callSync));
    } else if (value.selector == 1) {
        argsSerializer.writeInt8(1);
        const auto valueForIdx1 = value.value1;
        DragItemInfo_serializer::write(argsSerializer, valueForIdx1);
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_Union_Object_Idlize_Stdlib_Null_Undefined_Void(Ark_Int32 resourceId, Opt_Object value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Union_Object_Idlize_Stdlib_Null_Undefined_Void);
    argsSerializer.writeInt32(resourceId);
    if (runtimeType(value0) != INTEROP_RUNTIME_UNDEFINED) {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto value0TmpValue = value0.value;
        argsSerializer.writeObject(value0TmpValue);
    } else {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_Union_Object_Idlize_Stdlib_Null_Undefined_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Opt_Object value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_Union_Object_Idlize_Stdlib_Null_Undefined_Void);
    argsSerializer.writeInt32(resourceId);
    if (runtimeType(value0) != INTEROP_RUNTIME_UNDEFINED) {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto value0TmpValue = value0.value;
        argsSerializer.writeObject(value0TmpValue);
    } else {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_VisibilityChangeReason_Void(Ark_Int32 resourceId, Ark_VisibilityChangeReason value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_VisibilityChangeReason_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_VisibilityChangeReason>(value0));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_VisibilityChangeReason_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_VisibilityChangeReason value0)
{
    uint8_t dataBuffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&dataBuffer, sizeof(dataBuffer), nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_VisibilityChangeReason_Void);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_VisibilityChangeReason>(value0));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(dataBuffer), dataBuffer);
}
void callManagedCallback_Void(Ark_Int32 resourceId)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_Void);
    argsSerializer.writeInt32(resourceId);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_Void);
    argsSerializer.writeInt32(resourceId);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCallback_WebKeyboardOptions_Void(Ark_Int32 resourceId, Ark_WebKeyboardOptions value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Callback_WebKeyboardOptions_Void);
    argsSerializer.writeInt32(resourceId);
    WebKeyboardOptions_serializer::write(argsSerializer, value);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCallback_WebKeyboardOptions_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_WebKeyboardOptions value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Callback_WebKeyboardOptions_Void);
    argsSerializer.writeInt32(resourceId);
    WebKeyboardOptions_serializer::write(argsSerializer, value);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCheckBoxGroupModifierBuilder(Ark_Int32 resourceId, Ark_NativePointer parentNode, Ark_CheckBoxGroupConfiguration config, Callback_Pointer_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_CheckBoxGroupModifierBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    CheckBoxGroupConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCheckBoxGroupModifierBuilderSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NativePointer parentNode, Ark_CheckBoxGroupConfiguration config, Callback_Pointer_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_CheckBoxGroupModifierBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    CheckBoxGroupConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedType_WebAttribute_onInterceptRequest(Ark_Int32 resourceId, Ark_OnInterceptRequestEvent value0, Callback_Opt_WebResourceResponse_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Type_WebAttribute_onInterceptRequest);
    argsSerializer.writeInt32(resourceId);
    OnInterceptRequestEvent_serializer::write(argsSerializer, value0);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedType_WebAttribute_onInterceptRequestSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnInterceptRequestEvent value0, Callback_Opt_WebResourceResponse_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Type_WebAttribute_onInterceptRequest);
    argsSerializer.writeInt32(resourceId);
    OnInterceptRequestEvent_serializer::write(argsSerializer, value0);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCheckBoxModifierBuilder(Ark_Int32 resourceId, Ark_NativePointer parentNode, Ark_CheckBoxConfiguration config, Callback_Pointer_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_CheckBoxModifierBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    CheckBoxConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCheckBoxModifierBuilderSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NativePointer parentNode, Ark_CheckBoxConfiguration config, Callback_Pointer_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_CheckBoxModifierBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    CheckBoxConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedContentDidScrollCallback(Ark_Int32 resourceId, Ark_Int32 selectedIndex, Ark_Int32 index, Ark_Float64 position, Ark_Float64 mainAxisLength)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_ContentDidScrollCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(selectedIndex);
    argsSerializer.writeInt32(index);
    argsSerializer.writeFloat64(position);
    argsSerializer.writeFloat64(mainAxisLength);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedContentDidScrollCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 selectedIndex, Ark_Int32 index, Ark_Float64 position, Ark_Float64 mainAxisLength)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_ContentDidScrollCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(selectedIndex);
    argsSerializer.writeInt32(index);
    argsSerializer.writeFloat64(position);
    argsSerializer.writeFloat64(mainAxisLength);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedContentWillScrollCallback(Ark_Int32 resourceId, Ark_SwiperContentWillScrollResult result, Callback_Boolean_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_ContentWillScrollCallback);
    argsSerializer.writeInt32(resourceId);
    SwiperContentWillScrollResult_serializer::write(argsSerializer, result);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedContentWillScrollCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_SwiperContentWillScrollResult result, Callback_Boolean_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_ContentWillScrollCallback);
    argsSerializer.writeInt32(resourceId);
    SwiperContentWillScrollResult_serializer::write(argsSerializer, result);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCustomBuilderT_Arkui_Component_Enums_ResponseType(Ark_Int32 resourceId, Ark_ResponseType t, Ark_NativePointer parentNode, Callback_Pointer_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_CustomBuilderT_Arkui_Component_Enums_ResponseType);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_ResponseType>(t));
    argsSerializer.writePointer(parentNode);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCustomBuilderT_Arkui_Component_Enums_ResponseTypeSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_ResponseType t, Ark_NativePointer parentNode, Callback_Pointer_Void continuation)
{
    uint8_t dataBuffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&dataBuffer, sizeof(dataBuffer), nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_CustomBuilderT_Arkui_Component_Enums_ResponseType);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_ResponseType>(t));
    argsSerializer.writePointer(parentNode);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCustomBuilderT_I32(Ark_Int32 resourceId, Ark_Int32 t)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_CustomBuilderT_I32);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(t);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCustomBuilderT_I32Sync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 t)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_CustomBuilderT_I32);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(t);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedCustomNodeBuilder(Ark_Int32 resourceId, Ark_NativePointer parentNode, Callback_Pointer_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_CustomNodeBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedCustomNodeBuilderSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NativePointer parentNode, Callback_Pointer_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_CustomNodeBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedDataPanelModifierBuilder(Ark_Int32 resourceId, Ark_NativePointer parentNode, Ark_DataPanelConfiguration config, Callback_Pointer_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_DataPanelModifierBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    DataPanelConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedDataPanelModifierBuilderSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NativePointer parentNode, Ark_DataPanelConfiguration config, Callback_Pointer_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_DataPanelModifierBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    DataPanelConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedEditableTextOnChangeCallback(Ark_Int32 resourceId, Ark_String value, Opt_PreviewText previewText, Opt_TextChangeOptions options)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_EditableTextOnChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(value);
    if (runtimeType(previewText) != INTEROP_RUNTIME_UNDEFINED) {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto previewTextTmpValue = previewText.value;
        PreviewText_serializer::write(argsSerializer, previewTextTmpValue);
    } else {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    if (runtimeType(options) != INTEROP_RUNTIME_UNDEFINED) {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto optionsTmpValue = options.value;
        TextChangeOptions_serializer::write(argsSerializer, optionsTmpValue);
    } else {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    enqueueCallback(10, &callbackBuffer);
}
void callManagedEditableTextOnChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_String value, Opt_PreviewText previewText, Opt_TextChangeOptions options)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_EditableTextOnChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(value);
    if (runtimeType(previewText) != INTEROP_RUNTIME_UNDEFINED) {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto previewTextTmpValue = previewText.value;
        PreviewText_serializer::write(argsSerializer, previewTextTmpValue);
    } else {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    if (runtimeType(options) != INTEROP_RUNTIME_UNDEFINED) {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto optionsTmpValue = options.value;
        TextChangeOptions_serializer::write(argsSerializer, optionsTmpValue);
    } else {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedErrorCallback_Ohos_Base_BusinessError(Ark_Int32 resourceId, Ark_BusinessError err)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_ErrorCallback_Ohos_Base_BusinessError);
    argsSerializer.writeInt32(resourceId);
    BusinessError_serializer::write(argsSerializer, err);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedErrorCallback_Ohos_Base_BusinessErrorSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_BusinessError err)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_ErrorCallback_Ohos_Base_BusinessError);
    argsSerializer.writeInt32(resourceId);
    BusinessError_serializer::write(argsSerializer, err);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedGaugeModifierBuilder(Ark_Int32 resourceId, Ark_NativePointer parentNode, Ark_GaugeConfiguration config, Callback_Pointer_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_GaugeModifierBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    GaugeConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedGaugeModifierBuilderSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NativePointer parentNode, Ark_GaugeConfiguration config, Callback_Pointer_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_GaugeModifierBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    GaugeConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedGestureRecognizerJudgeBeginCallback(Ark_Int32 resourceId, Ark_BaseGestureEvent event, Ark_GestureRecognizer current, Array_GestureRecognizer recognizers, Callback_GestureJudgeResult_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_GestureRecognizerJudgeBeginCallback);
    argsSerializer.writeInt32(resourceId);
    BaseGestureEvent_serializer::write(argsSerializer, event);
    GestureRecognizer_serializer::write(argsSerializer, current);
    argsSerializer.writeInt32(recognizers.length);
    for (int recognizersCounterI = 0; recognizersCounterI < recognizers.length; recognizersCounterI++) {
        const Ark_GestureRecognizer recognizersTmpElement = recognizers.array[recognizersCounterI];
        GestureRecognizer_serializer::write(argsSerializer, recognizersTmpElement);
    }
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedGestureRecognizerJudgeBeginCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_BaseGestureEvent event, Ark_GestureRecognizer current, Array_GestureRecognizer recognizers, Callback_GestureJudgeResult_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_GestureRecognizerJudgeBeginCallback);
    argsSerializer.writeInt32(resourceId);
    BaseGestureEvent_serializer::write(argsSerializer, event);
    GestureRecognizer_serializer::write(argsSerializer, current);
    argsSerializer.writeInt32(recognizers.length);
    for (int recognizersCounterI = 0; recognizersCounterI < recognizers.length; recognizersCounterI++) {
        const Ark_GestureRecognizer recognizersTmpElement = recognizers.array[recognizersCounterI];
        GestureRecognizer_serializer::write(argsSerializer, recognizersTmpElement);
    }
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedGetItemMainSizeByIndex(Ark_Int32 resourceId, Ark_Int32 index, Callback_F64_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_GetItemMainSizeByIndex);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedGetItemMainSizeByIndexSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 index, Callback_F64_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_GetItemMainSizeByIndex);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedHoverCallback(Ark_Int32 resourceId, Ark_Boolean isHover, Ark_HoverEvent event)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_HoverCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(isHover);
    HoverEvent_serializer::write(argsSerializer, event);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedHoverCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Boolean isHover, Ark_HoverEvent event)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_HoverCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(isHover);
    HoverEvent_serializer::write(argsSerializer, event);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedImageCompleteCallback(Ark_Int32 resourceId, Ark_ImageLoadResult result)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_ImageCompleteCallback);
    argsSerializer.writeInt32(resourceId);
    ImageLoadResult_serializer::write(argsSerializer, result);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedImageCompleteCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_ImageLoadResult result)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_ImageCompleteCallback);
    argsSerializer.writeInt32(resourceId);
    ImageLoadResult_serializer::write(argsSerializer, result);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedImageErrorCallback(Ark_Int32 resourceId, Ark_ImageError error)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_ImageErrorCallback);
    argsSerializer.writeInt32(resourceId);
    ImageError_serializer::write(argsSerializer, error);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedImageErrorCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_ImageError error)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_ImageErrorCallback);
    argsSerializer.writeInt32(resourceId);
    ImageError_serializer::write(argsSerializer, error);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedImageOnCompleteCallback(Ark_Int32 resourceId, Opt_ImageCompleteEvent loadEvent)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_ImageOnCompleteCallback);
    argsSerializer.writeInt32(resourceId);
    if (runtimeType(loadEvent) != INTEROP_RUNTIME_UNDEFINED) {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto loadEventTmpValue = loadEvent.value;
        ImageCompleteEvent_serializer::write(argsSerializer, loadEventTmpValue);
    } else {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    enqueueCallback(10, &callbackBuffer);
}
void callManagedImageOnCompleteCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Opt_ImageCompleteEvent loadEvent)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_ImageOnCompleteCallback);
    argsSerializer.writeInt32(resourceId);
    if (runtimeType(loadEvent) != INTEROP_RUNTIME_UNDEFINED) {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto loadEventTmpValue = loadEvent.value;
        ImageCompleteEvent_serializer::write(argsSerializer, loadEventTmpValue);
    } else {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedInterceptionModeCallback(Ark_Int32 resourceId, Ark_NavigationMode mode)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_InterceptionModeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_NavigationMode>(mode));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedInterceptionModeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NavigationMode mode)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_InterceptionModeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_NavigationMode>(mode));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedInterceptionShowCallback(Ark_Int32 resourceId, Ark_Union_NavDestinationContext_NavBar from, Ark_Union_NavDestinationContext_NavBar to, Ark_NavigationOperation operation, Ark_Boolean isAnimated)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_InterceptionShowCallback);
    argsSerializer.writeInt32(resourceId);
    if (from.selector == 0) {
        argsSerializer.writeInt8(0);
        const auto fromForIdx0 = from.value0;
        NavDestinationContext_serializer::write(argsSerializer, fromForIdx0);
    } else if (from.selector == 1) {
        argsSerializer.writeInt8(1);
        const auto fromForIdx1 = from.value1;
        argsSerializer.writeString(fromForIdx1);
    }
    if (to.selector == 0) {
        argsSerializer.writeInt8(0);
        const auto toForIdx0 = to.value0;
        NavDestinationContext_serializer::write(argsSerializer, toForIdx0);
    } else if (to.selector == 1) {
        argsSerializer.writeInt8(1);
        const auto toForIdx1 = to.value1;
        argsSerializer.writeString(toForIdx1);
    }
    argsSerializer.writeInt32(static_cast<Ark_NavigationOperation>(operation));
    argsSerializer.writeBoolean(isAnimated);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedInterceptionShowCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Union_NavDestinationContext_NavBar from, Ark_Union_NavDestinationContext_NavBar to, Ark_NavigationOperation operation, Ark_Boolean isAnimated)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_InterceptionShowCallback);
    argsSerializer.writeInt32(resourceId);
    if (from.selector == 0) {
        argsSerializer.writeInt8(0);
        const auto fromForIdx0 = from.value0;
        NavDestinationContext_serializer::write(argsSerializer, fromForIdx0);
    } else if (from.selector == 1) {
        argsSerializer.writeInt8(1);
        const auto fromForIdx1 = from.value1;
        argsSerializer.writeString(fromForIdx1);
    }
    if (to.selector == 0) {
        argsSerializer.writeInt8(0);
        const auto toForIdx0 = to.value0;
        NavDestinationContext_serializer::write(argsSerializer, toForIdx0);
    } else if (to.selector == 1) {
        argsSerializer.writeInt8(1);
        const auto toForIdx1 = to.value1;
        argsSerializer.writeString(toForIdx1);
    }
    argsSerializer.writeInt32(static_cast<Ark_NavigationOperation>(operation));
    argsSerializer.writeBoolean(isAnimated);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedLoadingProgressModifierBuilder(Ark_Int32 resourceId, Ark_NativePointer parentNode, Ark_LoadingProgressConfiguration config, Callback_Pointer_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_LoadingProgressModifierBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    LoadingProgressConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedLoadingProgressModifierBuilderSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NativePointer parentNode, Ark_LoadingProgressConfiguration config, Callback_Pointer_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_LoadingProgressModifierBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    LoadingProgressConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedMenuCallback(Ark_Int32 resourceId, Ark_Int32 start, Ark_Int32 end)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_MenuCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(start);
    argsSerializer.writeInt32(end);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedMenuCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 start, Ark_Int32 end)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_MenuCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(start);
    argsSerializer.writeInt32(end);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedMenuItemModifierBuilder(Ark_Int32 resourceId, Ark_NativePointer parentNode, Ark_MenuItemConfiguration config, Callback_Pointer_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_MenuItemModifierBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    MenuItemConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedMenuItemModifierBuilderSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NativePointer parentNode, Ark_MenuItemConfiguration config, Callback_Pointer_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_MenuItemModifierBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    MenuItemConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedMenuOnAppearCallback(Ark_Int32 resourceId, Ark_Int32 start, Ark_Int32 end)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_MenuOnAppearCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(start);
    argsSerializer.writeInt32(end);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedMenuOnAppearCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 start, Ark_Int32 end)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_MenuOnAppearCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(start);
    argsSerializer.writeInt32(end);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedModifierKeyStateGetter(Ark_Int32 resourceId, Array_String keys, Callback_Boolean_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_ModifierKeyStateGetter);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(keys.length);
    for (int keysCounterI = 0; keysCounterI < keys.length; keysCounterI++) {
        const Ark_String keysTmpElement = keys.array[keysCounterI];
        argsSerializer.writeString(keysTmpElement);
    }
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedModifierKeyStateGetterSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Array_String keys, Callback_Boolean_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_ModifierKeyStateGetter);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(keys.length);
    for (int keysCounterI = 0; keysCounterI < keys.length; keysCounterI++) {
        const Ark_String keysTmpElement = keys.array[keysCounterI];
        argsSerializer.writeString(keysTmpElement);
    }
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedMouseInfoCallback(Ark_Int32 resourceId, Ark_NativeEmbedMouseInfo event)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_MouseInfoCallback);
    argsSerializer.writeInt32(resourceId);
    NativeEmbedMouseInfo_serializer::write(argsSerializer, event);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedMouseInfoCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NativeEmbedMouseInfo event)
{
    uint8_t dataBuffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&dataBuffer, sizeof(dataBuffer), nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_MouseInfoCallback);
    argsSerializer.writeInt32(resourceId);
    NativeEmbedMouseInfo_serializer::write(argsSerializer, event);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(dataBuffer), dataBuffer);
}
void callManagedNavDestinationTransitionDelegate(Ark_Int32 resourceId, Ark_NavigationOperation operation, Ark_Boolean isEnter, Callback_Opt_Array_NavDestinationTransition_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_NavDestinationTransitionDelegate);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_NavigationOperation>(operation));
    argsSerializer.writeBoolean(isEnter);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedNavDestinationTransitionDelegateSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NavigationOperation operation, Ark_Boolean isEnter, Callback_Opt_Array_NavDestinationTransition_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_NavDestinationTransitionDelegate);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_NavigationOperation>(operation));
    argsSerializer.writeBoolean(isEnter);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedNavExtender_CreateNavDestination(Ark_Int32 resourceId, Ark_Int32 index, Callback_Pointer_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_NavExtender_CreateNavDestination);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedNavExtender_CreateNavDestinationSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 index, Callback_Pointer_Void continuation)
{
    uint8_t dataBuffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&dataBuffer, sizeof(dataBuffer), nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_NavExtender_CreateNavDestination);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(dataBuffer), dataBuffer);
}
void callManagedNavExtender_OnUpdateStack(Ark_Int32 resourceId)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_NavExtender_OnUpdateStack);
    argsSerializer.writeInt32(resourceId);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedNavExtender_OnUpdateStackSync(Ark_VMContext vmContext, Ark_Int32 resourceId)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_NavExtender_OnUpdateStack);
    argsSerializer.writeInt32(resourceId);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedNavExtender_PageMapNodeBuilder(Ark_Int32 resourceId, Ark_String url, Opt_Object params, Callback_Pointer_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_NavExtender_PageMapNodeBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(url);
    if (runtimeType(params) != INTEROP_RUNTIME_UNDEFINED) {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto paramsTmpValue = params.value;
        argsSerializer.writeObject(paramsTmpValue);
    } else {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}

void callManagedNavExtender_PageMapNodeBuilderSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_String url, Opt_Object params, Callback_Pointer_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_NavExtender_PageMapNodeBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(url);
    if (runtimeType(params) != INTEROP_RUNTIME_UNDEFINED) {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto paramsTmpValue = params.value;
        argsSerializer.writeObject(paramsTmpValue);
    } else {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedOnAdsBlockedCallback(Ark_Int32 resourceId, Ark_AdsBlockedDetails details)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnAdsBlockedCallback);
    argsSerializer.writeInt32(resourceId);
    AdsBlockedDetails_serializer::write(argsSerializer, details);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedOnAdsBlockedCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_AdsBlockedDetails details)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_OnAdsBlockedCallback);
    argsSerializer.writeInt32(resourceId);
    AdsBlockedDetails_serializer::write(argsSerializer, details);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedOnAlphabetIndexerPopupSelectCallback(Ark_Int32 resourceId, Ark_Int32 index)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnAlphabetIndexerPopupSelectCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedOnAlphabetIndexerPopupSelectCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 index)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_OnAlphabetIndexerPopupSelectCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedOnAlphabetIndexerRequestPopupDataCallback(Ark_Int32 resourceId, Ark_Int32 index, Callback_Array_String_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnAlphabetIndexerRequestPopupDataCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedOnAlphabetIndexerRequestPopupDataCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 index, Callback_Array_String_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_OnAlphabetIndexerRequestPopupDataCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedOnAlphabetIndexerSelectCallback(Ark_Int32 resourceId, Ark_Int32 index)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnAlphabetIndexerSelectCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedOnAlphabetIndexerSelectCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 index)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_OnAlphabetIndexerSelectCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedOnCheckboxChangeCallback(Ark_Int32 resourceId, Ark_Boolean value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnCheckboxChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(value);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedOnCheckboxChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Boolean value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_OnCheckboxChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(value);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedOnCheckboxGroupChangeCallback(Ark_Int32 resourceId, Ark_CheckboxGroupResult value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnCheckboxGroupChangeCallback);
    argsSerializer.writeInt32(resourceId);
    CheckboxGroupResult_serializer::write(argsSerializer, value);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedOnCheckboxGroupChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_CheckboxGroupResult value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_OnCheckboxGroupChangeCallback);
    argsSerializer.writeInt32(resourceId);
    CheckboxGroupResult_serializer::write(argsSerializer, value);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedOnContentScrollCallback(Ark_Int32 resourceId, Ark_Float64 totalOffsetX, Ark_Float64 totalOffsetY)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnContentScrollCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFloat64(totalOffsetX);
    argsSerializer.writeFloat64(totalOffsetY);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedOnContentScrollCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Float64 totalOffsetX, Ark_Float64 totalOffsetY)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_OnContentScrollCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFloat64(totalOffsetX);
    argsSerializer.writeFloat64(totalOffsetY);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedOnContextMenuHideCallback(Ark_Int32 resourceId)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnContextMenuHideCallback);
    argsSerializer.writeInt32(resourceId);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedOnContextMenuHideCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_OnContextMenuHideCallback);
    argsSerializer.writeInt32(resourceId);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedOnCreateMenuCallback(Ark_Int32 resourceId, Array_TextMenuItem menuItems, Callback_Array_TextMenuItem_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnCreateMenuCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(menuItems.length);
    for (int menuItemsCounterI = 0; menuItemsCounterI < menuItems.length; menuItemsCounterI++) {
        const Ark_TextMenuItem menuItemsTmpElement = menuItems.array[menuItemsCounterI];
        TextMenuItem_serializer::write(argsSerializer, menuItemsTmpElement);
    }
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedOnCreateMenuCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Array_TextMenuItem menuItems, Callback_Array_TextMenuItem_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_OnCreateMenuCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(menuItems.length);
    for (int menuItemsCounterI = 0; menuItemsCounterI < menuItems.length; menuItemsCounterI++) {
        const Ark_TextMenuItem menuItemsTmpElement = menuItems.array[menuItemsCounterI];
        TextMenuItem_serializer::write(argsSerializer, menuItemsTmpElement);
    }
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedOnDetectBlankScreenCallback(Ark_Int32 resourceId, Ark_BlankScreenDetectionEventInfo event)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnDetectBlankScreenCallback);
    argsSerializer.writeInt32(resourceId);
    BlankScreenDetectionEventInfo_serializer::write(argsSerializer, event);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedOnDetectBlankScreenCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_BlankScreenDetectionEventInfo event)
{
    uint8_t dataBuffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&dataBuffer, sizeof(dataBuffer), nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_OnDetectBlankScreenCallback);
    argsSerializer.writeInt32(resourceId);
    BlankScreenDetectionEventInfo_serializer::write(argsSerializer, event);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(dataBuffer), dataBuffer);
}
void callManagedOnDidChangeCallback(Ark_Int32 resourceId, Ark_TextRange rangeBefore, Ark_TextRange rangeAfter)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnDidChangeCallback);
    argsSerializer.writeInt32(resourceId);
    TextRange_serializer::write(argsSerializer, rangeBefore);
    TextRange_serializer::write(argsSerializer, rangeAfter);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedOnDidChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_TextRange rangeBefore, Ark_TextRange rangeAfter)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_OnDidChangeCallback);
    argsSerializer.writeInt32(resourceId);
    TextRange_serializer::write(argsSerializer, rangeBefore);
    TextRange_serializer::write(argsSerializer, rangeAfter);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedOnDragEventCallback(Ark_Int32 resourceId, Ark_DragEvent event, Opt_String extraParams)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnDragEventCallback);
    argsSerializer.writeInt32(resourceId);
    DragEvent_serializer::write(argsSerializer, event);
    if (runtimeType(extraParams) != INTEROP_RUNTIME_UNDEFINED) {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto extraParamsTmpValue = extraParams.value;
        argsSerializer.writeString(extraParamsTmpValue);
    } else {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    enqueueCallback(10, &callbackBuffer);
}
void callManagedOnDragEventCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_DragEvent event, Opt_String extraParams)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_OnDragEventCallback);
    argsSerializer.writeInt32(resourceId);
    DragEvent_serializer::write(argsSerializer, event);
    if (runtimeType(extraParams) != INTEROP_RUNTIME_UNDEFINED) {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto extraParamsTmpValue = extraParams.value;
        argsSerializer.writeString(extraParamsTmpValue);
    } else {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedOnFirstMeaningfulPaintCallback(Ark_Int32 resourceId, Ark_FirstMeaningfulPaint firstMeaningfulPaint)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnFirstMeaningfulPaintCallback);
    argsSerializer.writeInt32(resourceId);
    FirstMeaningfulPaint_serializer::write(argsSerializer, firstMeaningfulPaint);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedOnFirstMeaningfulPaintCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_FirstMeaningfulPaint firstMeaningfulPaint)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_OnFirstMeaningfulPaintCallback);
    argsSerializer.writeInt32(resourceId);
    FirstMeaningfulPaint_serializer::write(argsSerializer, firstMeaningfulPaint);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedOnFoldStatusChangeCallback(Ark_Int32 resourceId, Ark_OnFoldStatusChangeInfo event)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnFoldStatusChangeCallback);
    argsSerializer.writeInt32(resourceId);
    OnFoldStatusChangeInfo_serializer::write(argsSerializer, event);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedOnFoldStatusChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnFoldStatusChangeInfo event)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_OnFoldStatusChangeCallback);
    argsSerializer.writeInt32(resourceId);
    OnFoldStatusChangeInfo_serializer::write(argsSerializer, event);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedOnFullScreenEnterCallback(Ark_Int32 resourceId, Ark_FullScreenEnterEvent event)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnFullScreenEnterCallback);
    argsSerializer.writeInt32(resourceId);
    FullScreenEnterEvent_serializer::write(argsSerializer, event);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedOnFullScreenEnterCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_FullScreenEnterEvent event)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_OnFullScreenEnterCallback);
    argsSerializer.writeInt32(resourceId);
    FullScreenEnterEvent_serializer::write(argsSerializer, event);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedOnHoverCallback(Ark_Int32 resourceId, Ark_Boolean status, Ark_HoverEvent event)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnHoverCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(status);
    HoverEvent_serializer::write(argsSerializer, event);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedOnHoverCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Boolean status, Ark_HoverEvent event)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_OnHoverCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(status);
    HoverEvent_serializer::write(argsSerializer, event);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedOnHoverStatusChangeCallback(Ark_Int32 resourceId, Ark_HoverEventParam param)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnHoverStatusChangeCallback);
    argsSerializer.writeInt32(resourceId);
    HoverEventParam_serializer::write(argsSerializer, param);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedOnHoverStatusChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_HoverEventParam param)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_OnHoverStatusChangeCallback);
    argsSerializer.writeInt32(resourceId);
    HoverEventParam_serializer::write(argsSerializer, param);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedOnIntelligentTrackingPreventionCallback(Ark_Int32 resourceId, Ark_IntelligentTrackingPreventionDetails details)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnIntelligentTrackingPreventionCallback);
    argsSerializer.writeInt32(resourceId);
    IntelligentTrackingPreventionDetails_serializer::write(argsSerializer, details);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedOnIntelligentTrackingPreventionCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_IntelligentTrackingPreventionDetails details)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_OnIntelligentTrackingPreventionCallback);
    argsSerializer.writeInt32(resourceId);
    IntelligentTrackingPreventionDetails_serializer::write(argsSerializer, details);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedOnItemDragStartCallback(Ark_Int32 resourceId, Ark_ItemDragInfo event, Ark_Int32 itemIndex, Callback_Opt_CustomBuilder_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnItemDragStartCallback);
    argsSerializer.writeInt32(resourceId);
    ItemDragInfo_serializer::write(argsSerializer, event);
    argsSerializer.writeInt32(itemIndex);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedOnItemDragStartCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_ItemDragInfo event, Ark_Int32 itemIndex, Callback_Opt_CustomBuilder_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_OnItemDragStartCallback);
    argsSerializer.writeInt32(resourceId);
    ItemDragInfo_serializer::write(argsSerializer, event);
    argsSerializer.writeInt32(itemIndex);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedOnLargestContentfulPaintCallback(Ark_Int32 resourceId, Ark_LargestContentfulPaint largestContentfulPaint)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnLargestContentfulPaintCallback);
    argsSerializer.writeInt32(resourceId);
    LargestContentfulPaint_serializer::write(argsSerializer, largestContentfulPaint);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedOnLargestContentfulPaintCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_LargestContentfulPaint largestContentfulPaint)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_OnLargestContentfulPaintCallback);
    argsSerializer.writeInt32(resourceId);
    LargestContentfulPaint_serializer::write(argsSerializer, largestContentfulPaint);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedOnLinearIndicatorChangeCallback(Ark_Int32 resourceId, Ark_Number index, Ark_Number progress)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnLinearIndicatorChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(index);
    argsSerializer.writeNumber(progress);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedOnLinearIndicatorChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number index, Ark_Number progress)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_OnLinearIndicatorChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(index);
    argsSerializer.writeNumber(progress);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedOnMenuItemClickCallback(Ark_Int32 resourceId, Ark_TextMenuItem menuItem, Ark_TextRange range, Callback_Boolean_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnMenuItemClickCallback);
    argsSerializer.writeInt32(resourceId);
    TextMenuItem_serializer::write(argsSerializer, menuItem);
    TextRange_serializer::write(argsSerializer, range);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedOnMenuItemClickCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_TextMenuItem menuItem, Ark_TextRange range, Callback_Boolean_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_OnMenuItemClickCallback);
    argsSerializer.writeInt32(resourceId);
    TextMenuItem_serializer::write(argsSerializer, menuItem);
    TextRange_serializer::write(argsSerializer, range);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedOnMoveHandler(Ark_Int32 resourceId, Ark_Int32 from, Ark_Int32 to)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnMoveHandler);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(from);
    argsSerializer.writeInt32(to);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedOnMoveHandlerSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 from, Ark_Int32 to)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_OnMoveHandler);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(from);
    argsSerializer.writeInt32(to);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedOnNativeEmbedObjectParamChangeCallback(Ark_Int32 resourceId, Ark_NativeEmbedParamDataInfo event)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnNativeEmbedObjectParamChangeCallback);
    argsSerializer.writeInt32(resourceId);
    NativeEmbedParamDataInfo_serializer::write(argsSerializer, event);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedOnNativeEmbedObjectParamChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NativeEmbedParamDataInfo event)
{
    uint8_t dataBuffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&dataBuffer, sizeof(dataBuffer), nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_OnNativeEmbedObjectParamChangeCallback);
    argsSerializer.writeInt32(resourceId);
    NativeEmbedParamDataInfo_serializer::write(argsSerializer, event);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(dataBuffer), dataBuffer);
}
void callManagedOnNativeEmbedVisibilityChangeCallback(Ark_Int32 resourceId, Ark_NativeEmbedVisibilityInfo nativeEmbedVisibilityInfo)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnNativeEmbedVisibilityChangeCallback);
    argsSerializer.writeInt32(resourceId);
    NativeEmbedVisibilityInfo_serializer::write(argsSerializer, nativeEmbedVisibilityInfo);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedOnNativeEmbedVisibilityChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NativeEmbedVisibilityInfo nativeEmbedVisibilityInfo)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_OnNativeEmbedVisibilityChangeCallback);
    argsSerializer.writeInt32(resourceId);
    NativeEmbedVisibilityInfo_serializer::write(argsSerializer, nativeEmbedVisibilityInfo);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedOnNavigationEntryCommittedCallback(Ark_Int32 resourceId, Ark_LoadCommittedDetails loadCommittedDetails)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnNavigationEntryCommittedCallback);
    argsSerializer.writeInt32(resourceId);
    LoadCommittedDetails_serializer::write(argsSerializer, loadCommittedDetails);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedOnNavigationEntryCommittedCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_LoadCommittedDetails loadCommittedDetails)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_OnNavigationEntryCommittedCallback);
    argsSerializer.writeInt32(resourceId);
    LoadCommittedDetails_serializer::write(argsSerializer, loadCommittedDetails);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedOnOverrideErrorPageCallback(Ark_Int32 resourceId, Ark_OnErrorReceiveEvent errorPageEvent, Callback_String_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnOverrideErrorPageCallback);
    argsSerializer.writeInt32(resourceId);
    OnErrorReceiveEvent_serializer::write(argsSerializer, errorPageEvent);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedOnOverrideErrorPageCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnErrorReceiveEvent errorPageEvent, Callback_String_Void continuation)
{
    uint8_t dataBuffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&dataBuffer, sizeof(dataBuffer), nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_OnOverrideErrorPageCallback);
    argsSerializer.writeInt32(resourceId);
    OnErrorReceiveEvent_serializer::write(argsSerializer, errorPageEvent);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(dataBuffer), dataBuffer);
}
void callManagedOnOverrideUrlLoadingCallback(Ark_Int32 resourceId, Ark_WebResourceRequest webResourceRequest, Callback_Boolean_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnOverrideUrlLoadingCallback);
    argsSerializer.writeInt32(resourceId);
    WebResourceRequest_serializer::write(argsSerializer, webResourceRequest);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedOnOverrideUrlLoadingCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_WebResourceRequest webResourceRequest, Callback_Boolean_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_OnOverrideUrlLoadingCallback);
    argsSerializer.writeInt32(resourceId);
    WebResourceRequest_serializer::write(argsSerializer, webResourceRequest);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedOnPasteCallback(Ark_Int32 resourceId, Ark_String content, Ark_PasteEvent event)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnPasteCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(content);
    PasteEvent_serializer::write(argsSerializer, event);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedOnPasteCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_String content, Ark_PasteEvent event)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_OnPasteCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(content);
    PasteEvent_serializer::write(argsSerializer, event);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedOnPickerCallback(Ark_Int32 resourceId, Ark_Int32 selectedIndex)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnPickerCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(selectedIndex);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedOnPickerCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 selectedIndex)
{
    uint8_t dataBuffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&dataBuffer, sizeof(dataBuffer), nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_OnPickerCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(selectedIndex);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(dataBuffer), dataBuffer);
}
void callManagedOnRadioChangeCallback(Ark_Int32 resourceId, Ark_Boolean isChecked)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnRadioChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(isChecked);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedOnRadioChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Boolean isChecked)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_OnRadioChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(isChecked);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedOnRatingChangeCallback(Ark_Int32 resourceId, Ark_Float64 rating)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnRatingChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFloat64(rating);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedOnRatingChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Float64 rating)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_OnRatingChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFloat64(rating);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedOnRenderProcessNotRespondingCallback(Ark_Int32 resourceId, Ark_RenderProcessNotRespondingData data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnRenderProcessNotRespondingCallback);
    argsSerializer.writeInt32(resourceId);
    RenderProcessNotRespondingData_serializer::write(argsSerializer, data);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedOnRenderProcessNotRespondingCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_RenderProcessNotRespondingData data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_OnRenderProcessNotRespondingCallback);
    argsSerializer.writeInt32(resourceId);
    RenderProcessNotRespondingData_serializer::write(argsSerializer, data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedOnRenderProcessRespondingCallback(Ark_Int32 resourceId)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnRenderProcessRespondingCallback);
    argsSerializer.writeInt32(resourceId);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedOnRenderProcessRespondingCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_OnRenderProcessRespondingCallback);
    argsSerializer.writeInt32(resourceId);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedOnSafeBrowsingCheckResultCallback(Ark_Int32 resourceId, Ark_ThreatType threatType)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnSafeBrowsingCheckResultCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_ThreatType>(threatType));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedOnSafeBrowsingCheckResultCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_ThreatType threatType)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_OnSafeBrowsingCheckResultCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_ThreatType>(threatType));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedOnScrollCallback(Ark_Int32 resourceId, Ark_Float64 scrollOffset, Ark_ScrollState scrollState)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnScrollCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFloat64(scrollOffset);
    argsSerializer.writeInt32(static_cast<Ark_ScrollState>(scrollState));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedOnScrollCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Float64 scrollOffset, Ark_ScrollState scrollState)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_OnScrollCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFloat64(scrollOffset);
    argsSerializer.writeInt32(static_cast<Ark_ScrollState>(scrollState));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedOnScrollEdgeCallback(Ark_Int32 resourceId, Ark_Edge side)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnScrollEdgeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_Edge>(side));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedOnScrollEdgeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Edge side)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_OnScrollEdgeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_Edge>(side));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedOnScrollFrameBeginCallback(Ark_Int32 resourceId, Ark_Float64 offset, Ark_ScrollState state, Callback_OnScrollFrameBeginHandlerResult_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnScrollFrameBeginCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFloat64(offset);
    argsSerializer.writeInt32(static_cast<Ark_ScrollState>(state));
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedOnScrollFrameBeginCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Float64 offset, Ark_ScrollState state, Callback_OnScrollFrameBeginHandlerResult_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_OnScrollFrameBeginCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFloat64(offset);
    argsSerializer.writeInt32(static_cast<Ark_ScrollState>(state));
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedOnScrollVisibleContentChangeCallback(Ark_Int32 resourceId, Ark_VisibleListContentInfo start, Ark_VisibleListContentInfo end)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnScrollVisibleContentChangeCallback);
    argsSerializer.writeInt32(resourceId);
    VisibleListContentInfo_serializer::write(argsSerializer, start);
    VisibleListContentInfo_serializer::write(argsSerializer, end);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedOnScrollVisibleContentChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_VisibleListContentInfo start, Ark_VisibleListContentInfo end)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_OnScrollVisibleContentChangeCallback);
    argsSerializer.writeInt32(resourceId);
    VisibleListContentInfo_serializer::write(argsSerializer, start);
    VisibleListContentInfo_serializer::write(argsSerializer, end);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedOnSelectCallback(Ark_Int32 resourceId, Ark_Int32 index, Ark_String selectStr)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnSelectCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    argsSerializer.writeString(selectStr);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedOnSelectCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 index, Ark_String selectStr)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_OnSelectCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    argsSerializer.writeString(selectStr);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedOnSslErrorEventCallback(Ark_Int32 resourceId, Ark_SslErrorEvent sslErrorEvent)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnSslErrorEventCallback);
    argsSerializer.writeInt32(resourceId);
    SslErrorEvent_serializer::write(argsSerializer, sslErrorEvent);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedOnSslErrorEventCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_SslErrorEvent sslErrorEvent)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_OnSslErrorEventCallback);
    argsSerializer.writeInt32(resourceId);
    SslErrorEvent_serializer::write(argsSerializer, sslErrorEvent);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedOnSubmitCallback(Ark_Int32 resourceId, Ark_EnterKeyType enterKey, Ark_SubmitEvent event)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnSubmitCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_EnterKeyType>(enterKey));
    SubmitEvent_serializer::write(argsSerializer, event);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedOnSubmitCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_EnterKeyType enterKey, Ark_SubmitEvent event)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_OnSubmitCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_EnterKeyType>(enterKey));
    SubmitEvent_serializer::write(argsSerializer, event);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedOnSwiperAnimationEndCallback(Ark_Int32 resourceId, Ark_Int32 index, Ark_SwiperAnimationEvent extraInfo)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnSwiperAnimationEndCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    SwiperAnimationEvent_serializer::write(argsSerializer, extraInfo);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedOnSwiperAnimationEndCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 index, Ark_SwiperAnimationEvent extraInfo)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_OnSwiperAnimationEndCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    SwiperAnimationEvent_serializer::write(argsSerializer, extraInfo);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedOnSwiperAnimationStartCallback(Ark_Int32 resourceId, Ark_Int32 index, Ark_Int32 targetIndex, Ark_SwiperAnimationEvent extraInfo)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnSwiperAnimationStartCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    argsSerializer.writeInt32(targetIndex);
    SwiperAnimationEvent_serializer::write(argsSerializer, extraInfo);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedOnSwiperAnimationStartCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 index, Ark_Int32 targetIndex, Ark_SwiperAnimationEvent extraInfo)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_OnSwiperAnimationStartCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    argsSerializer.writeInt32(targetIndex);
    SwiperAnimationEvent_serializer::write(argsSerializer, extraInfo);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedOnSwiperGestureSwipeCallback(Ark_Int32 resourceId, Ark_Int32 index, Ark_SwiperAnimationEvent extraInfo)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnSwiperGestureSwipeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    SwiperAnimationEvent_serializer::write(argsSerializer, extraInfo);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedOnSwiperGestureSwipeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 index, Ark_SwiperAnimationEvent extraInfo)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_OnSwiperGestureSwipeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    SwiperAnimationEvent_serializer::write(argsSerializer, extraInfo);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedOnTabsAnimationEndCallback(Ark_Int32 resourceId, Ark_Int32 index, Ark_TabsAnimationEvent extraInfo)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnTabsAnimationEndCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    TabsAnimationEvent_serializer::write(argsSerializer, extraInfo);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedOnTabsAnimationEndCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 index, Ark_TabsAnimationEvent extraInfo)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_OnTabsAnimationEndCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    TabsAnimationEvent_serializer::write(argsSerializer, extraInfo);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedOnTabsAnimationStartCallback(Ark_Int32 resourceId, Ark_Int32 index, Ark_Int32 targetIndex, Ark_TabsAnimationEvent extraInfo)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnTabsAnimationStartCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    argsSerializer.writeInt32(targetIndex);
    TabsAnimationEvent_serializer::write(argsSerializer, extraInfo);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedOnTabsAnimationStartCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 index, Ark_Int32 targetIndex, Ark_TabsAnimationEvent extraInfo)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_OnTabsAnimationStartCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    argsSerializer.writeInt32(targetIndex);
    TabsAnimationEvent_serializer::write(argsSerializer, extraInfo);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedOnTabsContentDidScrollCallback(Ark_Int32 resourceId, Ark_Int32 selectedIndex, Ark_Int32 index, Ark_Float64 position, Ark_Float64 mainAxisLength)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnTabsContentDidScrollCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(selectedIndex);
    argsSerializer.writeInt32(index);
    argsSerializer.writeFloat64(position);
    argsSerializer.writeFloat64(mainAxisLength);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedOnTabsContentDidScrollCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 selectedIndex, Ark_Int32 index, Ark_Float64 position, Ark_Float64 mainAxisLength)
{
    uint8_t dataBuffer[4096];
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&dataBuffer, sizeof(dataBuffer), nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_OnTabsContentDidScrollCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(selectedIndex);
    argsSerializer.writeInt32(index);
    argsSerializer.writeFloat64(position);
    argsSerializer.writeFloat64(mainAxisLength);
    KOALA_INTEROP_CALL_VOID(vmContext, 1, sizeof(dataBuffer), dataBuffer);
}
void callManagedOnTabsContentWillChangeCallback(Ark_Int32 resourceId, Ark_Int32 currentIndex, Ark_Int32 comingIndex, Callback_Boolean_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnTabsContentWillChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(currentIndex);
    argsSerializer.writeInt32(comingIndex);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedOnTabsContentWillChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 currentIndex, Ark_Int32 comingIndex, Callback_Boolean_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_OnTabsContentWillChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(currentIndex);
    argsSerializer.writeInt32(comingIndex);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedOnTabsGestureSwipeCallback(Ark_Int32 resourceId, Ark_Int32 index, Ark_TabsAnimationEvent extraInfo)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnTabsGestureSwipeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    TabsAnimationEvent_serializer::write(argsSerializer, extraInfo);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedOnTabsGestureSwipeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 index, Ark_TabsAnimationEvent extraInfo)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_OnTabsGestureSwipeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    TabsAnimationEvent_serializer::write(argsSerializer, extraInfo);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedOnTextPickerChangeCallback(Ark_Int32 resourceId, Ark_Union_String_Array_String selectItem, Ark_Union_I32_Array_I32 index)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnTextPickerChangeCallback);
    argsSerializer.writeInt32(resourceId);
    if (selectItem.selector == 0) {
        argsSerializer.writeInt8(0);
        const auto selectItemForIdx0 = selectItem.value0;
        argsSerializer.writeString(selectItemForIdx0);
    } else if (selectItem.selector == 1) {
        argsSerializer.writeInt8(1);
        const auto selectItemForIdx1 = selectItem.value1;
        argsSerializer.writeInt32(selectItemForIdx1.length);
        for (int selectItemForIdx1CounterI = 0; selectItemForIdx1CounterI < selectItemForIdx1.length; selectItemForIdx1CounterI++) {
            const Ark_String selectItemForIdx1TmpElement = selectItemForIdx1.array[selectItemForIdx1CounterI];
            argsSerializer.writeString(selectItemForIdx1TmpElement);
        }
    }
    if (index.selector == 0) {
        argsSerializer.writeInt8(0);
        const auto indexForIdx0 = index.value0;
        argsSerializer.writeInt32(indexForIdx0);
    } else if (index.selector == 1) {
        argsSerializer.writeInt8(1);
        const auto indexForIdx1 = index.value1;
        argsSerializer.writeInt32(indexForIdx1.length);
        for (int indexForIdx1CounterI = 0; indexForIdx1CounterI < indexForIdx1.length; indexForIdx1CounterI++) {
            const Ark_Int32 indexForIdx1TmpElement = indexForIdx1.array[indexForIdx1CounterI];
            argsSerializer.writeInt32(indexForIdx1TmpElement);
        }
    }
    enqueueCallback(10, &callbackBuffer);
}
void callManagedOnTextPickerChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Union_String_Array_String selectItem, Ark_Union_I32_Array_I32 index)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_OnTextPickerChangeCallback);
    argsSerializer.writeInt32(resourceId);
    if (selectItem.selector == 0) {
        argsSerializer.writeInt8(0);
        const auto selectItemForIdx0 = selectItem.value0;
        argsSerializer.writeString(selectItemForIdx0);
    } else if (selectItem.selector == 1) {
        argsSerializer.writeInt8(1);
        const auto selectItemForIdx1 = selectItem.value1;
        argsSerializer.writeInt32(selectItemForIdx1.length);
        for (int selectItemForIdx1CounterI = 0; selectItemForIdx1CounterI < selectItemForIdx1.length; selectItemForIdx1CounterI++) {
            const Ark_String selectItemForIdx1TmpElement = selectItemForIdx1.array[selectItemForIdx1CounterI];
            argsSerializer.writeString(selectItemForIdx1TmpElement);
        }
    }
    if (index.selector == 0) {
        argsSerializer.writeInt8(0);
        const auto indexForIdx0 = index.value0;
        argsSerializer.writeInt32(indexForIdx0);
    } else if (index.selector == 1) {
        argsSerializer.writeInt8(1);
        const auto indexForIdx1 = index.value1;
        argsSerializer.writeInt32(indexForIdx1.length);
        for (int indexForIdx1CounterI = 0; indexForIdx1CounterI < indexForIdx1.length; indexForIdx1CounterI++) {
            const Ark_Int32 indexForIdx1TmpElement = indexForIdx1.array[indexForIdx1CounterI];
            argsSerializer.writeInt32(indexForIdx1TmpElement);
        }
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedOnTextSelectionChangeCallback(Ark_Int32 resourceId, Ark_Int32 selectionStart, Ark_Int32 selectionEnd)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnTextSelectionChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(selectionStart);
    argsSerializer.writeInt32(selectionEnd);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedOnTextSelectionChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 selectionStart, Ark_Int32 selectionEnd)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_OnTextSelectionChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(selectionStart);
    argsSerializer.writeInt32(selectionEnd);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedOnTimePickerChangeCallback(Ark_Int32 resourceId, Ark_TimePickerResult result)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnTimePickerChangeCallback);
    argsSerializer.writeInt32(resourceId);
    TimePickerResult_serializer::write(argsSerializer, result);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedOnTimePickerChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_TimePickerResult result)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_OnTimePickerChangeCallback);
    argsSerializer.writeInt32(resourceId);
    TimePickerResult_serializer::write(argsSerializer, result);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedOnViewportFitChangedCallback(Ark_Int32 resourceId, Ark_ViewportFit viewportFit)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnViewportFitChangedCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_ViewportFit>(viewportFit));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedOnViewportFitChangedCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_ViewportFit viewportFit)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_OnViewportFitChangedCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_ViewportFit>(viewportFit));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedOnWillScrollCallback(Ark_Int32 resourceId, Ark_Float64 scrollOffset, Ark_ScrollState scrollState, Ark_ScrollSource scrollSource, Callback_Opt_ScrollResult_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_OnWillScrollCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFloat64(scrollOffset);
    argsSerializer.writeInt32(static_cast<Ark_ScrollState>(scrollState));
    argsSerializer.writeInt32(static_cast<Ark_ScrollSource>(scrollSource));
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedOnWillScrollCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Float64 scrollOffset, Ark_ScrollState scrollState, Ark_ScrollSource scrollSource, Callback_Opt_ScrollResult_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_OnWillScrollCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFloat64(scrollOffset);
    argsSerializer.writeInt32(static_cast<Ark_ScrollState>(scrollState));
    argsSerializer.writeInt32(static_cast<Ark_ScrollSource>(scrollSource));
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedPageMapBuilder(Ark_Int32 resourceId, Ark_String name, Opt_Object param)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_PageMapBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(name);
    if (runtimeType(param) != INTEROP_RUNTIME_UNDEFINED) {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto paramTmpValue = param.value;
        argsSerializer.writeObject(paramTmpValue);
    } else {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    enqueueCallback(10, &callbackBuffer);
}
void callManagedPageMapBuilderSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_String name, Opt_Object param)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_PageMapBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(name);
    if (runtimeType(param) != INTEROP_RUNTIME_UNDEFINED) {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto paramTmpValue = param.value;
        argsSerializer.writeObject(paramTmpValue);
    } else {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedPageTransitionCallback(Ark_Int32 resourceId, Ark_RouteType type, Ark_Float64 progress)
{
    CallbackBuffer callbackBuffer = { {}, {} };
    const Ark_CallbackResource callbackResourceSelf = { resourceId, holdManagedCallbackResource,
        releaseManagedCallbackResource };
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase(
        (KSerializerBuffer) & (callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_PageTransitionCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_RouteType>(type));
    argsSerializer.writeFloat64(progress);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedPageTransitionCallbackSync(
    Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_RouteType type, Ark_Float64 progress)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_PageTransitionCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_RouteType>(type));
    argsSerializer.writeFloat64(progress);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedPasteButtonCallback(Ark_Int32 resourceId, Ark_ClickEvent event, Ark_PasteButtonOnClickResult result, Opt_BusinessError error)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_PasteButtonCallback);
    argsSerializer.writeInt32(resourceId);
    ClickEvent_serializer::write(argsSerializer, event);
    argsSerializer.writeInt32(static_cast<Ark_PasteButtonOnClickResult>(result));
    if (runtimeType(error) != INTEROP_RUNTIME_UNDEFINED) {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto errorTmpValue = error.value;
        BusinessError_serializer::write(argsSerializer, errorTmpValue);
    } else {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    enqueueCallback(10, &callbackBuffer);
}
void callManagedPasteButtonCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_ClickEvent event, Ark_PasteButtonOnClickResult result, Opt_BusinessError error)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_PasteButtonCallback);
    argsSerializer.writeInt32(resourceId);
    ClickEvent_serializer::write(argsSerializer, event);
    argsSerializer.writeInt32(static_cast<Ark_PasteButtonOnClickResult>(result));
    if (runtimeType(error) != INTEROP_RUNTIME_UNDEFINED) {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto errorTmpValue = error.value;
        BusinessError_serializer::write(argsSerializer, errorTmpValue);
    } else {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedPasteEventCallback(Ark_Int32 resourceId, Opt_PasteEvent event)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_PasteEventCallback);
    argsSerializer.writeInt32(resourceId);
    if (runtimeType(event) != INTEROP_RUNTIME_UNDEFINED) {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto eventTmpValue = event.value;
        PasteEvent_serializer::write(argsSerializer, eventTmpValue);
    } else {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    enqueueCallback(10, &callbackBuffer);
}
void callManagedPasteEventCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Opt_PasteEvent event)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_PasteEventCallback);
    argsSerializer.writeInt32(resourceId);
    if (runtimeType(event) != INTEROP_RUNTIME_UNDEFINED) {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto eventTmpValue = event.value;
        PasteEvent_serializer::write(argsSerializer, eventTmpValue);
    } else {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedPluginErrorCallback(Ark_Int32 resourceId, Ark_PluginErrorData info)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_PluginErrorCallback);
    argsSerializer.writeInt32(resourceId);
    PluginErrorData_serializer::write(argsSerializer, info);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedPluginErrorCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_PluginErrorData info)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_PluginErrorCallback);
    argsSerializer.writeInt32(resourceId);
    PluginErrorData_serializer::write(argsSerializer, info);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedPopupStateChangeCallback(Ark_Int32 resourceId, Ark_PopupStateChangeParam event)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_PopupStateChangeCallback);
    argsSerializer.writeInt32(resourceId);
    PopupStateChangeParam_serializer::write(argsSerializer, event);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedPopupStateChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_PopupStateChangeParam event)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_PopupStateChangeCallback);
    argsSerializer.writeInt32(resourceId);
    PopupStateChangeParam_serializer::write(argsSerializer, event);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedProgressModifierBuilder(Ark_Int32 resourceId, Ark_NativePointer parentNode, Ark_ProgressConfiguration config, Callback_Pointer_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_ProgressModifierBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    ProgressConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedProgressModifierBuilderSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NativePointer parentNode, Ark_ProgressConfiguration config, Callback_Pointer_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_ProgressModifierBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    ProgressConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedRadioModifierBuilder(Ark_Int32 resourceId, Ark_NativePointer parentNode, Ark_RadioConfiguration config, Callback_Pointer_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_RadioModifierBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    RadioConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedRadioModifierBuilderSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NativePointer parentNode, Ark_RadioConfiguration config, Callback_Pointer_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_RadioModifierBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    RadioConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedRatingModifierBuilder(Ark_Int32 resourceId, Ark_NativePointer parentNode, Ark_RatingConfiguration config, Callback_Pointer_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_RatingModifierBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    RatingConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedRatingModifierBuilderSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NativePointer parentNode, Ark_RatingConfiguration config, Callback_Pointer_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_RatingModifierBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    RatingConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedRestrictedWorker_onerror_Callback(Ark_Int32 resourceId, Ark_ErrorEvent ev)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_RestrictedWorker_onerror_Callback);
    argsSerializer.writeInt32(resourceId);
    ErrorEvent_serializer::write(argsSerializer, ev);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedRestrictedWorker_onerror_CallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_ErrorEvent ev)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_RestrictedWorker_onerror_Callback);
    argsSerializer.writeInt32(resourceId);
    ErrorEvent_serializer::write(argsSerializer, ev);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedRestrictedWorker_onexit_Callback(Ark_Int32 resourceId, Ark_Number code)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_RestrictedWorker_onexit_Callback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(code);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedRestrictedWorker_onexit_CallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number code)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_RestrictedWorker_onexit_Callback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(code);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedRestrictedWorker_onmessage_Callback(Ark_Int32 resourceId, Ark_MessageEvents event)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_RestrictedWorker_onmessage_Callback);
    argsSerializer.writeInt32(resourceId);
    MessageEvents_serializer::write(argsSerializer, event);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedRestrictedWorker_onmessage_CallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_MessageEvents event)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_RestrictedWorker_onmessage_Callback);
    argsSerializer.writeInt32(resourceId);
    MessageEvents_serializer::write(argsSerializer, event);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedReuseIdCallback(Ark_Int32 resourceId, Callback_String_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_ReuseIdCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedReuseIdCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Callback_String_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_ReuseIdCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedRouterFinishCallback(Ark_Int32 resourceId, Ark_NativePointer value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_RouterFinishCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(value);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedRouterFinishCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NativePointer value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_RouterFinishCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(value);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedSaveButtonCallback(Ark_Int32 resourceId, Ark_ClickEvent event, Ark_SaveButtonOnClickResult result, Opt_BusinessError error)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_SaveButtonCallback);
    argsSerializer.writeInt32(resourceId);
    ClickEvent_serializer::write(argsSerializer, event);
    argsSerializer.writeInt32(static_cast<Ark_SaveButtonOnClickResult>(result));
    if (runtimeType(error) != INTEROP_RUNTIME_UNDEFINED) {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto errorTmpValue = error.value;
        BusinessError_serializer::write(argsSerializer, errorTmpValue);
    } else {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    enqueueCallback(10, &callbackBuffer);
}
void callManagedSaveButtonCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_ClickEvent event, Ark_SaveButtonOnClickResult result, Opt_BusinessError error)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_SaveButtonCallback);
    argsSerializer.writeInt32(resourceId);
    ClickEvent_serializer::write(argsSerializer, event);
    argsSerializer.writeInt32(static_cast<Ark_SaveButtonOnClickResult>(result));
    if (runtimeType(error) != INTEROP_RUNTIME_UNDEFINED) {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto errorTmpValue = error.value;
        BusinessError_serializer::write(argsSerializer, errorTmpValue);
    } else {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedScrollOnScrollCallback(Ark_Int32 resourceId, Ark_Float64 xOffset, Ark_Float64 yOffset, Ark_ScrollState scrollState)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_ScrollOnScrollCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFloat64(xOffset);
    argsSerializer.writeFloat64(yOffset);
    argsSerializer.writeInt32(static_cast<Ark_ScrollState>(scrollState));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedScrollOnScrollCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Float64 xOffset, Ark_Float64 yOffset, Ark_ScrollState scrollState)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_ScrollOnScrollCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFloat64(xOffset);
    argsSerializer.writeFloat64(yOffset);
    argsSerializer.writeInt32(static_cast<Ark_ScrollState>(scrollState));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedScrollOnWillScrollCallback(Ark_Int32 resourceId, Ark_Float64 xOffset, Ark_Float64 yOffset, Ark_ScrollState scrollState, Ark_ScrollSource scrollSource, Callback_Opt_OffsetResult_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_ScrollOnWillScrollCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFloat64(xOffset);
    argsSerializer.writeFloat64(yOffset);
    argsSerializer.writeInt32(static_cast<Ark_ScrollState>(scrollState));
    argsSerializer.writeInt32(static_cast<Ark_ScrollSource>(scrollSource));
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedScrollOnWillScrollCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Float64 xOffset, Ark_Float64 yOffset, Ark_ScrollState scrollState, Ark_ScrollSource scrollSource, Callback_Opt_OffsetResult_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_ScrollOnWillScrollCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFloat64(xOffset);
    argsSerializer.writeFloat64(yOffset);
    argsSerializer.writeInt32(static_cast<Ark_ScrollState>(scrollState));
    argsSerializer.writeInt32(static_cast<Ark_ScrollSource>(scrollSource));
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedSearchSubmitCallback(Ark_Int32 resourceId, Ark_String searchContent, Opt_SubmitEvent event)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_SearchSubmitCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(searchContent);
    if (runtimeType(event) != INTEROP_RUNTIME_UNDEFINED) {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto eventTmpValue = event.value;
        SubmitEvent_serializer::write(argsSerializer, eventTmpValue);
    } else {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    enqueueCallback(10, &callbackBuffer);
}
void callManagedSearchSubmitCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_String searchContent, Opt_SubmitEvent event)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_SearchSubmitCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(searchContent);
    if (runtimeType(event) != INTEROP_RUNTIME_UNDEFINED) {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto eventTmpValue = event.value;
        SubmitEvent_serializer::write(argsSerializer, eventTmpValue);
    } else {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedSearchValueCallback(Ark_Int32 resourceId, Ark_String value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_SearchValueCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(value);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedSearchValueCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_String value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_SearchValueCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(value);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedShouldBuiltInRecognizerParallelWithCallback(Ark_Int32 resourceId, Ark_GestureRecognizer current, Array_GestureRecognizer others, Callback_GestureRecognizer_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_ShouldBuiltInRecognizerParallelWithCallback);
    argsSerializer.writeInt32(resourceId);
    GestureRecognizer_serializer::write(argsSerializer, current);
    argsSerializer.writeInt32(others.length);
    for (int othersCounterI = 0; othersCounterI < others.length; othersCounterI++) {
        const Ark_GestureRecognizer othersTmpElement = others.array[othersCounterI];
        GestureRecognizer_serializer::write(argsSerializer, othersTmpElement);
    }
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedShouldBuiltInRecognizerParallelWithCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_GestureRecognizer current, Array_GestureRecognizer others, Callback_GestureRecognizer_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_ShouldBuiltInRecognizerParallelWithCallback);
    argsSerializer.writeInt32(resourceId);
    GestureRecognizer_serializer::write(argsSerializer, current);
    argsSerializer.writeInt32(others.length);
    for (int othersCounterI = 0; othersCounterI < others.length; othersCounterI++) {
        const Ark_GestureRecognizer othersTmpElement = others.array[othersCounterI];
        GestureRecognizer_serializer::write(argsSerializer, othersTmpElement);
    }
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedSizeChangeCallback(Ark_Int32 resourceId, Ark_SizeOptions oldValue, Ark_SizeOptions newValue)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_SizeChangeCallback);
    argsSerializer.writeInt32(resourceId);
    SizeOptions_serializer::write(argsSerializer, oldValue);
    SizeOptions_serializer::write(argsSerializer, newValue);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedSizeChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_SizeOptions oldValue, Ark_SizeOptions newValue)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_SizeChangeCallback);
    argsSerializer.writeInt32(resourceId);
    SizeOptions_serializer::write(argsSerializer, oldValue);
    SizeOptions_serializer::write(argsSerializer, newValue);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedSliderModifierBuilder(Ark_Int32 resourceId, Ark_NativePointer parentNode, Ark_SliderConfiguration config, Callback_Pointer_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_SliderModifierBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    SliderConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedSliderModifierBuilderSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NativePointer parentNode, Ark_SliderConfiguration config, Callback_Pointer_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_SliderModifierBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    SliderConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedSliderTriggerChangeCallback(Ark_Int32 resourceId, Ark_Float64 value, Ark_SliderChangeMode mode)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_SliderTriggerChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFloat64(value);
    argsSerializer.writeInt32(static_cast<Ark_SliderChangeMode>(mode));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedSliderTriggerChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Float64 value, Ark_SliderChangeMode mode)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_SliderTriggerChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFloat64(value);
    argsSerializer.writeInt32(static_cast<Ark_SliderChangeMode>(mode));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedStyledStringMarshallCallback(Ark_Int32 resourceId, Ark_UserDataSpan marshallableVal, Callback_Buffer_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_StyledStringMarshallCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeObject(marshallableVal);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedStyledStringMarshallCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_UserDataSpan marshallableVal, Callback_Buffer_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_StyledStringMarshallCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeObject(marshallableVal);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedStyledStringUnmarshallCallback(Ark_Int32 resourceId, Ark_Buffer buf, Callback_StyledStringMarshallingValue_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_StyledStringUnmarshallCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBuffer(buf);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedStyledStringUnmarshallCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Buffer buf, Callback_StyledStringMarshallingValue_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_StyledStringUnmarshallCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBuffer(buf);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedSubmitCallback(Ark_Int32 resourceId, Ark_EnterKeyType enterKey, Ark_SubmitEvent event)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_SubmitCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_EnterKeyType>(enterKey));
    SubmitEvent_serializer::write(argsSerializer, event);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedSubmitCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_EnterKeyType enterKey, Ark_SubmitEvent event)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_SubmitCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_EnterKeyType>(enterKey));
    SubmitEvent_serializer::write(argsSerializer, event);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedTabsCustomContentTransitionCallback(Ark_Int32 resourceId, Ark_Int32 from, Ark_Int32 to, Callback_Opt_TabContentAnimatedTransition_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_TabsCustomContentTransitionCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(from);
    argsSerializer.writeInt32(to);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedTabsCustomContentTransitionCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 from, Ark_Int32 to, Callback_Opt_TabContentAnimatedTransition_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_TabsCustomContentTransitionCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(from);
    argsSerializer.writeInt32(to);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedTextAreaSubmitCallback(Ark_Int32 resourceId, Ark_EnterKeyType enterKeyType, Opt_SubmitEvent event)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_TextAreaSubmitCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_EnterKeyType>(enterKeyType));
    if (runtimeType(event) != INTEROP_RUNTIME_UNDEFINED) {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto eventTmpValue = event.value;
        SubmitEvent_serializer::write(argsSerializer, eventTmpValue);
    } else {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    enqueueCallback(10, &callbackBuffer);
}
void callManagedTextAreaSubmitCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_EnterKeyType enterKeyType, Opt_SubmitEvent event)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_TextAreaSubmitCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_EnterKeyType>(enterKeyType));
    if (runtimeType(event) != INTEROP_RUNTIME_UNDEFINED) {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto eventTmpValue = event.value;
        SubmitEvent_serializer::write(argsSerializer, eventTmpValue);
    } else {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedTextClockModifierBuilder(Ark_Int32 resourceId, Ark_NativePointer parentNode, Ark_TextClockConfiguration config, Callback_Pointer_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_TextClockModifierBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    TextClockConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedTextClockModifierBuilderSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NativePointer parentNode, Ark_TextClockConfiguration config, Callback_Pointer_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_TextClockModifierBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    TextClockConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedTextFieldValueCallback(Ark_Int32 resourceId, Ark_ResourceStr value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_TextFieldValueCallback);
    argsSerializer.writeInt32(resourceId);
    if (value.selector == 0) {
        argsSerializer.writeInt8(0);
        const auto valueForIdx0 = value.value0;
        argsSerializer.writeString(valueForIdx0);
    } else if (value.selector == 1) {
        argsSerializer.writeInt8(1);
        const auto valueForIdx1 = value.value1;
        Resource_serializer::write(argsSerializer, valueForIdx1);
    }
    enqueueCallback(10, &callbackBuffer);
}
void callManagedTextFieldValueCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_ResourceStr value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_TextFieldValueCallback);
    argsSerializer.writeInt32(resourceId);
    if (value.selector == 0) {
        argsSerializer.writeInt8(0);
        const auto valueForIdx0 = value.value0;
        argsSerializer.writeString(valueForIdx0);
    } else if (value.selector == 1) {
        argsSerializer.writeInt8(1);
        const auto valueForIdx1 = value.value1;
        Resource_serializer::write(argsSerializer, valueForIdx1);
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedTextPickerEnterSelectedAreaCallback(Ark_Int32 resourceId, Ark_Union_String_Array_String value, Ark_Union_I32_Array_I32 index)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_TextPickerEnterSelectedAreaCallback);
    argsSerializer.writeInt32(resourceId);
    if (value.selector == 0) {
        argsSerializer.writeInt8(0);
        const auto valueForIdx0 = value.value0;
        argsSerializer.writeString(valueForIdx0);
    } else if (value.selector == 1) {
        argsSerializer.writeInt8(1);
        const auto valueForIdx1 = value.value1;
        argsSerializer.writeInt32(valueForIdx1.length);
        for (int valueForIdx1CounterI = 0; valueForIdx1CounterI < valueForIdx1.length; valueForIdx1CounterI++) {
            const Ark_String valueForIdx1TmpElement = valueForIdx1.array[valueForIdx1CounterI];
            argsSerializer.writeString(valueForIdx1TmpElement);
        }
    }
    if (index.selector == 0) {
        argsSerializer.writeInt8(0);
        const auto indexForIdx0 = index.value0;
        argsSerializer.writeInt32(indexForIdx0);
    } else if (index.selector == 1) {
        argsSerializer.writeInt8(1);
        const auto indexForIdx1 = index.value1;
        argsSerializer.writeInt32(indexForIdx1.length);
        for (int indexForIdx1CounterI = 0; indexForIdx1CounterI < indexForIdx1.length; indexForIdx1CounterI++) {
            const Ark_Int32 indexForIdx1TmpElement = indexForIdx1.array[indexForIdx1CounterI];
            argsSerializer.writeInt32(indexForIdx1TmpElement);
        }
    }
    enqueueCallback(10, &callbackBuffer);
}
void callManagedTextPickerEnterSelectedAreaCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Union_String_Array_String value, Ark_Union_I32_Array_I32 index)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_TextPickerEnterSelectedAreaCallback);
    argsSerializer.writeInt32(resourceId);
    if (value.selector == 0) {
        argsSerializer.writeInt8(0);
        const auto valueForIdx0 = value.value0;
        argsSerializer.writeString(valueForIdx0);
    } else if (value.selector == 1) {
        argsSerializer.writeInt8(1);
        const auto valueForIdx1 = value.value1;
        argsSerializer.writeInt32(valueForIdx1.length);
        for (int valueForIdx1CounterI = 0; valueForIdx1CounterI < valueForIdx1.length; valueForIdx1CounterI++) {
            const Ark_String valueForIdx1TmpElement = valueForIdx1.array[valueForIdx1CounterI];
            argsSerializer.writeString(valueForIdx1TmpElement);
        }
    }
    if (index.selector == 0) {
        argsSerializer.writeInt8(0);
        const auto indexForIdx0 = index.value0;
        argsSerializer.writeInt32(indexForIdx0);
    } else if (index.selector == 1) {
        argsSerializer.writeInt8(1);
        const auto indexForIdx1 = index.value1;
        argsSerializer.writeInt32(indexForIdx1.length);
        for (int indexForIdx1CounterI = 0; indexForIdx1CounterI < indexForIdx1.length; indexForIdx1CounterI++) {
            const Ark_Int32 indexForIdx1TmpElement = indexForIdx1.array[indexForIdx1CounterI];
            argsSerializer.writeInt32(indexForIdx1TmpElement);
        }
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedTextPickerScrollStopCallback(Ark_Int32 resourceId, Ark_Union_String_Array_String value, Ark_Union_I32_Array_I32 index)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_TextPickerScrollStopCallback);
    argsSerializer.writeInt32(resourceId);
    if (value.selector == 0) {
        argsSerializer.writeInt8(0);
        const auto valueForIdx0 = value.value0;
        argsSerializer.writeString(valueForIdx0);
    } else if (value.selector == 1) {
        argsSerializer.writeInt8(1);
        const auto valueForIdx1 = value.value1;
        argsSerializer.writeInt32(valueForIdx1.length);
        for (int valueForIdx1CounterI = 0; valueForIdx1CounterI < valueForIdx1.length; valueForIdx1CounterI++) {
            const Ark_String valueForIdx1TmpElement = valueForIdx1.array[valueForIdx1CounterI];
            argsSerializer.writeString(valueForIdx1TmpElement);
        }
    }
    if (index.selector == 0) {
        argsSerializer.writeInt8(0);
        const auto indexForIdx0 = index.value0;
        argsSerializer.writeInt32(indexForIdx0);
    } else if (index.selector == 1) {
        argsSerializer.writeInt8(1);
        const auto indexForIdx1 = index.value1;
        argsSerializer.writeInt32(indexForIdx1.length);
        for (int indexForIdx1CounterI = 0; indexForIdx1CounterI < indexForIdx1.length; indexForIdx1CounterI++) {
            const Ark_Int32 indexForIdx1TmpElement = indexForIdx1.array[indexForIdx1CounterI];
            argsSerializer.writeInt32(indexForIdx1TmpElement);
        }
    }
    enqueueCallback(10, &callbackBuffer);
}
void callManagedTextPickerScrollStopCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Union_String_Array_String value, Ark_Union_I32_Array_I32 index)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_TextPickerScrollStopCallback);
    argsSerializer.writeInt32(resourceId);
    if (value.selector == 0) {
        argsSerializer.writeInt8(0);
        const auto valueForIdx0 = value.value0;
        argsSerializer.writeString(valueForIdx0);
    } else if (value.selector == 1) {
        argsSerializer.writeInt8(1);
        const auto valueForIdx1 = value.value1;
        argsSerializer.writeInt32(valueForIdx1.length);
        for (int valueForIdx1CounterI = 0; valueForIdx1CounterI < valueForIdx1.length; valueForIdx1CounterI++) {
            const Ark_String valueForIdx1TmpElement = valueForIdx1.array[valueForIdx1CounterI];
            argsSerializer.writeString(valueForIdx1TmpElement);
        }
    }
    if (index.selector == 0) {
        argsSerializer.writeInt8(0);
        const auto indexForIdx0 = index.value0;
        argsSerializer.writeInt32(indexForIdx0);
    } else if (index.selector == 1) {
        argsSerializer.writeInt8(1);
        const auto indexForIdx1 = index.value1;
        argsSerializer.writeInt32(indexForIdx1.length);
        for (int indexForIdx1CounterI = 0; indexForIdx1CounterI < indexForIdx1.length; indexForIdx1CounterI++) {
            const Ark_Int32 indexForIdx1TmpElement = indexForIdx1.array[indexForIdx1CounterI];
            argsSerializer.writeInt32(indexForIdx1TmpElement);
        }
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedTextSelectionChangeCallback(Ark_Int32 resourceId, Ark_String selectionText)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_TextSelectionChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(selectionText);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedTextSelectionChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_String selectionText)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_TextSelectionChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(selectionText);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedTextTimerModifierBuilder(Ark_Int32 resourceId, Ark_NativePointer parentNode, Ark_TextTimerConfiguration config, Callback_Pointer_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_TextTimerModifierBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    TextTimerConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedTextTimerModifierBuilderSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NativePointer parentNode, Ark_TextTimerConfiguration config, Callback_Pointer_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_TextTimerModifierBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    TextTimerConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedTimerCallback(Ark_Int32 resourceId, Ark_Int64 utc, Ark_Int64 elapsedTime)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_TimerCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt64(utc);
    argsSerializer.writeInt64(elapsedTime);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedTimerCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int64 utc, Ark_Int64 elapsedTime)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_TimerCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt64(utc);
    argsSerializer.writeInt64(elapsedTime);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedToggleModifierBuilder(Ark_Int32 resourceId, Ark_NativePointer parentNode, Ark_ToggleConfiguration config, Callback_Pointer_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_ToggleModifierBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    ToggleConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedToggleModifierBuilderSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NativePointer parentNode, Ark_ToggleConfiguration config, Callback_Pointer_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_ToggleModifierBuilder);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    ToggleConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedTransitionFinishCallback(Ark_Int32 resourceId, Ark_Boolean transitionIn)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_TransitionFinishCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(transitionIn);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedTransitionFinishCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Boolean transitionIn)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_TransitionFinishCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(transitionIn);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedType_CommonMethod_onDragStart(Ark_Int32 resourceId, Ark_DragEvent event, Opt_String extraParams, Callback_Union_CustomBuilder_DragItemInfo_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Type_CommonMethod_onDragStart);
    argsSerializer.writeInt32(resourceId);
    DragEvent_serializer::write(argsSerializer, event);
    if (runtimeType(extraParams) != INTEROP_RUNTIME_UNDEFINED) {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto extraParamsTmpValue = extraParams.value;
        argsSerializer.writeString(extraParamsTmpValue);
    } else {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedType_CommonMethod_onDragStartSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_DragEvent event, Opt_String extraParams, Callback_Union_CustomBuilder_DragItemInfo_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Type_CommonMethod_onDragStart);
    argsSerializer.writeInt32(resourceId);
    DragEvent_serializer::write(argsSerializer, event);
    if (runtimeType(extraParams) != INTEROP_RUNTIME_UNDEFINED) {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto extraParamsTmpValue = extraParams.value;
        argsSerializer.writeString(extraParamsTmpValue);
    } else {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedType_NavigationAttribute_customNavContentTransition(Ark_Int32 resourceId, Ark_NavContentInfo from, Ark_NavContentInfo to, Ark_NavigationOperation operation, Callback_Opt_NavigationAnimatedTransition_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_Type_NavigationAttribute_customNavContentTransition);
    argsSerializer.writeInt32(resourceId);
    NavContentInfo_serializer::write(argsSerializer, from);
    NavContentInfo_serializer::write(argsSerializer, to);
    argsSerializer.writeInt32(static_cast<Ark_NavigationOperation>(operation));
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedType_NavigationAttribute_customNavContentTransitionSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NavContentInfo from, Ark_NavContentInfo to, Ark_NavigationOperation operation, Callback_Opt_NavigationAnimatedTransition_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_Type_NavigationAttribute_customNavContentTransition);
    argsSerializer.writeInt32(resourceId);
    NavContentInfo_serializer::write(argsSerializer, from);
    NavContentInfo_serializer::write(argsSerializer, to);
    argsSerializer.writeInt32(static_cast<Ark_NavigationOperation>(operation));
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedUpdateTransitionCallback(Ark_Int32 resourceId, Ark_Number progress)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_UpdateTransitionCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(progress);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedUpdateTransitionCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number progress)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_UpdateTransitionCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(progress);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedVisibleAreaChangeCallback(Ark_Int32 resourceId, Ark_Boolean isExpanding, Ark_Float64 currentRatio)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_VisibleAreaChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(isExpanding);
    argsSerializer.writeFloat64(currentRatio);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedVisibleAreaChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Boolean isExpanding, Ark_Float64 currentRatio)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_VisibleAreaChangeCallback);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(isExpanding);
    argsSerializer.writeFloat64(currentRatio);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedVoidCallback(Ark_Int32 resourceId)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_VoidCallback);
    argsSerializer.writeInt32(resourceId);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedVoidCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_VoidCallback);
    argsSerializer.writeInt32(resourceId);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedWebKeyboardCallback(Ark_Int32 resourceId, Ark_WebKeyboardCallbackInfo keyboardCallbackInfo, Callback_WebKeyboardOptions_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_WebKeyboardCallback);
    argsSerializer.writeInt32(resourceId);
    WebKeyboardCallbackInfo_serializer::write(argsSerializer, keyboardCallbackInfo);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(10, &callbackBuffer);
}
void callManagedWebKeyboardCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_WebKeyboardCallbackInfo keyboardCallbackInfo, Callback_WebKeyboardOptions_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_WebKeyboardCallback);
    argsSerializer.writeInt32(resourceId);
    WebKeyboardCallbackInfo_serializer::write(argsSerializer, keyboardCallbackInfo);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void callManagedWorkerEventListener(Ark_Int32 resourceId, Ark_Event event)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource, releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer)&(callbackBuffer.buffer), sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(Kind_WorkerEventListener);
    argsSerializer.writeInt32(resourceId);
    Event_serializer::write(argsSerializer, event);
    enqueueCallback(10, &callbackBuffer);
}
void callManagedWorkerEventListenerSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Event event)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(10);
    argsSerializer.writeInt32(Kind_WorkerEventListener);
    argsSerializer.writeInt32(resourceId);
    Event_serializer::write(argsSerializer, event);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
Ark_NativePointer getManagedCallbackCaller(CallbackKind kind)
{
    switch (kind) {
        case Kind_AccessibilityActionInterceptCallback: return reinterpret_cast<Ark_NativePointer>(callManagedAccessibilityActionInterceptCallback);
        case Kind_AccessibilityCallback: return reinterpret_cast<Ark_NativePointer>(callManagedAccessibilityCallback);
        case Kind_AccessibilityFocusCallback: return reinterpret_cast<Ark_NativePointer>(callManagedAccessibilityFocusCallback);
        case Kind_AccessibilityTransparentCallback: return reinterpret_cast<Ark_NativePointer>(callManagedAccessibilityTransparentCallback);
        case Kind_ArcScrollIndexHandler: return reinterpret_cast<Ark_NativePointer>(callManagedArcScrollIndexHandler);
        case Kind_AsyncCallback_image_PixelMap_Void: return reinterpret_cast<Ark_NativePointer>(callManagedAsyncCallback_image_PixelMap_Void);
        case Kind_AsyncCallback_Void: return reinterpret_cast<Ark_NativePointer>(callManagedAsyncCallback_Void);
        case Kind_ButtonModifierBuilder: return reinterpret_cast<Ark_NativePointer>(callManagedButtonModifierBuilder);
        case Kind_ButtonTriggerClickCallback: return reinterpret_cast<Ark_NativePointer>(callManagedButtonTriggerClickCallback);
        case Kind_Callback_AccessibilityActionInterceptResult_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_AccessibilityActionInterceptResult_Void);
        case Kind_Callback_Area_Area_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Area_Area_Void);
        case Kind_Callback_Array_I32_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Array_I32_Void);
        case Kind_Callback_Array_String_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Array_String_Void);
        case Kind_Callback_Array_TextMenuItem_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Array_TextMenuItem_Void);
        case Kind_Callback_Array_TouchTestInfo_TouchResult: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Array_TouchTestInfo_TouchResult);
        case Kind_Callback_AxisEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_AxisEvent_Void);
        case Kind_Callback_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Boolean);
        case Kind_Callback_Boolean_HoverEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Boolean_HoverEvent_Void);
        case Kind_Callback_Boolean_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Boolean_Void);
        case Kind_Callback_Buffer_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Buffer_Void);
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
        case Kind_Callback_ErrorInformation_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_ErrorInformation_Void);
        case Kind_Callback_Extender_OnFinish: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Extender_OnFinish);
        case Kind_Callback_Extender_OnProgress: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Extender_OnProgress);
        case Kind_Callback_F64_F64_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_F64_F64_Void);
        case Kind_Callback_F64_SliderChangeMode_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_F64_SliderChangeMode_Void);
        case Kind_Callback_F64_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_F64_Void);
        case Kind_Callback_FocusAxisEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_FocusAxisEvent_Void);
        case Kind_Callback_FormCallbackInfo_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_FormCallbackInfo_Void);
        case Kind_Callback_FullscreenInfo_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_FullscreenInfo_Void);
        case Kind_Callback_GestureEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_GestureEvent_Void);
        case Kind_Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_GestureInfo_BaseGestureEvent_GestureJudgeResult);
        case Kind_Callback_GestureJudgeResult_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_GestureJudgeResult_Void);
        case Kind_Callback_GestureRecognizer_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_GestureRecognizer_Void);
        case Kind_Callback_HitTestMode_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_HitTestMode_Void);
        case Kind_Callback_HoverEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_HoverEvent_Void);
        case Kind_Callback_I32_F64_ComputedBarAttribute: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_I32_F64_ComputedBarAttribute);
        case Kind_Callback_I32_I32_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_I32_I32_Boolean);
        case Kind_Callback_I32_I32_I32_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_I32_I32_I32_Void);        
        case Kind_Callback_I32_I32_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_I32_I32_Void);
        case Kind_Callback_I32_Tuple_I32_I32: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_I32_Tuple_I32_I32);
        case Kind_Callback_I32_Tuple_I32_I32_I32_I32: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_I32_Tuple_I32_I32_I32_I32);       
        case Kind_Callback_I64_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_I64_Void);
        case Kind_Callback_I32_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_I32_Void);
        case Kind_Callback_InsertValue_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_InsertValue_Boolean);
        case Kind_Callback_InsertValue_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_InsertValue_Void);
        case Kind_Callback_ItemDragInfo_I32_I32_Boolean_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_ItemDragInfo_I32_I32_Boolean_Void);
        case Kind_Callback_ItemDragInfo_I32_I32_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_ItemDragInfo_I32_I32_Void);
        case Kind_Callback_ItemDragInfo_I32_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_ItemDragInfo_I32_Void);
        case Kind_Callback_ItemDragInfo_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_ItemDragInfo_Void);
        case Kind_Callback_KeyEvent_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_KeyEvent_Boolean);
        case Kind_Callback_KeyEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_KeyEvent_Void);
        case Kind_Callback_Long_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Long_Void);
        case Kind_Callback_Map_String_RecordData_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Map_String_RecordData_Void);
        case Kind_Callback_MarqueeState_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_MarqueeState_Void);
        case Kind_Callback_MouseEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_MouseEvent_Void);
        case Kind_Callback_NativeEmbedDataInfo_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_NativeEmbedDataInfo_Void);
        case Kind_Callback_NativeEmbedTouchInfo_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_NativeEmbedTouchInfo_Void);
        case Kind_Callback_NativeXComponentPointer_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_NativeXComponentPointer_Void);
        case Kind_Callback_NavDestinationActiveReason_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_NavDestinationActiveReason_Void);
        case Kind_Callback_NavDestinationContext_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_NavDestinationContext_Void);
        case Kind_Callback_NavigationMode_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_NavigationMode_Void);
        case Kind_Callback_NavigationTitleMode_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_NavigationTitleMode_Void);
        case Kind_Callback_NavigationTransitionProxy_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_NavigationTransitionProxy_Void);
        case Kind_Callback_Number_Number_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Number_Number_Void);
        case Kind_Callback_Number_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Number_Void);
        case Kind_Callback_Object_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Object_Void);
        case Kind_Callback_OnAlertEvent_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnAlertEvent_Boolean);
        case Kind_Callback_OnAudioStateChangedEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnAudioStateChangedEvent_Void);
        case Kind_Callback_OnBeforeUnloadEvent_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnBeforeUnloadEvent_Boolean);
        case Kind_Callback_OnClientAuthenticationEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnClientAuthenticationEvent_Void);
        case Kind_Callback_OnConfirmEvent_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnConfirmEvent_Boolean);
        case Kind_Callback_OnConsoleEvent_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnConsoleEvent_Boolean);
        case Kind_Callback_OnContextMenuShowEvent_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnContextMenuShowEvent_Boolean);
        case Kind_Callback_OnDataResubmittedEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnDataResubmittedEvent_Void);
        case Kind_Callback_OnDestory_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnDestory_Void);
        case Kind_Callback_OnDownloadStartEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnDownloadStartEvent_Void);
        case Kind_Callback_OnErrorReceiveEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnErrorReceiveEvent_Void);
        case Kind_Callback_OnFaviconReceivedEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnFaviconReceivedEvent_Void);
        case Kind_Callback_OnFirstContentfulPaintEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnFirstContentfulPaintEvent_Void);
        case Kind_Callback_OnGeolocationShowEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnGeolocationShowEvent_Void);
        case Kind_Callback_OnHttpAuthRequestEvent_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnHttpAuthRequestEvent_Boolean);
        case Kind_Callback_OnHttpErrorReceiveEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnHttpErrorReceiveEvent_Void);
        case Kind_Callback_OnLoadFinishedEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnLoadFinishedEvent_Void);
        case Kind_Callback_OnLoadInterceptEvent_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnLoadInterceptEvent_Boolean);
        case Kind_Callback_OnLoadStartedEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnLoadStartedEvent_Void);
        case Kind_Callback_onMeasureSize_SizeResult: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_onMeasureSize_SizeResult);
        case Kind_Callback_OnMoveFromTo: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnMoveFromTo);
        case Kind_Callback_OnOverScrollEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnOverScrollEvent_Void);
        case Kind_Callback_OnPageBeginEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnPageBeginEvent_Void);
        case Kind_Callback_OnPageEndEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnPageEndEvent_Void);
        case Kind_Callback_OnPageVisibleEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnPageVisibleEvent_Void);
        case Kind_Callback_OnPdfLoadEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnPdfLoadEvent_Void);
        case Kind_Callback_OnPdfScrollEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnPdfScrollEvent_Void);
        case Kind_Callback_OnPermissionRequestEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnPermissionRequestEvent_Void);
        case Kind_Callback_onPlaceChildren_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_onPlaceChildren_Void);
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
        case Kind_Callback_Opt_CustomBuilder_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Opt_CustomBuilder_Void);
        case Kind_Callback_Opt_NavigationAnimatedTransition_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Opt_NavigationAnimatedTransition_Void);
        case Kind_Callback_Opt_OffsetResult_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Opt_OffsetResult_Void);
        case Kind_Callback_Opt_ScrollResult_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Opt_ScrollResult_Void);
        case Kind_Callback_Opt_StyledString_Opt_Array_String_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Opt_StyledString_Opt_Array_String_Void);
        case Kind_Callback_Opt_TabContentAnimatedTransition_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Opt_TabContentAnimatedTransition_Void);
        case Kind_Callback_Opt_WebResourceResponse_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Opt_WebResourceResponse_Void);
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
        case Kind_Callback_RouterCallbackInfo_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_RouterCallbackInfo_Void);
        case Kind_Callback_SheetDismiss_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_SheetDismiss_Void);
        case Kind_Callback_SheetType_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_SheetType_Void);
        case Kind_Callback_Size_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Size_Void);
        case Kind_Callback_SizeResult_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_SizeResult_Void);
        case Kind_Callback_SpringBackAction_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_SpringBackAction_Void);
        case Kind_Callback_StateStylesChange: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_StateStylesChange);
        case Kind_Callback_String_PasteEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_String_PasteEvent_Void);
        case Kind_Callback_String_SurfaceRect_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_String_SurfaceRect_Void);
        case Kind_Callback_String_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_String_Void);
        case Kind_Callback_StyledStringChangeValue_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_StyledStringChangeValue_Boolean);
        case Kind_Callback_StyledStringMarshallingValue_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_StyledStringMarshallingValue_Void);
        case Kind_Callback_SwipeActionState_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_SwipeActionState_Void);
        case Kind_Callback_SwiperContentTransitionProxy_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_SwiperContentTransitionProxy_Void);
        case Kind_Callback_T_Void_Arkui_Component_Units_Length: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_T_Void_Arkui_Component_Units_Length);
        case Kind_Callback_T_Void_Arkui_Component_Units_ResourceStr: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_T_Void_Arkui_Component_Units_ResourceStr);
        case Kind_Callback_T_Void_Array_Arkui_Component_Units_ResourceStr: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_T_Void_Array_Arkui_Component_Units_ResourceStr);
        case Kind_Callback_T_Void_Array_Global_Resource_Resource: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_T_Void_Array_Global_Resource_Resource);
        case Kind_Callback_T_Void_Array_I32: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_T_Void_Array_I32);
        case Kind_Callback_T_Void_Array_String: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_T_Void_Array_String);
        case Kind_Callback_T_Void_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_T_Void_Boolean);
        case Kind_Callback_T_Void_Date: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_T_Void_Date);
        case Kind_Callback_T_Void_F64: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_T_Void_F64);
        case Kind_Callback_T_Void_Global_Resource_Resource: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_T_Void_Global_Resource_Resource);
        case Kind_Callback_T_Void_I32: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_T_Void_I32);
        case Kind_Callback_T_Void_Number: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_T_Void_Number);
        case Kind_Callback_T_Void_String: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_T_Void_String);
        case Kind_Callback_TabContentTransitionProxy_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_TabContentTransitionProxy_Void);
        case Kind_Callback_TerminationInfo_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_TerminationInfo_Void);
        case Kind_Callback_TextPickerResult_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_TextPickerResult_Void);
        case Kind_Callback_TextRange_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_TextRange_Void);
        case Kind_Callback_TimePickerResult_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_TimePickerResult_Void);
        case Kind_Callback_TouchEvent_HitTestMode: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_TouchEvent_HitTestMode);
        case Kind_Callback_TouchEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_TouchEvent_Void);
        case Kind_Callback_TouchResult_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_TouchResult_Void);
        case Kind_Callback_Tuple_I32_I32_I32_I32_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Tuple_I32_I32_I32_I32_Void);
        case Kind_Callback_Tuple_I32_I32_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Tuple_I32_I32_Void);
        case Kind_Callback_UIExtensionProxy_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_UIExtensionProxy_Void);
        case Kind_Callback_Union_CustomBuilder_DragItemInfo_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Union_CustomBuilder_DragItemInfo_Void);
        case Kind_Callback_Union_Object_Idlize_Stdlib_Null_Undefined_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Union_Object_Idlize_Stdlib_Null_Undefined_Void);
        case Kind_Callback_VisibilityChangeReason_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_VisibilityChangeReason_Void);
        case Kind_Callback_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Void);
        case Kind_Callback_WebKeyboardOptions_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_WebKeyboardOptions_Void);
        case Kind_CheckBoxGroupModifierBuilder: return reinterpret_cast<Ark_NativePointer>(callManagedCheckBoxGroupModifierBuilder);
        case Kind_CheckBoxModifierBuilder: return reinterpret_cast<Ark_NativePointer>(callManagedCheckBoxModifierBuilder);
        case Kind_ContentDidScrollCallback: return reinterpret_cast<Ark_NativePointer>(callManagedContentDidScrollCallback);
        case Kind_ContentWillScrollCallback: return reinterpret_cast<Ark_NativePointer>(callManagedContentWillScrollCallback);
        case Kind_CustomBuilderT_Arkui_Component_Enums_ResponseType: return reinterpret_cast<Ark_NativePointer>(callManagedCustomBuilderT_Arkui_Component_Enums_ResponseType);
        case Kind_CustomBuilderT_I32: return reinterpret_cast<Ark_NativePointer>(callManagedCustomBuilderT_I32);
        case Kind_CustomNodeBuilder: return reinterpret_cast<Ark_NativePointer>(callManagedCustomNodeBuilder);
        case Kind_DataPanelModifierBuilder: return reinterpret_cast<Ark_NativePointer>(callManagedDataPanelModifierBuilder);
        case Kind_EditableTextOnChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedEditableTextOnChangeCallback);
        case Kind_ErrorCallback_Ohos_Base_BusinessError: return reinterpret_cast<Ark_NativePointer>(callManagedErrorCallback_Ohos_Base_BusinessError);
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
        case Kind_MouseInfoCallback: return reinterpret_cast<Ark_NativePointer>(callManagedMouseInfoCallback);
        case Kind_NavDestinationTransitionDelegate: return reinterpret_cast<Ark_NativePointer>(callManagedNavDestinationTransitionDelegate);
        case Kind_NavExtender_CreateNavDestination: return reinterpret_cast<Ark_NativePointer>(callManagedNavExtender_CreateNavDestination);
        case Kind_NavExtender_OnUpdateStack: return reinterpret_cast<Ark_NativePointer>(callManagedNavExtender_OnUpdateStack);
        case Kind_NavExtender_PageMapNodeBuilder: return reinterpret_cast<Ark_NativePointer>(callManagedNavExtender_PageMapNodeBuilder);
        case Kind_OnAdsBlockedCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnAdsBlockedCallback);
        case Kind_OnAlphabetIndexerPopupSelectCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnAlphabetIndexerPopupSelectCallback);
        case Kind_OnAlphabetIndexerRequestPopupDataCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnAlphabetIndexerRequestPopupDataCallback);
        case Kind_OnAlphabetIndexerSelectCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnAlphabetIndexerSelectCallback);
        case Kind_OnCheckboxChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnCheckboxChangeCallback);
        case Kind_OnCheckboxGroupChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnCheckboxGroupChangeCallback);
        case Kind_OnContentScrollCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnContentScrollCallback);
        case Kind_OnContextMenuHideCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnContextMenuHideCallback);
        case Kind_OnCreateMenuCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnCreateMenuCallback);
        case Kind_OnDetectBlankScreenCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnDetectBlankScreenCallback);
        case Kind_OnDidChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnDidChangeCallback);
        case Kind_OnDragEventCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnDragEventCallback);
        case Kind_OnFirstMeaningfulPaintCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnFirstMeaningfulPaintCallback);
        case Kind_OnFoldStatusChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnFoldStatusChangeCallback);
        case Kind_OnFullScreenEnterCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnFullScreenEnterCallback);
        case Kind_OnHoverCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnHoverCallback);
        case Kind_OnHoverStatusChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnHoverStatusChangeCallback);
        case Kind_OnIntelligentTrackingPreventionCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnIntelligentTrackingPreventionCallback);
        case Kind_OnItemDragStartCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnItemDragStartCallback);
        case Kind_OnLargestContentfulPaintCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnLargestContentfulPaintCallback);
        case Kind_OnLinearIndicatorChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnLinearIndicatorChangeCallback);
        case Kind_OnMenuItemClickCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnMenuItemClickCallback);
        case Kind_OnMoveHandler: return reinterpret_cast<Ark_NativePointer>(callManagedOnMoveHandler);
        case Kind_OnNativeEmbedObjectParamChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnNativeEmbedObjectParamChangeCallback);
        case Kind_OnNativeEmbedVisibilityChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnNativeEmbedVisibilityChangeCallback);
        case Kind_OnNavigationEntryCommittedCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnNavigationEntryCommittedCallback);
        case Kind_OnOverrideErrorPageCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnOverrideErrorPageCallback);
        case Kind_OnOverrideUrlLoadingCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnOverrideUrlLoadingCallback);
        case Kind_OnPasteCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnPasteCallback);
        case Kind_OnPickerCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnPickerCallback);
        case Kind_OnRadioChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnRadioChangeCallback);
        case Kind_OnRatingChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnRatingChangeCallback);
        case Kind_OnRenderProcessNotRespondingCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnRenderProcessNotRespondingCallback);
        case Kind_OnRenderProcessRespondingCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnRenderProcessRespondingCallback);
        case Kind_OnSafeBrowsingCheckResultCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnSafeBrowsingCheckResultCallback);
        case Kind_OnScrollCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnScrollCallback);
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
        case Kind_OnTabsContentDidScrollCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnTabsContentDidScrollCallback);
        case Kind_OnTabsContentWillChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnTabsContentWillChangeCallback);
        case Kind_OnTabsGestureSwipeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnTabsGestureSwipeCallback);
        case Kind_OnTextPickerChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnTextPickerChangeCallback);
        case Kind_OnTextSelectionChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnTextSelectionChangeCallback);
        case Kind_OnTimePickerChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnTimePickerChangeCallback);
        case Kind_OnViewportFitChangedCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnViewportFitChangedCallback);
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
        case Kind_RouterFinishCallback: return reinterpret_cast<Ark_NativePointer>(callManagedRouterFinishCallback);
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
        case Kind_TextSelectionChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedTextSelectionChangeCallback);
        case Kind_TextTimerModifierBuilder: return reinterpret_cast<Ark_NativePointer>(callManagedTextTimerModifierBuilder);
        case Kind_TimerCallback: return reinterpret_cast<Ark_NativePointer>(callManagedTimerCallback);
        case Kind_ToggleModifierBuilder: return reinterpret_cast<Ark_NativePointer>(callManagedToggleModifierBuilder);
        case Kind_TransitionFinishCallback: return reinterpret_cast<Ark_NativePointer>(callManagedTransitionFinishCallback);
        case Kind_Type_CommonMethod_onDragStart: return reinterpret_cast<Ark_NativePointer>(callManagedType_CommonMethod_onDragStart);
        case Kind_Type_NavigationAttribute_customNavContentTransition: return reinterpret_cast<Ark_NativePointer>(callManagedType_NavigationAttribute_customNavContentTransition);
        case Kind_Type_WebAttribute_onInterceptRequest: return reinterpret_cast<Ark_NativePointer>(callManagedType_WebAttribute_onInterceptRequest);
        case Kind_UpdateTransitionCallback: return reinterpret_cast<Ark_NativePointer>(callManagedUpdateTransitionCallback);
        case Kind_VisibleAreaChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedVisibleAreaChangeCallback);
        case Kind_VoidCallback: return reinterpret_cast<Ark_NativePointer>(callManagedVoidCallback);
        case Kind_WebKeyboardCallback: return reinterpret_cast<Ark_NativePointer>(callManagedWebKeyboardCallback);
        case Kind_WorkerEventListener: return reinterpret_cast<Ark_NativePointer>(callManagedWorkerEventListener);
    }
    return nullptr;
}
Ark_NativePointer getManagedCallbackCallerSync(CallbackKind kind)
{
    switch (kind) {
        case Kind_AccessibilityActionInterceptCallback: return reinterpret_cast<Ark_NativePointer>(callManagedAccessibilityActionInterceptCallbackSync);
        case Kind_AccessibilityCallback: return reinterpret_cast<Ark_NativePointer>(callManagedAccessibilityCallbackSync);
        case Kind_AccessibilityFocusCallback: return reinterpret_cast<Ark_NativePointer>(callManagedAccessibilityFocusCallbackSync);
        case Kind_AccessibilityTransparentCallback: return reinterpret_cast<Ark_NativePointer>(callManagedAccessibilityTransparentCallbackSync);
        case Kind_ArcScrollIndexHandler: return reinterpret_cast<Ark_NativePointer>(callManagedArcScrollIndexHandlerSync);
        case Kind_AsyncCallback_image_PixelMap_Void: return reinterpret_cast<Ark_NativePointer>(callManagedAsyncCallback_image_PixelMap_VoidSync);
        case Kind_AsyncCallback_Void: return reinterpret_cast<Ark_NativePointer>(callManagedAsyncCallback_VoidSync);
        case Kind_ButtonModifierBuilder: return reinterpret_cast<Ark_NativePointer>(callManagedButtonModifierBuilderSync);
        case Kind_ButtonTriggerClickCallback: return reinterpret_cast<Ark_NativePointer>(callManagedButtonTriggerClickCallbackSync);
        case Kind_Callback_AccessibilityActionInterceptResult_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_AccessibilityActionInterceptResult_VoidSync);
        case Kind_Callback_Area_Area_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Area_Area_VoidSync);
        case Kind_Callback_Array_I32_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Array_I32_VoidSync);
        case Kind_Callback_Array_String_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Array_String_VoidSync);
        case Kind_Callback_Array_TextMenuItem_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Array_TextMenuItem_VoidSync);
        case Kind_Callback_Array_TouchTestInfo_TouchResult: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Array_TouchTestInfo_TouchResultSync);
        case Kind_Callback_AxisEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_AxisEvent_VoidSync);
        case Kind_Callback_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_BooleanSync);
        case Kind_Callback_Boolean_HoverEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Boolean_HoverEvent_VoidSync);
        case Kind_Callback_Boolean_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Boolean_VoidSync);
        case Kind_Callback_Buffer_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Buffer_VoidSync);
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
        case Kind_Callback_ErrorInformation_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_ErrorInformation_VoidSync);
        case Kind_Callback_Extender_OnFinish: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Extender_OnFinishSync);
        case Kind_Callback_Extender_OnProgress: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Extender_OnProgressSync);
        case Kind_Callback_F64_F64_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_F64_F64_VoidSync);
        case Kind_Callback_F64_SliderChangeMode_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_F64_SliderChangeMode_VoidSync);
        case Kind_Callback_F64_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_F64_VoidSync);
        case Kind_Callback_FocusAxisEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_FocusAxisEvent_VoidSync);
        case Kind_Callback_FormCallbackInfo_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_FormCallbackInfo_VoidSync);
        case Kind_Callback_FullscreenInfo_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_FullscreenInfo_VoidSync);
        case Kind_Callback_GestureEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_GestureEvent_VoidSync);
        case Kind_Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_GestureInfo_BaseGestureEvent_GestureJudgeResultSync);
        case Kind_Callback_GestureJudgeResult_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_GestureJudgeResult_VoidSync);
        case Kind_Callback_GestureRecognizer_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_GestureRecognizer_VoidSync);
        case Kind_Callback_HitTestMode_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_HitTestMode_VoidSync);
        case Kind_Callback_HoverEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_HoverEvent_VoidSync);
        case Kind_Callback_I32_F64_ComputedBarAttribute: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_I32_F64_ComputedBarAttributeSync);
        case Kind_Callback_I32_I32_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_I32_I32_BooleanSync);
        case Kind_Callback_I32_I32_I32_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_I32_I32_I32_VoidSync);
        case Kind_Callback_I32_I32_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_I32_I32_VoidSync);
        case Kind_Callback_I32_Tuple_I32_I32: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_I32_Tuple_I32_I32Sync);
        case Kind_Callback_I32_Tuple_I32_I32_I32_I32: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_I32_Tuple_I32_I32_I32_I32Sync);
        case Kind_Callback_I64_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_I64_VoidSync);
        case Kind_Callback_I32_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_I32_VoidSync);
        case Kind_Callback_InsertValue_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_InsertValue_BooleanSync);
        case Kind_Callback_InsertValue_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_InsertValue_VoidSync);
        case Kind_Callback_ItemDragInfo_I32_I32_Boolean_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_ItemDragInfo_I32_I32_Boolean_VoidSync);
        case Kind_Callback_ItemDragInfo_I32_I32_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_ItemDragInfo_I32_I32_VoidSync);
        case Kind_Callback_ItemDragInfo_I32_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_ItemDragInfo_I32_VoidSync);
        case Kind_Callback_ItemDragInfo_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_ItemDragInfo_VoidSync);
        case Kind_Callback_KeyEvent_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_KeyEvent_BooleanSync);
        case Kind_Callback_KeyEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_KeyEvent_VoidSync);
        case Kind_Callback_Long_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Long_VoidSync);
        case Kind_Callback_Map_String_RecordData_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Map_String_RecordData_VoidSync);
        case Kind_Callback_MarqueeState_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_MarqueeState_VoidSync);
        case Kind_Callback_MouseEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_MouseEvent_VoidSync);
        case Kind_Callback_NativeEmbedDataInfo_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_NativeEmbedDataInfo_VoidSync);
        case Kind_Callback_NativeEmbedTouchInfo_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_NativeEmbedTouchInfo_VoidSync);
        case Kind_Callback_NativeXComponentPointer_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_NativeXComponentPointer_VoidSync);
        case Kind_Callback_NavDestinationActiveReason_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_NavDestinationActiveReason_VoidSync);
        case Kind_Callback_NavDestinationContext_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_NavDestinationContext_VoidSync);
        case Kind_Callback_NavigationMode_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_NavigationMode_VoidSync);
        case Kind_Callback_NavigationTitleMode_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_NavigationTitleMode_VoidSync);
        case Kind_Callback_NavigationTransitionProxy_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_NavigationTransitionProxy_VoidSync);
        case Kind_Callback_Number_Number_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Number_Number_VoidSync);
        case Kind_Callback_Number_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Number_VoidSync);
        case Kind_Callback_Object_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Object_VoidSync);
        case Kind_Callback_OnAlertEvent_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnAlertEvent_BooleanSync);
        case Kind_Callback_OnAudioStateChangedEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnAudioStateChangedEvent_VoidSync);
        case Kind_Callback_OnBeforeUnloadEvent_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnBeforeUnloadEvent_BooleanSync);
        case Kind_Callback_OnClientAuthenticationEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnClientAuthenticationEvent_VoidSync);
        case Kind_Callback_OnConfirmEvent_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnConfirmEvent_BooleanSync);
        case Kind_Callback_OnConsoleEvent_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnConsoleEvent_BooleanSync);
        case Kind_Callback_OnContextMenuShowEvent_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnContextMenuShowEvent_BooleanSync);
        case Kind_Callback_OnDataResubmittedEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnDataResubmittedEvent_VoidSync);
        case Kind_Callback_OnDestory_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnDestory_VoidSync);
        case Kind_Callback_OnDownloadStartEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnDownloadStartEvent_VoidSync);
        case Kind_Callback_OnErrorReceiveEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnErrorReceiveEvent_VoidSync);
        case Kind_Callback_OnFaviconReceivedEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnFaviconReceivedEvent_VoidSync);
        case Kind_Callback_OnFirstContentfulPaintEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnFirstContentfulPaintEvent_VoidSync);
        case Kind_Callback_OnGeolocationShowEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnGeolocationShowEvent_VoidSync);
        case Kind_Callback_OnHttpAuthRequestEvent_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnHttpAuthRequestEvent_BooleanSync);
        case Kind_Callback_OnHttpErrorReceiveEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnHttpErrorReceiveEvent_VoidSync);
        case Kind_Callback_OnLoadFinishedEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnLoadFinishedEvent_VoidSync);
        case Kind_Callback_OnLoadInterceptEvent_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnLoadInterceptEvent_BooleanSync);
        case Kind_Callback_OnLoadStartedEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnLoadStartedEvent_VoidSync);
        case Kind_Callback_onMeasureSize_SizeResult: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_onMeasureSize_SizeResultSync);
        case Kind_Callback_OnMoveFromTo: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnMoveFromToSync);
        case Kind_Callback_OnOverScrollEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnOverScrollEvent_VoidSync);
        case Kind_Callback_OnPageBeginEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnPageBeginEvent_VoidSync);
        case Kind_Callback_OnPageEndEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnPageEndEvent_VoidSync);
        case Kind_Callback_OnPageVisibleEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnPageVisibleEvent_VoidSync);
        case Kind_Callback_OnPdfLoadEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnPdfLoadEvent_VoidSync);
        case Kind_Callback_OnPdfScrollEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnPdfScrollEvent_VoidSync);
        case Kind_Callback_OnPermissionRequestEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_OnPermissionRequestEvent_VoidSync);
        case Kind_Callback_onPlaceChildren_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_onPlaceChildren_VoidSync);
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
        case Kind_Callback_Opt_CustomBuilder_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Opt_CustomBuilder_VoidSync);
        case Kind_Callback_Opt_NavigationAnimatedTransition_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Opt_NavigationAnimatedTransition_VoidSync);
        case Kind_Callback_Opt_OffsetResult_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Opt_OffsetResult_VoidSync);
        case Kind_Callback_Opt_ScrollResult_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Opt_ScrollResult_VoidSync);
        case Kind_Callback_Opt_StyledString_Opt_Array_String_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Opt_StyledString_Opt_Array_String_VoidSync);
        case Kind_Callback_Opt_TabContentAnimatedTransition_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Opt_TabContentAnimatedTransition_VoidSync);
        case Kind_Callback_Opt_WebResourceResponse_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Opt_WebResourceResponse_VoidSync);
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
        case Kind_Callback_RouterCallbackInfo_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_RouterCallbackInfo_VoidSync);
        case Kind_Callback_SheetDismiss_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_SheetDismiss_VoidSync);
        case Kind_Callback_SheetType_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_SheetType_VoidSync);
        case Kind_Callback_Size_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Size_VoidSync);
        case Kind_Callback_SizeResult_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_SizeResult_VoidSync);
        case Kind_Callback_SpringBackAction_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_SpringBackAction_VoidSync);
        case Kind_Callback_StateStylesChange: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_StateStylesChangeSync);
        case Kind_Callback_String_PasteEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_String_PasteEvent_VoidSync);
        case Kind_Callback_String_SurfaceRect_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_String_SurfaceRect_VoidSync);
        case Kind_Callback_String_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_String_VoidSync);
        case Kind_Callback_StyledStringChangeValue_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_StyledStringChangeValue_BooleanSync);
        case Kind_Callback_StyledStringMarshallingValue_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_StyledStringMarshallingValue_VoidSync);
        case Kind_Callback_SwipeActionState_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_SwipeActionState_VoidSync);
        case Kind_Callback_SwiperContentTransitionProxy_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_SwiperContentTransitionProxy_VoidSync);
        case Kind_Callback_T_Void_Arkui_Component_Units_Length: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_T_Void_Arkui_Component_Units_LengthSync);
        case Kind_Callback_T_Void_Arkui_Component_Units_ResourceStr: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_T_Void_Arkui_Component_Units_ResourceStrSync);
        case Kind_Callback_T_Void_Array_Arkui_Component_Units_ResourceStr: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_T_Void_Array_Arkui_Component_Units_ResourceStrSync);
        case Kind_Callback_T_Void_Array_Global_Resource_Resource: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_T_Void_Array_Global_Resource_ResourceSync);
        case Kind_Callback_T_Void_Array_I32: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_T_Void_Array_I32Sync);
        case Kind_Callback_T_Void_Array_String: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_T_Void_Array_StringSync);
        case Kind_Callback_T_Void_Boolean: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_T_Void_BooleanSync);
        case Kind_Callback_T_Void_Date: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_T_Void_DateSync);
        case Kind_Callback_T_Void_F64: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_T_Void_F64Sync);
        case Kind_Callback_T_Void_Global_Resource_Resource: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_T_Void_Global_Resource_ResourceSync);
        case Kind_Callback_T_Void_I32: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_T_Void_I32Sync);
        case Kind_Callback_T_Void_Number: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_T_Void_NumberSync);
        case Kind_Callback_T_Void_String: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_T_Void_StringSync);
        case Kind_Callback_TabContentTransitionProxy_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_TabContentTransitionProxy_VoidSync);
        case Kind_Callback_TerminationInfo_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_TerminationInfo_VoidSync);
        case Kind_Callback_TextPickerResult_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_TextPickerResult_VoidSync);
        case Kind_Callback_TextRange_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_TextRange_VoidSync);
        case Kind_Callback_TimePickerResult_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_TimePickerResult_VoidSync);
        case Kind_Callback_TouchEvent_HitTestMode: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_TouchEvent_HitTestModeSync);
        case Kind_Callback_TouchEvent_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_TouchEvent_VoidSync);
        case Kind_Callback_TouchResult_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_TouchResult_VoidSync);
        case Kind_Callback_Tuple_I32_I32_I32_I32_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Tuple_I32_I32_I32_I32_VoidSync);
        case Kind_Callback_Tuple_I32_I32_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Tuple_I32_I32_VoidSync);
        case Kind_Callback_UIExtensionProxy_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_UIExtensionProxy_VoidSync);
        case Kind_Callback_Union_CustomBuilder_DragItemInfo_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Union_CustomBuilder_DragItemInfo_VoidSync);
        case Kind_Callback_Union_Object_Idlize_Stdlib_Null_Undefined_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_Union_Object_Idlize_Stdlib_Null_Undefined_VoidSync);
        case Kind_Callback_VisibilityChangeReason_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_VisibilityChangeReason_VoidSync);
        case Kind_Callback_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_VoidSync);
        case Kind_Callback_WebKeyboardOptions_Void: return reinterpret_cast<Ark_NativePointer>(callManagedCallback_WebKeyboardOptions_VoidSync);
        case Kind_CheckBoxGroupModifierBuilder: return reinterpret_cast<Ark_NativePointer>(callManagedCheckBoxGroupModifierBuilderSync);
        case Kind_CheckBoxModifierBuilder: return reinterpret_cast<Ark_NativePointer>(callManagedCheckBoxModifierBuilderSync);
        case Kind_ContentDidScrollCallback: return reinterpret_cast<Ark_NativePointer>(callManagedContentDidScrollCallbackSync);
        case Kind_ContentWillScrollCallback: return reinterpret_cast<Ark_NativePointer>(callManagedContentWillScrollCallbackSync);
        case Kind_CustomBuilderT_Arkui_Component_Enums_ResponseType: return reinterpret_cast<Ark_NativePointer>(callManagedCustomBuilderT_Arkui_Component_Enums_ResponseTypeSync);
        case Kind_CustomBuilderT_I32: return reinterpret_cast<Ark_NativePointer>(callManagedCustomBuilderT_I32Sync);
        case Kind_CustomNodeBuilder: return reinterpret_cast<Ark_NativePointer>(callManagedCustomNodeBuilderSync);
        case Kind_DataPanelModifierBuilder: return reinterpret_cast<Ark_NativePointer>(callManagedDataPanelModifierBuilderSync);
        case Kind_EditableTextOnChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedEditableTextOnChangeCallbackSync);
        case Kind_ErrorCallback_Ohos_Base_BusinessError: return reinterpret_cast<Ark_NativePointer>(callManagedErrorCallback_Ohos_Base_BusinessErrorSync);
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
        case Kind_MouseInfoCallback: return reinterpret_cast<Ark_NativePointer>(callManagedMouseInfoCallbackSync);
        case Kind_NavDestinationTransitionDelegate: return reinterpret_cast<Ark_NativePointer>(callManagedNavDestinationTransitionDelegateSync);
        case Kind_NavExtender_CreateNavDestination: return reinterpret_cast<Ark_NativePointer>(callManagedNavExtender_CreateNavDestinationSync);
        case Kind_NavExtender_OnUpdateStack: return reinterpret_cast<Ark_NativePointer>(callManagedNavExtender_OnUpdateStackSync);
        case Kind_NavExtender_PageMapNodeBuilder: return reinterpret_cast<Ark_NativePointer>(callManagedNavExtender_PageMapNodeBuilderSync);
        case Kind_OnAdsBlockedCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnAdsBlockedCallbackSync);
        case Kind_OnAlphabetIndexerPopupSelectCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnAlphabetIndexerPopupSelectCallbackSync);
        case Kind_OnAlphabetIndexerRequestPopupDataCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnAlphabetIndexerRequestPopupDataCallbackSync);
        case Kind_OnAlphabetIndexerSelectCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnAlphabetIndexerSelectCallbackSync);
        case Kind_OnCheckboxChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnCheckboxChangeCallbackSync);
        case Kind_OnCheckboxGroupChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnCheckboxGroupChangeCallbackSync);
        case Kind_OnContentScrollCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnContentScrollCallbackSync);
        case Kind_OnContextMenuHideCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnContextMenuHideCallbackSync);
        case Kind_OnCreateMenuCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnCreateMenuCallbackSync);
        case Kind_OnDetectBlankScreenCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnDetectBlankScreenCallbackSync);
        case Kind_OnDidChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnDidChangeCallbackSync);
        case Kind_OnDragEventCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnDragEventCallbackSync);
        case Kind_OnFirstMeaningfulPaintCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnFirstMeaningfulPaintCallbackSync);
        case Kind_OnFoldStatusChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnFoldStatusChangeCallbackSync);
        case Kind_OnFullScreenEnterCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnFullScreenEnterCallbackSync);
        case Kind_OnHoverCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnHoverCallbackSync);
        case Kind_OnHoverStatusChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnHoverStatusChangeCallbackSync);
        case Kind_OnIntelligentTrackingPreventionCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnIntelligentTrackingPreventionCallbackSync);
        case Kind_OnItemDragStartCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnItemDragStartCallbackSync);
        case Kind_OnLargestContentfulPaintCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnLargestContentfulPaintCallbackSync);
        case Kind_OnLinearIndicatorChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnLinearIndicatorChangeCallbackSync);
        case Kind_OnMenuItemClickCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnMenuItemClickCallbackSync);
        case Kind_OnMoveHandler: return reinterpret_cast<Ark_NativePointer>(callManagedOnMoveHandlerSync);
        case Kind_OnNativeEmbedObjectParamChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnNativeEmbedObjectParamChangeCallbackSync);
        case Kind_OnNativeEmbedVisibilityChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnNativeEmbedVisibilityChangeCallbackSync);
        case Kind_OnNavigationEntryCommittedCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnNavigationEntryCommittedCallbackSync);
        case Kind_OnOverrideErrorPageCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnOverrideErrorPageCallbackSync);
        case Kind_OnOverrideUrlLoadingCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnOverrideUrlLoadingCallbackSync);
        case Kind_OnPasteCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnPasteCallbackSync);
        case Kind_OnPickerCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnPickerCallbackSync);
        case Kind_OnRadioChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnRadioChangeCallbackSync);
        case Kind_OnRatingChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnRatingChangeCallbackSync);
        case Kind_OnRenderProcessNotRespondingCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnRenderProcessNotRespondingCallbackSync);
        case Kind_OnRenderProcessRespondingCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnRenderProcessRespondingCallbackSync);
        case Kind_OnSafeBrowsingCheckResultCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnSafeBrowsingCheckResultCallbackSync);
        case Kind_OnScrollCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnScrollCallbackSync);
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
        case Kind_OnTabsContentDidScrollCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnTabsContentDidScrollCallbackSync);
        case Kind_OnTabsContentWillChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnTabsContentWillChangeCallbackSync);
        case Kind_OnTabsGestureSwipeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnTabsGestureSwipeCallbackSync);
        case Kind_OnTextPickerChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnTextPickerChangeCallbackSync);
        case Kind_OnTextSelectionChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnTextSelectionChangeCallbackSync);
        case Kind_OnTimePickerChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnTimePickerChangeCallbackSync);
        case Kind_OnViewportFitChangedCallback: return reinterpret_cast<Ark_NativePointer>(callManagedOnViewportFitChangedCallbackSync);
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
        case Kind_RouterFinishCallback: return reinterpret_cast<Ark_NativePointer>(callManagedRouterFinishCallbackSync);
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
        case Kind_TextSelectionChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedTextSelectionChangeCallbackSync);
        case Kind_TextTimerModifierBuilder: return reinterpret_cast<Ark_NativePointer>(callManagedTextTimerModifierBuilderSync);
        case Kind_TimerCallback: return reinterpret_cast<Ark_NativePointer>(callManagedTimerCallbackSync);
        case Kind_ToggleModifierBuilder: return reinterpret_cast<Ark_NativePointer>(callManagedToggleModifierBuilderSync);
        case Kind_TransitionFinishCallback: return reinterpret_cast<Ark_NativePointer>(callManagedTransitionFinishCallbackSync);
        case Kind_Type_CommonMethod_onDragStart: return reinterpret_cast<Ark_NativePointer>(callManagedType_CommonMethod_onDragStartSync);
        case Kind_Type_NavigationAttribute_customNavContentTransition: return reinterpret_cast<Ark_NativePointer>(callManagedType_NavigationAttribute_customNavContentTransitionSync);
        case Kind_Type_WebAttribute_onInterceptRequest: return reinterpret_cast<Ark_NativePointer>(callManagedType_WebAttribute_onInterceptRequestSync);
        case Kind_UpdateTransitionCallback: return reinterpret_cast<Ark_NativePointer>(callManagedUpdateTransitionCallbackSync);
        case Kind_VisibleAreaChangeCallback: return reinterpret_cast<Ark_NativePointer>(callManagedVisibleAreaChangeCallbackSync);
        case Kind_VoidCallback: return reinterpret_cast<Ark_NativePointer>(callManagedVoidCallbackSync);
        case Kind_WebKeyboardCallback: return reinterpret_cast<Ark_NativePointer>(callManagedWebKeyboardCallbackSync);
        case Kind_WorkerEventListener: return reinterpret_cast<Ark_NativePointer>(callManagedWorkerEventListenerSync);
    }
    return nullptr;
}
