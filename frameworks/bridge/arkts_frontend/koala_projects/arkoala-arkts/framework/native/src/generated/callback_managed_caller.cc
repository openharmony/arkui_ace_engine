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

#define API_KIND 10
void CallManagedAccessibilityActionInterceptCallback(Ark_Int32 resourceId, Ark_AccessibilityAction action,
                                                     Callback_AccessibilityActionInterceptResult_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_ACCESSIBILITYACTIONINTERCEPTCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_AccessibilityAction>(action));
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedAccessibilityActionInterceptCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                         Ark_AccessibilityAction action,
                                                         Callback_AccessibilityActionInterceptResult_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_ACCESSIBILITYACTIONINTERCEPTCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_AccessibilityAction>(action));
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedAccessibilityCallback(Ark_Int32 resourceId, Ark_Boolean isHover, Ark_AccessibilityHoverEvent event)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_ACCESSIBILITYCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(isHover);
    AccessibilityHoverEvent_serializer::write(argsSerializer, event);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedAccessibilityCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Boolean isHover,
                                          Ark_AccessibilityHoverEvent event)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_ACCESSIBILITYCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(isHover);
    AccessibilityHoverEvent_serializer::write(argsSerializer, event);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedAccessibilityFocusCallback(Ark_Int32 resourceId, Ark_Boolean isFocus)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_ACCESSIBILITYFOCUSCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(isFocus);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedAccessibilityFocusCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Boolean isFocus)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_ACCESSIBILITYFOCUSCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(isFocus);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedAccessibilityTransparentCallback(Ark_Int32 resourceId, Ark_TouchEvent event)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_ACCESSIBILITYTRANSPARENTCALLBACK);
    argsSerializer.writeInt32(resourceId);
    TouchEvent_serializer::write(argsSerializer, event);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedAccessibilityTransparentCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                     Ark_TouchEvent event)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_ACCESSIBILITYTRANSPARENTCALLBACK);
    argsSerializer.writeInt32(resourceId);
    TouchEvent_serializer::write(argsSerializer, event);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedButtonModifierBuilder(Ark_Int32 resourceId, Ark_NativePointer parentNode,
                                      Ark_ButtonConfiguration config, Callback_Pointer_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_BUTTONMODIFIERBUILDER);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    ButtonConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedButtonModifierBuilderSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NativePointer parentNode,
                                          Ark_ButtonConfiguration config, Callback_Pointer_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_BUTTONMODIFIERBUILDER);
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
void CallManagedButtonTriggerClickCallback(Ark_Int32 resourceId, Ark_Float64 xPos, Ark_Float64 yPos)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_BUTTONTRIGGERCLICKCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFloat64(xPos);
    argsSerializer.writeFloat64(yPos);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedButtonTriggerClickCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Float64 xPos,
                                               Ark_Float64 yPos)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_BUTTONTRIGGERCLICKCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFloat64(xPos);
    argsSerializer.writeFloat64(yPos);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_AccessibilityActionInterceptResult_Void(Ark_Int32 resourceId,
                                                                 Ark_AccessibilityActionInterceptResult value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_ACCESSIBILITYACTIONINTERCEPTRESULT_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_AccessibilityActionInterceptResult>(value));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_AccessibilityActionInterceptResult_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                                     Ark_AccessibilityActionInterceptResult value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_ACCESSIBILITYACTIONINTERCEPTRESULT_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_AccessibilityActionInterceptResult>(value));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_Area_Area_Void(Ark_Int32 resourceId, Ark_Area oldValue, Ark_Area newValue)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_AREA_AREA_VOID);
    argsSerializer.writeInt32(resourceId);
    Area_serializer::write(argsSerializer, oldValue);
    Area_serializer::write(argsSerializer, newValue);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_Area_Area_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Area oldValue,
                                            Ark_Area newValue)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_AREA_AREA_VOID);
    argsSerializer.writeInt32(resourceId);
    Area_serializer::write(argsSerializer, oldValue);
    Area_serializer::write(argsSerializer, newValue);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_Array_I32_Void(Ark_Int32 resourceId, Array_I32 data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_ARRAY_I32_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(data.length);
    for (int dataCounterI = 0; dataCounterI < data.length; dataCounterI++)
    {
        const Ark_Int32 dataTmpElement = data.array[dataCounterI];
        argsSerializer.writeInt32(dataTmpElement);
    }
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_Array_I32_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Array_I32 data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_ARRAY_I32_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(data.length);
    for (int dataCounterI = 0; dataCounterI < data.length; dataCounterI++)
    {
        const Ark_Int32 dataTmpElement = data.array[dataCounterI];
        argsSerializer.writeInt32(dataTmpElement);
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_Array_Resource_Void(Ark_Int32 resourceId, Array_Resource data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_ARRAY_RESOURCE_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(data.length);
    for (int dataCounterI = 0; dataCounterI < data.length; dataCounterI++)
    {
        const Ark_Resource dataTmpElement = data.array[dataCounterI];
        Resource_serializer::write(argsSerializer, dataTmpElement);
    }
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_Array_Resource_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Array_Resource data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_ARRAY_RESOURCE_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(data.length);
    for (int dataCounterI = 0; dataCounterI < data.length; dataCounterI++)
    {
        const Ark_Resource dataTmpElement = data.array[dataCounterI];
        Resource_serializer::write(argsSerializer, dataTmpElement);
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_Array_ResourceStr_Void(Ark_Int32 resourceId, Array_ResourceStr data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_ARRAY_RESOURCESTR_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(data.length);
    for (int dataCounterI = 0; dataCounterI < data.length; dataCounterI++)
    {
        const Ark_ResourceStr dataTmpElement = data.array[dataCounterI];
        if (dataTmpElement.selector == 0)
        {
            argsSerializer.writeInt8(0);
            const auto dataTmpElementForIdx0 = dataTmpElement.value0;
            argsSerializer.writeString(dataTmpElementForIdx0);
        }
        else if (dataTmpElement.selector == 1)
        {
            argsSerializer.writeInt8(1);
            const auto dataTmpElementForIdx1 = dataTmpElement.value1;
            Resource_serializer::write(argsSerializer, dataTmpElementForIdx1);
        }
    }
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_Array_ResourceStr_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                    Array_ResourceStr data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_ARRAY_RESOURCESTR_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(data.length);
    for (int dataCounterI = 0; dataCounterI < data.length; dataCounterI++)
    {
        const Ark_ResourceStr dataTmpElement = data.array[dataCounterI];
        if (dataTmpElement.selector == 0)
        {
            argsSerializer.writeInt8(0);
            const auto dataTmpElementForIdx0 = dataTmpElement.value0;
            argsSerializer.writeString(dataTmpElementForIdx0);
        }
        else if (dataTmpElement.selector == 1)
        {
            argsSerializer.writeInt8(1);
            const auto dataTmpElementForIdx1 = dataTmpElement.value1;
            Resource_serializer::write(argsSerializer, dataTmpElementForIdx1);
        }
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_Array_String_Void(Ark_Int32 resourceId, Array_String data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_ARRAY_STRING_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(data.length);
    for (int dataCounterI = 0; dataCounterI < data.length; dataCounterI++)
    {
        const Ark_String dataTmpElement = data.array[dataCounterI];
        argsSerializer.writeString(dataTmpElement);
    }
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_Array_String_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Array_String data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_ARRAY_STRING_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(data.length);
    for (int dataCounterI = 0; dataCounterI < data.length; dataCounterI++)
    {
        const Ark_String dataTmpElement = data.array[dataCounterI];
        argsSerializer.writeString(dataTmpElement);
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_Array_TextMenuItem_Void(Ark_Int32 resourceId, Array_TextMenuItem value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_ARRAY_TEXTMENUITEM_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(value.length);
    for (int valueCounterI = 0; valueCounterI < value.length; valueCounterI++)
    {
        const Ark_TextMenuItem valueTmpElement = value.array[valueCounterI];
        TextMenuItem_serializer::write(argsSerializer, valueTmpElement);
    }
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_Array_TextMenuItem_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                     Array_TextMenuItem value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_ARRAY_TEXTMENUITEM_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(value.length);
    for (int valueCounterI = 0; valueCounterI < value.length; valueCounterI++)
    {
        const Ark_TextMenuItem valueTmpElement = value.array[valueCounterI];
        TextMenuItem_serializer::write(argsSerializer, valueTmpElement);
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_Array_TouchTestInfo_TouchResult(Ark_Int32 resourceId, Array_TouchTestInfo value,
                                                         Callback_TouchResult_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_ARRAY_TOUCHTESTINFO_TOUCHRESULT);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(value.length);
    for (int valueCounterI = 0; valueCounterI < value.length; valueCounterI++)
    {
        const Ark_TouchTestInfo valueTmpElement = value.array[valueCounterI];
        TouchTestInfo_serializer::write(argsSerializer, valueTmpElement);
    }
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_Array_TouchTestInfo_TouchResultSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                             Array_TouchTestInfo value,
                                                             Callback_TouchResult_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_ARRAY_TOUCHTESTINFO_TOUCHRESULT);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(value.length);
    for (int valueCounterI = 0; valueCounterI < value.length; valueCounterI++)
    {
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
void CallManagedCallback_AxisEvent_Void(Ark_Int32 resourceId, Ark_AxisEvent data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_AXISEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    AxisEvent_serializer::write(argsSerializer, data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_AxisEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_AxisEvent data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_AXISEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    AxisEvent_serializer::write(argsSerializer, data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_Boolean(Ark_Int32 resourceId, synthetic_Callback_Boolean_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_BOOLEAN);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                     synthetic_Callback_Boolean_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_BOOLEAN);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_Boolean_HoverEvent_Void(Ark_Int32 resourceId, Ark_Boolean isHover, Ark_HoverEvent event)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_BOOLEAN_HOVEREVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(isHover);
    HoverEvent_serializer::write(argsSerializer, event);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_Boolean_HoverEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Boolean isHover,
                                                     Ark_HoverEvent event)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_BOOLEAN_HOVEREVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(isHover);
    HoverEvent_serializer::write(argsSerializer, event);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_Boolean_Void(Ark_Int32 resourceId, Ark_Boolean data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_BOOLEAN_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_Boolean_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Boolean data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_BOOLEAN_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_Buffer_Void(Ark_Int32 resourceId, Ark_Buffer value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_BUFFER_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBuffer(value);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_Buffer_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Buffer value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_BUFFER_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBuffer(value);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_BusinessError_Void(Ark_Int32 resourceId, Ark_Int32 code, Ark_String message)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_BUSINESSERROR_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(code);
    argsSerializer.writeString(message);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_BusinessError_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 code,
                                                Ark_String message)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_BUSINESSERROR_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(code);
    argsSerializer.writeString(message);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_ClickEvent_Void(Ark_Int32 resourceId, Ark_ClickEvent event)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_CLICKEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    ClickEvent_serializer::write(argsSerializer, event);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_ClickEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_ClickEvent event)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_CLICKEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    ClickEvent_serializer::write(argsSerializer, event);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_ComputedBarAttribute_Void(Ark_Int32 resourceId, Ark_ComputedBarAttribute value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_COMPUTEDBARATTRIBUTE_VOID);
    argsSerializer.writeInt32(resourceId);
    ComputedBarAttribute_serializer::write(argsSerializer, value);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_ComputedBarAttribute_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                       Ark_ComputedBarAttribute value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_COMPUTEDBARATTRIBUTE_VOID);
    argsSerializer.writeInt32(resourceId);
    ComputedBarAttribute_serializer::write(argsSerializer, value);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_CopyEvent_Void(Ark_Int32 resourceId, Ark_CopyEvent data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_COPYEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    CopyEvent_serializer::write(argsSerializer, data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_CopyEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_CopyEvent data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_COPYEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    CopyEvent_serializer::write(argsSerializer, data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_CreateItem(Ark_Int32 resourceId, Ark_Int32 index, Callback_Pointer_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_CREATEITEM);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_CreateItemSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 index,
                                        Callback_Pointer_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_CREATEITEM);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_CrownEvent_Void(Ark_Int32 resourceId, Ark_CrownEvent data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_CROWNEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    CrownEvent_serializer::write(argsSerializer, data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_CrownEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_CrownEvent data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_CROWNEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    CrownEvent_serializer::write(argsSerializer, data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_CustomSpanMeasureInfo_CustomSpanMetrics(Ark_Int32 resourceId,
                                                                 Ark_CustomSpanMeasureInfo measureInfo,
                                                                 Callback_CustomSpanMetrics_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_CUSTOMSPANMEASUREINFO_CUSTOMSPANMETRICS);
    argsSerializer.writeInt32(resourceId);
    CustomSpanMeasureInfo_serializer::write(argsSerializer, measureInfo);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_CustomSpanMeasureInfo_CustomSpanMetricsSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                                     Ark_CustomSpanMeasureInfo measureInfo,
                                                                     Callback_CustomSpanMetrics_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_CUSTOMSPANMEASUREINFO_CUSTOMSPANMETRICS);
    argsSerializer.writeInt32(resourceId);
    CustomSpanMeasureInfo_serializer::write(argsSerializer, measureInfo);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_CustomSpanMetrics_Void(Ark_Int32 resourceId, Ark_CustomSpanMetrics value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_CUSTOMSPANMETRICS_VOID);
    argsSerializer.writeInt32(resourceId);
    CustomSpanMetrics_serializer::write(argsSerializer, value);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_CustomSpanMetrics_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                    Ark_CustomSpanMetrics value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_CUSTOMSPANMETRICS_VOID);
    argsSerializer.writeInt32(resourceId);
    CustomSpanMetrics_serializer::write(argsSerializer, value);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_CutEvent_Void(Ark_Int32 resourceId, Ark_CutEvent data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_CUTEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    CutEvent_serializer::write(argsSerializer, data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_CutEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_CutEvent data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_CUTEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    CutEvent_serializer::write(argsSerializer, data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_Date_Void(Ark_Int32 resourceId, Ark_Date data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_DATE_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt64(data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_Date_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Date data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_DATE_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt64(data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_DeleteValue_Boolean(Ark_Int32 resourceId, Ark_DeleteValue data,
                                             synthetic_Callback_Boolean_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_DELETEVALUE_BOOLEAN);
    argsSerializer.writeInt32(resourceId);
    DeleteValue_serializer::write(argsSerializer, data);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_DeleteValue_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_DeleteValue data,
                                                 synthetic_Callback_Boolean_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_DELETEVALUE_BOOLEAN);
    argsSerializer.writeInt32(resourceId);
    DeleteValue_serializer::write(argsSerializer, data);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_DeleteValue_Void(Ark_Int32 resourceId, Ark_DeleteValue data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_DELETEVALUE_VOID);
    argsSerializer.writeInt32(resourceId);
    DeleteValue_serializer::write(argsSerializer, data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_DeleteValue_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_DeleteValue data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_DELETEVALUE_VOID);
    argsSerializer.writeInt32(resourceId);
    DeleteValue_serializer::write(argsSerializer, data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_DismissContentCoverAction_Void(Ark_Int32 resourceId, Ark_DismissContentCoverAction data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_DISMISSCONTENTCOVERACTION_VOID);
    argsSerializer.writeInt32(resourceId);
    DismissContentCoverAction_serializer::write(argsSerializer, data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_DismissContentCoverAction_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                            Ark_DismissContentCoverAction data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_DISMISSCONTENTCOVERACTION_VOID);
    argsSerializer.writeInt32(resourceId);
    DismissContentCoverAction_serializer::write(argsSerializer, data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_DismissDialogAction_Void(Ark_Int32 resourceId, Ark_DismissDialogAction data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_DISMISSDIALOGACTION_VOID);
    argsSerializer.writeInt32(resourceId);
    DismissDialogAction_serializer::write(argsSerializer, data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_DismissDialogAction_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                      Ark_DismissDialogAction data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_DISMISSDIALOGACTION_VOID);
    argsSerializer.writeInt32(resourceId);
    DismissDialogAction_serializer::write(argsSerializer, data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_DismissPopupAction_Void(Ark_Int32 resourceId, Ark_DismissPopupAction data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_DISMISSPOPUPACTION_VOID);
    argsSerializer.writeInt32(resourceId);
    DismissPopupAction_serializer::write(argsSerializer, data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_DismissPopupAction_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                     Ark_DismissPopupAction data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_DISMISSPOPUPACTION_VOID);
    argsSerializer.writeInt32(resourceId);
    DismissPopupAction_serializer::write(argsSerializer, data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_DismissSheetAction_Void(Ark_Int32 resourceId, Ark_DismissSheetAction data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_DISMISSSHEETACTION_VOID);
    argsSerializer.writeInt32(resourceId);
    DismissSheetAction_serializer::write(argsSerializer, data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_DismissSheetAction_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                     Ark_DismissSheetAction data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_DISMISSSHEETACTION_VOID);
    argsSerializer.writeInt32(resourceId);
    DismissSheetAction_serializer::write(argsSerializer, data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_DragEvent_Opt_String_Void(Ark_Int32 resourceId, Ark_DragEvent event, Opt_String extraParams)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_DRAGEVENT_OPT_STRING_VOID);
    argsSerializer.writeInt32(resourceId);
    DragEvent_serializer::write(argsSerializer, event);
    if (runtimeType(extraParams) != INTEROP_RUNTIME_UNDEFINED)
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto extraParamsTmpValue = extraParams.value;
        argsSerializer.writeString(extraParamsTmpValue);
    }
    else
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_DragEvent_Opt_String_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                       Ark_DragEvent event, Opt_String extraParams)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_DRAGEVENT_OPT_STRING_VOID);
    argsSerializer.writeInt32(resourceId);
    DragEvent_serializer::write(argsSerializer, event);
    if (runtimeType(extraParams) != INTEROP_RUNTIME_UNDEFINED)
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto extraParamsTmpValue = extraParams.value;
        argsSerializer.writeString(extraParamsTmpValue);
    }
    else
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_DrawContext_CustomSpanDrawInfo_Void(Ark_Int32 resourceId, Ark_DrawContext context,
                                                             Ark_CustomSpanDrawInfo drawInfo)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_DRAWCONTEXT_CUSTOMSPANDRAWINFO_VOID);
    argsSerializer.writeInt32(resourceId);
    DrawContext_serializer::write(argsSerializer, context);
    CustomSpanDrawInfo_serializer::write(argsSerializer, drawInfo);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_DrawContext_CustomSpanDrawInfo_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                                 Ark_DrawContext context,
                                                                 Ark_CustomSpanDrawInfo drawInfo)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_DRAWCONTEXT_CUSTOMSPANDRAWINFO_VOID);
    argsSerializer.writeInt32(resourceId);
    DrawContext_serializer::write(argsSerializer, context);
    CustomSpanDrawInfo_serializer::write(argsSerializer, drawInfo);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_DrawContext_Void(Ark_Int32 resourceId, Ark_DrawContext drawContext)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_DRAWCONTEXT_VOID);
    argsSerializer.writeInt32(resourceId);
    DrawContext_serializer::write(argsSerializer, drawContext);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_DrawContext_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                              Ark_DrawContext drawContext)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_DRAWCONTEXT_VOID);
    argsSerializer.writeInt32(resourceId);
    DrawContext_serializer::write(argsSerializer, drawContext);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_EditableTextChangeValue_Boolean(Ark_Int32 resourceId, Ark_EditableTextChangeValue data,
                                                         synthetic_Callback_Boolean_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_EDITABLETEXTCHANGEVALUE_BOOLEAN);
    argsSerializer.writeInt32(resourceId);
    EditableTextChangeValue_serializer::write(argsSerializer, data);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_EditableTextChangeValue_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                             Ark_EditableTextChangeValue data,
                                                             synthetic_Callback_Boolean_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_EDITABLETEXTCHANGEVALUE_BOOLEAN);
    argsSerializer.writeInt32(resourceId);
    EditableTextChangeValue_serializer::write(argsSerializer, data);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_ErrorInformation_Void(Ark_Int32 resourceId, Ark_ErrorInformation data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_ERRORINFORMATION_VOID);
    argsSerializer.writeInt32(resourceId);
    ErrorInformation_serializer::write(argsSerializer, data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_ErrorInformation_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                   Ark_ErrorInformation data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_ERRORINFORMATION_VOID);
    argsSerializer.writeInt32(resourceId);
    ErrorInformation_serializer::write(argsSerializer, data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_Extender_OnFinish(Ark_Int32 resourceId)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_EXTENDER_ONFINISH);
    argsSerializer.writeInt32(resourceId);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_Extender_OnFinishSync(Ark_VMContext vmContext, Ark_Int32 resourceId)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_EXTENDER_ONFINISH);
    argsSerializer.writeInt32(resourceId);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_Extender_OnProgress(Ark_Int32 resourceId, Ark_Float32 value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_EXTENDER_ONPROGRESS);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFloat32(value);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_Extender_OnProgressSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Float32 value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_EXTENDER_ONPROGRESS);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFloat32(value);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_F64_F64_Void(Ark_Int32 resourceId, Ark_Float64 totalOffsetX, Ark_Float64 totalOffsetY)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_F64_F64_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFloat64(totalOffsetX);
    argsSerializer.writeFloat64(totalOffsetY);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_F64_F64_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Float64 totalOffsetX,
                                          Ark_Float64 totalOffsetY)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_F64_F64_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFloat64(totalOffsetX);
    argsSerializer.writeFloat64(totalOffsetY);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_F64_SliderChangeMode_Void(Ark_Int32 resourceId, Ark_Float64 value, Ark_SliderChangeMode mode)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_F64_SLIDERCHANGEMODE_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFloat64(value);
    argsSerializer.writeInt32(static_cast<Ark_SliderChangeMode>(mode));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_F64_SliderChangeMode_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Float64 value,
                                                       Ark_SliderChangeMode mode)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_F64_SLIDERCHANGEMODE_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFloat64(value);
    argsSerializer.writeInt32(static_cast<Ark_SliderChangeMode>(mode));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_F64_Void(Ark_Int32 resourceId, Ark_Float64 data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_F64_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFloat64(data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_F64_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Float64 data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_F64_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFloat64(data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_FocusAxisEvent_Void(Ark_Int32 resourceId, Ark_FocusAxisEvent data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_FOCUSAXISEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    FocusAxisEvent_serializer::write(argsSerializer, data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_FocusAxisEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_FocusAxisEvent data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_FOCUSAXISEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    FocusAxisEvent_serializer::write(argsSerializer, data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_FormCallbackInfo_Void(Ark_Int32 resourceId, Ark_FormCallbackInfo data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_FORMCALLBACKINFO_VOID);
    argsSerializer.writeInt32(resourceId);
    FormCallbackInfo_serializer::write(argsSerializer, data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_FormCallbackInfo_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                   Ark_FormCallbackInfo data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_FORMCALLBACKINFO_VOID);
    argsSerializer.writeInt32(resourceId);
    FormCallbackInfo_serializer::write(argsSerializer, data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_FullscreenInfo_Void(Ark_Int32 resourceId, Ark_FullscreenInfo data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_FULLSCREENINFO_VOID);
    argsSerializer.writeInt32(resourceId);
    FullscreenInfo_serializer::write(argsSerializer, data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_FullscreenInfo_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_FullscreenInfo data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_FULLSCREENINFO_VOID);
    argsSerializer.writeInt32(resourceId);
    FullscreenInfo_serializer::write(argsSerializer, data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_GestureEvent_Void(Ark_Int32 resourceId, Ark_GestureEvent data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_GESTUREEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    GestureEvent_serializer::write(argsSerializer, data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_GestureEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_GestureEvent data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_GESTUREEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    GestureEvent_serializer::write(argsSerializer, data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_GestureInfo_BaseGestureEvent_GestureJudgeResult(Ark_Int32 resourceId,
                                                                         Ark_GestureInfo gestureInfo,
                                                                         Ark_BaseGestureEvent event,
                                                                         Callback_GestureJudgeResult_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_GESTUREINFO_BASEGESTUREEVENT_GESTUREJUDGERESULT);
    argsSerializer.writeInt32(resourceId);
    GestureInfo_serializer::write(argsSerializer, gestureInfo);
    BaseGestureEvent_serializer::write(argsSerializer, event);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_GestureInfo_BaseGestureEvent_GestureJudgeResultSync(
    Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_GestureInfo gestureInfo, Ark_BaseGestureEvent event,
    Callback_GestureJudgeResult_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_GESTUREINFO_BASEGESTUREEVENT_GESTUREJUDGERESULT);
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
void CallManagedCallback_GestureJudgeResult_Void(Ark_Int32 resourceId, Ark_GestureJudgeResult value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_GESTUREJUDGERESULT_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_GestureJudgeResult>(value));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_GestureJudgeResult_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                     Ark_GestureJudgeResult value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_GESTUREJUDGERESULT_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_GestureJudgeResult>(value));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_GestureRecognizer_Void(Ark_Int32 resourceId, Ark_GestureRecognizer value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_GESTURERECOGNIZER_VOID);
    argsSerializer.writeInt32(resourceId);
    GestureRecognizer_serializer::write(argsSerializer, value);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_GestureRecognizer_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                    Ark_GestureRecognizer value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_GESTURERECOGNIZER_VOID);
    argsSerializer.writeInt32(resourceId);
    GestureRecognizer_serializer::write(argsSerializer, value);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_HitTestMode_Void(Ark_Int32 resourceId, Ark_HitTestMode value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_HITTESTMODE_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_HitTestMode>(value));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_HitTestMode_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_HitTestMode value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_HITTESTMODE_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_HitTestMode>(value));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_HoverEvent_Void(Ark_Int32 resourceId, Ark_HoverEvent data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_HOVEREVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    HoverEvent_serializer::write(argsSerializer, data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_HoverEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_HoverEvent data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_HOVEREVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    HoverEvent_serializer::write(argsSerializer, data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_I32_F64_ComputedBarAttribute(Ark_Int32 resourceId, Ark_Int32 index, Ark_Float64 offset,
                                                      Callback_ComputedBarAttribute_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_I32_F64_COMPUTEDBARATTRIBUTE);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    argsSerializer.writeFloat64(offset);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_I32_F64_ComputedBarAttributeSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                          Ark_Int32 index, Ark_Float64 offset,
                                                          Callback_ComputedBarAttribute_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_I32_F64_COMPUTEDBARATTRIBUTE);
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
void CallManagedCallback_I32_I32_Boolean(Ark_Int32 resourceId, Ark_Int32 from, Ark_Int32 to,
                                         synthetic_Callback_Boolean_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_I32_I32_BOOLEAN);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(from);
    argsSerializer.writeInt32(to);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_I32_I32_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 from,
                                             Ark_Int32 to, synthetic_Callback_Boolean_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_I32_I32_BOOLEAN);
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
void CallManagedCallback_I32_I32_I32_Void(Ark_Int32 resourceId, Ark_Int32 start, Ark_Int32 end, Ark_Int32 center)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_I32_I32_I32_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(start);
    argsSerializer.writeInt32(end);
    argsSerializer.writeInt32(center);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_I32_I32_I32_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 start,
                                              Ark_Int32 end, Ark_Int32 center)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_I32_I32_I32_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(start);
    argsSerializer.writeInt32(end);
    argsSerializer.writeInt32(center);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_I32_I32_Void(Ark_Int32 resourceId, Ark_Int32 first, Ark_Int32 last)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_I32_I32_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(first);
    argsSerializer.writeInt32(last);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_I32_I32_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 first,
                                          Ark_Int32 last)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_I32_I32_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(first);
    argsSerializer.writeInt32(last);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_I32_Tuple_I32_I32(Ark_Int32 resourceId, Ark_Int32 index,
                                           Callback_Tuple_I32_I32_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_I32_TUPLE_I32_I32);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_I32_Tuple_I32_I32Sync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 index,
                                               Callback_Tuple_I32_I32_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_I32_TUPLE_I32_I32);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_I32_Tuple_I32_I32_I32_I32(Ark_Int32 resourceId, Ark_Int32 index,
                                                   Callback_Tuple_I32_I32_I32_I32_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_I32_TUPLE_I32_I32_I32_I32);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_I32_Tuple_I32_I32_I32_I32Sync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 index,
                                                       Callback_Tuple_I32_I32_I32_I32_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_I32_TUPLE_I32_I32_I32_I32);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_I32_Void(Ark_Int32 resourceId, Ark_Int32 data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_I32_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_I32_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_I32_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_I64_Void(Ark_Int32 resourceId, Ark_Int64 data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_I64_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt64(data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_I64_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int64 data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_I64_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt64(data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_InsertValue_Boolean(Ark_Int32 resourceId, Ark_InsertValue data,
                                             synthetic_Callback_Boolean_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_INSERTVALUE_BOOLEAN);
    argsSerializer.writeInt32(resourceId);
    InsertValue_serializer::write(argsSerializer, data);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_InsertValue_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_InsertValue data,
                                                 synthetic_Callback_Boolean_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_INSERTVALUE_BOOLEAN);
    argsSerializer.writeInt32(resourceId);
    InsertValue_serializer::write(argsSerializer, data);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_InsertValue_Void(Ark_Int32 resourceId, Ark_InsertValue data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_INSERTVALUE_VOID);
    argsSerializer.writeInt32(resourceId);
    InsertValue_serializer::write(argsSerializer, data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_InsertValue_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_InsertValue data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_INSERTVALUE_VOID);
    argsSerializer.writeInt32(resourceId);
    InsertValue_serializer::write(argsSerializer, data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_ItemDragInfo_I32_I32_Boolean_Void(Ark_Int32 resourceId, Ark_ItemDragInfo event,
                                                           Ark_Int32 itemIndex, Ark_Int32 insertIndex,
                                                           Ark_Boolean isSuccess)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_ITEMDRAGINFO_I32_I32_BOOLEAN_VOID);
    argsSerializer.writeInt32(resourceId);
    ItemDragInfo_serializer::write(argsSerializer, event);
    argsSerializer.writeInt32(itemIndex);
    argsSerializer.writeInt32(insertIndex);
    argsSerializer.writeBoolean(isSuccess);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_ItemDragInfo_I32_I32_Boolean_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                               Ark_ItemDragInfo event, Ark_Int32 itemIndex,
                                                               Ark_Int32 insertIndex, Ark_Boolean isSuccess)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_ITEMDRAGINFO_I32_I32_BOOLEAN_VOID);
    argsSerializer.writeInt32(resourceId);
    ItemDragInfo_serializer::write(argsSerializer, event);
    argsSerializer.writeInt32(itemIndex);
    argsSerializer.writeInt32(insertIndex);
    argsSerializer.writeBoolean(isSuccess);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_ItemDragInfo_I32_I32_Void(Ark_Int32 resourceId, Ark_ItemDragInfo event, Ark_Int32 itemIndex,
                                                   Ark_Int32 insertIndex)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_ITEMDRAGINFO_I32_I32_VOID);
    argsSerializer.writeInt32(resourceId);
    ItemDragInfo_serializer::write(argsSerializer, event);
    argsSerializer.writeInt32(itemIndex);
    argsSerializer.writeInt32(insertIndex);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_ItemDragInfo_I32_I32_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                       Ark_ItemDragInfo event, Ark_Int32 itemIndex,
                                                       Ark_Int32 insertIndex)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_ITEMDRAGINFO_I32_I32_VOID);
    argsSerializer.writeInt32(resourceId);
    ItemDragInfo_serializer::write(argsSerializer, event);
    argsSerializer.writeInt32(itemIndex);
    argsSerializer.writeInt32(insertIndex);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_ItemDragInfo_I32_Void(Ark_Int32 resourceId, Ark_ItemDragInfo event, Ark_Int32 itemIndex)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_ITEMDRAGINFO_I32_VOID);
    argsSerializer.writeInt32(resourceId);
    ItemDragInfo_serializer::write(argsSerializer, event);
    argsSerializer.writeInt32(itemIndex);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_ItemDragInfo_I32_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                   Ark_ItemDragInfo event, Ark_Int32 itemIndex)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_ITEMDRAGINFO_I32_VOID);
    argsSerializer.writeInt32(resourceId);
    ItemDragInfo_serializer::write(argsSerializer, event);
    argsSerializer.writeInt32(itemIndex);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_ItemDragInfo_Void(Ark_Int32 resourceId, Ark_ItemDragInfo event)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_ITEMDRAGINFO_VOID);
    argsSerializer.writeInt32(resourceId);
    ItemDragInfo_serializer::write(argsSerializer, event);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_ItemDragInfo_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_ItemDragInfo event)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_ITEMDRAGINFO_VOID);
    argsSerializer.writeInt32(resourceId);
    ItemDragInfo_serializer::write(argsSerializer, event);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_KeyEvent_Boolean(Ark_Int32 resourceId, Ark_KeyEvent data,
                                          synthetic_Callback_Boolean_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_KEYEVENT_BOOLEAN);
    argsSerializer.writeInt32(resourceId);
    KeyEvent_serializer::write(argsSerializer, data);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_KeyEvent_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_KeyEvent data,
                                              synthetic_Callback_Boolean_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_KEYEVENT_BOOLEAN);
    argsSerializer.writeInt32(resourceId);
    KeyEvent_serializer::write(argsSerializer, data);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_KeyEvent_Void(Ark_Int32 resourceId, Ark_KeyEvent data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_KEYEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    KeyEvent_serializer::write(argsSerializer, data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_KeyEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_KeyEvent data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_KEYEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    KeyEvent_serializer::write(argsSerializer, data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_Length_Void(Ark_Int32 resourceId, Ark_Length data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_LENGTH_VOID);
    argsSerializer.writeInt32(resourceId);
    if (data.selector == 0)
    {
        argsSerializer.writeInt8(0);
        const auto dataForIdx0 = data.value0;
        argsSerializer.writeString(dataForIdx0);
    }
    else if (data.selector == 1)
    {
        argsSerializer.writeInt8(1);
        const auto dataForIdx1 = data.value1;
        argsSerializer.writeFloat64(dataForIdx1);
    }
    else if (data.selector == 2)
    {
        argsSerializer.writeInt8(2);
        const auto dataForIdx2 = data.value2;
        Resource_serializer::write(argsSerializer, dataForIdx2);
    }
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_Length_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Length data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_LENGTH_VOID);
    argsSerializer.writeInt32(resourceId);
    if (data.selector == 0)
    {
        argsSerializer.writeInt8(0);
        const auto dataForIdx0 = data.value0;
        argsSerializer.writeString(dataForIdx0);
    }
    else if (data.selector == 1)
    {
        argsSerializer.writeInt8(1);
        const auto dataForIdx1 = data.value1;
        argsSerializer.writeFloat64(dataForIdx1);
    }
    else if (data.selector == 2)
    {
        argsSerializer.writeInt8(2);
        const auto dataForIdx2 = data.value2;
        Resource_serializer::write(argsSerializer, dataForIdx2);
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_Map_String_Opt_Object(Ark_Int32 resourceId, Map_String_Opt_Object data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_MAP_STRING_OPT_OBJECT);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(data.size);
    for (int32_t i = 0; i < data.size; i++)
    {
        auto dataKeyVar = data.keys[i];
        auto dataValueVar = data.values[i];
        argsSerializer.writeString(dataKeyVar);
        if (runtimeType(dataValueVar) != INTEROP_RUNTIME_UNDEFINED)
        {
            argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
            const auto dataValueVarTmpValue = dataValueVar.value;
            argsSerializer.writeObject(dataValueVarTmpValue);
        }
        else
        {
            argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
        }
    }
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_Map_String_Opt_ObjectSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                   Map_String_Opt_Object data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_MAP_STRING_OPT_OBJECT);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(data.size);
    for (int32_t i = 0; i < data.size; i++)
    {
        auto dataKeyVar = data.keys[i];
        auto dataValueVar = data.values[i];
        argsSerializer.writeString(dataKeyVar);
        if (runtimeType(dataValueVar) != INTEROP_RUNTIME_UNDEFINED)
        {
            argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
            const auto dataValueVarTmpValue = dataValueVar.value;
            argsSerializer.writeObject(dataValueVarTmpValue);
        }
        else
        {
            argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
        }
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_MarqueeState_Void(Ark_Int32 resourceId, Ark_MarqueeState data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_MARQUEESTATE_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_MarqueeState>(data));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_MarqueeState_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_MarqueeState data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_MARQUEESTATE_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_MarqueeState>(data));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_MouseEvent_Void(Ark_Int32 resourceId, Ark_MouseEvent event)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_MOUSEEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    MouseEvent_serializer::write(argsSerializer, event);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_MouseEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_MouseEvent event)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_MOUSEEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    MouseEvent_serializer::write(argsSerializer, event);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_NativeEmbedDataInfo_Void(Ark_Int32 resourceId, Ark_NativeEmbedDataInfo event)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_NATIVEEMBEDDATAINFO_VOID);
    argsSerializer.writeInt32(resourceId);
    NativeEmbedDataInfo_serializer::write(argsSerializer, event);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_NativeEmbedDataInfo_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                      Ark_NativeEmbedDataInfo event)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_NATIVEEMBEDDATAINFO_VOID);
    argsSerializer.writeInt32(resourceId);
    NativeEmbedDataInfo_serializer::write(argsSerializer, event);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_NativeEmbedTouchInfo_Void(Ark_Int32 resourceId, Ark_NativeEmbedTouchInfo event)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_NATIVEEMBEDTOUCHINFO_VOID);
    argsSerializer.writeInt32(resourceId);
    NativeEmbedTouchInfo_serializer::write(argsSerializer, event);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_NativeEmbedTouchInfo_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                       Ark_NativeEmbedTouchInfo event)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_NATIVEEMBEDTOUCHINFO_VOID);
    argsSerializer.writeInt32(resourceId);
    NativeEmbedTouchInfo_serializer::write(argsSerializer, event);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_NavDestinationActiveReason_Void(Ark_Int32 resourceId, Ark_NavDestinationActiveReason data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_NAVDESTINATIONACTIVEREASON_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_NavDestinationActiveReason>(data));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_NavDestinationActiveReason_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                             Ark_NavDestinationActiveReason data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_NAVDESTINATIONACTIVEREASON_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_NavDestinationActiveReason>(data));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_NavDestinationContext_Void(Ark_Int32 resourceId, Ark_NavDestinationContext data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_NAVDESTINATIONCONTEXT_VOID);
    argsSerializer.writeInt32(resourceId);
    NavDestinationContext_serializer::write(argsSerializer, data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_NavDestinationContext_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                        Ark_NavDestinationContext data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_NAVDESTINATIONCONTEXT_VOID);
    argsSerializer.writeInt32(resourceId);
    NavDestinationContext_serializer::write(argsSerializer, data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_NavigationMode_Void(Ark_Int32 resourceId, Ark_NavigationMode mode)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_NAVIGATIONMODE_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_NavigationMode>(mode));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_NavigationMode_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NavigationMode mode)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_NAVIGATIONMODE_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_NavigationMode>(mode));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_NavigationTitleMode_Void(Ark_Int32 resourceId, Ark_NavigationTitleMode titleMode)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_NAVIGATIONTITLEMODE_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_NavigationTitleMode>(titleMode));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_NavigationTitleMode_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                      Ark_NavigationTitleMode titleMode)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_NAVIGATIONTITLEMODE_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_NavigationTitleMode>(titleMode));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_NavigationTransitionProxy_Void(Ark_Int32 resourceId,
                                                        Ark_NavigationTransitionProxy transitionProxy)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_NAVIGATIONTRANSITIONPROXY_VOID);
    argsSerializer.writeInt32(resourceId);
    NavigationTransitionProxy_serializer::write(argsSerializer, transitionProxy);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_NavigationTransitionProxy_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                            Ark_NavigationTransitionProxy transitionProxy)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_NAVIGATIONTRANSITIONPROXY_VOID);
    argsSerializer.writeInt32(resourceId);
    NavigationTransitionProxy_serializer::write(argsSerializer, transitionProxy);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_Number_Void(Ark_Int32 resourceId, Ark_Number data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_NUMBER_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_Number_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_NUMBER_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_Object_Void(Ark_Int32 resourceId, Ark_Object data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_OBJECT_VOID);
    argsSerializer.writeInt32(resourceId);
    const Ark_CallbackResource arg0Resource = {data.resource.resourceId, holdManagedCallbackResource,
                                               releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&arg0Resource);
    argsSerializer.writeObject(data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_Object_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Object data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_OBJECT_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeObject(data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_OnAlertEvent_Boolean(Ark_Int32 resourceId, Ark_OnAlertEvent data,
                                              synthetic_Callback_Boolean_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_ONALERTEVENT_BOOLEAN);
    argsSerializer.writeInt32(resourceId);
    OnAlertEvent_serializer::write(argsSerializer, data);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_OnAlertEvent_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnAlertEvent data,
                                                  synthetic_Callback_Boolean_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_ONALERTEVENT_BOOLEAN);
    argsSerializer.writeInt32(resourceId);
    OnAlertEvent_serializer::write(argsSerializer, data);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_OnAudioStateChangedEvent_Void(Ark_Int32 resourceId, Ark_OnAudioStateChangedEvent data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_ONAUDIOSTATECHANGEDEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    OnAudioStateChangedEvent_serializer::write(argsSerializer, data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_OnAudioStateChangedEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                           Ark_OnAudioStateChangedEvent data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_ONAUDIOSTATECHANGEDEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    OnAudioStateChangedEvent_serializer::write(argsSerializer, data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_OnBeforeUnloadEvent_Boolean(Ark_Int32 resourceId, Ark_OnBeforeUnloadEvent data,
                                                     synthetic_Callback_Boolean_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_ONBEFOREUNLOADEVENT_BOOLEAN);
    argsSerializer.writeInt32(resourceId);
    OnBeforeUnloadEvent_serializer::write(argsSerializer, data);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_OnBeforeUnloadEvent_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                         Ark_OnBeforeUnloadEvent data,
                                                         synthetic_Callback_Boolean_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_ONBEFOREUNLOADEVENT_BOOLEAN);
    argsSerializer.writeInt32(resourceId);
    OnBeforeUnloadEvent_serializer::write(argsSerializer, data);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_OnClientAuthenticationEvent_Void(Ark_Int32 resourceId, Ark_OnClientAuthenticationEvent data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_ONCLIENTAUTHENTICATIONEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    OnClientAuthenticationEvent_serializer::write(argsSerializer, data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_OnClientAuthenticationEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                              Ark_OnClientAuthenticationEvent data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_ONCLIENTAUTHENTICATIONEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    OnClientAuthenticationEvent_serializer::write(argsSerializer, data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_OnConfirmEvent_Boolean(Ark_Int32 resourceId, Ark_OnConfirmEvent data,
                                                synthetic_Callback_Boolean_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_ONCONFIRMEVENT_BOOLEAN);
    argsSerializer.writeInt32(resourceId);
    OnConfirmEvent_serializer::write(argsSerializer, data);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_OnConfirmEvent_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                    Ark_OnConfirmEvent data,
                                                    synthetic_Callback_Boolean_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_ONCONFIRMEVENT_BOOLEAN);
    argsSerializer.writeInt32(resourceId);
    OnConfirmEvent_serializer::write(argsSerializer, data);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_OnConsoleEvent_Boolean(Ark_Int32 resourceId, Ark_OnConsoleEvent data,
                                                synthetic_Callback_Boolean_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_ONCONSOLEEVENT_BOOLEAN);
    argsSerializer.writeInt32(resourceId);
    OnConsoleEvent_serializer::write(argsSerializer, data);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_OnConsoleEvent_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                    Ark_OnConsoleEvent data,
                                                    synthetic_Callback_Boolean_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_ONCONSOLEEVENT_BOOLEAN);
    argsSerializer.writeInt32(resourceId);
    OnConsoleEvent_serializer::write(argsSerializer, data);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_OnContextMenuShowEvent_Boolean(Ark_Int32 resourceId, Ark_OnContextMenuShowEvent data,
                                                        synthetic_Callback_Boolean_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_ONCONTEXTMENUSHOWEVENT_BOOLEAN);
    argsSerializer.writeInt32(resourceId);
    OnContextMenuShowEvent_serializer::write(argsSerializer, data);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_OnContextMenuShowEvent_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                            Ark_OnContextMenuShowEvent data,
                                                            synthetic_Callback_Boolean_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_ONCONTEXTMENUSHOWEVENT_BOOLEAN);
    argsSerializer.writeInt32(resourceId);
    OnContextMenuShowEvent_serializer::write(argsSerializer, data);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_OnDataResubmittedEvent_Void(Ark_Int32 resourceId, Ark_OnDataResubmittedEvent data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_ONDATARESUBMITTEDEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    OnDataResubmittedEvent_serializer::write(argsSerializer, data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_OnDataResubmittedEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                         Ark_OnDataResubmittedEvent data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_ONDATARESUBMITTEDEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    OnDataResubmittedEvent_serializer::write(argsSerializer, data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_OnDestory_Void(Ark_Int32 resourceId, Ark_Int64 nodeId)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_ONDESTORY_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt64(nodeId);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_OnDestory_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int64 nodeId)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_ONDESTORY_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt64(nodeId);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_OnDownloadStartEvent_Void(Ark_Int32 resourceId, Ark_OnDownloadStartEvent data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_ONDOWNLOADSTARTEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    OnDownloadStartEvent_serializer::write(argsSerializer, data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_OnDownloadStartEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                       Ark_OnDownloadStartEvent data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_ONDOWNLOADSTARTEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    OnDownloadStartEvent_serializer::write(argsSerializer, data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_OnErrorReceiveEvent_Void(Ark_Int32 resourceId, Ark_OnErrorReceiveEvent data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_ONERRORRECEIVEEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    OnErrorReceiveEvent_serializer::write(argsSerializer, data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_OnErrorReceiveEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                      Ark_OnErrorReceiveEvent data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_ONERRORRECEIVEEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    OnErrorReceiveEvent_serializer::write(argsSerializer, data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_OnFaviconReceivedEvent_Void(Ark_Int32 resourceId, Ark_OnFaviconReceivedEvent data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_ONFAVICONRECEIVEDEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    OnFaviconReceivedEvent_serializer::write(argsSerializer, data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_OnFaviconReceivedEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                         Ark_OnFaviconReceivedEvent data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_ONFAVICONRECEIVEDEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    OnFaviconReceivedEvent_serializer::write(argsSerializer, data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_OnFirstContentfulPaintEvent_Void(Ark_Int32 resourceId, Ark_OnFirstContentfulPaintEvent data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_ONFIRSTCONTENTFULPAINTEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    OnFirstContentfulPaintEvent_serializer::write(argsSerializer, data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_OnFirstContentfulPaintEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                              Ark_OnFirstContentfulPaintEvent data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_ONFIRSTCONTENTFULPAINTEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    OnFirstContentfulPaintEvent_serializer::write(argsSerializer, data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_OnGeolocationShowEvent_Void(Ark_Int32 resourceId, Ark_OnGeolocationShowEvent data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_ONGEOLOCATIONSHOWEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    OnGeolocationShowEvent_serializer::write(argsSerializer, data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_OnGeolocationShowEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                         Ark_OnGeolocationShowEvent data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_ONGEOLOCATIONSHOWEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    OnGeolocationShowEvent_serializer::write(argsSerializer, data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_OnHttpAuthRequestEvent_Boolean(Ark_Int32 resourceId, Ark_OnHttpAuthRequestEvent data,
                                                        synthetic_Callback_Boolean_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_ONHTTPAUTHREQUESTEVENT_BOOLEAN);
    argsSerializer.writeInt32(resourceId);
    OnHttpAuthRequestEvent_serializer::write(argsSerializer, data);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_OnHttpAuthRequestEvent_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                            Ark_OnHttpAuthRequestEvent data,
                                                            synthetic_Callback_Boolean_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_ONHTTPAUTHREQUESTEVENT_BOOLEAN);
    argsSerializer.writeInt32(resourceId);
    OnHttpAuthRequestEvent_serializer::write(argsSerializer, data);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_OnHttpErrorReceiveEvent_Void(Ark_Int32 resourceId, Ark_OnHttpErrorReceiveEvent data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_ONHTTPERRORRECEIVEEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    OnHttpErrorReceiveEvent_serializer::write(argsSerializer, data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_OnHttpErrorReceiveEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                          Ark_OnHttpErrorReceiveEvent data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_ONHTTPERRORRECEIVEEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    OnHttpErrorReceiveEvent_serializer::write(argsSerializer, data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_OnInterceptRequestEvent_Opt_WebResourceResponse(
    Ark_Int32 resourceId, Ark_OnInterceptRequestEvent data, Callback_Opt_WebResourceResponse_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_ONINTERCEPTREQUESTEVENT_OPT_WEBRESOURCERESPONSE);
    argsSerializer.writeInt32(resourceId);
    OnInterceptRequestEvent_serializer::write(argsSerializer, data);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_OnInterceptRequestEvent_Opt_WebResourceResponseSync(
    Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnInterceptRequestEvent data,
    Callback_Opt_WebResourceResponse_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_ONINTERCEPTREQUESTEVENT_OPT_WEBRESOURCERESPONSE);
    argsSerializer.writeInt32(resourceId);
    OnInterceptRequestEvent_serializer::write(argsSerializer, data);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_OnLoadFinishedEvent_Void(Ark_Int32 resourceId, Ark_OnLoadFinishedEvent data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_ONLOADFINISHEDEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    OnLoadFinishedEvent_serializer::write(argsSerializer, data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_OnLoadFinishedEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                      Ark_OnLoadFinishedEvent data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_ONLOADFINISHEDEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    OnLoadFinishedEvent_serializer::write(argsSerializer, data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_OnLoadInterceptEvent_Boolean(Ark_Int32 resourceId, Ark_OnLoadInterceptEvent data,
                                                      synthetic_Callback_Boolean_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_ONLOADINTERCEPTEVENT_BOOLEAN);
    argsSerializer.writeInt32(resourceId);
    OnLoadInterceptEvent_serializer::write(argsSerializer, data);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_OnLoadInterceptEvent_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                          Ark_OnLoadInterceptEvent data,
                                                          synthetic_Callback_Boolean_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_ONLOADINTERCEPTEVENT_BOOLEAN);
    argsSerializer.writeInt32(resourceId);
    OnLoadInterceptEvent_serializer::write(argsSerializer, data);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_OnLoadStartedEvent_Void(Ark_Int32 resourceId, Ark_OnLoadStartedEvent data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_ONLOADSTARTEDEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    OnLoadStartedEvent_serializer::write(argsSerializer, data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_OnLoadStartedEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                     Ark_OnLoadStartedEvent data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_ONLOADSTARTEDEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    OnLoadStartedEvent_serializer::write(argsSerializer, data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_onMeasureSize_SizeResult(Ark_Int32 resourceId, Ark_GeometryInfo selfLayoutInfo,
                                                  Array_Measurable children, Ark_ConstraintSizeOptions constraint,
                                                  Callback_SizeResult_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_ONMEASURESIZE_SIZERESULT);
    argsSerializer.writeInt32(resourceId);
    GeometryInfo_serializer::write(argsSerializer, selfLayoutInfo);
    argsSerializer.writeInt32(children.length);
    for (int childrenCounterI = 0; childrenCounterI < children.length; childrenCounterI++)
    {
        const Ark_Measurable childrenTmpElement = children.array[childrenCounterI];
        Measurable_serializer::write(argsSerializer, childrenTmpElement);
    }
    ConstraintSizeOptions_serializer::write(argsSerializer, constraint);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_onMeasureSize_SizeResultSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                      Ark_GeometryInfo selfLayoutInfo, Array_Measurable children,
                                                      Ark_ConstraintSizeOptions constraint,
                                                      Callback_SizeResult_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_ONMEASURESIZE_SIZERESULT);
    argsSerializer.writeInt32(resourceId);
    GeometryInfo_serializer::write(argsSerializer, selfLayoutInfo);
    argsSerializer.writeInt32(children.length);
    for (int childrenCounterI = 0; childrenCounterI < children.length; childrenCounterI++)
    {
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
void CallManagedCallback_OnMoveFromTo(Ark_Int32 resourceId, Ark_Int32 from, Ark_Int32 to)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_ONMOVEFROMTO);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(from);
    argsSerializer.writeInt32(to);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_OnMoveFromToSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 from, Ark_Int32 to)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_ONMOVEFROMTO);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(from);
    argsSerializer.writeInt32(to);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_OnOverScrollEvent_Void(Ark_Int32 resourceId, Ark_OnOverScrollEvent data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_ONOVERSCROLLEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    OnOverScrollEvent_serializer::write(argsSerializer, data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_OnOverScrollEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                    Ark_OnOverScrollEvent data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_ONOVERSCROLLEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    OnOverScrollEvent_serializer::write(argsSerializer, data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_OnPageBeginEvent_Void(Ark_Int32 resourceId, Ark_OnPageBeginEvent data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_ONPAGEBEGINEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    OnPageBeginEvent_serializer::write(argsSerializer, data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_OnPageBeginEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                   Ark_OnPageBeginEvent data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_ONPAGEBEGINEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    OnPageBeginEvent_serializer::write(argsSerializer, data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_OnPageEndEvent_Void(Ark_Int32 resourceId, Ark_OnPageEndEvent data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_ONPAGEENDEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    OnPageEndEvent_serializer::write(argsSerializer, data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_OnPageEndEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnPageEndEvent data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_ONPAGEENDEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    OnPageEndEvent_serializer::write(argsSerializer, data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_OnPageVisibleEvent_Void(Ark_Int32 resourceId, Ark_OnPageVisibleEvent data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_ONPAGEVISIBLEEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    OnPageVisibleEvent_serializer::write(argsSerializer, data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_OnPageVisibleEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                     Ark_OnPageVisibleEvent data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_ONPAGEVISIBLEEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    OnPageVisibleEvent_serializer::write(argsSerializer, data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_OnPermissionRequestEvent_Void(Ark_Int32 resourceId, Ark_OnPermissionRequestEvent data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_ONPERMISSIONREQUESTEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    OnPermissionRequestEvent_serializer::write(argsSerializer, data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_OnPermissionRequestEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                           Ark_OnPermissionRequestEvent data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_ONPERMISSIONREQUESTEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    OnPermissionRequestEvent_serializer::write(argsSerializer, data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_onPlaceChildren_Void(Ark_Int32 resourceId, Ark_GeometryInfo selfLayoutInfo,
                                              Array_Layoutable children, Ark_ConstraintSizeOptions constraint)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_ONPLACECHILDREN_VOID);
    argsSerializer.writeInt32(resourceId);
    GeometryInfo_serializer::write(argsSerializer, selfLayoutInfo);
    argsSerializer.writeInt32(children.length);
    for (int childrenCounterI = 0; childrenCounterI < children.length; childrenCounterI++)
    {
        const Ark_Layoutable childrenTmpElement = children.array[childrenCounterI];
        Layoutable_serializer::write(argsSerializer, childrenTmpElement);
    }
    ConstraintSizeOptions_serializer::write(argsSerializer, constraint);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_onPlaceChildren_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                  Ark_GeometryInfo selfLayoutInfo, Array_Layoutable children,
                                                  Ark_ConstraintSizeOptions constraint)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_ONPLACECHILDREN_VOID);
    argsSerializer.writeInt32(resourceId);
    GeometryInfo_serializer::write(argsSerializer, selfLayoutInfo);
    argsSerializer.writeInt32(children.length);
    for (int childrenCounterI = 0; childrenCounterI < children.length; childrenCounterI++)
    {
        const Ark_Layoutable childrenTmpElement = children.array[childrenCounterI];
        Layoutable_serializer::write(argsSerializer, childrenTmpElement);
    }
    ConstraintSizeOptions_serializer::write(argsSerializer, constraint);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_OnProgressChangeEvent_Void(Ark_Int32 resourceId, Ark_OnProgressChangeEvent data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_ONPROGRESSCHANGEEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    OnProgressChangeEvent_serializer::write(argsSerializer, data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_OnProgressChangeEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                        Ark_OnProgressChangeEvent data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_ONPROGRESSCHANGEEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    OnProgressChangeEvent_serializer::write(argsSerializer, data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_OnPromptEvent_Boolean(Ark_Int32 resourceId, Ark_OnPromptEvent data,
                                               synthetic_Callback_Boolean_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_ONPROMPTEVENT_BOOLEAN);
    argsSerializer.writeInt32(resourceId);
    OnPromptEvent_serializer::write(argsSerializer, data);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_OnPromptEvent_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                   Ark_OnPromptEvent data, synthetic_Callback_Boolean_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_ONPROMPTEVENT_BOOLEAN);
    argsSerializer.writeInt32(resourceId);
    OnPromptEvent_serializer::write(argsSerializer, data);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_OnRefreshAccessedHistoryEvent_Void(Ark_Int32 resourceId,
                                                            Ark_OnRefreshAccessedHistoryEvent data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_ONREFRESHACCESSEDHISTORYEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    OnRefreshAccessedHistoryEvent_serializer::write(argsSerializer, data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_OnRefreshAccessedHistoryEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                                Ark_OnRefreshAccessedHistoryEvent data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_ONREFRESHACCESSEDHISTORYEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    OnRefreshAccessedHistoryEvent_serializer::write(argsSerializer, data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_OnRenderExitedEvent_Void(Ark_Int32 resourceId, Ark_OnRenderExitedEvent data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_ONRENDEREXITEDEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    OnRenderExitedEvent_serializer::write(argsSerializer, data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_OnRenderExitedEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                      Ark_OnRenderExitedEvent data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_ONRENDEREXITEDEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    OnRenderExitedEvent_serializer::write(argsSerializer, data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_OnResourceLoadEvent_Void(Ark_Int32 resourceId, Ark_OnResourceLoadEvent data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_ONRESOURCELOADEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    OnResourceLoadEvent_serializer::write(argsSerializer, data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_OnResourceLoadEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                      Ark_OnResourceLoadEvent data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_ONRESOURCELOADEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    OnResourceLoadEvent_serializer::write(argsSerializer, data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_OnScaleChangeEvent_Void(Ark_Int32 resourceId, Ark_OnScaleChangeEvent data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_ONSCALECHANGEEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    OnScaleChangeEvent_serializer::write(argsSerializer, data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_OnScaleChangeEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                     Ark_OnScaleChangeEvent data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_ONSCALECHANGEEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    OnScaleChangeEvent_serializer::write(argsSerializer, data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_OnScreenCaptureRequestEvent_Void(Ark_Int32 resourceId, Ark_OnScreenCaptureRequestEvent data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_ONSCREENCAPTUREREQUESTEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    OnScreenCaptureRequestEvent_serializer::write(argsSerializer, data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_OnScreenCaptureRequestEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                              Ark_OnScreenCaptureRequestEvent data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_ONSCREENCAPTUREREQUESTEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    OnScreenCaptureRequestEvent_serializer::write(argsSerializer, data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_OnScrollEvent_Void(Ark_Int32 resourceId, Ark_OnScrollEvent data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_ONSCROLLEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    OnScrollEvent_serializer::write(argsSerializer, data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_OnScrollEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_OnScrollEvent data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_ONSCROLLEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    OnScrollEvent_serializer::write(argsSerializer, data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_OnScrollFrameBeginHandlerResult_Void(Ark_Int32 resourceId,
                                                              Ark_OnScrollFrameBeginHandlerResult value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_ONSCROLLFRAMEBEGINHANDLERRESULT_VOID);
    argsSerializer.writeInt32(resourceId);
    OnScrollFrameBeginHandlerResult_serializer::write(argsSerializer, value);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_OnScrollFrameBeginHandlerResult_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                                  Ark_OnScrollFrameBeginHandlerResult value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_ONSCROLLFRAMEBEGINHANDLERRESULT_VOID);
    argsSerializer.writeInt32(resourceId);
    OnScrollFrameBeginHandlerResult_serializer::write(argsSerializer, value);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_OnSearchResultReceiveEvent_Void(Ark_Int32 resourceId, Ark_OnSearchResultReceiveEvent data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_ONSEARCHRESULTRECEIVEEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    OnSearchResultReceiveEvent_serializer::write(argsSerializer, data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_OnSearchResultReceiveEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                             Ark_OnSearchResultReceiveEvent data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_ONSEARCHRESULTRECEIVEEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    OnSearchResultReceiveEvent_serializer::write(argsSerializer, data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_OnShowFileSelectorEvent_Boolean(Ark_Int32 resourceId, Ark_OnShowFileSelectorEvent data,
                                                         synthetic_Callback_Boolean_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_ONSHOWFILESELECTOREVENT_BOOLEAN);
    argsSerializer.writeInt32(resourceId);
    OnShowFileSelectorEvent_serializer::write(argsSerializer, data);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_OnShowFileSelectorEvent_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                             Ark_OnShowFileSelectorEvent data,
                                                             synthetic_Callback_Boolean_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_ONSHOWFILESELECTOREVENT_BOOLEAN);
    argsSerializer.writeInt32(resourceId);
    OnShowFileSelectorEvent_serializer::write(argsSerializer, data);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_OnSslErrorEventReceiveEvent_Void(Ark_Int32 resourceId, Ark_OnSslErrorEventReceiveEvent data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_ONSSLERROREVENTRECEIVEEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    OnSslErrorEventReceiveEvent_serializer::write(argsSerializer, data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_OnSslErrorEventReceiveEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                              Ark_OnSslErrorEventReceiveEvent data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_ONSSLERROREVENTRECEIVEEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    OnSslErrorEventReceiveEvent_serializer::write(argsSerializer, data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_OnTitleReceiveEvent_Void(Ark_Int32 resourceId, Ark_OnTitleReceiveEvent data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_ONTITLERECEIVEEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    OnTitleReceiveEvent_serializer::write(argsSerializer, data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_OnTitleReceiveEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                      Ark_OnTitleReceiveEvent data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_ONTITLERECEIVEEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    OnTitleReceiveEvent_serializer::write(argsSerializer, data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_OnTouchIconUrlReceivedEvent_Void(Ark_Int32 resourceId, Ark_OnTouchIconUrlReceivedEvent data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_ONTOUCHICONURLRECEIVEDEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    OnTouchIconUrlReceivedEvent_serializer::write(argsSerializer, data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_OnTouchIconUrlReceivedEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                              Ark_OnTouchIconUrlReceivedEvent data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_ONTOUCHICONURLRECEIVEDEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    OnTouchIconUrlReceivedEvent_serializer::write(argsSerializer, data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_OnWindowNewEvent_Void(Ark_Int32 resourceId, Ark_OnWindowNewEvent data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_ONWINDOWNEWEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    OnWindowNewEvent_serializer::write(argsSerializer, data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_OnWindowNewEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                   Ark_OnWindowNewEvent data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_ONWINDOWNEWEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    OnWindowNewEvent_serializer::write(argsSerializer, data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_Opt_Array_NavDestinationTransition_Void(Ark_Int32 resourceId,
                                                                 Opt_Array_NavDestinationTransition value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_OPT_ARRAY_NAVDESTINATIONTRANSITION_VOID);
    argsSerializer.writeInt32(resourceId);
    if (runtimeType(value) != INTEROP_RUNTIME_UNDEFINED)
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto valueTmpValue = value.value;
        argsSerializer.writeInt32(valueTmpValue.length);
        for (int valueTmpValueCounterI = 0; valueTmpValueCounterI < valueTmpValue.length; valueTmpValueCounterI++)
        {
            const Ark_NavDestinationTransition valueTmpValueTmpElement = valueTmpValue.array[valueTmpValueCounterI];
            NavDestinationTransition_serializer::write(argsSerializer, valueTmpValueTmpElement);
        }
    }
    else
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_Opt_Array_NavDestinationTransition_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                                     Opt_Array_NavDestinationTransition value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_OPT_ARRAY_NAVDESTINATIONTRANSITION_VOID);
    argsSerializer.writeInt32(resourceId);
    if (runtimeType(value) != INTEROP_RUNTIME_UNDEFINED)
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto valueTmpValue = value.value;
        argsSerializer.writeInt32(valueTmpValue.length);
        for (int valueTmpValueCounterI = 0; valueTmpValueCounterI < valueTmpValue.length; valueTmpValueCounterI++)
        {
            const Ark_NavDestinationTransition valueTmpValueTmpElement = valueTmpValue.array[valueTmpValueCounterI];
            NavDestinationTransition_serializer::write(argsSerializer, valueTmpValueTmpElement);
        }
    }
    else
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_Opt_Array_String_Void(Ark_Int32 resourceId, Opt_Array_String error)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_OPT_ARRAY_STRING_VOID);
    argsSerializer.writeInt32(resourceId);
    if (runtimeType(error) != INTEROP_RUNTIME_UNDEFINED)
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto errorTmpValue = error.value;
        argsSerializer.writeInt32(errorTmpValue.length);
        for (int errorTmpValueCounterI = 0; errorTmpValueCounterI < errorTmpValue.length; errorTmpValueCounterI++)
        {
            const Ark_String errorTmpValueTmpElement = errorTmpValue.array[errorTmpValueCounterI];
            argsSerializer.writeString(errorTmpValueTmpElement);
        }
    }
    else
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_Opt_Array_String_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                   Opt_Array_String error)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_OPT_ARRAY_STRING_VOID);
    argsSerializer.writeInt32(resourceId);
    if (runtimeType(error) != INTEROP_RUNTIME_UNDEFINED)
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto errorTmpValue = error.value;
        argsSerializer.writeInt32(errorTmpValue.length);
        for (int errorTmpValueCounterI = 0; errorTmpValueCounterI < errorTmpValue.length; errorTmpValueCounterI++)
        {
            const Ark_String errorTmpValueTmpElement = errorTmpValue.array[errorTmpValueCounterI];
            argsSerializer.writeString(errorTmpValueTmpElement);
        }
    }
    else
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_Opt_CustomNodeBuilder_Void(Ark_Int32 resourceId, Opt_CustomNodeBuilder value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_OPT_CUSTOMNODEBUILDER_VOID);
    argsSerializer.writeInt32(resourceId);
    if (runtimeType(value) != INTEROP_RUNTIME_UNDEFINED)
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto valueTmpValue = value.value;
        argsSerializer.writeCallbackResource(valueTmpValue.resource);
        argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(valueTmpValue.call));
        argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(valueTmpValue.callSync));
    }
    else
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_Opt_CustomNodeBuilder_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                        Opt_CustomNodeBuilder value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_OPT_CUSTOMNODEBUILDER_VOID);
    argsSerializer.writeInt32(resourceId);
    if (runtimeType(value) != INTEROP_RUNTIME_UNDEFINED)
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto valueTmpValue = value.value;
        argsSerializer.writeCallbackResource(valueTmpValue.resource);
        argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(valueTmpValue.call));
        argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(valueTmpValue.callSync));
    }
    else
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_Opt_NavigationAnimatedTransition_Void(Ark_Int32 resourceId,
                                                               Opt_NavigationAnimatedTransition value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_OPT_NAVIGATIONANIMATEDTRANSITION_VOID);
    argsSerializer.writeInt32(resourceId);
    if (runtimeType(value) != INTEROP_RUNTIME_UNDEFINED)
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto valueTmpValue = value.value;
        NavigationAnimatedTransition_serializer::write(argsSerializer, valueTmpValue);
    }
    else
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_Opt_NavigationAnimatedTransition_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                                   Opt_NavigationAnimatedTransition value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_OPT_NAVIGATIONANIMATEDTRANSITION_VOID);
    argsSerializer.writeInt32(resourceId);
    if (runtimeType(value) != INTEROP_RUNTIME_UNDEFINED)
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto valueTmpValue = value.value;
        NavigationAnimatedTransition_serializer::write(argsSerializer, valueTmpValue);
    }
    else
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_Opt_Object_Void(Ark_Int32 resourceId, Opt_Object data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_OPT_OBJECT_VOID);
    argsSerializer.writeInt32(resourceId);
    if (runtimeType(data) != INTEROP_RUNTIME_UNDEFINED)
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto dataTmpValue = data.value;
        argsSerializer.writeObject(dataTmpValue);
    }
    else
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_Opt_Object_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Opt_Object data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_OPT_OBJECT_VOID);
    argsSerializer.writeInt32(resourceId);
    if (runtimeType(data) != INTEROP_RUNTIME_UNDEFINED)
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto dataTmpValue = data.value;
        argsSerializer.writeObject(dataTmpValue);
    }
    else
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_Opt_OffsetResult_Void(Ark_Int32 resourceId, Opt_OffsetResult value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_OPT_OFFSETRESULT_VOID);
    argsSerializer.writeInt32(resourceId);
    if (runtimeType(value) != INTEROP_RUNTIME_UNDEFINED)
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto valueTmpValue = value.value;
        OffsetResult_serializer::write(argsSerializer, valueTmpValue);
    }
    else
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_Opt_OffsetResult_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                   Opt_OffsetResult value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_OPT_OFFSETRESULT_VOID);
    argsSerializer.writeInt32(resourceId);
    if (runtimeType(value) != INTEROP_RUNTIME_UNDEFINED)
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto valueTmpValue = value.value;
        OffsetResult_serializer::write(argsSerializer, valueTmpValue);
    }
    else
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_Opt_ScrollResult_Void(Ark_Int32 resourceId, Opt_ScrollResult value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_OPT_SCROLLRESULT_VOID);
    argsSerializer.writeInt32(resourceId);
    if (runtimeType(value) != INTEROP_RUNTIME_UNDEFINED)
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto valueTmpValue = value.value;
        ScrollResult_serializer::write(argsSerializer, valueTmpValue);
    }
    else
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_Opt_ScrollResult_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                   Opt_ScrollResult value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_OPT_SCROLLRESULT_VOID);
    argsSerializer.writeInt32(resourceId);
    if (runtimeType(value) != INTEROP_RUNTIME_UNDEFINED)
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto valueTmpValue = value.value;
        ScrollResult_serializer::write(argsSerializer, valueTmpValue);
    }
    else
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_Opt_StyledString_Opt_Array_String_Void(Ark_Int32 resourceId, Opt_StyledString value,
                                                                Opt_Array_String error)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_OPT_STYLEDSTRING_OPT_ARRAY_STRING_VOID);
    argsSerializer.writeInt32(resourceId);
    if (runtimeType(value) != INTEROP_RUNTIME_UNDEFINED)
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto valueTmpValue = value.value;
        StyledString_serializer::write(argsSerializer, valueTmpValue);
    }
    else
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    if (runtimeType(error) != INTEROP_RUNTIME_UNDEFINED)
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto errorTmpValue = error.value;
        argsSerializer.writeInt32(errorTmpValue.length);
        for (int errorTmpValueCounterI = 0; errorTmpValueCounterI < errorTmpValue.length; errorTmpValueCounterI++)
        {
            const Ark_String errorTmpValueTmpElement = errorTmpValue.array[errorTmpValueCounterI];
            argsSerializer.writeString(errorTmpValueTmpElement);
        }
    }
    else
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_Opt_StyledString_Opt_Array_String_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                                    Opt_StyledString value, Opt_Array_String error)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_OPT_STYLEDSTRING_OPT_ARRAY_STRING_VOID);
    argsSerializer.writeInt32(resourceId);
    if (runtimeType(value) != INTEROP_RUNTIME_UNDEFINED)
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto valueTmpValue = value.value;
        StyledString_serializer::write(argsSerializer, valueTmpValue);
    }
    else
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    if (runtimeType(error) != INTEROP_RUNTIME_UNDEFINED)
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto errorTmpValue = error.value;
        argsSerializer.writeInt32(errorTmpValue.length);
        for (int errorTmpValueCounterI = 0; errorTmpValueCounterI < errorTmpValue.length; errorTmpValueCounterI++)
        {
            const Ark_String errorTmpValueTmpElement = errorTmpValue.array[errorTmpValueCounterI];
            argsSerializer.writeString(errorTmpValueTmpElement);
        }
    }
    else
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_Opt_TabContentAnimatedTransition_Void(Ark_Int32 resourceId,
                                                               Opt_TabContentAnimatedTransition value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_OPT_TABCONTENTANIMATEDTRANSITION_VOID);
    argsSerializer.writeInt32(resourceId);
    if (runtimeType(value) != INTEROP_RUNTIME_UNDEFINED)
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto valueTmpValue = value.value;
        TabContentAnimatedTransition_serializer::write(argsSerializer, valueTmpValue);
    }
    else
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_Opt_TabContentAnimatedTransition_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                                   Opt_TabContentAnimatedTransition value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_OPT_TABCONTENTANIMATEDTRANSITION_VOID);
    argsSerializer.writeInt32(resourceId);
    if (runtimeType(value) != INTEROP_RUNTIME_UNDEFINED)
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto valueTmpValue = value.value;
        TabContentAnimatedTransition_serializer::write(argsSerializer, valueTmpValue);
    }
    else
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_Opt_WebResourceResponse_Void(Ark_Int32 resourceId, Opt_WebResourceResponse value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_OPT_WEBRESOURCERESPONSE_VOID);
    argsSerializer.writeInt32(resourceId);
    if (runtimeType(value) != INTEROP_RUNTIME_UNDEFINED)
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto valueTmpValue = value.value;
        WebResourceResponse_serializer::write(argsSerializer, valueTmpValue);
    }
    else
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_Opt_WebResourceResponse_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                          Opt_WebResourceResponse value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_OPT_WEBRESOURCERESPONSE_VOID);
    argsSerializer.writeInt32(resourceId);
    if (runtimeType(value) != INTEROP_RUNTIME_UNDEFINED)
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto valueTmpValue = value.value;
        WebResourceResponse_serializer::write(argsSerializer, valueTmpValue);
    }
    else
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_PlaybackInfo_Void(Ark_Int32 resourceId, Ark_PlaybackInfo data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_PLAYBACKINFO_VOID);
    argsSerializer.writeInt32(resourceId);
    PlaybackInfo_serializer::write(argsSerializer, data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_PlaybackInfo_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_PlaybackInfo data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_PLAYBACKINFO_VOID);
    argsSerializer.writeInt32(resourceId);
    PlaybackInfo_serializer::write(argsSerializer, data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_Pointer_Void(Ark_Int32 resourceId, Ark_NativePointer value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_POINTER_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(value);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_Pointer_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NativePointer value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_POINTER_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(value);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_PopInfo_Void(Ark_Int32 resourceId, Ark_PopInfo data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_POPINFO_VOID);
    argsSerializer.writeInt32(resourceId);
    PopInfo_serializer::write(argsSerializer, data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_PopInfo_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_PopInfo data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_POPINFO_VOID);
    argsSerializer.writeInt32(resourceId);
    PopInfo_serializer::write(argsSerializer, data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_PreDragStatus_Void(Ark_Int32 resourceId, Ark_PreDragStatus data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_PREDRAGSTATUS_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_PreDragStatus>(data));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_PreDragStatus_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_PreDragStatus data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_PREDRAGSTATUS_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_PreDragStatus>(data));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_PreparedInfo_Void(Ark_Int32 resourceId, Ark_PreparedInfo data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_PREPAREDINFO_VOID);
    argsSerializer.writeInt32(resourceId);
    PreparedInfo_serializer::write(argsSerializer, data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_PreparedInfo_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_PreparedInfo data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_PREPAREDINFO_VOID);
    argsSerializer.writeInt32(resourceId);
    PreparedInfo_serializer::write(argsSerializer, data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_RangeUpdate(Ark_Int32 resourceId, Ark_Int32 start, Ark_Int32 end, Ark_Int32 cacheStart,
                                     Ark_Int32 cacheEnd, Ark_Boolean isLoop)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_RANGEUPDATE);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(start);
    argsSerializer.writeInt32(end);
    argsSerializer.writeInt32(cacheStart);
    argsSerializer.writeInt32(cacheEnd);
    argsSerializer.writeBoolean(isLoop);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_RangeUpdateSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 start, Ark_Int32 end,
                                         Ark_Int32 cacheStart, Ark_Int32 cacheEnd, Ark_Boolean isLoop)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_RANGEUPDATE);
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
void CallManagedCallback_RefreshStatus_Void(Ark_Int32 resourceId, Ark_RefreshStatus state)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_REFRESHSTATUS_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_RefreshStatus>(state));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_RefreshStatus_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_RefreshStatus state)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_REFRESHSTATUS_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_RefreshStatus>(state));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_Resource_Void(Ark_Int32 resourceId, Ark_Resource data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_RESOURCE_VOID);
    argsSerializer.writeInt32(resourceId);
    Resource_serializer::write(argsSerializer, data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_Resource_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Resource data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_RESOURCE_VOID);
    argsSerializer.writeInt32(resourceId);
    Resource_serializer::write(argsSerializer, data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_ResourceStr_Void(Ark_Int32 resourceId, Ark_ResourceStr data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_RESOURCESTR_VOID);
    argsSerializer.writeInt32(resourceId);
    if (data.selector == 0)
    {
        argsSerializer.writeInt8(0);
        const auto dataForIdx0 = data.value0;
        argsSerializer.writeString(dataForIdx0);
    }
    else if (data.selector == 1)
    {
        argsSerializer.writeInt8(1);
        const auto dataForIdx1 = data.value1;
        Resource_serializer::write(argsSerializer, dataForIdx1);
    }
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_ResourceStr_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_ResourceStr data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_RESOURCESTR_VOID);
    argsSerializer.writeInt32(resourceId);
    if (data.selector == 0)
    {
        argsSerializer.writeInt8(0);
        const auto dataForIdx0 = data.value0;
        argsSerializer.writeString(dataForIdx0);
    }
    else if (data.selector == 1)
    {
        argsSerializer.writeInt8(1);
        const auto dataForIdx1 = data.value1;
        Resource_serializer::write(argsSerializer, dataForIdx1);
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_RichEditorChangeValue_Boolean(Ark_Int32 resourceId, Ark_RichEditorChangeValue data,
                                                       synthetic_Callback_Boolean_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_RICHEDITORCHANGEVALUE_BOOLEAN);
    argsSerializer.writeInt32(resourceId);
    RichEditorChangeValue_serializer::write(argsSerializer, data);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_RichEditorChangeValue_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                           Ark_RichEditorChangeValue data,
                                                           synthetic_Callback_Boolean_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_RICHEDITORCHANGEVALUE_BOOLEAN);
    argsSerializer.writeInt32(resourceId);
    RichEditorChangeValue_serializer::write(argsSerializer, data);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_RichEditorDeleteValue_Boolean(Ark_Int32 resourceId, Ark_RichEditorDeleteValue data,
                                                       synthetic_Callback_Boolean_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_RICHEDITORDELETEVALUE_BOOLEAN);
    argsSerializer.writeInt32(resourceId);
    RichEditorDeleteValue_serializer::write(argsSerializer, data);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_RichEditorDeleteValue_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                           Ark_RichEditorDeleteValue data,
                                                           synthetic_Callback_Boolean_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_RICHEDITORDELETEVALUE_BOOLEAN);
    argsSerializer.writeInt32(resourceId);
    RichEditorDeleteValue_serializer::write(argsSerializer, data);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_RichEditorInsertValue_Boolean(Ark_Int32 resourceId, Ark_RichEditorInsertValue data,
                                                       synthetic_Callback_Boolean_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_RICHEDITORINSERTVALUE_BOOLEAN);
    argsSerializer.writeInt32(resourceId);
    RichEditorInsertValue_serializer::write(argsSerializer, data);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_RichEditorInsertValue_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                           Ark_RichEditorInsertValue data,
                                                           synthetic_Callback_Boolean_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_RICHEDITORINSERTVALUE_BOOLEAN);
    argsSerializer.writeInt32(resourceId);
    RichEditorInsertValue_serializer::write(argsSerializer, data);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_RichEditorRange_Void(Ark_Int32 resourceId, Ark_RichEditorRange data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_RICHEDITORRANGE_VOID);
    argsSerializer.writeInt32(resourceId);
    RichEditorRange_serializer::write(argsSerializer, data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_RichEditorRange_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                  Ark_RichEditorRange data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_RICHEDITORRANGE_VOID);
    argsSerializer.writeInt32(resourceId);
    RichEditorRange_serializer::write(argsSerializer, data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_RichEditorSelection_Void(Ark_Int32 resourceId, Ark_RichEditorSelection data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_RICHEDITORSELECTION_VOID);
    argsSerializer.writeInt32(resourceId);
    RichEditorSelection_serializer::write(argsSerializer, data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_RichEditorSelection_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                      Ark_RichEditorSelection data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_RICHEDITORSELECTION_VOID);
    argsSerializer.writeInt32(resourceId);
    RichEditorSelection_serializer::write(argsSerializer, data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_RichEditorTextSpanResult_Void(Ark_Int32 resourceId, Ark_RichEditorTextSpanResult data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_RICHEDITORTEXTSPANRESULT_VOID);
    argsSerializer.writeInt32(resourceId);
    RichEditorTextSpanResult_serializer::write(argsSerializer, data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_RichEditorTextSpanResult_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                           Ark_RichEditorTextSpanResult data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_RICHEDITORTEXTSPANRESULT_VOID);
    argsSerializer.writeInt32(resourceId);
    RichEditorTextSpanResult_serializer::write(argsSerializer, data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_SheetDismiss_Void(Ark_Int32 resourceId, Ark_SheetDismiss sheetDismiss)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_SHEETDISMISS_VOID);
    argsSerializer.writeInt32(resourceId);
    SheetDismiss_serializer::write(argsSerializer, sheetDismiss);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_SheetDismiss_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                               Ark_SheetDismiss sheetDismiss)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_SHEETDISMISS_VOID);
    argsSerializer.writeInt32(resourceId);
    SheetDismiss_serializer::write(argsSerializer, sheetDismiss);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_SheetType_Void(Ark_Int32 resourceId, Ark_SheetType data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_SHEETTYPE_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_SheetType>(data));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_SheetType_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_SheetType data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_SHEETTYPE_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_SheetType>(data));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_Size_Void(Ark_Int32 resourceId, Ark_Size size)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_SIZE_VOID);
    argsSerializer.writeInt32(resourceId);
    Size_serializer::write(argsSerializer, size);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_Size_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Size size)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_SIZE_VOID);
    argsSerializer.writeInt32(resourceId);
    Size_serializer::write(argsSerializer, size);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_SizeResult_Void(Ark_Int32 resourceId, Ark_SizeResult value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_SIZERESULT_VOID);
    argsSerializer.writeInt32(resourceId);
    SizeResult_serializer::write(argsSerializer, value);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_SizeResult_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_SizeResult value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_SIZERESULT_VOID);
    argsSerializer.writeInt32(resourceId);
    SizeResult_serializer::write(argsSerializer, value);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_SpringBackAction_Void(Ark_Int32 resourceId, Ark_SpringBackAction data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_SPRINGBACKACTION_VOID);
    argsSerializer.writeInt32(resourceId);
    SpringBackAction_serializer::write(argsSerializer, data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_SpringBackAction_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                   Ark_SpringBackAction data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_SPRINGBACKACTION_VOID);
    argsSerializer.writeInt32(resourceId);
    SpringBackAction_serializer::write(argsSerializer, data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_StateStylesChange(Ark_Int32 resourceId, Ark_Int32 currentState)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_STATESTYLESCHANGE);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(currentState);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_StateStylesChangeSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 currentState)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_STATESTYLESCHANGE);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(currentState);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_String(Ark_Int32 resourceId, Ark_String data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_STRING);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_StringSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_String data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_STRING);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_String_PasteEvent_Void(Ark_Int32 resourceId, Ark_String value, Ark_PasteEvent event)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_STRING_PASTEEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(value);
    PasteEvent_serializer::write(argsSerializer, event);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_String_PasteEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_String value,
                                                    Ark_PasteEvent event)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_STRING_PASTEEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(value);
    PasteEvent_serializer::write(argsSerializer, event);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_String_SurfaceRect_Void(Ark_Int32 resourceId, Ark_String surfaceId, Ark_SurfaceRect rect)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_STRING_SURFACERECT_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(surfaceId);
    SurfaceRect_serializer::write(argsSerializer, rect);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_String_SurfaceRect_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                     Ark_String surfaceId, Ark_SurfaceRect rect)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_STRING_SURFACERECT_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(surfaceId);
    SurfaceRect_serializer::write(argsSerializer, rect);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_String_Void(Ark_Int32 resourceId, Ark_String data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_STRING_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_String_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_String data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_STRING_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_StyledStringChangeValue_Boolean(Ark_Int32 resourceId, Ark_StyledStringChangeValue data,
                                                         synthetic_Callback_Boolean_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_STYLEDSTRINGCHANGEVALUE_BOOLEAN);
    argsSerializer.writeInt32(resourceId);
    StyledStringChangeValue_serializer::write(argsSerializer, data);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_StyledStringChangeValue_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                             Ark_StyledStringChangeValue data,
                                                             synthetic_Callback_Boolean_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_STYLEDSTRINGCHANGEVALUE_BOOLEAN);
    argsSerializer.writeInt32(resourceId);
    StyledStringChangeValue_serializer::write(argsSerializer, data);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_SwipeActionState_Void(Ark_Int32 resourceId, Ark_SwipeActionState state)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_SWIPEACTIONSTATE_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_SwipeActionState>(state));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_SwipeActionState_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                   Ark_SwipeActionState state)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_SWIPEACTIONSTATE_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_SwipeActionState>(state));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_SwiperContentTransitionProxy_Void(Ark_Int32 resourceId, Ark_SwiperContentTransitionProxy data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_SWIPERCONTENTTRANSITIONPROXY_VOID);
    argsSerializer.writeInt32(resourceId);
    SwiperContentTransitionProxy_serializer::write(argsSerializer, data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_SwiperContentTransitionProxy_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                               Ark_SwiperContentTransitionProxy data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_SWIPERCONTENTTRANSITIONPROXY_VOID);
    argsSerializer.writeInt32(resourceId);
    SwiperContentTransitionProxy_serializer::write(argsSerializer, data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_TabContentTransitionProxy_Void(Ark_Int32 resourceId, Ark_TabContentTransitionProxy data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_TABCONTENTTRANSITIONPROXY_VOID);
    argsSerializer.writeInt32(resourceId);
    TabContentTransitionProxy_serializer::write(argsSerializer, data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_TabContentTransitionProxy_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                            Ark_TabContentTransitionProxy data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_TABCONTENTTRANSITIONPROXY_VOID);
    argsSerializer.writeInt32(resourceId);
    TabContentTransitionProxy_serializer::write(argsSerializer, data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_TerminationInfo(Ark_Int32 resourceId, Ark_TerminationInfo data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_TERMINATIONINFO);
    argsSerializer.writeInt32(resourceId);
    TerminationInfo_serializer::write(argsSerializer, data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_TerminationInfoSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_TerminationInfo data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_TERMINATIONINFO);
    argsSerializer.writeInt32(resourceId);
    TerminationInfo_serializer::write(argsSerializer, data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_TextPickerResult_Void(Ark_Int32 resourceId, Ark_TextPickerResult data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_TEXTPICKERRESULT_VOID);
    argsSerializer.writeInt32(resourceId);
    TextPickerResult_serializer::write(argsSerializer, data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_TextPickerResult_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                   Ark_TextPickerResult data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_TEXTPICKERRESULT_VOID);
    argsSerializer.writeInt32(resourceId);
    TextPickerResult_serializer::write(argsSerializer, data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_TextRange_Void(Ark_Int32 resourceId, Ark_TextRange data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_TEXTRANGE_VOID);
    argsSerializer.writeInt32(resourceId);
    TextRange_serializer::write(argsSerializer, data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_TextRange_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_TextRange data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_TEXTRANGE_VOID);
    argsSerializer.writeInt32(resourceId);
    TextRange_serializer::write(argsSerializer, data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_TimePickerResult_Void(Ark_Int32 resourceId, Ark_TimePickerResult data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_TIMEPICKERRESULT_VOID);
    argsSerializer.writeInt32(resourceId);
    TimePickerResult_serializer::write(argsSerializer, data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_TimePickerResult_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                   Ark_TimePickerResult data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_TIMEPICKERRESULT_VOID);
    argsSerializer.writeInt32(resourceId);
    TimePickerResult_serializer::write(argsSerializer, data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_TouchEvent_HitTestMode(Ark_Int32 resourceId, Ark_TouchEvent data,
                                                Callback_HitTestMode_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_TOUCHEVENT_HITTESTMODE);
    argsSerializer.writeInt32(resourceId);
    TouchEvent_serializer::write(argsSerializer, data);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_TouchEvent_HitTestModeSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_TouchEvent data,
                                                    Callback_HitTestMode_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_TOUCHEVENT_HITTESTMODE);
    argsSerializer.writeInt32(resourceId);
    TouchEvent_serializer::write(argsSerializer, data);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_TouchEvent_Void(Ark_Int32 resourceId, Ark_TouchEvent event)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_TOUCHEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    TouchEvent_serializer::write(argsSerializer, event);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_TouchEvent_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_TouchEvent event)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_TOUCHEVENT_VOID);
    argsSerializer.writeInt32(resourceId);
    TouchEvent_serializer::write(argsSerializer, event);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_TouchResult_Void(Ark_Int32 resourceId, Ark_TouchResult value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_TOUCHRESULT_VOID);
    argsSerializer.writeInt32(resourceId);
    TouchResult_serializer::write(argsSerializer, value);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_TouchResult_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_TouchResult value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_TOUCHRESULT_VOID);
    argsSerializer.writeInt32(resourceId);
    TouchResult_serializer::write(argsSerializer, value);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_Tuple_I32_I32_I32_I32_Void(Ark_Int32 resourceId, Ark_Tuple_I32_I32_I32_I32 value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_TUPLE_I32_I32_I32_I32_VOID);
    argsSerializer.writeInt32(resourceId);
    const auto value_0 = value.value0;
    argsSerializer.writeInt32(value_0);
    const auto value_1 = value.value1;
    argsSerializer.writeInt32(value_1);
    const auto value_2 = value.value2;
    argsSerializer.writeInt32(value_2);
    const auto value_3 = value.value3;
    argsSerializer.writeInt32(value_3);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_Tuple_I32_I32_I32_I32_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                        Ark_Tuple_I32_I32_I32_I32 value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_TUPLE_I32_I32_I32_I32_VOID);
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
void CallManagedCallback_Tuple_I32_I32_Void(Ark_Int32 resourceId, Ark_Tuple_I32_I32 value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_TUPLE_I32_I32_VOID);
    argsSerializer.writeInt32(resourceId);
    const auto value_0 = value.value0;
    argsSerializer.writeInt32(value_0);
    const auto value_1 = value.value1;
    argsSerializer.writeInt32(value_1);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_Tuple_I32_I32_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Tuple_I32_I32 value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_TUPLE_I32_I32_VOID);
    argsSerializer.writeInt32(resourceId);
    const auto value_0 = value.value0;
    argsSerializer.writeInt32(value_0);
    const auto value_1 = value.value1;
    argsSerializer.writeInt32(value_1);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_UIExtensionProxy(Ark_Int32 resourceId, Ark_UIExtensionProxy data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_UIEXTENSIONPROXY);
    argsSerializer.writeInt32(resourceId);
    UIExtensionProxy_serializer::write(argsSerializer, data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_UIExtensionProxySync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_UIExtensionProxy data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_UIEXTENSIONPROXY);
    argsSerializer.writeInt32(resourceId);
    UIExtensionProxy_serializer::write(argsSerializer, data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_Union_CustomNodeBuilder_DragItemInfo_Void(Ark_Int32 resourceId,
                                                                   Ark_Union_CustomNodeBuilder_DragItemInfo value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_UNION_CUSTOMNODEBUILDER_DRAGITEMINFO_VOID);
    argsSerializer.writeInt32(resourceId);
    if (value.selector == 0)
    {
        argsSerializer.writeInt8(0);
        const auto valueForIdx0 = value.value0;
        argsSerializer.writeCallbackResource(valueForIdx0.resource);
        argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(valueForIdx0.call));
        argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(valueForIdx0.callSync));
    }
    else if (value.selector == 1)
    {
        argsSerializer.writeInt8(1);
        const auto valueForIdx1 = value.value1;
        DragItemInfo_serializer::write(argsSerializer, valueForIdx1);
    }
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_Union_CustomNodeBuilder_DragItemInfo_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                                       Ark_Union_CustomNodeBuilder_DragItemInfo value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_UNION_CUSTOMNODEBUILDER_DRAGITEMINFO_VOID);
    argsSerializer.writeInt32(resourceId);
    if (value.selector == 0)
    {
        argsSerializer.writeInt8(0);
        const auto valueForIdx0 = value.value0;
        argsSerializer.writeCallbackResource(valueForIdx0.resource);
        argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(valueForIdx0.call));
        argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(valueForIdx0.callSync));
    }
    else if (value.selector == 1)
    {
        argsSerializer.writeInt8(1);
        const auto valueForIdx1 = value.value1;
        DragItemInfo_serializer::write(argsSerializer, valueForIdx1);
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_UserDataSpan_Void(Ark_Int32 resourceId, Ark_UserDataSpan value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_USERDATASPAN_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeObject(value);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_UserDataSpan_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_UserDataSpan value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_USERDATASPAN_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeObject(value);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_Void_Void(Ark_Int32 resourceId)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_VOID_VOID);
    argsSerializer.writeInt32(resourceId);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_Void_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_VOID_VOID);
    argsSerializer.writeInt32(resourceId);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCallback_WebKeyboardOptions_Void(Ark_Int32 resourceId, Ark_WebKeyboardOptions value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CALLBACK_WEBKEYBOARDOPTIONS_VOID);
    argsSerializer.writeInt32(resourceId);
    WebKeyboardOptions_serializer::write(argsSerializer, value);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCallback_WebKeyboardOptions_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                     Ark_WebKeyboardOptions value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CALLBACK_WEBKEYBOARDOPTIONS_VOID);
    argsSerializer.writeInt32(resourceId);
    WebKeyboardOptions_serializer::write(argsSerializer, value);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCheckBoxModifierBuilder(Ark_Int32 resourceId, Ark_NativePointer parentNode,
                                        Ark_CheckBoxConfiguration config, Callback_Pointer_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CHECKBOXMODIFIERBUILDER);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    CheckBoxConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCheckBoxModifierBuilderSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NativePointer parentNode,
                                            Ark_CheckBoxConfiguration config, Callback_Pointer_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CHECKBOXMODIFIERBUILDER);
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
void CallManagedContentDidScrollCallback(Ark_Int32 resourceId, Ark_Int32 selectedIndex, Ark_Int32 index,
                                         Ark_Float64 position, Ark_Float64 mainAxisLength)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CONTENTDIDSCROLLCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(selectedIndex);
    argsSerializer.writeInt32(index);
    argsSerializer.writeFloat64(position);
    argsSerializer.writeFloat64(mainAxisLength);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedContentDidScrollCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 selectedIndex,
                                             Ark_Int32 index, Ark_Float64 position, Ark_Float64 mainAxisLength)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CONTENTDIDSCROLLCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(selectedIndex);
    argsSerializer.writeInt32(index);
    argsSerializer.writeFloat64(position);
    argsSerializer.writeFloat64(mainAxisLength);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedContentWillScrollCallback(Ark_Int32 resourceId, Ark_SwiperContentWillScrollResult result,
                                          synthetic_Callback_Boolean_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CONTENTWILLSCROLLCALLBACK);
    argsSerializer.writeInt32(resourceId);
    SwiperContentWillScrollResult_serializer::write(argsSerializer, result);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedContentWillScrollCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                              Ark_SwiperContentWillScrollResult result,
                                              synthetic_Callback_Boolean_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CONTENTWILLSCROLLCALLBACK);
    argsSerializer.writeInt32(resourceId);
    SwiperContentWillScrollResult_serializer::write(argsSerializer, result);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedCustomNodeBuilder(Ark_Int32 resourceId, Ark_NativePointer parentNode,
                                  Callback_Pointer_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_CUSTOMNODEBUILDER);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedCustomNodeBuilderSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NativePointer parentNode,
                                      Callback_Pointer_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_CUSTOMNODEBUILDER);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedDataPanelModifierBuilder(Ark_Int32 resourceId, Ark_NativePointer parentNode,
                                         Ark_DataPanelConfiguration config, Callback_Pointer_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_DATAPANELMODIFIERBUILDER);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    DataPanelConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedDataPanelModifierBuilderSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                             Ark_NativePointer parentNode, Ark_DataPanelConfiguration config,
                                             Callback_Pointer_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_DATAPANELMODIFIERBUILDER);
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
void CallManagedDataProgressListener(Ark_Int32 resourceId, Ark_unifiedDataChannel_ProgressInfo progressInfo,
                                     Opt_unifiedDataChannel_UnifiedData data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_DATAPROGRESSLISTENER);
    argsSerializer.writeInt32(resourceId);
    unifiedDataChannel_ProgressInfo_serializer::write(argsSerializer, progressInfo);
    if (runtimeType(data) != INTEROP_RUNTIME_UNDEFINED)
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto dataTmpValue = data.value;
        unifiedDataChannel_UnifiedData_serializer::write(argsSerializer, dataTmpValue);
    }
    else
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedDataProgressListenerSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                         Ark_unifiedDataChannel_ProgressInfo progressInfo,
                                         Opt_unifiedDataChannel_UnifiedData data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_DATAPROGRESSLISTENER);
    argsSerializer.writeInt32(resourceId);
    unifiedDataChannel_ProgressInfo_serializer::write(argsSerializer, progressInfo);
    if (runtimeType(data) != INTEROP_RUNTIME_UNDEFINED)
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto dataTmpValue = data.value;
        unifiedDataChannel_UnifiedData_serializer::write(argsSerializer, dataTmpValue);
    }
    else
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedEditableTextOnChangeCallback(Ark_Int32 resourceId, Ark_String value, Opt_PreviewText previewText,
                                             Opt_TextChangeOptions options)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_EDITABLETEXTONCHANGECALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(value);
    if (runtimeType(previewText) != INTEROP_RUNTIME_UNDEFINED)
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto previewTextTmpValue = previewText.value;
        PreviewText_serializer::write(argsSerializer, previewTextTmpValue);
    }
    else
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    if (runtimeType(options) != INTEROP_RUNTIME_UNDEFINED)
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto optionsTmpValue = options.value;
        TextChangeOptions_serializer::write(argsSerializer, optionsTmpValue);
    }
    else
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedEditableTextOnChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_String value,
                                                 Opt_PreviewText previewText, Opt_TextChangeOptions options)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_EDITABLETEXTONCHANGECALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(value);
    if (runtimeType(previewText) != INTEROP_RUNTIME_UNDEFINED)
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto previewTextTmpValue = previewText.value;
        PreviewText_serializer::write(argsSerializer, previewTextTmpValue);
    }
    else
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    if (runtimeType(options) != INTEROP_RUNTIME_UNDEFINED)
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto optionsTmpValue = options.value;
        TextChangeOptions_serializer::write(argsSerializer, optionsTmpValue);
    }
    else
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedErrorCallback_BusinessErrorInterface_Void(Ark_Int32 resourceId, Ark_BusinessErrorInterface_Void err)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_ERRORCALLBACK_BUSINESSERRORINTERFACE_VOID);
    argsSerializer.writeInt32(resourceId);
    BusinessErrorInterface_Void_serializer::write(argsSerializer, err);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedErrorCallback_BusinessErrorInterface_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                              Ark_BusinessErrorInterface_Void err)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_ERRORCALLBACK_BUSINESSERRORINTERFACE_VOID);
    argsSerializer.writeInt32(resourceId);
    BusinessErrorInterface_Void_serializer::write(argsSerializer, err);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedFrameCallbackHandler(Ark_Int32 resourceId, Ark_Int64 arg)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_FRAMECALLBACKHANDLER);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt64(arg);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedFrameCallbackHandlerSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int64 arg)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_FRAMECALLBACKHANDLER);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt64(arg);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedGaugeModifierBuilder(Ark_Int32 resourceId, Ark_NativePointer parentNode, Ark_GaugeConfiguration config,
                                     Callback_Pointer_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_GAUGEMODIFIERBUILDER);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    GaugeConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedGaugeModifierBuilderSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NativePointer parentNode,
                                         Ark_GaugeConfiguration config, Callback_Pointer_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_GAUGEMODIFIERBUILDER);
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
void CallManagedGestureEventHandler(Ark_Int32 resourceId, Ark_GestureEvent event)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_GESTUREEVENTHANDLER);
    argsSerializer.writeInt32(resourceId);
    GestureEvent_serializer::write(argsSerializer, event);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedGestureEventHandlerSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_GestureEvent event)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_GESTUREEVENTHANDLER);
    argsSerializer.writeInt32(resourceId);
    GestureEvent_serializer::write(argsSerializer, event);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedGestureRecognizerJudgeBeginCallback(Ark_Int32 resourceId, Ark_BaseGestureEvent event,
                                                    Ark_GestureRecognizer current, Array_GestureRecognizer recognizers,
                                                    Opt_Array_TouchRecognizer touchRecognizers,
                                                    Callback_GestureJudgeResult_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_GESTURERECOGNIZERJUDGEBEGINCALLBACK);
    argsSerializer.writeInt32(resourceId);
    BaseGestureEvent_serializer::write(argsSerializer, event);
    GestureRecognizer_serializer::write(argsSerializer, current);
    argsSerializer.writeInt32(recognizers.length);
    for (int recognizersCounterI = 0; recognizersCounterI < recognizers.length; recognizersCounterI++)
    {
        const Ark_GestureRecognizer recognizersTmpElement = recognizers.array[recognizersCounterI];
        GestureRecognizer_serializer::write(argsSerializer, recognizersTmpElement);
    }
    if (runtimeType(touchRecognizers) != INTEROP_RUNTIME_UNDEFINED)
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto touchRecognizersTmpValue = touchRecognizers.value;
        argsSerializer.writeInt32(touchRecognizersTmpValue.length);
        for (int touchRecognizersTmpValueCounterI = 0;
             touchRecognizersTmpValueCounterI < touchRecognizersTmpValue.length; touchRecognizersTmpValueCounterI++)
        {
            const Ark_TouchRecognizer touchRecognizersTmpValueTmpElement =
                touchRecognizersTmpValue.array[touchRecognizersTmpValueCounterI];
            TouchRecognizer_serializer::write(argsSerializer, touchRecognizersTmpValueTmpElement);
        }
    }
    else
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedGestureRecognizerJudgeBeginCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                        Ark_BaseGestureEvent event, Ark_GestureRecognizer current,
                                                        Array_GestureRecognizer recognizers,
                                                        Opt_Array_TouchRecognizer touchRecognizers,
                                                        Callback_GestureJudgeResult_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_GESTURERECOGNIZERJUDGEBEGINCALLBACK);
    argsSerializer.writeInt32(resourceId);
    BaseGestureEvent_serializer::write(argsSerializer, event);
    GestureRecognizer_serializer::write(argsSerializer, current);
    argsSerializer.writeInt32(recognizers.length);
    for (int recognizersCounterI = 0; recognizersCounterI < recognizers.length; recognizersCounterI++)
    {
        const Ark_GestureRecognizer recognizersTmpElement = recognizers.array[recognizersCounterI];
        GestureRecognizer_serializer::write(argsSerializer, recognizersTmpElement);
    }
    if (runtimeType(touchRecognizers) != INTEROP_RUNTIME_UNDEFINED)
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto touchRecognizersTmpValue = touchRecognizers.value;
        argsSerializer.writeInt32(touchRecognizersTmpValue.length);
        for (int touchRecognizersTmpValueCounterI = 0;
             touchRecognizersTmpValueCounterI < touchRecognizersTmpValue.length; touchRecognizersTmpValueCounterI++)
        {
            const Ark_TouchRecognizer touchRecognizersTmpValueTmpElement =
                touchRecognizersTmpValue.array[touchRecognizersTmpValueCounterI];
            TouchRecognizer_serializer::write(argsSerializer, touchRecognizersTmpValueTmpElement);
        }
    }
    else
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedHoverCallback(Ark_Int32 resourceId, Ark_Boolean isHover, Ark_HoverEvent event)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_HOVERCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(isHover);
    HoverEvent_serializer::write(argsSerializer, event);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedHoverCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Boolean isHover,
                                  Ark_HoverEvent event)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_HOVERCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(isHover);
    HoverEvent_serializer::write(argsSerializer, event);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedImageCompleteCallback(Ark_Int32 resourceId, Ark_ImageLoadResult result)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_IMAGECOMPLETECALLBACK);
    argsSerializer.writeInt32(resourceId);
    ImageLoadResult_serializer::write(argsSerializer, result);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedImageCompleteCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_ImageLoadResult result)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_IMAGECOMPLETECALLBACK);
    argsSerializer.writeInt32(resourceId);
    ImageLoadResult_serializer::write(argsSerializer, result);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedImageErrorCallback(Ark_Int32 resourceId, Ark_ImageError error)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_IMAGEERRORCALLBACK);
    argsSerializer.writeInt32(resourceId);
    ImageError_serializer::write(argsSerializer, error);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedImageErrorCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_ImageError error)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_IMAGEERRORCALLBACK);
    argsSerializer.writeInt32(resourceId);
    ImageError_serializer::write(argsSerializer, error);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedImageOnCompleteCallback(Ark_Int32 resourceId, Opt_ImageCompleteEvent loadEvent)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_IMAGEONCOMPLETECALLBACK);
    argsSerializer.writeInt32(resourceId);
    if (runtimeType(loadEvent) != INTEROP_RUNTIME_UNDEFINED)
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto loadEventTmpValue = loadEvent.value;
        ImageCompleteEvent_serializer::write(argsSerializer, loadEventTmpValue);
    }
    else
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedImageOnCompleteCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                            Opt_ImageCompleteEvent loadEvent)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_IMAGEONCOMPLETECALLBACK);
    argsSerializer.writeInt32(resourceId);
    if (runtimeType(loadEvent) != INTEROP_RUNTIME_UNDEFINED)
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto loadEventTmpValue = loadEvent.value;
        ImageCompleteEvent_serializer::write(argsSerializer, loadEventTmpValue);
    }
    else
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedInterceptionModeCallback(Ark_Int32 resourceId, Ark_NavigationMode mode)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_INTERCEPTIONMODECALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_NavigationMode>(mode));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedInterceptionModeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NavigationMode mode)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_INTERCEPTIONMODECALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_NavigationMode>(mode));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedInterceptionShowCallback(Ark_Int32 resourceId, Ark_Union_NavDestinationContext_String from,
                                         Ark_Union_NavDestinationContext_String to, Ark_NavigationOperation operation,
                                         Ark_Boolean isAnimated)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_INTERCEPTIONSHOWCALLBACK);
    argsSerializer.writeInt32(resourceId);
    if (from.selector == 0)
    {
        argsSerializer.writeInt8(0);
        const auto fromForIdx0 = from.value0;
        NavDestinationContext_serializer::write(argsSerializer, fromForIdx0);
    }
    else if (from.selector == 1)
    {
        argsSerializer.writeInt8(1);
        const auto fromForIdx1 = from.value1;
        argsSerializer.writeString(fromForIdx1);
    }
    if (to.selector == 0)
    {
        argsSerializer.writeInt8(0);
        const auto toForIdx0 = to.value0;
        NavDestinationContext_serializer::write(argsSerializer, toForIdx0);
    }
    else if (to.selector == 1)
    {
        argsSerializer.writeInt8(1);
        const auto toForIdx1 = to.value1;
        argsSerializer.writeString(toForIdx1);
    }
    argsSerializer.writeInt32(static_cast<Ark_NavigationOperation>(operation));
    argsSerializer.writeBoolean(isAnimated);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedInterceptionShowCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                             Ark_Union_NavDestinationContext_String from,
                                             Ark_Union_NavDestinationContext_String to,
                                             Ark_NavigationOperation operation, Ark_Boolean isAnimated)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_INTERCEPTIONSHOWCALLBACK);
    argsSerializer.writeInt32(resourceId);
    if (from.selector == 0)
    {
        argsSerializer.writeInt8(0);
        const auto fromForIdx0 = from.value0;
        NavDestinationContext_serializer::write(argsSerializer, fromForIdx0);
    }
    else if (from.selector == 1)
    {
        argsSerializer.writeInt8(1);
        const auto fromForIdx1 = from.value1;
        argsSerializer.writeString(fromForIdx1);
    }
    if (to.selector == 0)
    {
        argsSerializer.writeInt8(0);
        const auto toForIdx0 = to.value0;
        NavDestinationContext_serializer::write(argsSerializer, toForIdx0);
    }
    else if (to.selector == 1)
    {
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
void CallManagedLoadingProgressModifierBuilder(Ark_Int32 resourceId, Ark_NativePointer parentNode,
                                               Ark_LoadingProgressConfiguration config,
                                               Callback_Pointer_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_LOADINGPROGRESSMODIFIERBUILDER);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    LoadingProgressConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedLoadingProgressModifierBuilderSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                   Ark_NativePointer parentNode,
                                                   Ark_LoadingProgressConfiguration config,
                                                   Callback_Pointer_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_LOADINGPROGRESSMODIFIERBUILDER);
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
void CallManagedMenuCallback(Ark_Int32 resourceId, Ark_Int32 start, Ark_Int32 end)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_MENUCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(start);
    argsSerializer.writeInt32(end);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedMenuCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 start, Ark_Int32 end)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_MENUCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(start);
    argsSerializer.writeInt32(end);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedMenuItemModifierBuilder(Ark_Int32 resourceId, Ark_NativePointer parentNode,
                                        Ark_MenuItemConfiguration config, Callback_Pointer_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_MENUITEMMODIFIERBUILDER);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    MenuItemConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedMenuItemModifierBuilderSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NativePointer parentNode,
                                            Ark_MenuItemConfiguration config, Callback_Pointer_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_MENUITEMMODIFIERBUILDER);
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
void CallManagedMenuOnAppearCallback(Ark_Int32 resourceId, Ark_Int32 start, Ark_Int32 end)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_MENUONAPPEARCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(start);
    argsSerializer.writeInt32(end);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedMenuOnAppearCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 start, Ark_Int32 end)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_MENUONAPPEARCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(start);
    argsSerializer.writeInt32(end);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedModifierKeyStateGetter(Ark_Int32 resourceId, Array_String keys,
                                       synthetic_Callback_Boolean_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_MODIFIERKEYSTATEGETTER);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(keys.length);
    for (int keysCounterI = 0; keysCounterI < keys.length; keysCounterI++)
    {
        const Ark_String keysTmpElement = keys.array[keysCounterI];
        argsSerializer.writeString(keysTmpElement);
    }
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedModifierKeyStateGetterSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Array_String keys,
                                           synthetic_Callback_Boolean_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_MODIFIERKEYSTATEGETTER);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(keys.length);
    for (int keysCounterI = 0; keysCounterI < keys.length; keysCounterI++)
    {
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
void CallManagedNavDestinationTransitionDelegate(Ark_Int32 resourceId, Ark_NavigationOperation operation,
                                                 Ark_Boolean isEnter,
                                                 Callback_Opt_Array_NavDestinationTransition_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_NAVDESTINATIONTRANSITIONDELEGATE);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_NavigationOperation>(operation));
    argsSerializer.writeBoolean(isEnter);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedNavDestinationTransitionDelegateSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                     Ark_NavigationOperation operation, Ark_Boolean isEnter,
                                                     Callback_Opt_Array_NavDestinationTransition_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_NAVDESTINATIONTRANSITIONDELEGATE);
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
void CallManagedNavExtender_CreateNavDestination(Ark_Int32 resourceId, Ark_Int32 index,
                                                 Callback_Pointer_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_NAVEXTENDER_CREATENAVDESTINATION);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedNavExtender_CreateNavDestinationSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 index,
                                                     Callback_Pointer_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_NAVEXTENDER_CREATENAVDESTINATION);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedNavExtender_OnUpdateStack(Ark_Int32 resourceId)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_NAVEXTENDER_ONUPDATESTACK);
    argsSerializer.writeInt32(resourceId);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedNavExtender_OnUpdateStackSync(Ark_VMContext vmContext, Ark_Int32 resourceId)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_NAVEXTENDER_ONUPDATESTACK);
    argsSerializer.writeInt32(resourceId);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedNodeContainerOpsOnTouchCallback(Ark_Int32 resourceId, Ark_TouchEvent event)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_NODECONTAINEROPSONTOUCHCALLBACK);
    argsSerializer.writeInt32(resourceId);
    TouchEvent_serializer::write(argsSerializer, event);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedNodeContainerOpsOnTouchCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_TouchEvent event)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_NODECONTAINEROPSONTOUCHCALLBACK);
    argsSerializer.writeInt32(resourceId);
    TouchEvent_serializer::write(argsSerializer, event);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedOnAdsBlockedCallback(Ark_Int32 resourceId, Ark_AdsBlockedDetails details)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_ONADSBLOCKEDCALLBACK);
    argsSerializer.writeInt32(resourceId);
    AdsBlockedDetails_serializer::write(argsSerializer, details);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedOnAdsBlockedCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_AdsBlockedDetails details)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_ONADSBLOCKEDCALLBACK);
    argsSerializer.writeInt32(resourceId);
    AdsBlockedDetails_serializer::write(argsSerializer, details);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedOnAlphabetIndexerPopupSelectCallback(Ark_Int32 resourceId, Ark_Int32 index)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_ONALPHABETINDEXERPOPUPSELECTCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedOnAlphabetIndexerPopupSelectCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 index)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_ONALPHABETINDEXERPOPUPSELECTCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedOnAlphabetIndexerRequestPopupDataCallback(Ark_Int32 resourceId, Ark_Int32 index,
                                                          synthetic_Callback_Array_String_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_ONALPHABETINDEXERREQUESTPOPUPDATACALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedOnAlphabetIndexerRequestPopupDataCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                              Ark_Int32 index,
                                                              synthetic_Callback_Array_String_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_ONALPHABETINDEXERREQUESTPOPUPDATACALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedOnAlphabetIndexerSelectCallback(Ark_Int32 resourceId, Ark_Int32 index)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_ONALPHABETINDEXERSELECTCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedOnAlphabetIndexerSelectCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 index)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_ONALPHABETINDEXERSELECTCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedOnCheckboxChangeCallback(Ark_Int32 resourceId, Ark_Boolean value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_ONCHECKBOXCHANGECALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(value);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedOnCheckboxChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Boolean value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_ONCHECKBOXCHANGECALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(value);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedOnCheckboxGroupChangeCallback(Ark_Int32 resourceId, Ark_CheckboxGroupResult value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_ONCHECKBOXGROUPCHANGECALLBACK);
    argsSerializer.writeInt32(resourceId);
    CheckboxGroupResult_serializer::write(argsSerializer, value);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedOnCheckboxGroupChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                  Ark_CheckboxGroupResult value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_ONCHECKBOXGROUPCHANGECALLBACK);
    argsSerializer.writeInt32(resourceId);
    CheckboxGroupResult_serializer::write(argsSerializer, value);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedOnContentScrollCallback(Ark_Int32 resourceId, Ark_Float64 totalOffsetX, Ark_Float64 totalOffsetY)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_ONCONTENTSCROLLCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFloat64(totalOffsetX);
    argsSerializer.writeFloat64(totalOffsetY);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedOnContentScrollCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Float64 totalOffsetX,
                                            Ark_Float64 totalOffsetY)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_ONCONTENTSCROLLCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFloat64(totalOffsetX);
    argsSerializer.writeFloat64(totalOffsetY);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedOnContextMenuHideCallback(Ark_Int32 resourceId)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_ONCONTEXTMENUHIDECALLBACK);
    argsSerializer.writeInt32(resourceId);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedOnContextMenuHideCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_ONCONTEXTMENUHIDECALLBACK);
    argsSerializer.writeInt32(resourceId);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedOnCreateMenuCallback(Ark_Int32 resourceId, Array_TextMenuItem menuItems,
                                     Callback_Array_TextMenuItem_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_ONCREATEMENUCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(menuItems.length);
    for (int menuItemsCounterI = 0; menuItemsCounterI < menuItems.length; menuItemsCounterI++)
    {
        const Ark_TextMenuItem menuItemsTmpElement = menuItems.array[menuItemsCounterI];
        TextMenuItem_serializer::write(argsSerializer, menuItemsTmpElement);
    }
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedOnCreateMenuCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Array_TextMenuItem menuItems,
                                         Callback_Array_TextMenuItem_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_ONCREATEMENUCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(menuItems.length);
    for (int menuItemsCounterI = 0; menuItemsCounterI < menuItems.length; menuItemsCounterI++)
    {
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
void CallManagedOnDidChangeCallback(Ark_Int32 resourceId, Ark_TextRange rangeBefore, Ark_TextRange rangeAfter)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_ONDIDCHANGECALLBACK);
    argsSerializer.writeInt32(resourceId);
    TextRange_serializer::write(argsSerializer, rangeBefore);
    TextRange_serializer::write(argsSerializer, rangeAfter);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedOnDidChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_TextRange rangeBefore,
                                        Ark_TextRange rangeAfter)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_ONDIDCHANGECALLBACK);
    argsSerializer.writeInt32(resourceId);
    TextRange_serializer::write(argsSerializer, rangeBefore);
    TextRange_serializer::write(argsSerializer, rangeAfter);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedOnDragEventCallback(Ark_Int32 resourceId, Ark_DragEvent event, Opt_String extraParams)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_ONDRAGEVENTCALLBACK);
    argsSerializer.writeInt32(resourceId);
    DragEvent_serializer::write(argsSerializer, event);
    if (runtimeType(extraParams) != INTEROP_RUNTIME_UNDEFINED)
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto extraParamsTmpValue = extraParams.value;
        argsSerializer.writeString(extraParamsTmpValue);
    }
    else
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedOnDragEventCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_DragEvent event,
                                        Opt_String extraParams)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_ONDRAGEVENTCALLBACK);
    argsSerializer.writeInt32(resourceId);
    DragEvent_serializer::write(argsSerializer, event);
    if (runtimeType(extraParams) != INTEROP_RUNTIME_UNDEFINED)
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto extraParamsTmpValue = extraParams.value;
        argsSerializer.writeString(extraParamsTmpValue);
    }
    else
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedOnFirstMeaningfulPaintCallback(Ark_Int32 resourceId, Ark_FirstMeaningfulPaint firstMeaningfulPaint)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_ONFIRSTMEANINGFULPAINTCALLBACK);
    argsSerializer.writeInt32(resourceId);
    FirstMeaningfulPaint_serializer::write(argsSerializer, firstMeaningfulPaint);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedOnFirstMeaningfulPaintCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                   Ark_FirstMeaningfulPaint firstMeaningfulPaint)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_ONFIRSTMEANINGFULPAINTCALLBACK);
    argsSerializer.writeInt32(resourceId);
    FirstMeaningfulPaint_serializer::write(argsSerializer, firstMeaningfulPaint);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedOnFoldStatusChangeCallback(Ark_Int32 resourceId, Ark_OnFoldStatusChangeInfo event)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_ONFOLDSTATUSCHANGECALLBACK);
    argsSerializer.writeInt32(resourceId);
    OnFoldStatusChangeInfo_serializer::write(argsSerializer, event);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedOnFoldStatusChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                               Ark_OnFoldStatusChangeInfo event)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_ONFOLDSTATUSCHANGECALLBACK);
    argsSerializer.writeInt32(resourceId);
    OnFoldStatusChangeInfo_serializer::write(argsSerializer, event);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedOnFullScreenEnterCallback(Ark_Int32 resourceId, Ark_FullScreenEnterEvent event)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_ONFULLSCREENENTERCALLBACK);
    argsSerializer.writeInt32(resourceId);
    FullScreenEnterEvent_serializer::write(argsSerializer, event);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedOnFullScreenEnterCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                              Ark_FullScreenEnterEvent event)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_ONFULLSCREENENTERCALLBACK);
    argsSerializer.writeInt32(resourceId);
    FullScreenEnterEvent_serializer::write(argsSerializer, event);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedOnHoverCallback(Ark_Int32 resourceId, Ark_Boolean status, Ark_HoverEvent event)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_ONHOVERCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(status);
    HoverEvent_serializer::write(argsSerializer, event);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedOnHoverCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Boolean status,
                                    Ark_HoverEvent event)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_ONHOVERCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(status);
    HoverEvent_serializer::write(argsSerializer, event);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedOnHoverStatusChangeCallback(Ark_Int32 resourceId, Ark_HoverEventParam param)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_ONHOVERSTATUSCHANGECALLBACK);
    argsSerializer.writeInt32(resourceId);
    HoverEventParam_serializer::write(argsSerializer, param);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedOnHoverStatusChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                Ark_HoverEventParam param)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_ONHOVERSTATUSCHANGECALLBACK);
    argsSerializer.writeInt32(resourceId);
    HoverEventParam_serializer::write(argsSerializer, param);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedOnIntelligentTrackingPreventionCallback(Ark_Int32 resourceId,
                                                        Ark_IntelligentTrackingPreventionDetails details)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_ONINTELLIGENTTRACKINGPREVENTIONCALLBACK);
    argsSerializer.writeInt32(resourceId);
    IntelligentTrackingPreventionDetails_serializer::write(argsSerializer, details);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedOnIntelligentTrackingPreventionCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                            Ark_IntelligentTrackingPreventionDetails details)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_ONINTELLIGENTTRACKINGPREVENTIONCALLBACK);
    argsSerializer.writeInt32(resourceId);
    IntelligentTrackingPreventionDetails_serializer::write(argsSerializer, details);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedOnItemDragStartCallback(Ark_Int32 resourceId, Ark_ItemDragInfo event, Ark_Int32 itemIndex,
                                        Callback_Opt_CustomNodeBuilder_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_ONITEMDRAGSTARTCALLBACK);
    argsSerializer.writeInt32(resourceId);
    ItemDragInfo_serializer::write(argsSerializer, event);
    argsSerializer.writeInt32(itemIndex);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedOnItemDragStartCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_ItemDragInfo event,
                                            Ark_Int32 itemIndex, Callback_Opt_CustomNodeBuilder_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_ONITEMDRAGSTARTCALLBACK);
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
void CallManagedOnLargestContentfulPaintCallback(Ark_Int32 resourceId,
                                                 Ark_LargestContentfulPaint largestContentfulPaint)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_ONLARGESTCONTENTFULPAINTCALLBACK);
    argsSerializer.writeInt32(resourceId);
    LargestContentfulPaint_serializer::write(argsSerializer, largestContentfulPaint);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedOnLargestContentfulPaintCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                     Ark_LargestContentfulPaint largestContentfulPaint)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_ONLARGESTCONTENTFULPAINTCALLBACK);
    argsSerializer.writeInt32(resourceId);
    LargestContentfulPaint_serializer::write(argsSerializer, largestContentfulPaint);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedOnMenuItemClickCallback(Ark_Int32 resourceId, Ark_TextMenuItem menuItem, Ark_TextRange range,
                                        synthetic_Callback_Boolean_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_ONMENUITEMCLICKCALLBACK);
    argsSerializer.writeInt32(resourceId);
    TextMenuItem_serializer::write(argsSerializer, menuItem);
    TextRange_serializer::write(argsSerializer, range);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedOnMenuItemClickCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_TextMenuItem menuItem,
                                            Ark_TextRange range, synthetic_Callback_Boolean_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_ONMENUITEMCLICKCALLBACK);
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
void CallManagedOnMoveHandler(Ark_Int32 resourceId, Ark_Int32 from, Ark_Int32 to)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_ONMOVEHANDLER);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(from);
    argsSerializer.writeInt32(to);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedOnMoveHandlerSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 from, Ark_Int32 to)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_ONMOVEHANDLER);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(from);
    argsSerializer.writeInt32(to);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedOnNativeEmbedVisibilityChangeCallback(Ark_Int32 resourceId,
                                                      Ark_NativeEmbedVisibilityInfo nativeEmbedVisibilityInfo)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_ONNATIVEEMBEDVISIBILITYCHANGECALLBACK);
    argsSerializer.writeInt32(resourceId);
    NativeEmbedVisibilityInfo_serializer::write(argsSerializer, nativeEmbedVisibilityInfo);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedOnNativeEmbedVisibilityChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                          Ark_NativeEmbedVisibilityInfo nativeEmbedVisibilityInfo)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_ONNATIVEEMBEDVISIBILITYCHANGECALLBACK);
    argsSerializer.writeInt32(resourceId);
    NativeEmbedVisibilityInfo_serializer::write(argsSerializer, nativeEmbedVisibilityInfo);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedOnNavigationEntryCommittedCallback(Ark_Int32 resourceId, Ark_LoadCommittedDetails loadCommittedDetails)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_ONNAVIGATIONENTRYCOMMITTEDCALLBACK);
    argsSerializer.writeInt32(resourceId);
    LoadCommittedDetails_serializer::write(argsSerializer, loadCommittedDetails);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedOnNavigationEntryCommittedCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                       Ark_LoadCommittedDetails loadCommittedDetails)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_ONNAVIGATIONENTRYCOMMITTEDCALLBACK);
    argsSerializer.writeInt32(resourceId);
    LoadCommittedDetails_serializer::write(argsSerializer, loadCommittedDetails);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedOnOverrideUrlLoadingCallback(Ark_Int32 resourceId, Ark_WebResourceRequest webResourceRequest,
                                             synthetic_Callback_Boolean_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_ONOVERRIDEURLLOADINGCALLBACK);
    argsSerializer.writeInt32(resourceId);
    WebResourceRequest_serializer::write(argsSerializer, webResourceRequest);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedOnOverrideUrlLoadingCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                 Ark_WebResourceRequest webResourceRequest,
                                                 synthetic_Callback_Boolean_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_ONOVERRIDEURLLOADINGCALLBACK);
    argsSerializer.writeInt32(resourceId);
    WebResourceRequest_serializer::write(argsSerializer, webResourceRequest);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedOnPasteCallback(Ark_Int32 resourceId, Ark_String content, Ark_PasteEvent event)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_ONPASTECALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(content);
    PasteEvent_serializer::write(argsSerializer, event);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedOnPasteCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_String content,
                                    Ark_PasteEvent event)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_ONPASTECALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(content);
    PasteEvent_serializer::write(argsSerializer, event);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedOnRadioChangeCallback(Ark_Int32 resourceId, Ark_Boolean isChecked)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_ONRADIOCHANGECALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(isChecked);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedOnRadioChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Boolean isChecked)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_ONRADIOCHANGECALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(isChecked);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedOnRatingChangeCallback(Ark_Int32 resourceId, Ark_Float64 rating)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_ONRATINGCHANGECALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFloat64(rating);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedOnRatingChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Float64 rating)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_ONRATINGCHANGECALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFloat64(rating);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedOnRenderProcessNotRespondingCallback(Ark_Int32 resourceId, Ark_RenderProcessNotRespondingData data)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_ONRENDERPROCESSNOTRESPONDINGCALLBACK);
    argsSerializer.writeInt32(resourceId);
    RenderProcessNotRespondingData_serializer::write(argsSerializer, data);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedOnRenderProcessNotRespondingCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                         Ark_RenderProcessNotRespondingData data)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_ONRENDERPROCESSNOTRESPONDINGCALLBACK);
    argsSerializer.writeInt32(resourceId);
    RenderProcessNotRespondingData_serializer::write(argsSerializer, data);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedOnRenderProcessRespondingCallback(Ark_Int32 resourceId)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_ONRENDERPROCESSRESPONDINGCALLBACK);
    argsSerializer.writeInt32(resourceId);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedOnRenderProcessRespondingCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_ONRENDERPROCESSRESPONDINGCALLBACK);
    argsSerializer.writeInt32(resourceId);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedOnSafeBrowsingCheckResultCallback(Ark_Int32 resourceId, Ark_ThreatType threatType)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_ONSAFEBROWSINGCHECKRESULTCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_ThreatType>(threatType));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedOnSafeBrowsingCheckResultCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                      Ark_ThreatType threatType)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_ONSAFEBROWSINGCHECKRESULTCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_ThreatType>(threatType));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedOnScrollCallback(Ark_Int32 resourceId, Ark_Float64 scrollOffset, Ark_ScrollState scrollState)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_ONSCROLLCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFloat64(scrollOffset);
    argsSerializer.writeInt32(static_cast<Ark_ScrollState>(scrollState));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedOnScrollCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Float64 scrollOffset,
                                     Ark_ScrollState scrollState)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_ONSCROLLCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFloat64(scrollOffset);
    argsSerializer.writeInt32(static_cast<Ark_ScrollState>(scrollState));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedOnScrollEdgeCallback(Ark_Int32 resourceId, Ark_Edge side)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_ONSCROLLEDGECALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_Edge>(side));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedOnScrollEdgeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Edge side)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_ONSCROLLEDGECALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_Edge>(side));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedOnScrollFrameBeginCallback(Ark_Int32 resourceId, Ark_Float64 offset, Ark_ScrollState state,
                                           Callback_OnScrollFrameBeginHandlerResult_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_ONSCROLLFRAMEBEGINCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFloat64(offset);
    argsSerializer.writeInt32(static_cast<Ark_ScrollState>(state));
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedOnScrollFrameBeginCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Float64 offset,
                                               Ark_ScrollState state,
                                               Callback_OnScrollFrameBeginHandlerResult_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_ONSCROLLFRAMEBEGINCALLBACK);
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
void CallManagedOnScrollVisibleContentChangeCallback(Ark_Int32 resourceId, Ark_VisibleListContentInfo start,
                                                     Ark_VisibleListContentInfo end)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_ONSCROLLVISIBLECONTENTCHANGECALLBACK);
    argsSerializer.writeInt32(resourceId);
    VisibleListContentInfo_serializer::write(argsSerializer, start);
    VisibleListContentInfo_serializer::write(argsSerializer, end);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedOnScrollVisibleContentChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                         Ark_VisibleListContentInfo start,
                                                         Ark_VisibleListContentInfo end)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_ONSCROLLVISIBLECONTENTCHANGECALLBACK);
    argsSerializer.writeInt32(resourceId);
    VisibleListContentInfo_serializer::write(argsSerializer, start);
    VisibleListContentInfo_serializer::write(argsSerializer, end);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedOnSelectCallback(Ark_Int32 resourceId, Ark_Int32 index, Ark_String selectStr)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_ONSELECTCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    argsSerializer.writeString(selectStr);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedOnSelectCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 index,
                                     Ark_String selectStr)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_ONSELECTCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    argsSerializer.writeString(selectStr);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedOnSslErrorEventCallback(Ark_Int32 resourceId, Ark_SslErrorEvent sslErrorEvent)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_ONSSLERROREVENTCALLBACK);
    argsSerializer.writeInt32(resourceId);
    SslErrorEvent_serializer::write(argsSerializer, sslErrorEvent);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedOnSslErrorEventCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                            Ark_SslErrorEvent sslErrorEvent)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_ONSSLERROREVENTCALLBACK);
    argsSerializer.writeInt32(resourceId);
    SslErrorEvent_serializer::write(argsSerializer, sslErrorEvent);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedOnSubmitCallback(Ark_Int32 resourceId, Ark_EnterKeyType enterKey, Ark_SubmitEvent event)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_ONSUBMITCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_EnterKeyType>(enterKey));
    SubmitEvent_serializer::write(argsSerializer, event);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedOnSubmitCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_EnterKeyType enterKey,
                                     Ark_SubmitEvent event)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_ONSUBMITCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_EnterKeyType>(enterKey));
    SubmitEvent_serializer::write(argsSerializer, event);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedOnSwiperAnimationEndCallback(Ark_Int32 resourceId, Ark_Int32 index, Ark_SwiperAnimationEvent extraInfo)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_ONSWIPERANIMATIONENDCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    SwiperAnimationEvent_serializer::write(argsSerializer, extraInfo);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedOnSwiperAnimationEndCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 index,
                                                 Ark_SwiperAnimationEvent extraInfo)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_ONSWIPERANIMATIONENDCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    SwiperAnimationEvent_serializer::write(argsSerializer, extraInfo);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedOnSwiperAnimationStartCallback(Ark_Int32 resourceId, Ark_Int32 index, Ark_Int32 targetIndex,
                                               Ark_SwiperAnimationEvent extraInfo)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_ONSWIPERANIMATIONSTARTCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    argsSerializer.writeInt32(targetIndex);
    SwiperAnimationEvent_serializer::write(argsSerializer, extraInfo);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedOnSwiperAnimationStartCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 index,
                                                   Ark_Int32 targetIndex, Ark_SwiperAnimationEvent extraInfo)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_ONSWIPERANIMATIONSTARTCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    argsSerializer.writeInt32(targetIndex);
    SwiperAnimationEvent_serializer::write(argsSerializer, extraInfo);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedOnSwiperGestureSwipeCallback(Ark_Int32 resourceId, Ark_Int32 index, Ark_SwiperAnimationEvent extraInfo)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_ONSWIPERGESTURESWIPECALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    SwiperAnimationEvent_serializer::write(argsSerializer, extraInfo);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedOnSwiperGestureSwipeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 index,
                                                 Ark_SwiperAnimationEvent extraInfo)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_ONSWIPERGESTURESWIPECALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    SwiperAnimationEvent_serializer::write(argsSerializer, extraInfo);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedOnTabsAnimationEndCallback(Ark_Int32 resourceId, Ark_Int32 index, Ark_TabsAnimationEvent extraInfo)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_ONTABSANIMATIONENDCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    TabsAnimationEvent_serializer::write(argsSerializer, extraInfo);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedOnTabsAnimationEndCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 index,
                                               Ark_TabsAnimationEvent extraInfo)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_ONTABSANIMATIONENDCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    TabsAnimationEvent_serializer::write(argsSerializer, extraInfo);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedOnTabsAnimationStartCallback(Ark_Int32 resourceId, Ark_Int32 index, Ark_Int32 targetIndex,
                                             Ark_TabsAnimationEvent extraInfo)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_ONTABSANIMATIONSTARTCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    argsSerializer.writeInt32(targetIndex);
    TabsAnimationEvent_serializer::write(argsSerializer, extraInfo);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedOnTabsAnimationStartCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 index,
                                                 Ark_Int32 targetIndex, Ark_TabsAnimationEvent extraInfo)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_ONTABSANIMATIONSTARTCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    argsSerializer.writeInt32(targetIndex);
    TabsAnimationEvent_serializer::write(argsSerializer, extraInfo);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedOnTabsContentWillChangeCallback(Ark_Int32 resourceId, Ark_Int32 currentIndex, Ark_Int32 comingIndex,
                                                synthetic_Callback_Boolean_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_ONTABSCONTENTWILLCHANGECALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(currentIndex);
    argsSerializer.writeInt32(comingIndex);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedOnTabsContentWillChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                    Ark_Int32 currentIndex, Ark_Int32 comingIndex,
                                                    synthetic_Callback_Boolean_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_ONTABSCONTENTWILLCHANGECALLBACK);
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
void CallManagedOnTabsGestureSwipeCallback(Ark_Int32 resourceId, Ark_Int32 index, Ark_TabsAnimationEvent extraInfo)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_ONTABSGESTURESWIPECALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    TabsAnimationEvent_serializer::write(argsSerializer, extraInfo);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedOnTabsGestureSwipeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 index,
                                               Ark_TabsAnimationEvent extraInfo)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_ONTABSGESTURESWIPECALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(index);
    TabsAnimationEvent_serializer::write(argsSerializer, extraInfo);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedOnTextPickerChangeCallback(Ark_Int32 resourceId, Ark_Union_String_Array_String selectItem,
                                           Ark_Union_I32_Array_I32 index)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_ONTEXTPICKERCHANGECALLBACK);
    argsSerializer.writeInt32(resourceId);
    if (selectItem.selector == 0)
    {
        argsSerializer.writeInt8(0);
        const auto selectItemForIdx0 = selectItem.value0;
        argsSerializer.writeString(selectItemForIdx0);
    }
    else if (selectItem.selector == 1)
    {
        argsSerializer.writeInt8(1);
        const auto selectItemForIdx1 = selectItem.value1;
        argsSerializer.writeInt32(selectItemForIdx1.length);
        for (int selectItemForIdx1CounterI = 0; selectItemForIdx1CounterI < selectItemForIdx1.length;
             selectItemForIdx1CounterI++)
        {
            const Ark_String selectItemForIdx1TmpElement = selectItemForIdx1.array[selectItemForIdx1CounterI];
            argsSerializer.writeString(selectItemForIdx1TmpElement);
        }
    }
    if (index.selector == 0)
    {
        argsSerializer.writeInt8(0);
        const auto indexForIdx0 = index.value0;
        argsSerializer.writeInt32(indexForIdx0);
    }
    else if (index.selector == 1)
    {
        argsSerializer.writeInt8(1);
        const auto indexForIdx1 = index.value1;
        argsSerializer.writeInt32(indexForIdx1.length);
        for (int indexForIdx1CounterI = 0; indexForIdx1CounterI < indexForIdx1.length; indexForIdx1CounterI++)
        {
            const Ark_Int32 indexForIdx1TmpElement = indexForIdx1.array[indexForIdx1CounterI];
            argsSerializer.writeInt32(indexForIdx1TmpElement);
        }
    }
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedOnTextPickerChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                               Ark_Union_String_Array_String selectItem, Ark_Union_I32_Array_I32 index)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_ONTEXTPICKERCHANGECALLBACK);
    argsSerializer.writeInt32(resourceId);
    if (selectItem.selector == 0)
    {
        argsSerializer.writeInt8(0);
        const auto selectItemForIdx0 = selectItem.value0;
        argsSerializer.writeString(selectItemForIdx0);
    }
    else if (selectItem.selector == 1)
    {
        argsSerializer.writeInt8(1);
        const auto selectItemForIdx1 = selectItem.value1;
        argsSerializer.writeInt32(selectItemForIdx1.length);
        for (int selectItemForIdx1CounterI = 0; selectItemForIdx1CounterI < selectItemForIdx1.length;
             selectItemForIdx1CounterI++)
        {
            const Ark_String selectItemForIdx1TmpElement = selectItemForIdx1.array[selectItemForIdx1CounterI];
            argsSerializer.writeString(selectItemForIdx1TmpElement);
        }
    }
    if (index.selector == 0)
    {
        argsSerializer.writeInt8(0);
        const auto indexForIdx0 = index.value0;
        argsSerializer.writeInt32(indexForIdx0);
    }
    else if (index.selector == 1)
    {
        argsSerializer.writeInt8(1);
        const auto indexForIdx1 = index.value1;
        argsSerializer.writeInt32(indexForIdx1.length);
        for (int indexForIdx1CounterI = 0; indexForIdx1CounterI < indexForIdx1.length; indexForIdx1CounterI++)
        {
            const Ark_Int32 indexForIdx1TmpElement = indexForIdx1.array[indexForIdx1CounterI];
            argsSerializer.writeInt32(indexForIdx1TmpElement);
        }
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedOnTextSelectionChangeCallback(Ark_Int32 resourceId, Ark_Int32 selectionStart, Ark_Int32 selectionEnd)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_ONTEXTSELECTIONCHANGECALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(selectionStart);
    argsSerializer.writeInt32(selectionEnd);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedOnTextSelectionChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                  Ark_Int32 selectionStart, Ark_Int32 selectionEnd)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_ONTEXTSELECTIONCHANGECALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(selectionStart);
    argsSerializer.writeInt32(selectionEnd);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedOnTimePickerChangeCallback(Ark_Int32 resourceId, Ark_TimePickerResult result)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_ONTIMEPICKERCHANGECALLBACK);
    argsSerializer.writeInt32(resourceId);
    TimePickerResult_serializer::write(argsSerializer, result);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedOnTimePickerChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                               Ark_TimePickerResult result)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_ONTIMEPICKERCHANGECALLBACK);
    argsSerializer.writeInt32(resourceId);
    TimePickerResult_serializer::write(argsSerializer, result);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedOnViewportFitChangedCallback(Ark_Int32 resourceId, Ark_ViewportFit viewportFit)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_ONVIEWPORTFITCHANGEDCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_ViewportFit>(viewportFit));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedOnViewportFitChangedCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                 Ark_ViewportFit viewportFit)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_ONVIEWPORTFITCHANGEDCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_ViewportFit>(viewportFit));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedOnWillScrollCallback(Ark_Int32 resourceId, Ark_Float64 scrollOffset, Ark_ScrollState scrollState,
                                     Ark_ScrollSource scrollSource, Callback_Opt_ScrollResult_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_ONWILLSCROLLCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFloat64(scrollOffset);
    argsSerializer.writeInt32(static_cast<Ark_ScrollState>(scrollState));
    argsSerializer.writeInt32(static_cast<Ark_ScrollSource>(scrollSource));
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedOnWillScrollCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Float64 scrollOffset,
                                         Ark_ScrollState scrollState, Ark_ScrollSource scrollSource,
                                         Callback_Opt_ScrollResult_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_ONWILLSCROLLCALLBACK);
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
void CallManagedPageMapNodeBuilder(Ark_Int32 resourceId, Ark_NativePointer parentNode, Ark_String name,
                                   Opt_Object param, Callback_Pointer_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_PAGEMAPNODEBUILDER);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    argsSerializer.writeString(name);
    if (runtimeType(param) != INTEROP_RUNTIME_UNDEFINED)
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto paramTmpValue = param.value;
        argsSerializer.writeObject(paramTmpValue);
    }
    else
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedPageMapNodeBuilderSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NativePointer parentNode,
                                       Ark_String name, Opt_Object param, Callback_Pointer_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_PAGEMAPNODEBUILDER);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    argsSerializer.writeString(name);
    if (runtimeType(param) != INTEROP_RUNTIME_UNDEFINED)
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto paramTmpValue = param.value;
        argsSerializer.writeObject(paramTmpValue);
    }
    else
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedPasteButtonCallback(Ark_Int32 resourceId, Ark_ClickEvent event, Ark_PasteButtonOnClickResult result,
                                    Opt_BusinessErrorInterface_Void error)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_PASTEBUTTONCALLBACK);
    argsSerializer.writeInt32(resourceId);
    ClickEvent_serializer::write(argsSerializer, event);
    argsSerializer.writeInt32(static_cast<Ark_PasteButtonOnClickResult>(result));
    if (runtimeType(error) != INTEROP_RUNTIME_UNDEFINED)
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto errorTmpValue = error.value;
        BusinessErrorInterface_Void_serializer::write(argsSerializer, errorTmpValue);
    }
    else
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedPasteButtonCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_ClickEvent event,
                                        Ark_PasteButtonOnClickResult result, Opt_BusinessErrorInterface_Void error)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_PASTEBUTTONCALLBACK);
    argsSerializer.writeInt32(resourceId);
    ClickEvent_serializer::write(argsSerializer, event);
    argsSerializer.writeInt32(static_cast<Ark_PasteButtonOnClickResult>(result));
    if (runtimeType(error) != INTEROP_RUNTIME_UNDEFINED)
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto errorTmpValue = error.value;
        BusinessErrorInterface_Void_serializer::write(argsSerializer, errorTmpValue);
    }
    else
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedPasteEventCallback(Ark_Int32 resourceId, Opt_PasteEvent event)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_PASTEEVENTCALLBACK);
    argsSerializer.writeInt32(resourceId);
    if (runtimeType(event) != INTEROP_RUNTIME_UNDEFINED)
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto eventTmpValue = event.value;
        PasteEvent_serializer::write(argsSerializer, eventTmpValue);
    }
    else
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedPasteEventCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Opt_PasteEvent event)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_PASTEEVENTCALLBACK);
    argsSerializer.writeInt32(resourceId);
    if (runtimeType(event) != INTEROP_RUNTIME_UNDEFINED)
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto eventTmpValue = event.value;
        PasteEvent_serializer::write(argsSerializer, eventTmpValue);
    }
    else
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedPluginErrorCallback(Ark_Int32 resourceId, Ark_PluginErrorData info)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_PLUGINERRORCALLBACK);
    argsSerializer.writeInt32(resourceId);
    PluginErrorData_serializer::write(argsSerializer, info);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedPluginErrorCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_PluginErrorData info)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_PLUGINERRORCALLBACK);
    argsSerializer.writeInt32(resourceId);
    PluginErrorData_serializer::write(argsSerializer, info);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedPopupStateChangeCallback(Ark_Int32 resourceId, Ark_PopupStateChangeParam event)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_POPUPSTATECHANGECALLBACK);
    argsSerializer.writeInt32(resourceId);
    PopupStateChangeParam_serializer::write(argsSerializer, event);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedPopupStateChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                             Ark_PopupStateChangeParam event)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_POPUPSTATECHANGECALLBACK);
    argsSerializer.writeInt32(resourceId);
    PopupStateChangeParam_serializer::write(argsSerializer, event);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedProgressModifierBuilder(Ark_Int32 resourceId, Ark_NativePointer parentNode,
                                        Ark_ProgressConfiguration config, Callback_Pointer_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_PROGRESSMODIFIERBUILDER);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    ProgressConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedProgressModifierBuilderSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NativePointer parentNode,
                                            Ark_ProgressConfiguration config, Callback_Pointer_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_PROGRESSMODIFIERBUILDER);
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
void CallManagedRadioModifierBuilder(Ark_Int32 resourceId, Ark_NativePointer parentNode, Ark_RadioConfiguration config,
                                     Callback_Pointer_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_RADIOMODIFIERBUILDER);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    RadioConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedRadioModifierBuilderSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NativePointer parentNode,
                                         Ark_RadioConfiguration config, Callback_Pointer_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_RADIOMODIFIERBUILDER);
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
void CallManagedRatingModifierBuilder(Ark_Int32 resourceId, Ark_NativePointer parentNode,
                                      Ark_RatingConfiguration config, Callback_Pointer_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_RATINGMODIFIERBUILDER);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    RatingConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedRatingModifierBuilderSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NativePointer parentNode,
                                          Ark_RatingConfiguration config, Callback_Pointer_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_RATINGMODIFIERBUILDER);
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
void CallManagedRestrictedWorker_onerror_Callback(Ark_Int32 resourceId, Ark_ErrorEvent ev)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_RESTRICTEDWORKER_ONERROR_CALLBACK);
    argsSerializer.writeInt32(resourceId);
    ErrorEvent_serializer::write(argsSerializer, ev);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedRestrictedWorker_onerror_CallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_ErrorEvent ev)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_RESTRICTEDWORKER_ONERROR_CALLBACK);
    argsSerializer.writeInt32(resourceId);
    ErrorEvent_serializer::write(argsSerializer, ev);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedRestrictedWorker_onexit_Callback(Ark_Int32 resourceId, Ark_Number code)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_RESTRICTEDWORKER_ONEXIT_CALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(code);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedRestrictedWorker_onexit_CallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Number code)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_RESTRICTEDWORKER_ONEXIT_CALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeNumber(code);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedRestrictedWorker_onmessage_Callback(Ark_Int32 resourceId, Ark_MessageEvents event)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_RESTRICTEDWORKER_ONMESSAGE_CALLBACK);
    argsSerializer.writeInt32(resourceId);
    MessageEvents_serializer::write(argsSerializer, event);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedRestrictedWorker_onmessage_CallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                        Ark_MessageEvents event)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_RESTRICTEDWORKER_ONMESSAGE_CALLBACK);
    argsSerializer.writeInt32(resourceId);
    MessageEvents_serializer::write(argsSerializer, event);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedReuseIdCallback(Ark_Int32 resourceId, synthetic_Callback_String_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_REUSEIDCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedReuseIdCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                    synthetic_Callback_String_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_REUSEIDCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedRouterFinishCallback(Ark_Int32 resourceId, Ark_NativePointer value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_ROUTERFINISHCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(value);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedRouterFinishCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NativePointer value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_ROUTERFINISHCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(value);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedSaveButtonCallback(Ark_Int32 resourceId, Ark_ClickEvent event, Ark_SaveButtonOnClickResult result,
                                   Opt_BusinessErrorInterface_Void error)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_SAVEBUTTONCALLBACK);
    argsSerializer.writeInt32(resourceId);
    ClickEvent_serializer::write(argsSerializer, event);
    argsSerializer.writeInt32(static_cast<Ark_SaveButtonOnClickResult>(result));
    if (runtimeType(error) != INTEROP_RUNTIME_UNDEFINED)
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto errorTmpValue = error.value;
        BusinessErrorInterface_Void_serializer::write(argsSerializer, errorTmpValue);
    }
    else
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedSaveButtonCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_ClickEvent event,
                                       Ark_SaveButtonOnClickResult result, Opt_BusinessErrorInterface_Void error)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_SAVEBUTTONCALLBACK);
    argsSerializer.writeInt32(resourceId);
    ClickEvent_serializer::write(argsSerializer, event);
    argsSerializer.writeInt32(static_cast<Ark_SaveButtonOnClickResult>(result));
    if (runtimeType(error) != INTEROP_RUNTIME_UNDEFINED)
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto errorTmpValue = error.value;
        BusinessErrorInterface_Void_serializer::write(argsSerializer, errorTmpValue);
    }
    else
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedScrollOnScrollCallback(Ark_Int32 resourceId, Ark_Float64 xOffset, Ark_Float64 yOffset,
                                       Ark_ScrollState scrollState)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_SCROLLONSCROLLCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFloat64(xOffset);
    argsSerializer.writeFloat64(yOffset);
    argsSerializer.writeInt32(static_cast<Ark_ScrollState>(scrollState));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedScrollOnScrollCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Float64 xOffset,
                                           Ark_Float64 yOffset, Ark_ScrollState scrollState)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_SCROLLONSCROLLCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFloat64(xOffset);
    argsSerializer.writeFloat64(yOffset);
    argsSerializer.writeInt32(static_cast<Ark_ScrollState>(scrollState));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedScrollOnWillScrollCallback(Ark_Int32 resourceId, Ark_Float64 xOffset, Ark_Float64 yOffset,
                                           Ark_ScrollState scrollState, Ark_ScrollSource scrollSource,
                                           Callback_Opt_OffsetResult_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_SCROLLONWILLSCROLLCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFloat64(xOffset);
    argsSerializer.writeFloat64(yOffset);
    argsSerializer.writeInt32(static_cast<Ark_ScrollState>(scrollState));
    argsSerializer.writeInt32(static_cast<Ark_ScrollSource>(scrollSource));
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedScrollOnWillScrollCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Float64 xOffset,
                                               Ark_Float64 yOffset, Ark_ScrollState scrollState,
                                               Ark_ScrollSource scrollSource,
                                               Callback_Opt_OffsetResult_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_SCROLLONWILLSCROLLCALLBACK);
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
void CallManagedSearchSubmitCallback(Ark_Int32 resourceId, Ark_String searchContent, Opt_SubmitEvent event)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_SEARCHSUBMITCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(searchContent);
    if (runtimeType(event) != INTEROP_RUNTIME_UNDEFINED)
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto eventTmpValue = event.value;
        SubmitEvent_serializer::write(argsSerializer, eventTmpValue);
    }
    else
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedSearchSubmitCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_String searchContent,
                                         Opt_SubmitEvent event)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_SEARCHSUBMITCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(searchContent);
    if (runtimeType(event) != INTEROP_RUNTIME_UNDEFINED)
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto eventTmpValue = event.value;
        SubmitEvent_serializer::write(argsSerializer, eventTmpValue);
    }
    else
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedSearchValueCallback(Ark_Int32 resourceId, Ark_String value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_SEARCHVALUECALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(value);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedSearchValueCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_String value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_SEARCHVALUECALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(value);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedShouldBuiltInRecognizerParallelWithCallback(Ark_Int32 resourceId, Ark_GestureRecognizer current,
                                                            Array_GestureRecognizer others,
                                                            Callback_GestureRecognizer_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_SHOULDBUILTINRECOGNIZERPARALLELWITHCALLBACK);
    argsSerializer.writeInt32(resourceId);
    GestureRecognizer_serializer::write(argsSerializer, current);
    argsSerializer.writeInt32(others.length);
    for (int othersCounterI = 0; othersCounterI < others.length; othersCounterI++)
    {
        const Ark_GestureRecognizer othersTmpElement = others.array[othersCounterI];
        GestureRecognizer_serializer::write(argsSerializer, othersTmpElement);
    }
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedShouldBuiltInRecognizerParallelWithCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                                Ark_GestureRecognizer current,
                                                                Array_GestureRecognizer others,
                                                                Callback_GestureRecognizer_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_SHOULDBUILTINRECOGNIZERPARALLELWITHCALLBACK);
    argsSerializer.writeInt32(resourceId);
    GestureRecognizer_serializer::write(argsSerializer, current);
    argsSerializer.writeInt32(others.length);
    for (int othersCounterI = 0; othersCounterI < others.length; othersCounterI++)
    {
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
void CallManagedSizeChangeCallback(Ark_Int32 resourceId, Ark_SizeOptions oldValue, Ark_SizeOptions newValue)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_SIZECHANGECALLBACK);
    argsSerializer.writeInt32(resourceId);
    SizeOptions_serializer::write(argsSerializer, oldValue);
    SizeOptions_serializer::write(argsSerializer, newValue);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedSizeChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_SizeOptions oldValue,
                                       Ark_SizeOptions newValue)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_SIZECHANGECALLBACK);
    argsSerializer.writeInt32(resourceId);
    SizeOptions_serializer::write(argsSerializer, oldValue);
    SizeOptions_serializer::write(argsSerializer, newValue);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedSliderModifierBuilder(Ark_Int32 resourceId, Ark_NativePointer parentNode,
                                      Ark_SliderConfiguration config, Callback_Pointer_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_SLIDERMODIFIERBUILDER);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    SliderConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedSliderModifierBuilderSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NativePointer parentNode,
                                          Ark_SliderConfiguration config, Callback_Pointer_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_SLIDERMODIFIERBUILDER);
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
void CallManagedSliderTriggerChangeCallback(Ark_Int32 resourceId, Ark_Float64 value, Ark_SliderChangeMode mode)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_SLIDERTRIGGERCHANGECALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFloat64(value);
    argsSerializer.writeInt32(static_cast<Ark_SliderChangeMode>(mode));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedSliderTriggerChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Float64 value,
                                                Ark_SliderChangeMode mode)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_SLIDERTRIGGERCHANGECALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFloat64(value);
    argsSerializer.writeInt32(static_cast<Ark_SliderChangeMode>(mode));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedStyledStringMarshallCallback(Ark_Int32 resourceId, Ark_UserDataSpan marshallableVal,
                                             Callback_Buffer_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_STYLEDSTRINGMARSHALLCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeObject(marshallableVal);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedStyledStringMarshallCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                 Ark_UserDataSpan marshallableVal, Callback_Buffer_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_STYLEDSTRINGMARSHALLCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeObject(marshallableVal);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedStyledStringUnmarshallCallback(Ark_Int32 resourceId, Ark_Buffer buf,
                                               Callback_UserDataSpan_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_STYLEDSTRINGUNMARSHALLCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBuffer(buf);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedStyledStringUnmarshallCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Buffer buf,
                                                   Callback_UserDataSpan_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_STYLEDSTRINGUNMARSHALLCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBuffer(buf);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedSubmitCallback(Ark_Int32 resourceId, Ark_EnterKeyType enterKey, Ark_SubmitEvent event)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_SUBMITCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_EnterKeyType>(enterKey));
    SubmitEvent_serializer::write(argsSerializer, event);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedSubmitCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_EnterKeyType enterKey,
                                   Ark_SubmitEvent event)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_SUBMITCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_EnterKeyType>(enterKey));
    SubmitEvent_serializer::write(argsSerializer, event);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedsynthetic_AsyncCallback_image_PixelMap_Void(Ark_Int32 resourceId, Ark_image_PixelMap result)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_SYNTHETIC_ASYNCCALLBACK_IMAGE_PIXELMAP_VOID);
    argsSerializer.writeInt32(resourceId);
    image_PixelMap_serializer::write(argsSerializer, result);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedsynthetic_AsyncCallback_image_PixelMap_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                                Ark_image_PixelMap result)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_SYNTHETIC_ASYNCCALLBACK_IMAGE_PIXELMAP_VOID);
    argsSerializer.writeInt32(resourceId);
    image_PixelMap_serializer::write(argsSerializer, result);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedsynthetic_Callback_Array_String_Void(Ark_Int32 resourceId, Array_String value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_SYNTHETIC_CALLBACK_ARRAY_STRING_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(value.length);
    for (int valueCounterI = 0; valueCounterI < value.length; valueCounterI++)
    {
        const Ark_String valueTmpElement = value.array[valueCounterI];
        argsSerializer.writeString(valueTmpElement);
    }
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedsynthetic_Callback_Array_String_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                         Array_String value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_SYNTHETIC_CALLBACK_ARRAY_STRING_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(value.length);
    for (int valueCounterI = 0; valueCounterI < value.length; valueCounterI++)
    {
        const Ark_String valueTmpElement = value.array[valueCounterI];
        argsSerializer.writeString(valueTmpElement);
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedsynthetic_Callback_Boolean_Void(Ark_Int32 resourceId, Ark_Boolean isSelected)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(isSelected);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedsynthetic_Callback_Boolean_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                    Ark_Boolean isSelected)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(isSelected);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedsynthetic_Callback_DismissDialogAction_Void(Ark_Int32 resourceId, Ark_DismissDialogAction value0)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_SYNTHETIC_CALLBACK_DISMISSDIALOGACTION_VOID);
    argsSerializer.writeInt32(resourceId);
    DismissDialogAction_serializer::write(argsSerializer, value0);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedsynthetic_Callback_DismissDialogAction_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                                Ark_DismissDialogAction value0)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_SYNTHETIC_CALLBACK_DISMISSDIALOGACTION_VOID);
    argsSerializer.writeInt32(resourceId);
    DismissDialogAction_serializer::write(argsSerializer, value0);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedsynthetic_Callback_F64_Void(Ark_Int32 resourceId, Ark_Float64 progress)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_SYNTHETIC_CALLBACK_F64_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFloat64(progress);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedsynthetic_Callback_F64_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Float64 progress)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_SYNTHETIC_CALLBACK_F64_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFloat64(progress);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedsynthetic_Callback_KeyEvent_Boolean(Ark_Int32 resourceId, Ark_KeyEvent event,
                                                    synthetic_Callback_Boolean_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_SYNTHETIC_CALLBACK_KEYEVENT_BOOLEAN);
    argsSerializer.writeInt32(resourceId);
    KeyEvent_serializer::write(argsSerializer, event);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedsynthetic_Callback_KeyEvent_BooleanSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                        Ark_KeyEvent event,
                                                        synthetic_Callback_Boolean_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_SYNTHETIC_CALLBACK_KEYEVENT_BOOLEAN);
    argsSerializer.writeInt32(resourceId);
    KeyEvent_serializer::write(argsSerializer, event);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedsynthetic_Callback_String_Void(Ark_Int32 resourceId, Ark_String breakpoints)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_SYNTHETIC_CALLBACK_STRING_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(breakpoints);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedsynthetic_Callback_String_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                   Ark_String breakpoints)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_SYNTHETIC_CALLBACK_STRING_VOID);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeString(breakpoints);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedsynthetic_Callback_TextPickerResult_Void(Ark_Int32 resourceId, Ark_TextPickerResult value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_SYNTHETIC_CALLBACK_TEXTPICKERRESULT_VOID);
    argsSerializer.writeInt32(resourceId);
    TextPickerResult_serializer::write(argsSerializer, value);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedsynthetic_Callback_TextPickerResult_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                             Ark_TextPickerResult value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_SYNTHETIC_CALLBACK_TEXTPICKERRESULT_VOID);
    argsSerializer.writeInt32(resourceId);
    TextPickerResult_serializer::write(argsSerializer, value);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedsynthetic_Callback_TimePickerResult_Void(Ark_Int32 resourceId, Ark_TimePickerResult value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_SYNTHETIC_CALLBACK_TIMEPICKERRESULT_VOID);
    argsSerializer.writeInt32(resourceId);
    TimePickerResult_serializer::write(argsSerializer, value);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedsynthetic_Callback_TimePickerResult_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                             Ark_TimePickerResult value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_SYNTHETIC_CALLBACK_TIMEPICKERRESULT_VOID);
    argsSerializer.writeInt32(resourceId);
    TimePickerResult_serializer::write(argsSerializer, value);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedsynthetic_Callback_Void(Ark_Int32 resourceId)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_SYNTHETIC_CALLBACK_VOID);
    argsSerializer.writeInt32(resourceId);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedsynthetic_Callback_VoidSync(Ark_VMContext vmContext, Ark_Int32 resourceId)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_SYNTHETIC_CALLBACK_VOID);
    argsSerializer.writeInt32(resourceId);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedTabsCustomContentTransitionCallback(Ark_Int32 resourceId, Ark_Int32 from, Ark_Int32 to,
                                                    Callback_Opt_TabContentAnimatedTransition_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_TABSCUSTOMCONTENTTRANSITIONCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(from);
    argsSerializer.writeInt32(to);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedTabsCustomContentTransitionCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int32 from,
                                                        Ark_Int32 to,
                                                        Callback_Opt_TabContentAnimatedTransition_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_TABSCUSTOMCONTENTTRANSITIONCALLBACK);
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
void CallManagedTextAreaSubmitCallback(Ark_Int32 resourceId, Ark_EnterKeyType enterKeyType, Opt_SubmitEvent event)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_TEXTAREASUBMITCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_EnterKeyType>(enterKeyType));
    if (runtimeType(event) != INTEROP_RUNTIME_UNDEFINED)
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto eventTmpValue = event.value;
        SubmitEvent_serializer::write(argsSerializer, eventTmpValue);
    }
    else
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedTextAreaSubmitCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_EnterKeyType enterKeyType,
                                           Opt_SubmitEvent event)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_TEXTAREASUBMITCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt32(static_cast<Ark_EnterKeyType>(enterKeyType));
    if (runtimeType(event) != INTEROP_RUNTIME_UNDEFINED)
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto eventTmpValue = event.value;
        SubmitEvent_serializer::write(argsSerializer, eventTmpValue);
    }
    else
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedTextClockModifierBuilder(Ark_Int32 resourceId, Ark_NativePointer parentNode,
                                         Ark_TextClockConfiguration config, Callback_Pointer_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_TEXTCLOCKMODIFIERBUILDER);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    TextClockConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedTextClockModifierBuilderSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                             Ark_NativePointer parentNode, Ark_TextClockConfiguration config,
                                             Callback_Pointer_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_TEXTCLOCKMODIFIERBUILDER);
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
void CallManagedTextFieldValueCallback(Ark_Int32 resourceId, Ark_ResourceStr value)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_TEXTFIELDVALUECALLBACK);
    argsSerializer.writeInt32(resourceId);
    if (value.selector == 0)
    {
        argsSerializer.writeInt8(0);
        const auto valueForIdx0 = value.value0;
        argsSerializer.writeString(valueForIdx0);
    }
    else if (value.selector == 1)
    {
        argsSerializer.writeInt8(1);
        const auto valueForIdx1 = value.value1;
        Resource_serializer::write(argsSerializer, valueForIdx1);
    }
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedTextFieldValueCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_ResourceStr value)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_TEXTFIELDVALUECALLBACK);
    argsSerializer.writeInt32(resourceId);
    if (value.selector == 0)
    {
        argsSerializer.writeInt8(0);
        const auto valueForIdx0 = value.value0;
        argsSerializer.writeString(valueForIdx0);
    }
    else if (value.selector == 1)
    {
        argsSerializer.writeInt8(1);
        const auto valueForIdx1 = value.value1;
        Resource_serializer::write(argsSerializer, valueForIdx1);
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedTextPickerEnterSelectedAreaCallback(Ark_Int32 resourceId, Ark_Union_String_Array_String value,
                                                    Ark_Union_I32_Array_I32 index)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_TEXTPICKERENTERSELECTEDAREACALLBACK);
    argsSerializer.writeInt32(resourceId);
    if (value.selector == 0)
    {
        argsSerializer.writeInt8(0);
        const auto valueForIdx0 = value.value0;
        argsSerializer.writeString(valueForIdx0);
    }
    else if (value.selector == 1)
    {
        argsSerializer.writeInt8(1);
        const auto valueForIdx1 = value.value1;
        argsSerializer.writeInt32(valueForIdx1.length);
        for (int valueForIdx1CounterI = 0; valueForIdx1CounterI < valueForIdx1.length; valueForIdx1CounterI++)
        {
            const Ark_String valueForIdx1TmpElement = valueForIdx1.array[valueForIdx1CounterI];
            argsSerializer.writeString(valueForIdx1TmpElement);
        }
    }
    if (index.selector == 0)
    {
        argsSerializer.writeInt8(0);
        const auto indexForIdx0 = index.value0;
        argsSerializer.writeInt32(indexForIdx0);
    }
    else if (index.selector == 1)
    {
        argsSerializer.writeInt8(1);
        const auto indexForIdx1 = index.value1;
        argsSerializer.writeInt32(indexForIdx1.length);
        for (int indexForIdx1CounterI = 0; indexForIdx1CounterI < indexForIdx1.length; indexForIdx1CounterI++)
        {
            const Ark_Int32 indexForIdx1TmpElement = indexForIdx1.array[indexForIdx1CounterI];
            argsSerializer.writeInt32(indexForIdx1TmpElement);
        }
    }
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedTextPickerEnterSelectedAreaCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                        Ark_Union_String_Array_String value,
                                                        Ark_Union_I32_Array_I32 index)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_TEXTPICKERENTERSELECTEDAREACALLBACK);
    argsSerializer.writeInt32(resourceId);
    if (value.selector == 0)
    {
        argsSerializer.writeInt8(0);
        const auto valueForIdx0 = value.value0;
        argsSerializer.writeString(valueForIdx0);
    }
    else if (value.selector == 1)
    {
        argsSerializer.writeInt8(1);
        const auto valueForIdx1 = value.value1;
        argsSerializer.writeInt32(valueForIdx1.length);
        for (int valueForIdx1CounterI = 0; valueForIdx1CounterI < valueForIdx1.length; valueForIdx1CounterI++)
        {
            const Ark_String valueForIdx1TmpElement = valueForIdx1.array[valueForIdx1CounterI];
            argsSerializer.writeString(valueForIdx1TmpElement);
        }
    }
    if (index.selector == 0)
    {
        argsSerializer.writeInt8(0);
        const auto indexForIdx0 = index.value0;
        argsSerializer.writeInt32(indexForIdx0);
    }
    else if (index.selector == 1)
    {
        argsSerializer.writeInt8(1);
        const auto indexForIdx1 = index.value1;
        argsSerializer.writeInt32(indexForIdx1.length);
        for (int indexForIdx1CounterI = 0; indexForIdx1CounterI < indexForIdx1.length; indexForIdx1CounterI++)
        {
            const Ark_Int32 indexForIdx1TmpElement = indexForIdx1.array[indexForIdx1CounterI];
            argsSerializer.writeInt32(indexForIdx1TmpElement);
        }
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedTextPickerScrollStopCallback(Ark_Int32 resourceId, Ark_Union_String_Array_String value,
                                             Ark_Union_I32_Array_I32 index)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_TEXTPICKERSCROLLSTOPCALLBACK);
    argsSerializer.writeInt32(resourceId);
    if (value.selector == 0)
    {
        argsSerializer.writeInt8(0);
        const auto valueForIdx0 = value.value0;
        argsSerializer.writeString(valueForIdx0);
    }
    else if (value.selector == 1)
    {
        argsSerializer.writeInt8(1);
        const auto valueForIdx1 = value.value1;
        argsSerializer.writeInt32(valueForIdx1.length);
        for (int valueForIdx1CounterI = 0; valueForIdx1CounterI < valueForIdx1.length; valueForIdx1CounterI++)
        {
            const Ark_String valueForIdx1TmpElement = valueForIdx1.array[valueForIdx1CounterI];
            argsSerializer.writeString(valueForIdx1TmpElement);
        }
    }
    if (index.selector == 0)
    {
        argsSerializer.writeInt8(0);
        const auto indexForIdx0 = index.value0;
        argsSerializer.writeInt32(indexForIdx0);
    }
    else if (index.selector == 1)
    {
        argsSerializer.writeInt8(1);
        const auto indexForIdx1 = index.value1;
        argsSerializer.writeInt32(indexForIdx1.length);
        for (int indexForIdx1CounterI = 0; indexForIdx1CounterI < indexForIdx1.length; indexForIdx1CounterI++)
        {
            const Ark_Int32 indexForIdx1TmpElement = indexForIdx1.array[indexForIdx1CounterI];
            argsSerializer.writeInt32(indexForIdx1TmpElement);
        }
    }
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedTextPickerScrollStopCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                                 Ark_Union_String_Array_String value, Ark_Union_I32_Array_I32 index)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_TEXTPICKERSCROLLSTOPCALLBACK);
    argsSerializer.writeInt32(resourceId);
    if (value.selector == 0)
    {
        argsSerializer.writeInt8(0);
        const auto valueForIdx0 = value.value0;
        argsSerializer.writeString(valueForIdx0);
    }
    else if (value.selector == 1)
    {
        argsSerializer.writeInt8(1);
        const auto valueForIdx1 = value.value1;
        argsSerializer.writeInt32(valueForIdx1.length);
        for (int valueForIdx1CounterI = 0; valueForIdx1CounterI < valueForIdx1.length; valueForIdx1CounterI++)
        {
            const Ark_String valueForIdx1TmpElement = valueForIdx1.array[valueForIdx1CounterI];
            argsSerializer.writeString(valueForIdx1TmpElement);
        }
    }
    if (index.selector == 0)
    {
        argsSerializer.writeInt8(0);
        const auto indexForIdx0 = index.value0;
        argsSerializer.writeInt32(indexForIdx0);
    }
    else if (index.selector == 1)
    {
        argsSerializer.writeInt8(1);
        const auto indexForIdx1 = index.value1;
        argsSerializer.writeInt32(indexForIdx1.length);
        for (int indexForIdx1CounterI = 0; indexForIdx1CounterI < indexForIdx1.length; indexForIdx1CounterI++)
        {
            const Ark_Int32 indexForIdx1TmpElement = indexForIdx1.array[indexForIdx1CounterI];
            argsSerializer.writeInt32(indexForIdx1TmpElement);
        }
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedTextTimerModifierBuilder(Ark_Int32 resourceId, Ark_NativePointer parentNode,
                                         Ark_TextTimerConfiguration config, Callback_Pointer_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_TEXTTIMERMODIFIERBUILDER);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    TextTimerConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedTextTimerModifierBuilderSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                             Ark_NativePointer parentNode, Ark_TextTimerConfiguration config,
                                             Callback_Pointer_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_TEXTTIMERMODIFIERBUILDER);
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
void CallManagedTimerCallback(Ark_Int32 resourceId, Ark_Int64 utc, Ark_Int64 elapsedTime)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_TIMERCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt64(utc);
    argsSerializer.writeInt64(elapsedTime);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedTimerCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Int64 utc, Ark_Int64 elapsedTime)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_TIMERCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeInt64(utc);
    argsSerializer.writeInt64(elapsedTime);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedToggleModifierBuilder(Ark_Int32 resourceId, Ark_NativePointer parentNode,
                                      Ark_ToggleConfiguration config, Callback_Pointer_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_TOGGLEMODIFIERBUILDER);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writePointer(parentNode);
    ToggleConfiguration_serializer::write(argsSerializer, config);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedToggleModifierBuilderSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NativePointer parentNode,
                                          Ark_ToggleConfiguration config, Callback_Pointer_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_TOGGLEMODIFIERBUILDER);
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
void CallManagedTouchTestDoneCallback(Ark_Int32 resourceId, Ark_BaseGestureEvent event,
                                      Array_GestureRecognizer recognizers)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_TOUCHTESTDONECALLBACK);
    argsSerializer.writeInt32(resourceId);
    BaseGestureEvent_serializer::write(argsSerializer, event);
    argsSerializer.writeInt32(recognizers.length);
    for (int recognizersCounterI = 0; recognizersCounterI < recognizers.length; recognizersCounterI++)
    {
        const Ark_GestureRecognizer recognizersTmpElement = recognizers.array[recognizersCounterI];
        GestureRecognizer_serializer::write(argsSerializer, recognizersTmpElement);
    }
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedTouchTestDoneCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_BaseGestureEvent event,
                                          Array_GestureRecognizer recognizers)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_TOUCHTESTDONECALLBACK);
    argsSerializer.writeInt32(resourceId);
    BaseGestureEvent_serializer::write(argsSerializer, event);
    argsSerializer.writeInt32(recognizers.length);
    for (int recognizersCounterI = 0; recognizersCounterI < recognizers.length; recognizersCounterI++)
    {
        const Ark_GestureRecognizer recognizersTmpElement = recognizers.array[recognizersCounterI];
        GestureRecognizer_serializer::write(argsSerializer, recognizersTmpElement);
    }
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedTransitionFinishCallback(Ark_Int32 resourceId, Ark_Boolean transitionIn)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_TRANSITIONFINISHCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(transitionIn);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedTransitionFinishCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Boolean transitionIn)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_TRANSITIONFINISHCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(transitionIn);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedType_CommonMethod_onDragStart(Ark_Int32 resourceId, Ark_DragEvent event, Opt_String extraParams,
                                              Callback_Union_CustomNodeBuilder_DragItemInfo_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_TYPE_COMMONMETHOD_ONDRAGSTART);
    argsSerializer.writeInt32(resourceId);
    DragEvent_serializer::write(argsSerializer, event);
    if (runtimeType(extraParams) != INTEROP_RUNTIME_UNDEFINED)
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto extraParamsTmpValue = extraParams.value;
        argsSerializer.writeString(extraParamsTmpValue);
    }
    else
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedType_CommonMethod_onDragStartSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_DragEvent event,
                                                  Opt_String extraParams,
                                                  Callback_Union_CustomNodeBuilder_DragItemInfo_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_TYPE_COMMONMETHOD_ONDRAGSTART);
    argsSerializer.writeInt32(resourceId);
    DragEvent_serializer::write(argsSerializer, event);
    if (runtimeType(extraParams) != INTEROP_RUNTIME_UNDEFINED)
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_OBJECT);
        const auto extraParamsTmpValue = extraParams.value;
        argsSerializer.writeString(extraParamsTmpValue);
    }
    else
    {
        argsSerializer.writeInt8(INTEROP_RUNTIME_UNDEFINED);
    }
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedType_NavigationAttribute_customNavContentTransition(
    Ark_Int32 resourceId, Ark_NavContentInfo from, Ark_NavContentInfo to, Ark_NavigationOperation operation,
    Callback_Opt_NavigationAnimatedTransition_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_TYPE_NAVIGATIONATTRIBUTE_CUSTOMNAVCONTENTTRANSITION);
    argsSerializer.writeInt32(resourceId);
    NavContentInfo_serializer::write(argsSerializer, from);
    NavContentInfo_serializer::write(argsSerializer, to);
    argsSerializer.writeInt32(static_cast<Ark_NavigationOperation>(operation));
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedType_NavigationAttribute_customNavContentTransitionSync(
    Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_NavContentInfo from, Ark_NavContentInfo to,
    Ark_NavigationOperation operation, Callback_Opt_NavigationAnimatedTransition_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_TYPE_NAVIGATIONATTRIBUTE_CUSTOMNAVCONTENTTRANSITION);
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
void CallManagedUpdateTransitionCallback(Ark_Int32 resourceId, Ark_Float64 progress)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_UPDATETRANSITIONCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFloat64(progress);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedUpdateTransitionCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Float64 progress)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_UPDATETRANSITIONCALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeFloat64(progress);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedVisibleAreaChangeCallback(Ark_Int32 resourceId, Ark_Boolean isExpanding, Ark_Float64 currentRatio)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_VISIBLEAREACHANGECALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(isExpanding);
    argsSerializer.writeFloat64(currentRatio);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedVisibleAreaChangeCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Boolean isExpanding,
                                              Ark_Float64 currentRatio)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_VISIBLEAREACHANGECALLBACK);
    argsSerializer.writeInt32(resourceId);
    argsSerializer.writeBoolean(isExpanding);
    argsSerializer.writeFloat64(currentRatio);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedVoidCallback(Ark_Int32 resourceId)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_VOIDCALLBACK);
    argsSerializer.writeInt32(resourceId);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedVoidCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_VOIDCALLBACK);
    argsSerializer.writeInt32(resourceId);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedWebKeyboardCallback(Ark_Int32 resourceId, Ark_WebKeyboardCallbackInfo keyboardCallbackInfo,
                                    Callback_WebKeyboardOptions_Void continuation)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_WEBKEYBOARDCALLBACK);
    argsSerializer.writeInt32(resourceId);
    WebKeyboardCallbackInfo_serializer::write(argsSerializer, keyboardCallbackInfo);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedWebKeyboardCallbackSync(Ark_VMContext vmContext, Ark_Int32 resourceId,
                                        Ark_WebKeyboardCallbackInfo keyboardCallbackInfo,
                                        Callback_WebKeyboardOptions_Void continuation)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_WEBKEYBOARDCALLBACK);
    argsSerializer.writeInt32(resourceId);
    WebKeyboardCallbackInfo_serializer::write(argsSerializer, keyboardCallbackInfo);
    argsSerializer.writeCallbackResource(continuation.resource);
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.call));
    argsSerializer.writePointer(reinterpret_cast<Ark_NativePointer>(continuation.callSync));
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
void CallManagedWorkerEventListener(Ark_Int32 resourceId, Ark_Event event)
{
    CallbackBuffer callbackBuffer = {{}, {}};
    const Ark_CallbackResource callbackResourceSelf = {resourceId, holdManagedCallbackResource,
                                                       releaseManagedCallbackResource};
    callbackBuffer.resourceHolder.holdCallbackResource(&callbackResourceSelf);
    SerializerBase argsSerializer = SerializerBase((KSerializerBuffer) & (callbackBuffer.buffer),
                                                   sizeof(callbackBuffer.buffer), &(callbackBuffer.resourceHolder));
    argsSerializer.writeInt32(KIND_WORKEREVENTLISTENER);
    argsSerializer.writeInt32(resourceId);
    Event_serializer::write(argsSerializer, event);
    enqueueCallback(API_KIND, &callbackBuffer);
}
void CallManagedWorkerEventListenerSync(Ark_VMContext vmContext, Ark_Int32 resourceId, Ark_Event event)
{
    SerializerBase argsSerializer = SerializerBase(nullptr);
    argsSerializer.writeInt32(API_KIND);
    argsSerializer.writeInt32(KIND_WORKEREVENTLISTENER);
    argsSerializer.writeInt32(resourceId);
    Event_serializer::write(argsSerializer, event);
    KInteropReturnBuffer callData = argsSerializer.toReturnBuffer();
    KOALA_INTEROP_CALL_VOID(vmContext, 1, callData.length, callData.data);
    callData.dispose(callData.data, callData.length);
}
Ark_NativePointer getManagedCallbackCaller(CallbackKind kind)
{
    switch (kind)
    {
    case KIND_ACCESSIBILITYACTIONINTERCEPTCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedAccessibilityActionInterceptCallback);
    case KIND_ACCESSIBILITYCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedAccessibilityCallback);
    case KIND_ACCESSIBILITYFOCUSCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedAccessibilityFocusCallback);
    case KIND_ACCESSIBILITYTRANSPARENTCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedAccessibilityTransparentCallback);
    case KIND_BUTTONMODIFIERBUILDER:
        return reinterpret_cast<Ark_NativePointer>(CallManagedButtonModifierBuilder);
    case KIND_BUTTONTRIGGERCLICKCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedButtonTriggerClickCallback);
    case KIND_CALLBACK_ACCESSIBILITYACTIONINTERCEPTRESULT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_AccessibilityActionInterceptResult_Void);
    case KIND_CALLBACK_AREA_AREA_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Area_Area_Void);
    case KIND_CALLBACK_ARRAY_I32_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Array_I32_Void);
    case KIND_CALLBACK_ARRAY_RESOURCE_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Array_Resource_Void);
    case KIND_CALLBACK_ARRAY_RESOURCESTR_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Array_ResourceStr_Void);
    case KIND_CALLBACK_ARRAY_STRING_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Array_String_Void);
    case KIND_CALLBACK_ARRAY_TEXTMENUITEM_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Array_TextMenuItem_Void);
    case KIND_CALLBACK_ARRAY_TOUCHTESTINFO_TOUCHRESULT:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Array_TouchTestInfo_TouchResult);
    case KIND_CALLBACK_AXISEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_AxisEvent_Void);
    case KIND_CALLBACK_BOOLEAN:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Boolean);
    case KIND_CALLBACK_BOOLEAN_HOVEREVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Boolean_HoverEvent_Void);
    case KIND_CALLBACK_BOOLEAN_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Boolean_Void);
    case KIND_CALLBACK_BUFFER_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Buffer_Void);
    case KIND_CALLBACK_BUSINESSERROR_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_BusinessError_Void);
    case KIND_CALLBACK_CLICKEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_ClickEvent_Void);
    case KIND_CALLBACK_COMPUTEDBARATTRIBUTE_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_ComputedBarAttribute_Void);
    case KIND_CALLBACK_COPYEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_CopyEvent_Void);
    case KIND_CALLBACK_CREATEITEM:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_CreateItem);
    case KIND_CALLBACK_CROWNEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_CrownEvent_Void);
    case KIND_CALLBACK_CUSTOMSPANMEASUREINFO_CUSTOMSPANMETRICS:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_CustomSpanMeasureInfo_CustomSpanMetrics);
    case KIND_CALLBACK_CUSTOMSPANMETRICS_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_CustomSpanMetrics_Void);
    case KIND_CALLBACK_CUTEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_CutEvent_Void);
    case KIND_CALLBACK_DATE_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Date_Void);
    case KIND_CALLBACK_DELETEVALUE_BOOLEAN:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_DeleteValue_Boolean);
    case KIND_CALLBACK_DELETEVALUE_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_DeleteValue_Void);
    case KIND_CALLBACK_DISMISSCONTENTCOVERACTION_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_DismissContentCoverAction_Void);
    case KIND_CALLBACK_DISMISSDIALOGACTION_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_DismissDialogAction_Void);
    case KIND_CALLBACK_DISMISSPOPUPACTION_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_DismissPopupAction_Void);
    case KIND_CALLBACK_DISMISSSHEETACTION_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_DismissSheetAction_Void);
    case KIND_CALLBACK_DRAGEVENT_OPT_STRING_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_DragEvent_Opt_String_Void);
    case KIND_CALLBACK_DRAWCONTEXT_CUSTOMSPANDRAWINFO_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_DrawContext_CustomSpanDrawInfo_Void);
    case KIND_CALLBACK_DRAWCONTEXT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_DrawContext_Void);
    case KIND_CALLBACK_EDITABLETEXTCHANGEVALUE_BOOLEAN:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_EditableTextChangeValue_Boolean);
    case KIND_CALLBACK_ERRORINFORMATION_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_ErrorInformation_Void);
    case KIND_CALLBACK_EXTENDER_ONFINISH:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Extender_OnFinish);
    case KIND_CALLBACK_EXTENDER_ONPROGRESS:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Extender_OnProgress);
    case KIND_CALLBACK_F64_F64_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_F64_F64_Void);
    case KIND_CALLBACK_F64_SLIDERCHANGEMODE_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_F64_SliderChangeMode_Void);
    case KIND_CALLBACK_F64_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_F64_Void);
    case KIND_CALLBACK_FOCUSAXISEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_FocusAxisEvent_Void);
    case KIND_CALLBACK_FORMCALLBACKINFO_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_FormCallbackInfo_Void);
    case KIND_CALLBACK_FULLSCREENINFO_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_FullscreenInfo_Void);
    case KIND_CALLBACK_GESTUREEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_GestureEvent_Void);
    case KIND_CALLBACK_GESTUREINFO_BASEGESTUREEVENT_GESTUREJUDGERESULT:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_GestureInfo_BaseGestureEvent_GestureJudgeResult);
    case KIND_CALLBACK_GESTUREJUDGERESULT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_GestureJudgeResult_Void);
    case KIND_CALLBACK_GESTURERECOGNIZER_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_GestureRecognizer_Void);
    case KIND_CALLBACK_HITTESTMODE_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_HitTestMode_Void);
    case KIND_CALLBACK_HOVEREVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_HoverEvent_Void);
    case KIND_CALLBACK_I32_F64_COMPUTEDBARATTRIBUTE:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_I32_F64_ComputedBarAttribute);
    case KIND_CALLBACK_I32_I32_BOOLEAN:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_I32_I32_Boolean);
    case KIND_CALLBACK_I32_I32_I32_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_I32_I32_I32_Void);
    case KIND_CALLBACK_I32_I32_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_I32_I32_Void);
    case KIND_CALLBACK_I32_TUPLE_I32_I32:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_I32_Tuple_I32_I32);
    case KIND_CALLBACK_I32_TUPLE_I32_I32_I32_I32:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_I32_Tuple_I32_I32_I32_I32);
    case KIND_CALLBACK_I32_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_I32_Void);
    case KIND_CALLBACK_I64_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_I64_Void);
    case KIND_CALLBACK_INSERTVALUE_BOOLEAN:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_InsertValue_Boolean);
    case KIND_CALLBACK_INSERTVALUE_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_InsertValue_Void);
    case KIND_CALLBACK_ITEMDRAGINFO_I32_I32_BOOLEAN_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_ItemDragInfo_I32_I32_Boolean_Void);
    case KIND_CALLBACK_ITEMDRAGINFO_I32_I32_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_ItemDragInfo_I32_I32_Void);
    case KIND_CALLBACK_ITEMDRAGINFO_I32_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_ItemDragInfo_I32_Void);
    case KIND_CALLBACK_ITEMDRAGINFO_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_ItemDragInfo_Void);
    case KIND_CALLBACK_KEYEVENT_BOOLEAN:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_KeyEvent_Boolean);
    case KIND_CALLBACK_KEYEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_KeyEvent_Void);
    case KIND_CALLBACK_LENGTH_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Length_Void);
    case KIND_CALLBACK_MAP_STRING_OPT_OBJECT:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Map_String_Opt_Object);
    case KIND_CALLBACK_MARQUEESTATE_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_MarqueeState_Void);
    case KIND_CALLBACK_MOUSEEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_MouseEvent_Void);
    case KIND_CALLBACK_NATIVEEMBEDDATAINFO_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_NativeEmbedDataInfo_Void);
    case KIND_CALLBACK_NATIVEEMBEDTOUCHINFO_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_NativeEmbedTouchInfo_Void);
    case KIND_CALLBACK_NAVDESTINATIONACTIVEREASON_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_NavDestinationActiveReason_Void);
    case KIND_CALLBACK_NAVDESTINATIONCONTEXT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_NavDestinationContext_Void);
    case KIND_CALLBACK_NAVIGATIONMODE_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_NavigationMode_Void);
    case KIND_CALLBACK_NAVIGATIONTITLEMODE_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_NavigationTitleMode_Void);
    case KIND_CALLBACK_NAVIGATIONTRANSITIONPROXY_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_NavigationTransitionProxy_Void);
    case KIND_CALLBACK_NUMBER_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Number_Void);
    case KIND_CALLBACK_OBJECT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Object_Void);
    case KIND_CALLBACK_ONALERTEVENT_BOOLEAN:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnAlertEvent_Boolean);
    case KIND_CALLBACK_ONAUDIOSTATECHANGEDEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnAudioStateChangedEvent_Void);
    case KIND_CALLBACK_ONBEFOREUNLOADEVENT_BOOLEAN:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnBeforeUnloadEvent_Boolean);
    case KIND_CALLBACK_ONCLIENTAUTHENTICATIONEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnClientAuthenticationEvent_Void);
    case KIND_CALLBACK_ONCONFIRMEVENT_BOOLEAN:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnConfirmEvent_Boolean);
    case KIND_CALLBACK_ONCONSOLEEVENT_BOOLEAN:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnConsoleEvent_Boolean);
    case KIND_CALLBACK_ONCONTEXTMENUSHOWEVENT_BOOLEAN:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnContextMenuShowEvent_Boolean);
    case KIND_CALLBACK_ONDATARESUBMITTEDEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnDataResubmittedEvent_Void);
    case KIND_CALLBACK_ONDESTORY_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnDestory_Void);
    case KIND_CALLBACK_ONDOWNLOADSTARTEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnDownloadStartEvent_Void);
    case KIND_CALLBACK_ONERRORRECEIVEEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnErrorReceiveEvent_Void);
    case KIND_CALLBACK_ONFAVICONRECEIVEDEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnFaviconReceivedEvent_Void);
    case KIND_CALLBACK_ONFIRSTCONTENTFULPAINTEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnFirstContentfulPaintEvent_Void);
    case KIND_CALLBACK_ONGEOLOCATIONSHOWEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnGeolocationShowEvent_Void);
    case KIND_CALLBACK_ONHTTPAUTHREQUESTEVENT_BOOLEAN:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnHttpAuthRequestEvent_Boolean);
    case KIND_CALLBACK_ONHTTPERRORRECEIVEEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnHttpErrorReceiveEvent_Void);
    case KIND_CALLBACK_ONINTERCEPTREQUESTEVENT_OPT_WEBRESOURCERESPONSE:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnInterceptRequestEvent_Opt_WebResourceResponse);
    case KIND_CALLBACK_ONLOADFINISHEDEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnLoadFinishedEvent_Void);
    case KIND_CALLBACK_ONLOADINTERCEPTEVENT_BOOLEAN:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnLoadInterceptEvent_Boolean);
    case KIND_CALLBACK_ONLOADSTARTEDEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnLoadStartedEvent_Void);
    case KIND_CALLBACK_ONMEASURESIZE_SIZERESULT:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_onMeasureSize_SizeResult);
    case KIND_CALLBACK_ONMOVEFROMTO:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnMoveFromTo);
    case KIND_CALLBACK_ONOVERSCROLLEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnOverScrollEvent_Void);
    case KIND_CALLBACK_ONPAGEBEGINEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnPageBeginEvent_Void);
    case KIND_CALLBACK_ONPAGEENDEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnPageEndEvent_Void);
    case KIND_CALLBACK_ONPAGEVISIBLEEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnPageVisibleEvent_Void);
    case KIND_CALLBACK_ONPERMISSIONREQUESTEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnPermissionRequestEvent_Void);
    case KIND_CALLBACK_ONPLACECHILDREN_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_onPlaceChildren_Void);
    case KIND_CALLBACK_ONPROGRESSCHANGEEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnProgressChangeEvent_Void);
    case KIND_CALLBACK_ONPROMPTEVENT_BOOLEAN:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnPromptEvent_Boolean);
    case KIND_CALLBACK_ONREFRESHACCESSEDHISTORYEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnRefreshAccessedHistoryEvent_Void);
    case KIND_CALLBACK_ONRENDEREXITEDEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnRenderExitedEvent_Void);
    case KIND_CALLBACK_ONRESOURCELOADEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnResourceLoadEvent_Void);
    case KIND_CALLBACK_ONSCALECHANGEEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnScaleChangeEvent_Void);
    case KIND_CALLBACK_ONSCREENCAPTUREREQUESTEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnScreenCaptureRequestEvent_Void);
    case KIND_CALLBACK_ONSCROLLEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnScrollEvent_Void);
    case KIND_CALLBACK_ONSCROLLFRAMEBEGINHANDLERRESULT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnScrollFrameBeginHandlerResult_Void);
    case KIND_CALLBACK_ONSEARCHRESULTRECEIVEEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnSearchResultReceiveEvent_Void);
    case KIND_CALLBACK_ONSHOWFILESELECTOREVENT_BOOLEAN:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnShowFileSelectorEvent_Boolean);
    case KIND_CALLBACK_ONSSLERROREVENTRECEIVEEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnSslErrorEventReceiveEvent_Void);
    case KIND_CALLBACK_ONTITLERECEIVEEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnTitleReceiveEvent_Void);
    case KIND_CALLBACK_ONTOUCHICONURLRECEIVEDEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnTouchIconUrlReceivedEvent_Void);
    case KIND_CALLBACK_ONWINDOWNEWEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnWindowNewEvent_Void);
    case KIND_CALLBACK_OPT_ARRAY_NAVDESTINATIONTRANSITION_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Opt_Array_NavDestinationTransition_Void);
    case KIND_CALLBACK_OPT_ARRAY_STRING_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Opt_Array_String_Void);
    case KIND_CALLBACK_OPT_CUSTOMNODEBUILDER_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Opt_CustomNodeBuilder_Void);
    case KIND_CALLBACK_OPT_NAVIGATIONANIMATEDTRANSITION_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Opt_NavigationAnimatedTransition_Void);
    case KIND_CALLBACK_OPT_OBJECT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Opt_Object_Void);
    case KIND_CALLBACK_OPT_OFFSETRESULT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Opt_OffsetResult_Void);
    case KIND_CALLBACK_OPT_SCROLLRESULT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Opt_ScrollResult_Void);
    case KIND_CALLBACK_OPT_STYLEDSTRING_OPT_ARRAY_STRING_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Opt_StyledString_Opt_Array_String_Void);
    case KIND_CALLBACK_OPT_TABCONTENTANIMATEDTRANSITION_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Opt_TabContentAnimatedTransition_Void);
    case KIND_CALLBACK_OPT_WEBRESOURCERESPONSE_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Opt_WebResourceResponse_Void);
    case KIND_CALLBACK_PLAYBACKINFO_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_PlaybackInfo_Void);
    case KIND_CALLBACK_POINTER_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Pointer_Void);
    case KIND_CALLBACK_POPINFO_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_PopInfo_Void);
    case KIND_CALLBACK_PREDRAGSTATUS_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_PreDragStatus_Void);
    case KIND_CALLBACK_PREPAREDINFO_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_PreparedInfo_Void);
    case KIND_CALLBACK_RANGEUPDATE:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_RangeUpdate);
    case KIND_CALLBACK_REFRESHSTATUS_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_RefreshStatus_Void);
    case KIND_CALLBACK_RESOURCE_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Resource_Void);
    case KIND_CALLBACK_RESOURCESTR_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_ResourceStr_Void);
    case KIND_CALLBACK_RICHEDITORCHANGEVALUE_BOOLEAN:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_RichEditorChangeValue_Boolean);
    case KIND_CALLBACK_RICHEDITORDELETEVALUE_BOOLEAN:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_RichEditorDeleteValue_Boolean);
    case KIND_CALLBACK_RICHEDITORINSERTVALUE_BOOLEAN:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_RichEditorInsertValue_Boolean);
    case KIND_CALLBACK_RICHEDITORRANGE_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_RichEditorRange_Void);
    case KIND_CALLBACK_RICHEDITORSELECTION_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_RichEditorSelection_Void);
    case KIND_CALLBACK_RICHEDITORTEXTSPANRESULT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_RichEditorTextSpanResult_Void);
    case KIND_CALLBACK_SHEETDISMISS_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_SheetDismiss_Void);
    case KIND_CALLBACK_SHEETTYPE_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_SheetType_Void);
    case KIND_CALLBACK_SIZE_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Size_Void);
    case KIND_CALLBACK_SIZERESULT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_SizeResult_Void);
    case KIND_CALLBACK_SPRINGBACKACTION_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_SpringBackAction_Void);
    case KIND_CALLBACK_STATESTYLESCHANGE:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_StateStylesChange);
    case KIND_CALLBACK_STRING:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_String);
    case KIND_CALLBACK_STRING_PASTEEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_String_PasteEvent_Void);
    case KIND_CALLBACK_STRING_SURFACERECT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_String_SurfaceRect_Void);
    case KIND_CALLBACK_STRING_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_String_Void);
    case KIND_CALLBACK_STYLEDSTRINGCHANGEVALUE_BOOLEAN:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_StyledStringChangeValue_Boolean);
    case KIND_CALLBACK_SWIPEACTIONSTATE_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_SwipeActionState_Void);
    case KIND_CALLBACK_SWIPERCONTENTTRANSITIONPROXY_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_SwiperContentTransitionProxy_Void);
    case KIND_CALLBACK_TABCONTENTTRANSITIONPROXY_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_TabContentTransitionProxy_Void);
    case KIND_CALLBACK_TERMINATIONINFO:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_TerminationInfo);
    case KIND_CALLBACK_TEXTPICKERRESULT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_TextPickerResult_Void);
    case KIND_CALLBACK_TEXTRANGE_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_TextRange_Void);
    case KIND_CALLBACK_TIMEPICKERRESULT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_TimePickerResult_Void);
    case KIND_CALLBACK_TOUCHEVENT_HITTESTMODE:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_TouchEvent_HitTestMode);
    case KIND_CALLBACK_TOUCHEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_TouchEvent_Void);
    case KIND_CALLBACK_TOUCHRESULT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_TouchResult_Void);
    case KIND_CALLBACK_TUPLE_I32_I32_I32_I32_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Tuple_I32_I32_I32_I32_Void);
    case KIND_CALLBACK_TUPLE_I32_I32_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Tuple_I32_I32_Void);
    case KIND_CALLBACK_UIEXTENSIONPROXY:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_UIExtensionProxy);
    case KIND_CALLBACK_UNION_CUSTOMNODEBUILDER_DRAGITEMINFO_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Union_CustomNodeBuilder_DragItemInfo_Void);
    case KIND_CALLBACK_USERDATASPAN_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_UserDataSpan_Void);
    case KIND_CALLBACK_VOID_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Void_Void);
    case KIND_CALLBACK_WEBKEYBOARDOPTIONS_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_WebKeyboardOptions_Void);
    case KIND_CHECKBOXMODIFIERBUILDER:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCheckBoxModifierBuilder);
    case KIND_CONTENTDIDSCROLLCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedContentDidScrollCallback);
    case KIND_CONTENTWILLSCROLLCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedContentWillScrollCallback);
    case KIND_CUSTOMNODEBUILDER:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCustomNodeBuilder);
    case KIND_DATAPANELMODIFIERBUILDER:
        return reinterpret_cast<Ark_NativePointer>(CallManagedDataPanelModifierBuilder);
    case KIND_DATAPROGRESSLISTENER:
        return reinterpret_cast<Ark_NativePointer>(CallManagedDataProgressListener);
    case KIND_EDITABLETEXTONCHANGECALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedEditableTextOnChangeCallback);
    case KIND_ERRORCALLBACK_BUSINESSERRORINTERFACE_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedErrorCallback_BusinessErrorInterface_Void);
    case KIND_FRAMECALLBACKHANDLER:
        return reinterpret_cast<Ark_NativePointer>(CallManagedFrameCallbackHandler);
    case KIND_GAUGEMODIFIERBUILDER:
        return reinterpret_cast<Ark_NativePointer>(CallManagedGaugeModifierBuilder);
    case KIND_GESTUREEVENTHANDLER:
        return reinterpret_cast<Ark_NativePointer>(CallManagedGestureEventHandler);
    case KIND_GESTURERECOGNIZERJUDGEBEGINCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedGestureRecognizerJudgeBeginCallback);
    case KIND_HOVERCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedHoverCallback);
    case KIND_IMAGECOMPLETECALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedImageCompleteCallback);
    case KIND_IMAGEERRORCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedImageErrorCallback);
    case KIND_IMAGEONCOMPLETECALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedImageOnCompleteCallback);
    case KIND_INTERCEPTIONMODECALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedInterceptionModeCallback);
    case KIND_INTERCEPTIONSHOWCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedInterceptionShowCallback);
    case KIND_LOADINGPROGRESSMODIFIERBUILDER:
        return reinterpret_cast<Ark_NativePointer>(CallManagedLoadingProgressModifierBuilder);
    case KIND_MENUCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedMenuCallback);
    case KIND_MENUITEMMODIFIERBUILDER:
        return reinterpret_cast<Ark_NativePointer>(CallManagedMenuItemModifierBuilder);
    case KIND_MENUONAPPEARCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedMenuOnAppearCallback);
    case KIND_MODIFIERKEYSTATEGETTER:
        return reinterpret_cast<Ark_NativePointer>(CallManagedModifierKeyStateGetter);
    case KIND_NAVDESTINATIONTRANSITIONDELEGATE:
        return reinterpret_cast<Ark_NativePointer>(CallManagedNavDestinationTransitionDelegate);
    case KIND_NAVEXTENDER_CREATENAVDESTINATION:
        return reinterpret_cast<Ark_NativePointer>(CallManagedNavExtender_CreateNavDestination);
    case KIND_NAVEXTENDER_ONUPDATESTACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedNavExtender_OnUpdateStack);
    case KIND_NODECONTAINEROPSONTOUCHCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedNodeContainerOpsOnTouchCallback);
    case KIND_ONADSBLOCKEDCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnAdsBlockedCallback);
    case KIND_ONALPHABETINDEXERPOPUPSELECTCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnAlphabetIndexerPopupSelectCallback);
    case KIND_ONALPHABETINDEXERREQUESTPOPUPDATACALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnAlphabetIndexerRequestPopupDataCallback);
    case KIND_ONALPHABETINDEXERSELECTCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnAlphabetIndexerSelectCallback);
    case KIND_ONCHECKBOXCHANGECALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnCheckboxChangeCallback);
    case KIND_ONCHECKBOXGROUPCHANGECALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnCheckboxGroupChangeCallback);
    case KIND_ONCONTENTSCROLLCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnContentScrollCallback);
    case KIND_ONCONTEXTMENUHIDECALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnContextMenuHideCallback);
    case KIND_ONCREATEMENUCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnCreateMenuCallback);
    case KIND_ONDIDCHANGECALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnDidChangeCallback);
    case KIND_ONDRAGEVENTCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnDragEventCallback);
    case KIND_ONFIRSTMEANINGFULPAINTCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnFirstMeaningfulPaintCallback);
    case KIND_ONFOLDSTATUSCHANGECALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnFoldStatusChangeCallback);
    case KIND_ONFULLSCREENENTERCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnFullScreenEnterCallback);
    case KIND_ONHOVERCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnHoverCallback);
    case KIND_ONHOVERSTATUSCHANGECALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnHoverStatusChangeCallback);
    case KIND_ONINTELLIGENTTRACKINGPREVENTIONCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnIntelligentTrackingPreventionCallback);
    case KIND_ONITEMDRAGSTARTCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnItemDragStartCallback);
    case KIND_ONLARGESTCONTENTFULPAINTCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnLargestContentfulPaintCallback);
    case KIND_ONMENUITEMCLICKCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnMenuItemClickCallback);
    case KIND_ONMOVEHANDLER:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnMoveHandler);
    case KIND_ONNATIVEEMBEDVISIBILITYCHANGECALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnNativeEmbedVisibilityChangeCallback);
    case KIND_ONNAVIGATIONENTRYCOMMITTEDCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnNavigationEntryCommittedCallback);
    case KIND_ONOVERRIDEURLLOADINGCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnOverrideUrlLoadingCallback);
    case KIND_ONPASTECALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnPasteCallback);
    case KIND_ONRADIOCHANGECALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnRadioChangeCallback);
    case KIND_ONRATINGCHANGECALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnRatingChangeCallback);
    case KIND_ONRENDERPROCESSNOTRESPONDINGCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnRenderProcessNotRespondingCallback);
    case KIND_ONRENDERPROCESSRESPONDINGCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnRenderProcessRespondingCallback);
    case KIND_ONSAFEBROWSINGCHECKRESULTCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnSafeBrowsingCheckResultCallback);
    case KIND_ONSCROLLCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnScrollCallback);
    case KIND_ONSCROLLEDGECALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnScrollEdgeCallback);
    case KIND_ONSCROLLFRAMEBEGINCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnScrollFrameBeginCallback);
    case KIND_ONSCROLLVISIBLECONTENTCHANGECALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnScrollVisibleContentChangeCallback);
    case KIND_ONSELECTCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnSelectCallback);
    case KIND_ONSSLERROREVENTCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnSslErrorEventCallback);
    case KIND_ONSUBMITCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnSubmitCallback);
    case KIND_ONSWIPERANIMATIONENDCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnSwiperAnimationEndCallback);
    case KIND_ONSWIPERANIMATIONSTARTCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnSwiperAnimationStartCallback);
    case KIND_ONSWIPERGESTURESWIPECALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnSwiperGestureSwipeCallback);
    case KIND_ONTABSANIMATIONENDCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnTabsAnimationEndCallback);
    case KIND_ONTABSANIMATIONSTARTCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnTabsAnimationStartCallback);
    case KIND_ONTABSCONTENTWILLCHANGECALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnTabsContentWillChangeCallback);
    case KIND_ONTABSGESTURESWIPECALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnTabsGestureSwipeCallback);
    case KIND_ONTEXTPICKERCHANGECALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnTextPickerChangeCallback);
    case KIND_ONTEXTSELECTIONCHANGECALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnTextSelectionChangeCallback);
    case KIND_ONTIMEPICKERCHANGECALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnTimePickerChangeCallback);
    case KIND_ONVIEWPORTFITCHANGEDCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnViewportFitChangedCallback);
    case KIND_ONWILLSCROLLCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnWillScrollCallback);
    case KIND_PAGEMAPNODEBUILDER:
        return reinterpret_cast<Ark_NativePointer>(CallManagedPageMapNodeBuilder);
    case KIND_PASTEBUTTONCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedPasteButtonCallback);
    case KIND_PASTEEVENTCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedPasteEventCallback);
    case KIND_PLUGINERRORCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedPluginErrorCallback);
    case KIND_POPUPSTATECHANGECALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedPopupStateChangeCallback);
    case KIND_PROGRESSMODIFIERBUILDER:
        return reinterpret_cast<Ark_NativePointer>(CallManagedProgressModifierBuilder);
    case KIND_RADIOMODIFIERBUILDER:
        return reinterpret_cast<Ark_NativePointer>(CallManagedRadioModifierBuilder);
    case KIND_RATINGMODIFIERBUILDER:
        return reinterpret_cast<Ark_NativePointer>(CallManagedRatingModifierBuilder);
    case KIND_RESTRICTEDWORKER_ONERROR_CALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedRestrictedWorker_onerror_Callback);
    case KIND_RESTRICTEDWORKER_ONEXIT_CALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedRestrictedWorker_onexit_Callback);
    case KIND_RESTRICTEDWORKER_ONMESSAGE_CALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedRestrictedWorker_onmessage_Callback);
    case KIND_REUSEIDCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedReuseIdCallback);
    case KIND_ROUTERFINISHCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedRouterFinishCallback);
    case KIND_SAVEBUTTONCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedSaveButtonCallback);
    case KIND_SCROLLONSCROLLCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedScrollOnScrollCallback);
    case KIND_SCROLLONWILLSCROLLCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedScrollOnWillScrollCallback);
    case KIND_SEARCHSUBMITCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedSearchSubmitCallback);
    case KIND_SEARCHVALUECALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedSearchValueCallback);
    case KIND_SHOULDBUILTINRECOGNIZERPARALLELWITHCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedShouldBuiltInRecognizerParallelWithCallback);
    case KIND_SIZECHANGECALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedSizeChangeCallback);
    case KIND_SLIDERMODIFIERBUILDER:
        return reinterpret_cast<Ark_NativePointer>(CallManagedSliderModifierBuilder);
    case KIND_SLIDERTRIGGERCHANGECALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedSliderTriggerChangeCallback);
    case KIND_STYLEDSTRINGMARSHALLCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedStyledStringMarshallCallback);
    case KIND_STYLEDSTRINGUNMARSHALLCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedStyledStringUnmarshallCallback);
    case KIND_SUBMITCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedSubmitCallback);
    case KIND_SYNTHETIC_ASYNCCALLBACK_IMAGE_PIXELMAP_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedsynthetic_AsyncCallback_image_PixelMap_Void);
    case KIND_SYNTHETIC_CALLBACK_ARRAY_STRING_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedsynthetic_Callback_Array_String_Void);
    case KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedsynthetic_Callback_Boolean_Void);
    case KIND_SYNTHETIC_CALLBACK_DISMISSDIALOGACTION_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedsynthetic_Callback_DismissDialogAction_Void);
    case KIND_SYNTHETIC_CALLBACK_F64_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedsynthetic_Callback_F64_Void);
    case KIND_SYNTHETIC_CALLBACK_KEYEVENT_BOOLEAN:
        return reinterpret_cast<Ark_NativePointer>(CallManagedsynthetic_Callback_KeyEvent_Boolean);
    case KIND_SYNTHETIC_CALLBACK_STRING_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedsynthetic_Callback_String_Void);
    case KIND_SYNTHETIC_CALLBACK_TEXTPICKERRESULT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedsynthetic_Callback_TextPickerResult_Void);
    case KIND_SYNTHETIC_CALLBACK_TIMEPICKERRESULT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedsynthetic_Callback_TimePickerResult_Void);
    case KIND_SYNTHETIC_CALLBACK_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedsynthetic_Callback_Void);
    case KIND_TABSCUSTOMCONTENTTRANSITIONCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedTabsCustomContentTransitionCallback);
    case KIND_TEXTAREASUBMITCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedTextAreaSubmitCallback);
    case KIND_TEXTCLOCKMODIFIERBUILDER:
        return reinterpret_cast<Ark_NativePointer>(CallManagedTextClockModifierBuilder);
    case KIND_TEXTFIELDVALUECALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedTextFieldValueCallback);
    case KIND_TEXTPICKERENTERSELECTEDAREACALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedTextPickerEnterSelectedAreaCallback);
    case KIND_TEXTPICKERSCROLLSTOPCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedTextPickerScrollStopCallback);
    case KIND_TEXTTIMERMODIFIERBUILDER:
        return reinterpret_cast<Ark_NativePointer>(CallManagedTextTimerModifierBuilder);
    case KIND_TIMERCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedTimerCallback);
    case KIND_TOGGLEMODIFIERBUILDER:
        return reinterpret_cast<Ark_NativePointer>(CallManagedToggleModifierBuilder);
    case KIND_TOUCHTESTDONECALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedTouchTestDoneCallback);
    case KIND_TRANSITIONFINISHCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedTransitionFinishCallback);
    case KIND_TYPE_COMMONMETHOD_ONDRAGSTART:
        return reinterpret_cast<Ark_NativePointer>(CallManagedType_CommonMethod_onDragStart);
    case KIND_TYPE_NAVIGATIONATTRIBUTE_CUSTOMNAVCONTENTTRANSITION:
        return reinterpret_cast<Ark_NativePointer>(CallManagedType_NavigationAttribute_customNavContentTransition);
    case KIND_UPDATETRANSITIONCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedUpdateTransitionCallback);
    case KIND_VISIBLEAREACHANGECALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedVisibleAreaChangeCallback);
    case KIND_VOIDCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedVoidCallback);
    case KIND_WEBKEYBOARDCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedWebKeyboardCallback);
    case KIND_WORKEREVENTLISTENER:
        return reinterpret_cast<Ark_NativePointer>(CallManagedWorkerEventListener);
    }
    return nullptr;
}
Ark_NativePointer getManagedCallbackCallerSync(CallbackKind kind)
{
    switch (kind)
    {
    case KIND_ACCESSIBILITYACTIONINTERCEPTCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedAccessibilityActionInterceptCallbackSync);
    case KIND_ACCESSIBILITYCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedAccessibilityCallbackSync);
    case KIND_ACCESSIBILITYFOCUSCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedAccessibilityFocusCallbackSync);
    case KIND_ACCESSIBILITYTRANSPARENTCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedAccessibilityTransparentCallbackSync);
    case KIND_BUTTONMODIFIERBUILDER:
        return reinterpret_cast<Ark_NativePointer>(CallManagedButtonModifierBuilderSync);
    case KIND_BUTTONTRIGGERCLICKCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedButtonTriggerClickCallbackSync);
    case KIND_CALLBACK_ACCESSIBILITYACTIONINTERCEPTRESULT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_AccessibilityActionInterceptResult_VoidSync);
    case KIND_CALLBACK_AREA_AREA_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Area_Area_VoidSync);
    case KIND_CALLBACK_ARRAY_I32_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Array_I32_VoidSync);
    case KIND_CALLBACK_ARRAY_RESOURCE_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Array_Resource_VoidSync);
    case KIND_CALLBACK_ARRAY_RESOURCESTR_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Array_ResourceStr_VoidSync);
    case KIND_CALLBACK_ARRAY_STRING_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Array_String_VoidSync);
    case KIND_CALLBACK_ARRAY_TEXTMENUITEM_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Array_TextMenuItem_VoidSync);
    case KIND_CALLBACK_ARRAY_TOUCHTESTINFO_TOUCHRESULT:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Array_TouchTestInfo_TouchResultSync);
    case KIND_CALLBACK_AXISEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_AxisEvent_VoidSync);
    case KIND_CALLBACK_BOOLEAN:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_BooleanSync);
    case KIND_CALLBACK_BOOLEAN_HOVEREVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Boolean_HoverEvent_VoidSync);
    case KIND_CALLBACK_BOOLEAN_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Boolean_VoidSync);
    case KIND_CALLBACK_BUFFER_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Buffer_VoidSync);
    case KIND_CALLBACK_BUSINESSERROR_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_BusinessError_VoidSync);
    case KIND_CALLBACK_CLICKEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_ClickEvent_VoidSync);
    case KIND_CALLBACK_COMPUTEDBARATTRIBUTE_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_ComputedBarAttribute_VoidSync);
    case KIND_CALLBACK_COPYEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_CopyEvent_VoidSync);
    case KIND_CALLBACK_CREATEITEM:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_CreateItemSync);
    case KIND_CALLBACK_CROWNEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_CrownEvent_VoidSync);
    case KIND_CALLBACK_CUSTOMSPANMEASUREINFO_CUSTOMSPANMETRICS:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_CustomSpanMeasureInfo_CustomSpanMetricsSync);
    case KIND_CALLBACK_CUSTOMSPANMETRICS_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_CustomSpanMetrics_VoidSync);
    case KIND_CALLBACK_CUTEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_CutEvent_VoidSync);
    case KIND_CALLBACK_DATE_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Date_VoidSync);
    case KIND_CALLBACK_DELETEVALUE_BOOLEAN:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_DeleteValue_BooleanSync);
    case KIND_CALLBACK_DELETEVALUE_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_DeleteValue_VoidSync);
    case KIND_CALLBACK_DISMISSCONTENTCOVERACTION_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_DismissContentCoverAction_VoidSync);
    case KIND_CALLBACK_DISMISSDIALOGACTION_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_DismissDialogAction_VoidSync);
    case KIND_CALLBACK_DISMISSPOPUPACTION_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_DismissPopupAction_VoidSync);
    case KIND_CALLBACK_DISMISSSHEETACTION_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_DismissSheetAction_VoidSync);
    case KIND_CALLBACK_DRAGEVENT_OPT_STRING_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_DragEvent_Opt_String_VoidSync);
    case KIND_CALLBACK_DRAWCONTEXT_CUSTOMSPANDRAWINFO_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_DrawContext_CustomSpanDrawInfo_VoidSync);
    case KIND_CALLBACK_DRAWCONTEXT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_DrawContext_VoidSync);
    case KIND_CALLBACK_EDITABLETEXTCHANGEVALUE_BOOLEAN:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_EditableTextChangeValue_BooleanSync);
    case KIND_CALLBACK_ERRORINFORMATION_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_ErrorInformation_VoidSync);
    case KIND_CALLBACK_EXTENDER_ONFINISH:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Extender_OnFinishSync);
    case KIND_CALLBACK_EXTENDER_ONPROGRESS:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Extender_OnProgressSync);
    case KIND_CALLBACK_F64_F64_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_F64_F64_VoidSync);
    case KIND_CALLBACK_F64_SLIDERCHANGEMODE_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_F64_SliderChangeMode_VoidSync);
    case KIND_CALLBACK_F64_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_F64_VoidSync);
    case KIND_CALLBACK_FOCUSAXISEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_FocusAxisEvent_VoidSync);
    case KIND_CALLBACK_FORMCALLBACKINFO_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_FormCallbackInfo_VoidSync);
    case KIND_CALLBACK_FULLSCREENINFO_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_FullscreenInfo_VoidSync);
    case KIND_CALLBACK_GESTUREEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_GestureEvent_VoidSync);
    case KIND_CALLBACK_GESTUREINFO_BASEGESTUREEVENT_GESTUREJUDGERESULT:
        return reinterpret_cast<Ark_NativePointer>(
            CallManagedCallback_GestureInfo_BaseGestureEvent_GestureJudgeResultSync);
    case KIND_CALLBACK_GESTUREJUDGERESULT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_GestureJudgeResult_VoidSync);
    case KIND_CALLBACK_GESTURERECOGNIZER_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_GestureRecognizer_VoidSync);
    case KIND_CALLBACK_HITTESTMODE_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_HitTestMode_VoidSync);
    case KIND_CALLBACK_HOVEREVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_HoverEvent_VoidSync);
    case KIND_CALLBACK_I32_F64_COMPUTEDBARATTRIBUTE:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_I32_F64_ComputedBarAttributeSync);
    case KIND_CALLBACK_I32_I32_BOOLEAN:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_I32_I32_BooleanSync);
    case KIND_CALLBACK_I32_I32_I32_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_I32_I32_I32_VoidSync);
    case KIND_CALLBACK_I32_I32_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_I32_I32_VoidSync);
    case KIND_CALLBACK_I32_TUPLE_I32_I32:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_I32_Tuple_I32_I32Sync);
    case KIND_CALLBACK_I32_TUPLE_I32_I32_I32_I32:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_I32_Tuple_I32_I32_I32_I32Sync);
    case KIND_CALLBACK_I32_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_I32_VoidSync);
    case KIND_CALLBACK_I64_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_I64_VoidSync);
    case KIND_CALLBACK_INSERTVALUE_BOOLEAN:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_InsertValue_BooleanSync);
    case KIND_CALLBACK_INSERTVALUE_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_InsertValue_VoidSync);
    case KIND_CALLBACK_ITEMDRAGINFO_I32_I32_BOOLEAN_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_ItemDragInfo_I32_I32_Boolean_VoidSync);
    case KIND_CALLBACK_ITEMDRAGINFO_I32_I32_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_ItemDragInfo_I32_I32_VoidSync);
    case KIND_CALLBACK_ITEMDRAGINFO_I32_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_ItemDragInfo_I32_VoidSync);
    case KIND_CALLBACK_ITEMDRAGINFO_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_ItemDragInfo_VoidSync);
    case KIND_CALLBACK_KEYEVENT_BOOLEAN:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_KeyEvent_BooleanSync);
    case KIND_CALLBACK_KEYEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_KeyEvent_VoidSync);
    case KIND_CALLBACK_LENGTH_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Length_VoidSync);
    case KIND_CALLBACK_MAP_STRING_OPT_OBJECT:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Map_String_Opt_ObjectSync);
    case KIND_CALLBACK_MARQUEESTATE_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_MarqueeState_VoidSync);
    case KIND_CALLBACK_MOUSEEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_MouseEvent_VoidSync);
    case KIND_CALLBACK_NATIVEEMBEDDATAINFO_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_NativeEmbedDataInfo_VoidSync);
    case KIND_CALLBACK_NATIVEEMBEDTOUCHINFO_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_NativeEmbedTouchInfo_VoidSync);
    case KIND_CALLBACK_NAVDESTINATIONACTIVEREASON_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_NavDestinationActiveReason_VoidSync);
    case KIND_CALLBACK_NAVDESTINATIONCONTEXT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_NavDestinationContext_VoidSync);
    case KIND_CALLBACK_NAVIGATIONMODE_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_NavigationMode_VoidSync);
    case KIND_CALLBACK_NAVIGATIONTITLEMODE_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_NavigationTitleMode_VoidSync);
    case KIND_CALLBACK_NAVIGATIONTRANSITIONPROXY_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_NavigationTransitionProxy_VoidSync);
    case KIND_CALLBACK_NUMBER_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Number_VoidSync);
    case KIND_CALLBACK_OBJECT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Object_VoidSync);
    case KIND_CALLBACK_ONALERTEVENT_BOOLEAN:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnAlertEvent_BooleanSync);
    case KIND_CALLBACK_ONAUDIOSTATECHANGEDEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnAudioStateChangedEvent_VoidSync);
    case KIND_CALLBACK_ONBEFOREUNLOADEVENT_BOOLEAN:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnBeforeUnloadEvent_BooleanSync);
    case KIND_CALLBACK_ONCLIENTAUTHENTICATIONEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnClientAuthenticationEvent_VoidSync);
    case KIND_CALLBACK_ONCONFIRMEVENT_BOOLEAN:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnConfirmEvent_BooleanSync);
    case KIND_CALLBACK_ONCONSOLEEVENT_BOOLEAN:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnConsoleEvent_BooleanSync);
    case KIND_CALLBACK_ONCONTEXTMENUSHOWEVENT_BOOLEAN:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnContextMenuShowEvent_BooleanSync);
    case KIND_CALLBACK_ONDATARESUBMITTEDEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnDataResubmittedEvent_VoidSync);
    case KIND_CALLBACK_ONDESTORY_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnDestory_VoidSync);
    case KIND_CALLBACK_ONDOWNLOADSTARTEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnDownloadStartEvent_VoidSync);
    case KIND_CALLBACK_ONERRORRECEIVEEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnErrorReceiveEvent_VoidSync);
    case KIND_CALLBACK_ONFAVICONRECEIVEDEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnFaviconReceivedEvent_VoidSync);
    case KIND_CALLBACK_ONFIRSTCONTENTFULPAINTEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnFirstContentfulPaintEvent_VoidSync);
    case KIND_CALLBACK_ONGEOLOCATIONSHOWEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnGeolocationShowEvent_VoidSync);
    case KIND_CALLBACK_ONHTTPAUTHREQUESTEVENT_BOOLEAN:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnHttpAuthRequestEvent_BooleanSync);
    case KIND_CALLBACK_ONHTTPERRORRECEIVEEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnHttpErrorReceiveEvent_VoidSync);
    case KIND_CALLBACK_ONINTERCEPTREQUESTEVENT_OPT_WEBRESOURCERESPONSE:
        return reinterpret_cast<Ark_NativePointer>(
            CallManagedCallback_OnInterceptRequestEvent_Opt_WebResourceResponseSync);
    case KIND_CALLBACK_ONLOADFINISHEDEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnLoadFinishedEvent_VoidSync);
    case KIND_CALLBACK_ONLOADINTERCEPTEVENT_BOOLEAN:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnLoadInterceptEvent_BooleanSync);
    case KIND_CALLBACK_ONLOADSTARTEDEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnLoadStartedEvent_VoidSync);
    case KIND_CALLBACK_ONMEASURESIZE_SIZERESULT:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_onMeasureSize_SizeResultSync);
    case KIND_CALLBACK_ONMOVEFROMTO:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnMoveFromToSync);
    case KIND_CALLBACK_ONOVERSCROLLEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnOverScrollEvent_VoidSync);
    case KIND_CALLBACK_ONPAGEBEGINEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnPageBeginEvent_VoidSync);
    case KIND_CALLBACK_ONPAGEENDEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnPageEndEvent_VoidSync);
    case KIND_CALLBACK_ONPAGEVISIBLEEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnPageVisibleEvent_VoidSync);
    case KIND_CALLBACK_ONPERMISSIONREQUESTEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnPermissionRequestEvent_VoidSync);
    case KIND_CALLBACK_ONPLACECHILDREN_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_onPlaceChildren_VoidSync);
    case KIND_CALLBACK_ONPROGRESSCHANGEEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnProgressChangeEvent_VoidSync);
    case KIND_CALLBACK_ONPROMPTEVENT_BOOLEAN:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnPromptEvent_BooleanSync);
    case KIND_CALLBACK_ONREFRESHACCESSEDHISTORYEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnRefreshAccessedHistoryEvent_VoidSync);
    case KIND_CALLBACK_ONRENDEREXITEDEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnRenderExitedEvent_VoidSync);
    case KIND_CALLBACK_ONRESOURCELOADEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnResourceLoadEvent_VoidSync);
    case KIND_CALLBACK_ONSCALECHANGEEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnScaleChangeEvent_VoidSync);
    case KIND_CALLBACK_ONSCREENCAPTUREREQUESTEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnScreenCaptureRequestEvent_VoidSync);
    case KIND_CALLBACK_ONSCROLLEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnScrollEvent_VoidSync);
    case KIND_CALLBACK_ONSCROLLFRAMEBEGINHANDLERRESULT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnScrollFrameBeginHandlerResult_VoidSync);
    case KIND_CALLBACK_ONSEARCHRESULTRECEIVEEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnSearchResultReceiveEvent_VoidSync);
    case KIND_CALLBACK_ONSHOWFILESELECTOREVENT_BOOLEAN:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnShowFileSelectorEvent_BooleanSync);
    case KIND_CALLBACK_ONSSLERROREVENTRECEIVEEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnSslErrorEventReceiveEvent_VoidSync);
    case KIND_CALLBACK_ONTITLERECEIVEEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnTitleReceiveEvent_VoidSync);
    case KIND_CALLBACK_ONTOUCHICONURLRECEIVEDEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnTouchIconUrlReceivedEvent_VoidSync);
    case KIND_CALLBACK_ONWINDOWNEWEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_OnWindowNewEvent_VoidSync);
    case KIND_CALLBACK_OPT_ARRAY_NAVDESTINATIONTRANSITION_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Opt_Array_NavDestinationTransition_VoidSync);
    case KIND_CALLBACK_OPT_ARRAY_STRING_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Opt_Array_String_VoidSync);
    case KIND_CALLBACK_OPT_CUSTOMNODEBUILDER_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Opt_CustomNodeBuilder_VoidSync);
    case KIND_CALLBACK_OPT_NAVIGATIONANIMATEDTRANSITION_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Opt_NavigationAnimatedTransition_VoidSync);
    case KIND_CALLBACK_OPT_OBJECT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Opt_Object_VoidSync);
    case KIND_CALLBACK_OPT_OFFSETRESULT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Opt_OffsetResult_VoidSync);
    case KIND_CALLBACK_OPT_SCROLLRESULT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Opt_ScrollResult_VoidSync);
    case KIND_CALLBACK_OPT_STYLEDSTRING_OPT_ARRAY_STRING_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Opt_StyledString_Opt_Array_String_VoidSync);
    case KIND_CALLBACK_OPT_TABCONTENTANIMATEDTRANSITION_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Opt_TabContentAnimatedTransition_VoidSync);
    case KIND_CALLBACK_OPT_WEBRESOURCERESPONSE_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Opt_WebResourceResponse_VoidSync);
    case KIND_CALLBACK_PLAYBACKINFO_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_PlaybackInfo_VoidSync);
    case KIND_CALLBACK_POINTER_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Pointer_VoidSync);
    case KIND_CALLBACK_POPINFO_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_PopInfo_VoidSync);
    case KIND_CALLBACK_PREDRAGSTATUS_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_PreDragStatus_VoidSync);
    case KIND_CALLBACK_PREPAREDINFO_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_PreparedInfo_VoidSync);
    case KIND_CALLBACK_RANGEUPDATE:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_RangeUpdateSync);
    case KIND_CALLBACK_REFRESHSTATUS_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_RefreshStatus_VoidSync);
    case KIND_CALLBACK_RESOURCE_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Resource_VoidSync);
    case KIND_CALLBACK_RESOURCESTR_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_ResourceStr_VoidSync);
    case KIND_CALLBACK_RICHEDITORCHANGEVALUE_BOOLEAN:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_RichEditorChangeValue_BooleanSync);
    case KIND_CALLBACK_RICHEDITORDELETEVALUE_BOOLEAN:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_RichEditorDeleteValue_BooleanSync);
    case KIND_CALLBACK_RICHEDITORINSERTVALUE_BOOLEAN:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_RichEditorInsertValue_BooleanSync);
    case KIND_CALLBACK_RICHEDITORRANGE_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_RichEditorRange_VoidSync);
    case KIND_CALLBACK_RICHEDITORSELECTION_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_RichEditorSelection_VoidSync);
    case KIND_CALLBACK_RICHEDITORTEXTSPANRESULT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_RichEditorTextSpanResult_VoidSync);
    case KIND_CALLBACK_SHEETDISMISS_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_SheetDismiss_VoidSync);
    case KIND_CALLBACK_SHEETTYPE_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_SheetType_VoidSync);
    case KIND_CALLBACK_SIZE_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Size_VoidSync);
    case KIND_CALLBACK_SIZERESULT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_SizeResult_VoidSync);
    case KIND_CALLBACK_SPRINGBACKACTION_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_SpringBackAction_VoidSync);
    case KIND_CALLBACK_STATESTYLESCHANGE:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_StateStylesChangeSync);
    case KIND_CALLBACK_STRING:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_StringSync);
    case KIND_CALLBACK_STRING_PASTEEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_String_PasteEvent_VoidSync);
    case KIND_CALLBACK_STRING_SURFACERECT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_String_SurfaceRect_VoidSync);
    case KIND_CALLBACK_STRING_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_String_VoidSync);
    case KIND_CALLBACK_STYLEDSTRINGCHANGEVALUE_BOOLEAN:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_StyledStringChangeValue_BooleanSync);
    case KIND_CALLBACK_SWIPEACTIONSTATE_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_SwipeActionState_VoidSync);
    case KIND_CALLBACK_SWIPERCONTENTTRANSITIONPROXY_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_SwiperContentTransitionProxy_VoidSync);
    case KIND_CALLBACK_TABCONTENTTRANSITIONPROXY_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_TabContentTransitionProxy_VoidSync);
    case KIND_CALLBACK_TERMINATIONINFO:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_TerminationInfoSync);
    case KIND_CALLBACK_TEXTPICKERRESULT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_TextPickerResult_VoidSync);
    case KIND_CALLBACK_TEXTRANGE_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_TextRange_VoidSync);
    case KIND_CALLBACK_TIMEPICKERRESULT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_TimePickerResult_VoidSync);
    case KIND_CALLBACK_TOUCHEVENT_HITTESTMODE:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_TouchEvent_HitTestModeSync);
    case KIND_CALLBACK_TOUCHEVENT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_TouchEvent_VoidSync);
    case KIND_CALLBACK_TOUCHRESULT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_TouchResult_VoidSync);
    case KIND_CALLBACK_TUPLE_I32_I32_I32_I32_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Tuple_I32_I32_I32_I32_VoidSync);
    case KIND_CALLBACK_TUPLE_I32_I32_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Tuple_I32_I32_VoidSync);
    case KIND_CALLBACK_UIEXTENSIONPROXY:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_UIExtensionProxySync);
    case KIND_CALLBACK_UNION_CUSTOMNODEBUILDER_DRAGITEMINFO_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Union_CustomNodeBuilder_DragItemInfo_VoidSync);
    case KIND_CALLBACK_USERDATASPAN_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_UserDataSpan_VoidSync);
    case KIND_CALLBACK_VOID_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_Void_VoidSync);
    case KIND_CALLBACK_WEBKEYBOARDOPTIONS_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCallback_WebKeyboardOptions_VoidSync);
    case KIND_CHECKBOXMODIFIERBUILDER:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCheckBoxModifierBuilderSync);
    case KIND_CONTENTDIDSCROLLCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedContentDidScrollCallbackSync);
    case KIND_CONTENTWILLSCROLLCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedContentWillScrollCallbackSync);
    case KIND_CUSTOMNODEBUILDER:
        return reinterpret_cast<Ark_NativePointer>(CallManagedCustomNodeBuilderSync);
    case KIND_DATAPANELMODIFIERBUILDER:
        return reinterpret_cast<Ark_NativePointer>(CallManagedDataPanelModifierBuilderSync);
    case KIND_DATAPROGRESSLISTENER:
        return reinterpret_cast<Ark_NativePointer>(CallManagedDataProgressListenerSync);
    case KIND_EDITABLETEXTONCHANGECALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedEditableTextOnChangeCallbackSync);
    case KIND_ERRORCALLBACK_BUSINESSERRORINTERFACE_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedErrorCallback_BusinessErrorInterface_VoidSync);
    case KIND_FRAMECALLBACKHANDLER:
        return reinterpret_cast<Ark_NativePointer>(CallManagedFrameCallbackHandlerSync);
    case KIND_GAUGEMODIFIERBUILDER:
        return reinterpret_cast<Ark_NativePointer>(CallManagedGaugeModifierBuilderSync);
    case KIND_GESTUREEVENTHANDLER:
        return reinterpret_cast<Ark_NativePointer>(CallManagedGestureEventHandlerSync);
    case KIND_GESTURERECOGNIZERJUDGEBEGINCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedGestureRecognizerJudgeBeginCallbackSync);
    case KIND_HOVERCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedHoverCallbackSync);
    case KIND_IMAGECOMPLETECALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedImageCompleteCallbackSync);
    case KIND_IMAGEERRORCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedImageErrorCallbackSync);
    case KIND_IMAGEONCOMPLETECALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedImageOnCompleteCallbackSync);
    case KIND_INTERCEPTIONMODECALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedInterceptionModeCallbackSync);
    case KIND_INTERCEPTIONSHOWCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedInterceptionShowCallbackSync);
    case KIND_LOADINGPROGRESSMODIFIERBUILDER:
        return reinterpret_cast<Ark_NativePointer>(CallManagedLoadingProgressModifierBuilderSync);
    case KIND_MENUCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedMenuCallbackSync);
    case KIND_MENUITEMMODIFIERBUILDER:
        return reinterpret_cast<Ark_NativePointer>(CallManagedMenuItemModifierBuilderSync);
    case KIND_MENUONAPPEARCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedMenuOnAppearCallbackSync);
    case KIND_MODIFIERKEYSTATEGETTER:
        return reinterpret_cast<Ark_NativePointer>(CallManagedModifierKeyStateGetterSync);
    case KIND_NAVDESTINATIONTRANSITIONDELEGATE:
        return reinterpret_cast<Ark_NativePointer>(CallManagedNavDestinationTransitionDelegateSync);
    case KIND_NAVEXTENDER_CREATENAVDESTINATION:
        return reinterpret_cast<Ark_NativePointer>(CallManagedNavExtender_CreateNavDestinationSync);
    case KIND_NAVEXTENDER_ONUPDATESTACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedNavExtender_OnUpdateStackSync);
    case KIND_NODECONTAINEROPSONTOUCHCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedNodeContainerOpsOnTouchCallbackSync);
    case KIND_ONADSBLOCKEDCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnAdsBlockedCallbackSync);
    case KIND_ONALPHABETINDEXERPOPUPSELECTCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnAlphabetIndexerPopupSelectCallbackSync);
    case KIND_ONALPHABETINDEXERREQUESTPOPUPDATACALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnAlphabetIndexerRequestPopupDataCallbackSync);
    case KIND_ONALPHABETINDEXERSELECTCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnAlphabetIndexerSelectCallbackSync);
    case KIND_ONCHECKBOXCHANGECALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnCheckboxChangeCallbackSync);
    case KIND_ONCHECKBOXGROUPCHANGECALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnCheckboxGroupChangeCallbackSync);
    case KIND_ONCONTENTSCROLLCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnContentScrollCallbackSync);
    case KIND_ONCONTEXTMENUHIDECALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnContextMenuHideCallbackSync);
    case KIND_ONCREATEMENUCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnCreateMenuCallbackSync);
    case KIND_ONDIDCHANGECALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnDidChangeCallbackSync);
    case KIND_ONDRAGEVENTCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnDragEventCallbackSync);
    case KIND_ONFIRSTMEANINGFULPAINTCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnFirstMeaningfulPaintCallbackSync);
    case KIND_ONFOLDSTATUSCHANGECALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnFoldStatusChangeCallbackSync);
    case KIND_ONFULLSCREENENTERCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnFullScreenEnterCallbackSync);
    case KIND_ONHOVERCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnHoverCallbackSync);
    case KIND_ONHOVERSTATUSCHANGECALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnHoverStatusChangeCallbackSync);
    case KIND_ONINTELLIGENTTRACKINGPREVENTIONCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnIntelligentTrackingPreventionCallbackSync);
    case KIND_ONITEMDRAGSTARTCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnItemDragStartCallbackSync);
    case KIND_ONLARGESTCONTENTFULPAINTCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnLargestContentfulPaintCallbackSync);
    case KIND_ONMENUITEMCLICKCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnMenuItemClickCallbackSync);
    case KIND_ONMOVEHANDLER:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnMoveHandlerSync);
    case KIND_ONNATIVEEMBEDVISIBILITYCHANGECALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnNativeEmbedVisibilityChangeCallbackSync);
    case KIND_ONNAVIGATIONENTRYCOMMITTEDCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnNavigationEntryCommittedCallbackSync);
    case KIND_ONOVERRIDEURLLOADINGCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnOverrideUrlLoadingCallbackSync);
    case KIND_ONPASTECALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnPasteCallbackSync);
    case KIND_ONRADIOCHANGECALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnRadioChangeCallbackSync);
    case KIND_ONRATINGCHANGECALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnRatingChangeCallbackSync);
    case KIND_ONRENDERPROCESSNOTRESPONDINGCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnRenderProcessNotRespondingCallbackSync);
    case KIND_ONRENDERPROCESSRESPONDINGCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnRenderProcessRespondingCallbackSync);
    case KIND_ONSAFEBROWSINGCHECKRESULTCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnSafeBrowsingCheckResultCallbackSync);
    case KIND_ONSCROLLCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnScrollCallbackSync);
    case KIND_ONSCROLLEDGECALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnScrollEdgeCallbackSync);
    case KIND_ONSCROLLFRAMEBEGINCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnScrollFrameBeginCallbackSync);
    case KIND_ONSCROLLVISIBLECONTENTCHANGECALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnScrollVisibleContentChangeCallbackSync);
    case KIND_ONSELECTCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnSelectCallbackSync);
    case KIND_ONSSLERROREVENTCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnSslErrorEventCallbackSync);
    case KIND_ONSUBMITCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnSubmitCallbackSync);
    case KIND_ONSWIPERANIMATIONENDCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnSwiperAnimationEndCallbackSync);
    case KIND_ONSWIPERANIMATIONSTARTCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnSwiperAnimationStartCallbackSync);
    case KIND_ONSWIPERGESTURESWIPECALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnSwiperGestureSwipeCallbackSync);
    case KIND_ONTABSANIMATIONENDCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnTabsAnimationEndCallbackSync);
    case KIND_ONTABSANIMATIONSTARTCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnTabsAnimationStartCallbackSync);
    case KIND_ONTABSCONTENTWILLCHANGECALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnTabsContentWillChangeCallbackSync);
    case KIND_ONTABSGESTURESWIPECALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnTabsGestureSwipeCallbackSync);
    case KIND_ONTEXTPICKERCHANGECALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnTextPickerChangeCallbackSync);
    case KIND_ONTEXTSELECTIONCHANGECALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnTextSelectionChangeCallbackSync);
    case KIND_ONTIMEPICKERCHANGECALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnTimePickerChangeCallbackSync);
    case KIND_ONVIEWPORTFITCHANGEDCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnViewportFitChangedCallbackSync);
    case KIND_ONWILLSCROLLCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedOnWillScrollCallbackSync);
    case KIND_PAGEMAPNODEBUILDER:
        return reinterpret_cast<Ark_NativePointer>(CallManagedPageMapNodeBuilderSync);
    case KIND_PASTEBUTTONCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedPasteButtonCallbackSync);
    case KIND_PASTEEVENTCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedPasteEventCallbackSync);
    case KIND_PLUGINERRORCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedPluginErrorCallbackSync);
    case KIND_POPUPSTATECHANGECALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedPopupStateChangeCallbackSync);
    case KIND_PROGRESSMODIFIERBUILDER:
        return reinterpret_cast<Ark_NativePointer>(CallManagedProgressModifierBuilderSync);
    case KIND_RADIOMODIFIERBUILDER:
        return reinterpret_cast<Ark_NativePointer>(CallManagedRadioModifierBuilderSync);
    case KIND_RATINGMODIFIERBUILDER:
        return reinterpret_cast<Ark_NativePointer>(CallManagedRatingModifierBuilderSync);
    case KIND_RESTRICTEDWORKER_ONERROR_CALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedRestrictedWorker_onerror_CallbackSync);
    case KIND_RESTRICTEDWORKER_ONEXIT_CALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedRestrictedWorker_onexit_CallbackSync);
    case KIND_RESTRICTEDWORKER_ONMESSAGE_CALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedRestrictedWorker_onmessage_CallbackSync);
    case KIND_REUSEIDCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedReuseIdCallbackSync);
    case KIND_ROUTERFINISHCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedRouterFinishCallbackSync);
    case KIND_SAVEBUTTONCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedSaveButtonCallbackSync);
    case KIND_SCROLLONSCROLLCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedScrollOnScrollCallbackSync);
    case KIND_SCROLLONWILLSCROLLCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedScrollOnWillScrollCallbackSync);
    case KIND_SEARCHSUBMITCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedSearchSubmitCallbackSync);
    case KIND_SEARCHVALUECALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedSearchValueCallbackSync);
    case KIND_SHOULDBUILTINRECOGNIZERPARALLELWITHCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedShouldBuiltInRecognizerParallelWithCallbackSync);
    case KIND_SIZECHANGECALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedSizeChangeCallbackSync);
    case KIND_SLIDERMODIFIERBUILDER:
        return reinterpret_cast<Ark_NativePointer>(CallManagedSliderModifierBuilderSync);
    case KIND_SLIDERTRIGGERCHANGECALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedSliderTriggerChangeCallbackSync);
    case KIND_STYLEDSTRINGMARSHALLCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedStyledStringMarshallCallbackSync);
    case KIND_STYLEDSTRINGUNMARSHALLCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedStyledStringUnmarshallCallbackSync);
    case KIND_SUBMITCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedSubmitCallbackSync);
    case KIND_SYNTHETIC_ASYNCCALLBACK_IMAGE_PIXELMAP_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedsynthetic_AsyncCallback_image_PixelMap_VoidSync);
    case KIND_SYNTHETIC_CALLBACK_ARRAY_STRING_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedsynthetic_Callback_Array_String_VoidSync);
    case KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedsynthetic_Callback_Boolean_VoidSync);
    case KIND_SYNTHETIC_CALLBACK_DISMISSDIALOGACTION_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedsynthetic_Callback_DismissDialogAction_VoidSync);
    case KIND_SYNTHETIC_CALLBACK_F64_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedsynthetic_Callback_F64_VoidSync);
    case KIND_SYNTHETIC_CALLBACK_KEYEVENT_BOOLEAN:
        return reinterpret_cast<Ark_NativePointer>(CallManagedsynthetic_Callback_KeyEvent_BooleanSync);
    case KIND_SYNTHETIC_CALLBACK_STRING_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedsynthetic_Callback_String_VoidSync);
    case KIND_SYNTHETIC_CALLBACK_TEXTPICKERRESULT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedsynthetic_Callback_TextPickerResult_VoidSync);
    case KIND_SYNTHETIC_CALLBACK_TIMEPICKERRESULT_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedsynthetic_Callback_TimePickerResult_VoidSync);
    case KIND_SYNTHETIC_CALLBACK_VOID:
        return reinterpret_cast<Ark_NativePointer>(CallManagedsynthetic_Callback_VoidSync);
    case KIND_TABSCUSTOMCONTENTTRANSITIONCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedTabsCustomContentTransitionCallbackSync);
    case KIND_TEXTAREASUBMITCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedTextAreaSubmitCallbackSync);
    case KIND_TEXTCLOCKMODIFIERBUILDER:
        return reinterpret_cast<Ark_NativePointer>(CallManagedTextClockModifierBuilderSync);
    case KIND_TEXTFIELDVALUECALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedTextFieldValueCallbackSync);
    case KIND_TEXTPICKERENTERSELECTEDAREACALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedTextPickerEnterSelectedAreaCallbackSync);
    case KIND_TEXTPICKERSCROLLSTOPCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedTextPickerScrollStopCallbackSync);
    case KIND_TEXTTIMERMODIFIERBUILDER:
        return reinterpret_cast<Ark_NativePointer>(CallManagedTextTimerModifierBuilderSync);
    case KIND_TIMERCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedTimerCallbackSync);
    case KIND_TOGGLEMODIFIERBUILDER:
        return reinterpret_cast<Ark_NativePointer>(CallManagedToggleModifierBuilderSync);
    case KIND_TOUCHTESTDONECALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedTouchTestDoneCallbackSync);
    case KIND_TRANSITIONFINISHCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedTransitionFinishCallbackSync);
    case KIND_TYPE_COMMONMETHOD_ONDRAGSTART:
        return reinterpret_cast<Ark_NativePointer>(CallManagedType_CommonMethod_onDragStartSync);
    case KIND_TYPE_NAVIGATIONATTRIBUTE_CUSTOMNAVCONTENTTRANSITION:
        return reinterpret_cast<Ark_NativePointer>(CallManagedType_NavigationAttribute_customNavContentTransitionSync);
    case KIND_UPDATETRANSITIONCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedUpdateTransitionCallbackSync);
    case KIND_VISIBLEAREACHANGECALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedVisibleAreaChangeCallbackSync);
    case KIND_VOIDCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedVoidCallbackSync);
    case KIND_WEBKEYBOARDCALLBACK:
        return reinterpret_cast<Ark_NativePointer>(CallManagedWebKeyboardCallbackSync);
    case KIND_WORKEREVENTLISTENER:
        return reinterpret_cast<Ark_NativePointer>(CallManagedWorkerEventListenerSync);
    }
    return nullptr;
}