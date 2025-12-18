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
#define API_KIND 10
#define KOALA_INTEROP_MODULE NotSpecifiedInteropModule
#include "callback_kind.h"
#include "Serializers.h"
#include "callbacks.h"
#include "common-interop.h"
#include "arkoala_api_generated.h"
void deserializeAndCallAccessibilityActionInterceptCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, Ark_AccessibilityAction action,
                                                const Callback_AccessibilityActionInterceptResult_Void continuation)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_ACCESSIBILITYACTIONINTERCEPTCALLBACK))));
    thisDeserializer.readPointer();
    Ark_AccessibilityAction action = static_cast<Ark_AccessibilityAction>(thisDeserializer.readInt32());
    Callback_AccessibilityActionInterceptResult_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, Ark_AccessibilityActionInterceptResult value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCaller(KIND_CALLBACK_ACCESSIBILITYACTIONINTERCEPTRESULT_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                  Ark_AccessibilityActionInterceptResult value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_CALLBACK_ACCESSIBILITYACTIONINTERCEPTRESULT_VOID))))};
    call(resourceId, action, continuationResult);
}
void deserializeAndCallSyncAccessibilityActionInterceptCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                                Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_AccessibilityAction action,
                                  const Callback_AccessibilityActionInterceptResult_Void continuation)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_ACCESSIBILITYACTIONINTERCEPTCALLBACK))));
    Ark_AccessibilityAction action = static_cast<Ark_AccessibilityAction>(thisDeserializer.readInt32());
    Callback_AccessibilityActionInterceptResult_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, Ark_AccessibilityActionInterceptResult value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCaller(KIND_CALLBACK_ACCESSIBILITYACTIONINTERCEPTRESULT_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                  Ark_AccessibilityActionInterceptResult value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_CALLBACK_ACCESSIBILITYACTIONINTERCEPTRESULT_VOID))))};
    callSyncMethod(vmContext, resourceId, action, continuationResult);
}
void deserializeAndCallAccessibilityCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Boolean isHover,
                                                const Ark_AccessibilityHoverEvent event)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_ACCESSIBILITYCALLBACK))));
    thisDeserializer.readPointer();
    Ark_Boolean isHover = thisDeserializer.readBoolean();
    Ark_AccessibilityHoverEvent event = static_cast<Ark_AccessibilityHoverEvent>(
        AccessibilityHoverEvent_serializer::read(thisDeserializer));
    call(resourceId, isHover, event);
}
void deserializeAndCallSyncAccessibilityCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                 Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isHover,
                                  const Ark_AccessibilityHoverEvent event)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_ACCESSIBILITYCALLBACK))));
    Ark_Boolean isHover = thisDeserializer.readBoolean();
    Ark_AccessibilityHoverEvent event = static_cast<Ark_AccessibilityHoverEvent>(
        AccessibilityHoverEvent_serializer::read(thisDeserializer));
    callSyncMethod(vmContext, resourceId, isHover, event);
}
void deserializeAndCallAccessibilityFocusCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Boolean isFocus)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_ACCESSIBILITYFOCUSCALLBACK))));
    thisDeserializer.readPointer();
    Ark_Boolean isFocus = thisDeserializer.readBoolean();
    call(resourceId, isFocus);
}
void deserializeAndCallSyncAccessibilityFocusCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                      Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isFocus)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_ACCESSIBILITYFOCUSCALLBACK))));
    Ark_Boolean isFocus = thisDeserializer.readBoolean();
    callSyncMethod(vmContext, resourceId, isFocus);
}
void deserializeAndCallAccessibilityTransparentCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_TouchEvent event)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_ACCESSIBILITYTRANSPARENTCALLBACK))));
    thisDeserializer.readPointer();
    Ark_TouchEvent event = static_cast<Ark_TouchEvent>(TouchEvent_serializer::read(thisDeserializer));
    call(resourceId, event);
}
void deserializeAndCallSyncAccessibilityTransparentCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                            Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_TouchEvent event)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_ACCESSIBILITYTRANSPARENTCALLBACK))));
    Ark_TouchEvent event = static_cast<Ark_TouchEvent>(TouchEvent_serializer::read(thisDeserializer));
    callSyncMethod(vmContext, resourceId, event);
}
void deserializeAndCallButtonModifierBuilder(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_NativePointer parentNode,
                                  const Ark_ButtonConfiguration config, const Callback_Pointer_Void continuation)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_BUTTONMODIFIERBUILDER))));
    thisDeserializer.readPointer();
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_ButtonConfiguration config = ButtonConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_POINTER_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_POINTER_VOID))))};
    call(resourceId, parentNode, config, continuationResult);
}
void deserializeAndCallSyncButtonModifierBuilder(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                 Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<
        void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer parentNode,
                 const Ark_ButtonConfiguration config, const Callback_Pointer_Void continuation)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_BUTTONMODIFIERBUILDER))));
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_ButtonConfiguration config = ButtonConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_POINTER_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_POINTER_VOID))))};
    callSyncMethod(vmContext, resourceId, parentNode, config, continuationResult);
}
void deserializeAndCallButtonTriggerClickCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Float64 xPos, const Ark_Float64 yPos)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_BUTTONTRIGGERCLICKCALLBACK))));
    thisDeserializer.readPointer();
    Ark_Float64 xPos = thisDeserializer.readFloat64();
    Ark_Float64 yPos = thisDeserializer.readFloat64();
    call(resourceId, xPos, yPos);
}
void deserializeAndCallSyncButtonTriggerClickCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                      Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_Float64 xPos, const Ark_Float64 yPos)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_BUTTONTRIGGERCLICKCALLBACK))));
    Ark_Float64 xPos = thisDeserializer.readFloat64();
    Ark_Float64 yPos = thisDeserializer.readFloat64();
    callSyncMethod(vmContext, resourceId, xPos, yPos);
}
void deserializeAndCallCallback_AccessibilityActionInterceptResult_Void(KSerializerBuffer thisArray,
                                                                        Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, Ark_AccessibilityActionInterceptResult value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCaller(KIND_CALLBACK_ACCESSIBILITYACTIONINTERCEPTRESULT_VOID))));
    thisDeserializer.readPointer();
    Ark_AccessibilityActionInterceptResult value = static_cast<Ark_AccessibilityActionInterceptResult>(
        thisDeserializer.readInt32());
    call(resourceId, value);
}
void deserializeAndCallSyncCallback_AccessibilityActionInterceptResult_Void(Ark_VMContext vmContext,
                                                                            KSerializerBuffer thisArray,
                                                                            Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          Ark_AccessibilityActionInterceptResult value)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCallerSync(KIND_CALLBACK_ACCESSIBILITYACTIONINTERCEPTRESULT_VOID))));
    Ark_AccessibilityActionInterceptResult value = static_cast<Ark_AccessibilityActionInterceptResult>(
        thisDeserializer.readInt32());
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallCallback_Area_Area_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Area oldValue, const Ark_Area newValue)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_AREA_AREA_VOID))));
    thisDeserializer.readPointer();
    Ark_Area oldValue = Area_serializer::read(thisDeserializer);
    Ark_Area newValue = Area_serializer::read(thisDeserializer);
    call(resourceId, oldValue, newValue);
}
void deserializeAndCallSyncCallback_Area_Area_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                   Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_Area oldValue, const Ark_Area newValue)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_AREA_AREA_VOID))));
    Ark_Area oldValue = Area_serializer::read(thisDeserializer);
    Ark_Area newValue = Area_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, oldValue, newValue);
}
void deserializeAndCallCallback_Array_I32_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Array_I32 data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_ARRAY_I32_VOID))));
    thisDeserializer.readPointer();
    const Ark_Int32 dataTmpBufLength = thisDeserializer.readInt32();
    Array_I32 dataTmpBuf = {};
    thisDeserializer.resizeArray<std::decay<decltype(dataTmpBuf)>::type, std::decay<decltype(*dataTmpBuf.array)>::type>(
        &dataTmpBuf, dataTmpBufLength);
    for (int dataTmpBufBufCounterI = 0; dataTmpBufBufCounterI < dataTmpBufLength; dataTmpBufBufCounterI++)
    {
        dataTmpBuf.array[dataTmpBufBufCounterI] = thisDeserializer.readInt32();
    }
    Array_I32 data = dataTmpBuf;
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_Array_I32_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                   Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Array_I32 data)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_ARRAY_I32_VOID))));
    const Ark_Int32 dataTmpBufLength = thisDeserializer.readInt32();
    Array_I32 dataTmpBuf = {};
    thisDeserializer.resizeArray<std::decay<decltype(dataTmpBuf)>::type, std::decay<decltype(*dataTmpBuf.array)>::type>(
        &dataTmpBuf, dataTmpBufLength);
    for (int dataTmpBufBufCounterI = 0; dataTmpBufBufCounterI < dataTmpBufLength; dataTmpBufBufCounterI++)
    {
        dataTmpBuf.array[dataTmpBufBufCounterI] = thisDeserializer.readInt32();
    }
    Array_I32 data = dataTmpBuf;
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_Array_Resource_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Array_Resource data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_ARRAY_RESOURCE_VOID))));
    thisDeserializer.readPointer();
    const Ark_Int32 dataTmpBufLength = thisDeserializer.readInt32();
    Array_Resource dataTmpBuf = {};
    thisDeserializer.resizeArray<std::decay<decltype(dataTmpBuf)>::type, std::decay<decltype(*dataTmpBuf.array)>::type>(
        &dataTmpBuf, dataTmpBufLength);
    for (int dataTmpBufBufCounterI = 0; dataTmpBufBufCounterI < dataTmpBufLength; dataTmpBufBufCounterI++)
    {
        dataTmpBuf.array[dataTmpBufBufCounterI] = Resource_serializer::read(thisDeserializer);
    }
    Array_Resource data = dataTmpBuf;
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_Array_Resource_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                        Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Array_Resource data)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_ARRAY_RESOURCE_VOID))));
    const Ark_Int32 dataTmpBufLength = thisDeserializer.readInt32();
    Array_Resource dataTmpBuf = {};
    thisDeserializer.resizeArray<std::decay<decltype(dataTmpBuf)>::type, std::decay<decltype(*dataTmpBuf.array)>::type>(
        &dataTmpBuf, dataTmpBufLength);
    for (int dataTmpBufBufCounterI = 0; dataTmpBufBufCounterI < dataTmpBufLength; dataTmpBufBufCounterI++)
    {
        dataTmpBuf.array[dataTmpBufBufCounterI] = Resource_serializer::read(thisDeserializer);
    }
    Array_Resource data = dataTmpBuf;
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_Array_ResourceStr_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Array_ResourceStr data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_ARRAY_RESOURCESTR_VOID))));
    thisDeserializer.readPointer();
    const Ark_Int32 dataTmpBufLength = thisDeserializer.readInt32();
    Array_ResourceStr dataTmpBuf = {};
    thisDeserializer.resizeArray<std::decay<decltype(dataTmpBuf)>::type, std::decay<decltype(*dataTmpBuf.array)>::type>(
        &dataTmpBuf, dataTmpBufLength);
    for (int dataTmpBufBufCounterI = 0; dataTmpBufBufCounterI < dataTmpBufLength; dataTmpBufBufCounterI++)
    {
        const Ark_Int8 dataTmpBufTempBufUnionSelector = thisDeserializer.readInt8();
        Ark_ResourceStr dataTmpBufTempBuf = {};
        dataTmpBufTempBuf.selector = dataTmpBufTempBufUnionSelector;
        if (dataTmpBufTempBufUnionSelector == 0)
        {
            dataTmpBufTempBuf.selector = 0;
            dataTmpBufTempBuf.value0 = static_cast<Ark_String>(thisDeserializer.readString());
        }
        else if (dataTmpBufTempBufUnionSelector == 1)
        {
            dataTmpBufTempBuf.selector = 1;
            dataTmpBufTempBuf.value1 = Resource_serializer::read(thisDeserializer);
        }
        else
        {
            INTEROP_FATAL("One of the branches for dataTmpBufTempBuf has to be chosen through deserialisation.");
        }
        dataTmpBuf.array[dataTmpBufBufCounterI] = static_cast<Ark_ResourceStr>(dataTmpBufTempBuf);
    }
    Array_ResourceStr data = dataTmpBuf;
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_Array_ResourceStr_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                           Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Array_ResourceStr data)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_CALLBACK_ARRAY_RESOURCESTR_VOID))));
    const Ark_Int32 dataTmpBufLength = thisDeserializer.readInt32();
    Array_ResourceStr dataTmpBuf = {};
    thisDeserializer.resizeArray<std::decay<decltype(dataTmpBuf)>::type, std::decay<decltype(*dataTmpBuf.array)>::type>(
        &dataTmpBuf, dataTmpBufLength);
    for (int dataTmpBufBufCounterI = 0; dataTmpBufBufCounterI < dataTmpBufLength; dataTmpBufBufCounterI++)
    {
        const Ark_Int8 dataTmpBufTempBufUnionSelector = thisDeserializer.readInt8();
        Ark_ResourceStr dataTmpBufTempBuf = {};
        dataTmpBufTempBuf.selector = dataTmpBufTempBufUnionSelector;
        if (dataTmpBufTempBufUnionSelector == 0)
        {
            dataTmpBufTempBuf.selector = 0;
            dataTmpBufTempBuf.value0 = static_cast<Ark_String>(thisDeserializer.readString());
        }
        else if (dataTmpBufTempBufUnionSelector == 1)
        {
            dataTmpBufTempBuf.selector = 1;
            dataTmpBufTempBuf.value1 = Resource_serializer::read(thisDeserializer);
        }
        else
        {
            INTEROP_FATAL("One of the branches for dataTmpBufTempBuf has to be chosen through deserialisation.");
        }
        dataTmpBuf.array[dataTmpBufBufCounterI] = static_cast<Ark_ResourceStr>(dataTmpBufTempBuf);
    }
    Array_ResourceStr data = dataTmpBuf;
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_Array_String_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Array_String data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_ARRAY_STRING_VOID))));
    thisDeserializer.readPointer();
    const Ark_Int32 dataTmpBufLength = thisDeserializer.readInt32();
    Array_String dataTmpBuf = {};
    thisDeserializer.resizeArray<std::decay<decltype(dataTmpBuf)>::type, std::decay<decltype(*dataTmpBuf.array)>::type>(
        &dataTmpBuf, dataTmpBufLength);
    for (int dataTmpBufBufCounterI = 0; dataTmpBufBufCounterI < dataTmpBufLength; dataTmpBufBufCounterI++)
    {
        dataTmpBuf.array[dataTmpBufBufCounterI] = static_cast<Ark_String>(thisDeserializer.readString());
    }
    Array_String data = dataTmpBuf;
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_Array_String_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                      Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Array_String data)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_ARRAY_STRING_VOID))));
    const Ark_Int32 dataTmpBufLength = thisDeserializer.readInt32();
    Array_String dataTmpBuf = {};
    thisDeserializer.resizeArray<std::decay<decltype(dataTmpBuf)>::type, std::decay<decltype(*dataTmpBuf.array)>::type>(
        &dataTmpBuf, dataTmpBufLength);
    for (int dataTmpBufBufCounterI = 0; dataTmpBufBufCounterI < dataTmpBufLength; dataTmpBufBufCounterI++)
    {
        dataTmpBuf.array[dataTmpBufBufCounterI] = static_cast<Ark_String>(thisDeserializer.readString());
    }
    Array_String data = dataTmpBuf;
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_Array_TextMenuItem_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Array_TextMenuItem value)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_ARRAY_TEXTMENUITEM_VOID))));
    thisDeserializer.readPointer();
    const Ark_Int32 valueTmpBufLength = thisDeserializer.readInt32();
    Array_TextMenuItem valueTmpBuf = {};
    thisDeserializer.resizeArray<std::decay<decltype(valueTmpBuf)>::type,
                                 std::decay<decltype(*valueTmpBuf.array)>::type>(&valueTmpBuf, valueTmpBufLength);
    for (int valueTmpBufBufCounterI = 0; valueTmpBufBufCounterI < valueTmpBufLength; valueTmpBufBufCounterI++)
    {
        valueTmpBuf.array[valueTmpBufBufCounterI] = TextMenuItem_serializer::read(thisDeserializer);
    }
    Array_TextMenuItem value = valueTmpBuf;
    call(resourceId, value);
}
void deserializeAndCallSyncCallback_Array_TextMenuItem_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                            Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Array_TextMenuItem value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_CALLBACK_ARRAY_TEXTMENUITEM_VOID))));
    const Ark_Int32 valueTmpBufLength = thisDeserializer.readInt32();
    Array_TextMenuItem valueTmpBuf = {};
    thisDeserializer.resizeArray<std::decay<decltype(valueTmpBuf)>::type,
                                 std::decay<decltype(*valueTmpBuf.array)>::type>(&valueTmpBuf, valueTmpBufLength);
    for (int valueTmpBufBufCounterI = 0; valueTmpBufBufCounterI < valueTmpBufLength; valueTmpBufBufCounterI++)
    {
        valueTmpBuf.array[valueTmpBufBufCounterI] = TextMenuItem_serializer::read(thisDeserializer);
    }
    Array_TextMenuItem value = valueTmpBuf;
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallCallback_Array_TouchTestInfo_TouchResult(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Array_TouchTestInfo value,
                                                const Callback_TouchResult_Void continuation)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCaller(KIND_CALLBACK_ARRAY_TOUCHTESTINFO_TOUCHRESULT))));
    thisDeserializer.readPointer();
    const Ark_Int32 valueTmpBufLength = thisDeserializer.readInt32();
    Array_TouchTestInfo valueTmpBuf = {};
    thisDeserializer.resizeArray<std::decay<decltype(valueTmpBuf)>::type,
                                 std::decay<decltype(*valueTmpBuf.array)>::type>(&valueTmpBuf, valueTmpBufLength);
    for (int valueTmpBufBufCounterI = 0; valueTmpBufBufCounterI < valueTmpBufLength; valueTmpBufBufCounterI++)
    {
        valueTmpBuf.array[valueTmpBufBufCounterI] = TouchTestInfo_serializer::read(thisDeserializer);
    }
    Array_TouchTestInfo value = valueTmpBuf;
    Callback_TouchResult_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_TouchResult value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_TOUCHRESULT_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_TouchResult value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_TOUCHRESULT_VOID))))};
    call(resourceId, value, continuationResult);
}
void deserializeAndCallSyncCallback_Array_TouchTestInfo_TouchResult(Ark_VMContext vmContext,
                                                                    KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Array_TouchTestInfo value,
                                  const Callback_TouchResult_Void continuation)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_CALLBACK_ARRAY_TOUCHTESTINFO_TOUCHRESULT))));
    const Ark_Int32 valueTmpBufLength = thisDeserializer.readInt32();
    Array_TouchTestInfo valueTmpBuf = {};
    thisDeserializer.resizeArray<std::decay<decltype(valueTmpBuf)>::type,
                                 std::decay<decltype(*valueTmpBuf.array)>::type>(&valueTmpBuf, valueTmpBufLength);
    for (int valueTmpBufBufCounterI = 0; valueTmpBufBufCounterI < valueTmpBufLength; valueTmpBufBufCounterI++)
    {
        valueTmpBuf.array[valueTmpBufBufCounterI] = TouchTestInfo_serializer::read(thisDeserializer);
    }
    Array_TouchTestInfo value = valueTmpBuf;
    Callback_TouchResult_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_TouchResult value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_TOUCHRESULT_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_TouchResult value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_TOUCHRESULT_VOID))))};
    callSyncMethod(vmContext, resourceId, value, continuationResult);
}
void deserializeAndCallCallback_AxisEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_AxisEvent data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_AXISEVENT_VOID))));
    thisDeserializer.readPointer();
    Ark_AxisEvent data = static_cast<Ark_AxisEvent>(AxisEvent_serializer::read(thisDeserializer));
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_AxisEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                   Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_AxisEvent data)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_AXISEVENT_VOID))));
    Ark_AxisEvent data = static_cast<Ark_AxisEvent>(AxisEvent_serializer::read(thisDeserializer));
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const synthetic_Callback_Boolean_Void continuation)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_BOOLEAN))));
    thisDeserializer.readPointer();
    synthetic_Callback_Boolean_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID))))};
    call(resourceId, continuationResult);
}
void deserializeAndCallSyncCallback_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const synthetic_Callback_Boolean_Void continuation)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_BOOLEAN))));
    synthetic_Callback_Boolean_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID))))};
    callSyncMethod(vmContext, resourceId, continuationResult);
}
void deserializeAndCallCallback_Boolean_HoverEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Boolean isHover, const Ark_HoverEvent event)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_BOOLEAN_HOVEREVENT_VOID))));
    thisDeserializer.readPointer();
    Ark_Boolean isHover = thisDeserializer.readBoolean();
    Ark_HoverEvent event = static_cast<Ark_HoverEvent>(HoverEvent_serializer::read(thisDeserializer));
    call(resourceId, isHover, event);
}
void deserializeAndCallSyncCallback_Boolean_HoverEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                            Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_Boolean isHover, const Ark_HoverEvent event)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_BOOLEAN_HOVEREVENT_VOID))));
    Ark_Boolean isHover = thisDeserializer.readBoolean();
    Ark_HoverEvent event = static_cast<Ark_HoverEvent>(HoverEvent_serializer::read(thisDeserializer));
    callSyncMethod(vmContext, resourceId, isHover, event);
}
void deserializeAndCallCallback_Boolean_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Boolean data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_BOOLEAN_VOID))));
    thisDeserializer.readPointer();
    Ark_Boolean data = thisDeserializer.readBoolean();
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_Boolean_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                 Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean data)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_BOOLEAN_VOID))));
    Ark_Boolean data = thisDeserializer.readBoolean();
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_Buffer_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Buffer value)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_BUFFER_VOID))));
    thisDeserializer.readPointer();
    Ark_Buffer value = static_cast<Ark_Buffer>(thisDeserializer.readBuffer());
    call(resourceId, value);
}
void deserializeAndCallSyncCallback_Buffer_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Buffer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_BUFFER_VOID))));
    Ark_Buffer value = static_cast<Ark_Buffer>(thisDeserializer.readBuffer());
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallCallback_BusinessError_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Int32 code, const Ark_String message)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_BUSINESSERROR_VOID))));
    thisDeserializer.readPointer();
    Ark_Int32 code = thisDeserializer.readInt32();
    Ark_String message = static_cast<Ark_String>(thisDeserializer.readString());
    call(resourceId, code, message);
}
void deserializeAndCallSyncCallback_BusinessError_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                       Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_Int32 code, const Ark_String message)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_BUSINESSERROR_VOID))));
    Ark_Int32 code = thisDeserializer.readInt32();
    Ark_String message = static_cast<Ark_String>(thisDeserializer.readString());
    callSyncMethod(vmContext, resourceId, code, message);
}
void deserializeAndCallCallback_ClickEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_ClickEvent event)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_CLICKEVENT_VOID))));
    thisDeserializer.readPointer();
    Ark_ClickEvent event = static_cast<Ark_ClickEvent>(ClickEvent_serializer::read(thisDeserializer));
    call(resourceId, event);
}
void deserializeAndCallSyncCallback_ClickEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                    Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_ClickEvent event)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_CLICKEVENT_VOID))));
    Ark_ClickEvent event = static_cast<Ark_ClickEvent>(ClickEvent_serializer::read(thisDeserializer));
    callSyncMethod(vmContext, resourceId, event);
}
void deserializeAndCallCallback_ComputedBarAttribute_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_ComputedBarAttribute value)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_COMPUTEDBARATTRIBUTE_VOID))));
    thisDeserializer.readPointer();
    Ark_ComputedBarAttribute value = ComputedBarAttribute_serializer::read(thisDeserializer);
    call(resourceId, value);
}
void deserializeAndCallSyncCallback_ComputedBarAttribute_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                              Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_ComputedBarAttribute value)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCallerSync(KIND_CALLBACK_COMPUTEDBARATTRIBUTE_VOID))));
    Ark_ComputedBarAttribute value = ComputedBarAttribute_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallCallback_CopyEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_CopyEvent data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_COPYEVENT_VOID))));
    thisDeserializer.readPointer();
    Ark_CopyEvent data = static_cast<Ark_CopyEvent>(CopyEvent_serializer::read(thisDeserializer));
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_CopyEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                   Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_CopyEvent data)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_COPYEVENT_VOID))));
    Ark_CopyEvent data = static_cast<Ark_CopyEvent>(CopyEvent_serializer::read(thisDeserializer));
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_CreateItem(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Int32 index,
                                                const Callback_Pointer_Void continuation)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_CREATEITEM))));
    thisDeserializer.readPointer();
    Ark_Int32 index = thisDeserializer.readInt32();
    Callback_Pointer_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_POINTER_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_POINTER_VOID))))};
    call(resourceId, index, continuationResult);
}
void deserializeAndCallSyncCallback_CreateItem(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                               Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int32 index,
                                  const Callback_Pointer_Void continuation)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_CREATEITEM))));
    Ark_Int32 index = thisDeserializer.readInt32();
    Callback_Pointer_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_POINTER_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_POINTER_VOID))))};
    callSyncMethod(vmContext, resourceId, index, continuationResult);
}
void deserializeAndCallCallback_CrownEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_CrownEvent data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_CROWNEVENT_VOID))));
    thisDeserializer.readPointer();
    Ark_CrownEvent data = static_cast<Ark_CrownEvent>(CrownEvent_serializer::read(thisDeserializer));
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_CrownEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                    Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_CrownEvent data)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_CROWNEVENT_VOID))));
    Ark_CrownEvent data = static_cast<Ark_CrownEvent>(CrownEvent_serializer::read(thisDeserializer));
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_CustomSpanMeasureInfo_CustomSpanMetrics(KSerializerBuffer thisArray,
                                                                        Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_CustomSpanMeasureInfo measureInfo,
                                                const Callback_CustomSpanMetrics_Void continuation)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCaller(KIND_CALLBACK_CUSTOMSPANMEASUREINFO_CUSTOMSPANMETRICS))));
    thisDeserializer.readPointer();
    Ark_CustomSpanMeasureInfo measureInfo = CustomSpanMeasureInfo_serializer::read(thisDeserializer);
    Callback_CustomSpanMetrics_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_CustomSpanMetrics value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_CUSTOMSPANMETRICS_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                  const Ark_CustomSpanMetrics value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_CALLBACK_CUSTOMSPANMETRICS_VOID))))};
    call(resourceId, measureInfo, continuationResult);
}
void deserializeAndCallSyncCallback_CustomSpanMeasureInfo_CustomSpanMetrics(Ark_VMContext vmContext,
                                                                            KSerializerBuffer thisArray,
                                                                            Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_CustomSpanMeasureInfo measureInfo,
                                                          const Callback_CustomSpanMetrics_Void continuation)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCallerSync(KIND_CALLBACK_CUSTOMSPANMEASUREINFO_CUSTOMSPANMETRICS))));
    Ark_CustomSpanMeasureInfo measureInfo = CustomSpanMeasureInfo_serializer::read(thisDeserializer);
    Callback_CustomSpanMetrics_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_CustomSpanMetrics value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_CUSTOMSPANMETRICS_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                  const Ark_CustomSpanMetrics value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_CALLBACK_CUSTOMSPANMETRICS_VOID))))};
    callSyncMethod(vmContext, resourceId, measureInfo, continuationResult);
}
void deserializeAndCallCallback_CustomSpanMetrics_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_CustomSpanMetrics value)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_CUSTOMSPANMETRICS_VOID))));
    thisDeserializer.readPointer();
    Ark_CustomSpanMetrics value = CustomSpanMetrics_serializer::read(thisDeserializer);
    call(resourceId, value);
}
void deserializeAndCallSyncCallback_CustomSpanMetrics_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                           Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_CustomSpanMetrics value)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_CUSTOMSPANMETRICS_VOID))));
    Ark_CustomSpanMetrics value = CustomSpanMetrics_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallCallback_CutEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_CutEvent data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_CUTEVENT_VOID))));
    thisDeserializer.readPointer();
    Ark_CutEvent data = static_cast<Ark_CutEvent>(CutEvent_serializer::read(thisDeserializer));
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_CutEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                  Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_CutEvent data)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_CUTEVENT_VOID))));
    Ark_CutEvent data = static_cast<Ark_CutEvent>(CutEvent_serializer::read(thisDeserializer));
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_Date_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Date data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_DATE_VOID))));
    thisDeserializer.readPointer();
    Ark_Date data = thisDeserializer.readInt64();
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_Date_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                              Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Date data)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_DATE_VOID))));
    Ark_Date data = thisDeserializer.readInt64();
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_DeleteValue_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_DeleteValue data,
                                                const synthetic_Callback_Boolean_Void continuation)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_DELETEVALUE_BOOLEAN))));
    thisDeserializer.readPointer();
    Ark_DeleteValue data = DeleteValue_serializer::read(thisDeserializer);
    synthetic_Callback_Boolean_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID))))};
    call(resourceId, data, continuationResult);
}
void deserializeAndCallSyncCallback_DeleteValue_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                        Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_DeleteValue data,
                                  const synthetic_Callback_Boolean_Void continuation)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_DELETEVALUE_BOOLEAN))));
    Ark_DeleteValue data = DeleteValue_serializer::read(thisDeserializer);
    synthetic_Callback_Boolean_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID))))};
    callSyncMethod(vmContext, resourceId, data, continuationResult);
}
void deserializeAndCallCallback_DeleteValue_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_DeleteValue data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_DELETEVALUE_VOID))));
    thisDeserializer.readPointer();
    Ark_DeleteValue data = DeleteValue_serializer::read(thisDeserializer);
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_DeleteValue_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                     Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_DeleteValue data)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_DELETEVALUE_VOID))));
    Ark_DeleteValue data = DeleteValue_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_DismissContentCoverAction_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_DismissContentCoverAction data)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCaller(KIND_CALLBACK_DISMISSCONTENTCOVERACTION_VOID))));
    thisDeserializer.readPointer();
    Ark_DismissContentCoverAction data = DismissContentCoverAction_serializer::read(thisDeserializer);
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_DismissContentCoverAction_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                                   Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_DismissContentCoverAction data)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCallerSync(KIND_CALLBACK_DISMISSCONTENTCOVERACTION_VOID))));
    Ark_DismissContentCoverAction data = DismissContentCoverAction_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_DismissDialogAction_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_DismissDialogAction data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_DISMISSDIALOGACTION_VOID))));
    thisDeserializer.readPointer();
    Ark_DismissDialogAction data = static_cast<Ark_DismissDialogAction>(
        DismissDialogAction_serializer::read(thisDeserializer));
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_DismissDialogAction_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                             Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_DismissDialogAction data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_DISMISSDIALOGACTION_VOID))));
    Ark_DismissDialogAction data = static_cast<Ark_DismissDialogAction>(
        DismissDialogAction_serializer::read(thisDeserializer));
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_DismissPopupAction_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_DismissPopupAction data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_DISMISSPOPUPACTION_VOID))));
    thisDeserializer.readPointer();
    Ark_DismissPopupAction data = static_cast<Ark_DismissPopupAction>(
        DismissPopupAction_serializer::read(thisDeserializer));
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_DismissPopupAction_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                            Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_DismissPopupAction data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_DISMISSPOPUPACTION_VOID))));
    Ark_DismissPopupAction data = static_cast<Ark_DismissPopupAction>(
        DismissPopupAction_serializer::read(thisDeserializer));
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_DismissSheetAction_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_DismissSheetAction data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_DISMISSSHEETACTION_VOID))));
    thisDeserializer.readPointer();
    Ark_DismissSheetAction data = DismissSheetAction_serializer::read(thisDeserializer);
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_DismissSheetAction_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                            Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_DismissSheetAction data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_DISMISSSHEETACTION_VOID))));
    Ark_DismissSheetAction data = DismissSheetAction_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_DragEvent_Opt_String_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_DragEvent event, const Opt_String extraParams)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCaller(KIND_CALLBACK_DRAGEVENT_OPT_STRING_VOID))));
    thisDeserializer.readPointer();
    Ark_DragEvent event = static_cast<Ark_DragEvent>(DragEvent_serializer::read(thisDeserializer));
    const auto extraParamsTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_String extraParamsTmpBuf = {};
    extraParamsTmpBuf.tag = extraParamsTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED :
                                                                                         INTEROP_TAG_OBJECT;
    if ((extraParamsTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        extraParamsTmpBuf.value = static_cast<Ark_String>(thisDeserializer.readString());
    }
    Opt_String extraParams = extraParamsTmpBuf;
    call(resourceId, event, extraParams);
}
void deserializeAndCallSyncCallback_DragEvent_Opt_String_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                              Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_DragEvent event, const Opt_String extraParams)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCallerSync(KIND_CALLBACK_DRAGEVENT_OPT_STRING_VOID))));
    Ark_DragEvent event = static_cast<Ark_DragEvent>(DragEvent_serializer::read(thisDeserializer));
    const auto extraParamsTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_String extraParamsTmpBuf = {};
    extraParamsTmpBuf.tag = extraParamsTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED :
                                                                                         INTEROP_TAG_OBJECT;
    if ((extraParamsTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        extraParamsTmpBuf.value = static_cast<Ark_String>(thisDeserializer.readString());
    }
    Opt_String extraParams = extraParamsTmpBuf;
    callSyncMethod(vmContext, resourceId, event, extraParams);
}
void deserializeAndCallCallback_DrawContext_CustomSpanDrawInfo_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_DrawContext context,
                                                const Ark_CustomSpanDrawInfo drawInfo)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCaller(KIND_CALLBACK_DRAWCONTEXT_CUSTOMSPANDRAWINFO_VOID))));
    thisDeserializer.readPointer();
    Ark_DrawContext context = static_cast<Ark_DrawContext>(DrawContext_serializer::read(thisDeserializer));
    Ark_CustomSpanDrawInfo drawInfo = CustomSpanDrawInfo_serializer::read(thisDeserializer);
    call(resourceId, context, drawInfo);
}
void deserializeAndCallSyncCallback_DrawContext_CustomSpanDrawInfo_Void(Ark_VMContext vmContext,
                                                                        KSerializerBuffer thisArray,
                                                                        Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_DrawContext context,
                                  const Ark_CustomSpanDrawInfo drawInfo)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_CALLBACK_DRAWCONTEXT_CUSTOMSPANDRAWINFO_VOID))));
    Ark_DrawContext context = static_cast<Ark_DrawContext>(DrawContext_serializer::read(thisDeserializer));
    Ark_CustomSpanDrawInfo drawInfo = CustomSpanDrawInfo_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, context, drawInfo);
}
void deserializeAndCallCallback_DrawContext_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_DrawContext drawContext)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_DRAWCONTEXT_VOID))));
    thisDeserializer.readPointer();
    Ark_DrawContext drawContext = static_cast<Ark_DrawContext>(DrawContext_serializer::read(thisDeserializer));
    call(resourceId, drawContext);
}
void deserializeAndCallSyncCallback_DrawContext_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                     Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_DrawContext drawContext)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_DRAWCONTEXT_VOID))));
    Ark_DrawContext drawContext = static_cast<Ark_DrawContext>(DrawContext_serializer::read(thisDeserializer));
    callSyncMethod(vmContext, resourceId, drawContext);
}
void deserializeAndCallCallback_EditableTextChangeValue_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_EditableTextChangeValue data,
                                                const synthetic_Callback_Boolean_Void continuation)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCaller(KIND_CALLBACK_EDITABLETEXTCHANGEVALUE_BOOLEAN))));
    thisDeserializer.readPointer();
    Ark_EditableTextChangeValue data = EditableTextChangeValue_serializer::read(thisDeserializer);
    synthetic_Callback_Boolean_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID))))};
    call(resourceId, data, continuationResult);
}
void deserializeAndCallSyncCallback_EditableTextChangeValue_Boolean(Ark_VMContext vmContext,
                                                                    KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_EditableTextChangeValue data,
                                                          const synthetic_Callback_Boolean_Void continuation)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCallerSync(KIND_CALLBACK_EDITABLETEXTCHANGEVALUE_BOOLEAN))));
    Ark_EditableTextChangeValue data = EditableTextChangeValue_serializer::read(thisDeserializer);
    synthetic_Callback_Boolean_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID))))};
    callSyncMethod(vmContext, resourceId, data, continuationResult);
}
void deserializeAndCallCallback_ErrorInformation_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_ErrorInformation data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_ERRORINFORMATION_VOID))));
    thisDeserializer.readPointer();
    Ark_ErrorInformation data = ErrorInformation_serializer::read(thisDeserializer);
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_ErrorInformation_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                          Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_ErrorInformation data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_ERRORINFORMATION_VOID))));
    Ark_ErrorInformation data = ErrorInformation_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_Extender_OnFinish(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId)>(thisDeserializer.readPointerOrDefault(
        reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_EXTENDER_ONFINISH))));
    thisDeserializer.readPointer();
    call(resourceId);
}
void deserializeAndCallSyncCallback_Extender_OnFinish(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                      Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_EXTENDER_ONFINISH))));
    callSyncMethod(vmContext, resourceId);
}
void deserializeAndCallCallback_Extender_OnProgress(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Float32 value)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_EXTENDER_ONPROGRESS))));
    thisDeserializer.readPointer();
    Ark_Float32 value = thisDeserializer.readFloat32();
    call(resourceId, value);
}
void deserializeAndCallSyncCallback_Extender_OnProgress(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                        Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Float32 value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_EXTENDER_ONPROGRESS))));
    Ark_Float32 value = thisDeserializer.readFloat32();
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallCallback_F64_F64_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Float64 totalOffsetX,
                                                const Ark_Float64 totalOffsetY)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_F64_F64_VOID))));
    thisDeserializer.readPointer();
    Ark_Float64 totalOffsetX = thisDeserializer.readFloat64();
    Ark_Float64 totalOffsetY = thisDeserializer.readFloat64();
    call(resourceId, totalOffsetX, totalOffsetY);
}
void deserializeAndCallSyncCallback_F64_F64_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                 Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Float64 totalOffsetX,
                                  const Ark_Float64 totalOffsetY)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_F64_F64_VOID))));
    Ark_Float64 totalOffsetX = thisDeserializer.readFloat64();
    Ark_Float64 totalOffsetY = thisDeserializer.readFloat64();
    callSyncMethod(vmContext, resourceId, totalOffsetX, totalOffsetY);
}
void deserializeAndCallCallback_F64_SliderChangeMode_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Float64 value, Ark_SliderChangeMode mode)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCaller(KIND_CALLBACK_F64_SLIDERCHANGEMODE_VOID))));
    thisDeserializer.readPointer();
    Ark_Float64 value = thisDeserializer.readFloat64();
    Ark_SliderChangeMode mode = static_cast<Ark_SliderChangeMode>(thisDeserializer.readInt32());
    call(resourceId, value, mode);
}
void deserializeAndCallSyncCallback_F64_SliderChangeMode_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                              Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_Float64 value, Ark_SliderChangeMode mode)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCallerSync(KIND_CALLBACK_F64_SLIDERCHANGEMODE_VOID))));
    Ark_Float64 value = thisDeserializer.readFloat64();
    Ark_SliderChangeMode mode = static_cast<Ark_SliderChangeMode>(thisDeserializer.readInt32());
    callSyncMethod(vmContext, resourceId, value, mode);
}
void deserializeAndCallCallback_F64_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Float64 data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_F64_VOID))));
    thisDeserializer.readPointer();
    Ark_Float64 data = thisDeserializer.readFloat64();
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_F64_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Float64 data)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_F64_VOID))));
    Ark_Float64 data = thisDeserializer.readFloat64();
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_FocusAxisEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_FocusAxisEvent data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_FOCUSAXISEVENT_VOID))));
    thisDeserializer.readPointer();
    Ark_FocusAxisEvent data = static_cast<Ark_FocusAxisEvent>(FocusAxisEvent_serializer::read(thisDeserializer));
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_FocusAxisEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                        Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_FocusAxisEvent data)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_FOCUSAXISEVENT_VOID))));
    Ark_FocusAxisEvent data = static_cast<Ark_FocusAxisEvent>(FocusAxisEvent_serializer::read(thisDeserializer));
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_FormCallbackInfo_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_FormCallbackInfo data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_FORMCALLBACKINFO_VOID))));
    thisDeserializer.readPointer();
    Ark_FormCallbackInfo data = FormCallbackInfo_serializer::read(thisDeserializer);
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_FormCallbackInfo_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                          Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_FormCallbackInfo data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_FORMCALLBACKINFO_VOID))));
    Ark_FormCallbackInfo data = FormCallbackInfo_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_FullscreenInfo_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_FullscreenInfo data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_FULLSCREENINFO_VOID))));
    thisDeserializer.readPointer();
    Ark_FullscreenInfo data = FullscreenInfo_serializer::read(thisDeserializer);
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_FullscreenInfo_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                        Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_FullscreenInfo data)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_FULLSCREENINFO_VOID))));
    Ark_FullscreenInfo data = FullscreenInfo_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_GestureEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_GestureEvent data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_GESTUREEVENT_VOID))));
    thisDeserializer.readPointer();
    Ark_GestureEvent data = static_cast<Ark_GestureEvent>(GestureEvent_serializer::read(thisDeserializer));
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_GestureEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                      Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_GestureEvent data)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_GESTUREEVENT_VOID))));
    Ark_GestureEvent data = static_cast<Ark_GestureEvent>(GestureEvent_serializer::read(thisDeserializer));
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_GestureInfo_BaseGestureEvent_GestureJudgeResult(KSerializerBuffer thisArray,
                                                                                Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_GestureInfo gestureInfo,
                                                const Ark_BaseGestureEvent event,
                                                const Callback_GestureJudgeResult_Void continuation)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCaller(KIND_CALLBACK_GESTUREINFO_BASEGESTUREEVENT_GESTUREJUDGERESULT))));
    thisDeserializer.readPointer();
    Ark_GestureInfo gestureInfo = GestureInfo_serializer::read(thisDeserializer);
    Ark_BaseGestureEvent event = static_cast<Ark_BaseGestureEvent>(BaseGestureEvent_serializer::read(thisDeserializer));
    Callback_GestureJudgeResult_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, Ark_GestureJudgeResult value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_GESTUREJUDGERESULT_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_GestureJudgeResult value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_CALLBACK_GESTUREJUDGERESULT_VOID))))};
    call(resourceId, gestureInfo, event, continuationResult);
}
void deserializeAndCallSyncCallback_GestureInfo_BaseGestureEvent_GestureJudgeResult(Ark_VMContext vmContext,
                                                                                    KSerializerBuffer thisArray,
                                                                                    Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<
        void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_GestureInfo gestureInfo,
                 const Ark_BaseGestureEvent event, const Callback_GestureJudgeResult_Void continuation)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCallerSync(KIND_CALLBACK_GESTUREINFO_BASEGESTUREEVENT_GESTUREJUDGERESULT))));
    Ark_GestureInfo gestureInfo = GestureInfo_serializer::read(thisDeserializer);
    Ark_BaseGestureEvent event = static_cast<Ark_BaseGestureEvent>(BaseGestureEvent_serializer::read(thisDeserializer));
    Callback_GestureJudgeResult_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, Ark_GestureJudgeResult value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_GESTUREJUDGERESULT_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_GestureJudgeResult value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_CALLBACK_GESTUREJUDGERESULT_VOID))))};
    callSyncMethod(vmContext, resourceId, gestureInfo, event, continuationResult);
}
void deserializeAndCallCallback_GestureJudgeResult_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, Ark_GestureJudgeResult value)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_GESTUREJUDGERESULT_VOID))));
    thisDeserializer.readPointer();
    Ark_GestureJudgeResult value = static_cast<Ark_GestureJudgeResult>(thisDeserializer.readInt32());
    call(resourceId, value);
}
void deserializeAndCallSyncCallback_GestureJudgeResult_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                            Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_GestureJudgeResult value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_CALLBACK_GESTUREJUDGERESULT_VOID))));
    Ark_GestureJudgeResult value = static_cast<Ark_GestureJudgeResult>(thisDeserializer.readInt32());
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallCallback_GestureRecognizer_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_GestureRecognizer value)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_GESTURERECOGNIZER_VOID))));
    thisDeserializer.readPointer();
    Ark_GestureRecognizer value = static_cast<Ark_GestureRecognizer>(
        GestureRecognizer_serializer::read(thisDeserializer));
    call(resourceId, value);
}
void deserializeAndCallSyncCallback_GestureRecognizer_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                           Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_GestureRecognizer value)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_GESTURERECOGNIZER_VOID))));
    Ark_GestureRecognizer value = static_cast<Ark_GestureRecognizer>(
        GestureRecognizer_serializer::read(thisDeserializer));
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallCallback_HitTestMode_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, Ark_HitTestMode value)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_HITTESTMODE_VOID))));
    thisDeserializer.readPointer();
    Ark_HitTestMode value = static_cast<Ark_HitTestMode>(thisDeserializer.readInt32());
    call(resourceId, value);
}
void deserializeAndCallSyncCallback_HitTestMode_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                     Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_HitTestMode value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_HITTESTMODE_VOID))));
    Ark_HitTestMode value = static_cast<Ark_HitTestMode>(thisDeserializer.readInt32());
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallCallback_HoverEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_HoverEvent data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_HOVEREVENT_VOID))));
    thisDeserializer.readPointer();
    Ark_HoverEvent data = static_cast<Ark_HoverEvent>(HoverEvent_serializer::read(thisDeserializer));
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_HoverEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                    Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_HoverEvent data)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_HOVEREVENT_VOID))));
    Ark_HoverEvent data = static_cast<Ark_HoverEvent>(HoverEvent_serializer::read(thisDeserializer));
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_I32_F64_ComputedBarAttribute(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Int32 index, const Ark_Float64 offset,
                                  const Callback_ComputedBarAttribute_Void continuation)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCaller(KIND_CALLBACK_I32_F64_COMPUTEDBARATTRIBUTE))));
    thisDeserializer.readPointer();
    Ark_Int32 index = thisDeserializer.readInt32();
    Ark_Float64 offset = thisDeserializer.readFloat64();
    Callback_ComputedBarAttribute_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_ComputedBarAttribute value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCaller(KIND_CALLBACK_COMPUTEDBARATTRIBUTE_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                  const Ark_ComputedBarAttribute value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_CALLBACK_COMPUTEDBARATTRIBUTE_VOID))))};
    call(resourceId, index, offset, continuationResult);
}
void deserializeAndCallSyncCallback_I32_F64_ComputedBarAttribute(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                                 Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int32 index,
                                  const Ark_Float64 offset, const Callback_ComputedBarAttribute_Void continuation)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_CALLBACK_I32_F64_COMPUTEDBARATTRIBUTE))));
    Ark_Int32 index = thisDeserializer.readInt32();
    Ark_Float64 offset = thisDeserializer.readFloat64();
    Callback_ComputedBarAttribute_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_ComputedBarAttribute value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCaller(KIND_CALLBACK_COMPUTEDBARATTRIBUTE_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                  const Ark_ComputedBarAttribute value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_CALLBACK_COMPUTEDBARATTRIBUTE_VOID))))};
    callSyncMethod(vmContext, resourceId, index, offset, continuationResult);
}
void deserializeAndCallCallback_I32_I32_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Int32 from, const Ark_Int32 to,
                                                const synthetic_Callback_Boolean_Void continuation)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_I32_I32_BOOLEAN))));
    thisDeserializer.readPointer();
    Ark_Int32 from = thisDeserializer.readInt32();
    Ark_Int32 to = thisDeserializer.readInt32();
    synthetic_Callback_Boolean_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID))))};
    call(resourceId, from, to, continuationResult);
}
void deserializeAndCallSyncCallback_I32_I32_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                    Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int32 from,
                                  const Ark_Int32 to, const synthetic_Callback_Boolean_Void continuation)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_I32_I32_BOOLEAN))));
    Ark_Int32 from = thisDeserializer.readInt32();
    Ark_Int32 to = thisDeserializer.readInt32();
    synthetic_Callback_Boolean_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID))))};
    callSyncMethod(vmContext, resourceId, from, to, continuationResult);
}
void deserializeAndCallCallback_I32_I32_I32_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Int32 start, const Ark_Int32 end,
                                                const Ark_Int32 center)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_I32_I32_I32_VOID))));
    thisDeserializer.readPointer();
    Ark_Int32 start = thisDeserializer.readInt32();
    Ark_Int32 end = thisDeserializer.readInt32();
    Ark_Int32 center = thisDeserializer.readInt32();
    call(resourceId, start, end, center);
}
void deserializeAndCallSyncCallback_I32_I32_I32_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                     Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int32 start,
                                  const Ark_Int32 end, const Ark_Int32 center)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_I32_I32_I32_VOID))));
    Ark_Int32 start = thisDeserializer.readInt32();
    Ark_Int32 end = thisDeserializer.readInt32();
    Ark_Int32 center = thisDeserializer.readInt32();
    callSyncMethod(vmContext, resourceId, start, end, center);
}
void deserializeAndCallCallback_I32_I32_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Int32 first, const Ark_Int32 last)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_I32_I32_VOID))));
    thisDeserializer.readPointer();
    Ark_Int32 first = thisDeserializer.readInt32();
    Ark_Int32 last = thisDeserializer.readInt32();
    call(resourceId, first, last);
}
void deserializeAndCallSyncCallback_I32_I32_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                 Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_Int32 first, const Ark_Int32 last)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_I32_I32_VOID))));
    Ark_Int32 first = thisDeserializer.readInt32();
    Ark_Int32 last = thisDeserializer.readInt32();
    callSyncMethod(vmContext, resourceId, first, last);
}
void deserializeAndCallCallback_I32_Tuple_I32_I32(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Int32 index,
                                                const Callback_Tuple_I32_I32_Void continuation)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_I32_TUPLE_I32_I32))));
    thisDeserializer.readPointer();
    Ark_Int32 index = thisDeserializer.readInt32();
    Callback_Tuple_I32_I32_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Tuple_I32_I32 value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_TUPLE_I32_I32_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Tuple_I32_I32 value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_TUPLE_I32_I32_VOID))))};
    call(resourceId, index, continuationResult);
}
void deserializeAndCallSyncCallback_I32_Tuple_I32_I32(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                      Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int32 index,
                                  const Callback_Tuple_I32_I32_Void continuation)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_I32_TUPLE_I32_I32))));
    Ark_Int32 index = thisDeserializer.readInt32();
    Callback_Tuple_I32_I32_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Tuple_I32_I32 value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_TUPLE_I32_I32_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Tuple_I32_I32 value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_TUPLE_I32_I32_VOID))))};
    callSyncMethod(vmContext, resourceId, index, continuationResult);
}
void deserializeAndCallCallback_I32_Tuple_I32_I32_I32_I32(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Int32 index,
                                                const Callback_Tuple_I32_I32_I32_I32_Void continuation)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_I32_TUPLE_I32_I32_I32_I32))));
    thisDeserializer.readPointer();
    Ark_Int32 index = thisDeserializer.readInt32();
    Callback_Tuple_I32_I32_I32_I32_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Tuple_I32_I32_I32_I32 value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCaller(KIND_CALLBACK_TUPLE_I32_I32_I32_I32_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                  const Ark_Tuple_I32_I32_I32_I32 value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_CALLBACK_TUPLE_I32_I32_I32_I32_VOID))))};
    call(resourceId, index, continuationResult);
}
void deserializeAndCallSyncCallback_I32_Tuple_I32_I32_I32_I32(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                              Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int32 index,
                                  const Callback_Tuple_I32_I32_I32_I32_Void continuation)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_CALLBACK_I32_TUPLE_I32_I32_I32_I32))));
    Ark_Int32 index = thisDeserializer.readInt32();
    Callback_Tuple_I32_I32_I32_I32_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Tuple_I32_I32_I32_I32 value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCaller(KIND_CALLBACK_TUPLE_I32_I32_I32_I32_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                  const Ark_Tuple_I32_I32_I32_I32 value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_CALLBACK_TUPLE_I32_I32_I32_I32_VOID))))};
    callSyncMethod(vmContext, resourceId, index, continuationResult);
}
void deserializeAndCallCallback_I32_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Int32 data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_I32_VOID))));
    thisDeserializer.readPointer();
    Ark_Int32 data = thisDeserializer.readInt32();
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_I32_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int32 data)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_I32_VOID))));
    Ark_Int32 data = thisDeserializer.readInt32();
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_I64_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Int64 data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_I64_VOID))));
    thisDeserializer.readPointer();
    Ark_Int64 data = thisDeserializer.readInt64();
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_I64_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int64 data)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_I64_VOID))));
    Ark_Int64 data = thisDeserializer.readInt64();
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_InsertValue_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_InsertValue data,
                                                const synthetic_Callback_Boolean_Void continuation)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_INSERTVALUE_BOOLEAN))));
    thisDeserializer.readPointer();
    Ark_InsertValue data = InsertValue_serializer::read(thisDeserializer);
    synthetic_Callback_Boolean_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID))))};
    call(resourceId, data, continuationResult);
}
void deserializeAndCallSyncCallback_InsertValue_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                        Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_InsertValue data,
                                  const synthetic_Callback_Boolean_Void continuation)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_INSERTVALUE_BOOLEAN))));
    Ark_InsertValue data = InsertValue_serializer::read(thisDeserializer);
    synthetic_Callback_Boolean_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID))))};
    callSyncMethod(vmContext, resourceId, data, continuationResult);
}
void deserializeAndCallCallback_InsertValue_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_InsertValue data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_INSERTVALUE_VOID))));
    thisDeserializer.readPointer();
    Ark_InsertValue data = InsertValue_serializer::read(thisDeserializer);
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_InsertValue_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                     Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_InsertValue data)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_INSERTVALUE_VOID))));
    Ark_InsertValue data = InsertValue_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_ItemDragInfo_I32_I32_Boolean_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_ItemDragInfo event, const Ark_Int32 itemIndex,
                                  const Ark_Int32 insertIndex, const Ark_Boolean isSuccess)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCaller(KIND_CALLBACK_ITEMDRAGINFO_I32_I32_BOOLEAN_VOID))));
    thisDeserializer.readPointer();
    Ark_ItemDragInfo event = ItemDragInfo_serializer::read(thisDeserializer);
    Ark_Int32 itemIndex = thisDeserializer.readInt32();
    Ark_Int32 insertIndex = thisDeserializer.readInt32();
    Ark_Boolean isSuccess = thisDeserializer.readBoolean();
    call(resourceId, event, itemIndex, insertIndex, isSuccess);
}
void deserializeAndCallSyncCallback_ItemDragInfo_I32_I32_Boolean_Void(Ark_VMContext vmContext,
                                                                      KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_ItemDragInfo event,
                                  const Ark_Int32 itemIndex, const Ark_Int32 insertIndex, const Ark_Boolean isSuccess)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_CALLBACK_ITEMDRAGINFO_I32_I32_BOOLEAN_VOID))));
    Ark_ItemDragInfo event = ItemDragInfo_serializer::read(thisDeserializer);
    Ark_Int32 itemIndex = thisDeserializer.readInt32();
    Ark_Int32 insertIndex = thisDeserializer.readInt32();
    Ark_Boolean isSuccess = thisDeserializer.readBoolean();
    callSyncMethod(vmContext, resourceId, event, itemIndex, insertIndex, isSuccess);
}
void deserializeAndCallCallback_ItemDragInfo_I32_I32_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_ItemDragInfo event,
                                                const Ark_Int32 itemIndex, const Ark_Int32 insertIndex)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_ITEMDRAGINFO_I32_I32_VOID))));
    thisDeserializer.readPointer();
    Ark_ItemDragInfo event = ItemDragInfo_serializer::read(thisDeserializer);
    Ark_Int32 itemIndex = thisDeserializer.readInt32();
    Ark_Int32 insertIndex = thisDeserializer.readInt32();
    call(resourceId, event, itemIndex, insertIndex);
}
void deserializeAndCallSyncCallback_ItemDragInfo_I32_I32_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                              Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_ItemDragInfo event,
                                  const Ark_Int32 itemIndex, const Ark_Int32 insertIndex)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_CALLBACK_ITEMDRAGINFO_I32_I32_VOID))));
    Ark_ItemDragInfo event = ItemDragInfo_serializer::read(thisDeserializer);
    Ark_Int32 itemIndex = thisDeserializer.readInt32();
    Ark_Int32 insertIndex = thisDeserializer.readInt32();
    callSyncMethod(vmContext, resourceId, event, itemIndex, insertIndex);
}
void deserializeAndCallCallback_ItemDragInfo_I32_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_ItemDragInfo event, const Ark_Int32 itemIndex)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_ITEMDRAGINFO_I32_VOID))));
    thisDeserializer.readPointer();
    Ark_ItemDragInfo event = ItemDragInfo_serializer::read(thisDeserializer);
    Ark_Int32 itemIndex = thisDeserializer.readInt32();
    call(resourceId, event, itemIndex);
}
void deserializeAndCallSyncCallback_ItemDragInfo_I32_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                          Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_ItemDragInfo event, const Ark_Int32 itemIndex)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_ITEMDRAGINFO_I32_VOID))));
    Ark_ItemDragInfo event = ItemDragInfo_serializer::read(thisDeserializer);
    Ark_Int32 itemIndex = thisDeserializer.readInt32();
    callSyncMethod(vmContext, resourceId, event, itemIndex);
}
void deserializeAndCallCallback_ItemDragInfo_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_ItemDragInfo event)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_ITEMDRAGINFO_VOID))));
    thisDeserializer.readPointer();
    Ark_ItemDragInfo event = ItemDragInfo_serializer::read(thisDeserializer);
    call(resourceId, event);
}
void deserializeAndCallSyncCallback_ItemDragInfo_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                      Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_ItemDragInfo event)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_ITEMDRAGINFO_VOID))));
    Ark_ItemDragInfo event = ItemDragInfo_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, event);
}
void deserializeAndCallCallback_KeyEvent_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_KeyEvent data,
                                                const synthetic_Callback_Boolean_Void continuation)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_KEYEVENT_BOOLEAN))));
    thisDeserializer.readPointer();
    Ark_KeyEvent data = static_cast<Ark_KeyEvent>(KeyEvent_serializer::read(thisDeserializer));
    synthetic_Callback_Boolean_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID))))};
    call(resourceId, data, continuationResult);
}
void deserializeAndCallSyncCallback_KeyEvent_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                     Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_KeyEvent data,
                                  const synthetic_Callback_Boolean_Void continuation)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_KEYEVENT_BOOLEAN))));
    Ark_KeyEvent data = static_cast<Ark_KeyEvent>(KeyEvent_serializer::read(thisDeserializer));
    synthetic_Callback_Boolean_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID))))};
    callSyncMethod(vmContext, resourceId, data, continuationResult);
}
void deserializeAndCallCallback_KeyEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_KeyEvent data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_KEYEVENT_VOID))));
    thisDeserializer.readPointer();
    Ark_KeyEvent data = static_cast<Ark_KeyEvent>(KeyEvent_serializer::read(thisDeserializer));
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_KeyEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                  Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_KeyEvent data)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_KEYEVENT_VOID))));
    Ark_KeyEvent data = static_cast<Ark_KeyEvent>(KeyEvent_serializer::read(thisDeserializer));
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_Length_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Length data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_LENGTH_VOID))));
    thisDeserializer.readPointer();
    const Ark_Int8 dataTmpBufUnionSelector = thisDeserializer.readInt8();
    Ark_Length dataTmpBuf = {};
    dataTmpBuf.selector = dataTmpBufUnionSelector;
    if (dataTmpBufUnionSelector == 0)
    {
        dataTmpBuf.selector = 0;
        dataTmpBuf.value0 = static_cast<Ark_String>(thisDeserializer.readString());
    }
    else if (dataTmpBufUnionSelector == 1)
    {
        dataTmpBuf.selector = 1;
        dataTmpBuf.value1 = thisDeserializer.readFloat64();
    }
    else if (dataTmpBufUnionSelector == 2)
    {
        dataTmpBuf.selector = 2;
        dataTmpBuf.value2 = Resource_serializer::read(thisDeserializer);
    }
    else
    {
        INTEROP_FATAL("One of the branches for dataTmpBuf has to be chosen through deserialisation.");
    }
    Ark_Length data = static_cast<Ark_Length>(dataTmpBuf);
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_Length_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Length data)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_LENGTH_VOID))));
    const Ark_Int8 dataTmpBufUnionSelector = thisDeserializer.readInt8();
    Ark_Length dataTmpBuf = {};
    dataTmpBuf.selector = dataTmpBufUnionSelector;
    if (dataTmpBufUnionSelector == 0)
    {
        dataTmpBuf.selector = 0;
        dataTmpBuf.value0 = static_cast<Ark_String>(thisDeserializer.readString());
    }
    else if (dataTmpBufUnionSelector == 1)
    {
        dataTmpBuf.selector = 1;
        dataTmpBuf.value1 = thisDeserializer.readFloat64();
    }
    else if (dataTmpBufUnionSelector == 2)
    {
        dataTmpBuf.selector = 2;
        dataTmpBuf.value2 = Resource_serializer::read(thisDeserializer);
    }
    else
    {
        INTEROP_FATAL("One of the branches for dataTmpBuf has to be chosen through deserialisation.");
    }
    Ark_Length data = static_cast<Ark_Length>(dataTmpBuf);
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_Map_String_Opt_Object(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Map_String_Opt_Object data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_MAP_STRING_OPT_OBJECT))));
    thisDeserializer.readPointer();
    const Ark_Int32 dataTmpBufSizeVar = thisDeserializer.readInt32();
    Map_String_Opt_Object dataTmpBuf = {};
    thisDeserializer.resizeMap<Map_String_Opt_Object, Ark_String, Opt_Object>(&dataTmpBuf, dataTmpBufSizeVar);
    for (int dataTmpBufIVar = 0; dataTmpBufIVar < dataTmpBufSizeVar; dataTmpBufIVar++)
    {
        const Ark_String dataTmpBufKeyVar = static_cast<Ark_String>(thisDeserializer.readString());
        const auto dataTmpBufValueVarTempBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
        Opt_Object dataTmpBufValueVarTempBuf = {};
        dataTmpBufValueVarTempBuf.tag = dataTmpBufValueVarTempBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ?
                                            INTEROP_TAG_UNDEFINED :
                                            INTEROP_TAG_OBJECT;
        if ((dataTmpBufValueVarTempBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
        {
            dataTmpBufValueVarTempBuf.value = static_cast<Ark_Object>(thisDeserializer.readObject());
        }
        const Opt_Object dataTmpBufValueVar = dataTmpBufValueVarTempBuf;
        dataTmpBuf.keys[dataTmpBufIVar] = dataTmpBufKeyVar;
        dataTmpBuf.values[dataTmpBufIVar] = dataTmpBufValueVar;
    }
    Map_String_Opt_Object data = dataTmpBuf;
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_Map_String_Opt_Object(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                          Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Map_String_Opt_Object data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_MAP_STRING_OPT_OBJECT))));
    const Ark_Int32 dataTmpBufSizeVar = thisDeserializer.readInt32();
    Map_String_Opt_Object dataTmpBuf = {};
    thisDeserializer.resizeMap<Map_String_Opt_Object, Ark_String, Opt_Object>(&dataTmpBuf, dataTmpBufSizeVar);
    for (int dataTmpBufIVar = 0; dataTmpBufIVar < dataTmpBufSizeVar; dataTmpBufIVar++)
    {
        const Ark_String dataTmpBufKeyVar = static_cast<Ark_String>(thisDeserializer.readString());
        const auto dataTmpBufValueVarTempBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
        Opt_Object dataTmpBufValueVarTempBuf = {};
        dataTmpBufValueVarTempBuf.tag = dataTmpBufValueVarTempBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ?
                                            INTEROP_TAG_UNDEFINED :
                                            INTEROP_TAG_OBJECT;
        if ((dataTmpBufValueVarTempBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
        {
            dataTmpBufValueVarTempBuf.value = static_cast<Ark_Object>(thisDeserializer.readObject());
        }
        const Opt_Object dataTmpBufValueVar = dataTmpBufValueVarTempBuf;
        dataTmpBuf.keys[dataTmpBufIVar] = dataTmpBufKeyVar;
        dataTmpBuf.values[dataTmpBufIVar] = dataTmpBufValueVar;
    }
    Map_String_Opt_Object data = dataTmpBuf;
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_MarqueeState_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, Ark_MarqueeState data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_MARQUEESTATE_VOID))));
    thisDeserializer.readPointer();
    Ark_MarqueeState data = static_cast<Ark_MarqueeState>(thisDeserializer.readInt32());
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_MarqueeState_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                      Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_MarqueeState data)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_MARQUEESTATE_VOID))));
    Ark_MarqueeState data = static_cast<Ark_MarqueeState>(thisDeserializer.readInt32());
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_MouseEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_MouseEvent event)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_MOUSEEVENT_VOID))));
    thisDeserializer.readPointer();
    Ark_MouseEvent event = static_cast<Ark_MouseEvent>(MouseEvent_serializer::read(thisDeserializer));
    call(resourceId, event);
}
void deserializeAndCallSyncCallback_MouseEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                    Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_MouseEvent event)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_MOUSEEVENT_VOID))));
    Ark_MouseEvent event = static_cast<Ark_MouseEvent>(MouseEvent_serializer::read(thisDeserializer));
    callSyncMethod(vmContext, resourceId, event);
}
void deserializeAndCallCallback_NativeEmbedDataInfo_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_NativeEmbedDataInfo event)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_NATIVEEMBEDDATAINFO_VOID))));
    thisDeserializer.readPointer();
    Ark_NativeEmbedDataInfo event = NativeEmbedDataInfo_serializer::read(thisDeserializer);
    call(resourceId, event);
}
void deserializeAndCallSyncCallback_NativeEmbedDataInfo_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                             Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_NativeEmbedDataInfo event)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_NATIVEEMBEDDATAINFO_VOID))));
    Ark_NativeEmbedDataInfo event = NativeEmbedDataInfo_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, event);
}
void deserializeAndCallCallback_NativeEmbedTouchInfo_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_NativeEmbedTouchInfo event)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_NATIVEEMBEDTOUCHINFO_VOID))));
    thisDeserializer.readPointer();
    Ark_NativeEmbedTouchInfo event = NativeEmbedTouchInfo_serializer::read(thisDeserializer);
    call(resourceId, event);
}
void deserializeAndCallSyncCallback_NativeEmbedTouchInfo_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                              Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_NativeEmbedTouchInfo event)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCallerSync(KIND_CALLBACK_NATIVEEMBEDTOUCHINFO_VOID))));
    Ark_NativeEmbedTouchInfo event = NativeEmbedTouchInfo_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, event);
}
void deserializeAndCallCallback_NavDestinationActiveReason_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, Ark_NavDestinationActiveReason data)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCaller(KIND_CALLBACK_NAVDESTINATIONACTIVEREASON_VOID))));
    thisDeserializer.readPointer();
    Ark_NavDestinationActiveReason data = static_cast<Ark_NavDestinationActiveReason>(thisDeserializer.readInt32());
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_NavDestinationActiveReason_Void(Ark_VMContext vmContext,
                                                                    KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          Ark_NavDestinationActiveReason data)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCallerSync(KIND_CALLBACK_NAVDESTINATIONACTIVEREASON_VOID))));
    Ark_NavDestinationActiveReason data = static_cast<Ark_NavDestinationActiveReason>(thisDeserializer.readInt32());
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_NavDestinationContext_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_NavDestinationContext data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_NAVDESTINATIONCONTEXT_VOID))));
    thisDeserializer.readPointer();
    Ark_NavDestinationContext data = static_cast<Ark_NavDestinationContext>(
        NavDestinationContext_serializer::read(thisDeserializer));
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_NavDestinationContext_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                               Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_NavDestinationContext data)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCallerSync(KIND_CALLBACK_NAVDESTINATIONCONTEXT_VOID))));
    Ark_NavDestinationContext data = static_cast<Ark_NavDestinationContext>(
        NavDestinationContext_serializer::read(thisDeserializer));
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_NavigationMode_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, Ark_NavigationMode mode)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_NAVIGATIONMODE_VOID))));
    thisDeserializer.readPointer();
    Ark_NavigationMode mode = static_cast<Ark_NavigationMode>(thisDeserializer.readInt32());
    call(resourceId, mode);
}
void deserializeAndCallSyncCallback_NavigationMode_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                        Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_NavigationMode mode)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_NAVIGATIONMODE_VOID))));
    Ark_NavigationMode mode = static_cast<Ark_NavigationMode>(thisDeserializer.readInt32());
    callSyncMethod(vmContext, resourceId, mode);
}
void deserializeAndCallCallback_NavigationTitleMode_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, Ark_NavigationTitleMode titleMode)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_NAVIGATIONTITLEMODE_VOID))));
    thisDeserializer.readPointer();
    Ark_NavigationTitleMode titleMode = static_cast<Ark_NavigationTitleMode>(thisDeserializer.readInt32());
    call(resourceId, titleMode);
}
void deserializeAndCallSyncCallback_NavigationTitleMode_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                             Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          Ark_NavigationTitleMode titleMode)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_NAVIGATIONTITLEMODE_VOID))));
    Ark_NavigationTitleMode titleMode = static_cast<Ark_NavigationTitleMode>(thisDeserializer.readInt32());
    callSyncMethod(vmContext, resourceId, titleMode);
}
void deserializeAndCallCallback_NavigationTransitionProxy_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_NavigationTransitionProxy transitionProxy)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCaller(KIND_CALLBACK_NAVIGATIONTRANSITIONPROXY_VOID))));
    thisDeserializer.readPointer();
    Ark_NavigationTransitionProxy transitionProxy = static_cast<Ark_NavigationTransitionProxy>(
        NavigationTransitionProxy_serializer::read(thisDeserializer));
    call(resourceId, transitionProxy);
}
void deserializeAndCallSyncCallback_NavigationTransitionProxy_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                                   Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_NavigationTransitionProxy transitionProxy)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCallerSync(KIND_CALLBACK_NAVIGATIONTRANSITIONPROXY_VOID))));
    Ark_NavigationTransitionProxy transitionProxy = static_cast<Ark_NavigationTransitionProxy>(
        NavigationTransitionProxy_serializer::read(thisDeserializer));
    callSyncMethod(vmContext, resourceId, transitionProxy);
}
void deserializeAndCallCallback_Number_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Number data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_NUMBER_VOID))));
    thisDeserializer.readPointer();
    Ark_Number data = static_cast<Ark_Number>(thisDeserializer.readNumber());
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_Number_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number data)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_NUMBER_VOID))));
    Ark_Number data = static_cast<Ark_Number>(thisDeserializer.readNumber());
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_Object_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Object data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_OBJECT_VOID))));
    thisDeserializer.readPointer();
    Ark_Object data = static_cast<Ark_Object>(thisDeserializer.readObject());
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_Object_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Object data)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_OBJECT_VOID))));
    Ark_Object data = static_cast<Ark_Object>(thisDeserializer.readObject());
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_OnAlertEvent_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_OnAlertEvent data,
                                                const synthetic_Callback_Boolean_Void continuation)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_ONALERTEVENT_BOOLEAN))));
    thisDeserializer.readPointer();
    Ark_OnAlertEvent data = OnAlertEvent_serializer::read(thisDeserializer);
    synthetic_Callback_Boolean_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID))))};
    call(resourceId, data, continuationResult);
}
void deserializeAndCallSyncCallback_OnAlertEvent_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                         Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnAlertEvent data,
                                  const synthetic_Callback_Boolean_Void continuation)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_ONALERTEVENT_BOOLEAN))));
    Ark_OnAlertEvent data = OnAlertEvent_serializer::read(thisDeserializer);
    synthetic_Callback_Boolean_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID))))};
    callSyncMethod(vmContext, resourceId, data, continuationResult);
}
void deserializeAndCallCallback_OnAudioStateChangedEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_OnAudioStateChangedEvent data)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCaller(KIND_CALLBACK_ONAUDIOSTATECHANGEDEVENT_VOID))));
    thisDeserializer.readPointer();
    Ark_OnAudioStateChangedEvent data = OnAudioStateChangedEvent_serializer::read(thisDeserializer);
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_OnAudioStateChangedEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                                  Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_OnAudioStateChangedEvent data)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCallerSync(KIND_CALLBACK_ONAUDIOSTATECHANGEDEVENT_VOID))));
    Ark_OnAudioStateChangedEvent data = OnAudioStateChangedEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_OnBeforeUnloadEvent_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_OnBeforeUnloadEvent data,
                                                const synthetic_Callback_Boolean_Void continuation)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_ONBEFOREUNLOADEVENT_BOOLEAN))));
    thisDeserializer.readPointer();
    Ark_OnBeforeUnloadEvent data = OnBeforeUnloadEvent_serializer::read(thisDeserializer);
    synthetic_Callback_Boolean_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID))))};
    call(resourceId, data, continuationResult);
}
void deserializeAndCallSyncCallback_OnBeforeUnloadEvent_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                                Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_OnBeforeUnloadEvent data,
                                                          const synthetic_Callback_Boolean_Void continuation)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCallerSync(KIND_CALLBACK_ONBEFOREUNLOADEVENT_BOOLEAN))));
    Ark_OnBeforeUnloadEvent data = OnBeforeUnloadEvent_serializer::read(thisDeserializer);
    synthetic_Callback_Boolean_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID))))};
    callSyncMethod(vmContext, resourceId, data, continuationResult);
}
void deserializeAndCallCallback_OnClientAuthenticationEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_OnClientAuthenticationEvent data)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCaller(KIND_CALLBACK_ONCLIENTAUTHENTICATIONEVENT_VOID))));
    thisDeserializer.readPointer();
    Ark_OnClientAuthenticationEvent data = OnClientAuthenticationEvent_serializer::read(thisDeserializer);
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_OnClientAuthenticationEvent_Void(Ark_VMContext vmContext,
                                                                     KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_OnClientAuthenticationEvent data)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCallerSync(KIND_CALLBACK_ONCLIENTAUTHENTICATIONEVENT_VOID))));
    Ark_OnClientAuthenticationEvent data = OnClientAuthenticationEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_OnConfirmEvent_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_OnConfirmEvent data,
                                                const synthetic_Callback_Boolean_Void continuation)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_ONCONFIRMEVENT_BOOLEAN))));
    thisDeserializer.readPointer();
    Ark_OnConfirmEvent data = OnConfirmEvent_serializer::read(thisDeserializer);
    synthetic_Callback_Boolean_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID))))};
    call(resourceId, data, continuationResult);
}
void deserializeAndCallSyncCallback_OnConfirmEvent_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                           Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnConfirmEvent data,
                                  const synthetic_Callback_Boolean_Void continuation)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_CALLBACK_ONCONFIRMEVENT_BOOLEAN))));
    Ark_OnConfirmEvent data = OnConfirmEvent_serializer::read(thisDeserializer);
    synthetic_Callback_Boolean_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID))))};
    callSyncMethod(vmContext, resourceId, data, continuationResult);
}
void deserializeAndCallCallback_OnConsoleEvent_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_OnConsoleEvent data,
                                                const synthetic_Callback_Boolean_Void continuation)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_ONCONSOLEEVENT_BOOLEAN))));
    thisDeserializer.readPointer();
    Ark_OnConsoleEvent data = OnConsoleEvent_serializer::read(thisDeserializer);
    synthetic_Callback_Boolean_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID))))};
    call(resourceId, data, continuationResult);
}
void deserializeAndCallSyncCallback_OnConsoleEvent_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                           Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnConsoleEvent data,
                                  const synthetic_Callback_Boolean_Void continuation)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_CALLBACK_ONCONSOLEEVENT_BOOLEAN))));
    Ark_OnConsoleEvent data = OnConsoleEvent_serializer::read(thisDeserializer);
    synthetic_Callback_Boolean_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID))))};
    callSyncMethod(vmContext, resourceId, data, continuationResult);
}
void deserializeAndCallCallback_OnContextMenuShowEvent_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_OnContextMenuShowEvent data,
                                                const synthetic_Callback_Boolean_Void continuation)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCaller(KIND_CALLBACK_ONCONTEXTMENUSHOWEVENT_BOOLEAN))));
    thisDeserializer.readPointer();
    Ark_OnContextMenuShowEvent data = OnContextMenuShowEvent_serializer::read(thisDeserializer);
    synthetic_Callback_Boolean_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID))))};
    call(resourceId, data, continuationResult);
}
void deserializeAndCallSyncCallback_OnContextMenuShowEvent_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                                   Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_OnContextMenuShowEvent data,
                                                          const synthetic_Callback_Boolean_Void continuation)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCallerSync(KIND_CALLBACK_ONCONTEXTMENUSHOWEVENT_BOOLEAN))));
    Ark_OnContextMenuShowEvent data = OnContextMenuShowEvent_serializer::read(thisDeserializer);
    synthetic_Callback_Boolean_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID))))};
    callSyncMethod(vmContext, resourceId, data, continuationResult);
}
void deserializeAndCallCallback_OnDataResubmittedEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_OnDataResubmittedEvent data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_ONDATARESUBMITTEDEVENT_VOID))));
    thisDeserializer.readPointer();
    Ark_OnDataResubmittedEvent data = OnDataResubmittedEvent_serializer::read(thisDeserializer);
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_OnDataResubmittedEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                                Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_OnDataResubmittedEvent data)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCallerSync(KIND_CALLBACK_ONDATARESUBMITTEDEVENT_VOID))));
    Ark_OnDataResubmittedEvent data = OnDataResubmittedEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_OnDestory_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Int64 nodeId)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_ONDESTORY_VOID))));
    thisDeserializer.readPointer();
    Ark_Int64 nodeId = thisDeserializer.readInt64();
    call(resourceId, nodeId);
}
void deserializeAndCallSyncCallback_OnDestory_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                   Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int64 nodeId)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_ONDESTORY_VOID))));
    Ark_Int64 nodeId = thisDeserializer.readInt64();
    callSyncMethod(vmContext, resourceId, nodeId);
}
void deserializeAndCallCallback_OnDownloadStartEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_OnDownloadStartEvent data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_ONDOWNLOADSTARTEVENT_VOID))));
    thisDeserializer.readPointer();
    Ark_OnDownloadStartEvent data = OnDownloadStartEvent_serializer::read(thisDeserializer);
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_OnDownloadStartEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                              Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_OnDownloadStartEvent data)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCallerSync(KIND_CALLBACK_ONDOWNLOADSTARTEVENT_VOID))));
    Ark_OnDownloadStartEvent data = OnDownloadStartEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_OnErrorReceiveEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_OnErrorReceiveEvent data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_ONERRORRECEIVEEVENT_VOID))));
    thisDeserializer.readPointer();
    Ark_OnErrorReceiveEvent data = OnErrorReceiveEvent_serializer::read(thisDeserializer);
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_OnErrorReceiveEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                             Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_OnErrorReceiveEvent data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_ONERRORRECEIVEEVENT_VOID))));
    Ark_OnErrorReceiveEvent data = OnErrorReceiveEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_OnFaviconReceivedEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_OnFaviconReceivedEvent data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_ONFAVICONRECEIVEDEVENT_VOID))));
    thisDeserializer.readPointer();
    Ark_OnFaviconReceivedEvent data = OnFaviconReceivedEvent_serializer::read(thisDeserializer);
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_OnFaviconReceivedEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                                Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_OnFaviconReceivedEvent data)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCallerSync(KIND_CALLBACK_ONFAVICONRECEIVEDEVENT_VOID))));
    Ark_OnFaviconReceivedEvent data = OnFaviconReceivedEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_OnFirstContentfulPaintEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_OnFirstContentfulPaintEvent data)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCaller(KIND_CALLBACK_ONFIRSTCONTENTFULPAINTEVENT_VOID))));
    thisDeserializer.readPointer();
    Ark_OnFirstContentfulPaintEvent data = OnFirstContentfulPaintEvent_serializer::read(thisDeserializer);
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_OnFirstContentfulPaintEvent_Void(Ark_VMContext vmContext,
                                                                     KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_OnFirstContentfulPaintEvent data)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCallerSync(KIND_CALLBACK_ONFIRSTCONTENTFULPAINTEVENT_VOID))));
    Ark_OnFirstContentfulPaintEvent data = OnFirstContentfulPaintEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_OnGeolocationShowEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_OnGeolocationShowEvent data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_ONGEOLOCATIONSHOWEVENT_VOID))));
    thisDeserializer.readPointer();
    Ark_OnGeolocationShowEvent data = OnGeolocationShowEvent_serializer::read(thisDeserializer);
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_OnGeolocationShowEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                                Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_OnGeolocationShowEvent data)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCallerSync(KIND_CALLBACK_ONGEOLOCATIONSHOWEVENT_VOID))));
    Ark_OnGeolocationShowEvent data = OnGeolocationShowEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_OnHttpAuthRequestEvent_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_OnHttpAuthRequestEvent data,
                                                const synthetic_Callback_Boolean_Void continuation)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCaller(KIND_CALLBACK_ONHTTPAUTHREQUESTEVENT_BOOLEAN))));
    thisDeserializer.readPointer();
    Ark_OnHttpAuthRequestEvent data = OnHttpAuthRequestEvent_serializer::read(thisDeserializer);
    synthetic_Callback_Boolean_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID))))};
    call(resourceId, data, continuationResult);
}
void deserializeAndCallSyncCallback_OnHttpAuthRequestEvent_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                                   Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_OnHttpAuthRequestEvent data,
                                                          const synthetic_Callback_Boolean_Void continuation)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCallerSync(KIND_CALLBACK_ONHTTPAUTHREQUESTEVENT_BOOLEAN))));
    Ark_OnHttpAuthRequestEvent data = OnHttpAuthRequestEvent_serializer::read(thisDeserializer);
    synthetic_Callback_Boolean_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID))))};
    callSyncMethod(vmContext, resourceId, data, continuationResult);
}
void deserializeAndCallCallback_OnHttpErrorReceiveEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_OnHttpErrorReceiveEvent data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_ONHTTPERRORRECEIVEEVENT_VOID))));
    thisDeserializer.readPointer();
    Ark_OnHttpErrorReceiveEvent data = OnHttpErrorReceiveEvent_serializer::read(thisDeserializer);
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_OnHttpErrorReceiveEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                                 Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_OnHttpErrorReceiveEvent data)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCallerSync(KIND_CALLBACK_ONHTTPERRORRECEIVEEVENT_VOID))));
    Ark_OnHttpErrorReceiveEvent data = OnHttpErrorReceiveEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_OnInterceptRequestEvent_Opt_WebResourceResponse(KSerializerBuffer thisArray,
                                                                                Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_OnInterceptRequestEvent data,
                                                const Callback_Opt_WebResourceResponse_Void continuation)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCaller(KIND_CALLBACK_ONINTERCEPTREQUESTEVENT_OPT_WEBRESOURCERESPONSE))));
    thisDeserializer.readPointer();
    Ark_OnInterceptRequestEvent data = OnInterceptRequestEvent_serializer::read(thisDeserializer);
    Callback_Opt_WebResourceResponse_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Opt_WebResourceResponse value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCaller(KIND_CALLBACK_OPT_WEBRESOURCERESPONSE_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                  const Opt_WebResourceResponse value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_CALLBACK_OPT_WEBRESOURCERESPONSE_VOID))))};
    call(resourceId, data, continuationResult);
}
void deserializeAndCallSyncCallback_OnInterceptRequestEvent_Opt_WebResourceResponse(Ark_VMContext vmContext,
                                                                                    KSerializerBuffer thisArray,
                                                                                    Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_OnInterceptRequestEvent data,
                                                          const Callback_Opt_WebResourceResponse_Void continuation)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCallerSync(KIND_CALLBACK_ONINTERCEPTREQUESTEVENT_OPT_WEBRESOURCERESPONSE))));
    Ark_OnInterceptRequestEvent data = OnInterceptRequestEvent_serializer::read(thisDeserializer);
    Callback_Opt_WebResourceResponse_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Opt_WebResourceResponse value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCaller(KIND_CALLBACK_OPT_WEBRESOURCERESPONSE_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                  const Opt_WebResourceResponse value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_CALLBACK_OPT_WEBRESOURCERESPONSE_VOID))))};
    callSyncMethod(vmContext, resourceId, data, continuationResult);
}
void deserializeAndCallCallback_OnLoadFinishedEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_OnLoadFinishedEvent data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_ONLOADFINISHEDEVENT_VOID))));
    thisDeserializer.readPointer();
    Ark_OnLoadFinishedEvent data = OnLoadFinishedEvent_serializer::read(thisDeserializer);
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_OnLoadFinishedEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                             Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_OnLoadFinishedEvent data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_ONLOADFINISHEDEVENT_VOID))));
    Ark_OnLoadFinishedEvent data = OnLoadFinishedEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_OnLoadInterceptEvent_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_OnLoadInterceptEvent data,
                                                const synthetic_Callback_Boolean_Void continuation)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_ONLOADINTERCEPTEVENT_BOOLEAN))));
    thisDeserializer.readPointer();
    Ark_OnLoadInterceptEvent data = OnLoadInterceptEvent_serializer::read(thisDeserializer);
    synthetic_Callback_Boolean_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID))))};
    call(resourceId, data, continuationResult);
}
void deserializeAndCallSyncCallback_OnLoadInterceptEvent_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                                 Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_OnLoadInterceptEvent data,
                                                          const synthetic_Callback_Boolean_Void continuation)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCallerSync(KIND_CALLBACK_ONLOADINTERCEPTEVENT_BOOLEAN))));
    Ark_OnLoadInterceptEvent data = OnLoadInterceptEvent_serializer::read(thisDeserializer);
    synthetic_Callback_Boolean_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID))))};
    callSyncMethod(vmContext, resourceId, data, continuationResult);
}
void deserializeAndCallCallback_OnLoadStartedEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_OnLoadStartedEvent data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_ONLOADSTARTEDEVENT_VOID))));
    thisDeserializer.readPointer();
    Ark_OnLoadStartedEvent data = OnLoadStartedEvent_serializer::read(thisDeserializer);
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_OnLoadStartedEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                            Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_OnLoadStartedEvent data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_ONLOADSTARTEDEVENT_VOID))));
    Ark_OnLoadStartedEvent data = OnLoadStartedEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_onMeasureSize_SizeResult(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<
        void (*)(const Ark_Int32 resourceId, const Ark_GeometryInfo selfLayoutInfo, const Array_Measurable children,
                 const Ark_ConstraintSizeOptions constraint, const Callback_SizeResult_Void continuation)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_ONMEASURESIZE_SIZERESULT))));
    thisDeserializer.readPointer();
    Ark_GeometryInfo selfLayoutInfo = GeometryInfo_serializer::read(thisDeserializer);
    const Ark_Int32 childrenTmpBufLength = thisDeserializer.readInt32();
    Array_Measurable childrenTmpBuf = {};
    thisDeserializer.resizeArray<std::decay<decltype(childrenTmpBuf)>::type,
                                 std::decay<decltype(*childrenTmpBuf.array)>::type>(&childrenTmpBuf,
                                                                                    childrenTmpBufLength);
    for (int childrenTmpBufBufCounterI = 0; childrenTmpBufBufCounterI < childrenTmpBufLength;
         childrenTmpBufBufCounterI++)
    {
        childrenTmpBuf.array[childrenTmpBufBufCounterI] = static_cast<Ark_Measurable>(
            Measurable_serializer::read(thisDeserializer));
    }
    Array_Measurable children = childrenTmpBuf;
    Ark_ConstraintSizeOptions constraint = ConstraintSizeOptions_serializer::read(thisDeserializer);
    Callback_SizeResult_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_SizeResult value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_SIZERESULT_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_SizeResult value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_SIZERESULT_VOID))))};
    call(resourceId, selfLayoutInfo, children, constraint, continuationResult);
}
void deserializeAndCallSyncCallback_onMeasureSize_SizeResult(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                             Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<
        void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_GeometryInfo selfLayoutInfo,
                 const Array_Measurable children, const Ark_ConstraintSizeOptions constraint,
                 const Callback_SizeResult_Void continuation)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_ONMEASURESIZE_SIZERESULT))));
    Ark_GeometryInfo selfLayoutInfo = GeometryInfo_serializer::read(thisDeserializer);
    const Ark_Int32 childrenTmpBufLength = thisDeserializer.readInt32();
    Array_Measurable childrenTmpBuf = {};
    thisDeserializer.resizeArray<std::decay<decltype(childrenTmpBuf)>::type,
                                 std::decay<decltype(*childrenTmpBuf.array)>::type>(&childrenTmpBuf,
                                                                                    childrenTmpBufLength);
    for (int childrenTmpBufBufCounterI = 0; childrenTmpBufBufCounterI < childrenTmpBufLength;
         childrenTmpBufBufCounterI++)
    {
        childrenTmpBuf.array[childrenTmpBufBufCounterI] = static_cast<Ark_Measurable>(
            Measurable_serializer::read(thisDeserializer));
    }
    Array_Measurable children = childrenTmpBuf;
    Ark_ConstraintSizeOptions constraint = ConstraintSizeOptions_serializer::read(thisDeserializer);
    Callback_SizeResult_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_SizeResult value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_SIZERESULT_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_SizeResult value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_SIZERESULT_VOID))))};
    callSyncMethod(vmContext, resourceId, selfLayoutInfo, children, constraint, continuationResult);
}
void deserializeAndCallCallback_OnMoveFromTo(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Int32 from, const Ark_Int32 to)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_ONMOVEFROMTO))));
    thisDeserializer.readPointer();
    Ark_Int32 from = thisDeserializer.readInt32();
    Ark_Int32 to = thisDeserializer.readInt32();
    call(resourceId, from, to);
}
void deserializeAndCallSyncCallback_OnMoveFromTo(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                 Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_Int32 from, const Ark_Int32 to)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_ONMOVEFROMTO))));
    Ark_Int32 from = thisDeserializer.readInt32();
    Ark_Int32 to = thisDeserializer.readInt32();
    callSyncMethod(vmContext, resourceId, from, to);
}
void deserializeAndCallCallback_OnOverScrollEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_OnOverScrollEvent data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_ONOVERSCROLLEVENT_VOID))));
    thisDeserializer.readPointer();
    Ark_OnOverScrollEvent data = OnOverScrollEvent_serializer::read(thisDeserializer);
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_OnOverScrollEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                           Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_OnOverScrollEvent data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_ONOVERSCROLLEVENT_VOID))));
    Ark_OnOverScrollEvent data = OnOverScrollEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_OnPageBeginEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_OnPageBeginEvent data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_ONPAGEBEGINEVENT_VOID))));
    thisDeserializer.readPointer();
    Ark_OnPageBeginEvent data = OnPageBeginEvent_serializer::read(thisDeserializer);
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_OnPageBeginEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                          Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_OnPageBeginEvent data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_ONPAGEBEGINEVENT_VOID))));
    Ark_OnPageBeginEvent data = OnPageBeginEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_OnPageEndEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_OnPageEndEvent data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_ONPAGEENDEVENT_VOID))));
    thisDeserializer.readPointer();
    Ark_OnPageEndEvent data = OnPageEndEvent_serializer::read(thisDeserializer);
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_OnPageEndEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                        Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnPageEndEvent data)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_ONPAGEENDEVENT_VOID))));
    Ark_OnPageEndEvent data = OnPageEndEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_OnPageVisibleEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_OnPageVisibleEvent data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_ONPAGEVISIBLEEVENT_VOID))));
    thisDeserializer.readPointer();
    Ark_OnPageVisibleEvent data = OnPageVisibleEvent_serializer::read(thisDeserializer);
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_OnPageVisibleEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                            Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_OnPageVisibleEvent data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_ONPAGEVISIBLEEVENT_VOID))));
    Ark_OnPageVisibleEvent data = OnPageVisibleEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_OnPermissionRequestEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_OnPermissionRequestEvent data)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCaller(KIND_CALLBACK_ONPERMISSIONREQUESTEVENT_VOID))));
    thisDeserializer.readPointer();
    Ark_OnPermissionRequestEvent data = OnPermissionRequestEvent_serializer::read(thisDeserializer);
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_OnPermissionRequestEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                                  Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_OnPermissionRequestEvent data)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCallerSync(KIND_CALLBACK_ONPERMISSIONREQUESTEVENT_VOID))));
    Ark_OnPermissionRequestEvent data = OnPermissionRequestEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_onPlaceChildren_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_GeometryInfo selfLayoutInfo,
                                  const Array_Layoutable children, const Ark_ConstraintSizeOptions constraint)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_ONPLACECHILDREN_VOID))));
    thisDeserializer.readPointer();
    Ark_GeometryInfo selfLayoutInfo = GeometryInfo_serializer::read(thisDeserializer);
    const Ark_Int32 childrenTmpBufLength = thisDeserializer.readInt32();
    Array_Layoutable childrenTmpBuf = {};
    thisDeserializer.resizeArray<std::decay<decltype(childrenTmpBuf)>::type,
                                 std::decay<decltype(*childrenTmpBuf.array)>::type>(&childrenTmpBuf,
                                                                                    childrenTmpBufLength);
    for (int childrenTmpBufBufCounterI = 0; childrenTmpBufBufCounterI < childrenTmpBufLength;
         childrenTmpBufBufCounterI++)
    {
        childrenTmpBuf.array[childrenTmpBufBufCounterI] = static_cast<Ark_Layoutable>(
            Layoutable_serializer::read(thisDeserializer));
    }
    Array_Layoutable children = childrenTmpBuf;
    Ark_ConstraintSizeOptions constraint = ConstraintSizeOptions_serializer::read(thisDeserializer);
    call(resourceId, selfLayoutInfo, children, constraint);
}
void deserializeAndCallSyncCallback_onPlaceChildren_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                         Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<
        void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_GeometryInfo selfLayoutInfo,
                 const Array_Layoutable children, const Ark_ConstraintSizeOptions constraint)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_ONPLACECHILDREN_VOID))));
    Ark_GeometryInfo selfLayoutInfo = GeometryInfo_serializer::read(thisDeserializer);
    const Ark_Int32 childrenTmpBufLength = thisDeserializer.readInt32();
    Array_Layoutable childrenTmpBuf = {};
    thisDeserializer.resizeArray<std::decay<decltype(childrenTmpBuf)>::type,
                                 std::decay<decltype(*childrenTmpBuf.array)>::type>(&childrenTmpBuf,
                                                                                    childrenTmpBufLength);
    for (int childrenTmpBufBufCounterI = 0; childrenTmpBufBufCounterI < childrenTmpBufLength;
         childrenTmpBufBufCounterI++)
    {
        childrenTmpBuf.array[childrenTmpBufBufCounterI] = static_cast<Ark_Layoutable>(
            Layoutable_serializer::read(thisDeserializer));
    }
    Array_Layoutable children = childrenTmpBuf;
    Ark_ConstraintSizeOptions constraint = ConstraintSizeOptions_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, selfLayoutInfo, children, constraint);
}
void deserializeAndCallCallback_OnProgressChangeEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_OnProgressChangeEvent data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_ONPROGRESSCHANGEEVENT_VOID))));
    thisDeserializer.readPointer();
    Ark_OnProgressChangeEvent data = OnProgressChangeEvent_serializer::read(thisDeserializer);
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_OnProgressChangeEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                               Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_OnProgressChangeEvent data)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCallerSync(KIND_CALLBACK_ONPROGRESSCHANGEEVENT_VOID))));
    Ark_OnProgressChangeEvent data = OnProgressChangeEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_OnPromptEvent_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_OnPromptEvent data,
                                                const synthetic_Callback_Boolean_Void continuation)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_ONPROMPTEVENT_BOOLEAN))));
    thisDeserializer.readPointer();
    Ark_OnPromptEvent data = OnPromptEvent_serializer::read(thisDeserializer);
    synthetic_Callback_Boolean_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID))))};
    call(resourceId, data, continuationResult);
}
void deserializeAndCallSyncCallback_OnPromptEvent_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                          Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnPromptEvent data,
                                  const synthetic_Callback_Boolean_Void continuation)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_CALLBACK_ONPROMPTEVENT_BOOLEAN))));
    Ark_OnPromptEvent data = OnPromptEvent_serializer::read(thisDeserializer);
    synthetic_Callback_Boolean_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID))))};
    callSyncMethod(vmContext, resourceId, data, continuationResult);
}
void deserializeAndCallCallback_OnRefreshAccessedHistoryEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_OnRefreshAccessedHistoryEvent data)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCaller(KIND_CALLBACK_ONREFRESHACCESSEDHISTORYEVENT_VOID))));
    thisDeserializer.readPointer();
    Ark_OnRefreshAccessedHistoryEvent data = OnRefreshAccessedHistoryEvent_serializer::read(thisDeserializer);
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_OnRefreshAccessedHistoryEvent_Void(Ark_VMContext vmContext,
                                                                       KSerializerBuffer thisArray,
                                                                       Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_OnRefreshAccessedHistoryEvent data)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCallerSync(KIND_CALLBACK_ONREFRESHACCESSEDHISTORYEVENT_VOID))));
    Ark_OnRefreshAccessedHistoryEvent data = OnRefreshAccessedHistoryEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_OnRenderExitedEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_OnRenderExitedEvent data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_ONRENDEREXITEDEVENT_VOID))));
    thisDeserializer.readPointer();
    Ark_OnRenderExitedEvent data = OnRenderExitedEvent_serializer::read(thisDeserializer);
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_OnRenderExitedEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                             Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_OnRenderExitedEvent data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_ONRENDEREXITEDEVENT_VOID))));
    Ark_OnRenderExitedEvent data = OnRenderExitedEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_OnResourceLoadEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_OnResourceLoadEvent data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_ONRESOURCELOADEVENT_VOID))));
    thisDeserializer.readPointer();
    Ark_OnResourceLoadEvent data = OnResourceLoadEvent_serializer::read(thisDeserializer);
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_OnResourceLoadEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                             Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_OnResourceLoadEvent data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_ONRESOURCELOADEVENT_VOID))));
    Ark_OnResourceLoadEvent data = OnResourceLoadEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_OnScaleChangeEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_OnScaleChangeEvent data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_ONSCALECHANGEEVENT_VOID))));
    thisDeserializer.readPointer();
    Ark_OnScaleChangeEvent data = OnScaleChangeEvent_serializer::read(thisDeserializer);
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_OnScaleChangeEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                            Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_OnScaleChangeEvent data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_ONSCALECHANGEEVENT_VOID))));
    Ark_OnScaleChangeEvent data = OnScaleChangeEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_OnScreenCaptureRequestEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_OnScreenCaptureRequestEvent data)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCaller(KIND_CALLBACK_ONSCREENCAPTUREREQUESTEVENT_VOID))));
    thisDeserializer.readPointer();
    Ark_OnScreenCaptureRequestEvent data = OnScreenCaptureRequestEvent_serializer::read(thisDeserializer);
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_OnScreenCaptureRequestEvent_Void(Ark_VMContext vmContext,
                                                                     KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_OnScreenCaptureRequestEvent data)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCallerSync(KIND_CALLBACK_ONSCREENCAPTUREREQUESTEVENT_VOID))));
    Ark_OnScreenCaptureRequestEvent data = OnScreenCaptureRequestEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_OnScrollEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_OnScrollEvent data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_ONSCROLLEVENT_VOID))));
    thisDeserializer.readPointer();
    Ark_OnScrollEvent data = OnScrollEvent_serializer::read(thisDeserializer);
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_OnScrollEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                       Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnScrollEvent data)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_ONSCROLLEVENT_VOID))));
    Ark_OnScrollEvent data = OnScrollEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_OnScrollFrameBeginHandlerResult_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_OnScrollFrameBeginHandlerResult value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCaller(KIND_CALLBACK_ONSCROLLFRAMEBEGINHANDLERRESULT_VOID))));
    thisDeserializer.readPointer();
    Ark_OnScrollFrameBeginHandlerResult value = OnScrollFrameBeginHandlerResult_serializer::read(thisDeserializer);
    call(resourceId, value);
}
void deserializeAndCallSyncCallback_OnScrollFrameBeginHandlerResult_Void(Ark_VMContext vmContext,
                                                                         KSerializerBuffer thisArray,
                                                                         Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_OnScrollFrameBeginHandlerResult value)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCallerSync(KIND_CALLBACK_ONSCROLLFRAMEBEGINHANDLERRESULT_VOID))));
    Ark_OnScrollFrameBeginHandlerResult value = OnScrollFrameBeginHandlerResult_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallCallback_OnSearchResultReceiveEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_OnSearchResultReceiveEvent data)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCaller(KIND_CALLBACK_ONSEARCHRESULTRECEIVEEVENT_VOID))));
    thisDeserializer.readPointer();
    Ark_OnSearchResultReceiveEvent data = OnSearchResultReceiveEvent_serializer::read(thisDeserializer);
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_OnSearchResultReceiveEvent_Void(Ark_VMContext vmContext,
                                                                    KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_OnSearchResultReceiveEvent data)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCallerSync(KIND_CALLBACK_ONSEARCHRESULTRECEIVEEVENT_VOID))));
    Ark_OnSearchResultReceiveEvent data = OnSearchResultReceiveEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_OnShowFileSelectorEvent_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_OnShowFileSelectorEvent data,
                                                const synthetic_Callback_Boolean_Void continuation)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCaller(KIND_CALLBACK_ONSHOWFILESELECTOREVENT_BOOLEAN))));
    thisDeserializer.readPointer();
    Ark_OnShowFileSelectorEvent data = OnShowFileSelectorEvent_serializer::read(thisDeserializer);
    synthetic_Callback_Boolean_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID))))};
    call(resourceId, data, continuationResult);
}
void deserializeAndCallSyncCallback_OnShowFileSelectorEvent_Boolean(Ark_VMContext vmContext,
                                                                    KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_OnShowFileSelectorEvent data,
                                                          const synthetic_Callback_Boolean_Void continuation)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCallerSync(KIND_CALLBACK_ONSHOWFILESELECTOREVENT_BOOLEAN))));
    Ark_OnShowFileSelectorEvent data = OnShowFileSelectorEvent_serializer::read(thisDeserializer);
    synthetic_Callback_Boolean_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID))))};
    callSyncMethod(vmContext, resourceId, data, continuationResult);
}
void deserializeAndCallCallback_OnSslErrorEventReceiveEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_OnSslErrorEventReceiveEvent data)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCaller(KIND_CALLBACK_ONSSLERROREVENTRECEIVEEVENT_VOID))));
    thisDeserializer.readPointer();
    Ark_OnSslErrorEventReceiveEvent data = OnSslErrorEventReceiveEvent_serializer::read(thisDeserializer);
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_OnSslErrorEventReceiveEvent_Void(Ark_VMContext vmContext,
                                                                     KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_OnSslErrorEventReceiveEvent data)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCallerSync(KIND_CALLBACK_ONSSLERROREVENTRECEIVEEVENT_VOID))));
    Ark_OnSslErrorEventReceiveEvent data = OnSslErrorEventReceiveEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_OnTitleReceiveEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_OnTitleReceiveEvent data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_ONTITLERECEIVEEVENT_VOID))));
    thisDeserializer.readPointer();
    Ark_OnTitleReceiveEvent data = OnTitleReceiveEvent_serializer::read(thisDeserializer);
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_OnTitleReceiveEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                             Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_OnTitleReceiveEvent data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_ONTITLERECEIVEEVENT_VOID))));
    Ark_OnTitleReceiveEvent data = OnTitleReceiveEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_OnTouchIconUrlReceivedEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_OnTouchIconUrlReceivedEvent data)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCaller(KIND_CALLBACK_ONTOUCHICONURLRECEIVEDEVENT_VOID))));
    thisDeserializer.readPointer();
    Ark_OnTouchIconUrlReceivedEvent data = OnTouchIconUrlReceivedEvent_serializer::read(thisDeserializer);
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_OnTouchIconUrlReceivedEvent_Void(Ark_VMContext vmContext,
                                                                     KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_OnTouchIconUrlReceivedEvent data)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCallerSync(KIND_CALLBACK_ONTOUCHICONURLRECEIVEDEVENT_VOID))));
    Ark_OnTouchIconUrlReceivedEvent data = OnTouchIconUrlReceivedEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_OnWindowNewEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_OnWindowNewEvent data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_ONWINDOWNEWEVENT_VOID))));
    thisDeserializer.readPointer();
    Ark_OnWindowNewEvent data = OnWindowNewEvent_serializer::read(thisDeserializer);
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_OnWindowNewEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                          Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_OnWindowNewEvent data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_ONWINDOWNEWEVENT_VOID))));
    Ark_OnWindowNewEvent data = OnWindowNewEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_Opt_Array_NavDestinationTransition_Void(KSerializerBuffer thisArray,
                                                                        Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Opt_Array_NavDestinationTransition value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCaller(KIND_CALLBACK_OPT_ARRAY_NAVDESTINATIONTRANSITION_VOID))));
    thisDeserializer.readPointer();
    const auto valueTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Array_NavDestinationTransition valueTmpBuf = {};
    valueTmpBuf.tag = valueTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((valueTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        const Ark_Int32 valueTmpBufOptLength = thisDeserializer.readInt32();
        Array_NavDestinationTransition valueTmpBufOpt = {};
        thisDeserializer.resizeArray<std::decay<decltype(valueTmpBufOpt)>::type,
                                     std::decay<decltype(*valueTmpBufOpt.array)>::type>(&valueTmpBufOpt,
                                                                                        valueTmpBufOptLength);
        for (int valueTmpBufOptBufCounterI = 0; valueTmpBufOptBufCounterI < valueTmpBufOptLength;
             valueTmpBufOptBufCounterI++)
        {
            valueTmpBufOpt.array[valueTmpBufOptBufCounterI] = NavDestinationTransition_serializer::read(
                thisDeserializer);
        }
        valueTmpBuf.value = valueTmpBufOpt;
    }
    Opt_Array_NavDestinationTransition value = valueTmpBuf;
    call(resourceId, value);
}
void deserializeAndCallSyncCallback_Opt_Array_NavDestinationTransition_Void(Ark_VMContext vmContext,
                                                                            KSerializerBuffer thisArray,
                                                                            Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Opt_Array_NavDestinationTransition value)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCallerSync(KIND_CALLBACK_OPT_ARRAY_NAVDESTINATIONTRANSITION_VOID))));
    const auto valueTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Array_NavDestinationTransition valueTmpBuf = {};
    valueTmpBuf.tag = valueTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((valueTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        const Ark_Int32 valueTmpBufOptLength = thisDeserializer.readInt32();
        Array_NavDestinationTransition valueTmpBufOpt = {};
        thisDeserializer.resizeArray<std::decay<decltype(valueTmpBufOpt)>::type,
                                     std::decay<decltype(*valueTmpBufOpt.array)>::type>(&valueTmpBufOpt,
                                                                                        valueTmpBufOptLength);
        for (int valueTmpBufOptBufCounterI = 0; valueTmpBufOptBufCounterI < valueTmpBufOptLength;
             valueTmpBufOptBufCounterI++)
        {
            valueTmpBufOpt.array[valueTmpBufOptBufCounterI] = NavDestinationTransition_serializer::read(
                thisDeserializer);
        }
        valueTmpBuf.value = valueTmpBufOpt;
    }
    Opt_Array_NavDestinationTransition value = valueTmpBuf;
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallCallback_Opt_Array_String_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Opt_Array_String error)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_OPT_ARRAY_STRING_VOID))));
    thisDeserializer.readPointer();
    const auto errorTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Array_String errorTmpBuf = {};
    errorTmpBuf.tag = errorTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((errorTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        const Ark_Int32 errorTmpBufOptLength = thisDeserializer.readInt32();
        Array_String errorTmpBufOpt = {};
        thisDeserializer.resizeArray<std::decay<decltype(errorTmpBufOpt)>::type,
                                     std::decay<decltype(*errorTmpBufOpt.array)>::type>(&errorTmpBufOpt,
                                                                                        errorTmpBufOptLength);
        for (int errorTmpBufOptBufCounterI = 0; errorTmpBufOptBufCounterI < errorTmpBufOptLength;
             errorTmpBufOptBufCounterI++)
        {
            errorTmpBufOpt.array[errorTmpBufOptBufCounterI] = static_cast<Ark_String>(thisDeserializer.readString());
        }
        errorTmpBuf.value = errorTmpBufOpt;
    }
    Opt_Array_String error = errorTmpBuf;
    call(resourceId, error);
}
void deserializeAndCallSyncCallback_Opt_Array_String_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                          Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_Array_String error)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_CALLBACK_OPT_ARRAY_STRING_VOID))));
    const auto errorTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Array_String errorTmpBuf = {};
    errorTmpBuf.tag = errorTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((errorTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        const Ark_Int32 errorTmpBufOptLength = thisDeserializer.readInt32();
        Array_String errorTmpBufOpt = {};
        thisDeserializer.resizeArray<std::decay<decltype(errorTmpBufOpt)>::type,
                                     std::decay<decltype(*errorTmpBufOpt.array)>::type>(&errorTmpBufOpt,
                                                                                        errorTmpBufOptLength);
        for (int errorTmpBufOptBufCounterI = 0; errorTmpBufOptBufCounterI < errorTmpBufOptLength;
             errorTmpBufOptBufCounterI++)
        {
            errorTmpBufOpt.array[errorTmpBufOptBufCounterI] = static_cast<Ark_String>(thisDeserializer.readString());
        }
        errorTmpBuf.value = errorTmpBufOpt;
    }
    Opt_Array_String error = errorTmpBuf;
    callSyncMethod(vmContext, resourceId, error);
}
void deserializeAndCallCallback_Opt_CustomNodeBuilder_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Opt_CustomNodeBuilder value)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_OPT_CUSTOMNODEBUILDER_VOID))));
    thisDeserializer.readPointer();
    const auto valueTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_CustomNodeBuilder valueTmpBuf = {};
    valueTmpBuf.tag = valueTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((valueTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        valueTmpBuf.value = {
            thisDeserializer.readCallbackResource(),
            reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_NativePointer parentNode,
                                      const Callback_Pointer_Void continuation)>(
                thisDeserializer.readPointerOrDefault(
                    reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CUSTOMNODEBUILDER)))),
            reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                      const Ark_NativePointer parentNode, const Callback_Pointer_Void continuation)>(
                thisDeserializer.readPointerOrDefault(
                    reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CUSTOMNODEBUILDER))))};
    }
    Opt_CustomNodeBuilder value = valueTmpBuf;
    call(resourceId, value);
}
void deserializeAndCallSyncCallback_Opt_CustomNodeBuilder_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                               Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Opt_CustomNodeBuilder value)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCallerSync(KIND_CALLBACK_OPT_CUSTOMNODEBUILDER_VOID))));
    const auto valueTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_CustomNodeBuilder valueTmpBuf = {};
    valueTmpBuf.tag = valueTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((valueTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        valueTmpBuf.value = {
            thisDeserializer.readCallbackResource(),
            reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_NativePointer parentNode,
                                      const Callback_Pointer_Void continuation)>(
                thisDeserializer.readPointerOrDefault(
                    reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CUSTOMNODEBUILDER)))),
            reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                      const Ark_NativePointer parentNode, const Callback_Pointer_Void continuation)>(
                thisDeserializer.readPointerOrDefault(
                    reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CUSTOMNODEBUILDER))))};
    }
    Opt_CustomNodeBuilder value = valueTmpBuf;
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallCallback_Opt_NavigationAnimatedTransition_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Opt_NavigationAnimatedTransition value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCaller(KIND_CALLBACK_OPT_NAVIGATIONANIMATEDTRANSITION_VOID))));
    thisDeserializer.readPointer();
    const auto valueTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_NavigationAnimatedTransition valueTmpBuf = {};
    valueTmpBuf.tag = valueTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((valueTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        valueTmpBuf.value = NavigationAnimatedTransition_serializer::read(thisDeserializer);
    }
    Opt_NavigationAnimatedTransition value = valueTmpBuf;
    call(resourceId, value);
}
void deserializeAndCallSyncCallback_Opt_NavigationAnimatedTransition_Void(Ark_VMContext vmContext,
                                                                          KSerializerBuffer thisArray,
                                                                          Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Opt_NavigationAnimatedTransition value)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCallerSync(KIND_CALLBACK_OPT_NAVIGATIONANIMATEDTRANSITION_VOID))));
    const auto valueTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_NavigationAnimatedTransition valueTmpBuf = {};
    valueTmpBuf.tag = valueTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((valueTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        valueTmpBuf.value = NavigationAnimatedTransition_serializer::read(thisDeserializer);
    }
    Opt_NavigationAnimatedTransition value = valueTmpBuf;
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallCallback_Opt_Object_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Opt_Object data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_OPT_OBJECT_VOID))));
    thisDeserializer.readPointer();
    const auto dataTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Object dataTmpBuf = {};
    dataTmpBuf.tag = dataTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((dataTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        dataTmpBuf.value = static_cast<Ark_Object>(thisDeserializer.readObject());
    }
    Opt_Object data = dataTmpBuf;
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_Opt_Object_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                    Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_Object data)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_OPT_OBJECT_VOID))));
    const auto dataTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Object dataTmpBuf = {};
    dataTmpBuf.tag = dataTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((dataTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        dataTmpBuf.value = static_cast<Ark_Object>(thisDeserializer.readObject());
    }
    Opt_Object data = dataTmpBuf;
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_Opt_OffsetResult_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Opt_OffsetResult value)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_OPT_OFFSETRESULT_VOID))));
    thisDeserializer.readPointer();
    const auto valueTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_OffsetResult valueTmpBuf = {};
    valueTmpBuf.tag = valueTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((valueTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        valueTmpBuf.value = OffsetResult_serializer::read(thisDeserializer);
    }
    Opt_OffsetResult value = valueTmpBuf;
    call(resourceId, value);
}
void deserializeAndCallSyncCallback_Opt_OffsetResult_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                          Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_OffsetResult value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_CALLBACK_OPT_OFFSETRESULT_VOID))));
    const auto valueTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_OffsetResult valueTmpBuf = {};
    valueTmpBuf.tag = valueTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((valueTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        valueTmpBuf.value = OffsetResult_serializer::read(thisDeserializer);
    }
    Opt_OffsetResult value = valueTmpBuf;
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallCallback_Opt_ScrollResult_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Opt_ScrollResult value)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_OPT_SCROLLRESULT_VOID))));
    thisDeserializer.readPointer();
    const auto valueTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_ScrollResult valueTmpBuf = {};
    valueTmpBuf.tag = valueTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((valueTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        valueTmpBuf.value = static_cast<Ark_ScrollResult>(ScrollResult_serializer::read(thisDeserializer));
    }
    Opt_ScrollResult value = valueTmpBuf;
    call(resourceId, value);
}
void deserializeAndCallSyncCallback_Opt_ScrollResult_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                          Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_ScrollResult value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_CALLBACK_OPT_SCROLLRESULT_VOID))));
    const auto valueTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_ScrollResult valueTmpBuf = {};
    valueTmpBuf.tag = valueTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((valueTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        valueTmpBuf.value = static_cast<Ark_ScrollResult>(ScrollResult_serializer::read(thisDeserializer));
    }
    Opt_ScrollResult value = valueTmpBuf;
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallCallback_Opt_StyledString_Opt_Array_String_Void(KSerializerBuffer thisArray,
                                                                       Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Opt_StyledString value,
                                                const Opt_Array_String error)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCaller(KIND_CALLBACK_OPT_STYLEDSTRING_OPT_ARRAY_STRING_VOID))));
    thisDeserializer.readPointer();
    const auto valueTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_StyledString valueTmpBuf = {};
    valueTmpBuf.tag = valueTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((valueTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        valueTmpBuf.value = static_cast<Ark_StyledString>(StyledString_serializer::read(thisDeserializer));
    }
    Opt_StyledString value = valueTmpBuf;
    const auto errorTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Array_String errorTmpBuf = {};
    errorTmpBuf.tag = errorTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((errorTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        const Ark_Int32 errorTmpBufOptLength = thisDeserializer.readInt32();
        Array_String errorTmpBufOpt = {};
        thisDeserializer.resizeArray<std::decay<decltype(errorTmpBufOpt)>::type,
                                     std::decay<decltype(*errorTmpBufOpt.array)>::type>(&errorTmpBufOpt,
                                                                                        errorTmpBufOptLength);
        for (int errorTmpBufOptBufCounterI = 0; errorTmpBufOptBufCounterI < errorTmpBufOptLength;
             errorTmpBufOptBufCounterI++)
        {
            errorTmpBufOpt.array[errorTmpBufOptBufCounterI] = static_cast<Ark_String>(thisDeserializer.readString());
        }
        errorTmpBuf.value = errorTmpBufOpt;
    }
    Opt_Array_String error = errorTmpBuf;
    call(resourceId, value, error);
}
void deserializeAndCallSyncCallback_Opt_StyledString_Opt_Array_String_Void(Ark_VMContext vmContext,
                                                                           KSerializerBuffer thisArray,
                                                                           Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Opt_StyledString value, const Opt_Array_String error)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCallerSync(KIND_CALLBACK_OPT_STYLEDSTRING_OPT_ARRAY_STRING_VOID))));
    const auto valueTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_StyledString valueTmpBuf = {};
    valueTmpBuf.tag = valueTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((valueTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        valueTmpBuf.value = static_cast<Ark_StyledString>(StyledString_serializer::read(thisDeserializer));
    }
    Opt_StyledString value = valueTmpBuf;
    const auto errorTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Array_String errorTmpBuf = {};
    errorTmpBuf.tag = errorTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((errorTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        const Ark_Int32 errorTmpBufOptLength = thisDeserializer.readInt32();
        Array_String errorTmpBufOpt = {};
        thisDeserializer.resizeArray<std::decay<decltype(errorTmpBufOpt)>::type,
                                     std::decay<decltype(*errorTmpBufOpt.array)>::type>(&errorTmpBufOpt,
                                                                                        errorTmpBufOptLength);
        for (int errorTmpBufOptBufCounterI = 0; errorTmpBufOptBufCounterI < errorTmpBufOptLength;
             errorTmpBufOptBufCounterI++)
        {
            errorTmpBufOpt.array[errorTmpBufOptBufCounterI] = static_cast<Ark_String>(thisDeserializer.readString());
        }
        errorTmpBuf.value = errorTmpBufOpt;
    }
    Opt_Array_String error = errorTmpBuf;
    callSyncMethod(vmContext, resourceId, value, error);
}
void deserializeAndCallCallback_Opt_TabContentAnimatedTransition_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Opt_TabContentAnimatedTransition value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCaller(KIND_CALLBACK_OPT_TABCONTENTANIMATEDTRANSITION_VOID))));
    thisDeserializer.readPointer();
    const auto valueTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_TabContentAnimatedTransition valueTmpBuf = {};
    valueTmpBuf.tag = valueTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((valueTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        valueTmpBuf.value = TabContentAnimatedTransition_serializer::read(thisDeserializer);
    }
    Opt_TabContentAnimatedTransition value = valueTmpBuf;
    call(resourceId, value);
}
void deserializeAndCallSyncCallback_Opt_TabContentAnimatedTransition_Void(Ark_VMContext vmContext,
                                                                          KSerializerBuffer thisArray,
                                                                          Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Opt_TabContentAnimatedTransition value)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCallerSync(KIND_CALLBACK_OPT_TABCONTENTANIMATEDTRANSITION_VOID))));
    const auto valueTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_TabContentAnimatedTransition valueTmpBuf = {};
    valueTmpBuf.tag = valueTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((valueTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        valueTmpBuf.value = TabContentAnimatedTransition_serializer::read(thisDeserializer);
    }
    Opt_TabContentAnimatedTransition value = valueTmpBuf;
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallCallback_Opt_WebResourceResponse_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Opt_WebResourceResponse value)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_OPT_WEBRESOURCERESPONSE_VOID))));
    thisDeserializer.readPointer();
    const auto valueTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_WebResourceResponse valueTmpBuf = {};
    valueTmpBuf.tag = valueTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((valueTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        valueTmpBuf.value = static_cast<Ark_WebResourceResponse>(
            WebResourceResponse_serializer::read(thisDeserializer));
    }
    Opt_WebResourceResponse value = valueTmpBuf;
    call(resourceId, value);
}
void deserializeAndCallSyncCallback_Opt_WebResourceResponse_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                                 Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Opt_WebResourceResponse value)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCallerSync(KIND_CALLBACK_OPT_WEBRESOURCERESPONSE_VOID))));
    const auto valueTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_WebResourceResponse valueTmpBuf = {};
    valueTmpBuf.tag = valueTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((valueTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        valueTmpBuf.value = static_cast<Ark_WebResourceResponse>(
            WebResourceResponse_serializer::read(thisDeserializer));
    }
    Opt_WebResourceResponse value = valueTmpBuf;
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallCallback_PlaybackInfo_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_PlaybackInfo data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_PLAYBACKINFO_VOID))));
    thisDeserializer.readPointer();
    Ark_PlaybackInfo data = PlaybackInfo_serializer::read(thisDeserializer);
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_PlaybackInfo_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                      Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_PlaybackInfo data)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_PLAYBACKINFO_VOID))));
    Ark_PlaybackInfo data = PlaybackInfo_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_Pointer_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_POINTER_VOID))));
    thisDeserializer.readPointer();
    Ark_NativePointer value = thisDeserializer.readPointer();
    call(resourceId, value);
}
void deserializeAndCallSyncCallback_Pointer_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                 Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_POINTER_VOID))));
    Ark_NativePointer value = thisDeserializer.readPointer();
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallCallback_PopInfo_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_PopInfo data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_POPINFO_VOID))));
    thisDeserializer.readPointer();
    Ark_PopInfo data = PopInfo_serializer::read(thisDeserializer);
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_PopInfo_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                 Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_PopInfo data)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_POPINFO_VOID))));
    Ark_PopInfo data = PopInfo_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_PreDragStatus_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, Ark_PreDragStatus data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_PREDRAGSTATUS_VOID))));
    thisDeserializer.readPointer();
    Ark_PreDragStatus data = static_cast<Ark_PreDragStatus>(thisDeserializer.readInt32());
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_PreDragStatus_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                       Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_PreDragStatus data)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_PREDRAGSTATUS_VOID))));
    Ark_PreDragStatus data = static_cast<Ark_PreDragStatus>(thisDeserializer.readInt32());
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_PreparedInfo_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_PreparedInfo data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_PREPAREDINFO_VOID))));
    thisDeserializer.readPointer();
    Ark_PreparedInfo data = PreparedInfo_serializer::read(thisDeserializer);
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_PreparedInfo_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                      Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_PreparedInfo data)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_PREPAREDINFO_VOID))));
    Ark_PreparedInfo data = PreparedInfo_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_RangeUpdate(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Int32 start, const Ark_Int32 end,
                                  const Ark_Int32 cacheStart, const Ark_Int32 cacheEnd, const Ark_Boolean isLoop)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_RANGEUPDATE))));
    thisDeserializer.readPointer();
    Ark_Int32 start = thisDeserializer.readInt32();
    Ark_Int32 end = thisDeserializer.readInt32();
    Ark_Int32 cacheStart = thisDeserializer.readInt32();
    Ark_Int32 cacheEnd = thisDeserializer.readInt32();
    Ark_Boolean isLoop = thisDeserializer.readBoolean();
    call(resourceId, start, end, cacheStart, cacheEnd, isLoop);
}
void deserializeAndCallSyncCallback_RangeUpdate(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<
        void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int32 start, const Ark_Int32 end,
                 const Ark_Int32 cacheStart, const Ark_Int32 cacheEnd, const Ark_Boolean isLoop)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_RANGEUPDATE))));
    Ark_Int32 start = thisDeserializer.readInt32();
    Ark_Int32 end = thisDeserializer.readInt32();
    Ark_Int32 cacheStart = thisDeserializer.readInt32();
    Ark_Int32 cacheEnd = thisDeserializer.readInt32();
    Ark_Boolean isLoop = thisDeserializer.readBoolean();
    callSyncMethod(vmContext, resourceId, start, end, cacheStart, cacheEnd, isLoop);
}
void deserializeAndCallCallback_RefreshStatus_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, Ark_RefreshStatus state)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_REFRESHSTATUS_VOID))));
    thisDeserializer.readPointer();
    Ark_RefreshStatus state = static_cast<Ark_RefreshStatus>(thisDeserializer.readInt32());
    call(resourceId, state);
}
void deserializeAndCallSyncCallback_RefreshStatus_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                       Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_RefreshStatus state)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_REFRESHSTATUS_VOID))));
    Ark_RefreshStatus state = static_cast<Ark_RefreshStatus>(thisDeserializer.readInt32());
    callSyncMethod(vmContext, resourceId, state);
}
void deserializeAndCallCallback_Resource_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Resource data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_RESOURCE_VOID))));
    thisDeserializer.readPointer();
    Ark_Resource data = Resource_serializer::read(thisDeserializer);
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_Resource_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                  Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Resource data)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_RESOURCE_VOID))));
    Ark_Resource data = Resource_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_ResourceStr_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_ResourceStr data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_RESOURCESTR_VOID))));
    thisDeserializer.readPointer();
    const Ark_Int8 dataTmpBufUnionSelector = thisDeserializer.readInt8();
    Ark_ResourceStr dataTmpBuf = {};
    dataTmpBuf.selector = dataTmpBufUnionSelector;
    if (dataTmpBufUnionSelector == 0)
    {
        dataTmpBuf.selector = 0;
        dataTmpBuf.value0 = static_cast<Ark_String>(thisDeserializer.readString());
    }
    else if (dataTmpBufUnionSelector == 1)
    {
        dataTmpBuf.selector = 1;
        dataTmpBuf.value1 = Resource_serializer::read(thisDeserializer);
    }
    else
    {
        INTEROP_FATAL("One of the branches for dataTmpBuf has to be chosen through deserialisation.");
    }
    Ark_ResourceStr data = static_cast<Ark_ResourceStr>(dataTmpBuf);
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_ResourceStr_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                     Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_ResourceStr data)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_RESOURCESTR_VOID))));
    const Ark_Int8 dataTmpBufUnionSelector = thisDeserializer.readInt8();
    Ark_ResourceStr dataTmpBuf = {};
    dataTmpBuf.selector = dataTmpBufUnionSelector;
    if (dataTmpBufUnionSelector == 0)
    {
        dataTmpBuf.selector = 0;
        dataTmpBuf.value0 = static_cast<Ark_String>(thisDeserializer.readString());
    }
    else if (dataTmpBufUnionSelector == 1)
    {
        dataTmpBuf.selector = 1;
        dataTmpBuf.value1 = Resource_serializer::read(thisDeserializer);
    }
    else
    {
        INTEROP_FATAL("One of the branches for dataTmpBuf has to be chosen through deserialisation.");
    }
    Ark_ResourceStr data = static_cast<Ark_ResourceStr>(dataTmpBuf);
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_RichEditorChangeValue_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_RichEditorChangeValue data,
                                                const synthetic_Callback_Boolean_Void continuation)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCaller(KIND_CALLBACK_RICHEDITORCHANGEVALUE_BOOLEAN))));
    thisDeserializer.readPointer();
    Ark_RichEditorChangeValue data = RichEditorChangeValue_serializer::read(thisDeserializer);
    synthetic_Callback_Boolean_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID))))};
    call(resourceId, data, continuationResult);
}
void deserializeAndCallSyncCallback_RichEditorChangeValue_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                                  Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_RichEditorChangeValue data,
                                                          const synthetic_Callback_Boolean_Void continuation)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCallerSync(KIND_CALLBACK_RICHEDITORCHANGEVALUE_BOOLEAN))));
    Ark_RichEditorChangeValue data = RichEditorChangeValue_serializer::read(thisDeserializer);
    synthetic_Callback_Boolean_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID))))};
    callSyncMethod(vmContext, resourceId, data, continuationResult);
}
void deserializeAndCallCallback_RichEditorDeleteValue_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_RichEditorDeleteValue data,
                                                const synthetic_Callback_Boolean_Void continuation)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCaller(KIND_CALLBACK_RICHEDITORDELETEVALUE_BOOLEAN))));
    thisDeserializer.readPointer();
    Ark_RichEditorDeleteValue data = RichEditorDeleteValue_serializer::read(thisDeserializer);
    synthetic_Callback_Boolean_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID))))};
    call(resourceId, data, continuationResult);
}
void deserializeAndCallSyncCallback_RichEditorDeleteValue_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                                  Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_RichEditorDeleteValue data,
                                                          const synthetic_Callback_Boolean_Void continuation)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCallerSync(KIND_CALLBACK_RICHEDITORDELETEVALUE_BOOLEAN))));
    Ark_RichEditorDeleteValue data = RichEditorDeleteValue_serializer::read(thisDeserializer);
    synthetic_Callback_Boolean_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID))))};
    callSyncMethod(vmContext, resourceId, data, continuationResult);
}
void deserializeAndCallCallback_RichEditorInsertValue_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_RichEditorInsertValue data,
                                                const synthetic_Callback_Boolean_Void continuation)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCaller(KIND_CALLBACK_RICHEDITORINSERTVALUE_BOOLEAN))));
    thisDeserializer.readPointer();
    Ark_RichEditorInsertValue data = RichEditorInsertValue_serializer::read(thisDeserializer);
    synthetic_Callback_Boolean_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID))))};
    call(resourceId, data, continuationResult);
}
void deserializeAndCallSyncCallback_RichEditorInsertValue_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                                  Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_RichEditorInsertValue data,
                                                          const synthetic_Callback_Boolean_Void continuation)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCallerSync(KIND_CALLBACK_RICHEDITORINSERTVALUE_BOOLEAN))));
    Ark_RichEditorInsertValue data = RichEditorInsertValue_serializer::read(thisDeserializer);
    synthetic_Callback_Boolean_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID))))};
    callSyncMethod(vmContext, resourceId, data, continuationResult);
}
void deserializeAndCallCallback_RichEditorRange_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_RichEditorRange data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_RICHEDITORRANGE_VOID))));
    thisDeserializer.readPointer();
    Ark_RichEditorRange data = RichEditorRange_serializer::read(thisDeserializer);
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_RichEditorRange_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                         Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_RichEditorRange data)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_RICHEDITORRANGE_VOID))));
    Ark_RichEditorRange data = RichEditorRange_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_RichEditorSelection_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_RichEditorSelection data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_RICHEDITORSELECTION_VOID))));
    thisDeserializer.readPointer();
    Ark_RichEditorSelection data = RichEditorSelection_serializer::read(thisDeserializer);
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_RichEditorSelection_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                             Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_RichEditorSelection data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_RICHEDITORSELECTION_VOID))));
    Ark_RichEditorSelection data = RichEditorSelection_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_RichEditorTextSpanResult_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_RichEditorTextSpanResult data)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCaller(KIND_CALLBACK_RICHEDITORTEXTSPANRESULT_VOID))));
    thisDeserializer.readPointer();
    Ark_RichEditorTextSpanResult data = RichEditorTextSpanResult_serializer::read(thisDeserializer);
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_RichEditorTextSpanResult_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                                  Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_RichEditorTextSpanResult data)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCallerSync(KIND_CALLBACK_RICHEDITORTEXTSPANRESULT_VOID))));
    Ark_RichEditorTextSpanResult data = RichEditorTextSpanResult_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_SheetDismiss_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_SheetDismiss sheetDismiss)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_SHEETDISMISS_VOID))));
    thisDeserializer.readPointer();
    Ark_SheetDismiss sheetDismiss = SheetDismiss_serializer::read(thisDeserializer);
    call(resourceId, sheetDismiss);
}
void deserializeAndCallSyncCallback_SheetDismiss_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                      Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_SheetDismiss sheetDismiss)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_SHEETDISMISS_VOID))));
    Ark_SheetDismiss sheetDismiss = SheetDismiss_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, sheetDismiss);
}
void deserializeAndCallCallback_SheetType_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, Ark_SheetType data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_SHEETTYPE_VOID))));
    thisDeserializer.readPointer();
    Ark_SheetType data = static_cast<Ark_SheetType>(thisDeserializer.readInt32());
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_SheetType_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                   Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_SheetType data)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_SHEETTYPE_VOID))));
    Ark_SheetType data = static_cast<Ark_SheetType>(thisDeserializer.readInt32());
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_Size_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Size size)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_SIZE_VOID))));
    thisDeserializer.readPointer();
    Ark_Size size = Size_serializer::read(thisDeserializer);
    call(resourceId, size);
}
void deserializeAndCallSyncCallback_Size_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                              Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Size size)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_SIZE_VOID))));
    Ark_Size size = Size_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, size);
}
void deserializeAndCallCallback_SizeResult_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_SizeResult value)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_SIZERESULT_VOID))));
    thisDeserializer.readPointer();
    Ark_SizeResult value = SizeResult_serializer::read(thisDeserializer);
    call(resourceId, value);
}
void deserializeAndCallSyncCallback_SizeResult_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                    Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_SizeResult value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_SIZERESULT_VOID))));
    Ark_SizeResult value = SizeResult_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallCallback_SpringBackAction_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_SpringBackAction data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_SPRINGBACKACTION_VOID))));
    thisDeserializer.readPointer();
    Ark_SpringBackAction data = static_cast<Ark_SpringBackAction>(SpringBackAction_serializer::read(thisDeserializer));
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_SpringBackAction_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                          Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_SpringBackAction data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_SPRINGBACKACTION_VOID))));
    Ark_SpringBackAction data = static_cast<Ark_SpringBackAction>(SpringBackAction_serializer::read(thisDeserializer));
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_StateStylesChange(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Int32 currentState)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_STATESTYLESCHANGE))));
    thisDeserializer.readPointer();
    Ark_Int32 currentState = thisDeserializer.readInt32();
    call(resourceId, currentState);
}
void deserializeAndCallSyncCallback_StateStylesChange(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                      Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int32 currentState)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_STATESTYLESCHANGE))));
    Ark_Int32 currentState = thisDeserializer.readInt32();
    callSyncMethod(vmContext, resourceId, currentState);
}
void deserializeAndCallCallback_String(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_String data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_STRING))));
    thisDeserializer.readPointer();
    Ark_String data = static_cast<Ark_String>(thisDeserializer.readString());
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_String(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_String data)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_STRING))));
    Ark_String data = static_cast<Ark_String>(thisDeserializer.readString());
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_String_PasteEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_String value, const Ark_PasteEvent event)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_STRING_PASTEEVENT_VOID))));
    thisDeserializer.readPointer();
    Ark_String value = static_cast<Ark_String>(thisDeserializer.readString());
    Ark_PasteEvent event = static_cast<Ark_PasteEvent>(PasteEvent_serializer::read(thisDeserializer));
    call(resourceId, value, event);
}
void deserializeAndCallSyncCallback_String_PasteEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                           Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_String value, const Ark_PasteEvent event)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_STRING_PASTEEVENT_VOID))));
    Ark_String value = static_cast<Ark_String>(thisDeserializer.readString());
    Ark_PasteEvent event = static_cast<Ark_PasteEvent>(PasteEvent_serializer::read(thisDeserializer));
    callSyncMethod(vmContext, resourceId, value, event);
}
void deserializeAndCallCallback_String_SurfaceRect_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_String surfaceId, const Ark_SurfaceRect rect)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_STRING_SURFACERECT_VOID))));
    thisDeserializer.readPointer();
    Ark_String surfaceId = static_cast<Ark_String>(thisDeserializer.readString());
    Ark_SurfaceRect rect = SurfaceRect_serializer::read(thisDeserializer);
    call(resourceId, surfaceId, rect);
}
void deserializeAndCallSyncCallback_String_SurfaceRect_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                            Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_String surfaceId, const Ark_SurfaceRect rect)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_STRING_SURFACERECT_VOID))));
    Ark_String surfaceId = static_cast<Ark_String>(thisDeserializer.readString());
    Ark_SurfaceRect rect = SurfaceRect_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, surfaceId, rect);
}
void deserializeAndCallCallback_String_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_String data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_STRING_VOID))));
    thisDeserializer.readPointer();
    Ark_String data = static_cast<Ark_String>(thisDeserializer.readString());
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_String_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_String data)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_STRING_VOID))));
    Ark_String data = static_cast<Ark_String>(thisDeserializer.readString());
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_StyledStringChangeValue_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_StyledStringChangeValue data,
                                                const synthetic_Callback_Boolean_Void continuation)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCaller(KIND_CALLBACK_STYLEDSTRINGCHANGEVALUE_BOOLEAN))));
    thisDeserializer.readPointer();
    Ark_StyledStringChangeValue data = StyledStringChangeValue_serializer::read(thisDeserializer);
    synthetic_Callback_Boolean_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID))))};
    call(resourceId, data, continuationResult);
}
void deserializeAndCallSyncCallback_StyledStringChangeValue_Boolean(Ark_VMContext vmContext,
                                                                    KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_StyledStringChangeValue data,
                                                          const synthetic_Callback_Boolean_Void continuation)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCallerSync(KIND_CALLBACK_STYLEDSTRINGCHANGEVALUE_BOOLEAN))));
    Ark_StyledStringChangeValue data = StyledStringChangeValue_serializer::read(thisDeserializer);
    synthetic_Callback_Boolean_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID))))};
    callSyncMethod(vmContext, resourceId, data, continuationResult);
}
void deserializeAndCallCallback_SwipeActionState_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, Ark_SwipeActionState state)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_SWIPEACTIONSTATE_VOID))));
    thisDeserializer.readPointer();
    Ark_SwipeActionState state = static_cast<Ark_SwipeActionState>(thisDeserializer.readInt32());
    call(resourceId, state);
}
void deserializeAndCallSyncCallback_SwipeActionState_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                          Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_SwipeActionState state)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_CALLBACK_SWIPEACTIONSTATE_VOID))));
    Ark_SwipeActionState state = static_cast<Ark_SwipeActionState>(thisDeserializer.readInt32());
    callSyncMethod(vmContext, resourceId, state);
}
void deserializeAndCallCallback_SwiperContentTransitionProxy_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_SwiperContentTransitionProxy data)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCaller(KIND_CALLBACK_SWIPERCONTENTTRANSITIONPROXY_VOID))));
    thisDeserializer.readPointer();
    Ark_SwiperContentTransitionProxy data = static_cast<Ark_SwiperContentTransitionProxy>(
        SwiperContentTransitionProxy_serializer::read(thisDeserializer));
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_SwiperContentTransitionProxy_Void(Ark_VMContext vmContext,
                                                                      KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_SwiperContentTransitionProxy data)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCallerSync(KIND_CALLBACK_SWIPERCONTENTTRANSITIONPROXY_VOID))));
    Ark_SwiperContentTransitionProxy data = static_cast<Ark_SwiperContentTransitionProxy>(
        SwiperContentTransitionProxy_serializer::read(thisDeserializer));
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_TabContentTransitionProxy_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_TabContentTransitionProxy data)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCaller(KIND_CALLBACK_TABCONTENTTRANSITIONPROXY_VOID))));
    thisDeserializer.readPointer();
    Ark_TabContentTransitionProxy data = static_cast<Ark_TabContentTransitionProxy>(
        TabContentTransitionProxy_serializer::read(thisDeserializer));
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_TabContentTransitionProxy_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                                   Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_TabContentTransitionProxy data)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCallerSync(KIND_CALLBACK_TABCONTENTTRANSITIONPROXY_VOID))));
    Ark_TabContentTransitionProxy data = static_cast<Ark_TabContentTransitionProxy>(
        TabContentTransitionProxy_serializer::read(thisDeserializer));
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_TerminationInfo(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_TerminationInfo data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_TERMINATIONINFO))));
    thisDeserializer.readPointer();
    Ark_TerminationInfo data = TerminationInfo_serializer::read(thisDeserializer);
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_TerminationInfo(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                    Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_TerminationInfo data)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_TERMINATIONINFO))));
    Ark_TerminationInfo data = TerminationInfo_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_TextPickerResult_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_TextPickerResult data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_TEXTPICKERRESULT_VOID))));
    thisDeserializer.readPointer();
    Ark_TextPickerResult data = TextPickerResult_serializer::read(thisDeserializer);
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_TextPickerResult_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                          Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_TextPickerResult data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_TEXTPICKERRESULT_VOID))));
    Ark_TextPickerResult data = TextPickerResult_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_TextRange_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_TextRange data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_TEXTRANGE_VOID))));
    thisDeserializer.readPointer();
    Ark_TextRange data = TextRange_serializer::read(thisDeserializer);
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_TextRange_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                   Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_TextRange data)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_TEXTRANGE_VOID))));
    Ark_TextRange data = TextRange_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_TimePickerResult_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_TimePickerResult data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_TIMEPICKERRESULT_VOID))));
    thisDeserializer.readPointer();
    Ark_TimePickerResult data = TimePickerResult_serializer::read(thisDeserializer);
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_TimePickerResult_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                          Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_TimePickerResult data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_TIMEPICKERRESULT_VOID))));
    Ark_TimePickerResult data = TimePickerResult_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_TouchEvent_HitTestMode(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_TouchEvent data,
                                                const Callback_HitTestMode_Void continuation)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_TOUCHEVENT_HITTESTMODE))));
    thisDeserializer.readPointer();
    Ark_TouchEvent data = static_cast<Ark_TouchEvent>(TouchEvent_serializer::read(thisDeserializer));
    Callback_HitTestMode_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, Ark_HitTestMode value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_HITTESTMODE_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_HitTestMode value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_HITTESTMODE_VOID))))};
    call(resourceId, data, continuationResult);
}
void deserializeAndCallSyncCallback_TouchEvent_HitTestMode(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                           Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_TouchEvent data,
                                  const Callback_HitTestMode_Void continuation)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_CALLBACK_TOUCHEVENT_HITTESTMODE))));
    Ark_TouchEvent data = static_cast<Ark_TouchEvent>(TouchEvent_serializer::read(thisDeserializer));
    Callback_HitTestMode_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, Ark_HitTestMode value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_HITTESTMODE_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_HitTestMode value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_HITTESTMODE_VOID))))};
    callSyncMethod(vmContext, resourceId, data, continuationResult);
}
void deserializeAndCallCallback_TouchEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_TouchEvent event)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_TOUCHEVENT_VOID))));
    thisDeserializer.readPointer();
    Ark_TouchEvent event = static_cast<Ark_TouchEvent>(TouchEvent_serializer::read(thisDeserializer));
    call(resourceId, event);
}
void deserializeAndCallSyncCallback_TouchEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                    Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_TouchEvent event)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_TOUCHEVENT_VOID))));
    Ark_TouchEvent event = static_cast<Ark_TouchEvent>(TouchEvent_serializer::read(thisDeserializer));
    callSyncMethod(vmContext, resourceId, event);
}
void deserializeAndCallCallback_TouchResult_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_TouchResult value)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_TOUCHRESULT_VOID))));
    thisDeserializer.readPointer();
    Ark_TouchResult value = TouchResult_serializer::read(thisDeserializer);
    call(resourceId, value);
}
void deserializeAndCallSyncCallback_TouchResult_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                     Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_TouchResult value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_TOUCHRESULT_VOID))));
    Ark_TouchResult value = TouchResult_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallCallback_Tuple_I32_I32_I32_I32_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Tuple_I32_I32_I32_I32 value)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_TUPLE_I32_I32_I32_I32_VOID))));
    thisDeserializer.readPointer();
    Ark_Tuple_I32_I32_I32_I32 valueTmpBuf = {};
    valueTmpBuf.value0 = thisDeserializer.readInt32();
    valueTmpBuf.value1 = thisDeserializer.readInt32();
    valueTmpBuf.value2 = thisDeserializer.readInt32();
    valueTmpBuf.value3 = thisDeserializer.readInt32();
    Ark_Tuple_I32_I32_I32_I32 value = valueTmpBuf;
    call(resourceId, value);
}
void deserializeAndCallSyncCallback_Tuple_I32_I32_I32_I32_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                               Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_Tuple_I32_I32_I32_I32 value)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCallerSync(KIND_CALLBACK_TUPLE_I32_I32_I32_I32_VOID))));
    Ark_Tuple_I32_I32_I32_I32 valueTmpBuf = {};
    valueTmpBuf.value0 = thisDeserializer.readInt32();
    valueTmpBuf.value1 = thisDeserializer.readInt32();
    valueTmpBuf.value2 = thisDeserializer.readInt32();
    valueTmpBuf.value3 = thisDeserializer.readInt32();
    Ark_Tuple_I32_I32_I32_I32 value = valueTmpBuf;
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallCallback_Tuple_I32_I32_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Tuple_I32_I32 value)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_TUPLE_I32_I32_VOID))));
    thisDeserializer.readPointer();
    Ark_Tuple_I32_I32 valueTmpBuf = {};
    valueTmpBuf.value0 = thisDeserializer.readInt32();
    valueTmpBuf.value1 = thisDeserializer.readInt32();
    Ark_Tuple_I32_I32 value = valueTmpBuf;
    call(resourceId, value);
}
void deserializeAndCallSyncCallback_Tuple_I32_I32_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                       Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Tuple_I32_I32 value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_TUPLE_I32_I32_VOID))));
    Ark_Tuple_I32_I32 valueTmpBuf = {};
    valueTmpBuf.value0 = thisDeserializer.readInt32();
    valueTmpBuf.value1 = thisDeserializer.readInt32();
    Ark_Tuple_I32_I32 value = valueTmpBuf;
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallCallback_UIExtensionProxy(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_UIExtensionProxy data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_UIEXTENSIONPROXY))));
    thisDeserializer.readPointer();
    Ark_UIExtensionProxy data = static_cast<Ark_UIExtensionProxy>(UIExtensionProxy_serializer::read(thisDeserializer));
    call(resourceId, data);
}
void deserializeAndCallSyncCallback_UIExtensionProxy(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                     Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_UIExtensionProxy data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_UIEXTENSIONPROXY))));
    Ark_UIExtensionProxy data = static_cast<Ark_UIExtensionProxy>(UIExtensionProxy_serializer::read(thisDeserializer));
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallCallback_Union_CustomNodeBuilder_DragItemInfo_Void(KSerializerBuffer thisArray,
                                                                          Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Union_CustomNodeBuilder_DragItemInfo value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCaller(KIND_CALLBACK_UNION_CUSTOMNODEBUILDER_DRAGITEMINFO_VOID))));
    thisDeserializer.readPointer();
    const Ark_Int8 valueTmpBufUnionSelector = thisDeserializer.readInt8();
    Ark_Union_CustomNodeBuilder_DragItemInfo valueTmpBuf = {};
    valueTmpBuf.selector = valueTmpBufUnionSelector;
    if (valueTmpBufUnionSelector == 0)
    {
        valueTmpBuf.selector = 0;
        valueTmpBuf.value0 = {
            thisDeserializer.readCallbackResource(),
            reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_NativePointer parentNode,
                                      const Callback_Pointer_Void continuation)>(
                thisDeserializer.readPointerOrDefault(
                    reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CUSTOMNODEBUILDER)))),
            reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                      const Ark_NativePointer parentNode, const Callback_Pointer_Void continuation)>(
                thisDeserializer.readPointerOrDefault(
                    reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CUSTOMNODEBUILDER))))};
    }
    else if (valueTmpBufUnionSelector == 1)
    {
        valueTmpBuf.selector = 1;
        valueTmpBuf.value1 = DragItemInfo_serializer::read(thisDeserializer);
    }
    else
    {
        INTEROP_FATAL("One of the branches for valueTmpBuf has to be chosen through deserialisation.");
    }
    Ark_Union_CustomNodeBuilder_DragItemInfo value = static_cast<Ark_Union_CustomNodeBuilder_DragItemInfo>(valueTmpBuf);
    call(resourceId, value);
}
void deserializeAndCallSyncCallback_Union_CustomNodeBuilder_DragItemInfo_Void(Ark_VMContext vmContext,
                                                                              KSerializerBuffer thisArray,
                                                                              Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_Union_CustomNodeBuilder_DragItemInfo value)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCallerSync(KIND_CALLBACK_UNION_CUSTOMNODEBUILDER_DRAGITEMINFO_VOID))));
    const Ark_Int8 valueTmpBufUnionSelector = thisDeserializer.readInt8();
    Ark_Union_CustomNodeBuilder_DragItemInfo valueTmpBuf = {};
    valueTmpBuf.selector = valueTmpBufUnionSelector;
    if (valueTmpBufUnionSelector == 0)
    {
        valueTmpBuf.selector = 0;
        valueTmpBuf.value0 = {
            thisDeserializer.readCallbackResource(),
            reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_NativePointer parentNode,
                                      const Callback_Pointer_Void continuation)>(
                thisDeserializer.readPointerOrDefault(
                    reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CUSTOMNODEBUILDER)))),
            reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                      const Ark_NativePointer parentNode, const Callback_Pointer_Void continuation)>(
                thisDeserializer.readPointerOrDefault(
                    reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CUSTOMNODEBUILDER))))};
    }
    else if (valueTmpBufUnionSelector == 1)
    {
        valueTmpBuf.selector = 1;
        valueTmpBuf.value1 = DragItemInfo_serializer::read(thisDeserializer);
    }
    else
    {
        INTEROP_FATAL("One of the branches for valueTmpBuf has to be chosen through deserialisation.");
    }
    Ark_Union_CustomNodeBuilder_DragItemInfo value = static_cast<Ark_Union_CustomNodeBuilder_DragItemInfo>(valueTmpBuf);
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallCallback_UserDataSpan_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Object value)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_USERDATASPAN_VOID))));
    thisDeserializer.readPointer();
    Ark_UserDataSpan value = static_cast<Ark_UserDataSpan>(thisDeserializer.readObject());
    call(resourceId, value);
}
void deserializeAndCallSyncCallback_UserDataSpan_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                      Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Object value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_USERDATASPAN_VOID))));
    Ark_UserDataSpan value = static_cast<Ark_UserDataSpan>(thisDeserializer.readObject());
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallCallback_Void_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId)>(thisDeserializer.readPointerOrDefault(
        reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_VOID_VOID))));
    thisDeserializer.readPointer();
    call(resourceId);
}
void deserializeAndCallSyncCallback_Void_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                              Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_VOID_VOID))));
    callSyncMethod(vmContext, resourceId);
}
void deserializeAndCallCallback_WebKeyboardOptions_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_WebKeyboardOptions value)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_WEBKEYBOARDOPTIONS_VOID))));
    thisDeserializer.readPointer();
    Ark_WebKeyboardOptions value = WebKeyboardOptions_serializer::read(thisDeserializer);
    call(resourceId, value);
}
void deserializeAndCallSyncCallback_WebKeyboardOptions_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                            Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_WebKeyboardOptions value)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_WEBKEYBOARDOPTIONS_VOID))));
    Ark_WebKeyboardOptions value = WebKeyboardOptions_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallCheckBoxModifierBuilder(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_NativePointer parentNode,
                                  const Ark_CheckBoxConfiguration config, const Callback_Pointer_Void continuation)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CHECKBOXMODIFIERBUILDER))));
    thisDeserializer.readPointer();
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_CheckBoxConfiguration config = CheckBoxConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_POINTER_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_POINTER_VOID))))};
    call(resourceId, parentNode, config, continuationResult);
}
void deserializeAndCallSyncCheckBoxModifierBuilder(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                   Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<
        void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer parentNode,
                 const Ark_CheckBoxConfiguration config, const Callback_Pointer_Void continuation)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CHECKBOXMODIFIERBUILDER))));
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_CheckBoxConfiguration config = CheckBoxConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_POINTER_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_POINTER_VOID))))};
    callSyncMethod(vmContext, resourceId, parentNode, config, continuationResult);
}
void deserializeAndCallContentDidScrollCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Int32 selectedIndex, const Ark_Int32 index,
                                  const Ark_Float64 position, const Ark_Float64 mainAxisLength)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CONTENTDIDSCROLLCALLBACK))));
    thisDeserializer.readPointer();
    Ark_Int32 selectedIndex = thisDeserializer.readInt32();
    Ark_Int32 index = thisDeserializer.readInt32();
    Ark_Float64 position = thisDeserializer.readFloat64();
    Ark_Float64 mainAxisLength = thisDeserializer.readFloat64();
    call(resourceId, selectedIndex, index, position, mainAxisLength);
}
void deserializeAndCallSyncContentDidScrollCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                    Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int32 selectedIndex,
                                  const Ark_Int32 index, const Ark_Float64 position, const Ark_Float64 mainAxisLength)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CONTENTDIDSCROLLCALLBACK))));
    Ark_Int32 selectedIndex = thisDeserializer.readInt32();
    Ark_Int32 index = thisDeserializer.readInt32();
    Ark_Float64 position = thisDeserializer.readFloat64();
    Ark_Float64 mainAxisLength = thisDeserializer.readFloat64();
    callSyncMethod(vmContext, resourceId, selectedIndex, index, position, mainAxisLength);
}
void deserializeAndCallContentWillScrollCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_SwiperContentWillScrollResult result,
                                  const synthetic_Callback_Boolean_Void continuation)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CONTENTWILLSCROLLCALLBACK))));
    thisDeserializer.readPointer();
    Ark_SwiperContentWillScrollResult result = SwiperContentWillScrollResult_serializer::read(thisDeserializer);
    synthetic_Callback_Boolean_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID))))};
    call(resourceId, result, continuationResult);
}
void deserializeAndCallSyncContentWillScrollCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                     Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_SwiperContentWillScrollResult result,
                                                          const synthetic_Callback_Boolean_Void continuation)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CONTENTWILLSCROLLCALLBACK))));
    Ark_SwiperContentWillScrollResult result = SwiperContentWillScrollResult_serializer::read(thisDeserializer);
    synthetic_Callback_Boolean_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID))))};
    callSyncMethod(vmContext, resourceId, result, continuationResult);
}
void deserializeAndCallCustomNodeBuilder(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_NativePointer parentNode,
                                                const Callback_Pointer_Void continuation)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CUSTOMNODEBUILDER))));
    thisDeserializer.readPointer();
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Callback_Pointer_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_POINTER_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_POINTER_VOID))))};
    call(resourceId, parentNode, continuationResult);
}
void deserializeAndCallSyncCustomNodeBuilder(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                  const Ark_NativePointer parentNode, const Callback_Pointer_Void continuation)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CUSTOMNODEBUILDER))));
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Callback_Pointer_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_POINTER_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_POINTER_VOID))))};
    callSyncMethod(vmContext, resourceId, parentNode, continuationResult);
}
void deserializeAndCallDataPanelModifierBuilder(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_NativePointer parentNode,
                                  const Ark_DataPanelConfiguration config, const Callback_Pointer_Void continuation)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_DATAPANELMODIFIERBUILDER))));
    thisDeserializer.readPointer();
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_DataPanelConfiguration config = DataPanelConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_POINTER_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_POINTER_VOID))))};
    call(resourceId, parentNode, config, continuationResult);
}
void deserializeAndCallSyncDataPanelModifierBuilder(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                    Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<
        void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer parentNode,
                 const Ark_DataPanelConfiguration config, const Callback_Pointer_Void continuation)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_DATAPANELMODIFIERBUILDER))));
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_DataPanelConfiguration config = DataPanelConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_POINTER_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_POINTER_VOID))))};
    callSyncMethod(vmContext, resourceId, parentNode, config, continuationResult);
}
void deserializeAndCallDataProgressListener(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_unifiedDataChannel_ProgressInfo progressInfo,
                                  const Opt_unifiedDataChannel_UnifiedData data)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_DATAPROGRESSLISTENER))));
    thisDeserializer.readPointer();
    Ark_unifiedDataChannel_ProgressInfo progressInfo = unifiedDataChannel_ProgressInfo_serializer::read(
        thisDeserializer);
    const auto dataTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_unifiedDataChannel_UnifiedData dataTmpBuf = {};
    dataTmpBuf.tag = dataTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((dataTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        dataTmpBuf.value = static_cast<Ark_unifiedDataChannel_UnifiedData>(
            unifiedDataChannel_UnifiedData_serializer::read(thisDeserializer));
    }
    Opt_unifiedDataChannel_UnifiedData data = dataTmpBuf;
    call(resourceId, progressInfo, data);
}
void deserializeAndCallSyncDataProgressListener(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_unifiedDataChannel_ProgressInfo progressInfo,
                                                          const Opt_unifiedDataChannel_UnifiedData data)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_DATAPROGRESSLISTENER))));
    Ark_unifiedDataChannel_ProgressInfo progressInfo = unifiedDataChannel_ProgressInfo_serializer::read(
        thisDeserializer);
    const auto dataTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_unifiedDataChannel_UnifiedData dataTmpBuf = {};
    dataTmpBuf.tag = dataTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((dataTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        dataTmpBuf.value = static_cast<Ark_unifiedDataChannel_UnifiedData>(
            unifiedDataChannel_UnifiedData_serializer::read(thisDeserializer));
    }
    Opt_unifiedDataChannel_UnifiedData data = dataTmpBuf;
    callSyncMethod(vmContext, resourceId, progressInfo, data);
}
void deserializeAndCallEditableTextOnChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_String value, const Opt_PreviewText previewText,
                                  const Opt_TextChangeOptions options)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_EDITABLETEXTONCHANGECALLBACK))));
    thisDeserializer.readPointer();
    Ark_String value = static_cast<Ark_String>(thisDeserializer.readString());
    const auto previewTextTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_PreviewText previewTextTmpBuf = {};
    previewTextTmpBuf.tag = previewTextTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED :
                                                                                         INTEROP_TAG_OBJECT;
    if ((previewTextTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        previewTextTmpBuf.value = PreviewText_serializer::read(thisDeserializer);
    }
    Opt_PreviewText previewText = previewTextTmpBuf;
    const auto optionsTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_TextChangeOptions optionsTmpBuf = {};
    optionsTmpBuf.tag = optionsTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED :
                                                                                 INTEROP_TAG_OBJECT;
    if ((optionsTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        optionsTmpBuf.value = TextChangeOptions_serializer::read(thisDeserializer);
    }
    Opt_TextChangeOptions options = optionsTmpBuf;
    call(resourceId, value, previewText, options);
}
void deserializeAndCallSyncEditableTextOnChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                        Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_String value,
                                  const Opt_PreviewText previewText, const Opt_TextChangeOptions options)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_EDITABLETEXTONCHANGECALLBACK))));
    Ark_String value = static_cast<Ark_String>(thisDeserializer.readString());
    const auto previewTextTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_PreviewText previewTextTmpBuf = {};
    previewTextTmpBuf.tag = previewTextTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED :
                                                                                         INTEROP_TAG_OBJECT;
    if ((previewTextTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        previewTextTmpBuf.value = PreviewText_serializer::read(thisDeserializer);
    }
    Opt_PreviewText previewText = previewTextTmpBuf;
    const auto optionsTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_TextChangeOptions optionsTmpBuf = {};
    optionsTmpBuf.tag = optionsTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED :
                                                                                 INTEROP_TAG_OBJECT;
    if ((optionsTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        optionsTmpBuf.value = TextChangeOptions_serializer::read(thisDeserializer);
    }
    Opt_TextChangeOptions options = optionsTmpBuf;
    callSyncMethod(vmContext, resourceId, value, previewText, options);
}
void deserializeAndCallErrorCallback_BusinessErrorInterface_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_BusinessErrorInterface_Void err)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCaller(KIND_ERRORCALLBACK_BUSINESSERRORINTERFACE_VOID))));
    thisDeserializer.readPointer();
    Ark_BusinessErrorInterface_Void err = BusinessErrorInterface_Void_serializer::read(thisDeserializer);
    call(resourceId, err);
}
void deserializeAndCallSyncErrorCallback_BusinessErrorInterface_Void(Ark_VMContext vmContext,
                                                                     KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_BusinessErrorInterface_Void err)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCallerSync(KIND_ERRORCALLBACK_BUSINESSERRORINTERFACE_VOID))));
    Ark_BusinessErrorInterface_Void err = BusinessErrorInterface_Void_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, err);
}
void deserializeAndCallFrameCallbackHandler(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Int64 arg)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_FRAMECALLBACKHANDLER))));
    thisDeserializer.readPointer();
    Ark_Int64 arg = thisDeserializer.readInt64();
    call(resourceId, arg);
}
void deserializeAndCallSyncFrameCallbackHandler(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int64 arg)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_FRAMECALLBACKHANDLER))));
    Ark_Int64 arg = thisDeserializer.readInt64();
    callSyncMethod(vmContext, resourceId, arg);
}
void deserializeAndCallGaugeModifierBuilder(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_NativePointer parentNode,
                                  const Ark_GaugeConfiguration config, const Callback_Pointer_Void continuation)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_GAUGEMODIFIERBUILDER))));
    thisDeserializer.readPointer();
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_GaugeConfiguration config = GaugeConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_POINTER_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_POINTER_VOID))))};
    call(resourceId, parentNode, config, continuationResult);
}
void deserializeAndCallSyncGaugeModifierBuilder(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<
        void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer parentNode,
                 const Ark_GaugeConfiguration config, const Callback_Pointer_Void continuation)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_GAUGEMODIFIERBUILDER))));
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_GaugeConfiguration config = GaugeConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_POINTER_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_POINTER_VOID))))};
    callSyncMethod(vmContext, resourceId, parentNode, config, continuationResult);
}
void deserializeAndCallGestureEventHandler(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_GestureEvent event)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_GESTUREEVENTHANDLER))));
    thisDeserializer.readPointer();
    Ark_GestureEvent event = static_cast<Ark_GestureEvent>(GestureEvent_serializer::read(thisDeserializer));
    call(resourceId, event);
}
void deserializeAndCallSyncGestureEventHandler(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                               Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_GestureEvent event)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_GESTUREEVENTHANDLER))));
    Ark_GestureEvent event = static_cast<Ark_GestureEvent>(GestureEvent_serializer::read(thisDeserializer));
    callSyncMethod(vmContext, resourceId, event);
}
void deserializeAndCallGestureRecognizerJudgeBeginCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<
        void (*)(const Ark_Int32 resourceId, const Ark_BaseGestureEvent event, const Ark_GestureRecognizer current,
                 const Array_GestureRecognizer recognizers, const Opt_Array_TouchRecognizer touchRecognizers,
                 const Callback_GestureJudgeResult_Void continuation)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_GESTURERECOGNIZERJUDGEBEGINCALLBACK))));
    thisDeserializer.readPointer();
    Ark_BaseGestureEvent event = static_cast<Ark_BaseGestureEvent>(BaseGestureEvent_serializer::read(thisDeserializer));
    Ark_GestureRecognizer current = static_cast<Ark_GestureRecognizer>(
        GestureRecognizer_serializer::read(thisDeserializer));
    const Ark_Int32 recognizersTmpBufLength = thisDeserializer.readInt32();
    Array_GestureRecognizer recognizersTmpBuf = {};
    thisDeserializer.resizeArray<std::decay<decltype(recognizersTmpBuf)>::type,
                                 std::decay<decltype(*recognizersTmpBuf.array)>::type>(&recognizersTmpBuf,
                                                                                       recognizersTmpBufLength);
    for (int recognizersTmpBufBufCounterI = 0; recognizersTmpBufBufCounterI < recognizersTmpBufLength;
         recognizersTmpBufBufCounterI++)
    {
        recognizersTmpBuf.array[recognizersTmpBufBufCounterI] = static_cast<Ark_GestureRecognizer>(
            GestureRecognizer_serializer::read(thisDeserializer));
    }
    Array_GestureRecognizer recognizers = recognizersTmpBuf;
    const auto touchRecognizersTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Array_TouchRecognizer touchRecognizersTmpBuf = {};
    touchRecognizersTmpBuf.tag = touchRecognizersTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ?
                                     INTEROP_TAG_UNDEFINED :
                                     INTEROP_TAG_OBJECT;
    if ((touchRecognizersTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        const Ark_Int32 touchRecognizersTmpBufOptLength = thisDeserializer.readInt32();
        Array_TouchRecognizer touchRecognizersTmpBufOpt = {};
        thisDeserializer.resizeArray<std::decay<decltype(touchRecognizersTmpBufOpt)>::type,
                                     std::decay<decltype(*touchRecognizersTmpBufOpt.array)>::type>(
            &touchRecognizersTmpBufOpt, touchRecognizersTmpBufOptLength);
        for (int touchRecognizersTmpBufOptBufCounterI = 0;
             touchRecognizersTmpBufOptBufCounterI < touchRecognizersTmpBufOptLength;
             touchRecognizersTmpBufOptBufCounterI++)
        {
            touchRecognizersTmpBufOpt.array[touchRecognizersTmpBufOptBufCounterI] = static_cast<Ark_TouchRecognizer>(
                TouchRecognizer_serializer::read(thisDeserializer));
        }
        touchRecognizersTmpBuf.value = touchRecognizersTmpBufOpt;
    }
    Opt_Array_TouchRecognizer touchRecognizers = touchRecognizersTmpBuf;
    Callback_GestureJudgeResult_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, Ark_GestureJudgeResult value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_GESTUREJUDGERESULT_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_GestureJudgeResult value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_CALLBACK_GESTUREJUDGERESULT_VOID))))};
    call(resourceId, event, current, recognizers, touchRecognizers, continuationResult);
}
void deserializeAndCallSyncGestureRecognizerJudgeBeginCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                               Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(
        Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_BaseGestureEvent event,
        const Ark_GestureRecognizer current, const Array_GestureRecognizer recognizers,
        const Opt_Array_TouchRecognizer touchRecognizers, const Callback_GestureJudgeResult_Void continuation)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCallerSync(KIND_GESTURERECOGNIZERJUDGEBEGINCALLBACK))));
    Ark_BaseGestureEvent event = static_cast<Ark_BaseGestureEvent>(BaseGestureEvent_serializer::read(thisDeserializer));
    Ark_GestureRecognizer current = static_cast<Ark_GestureRecognizer>(
        GestureRecognizer_serializer::read(thisDeserializer));
    const Ark_Int32 recognizersTmpBufLength = thisDeserializer.readInt32();
    Array_GestureRecognizer recognizersTmpBuf = {};
    thisDeserializer.resizeArray<std::decay<decltype(recognizersTmpBuf)>::type,
                                 std::decay<decltype(*recognizersTmpBuf.array)>::type>(&recognizersTmpBuf,
                                                                                       recognizersTmpBufLength);
    for (int recognizersTmpBufBufCounterI = 0; recognizersTmpBufBufCounterI < recognizersTmpBufLength;
         recognizersTmpBufBufCounterI++)
    {
        recognizersTmpBuf.array[recognizersTmpBufBufCounterI] = static_cast<Ark_GestureRecognizer>(
            GestureRecognizer_serializer::read(thisDeserializer));
    }
    Array_GestureRecognizer recognizers = recognizersTmpBuf;
    const auto touchRecognizersTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Array_TouchRecognizer touchRecognizersTmpBuf = {};
    touchRecognizersTmpBuf.tag = touchRecognizersTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ?
                                     INTEROP_TAG_UNDEFINED :
                                     INTEROP_TAG_OBJECT;
    if ((touchRecognizersTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        const Ark_Int32 touchRecognizersTmpBufOptLength = thisDeserializer.readInt32();
        Array_TouchRecognizer touchRecognizersTmpBufOpt = {};
        thisDeserializer.resizeArray<std::decay<decltype(touchRecognizersTmpBufOpt)>::type,
                                     std::decay<decltype(*touchRecognizersTmpBufOpt.array)>::type>(
            &touchRecognizersTmpBufOpt, touchRecognizersTmpBufOptLength);
        for (int touchRecognizersTmpBufOptBufCounterI = 0;
             touchRecognizersTmpBufOptBufCounterI < touchRecognizersTmpBufOptLength;
             touchRecognizersTmpBufOptBufCounterI++)
        {
            touchRecognizersTmpBufOpt.array[touchRecognizersTmpBufOptBufCounterI] = static_cast<Ark_TouchRecognizer>(
                TouchRecognizer_serializer::read(thisDeserializer));
        }
        touchRecognizersTmpBuf.value = touchRecognizersTmpBufOpt;
    }
    Opt_Array_TouchRecognizer touchRecognizers = touchRecognizersTmpBuf;
    Callback_GestureJudgeResult_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, Ark_GestureJudgeResult value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_GESTUREJUDGERESULT_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_GestureJudgeResult value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_CALLBACK_GESTUREJUDGERESULT_VOID))))};
    callSyncMethod(vmContext, resourceId, event, current, recognizers, touchRecognizers, continuationResult);
}
void deserializeAndCallHoverCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Boolean isHover, const Ark_HoverEvent event)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_HOVERCALLBACK))));
    thisDeserializer.readPointer();
    Ark_Boolean isHover = thisDeserializer.readBoolean();
    Ark_HoverEvent event = static_cast<Ark_HoverEvent>(HoverEvent_serializer::read(thisDeserializer));
    call(resourceId, isHover, event);
}
void deserializeAndCallSyncHoverCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_Boolean isHover, const Ark_HoverEvent event)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_HOVERCALLBACK))));
    Ark_Boolean isHover = thisDeserializer.readBoolean();
    Ark_HoverEvent event = static_cast<Ark_HoverEvent>(HoverEvent_serializer::read(thisDeserializer));
    callSyncMethod(vmContext, resourceId, isHover, event);
}
void deserializeAndCallImageCompleteCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_ImageLoadResult result)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_IMAGECOMPLETECALLBACK))));
    thisDeserializer.readPointer();
    Ark_ImageLoadResult result = ImageLoadResult_serializer::read(thisDeserializer);
    call(resourceId, result);
}
void deserializeAndCallSyncImageCompleteCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                 Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_ImageLoadResult result)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_IMAGECOMPLETECALLBACK))));
    Ark_ImageLoadResult result = ImageLoadResult_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, result);
}
void deserializeAndCallImageErrorCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_ImageError error)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_IMAGEERRORCALLBACK))));
    thisDeserializer.readPointer();
    Ark_ImageError error = ImageError_serializer::read(thisDeserializer);
    call(resourceId, error);
}
void deserializeAndCallSyncImageErrorCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                              Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_ImageError error)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_IMAGEERRORCALLBACK))));
    Ark_ImageError error = ImageError_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, error);
}
void deserializeAndCallImageOnCompleteCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Opt_ImageCompleteEvent loadEvent)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_IMAGEONCOMPLETECALLBACK))));
    thisDeserializer.readPointer();
    const auto loadEventTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_ImageCompleteEvent loadEventTmpBuf = {};
    loadEventTmpBuf.tag = loadEventTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED :
                                                                                     INTEROP_TAG_OBJECT;
    if ((loadEventTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        loadEventTmpBuf.value = ImageCompleteEvent_serializer::read(thisDeserializer);
    }
    Opt_ImageCompleteEvent loadEvent = loadEventTmpBuf;
    call(resourceId, loadEvent);
}
void deserializeAndCallSyncImageOnCompleteCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                   Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Opt_ImageCompleteEvent loadEvent)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_IMAGEONCOMPLETECALLBACK))));
    const auto loadEventTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_ImageCompleteEvent loadEventTmpBuf = {};
    loadEventTmpBuf.tag = loadEventTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED :
                                                                                     INTEROP_TAG_OBJECT;
    if ((loadEventTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        loadEventTmpBuf.value = ImageCompleteEvent_serializer::read(thisDeserializer);
    }
    Opt_ImageCompleteEvent loadEvent = loadEventTmpBuf;
    callSyncMethod(vmContext, resourceId, loadEvent);
}
void deserializeAndCallInterceptionModeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, Ark_NavigationMode mode)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_INTERCEPTIONMODECALLBACK))));
    thisDeserializer.readPointer();
    Ark_NavigationMode mode = static_cast<Ark_NavigationMode>(thisDeserializer.readInt32());
    call(resourceId, mode);
}
void deserializeAndCallSyncInterceptionModeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                    Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_NavigationMode mode)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_INTERCEPTIONMODECALLBACK))));
    Ark_NavigationMode mode = static_cast<Ark_NavigationMode>(thisDeserializer.readInt32());
    callSyncMethod(vmContext, resourceId, mode);
}
void deserializeAndCallInterceptionShowCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Union_NavDestinationContext_String from,
                                  const Ark_Union_NavDestinationContext_String to, Ark_NavigationOperation operation,
                                  const Ark_Boolean isAnimated)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_INTERCEPTIONSHOWCALLBACK))));
    thisDeserializer.readPointer();
    const Ark_Int8 fromTmpBufUnionSelector = thisDeserializer.readInt8();
    Ark_Union_NavDestinationContext_String fromTmpBuf = {};
    fromTmpBuf.selector = fromTmpBufUnionSelector;
    if (fromTmpBufUnionSelector == 0)
    {
        fromTmpBuf.selector = 0;
        fromTmpBuf.value0 = static_cast<Ark_NavDestinationContext>(
            NavDestinationContext_serializer::read(thisDeserializer));
    }
    else if (fromTmpBufUnionSelector == 1)
    {
        fromTmpBuf.selector = 1;
        fromTmpBuf.value1 = static_cast<Ark_String>(thisDeserializer.readString());
    }
    else
    {
        INTEROP_FATAL("One of the branches for fromTmpBuf has to be chosen through deserialisation.");
    }
    Ark_Union_NavDestinationContext_String from = static_cast<Ark_Union_NavDestinationContext_String>(fromTmpBuf);
    const Ark_Int8 toTmpBufUnionSelector = thisDeserializer.readInt8();
    Ark_Union_NavDestinationContext_String toTmpBuf = {};
    toTmpBuf.selector = toTmpBufUnionSelector;
    if (toTmpBufUnionSelector == 0)
    {
        toTmpBuf.selector = 0;
        toTmpBuf.value0 = static_cast<Ark_NavDestinationContext>(
            NavDestinationContext_serializer::read(thisDeserializer));
    }
    else if (toTmpBufUnionSelector == 1)
    {
        toTmpBuf.selector = 1;
        toTmpBuf.value1 = static_cast<Ark_String>(thisDeserializer.readString());
    }
    else
    {
        INTEROP_FATAL("One of the branches for toTmpBuf has to be chosen through deserialisation.");
    }
    Ark_Union_NavDestinationContext_String to = static_cast<Ark_Union_NavDestinationContext_String>(toTmpBuf);
    Ark_NavigationOperation operation = static_cast<Ark_NavigationOperation>(thisDeserializer.readInt32());
    Ark_Boolean isAnimated = thisDeserializer.readBoolean();
    call(resourceId, from, to, operation, isAnimated);
}
void deserializeAndCallSyncInterceptionShowCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                    Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<
        void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Union_NavDestinationContext_String from,
                 const Ark_Union_NavDestinationContext_String to, Ark_NavigationOperation operation,
                 const Ark_Boolean isAnimated)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_INTERCEPTIONSHOWCALLBACK))));
    const Ark_Int8 fromTmpBufUnionSelector = thisDeserializer.readInt8();
    Ark_Union_NavDestinationContext_String fromTmpBuf = {};
    fromTmpBuf.selector = fromTmpBufUnionSelector;
    if (fromTmpBufUnionSelector == 0)
    {
        fromTmpBuf.selector = 0;
        fromTmpBuf.value0 = static_cast<Ark_NavDestinationContext>(
            NavDestinationContext_serializer::read(thisDeserializer));
    }
    else if (fromTmpBufUnionSelector == 1)
    {
        fromTmpBuf.selector = 1;
        fromTmpBuf.value1 = static_cast<Ark_String>(thisDeserializer.readString());
    }
    else
    {
        INTEROP_FATAL("One of the branches for fromTmpBuf has to be chosen through deserialisation.");
    }
    Ark_Union_NavDestinationContext_String from = static_cast<Ark_Union_NavDestinationContext_String>(fromTmpBuf);
    const Ark_Int8 toTmpBufUnionSelector = thisDeserializer.readInt8();
    Ark_Union_NavDestinationContext_String toTmpBuf = {};
    toTmpBuf.selector = toTmpBufUnionSelector;
    if (toTmpBufUnionSelector == 0)
    {
        toTmpBuf.selector = 0;
        toTmpBuf.value0 = static_cast<Ark_NavDestinationContext>(
            NavDestinationContext_serializer::read(thisDeserializer));
    }
    else if (toTmpBufUnionSelector == 1)
    {
        toTmpBuf.selector = 1;
        toTmpBuf.value1 = static_cast<Ark_String>(thisDeserializer.readString());
    }
    else
    {
        INTEROP_FATAL("One of the branches for toTmpBuf has to be chosen through deserialisation.");
    }
    Ark_Union_NavDestinationContext_String to = static_cast<Ark_Union_NavDestinationContext_String>(toTmpBuf);
    Ark_NavigationOperation operation = static_cast<Ark_NavigationOperation>(thisDeserializer.readInt32());
    Ark_Boolean isAnimated = thisDeserializer.readBoolean();
    callSyncMethod(vmContext, resourceId, from, to, operation, isAnimated);
}
void deserializeAndCallLoadingProgressModifierBuilder(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_NativePointer parentNode,
                                                const Ark_LoadingProgressConfiguration config,
                                                const Callback_Pointer_Void continuation)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_LOADINGPROGRESSMODIFIERBUILDER))));
    thisDeserializer.readPointer();
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_LoadingProgressConfiguration config = LoadingProgressConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_POINTER_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_POINTER_VOID))))};
    call(resourceId, parentNode, config, continuationResult);
}
void deserializeAndCallSyncLoadingProgressModifierBuilder(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                          Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<
        void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer parentNode,
                 const Ark_LoadingProgressConfiguration config, const Callback_Pointer_Void continuation)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_LOADINGPROGRESSMODIFIERBUILDER))));
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_LoadingProgressConfiguration config = LoadingProgressConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_POINTER_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_POINTER_VOID))))};
    callSyncMethod(vmContext, resourceId, parentNode, config, continuationResult);
}
void deserializeAndCallMenuCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Int32 start, const Ark_Int32 end)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_MENUCALLBACK))));
    thisDeserializer.readPointer();
    Ark_Int32 start = thisDeserializer.readInt32();
    Ark_Int32 end = thisDeserializer.readInt32();
    call(resourceId, start, end);
}
void deserializeAndCallSyncMenuCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_Int32 start, const Ark_Int32 end)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_MENUCALLBACK))));
    Ark_Int32 start = thisDeserializer.readInt32();
    Ark_Int32 end = thisDeserializer.readInt32();
    callSyncMethod(vmContext, resourceId, start, end);
}
void deserializeAndCallMenuItemModifierBuilder(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_NativePointer parentNode,
                                  const Ark_MenuItemConfiguration config, const Callback_Pointer_Void continuation)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_MENUITEMMODIFIERBUILDER))));
    thisDeserializer.readPointer();
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_MenuItemConfiguration config = static_cast<Ark_MenuItemConfiguration>(
        MenuItemConfiguration_serializer::read(thisDeserializer));
    Callback_Pointer_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_POINTER_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_POINTER_VOID))))};
    call(resourceId, parentNode, config, continuationResult);
}
void deserializeAndCallSyncMenuItemModifierBuilder(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                   Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<
        void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer parentNode,
                 const Ark_MenuItemConfiguration config, const Callback_Pointer_Void continuation)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_MENUITEMMODIFIERBUILDER))));
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_MenuItemConfiguration config = static_cast<Ark_MenuItemConfiguration>(
        MenuItemConfiguration_serializer::read(thisDeserializer));
    Callback_Pointer_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_POINTER_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_POINTER_VOID))))};
    callSyncMethod(vmContext, resourceId, parentNode, config, continuationResult);
}
void deserializeAndCallMenuOnAppearCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Int32 start, const Ark_Int32 end)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_MENUONAPPEARCALLBACK))));
    thisDeserializer.readPointer();
    Ark_Int32 start = thisDeserializer.readInt32();
    Ark_Int32 end = thisDeserializer.readInt32();
    call(resourceId, start, end);
}
void deserializeAndCallSyncMenuOnAppearCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_Int32 start, const Ark_Int32 end)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_MENUONAPPEARCALLBACK))));
    Ark_Int32 start = thisDeserializer.readInt32();
    Ark_Int32 end = thisDeserializer.readInt32();
    callSyncMethod(vmContext, resourceId, start, end);
}
void deserializeAndCallModifierKeyStateGetter(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Array_String keys,
                                                const synthetic_Callback_Boolean_Void continuation)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_MODIFIERKEYSTATEGETTER))));
    thisDeserializer.readPointer();
    const Ark_Int32 keysTmpBufLength = thisDeserializer.readInt32();
    Array_String keysTmpBuf = {};
    thisDeserializer.resizeArray<std::decay<decltype(keysTmpBuf)>::type, std::decay<decltype(*keysTmpBuf.array)>::type>(
        &keysTmpBuf, keysTmpBufLength);
    for (int keysTmpBufBufCounterI = 0; keysTmpBufBufCounterI < keysTmpBufLength; keysTmpBufBufCounterI++)
    {
        keysTmpBuf.array[keysTmpBufBufCounterI] = static_cast<Ark_String>(thisDeserializer.readString());
    }
    Array_String keys = keysTmpBuf;
    synthetic_Callback_Boolean_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID))))};
    call(resourceId, keys, continuationResult);
}
void deserializeAndCallSyncModifierKeyStateGetter(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                  Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Array_String keys,
                                  const synthetic_Callback_Boolean_Void continuation)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_MODIFIERKEYSTATEGETTER))));
    const Ark_Int32 keysTmpBufLength = thisDeserializer.readInt32();
    Array_String keysTmpBuf = {};
    thisDeserializer.resizeArray<std::decay<decltype(keysTmpBuf)>::type, std::decay<decltype(*keysTmpBuf.array)>::type>(
        &keysTmpBuf, keysTmpBufLength);
    for (int keysTmpBufBufCounterI = 0; keysTmpBufBufCounterI < keysTmpBufLength; keysTmpBufBufCounterI++)
    {
        keysTmpBuf.array[keysTmpBufBufCounterI] = static_cast<Ark_String>(thisDeserializer.readString());
    }
    Array_String keys = keysTmpBuf;
    synthetic_Callback_Boolean_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID))))};
    callSyncMethod(vmContext, resourceId, keys, continuationResult);
}
void deserializeAndCallNavDestinationTransitionDelegate(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, Ark_NavigationOperation operation,
                                                const Ark_Boolean isEnter,
                                                const Callback_Opt_Array_NavDestinationTransition_Void continuation)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_NAVDESTINATIONTRANSITIONDELEGATE))));
    thisDeserializer.readPointer();
    Ark_NavigationOperation operation = static_cast<Ark_NavigationOperation>(thisDeserializer.readInt32());
    Ark_Boolean isEnter = thisDeserializer.readBoolean();
    Callback_Opt_Array_NavDestinationTransition_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Opt_Array_NavDestinationTransition value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCaller(KIND_CALLBACK_OPT_ARRAY_NAVDESTINATIONTRANSITION_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                  const Opt_Array_NavDestinationTransition value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_CALLBACK_OPT_ARRAY_NAVDESTINATIONTRANSITION_VOID))))};
    call(resourceId, operation, isEnter, continuationResult);
}
void deserializeAndCallSyncNavDestinationTransitionDelegate(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                            Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<
        void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_NavigationOperation operation,
                 const Ark_Boolean isEnter, const Callback_Opt_Array_NavDestinationTransition_Void continuation)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_NAVDESTINATIONTRANSITIONDELEGATE))));
    Ark_NavigationOperation operation = static_cast<Ark_NavigationOperation>(thisDeserializer.readInt32());
    Ark_Boolean isEnter = thisDeserializer.readBoolean();
    Callback_Opt_Array_NavDestinationTransition_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Opt_Array_NavDestinationTransition value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCaller(KIND_CALLBACK_OPT_ARRAY_NAVDESTINATIONTRANSITION_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                  const Opt_Array_NavDestinationTransition value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_CALLBACK_OPT_ARRAY_NAVDESTINATIONTRANSITION_VOID))))};
    callSyncMethod(vmContext, resourceId, operation, isEnter, continuationResult);
}
void deserializeAndCallNavExtender_CreateNavDestination(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Int32 index,
                                                const Callback_Pointer_Void continuation)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_NAVEXTENDER_CREATENAVDESTINATION))));
    thisDeserializer.readPointer();
    Ark_Int32 index = thisDeserializer.readInt32();
    Callback_Pointer_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_POINTER_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_POINTER_VOID))))};
    call(resourceId, index, continuationResult);
}
void deserializeAndCallSyncNavExtender_CreateNavDestination(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                            Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int32 index,
                                  const Callback_Pointer_Void continuation)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_NAVEXTENDER_CREATENAVDESTINATION))));
    Ark_Int32 index = thisDeserializer.readInt32();
    Callback_Pointer_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_POINTER_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_POINTER_VOID))))};
    callSyncMethod(vmContext, resourceId, index, continuationResult);
}
void deserializeAndCallNavExtender_OnUpdateStack(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId)>(thisDeserializer.readPointerOrDefault(
        reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_NAVEXTENDER_ONUPDATESTACK))));
    thisDeserializer.readPointer();
    call(resourceId);
}
void deserializeAndCallSyncNavExtender_OnUpdateStack(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                     Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_NAVEXTENDER_ONUPDATESTACK))));
    callSyncMethod(vmContext, resourceId);
}
void deserializeAndCallNodeContainerOpsOnTouchCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_TouchEvent event)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_NODECONTAINEROPSONTOUCHCALLBACK))));
    thisDeserializer.readPointer();
    Ark_TouchEvent event = static_cast<Ark_TouchEvent>(TouchEvent_serializer::read(thisDeserializer));
    call(resourceId, event);
}
void deserializeAndCallSyncNodeContainerOpsOnTouchCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                           Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_TouchEvent event)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_NODECONTAINEROPSONTOUCHCALLBACK))));
    Ark_TouchEvent event = static_cast<Ark_TouchEvent>(TouchEvent_serializer::read(thisDeserializer));
    callSyncMethod(vmContext, resourceId, event);
}
void deserializeAndCallOnAdsBlockedCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_AdsBlockedDetails details)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_ONADSBLOCKEDCALLBACK))));
    thisDeserializer.readPointer();
    Ark_AdsBlockedDetails details = AdsBlockedDetails_serializer::read(thisDeserializer);
    call(resourceId, details);
}
void deserializeAndCallSyncOnAdsBlockedCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_AdsBlockedDetails details)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_ONADSBLOCKEDCALLBACK))));
    Ark_AdsBlockedDetails details = AdsBlockedDetails_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, details);
}
void deserializeAndCallOnAlphabetIndexerPopupSelectCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Int32 index)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_ONALPHABETINDEXERPOPUPSELECTCALLBACK))));
    thisDeserializer.readPointer();
    Ark_Int32 index = thisDeserializer.readInt32();
    call(resourceId, index);
}
void deserializeAndCallSyncOnAlphabetIndexerPopupSelectCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                                Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int32 index)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_ONALPHABETINDEXERPOPUPSELECTCALLBACK))));
    Ark_Int32 index = thisDeserializer.readInt32();
    callSyncMethod(vmContext, resourceId, index);
}
void deserializeAndCallOnAlphabetIndexerRequestPopupDataCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Int32 index,
                                                const synthetic_Callback_Array_String_Void continuation)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCaller(KIND_ONALPHABETINDEXERREQUESTPOPUPDATACALLBACK))));
    thisDeserializer.readPointer();
    Ark_Int32 index = thisDeserializer.readInt32();
    synthetic_Callback_Array_String_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Array_String value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCaller(KIND_SYNTHETIC_CALLBACK_ARRAY_STRING_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Array_String value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_SYNTHETIC_CALLBACK_ARRAY_STRING_VOID))))};
    call(resourceId, index, continuationResult);
}
void deserializeAndCallSyncOnAlphabetIndexerRequestPopupDataCallback(Ark_VMContext vmContext,
                                                                     KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int32 index,
                                  const synthetic_Callback_Array_String_Void continuation)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_ONALPHABETINDEXERREQUESTPOPUPDATACALLBACK))));
    Ark_Int32 index = thisDeserializer.readInt32();
    synthetic_Callback_Array_String_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Array_String value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCaller(KIND_SYNTHETIC_CALLBACK_ARRAY_STRING_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Array_String value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_SYNTHETIC_CALLBACK_ARRAY_STRING_VOID))))};
    callSyncMethod(vmContext, resourceId, index, continuationResult);
}
void deserializeAndCallOnAlphabetIndexerSelectCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Int32 index)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_ONALPHABETINDEXERSELECTCALLBACK))));
    thisDeserializer.readPointer();
    Ark_Int32 index = thisDeserializer.readInt32();
    call(resourceId, index);
}
void deserializeAndCallSyncOnAlphabetIndexerSelectCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                           Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int32 index)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_ONALPHABETINDEXERSELECTCALLBACK))));
    Ark_Int32 index = thisDeserializer.readInt32();
    callSyncMethod(vmContext, resourceId, index);
}
void deserializeAndCallOnCheckboxChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Boolean value)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_ONCHECKBOXCHANGECALLBACK))));
    thisDeserializer.readPointer();
    Ark_Boolean value = thisDeserializer.readBoolean();
    call(resourceId, value);
}
void deserializeAndCallSyncOnCheckboxChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                    Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_ONCHECKBOXCHANGECALLBACK))));
    Ark_Boolean value = thisDeserializer.readBoolean();
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallOnCheckboxGroupChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_CheckboxGroupResult value)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_ONCHECKBOXGROUPCHANGECALLBACK))));
    thisDeserializer.readPointer();
    Ark_CheckboxGroupResult value = CheckboxGroupResult_serializer::read(thisDeserializer);
    call(resourceId, value);
}
void deserializeAndCallSyncOnCheckboxGroupChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                         Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_CheckboxGroupResult value)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_ONCHECKBOXGROUPCHANGECALLBACK))));
    Ark_CheckboxGroupResult value = CheckboxGroupResult_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallOnContentScrollCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Float64 totalOffsetX,
                                                const Ark_Float64 totalOffsetY)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_ONCONTENTSCROLLCALLBACK))));
    thisDeserializer.readPointer();
    Ark_Float64 totalOffsetX = thisDeserializer.readFloat64();
    Ark_Float64 totalOffsetY = thisDeserializer.readFloat64();
    call(resourceId, totalOffsetX, totalOffsetY);
}
void deserializeAndCallSyncOnContentScrollCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                   Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Float64 totalOffsetX,
                                  const Ark_Float64 totalOffsetY)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_ONCONTENTSCROLLCALLBACK))));
    Ark_Float64 totalOffsetX = thisDeserializer.readFloat64();
    Ark_Float64 totalOffsetY = thisDeserializer.readFloat64();
    callSyncMethod(vmContext, resourceId, totalOffsetX, totalOffsetY);
}
void deserializeAndCallOnContextMenuHideCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId)>(thisDeserializer.readPointerOrDefault(
        reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_ONCONTEXTMENUHIDECALLBACK))));
    thisDeserializer.readPointer();
    call(resourceId);
}
void deserializeAndCallSyncOnContextMenuHideCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                     Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_ONCONTEXTMENUHIDECALLBACK))));
    callSyncMethod(vmContext, resourceId);
}
void deserializeAndCallOnCreateMenuCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Array_TextMenuItem menuItems,
                                                const Callback_Array_TextMenuItem_Void continuation)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_ONCREATEMENUCALLBACK))));
    thisDeserializer.readPointer();
    const Ark_Int32 menuItemsTmpBufLength = thisDeserializer.readInt32();
    Array_TextMenuItem menuItemsTmpBuf = {};
    thisDeserializer.resizeArray<std::decay<decltype(menuItemsTmpBuf)>::type,
                                 std::decay<decltype(*menuItemsTmpBuf.array)>::type>(&menuItemsTmpBuf,
                                                                                     menuItemsTmpBufLength);
    for (int menuItemsTmpBufBufCounterI = 0; menuItemsTmpBufBufCounterI < menuItemsTmpBufLength;
         menuItemsTmpBufBufCounterI++)
    {
        menuItemsTmpBuf.array[menuItemsTmpBufBufCounterI] = TextMenuItem_serializer::read(thisDeserializer);
    }
    Array_TextMenuItem menuItems = menuItemsTmpBuf;
    Callback_Array_TextMenuItem_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Array_TextMenuItem value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_ARRAY_TEXTMENUITEM_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Array_TextMenuItem value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_CALLBACK_ARRAY_TEXTMENUITEM_VOID))))};
    call(resourceId, menuItems, continuationResult);
}
void deserializeAndCallSyncOnCreateMenuCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Array_TextMenuItem menuItems,
                                                          const Callback_Array_TextMenuItem_Void continuation)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_ONCREATEMENUCALLBACK))));
    const Ark_Int32 menuItemsTmpBufLength = thisDeserializer.readInt32();
    Array_TextMenuItem menuItemsTmpBuf = {};
    thisDeserializer.resizeArray<std::decay<decltype(menuItemsTmpBuf)>::type,
                                 std::decay<decltype(*menuItemsTmpBuf.array)>::type>(&menuItemsTmpBuf,
                                                                                     menuItemsTmpBufLength);
    for (int menuItemsTmpBufBufCounterI = 0; menuItemsTmpBufBufCounterI < menuItemsTmpBufLength;
         menuItemsTmpBufBufCounterI++)
    {
        menuItemsTmpBuf.array[menuItemsTmpBufBufCounterI] = TextMenuItem_serializer::read(thisDeserializer);
    }
    Array_TextMenuItem menuItems = menuItemsTmpBuf;
    Callback_Array_TextMenuItem_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Array_TextMenuItem value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_ARRAY_TEXTMENUITEM_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Array_TextMenuItem value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_CALLBACK_ARRAY_TEXTMENUITEM_VOID))))};
    callSyncMethod(vmContext, resourceId, menuItems, continuationResult);
}
void deserializeAndCallOnDidChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_TextRange rangeBefore,
                                                const Ark_TextRange rangeAfter)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_ONDIDCHANGECALLBACK))));
    thisDeserializer.readPointer();
    Ark_TextRange rangeBefore = TextRange_serializer::read(thisDeserializer);
    Ark_TextRange rangeAfter = TextRange_serializer::read(thisDeserializer);
    call(resourceId, rangeBefore, rangeAfter);
}
void deserializeAndCallSyncOnDidChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                               Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_TextRange rangeBefore,
                                  const Ark_TextRange rangeAfter)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_ONDIDCHANGECALLBACK))));
    Ark_TextRange rangeBefore = TextRange_serializer::read(thisDeserializer);
    Ark_TextRange rangeAfter = TextRange_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, rangeBefore, rangeAfter);
}
void deserializeAndCallOnDragEventCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_DragEvent event, const Opt_String extraParams)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_ONDRAGEVENTCALLBACK))));
    thisDeserializer.readPointer();
    Ark_DragEvent event = static_cast<Ark_DragEvent>(DragEvent_serializer::read(thisDeserializer));
    const auto extraParamsTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_String extraParamsTmpBuf = {};
    extraParamsTmpBuf.tag = extraParamsTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED :
                                                                                         INTEROP_TAG_OBJECT;
    if ((extraParamsTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        extraParamsTmpBuf.value = static_cast<Ark_String>(thisDeserializer.readString());
    }
    Opt_String extraParams = extraParamsTmpBuf;
    call(resourceId, event, extraParams);
}
void deserializeAndCallSyncOnDragEventCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                               Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_DragEvent event, const Opt_String extraParams)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_ONDRAGEVENTCALLBACK))));
    Ark_DragEvent event = static_cast<Ark_DragEvent>(DragEvent_serializer::read(thisDeserializer));
    const auto extraParamsTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_String extraParamsTmpBuf = {};
    extraParamsTmpBuf.tag = extraParamsTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED :
                                                                                         INTEROP_TAG_OBJECT;
    if ((extraParamsTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        extraParamsTmpBuf.value = static_cast<Ark_String>(thisDeserializer.readString());
    }
    Opt_String extraParams = extraParamsTmpBuf;
    callSyncMethod(vmContext, resourceId, event, extraParams);
}
void deserializeAndCallOnFirstMeaningfulPaintCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_FirstMeaningfulPaint firstMeaningfulPaint)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_ONFIRSTMEANINGFULPAINTCALLBACK))));
    thisDeserializer.readPointer();
    Ark_FirstMeaningfulPaint firstMeaningfulPaint = FirstMeaningfulPaint_serializer::read(thisDeserializer);
    call(resourceId, firstMeaningfulPaint);
}
void deserializeAndCallSyncOnFirstMeaningfulPaintCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                          Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_FirstMeaningfulPaint firstMeaningfulPaint)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_ONFIRSTMEANINGFULPAINTCALLBACK))));
    Ark_FirstMeaningfulPaint firstMeaningfulPaint = FirstMeaningfulPaint_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, firstMeaningfulPaint);
}
void deserializeAndCallOnFoldStatusChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_OnFoldStatusChangeInfo event)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_ONFOLDSTATUSCHANGECALLBACK))));
    thisDeserializer.readPointer();
    Ark_OnFoldStatusChangeInfo event = OnFoldStatusChangeInfo_serializer::read(thisDeserializer);
    call(resourceId, event);
}
void deserializeAndCallSyncOnFoldStatusChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                      Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_OnFoldStatusChangeInfo event)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_ONFOLDSTATUSCHANGECALLBACK))));
    Ark_OnFoldStatusChangeInfo event = OnFoldStatusChangeInfo_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, event);
}
void deserializeAndCallOnFullScreenEnterCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_FullScreenEnterEvent event)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_ONFULLSCREENENTERCALLBACK))));
    thisDeserializer.readPointer();
    Ark_FullScreenEnterEvent event = FullScreenEnterEvent_serializer::read(thisDeserializer);
    call(resourceId, event);
}
void deserializeAndCallSyncOnFullScreenEnterCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                     Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_FullScreenEnterEvent event)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_ONFULLSCREENENTERCALLBACK))));
    Ark_FullScreenEnterEvent event = FullScreenEnterEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, event);
}
void deserializeAndCallOnHoverCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Boolean status, const Ark_HoverEvent event)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_ONHOVERCALLBACK))));
    thisDeserializer.readPointer();
    Ark_Boolean status = thisDeserializer.readBoolean();
    Ark_HoverEvent event = static_cast<Ark_HoverEvent>(HoverEvent_serializer::read(thisDeserializer));
    call(resourceId, status, event);
}
void deserializeAndCallSyncOnHoverCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_Boolean status, const Ark_HoverEvent event)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_ONHOVERCALLBACK))));
    Ark_Boolean status = thisDeserializer.readBoolean();
    Ark_HoverEvent event = static_cast<Ark_HoverEvent>(HoverEvent_serializer::read(thisDeserializer));
    callSyncMethod(vmContext, resourceId, status, event);
}
void deserializeAndCallOnHoverStatusChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_HoverEventParam param)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_ONHOVERSTATUSCHANGECALLBACK))));
    thisDeserializer.readPointer();
    Ark_HoverEventParam param = HoverEventParam_serializer::read(thisDeserializer);
    call(resourceId, param);
}
void deserializeAndCallSyncOnHoverStatusChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                       Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_HoverEventParam param)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_ONHOVERSTATUSCHANGECALLBACK))));
    Ark_HoverEventParam param = HoverEventParam_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, param);
}
void deserializeAndCallOnIntelligentTrackingPreventionCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_IntelligentTrackingPreventionDetails details)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCaller(KIND_ONINTELLIGENTTRACKINGPREVENTIONCALLBACK))));
    thisDeserializer.readPointer();
    Ark_IntelligentTrackingPreventionDetails details = IntelligentTrackingPreventionDetails_serializer::read(
        thisDeserializer);
    call(resourceId, details);
}
void deserializeAndCallSyncOnIntelligentTrackingPreventionCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                                   Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_IntelligentTrackingPreventionDetails details)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCallerSync(KIND_ONINTELLIGENTTRACKINGPREVENTIONCALLBACK))));
    Ark_IntelligentTrackingPreventionDetails details = IntelligentTrackingPreventionDetails_serializer::read(
        thisDeserializer);
    callSyncMethod(vmContext, resourceId, details);
}
void deserializeAndCallOnItemDragStartCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_ItemDragInfo event, const Ark_Int32 itemIndex,
                                  const Callback_Opt_CustomNodeBuilder_Void continuation)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_ONITEMDRAGSTARTCALLBACK))));
    thisDeserializer.readPointer();
    Ark_ItemDragInfo event = ItemDragInfo_serializer::read(thisDeserializer);
    Ark_Int32 itemIndex = thisDeserializer.readInt32();
    Callback_Opt_CustomNodeBuilder_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Opt_CustomNodeBuilder value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCaller(KIND_CALLBACK_OPT_CUSTOMNODEBUILDER_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                  const Opt_CustomNodeBuilder value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_CALLBACK_OPT_CUSTOMNODEBUILDER_VOID))))};
    call(resourceId, event, itemIndex, continuationResult);
}
void deserializeAndCallSyncOnItemDragStartCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                   Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_ItemDragInfo event,
                                  const Ark_Int32 itemIndex, const Callback_Opt_CustomNodeBuilder_Void continuation)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_ONITEMDRAGSTARTCALLBACK))));
    Ark_ItemDragInfo event = ItemDragInfo_serializer::read(thisDeserializer);
    Ark_Int32 itemIndex = thisDeserializer.readInt32();
    Callback_Opt_CustomNodeBuilder_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Opt_CustomNodeBuilder value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCaller(KIND_CALLBACK_OPT_CUSTOMNODEBUILDER_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                  const Opt_CustomNodeBuilder value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_CALLBACK_OPT_CUSTOMNODEBUILDER_VOID))))};
    callSyncMethod(vmContext, resourceId, event, itemIndex, continuationResult);
}
void deserializeAndCallOnLargestContentfulPaintCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_LargestContentfulPaint largestContentfulPaint)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_ONLARGESTCONTENTFULPAINTCALLBACK))));
    thisDeserializer.readPointer();
    Ark_LargestContentfulPaint largestContentfulPaint = LargestContentfulPaint_serializer::read(thisDeserializer);
    call(resourceId, largestContentfulPaint);
}
void deserializeAndCallSyncOnLargestContentfulPaintCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                            Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_LargestContentfulPaint largestContentfulPaint)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_ONLARGESTCONTENTFULPAINTCALLBACK))));
    Ark_LargestContentfulPaint largestContentfulPaint = LargestContentfulPaint_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, largestContentfulPaint);
}
void deserializeAndCallOnMenuItemClickCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_TextMenuItem menuItem,
                                  const Ark_TextRange range, const synthetic_Callback_Boolean_Void continuation)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_ONMENUITEMCLICKCALLBACK))));
    thisDeserializer.readPointer();
    Ark_TextMenuItem menuItem = TextMenuItem_serializer::read(thisDeserializer);
    Ark_TextRange range = TextRange_serializer::read(thisDeserializer);
    synthetic_Callback_Boolean_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID))))};
    call(resourceId, menuItem, range, continuationResult);
}
void deserializeAndCallSyncOnMenuItemClickCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                   Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_TextMenuItem menuItem,
                                  const Ark_TextRange range, const synthetic_Callback_Boolean_Void continuation)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_ONMENUITEMCLICKCALLBACK))));
    Ark_TextMenuItem menuItem = TextMenuItem_serializer::read(thisDeserializer);
    Ark_TextRange range = TextRange_serializer::read(thisDeserializer);
    synthetic_Callback_Boolean_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID))))};
    callSyncMethod(vmContext, resourceId, menuItem, range, continuationResult);
}
void deserializeAndCallOnMoveHandler(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Int32 from, const Ark_Int32 to)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_ONMOVEHANDLER))));
    thisDeserializer.readPointer();
    Ark_Int32 from = thisDeserializer.readInt32();
    Ark_Int32 to = thisDeserializer.readInt32();
    call(resourceId, from, to);
}
void deserializeAndCallSyncOnMoveHandler(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_Int32 from, const Ark_Int32 to)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_ONMOVEHANDLER))));
    Ark_Int32 from = thisDeserializer.readInt32();
    Ark_Int32 to = thisDeserializer.readInt32();
    callSyncMethod(vmContext, resourceId, from, to);
}
void deserializeAndCallOnNativeEmbedVisibilityChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId,
                                                const Ark_NativeEmbedVisibilityInfo nativeEmbedVisibilityInfo)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_ONNATIVEEMBEDVISIBILITYCHANGECALLBACK))));
    thisDeserializer.readPointer();
    Ark_NativeEmbedVisibilityInfo nativeEmbedVisibilityInfo = NativeEmbedVisibilityInfo_serializer::read(
        thisDeserializer);
    call(resourceId, nativeEmbedVisibilityInfo);
}
void deserializeAndCallSyncOnNativeEmbedVisibilityChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                                 Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                  const Ark_NativeEmbedVisibilityInfo nativeEmbedVisibilityInfo)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_ONNATIVEEMBEDVISIBILITYCHANGECALLBACK))));
    Ark_NativeEmbedVisibilityInfo nativeEmbedVisibilityInfo = NativeEmbedVisibilityInfo_serializer::read(
        thisDeserializer);
    callSyncMethod(vmContext, resourceId, nativeEmbedVisibilityInfo);
}
void deserializeAndCallOnNavigationEntryCommittedCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_LoadCommittedDetails loadCommittedDetails)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCaller(KIND_ONNAVIGATIONENTRYCOMMITTEDCALLBACK))));
    thisDeserializer.readPointer();
    Ark_LoadCommittedDetails loadCommittedDetails = LoadCommittedDetails_serializer::read(thisDeserializer);
    call(resourceId, loadCommittedDetails);
}
void deserializeAndCallSyncOnNavigationEntryCommittedCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                              Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_LoadCommittedDetails loadCommittedDetails)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCallerSync(KIND_ONNAVIGATIONENTRYCOMMITTEDCALLBACK))));
    Ark_LoadCommittedDetails loadCommittedDetails = LoadCommittedDetails_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, loadCommittedDetails);
}
void deserializeAndCallOnOverrideUrlLoadingCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_WebResourceRequest webResourceRequest,
                                  const synthetic_Callback_Boolean_Void continuation)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_ONOVERRIDEURLLOADINGCALLBACK))));
    thisDeserializer.readPointer();
    Ark_WebResourceRequest webResourceRequest = static_cast<Ark_WebResourceRequest>(
        WebResourceRequest_serializer::read(thisDeserializer));
    synthetic_Callback_Boolean_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID))))};
    call(resourceId, webResourceRequest, continuationResult);
}
void deserializeAndCallSyncOnOverrideUrlLoadingCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                        Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_WebResourceRequest webResourceRequest,
                                                          const synthetic_Callback_Boolean_Void continuation)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_ONOVERRIDEURLLOADINGCALLBACK))));
    Ark_WebResourceRequest webResourceRequest = static_cast<Ark_WebResourceRequest>(
        WebResourceRequest_serializer::read(thisDeserializer));
    synthetic_Callback_Boolean_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID))))};
    callSyncMethod(vmContext, resourceId, webResourceRequest, continuationResult);
}
void deserializeAndCallOnPasteCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_String content, const Ark_PasteEvent event)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_ONPASTECALLBACK))));
    thisDeserializer.readPointer();
    Ark_String content = static_cast<Ark_String>(thisDeserializer.readString());
    Ark_PasteEvent event = static_cast<Ark_PasteEvent>(PasteEvent_serializer::read(thisDeserializer));
    call(resourceId, content, event);
}
void deserializeAndCallSyncOnPasteCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_String content, const Ark_PasteEvent event)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_ONPASTECALLBACK))));
    Ark_String content = static_cast<Ark_String>(thisDeserializer.readString());
    Ark_PasteEvent event = static_cast<Ark_PasteEvent>(PasteEvent_serializer::read(thisDeserializer));
    callSyncMethod(vmContext, resourceId, content, event);
}
void deserializeAndCallOnRadioChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Boolean isChecked)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_ONRADIOCHANGECALLBACK))));
    thisDeserializer.readPointer();
    Ark_Boolean isChecked = thisDeserializer.readBoolean();
    call(resourceId, isChecked);
}
void deserializeAndCallSyncOnRadioChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                 Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isChecked)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_ONRADIOCHANGECALLBACK))));
    Ark_Boolean isChecked = thisDeserializer.readBoolean();
    callSyncMethod(vmContext, resourceId, isChecked);
}
void deserializeAndCallOnRatingChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Float64 rating)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_ONRATINGCHANGECALLBACK))));
    thisDeserializer.readPointer();
    Ark_Float64 rating = thisDeserializer.readFloat64();
    call(resourceId, rating);
}
void deserializeAndCallSyncOnRatingChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                  Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Float64 rating)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_ONRATINGCHANGECALLBACK))));
    Ark_Float64 rating = thisDeserializer.readFloat64();
    callSyncMethod(vmContext, resourceId, rating);
}
void deserializeAndCallOnRenderProcessNotRespondingCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_RenderProcessNotRespondingData data)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCaller(KIND_ONRENDERPROCESSNOTRESPONDINGCALLBACK))));
    thisDeserializer.readPointer();
    Ark_RenderProcessNotRespondingData data = RenderProcessNotRespondingData_serializer::read(thisDeserializer);
    call(resourceId, data);
}
void deserializeAndCallSyncOnRenderProcessNotRespondingCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                                Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_RenderProcessNotRespondingData data)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCallerSync(KIND_ONRENDERPROCESSNOTRESPONDINGCALLBACK))));
    Ark_RenderProcessNotRespondingData data = RenderProcessNotRespondingData_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallOnRenderProcessRespondingCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId)>(thisDeserializer.readPointerOrDefault(
        reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_ONRENDERPROCESSRESPONDINGCALLBACK))));
    thisDeserializer.readPointer();
    call(resourceId);
}
void deserializeAndCallSyncOnRenderProcessRespondingCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                             Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_ONRENDERPROCESSRESPONDINGCALLBACK))));
    callSyncMethod(vmContext, resourceId);
}
void deserializeAndCallOnSafeBrowsingCheckResultCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, Ark_ThreatType threatType)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_ONSAFEBROWSINGCHECKRESULTCALLBACK))));
    thisDeserializer.readPointer();
    Ark_ThreatType threatType = static_cast<Ark_ThreatType>(thisDeserializer.readInt32());
    call(resourceId, threatType);
}
void deserializeAndCallSyncOnSafeBrowsingCheckResultCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                             Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_ThreatType threatType)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_ONSAFEBROWSINGCHECKRESULTCALLBACK))));
    Ark_ThreatType threatType = static_cast<Ark_ThreatType>(thisDeserializer.readInt32());
    callSyncMethod(vmContext, resourceId, threatType);
}
void deserializeAndCallOnScrollCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Float64 scrollOffset,
                                                Ark_ScrollState scrollState)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_ONSCROLLCALLBACK))));
    thisDeserializer.readPointer();
    Ark_Float64 scrollOffset = thisDeserializer.readFloat64();
    Ark_ScrollState scrollState = static_cast<Ark_ScrollState>(thisDeserializer.readInt32());
    call(resourceId, scrollOffset, scrollState);
}
void deserializeAndCallSyncOnScrollCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_Float64 scrollOffset, Ark_ScrollState scrollState)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_ONSCROLLCALLBACK))));
    Ark_Float64 scrollOffset = thisDeserializer.readFloat64();
    Ark_ScrollState scrollState = static_cast<Ark_ScrollState>(thisDeserializer.readInt32());
    callSyncMethod(vmContext, resourceId, scrollOffset, scrollState);
}
void deserializeAndCallOnScrollEdgeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, Ark_Edge side)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_ONSCROLLEDGECALLBACK))));
    thisDeserializer.readPointer();
    Ark_Edge side = static_cast<Ark_Edge>(thisDeserializer.readInt32());
    call(resourceId, side);
}
void deserializeAndCallSyncOnScrollEdgeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_Edge side)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_ONSCROLLEDGECALLBACK))));
    Ark_Edge side = static_cast<Ark_Edge>(thisDeserializer.readInt32());
    callSyncMethod(vmContext, resourceId, side);
}
void deserializeAndCallOnScrollFrameBeginCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Float64 offset, Ark_ScrollState state,
                                  const Callback_OnScrollFrameBeginHandlerResult_Void continuation)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_ONSCROLLFRAMEBEGINCALLBACK))));
    thisDeserializer.readPointer();
    Ark_Float64 offset = thisDeserializer.readFloat64();
    Ark_ScrollState state = static_cast<Ark_ScrollState>(thisDeserializer.readInt32());
    Callback_OnScrollFrameBeginHandlerResult_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_OnScrollFrameBeginHandlerResult value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCaller(KIND_CALLBACK_ONSCROLLFRAMEBEGINHANDLERRESULT_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                  const Ark_OnScrollFrameBeginHandlerResult value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_CALLBACK_ONSCROLLFRAMEBEGINHANDLERRESULT_VOID))))};
    call(resourceId, offset, state, continuationResult);
}
void deserializeAndCallSyncOnScrollFrameBeginCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                      Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<
        void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Float64 offset, Ark_ScrollState state,
                 const Callback_OnScrollFrameBeginHandlerResult_Void continuation)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_ONSCROLLFRAMEBEGINCALLBACK))));
    Ark_Float64 offset = thisDeserializer.readFloat64();
    Ark_ScrollState state = static_cast<Ark_ScrollState>(thisDeserializer.readInt32());
    Callback_OnScrollFrameBeginHandlerResult_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_OnScrollFrameBeginHandlerResult value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCaller(KIND_CALLBACK_ONSCROLLFRAMEBEGINHANDLERRESULT_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                  const Ark_OnScrollFrameBeginHandlerResult value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_CALLBACK_ONSCROLLFRAMEBEGINHANDLERRESULT_VOID))))};
    callSyncMethod(vmContext, resourceId, offset, state, continuationResult);
}
void deserializeAndCallOnScrollVisibleContentChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_VisibleListContentInfo start,
                                                const Ark_VisibleListContentInfo end)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_ONSCROLLVISIBLECONTENTCHANGECALLBACK))));
    thisDeserializer.readPointer();
    Ark_VisibleListContentInfo start = VisibleListContentInfo_serializer::read(thisDeserializer);
    Ark_VisibleListContentInfo end = VisibleListContentInfo_serializer::read(thisDeserializer);
    call(resourceId, start, end);
}
void deserializeAndCallSyncOnScrollVisibleContentChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                                Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                  const Ark_VisibleListContentInfo start, const Ark_VisibleListContentInfo end)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_ONSCROLLVISIBLECONTENTCHANGECALLBACK))));
    Ark_VisibleListContentInfo start = VisibleListContentInfo_serializer::read(thisDeserializer);
    Ark_VisibleListContentInfo end = VisibleListContentInfo_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, start, end);
}
void deserializeAndCallOnSelectCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Int32 index, const Ark_String selectStr)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_ONSELECTCALLBACK))));
    thisDeserializer.readPointer();
    Ark_Int32 index = thisDeserializer.readInt32();
    Ark_String selectStr = static_cast<Ark_String>(thisDeserializer.readString());
    call(resourceId, index, selectStr);
}
void deserializeAndCallSyncOnSelectCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_Int32 index, const Ark_String selectStr)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_ONSELECTCALLBACK))));
    Ark_Int32 index = thisDeserializer.readInt32();
    Ark_String selectStr = static_cast<Ark_String>(thisDeserializer.readString());
    callSyncMethod(vmContext, resourceId, index, selectStr);
}
void deserializeAndCallOnSslErrorEventCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_SslErrorEvent sslErrorEvent)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_ONSSLERROREVENTCALLBACK))));
    thisDeserializer.readPointer();
    Ark_SslErrorEvent sslErrorEvent = SslErrorEvent_serializer::read(thisDeserializer);
    call(resourceId, sslErrorEvent);
}
void deserializeAndCallSyncOnSslErrorEventCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                   Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_SslErrorEvent sslErrorEvent)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_ONSSLERROREVENTCALLBACK))));
    Ark_SslErrorEvent sslErrorEvent = SslErrorEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, sslErrorEvent);
}
void deserializeAndCallOnSubmitCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, Ark_EnterKeyType enterKey, const Ark_SubmitEvent event)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_ONSUBMITCALLBACK))));
    thisDeserializer.readPointer();
    Ark_EnterKeyType enterKey = static_cast<Ark_EnterKeyType>(thisDeserializer.readInt32());
    Ark_SubmitEvent event = static_cast<Ark_SubmitEvent>(SubmitEvent_serializer::read(thisDeserializer));
    call(resourceId, enterKey, event);
}
void deserializeAndCallSyncOnSubmitCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          Ark_EnterKeyType enterKey, const Ark_SubmitEvent event)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_ONSUBMITCALLBACK))));
    Ark_EnterKeyType enterKey = static_cast<Ark_EnterKeyType>(thisDeserializer.readInt32());
    Ark_SubmitEvent event = static_cast<Ark_SubmitEvent>(SubmitEvent_serializer::read(thisDeserializer));
    callSyncMethod(vmContext, resourceId, enterKey, event);
}
void deserializeAndCallOnSwiperAnimationEndCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Int32 index,
                                                const Ark_SwiperAnimationEvent extraInfo)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_ONSWIPERANIMATIONENDCALLBACK))));
    thisDeserializer.readPointer();
    Ark_Int32 index = thisDeserializer.readInt32();
    Ark_SwiperAnimationEvent extraInfo = SwiperAnimationEvent_serializer::read(thisDeserializer);
    call(resourceId, index, extraInfo);
}
void deserializeAndCallSyncOnSwiperAnimationEndCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                        Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int32 index,
                                  const Ark_SwiperAnimationEvent extraInfo)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_ONSWIPERANIMATIONENDCALLBACK))));
    Ark_Int32 index = thisDeserializer.readInt32();
    Ark_SwiperAnimationEvent extraInfo = SwiperAnimationEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, index, extraInfo);
}
void deserializeAndCallOnSwiperAnimationStartCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Int32 index,
                                                const Ark_Int32 targetIndex, const Ark_SwiperAnimationEvent extraInfo)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_ONSWIPERANIMATIONSTARTCALLBACK))));
    thisDeserializer.readPointer();
    Ark_Int32 index = thisDeserializer.readInt32();
    Ark_Int32 targetIndex = thisDeserializer.readInt32();
    Ark_SwiperAnimationEvent extraInfo = SwiperAnimationEvent_serializer::read(thisDeserializer);
    call(resourceId, index, targetIndex, extraInfo);
}
void deserializeAndCallSyncOnSwiperAnimationStartCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                          Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int32 index,
                                  const Ark_Int32 targetIndex, const Ark_SwiperAnimationEvent extraInfo)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_ONSWIPERANIMATIONSTARTCALLBACK))));
    Ark_Int32 index = thisDeserializer.readInt32();
    Ark_Int32 targetIndex = thisDeserializer.readInt32();
    Ark_SwiperAnimationEvent extraInfo = SwiperAnimationEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, index, targetIndex, extraInfo);
}
void deserializeAndCallOnSwiperGestureSwipeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Int32 index,
                                                const Ark_SwiperAnimationEvent extraInfo)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_ONSWIPERGESTURESWIPECALLBACK))));
    thisDeserializer.readPointer();
    Ark_Int32 index = thisDeserializer.readInt32();
    Ark_SwiperAnimationEvent extraInfo = SwiperAnimationEvent_serializer::read(thisDeserializer);
    call(resourceId, index, extraInfo);
}
void deserializeAndCallSyncOnSwiperGestureSwipeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                        Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int32 index,
                                  const Ark_SwiperAnimationEvent extraInfo)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_ONSWIPERGESTURESWIPECALLBACK))));
    Ark_Int32 index = thisDeserializer.readInt32();
    Ark_SwiperAnimationEvent extraInfo = SwiperAnimationEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, index, extraInfo);
}
void deserializeAndCallOnTabsAnimationEndCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Int32 index,
                                                const Ark_TabsAnimationEvent extraInfo)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_ONTABSANIMATIONENDCALLBACK))));
    thisDeserializer.readPointer();
    Ark_Int32 index = thisDeserializer.readInt32();
    Ark_TabsAnimationEvent extraInfo = TabsAnimationEvent_serializer::read(thisDeserializer);
    call(resourceId, index, extraInfo);
}
void deserializeAndCallSyncOnTabsAnimationEndCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                      Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int32 index,
                                  const Ark_TabsAnimationEvent extraInfo)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_ONTABSANIMATIONENDCALLBACK))));
    Ark_Int32 index = thisDeserializer.readInt32();
    Ark_TabsAnimationEvent extraInfo = TabsAnimationEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, index, extraInfo);
}
void deserializeAndCallOnTabsAnimationStartCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Int32 index,
                                                const Ark_Int32 targetIndex, const Ark_TabsAnimationEvent extraInfo)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_ONTABSANIMATIONSTARTCALLBACK))));
    thisDeserializer.readPointer();
    Ark_Int32 index = thisDeserializer.readInt32();
    Ark_Int32 targetIndex = thisDeserializer.readInt32();
    Ark_TabsAnimationEvent extraInfo = TabsAnimationEvent_serializer::read(thisDeserializer);
    call(resourceId, index, targetIndex, extraInfo);
}
void deserializeAndCallSyncOnTabsAnimationStartCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                        Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int32 index,
                                  const Ark_Int32 targetIndex, const Ark_TabsAnimationEvent extraInfo)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_ONTABSANIMATIONSTARTCALLBACK))));
    Ark_Int32 index = thisDeserializer.readInt32();
    Ark_Int32 targetIndex = thisDeserializer.readInt32();
    Ark_TabsAnimationEvent extraInfo = TabsAnimationEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, index, targetIndex, extraInfo);
}
void deserializeAndCallOnTabsContentWillChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Int32 currentIndex, const Ark_Int32 comingIndex,
                                  const synthetic_Callback_Boolean_Void continuation)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_ONTABSCONTENTWILLCHANGECALLBACK))));
    thisDeserializer.readPointer();
    Ark_Int32 currentIndex = thisDeserializer.readInt32();
    Ark_Int32 comingIndex = thisDeserializer.readInt32();
    synthetic_Callback_Boolean_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID))))};
    call(resourceId, currentIndex, comingIndex, continuationResult);
}
void deserializeAndCallSyncOnTabsContentWillChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                           Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int32 currentIndex,
                                  const Ark_Int32 comingIndex, const synthetic_Callback_Boolean_Void continuation)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_ONTABSCONTENTWILLCHANGECALLBACK))));
    Ark_Int32 currentIndex = thisDeserializer.readInt32();
    Ark_Int32 comingIndex = thisDeserializer.readInt32();
    synthetic_Callback_Boolean_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID))))};
    callSyncMethod(vmContext, resourceId, currentIndex, comingIndex, continuationResult);
}
void deserializeAndCallOnTabsGestureSwipeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Int32 index,
                                                const Ark_TabsAnimationEvent extraInfo)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_ONTABSGESTURESWIPECALLBACK))));
    thisDeserializer.readPointer();
    Ark_Int32 index = thisDeserializer.readInt32();
    Ark_TabsAnimationEvent extraInfo = TabsAnimationEvent_serializer::read(thisDeserializer);
    call(resourceId, index, extraInfo);
}
void deserializeAndCallSyncOnTabsGestureSwipeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                      Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int32 index,
                                  const Ark_TabsAnimationEvent extraInfo)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_ONTABSGESTURESWIPECALLBACK))));
    Ark_Int32 index = thisDeserializer.readInt32();
    Ark_TabsAnimationEvent extraInfo = TabsAnimationEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, index, extraInfo);
}
void deserializeAndCallOnTextPickerChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Union_String_Array_String selectItem,
                                  const Ark_Union_I32_Array_I32 index)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_ONTEXTPICKERCHANGECALLBACK))));
    thisDeserializer.readPointer();
    const Ark_Int8 selectItemTmpBufUnionSelector = thisDeserializer.readInt8();
    Ark_Union_String_Array_String selectItemTmpBuf = {};
    selectItemTmpBuf.selector = selectItemTmpBufUnionSelector;
    if (selectItemTmpBufUnionSelector == 0)
    {
        selectItemTmpBuf.selector = 0;
        selectItemTmpBuf.value0 = static_cast<Ark_String>(thisDeserializer.readString());
    }
    else if (selectItemTmpBufUnionSelector == 1)
    {
        selectItemTmpBuf.selector = 1;
        const Ark_Int32 selectItemTmpBufBufULength = thisDeserializer.readInt32();
        Array_String selectItemTmpBufBufU = {};
        thisDeserializer.resizeArray<std::decay<decltype(selectItemTmpBufBufU)>::type,
                                     std::decay<decltype(*selectItemTmpBufBufU.array)>::type>(
            &selectItemTmpBufBufU, selectItemTmpBufBufULength);
        for (int selectItemTmpBufBufUBufCounterI = 0; selectItemTmpBufBufUBufCounterI < selectItemTmpBufBufULength;
             selectItemTmpBufBufUBufCounterI++)
        {
            selectItemTmpBufBufU.array[selectItemTmpBufBufUBufCounterI] = static_cast<Ark_String>(
                thisDeserializer.readString());
        }
        selectItemTmpBuf.value1 = selectItemTmpBufBufU;
    }
    else
    {
        INTEROP_FATAL("One of the branches for selectItemTmpBuf has to be chosen through deserialisation.");
    }
    Ark_Union_String_Array_String selectItem = static_cast<Ark_Union_String_Array_String>(selectItemTmpBuf);
    const Ark_Int8 indexTmpBufUnionSelector = thisDeserializer.readInt8();
    Ark_Union_I32_Array_I32 indexTmpBuf = {};
    indexTmpBuf.selector = indexTmpBufUnionSelector;
    if (indexTmpBufUnionSelector == 0)
    {
        indexTmpBuf.selector = 0;
        indexTmpBuf.value0 = thisDeserializer.readInt32();
    }
    else if (indexTmpBufUnionSelector == 1)
    {
        indexTmpBuf.selector = 1;
        const Ark_Int32 indexTmpBufBufULength = thisDeserializer.readInt32();
        Array_I32 indexTmpBufBufU = {};
        thisDeserializer.resizeArray<std::decay<decltype(indexTmpBufBufU)>::type,
                                     std::decay<decltype(*indexTmpBufBufU.array)>::type>(&indexTmpBufBufU,
                                                                                         indexTmpBufBufULength);
        for (int indexTmpBufBufUBufCounterI = 0; indexTmpBufBufUBufCounterI < indexTmpBufBufULength;
             indexTmpBufBufUBufCounterI++)
        {
            indexTmpBufBufU.array[indexTmpBufBufUBufCounterI] = thisDeserializer.readInt32();
        }
        indexTmpBuf.value1 = indexTmpBufBufU;
    }
    else
    {
        INTEROP_FATAL("One of the branches for indexTmpBuf has to be chosen through deserialisation.");
    }
    Ark_Union_I32_Array_I32 index = static_cast<Ark_Union_I32_Array_I32>(indexTmpBuf);
    call(resourceId, selectItem, index);
}
void deserializeAndCallSyncOnTextPickerChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                      Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                  const Ark_Union_String_Array_String selectItem, const Ark_Union_I32_Array_I32 index)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_ONTEXTPICKERCHANGECALLBACK))));
    const Ark_Int8 selectItemTmpBufUnionSelector = thisDeserializer.readInt8();
    Ark_Union_String_Array_String selectItemTmpBuf = {};
    selectItemTmpBuf.selector = selectItemTmpBufUnionSelector;
    if (selectItemTmpBufUnionSelector == 0)
    {
        selectItemTmpBuf.selector = 0;
        selectItemTmpBuf.value0 = static_cast<Ark_String>(thisDeserializer.readString());
    }
    else if (selectItemTmpBufUnionSelector == 1)
    {
        selectItemTmpBuf.selector = 1;
        const Ark_Int32 selectItemTmpBufBufULength = thisDeserializer.readInt32();
        Array_String selectItemTmpBufBufU = {};
        thisDeserializer.resizeArray<std::decay<decltype(selectItemTmpBufBufU)>::type,
                                     std::decay<decltype(*selectItemTmpBufBufU.array)>::type>(
            &selectItemTmpBufBufU, selectItemTmpBufBufULength);
        for (int selectItemTmpBufBufUBufCounterI = 0; selectItemTmpBufBufUBufCounterI < selectItemTmpBufBufULength;
             selectItemTmpBufBufUBufCounterI++)
        {
            selectItemTmpBufBufU.array[selectItemTmpBufBufUBufCounterI] = static_cast<Ark_String>(
                thisDeserializer.readString());
        }
        selectItemTmpBuf.value1 = selectItemTmpBufBufU;
    }
    else
    {
        INTEROP_FATAL("One of the branches for selectItemTmpBuf has to be chosen through deserialisation.");
    }
    Ark_Union_String_Array_String selectItem = static_cast<Ark_Union_String_Array_String>(selectItemTmpBuf);
    const Ark_Int8 indexTmpBufUnionSelector = thisDeserializer.readInt8();
    Ark_Union_I32_Array_I32 indexTmpBuf = {};
    indexTmpBuf.selector = indexTmpBufUnionSelector;
    if (indexTmpBufUnionSelector == 0)
    {
        indexTmpBuf.selector = 0;
        indexTmpBuf.value0 = thisDeserializer.readInt32();
    }
    else if (indexTmpBufUnionSelector == 1)
    {
        indexTmpBuf.selector = 1;
        const Ark_Int32 indexTmpBufBufULength = thisDeserializer.readInt32();
        Array_I32 indexTmpBufBufU = {};
        thisDeserializer.resizeArray<std::decay<decltype(indexTmpBufBufU)>::type,
                                     std::decay<decltype(*indexTmpBufBufU.array)>::type>(&indexTmpBufBufU,
                                                                                         indexTmpBufBufULength);
        for (int indexTmpBufBufUBufCounterI = 0; indexTmpBufBufUBufCounterI < indexTmpBufBufULength;
             indexTmpBufBufUBufCounterI++)
        {
            indexTmpBufBufU.array[indexTmpBufBufUBufCounterI] = thisDeserializer.readInt32();
        }
        indexTmpBuf.value1 = indexTmpBufBufU;
    }
    else
    {
        INTEROP_FATAL("One of the branches for indexTmpBuf has to be chosen through deserialisation.");
    }
    Ark_Union_I32_Array_I32 index = static_cast<Ark_Union_I32_Array_I32>(indexTmpBuf);
    callSyncMethod(vmContext, resourceId, selectItem, index);
}
void deserializeAndCallOnTextSelectionChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Int32 selectionStart,
                                                const Ark_Int32 selectionEnd)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_ONTEXTSELECTIONCHANGECALLBACK))));
    thisDeserializer.readPointer();
    Ark_Int32 selectionStart = thisDeserializer.readInt32();
    Ark_Int32 selectionEnd = thisDeserializer.readInt32();
    call(resourceId, selectionStart, selectionEnd);
}
void deserializeAndCallSyncOnTextSelectionChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                         Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int32 selectionStart,
                                  const Ark_Int32 selectionEnd)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_ONTEXTSELECTIONCHANGECALLBACK))));
    Ark_Int32 selectionStart = thisDeserializer.readInt32();
    Ark_Int32 selectionEnd = thisDeserializer.readInt32();
    callSyncMethod(vmContext, resourceId, selectionStart, selectionEnd);
}
void deserializeAndCallOnTimePickerChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_TimePickerResult result)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_ONTIMEPICKERCHANGECALLBACK))));
    thisDeserializer.readPointer();
    Ark_TimePickerResult result = TimePickerResult_serializer::read(thisDeserializer);
    call(resourceId, result);
}
void deserializeAndCallSyncOnTimePickerChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                      Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_TimePickerResult result)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_ONTIMEPICKERCHANGECALLBACK))));
    Ark_TimePickerResult result = TimePickerResult_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, result);
}
void deserializeAndCallOnViewportFitChangedCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, Ark_ViewportFit viewportFit)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_ONVIEWPORTFITCHANGEDCALLBACK))));
    thisDeserializer.readPointer();
    Ark_ViewportFit viewportFit = static_cast<Ark_ViewportFit>(thisDeserializer.readInt32());
    call(resourceId, viewportFit);
}
void deserializeAndCallSyncOnViewportFitChangedCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                        Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_ViewportFit viewportFit)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_ONVIEWPORTFITCHANGEDCALLBACK))));
    Ark_ViewportFit viewportFit = static_cast<Ark_ViewportFit>(thisDeserializer.readInt32());
    callSyncMethod(vmContext, resourceId, viewportFit);
}
void deserializeAndCallOnWillScrollCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Float64 scrollOffset,
                                                Ark_ScrollState scrollState, Ark_ScrollSource scrollSource,
                                                const Callback_Opt_ScrollResult_Void continuation)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_ONWILLSCROLLCALLBACK))));
    thisDeserializer.readPointer();
    Ark_Float64 scrollOffset = thisDeserializer.readFloat64();
    Ark_ScrollState scrollState = static_cast<Ark_ScrollState>(thisDeserializer.readInt32());
    Ark_ScrollSource scrollSource = static_cast<Ark_ScrollSource>(thisDeserializer.readInt32());
    Callback_Opt_ScrollResult_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Opt_ScrollResult value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_OPT_SCROLLRESULT_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_ScrollResult value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_CALLBACK_OPT_SCROLLRESULT_VOID))))};
    call(resourceId, scrollOffset, scrollState, scrollSource, continuationResult);
}
void deserializeAndCallSyncOnWillScrollCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(
        Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Float64 scrollOffset,
        Ark_ScrollState scrollState, Ark_ScrollSource scrollSource, const Callback_Opt_ScrollResult_Void continuation)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_ONWILLSCROLLCALLBACK))));
    Ark_Float64 scrollOffset = thisDeserializer.readFloat64();
    Ark_ScrollState scrollState = static_cast<Ark_ScrollState>(thisDeserializer.readInt32());
    Ark_ScrollSource scrollSource = static_cast<Ark_ScrollSource>(thisDeserializer.readInt32());
    Callback_Opt_ScrollResult_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Opt_ScrollResult value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_OPT_SCROLLRESULT_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_ScrollResult value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_CALLBACK_OPT_SCROLLRESULT_VOID))))};
    callSyncMethod(vmContext, resourceId, scrollOffset, scrollState, scrollSource, continuationResult);
}
void deserializeAndCallPageMapNodeBuilder(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Ark_String name,
                                  const Opt_Object param, const Callback_Pointer_Void continuation)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_PAGEMAPNODEBUILDER))));
    thisDeserializer.readPointer();
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_String name = static_cast<Ark_String>(thisDeserializer.readString());
    const auto paramTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Object paramTmpBuf = {};
    paramTmpBuf.tag = paramTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((paramTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        paramTmpBuf.value = static_cast<Ark_Object>(thisDeserializer.readObject());
    }
    Opt_Object param = paramTmpBuf;
    Callback_Pointer_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_POINTER_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_POINTER_VOID))))};
    call(resourceId, parentNode, name, param, continuationResult);
}
void deserializeAndCallSyncPageMapNodeBuilder(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                              Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<
        void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer parentNode,
                 const Ark_String name, const Opt_Object param, const Callback_Pointer_Void continuation)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_PAGEMAPNODEBUILDER))));
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_String name = static_cast<Ark_String>(thisDeserializer.readString());
    const auto paramTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Object paramTmpBuf = {};
    paramTmpBuf.tag = paramTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((paramTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        paramTmpBuf.value = static_cast<Ark_Object>(thisDeserializer.readObject());
    }
    Opt_Object param = paramTmpBuf;
    Callback_Pointer_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_POINTER_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_POINTER_VOID))))};
    callSyncMethod(vmContext, resourceId, parentNode, name, param, continuationResult);
}
void deserializeAndCallPasteButtonCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_ClickEvent event,
                                  Ark_PasteButtonOnClickResult result, const Opt_BusinessErrorInterface_Void error)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_PASTEBUTTONCALLBACK))));
    thisDeserializer.readPointer();
    Ark_ClickEvent event = static_cast<Ark_ClickEvent>(ClickEvent_serializer::read(thisDeserializer));
    Ark_PasteButtonOnClickResult result = static_cast<Ark_PasteButtonOnClickResult>(thisDeserializer.readInt32());
    const auto errorTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_BusinessErrorInterface_Void errorTmpBuf = {};
    errorTmpBuf.tag = errorTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((errorTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        errorTmpBuf.value = BusinessErrorInterface_Void_serializer::read(thisDeserializer);
    }
    Opt_BusinessErrorInterface_Void error = errorTmpBuf;
    call(resourceId, event, result, error);
}
void deserializeAndCallSyncPasteButtonCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                               Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_ClickEvent event,
                                  Ark_PasteButtonOnClickResult result, const Opt_BusinessErrorInterface_Void error)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_PASTEBUTTONCALLBACK))));
    Ark_ClickEvent event = static_cast<Ark_ClickEvent>(ClickEvent_serializer::read(thisDeserializer));
    Ark_PasteButtonOnClickResult result = static_cast<Ark_PasteButtonOnClickResult>(thisDeserializer.readInt32());
    const auto errorTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_BusinessErrorInterface_Void errorTmpBuf = {};
    errorTmpBuf.tag = errorTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((errorTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        errorTmpBuf.value = BusinessErrorInterface_Void_serializer::read(thisDeserializer);
    }
    Opt_BusinessErrorInterface_Void error = errorTmpBuf;
    callSyncMethod(vmContext, resourceId, event, result, error);
}
void deserializeAndCallPasteEventCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Opt_PasteEvent event)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_PASTEEVENTCALLBACK))));
    thisDeserializer.readPointer();
    const auto eventTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_PasteEvent eventTmpBuf = {};
    eventTmpBuf.tag = eventTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((eventTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        eventTmpBuf.value = static_cast<Ark_PasteEvent>(PasteEvent_serializer::read(thisDeserializer));
    }
    Opt_PasteEvent event = eventTmpBuf;
    call(resourceId, event);
}
void deserializeAndCallSyncPasteEventCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                              Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_PasteEvent event)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_PASTEEVENTCALLBACK))));
    const auto eventTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_PasteEvent eventTmpBuf = {};
    eventTmpBuf.tag = eventTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((eventTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        eventTmpBuf.value = static_cast<Ark_PasteEvent>(PasteEvent_serializer::read(thisDeserializer));
    }
    Opt_PasteEvent event = eventTmpBuf;
    callSyncMethod(vmContext, resourceId, event);
}
void deserializeAndCallPluginErrorCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_PluginErrorData info)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_PLUGINERRORCALLBACK))));
    thisDeserializer.readPointer();
    Ark_PluginErrorData info = PluginErrorData_serializer::read(thisDeserializer);
    call(resourceId, info);
}
void deserializeAndCallSyncPluginErrorCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                               Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_PluginErrorData info)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_PLUGINERRORCALLBACK))));
    Ark_PluginErrorData info = PluginErrorData_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, info);
}
void deserializeAndCallPopupStateChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_PopupStateChangeParam event)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_POPUPSTATECHANGECALLBACK))));
    thisDeserializer.readPointer();
    Ark_PopupStateChangeParam event = PopupStateChangeParam_serializer::read(thisDeserializer);
    call(resourceId, event);
}
void deserializeAndCallSyncPopupStateChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                    Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_PopupStateChangeParam event)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_POPUPSTATECHANGECALLBACK))));
    Ark_PopupStateChangeParam event = PopupStateChangeParam_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, event);
}
void deserializeAndCallProgressModifierBuilder(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_NativePointer parentNode,
                                  const Ark_ProgressConfiguration config, const Callback_Pointer_Void continuation)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_PROGRESSMODIFIERBUILDER))));
    thisDeserializer.readPointer();
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_ProgressConfiguration config = ProgressConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_POINTER_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_POINTER_VOID))))};
    call(resourceId, parentNode, config, continuationResult);
}
void deserializeAndCallSyncProgressModifierBuilder(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                   Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<
        void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer parentNode,
                 const Ark_ProgressConfiguration config, const Callback_Pointer_Void continuation)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_PROGRESSMODIFIERBUILDER))));
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_ProgressConfiguration config = ProgressConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_POINTER_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_POINTER_VOID))))};
    callSyncMethod(vmContext, resourceId, parentNode, config, continuationResult);
}
void deserializeAndCallRadioModifierBuilder(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_NativePointer parentNode,
                                  const Ark_RadioConfiguration config, const Callback_Pointer_Void continuation)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_RADIOMODIFIERBUILDER))));
    thisDeserializer.readPointer();
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_RadioConfiguration config = RadioConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_POINTER_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_POINTER_VOID))))};
    call(resourceId, parentNode, config, continuationResult);
}
void deserializeAndCallSyncRadioModifierBuilder(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<
        void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer parentNode,
                 const Ark_RadioConfiguration config, const Callback_Pointer_Void continuation)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_RADIOMODIFIERBUILDER))));
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_RadioConfiguration config = RadioConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_POINTER_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_POINTER_VOID))))};
    callSyncMethod(vmContext, resourceId, parentNode, config, continuationResult);
}
void deserializeAndCallRatingModifierBuilder(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_NativePointer parentNode,
                                  const Ark_RatingConfiguration config, const Callback_Pointer_Void continuation)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_RATINGMODIFIERBUILDER))));
    thisDeserializer.readPointer();
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_RatingConfiguration config = RatingConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_POINTER_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_POINTER_VOID))))};
    call(resourceId, parentNode, config, continuationResult);
}
void deserializeAndCallSyncRatingModifierBuilder(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                 Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<
        void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer parentNode,
                 const Ark_RatingConfiguration config, const Callback_Pointer_Void continuation)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_RATINGMODIFIERBUILDER))));
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_RatingConfiguration config = RatingConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_POINTER_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_POINTER_VOID))))};
    callSyncMethod(vmContext, resourceId, parentNode, config, continuationResult);
}
void deserializeAndCallRestrictedWorker_onerror_Callback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_ErrorEvent ev)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_RESTRICTEDWORKER_ONERROR_CALLBACK))));
    thisDeserializer.readPointer();
    Ark_ErrorEvent ev = ErrorEvent_serializer::read(thisDeserializer);
    call(resourceId, ev);
}
void deserializeAndCallSyncRestrictedWorker_onerror_Callback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                             Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_ErrorEvent ev)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_RESTRICTEDWORKER_ONERROR_CALLBACK))));
    Ark_ErrorEvent ev = ErrorEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, ev);
}
void deserializeAndCallRestrictedWorker_onexit_Callback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Number code)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_RESTRICTEDWORKER_ONEXIT_CALLBACK))));
    thisDeserializer.readPointer();
    Ark_Number code = static_cast<Ark_Number>(thisDeserializer.readNumber());
    call(resourceId, code);
}
void deserializeAndCallSyncRestrictedWorker_onexit_Callback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                            Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number code)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_RESTRICTEDWORKER_ONEXIT_CALLBACK))));
    Ark_Number code = static_cast<Ark_Number>(thisDeserializer.readNumber());
    callSyncMethod(vmContext, resourceId, code);
}
void deserializeAndCallRestrictedWorker_onmessage_Callback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_MessageEvents event)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_RESTRICTEDWORKER_ONMESSAGE_CALLBACK))));
    thisDeserializer.readPointer();
    Ark_MessageEvents event = MessageEvents_serializer::read(thisDeserializer);
    call(resourceId, event);
}
void deserializeAndCallSyncRestrictedWorker_onmessage_Callback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                               Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_MessageEvents event)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_RESTRICTEDWORKER_ONMESSAGE_CALLBACK))));
    Ark_MessageEvents event = MessageEvents_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, event);
}
void deserializeAndCallReuseIdCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const synthetic_Callback_String_Void continuation)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_REUSEIDCALLBACK))));
    thisDeserializer.readPointer();
    synthetic_Callback_String_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_String breakpoints)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SYNTHETIC_CALLBACK_STRING_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_String breakpoints)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_SYNTHETIC_CALLBACK_STRING_VOID))))};
    call(resourceId, continuationResult);
}
void deserializeAndCallSyncReuseIdCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const synthetic_Callback_String_Void continuation)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_REUSEIDCALLBACK))));
    synthetic_Callback_String_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_String breakpoints)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SYNTHETIC_CALLBACK_STRING_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_String breakpoints)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_SYNTHETIC_CALLBACK_STRING_VOID))))};
    callSyncMethod(vmContext, resourceId, continuationResult);
}
void deserializeAndCallRouterFinishCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_ROUTERFINISHCALLBACK))));
    thisDeserializer.readPointer();
    Ark_NativePointer value = thisDeserializer.readPointer();
    call(resourceId, value);
}
void deserializeAndCallSyncRouterFinishCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_ROUTERFINISHCALLBACK))));
    Ark_NativePointer value = thisDeserializer.readPointer();
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallSaveButtonCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_ClickEvent event,
                                  Ark_SaveButtonOnClickResult result, const Opt_BusinessErrorInterface_Void error)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SAVEBUTTONCALLBACK))));
    thisDeserializer.readPointer();
    Ark_ClickEvent event = static_cast<Ark_ClickEvent>(ClickEvent_serializer::read(thisDeserializer));
    Ark_SaveButtonOnClickResult result = static_cast<Ark_SaveButtonOnClickResult>(thisDeserializer.readInt32());
    const auto errorTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_BusinessErrorInterface_Void errorTmpBuf = {};
    errorTmpBuf.tag = errorTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((errorTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        errorTmpBuf.value = BusinessErrorInterface_Void_serializer::read(thisDeserializer);
    }
    Opt_BusinessErrorInterface_Void error = errorTmpBuf;
    call(resourceId, event, result, error);
}
void deserializeAndCallSyncSaveButtonCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                              Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_ClickEvent event,
                                  Ark_SaveButtonOnClickResult result, const Opt_BusinessErrorInterface_Void error)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_SAVEBUTTONCALLBACK))));
    Ark_ClickEvent event = static_cast<Ark_ClickEvent>(ClickEvent_serializer::read(thisDeserializer));
    Ark_SaveButtonOnClickResult result = static_cast<Ark_SaveButtonOnClickResult>(thisDeserializer.readInt32());
    const auto errorTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_BusinessErrorInterface_Void errorTmpBuf = {};
    errorTmpBuf.tag = errorTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((errorTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        errorTmpBuf.value = BusinessErrorInterface_Void_serializer::read(thisDeserializer);
    }
    Opt_BusinessErrorInterface_Void error = errorTmpBuf;
    callSyncMethod(vmContext, resourceId, event, result, error);
}
void deserializeAndCallScrollOnScrollCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Float64 xOffset,
                                                const Ark_Float64 yOffset, Ark_ScrollState scrollState)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SCROLLONSCROLLCALLBACK))));
    thisDeserializer.readPointer();
    Ark_Float64 xOffset = thisDeserializer.readFloat64();
    Ark_Float64 yOffset = thisDeserializer.readFloat64();
    Ark_ScrollState scrollState = static_cast<Ark_ScrollState>(thisDeserializer.readInt32());
    call(resourceId, xOffset, yOffset, scrollState);
}
void deserializeAndCallSyncScrollOnScrollCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                  Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Float64 xOffset,
                                  const Ark_Float64 yOffset, Ark_ScrollState scrollState)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_SCROLLONSCROLLCALLBACK))));
    Ark_Float64 xOffset = thisDeserializer.readFloat64();
    Ark_Float64 yOffset = thisDeserializer.readFloat64();
    Ark_ScrollState scrollState = static_cast<Ark_ScrollState>(thisDeserializer.readInt32());
    callSyncMethod(vmContext, resourceId, xOffset, yOffset, scrollState);
}
void deserializeAndCallScrollOnWillScrollCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(
        const Ark_Int32 resourceId, const Ark_Float64 xOffset, const Ark_Float64 yOffset, Ark_ScrollState scrollState,
        Ark_ScrollSource scrollSource, const Callback_Opt_OffsetResult_Void continuation)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SCROLLONWILLSCROLLCALLBACK))));
    thisDeserializer.readPointer();
    Ark_Float64 xOffset = thisDeserializer.readFloat64();
    Ark_Float64 yOffset = thisDeserializer.readFloat64();
    Ark_ScrollState scrollState = static_cast<Ark_ScrollState>(thisDeserializer.readInt32());
    Ark_ScrollSource scrollSource = static_cast<Ark_ScrollSource>(thisDeserializer.readInt32());
    Callback_Opt_OffsetResult_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Opt_OffsetResult value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_OPT_OFFSETRESULT_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_OffsetResult value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_CALLBACK_OPT_OFFSETRESULT_VOID))))};
    call(resourceId, xOffset, yOffset, scrollState, scrollSource, continuationResult);
}
void deserializeAndCallSyncScrollOnWillScrollCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                      Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(
        Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Float64 xOffset, const Ark_Float64 yOffset,
        Ark_ScrollState scrollState, Ark_ScrollSource scrollSource, const Callback_Opt_OffsetResult_Void continuation)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_SCROLLONWILLSCROLLCALLBACK))));
    Ark_Float64 xOffset = thisDeserializer.readFloat64();
    Ark_Float64 yOffset = thisDeserializer.readFloat64();
    Ark_ScrollState scrollState = static_cast<Ark_ScrollState>(thisDeserializer.readInt32());
    Ark_ScrollSource scrollSource = static_cast<Ark_ScrollSource>(thisDeserializer.readInt32());
    Callback_Opt_OffsetResult_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Opt_OffsetResult value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_OPT_OFFSETRESULT_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_OffsetResult value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_CALLBACK_OPT_OFFSETRESULT_VOID))))};
    callSyncMethod(vmContext, resourceId, xOffset, yOffset, scrollState, scrollSource, continuationResult);
}
void deserializeAndCallSearchSubmitCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_String searchContent,
                                                const Opt_SubmitEvent event)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SEARCHSUBMITCALLBACK))));
    thisDeserializer.readPointer();
    Ark_String searchContent = static_cast<Ark_String>(thisDeserializer.readString());
    const auto eventTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_SubmitEvent eventTmpBuf = {};
    eventTmpBuf.tag = eventTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((eventTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        eventTmpBuf.value = static_cast<Ark_SubmitEvent>(SubmitEvent_serializer::read(thisDeserializer));
    }
    Opt_SubmitEvent event = eventTmpBuf;
    call(resourceId, searchContent, event);
}
void deserializeAndCallSyncSearchSubmitCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_String searchContent, const Opt_SubmitEvent event)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_SEARCHSUBMITCALLBACK))));
    Ark_String searchContent = static_cast<Ark_String>(thisDeserializer.readString());
    const auto eventTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_SubmitEvent eventTmpBuf = {};
    eventTmpBuf.tag = eventTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((eventTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        eventTmpBuf.value = static_cast<Ark_SubmitEvent>(SubmitEvent_serializer::read(thisDeserializer));
    }
    Opt_SubmitEvent event = eventTmpBuf;
    callSyncMethod(vmContext, resourceId, searchContent, event);
}
void deserializeAndCallSearchValueCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_String value)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SEARCHVALUECALLBACK))));
    thisDeserializer.readPointer();
    Ark_String value = static_cast<Ark_String>(thisDeserializer.readString());
    call(resourceId, value);
}
void deserializeAndCallSyncSearchValueCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                               Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_String value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_SEARCHVALUECALLBACK))));
    Ark_String value = static_cast<Ark_String>(thisDeserializer.readString());
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallShouldBuiltInRecognizerParallelWithCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_GestureRecognizer current,
                                                const Array_GestureRecognizer others,
                                                const Callback_GestureRecognizer_Void continuation)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCaller(KIND_SHOULDBUILTINRECOGNIZERPARALLELWITHCALLBACK))));
    thisDeserializer.readPointer();
    Ark_GestureRecognizer current = static_cast<Ark_GestureRecognizer>(
        GestureRecognizer_serializer::read(thisDeserializer));
    const Ark_Int32 othersTmpBufLength = thisDeserializer.readInt32();
    Array_GestureRecognizer othersTmpBuf = {};
    thisDeserializer.resizeArray<std::decay<decltype(othersTmpBuf)>::type,
                                 std::decay<decltype(*othersTmpBuf.array)>::type>(&othersTmpBuf, othersTmpBufLength);
    for (int othersTmpBufBufCounterI = 0; othersTmpBufBufCounterI < othersTmpBufLength; othersTmpBufBufCounterI++)
    {
        othersTmpBuf.array[othersTmpBufBufCounterI] = static_cast<Ark_GestureRecognizer>(
            GestureRecognizer_serializer::read(thisDeserializer));
    }
    Array_GestureRecognizer others = othersTmpBuf;
    Callback_GestureRecognizer_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_GestureRecognizer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_GESTURERECOGNIZER_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                  const Ark_GestureRecognizer value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_CALLBACK_GESTURERECOGNIZER_VOID))))};
    call(resourceId, current, others, continuationResult);
}
void deserializeAndCallSyncShouldBuiltInRecognizerParallelWithCallback(Ark_VMContext vmContext,
                                                                       KSerializerBuffer thisArray,
                                                                       Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<
        void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_GestureRecognizer current,
                 const Array_GestureRecognizer others, const Callback_GestureRecognizer_Void continuation)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCallerSync(KIND_SHOULDBUILTINRECOGNIZERPARALLELWITHCALLBACK))));
    Ark_GestureRecognizer current = static_cast<Ark_GestureRecognizer>(
        GestureRecognizer_serializer::read(thisDeserializer));
    const Ark_Int32 othersTmpBufLength = thisDeserializer.readInt32();
    Array_GestureRecognizer othersTmpBuf = {};
    thisDeserializer.resizeArray<std::decay<decltype(othersTmpBuf)>::type,
                                 std::decay<decltype(*othersTmpBuf.array)>::type>(&othersTmpBuf, othersTmpBufLength);
    for (int othersTmpBufBufCounterI = 0; othersTmpBufBufCounterI < othersTmpBufLength; othersTmpBufBufCounterI++)
    {
        othersTmpBuf.array[othersTmpBufBufCounterI] = static_cast<Ark_GestureRecognizer>(
            GestureRecognizer_serializer::read(thisDeserializer));
    }
    Array_GestureRecognizer others = othersTmpBuf;
    Callback_GestureRecognizer_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_GestureRecognizer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_GESTURERECOGNIZER_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                  const Ark_GestureRecognizer value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_CALLBACK_GESTURERECOGNIZER_VOID))))};
    callSyncMethod(vmContext, resourceId, current, others, continuationResult);
}
void deserializeAndCallSizeChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_SizeOptions oldValue,
                                                const Ark_SizeOptions newValue)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SIZECHANGECALLBACK))));
    thisDeserializer.readPointer();
    Ark_SizeOptions oldValue = SizeOptions_serializer::read(thisDeserializer);
    Ark_SizeOptions newValue = SizeOptions_serializer::read(thisDeserializer);
    call(resourceId, oldValue, newValue);
}
void deserializeAndCallSyncSizeChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                              Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_SizeOptions oldValue,
                                  const Ark_SizeOptions newValue)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_SIZECHANGECALLBACK))));
    Ark_SizeOptions oldValue = SizeOptions_serializer::read(thisDeserializer);
    Ark_SizeOptions newValue = SizeOptions_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, oldValue, newValue);
}
void deserializeAndCallSliderModifierBuilder(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_NativePointer parentNode,
                                  const Ark_SliderConfiguration config, const Callback_Pointer_Void continuation)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SLIDERMODIFIERBUILDER))));
    thisDeserializer.readPointer();
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_SliderConfiguration config = SliderConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_POINTER_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_POINTER_VOID))))};
    call(resourceId, parentNode, config, continuationResult);
}
void deserializeAndCallSyncSliderModifierBuilder(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                 Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<
        void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer parentNode,
                 const Ark_SliderConfiguration config, const Callback_Pointer_Void continuation)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_SLIDERMODIFIERBUILDER))));
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_SliderConfiguration config = SliderConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_POINTER_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_POINTER_VOID))))};
    callSyncMethod(vmContext, resourceId, parentNode, config, continuationResult);
}
void deserializeAndCallSliderTriggerChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Float64 value, Ark_SliderChangeMode mode)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SLIDERTRIGGERCHANGECALLBACK))));
    thisDeserializer.readPointer();
    Ark_Float64 value = thisDeserializer.readFloat64();
    Ark_SliderChangeMode mode = static_cast<Ark_SliderChangeMode>(thisDeserializer.readInt32());
    call(resourceId, value, mode);
}
void deserializeAndCallSyncSliderTriggerChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                       Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_Float64 value, Ark_SliderChangeMode mode)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_SLIDERTRIGGERCHANGECALLBACK))));
    Ark_Float64 value = thisDeserializer.readFloat64();
    Ark_SliderChangeMode mode = static_cast<Ark_SliderChangeMode>(thisDeserializer.readInt32());
    callSyncMethod(vmContext, resourceId, value, mode);
}
void deserializeAndCallStyledStringMarshallCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Object marshallableVal,
                                                const Callback_Buffer_Void continuation)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_STYLEDSTRINGMARSHALLCALLBACK))));
    thisDeserializer.readPointer();
    Ark_UserDataSpan marshallableVal = static_cast<Ark_UserDataSpan>(thisDeserializer.readObject());
    Callback_Buffer_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Buffer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_BUFFER_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Buffer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_BUFFER_VOID))))};
    call(resourceId, marshallableVal, continuationResult);
}
void deserializeAndCallSyncStyledStringMarshallCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                        Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Object marshallableVal,
                                  const Callback_Buffer_Void continuation)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_STYLEDSTRINGMARSHALLCALLBACK))));
    Ark_UserDataSpan marshallableVal = static_cast<Ark_UserDataSpan>(thisDeserializer.readObject());
    Callback_Buffer_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Buffer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_BUFFER_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Buffer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_BUFFER_VOID))))};
    callSyncMethod(vmContext, resourceId, marshallableVal, continuationResult);
}
void deserializeAndCallStyledStringUnmarshallCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Buffer buf,
                                                const Callback_UserDataSpan_Void continuation)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_STYLEDSTRINGUNMARSHALLCALLBACK))));
    thisDeserializer.readPointer();
    Ark_Buffer buf = static_cast<Ark_Buffer>(thisDeserializer.readBuffer());
    Callback_UserDataSpan_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Object value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_USERDATASPAN_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Object value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_USERDATASPAN_VOID))))};
    call(resourceId, buf, continuationResult);
}
void deserializeAndCallSyncStyledStringUnmarshallCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                          Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Buffer buf,
                                  const Callback_UserDataSpan_Void continuation)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_STYLEDSTRINGUNMARSHALLCALLBACK))));
    Ark_Buffer buf = static_cast<Ark_Buffer>(thisDeserializer.readBuffer());
    Callback_UserDataSpan_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Object value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_USERDATASPAN_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Object value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_USERDATASPAN_VOID))))};
    callSyncMethod(vmContext, resourceId, buf, continuationResult);
}
void deserializeAndCallSubmitCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, Ark_EnterKeyType enterKey, const Ark_SubmitEvent event)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SUBMITCALLBACK))));
    thisDeserializer.readPointer();
    Ark_EnterKeyType enterKey = static_cast<Ark_EnterKeyType>(thisDeserializer.readInt32());
    Ark_SubmitEvent event = static_cast<Ark_SubmitEvent>(SubmitEvent_serializer::read(thisDeserializer));
    call(resourceId, enterKey, event);
}
void deserializeAndCallSyncSubmitCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          Ark_EnterKeyType enterKey, const Ark_SubmitEvent event)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_SUBMITCALLBACK))));
    Ark_EnterKeyType enterKey = static_cast<Ark_EnterKeyType>(thisDeserializer.readInt32());
    Ark_SubmitEvent event = static_cast<Ark_SubmitEvent>(SubmitEvent_serializer::read(thisDeserializer));
    callSyncMethod(vmContext, resourceId, enterKey, event);
}
void deserializeAndCallsynthetic_AsyncCallback_image_PixelMap_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_image_PixelMap result)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCaller(KIND_SYNTHETIC_ASYNCCALLBACK_IMAGE_PIXELMAP_VOID))));
    thisDeserializer.readPointer();
    Ark_image_PixelMap result = static_cast<Ark_image_PixelMap>(image_PixelMap_serializer::read(thisDeserializer));
    call(resourceId, result);
}
void deserializeAndCallSyncsynthetic_AsyncCallback_image_PixelMap_Void(Ark_VMContext vmContext,
                                                                       KSerializerBuffer thisArray,
                                                                       Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_image_PixelMap result)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCallerSync(KIND_SYNTHETIC_ASYNCCALLBACK_IMAGE_PIXELMAP_VOID))));
    Ark_image_PixelMap result = static_cast<Ark_image_PixelMap>(image_PixelMap_serializer::read(thisDeserializer));
    callSyncMethod(vmContext, resourceId, result);
}
void deserializeAndCallsynthetic_Callback_Array_String_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Array_String value)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SYNTHETIC_CALLBACK_ARRAY_STRING_VOID))));
    thisDeserializer.readPointer();
    const Ark_Int32 valueTmpBufLength = thisDeserializer.readInt32();
    Array_String valueTmpBuf = {};
    thisDeserializer.resizeArray<std::decay<decltype(valueTmpBuf)>::type,
                                 std::decay<decltype(*valueTmpBuf.array)>::type>(&valueTmpBuf, valueTmpBufLength);
    for (int valueTmpBufBufCounterI = 0; valueTmpBufBufCounterI < valueTmpBufLength; valueTmpBufBufCounterI++)
    {
        valueTmpBuf.array[valueTmpBufBufCounterI] = static_cast<Ark_String>(thisDeserializer.readString());
    }
    Array_String value = valueTmpBuf;
    call(resourceId, value);
}
void deserializeAndCallSyncsynthetic_Callback_Array_String_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                                Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Array_String value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_SYNTHETIC_CALLBACK_ARRAY_STRING_VOID))));
    const Ark_Int32 valueTmpBufLength = thisDeserializer.readInt32();
    Array_String valueTmpBuf = {};
    thisDeserializer.resizeArray<std::decay<decltype(valueTmpBuf)>::type,
                                 std::decay<decltype(*valueTmpBuf.array)>::type>(&valueTmpBuf, valueTmpBufLength);
    for (int valueTmpBufBufCounterI = 0; valueTmpBufBufCounterI < valueTmpBufLength; valueTmpBufBufCounterI++)
    {
        valueTmpBuf.array[valueTmpBufBufCounterI] = static_cast<Ark_String>(thisDeserializer.readString());
    }
    Array_String value = valueTmpBuf;
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallsynthetic_Callback_Boolean_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID))));
    thisDeserializer.readPointer();
    Ark_Boolean isSelected = thisDeserializer.readBoolean();
    call(resourceId, isSelected);
}
void deserializeAndCallSyncsynthetic_Callback_Boolean_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                           Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID))));
    Ark_Boolean isSelected = thisDeserializer.readBoolean();
    callSyncMethod(vmContext, resourceId, isSelected);
}
void deserializeAndCallsynthetic_Callback_DismissDialogAction_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_DismissDialogAction value0)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCaller(KIND_SYNTHETIC_CALLBACK_DISMISSDIALOGACTION_VOID))));
    thisDeserializer.readPointer();
    Ark_DismissDialogAction value0 = static_cast<Ark_DismissDialogAction>(
        DismissDialogAction_serializer::read(thisDeserializer));
    call(resourceId, value0);
}
void deserializeAndCallSyncsynthetic_Callback_DismissDialogAction_Void(Ark_VMContext vmContext,
                                                                       KSerializerBuffer thisArray,
                                                                       Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_DismissDialogAction value0)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCallerSync(KIND_SYNTHETIC_CALLBACK_DISMISSDIALOGACTION_VOID))));
    Ark_DismissDialogAction value0 = static_cast<Ark_DismissDialogAction>(
        DismissDialogAction_serializer::read(thisDeserializer));
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallsynthetic_Callback_F64_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Float64 progress)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SYNTHETIC_CALLBACK_F64_VOID))));
    thisDeserializer.readPointer();
    Ark_Float64 progress = thisDeserializer.readFloat64();
    call(resourceId, progress);
}
void deserializeAndCallSyncsynthetic_Callback_F64_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                       Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Float64 progress)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_SYNTHETIC_CALLBACK_F64_VOID))));
    Ark_Float64 progress = thisDeserializer.readFloat64();
    callSyncMethod(vmContext, resourceId, progress);
}
void deserializeAndCallsynthetic_Callback_KeyEvent_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_KeyEvent event,
                                                const synthetic_Callback_Boolean_Void continuation)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SYNTHETIC_CALLBACK_KEYEVENT_BOOLEAN))));
    thisDeserializer.readPointer();
    Ark_KeyEvent event = static_cast<Ark_KeyEvent>(KeyEvent_serializer::read(thisDeserializer));
    synthetic_Callback_Boolean_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID))))};
    call(resourceId, event, continuationResult);
}
void deserializeAndCallSyncsynthetic_Callback_KeyEvent_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                               Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_KeyEvent event,
                                  const synthetic_Callback_Boolean_Void continuation)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_SYNTHETIC_CALLBACK_KEYEVENT_BOOLEAN))));
    Ark_KeyEvent event = static_cast<Ark_KeyEvent>(KeyEvent_serializer::read(thisDeserializer));
    synthetic_Callback_Boolean_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isSelected)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID))))};
    callSyncMethod(vmContext, resourceId, event, continuationResult);
}
void deserializeAndCallsynthetic_Callback_String_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_String breakpoints)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SYNTHETIC_CALLBACK_STRING_VOID))));
    thisDeserializer.readPointer();
    Ark_String breakpoints = static_cast<Ark_String>(thisDeserializer.readString());
    call(resourceId, breakpoints);
}
void deserializeAndCallSyncsynthetic_Callback_String_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                          Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_String breakpoints)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_SYNTHETIC_CALLBACK_STRING_VOID))));
    Ark_String breakpoints = static_cast<Ark_String>(thisDeserializer.readString());
    callSyncMethod(vmContext, resourceId, breakpoints);
}
void deserializeAndCallsynthetic_Callback_TextPickerResult_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_TextPickerResult value)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCaller(KIND_SYNTHETIC_CALLBACK_TEXTPICKERRESULT_VOID))));
    thisDeserializer.readPointer();
    Ark_TextPickerResult value = TextPickerResult_serializer::read(thisDeserializer);
    call(resourceId, value);
}
void deserializeAndCallSyncsynthetic_Callback_TextPickerResult_Void(Ark_VMContext vmContext,
                                                                    KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_TextPickerResult value)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCallerSync(KIND_SYNTHETIC_CALLBACK_TEXTPICKERRESULT_VOID))));
    Ark_TextPickerResult value = TextPickerResult_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallsynthetic_Callback_TimePickerResult_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_TimePickerResult value)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCaller(KIND_SYNTHETIC_CALLBACK_TIMEPICKERRESULT_VOID))));
    thisDeserializer.readPointer();
    Ark_TimePickerResult value = TimePickerResult_serializer::read(thisDeserializer);
    call(resourceId, value);
}
void deserializeAndCallSyncsynthetic_Callback_TimePickerResult_Void(Ark_VMContext vmContext,
                                                                    KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_TimePickerResult value)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCallerSync(KIND_SYNTHETIC_CALLBACK_TIMEPICKERRESULT_VOID))));
    Ark_TimePickerResult value = TimePickerResult_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallsynthetic_Callback_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId)>(thisDeserializer.readPointerOrDefault(
        reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_SYNTHETIC_CALLBACK_VOID))));
    thisDeserializer.readPointer();
    call(resourceId);
}
void deserializeAndCallSyncsynthetic_Callback_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                   Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_SYNTHETIC_CALLBACK_VOID))));
    callSyncMethod(vmContext, resourceId);
}
void deserializeAndCallTabsCustomContentTransitionCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Int32 from, const Ark_Int32 to,
                                                const Callback_Opt_TabContentAnimatedTransition_Void continuation)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_TABSCUSTOMCONTENTTRANSITIONCALLBACK))));
    thisDeserializer.readPointer();
    Ark_Int32 from = thisDeserializer.readInt32();
    Ark_Int32 to = thisDeserializer.readInt32();
    Callback_Opt_TabContentAnimatedTransition_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Opt_TabContentAnimatedTransition value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCaller(KIND_CALLBACK_OPT_TABCONTENTANIMATEDTRANSITION_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                  const Opt_TabContentAnimatedTransition value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_CALLBACK_OPT_TABCONTENTANIMATEDTRANSITION_VOID))))};
    call(resourceId, from, to, continuationResult);
}
void deserializeAndCallSyncTabsCustomContentTransitionCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                               Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<
        void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int32 from, const Ark_Int32 to,
                 const Callback_Opt_TabContentAnimatedTransition_Void continuation)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCallerSync(KIND_TABSCUSTOMCONTENTTRANSITIONCALLBACK))));
    Ark_Int32 from = thisDeserializer.readInt32();
    Ark_Int32 to = thisDeserializer.readInt32();
    Callback_Opt_TabContentAnimatedTransition_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Opt_TabContentAnimatedTransition value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCaller(KIND_CALLBACK_OPT_TABCONTENTANIMATEDTRANSITION_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                  const Opt_TabContentAnimatedTransition value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_CALLBACK_OPT_TABCONTENTANIMATEDTRANSITION_VOID))))};
    callSyncMethod(vmContext, resourceId, from, to, continuationResult);
}
void deserializeAndCallTextAreaSubmitCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, Ark_EnterKeyType enterKeyType,
                                                const Opt_SubmitEvent event)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_TEXTAREASUBMITCALLBACK))));
    thisDeserializer.readPointer();
    Ark_EnterKeyType enterKeyType = static_cast<Ark_EnterKeyType>(thisDeserializer.readInt32());
    const auto eventTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_SubmitEvent eventTmpBuf = {};
    eventTmpBuf.tag = eventTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((eventTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        eventTmpBuf.value = static_cast<Ark_SubmitEvent>(SubmitEvent_serializer::read(thisDeserializer));
    }
    Opt_SubmitEvent event = eventTmpBuf;
    call(resourceId, enterKeyType, event);
}
void deserializeAndCallSyncTextAreaSubmitCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                  Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          Ark_EnterKeyType enterKeyType, const Opt_SubmitEvent event)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_TEXTAREASUBMITCALLBACK))));
    Ark_EnterKeyType enterKeyType = static_cast<Ark_EnterKeyType>(thisDeserializer.readInt32());
    const auto eventTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_SubmitEvent eventTmpBuf = {};
    eventTmpBuf.tag = eventTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((eventTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        eventTmpBuf.value = static_cast<Ark_SubmitEvent>(SubmitEvent_serializer::read(thisDeserializer));
    }
    Opt_SubmitEvent event = eventTmpBuf;
    callSyncMethod(vmContext, resourceId, enterKeyType, event);
}
void deserializeAndCallTextClockModifierBuilder(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_NativePointer parentNode,
                                  const Ark_TextClockConfiguration config, const Callback_Pointer_Void continuation)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_TEXTCLOCKMODIFIERBUILDER))));
    thisDeserializer.readPointer();
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_TextClockConfiguration config = TextClockConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_POINTER_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_POINTER_VOID))))};
    call(resourceId, parentNode, config, continuationResult);
}
void deserializeAndCallSyncTextClockModifierBuilder(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                    Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<
        void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer parentNode,
                 const Ark_TextClockConfiguration config, const Callback_Pointer_Void continuation)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_TEXTCLOCKMODIFIERBUILDER))));
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_TextClockConfiguration config = TextClockConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_POINTER_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_POINTER_VOID))))};
    callSyncMethod(vmContext, resourceId, parentNode, config, continuationResult);
}
void deserializeAndCallTextFieldValueCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_ResourceStr value)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_TEXTFIELDVALUECALLBACK))));
    thisDeserializer.readPointer();
    const Ark_Int8 valueTmpBufUnionSelector = thisDeserializer.readInt8();
    Ark_ResourceStr valueTmpBuf = {};
    valueTmpBuf.selector = valueTmpBufUnionSelector;
    if (valueTmpBufUnionSelector == 0)
    {
        valueTmpBuf.selector = 0;
        valueTmpBuf.value0 = static_cast<Ark_String>(thisDeserializer.readString());
    }
    else if (valueTmpBufUnionSelector == 1)
    {
        valueTmpBuf.selector = 1;
        valueTmpBuf.value1 = Resource_serializer::read(thisDeserializer);
    }
    else
    {
        INTEROP_FATAL("One of the branches for valueTmpBuf has to be chosen through deserialisation.");
    }
    Ark_ResourceStr value = static_cast<Ark_ResourceStr>(valueTmpBuf);
    call(resourceId, value);
}
void deserializeAndCallSyncTextFieldValueCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                  Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_ResourceStr value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_TEXTFIELDVALUECALLBACK))));
    const Ark_Int8 valueTmpBufUnionSelector = thisDeserializer.readInt8();
    Ark_ResourceStr valueTmpBuf = {};
    valueTmpBuf.selector = valueTmpBufUnionSelector;
    if (valueTmpBufUnionSelector == 0)
    {
        valueTmpBuf.selector = 0;
        valueTmpBuf.value0 = static_cast<Ark_String>(thisDeserializer.readString());
    }
    else if (valueTmpBufUnionSelector == 1)
    {
        valueTmpBuf.selector = 1;
        valueTmpBuf.value1 = Resource_serializer::read(thisDeserializer);
    }
    else
    {
        INTEROP_FATAL("One of the branches for valueTmpBuf has to be chosen through deserialisation.");
    }
    Ark_ResourceStr value = static_cast<Ark_ResourceStr>(valueTmpBuf);
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallTextPickerEnterSelectedAreaCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Union_String_Array_String value,
                                                const Ark_Union_I32_Array_I32 index)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_TEXTPICKERENTERSELECTEDAREACALLBACK))));
    thisDeserializer.readPointer();
    const Ark_Int8 valueTmpBufUnionSelector = thisDeserializer.readInt8();
    Ark_Union_String_Array_String valueTmpBuf = {};
    valueTmpBuf.selector = valueTmpBufUnionSelector;
    if (valueTmpBufUnionSelector == 0)
    {
        valueTmpBuf.selector = 0;
        valueTmpBuf.value0 = static_cast<Ark_String>(thisDeserializer.readString());
    }
    else if (valueTmpBufUnionSelector == 1)
    {
        valueTmpBuf.selector = 1;
        const Ark_Int32 valueTmpBufBufULength = thisDeserializer.readInt32();
        Array_String valueTmpBufBufU = {};
        thisDeserializer.resizeArray<std::decay<decltype(valueTmpBufBufU)>::type,
                                     std::decay<decltype(*valueTmpBufBufU.array)>::type>(&valueTmpBufBufU,
                                                                                         valueTmpBufBufULength);
        for (int valueTmpBufBufUBufCounterI = 0; valueTmpBufBufUBufCounterI < valueTmpBufBufULength;
             valueTmpBufBufUBufCounterI++)
        {
            valueTmpBufBufU.array[valueTmpBufBufUBufCounterI] = static_cast<Ark_String>(thisDeserializer.readString());
        }
        valueTmpBuf.value1 = valueTmpBufBufU;
    }
    else
    {
        INTEROP_FATAL("One of the branches for valueTmpBuf has to be chosen through deserialisation.");
    }
    Ark_Union_String_Array_String value = static_cast<Ark_Union_String_Array_String>(valueTmpBuf);
    const Ark_Int8 indexTmpBufUnionSelector = thisDeserializer.readInt8();
    Ark_Union_I32_Array_I32 indexTmpBuf = {};
    indexTmpBuf.selector = indexTmpBufUnionSelector;
    if (indexTmpBufUnionSelector == 0)
    {
        indexTmpBuf.selector = 0;
        indexTmpBuf.value0 = thisDeserializer.readInt32();
    }
    else if (indexTmpBufUnionSelector == 1)
    {
        indexTmpBuf.selector = 1;
        const Ark_Int32 indexTmpBufBufULength = thisDeserializer.readInt32();
        Array_I32 indexTmpBufBufU = {};
        thisDeserializer.resizeArray<std::decay<decltype(indexTmpBufBufU)>::type,
                                     std::decay<decltype(*indexTmpBufBufU.array)>::type>(&indexTmpBufBufU,
                                                                                         indexTmpBufBufULength);
        for (int indexTmpBufBufUBufCounterI = 0; indexTmpBufBufUBufCounterI < indexTmpBufBufULength;
             indexTmpBufBufUBufCounterI++)
        {
            indexTmpBufBufU.array[indexTmpBufBufUBufCounterI] = thisDeserializer.readInt32();
        }
        indexTmpBuf.value1 = indexTmpBufBufU;
    }
    else
    {
        INTEROP_FATAL("One of the branches for indexTmpBuf has to be chosen through deserialisation.");
    }
    Ark_Union_I32_Array_I32 index = static_cast<Ark_Union_I32_Array_I32>(indexTmpBuf);
    call(resourceId, value, index);
}
void deserializeAndCallSyncTextPickerEnterSelectedAreaCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                               Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                  const Ark_Union_String_Array_String value, const Ark_Union_I32_Array_I32 index)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_TEXTPICKERENTERSELECTEDAREACALLBACK))));
    const Ark_Int8 valueTmpBufUnionSelector = thisDeserializer.readInt8();
    Ark_Union_String_Array_String valueTmpBuf = {};
    valueTmpBuf.selector = valueTmpBufUnionSelector;
    if (valueTmpBufUnionSelector == 0)
    {
        valueTmpBuf.selector = 0;
        valueTmpBuf.value0 = static_cast<Ark_String>(thisDeserializer.readString());
    }
    else if (valueTmpBufUnionSelector == 1)
    {
        valueTmpBuf.selector = 1;
        const Ark_Int32 valueTmpBufBufULength = thisDeserializer.readInt32();
        Array_String valueTmpBufBufU = {};
        thisDeserializer.resizeArray<std::decay<decltype(valueTmpBufBufU)>::type,
                                     std::decay<decltype(*valueTmpBufBufU.array)>::type>(&valueTmpBufBufU,
                                                                                         valueTmpBufBufULength);
        for (int valueTmpBufBufUBufCounterI = 0; valueTmpBufBufUBufCounterI < valueTmpBufBufULength;
             valueTmpBufBufUBufCounterI++)
        {
            valueTmpBufBufU.array[valueTmpBufBufUBufCounterI] = static_cast<Ark_String>(thisDeserializer.readString());
        }
        valueTmpBuf.value1 = valueTmpBufBufU;
    }
    else
    {
        INTEROP_FATAL("One of the branches for valueTmpBuf has to be chosen through deserialisation.");
    }
    Ark_Union_String_Array_String value = static_cast<Ark_Union_String_Array_String>(valueTmpBuf);
    const Ark_Int8 indexTmpBufUnionSelector = thisDeserializer.readInt8();
    Ark_Union_I32_Array_I32 indexTmpBuf = {};
    indexTmpBuf.selector = indexTmpBufUnionSelector;
    if (indexTmpBufUnionSelector == 0)
    {
        indexTmpBuf.selector = 0;
        indexTmpBuf.value0 = thisDeserializer.readInt32();
    }
    else if (indexTmpBufUnionSelector == 1)
    {
        indexTmpBuf.selector = 1;
        const Ark_Int32 indexTmpBufBufULength = thisDeserializer.readInt32();
        Array_I32 indexTmpBufBufU = {};
        thisDeserializer.resizeArray<std::decay<decltype(indexTmpBufBufU)>::type,
                                     std::decay<decltype(*indexTmpBufBufU.array)>::type>(&indexTmpBufBufU,
                                                                                         indexTmpBufBufULength);
        for (int indexTmpBufBufUBufCounterI = 0; indexTmpBufBufUBufCounterI < indexTmpBufBufULength;
             indexTmpBufBufUBufCounterI++)
        {
            indexTmpBufBufU.array[indexTmpBufBufUBufCounterI] = thisDeserializer.readInt32();
        }
        indexTmpBuf.value1 = indexTmpBufBufU;
    }
    else
    {
        INTEROP_FATAL("One of the branches for indexTmpBuf has to be chosen through deserialisation.");
    }
    Ark_Union_I32_Array_I32 index = static_cast<Ark_Union_I32_Array_I32>(indexTmpBuf);
    callSyncMethod(vmContext, resourceId, value, index);
}
void deserializeAndCallTextPickerScrollStopCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Union_String_Array_String value,
                                                const Ark_Union_I32_Array_I32 index)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_TEXTPICKERSCROLLSTOPCALLBACK))));
    thisDeserializer.readPointer();
    const Ark_Int8 valueTmpBufUnionSelector = thisDeserializer.readInt8();
    Ark_Union_String_Array_String valueTmpBuf = {};
    valueTmpBuf.selector = valueTmpBufUnionSelector;
    if (valueTmpBufUnionSelector == 0)
    {
        valueTmpBuf.selector = 0;
        valueTmpBuf.value0 = static_cast<Ark_String>(thisDeserializer.readString());
    }
    else if (valueTmpBufUnionSelector == 1)
    {
        valueTmpBuf.selector = 1;
        const Ark_Int32 valueTmpBufBufULength = thisDeserializer.readInt32();
        Array_String valueTmpBufBufU = {};
        thisDeserializer.resizeArray<std::decay<decltype(valueTmpBufBufU)>::type,
                                     std::decay<decltype(*valueTmpBufBufU.array)>::type>(&valueTmpBufBufU,
                                                                                         valueTmpBufBufULength);
        for (int valueTmpBufBufUBufCounterI = 0; valueTmpBufBufUBufCounterI < valueTmpBufBufULength;
             valueTmpBufBufUBufCounterI++)
        {
            valueTmpBufBufU.array[valueTmpBufBufUBufCounterI] = static_cast<Ark_String>(thisDeserializer.readString());
        }
        valueTmpBuf.value1 = valueTmpBufBufU;
    }
    else
    {
        INTEROP_FATAL("One of the branches for valueTmpBuf has to be chosen through deserialisation.");
    }
    Ark_Union_String_Array_String value = static_cast<Ark_Union_String_Array_String>(valueTmpBuf);
    const Ark_Int8 indexTmpBufUnionSelector = thisDeserializer.readInt8();
    Ark_Union_I32_Array_I32 indexTmpBuf = {};
    indexTmpBuf.selector = indexTmpBufUnionSelector;
    if (indexTmpBufUnionSelector == 0)
    {
        indexTmpBuf.selector = 0;
        indexTmpBuf.value0 = thisDeserializer.readInt32();
    }
    else if (indexTmpBufUnionSelector == 1)
    {
        indexTmpBuf.selector = 1;
        const Ark_Int32 indexTmpBufBufULength = thisDeserializer.readInt32();
        Array_I32 indexTmpBufBufU = {};
        thisDeserializer.resizeArray<std::decay<decltype(indexTmpBufBufU)>::type,
                                     std::decay<decltype(*indexTmpBufBufU.array)>::type>(&indexTmpBufBufU,
                                                                                         indexTmpBufBufULength);
        for (int indexTmpBufBufUBufCounterI = 0; indexTmpBufBufUBufCounterI < indexTmpBufBufULength;
             indexTmpBufBufUBufCounterI++)
        {
            indexTmpBufBufU.array[indexTmpBufBufUBufCounterI] = thisDeserializer.readInt32();
        }
        indexTmpBuf.value1 = indexTmpBufBufU;
    }
    else
    {
        INTEROP_FATAL("One of the branches for indexTmpBuf has to be chosen through deserialisation.");
    }
    Ark_Union_I32_Array_I32 index = static_cast<Ark_Union_I32_Array_I32>(indexTmpBuf);
    call(resourceId, value, index);
}
void deserializeAndCallSyncTextPickerScrollStopCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                        Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                  const Ark_Union_String_Array_String value, const Ark_Union_I32_Array_I32 index)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_TEXTPICKERSCROLLSTOPCALLBACK))));
    const Ark_Int8 valueTmpBufUnionSelector = thisDeserializer.readInt8();
    Ark_Union_String_Array_String valueTmpBuf = {};
    valueTmpBuf.selector = valueTmpBufUnionSelector;
    if (valueTmpBufUnionSelector == 0)
    {
        valueTmpBuf.selector = 0;
        valueTmpBuf.value0 = static_cast<Ark_String>(thisDeserializer.readString());
    }
    else if (valueTmpBufUnionSelector == 1)
    {
        valueTmpBuf.selector = 1;
        const Ark_Int32 valueTmpBufBufULength = thisDeserializer.readInt32();
        Array_String valueTmpBufBufU = {};
        thisDeserializer.resizeArray<std::decay<decltype(valueTmpBufBufU)>::type,
                                     std::decay<decltype(*valueTmpBufBufU.array)>::type>(&valueTmpBufBufU,
                                                                                         valueTmpBufBufULength);
        for (int valueTmpBufBufUBufCounterI = 0; valueTmpBufBufUBufCounterI < valueTmpBufBufULength;
             valueTmpBufBufUBufCounterI++)
        {
            valueTmpBufBufU.array[valueTmpBufBufUBufCounterI] = static_cast<Ark_String>(thisDeserializer.readString());
        }
        valueTmpBuf.value1 = valueTmpBufBufU;
    }
    else
    {
        INTEROP_FATAL("One of the branches for valueTmpBuf has to be chosen through deserialisation.");
    }
    Ark_Union_String_Array_String value = static_cast<Ark_Union_String_Array_String>(valueTmpBuf);
    const Ark_Int8 indexTmpBufUnionSelector = thisDeserializer.readInt8();
    Ark_Union_I32_Array_I32 indexTmpBuf = {};
    indexTmpBuf.selector = indexTmpBufUnionSelector;
    if (indexTmpBufUnionSelector == 0)
    {
        indexTmpBuf.selector = 0;
        indexTmpBuf.value0 = thisDeserializer.readInt32();
    }
    else if (indexTmpBufUnionSelector == 1)
    {
        indexTmpBuf.selector = 1;
        const Ark_Int32 indexTmpBufBufULength = thisDeserializer.readInt32();
        Array_I32 indexTmpBufBufU = {};
        thisDeserializer.resizeArray<std::decay<decltype(indexTmpBufBufU)>::type,
                                     std::decay<decltype(*indexTmpBufBufU.array)>::type>(&indexTmpBufBufU,
                                                                                         indexTmpBufBufULength);
        for (int indexTmpBufBufUBufCounterI = 0; indexTmpBufBufUBufCounterI < indexTmpBufBufULength;
             indexTmpBufBufUBufCounterI++)
        {
            indexTmpBufBufU.array[indexTmpBufBufUBufCounterI] = thisDeserializer.readInt32();
        }
        indexTmpBuf.value1 = indexTmpBufBufU;
    }
    else
    {
        INTEROP_FATAL("One of the branches for indexTmpBuf has to be chosen through deserialisation.");
    }
    Ark_Union_I32_Array_I32 index = static_cast<Ark_Union_I32_Array_I32>(indexTmpBuf);
    callSyncMethod(vmContext, resourceId, value, index);
}
void deserializeAndCallTextTimerModifierBuilder(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_NativePointer parentNode,
                                  const Ark_TextTimerConfiguration config, const Callback_Pointer_Void continuation)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_TEXTTIMERMODIFIERBUILDER))));
    thisDeserializer.readPointer();
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_TextTimerConfiguration config = TextTimerConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_POINTER_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_POINTER_VOID))))};
    call(resourceId, parentNode, config, continuationResult);
}
void deserializeAndCallSyncTextTimerModifierBuilder(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                    Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<
        void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer parentNode,
                 const Ark_TextTimerConfiguration config, const Callback_Pointer_Void continuation)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_TEXTTIMERMODIFIERBUILDER))));
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_TextTimerConfiguration config = TextTimerConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_POINTER_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_POINTER_VOID))))};
    callSyncMethod(vmContext, resourceId, parentNode, config, continuationResult);
}
void deserializeAndCallTimerCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Int64 utc, const Ark_Int64 elapsedTime)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_TIMERCALLBACK))));
    thisDeserializer.readPointer();
    Ark_Int64 utc = thisDeserializer.readInt64();
    Ark_Int64 elapsedTime = thisDeserializer.readInt64();
    call(resourceId, utc, elapsedTime);
}
void deserializeAndCallSyncTimerCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_Int64 utc, const Ark_Int64 elapsedTime)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_TIMERCALLBACK))));
    Ark_Int64 utc = thisDeserializer.readInt64();
    Ark_Int64 elapsedTime = thisDeserializer.readInt64();
    callSyncMethod(vmContext, resourceId, utc, elapsedTime);
}
void deserializeAndCallToggleModifierBuilder(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_NativePointer parentNode,
                                  const Ark_ToggleConfiguration config, const Callback_Pointer_Void continuation)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_TOGGLEMODIFIERBUILDER))));
    thisDeserializer.readPointer();
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_ToggleConfiguration config = ToggleConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_POINTER_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_POINTER_VOID))))};
    call(resourceId, parentNode, config, continuationResult);
}
void deserializeAndCallSyncToggleModifierBuilder(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                 Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<
        void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer parentNode,
                 const Ark_ToggleConfiguration config, const Callback_Pointer_Void continuation)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_TOGGLEMODIFIERBUILDER))));
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_ToggleConfiguration config = ToggleConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_POINTER_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_CALLBACK_POINTER_VOID))))};
    callSyncMethod(vmContext, resourceId, parentNode, config, continuationResult);
}
void deserializeAndCallTouchTestDoneCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_BaseGestureEvent event,
                                                const Array_GestureRecognizer recognizers)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_TOUCHTESTDONECALLBACK))));
    thisDeserializer.readPointer();
    Ark_BaseGestureEvent event = static_cast<Ark_BaseGestureEvent>(BaseGestureEvent_serializer::read(thisDeserializer));
    const Ark_Int32 recognizersTmpBufLength = thisDeserializer.readInt32();
    Array_GestureRecognizer recognizersTmpBuf = {};
    thisDeserializer.resizeArray<std::decay<decltype(recognizersTmpBuf)>::type,
                                 std::decay<decltype(*recognizersTmpBuf.array)>::type>(&recognizersTmpBuf,
                                                                                       recognizersTmpBufLength);
    for (int recognizersTmpBufBufCounterI = 0; recognizersTmpBufBufCounterI < recognizersTmpBufLength;
         recognizersTmpBufBufCounterI++)
    {
        recognizersTmpBuf.array[recognizersTmpBufBufCounterI] = static_cast<Ark_GestureRecognizer>(
            GestureRecognizer_serializer::read(thisDeserializer));
    }
    Array_GestureRecognizer recognizers = recognizersTmpBuf;
    call(resourceId, event, recognizers);
}
void deserializeAndCallSyncTouchTestDoneCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                 Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_BaseGestureEvent event,
                                  const Array_GestureRecognizer recognizers)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_TOUCHTESTDONECALLBACK))));
    Ark_BaseGestureEvent event = static_cast<Ark_BaseGestureEvent>(BaseGestureEvent_serializer::read(thisDeserializer));
    const Ark_Int32 recognizersTmpBufLength = thisDeserializer.readInt32();
    Array_GestureRecognizer recognizersTmpBuf = {};
    thisDeserializer.resizeArray<std::decay<decltype(recognizersTmpBuf)>::type,
                                 std::decay<decltype(*recognizersTmpBuf.array)>::type>(&recognizersTmpBuf,
                                                                                       recognizersTmpBufLength);
    for (int recognizersTmpBufBufCounterI = 0; recognizersTmpBufBufCounterI < recognizersTmpBufLength;
         recognizersTmpBufBufCounterI++)
    {
        recognizersTmpBuf.array[recognizersTmpBufBufCounterI] = static_cast<Ark_GestureRecognizer>(
            GestureRecognizer_serializer::read(thisDeserializer));
    }
    Array_GestureRecognizer recognizers = recognizersTmpBuf;
    callSyncMethod(vmContext, resourceId, event, recognizers);
}
void deserializeAndCallTransitionFinishCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Boolean transitionIn)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_TRANSITIONFINISHCALLBACK))));
    thisDeserializer.readPointer();
    Ark_Boolean transitionIn = thisDeserializer.readBoolean();
    call(resourceId, transitionIn);
}
void deserializeAndCallSyncTransitionFinishCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                    Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean transitionIn)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_TRANSITIONFINISHCALLBACK))));
    Ark_Boolean transitionIn = thisDeserializer.readBoolean();
    callSyncMethod(vmContext, resourceId, transitionIn);
}
void deserializeAndCallType_CommonMethod_onDragStart(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_DragEvent event, const Opt_String extraParams,
                                  const Callback_Union_CustomNodeBuilder_DragItemInfo_Void continuation)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_TYPE_COMMONMETHOD_ONDRAGSTART))));
    thisDeserializer.readPointer();
    Ark_DragEvent event = static_cast<Ark_DragEvent>(DragEvent_serializer::read(thisDeserializer));
    const auto extraParamsTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_String extraParamsTmpBuf = {};
    extraParamsTmpBuf.tag = extraParamsTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED :
                                                                                         INTEROP_TAG_OBJECT;
    if ((extraParamsTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        extraParamsTmpBuf.value = static_cast<Ark_String>(thisDeserializer.readString());
    }
    Opt_String extraParams = extraParamsTmpBuf;
    Callback_Union_CustomNodeBuilder_DragItemInfo_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Union_CustomNodeBuilder_DragItemInfo value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCaller(KIND_CALLBACK_UNION_CUSTOMNODEBUILDER_DRAGITEMINFO_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                  const Ark_Union_CustomNodeBuilder_DragItemInfo value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_CALLBACK_UNION_CUSTOMNODEBUILDER_DRAGITEMINFO_VOID))))};
    call(resourceId, event, extraParams, continuationResult);
}
void deserializeAndCallSyncType_CommonMethod_onDragStart(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                         Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<
        void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_DragEvent event,
                 const Opt_String extraParams, const Callback_Union_CustomNodeBuilder_DragItemInfo_Void continuation)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_TYPE_COMMONMETHOD_ONDRAGSTART))));
    Ark_DragEvent event = static_cast<Ark_DragEvent>(DragEvent_serializer::read(thisDeserializer));
    const auto extraParamsTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_String extraParamsTmpBuf = {};
    extraParamsTmpBuf.tag = extraParamsTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED :
                                                                                         INTEROP_TAG_OBJECT;
    if ((extraParamsTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED))
    {
        extraParamsTmpBuf.value = static_cast<Ark_String>(thisDeserializer.readString());
    }
    Opt_String extraParams = extraParamsTmpBuf;
    Callback_Union_CustomNodeBuilder_DragItemInfo_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Union_CustomNodeBuilder_DragItemInfo value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCaller(KIND_CALLBACK_UNION_CUSTOMNODEBUILDER_DRAGITEMINFO_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                  const Ark_Union_CustomNodeBuilder_DragItemInfo value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_CALLBACK_UNION_CUSTOMNODEBUILDER_DRAGITEMINFO_VOID))))};
    callSyncMethod(vmContext, resourceId, event, extraParams, continuationResult);
}
void deserializeAndCallType_NavigationAttribute_customNavContentTransition(KSerializerBuffer thisArray,
                                                                           Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_NavContentInfo from,
                                                const Ark_NavContentInfo to, Ark_NavigationOperation operation,
                                                const Callback_Opt_NavigationAnimatedTransition_Void continuation)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCaller(KIND_TYPE_NAVIGATIONATTRIBUTE_CUSTOMNAVCONTENTTRANSITION))));
    thisDeserializer.readPointer();
    Ark_NavContentInfo from = NavContentInfo_serializer::read(thisDeserializer);
    Ark_NavContentInfo to = NavContentInfo_serializer::read(thisDeserializer);
    Ark_NavigationOperation operation = static_cast<Ark_NavigationOperation>(thisDeserializer.readInt32());
    Callback_Opt_NavigationAnimatedTransition_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Opt_NavigationAnimatedTransition value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCaller(KIND_CALLBACK_OPT_NAVIGATIONANIMATEDTRANSITION_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                  const Opt_NavigationAnimatedTransition value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_CALLBACK_OPT_NAVIGATIONANIMATEDTRANSITION_VOID))))};
    call(resourceId, from, to, operation, continuationResult);
}
void deserializeAndCallSyncType_NavigationAttribute_customNavContentTransition(Ark_VMContext vmContext,
                                                                               KSerializerBuffer thisArray,
                                                                               Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(
        Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NavContentInfo from, const Ark_NavContentInfo to,
        Ark_NavigationOperation operation, const Callback_Opt_NavigationAnimatedTransition_Void continuation)>(
        thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
            getManagedCallbackCallerSync(KIND_TYPE_NAVIGATIONATTRIBUTE_CUSTOMNAVCONTENTTRANSITION))));
    Ark_NavContentInfo from = NavContentInfo_serializer::read(thisDeserializer);
    Ark_NavContentInfo to = NavContentInfo_serializer::read(thisDeserializer);
    Ark_NavigationOperation operation = static_cast<Ark_NavigationOperation>(thisDeserializer.readInt32());
    Callback_Opt_NavigationAnimatedTransition_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Opt_NavigationAnimatedTransition value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCaller(KIND_CALLBACK_OPT_NAVIGATIONANIMATEDTRANSITION_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                  const Opt_NavigationAnimatedTransition value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_CALLBACK_OPT_NAVIGATIONANIMATEDTRANSITION_VOID))))};
    callSyncMethod(vmContext, resourceId, from, to, operation, continuationResult);
}
void deserializeAndCallUpdateTransitionCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Float64 progress)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_UPDATETRANSITIONCALLBACK))));
    thisDeserializer.readPointer();
    Ark_Float64 progress = thisDeserializer.readFloat64();
    call(resourceId, progress);
}
void deserializeAndCallSyncUpdateTransitionCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                    Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Float64 progress)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_UPDATETRANSITIONCALLBACK))));
    Ark_Float64 progress = thisDeserializer.readFloat64();
    callSyncMethod(vmContext, resourceId, progress);
}
void deserializeAndCallVisibleAreaChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Boolean isExpanding,
                                                const Ark_Float64 currentRatio)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_VISIBLEAREACHANGECALLBACK))));
    thisDeserializer.readPointer();
    Ark_Boolean isExpanding = thisDeserializer.readBoolean();
    Ark_Float64 currentRatio = thisDeserializer.readFloat64();
    call(resourceId, isExpanding, currentRatio);
}
void deserializeAndCallSyncVisibleAreaChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                                     Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isExpanding,
                                  const Ark_Float64 currentRatio)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_VISIBLEAREACHANGECALLBACK))));
    Ark_Boolean isExpanding = thisDeserializer.readBoolean();
    Ark_Float64 currentRatio = thisDeserializer.readFloat64();
    callSyncMethod(vmContext, resourceId, isExpanding, currentRatio);
}
void deserializeAndCallVoidCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId)>(thisDeserializer.readPointerOrDefault(
        reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_VOIDCALLBACK))));
    thisDeserializer.readPointer();
    call(resourceId);
}
void deserializeAndCallSyncVoidCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_VOIDCALLBACK))));
    callSyncMethod(vmContext, resourceId);
}
void deserializeAndCallWebKeyboardCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_WebKeyboardCallbackInfo keyboardCallbackInfo,
                                  const Callback_WebKeyboardOptions_Void continuation)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_WEBKEYBOARDCALLBACK))));
    thisDeserializer.readPointer();
    Ark_WebKeyboardCallbackInfo keyboardCallbackInfo = WebKeyboardCallbackInfo_serializer::read(thisDeserializer);
    Callback_WebKeyboardOptions_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_WebKeyboardOptions value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_WEBKEYBOARDOPTIONS_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                  const Ark_WebKeyboardOptions value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_CALLBACK_WEBKEYBOARDOPTIONS_VOID))))};
    call(resourceId, keyboardCallbackInfo, continuationResult);
}
void deserializeAndCallSyncWebKeyboardCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                               Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                                          const Ark_WebKeyboardCallbackInfo keyboardCallbackInfo,
                                                          const Callback_WebKeyboardOptions_Void continuation)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_WEBKEYBOARDCALLBACK))));
    Ark_WebKeyboardCallbackInfo keyboardCallbackInfo = WebKeyboardCallbackInfo_serializer::read(thisDeserializer);
    Callback_WebKeyboardOptions_Void continuationResult = {
        thisDeserializer.readCallbackResource(),
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_WebKeyboardOptions value)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_CALLBACK_WEBKEYBOARDOPTIONS_VOID)))),
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId,
                                  const Ark_WebKeyboardOptions value)>(
            thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(
                getManagedCallbackCallerSync(KIND_CALLBACK_WEBKEYBOARDOPTIONS_VOID))))};
    callSyncMethod(vmContext, resourceId, keyboardCallbackInfo, continuationResult);
}
void deserializeAndCallWorkerEventListener(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    const auto call = reinterpret_cast<void (*)(const Ark_Int32 resourceId, const Ark_Event event)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(KIND_WORKEREVENTLISTENER))));
    thisDeserializer.readPointer();
    Ark_Event event = Event_serializer::read(thisDeserializer);
    call(resourceId, event);
}
void deserializeAndCallSyncWorkerEventListener(Ark_VMContext vmContext, KSerializerBuffer thisArray,
                                               Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod =
        reinterpret_cast<void (*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Event event)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(KIND_WORKEREVENTLISTENER))));
    Ark_Event event = Event_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, event);
}
void deserializeAndCallCallback(Ark_Int32 kind, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    switch (static_cast<CallbackKind>(kind))
    {
    case KIND_ACCESSIBILITYACTIONINTERCEPTCALLBACK:
        return deserializeAndCallAccessibilityActionInterceptCallback(thisArray, thisLength);
    case KIND_ACCESSIBILITYCALLBACK:
        return deserializeAndCallAccessibilityCallback(thisArray, thisLength);
    case KIND_ACCESSIBILITYFOCUSCALLBACK:
        return deserializeAndCallAccessibilityFocusCallback(thisArray, thisLength);
    case KIND_ACCESSIBILITYTRANSPARENTCALLBACK:
        return deserializeAndCallAccessibilityTransparentCallback(thisArray, thisLength);
    case KIND_BUTTONMODIFIERBUILDER:
        return deserializeAndCallButtonModifierBuilder(thisArray, thisLength);
    case KIND_BUTTONTRIGGERCLICKCALLBACK:
        return deserializeAndCallButtonTriggerClickCallback(thisArray, thisLength);
    case KIND_CALLBACK_ACCESSIBILITYACTIONINTERCEPTRESULT_VOID:
        return deserializeAndCallCallback_AccessibilityActionInterceptResult_Void(thisArray, thisLength);
    case KIND_CALLBACK_AREA_AREA_VOID:
        return deserializeAndCallCallback_Area_Area_Void(thisArray, thisLength);
    case KIND_CALLBACK_ARRAY_I32_VOID:
        return deserializeAndCallCallback_Array_I32_Void(thisArray, thisLength);
    case KIND_CALLBACK_ARRAY_RESOURCE_VOID:
        return deserializeAndCallCallback_Array_Resource_Void(thisArray, thisLength);
    case KIND_CALLBACK_ARRAY_RESOURCESTR_VOID:
        return deserializeAndCallCallback_Array_ResourceStr_Void(thisArray, thisLength);
    case KIND_CALLBACK_ARRAY_STRING_VOID:
        return deserializeAndCallCallback_Array_String_Void(thisArray, thisLength);
    case KIND_CALLBACK_ARRAY_TEXTMENUITEM_VOID:
        return deserializeAndCallCallback_Array_TextMenuItem_Void(thisArray, thisLength);
    case KIND_CALLBACK_ARRAY_TOUCHTESTINFO_TOUCHRESULT:
        return deserializeAndCallCallback_Array_TouchTestInfo_TouchResult(thisArray, thisLength);
    case KIND_CALLBACK_AXISEVENT_VOID:
        return deserializeAndCallCallback_AxisEvent_Void(thisArray, thisLength);
    case KIND_CALLBACK_BOOLEAN:
        return deserializeAndCallCallback_Boolean(thisArray, thisLength);
    case KIND_CALLBACK_BOOLEAN_HOVEREVENT_VOID:
        return deserializeAndCallCallback_Boolean_HoverEvent_Void(thisArray, thisLength);
    case KIND_CALLBACK_BOOLEAN_VOID:
        return deserializeAndCallCallback_Boolean_Void(thisArray, thisLength);
    case KIND_CALLBACK_BUFFER_VOID:
        return deserializeAndCallCallback_Buffer_Void(thisArray, thisLength);
    case KIND_CALLBACK_BUSINESSERROR_VOID:
        return deserializeAndCallCallback_BusinessError_Void(thisArray, thisLength);
    case KIND_CALLBACK_CLICKEVENT_VOID:
        return deserializeAndCallCallback_ClickEvent_Void(thisArray, thisLength);
    case KIND_CALLBACK_COMPUTEDBARATTRIBUTE_VOID:
        return deserializeAndCallCallback_ComputedBarAttribute_Void(thisArray, thisLength);
    case KIND_CALLBACK_COPYEVENT_VOID:
        return deserializeAndCallCallback_CopyEvent_Void(thisArray, thisLength);
    case KIND_CALLBACK_CREATEITEM:
        return deserializeAndCallCallback_CreateItem(thisArray, thisLength);
    case KIND_CALLBACK_CROWNEVENT_VOID:
        return deserializeAndCallCallback_CrownEvent_Void(thisArray, thisLength);
    case KIND_CALLBACK_CUSTOMSPANMEASUREINFO_CUSTOMSPANMETRICS:
        return deserializeAndCallCallback_CustomSpanMeasureInfo_CustomSpanMetrics(thisArray, thisLength);
    case KIND_CALLBACK_CUSTOMSPANMETRICS_VOID:
        return deserializeAndCallCallback_CustomSpanMetrics_Void(thisArray, thisLength);
    case KIND_CALLBACK_CUTEVENT_VOID:
        return deserializeAndCallCallback_CutEvent_Void(thisArray, thisLength);
    case KIND_CALLBACK_DATE_VOID:
        return deserializeAndCallCallback_Date_Void(thisArray, thisLength);
    case KIND_CALLBACK_DELETEVALUE_BOOLEAN:
        return deserializeAndCallCallback_DeleteValue_Boolean(thisArray, thisLength);
    case KIND_CALLBACK_DELETEVALUE_VOID:
        return deserializeAndCallCallback_DeleteValue_Void(thisArray, thisLength);
    case KIND_CALLBACK_DISMISSCONTENTCOVERACTION_VOID:
        return deserializeAndCallCallback_DismissContentCoverAction_Void(thisArray, thisLength);
    case KIND_CALLBACK_DISMISSDIALOGACTION_VOID:
        return deserializeAndCallCallback_DismissDialogAction_Void(thisArray, thisLength);
    case KIND_CALLBACK_DISMISSPOPUPACTION_VOID:
        return deserializeAndCallCallback_DismissPopupAction_Void(thisArray, thisLength);
    case KIND_CALLBACK_DISMISSSHEETACTION_VOID:
        return deserializeAndCallCallback_DismissSheetAction_Void(thisArray, thisLength);
    case KIND_CALLBACK_DRAGEVENT_OPT_STRING_VOID:
        return deserializeAndCallCallback_DragEvent_Opt_String_Void(thisArray, thisLength);
    case KIND_CALLBACK_DRAWCONTEXT_CUSTOMSPANDRAWINFO_VOID:
        return deserializeAndCallCallback_DrawContext_CustomSpanDrawInfo_Void(thisArray, thisLength);
    case KIND_CALLBACK_DRAWCONTEXT_VOID:
        return deserializeAndCallCallback_DrawContext_Void(thisArray, thisLength);
    case KIND_CALLBACK_EDITABLETEXTCHANGEVALUE_BOOLEAN:
        return deserializeAndCallCallback_EditableTextChangeValue_Boolean(thisArray, thisLength);
    case KIND_CALLBACK_ERRORINFORMATION_VOID:
        return deserializeAndCallCallback_ErrorInformation_Void(thisArray, thisLength);
    case KIND_CALLBACK_EXTENDER_ONFINISH:
        return deserializeAndCallCallback_Extender_OnFinish(thisArray, thisLength);
    case KIND_CALLBACK_EXTENDER_ONPROGRESS:
        return deserializeAndCallCallback_Extender_OnProgress(thisArray, thisLength);
    case KIND_CALLBACK_F64_F64_VOID:
        return deserializeAndCallCallback_F64_F64_Void(thisArray, thisLength);
    case KIND_CALLBACK_F64_SLIDERCHANGEMODE_VOID:
        return deserializeAndCallCallback_F64_SliderChangeMode_Void(thisArray, thisLength);
    case KIND_CALLBACK_F64_VOID:
        return deserializeAndCallCallback_F64_Void(thisArray, thisLength);
    case KIND_CALLBACK_FOCUSAXISEVENT_VOID:
        return deserializeAndCallCallback_FocusAxisEvent_Void(thisArray, thisLength);
    case KIND_CALLBACK_FORMCALLBACKINFO_VOID:
        return deserializeAndCallCallback_FormCallbackInfo_Void(thisArray, thisLength);
    case KIND_CALLBACK_FULLSCREENINFO_VOID:
        return deserializeAndCallCallback_FullscreenInfo_Void(thisArray, thisLength);
    case KIND_CALLBACK_GESTUREEVENT_VOID:
        return deserializeAndCallCallback_GestureEvent_Void(thisArray, thisLength);
    case KIND_CALLBACK_GESTUREINFO_BASEGESTUREEVENT_GESTUREJUDGERESULT:
        return deserializeAndCallCallback_GestureInfo_BaseGestureEvent_GestureJudgeResult(thisArray, thisLength);
    case KIND_CALLBACK_GESTUREJUDGERESULT_VOID:
        return deserializeAndCallCallback_GestureJudgeResult_Void(thisArray, thisLength);
    case KIND_CALLBACK_GESTURERECOGNIZER_VOID:
        return deserializeAndCallCallback_GestureRecognizer_Void(thisArray, thisLength);
    case KIND_CALLBACK_HITTESTMODE_VOID:
        return deserializeAndCallCallback_HitTestMode_Void(thisArray, thisLength);
    case KIND_CALLBACK_HOVEREVENT_VOID:
        return deserializeAndCallCallback_HoverEvent_Void(thisArray, thisLength);
    case KIND_CALLBACK_I32_F64_COMPUTEDBARATTRIBUTE:
        return deserializeAndCallCallback_I32_F64_ComputedBarAttribute(thisArray, thisLength);
    case KIND_CALLBACK_I32_I32_BOOLEAN:
        return deserializeAndCallCallback_I32_I32_Boolean(thisArray, thisLength);
    case KIND_CALLBACK_I32_I32_I32_VOID:
        return deserializeAndCallCallback_I32_I32_I32_Void(thisArray, thisLength);
    case KIND_CALLBACK_I32_I32_VOID:
        return deserializeAndCallCallback_I32_I32_Void(thisArray, thisLength);
    case KIND_CALLBACK_I32_TUPLE_I32_I32:
        return deserializeAndCallCallback_I32_Tuple_I32_I32(thisArray, thisLength);
    case KIND_CALLBACK_I32_TUPLE_I32_I32_I32_I32:
        return deserializeAndCallCallback_I32_Tuple_I32_I32_I32_I32(thisArray, thisLength);
    case KIND_CALLBACK_I32_VOID:
        return deserializeAndCallCallback_I32_Void(thisArray, thisLength);
    case KIND_CALLBACK_I64_VOID:
        return deserializeAndCallCallback_I64_Void(thisArray, thisLength);
    case KIND_CALLBACK_INSERTVALUE_BOOLEAN:
        return deserializeAndCallCallback_InsertValue_Boolean(thisArray, thisLength);
    case KIND_CALLBACK_INSERTVALUE_VOID:
        return deserializeAndCallCallback_InsertValue_Void(thisArray, thisLength);
    case KIND_CALLBACK_ITEMDRAGINFO_I32_I32_BOOLEAN_VOID:
        return deserializeAndCallCallback_ItemDragInfo_I32_I32_Boolean_Void(thisArray, thisLength);
    case KIND_CALLBACK_ITEMDRAGINFO_I32_I32_VOID:
        return deserializeAndCallCallback_ItemDragInfo_I32_I32_Void(thisArray, thisLength);
    case KIND_CALLBACK_ITEMDRAGINFO_I32_VOID:
        return deserializeAndCallCallback_ItemDragInfo_I32_Void(thisArray, thisLength);
    case KIND_CALLBACK_ITEMDRAGINFO_VOID:
        return deserializeAndCallCallback_ItemDragInfo_Void(thisArray, thisLength);
    case KIND_CALLBACK_KEYEVENT_BOOLEAN:
        return deserializeAndCallCallback_KeyEvent_Boolean(thisArray, thisLength);
    case KIND_CALLBACK_KEYEVENT_VOID:
        return deserializeAndCallCallback_KeyEvent_Void(thisArray, thisLength);
    case KIND_CALLBACK_LENGTH_VOID:
        return deserializeAndCallCallback_Length_Void(thisArray, thisLength);
    case KIND_CALLBACK_MAP_STRING_OPT_OBJECT:
        return deserializeAndCallCallback_Map_String_Opt_Object(thisArray, thisLength);
    case KIND_CALLBACK_MARQUEESTATE_VOID:
        return deserializeAndCallCallback_MarqueeState_Void(thisArray, thisLength);
    case KIND_CALLBACK_MOUSEEVENT_VOID:
        return deserializeAndCallCallback_MouseEvent_Void(thisArray, thisLength);
    case KIND_CALLBACK_NATIVEEMBEDDATAINFO_VOID:
        return deserializeAndCallCallback_NativeEmbedDataInfo_Void(thisArray, thisLength);
    case KIND_CALLBACK_NATIVEEMBEDTOUCHINFO_VOID:
        return deserializeAndCallCallback_NativeEmbedTouchInfo_Void(thisArray, thisLength);
    case KIND_CALLBACK_NAVDESTINATIONACTIVEREASON_VOID:
        return deserializeAndCallCallback_NavDestinationActiveReason_Void(thisArray, thisLength);
    case KIND_CALLBACK_NAVDESTINATIONCONTEXT_VOID:
        return deserializeAndCallCallback_NavDestinationContext_Void(thisArray, thisLength);
    case KIND_CALLBACK_NAVIGATIONMODE_VOID:
        return deserializeAndCallCallback_NavigationMode_Void(thisArray, thisLength);
    case KIND_CALLBACK_NAVIGATIONTITLEMODE_VOID:
        return deserializeAndCallCallback_NavigationTitleMode_Void(thisArray, thisLength);
    case KIND_CALLBACK_NAVIGATIONTRANSITIONPROXY_VOID:
        return deserializeAndCallCallback_NavigationTransitionProxy_Void(thisArray, thisLength);
    case KIND_CALLBACK_NUMBER_VOID:
        return deserializeAndCallCallback_Number_Void(thisArray, thisLength);
    case KIND_CALLBACK_OBJECT_VOID:
        return deserializeAndCallCallback_Object_Void(thisArray, thisLength);
    case KIND_CALLBACK_ONALERTEVENT_BOOLEAN:
        return deserializeAndCallCallback_OnAlertEvent_Boolean(thisArray, thisLength);
    case KIND_CALLBACK_ONAUDIOSTATECHANGEDEVENT_VOID:
        return deserializeAndCallCallback_OnAudioStateChangedEvent_Void(thisArray, thisLength);
    case KIND_CALLBACK_ONBEFOREUNLOADEVENT_BOOLEAN:
        return deserializeAndCallCallback_OnBeforeUnloadEvent_Boolean(thisArray, thisLength);
    case KIND_CALLBACK_ONCLIENTAUTHENTICATIONEVENT_VOID:
        return deserializeAndCallCallback_OnClientAuthenticationEvent_Void(thisArray, thisLength);
    case KIND_CALLBACK_ONCONFIRMEVENT_BOOLEAN:
        return deserializeAndCallCallback_OnConfirmEvent_Boolean(thisArray, thisLength);
    case KIND_CALLBACK_ONCONSOLEEVENT_BOOLEAN:
        return deserializeAndCallCallback_OnConsoleEvent_Boolean(thisArray, thisLength);
    case KIND_CALLBACK_ONCONTEXTMENUSHOWEVENT_BOOLEAN:
        return deserializeAndCallCallback_OnContextMenuShowEvent_Boolean(thisArray, thisLength);
    case KIND_CALLBACK_ONDATARESUBMITTEDEVENT_VOID:
        return deserializeAndCallCallback_OnDataResubmittedEvent_Void(thisArray, thisLength);
    case KIND_CALLBACK_ONDESTORY_VOID:
        return deserializeAndCallCallback_OnDestory_Void(thisArray, thisLength);
    case KIND_CALLBACK_ONDOWNLOADSTARTEVENT_VOID:
        return deserializeAndCallCallback_OnDownloadStartEvent_Void(thisArray, thisLength);
    case KIND_CALLBACK_ONERRORRECEIVEEVENT_VOID:
        return deserializeAndCallCallback_OnErrorReceiveEvent_Void(thisArray, thisLength);
    case KIND_CALLBACK_ONFAVICONRECEIVEDEVENT_VOID:
        return deserializeAndCallCallback_OnFaviconReceivedEvent_Void(thisArray, thisLength);
    case KIND_CALLBACK_ONFIRSTCONTENTFULPAINTEVENT_VOID:
        return deserializeAndCallCallback_OnFirstContentfulPaintEvent_Void(thisArray, thisLength);
    case KIND_CALLBACK_ONGEOLOCATIONSHOWEVENT_VOID:
        return deserializeAndCallCallback_OnGeolocationShowEvent_Void(thisArray, thisLength);
    case KIND_CALLBACK_ONHTTPAUTHREQUESTEVENT_BOOLEAN:
        return deserializeAndCallCallback_OnHttpAuthRequestEvent_Boolean(thisArray, thisLength);
    case KIND_CALLBACK_ONHTTPERRORRECEIVEEVENT_VOID:
        return deserializeAndCallCallback_OnHttpErrorReceiveEvent_Void(thisArray, thisLength);
    case KIND_CALLBACK_ONINTERCEPTREQUESTEVENT_OPT_WEBRESOURCERESPONSE:
        return deserializeAndCallCallback_OnInterceptRequestEvent_Opt_WebResourceResponse(thisArray, thisLength);
    case KIND_CALLBACK_ONLOADFINISHEDEVENT_VOID:
        return deserializeAndCallCallback_OnLoadFinishedEvent_Void(thisArray, thisLength);
    case KIND_CALLBACK_ONLOADINTERCEPTEVENT_BOOLEAN:
        return deserializeAndCallCallback_OnLoadInterceptEvent_Boolean(thisArray, thisLength);
    case KIND_CALLBACK_ONLOADSTARTEDEVENT_VOID:
        return deserializeAndCallCallback_OnLoadStartedEvent_Void(thisArray, thisLength);
    case KIND_CALLBACK_ONMEASURESIZE_SIZERESULT:
        return deserializeAndCallCallback_onMeasureSize_SizeResult(thisArray, thisLength);
    case KIND_CALLBACK_ONMOVEFROMTO:
        return deserializeAndCallCallback_OnMoveFromTo(thisArray, thisLength);
    case KIND_CALLBACK_ONOVERSCROLLEVENT_VOID:
        return deserializeAndCallCallback_OnOverScrollEvent_Void(thisArray, thisLength);
    case KIND_CALLBACK_ONPAGEBEGINEVENT_VOID:
        return deserializeAndCallCallback_OnPageBeginEvent_Void(thisArray, thisLength);
    case KIND_CALLBACK_ONPAGEENDEVENT_VOID:
        return deserializeAndCallCallback_OnPageEndEvent_Void(thisArray, thisLength);
    case KIND_CALLBACK_ONPAGEVISIBLEEVENT_VOID:
        return deserializeAndCallCallback_OnPageVisibleEvent_Void(thisArray, thisLength);
    case KIND_CALLBACK_ONPERMISSIONREQUESTEVENT_VOID:
        return deserializeAndCallCallback_OnPermissionRequestEvent_Void(thisArray, thisLength);
    case KIND_CALLBACK_ONPLACECHILDREN_VOID:
        return deserializeAndCallCallback_onPlaceChildren_Void(thisArray, thisLength);
    case KIND_CALLBACK_ONPROGRESSCHANGEEVENT_VOID:
        return deserializeAndCallCallback_OnProgressChangeEvent_Void(thisArray, thisLength);
    case KIND_CALLBACK_ONPROMPTEVENT_BOOLEAN:
        return deserializeAndCallCallback_OnPromptEvent_Boolean(thisArray, thisLength);
    case KIND_CALLBACK_ONREFRESHACCESSEDHISTORYEVENT_VOID:
        return deserializeAndCallCallback_OnRefreshAccessedHistoryEvent_Void(thisArray, thisLength);
    case KIND_CALLBACK_ONRENDEREXITEDEVENT_VOID:
        return deserializeAndCallCallback_OnRenderExitedEvent_Void(thisArray, thisLength);
    case KIND_CALLBACK_ONRESOURCELOADEVENT_VOID:
        return deserializeAndCallCallback_OnResourceLoadEvent_Void(thisArray, thisLength);
    case KIND_CALLBACK_ONSCALECHANGEEVENT_VOID:
        return deserializeAndCallCallback_OnScaleChangeEvent_Void(thisArray, thisLength);
    case KIND_CALLBACK_ONSCREENCAPTUREREQUESTEVENT_VOID:
        return deserializeAndCallCallback_OnScreenCaptureRequestEvent_Void(thisArray, thisLength);
    case KIND_CALLBACK_ONSCROLLEVENT_VOID:
        return deserializeAndCallCallback_OnScrollEvent_Void(thisArray, thisLength);
    case KIND_CALLBACK_ONSCROLLFRAMEBEGINHANDLERRESULT_VOID:
        return deserializeAndCallCallback_OnScrollFrameBeginHandlerResult_Void(thisArray, thisLength);
    case KIND_CALLBACK_ONSEARCHRESULTRECEIVEEVENT_VOID:
        return deserializeAndCallCallback_OnSearchResultReceiveEvent_Void(thisArray, thisLength);
    case KIND_CALLBACK_ONSHOWFILESELECTOREVENT_BOOLEAN:
        return deserializeAndCallCallback_OnShowFileSelectorEvent_Boolean(thisArray, thisLength);
    case KIND_CALLBACK_ONSSLERROREVENTRECEIVEEVENT_VOID:
        return deserializeAndCallCallback_OnSslErrorEventReceiveEvent_Void(thisArray, thisLength);
    case KIND_CALLBACK_ONTITLERECEIVEEVENT_VOID:
        return deserializeAndCallCallback_OnTitleReceiveEvent_Void(thisArray, thisLength);
    case KIND_CALLBACK_ONTOUCHICONURLRECEIVEDEVENT_VOID:
        return deserializeAndCallCallback_OnTouchIconUrlReceivedEvent_Void(thisArray, thisLength);
    case KIND_CALLBACK_ONWINDOWNEWEVENT_VOID:
        return deserializeAndCallCallback_OnWindowNewEvent_Void(thisArray, thisLength);
    case KIND_CALLBACK_OPT_ARRAY_NAVDESTINATIONTRANSITION_VOID:
        return deserializeAndCallCallback_Opt_Array_NavDestinationTransition_Void(thisArray, thisLength);
    case KIND_CALLBACK_OPT_ARRAY_STRING_VOID:
        return deserializeAndCallCallback_Opt_Array_String_Void(thisArray, thisLength);
    case KIND_CALLBACK_OPT_CUSTOMNODEBUILDER_VOID:
        return deserializeAndCallCallback_Opt_CustomNodeBuilder_Void(thisArray, thisLength);
    case KIND_CALLBACK_OPT_NAVIGATIONANIMATEDTRANSITION_VOID:
        return deserializeAndCallCallback_Opt_NavigationAnimatedTransition_Void(thisArray, thisLength);
    case KIND_CALLBACK_OPT_OBJECT_VOID:
        return deserializeAndCallCallback_Opt_Object_Void(thisArray, thisLength);
    case KIND_CALLBACK_OPT_OFFSETRESULT_VOID:
        return deserializeAndCallCallback_Opt_OffsetResult_Void(thisArray, thisLength);
    case KIND_CALLBACK_OPT_SCROLLRESULT_VOID:
        return deserializeAndCallCallback_Opt_ScrollResult_Void(thisArray, thisLength);
    case KIND_CALLBACK_OPT_STYLEDSTRING_OPT_ARRAY_STRING_VOID:
        return deserializeAndCallCallback_Opt_StyledString_Opt_Array_String_Void(thisArray, thisLength);
    case KIND_CALLBACK_OPT_TABCONTENTANIMATEDTRANSITION_VOID:
        return deserializeAndCallCallback_Opt_TabContentAnimatedTransition_Void(thisArray, thisLength);
    case KIND_CALLBACK_OPT_WEBRESOURCERESPONSE_VOID:
        return deserializeAndCallCallback_Opt_WebResourceResponse_Void(thisArray, thisLength);
    case KIND_CALLBACK_PLAYBACKINFO_VOID:
        return deserializeAndCallCallback_PlaybackInfo_Void(thisArray, thisLength);
    case KIND_CALLBACK_POINTER_VOID:
        return deserializeAndCallCallback_Pointer_Void(thisArray, thisLength);
    case KIND_CALLBACK_POPINFO_VOID:
        return deserializeAndCallCallback_PopInfo_Void(thisArray, thisLength);
    case KIND_CALLBACK_PREDRAGSTATUS_VOID:
        return deserializeAndCallCallback_PreDragStatus_Void(thisArray, thisLength);
    case KIND_CALLBACK_PREPAREDINFO_VOID:
        return deserializeAndCallCallback_PreparedInfo_Void(thisArray, thisLength);
    case KIND_CALLBACK_RANGEUPDATE:
        return deserializeAndCallCallback_RangeUpdate(thisArray, thisLength);
    case KIND_CALLBACK_REFRESHSTATUS_VOID:
        return deserializeAndCallCallback_RefreshStatus_Void(thisArray, thisLength);
    case KIND_CALLBACK_RESOURCE_VOID:
        return deserializeAndCallCallback_Resource_Void(thisArray, thisLength);
    case KIND_CALLBACK_RESOURCESTR_VOID:
        return deserializeAndCallCallback_ResourceStr_Void(thisArray, thisLength);
    case KIND_CALLBACK_RICHEDITORCHANGEVALUE_BOOLEAN:
        return deserializeAndCallCallback_RichEditorChangeValue_Boolean(thisArray, thisLength);
    case KIND_CALLBACK_RICHEDITORDELETEVALUE_BOOLEAN:
        return deserializeAndCallCallback_RichEditorDeleteValue_Boolean(thisArray, thisLength);
    case KIND_CALLBACK_RICHEDITORINSERTVALUE_BOOLEAN:
        return deserializeAndCallCallback_RichEditorInsertValue_Boolean(thisArray, thisLength);
    case KIND_CALLBACK_RICHEDITORRANGE_VOID:
        return deserializeAndCallCallback_RichEditorRange_Void(thisArray, thisLength);
    case KIND_CALLBACK_RICHEDITORSELECTION_VOID:
        return deserializeAndCallCallback_RichEditorSelection_Void(thisArray, thisLength);
    case KIND_CALLBACK_RICHEDITORTEXTSPANRESULT_VOID:
        return deserializeAndCallCallback_RichEditorTextSpanResult_Void(thisArray, thisLength);
    case KIND_CALLBACK_SHEETDISMISS_VOID:
        return deserializeAndCallCallback_SheetDismiss_Void(thisArray, thisLength);
    case KIND_CALLBACK_SHEETTYPE_VOID:
        return deserializeAndCallCallback_SheetType_Void(thisArray, thisLength);
    case KIND_CALLBACK_SIZE_VOID:
        return deserializeAndCallCallback_Size_Void(thisArray, thisLength);
    case KIND_CALLBACK_SIZERESULT_VOID:
        return deserializeAndCallCallback_SizeResult_Void(thisArray, thisLength);
    case KIND_CALLBACK_SPRINGBACKACTION_VOID:
        return deserializeAndCallCallback_SpringBackAction_Void(thisArray, thisLength);
    case KIND_CALLBACK_STATESTYLESCHANGE:
        return deserializeAndCallCallback_StateStylesChange(thisArray, thisLength);
    case KIND_CALLBACK_STRING:
        return deserializeAndCallCallback_String(thisArray, thisLength);
    case KIND_CALLBACK_STRING_PASTEEVENT_VOID:
        return deserializeAndCallCallback_String_PasteEvent_Void(thisArray, thisLength);
    case KIND_CALLBACK_STRING_SURFACERECT_VOID:
        return deserializeAndCallCallback_String_SurfaceRect_Void(thisArray, thisLength);
    case KIND_CALLBACK_STRING_VOID:
        return deserializeAndCallCallback_String_Void(thisArray, thisLength);
    case KIND_CALLBACK_STYLEDSTRINGCHANGEVALUE_BOOLEAN:
        return deserializeAndCallCallback_StyledStringChangeValue_Boolean(thisArray, thisLength);
    case KIND_CALLBACK_SWIPEACTIONSTATE_VOID:
        return deserializeAndCallCallback_SwipeActionState_Void(thisArray, thisLength);
    case KIND_CALLBACK_SWIPERCONTENTTRANSITIONPROXY_VOID:
        return deserializeAndCallCallback_SwiperContentTransitionProxy_Void(thisArray, thisLength);
    case KIND_CALLBACK_TABCONTENTTRANSITIONPROXY_VOID:
        return deserializeAndCallCallback_TabContentTransitionProxy_Void(thisArray, thisLength);
    case KIND_CALLBACK_TERMINATIONINFO:
        return deserializeAndCallCallback_TerminationInfo(thisArray, thisLength);
    case KIND_CALLBACK_TEXTPICKERRESULT_VOID:
        return deserializeAndCallCallback_TextPickerResult_Void(thisArray, thisLength);
    case KIND_CALLBACK_TEXTRANGE_VOID:
        return deserializeAndCallCallback_TextRange_Void(thisArray, thisLength);
    case KIND_CALLBACK_TIMEPICKERRESULT_VOID:
        return deserializeAndCallCallback_TimePickerResult_Void(thisArray, thisLength);
    case KIND_CALLBACK_TOUCHEVENT_HITTESTMODE:
        return deserializeAndCallCallback_TouchEvent_HitTestMode(thisArray, thisLength);
    case KIND_CALLBACK_TOUCHEVENT_VOID:
        return deserializeAndCallCallback_TouchEvent_Void(thisArray, thisLength);
    case KIND_CALLBACK_TOUCHRESULT_VOID:
        return deserializeAndCallCallback_TouchResult_Void(thisArray, thisLength);
    case KIND_CALLBACK_TUPLE_I32_I32_I32_I32_VOID:
        return deserializeAndCallCallback_Tuple_I32_I32_I32_I32_Void(thisArray, thisLength);
    case KIND_CALLBACK_TUPLE_I32_I32_VOID:
        return deserializeAndCallCallback_Tuple_I32_I32_Void(thisArray, thisLength);
    case KIND_CALLBACK_UIEXTENSIONPROXY:
        return deserializeAndCallCallback_UIExtensionProxy(thisArray, thisLength);
    case KIND_CALLBACK_UNION_CUSTOMNODEBUILDER_DRAGITEMINFO_VOID:
        return deserializeAndCallCallback_Union_CustomNodeBuilder_DragItemInfo_Void(thisArray, thisLength);
    case KIND_CALLBACK_USERDATASPAN_VOID:
        return deserializeAndCallCallback_UserDataSpan_Void(thisArray, thisLength);
    case KIND_CALLBACK_VOID_VOID:
        return deserializeAndCallCallback_Void_Void(thisArray, thisLength);
    case KIND_CALLBACK_WEBKEYBOARDOPTIONS_VOID:
        return deserializeAndCallCallback_WebKeyboardOptions_Void(thisArray, thisLength);
    case KIND_CHECKBOXMODIFIERBUILDER:
        return deserializeAndCallCheckBoxModifierBuilder(thisArray, thisLength);
    case KIND_CONTENTDIDSCROLLCALLBACK:
        return deserializeAndCallContentDidScrollCallback(thisArray, thisLength);
    case KIND_CONTENTWILLSCROLLCALLBACK:
        return deserializeAndCallContentWillScrollCallback(thisArray, thisLength);
    case KIND_CUSTOMNODEBUILDER:
        return deserializeAndCallCustomNodeBuilder(thisArray, thisLength);
    case KIND_DATAPANELMODIFIERBUILDER:
        return deserializeAndCallDataPanelModifierBuilder(thisArray, thisLength);
    case KIND_DATAPROGRESSLISTENER:
        return deserializeAndCallDataProgressListener(thisArray, thisLength);
    case KIND_EDITABLETEXTONCHANGECALLBACK:
        return deserializeAndCallEditableTextOnChangeCallback(thisArray, thisLength);
    case KIND_ERRORCALLBACK_BUSINESSERRORINTERFACE_VOID:
        return deserializeAndCallErrorCallback_BusinessErrorInterface_Void(thisArray, thisLength);
    case KIND_FRAMECALLBACKHANDLER:
        return deserializeAndCallFrameCallbackHandler(thisArray, thisLength);
    case KIND_GAUGEMODIFIERBUILDER:
        return deserializeAndCallGaugeModifierBuilder(thisArray, thisLength);
    case KIND_GESTUREEVENTHANDLER:
        return deserializeAndCallGestureEventHandler(thisArray, thisLength);
    case KIND_GESTURERECOGNIZERJUDGEBEGINCALLBACK:
        return deserializeAndCallGestureRecognizerJudgeBeginCallback(thisArray, thisLength);
    case KIND_HOVERCALLBACK:
        return deserializeAndCallHoverCallback(thisArray, thisLength);
    case KIND_IMAGECOMPLETECALLBACK:
        return deserializeAndCallImageCompleteCallback(thisArray, thisLength);
    case KIND_IMAGEERRORCALLBACK:
        return deserializeAndCallImageErrorCallback(thisArray, thisLength);
    case KIND_IMAGEONCOMPLETECALLBACK:
        return deserializeAndCallImageOnCompleteCallback(thisArray, thisLength);
    case KIND_INTERCEPTIONMODECALLBACK:
        return deserializeAndCallInterceptionModeCallback(thisArray, thisLength);
    case KIND_INTERCEPTIONSHOWCALLBACK:
        return deserializeAndCallInterceptionShowCallback(thisArray, thisLength);
    case KIND_LOADINGPROGRESSMODIFIERBUILDER:
        return deserializeAndCallLoadingProgressModifierBuilder(thisArray, thisLength);
    case KIND_MENUCALLBACK:
        return deserializeAndCallMenuCallback(thisArray, thisLength);
    case KIND_MENUITEMMODIFIERBUILDER:
        return deserializeAndCallMenuItemModifierBuilder(thisArray, thisLength);
    case KIND_MENUONAPPEARCALLBACK:
        return deserializeAndCallMenuOnAppearCallback(thisArray, thisLength);
    case KIND_MODIFIERKEYSTATEGETTER:
        return deserializeAndCallModifierKeyStateGetter(thisArray, thisLength);
    case KIND_NAVDESTINATIONTRANSITIONDELEGATE:
        return deserializeAndCallNavDestinationTransitionDelegate(thisArray, thisLength);
    case KIND_NAVEXTENDER_CREATENAVDESTINATION:
        return deserializeAndCallNavExtender_CreateNavDestination(thisArray, thisLength);
    case KIND_NAVEXTENDER_ONUPDATESTACK:
        return deserializeAndCallNavExtender_OnUpdateStack(thisArray, thisLength);
    case KIND_NODECONTAINEROPSONTOUCHCALLBACK:
        return deserializeAndCallNodeContainerOpsOnTouchCallback(thisArray, thisLength);
    case KIND_ONADSBLOCKEDCALLBACK:
        return deserializeAndCallOnAdsBlockedCallback(thisArray, thisLength);
    case KIND_ONALPHABETINDEXERPOPUPSELECTCALLBACK:
        return deserializeAndCallOnAlphabetIndexerPopupSelectCallback(thisArray, thisLength);
    case KIND_ONALPHABETINDEXERREQUESTPOPUPDATACALLBACK:
        return deserializeAndCallOnAlphabetIndexerRequestPopupDataCallback(thisArray, thisLength);
    case KIND_ONALPHABETINDEXERSELECTCALLBACK:
        return deserializeAndCallOnAlphabetIndexerSelectCallback(thisArray, thisLength);
    case KIND_ONCHECKBOXCHANGECALLBACK:
        return deserializeAndCallOnCheckboxChangeCallback(thisArray, thisLength);
    case KIND_ONCHECKBOXGROUPCHANGECALLBACK:
        return deserializeAndCallOnCheckboxGroupChangeCallback(thisArray, thisLength);
    case KIND_ONCONTENTSCROLLCALLBACK:
        return deserializeAndCallOnContentScrollCallback(thisArray, thisLength);
    case KIND_ONCONTEXTMENUHIDECALLBACK:
        return deserializeAndCallOnContextMenuHideCallback(thisArray, thisLength);
    case KIND_ONCREATEMENUCALLBACK:
        return deserializeAndCallOnCreateMenuCallback(thisArray, thisLength);
    case KIND_ONDIDCHANGECALLBACK:
        return deserializeAndCallOnDidChangeCallback(thisArray, thisLength);
    case KIND_ONDRAGEVENTCALLBACK:
        return deserializeAndCallOnDragEventCallback(thisArray, thisLength);
    case KIND_ONFIRSTMEANINGFULPAINTCALLBACK:
        return deserializeAndCallOnFirstMeaningfulPaintCallback(thisArray, thisLength);
    case KIND_ONFOLDSTATUSCHANGECALLBACK:
        return deserializeAndCallOnFoldStatusChangeCallback(thisArray, thisLength);
    case KIND_ONFULLSCREENENTERCALLBACK:
        return deserializeAndCallOnFullScreenEnterCallback(thisArray, thisLength);
    case KIND_ONHOVERCALLBACK:
        return deserializeAndCallOnHoverCallback(thisArray, thisLength);
    case KIND_ONHOVERSTATUSCHANGECALLBACK:
        return deserializeAndCallOnHoverStatusChangeCallback(thisArray, thisLength);
    case KIND_ONINTELLIGENTTRACKINGPREVENTIONCALLBACK:
        return deserializeAndCallOnIntelligentTrackingPreventionCallback(thisArray, thisLength);
    case KIND_ONITEMDRAGSTARTCALLBACK:
        return deserializeAndCallOnItemDragStartCallback(thisArray, thisLength);
    case KIND_ONLARGESTCONTENTFULPAINTCALLBACK:
        return deserializeAndCallOnLargestContentfulPaintCallback(thisArray, thisLength);
    case KIND_ONMENUITEMCLICKCALLBACK:
        return deserializeAndCallOnMenuItemClickCallback(thisArray, thisLength);
    case KIND_ONMOVEHANDLER:
        return deserializeAndCallOnMoveHandler(thisArray, thisLength);
    case KIND_ONNATIVEEMBEDVISIBILITYCHANGECALLBACK:
        return deserializeAndCallOnNativeEmbedVisibilityChangeCallback(thisArray, thisLength);
    case KIND_ONNAVIGATIONENTRYCOMMITTEDCALLBACK:
        return deserializeAndCallOnNavigationEntryCommittedCallback(thisArray, thisLength);
    case KIND_ONOVERRIDEURLLOADINGCALLBACK:
        return deserializeAndCallOnOverrideUrlLoadingCallback(thisArray, thisLength);
    case KIND_ONPASTECALLBACK:
        return deserializeAndCallOnPasteCallback(thisArray, thisLength);
    case KIND_ONRADIOCHANGECALLBACK:
        return deserializeAndCallOnRadioChangeCallback(thisArray, thisLength);
    case KIND_ONRATINGCHANGECALLBACK:
        return deserializeAndCallOnRatingChangeCallback(thisArray, thisLength);
    case KIND_ONRENDERPROCESSNOTRESPONDINGCALLBACK:
        return deserializeAndCallOnRenderProcessNotRespondingCallback(thisArray, thisLength);
    case KIND_ONRENDERPROCESSRESPONDINGCALLBACK:
        return deserializeAndCallOnRenderProcessRespondingCallback(thisArray, thisLength);
    case KIND_ONSAFEBROWSINGCHECKRESULTCALLBACK:
        return deserializeAndCallOnSafeBrowsingCheckResultCallback(thisArray, thisLength);
    case KIND_ONSCROLLCALLBACK:
        return deserializeAndCallOnScrollCallback(thisArray, thisLength);
    case KIND_ONSCROLLEDGECALLBACK:
        return deserializeAndCallOnScrollEdgeCallback(thisArray, thisLength);
    case KIND_ONSCROLLFRAMEBEGINCALLBACK:
        return deserializeAndCallOnScrollFrameBeginCallback(thisArray, thisLength);
    case KIND_ONSCROLLVISIBLECONTENTCHANGECALLBACK:
        return deserializeAndCallOnScrollVisibleContentChangeCallback(thisArray, thisLength);
    case KIND_ONSELECTCALLBACK:
        return deserializeAndCallOnSelectCallback(thisArray, thisLength);
    case KIND_ONSSLERROREVENTCALLBACK:
        return deserializeAndCallOnSslErrorEventCallback(thisArray, thisLength);
    case KIND_ONSUBMITCALLBACK:
        return deserializeAndCallOnSubmitCallback(thisArray, thisLength);
    case KIND_ONSWIPERANIMATIONENDCALLBACK:
        return deserializeAndCallOnSwiperAnimationEndCallback(thisArray, thisLength);
    case KIND_ONSWIPERANIMATIONSTARTCALLBACK:
        return deserializeAndCallOnSwiperAnimationStartCallback(thisArray, thisLength);
    case KIND_ONSWIPERGESTURESWIPECALLBACK:
        return deserializeAndCallOnSwiperGestureSwipeCallback(thisArray, thisLength);
    case KIND_ONTABSANIMATIONENDCALLBACK:
        return deserializeAndCallOnTabsAnimationEndCallback(thisArray, thisLength);
    case KIND_ONTABSANIMATIONSTARTCALLBACK:
        return deserializeAndCallOnTabsAnimationStartCallback(thisArray, thisLength);
    case KIND_ONTABSCONTENTWILLCHANGECALLBACK:
        return deserializeAndCallOnTabsContentWillChangeCallback(thisArray, thisLength);
    case KIND_ONTABSGESTURESWIPECALLBACK:
        return deserializeAndCallOnTabsGestureSwipeCallback(thisArray, thisLength);
    case KIND_ONTEXTPICKERCHANGECALLBACK:
        return deserializeAndCallOnTextPickerChangeCallback(thisArray, thisLength);
    case KIND_ONTEXTSELECTIONCHANGECALLBACK:
        return deserializeAndCallOnTextSelectionChangeCallback(thisArray, thisLength);
    case KIND_ONTIMEPICKERCHANGECALLBACK:
        return deserializeAndCallOnTimePickerChangeCallback(thisArray, thisLength);
    case KIND_ONVIEWPORTFITCHANGEDCALLBACK:
        return deserializeAndCallOnViewportFitChangedCallback(thisArray, thisLength);
    case KIND_ONWILLSCROLLCALLBACK:
        return deserializeAndCallOnWillScrollCallback(thisArray, thisLength);
    case KIND_PAGEMAPNODEBUILDER:
        return deserializeAndCallPageMapNodeBuilder(thisArray, thisLength);
    case KIND_PASTEBUTTONCALLBACK:
        return deserializeAndCallPasteButtonCallback(thisArray, thisLength);
    case KIND_PASTEEVENTCALLBACK:
        return deserializeAndCallPasteEventCallback(thisArray, thisLength);
    case KIND_PLUGINERRORCALLBACK:
        return deserializeAndCallPluginErrorCallback(thisArray, thisLength);
    case KIND_POPUPSTATECHANGECALLBACK:
        return deserializeAndCallPopupStateChangeCallback(thisArray, thisLength);
    case KIND_PROGRESSMODIFIERBUILDER:
        return deserializeAndCallProgressModifierBuilder(thisArray, thisLength);
    case KIND_RADIOMODIFIERBUILDER:
        return deserializeAndCallRadioModifierBuilder(thisArray, thisLength);
    case KIND_RATINGMODIFIERBUILDER:
        return deserializeAndCallRatingModifierBuilder(thisArray, thisLength);
    case KIND_RESTRICTEDWORKER_ONERROR_CALLBACK:
        return deserializeAndCallRestrictedWorker_onerror_Callback(thisArray, thisLength);
    case KIND_RESTRICTEDWORKER_ONEXIT_CALLBACK:
        return deserializeAndCallRestrictedWorker_onexit_Callback(thisArray, thisLength);
    case KIND_RESTRICTEDWORKER_ONMESSAGE_CALLBACK:
        return deserializeAndCallRestrictedWorker_onmessage_Callback(thisArray, thisLength);
    case KIND_REUSEIDCALLBACK:
        return deserializeAndCallReuseIdCallback(thisArray, thisLength);
    case KIND_ROUTERFINISHCALLBACK:
        return deserializeAndCallRouterFinishCallback(thisArray, thisLength);
    case KIND_SAVEBUTTONCALLBACK:
        return deserializeAndCallSaveButtonCallback(thisArray, thisLength);
    case KIND_SCROLLONSCROLLCALLBACK:
        return deserializeAndCallScrollOnScrollCallback(thisArray, thisLength);
    case KIND_SCROLLONWILLSCROLLCALLBACK:
        return deserializeAndCallScrollOnWillScrollCallback(thisArray, thisLength);
    case KIND_SEARCHSUBMITCALLBACK:
        return deserializeAndCallSearchSubmitCallback(thisArray, thisLength);
    case KIND_SEARCHVALUECALLBACK:
        return deserializeAndCallSearchValueCallback(thisArray, thisLength);
    case KIND_SHOULDBUILTINRECOGNIZERPARALLELWITHCALLBACK:
        return deserializeAndCallShouldBuiltInRecognizerParallelWithCallback(thisArray, thisLength);
    case KIND_SIZECHANGECALLBACK:
        return deserializeAndCallSizeChangeCallback(thisArray, thisLength);
    case KIND_SLIDERMODIFIERBUILDER:
        return deserializeAndCallSliderModifierBuilder(thisArray, thisLength);
    case KIND_SLIDERTRIGGERCHANGECALLBACK:
        return deserializeAndCallSliderTriggerChangeCallback(thisArray, thisLength);
    case KIND_STYLEDSTRINGMARSHALLCALLBACK:
        return deserializeAndCallStyledStringMarshallCallback(thisArray, thisLength);
    case KIND_STYLEDSTRINGUNMARSHALLCALLBACK:
        return deserializeAndCallStyledStringUnmarshallCallback(thisArray, thisLength);
    case KIND_SUBMITCALLBACK:
        return deserializeAndCallSubmitCallback(thisArray, thisLength);
    case KIND_SYNTHETIC_ASYNCCALLBACK_IMAGE_PIXELMAP_VOID:
        return deserializeAndCallsynthetic_AsyncCallback_image_PixelMap_Void(thisArray, thisLength);
    case KIND_SYNTHETIC_CALLBACK_ARRAY_STRING_VOID:
        return deserializeAndCallsynthetic_Callback_Array_String_Void(thisArray, thisLength);
    case KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID:
        return deserializeAndCallsynthetic_Callback_Boolean_Void(thisArray, thisLength);
    case KIND_SYNTHETIC_CALLBACK_DISMISSDIALOGACTION_VOID:
        return deserializeAndCallsynthetic_Callback_DismissDialogAction_Void(thisArray, thisLength);
    case KIND_SYNTHETIC_CALLBACK_F64_VOID:
        return deserializeAndCallsynthetic_Callback_F64_Void(thisArray, thisLength);
    case KIND_SYNTHETIC_CALLBACK_KEYEVENT_BOOLEAN:
        return deserializeAndCallsynthetic_Callback_KeyEvent_Boolean(thisArray, thisLength);
    case KIND_SYNTHETIC_CALLBACK_STRING_VOID:
        return deserializeAndCallsynthetic_Callback_String_Void(thisArray, thisLength);
    case KIND_SYNTHETIC_CALLBACK_TEXTPICKERRESULT_VOID:
        return deserializeAndCallsynthetic_Callback_TextPickerResult_Void(thisArray, thisLength);
    case KIND_SYNTHETIC_CALLBACK_TIMEPICKERRESULT_VOID:
        return deserializeAndCallsynthetic_Callback_TimePickerResult_Void(thisArray, thisLength);
    case KIND_SYNTHETIC_CALLBACK_VOID:
        return deserializeAndCallsynthetic_Callback_Void(thisArray, thisLength);
    case KIND_TABSCUSTOMCONTENTTRANSITIONCALLBACK:
        return deserializeAndCallTabsCustomContentTransitionCallback(thisArray, thisLength);
    case KIND_TEXTAREASUBMITCALLBACK:
        return deserializeAndCallTextAreaSubmitCallback(thisArray, thisLength);
    case KIND_TEXTCLOCKMODIFIERBUILDER:
        return deserializeAndCallTextClockModifierBuilder(thisArray, thisLength);
    case KIND_TEXTFIELDVALUECALLBACK:
        return deserializeAndCallTextFieldValueCallback(thisArray, thisLength);
    case KIND_TEXTPICKERENTERSELECTEDAREACALLBACK:
        return deserializeAndCallTextPickerEnterSelectedAreaCallback(thisArray, thisLength);
    case KIND_TEXTPICKERSCROLLSTOPCALLBACK:
        return deserializeAndCallTextPickerScrollStopCallback(thisArray, thisLength);
    case KIND_TEXTTIMERMODIFIERBUILDER:
        return deserializeAndCallTextTimerModifierBuilder(thisArray, thisLength);
    case KIND_TIMERCALLBACK:
        return deserializeAndCallTimerCallback(thisArray, thisLength);
    case KIND_TOGGLEMODIFIERBUILDER:
        return deserializeAndCallToggleModifierBuilder(thisArray, thisLength);
    case KIND_TOUCHTESTDONECALLBACK:
        return deserializeAndCallTouchTestDoneCallback(thisArray, thisLength);
    case KIND_TRANSITIONFINISHCALLBACK:
        return deserializeAndCallTransitionFinishCallback(thisArray, thisLength);
    case KIND_TYPE_COMMONMETHOD_ONDRAGSTART:
        return deserializeAndCallType_CommonMethod_onDragStart(thisArray, thisLength);
    case KIND_TYPE_NAVIGATIONATTRIBUTE_CUSTOMNAVCONTENTTRANSITION:
        return deserializeAndCallType_NavigationAttribute_customNavContentTransition(thisArray, thisLength);
    case KIND_UPDATETRANSITIONCALLBACK:
        return deserializeAndCallUpdateTransitionCallback(thisArray, thisLength);
    case KIND_VISIBLEAREACHANGECALLBACK:
        return deserializeAndCallVisibleAreaChangeCallback(thisArray, thisLength);
    case KIND_VOIDCALLBACK:
        return deserializeAndCallVoidCallback(thisArray, thisLength);
    case KIND_WEBKEYBOARDCALLBACK:
        return deserializeAndCallWebKeyboardCallback(thisArray, thisLength);
    case KIND_WORKEREVENTLISTENER:
        return deserializeAndCallWorkerEventListener(thisArray, thisLength);
    }
    INTEROP_FATAL("Unknown callback kind");
}
KOALA_EXECUTE(deserializeAndCallCallback,
              setCallbackCaller(API_KIND, static_cast<Callback_Caller_t>(deserializeAndCallCallback)))
void deserializeAndCallCallbackSync(Ark_VMContext vmContext, Ark_Int32 kind, KSerializerBuffer thisArray,
                                    Ark_Int32 thisLength)
{
    switch (kind)
    {
    case KIND_ACCESSIBILITYACTIONINTERCEPTCALLBACK:
        return deserializeAndCallSyncAccessibilityActionInterceptCallback(vmContext, thisArray, thisLength);
    case KIND_ACCESSIBILITYCALLBACK:
        return deserializeAndCallSyncAccessibilityCallback(vmContext, thisArray, thisLength);
    case KIND_ACCESSIBILITYFOCUSCALLBACK:
        return deserializeAndCallSyncAccessibilityFocusCallback(vmContext, thisArray, thisLength);
    case KIND_ACCESSIBILITYTRANSPARENTCALLBACK:
        return deserializeAndCallSyncAccessibilityTransparentCallback(vmContext, thisArray, thisLength);
    case KIND_BUTTONMODIFIERBUILDER:
        return deserializeAndCallSyncButtonModifierBuilder(vmContext, thisArray, thisLength);
    case KIND_BUTTONTRIGGERCLICKCALLBACK:
        return deserializeAndCallSyncButtonTriggerClickCallback(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_ACCESSIBILITYACTIONINTERCEPTRESULT_VOID:
        return deserializeAndCallSyncCallback_AccessibilityActionInterceptResult_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_AREA_AREA_VOID:
        return deserializeAndCallSyncCallback_Area_Area_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_ARRAY_I32_VOID:
        return deserializeAndCallSyncCallback_Array_I32_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_ARRAY_RESOURCE_VOID:
        return deserializeAndCallSyncCallback_Array_Resource_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_ARRAY_RESOURCESTR_VOID:
        return deserializeAndCallSyncCallback_Array_ResourceStr_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_ARRAY_STRING_VOID:
        return deserializeAndCallSyncCallback_Array_String_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_ARRAY_TEXTMENUITEM_VOID:
        return deserializeAndCallSyncCallback_Array_TextMenuItem_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_ARRAY_TOUCHTESTINFO_TOUCHRESULT:
        return deserializeAndCallSyncCallback_Array_TouchTestInfo_TouchResult(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_AXISEVENT_VOID:
        return deserializeAndCallSyncCallback_AxisEvent_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_BOOLEAN:
        return deserializeAndCallSyncCallback_Boolean(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_BOOLEAN_HOVEREVENT_VOID:
        return deserializeAndCallSyncCallback_Boolean_HoverEvent_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_BOOLEAN_VOID:
        return deserializeAndCallSyncCallback_Boolean_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_BUFFER_VOID:
        return deserializeAndCallSyncCallback_Buffer_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_BUSINESSERROR_VOID:
        return deserializeAndCallSyncCallback_BusinessError_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_CLICKEVENT_VOID:
        return deserializeAndCallSyncCallback_ClickEvent_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_COMPUTEDBARATTRIBUTE_VOID:
        return deserializeAndCallSyncCallback_ComputedBarAttribute_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_COPYEVENT_VOID:
        return deserializeAndCallSyncCallback_CopyEvent_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_CREATEITEM:
        return deserializeAndCallSyncCallback_CreateItem(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_CROWNEVENT_VOID:
        return deserializeAndCallSyncCallback_CrownEvent_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_CUSTOMSPANMEASUREINFO_CUSTOMSPANMETRICS:
        return deserializeAndCallSyncCallback_CustomSpanMeasureInfo_CustomSpanMetrics(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_CUSTOMSPANMETRICS_VOID:
        return deserializeAndCallSyncCallback_CustomSpanMetrics_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_CUTEVENT_VOID:
        return deserializeAndCallSyncCallback_CutEvent_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_DATE_VOID:
        return deserializeAndCallSyncCallback_Date_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_DELETEVALUE_BOOLEAN:
        return deserializeAndCallSyncCallback_DeleteValue_Boolean(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_DELETEVALUE_VOID:
        return deserializeAndCallSyncCallback_DeleteValue_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_DISMISSCONTENTCOVERACTION_VOID:
        return deserializeAndCallSyncCallback_DismissContentCoverAction_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_DISMISSDIALOGACTION_VOID:
        return deserializeAndCallSyncCallback_DismissDialogAction_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_DISMISSPOPUPACTION_VOID:
        return deserializeAndCallSyncCallback_DismissPopupAction_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_DISMISSSHEETACTION_VOID:
        return deserializeAndCallSyncCallback_DismissSheetAction_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_DRAGEVENT_OPT_STRING_VOID:
        return deserializeAndCallSyncCallback_DragEvent_Opt_String_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_DRAWCONTEXT_CUSTOMSPANDRAWINFO_VOID:
        return deserializeAndCallSyncCallback_DrawContext_CustomSpanDrawInfo_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_DRAWCONTEXT_VOID:
        return deserializeAndCallSyncCallback_DrawContext_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_EDITABLETEXTCHANGEVALUE_BOOLEAN:
        return deserializeAndCallSyncCallback_EditableTextChangeValue_Boolean(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_ERRORINFORMATION_VOID:
        return deserializeAndCallSyncCallback_ErrorInformation_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_EXTENDER_ONFINISH:
        return deserializeAndCallSyncCallback_Extender_OnFinish(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_EXTENDER_ONPROGRESS:
        return deserializeAndCallSyncCallback_Extender_OnProgress(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_F64_F64_VOID:
        return deserializeAndCallSyncCallback_F64_F64_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_F64_SLIDERCHANGEMODE_VOID:
        return deserializeAndCallSyncCallback_F64_SliderChangeMode_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_F64_VOID:
        return deserializeAndCallSyncCallback_F64_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_FOCUSAXISEVENT_VOID:
        return deserializeAndCallSyncCallback_FocusAxisEvent_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_FORMCALLBACKINFO_VOID:
        return deserializeAndCallSyncCallback_FormCallbackInfo_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_FULLSCREENINFO_VOID:
        return deserializeAndCallSyncCallback_FullscreenInfo_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_GESTUREEVENT_VOID:
        return deserializeAndCallSyncCallback_GestureEvent_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_GESTUREINFO_BASEGESTUREEVENT_GESTUREJUDGERESULT:
        return deserializeAndCallSyncCallback_GestureInfo_BaseGestureEvent_GestureJudgeResult(vmContext, thisArray,
                                                                                              thisLength);
    case KIND_CALLBACK_GESTUREJUDGERESULT_VOID:
        return deserializeAndCallSyncCallback_GestureJudgeResult_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_GESTURERECOGNIZER_VOID:
        return deserializeAndCallSyncCallback_GestureRecognizer_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_HITTESTMODE_VOID:
        return deserializeAndCallSyncCallback_HitTestMode_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_HOVEREVENT_VOID:
        return deserializeAndCallSyncCallback_HoverEvent_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_I32_F64_COMPUTEDBARATTRIBUTE:
        return deserializeAndCallSyncCallback_I32_F64_ComputedBarAttribute(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_I32_I32_BOOLEAN:
        return deserializeAndCallSyncCallback_I32_I32_Boolean(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_I32_I32_I32_VOID:
        return deserializeAndCallSyncCallback_I32_I32_I32_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_I32_I32_VOID:
        return deserializeAndCallSyncCallback_I32_I32_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_I32_TUPLE_I32_I32:
        return deserializeAndCallSyncCallback_I32_Tuple_I32_I32(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_I32_TUPLE_I32_I32_I32_I32:
        return deserializeAndCallSyncCallback_I32_Tuple_I32_I32_I32_I32(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_I32_VOID:
        return deserializeAndCallSyncCallback_I32_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_I64_VOID:
        return deserializeAndCallSyncCallback_I64_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_INSERTVALUE_BOOLEAN:
        return deserializeAndCallSyncCallback_InsertValue_Boolean(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_INSERTVALUE_VOID:
        return deserializeAndCallSyncCallback_InsertValue_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_ITEMDRAGINFO_I32_I32_BOOLEAN_VOID:
        return deserializeAndCallSyncCallback_ItemDragInfo_I32_I32_Boolean_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_ITEMDRAGINFO_I32_I32_VOID:
        return deserializeAndCallSyncCallback_ItemDragInfo_I32_I32_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_ITEMDRAGINFO_I32_VOID:
        return deserializeAndCallSyncCallback_ItemDragInfo_I32_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_ITEMDRAGINFO_VOID:
        return deserializeAndCallSyncCallback_ItemDragInfo_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_KEYEVENT_BOOLEAN:
        return deserializeAndCallSyncCallback_KeyEvent_Boolean(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_KEYEVENT_VOID:
        return deserializeAndCallSyncCallback_KeyEvent_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_LENGTH_VOID:
        return deserializeAndCallSyncCallback_Length_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_MAP_STRING_OPT_OBJECT:
        return deserializeAndCallSyncCallback_Map_String_Opt_Object(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_MARQUEESTATE_VOID:
        return deserializeAndCallSyncCallback_MarqueeState_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_MOUSEEVENT_VOID:
        return deserializeAndCallSyncCallback_MouseEvent_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_NATIVEEMBEDDATAINFO_VOID:
        return deserializeAndCallSyncCallback_NativeEmbedDataInfo_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_NATIVEEMBEDTOUCHINFO_VOID:
        return deserializeAndCallSyncCallback_NativeEmbedTouchInfo_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_NAVDESTINATIONACTIVEREASON_VOID:
        return deserializeAndCallSyncCallback_NavDestinationActiveReason_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_NAVDESTINATIONCONTEXT_VOID:
        return deserializeAndCallSyncCallback_NavDestinationContext_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_NAVIGATIONMODE_VOID:
        return deserializeAndCallSyncCallback_NavigationMode_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_NAVIGATIONTITLEMODE_VOID:
        return deserializeAndCallSyncCallback_NavigationTitleMode_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_NAVIGATIONTRANSITIONPROXY_VOID:
        return deserializeAndCallSyncCallback_NavigationTransitionProxy_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_NUMBER_VOID:
        return deserializeAndCallSyncCallback_Number_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_OBJECT_VOID:
        return deserializeAndCallSyncCallback_Object_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_ONALERTEVENT_BOOLEAN:
        return deserializeAndCallSyncCallback_OnAlertEvent_Boolean(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_ONAUDIOSTATECHANGEDEVENT_VOID:
        return deserializeAndCallSyncCallback_OnAudioStateChangedEvent_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_ONBEFOREUNLOADEVENT_BOOLEAN:
        return deserializeAndCallSyncCallback_OnBeforeUnloadEvent_Boolean(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_ONCLIENTAUTHENTICATIONEVENT_VOID:
        return deserializeAndCallSyncCallback_OnClientAuthenticationEvent_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_ONCONFIRMEVENT_BOOLEAN:
        return deserializeAndCallSyncCallback_OnConfirmEvent_Boolean(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_ONCONSOLEEVENT_BOOLEAN:
        return deserializeAndCallSyncCallback_OnConsoleEvent_Boolean(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_ONCONTEXTMENUSHOWEVENT_BOOLEAN:
        return deserializeAndCallSyncCallback_OnContextMenuShowEvent_Boolean(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_ONDATARESUBMITTEDEVENT_VOID:
        return deserializeAndCallSyncCallback_OnDataResubmittedEvent_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_ONDESTORY_VOID:
        return deserializeAndCallSyncCallback_OnDestory_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_ONDOWNLOADSTARTEVENT_VOID:
        return deserializeAndCallSyncCallback_OnDownloadStartEvent_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_ONERRORRECEIVEEVENT_VOID:
        return deserializeAndCallSyncCallback_OnErrorReceiveEvent_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_ONFAVICONRECEIVEDEVENT_VOID:
        return deserializeAndCallSyncCallback_OnFaviconReceivedEvent_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_ONFIRSTCONTENTFULPAINTEVENT_VOID:
        return deserializeAndCallSyncCallback_OnFirstContentfulPaintEvent_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_ONGEOLOCATIONSHOWEVENT_VOID:
        return deserializeAndCallSyncCallback_OnGeolocationShowEvent_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_ONHTTPAUTHREQUESTEVENT_BOOLEAN:
        return deserializeAndCallSyncCallback_OnHttpAuthRequestEvent_Boolean(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_ONHTTPERRORRECEIVEEVENT_VOID:
        return deserializeAndCallSyncCallback_OnHttpErrorReceiveEvent_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_ONINTERCEPTREQUESTEVENT_OPT_WEBRESOURCERESPONSE:
        return deserializeAndCallSyncCallback_OnInterceptRequestEvent_Opt_WebResourceResponse(vmContext, thisArray,
                                                                                              thisLength);
    case KIND_CALLBACK_ONLOADFINISHEDEVENT_VOID:
        return deserializeAndCallSyncCallback_OnLoadFinishedEvent_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_ONLOADINTERCEPTEVENT_BOOLEAN:
        return deserializeAndCallSyncCallback_OnLoadInterceptEvent_Boolean(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_ONLOADSTARTEDEVENT_VOID:
        return deserializeAndCallSyncCallback_OnLoadStartedEvent_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_ONMEASURESIZE_SIZERESULT:
        return deserializeAndCallSyncCallback_onMeasureSize_SizeResult(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_ONMOVEFROMTO:
        return deserializeAndCallSyncCallback_OnMoveFromTo(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_ONOVERSCROLLEVENT_VOID:
        return deserializeAndCallSyncCallback_OnOverScrollEvent_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_ONPAGEBEGINEVENT_VOID:
        return deserializeAndCallSyncCallback_OnPageBeginEvent_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_ONPAGEENDEVENT_VOID:
        return deserializeAndCallSyncCallback_OnPageEndEvent_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_ONPAGEVISIBLEEVENT_VOID:
        return deserializeAndCallSyncCallback_OnPageVisibleEvent_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_ONPERMISSIONREQUESTEVENT_VOID:
        return deserializeAndCallSyncCallback_OnPermissionRequestEvent_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_ONPLACECHILDREN_VOID:
        return deserializeAndCallSyncCallback_onPlaceChildren_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_ONPROGRESSCHANGEEVENT_VOID:
        return deserializeAndCallSyncCallback_OnProgressChangeEvent_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_ONPROMPTEVENT_BOOLEAN:
        return deserializeAndCallSyncCallback_OnPromptEvent_Boolean(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_ONREFRESHACCESSEDHISTORYEVENT_VOID:
        return deserializeAndCallSyncCallback_OnRefreshAccessedHistoryEvent_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_ONRENDEREXITEDEVENT_VOID:
        return deserializeAndCallSyncCallback_OnRenderExitedEvent_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_ONRESOURCELOADEVENT_VOID:
        return deserializeAndCallSyncCallback_OnResourceLoadEvent_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_ONSCALECHANGEEVENT_VOID:
        return deserializeAndCallSyncCallback_OnScaleChangeEvent_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_ONSCREENCAPTUREREQUESTEVENT_VOID:
        return deserializeAndCallSyncCallback_OnScreenCaptureRequestEvent_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_ONSCROLLEVENT_VOID:
        return deserializeAndCallSyncCallback_OnScrollEvent_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_ONSCROLLFRAMEBEGINHANDLERRESULT_VOID:
        return deserializeAndCallSyncCallback_OnScrollFrameBeginHandlerResult_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_ONSEARCHRESULTRECEIVEEVENT_VOID:
        return deserializeAndCallSyncCallback_OnSearchResultReceiveEvent_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_ONSHOWFILESELECTOREVENT_BOOLEAN:
        return deserializeAndCallSyncCallback_OnShowFileSelectorEvent_Boolean(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_ONSSLERROREVENTRECEIVEEVENT_VOID:
        return deserializeAndCallSyncCallback_OnSslErrorEventReceiveEvent_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_ONTITLERECEIVEEVENT_VOID:
        return deserializeAndCallSyncCallback_OnTitleReceiveEvent_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_ONTOUCHICONURLRECEIVEDEVENT_VOID:
        return deserializeAndCallSyncCallback_OnTouchIconUrlReceivedEvent_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_ONWINDOWNEWEVENT_VOID:
        return deserializeAndCallSyncCallback_OnWindowNewEvent_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_OPT_ARRAY_NAVDESTINATIONTRANSITION_VOID:
        return deserializeAndCallSyncCallback_Opt_Array_NavDestinationTransition_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_OPT_ARRAY_STRING_VOID:
        return deserializeAndCallSyncCallback_Opt_Array_String_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_OPT_CUSTOMNODEBUILDER_VOID:
        return deserializeAndCallSyncCallback_Opt_CustomNodeBuilder_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_OPT_NAVIGATIONANIMATEDTRANSITION_VOID:
        return deserializeAndCallSyncCallback_Opt_NavigationAnimatedTransition_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_OPT_OBJECT_VOID:
        return deserializeAndCallSyncCallback_Opt_Object_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_OPT_OFFSETRESULT_VOID:
        return deserializeAndCallSyncCallback_Opt_OffsetResult_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_OPT_SCROLLRESULT_VOID:
        return deserializeAndCallSyncCallback_Opt_ScrollResult_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_OPT_STYLEDSTRING_OPT_ARRAY_STRING_VOID:
        return deserializeAndCallSyncCallback_Opt_StyledString_Opt_Array_String_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_OPT_TABCONTENTANIMATEDTRANSITION_VOID:
        return deserializeAndCallSyncCallback_Opt_TabContentAnimatedTransition_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_OPT_WEBRESOURCERESPONSE_VOID:
        return deserializeAndCallSyncCallback_Opt_WebResourceResponse_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_PLAYBACKINFO_VOID:
        return deserializeAndCallSyncCallback_PlaybackInfo_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_POINTER_VOID:
        return deserializeAndCallSyncCallback_Pointer_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_POPINFO_VOID:
        return deserializeAndCallSyncCallback_PopInfo_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_PREDRAGSTATUS_VOID:
        return deserializeAndCallSyncCallback_PreDragStatus_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_PREPAREDINFO_VOID:
        return deserializeAndCallSyncCallback_PreparedInfo_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_RANGEUPDATE:
        return deserializeAndCallSyncCallback_RangeUpdate(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_REFRESHSTATUS_VOID:
        return deserializeAndCallSyncCallback_RefreshStatus_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_RESOURCE_VOID:
        return deserializeAndCallSyncCallback_Resource_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_RESOURCESTR_VOID:
        return deserializeAndCallSyncCallback_ResourceStr_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_RICHEDITORCHANGEVALUE_BOOLEAN:
        return deserializeAndCallSyncCallback_RichEditorChangeValue_Boolean(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_RICHEDITORDELETEVALUE_BOOLEAN:
        return deserializeAndCallSyncCallback_RichEditorDeleteValue_Boolean(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_RICHEDITORINSERTVALUE_BOOLEAN:
        return deserializeAndCallSyncCallback_RichEditorInsertValue_Boolean(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_RICHEDITORRANGE_VOID:
        return deserializeAndCallSyncCallback_RichEditorRange_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_RICHEDITORSELECTION_VOID:
        return deserializeAndCallSyncCallback_RichEditorSelection_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_RICHEDITORTEXTSPANRESULT_VOID:
        return deserializeAndCallSyncCallback_RichEditorTextSpanResult_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_SHEETDISMISS_VOID:
        return deserializeAndCallSyncCallback_SheetDismiss_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_SHEETTYPE_VOID:
        return deserializeAndCallSyncCallback_SheetType_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_SIZE_VOID:
        return deserializeAndCallSyncCallback_Size_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_SIZERESULT_VOID:
        return deserializeAndCallSyncCallback_SizeResult_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_SPRINGBACKACTION_VOID:
        return deserializeAndCallSyncCallback_SpringBackAction_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_STATESTYLESCHANGE:
        return deserializeAndCallSyncCallback_StateStylesChange(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_STRING:
        return deserializeAndCallSyncCallback_String(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_STRING_PASTEEVENT_VOID:
        return deserializeAndCallSyncCallback_String_PasteEvent_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_STRING_SURFACERECT_VOID:
        return deserializeAndCallSyncCallback_String_SurfaceRect_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_STRING_VOID:
        return deserializeAndCallSyncCallback_String_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_STYLEDSTRINGCHANGEVALUE_BOOLEAN:
        return deserializeAndCallSyncCallback_StyledStringChangeValue_Boolean(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_SWIPEACTIONSTATE_VOID:
        return deserializeAndCallSyncCallback_SwipeActionState_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_SWIPERCONTENTTRANSITIONPROXY_VOID:
        return deserializeAndCallSyncCallback_SwiperContentTransitionProxy_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_TABCONTENTTRANSITIONPROXY_VOID:
        return deserializeAndCallSyncCallback_TabContentTransitionProxy_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_TERMINATIONINFO:
        return deserializeAndCallSyncCallback_TerminationInfo(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_TEXTPICKERRESULT_VOID:
        return deserializeAndCallSyncCallback_TextPickerResult_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_TEXTRANGE_VOID:
        return deserializeAndCallSyncCallback_TextRange_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_TIMEPICKERRESULT_VOID:
        return deserializeAndCallSyncCallback_TimePickerResult_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_TOUCHEVENT_HITTESTMODE:
        return deserializeAndCallSyncCallback_TouchEvent_HitTestMode(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_TOUCHEVENT_VOID:
        return deserializeAndCallSyncCallback_TouchEvent_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_TOUCHRESULT_VOID:
        return deserializeAndCallSyncCallback_TouchResult_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_TUPLE_I32_I32_I32_I32_VOID:
        return deserializeAndCallSyncCallback_Tuple_I32_I32_I32_I32_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_TUPLE_I32_I32_VOID:
        return deserializeAndCallSyncCallback_Tuple_I32_I32_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_UIEXTENSIONPROXY:
        return deserializeAndCallSyncCallback_UIExtensionProxy(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_UNION_CUSTOMNODEBUILDER_DRAGITEMINFO_VOID:
        return deserializeAndCallSyncCallback_Union_CustomNodeBuilder_DragItemInfo_Void(vmContext, thisArray,
                                                                                        thisLength);
    case KIND_CALLBACK_USERDATASPAN_VOID:
        return deserializeAndCallSyncCallback_UserDataSpan_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_VOID_VOID:
        return deserializeAndCallSyncCallback_Void_Void(vmContext, thisArray, thisLength);
    case KIND_CALLBACK_WEBKEYBOARDOPTIONS_VOID:
        return deserializeAndCallSyncCallback_WebKeyboardOptions_Void(vmContext, thisArray, thisLength);
    case KIND_CHECKBOXMODIFIERBUILDER:
        return deserializeAndCallSyncCheckBoxModifierBuilder(vmContext, thisArray, thisLength);
    case KIND_CONTENTDIDSCROLLCALLBACK:
        return deserializeAndCallSyncContentDidScrollCallback(vmContext, thisArray, thisLength);
    case KIND_CONTENTWILLSCROLLCALLBACK:
        return deserializeAndCallSyncContentWillScrollCallback(vmContext, thisArray, thisLength);
    case KIND_CUSTOMNODEBUILDER:
        return deserializeAndCallSyncCustomNodeBuilder(vmContext, thisArray, thisLength);
    case KIND_DATAPANELMODIFIERBUILDER:
        return deserializeAndCallSyncDataPanelModifierBuilder(vmContext, thisArray, thisLength);
    case KIND_DATAPROGRESSLISTENER:
        return deserializeAndCallSyncDataProgressListener(vmContext, thisArray, thisLength);
    case KIND_EDITABLETEXTONCHANGECALLBACK:
        return deserializeAndCallSyncEditableTextOnChangeCallback(vmContext, thisArray, thisLength);
    case KIND_ERRORCALLBACK_BUSINESSERRORINTERFACE_VOID:
        return deserializeAndCallSyncErrorCallback_BusinessErrorInterface_Void(vmContext, thisArray, thisLength);
    case KIND_FRAMECALLBACKHANDLER:
        return deserializeAndCallSyncFrameCallbackHandler(vmContext, thisArray, thisLength);
    case KIND_GAUGEMODIFIERBUILDER:
        return deserializeAndCallSyncGaugeModifierBuilder(vmContext, thisArray, thisLength);
    case KIND_GESTUREEVENTHANDLER:
        return deserializeAndCallSyncGestureEventHandler(vmContext, thisArray, thisLength);
    case KIND_GESTURERECOGNIZERJUDGEBEGINCALLBACK:
        return deserializeAndCallSyncGestureRecognizerJudgeBeginCallback(vmContext, thisArray, thisLength);
    case KIND_HOVERCALLBACK:
        return deserializeAndCallSyncHoverCallback(vmContext, thisArray, thisLength);
    case KIND_IMAGECOMPLETECALLBACK:
        return deserializeAndCallSyncImageCompleteCallback(vmContext, thisArray, thisLength);
    case KIND_IMAGEERRORCALLBACK:
        return deserializeAndCallSyncImageErrorCallback(vmContext, thisArray, thisLength);
    case KIND_IMAGEONCOMPLETECALLBACK:
        return deserializeAndCallSyncImageOnCompleteCallback(vmContext, thisArray, thisLength);
    case KIND_INTERCEPTIONMODECALLBACK:
        return deserializeAndCallSyncInterceptionModeCallback(vmContext, thisArray, thisLength);
    case KIND_INTERCEPTIONSHOWCALLBACK:
        return deserializeAndCallSyncInterceptionShowCallback(vmContext, thisArray, thisLength);
    case KIND_LOADINGPROGRESSMODIFIERBUILDER:
        return deserializeAndCallSyncLoadingProgressModifierBuilder(vmContext, thisArray, thisLength);
    case KIND_MENUCALLBACK:
        return deserializeAndCallSyncMenuCallback(vmContext, thisArray, thisLength);
    case KIND_MENUITEMMODIFIERBUILDER:
        return deserializeAndCallSyncMenuItemModifierBuilder(vmContext, thisArray, thisLength);
    case KIND_MENUONAPPEARCALLBACK:
        return deserializeAndCallSyncMenuOnAppearCallback(vmContext, thisArray, thisLength);
    case KIND_MODIFIERKEYSTATEGETTER:
        return deserializeAndCallSyncModifierKeyStateGetter(vmContext, thisArray, thisLength);
    case KIND_NAVDESTINATIONTRANSITIONDELEGATE:
        return deserializeAndCallSyncNavDestinationTransitionDelegate(vmContext, thisArray, thisLength);
    case KIND_NAVEXTENDER_CREATENAVDESTINATION:
        return deserializeAndCallSyncNavExtender_CreateNavDestination(vmContext, thisArray, thisLength);
    case KIND_NAVEXTENDER_ONUPDATESTACK:
        return deserializeAndCallSyncNavExtender_OnUpdateStack(vmContext, thisArray, thisLength);
    case KIND_NODECONTAINEROPSONTOUCHCALLBACK:
        return deserializeAndCallSyncNodeContainerOpsOnTouchCallback(vmContext, thisArray, thisLength);
    case KIND_ONADSBLOCKEDCALLBACK:
        return deserializeAndCallSyncOnAdsBlockedCallback(vmContext, thisArray, thisLength);
    case KIND_ONALPHABETINDEXERPOPUPSELECTCALLBACK:
        return deserializeAndCallSyncOnAlphabetIndexerPopupSelectCallback(vmContext, thisArray, thisLength);
    case KIND_ONALPHABETINDEXERREQUESTPOPUPDATACALLBACK:
        return deserializeAndCallSyncOnAlphabetIndexerRequestPopupDataCallback(vmContext, thisArray, thisLength);
    case KIND_ONALPHABETINDEXERSELECTCALLBACK:
        return deserializeAndCallSyncOnAlphabetIndexerSelectCallback(vmContext, thisArray, thisLength);
    case KIND_ONCHECKBOXCHANGECALLBACK:
        return deserializeAndCallSyncOnCheckboxChangeCallback(vmContext, thisArray, thisLength);
    case KIND_ONCHECKBOXGROUPCHANGECALLBACK:
        return deserializeAndCallSyncOnCheckboxGroupChangeCallback(vmContext, thisArray, thisLength);
    case KIND_ONCONTENTSCROLLCALLBACK:
        return deserializeAndCallSyncOnContentScrollCallback(vmContext, thisArray, thisLength);
    case KIND_ONCONTEXTMENUHIDECALLBACK:
        return deserializeAndCallSyncOnContextMenuHideCallback(vmContext, thisArray, thisLength);
    case KIND_ONCREATEMENUCALLBACK:
        return deserializeAndCallSyncOnCreateMenuCallback(vmContext, thisArray, thisLength);
    case KIND_ONDIDCHANGECALLBACK:
        return deserializeAndCallSyncOnDidChangeCallback(vmContext, thisArray, thisLength);
    case KIND_ONDRAGEVENTCALLBACK:
        return deserializeAndCallSyncOnDragEventCallback(vmContext, thisArray, thisLength);
    case KIND_ONFIRSTMEANINGFULPAINTCALLBACK:
        return deserializeAndCallSyncOnFirstMeaningfulPaintCallback(vmContext, thisArray, thisLength);
    case KIND_ONFOLDSTATUSCHANGECALLBACK:
        return deserializeAndCallSyncOnFoldStatusChangeCallback(vmContext, thisArray, thisLength);
    case KIND_ONFULLSCREENENTERCALLBACK:
        return deserializeAndCallSyncOnFullScreenEnterCallback(vmContext, thisArray, thisLength);
    case KIND_ONHOVERCALLBACK:
        return deserializeAndCallSyncOnHoverCallback(vmContext, thisArray, thisLength);
    case KIND_ONHOVERSTATUSCHANGECALLBACK:
        return deserializeAndCallSyncOnHoverStatusChangeCallback(vmContext, thisArray, thisLength);
    case KIND_ONINTELLIGENTTRACKINGPREVENTIONCALLBACK:
        return deserializeAndCallSyncOnIntelligentTrackingPreventionCallback(vmContext, thisArray, thisLength);
    case KIND_ONITEMDRAGSTARTCALLBACK:
        return deserializeAndCallSyncOnItemDragStartCallback(vmContext, thisArray, thisLength);
    case KIND_ONLARGESTCONTENTFULPAINTCALLBACK:
        return deserializeAndCallSyncOnLargestContentfulPaintCallback(vmContext, thisArray, thisLength);
    case KIND_ONMENUITEMCLICKCALLBACK:
        return deserializeAndCallSyncOnMenuItemClickCallback(vmContext, thisArray, thisLength);
    case KIND_ONMOVEHANDLER:
        return deserializeAndCallSyncOnMoveHandler(vmContext, thisArray, thisLength);
    case KIND_ONNATIVEEMBEDVISIBILITYCHANGECALLBACK:
        return deserializeAndCallSyncOnNativeEmbedVisibilityChangeCallback(vmContext, thisArray, thisLength);
    case KIND_ONNAVIGATIONENTRYCOMMITTEDCALLBACK:
        return deserializeAndCallSyncOnNavigationEntryCommittedCallback(vmContext, thisArray, thisLength);
    case KIND_ONOVERRIDEURLLOADINGCALLBACK:
        return deserializeAndCallSyncOnOverrideUrlLoadingCallback(vmContext, thisArray, thisLength);
    case KIND_ONPASTECALLBACK:
        return deserializeAndCallSyncOnPasteCallback(vmContext, thisArray, thisLength);
    case KIND_ONRADIOCHANGECALLBACK:
        return deserializeAndCallSyncOnRadioChangeCallback(vmContext, thisArray, thisLength);
    case KIND_ONRATINGCHANGECALLBACK:
        return deserializeAndCallSyncOnRatingChangeCallback(vmContext, thisArray, thisLength);
    case KIND_ONRENDERPROCESSNOTRESPONDINGCALLBACK:
        return deserializeAndCallSyncOnRenderProcessNotRespondingCallback(vmContext, thisArray, thisLength);
    case KIND_ONRENDERPROCESSRESPONDINGCALLBACK:
        return deserializeAndCallSyncOnRenderProcessRespondingCallback(vmContext, thisArray, thisLength);
    case KIND_ONSAFEBROWSINGCHECKRESULTCALLBACK:
        return deserializeAndCallSyncOnSafeBrowsingCheckResultCallback(vmContext, thisArray, thisLength);
    case KIND_ONSCROLLCALLBACK:
        return deserializeAndCallSyncOnScrollCallback(vmContext, thisArray, thisLength);
    case KIND_ONSCROLLEDGECALLBACK:
        return deserializeAndCallSyncOnScrollEdgeCallback(vmContext, thisArray, thisLength);
    case KIND_ONSCROLLFRAMEBEGINCALLBACK:
        return deserializeAndCallSyncOnScrollFrameBeginCallback(vmContext, thisArray, thisLength);
    case KIND_ONSCROLLVISIBLECONTENTCHANGECALLBACK:
        return deserializeAndCallSyncOnScrollVisibleContentChangeCallback(vmContext, thisArray, thisLength);
    case KIND_ONSELECTCALLBACK:
        return deserializeAndCallSyncOnSelectCallback(vmContext, thisArray, thisLength);
    case KIND_ONSSLERROREVENTCALLBACK:
        return deserializeAndCallSyncOnSslErrorEventCallback(vmContext, thisArray, thisLength);
    case KIND_ONSUBMITCALLBACK:
        return deserializeAndCallSyncOnSubmitCallback(vmContext, thisArray, thisLength);
    case KIND_ONSWIPERANIMATIONENDCALLBACK:
        return deserializeAndCallSyncOnSwiperAnimationEndCallback(vmContext, thisArray, thisLength);
    case KIND_ONSWIPERANIMATIONSTARTCALLBACK:
        return deserializeAndCallSyncOnSwiperAnimationStartCallback(vmContext, thisArray, thisLength);
    case KIND_ONSWIPERGESTURESWIPECALLBACK:
        return deserializeAndCallSyncOnSwiperGestureSwipeCallback(vmContext, thisArray, thisLength);
    case KIND_ONTABSANIMATIONENDCALLBACK:
        return deserializeAndCallSyncOnTabsAnimationEndCallback(vmContext, thisArray, thisLength);
    case KIND_ONTABSANIMATIONSTARTCALLBACK:
        return deserializeAndCallSyncOnTabsAnimationStartCallback(vmContext, thisArray, thisLength);
    case KIND_ONTABSCONTENTWILLCHANGECALLBACK:
        return deserializeAndCallSyncOnTabsContentWillChangeCallback(vmContext, thisArray, thisLength);
    case KIND_ONTABSGESTURESWIPECALLBACK:
        return deserializeAndCallSyncOnTabsGestureSwipeCallback(vmContext, thisArray, thisLength);
    case KIND_ONTEXTPICKERCHANGECALLBACK:
        return deserializeAndCallSyncOnTextPickerChangeCallback(vmContext, thisArray, thisLength);
    case KIND_ONTEXTSELECTIONCHANGECALLBACK:
        return deserializeAndCallSyncOnTextSelectionChangeCallback(vmContext, thisArray, thisLength);
    case KIND_ONTIMEPICKERCHANGECALLBACK:
        return deserializeAndCallSyncOnTimePickerChangeCallback(vmContext, thisArray, thisLength);
    case KIND_ONVIEWPORTFITCHANGEDCALLBACK:
        return deserializeAndCallSyncOnViewportFitChangedCallback(vmContext, thisArray, thisLength);
    case KIND_ONWILLSCROLLCALLBACK:
        return deserializeAndCallSyncOnWillScrollCallback(vmContext, thisArray, thisLength);
    case KIND_PAGEMAPNODEBUILDER:
        return deserializeAndCallSyncPageMapNodeBuilder(vmContext, thisArray, thisLength);
    case KIND_PASTEBUTTONCALLBACK:
        return deserializeAndCallSyncPasteButtonCallback(vmContext, thisArray, thisLength);
    case KIND_PASTEEVENTCALLBACK:
        return deserializeAndCallSyncPasteEventCallback(vmContext, thisArray, thisLength);
    case KIND_PLUGINERRORCALLBACK:
        return deserializeAndCallSyncPluginErrorCallback(vmContext, thisArray, thisLength);
    case KIND_POPUPSTATECHANGECALLBACK:
        return deserializeAndCallSyncPopupStateChangeCallback(vmContext, thisArray, thisLength);
    case KIND_PROGRESSMODIFIERBUILDER:
        return deserializeAndCallSyncProgressModifierBuilder(vmContext, thisArray, thisLength);
    case KIND_RADIOMODIFIERBUILDER:
        return deserializeAndCallSyncRadioModifierBuilder(vmContext, thisArray, thisLength);
    case KIND_RATINGMODIFIERBUILDER:
        return deserializeAndCallSyncRatingModifierBuilder(vmContext, thisArray, thisLength);
    case KIND_RESTRICTEDWORKER_ONERROR_CALLBACK:
        return deserializeAndCallSyncRestrictedWorker_onerror_Callback(vmContext, thisArray, thisLength);
    case KIND_RESTRICTEDWORKER_ONEXIT_CALLBACK:
        return deserializeAndCallSyncRestrictedWorker_onexit_Callback(vmContext, thisArray, thisLength);
    case KIND_RESTRICTEDWORKER_ONMESSAGE_CALLBACK:
        return deserializeAndCallSyncRestrictedWorker_onmessage_Callback(vmContext, thisArray, thisLength);
    case KIND_REUSEIDCALLBACK:
        return deserializeAndCallSyncReuseIdCallback(vmContext, thisArray, thisLength);
    case KIND_ROUTERFINISHCALLBACK:
        return deserializeAndCallSyncRouterFinishCallback(vmContext, thisArray, thisLength);
    case KIND_SAVEBUTTONCALLBACK:
        return deserializeAndCallSyncSaveButtonCallback(vmContext, thisArray, thisLength);
    case KIND_SCROLLONSCROLLCALLBACK:
        return deserializeAndCallSyncScrollOnScrollCallback(vmContext, thisArray, thisLength);
    case KIND_SCROLLONWILLSCROLLCALLBACK:
        return deserializeAndCallSyncScrollOnWillScrollCallback(vmContext, thisArray, thisLength);
    case KIND_SEARCHSUBMITCALLBACK:
        return deserializeAndCallSyncSearchSubmitCallback(vmContext, thisArray, thisLength);
    case KIND_SEARCHVALUECALLBACK:
        return deserializeAndCallSyncSearchValueCallback(vmContext, thisArray, thisLength);
    case KIND_SHOULDBUILTINRECOGNIZERPARALLELWITHCALLBACK:
        return deserializeAndCallSyncShouldBuiltInRecognizerParallelWithCallback(vmContext, thisArray, thisLength);
    case KIND_SIZECHANGECALLBACK:
        return deserializeAndCallSyncSizeChangeCallback(vmContext, thisArray, thisLength);
    case KIND_SLIDERMODIFIERBUILDER:
        return deserializeAndCallSyncSliderModifierBuilder(vmContext, thisArray, thisLength);
    case KIND_SLIDERTRIGGERCHANGECALLBACK:
        return deserializeAndCallSyncSliderTriggerChangeCallback(vmContext, thisArray, thisLength);
    case KIND_STYLEDSTRINGMARSHALLCALLBACK:
        return deserializeAndCallSyncStyledStringMarshallCallback(vmContext, thisArray, thisLength);
    case KIND_STYLEDSTRINGUNMARSHALLCALLBACK:
        return deserializeAndCallSyncStyledStringUnmarshallCallback(vmContext, thisArray, thisLength);
    case KIND_SUBMITCALLBACK:
        return deserializeAndCallSyncSubmitCallback(vmContext, thisArray, thisLength);
    case KIND_SYNTHETIC_ASYNCCALLBACK_IMAGE_PIXELMAP_VOID:
        return deserializeAndCallSyncsynthetic_AsyncCallback_image_PixelMap_Void(vmContext, thisArray, thisLength);
    case KIND_SYNTHETIC_CALLBACK_ARRAY_STRING_VOID:
        return deserializeAndCallSyncsynthetic_Callback_Array_String_Void(vmContext, thisArray, thisLength);
    case KIND_SYNTHETIC_CALLBACK_BOOLEAN_VOID:
        return deserializeAndCallSyncsynthetic_Callback_Boolean_Void(vmContext, thisArray, thisLength);
    case KIND_SYNTHETIC_CALLBACK_DISMISSDIALOGACTION_VOID:
        return deserializeAndCallSyncsynthetic_Callback_DismissDialogAction_Void(vmContext, thisArray, thisLength);
    case KIND_SYNTHETIC_CALLBACK_F64_VOID:
        return deserializeAndCallSyncsynthetic_Callback_F64_Void(vmContext, thisArray, thisLength);
    case KIND_SYNTHETIC_CALLBACK_KEYEVENT_BOOLEAN:
        return deserializeAndCallSyncsynthetic_Callback_KeyEvent_Boolean(vmContext, thisArray, thisLength);
    case KIND_SYNTHETIC_CALLBACK_STRING_VOID:
        return deserializeAndCallSyncsynthetic_Callback_String_Void(vmContext, thisArray, thisLength);
    case KIND_SYNTHETIC_CALLBACK_TEXTPICKERRESULT_VOID:
        return deserializeAndCallSyncsynthetic_Callback_TextPickerResult_Void(vmContext, thisArray, thisLength);
    case KIND_SYNTHETIC_CALLBACK_TIMEPICKERRESULT_VOID:
        return deserializeAndCallSyncsynthetic_Callback_TimePickerResult_Void(vmContext, thisArray, thisLength);
    case KIND_SYNTHETIC_CALLBACK_VOID:
        return deserializeAndCallSyncsynthetic_Callback_Void(vmContext, thisArray, thisLength);
    case KIND_TABSCUSTOMCONTENTTRANSITIONCALLBACK:
        return deserializeAndCallSyncTabsCustomContentTransitionCallback(vmContext, thisArray, thisLength);
    case KIND_TEXTAREASUBMITCALLBACK:
        return deserializeAndCallSyncTextAreaSubmitCallback(vmContext, thisArray, thisLength);
    case KIND_TEXTCLOCKMODIFIERBUILDER:
        return deserializeAndCallSyncTextClockModifierBuilder(vmContext, thisArray, thisLength);
    case KIND_TEXTFIELDVALUECALLBACK:
        return deserializeAndCallSyncTextFieldValueCallback(vmContext, thisArray, thisLength);
    case KIND_TEXTPICKERENTERSELECTEDAREACALLBACK:
        return deserializeAndCallSyncTextPickerEnterSelectedAreaCallback(vmContext, thisArray, thisLength);
    case KIND_TEXTPICKERSCROLLSTOPCALLBACK:
        return deserializeAndCallSyncTextPickerScrollStopCallback(vmContext, thisArray, thisLength);
    case KIND_TEXTTIMERMODIFIERBUILDER:
        return deserializeAndCallSyncTextTimerModifierBuilder(vmContext, thisArray, thisLength);
    case KIND_TIMERCALLBACK:
        return deserializeAndCallSyncTimerCallback(vmContext, thisArray, thisLength);
    case KIND_TOGGLEMODIFIERBUILDER:
        return deserializeAndCallSyncToggleModifierBuilder(vmContext, thisArray, thisLength);
    case KIND_TOUCHTESTDONECALLBACK:
        return deserializeAndCallSyncTouchTestDoneCallback(vmContext, thisArray, thisLength);
    case KIND_TRANSITIONFINISHCALLBACK:
        return deserializeAndCallSyncTransitionFinishCallback(vmContext, thisArray, thisLength);
    case KIND_TYPE_COMMONMETHOD_ONDRAGSTART:
        return deserializeAndCallSyncType_CommonMethod_onDragStart(vmContext, thisArray, thisLength);
    case KIND_TYPE_NAVIGATIONATTRIBUTE_CUSTOMNAVCONTENTTRANSITION:
        return deserializeAndCallSyncType_NavigationAttribute_customNavContentTransition(vmContext, thisArray,
                                                                                         thisLength);
    case KIND_UPDATETRANSITIONCALLBACK:
        return deserializeAndCallSyncUpdateTransitionCallback(vmContext, thisArray, thisLength);
    case KIND_VISIBLEAREACHANGECALLBACK:
        return deserializeAndCallSyncVisibleAreaChangeCallback(vmContext, thisArray, thisLength);
    case KIND_VOIDCALLBACK:
        return deserializeAndCallSyncVoidCallback(vmContext, thisArray, thisLength);
    case KIND_WEBKEYBOARDCALLBACK:
        return deserializeAndCallSyncWebKeyboardCallback(vmContext, thisArray, thisLength);
    case KIND_WORKEREVENTLISTENER:
        return deserializeAndCallSyncWorkerEventListener(vmContext, thisArray, thisLength);
    }
    INTEROP_FATAL("Unknown callback kind");
}
KOALA_EXECUTE(deserializeAndCallCallbackSync,
              setCallbackCallerSync(API_KIND, static_cast<Callback_Caller_Sync_t>(deserializeAndCallCallbackSync)))