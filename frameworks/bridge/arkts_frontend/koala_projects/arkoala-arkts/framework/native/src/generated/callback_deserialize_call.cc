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
void deserializeAndCallAccessibilityActionInterceptCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_AccessibilityAction action, const Callback_AccessibilityActionInterceptResult_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_AccessibilityActionInterceptCallback))));
    thisDeserializer.readPointer();
    Ark_AccessibilityAction action = static_cast<Ark_AccessibilityAction>(thisDeserializer.readInt32());
    Callback_AccessibilityActionInterceptResult_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_AccessibilityActionInterceptResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_AccessibilityActionInterceptResult_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_AccessibilityActionInterceptResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_AccessibilityActionInterceptResult_Void))))};
    _call(_resourceId, action, continuationResult);
}
void deserializeAndCallSyncAccessibilityActionInterceptCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_AccessibilityAction action, const Callback_AccessibilityActionInterceptResult_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_AccessibilityActionInterceptCallback))));
    Ark_AccessibilityAction action = static_cast<Ark_AccessibilityAction>(thisDeserializer.readInt32());
    Callback_AccessibilityActionInterceptResult_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_AccessibilityActionInterceptResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_AccessibilityActionInterceptResult_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_AccessibilityActionInterceptResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_AccessibilityActionInterceptResult_Void))))};
    callSyncMethod(vmContext, resourceId, action, continuationResult);
}
void deserializeAndCallAccessibilityCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean isHover, const Ark_AccessibilityHoverEvent event)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_AccessibilityCallback))));
    thisDeserializer.readPointer();
    Ark_Boolean isHover = thisDeserializer.readBoolean();
    Ark_AccessibilityHoverEvent event = static_cast<Ark_AccessibilityHoverEvent>(AccessibilityHoverEvent_serializer::read(thisDeserializer));
    _call(_resourceId, isHover, event);
}
void deserializeAndCallSyncAccessibilityCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isHover, const Ark_AccessibilityHoverEvent event)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_AccessibilityCallback))));
    Ark_Boolean isHover = thisDeserializer.readBoolean();
    Ark_AccessibilityHoverEvent event = static_cast<Ark_AccessibilityHoverEvent>(AccessibilityHoverEvent_serializer::read(thisDeserializer));
    callSyncMethod(vmContext, resourceId, isHover, event);
}
void deserializeAndCallAccessibilityFocusCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean isFocus)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_AccessibilityFocusCallback))));
    thisDeserializer.readPointer();
    Ark_Boolean isFocus = thisDeserializer.readBoolean();
    _call(_resourceId, isFocus);
}
void deserializeAndCallSyncAccessibilityFocusCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isFocus)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_AccessibilityFocusCallback))));
    Ark_Boolean isFocus = thisDeserializer.readBoolean();
    callSyncMethod(vmContext, resourceId, isFocus);
}
void deserializeAndCallAsyncCallback_image_PixelMap_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_image_PixelMap result)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_AsyncCallback_image_PixelMap_Void))));
    thisDeserializer.readPointer();
    Ark_image_PixelMap result = static_cast<Ark_image_PixelMap>(image_PixelMap_serializer::read(thisDeserializer));
    _call(_resourceId, result);
}
void deserializeAndCallSyncAsyncCallback_image_PixelMap_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_image_PixelMap result)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_AsyncCallback_image_PixelMap_Void))));
    Ark_image_PixelMap result = static_cast<Ark_image_PixelMap>(image_PixelMap_serializer::read(thisDeserializer));
    callSyncMethod(vmContext, resourceId, result);
}
void deserializeAndCallAsyncCallback_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_BusinessError err, const Opt_void data)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_AsyncCallback_Void))));
    thisDeserializer.readPointer();
    const auto errTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_BusinessError errTmpBuf = {};
    errTmpBuf.tag = errTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((errTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED)) {
        errTmpBuf.value = static_cast<Ark_BusinessError>(BusinessError_serializer::read(thisDeserializer));
    }
    Opt_BusinessError err = errTmpBuf;
    const auto dataTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_void dataTmpBuf = {};
    dataTmpBuf.tag = dataTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((dataTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED)) {
        dataTmpBuf.value = Ark_Void();
    }
    Opt_void data = dataTmpBuf;
    _call(_resourceId, err, data);
}
void deserializeAndCallSyncAsyncCallback_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_BusinessError err, const Opt_void data)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_AsyncCallback_Void))));
    const auto errTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_BusinessError errTmpBuf = {};
    errTmpBuf.tag = errTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((errTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED)) {
        errTmpBuf.value = static_cast<Ark_BusinessError>(BusinessError_serializer::read(thisDeserializer));
    }
    Opt_BusinessError err = errTmpBuf;
    const auto dataTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_void dataTmpBuf = {};
    dataTmpBuf.tag = dataTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((dataTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED)) {
        dataTmpBuf.value = Ark_Void();
    }
    Opt_void data = dataTmpBuf;
    callSyncMethod(vmContext, resourceId, err, data);
}
void deserializeAndCallButtonModifierBuilder(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Ark_ButtonConfiguration config, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_ButtonModifierBuilder))));
    thisDeserializer.readPointer();
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_ButtonConfiguration config = ButtonConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Pointer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Pointer_Void))))};
    _call(_resourceId, parentNode, config, continuationResult);
}
void deserializeAndCallSyncButtonModifierBuilder(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Ark_ButtonConfiguration config, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_ButtonModifierBuilder))));
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_ButtonConfiguration config = ButtonConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Pointer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Pointer_Void))))};
    callSyncMethod(vmContext, resourceId, parentNode, config, continuationResult);
}
void deserializeAndCallButtonTriggerClickCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Float64 xPos, const Ark_Float64 yPos)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_ButtonTriggerClickCallback))));
    thisDeserializer.readPointer();
    Ark_Float64 xPos = thisDeserializer.readFloat64();
    Ark_Float64 yPos = thisDeserializer.readFloat64();
    _call(_resourceId, xPos, yPos);
}
void deserializeAndCallSyncButtonTriggerClickCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Float64 xPos, const Ark_Float64 yPos)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_ButtonTriggerClickCallback))));
    Ark_Float64 xPos = thisDeserializer.readFloat64();
    Ark_Float64 yPos = thisDeserializer.readFloat64();
    callSyncMethod(vmContext, resourceId, xPos, yPos);
}
void deserializeAndCallCallback_AccessibilityActionInterceptResult_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_AccessibilityActionInterceptResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_AccessibilityActionInterceptResult_Void))));
    thisDeserializer.readPointer();
    Ark_AccessibilityActionInterceptResult value = static_cast<Ark_AccessibilityActionInterceptResult>(thisDeserializer.readInt32());
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_AccessibilityActionInterceptResult_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_AccessibilityActionInterceptResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_AccessibilityActionInterceptResult_Void))));
    Ark_AccessibilityActionInterceptResult value = static_cast<Ark_AccessibilityActionInterceptResult>(thisDeserializer.readInt32());
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallCallback_Area_Area_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Area oldValue, const Ark_Area newValue)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Area_Area_Void))));
    thisDeserializer.readPointer();
    Ark_Area oldValue = Area_serializer::read(thisDeserializer);
    Ark_Area newValue = Area_serializer::read(thisDeserializer);
    _call(_resourceId, oldValue, newValue);
}
void deserializeAndCallSyncCallback_Area_Area_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Area oldValue, const Ark_Area newValue)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Area_Area_Void))));
    Ark_Area oldValue = Area_serializer::read(thisDeserializer);
    Ark_Area newValue = Area_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, oldValue, newValue);
}
void deserializeAndCallCallback_Array_I32_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Array_Int32 input)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Array_I32_Void))));
    thisDeserializer.readPointer();
    const Ark_Int32 inputTmpBufLength = thisDeserializer.readInt32();
    Array_Int32 inputTmpBuf = {};
    thisDeserializer.resizeArray<std::decay<decltype(inputTmpBuf)>::type,
        std::decay<decltype(*inputTmpBuf.array)>::type>(&inputTmpBuf, inputTmpBufLength);
    for (int inputTmpBufBufCounterI = 0; inputTmpBufBufCounterI < inputTmpBufLength; inputTmpBufBufCounterI++) {
        inputTmpBuf.array[inputTmpBufBufCounterI] = thisDeserializer.readInt32();
    }
    Array_Int32 input = inputTmpBuf;
    _call(_resourceId, input);
}
void deserializeAndCallSyncCallback_Array_I32_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Array_Int32 input)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Array_I32_Void))));
    const Ark_Int32 inputTmpBufLength = thisDeserializer.readInt32();
    Array_Int32 inputTmpBuf = {};
    thisDeserializer.resizeArray<std::decay<decltype(inputTmpBuf)>::type,
        std::decay<decltype(*inputTmpBuf.array)>::type>(&inputTmpBuf, inputTmpBufLength);
    for (int inputTmpBufBufCounterI = 0; inputTmpBufBufCounterI < inputTmpBufLength; inputTmpBufBufCounterI++) {
        inputTmpBuf.array[inputTmpBufBufCounterI] = thisDeserializer.readInt32();
    }
    Array_Int32 input = inputTmpBuf;
    callSyncMethod(vmContext, resourceId, input);
}
void deserializeAndCallCallback_Array_String_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Array_String value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Array_String_Void))));
    thisDeserializer.readPointer();
    const Ark_Int32 valueTmpBufLength = thisDeserializer.readInt32();
    Array_String valueTmpBuf = {};
    thisDeserializer.resizeArray<std::decay<decltype(valueTmpBuf)>::type,
        std::decay<decltype(*valueTmpBuf.array)>::type>(&valueTmpBuf, valueTmpBufLength);
    for (int valueTmpBufBufCounterI = 0; valueTmpBufBufCounterI < valueTmpBufLength; valueTmpBufBufCounterI++) {
        valueTmpBuf.array[valueTmpBufBufCounterI] = static_cast<Ark_String>(thisDeserializer.readString());
    }
    Array_String value = valueTmpBuf;
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_Array_String_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Array_String value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Array_String_Void))));
    const Ark_Int32 valueTmpBufLength = thisDeserializer.readInt32();
    Array_String valueTmpBuf = {};
    thisDeserializer.resizeArray<std::decay<decltype(valueTmpBuf)>::type,
        std::decay<decltype(*valueTmpBuf.array)>::type>(&valueTmpBuf, valueTmpBufLength);
    for (int valueTmpBufBufCounterI = 0; valueTmpBufBufCounterI < valueTmpBufLength; valueTmpBufBufCounterI++) {
        valueTmpBuf.array[valueTmpBufBufCounterI] = static_cast<Ark_String>(thisDeserializer.readString());
    }
    Array_String value = valueTmpBuf;
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallCallback_Array_TextMenuItem_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Array_TextMenuItem value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Array_TextMenuItem_Void))));
    thisDeserializer.readPointer();
    const Ark_Int32 valueTmpBufLength = thisDeserializer.readInt32();
    Array_TextMenuItem valueTmpBuf = {};
    thisDeserializer.resizeArray<std::decay<decltype(valueTmpBuf)>::type,
        std::decay<decltype(*valueTmpBuf.array)>::type>(&valueTmpBuf, valueTmpBufLength);
    for (int valueTmpBufBufCounterI = 0; valueTmpBufBufCounterI < valueTmpBufLength; valueTmpBufBufCounterI++) {
        valueTmpBuf.array[valueTmpBufBufCounterI] = TextMenuItem_serializer::read(thisDeserializer);
    }
    Array_TextMenuItem value = valueTmpBuf;
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_Array_TextMenuItem_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Array_TextMenuItem value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Array_TextMenuItem_Void))));
    const Ark_Int32 valueTmpBufLength = thisDeserializer.readInt32();
    Array_TextMenuItem valueTmpBuf = {};
    thisDeserializer.resizeArray<std::decay<decltype(valueTmpBuf)>::type,
        std::decay<decltype(*valueTmpBuf.array)>::type>(&valueTmpBuf, valueTmpBufLength);
    for (int valueTmpBufBufCounterI = 0; valueTmpBufBufCounterI < valueTmpBufLength; valueTmpBufBufCounterI++) {
        valueTmpBuf.array[valueTmpBufBufCounterI] = TextMenuItem_serializer::read(thisDeserializer);
    }
    Array_TextMenuItem value = valueTmpBuf;
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallCallback_Array_TouchTestInfo_TouchResult(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Array_TouchTestInfo value, const Callback_TouchResult_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Array_TouchTestInfo_TouchResult))));
    thisDeserializer.readPointer();
    const Ark_Int32 valueTmpBufLength = thisDeserializer.readInt32();
    Array_TouchTestInfo valueTmpBuf = {};
    thisDeserializer.resizeArray<std::decay<decltype(valueTmpBuf)>::type,
        std::decay<decltype(*valueTmpBuf.array)>::type>(&valueTmpBuf, valueTmpBufLength);
    for (int valueTmpBufBufCounterI = 0; valueTmpBufBufCounterI < valueTmpBufLength; valueTmpBufBufCounterI++) {
        valueTmpBuf.array[valueTmpBufBufCounterI] = TouchTestInfo_serializer::read(thisDeserializer);
    }
    Array_TouchTestInfo value = valueTmpBuf;
    Callback_TouchResult_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_TouchResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_TouchResult_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_TouchResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_TouchResult_Void))))};
    _call(_resourceId, value, continuationResult);
}
void deserializeAndCallSyncCallback_Array_TouchTestInfo_TouchResult(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Array_TouchTestInfo value, const Callback_TouchResult_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Array_TouchTestInfo_TouchResult))));
    const Ark_Int32 valueTmpBufLength = thisDeserializer.readInt32();
    Array_TouchTestInfo valueTmpBuf = {};
    thisDeserializer.resizeArray<std::decay<decltype(valueTmpBuf)>::type,
        std::decay<decltype(*valueTmpBuf.array)>::type>(&valueTmpBuf, valueTmpBufLength);
    for (int valueTmpBufBufCounterI = 0; valueTmpBufBufCounterI < valueTmpBufLength; valueTmpBufBufCounterI++) {
        valueTmpBuf.array[valueTmpBufBufCounterI] = TouchTestInfo_serializer::read(thisDeserializer);
    }
    Array_TouchTestInfo value = valueTmpBuf;
    Callback_TouchResult_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_TouchResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_TouchResult_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_TouchResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_TouchResult_Void))))};
    callSyncMethod(vmContext, resourceId, value, continuationResult);
}
void deserializeAndCallCallback_AxisEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_AxisEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_AxisEvent_Void))));
    thisDeserializer.readPointer();
    Ark_AxisEvent value0 = static_cast<Ark_AxisEvent>(AxisEvent_serializer::read(thisDeserializer));
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_AxisEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_AxisEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_AxisEvent_Void))));
    Ark_AxisEvent value0 = static_cast<Ark_AxisEvent>(AxisEvent_serializer::read(thisDeserializer));
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean))));
    thisDeserializer.readPointer();
    Callback_Boolean_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, continuationResult);
}
void deserializeAndCallSyncCallback_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean))));
    Callback_Boolean_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    callSyncMethod(vmContext, resourceId, continuationResult);
}
void deserializeAndCallCallback_Boolean_HoverEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean isHover, const Ark_HoverEvent event)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_HoverEvent_Void))));
    thisDeserializer.readPointer();
    Ark_Boolean isHover = thisDeserializer.readBoolean();
    Ark_HoverEvent event = static_cast<Ark_HoverEvent>(HoverEvent_serializer::read(thisDeserializer));
    _call(_resourceId, isHover, event);
}
void deserializeAndCallSyncCallback_Boolean_HoverEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isHover, const Ark_HoverEvent event)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_HoverEvent_Void))));
    Ark_Boolean isHover = thisDeserializer.readBoolean();
    Ark_HoverEvent event = static_cast<Ark_HoverEvent>(HoverEvent_serializer::read(thisDeserializer));
    callSyncMethod(vmContext, resourceId, isHover, event);
}
void deserializeAndCallCallback_Boolean_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void))));
    thisDeserializer.readPointer();
    Ark_Boolean value0 = thisDeserializer.readBoolean();
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_Boolean_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))));
    Ark_Boolean value0 = thisDeserializer.readBoolean();
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_Buffer_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Buffer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Buffer_Void))));
    thisDeserializer.readPointer();
    Ark_Buffer value = static_cast<Ark_Buffer>(thisDeserializer.readBuffer());
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_Buffer_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Buffer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Buffer_Void))));
    Ark_Buffer value = static_cast<Ark_Buffer>(thisDeserializer.readBuffer());
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallCallback_BusinessError_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Int32 code, const Ark_String message)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_BusinessError_Void))));
    thisDeserializer.readPointer();
    Ark_Int32 code = thisDeserializer.readInt32();
    Ark_String message = static_cast<Ark_String>(thisDeserializer.readString());
    _call(_resourceId, code, message);
}
void deserializeAndCallSyncCallback_BusinessError_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int32 code, const Ark_String message)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_BusinessError_Void))));
    Ark_Int32 code = thisDeserializer.readInt32();
    Ark_String message = static_cast<Ark_String>(thisDeserializer.readString());
    callSyncMethod(vmContext, resourceId, code, message);
}
void deserializeAndCallCallback_ClickEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_ClickEvent event)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_ClickEvent_Void))));
    thisDeserializer.readPointer();
    Ark_ClickEvent event = static_cast<Ark_ClickEvent>(ClickEvent_serializer::read(thisDeserializer));
    _call(_resourceId, event);
}
void deserializeAndCallSyncCallback_ClickEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_ClickEvent event)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_ClickEvent_Void))));
    Ark_ClickEvent event = static_cast<Ark_ClickEvent>(ClickEvent_serializer::read(thisDeserializer));
    callSyncMethod(vmContext, resourceId, event);
}
void deserializeAndCallCallback_ComputedBarAttribute_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_ComputedBarAttribute value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_ComputedBarAttribute_Void))));
    thisDeserializer.readPointer();
    Ark_ComputedBarAttribute value = ComputedBarAttribute_serializer::read(thisDeserializer);
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_ComputedBarAttribute_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_ComputedBarAttribute value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_ComputedBarAttribute_Void))));
    Ark_ComputedBarAttribute value = ComputedBarAttribute_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallCallback_CopyEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_CopyEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_CopyEvent_Void))));
    thisDeserializer.readPointer();
    Ark_CopyEvent value0 = CopyEvent_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_CopyEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_CopyEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_CopyEvent_Void))));
    Ark_CopyEvent value0 = CopyEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_CreateItem(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Int32 index, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_CreateItem))));
    thisDeserializer.readPointer();
    Ark_Int32 index = thisDeserializer.readInt32();
    Callback_Pointer_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Pointer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Pointer_Void))))};
    _call(_resourceId, index, continuationResult);
}
void deserializeAndCallSyncCallback_CreateItem(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int32 index, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_CreateItem))));
    Ark_Int32 index = thisDeserializer.readInt32();
    Callback_Pointer_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Pointer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Pointer_Void))))};
    callSyncMethod(vmContext, resourceId, index, continuationResult);
}
void deserializeAndCallCallback_CrownEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_CrownEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_CrownEvent_Void))));
    thisDeserializer.readPointer();
    Ark_CrownEvent value0 = CrownEvent_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_CrownEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_CrownEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_CrownEvent_Void))));
    Ark_CrownEvent value0 = CrownEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_CustomSpanMeasureInfo_CustomSpanMetrics(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_CustomSpanMeasureInfo measureInfo, const Callback_CustomSpanMetrics_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_CustomSpanMeasureInfo_CustomSpanMetrics))));
    thisDeserializer.readPointer();
    Ark_CustomSpanMeasureInfo measureInfo = CustomSpanMeasureInfo_serializer::read(thisDeserializer);
    Callback_CustomSpanMetrics_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_CustomSpanMetrics value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_CustomSpanMetrics_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_CustomSpanMetrics value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_CustomSpanMetrics_Void))))};
    _call(_resourceId, measureInfo, continuationResult);
}
void deserializeAndCallSyncCallback_CustomSpanMeasureInfo_CustomSpanMetrics(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_CustomSpanMeasureInfo measureInfo, const Callback_CustomSpanMetrics_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_CustomSpanMeasureInfo_CustomSpanMetrics))));
    Ark_CustomSpanMeasureInfo measureInfo = CustomSpanMeasureInfo_serializer::read(thisDeserializer);
    Callback_CustomSpanMetrics_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_CustomSpanMetrics value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_CustomSpanMetrics_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_CustomSpanMetrics value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_CustomSpanMetrics_Void))))};
    callSyncMethod(vmContext, resourceId, measureInfo, continuationResult);
}
void deserializeAndCallCallback_CustomSpanMetrics_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_CustomSpanMetrics value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_CustomSpanMetrics_Void))));
    thisDeserializer.readPointer();
    Ark_CustomSpanMetrics value = CustomSpanMetrics_serializer::read(thisDeserializer);
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_CustomSpanMetrics_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_CustomSpanMetrics value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_CustomSpanMetrics_Void))));
    Ark_CustomSpanMetrics value = CustomSpanMetrics_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallCallback_CutEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_CutEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_CutEvent_Void))));
    thisDeserializer.readPointer();
    Ark_CutEvent value0 = CutEvent_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_CutEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_CutEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_CutEvent_Void))));
    Ark_CutEvent value0 = CutEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_Date_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Date value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Date_Void))));
    thisDeserializer.readPointer();
    Ark_Date value0 = thisDeserializer.readInt64();
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_Date_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Date value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Date_Void))));
    Ark_Date value0 = thisDeserializer.readInt64();
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_DeleteValue_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_DeleteValue value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_DeleteValue_Boolean))));
    thisDeserializer.readPointer();
    Ark_DeleteValue value0 = DeleteValue_serializer::read(thisDeserializer);
    Callback_Boolean_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, value0, continuationResult);
}
void deserializeAndCallSyncCallback_DeleteValue_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_DeleteValue value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_DeleteValue_Boolean))));
    Ark_DeleteValue value0 = DeleteValue_serializer::read(thisDeserializer);
    Callback_Boolean_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    callSyncMethod(vmContext, resourceId, value0, continuationResult);
}
void deserializeAndCallCallback_DeleteValue_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_DeleteValue value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_DeleteValue_Void))));
    thisDeserializer.readPointer();
    Ark_DeleteValue value0 = DeleteValue_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_DeleteValue_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_DeleteValue value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_DeleteValue_Void))));
    Ark_DeleteValue value0 = DeleteValue_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_DismissContentCoverAction_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_DismissContentCoverAction value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_DismissContentCoverAction_Void))));
    thisDeserializer.readPointer();
    Ark_DismissContentCoverAction value0 = DismissContentCoverAction_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_DismissContentCoverAction_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_DismissContentCoverAction value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_DismissContentCoverAction_Void))));
    Ark_DismissContentCoverAction value0 = DismissContentCoverAction_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_DismissDialogAction_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_DismissDialogAction value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_DismissDialogAction_Void))));
    thisDeserializer.readPointer();
    Ark_DismissDialogAction value0 = static_cast<Ark_DismissDialogAction>(DismissDialogAction_serializer::read(thisDeserializer));
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_DismissDialogAction_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_DismissDialogAction value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_DismissDialogAction_Void))));
    Ark_DismissDialogAction value0 = static_cast<Ark_DismissDialogAction>(DismissDialogAction_serializer::read(thisDeserializer));
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_DismissPopupAction_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_DismissPopupAction value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_DismissPopupAction_Void))));
    thisDeserializer.readPointer();
    Ark_DismissPopupAction value0 = static_cast<Ark_DismissPopupAction>(DismissPopupAction_serializer::read(thisDeserializer));
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_DismissPopupAction_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_DismissPopupAction value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_DismissPopupAction_Void))));
    Ark_DismissPopupAction value0 = static_cast<Ark_DismissPopupAction>(DismissPopupAction_serializer::read(thisDeserializer));
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_DismissSheetAction_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_DismissSheetAction value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_DismissSheetAction_Void))));
    thisDeserializer.readPointer();
    Ark_DismissSheetAction value0 = DismissSheetAction_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_DismissSheetAction_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_DismissSheetAction value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_DismissSheetAction_Void))));
    Ark_DismissSheetAction value0 = DismissSheetAction_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_DragEvent_Opt_String_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_DragEvent event, const Opt_String extraParams)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_DragEvent_Opt_String_Void))));
    thisDeserializer.readPointer();
    Ark_DragEvent event = static_cast<Ark_DragEvent>(DragEvent_serializer::read(thisDeserializer));
    const auto extraParamsTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_String extraParamsTmpBuf = {};
    extraParamsTmpBuf.tag = extraParamsTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((extraParamsTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED)) {
        extraParamsTmpBuf.value = static_cast<Ark_String>(thisDeserializer.readString());
    }
    Opt_String extraParams = extraParamsTmpBuf;
    _call(_resourceId, event, extraParams);
}
void deserializeAndCallSyncCallback_DragEvent_Opt_String_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_DragEvent event, const Opt_String extraParams)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_DragEvent_Opt_String_Void))));
    Ark_DragEvent event = static_cast<Ark_DragEvent>(DragEvent_serializer::read(thisDeserializer));
    const auto extraParamsTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_String extraParamsTmpBuf = {};
    extraParamsTmpBuf.tag = extraParamsTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((extraParamsTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED)) {
        extraParamsTmpBuf.value = static_cast<Ark_String>(thisDeserializer.readString());
    }
    Opt_String extraParams = extraParamsTmpBuf;
    callSyncMethod(vmContext, resourceId, event, extraParams);
}
void deserializeAndCallCallback_DrawContext_CustomSpanDrawInfo_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_DrawContext context, const Ark_CustomSpanDrawInfo drawInfo)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_DrawContext_CustomSpanDrawInfo_Void))));
    thisDeserializer.readPointer();
    Ark_DrawContext context = static_cast<Ark_DrawContext>(DrawContext_serializer::read(thisDeserializer));
    Ark_CustomSpanDrawInfo drawInfo = CustomSpanDrawInfo_serializer::read(thisDeserializer);
    _call(_resourceId, context, drawInfo);
}
void deserializeAndCallSyncCallback_DrawContext_CustomSpanDrawInfo_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_DrawContext context, const Ark_CustomSpanDrawInfo drawInfo)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_DrawContext_CustomSpanDrawInfo_Void))));
    Ark_DrawContext context = static_cast<Ark_DrawContext>(DrawContext_serializer::read(thisDeserializer));
    Ark_CustomSpanDrawInfo drawInfo = CustomSpanDrawInfo_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, context, drawInfo);
}
void deserializeAndCallCallback_DrawContext_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_DrawContext drawContext)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_DrawContext_Void))));
    thisDeserializer.readPointer();
    Ark_DrawContext drawContext = static_cast<Ark_DrawContext>(DrawContext_serializer::read(thisDeserializer));
    _call(_resourceId, drawContext);
}
void deserializeAndCallSyncCallback_DrawContext_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_DrawContext drawContext)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_DrawContext_Void))));
    Ark_DrawContext drawContext = static_cast<Ark_DrawContext>(DrawContext_serializer::read(thisDeserializer));
    callSyncMethod(vmContext, resourceId, drawContext);
}
void deserializeAndCallCallback_EditableTextChangeValue_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_EditableTextChangeValue value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_EditableTextChangeValue_Boolean))));
    thisDeserializer.readPointer();
    Ark_EditableTextChangeValue value0 = EditableTextChangeValue_serializer::read(thisDeserializer);
    Callback_Boolean_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, value0, continuationResult);
}
void deserializeAndCallSyncCallback_EditableTextChangeValue_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_EditableTextChangeValue value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_EditableTextChangeValue_Boolean))));
    Ark_EditableTextChangeValue value0 = EditableTextChangeValue_serializer::read(thisDeserializer);
    Callback_Boolean_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    callSyncMethod(vmContext, resourceId, value0, continuationResult);
}
void deserializeAndCallCallback_ErrorInformation_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_ErrorInformation value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_ErrorInformation_Void))));
    thisDeserializer.readPointer();
    Ark_ErrorInformation value0 = ErrorInformation_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_ErrorInformation_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_ErrorInformation value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_ErrorInformation_Void))));
    Ark_ErrorInformation value0 = ErrorInformation_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_Extender_OnFinish(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Extender_OnFinish))));
    thisDeserializer.readPointer();
    _call(_resourceId);
}
void deserializeAndCallSyncCallback_Extender_OnFinish(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Extender_OnFinish))));
    callSyncMethod(vmContext, resourceId);
}
void deserializeAndCallCallback_Extender_OnProgress(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Float32 value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Extender_OnProgress))));
    thisDeserializer.readPointer();
    Ark_Float32 value = thisDeserializer.readFloat32();
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_Extender_OnProgress(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Float32 value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Extender_OnProgress))));
    Ark_Float32 value = thisDeserializer.readFloat32();
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallCallback_F64_F64_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Float64 totalOffsetX, const Ark_Float64 totalOffsetY)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_F64_F64_Void))));
    thisDeserializer.readPointer();
    Ark_Float64 totalOffsetX = thisDeserializer.readFloat64();
    Ark_Float64 totalOffsetY = thisDeserializer.readFloat64();
    _call(_resourceId, totalOffsetX, totalOffsetY);
}
void deserializeAndCallSyncCallback_F64_F64_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Float64 totalOffsetX, const Ark_Float64 totalOffsetY)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_F64_F64_Void))));
    Ark_Float64 totalOffsetX = thisDeserializer.readFloat64();
    Ark_Float64 totalOffsetY = thisDeserializer.readFloat64();
    callSyncMethod(vmContext, resourceId, totalOffsetX, totalOffsetY);
}
void deserializeAndCallCallback_F64_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Float64 offset)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_F64_Void))));
    thisDeserializer.readPointer();
    Ark_Float64 offset = thisDeserializer.readFloat64();
    _call(_resourceId, offset);
}
void deserializeAndCallSyncCallback_F64_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Float64 offset)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_F64_Void))));
    Ark_Float64 offset = thisDeserializer.readFloat64();
    callSyncMethod(vmContext, resourceId, offset);
}
void deserializeAndCallCallback_F64_SliderChangeMode_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Float64 value, Ark_SliderChangeMode mode)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_F64_SliderChangeMode_Void))));
    thisDeserializer.readPointer();
    Ark_Float64 value = thisDeserializer.readFloat64();
    Ark_SliderChangeMode mode = static_cast<Ark_SliderChangeMode>(thisDeserializer.readInt32());
    _call(_resourceId, value, mode);
}
void deserializeAndCallSyncCallback_F64_SliderChangeMode_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Float64 value, Ark_SliderChangeMode mode)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_F64_SliderChangeMode_Void))));
    Ark_Float64 value = thisDeserializer.readFloat64();
    Ark_SliderChangeMode mode = static_cast<Ark_SliderChangeMode>(thisDeserializer.readInt32());
    callSyncMethod(vmContext, resourceId, value, mode);
}
void deserializeAndCallCallback_FocusAxisEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_FocusAxisEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_FocusAxisEvent_Void))));
    thisDeserializer.readPointer();
    Ark_FocusAxisEvent value0 = static_cast<Ark_FocusAxisEvent>(FocusAxisEvent_serializer::read(thisDeserializer));
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_FocusAxisEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_FocusAxisEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_FocusAxisEvent_Void))));
    Ark_FocusAxisEvent value0 = static_cast<Ark_FocusAxisEvent>(FocusAxisEvent_serializer::read(thisDeserializer));
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_FormCallbackInfo_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_FormCallbackInfo value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_FormCallbackInfo_Void))));
    thisDeserializer.readPointer();
    Ark_FormCallbackInfo value0 = FormCallbackInfo_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_FormCallbackInfo_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_FormCallbackInfo value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_FormCallbackInfo_Void))));
    Ark_FormCallbackInfo value0 = FormCallbackInfo_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_FullscreenInfo_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_FullscreenInfo value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_FullscreenInfo_Void))));
    thisDeserializer.readPointer();
    Ark_FullscreenInfo value0 = FullscreenInfo_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_FullscreenInfo_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_FullscreenInfo value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_FullscreenInfo_Void))));
    Ark_FullscreenInfo value0 = FullscreenInfo_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_GestureEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_GestureEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_GestureEvent_Void))));
    thisDeserializer.readPointer();
    Ark_GestureEvent value0 = static_cast<Ark_GestureEvent>(GestureEvent_serializer::read(thisDeserializer));
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_GestureEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_GestureEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_GestureEvent_Void))));
    Ark_GestureEvent value0 = static_cast<Ark_GestureEvent>(GestureEvent_serializer::read(thisDeserializer));
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_GestureInfo_BaseGestureEvent_GestureJudgeResult(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_GestureInfo gestureInfo, const Ark_BaseGestureEvent event, const Callback_GestureJudgeResult_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult))));
    thisDeserializer.readPointer();
    Ark_GestureInfo gestureInfo = GestureInfo_serializer::read(thisDeserializer);
    Ark_BaseGestureEvent event = static_cast<Ark_BaseGestureEvent>(BaseGestureEvent_serializer::read(thisDeserializer));
    Callback_GestureJudgeResult_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_GestureJudgeResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_GestureJudgeResult_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_GestureJudgeResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_GestureJudgeResult_Void))))};
    _call(_resourceId, gestureInfo, event, continuationResult);
}
void deserializeAndCallSyncCallback_GestureInfo_BaseGestureEvent_GestureJudgeResult(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_GestureInfo gestureInfo, const Ark_BaseGestureEvent event, const Callback_GestureJudgeResult_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult))));
    Ark_GestureInfo gestureInfo = GestureInfo_serializer::read(thisDeserializer);
    Ark_BaseGestureEvent event = static_cast<Ark_BaseGestureEvent>(BaseGestureEvent_serializer::read(thisDeserializer));
    Callback_GestureJudgeResult_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_GestureJudgeResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_GestureJudgeResult_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_GestureJudgeResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_GestureJudgeResult_Void))))};
    callSyncMethod(vmContext, resourceId, gestureInfo, event, continuationResult);
}
void deserializeAndCallCallback_GestureJudgeResult_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_GestureJudgeResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_GestureJudgeResult_Void))));
    thisDeserializer.readPointer();
    Ark_GestureJudgeResult value = static_cast<Ark_GestureJudgeResult>(thisDeserializer.readInt32());
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_GestureJudgeResult_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_GestureJudgeResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_GestureJudgeResult_Void))));
    Ark_GestureJudgeResult value = static_cast<Ark_GestureJudgeResult>(thisDeserializer.readInt32());
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallCallback_GestureRecognizer_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_GestureRecognizer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_GestureRecognizer_Void))));
    thisDeserializer.readPointer();
    Ark_GestureRecognizer value = static_cast<Ark_GestureRecognizer>(GestureRecognizer_serializer::read(thisDeserializer));
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_GestureRecognizer_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_GestureRecognizer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_GestureRecognizer_Void))));
    Ark_GestureRecognizer value = static_cast<Ark_GestureRecognizer>(GestureRecognizer_serializer::read(thisDeserializer));
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallCallback_HitTestMode_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_HitTestMode value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_HitTestMode_Void))));
    thisDeserializer.readPointer();
    Ark_HitTestMode value = static_cast<Ark_HitTestMode>(thisDeserializer.readInt32());
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_HitTestMode_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_HitTestMode value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_HitTestMode_Void))));
    Ark_HitTestMode value = static_cast<Ark_HitTestMode>(thisDeserializer.readInt32());
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallCallback_HoverEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_HoverEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_HoverEvent_Void))));
    thisDeserializer.readPointer();
    Ark_HoverEvent value0 = static_cast<Ark_HoverEvent>(HoverEvent_serializer::read(thisDeserializer));
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_HoverEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_HoverEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_HoverEvent_Void))));
    Ark_HoverEvent value0 = static_cast<Ark_HoverEvent>(HoverEvent_serializer::read(thisDeserializer));
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_I32_F64_ComputedBarAttribute(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Int32 index, const Ark_Float64 offset, const Callback_ComputedBarAttribute_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_I32_F64_ComputedBarAttribute))));
    thisDeserializer.readPointer();
    Ark_Int32 index = thisDeserializer.readInt32();
    Ark_Float64 offset = thisDeserializer.readFloat64();
    Callback_ComputedBarAttribute_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_ComputedBarAttribute value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_ComputedBarAttribute_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_ComputedBarAttribute value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_ComputedBarAttribute_Void))))};
    _call(_resourceId, index, offset, continuationResult);
}
void deserializeAndCallSyncCallback_I32_F64_ComputedBarAttribute(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int32 index, const Ark_Float64 offset, const Callback_ComputedBarAttribute_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_I32_F64_ComputedBarAttribute))));
    Ark_Int32 index = thisDeserializer.readInt32();
    Ark_Float64 offset = thisDeserializer.readFloat64();
    Callback_ComputedBarAttribute_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_ComputedBarAttribute value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_ComputedBarAttribute_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_ComputedBarAttribute value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_ComputedBarAttribute_Void))))};
    callSyncMethod(vmContext, resourceId, index, offset, continuationResult);
}
void deserializeAndCallCallback_I32_I32_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Int32 from, const Ark_Int32 to, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_I32_I32_Boolean))));
    thisDeserializer.readPointer();
    Ark_Int32 from = thisDeserializer.readInt32();
    Ark_Int32 to = thisDeserializer.readInt32();
    Callback_Boolean_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, from, to, continuationResult);
}
void deserializeAndCallSyncCallback_I32_I32_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int32 from, const Ark_Int32 to, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_I32_I32_Boolean))));
    Ark_Int32 from = thisDeserializer.readInt32();
    Ark_Int32 to = thisDeserializer.readInt32();
    Callback_Boolean_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    callSyncMethod(vmContext, resourceId, from, to, continuationResult);
}
void deserializeAndCallCallback_I32_I32_I32_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Int32 start, const Ark_Int32 end, const Ark_Int32 center)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_I32_I32_I32_Void))));
    thisDeserializer.readPointer();
    Ark_Int32 start = thisDeserializer.readInt32();
    Ark_Int32 end = thisDeserializer.readInt32();
    Ark_Int32 center = thisDeserializer.readInt32();
    _call(_resourceId, start, end, center);
}
void deserializeAndCallSyncCallback_I32_I32_I32_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int32 start, const Ark_Int32 end, const Ark_Int32 center)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_I32_I32_I32_Void))));
    Ark_Int32 start = thisDeserializer.readInt32();
    Ark_Int32 end = thisDeserializer.readInt32();
    Ark_Int32 center = thisDeserializer.readInt32();
    callSyncMethod(vmContext, resourceId, start, end, center);
}
void deserializeAndCallCallback_I32_I32_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Int32 first, const Ark_Int32 last)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_I32_I32_Void))));
    thisDeserializer.readPointer();
    Ark_Int32 first = thisDeserializer.readInt32();
    Ark_Int32 last = thisDeserializer.readInt32();
    _call(_resourceId, first, last);
}
void deserializeAndCallSyncCallback_I32_I32_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int32 first, const Ark_Int32 last)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_I32_I32_Void))));
    Ark_Int32 first = thisDeserializer.readInt32();
    Ark_Int32 last = thisDeserializer.readInt32();
    callSyncMethod(vmContext, resourceId, first, last);
}
void deserializeAndCallCallback_I32_Tuple_I32_I32(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Int32 index, const Callback_Tuple_I32_I32_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_I32_Tuple_I32_I32))));
    thisDeserializer.readPointer();
    Ark_Int32 index = thisDeserializer.readInt32();
    Callback_Tuple_I32_I32_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Tuple_I32_I32 value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Tuple_I32_I32_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Tuple_I32_I32 value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Tuple_I32_I32_Void))))};
    _call(_resourceId, index, continuationResult);
}
void deserializeAndCallSyncCallback_I32_Tuple_I32_I32(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int32 index, const Callback_Tuple_I32_I32_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_I32_Tuple_I32_I32))));
    Ark_Int32 index = thisDeserializer.readInt32();
    Callback_Tuple_I32_I32_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Tuple_I32_I32 value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Tuple_I32_I32_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Tuple_I32_I32 value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Tuple_I32_I32_Void))))};
    callSyncMethod(vmContext, resourceId, index, continuationResult);
}
void deserializeAndCallCallback_I32_Tuple_I32_I32_I32_I32(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Int32 index, const Callback_Tuple_I32_I32_I32_I32_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_I32_Tuple_I32_I32_I32_I32))));
    thisDeserializer.readPointer();
    Ark_Int32 index = thisDeserializer.readInt32();
    Callback_Tuple_I32_I32_I32_I32_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Tuple_I32_I32_I32_I32 value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Tuple_I32_I32_I32_I32_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Tuple_I32_I32_I32_I32 value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Tuple_I32_I32_I32_I32_Void))))};
    _call(_resourceId, index, continuationResult);
}
void deserializeAndCallSyncCallback_I32_Tuple_I32_I32_I32_I32(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int32 index, const Callback_Tuple_I32_I32_I32_I32_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_I32_Tuple_I32_I32_I32_I32))));
    Ark_Int32 index = thisDeserializer.readInt32();
    Callback_Tuple_I32_I32_I32_I32_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Tuple_I32_I32_I32_I32 value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Tuple_I32_I32_I32_I32_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Tuple_I32_I32_I32_I32 value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Tuple_I32_I32_I32_I32_Void))))};
    callSyncMethod(vmContext, resourceId, index, continuationResult);
}
void deserializeAndCallCallback_I64_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Int64 value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_I64_Void))));
    thisDeserializer.readPointer();
    Ark_Int64 value = thisDeserializer.readInt64();
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_I64_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int64 value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_I64_Void))));
    Ark_Int64 value = thisDeserializer.readInt64();
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallCallback_I32_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Int32 value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_I32_Void))));
    thisDeserializer.readPointer();
    Ark_Int32 value0 = thisDeserializer.readInt32();
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_I32_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int32 value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_I32_Void))));
    Ark_Int32 value0 = thisDeserializer.readInt32();
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_InsertValue_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_InsertValue value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_InsertValue_Boolean))));
    thisDeserializer.readPointer();
    Ark_InsertValue value0 = InsertValue_serializer::read(thisDeserializer);
    Callback_Boolean_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, value0, continuationResult);
}
void deserializeAndCallSyncCallback_InsertValue_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_InsertValue value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_InsertValue_Boolean))));
    Ark_InsertValue value0 = InsertValue_serializer::read(thisDeserializer);
    Callback_Boolean_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    callSyncMethod(vmContext, resourceId, value0, continuationResult);
}
void deserializeAndCallCallback_InsertValue_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_InsertValue value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_InsertValue_Void))));
    thisDeserializer.readPointer();
    Ark_InsertValue value0 = InsertValue_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_InsertValue_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_InsertValue value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_InsertValue_Void))));
    Ark_InsertValue value0 = InsertValue_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_ItemDragInfo_I32_I32_Boolean_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_ItemDragInfo event, const Ark_Int32 itemIndex, const Ark_Int32 insertIndex, const Ark_Boolean isSuccess)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_ItemDragInfo_I32_I32_Boolean_Void))));
    thisDeserializer.readPointer();
    Ark_ItemDragInfo event = ItemDragInfo_serializer::read(thisDeserializer);
    Ark_Int32 itemIndex = thisDeserializer.readInt32();
    Ark_Int32 insertIndex = thisDeserializer.readInt32();
    Ark_Boolean isSuccess = thisDeserializer.readBoolean();
    _call(_resourceId, event, itemIndex, insertIndex, isSuccess);
}
void deserializeAndCallSyncCallback_ItemDragInfo_I32_I32_Boolean_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_ItemDragInfo event, const Ark_Int32 itemIndex, const Ark_Int32 insertIndex, const Ark_Boolean isSuccess)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_ItemDragInfo_I32_I32_Boolean_Void))));
    Ark_ItemDragInfo event = ItemDragInfo_serializer::read(thisDeserializer);
    Ark_Int32 itemIndex = thisDeserializer.readInt32();
    Ark_Int32 insertIndex = thisDeserializer.readInt32();
    Ark_Boolean isSuccess = thisDeserializer.readBoolean();
    callSyncMethod(vmContext, resourceId, event, itemIndex, insertIndex, isSuccess);
}
void deserializeAndCallCallback_ItemDragInfo_I32_I32_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_ItemDragInfo event, const Ark_Int32 itemIndex, const Ark_Int32 insertIndex)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_ItemDragInfo_I32_I32_Void))));
    thisDeserializer.readPointer();
    Ark_ItemDragInfo event = ItemDragInfo_serializer::read(thisDeserializer);
    Ark_Int32 itemIndex = thisDeserializer.readInt32();
    Ark_Int32 insertIndex = thisDeserializer.readInt32();
    _call(_resourceId, event, itemIndex, insertIndex);
}
void deserializeAndCallSyncCallback_ItemDragInfo_I32_I32_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_ItemDragInfo event, const Ark_Int32 itemIndex, const Ark_Int32 insertIndex)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_ItemDragInfo_I32_I32_Void))));
    Ark_ItemDragInfo event = ItemDragInfo_serializer::read(thisDeserializer);
    Ark_Int32 itemIndex = thisDeserializer.readInt32();
    Ark_Int32 insertIndex = thisDeserializer.readInt32();
    callSyncMethod(vmContext, resourceId, event, itemIndex, insertIndex);
}
void deserializeAndCallCallback_ItemDragInfo_I32_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_ItemDragInfo event, const Ark_Int32 itemIndex)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_ItemDragInfo_I32_Void))));
    thisDeserializer.readPointer();
    Ark_ItemDragInfo event = ItemDragInfo_serializer::read(thisDeserializer);
    Ark_Int32 itemIndex = thisDeserializer.readInt32();
    _call(_resourceId, event, itemIndex);
}
void deserializeAndCallSyncCallback_ItemDragInfo_I32_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_ItemDragInfo event, const Ark_Int32 itemIndex)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_ItemDragInfo_I32_Void))));
    Ark_ItemDragInfo event = ItemDragInfo_serializer::read(thisDeserializer);
    Ark_Int32 itemIndex = thisDeserializer.readInt32();
    callSyncMethod(vmContext, resourceId, event, itemIndex);
}
void deserializeAndCallCallback_ItemDragInfo_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_ItemDragInfo event)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_ItemDragInfo_Void))));
    thisDeserializer.readPointer();
    Ark_ItemDragInfo event = ItemDragInfo_serializer::read(thisDeserializer);
    _call(_resourceId, event);
}
void deserializeAndCallSyncCallback_ItemDragInfo_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_ItemDragInfo event)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_ItemDragInfo_Void))));
    Ark_ItemDragInfo event = ItemDragInfo_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, event);
}
void deserializeAndCallCallback_KeyEvent_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_KeyEvent value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_KeyEvent_Boolean))));
    thisDeserializer.readPointer();
    Ark_KeyEvent value0 = static_cast<Ark_KeyEvent>(KeyEvent_serializer::read(thisDeserializer));
    Callback_Boolean_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, value0, continuationResult);
}
void deserializeAndCallSyncCallback_KeyEvent_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_KeyEvent value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_KeyEvent_Boolean))));
    Ark_KeyEvent value0 = static_cast<Ark_KeyEvent>(KeyEvent_serializer::read(thisDeserializer));
    Callback_Boolean_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    callSyncMethod(vmContext, resourceId, value0, continuationResult);
}
void deserializeAndCallCallback_KeyEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_KeyEvent event)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_KeyEvent_Void))));
    thisDeserializer.readPointer();
    Ark_KeyEvent event = static_cast<Ark_KeyEvent>(KeyEvent_serializer::read(thisDeserializer));
    _call(_resourceId, event);
}
void deserializeAndCallSyncCallback_KeyEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_KeyEvent event)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_KeyEvent_Void))));
    Ark_KeyEvent event = static_cast<Ark_KeyEvent>(KeyEvent_serializer::read(thisDeserializer));
    callSyncMethod(vmContext, resourceId, event);
}
void deserializeAndCallCallback_Long_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Int64 value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Long_Void))));
    thisDeserializer.readPointer();
    Ark_Int64 value = thisDeserializer.readInt64();
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_Long_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int64 value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Long_Void))));
    Ark_Int64 value = thisDeserializer.readInt64();
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallCallback_Map_String_RecordData_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Map_String_Opt_Object value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Map_String_RecordData_Void))));
    thisDeserializer.readPointer();
    const Ark_Int32 value0TmpBufSizeVar = thisDeserializer.readInt32();
    Map_String_Opt_Object value0TmpBuf = {};
    thisDeserializer.resizeMap<Map_String_Opt_Object, Ark_String, Opt_Object>(&value0TmpBuf, value0TmpBufSizeVar);
    for (int value0TmpBufIVar = 0; value0TmpBufIVar < value0TmpBufSizeVar; value0TmpBufIVar++) {
        const Ark_String value0TmpBufKeyVar = static_cast<Ark_String>(thisDeserializer.readString());
        const auto value0TmpBufValueVarTempBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
        Opt_Object value0TmpBufValueVarTempBuf = {};
        value0TmpBufValueVarTempBuf.tag = value0TmpBufValueVarTempBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
        if ((value0TmpBufValueVarTempBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED)) {
            value0TmpBufValueVarTempBuf.value = static_cast<Ark_Object>(thisDeserializer.readObject());
        }
        const Opt_Object value0TmpBufValueVar = value0TmpBufValueVarTempBuf;
        value0TmpBuf.keys[value0TmpBufIVar] = value0TmpBufKeyVar;
        value0TmpBuf.values[value0TmpBufIVar] = value0TmpBufValueVar;
    }
    Map_String_Opt_Object value0 = value0TmpBuf;
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_Map_String_RecordData_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Map_String_Opt_Object value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Map_String_RecordData_Void))));
    const Ark_Int32 value0TmpBufSizeVar = thisDeserializer.readInt32();
    Map_String_Opt_Object value0TmpBuf = {};
    thisDeserializer.resizeMap<Map_String_Opt_Object, Ark_String, Opt_Object>(&value0TmpBuf, value0TmpBufSizeVar);
    for (int value0TmpBufIVar = 0; value0TmpBufIVar < value0TmpBufSizeVar; value0TmpBufIVar++) {
        const Ark_String value0TmpBufKeyVar = static_cast<Ark_String>(thisDeserializer.readString());
        const auto value0TmpBufValueVarTempBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
        Opt_Object value0TmpBufValueVarTempBuf = {};
        value0TmpBufValueVarTempBuf.tag = value0TmpBufValueVarTempBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
        if ((value0TmpBufValueVarTempBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED)) {
            value0TmpBufValueVarTempBuf.value = static_cast<Ark_Object>(thisDeserializer.readObject());
        }
        const Opt_Object value0TmpBufValueVar = value0TmpBufValueVarTempBuf;
        value0TmpBuf.keys[value0TmpBufIVar] = value0TmpBufKeyVar;
        value0TmpBuf.values[value0TmpBufIVar] = value0TmpBufValueVar;
    }
    Map_String_Opt_Object value0 = value0TmpBuf;
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_MarqueeState_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_MarqueeState value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_MarqueeState_Void))));
    thisDeserializer.readPointer();
    Ark_MarqueeState value0 = static_cast<Ark_MarqueeState>(thisDeserializer.readInt32());
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_MarqueeState_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_MarqueeState value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_MarqueeState_Void))));
    Ark_MarqueeState value0 = static_cast<Ark_MarqueeState>(thisDeserializer.readInt32());
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_MouseEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_MouseEvent event)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_MouseEvent_Void))));
    thisDeserializer.readPointer();
    Ark_MouseEvent event = static_cast<Ark_MouseEvent>(MouseEvent_serializer::read(thisDeserializer));
    _call(_resourceId, event);
}
void deserializeAndCallSyncCallback_MouseEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_MouseEvent event)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_MouseEvent_Void))));
    Ark_MouseEvent event = static_cast<Ark_MouseEvent>(MouseEvent_serializer::read(thisDeserializer));
    callSyncMethod(vmContext, resourceId, event);
}
void deserializeAndCallCallback_NativeEmbedDataInfo_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativeEmbedDataInfo event)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_NativeEmbedDataInfo_Void))));
    thisDeserializer.readPointer();
    Ark_NativeEmbedDataInfo event = NativeEmbedDataInfo_serializer::read(thisDeserializer);
    _call(_resourceId, event);
}
void deserializeAndCallSyncCallback_NativeEmbedDataInfo_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativeEmbedDataInfo event)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_NativeEmbedDataInfo_Void))));
    Ark_NativeEmbedDataInfo event = NativeEmbedDataInfo_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, event);
}
void deserializeAndCallCallback_NativeEmbedTouchInfo_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativeEmbedTouchInfo event)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_NativeEmbedTouchInfo_Void))));
    thisDeserializer.readPointer();
    Ark_NativeEmbedTouchInfo event = NativeEmbedTouchInfo_serializer::read(thisDeserializer);
    _call(_resourceId, event);
}
void deserializeAndCallSyncCallback_NativeEmbedTouchInfo_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativeEmbedTouchInfo event)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_NativeEmbedTouchInfo_Void))));
    Ark_NativeEmbedTouchInfo event = NativeEmbedTouchInfo_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, event);
}
void deserializeAndCallCallback_NativeXComponentPointer_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Int64 value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_NativeXComponentPointer_Void))));
    thisDeserializer.readPointer();
    Ark_Int64 value0 = thisDeserializer.readInt64();
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_NativeXComponentPointer_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int64 value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_NativeXComponentPointer_Void))));
    Ark_Int64 value0 = thisDeserializer.readInt64();
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_NavDestinationActiveReason_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_NavDestinationActiveReason value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_NavDestinationActiveReason_Void))));
    thisDeserializer.readPointer();
    Ark_NavDestinationActiveReason value0 = static_cast<Ark_NavDestinationActiveReason>(thisDeserializer.readInt32());
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_NavDestinationActiveReason_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_NavDestinationActiveReason value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_NavDestinationActiveReason_Void))));
    Ark_NavDestinationActiveReason value0 = static_cast<Ark_NavDestinationActiveReason>(thisDeserializer.readInt32());
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_NavDestinationContext_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NavDestinationContext value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_NavDestinationContext_Void))));
    thisDeserializer.readPointer();
    Ark_NavDestinationContext value0 = static_cast<Ark_NavDestinationContext>(NavDestinationContext_serializer::read(thisDeserializer));
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_NavDestinationContext_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NavDestinationContext value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_NavDestinationContext_Void))));
    Ark_NavDestinationContext value0 = static_cast<Ark_NavDestinationContext>(NavDestinationContext_serializer::read(thisDeserializer));
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_NavigationMode_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_NavigationMode mode)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_NavigationMode_Void))));
    thisDeserializer.readPointer();
    Ark_NavigationMode mode = static_cast<Ark_NavigationMode>(thisDeserializer.readInt32());
    _call(_resourceId, mode);
}
void deserializeAndCallSyncCallback_NavigationMode_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_NavigationMode mode)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_NavigationMode_Void))));
    Ark_NavigationMode mode = static_cast<Ark_NavigationMode>(thisDeserializer.readInt32());
    callSyncMethod(vmContext, resourceId, mode);
}
void deserializeAndCallCallback_NavigationTitleMode_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_NavigationTitleMode titleMode)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_NavigationTitleMode_Void))));
    thisDeserializer.readPointer();
    Ark_NavigationTitleMode titleMode = static_cast<Ark_NavigationTitleMode>(thisDeserializer.readInt32());
    _call(_resourceId, titleMode);
}
void deserializeAndCallSyncCallback_NavigationTitleMode_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_NavigationTitleMode titleMode)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_NavigationTitleMode_Void))));
    Ark_NavigationTitleMode titleMode = static_cast<Ark_NavigationTitleMode>(thisDeserializer.readInt32());
    callSyncMethod(vmContext, resourceId, titleMode);
}
void deserializeAndCallCallback_NavigationTransitionProxy_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NavigationTransitionProxy transitionProxy)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_NavigationTransitionProxy_Void))));
    thisDeserializer.readPointer();
    Ark_NavigationTransitionProxy transitionProxy = static_cast<Ark_NavigationTransitionProxy>(NavigationTransitionProxy_serializer::read(thisDeserializer));
    _call(_resourceId, transitionProxy);
}
void deserializeAndCallSyncCallback_NavigationTransitionProxy_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NavigationTransitionProxy transitionProxy)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_NavigationTransitionProxy_Void))));
    Ark_NavigationTransitionProxy transitionProxy = static_cast<Ark_NavigationTransitionProxy>(NavigationTransitionProxy_serializer::read(thisDeserializer));
    callSyncMethod(vmContext, resourceId, transitionProxy);
}
void deserializeAndCallCallback_Number_Number_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number prevIndex, const Ark_Number index)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Number_Number_Void))));
    thisDeserializer.readPointer();
    Ark_Number prevIndex = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _call(_resourceId, prevIndex, index);
}
void deserializeAndCallSyncCallback_Number_Number_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number prevIndex, const Ark_Number index)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Number_Number_Void))));
    Ark_Number prevIndex = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    callSyncMethod(vmContext, resourceId, prevIndex, index);
}
void deserializeAndCallCallback_Number_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Number_Void))));
    thisDeserializer.readPointer();
    Ark_Number value = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_Number_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Number_Void))));
    Ark_Number value = static_cast<Ark_Number>(thisDeserializer.readNumber());
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallCallback_Object_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Object value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Object_Void))));
    thisDeserializer.readPointer();
    Ark_Object value0 = static_cast<Ark_Object>(thisDeserializer.readObject());
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_Object_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Object value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Object_Void))));
    Ark_Object value0 = static_cast<Ark_Object>(thisDeserializer.readObject());
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_OnAlertEvent_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnAlertEvent value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_OnAlertEvent_Boolean))));
    thisDeserializer.readPointer();
    Ark_OnAlertEvent value0 = OnAlertEvent_serializer::read(thisDeserializer);
    Callback_Boolean_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, value0, continuationResult);
}
void deserializeAndCallSyncCallback_OnAlertEvent_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnAlertEvent value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_OnAlertEvent_Boolean))));
    Ark_OnAlertEvent value0 = OnAlertEvent_serializer::read(thisDeserializer);
    Callback_Boolean_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    callSyncMethod(vmContext, resourceId, value0, continuationResult);
}
void deserializeAndCallCallback_OnAudioStateChangedEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnAudioStateChangedEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_OnAudioStateChangedEvent_Void))));
    thisDeserializer.readPointer();
    Ark_OnAudioStateChangedEvent value0 = OnAudioStateChangedEvent_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_OnAudioStateChangedEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnAudioStateChangedEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_OnAudioStateChangedEvent_Void))));
    Ark_OnAudioStateChangedEvent value0 = OnAudioStateChangedEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_OnBeforeUnloadEvent_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnBeforeUnloadEvent value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_OnBeforeUnloadEvent_Boolean))));
    thisDeserializer.readPointer();
    Ark_OnBeforeUnloadEvent value0 = OnBeforeUnloadEvent_serializer::read(thisDeserializer);
    Callback_Boolean_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, value0, continuationResult);
}
void deserializeAndCallSyncCallback_OnBeforeUnloadEvent_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnBeforeUnloadEvent value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_OnBeforeUnloadEvent_Boolean))));
    Ark_OnBeforeUnloadEvent value0 = OnBeforeUnloadEvent_serializer::read(thisDeserializer);
    Callback_Boolean_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    callSyncMethod(vmContext, resourceId, value0, continuationResult);
}
void deserializeAndCallCallback_OnClientAuthenticationEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnClientAuthenticationEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_OnClientAuthenticationEvent_Void))));
    thisDeserializer.readPointer();
    Ark_OnClientAuthenticationEvent value0 = OnClientAuthenticationEvent_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_OnClientAuthenticationEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnClientAuthenticationEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_OnClientAuthenticationEvent_Void))));
    Ark_OnClientAuthenticationEvent value0 = OnClientAuthenticationEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_OnConfirmEvent_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnConfirmEvent value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_OnConfirmEvent_Boolean))));
    thisDeserializer.readPointer();
    Ark_OnConfirmEvent value0 = OnConfirmEvent_serializer::read(thisDeserializer);
    Callback_Boolean_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, value0, continuationResult);
}
void deserializeAndCallSyncCallback_OnConfirmEvent_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnConfirmEvent value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_OnConfirmEvent_Boolean))));
    Ark_OnConfirmEvent value0 = OnConfirmEvent_serializer::read(thisDeserializer);
    Callback_Boolean_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    callSyncMethod(vmContext, resourceId, value0, continuationResult);
}
void deserializeAndCallCallback_OnConsoleEvent_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnConsoleEvent value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_OnConsoleEvent_Boolean))));
    thisDeserializer.readPointer();
    Ark_OnConsoleEvent value0 = OnConsoleEvent_serializer::read(thisDeserializer);
    Callback_Boolean_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, value0, continuationResult);
}
void deserializeAndCallSyncCallback_OnConsoleEvent_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnConsoleEvent value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_OnConsoleEvent_Boolean))));
    Ark_OnConsoleEvent value0 = OnConsoleEvent_serializer::read(thisDeserializer);
    Callback_Boolean_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    callSyncMethod(vmContext, resourceId, value0, continuationResult);
}
void deserializeAndCallCallback_OnContextMenuShowEvent_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnContextMenuShowEvent value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_OnContextMenuShowEvent_Boolean))));
    thisDeserializer.readPointer();
    Ark_OnContextMenuShowEvent value0 = OnContextMenuShowEvent_serializer::read(thisDeserializer);
    Callback_Boolean_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, value0, continuationResult);
}
void deserializeAndCallSyncCallback_OnContextMenuShowEvent_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnContextMenuShowEvent value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_OnContextMenuShowEvent_Boolean))));
    Ark_OnContextMenuShowEvent value0 = OnContextMenuShowEvent_serializer::read(thisDeserializer);
    Callback_Boolean_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    callSyncMethod(vmContext, resourceId, value0, continuationResult);
}
void deserializeAndCallCallback_OnDataResubmittedEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnDataResubmittedEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_OnDataResubmittedEvent_Void))));
    thisDeserializer.readPointer();
    Ark_OnDataResubmittedEvent value0 = OnDataResubmittedEvent_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_OnDataResubmittedEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnDataResubmittedEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_OnDataResubmittedEvent_Void))));
    Ark_OnDataResubmittedEvent value0 = OnDataResubmittedEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_OnDestory_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Int64 nodeId)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_OnDestory_Void))));
    thisDeserializer.readPointer();
    Ark_Int64 nodeId = thisDeserializer.readInt64();
    _call(_resourceId, nodeId);
}
void deserializeAndCallSyncCallback_OnDestory_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int64 nodeId)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_OnDestory_Void))));
    Ark_Int64 nodeId = thisDeserializer.readInt64();
    callSyncMethod(vmContext, resourceId, nodeId);
}
void deserializeAndCallCallback_OnDownloadStartEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnDownloadStartEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_OnDownloadStartEvent_Void))));
    thisDeserializer.readPointer();
    Ark_OnDownloadStartEvent value0 = OnDownloadStartEvent_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_OnDownloadStartEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnDownloadStartEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_OnDownloadStartEvent_Void))));
    Ark_OnDownloadStartEvent value0 = OnDownloadStartEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_OnErrorReceiveEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnErrorReceiveEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_OnErrorReceiveEvent_Void))));
    thisDeserializer.readPointer();
    Ark_OnErrorReceiveEvent value0 = OnErrorReceiveEvent_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_OnErrorReceiveEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnErrorReceiveEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_OnErrorReceiveEvent_Void))));
    Ark_OnErrorReceiveEvent value0 = OnErrorReceiveEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_OnFaviconReceivedEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnFaviconReceivedEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_OnFaviconReceivedEvent_Void))));
    thisDeserializer.readPointer();
    Ark_OnFaviconReceivedEvent value0 = OnFaviconReceivedEvent_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_OnFaviconReceivedEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnFaviconReceivedEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_OnFaviconReceivedEvent_Void))));
    Ark_OnFaviconReceivedEvent value0 = OnFaviconReceivedEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_OnFirstContentfulPaintEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnFirstContentfulPaintEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_OnFirstContentfulPaintEvent_Void))));
    thisDeserializer.readPointer();
    Ark_OnFirstContentfulPaintEvent value0 = OnFirstContentfulPaintEvent_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_OnFirstContentfulPaintEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnFirstContentfulPaintEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_OnFirstContentfulPaintEvent_Void))));
    Ark_OnFirstContentfulPaintEvent value0 = OnFirstContentfulPaintEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_OnGeolocationShowEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnGeolocationShowEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_OnGeolocationShowEvent_Void))));
    thisDeserializer.readPointer();
    Ark_OnGeolocationShowEvent value0 = OnGeolocationShowEvent_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_OnGeolocationShowEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnGeolocationShowEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_OnGeolocationShowEvent_Void))));
    Ark_OnGeolocationShowEvent value0 = OnGeolocationShowEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_OnHttpAuthRequestEvent_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnHttpAuthRequestEvent value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_OnHttpAuthRequestEvent_Boolean))));
    thisDeserializer.readPointer();
    Ark_OnHttpAuthRequestEvent value0 = OnHttpAuthRequestEvent_serializer::read(thisDeserializer);
    Callback_Boolean_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, value0, continuationResult);
}
void deserializeAndCallSyncCallback_OnHttpAuthRequestEvent_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnHttpAuthRequestEvent value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_OnHttpAuthRequestEvent_Boolean))));
    Ark_OnHttpAuthRequestEvent value0 = OnHttpAuthRequestEvent_serializer::read(thisDeserializer);
    Callback_Boolean_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    callSyncMethod(vmContext, resourceId, value0, continuationResult);
}
void deserializeAndCallCallback_OnHttpErrorReceiveEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnHttpErrorReceiveEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_OnHttpErrorReceiveEvent_Void))));
    thisDeserializer.readPointer();
    Ark_OnHttpErrorReceiveEvent value0 = OnHttpErrorReceiveEvent_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_OnHttpErrorReceiveEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnHttpErrorReceiveEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_OnHttpErrorReceiveEvent_Void))));
    Ark_OnHttpErrorReceiveEvent value0 = OnHttpErrorReceiveEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_OnLoadFinishedEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnLoadFinishedEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_OnLoadFinishedEvent_Void))));
    thisDeserializer.readPointer();
    Ark_OnLoadFinishedEvent value0 = OnLoadFinishedEvent_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_OnLoadFinishedEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnLoadFinishedEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_OnLoadFinishedEvent_Void))));
    Ark_OnLoadFinishedEvent value0 = OnLoadFinishedEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_OnLoadInterceptEvent_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnLoadInterceptEvent value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_OnLoadInterceptEvent_Boolean))));
    thisDeserializer.readPointer();
    Ark_OnLoadInterceptEvent value0 = OnLoadInterceptEvent_serializer::read(thisDeserializer);
    Callback_Boolean_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, value0, continuationResult);
}
void deserializeAndCallSyncCallback_OnLoadInterceptEvent_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnLoadInterceptEvent value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_OnLoadInterceptEvent_Boolean))));
    Ark_OnLoadInterceptEvent value0 = OnLoadInterceptEvent_serializer::read(thisDeserializer);
    Callback_Boolean_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    callSyncMethod(vmContext, resourceId, value0, continuationResult);
}
void deserializeAndCallCallback_OnLoadStartedEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnLoadStartedEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_OnLoadStartedEvent_Void))));
    thisDeserializer.readPointer();
    Ark_OnLoadStartedEvent value0 = OnLoadStartedEvent_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_OnLoadStartedEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnLoadStartedEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_OnLoadStartedEvent_Void))));
    Ark_OnLoadStartedEvent value0 = OnLoadStartedEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_onMeasureSize_SizeResult(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_GeometryInfo selfLayoutInfo, const Array_Measurable children, const Ark_ConstraintSizeOptions constraint, const Callback_SizeResult_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_onMeasureSize_SizeResult))));
    thisDeserializer.readPointer();
    Ark_GeometryInfo selfLayoutInfo = GeometryInfo_serializer::read(thisDeserializer);
    const Ark_Int32 childrenTmpBufLength = thisDeserializer.readInt32();
    Array_Measurable childrenTmpBuf = {};
    thisDeserializer.resizeArray<std::decay<decltype(childrenTmpBuf)>::type,
        std::decay<decltype(*childrenTmpBuf.array)>::type>(&childrenTmpBuf, childrenTmpBufLength);
    for (int childrenTmpBufBufCounterI = 0; childrenTmpBufBufCounterI < childrenTmpBufLength; childrenTmpBufBufCounterI++) {
        childrenTmpBuf.array[childrenTmpBufBufCounterI] = static_cast<Ark_Measurable>(Measurable_serializer::read(thisDeserializer));
    }
    Array_Measurable children = childrenTmpBuf;
    Ark_ConstraintSizeOptions constraint = ConstraintSizeOptions_serializer::read(thisDeserializer);
    Callback_SizeResult_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_SizeResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_SizeResult_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_SizeResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_SizeResult_Void))))};
    _call(_resourceId, selfLayoutInfo, children, constraint, continuationResult);
}
void deserializeAndCallSyncCallback_onMeasureSize_SizeResult(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_GeometryInfo selfLayoutInfo, const Array_Measurable children, const Ark_ConstraintSizeOptions constraint, const Callback_SizeResult_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_onMeasureSize_SizeResult))));
    Ark_GeometryInfo selfLayoutInfo = GeometryInfo_serializer::read(thisDeserializer);
    const Ark_Int32 childrenTmpBufLength = thisDeserializer.readInt32();
    Array_Measurable childrenTmpBuf = {};
    thisDeserializer.resizeArray<std::decay<decltype(childrenTmpBuf)>::type,
        std::decay<decltype(*childrenTmpBuf.array)>::type>(&childrenTmpBuf, childrenTmpBufLength);
    for (int childrenTmpBufBufCounterI = 0; childrenTmpBufBufCounterI < childrenTmpBufLength; childrenTmpBufBufCounterI++) {
        childrenTmpBuf.array[childrenTmpBufBufCounterI] = static_cast<Ark_Measurable>(Measurable_serializer::read(thisDeserializer));
    }
    Array_Measurable children = childrenTmpBuf;
    Ark_ConstraintSizeOptions constraint = ConstraintSizeOptions_serializer::read(thisDeserializer);
    Callback_SizeResult_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_SizeResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_SizeResult_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_SizeResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_SizeResult_Void))))};
    callSyncMethod(vmContext, resourceId, selfLayoutInfo, children, constraint, continuationResult);
}
void deserializeAndCallCallback_OnMoveFromTo(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Int32 from, const Ark_Int32 to)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_OnMoveFromTo))));
    thisDeserializer.readPointer();
    Ark_Int32 from = thisDeserializer.readInt32();
    Ark_Int32 to = thisDeserializer.readInt32();
    _call(_resourceId, from, to);
}
void deserializeAndCallSyncCallback_OnMoveFromTo(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int32 from, const Ark_Int32 to)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_OnMoveFromTo))));
    Ark_Int32 from = thisDeserializer.readInt32();
    Ark_Int32 to = thisDeserializer.readInt32();
    callSyncMethod(vmContext, resourceId, from, to);
}
void deserializeAndCallCallback_OnOverScrollEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnOverScrollEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_OnOverScrollEvent_Void))));
    thisDeserializer.readPointer();
    Ark_OnOverScrollEvent value0 = OnOverScrollEvent_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_OnOverScrollEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnOverScrollEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_OnOverScrollEvent_Void))));
    Ark_OnOverScrollEvent value0 = OnOverScrollEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_OnPageBeginEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnPageBeginEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_OnPageBeginEvent_Void))));
    thisDeserializer.readPointer();
    Ark_OnPageBeginEvent value0 = OnPageBeginEvent_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_OnPageBeginEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnPageBeginEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_OnPageBeginEvent_Void))));
    Ark_OnPageBeginEvent value0 = OnPageBeginEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_OnPageEndEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnPageEndEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_OnPageEndEvent_Void))));
    thisDeserializer.readPointer();
    Ark_OnPageEndEvent value0 = OnPageEndEvent_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_OnPageEndEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnPageEndEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_OnPageEndEvent_Void))));
    Ark_OnPageEndEvent value0 = OnPageEndEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_OnPageVisibleEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnPageVisibleEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_OnPageVisibleEvent_Void))));
    thisDeserializer.readPointer();
    Ark_OnPageVisibleEvent value0 = OnPageVisibleEvent_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_OnPageVisibleEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnPageVisibleEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_OnPageVisibleEvent_Void))));
    Ark_OnPageVisibleEvent value0 = OnPageVisibleEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_OnPermissionRequestEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnPermissionRequestEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_OnPermissionRequestEvent_Void))));
    thisDeserializer.readPointer();
    Ark_OnPermissionRequestEvent value0 = OnPermissionRequestEvent_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_OnPermissionRequestEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnPermissionRequestEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_OnPermissionRequestEvent_Void))));
    Ark_OnPermissionRequestEvent value0 = OnPermissionRequestEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_onPlaceChildren_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_GeometryInfo selfLayoutInfo, const Array_Layoutable children, const Ark_ConstraintSizeOptions constraint)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_onPlaceChildren_Void))));
    thisDeserializer.readPointer();
    Ark_GeometryInfo selfLayoutInfo = GeometryInfo_serializer::read(thisDeserializer);
    const Ark_Int32 childrenTmpBufLength = thisDeserializer.readInt32();
    Array_Layoutable childrenTmpBuf = {};
    thisDeserializer.resizeArray<std::decay<decltype(childrenTmpBuf)>::type,
        std::decay<decltype(*childrenTmpBuf.array)>::type>(&childrenTmpBuf, childrenTmpBufLength);
    for (int childrenTmpBufBufCounterI = 0; childrenTmpBufBufCounterI < childrenTmpBufLength; childrenTmpBufBufCounterI++) {
        childrenTmpBuf.array[childrenTmpBufBufCounterI] = static_cast<Ark_Layoutable>(Layoutable_serializer::read(thisDeserializer));
    }
    Array_Layoutable children = childrenTmpBuf;
    Ark_ConstraintSizeOptions constraint = ConstraintSizeOptions_serializer::read(thisDeserializer);
    _call(_resourceId, selfLayoutInfo, children, constraint);
}
void deserializeAndCallSyncCallback_onPlaceChildren_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_GeometryInfo selfLayoutInfo, const Array_Layoutable children, const Ark_ConstraintSizeOptions constraint)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_onPlaceChildren_Void))));
    Ark_GeometryInfo selfLayoutInfo = GeometryInfo_serializer::read(thisDeserializer);
    const Ark_Int32 childrenTmpBufLength = thisDeserializer.readInt32();
    Array_Layoutable childrenTmpBuf = {};
    thisDeserializer.resizeArray<std::decay<decltype(childrenTmpBuf)>::type,
        std::decay<decltype(*childrenTmpBuf.array)>::type>(&childrenTmpBuf, childrenTmpBufLength);
    for (int childrenTmpBufBufCounterI = 0; childrenTmpBufBufCounterI < childrenTmpBufLength; childrenTmpBufBufCounterI++) {
        childrenTmpBuf.array[childrenTmpBufBufCounterI] = static_cast<Ark_Layoutable>(Layoutable_serializer::read(thisDeserializer));
    }
    Array_Layoutable children = childrenTmpBuf;
    Ark_ConstraintSizeOptions constraint = ConstraintSizeOptions_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, selfLayoutInfo, children, constraint);
}
void deserializeAndCallCallback_OnProgressChangeEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnProgressChangeEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_OnProgressChangeEvent_Void))));
    thisDeserializer.readPointer();
    Ark_OnProgressChangeEvent value0 = OnProgressChangeEvent_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_OnProgressChangeEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnProgressChangeEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_OnProgressChangeEvent_Void))));
    Ark_OnProgressChangeEvent value0 = OnProgressChangeEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_OnPromptEvent_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnPromptEvent value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_OnPromptEvent_Boolean))));
    thisDeserializer.readPointer();
    Ark_OnPromptEvent value0 = OnPromptEvent_serializer::read(thisDeserializer);
    Callback_Boolean_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, value0, continuationResult);
}
void deserializeAndCallSyncCallback_OnPromptEvent_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnPromptEvent value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_OnPromptEvent_Boolean))));
    Ark_OnPromptEvent value0 = OnPromptEvent_serializer::read(thisDeserializer);
    Callback_Boolean_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    callSyncMethod(vmContext, resourceId, value0, continuationResult);
}
void deserializeAndCallCallback_OnRefreshAccessedHistoryEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnRefreshAccessedHistoryEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_OnRefreshAccessedHistoryEvent_Void))));
    thisDeserializer.readPointer();
    Ark_OnRefreshAccessedHistoryEvent value0 = OnRefreshAccessedHistoryEvent_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_OnRefreshAccessedHistoryEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnRefreshAccessedHistoryEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_OnRefreshAccessedHistoryEvent_Void))));
    Ark_OnRefreshAccessedHistoryEvent value0 = OnRefreshAccessedHistoryEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_OnRenderExitedEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnRenderExitedEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_OnRenderExitedEvent_Void))));
    thisDeserializer.readPointer();
    Ark_OnRenderExitedEvent value0 = OnRenderExitedEvent_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_OnRenderExitedEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnRenderExitedEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_OnRenderExitedEvent_Void))));
    Ark_OnRenderExitedEvent value0 = OnRenderExitedEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_OnResourceLoadEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnResourceLoadEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_OnResourceLoadEvent_Void))));
    thisDeserializer.readPointer();
    Ark_OnResourceLoadEvent value0 = OnResourceLoadEvent_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_OnResourceLoadEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnResourceLoadEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_OnResourceLoadEvent_Void))));
    Ark_OnResourceLoadEvent value0 = OnResourceLoadEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_OnScaleChangeEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnScaleChangeEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_OnScaleChangeEvent_Void))));
    thisDeserializer.readPointer();
    Ark_OnScaleChangeEvent value0 = OnScaleChangeEvent_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_OnScaleChangeEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnScaleChangeEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_OnScaleChangeEvent_Void))));
    Ark_OnScaleChangeEvent value0 = OnScaleChangeEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_OnScreenCaptureRequestEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnScreenCaptureRequestEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_OnScreenCaptureRequestEvent_Void))));
    thisDeserializer.readPointer();
    Ark_OnScreenCaptureRequestEvent value0 = OnScreenCaptureRequestEvent_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_OnScreenCaptureRequestEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnScreenCaptureRequestEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_OnScreenCaptureRequestEvent_Void))));
    Ark_OnScreenCaptureRequestEvent value0 = OnScreenCaptureRequestEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_OnScrollEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnScrollEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_OnScrollEvent_Void))));
    thisDeserializer.readPointer();
    Ark_OnScrollEvent value0 = OnScrollEvent_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_OnScrollEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnScrollEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_OnScrollEvent_Void))));
    Ark_OnScrollEvent value0 = OnScrollEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_OnScrollFrameBeginHandlerResult_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnScrollFrameBeginHandlerResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_OnScrollFrameBeginHandlerResult_Void))));
    thisDeserializer.readPointer();
    Ark_OnScrollFrameBeginHandlerResult value = OnScrollFrameBeginHandlerResult_serializer::read(thisDeserializer);
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_OnScrollFrameBeginHandlerResult_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnScrollFrameBeginHandlerResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_OnScrollFrameBeginHandlerResult_Void))));
    Ark_OnScrollFrameBeginHandlerResult value = OnScrollFrameBeginHandlerResult_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallCallback_OnSearchResultReceiveEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnSearchResultReceiveEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_OnSearchResultReceiveEvent_Void))));
    thisDeserializer.readPointer();
    Ark_OnSearchResultReceiveEvent value0 = OnSearchResultReceiveEvent_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_OnSearchResultReceiveEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnSearchResultReceiveEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_OnSearchResultReceiveEvent_Void))));
    Ark_OnSearchResultReceiveEvent value0 = OnSearchResultReceiveEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_OnShowFileSelectorEvent_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnShowFileSelectorEvent value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_OnShowFileSelectorEvent_Boolean))));
    thisDeserializer.readPointer();
    Ark_OnShowFileSelectorEvent value0 = OnShowFileSelectorEvent_serializer::read(thisDeserializer);
    Callback_Boolean_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, value0, continuationResult);
}
void deserializeAndCallSyncCallback_OnShowFileSelectorEvent_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnShowFileSelectorEvent value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_OnShowFileSelectorEvent_Boolean))));
    Ark_OnShowFileSelectorEvent value0 = OnShowFileSelectorEvent_serializer::read(thisDeserializer);
    Callback_Boolean_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    callSyncMethod(vmContext, resourceId, value0, continuationResult);
}
void deserializeAndCallCallback_OnSslErrorEventReceiveEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnSslErrorEventReceiveEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_OnSslErrorEventReceiveEvent_Void))));
    thisDeserializer.readPointer();
    Ark_OnSslErrorEventReceiveEvent value0 = OnSslErrorEventReceiveEvent_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_OnSslErrorEventReceiveEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnSslErrorEventReceiveEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_OnSslErrorEventReceiveEvent_Void))));
    Ark_OnSslErrorEventReceiveEvent value0 = OnSslErrorEventReceiveEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_OnTitleReceiveEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnTitleReceiveEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_OnTitleReceiveEvent_Void))));
    thisDeserializer.readPointer();
    Ark_OnTitleReceiveEvent value0 = OnTitleReceiveEvent_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_OnTitleReceiveEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnTitleReceiveEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_OnTitleReceiveEvent_Void))));
    Ark_OnTitleReceiveEvent value0 = OnTitleReceiveEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_OnTouchIconUrlReceivedEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnTouchIconUrlReceivedEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_OnTouchIconUrlReceivedEvent_Void))));
    thisDeserializer.readPointer();
    Ark_OnTouchIconUrlReceivedEvent value0 = OnTouchIconUrlReceivedEvent_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_OnTouchIconUrlReceivedEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnTouchIconUrlReceivedEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_OnTouchIconUrlReceivedEvent_Void))));
    Ark_OnTouchIconUrlReceivedEvent value0 = OnTouchIconUrlReceivedEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_OnWindowNewEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnWindowNewEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_OnWindowNewEvent_Void))));
    thisDeserializer.readPointer();
    Ark_OnWindowNewEvent value0 = OnWindowNewEvent_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_OnWindowNewEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnWindowNewEvent value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_OnWindowNewEvent_Void))));
    Ark_OnWindowNewEvent value0 = OnWindowNewEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_Opt_Array_NavDestinationTransition_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_Array_NavDestinationTransition value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Opt_Array_NavDestinationTransition_Void))));
    thisDeserializer.readPointer();
    const auto valueTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Array_NavDestinationTransition valueTmpBuf = {};
    valueTmpBuf.tag = valueTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((valueTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED)) {
        const Ark_Int32 valueTmpBuf_Length = thisDeserializer.readInt32();
        Array_NavDestinationTransition valueTmpBuf_ = {};
        thisDeserializer.resizeArray<std::decay<decltype(valueTmpBuf_)>::type,
        std::decay<decltype(*valueTmpBuf_.array)>::type>(&valueTmpBuf_, valueTmpBuf_Length);
        for (int valueTmpBuf_BufCounterI = 0; valueTmpBuf_BufCounterI < valueTmpBuf_Length; valueTmpBuf_BufCounterI++) {
            valueTmpBuf_.array[valueTmpBuf_BufCounterI] = NavDestinationTransition_serializer::read(thisDeserializer);
        }
        valueTmpBuf.value = valueTmpBuf_;
    }
    Opt_Array_NavDestinationTransition value = valueTmpBuf;
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_Opt_Array_NavDestinationTransition_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_Array_NavDestinationTransition value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Opt_Array_NavDestinationTransition_Void))));
    const auto valueTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Array_NavDestinationTransition valueTmpBuf = {};
    valueTmpBuf.tag = valueTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((valueTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED)) {
        const Ark_Int32 valueTmpBuf_Length = thisDeserializer.readInt32();
        Array_NavDestinationTransition valueTmpBuf_ = {};
        thisDeserializer.resizeArray<std::decay<decltype(valueTmpBuf_)>::type,
        std::decay<decltype(*valueTmpBuf_.array)>::type>(&valueTmpBuf_, valueTmpBuf_Length);
        for (int valueTmpBuf_BufCounterI = 0; valueTmpBuf_BufCounterI < valueTmpBuf_Length; valueTmpBuf_BufCounterI++) {
            valueTmpBuf_.array[valueTmpBuf_BufCounterI] = NavDestinationTransition_serializer::read(thisDeserializer);
        }
        valueTmpBuf.value = valueTmpBuf_;
    }
    Opt_Array_NavDestinationTransition value = valueTmpBuf;
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallCallback_Opt_Array_String_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_Array_String error)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Opt_Array_String_Void))));
    thisDeserializer.readPointer();
    const auto errorTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Array_String errorTmpBuf = {};
    errorTmpBuf.tag = errorTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((errorTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED)) {
        const Ark_Int32 errorTmpBuf_Length = thisDeserializer.readInt32();
        Array_String errorTmpBuf_ = {};
        thisDeserializer.resizeArray<std::decay<decltype(errorTmpBuf_)>::type,
        std::decay<decltype(*errorTmpBuf_.array)>::type>(&errorTmpBuf_, errorTmpBuf_Length);
        for (int errorTmpBuf_BufCounterI = 0; errorTmpBuf_BufCounterI < errorTmpBuf_Length; errorTmpBuf_BufCounterI++) {
            errorTmpBuf_.array[errorTmpBuf_BufCounterI] = static_cast<Ark_String>(thisDeserializer.readString());
        }
        errorTmpBuf.value = errorTmpBuf_;
    }
    Opt_Array_String error = errorTmpBuf;
    _call(_resourceId, error);
}
void deserializeAndCallSyncCallback_Opt_Array_String_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_Array_String error)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Opt_Array_String_Void))));
    const auto errorTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Array_String errorTmpBuf = {};
    errorTmpBuf.tag = errorTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((errorTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED)) {
        const Ark_Int32 errorTmpBuf_Length = thisDeserializer.readInt32();
        Array_String errorTmpBuf_ = {};
        thisDeserializer.resizeArray<std::decay<decltype(errorTmpBuf_)>::type,
        std::decay<decltype(*errorTmpBuf_.array)>::type>(&errorTmpBuf_, errorTmpBuf_Length);
        for (int errorTmpBuf_BufCounterI = 0; errorTmpBuf_BufCounterI < errorTmpBuf_Length; errorTmpBuf_BufCounterI++) {
            errorTmpBuf_.array[errorTmpBuf_BufCounterI] = static_cast<Ark_String>(thisDeserializer.readString());
        }
        errorTmpBuf.value = errorTmpBuf_;
    }
    Opt_Array_String error = errorTmpBuf;
    callSyncMethod(vmContext, resourceId, error);
}
void deserializeAndCallCallback_Opt_CustomBuilder_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_CustomNodeBuilder value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Opt_CustomBuilder_Void))));
    thisDeserializer.readPointer();
    const auto valueTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_CustomNodeBuilder valueTmpBuf = {};
    valueTmpBuf.tag = valueTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((valueTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED)) {
        valueTmpBuf.value = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_CustomNodeBuilder)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_CustomNodeBuilder))))};
    }
    Opt_CustomNodeBuilder value = valueTmpBuf;
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_Opt_CustomBuilder_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_CustomNodeBuilder value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Opt_CustomBuilder_Void))));
    const auto valueTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_CustomNodeBuilder valueTmpBuf = {};
    valueTmpBuf.tag = valueTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((valueTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED)) {
        valueTmpBuf.value = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_CustomNodeBuilder)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_CustomNodeBuilder))))};
    }
    Opt_CustomNodeBuilder value = valueTmpBuf;
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallCallback_Opt_NavigationAnimatedTransition_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_NavigationAnimatedTransition value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Opt_NavigationAnimatedTransition_Void))));
    thisDeserializer.readPointer();
    const auto valueTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_NavigationAnimatedTransition valueTmpBuf = {};
    valueTmpBuf.tag = valueTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((valueTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED)) {
        valueTmpBuf.value = NavigationAnimatedTransition_serializer::read(thisDeserializer);
    }
    Opt_NavigationAnimatedTransition value = valueTmpBuf;
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_Opt_NavigationAnimatedTransition_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_NavigationAnimatedTransition value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Opt_NavigationAnimatedTransition_Void))));
    const auto valueTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_NavigationAnimatedTransition valueTmpBuf = {};
    valueTmpBuf.tag = valueTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((valueTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED)) {
        valueTmpBuf.value = NavigationAnimatedTransition_serializer::read(thisDeserializer);
    }
    Opt_NavigationAnimatedTransition value = valueTmpBuf;
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallCallback_Opt_OffsetResult_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_OffsetResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Opt_OffsetResult_Void))));
    thisDeserializer.readPointer();
    const auto valueTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_OffsetResult valueTmpBuf = {};
    valueTmpBuf.tag = valueTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((valueTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED)) {
        valueTmpBuf.value = OffsetResult_serializer::read(thisDeserializer);
    }
    Opt_OffsetResult value = valueTmpBuf;
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_Opt_OffsetResult_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_OffsetResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Opt_OffsetResult_Void))));
    const auto valueTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_OffsetResult valueTmpBuf = {};
    valueTmpBuf.tag = valueTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((valueTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED)) {
        valueTmpBuf.value = OffsetResult_serializer::read(thisDeserializer);
    }
    Opt_OffsetResult value = valueTmpBuf;
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallCallback_Opt_ScrollResult_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_ScrollResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Opt_ScrollResult_Void))));
    thisDeserializer.readPointer();
    const auto valueTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_ScrollResult valueTmpBuf = {};
    valueTmpBuf.tag = valueTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((valueTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED)) {
        valueTmpBuf.value = static_cast<Ark_ScrollResult>(ScrollResult_serializer::read(thisDeserializer));
    }
    Opt_ScrollResult value = valueTmpBuf;
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_Opt_ScrollResult_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_ScrollResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Opt_ScrollResult_Void))));
    const auto valueTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_ScrollResult valueTmpBuf = {};
    valueTmpBuf.tag = valueTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((valueTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED)) {
        valueTmpBuf.value = static_cast<Ark_ScrollResult>(ScrollResult_serializer::read(thisDeserializer));
    }
    Opt_ScrollResult value = valueTmpBuf;
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallCallback_Opt_StyledString_Opt_Array_String_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_StyledString value, const Opt_Array_String error)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Opt_StyledString_Opt_Array_String_Void))));
    thisDeserializer.readPointer();
    const auto valueTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_StyledString valueTmpBuf = {};
    valueTmpBuf.tag = valueTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((valueTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED)) {
        valueTmpBuf.value = static_cast<Ark_StyledString>(StyledString_serializer::read(thisDeserializer));
    }
    Opt_StyledString value = valueTmpBuf;
    const auto errorTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Array_String errorTmpBuf = {};
    errorTmpBuf.tag = errorTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((errorTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED)) {
        const Ark_Int32 errorTmpBuf_Length = thisDeserializer.readInt32();
        Array_String errorTmpBuf_ = {};
        thisDeserializer.resizeArray<std::decay<decltype(errorTmpBuf_)>::type,
        std::decay<decltype(*errorTmpBuf_.array)>::type>(&errorTmpBuf_, errorTmpBuf_Length);
        for (int errorTmpBuf_BufCounterI = 0; errorTmpBuf_BufCounterI < errorTmpBuf_Length; errorTmpBuf_BufCounterI++) {
            errorTmpBuf_.array[errorTmpBuf_BufCounterI] = static_cast<Ark_String>(thisDeserializer.readString());
        }
        errorTmpBuf.value = errorTmpBuf_;
    }
    Opt_Array_String error = errorTmpBuf;
    _call(_resourceId, value, error);
}
void deserializeAndCallSyncCallback_Opt_StyledString_Opt_Array_String_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_StyledString value, const Opt_Array_String error)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Opt_StyledString_Opt_Array_String_Void))));
    const auto valueTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_StyledString valueTmpBuf = {};
    valueTmpBuf.tag = valueTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((valueTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED)) {
        valueTmpBuf.value = static_cast<Ark_StyledString>(StyledString_serializer::read(thisDeserializer));
    }
    Opt_StyledString value = valueTmpBuf;
    const auto errorTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Array_String errorTmpBuf = {};
    errorTmpBuf.tag = errorTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((errorTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED)) {
        const Ark_Int32 errorTmpBuf_Length = thisDeserializer.readInt32();
        Array_String errorTmpBuf_ = {};
        thisDeserializer.resizeArray<std::decay<decltype(errorTmpBuf_)>::type,
        std::decay<decltype(*errorTmpBuf_.array)>::type>(&errorTmpBuf_, errorTmpBuf_Length);
        for (int errorTmpBuf_BufCounterI = 0; errorTmpBuf_BufCounterI < errorTmpBuf_Length; errorTmpBuf_BufCounterI++) {
            errorTmpBuf_.array[errorTmpBuf_BufCounterI] = static_cast<Ark_String>(thisDeserializer.readString());
        }
        errorTmpBuf.value = errorTmpBuf_;
    }
    Opt_Array_String error = errorTmpBuf;
    callSyncMethod(vmContext, resourceId, value, error);
}
void deserializeAndCallCallback_Opt_TabContentAnimatedTransition_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_TabContentAnimatedTransition value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Opt_TabContentAnimatedTransition_Void))));
    thisDeserializer.readPointer();
    const auto valueTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_TabContentAnimatedTransition valueTmpBuf = {};
    valueTmpBuf.tag = valueTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((valueTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED)) {
        valueTmpBuf.value = TabContentAnimatedTransition_serializer::read(thisDeserializer);
    }
    Opt_TabContentAnimatedTransition value = valueTmpBuf;
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_Opt_TabContentAnimatedTransition_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_TabContentAnimatedTransition value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Opt_TabContentAnimatedTransition_Void))));
    const auto valueTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_TabContentAnimatedTransition valueTmpBuf = {};
    valueTmpBuf.tag = valueTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((valueTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED)) {
        valueTmpBuf.value = TabContentAnimatedTransition_serializer::read(thisDeserializer);
    }
    Opt_TabContentAnimatedTransition value = valueTmpBuf;
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallCallback_Opt_WebResourceResponse_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_WebResourceResponse value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Opt_WebResourceResponse_Void))));
    thisDeserializer.readPointer();
    const auto valueTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_WebResourceResponse valueTmpBuf = {};
    valueTmpBuf.tag = valueTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((valueTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED)) {
        valueTmpBuf.value = static_cast<Ark_WebResourceResponse>(WebResourceResponse_serializer::read(thisDeserializer));
    }
    Opt_WebResourceResponse value = valueTmpBuf;
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_Opt_WebResourceResponse_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_WebResourceResponse value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Opt_WebResourceResponse_Void))));
    const auto valueTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_WebResourceResponse valueTmpBuf = {};
    valueTmpBuf.tag = valueTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((valueTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED)) {
        valueTmpBuf.value = static_cast<Ark_WebResourceResponse>(WebResourceResponse_serializer::read(thisDeserializer));
    }
    Opt_WebResourceResponse value = valueTmpBuf;
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallCallback_PlaybackInfo_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_PlaybackInfo value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_PlaybackInfo_Void))));
    thisDeserializer.readPointer();
    Ark_PlaybackInfo value0 = PlaybackInfo_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_PlaybackInfo_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_PlaybackInfo value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_PlaybackInfo_Void))));
    Ark_PlaybackInfo value0 = PlaybackInfo_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_Pointer_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Pointer_Void))));
    thisDeserializer.readPointer();
    Ark_NativePointer value = thisDeserializer.readPointer();
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_Pointer_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Pointer_Void))));
    Ark_NativePointer value = thisDeserializer.readPointer();
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallCallback_PopInfo_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_PopInfo value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_PopInfo_Void))));
    thisDeserializer.readPointer();
    Ark_PopInfo value0 = PopInfo_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_PopInfo_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_PopInfo value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_PopInfo_Void))));
    Ark_PopInfo value0 = PopInfo_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_PreDragStatus_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_PreDragStatus value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_PreDragStatus_Void))));
    thisDeserializer.readPointer();
    Ark_PreDragStatus value0 = static_cast<Ark_PreDragStatus>(thisDeserializer.readInt32());
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_PreDragStatus_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_PreDragStatus value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_PreDragStatus_Void))));
    Ark_PreDragStatus value0 = static_cast<Ark_PreDragStatus>(thisDeserializer.readInt32());
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_PreparedInfo_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_PreparedInfo value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_PreparedInfo_Void))));
    thisDeserializer.readPointer();
    Ark_PreparedInfo value0 = PreparedInfo_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_PreparedInfo_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_PreparedInfo value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_PreparedInfo_Void))));
    Ark_PreparedInfo value0 = PreparedInfo_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_RangeUpdate(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Int32 start, const Ark_Int32 end, const Ark_Int32 cacheStart, const Ark_Int32 cacheEnd, const Ark_Boolean isLoop)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_RangeUpdate))));
    thisDeserializer.readPointer();
    Ark_Int32 start = thisDeserializer.readInt32();
    Ark_Int32 end = thisDeserializer.readInt32();
    Ark_Int32 cacheStart = thisDeserializer.readInt32();
    Ark_Int32 cacheEnd = thisDeserializer.readInt32();
    Ark_Boolean isLoop = thisDeserializer.readBoolean();
    _call(_resourceId, start, end, cacheStart, cacheEnd, isLoop);
}
void deserializeAndCallSyncCallback_RangeUpdate(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int32 start, const Ark_Int32 end, const Ark_Int32 cacheStart, const Ark_Int32 cacheEnd, const Ark_Boolean isLoop)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_RangeUpdate))));
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
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_RefreshStatus state)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_RefreshStatus_Void))));
    thisDeserializer.readPointer();
    Ark_RefreshStatus state = static_cast<Ark_RefreshStatus>(thisDeserializer.readInt32());
    _call(_resourceId, state);
}
void deserializeAndCallSyncCallback_RefreshStatus_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_RefreshStatus state)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_RefreshStatus_Void))));
    Ark_RefreshStatus state = static_cast<Ark_RefreshStatus>(thisDeserializer.readInt32());
    callSyncMethod(vmContext, resourceId, state);
}
void deserializeAndCallCallback_RichEditorChangeValue_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_RichEditorChangeValue value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_RichEditorChangeValue_Boolean))));
    thisDeserializer.readPointer();
    Ark_RichEditorChangeValue value0 = RichEditorChangeValue_serializer::read(thisDeserializer);
    Callback_Boolean_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, value0, continuationResult);
}
void deserializeAndCallSyncCallback_RichEditorChangeValue_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_RichEditorChangeValue value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_RichEditorChangeValue_Boolean))));
    Ark_RichEditorChangeValue value0 = RichEditorChangeValue_serializer::read(thisDeserializer);
    Callback_Boolean_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    callSyncMethod(vmContext, resourceId, value0, continuationResult);
}
void deserializeAndCallCallback_RichEditorDeleteValue_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_RichEditorDeleteValue value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_RichEditorDeleteValue_Boolean))));
    thisDeserializer.readPointer();
    Ark_RichEditorDeleteValue value0 = RichEditorDeleteValue_serializer::read(thisDeserializer);
    Callback_Boolean_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, value0, continuationResult);
}
void deserializeAndCallSyncCallback_RichEditorDeleteValue_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_RichEditorDeleteValue value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_RichEditorDeleteValue_Boolean))));
    Ark_RichEditorDeleteValue value0 = RichEditorDeleteValue_serializer::read(thisDeserializer);
    Callback_Boolean_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    callSyncMethod(vmContext, resourceId, value0, continuationResult);
}
void deserializeAndCallCallback_RichEditorInsertValue_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_RichEditorInsertValue value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_RichEditorInsertValue_Boolean))));
    thisDeserializer.readPointer();
    Ark_RichEditorInsertValue value0 = RichEditorInsertValue_serializer::read(thisDeserializer);
    Callback_Boolean_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, value0, continuationResult);
}
void deserializeAndCallSyncCallback_RichEditorInsertValue_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_RichEditorInsertValue value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_RichEditorInsertValue_Boolean))));
    Ark_RichEditorInsertValue value0 = RichEditorInsertValue_serializer::read(thisDeserializer);
    Callback_Boolean_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    callSyncMethod(vmContext, resourceId, value0, continuationResult);
}
void deserializeAndCallCallback_RichEditorRange_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_RichEditorRange value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_RichEditorRange_Void))));
    thisDeserializer.readPointer();
    Ark_RichEditorRange value0 = RichEditorRange_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_RichEditorRange_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_RichEditorRange value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_RichEditorRange_Void))));
    Ark_RichEditorRange value0 = RichEditorRange_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_RichEditorSelection_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_RichEditorSelection value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_RichEditorSelection_Void))));
    thisDeserializer.readPointer();
    Ark_RichEditorSelection value0 = RichEditorSelection_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_RichEditorSelection_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_RichEditorSelection value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_RichEditorSelection_Void))));
    Ark_RichEditorSelection value0 = RichEditorSelection_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_RichEditorTextSpanResult_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_RichEditorTextSpanResult value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_RichEditorTextSpanResult_Void))));
    thisDeserializer.readPointer();
    Ark_RichEditorTextSpanResult value0 = RichEditorTextSpanResult_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_RichEditorTextSpanResult_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_RichEditorTextSpanResult value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_RichEditorTextSpanResult_Void))));
    Ark_RichEditorTextSpanResult value0 = RichEditorTextSpanResult_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_SheetDismiss_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_SheetDismiss sheetDismiss)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_SheetDismiss_Void))));
    thisDeserializer.readPointer();
    Ark_SheetDismiss sheetDismiss = SheetDismiss_serializer::read(thisDeserializer);
    _call(_resourceId, sheetDismiss);
}
void deserializeAndCallSyncCallback_SheetDismiss_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_SheetDismiss sheetDismiss)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_SheetDismiss_Void))));
    Ark_SheetDismiss sheetDismiss = SheetDismiss_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, sheetDismiss);
}
void deserializeAndCallCallback_SheetType_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_SheetType value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_SheetType_Void))));
    thisDeserializer.readPointer();
    Ark_SheetType value0 = static_cast<Ark_SheetType>(thisDeserializer.readInt32());
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_SheetType_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_SheetType value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_SheetType_Void))));
    Ark_SheetType value0 = static_cast<Ark_SheetType>(thisDeserializer.readInt32());
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_Size_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Size size)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Size_Void))));
    thisDeserializer.readPointer();
    Ark_Size size = Size_serializer::read(thisDeserializer);
    _call(_resourceId, size);
}
void deserializeAndCallSyncCallback_Size_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Size size)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Size_Void))));
    Ark_Size size = Size_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, size);
}
void deserializeAndCallCallback_SizeResult_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_SizeResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_SizeResult_Void))));
    thisDeserializer.readPointer();
    Ark_SizeResult value = SizeResult_serializer::read(thisDeserializer);
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_SizeResult_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_SizeResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_SizeResult_Void))));
    Ark_SizeResult value = SizeResult_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallCallback_SpringBackAction_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_SpringBackAction value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_SpringBackAction_Void))));
    thisDeserializer.readPointer();
    Ark_SpringBackAction value0 = static_cast<Ark_SpringBackAction>(
        SpringBackAction_serializer::read(thisDeserializer));
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_SpringBackAction_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_SpringBackAction value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_SpringBackAction_Void))));
    Ark_SpringBackAction value0 = static_cast<Ark_SpringBackAction>(
        SpringBackAction_serializer::read(thisDeserializer));
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_StateStylesChange(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Int32 currentState)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_StateStylesChange))));
    thisDeserializer.readPointer();
    Ark_Int32 currentState = thisDeserializer.readInt32();
    _call(_resourceId, currentState);
}
void deserializeAndCallSyncCallback_StateStylesChange(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int32 currentState)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_StateStylesChange))));
    Ark_Int32 currentState = thisDeserializer.readInt32();
    callSyncMethod(vmContext, resourceId, currentState);
}
void deserializeAndCallCallback_String_PasteEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_String value, const Ark_PasteEvent event)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_String_PasteEvent_Void))));
    thisDeserializer.readPointer();
    Ark_String value = static_cast<Ark_String>(thisDeserializer.readString());
    Ark_PasteEvent event = PasteEvent_serializer::read(thisDeserializer);
    _call(_resourceId, value, event);
}
void deserializeAndCallSyncCallback_String_PasteEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_String value, const Ark_PasteEvent event)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_String_PasteEvent_Void))));
    Ark_String value = static_cast<Ark_String>(thisDeserializer.readString());
    Ark_PasteEvent event = PasteEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value, event);
}
void deserializeAndCallCallback_String_SurfaceRect_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_String surfaceId, const Ark_SurfaceRect rect)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_String_SurfaceRect_Void))));
    thisDeserializer.readPointer();
    Ark_String surfaceId = static_cast<Ark_String>(thisDeserializer.readString());
    Ark_SurfaceRect rect = SurfaceRect_serializer::read(thisDeserializer);
    _call(_resourceId, surfaceId, rect);
}
void deserializeAndCallSyncCallback_String_SurfaceRect_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_String surfaceId, const Ark_SurfaceRect rect)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_String_SurfaceRect_Void))));
    Ark_String surfaceId = static_cast<Ark_String>(thisDeserializer.readString());
    Ark_SurfaceRect rect = SurfaceRect_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, surfaceId, rect);
}
void deserializeAndCallCallback_String_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_String breakpoints)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_String_Void))));
    thisDeserializer.readPointer();
    Ark_String breakpoints = static_cast<Ark_String>(thisDeserializer.readString());
    _call(_resourceId, breakpoints);
}
void deserializeAndCallSyncCallback_String_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_String breakpoints)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_String_Void))));
    Ark_String breakpoints = static_cast<Ark_String>(thisDeserializer.readString());
    callSyncMethod(vmContext, resourceId, breakpoints);
}
void deserializeAndCallCallback_StyledStringChangeValue_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_StyledStringChangeValue value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_StyledStringChangeValue_Boolean))));
    thisDeserializer.readPointer();
    Ark_StyledStringChangeValue value0 = StyledStringChangeValue_serializer::read(thisDeserializer);
    Callback_Boolean_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, value0, continuationResult);
}
void deserializeAndCallSyncCallback_StyledStringChangeValue_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_StyledStringChangeValue value0, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_StyledStringChangeValue_Boolean))));
    Ark_StyledStringChangeValue value0 = StyledStringChangeValue_serializer::read(thisDeserializer);
    Callback_Boolean_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    callSyncMethod(vmContext, resourceId, value0, continuationResult);
}
void deserializeAndCallCallback_StyledStringMarshallingValue_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_UserDataSpan value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_StyledStringMarshallingValue_Void))));
    thisDeserializer.readPointer();
    Ark_UserDataSpan value = static_cast<Ark_UserDataSpan>(thisDeserializer.readObject());
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_StyledStringMarshallingValue_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_UserDataSpan value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_StyledStringMarshallingValue_Void))));
    Ark_UserDataSpan value = static_cast<Ark_UserDataSpan>(thisDeserializer.readObject());
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallCallback_SwipeActionState_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_SwipeActionState state)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_SwipeActionState_Void))));
    thisDeserializer.readPointer();
    Ark_SwipeActionState state = static_cast<Ark_SwipeActionState>(thisDeserializer.readInt32());
    _call(_resourceId, state);
}
void deserializeAndCallSyncCallback_SwipeActionState_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_SwipeActionState state)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_SwipeActionState_Void))));
    Ark_SwipeActionState state = static_cast<Ark_SwipeActionState>(thisDeserializer.readInt32());
    callSyncMethod(vmContext, resourceId, state);
}
void deserializeAndCallCallback_SwiperContentTransitionProxy_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_SwiperContentTransitionProxy value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_SwiperContentTransitionProxy_Void))));
    thisDeserializer.readPointer();
    Ark_SwiperContentTransitionProxy value0 = static_cast<Ark_SwiperContentTransitionProxy>(SwiperContentTransitionProxy_serializer::read(thisDeserializer));
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_SwiperContentTransitionProxy_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_SwiperContentTransitionProxy value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_SwiperContentTransitionProxy_Void))));
    Ark_SwiperContentTransitionProxy value0 = static_cast<Ark_SwiperContentTransitionProxy>(SwiperContentTransitionProxy_serializer::read(thisDeserializer));
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_T_Void_Arkui_Component_Units_Length(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Length value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_T_Void_Arkui_Component_Units_Length))));
    thisDeserializer.readPointer();
    const Ark_Int8 value0TmpBufUnionSelector = thisDeserializer.readInt8();
    Ark_Length value0TmpBuf = {};
    value0TmpBuf.selector = value0TmpBufUnionSelector;
    if (value0TmpBufUnionSelector == 0) {
        value0TmpBuf.selector = 0;
        value0TmpBuf.value0 = static_cast<Ark_String>(thisDeserializer.readString());
    } else if (value0TmpBufUnionSelector == 1) {
        value0TmpBuf.selector = 1;
        value0TmpBuf.value1 = thisDeserializer.readFloat64();
    } else if (value0TmpBufUnionSelector == 2) {
        value0TmpBuf.selector = 2;
        value0TmpBuf.value2 = Resource_serializer::read(thisDeserializer);
    } else {
        INTEROP_FATAL("One of the branches for value0TmpBuf has to be chosen through deserialisation.");
    }
    Ark_Length value0 = static_cast<Ark_Length>(value0TmpBuf);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_T_Void_Arkui_Component_Units_Length(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Length value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_T_Void_Arkui_Component_Units_Length))));
    const Ark_Int8 value0TmpBufUnionSelector = thisDeserializer.readInt8();
    Ark_Length value0TmpBuf = {};
    value0TmpBuf.selector = value0TmpBufUnionSelector;
    if (value0TmpBufUnionSelector == 0) {
        value0TmpBuf.selector = 0;
        value0TmpBuf.value0 = static_cast<Ark_String>(thisDeserializer.readString());
    } else if (value0TmpBufUnionSelector == 1) {
        value0TmpBuf.selector = 1;
        value0TmpBuf.value1 = thisDeserializer.readFloat64();
    } else if (value0TmpBufUnionSelector == 2) {
        value0TmpBuf.selector = 2;
        value0TmpBuf.value2 = Resource_serializer::read(thisDeserializer);
    } else {
        INTEROP_FATAL("One of the branches for value0TmpBuf has to be chosen through deserialisation.");
    }
    Ark_Length value0 = static_cast<Ark_Length>(value0TmpBuf);
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_T_Void_Arkui_Component_Units_ResourceStr(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_ResourceStr value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_T_Void_Arkui_Component_Units_ResourceStr))));
    thisDeserializer.readPointer();
    const Ark_Int8 value0TmpBufUnionSelector = thisDeserializer.readInt8();
    Ark_ResourceStr value0TmpBuf = {};
    value0TmpBuf.selector = value0TmpBufUnionSelector;
    if (value0TmpBufUnionSelector == 0) {
        value0TmpBuf.selector = 0;
        value0TmpBuf.value0 = static_cast<Ark_String>(thisDeserializer.readString());
    } else if (value0TmpBufUnionSelector == 1) {
        value0TmpBuf.selector = 1;
        value0TmpBuf.value1 = Resource_serializer::read(thisDeserializer);
    } else {
        INTEROP_FATAL("One of the branches for value0TmpBuf has to be chosen through deserialisation.");
    }
    Ark_ResourceStr value0 = static_cast<Ark_ResourceStr>(value0TmpBuf);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_T_Void_Arkui_Component_Units_ResourceStr(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_ResourceStr value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_T_Void_Arkui_Component_Units_ResourceStr))));
    const Ark_Int8 value0TmpBufUnionSelector = thisDeserializer.readInt8();
    Ark_ResourceStr value0TmpBuf = {};
    value0TmpBuf.selector = value0TmpBufUnionSelector;
    if (value0TmpBufUnionSelector == 0) {
        value0TmpBuf.selector = 0;
        value0TmpBuf.value0 = static_cast<Ark_String>(thisDeserializer.readString());
    } else if (value0TmpBufUnionSelector == 1) {
        value0TmpBuf.selector = 1;
        value0TmpBuf.value1 = Resource_serializer::read(thisDeserializer);
    } else {
        INTEROP_FATAL("One of the branches for value0TmpBuf has to be chosen through deserialisation.");
    }
    Ark_ResourceStr value0 = static_cast<Ark_ResourceStr>(value0TmpBuf);
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_T_Void_Array_Arkui_Component_Units_ResourceStr(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Array_ResourceStr value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_T_Void_Array_Arkui_Component_Units_ResourceStr))));
    thisDeserializer.readPointer();
    const Ark_Int32 value0TmpBufLength = thisDeserializer.readInt32();
    Array_ResourceStr value0TmpBuf = {};
    thisDeserializer.resizeArray<std::decay<decltype(value0TmpBuf)>::type,
        std::decay<decltype(*value0TmpBuf.array)>::type>(&value0TmpBuf, value0TmpBufLength);
    for (int value0TmpBufBufCounterI = 0; value0TmpBufBufCounterI < value0TmpBufLength; value0TmpBufBufCounterI++) {
        const Ark_Int8 value0TmpBufTempBufUnionSelector = thisDeserializer.readInt8();
        Ark_ResourceStr value0TmpBufTempBuf = {};
        value0TmpBufTempBuf.selector = value0TmpBufTempBufUnionSelector;
        if (value0TmpBufTempBufUnionSelector == 0) {
            value0TmpBufTempBuf.selector = 0;
            value0TmpBufTempBuf.value0 = static_cast<Ark_String>(thisDeserializer.readString());
        } else if (value0TmpBufTempBufUnionSelector == 1) {
            value0TmpBufTempBuf.selector = 1;
            value0TmpBufTempBuf.value1 = Resource_serializer::read(thisDeserializer);
        } else {
            INTEROP_FATAL("One of the branches for value0TmpBufTempBuf has to be chosen through deserialisation.");
        }
        value0TmpBuf.array[value0TmpBufBufCounterI] = static_cast<Ark_ResourceStr>(value0TmpBufTempBuf);
    }
    Array_ResourceStr value0 = value0TmpBuf;
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_T_Void_Array_Arkui_Component_Units_ResourceStr(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Array_ResourceStr value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_T_Void_Array_Arkui_Component_Units_ResourceStr))));
    const Ark_Int32 value0TmpBufLength = thisDeserializer.readInt32();
    Array_ResourceStr value0TmpBuf = {};
    thisDeserializer.resizeArray<std::decay<decltype(value0TmpBuf)>::type,
        std::decay<decltype(*value0TmpBuf.array)>::type>(&value0TmpBuf, value0TmpBufLength);
    for (int value0TmpBufBufCounterI = 0; value0TmpBufBufCounterI < value0TmpBufLength; value0TmpBufBufCounterI++) {
        const Ark_Int8 value0TmpBufTempBufUnionSelector = thisDeserializer.readInt8();
        Ark_ResourceStr value0TmpBufTempBuf = {};
        value0TmpBufTempBuf.selector = value0TmpBufTempBufUnionSelector;
        if (value0TmpBufTempBufUnionSelector == 0) {
            value0TmpBufTempBuf.selector = 0;
            value0TmpBufTempBuf.value0 = static_cast<Ark_String>(thisDeserializer.readString());
        } else if (value0TmpBufTempBufUnionSelector == 1) {
            value0TmpBufTempBuf.selector = 1;
            value0TmpBufTempBuf.value1 = Resource_serializer::read(thisDeserializer);
        } else {
            INTEROP_FATAL("One of the branches for value0TmpBufTempBuf has to be chosen through deserialisation.");
        }
        value0TmpBuf.array[value0TmpBufBufCounterI] = static_cast<Ark_ResourceStr>(value0TmpBufTempBuf);
    }
    Array_ResourceStr value0 = value0TmpBuf;
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_T_Void_Array_Global_Resource_Resource(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Array_Resource value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_T_Void_Array_Global_Resource_Resource))));
    thisDeserializer.readPointer();
    const Ark_Int32 value0TmpBufLength = thisDeserializer.readInt32();
    Array_Resource value0TmpBuf = {};
    thisDeserializer.resizeArray<std::decay<decltype(value0TmpBuf)>::type,
        std::decay<decltype(*value0TmpBuf.array)>::type>(&value0TmpBuf, value0TmpBufLength);
    for (int value0TmpBufBufCounterI = 0; value0TmpBufBufCounterI < value0TmpBufLength; value0TmpBufBufCounterI++) {
        value0TmpBuf.array[value0TmpBufBufCounterI] = Resource_serializer::read(thisDeserializer);
    }
    Array_Resource value0 = value0TmpBuf;
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_T_Void_Array_Global_Resource_Resource(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Array_Resource value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_T_Void_Array_Global_Resource_Resource))));
    const Ark_Int32 value0TmpBufLength = thisDeserializer.readInt32();
    Array_Resource value0TmpBuf = {};
    thisDeserializer.resizeArray<std::decay<decltype(value0TmpBuf)>::type,
        std::decay<decltype(*value0TmpBuf.array)>::type>(&value0TmpBuf, value0TmpBufLength);
    for (int value0TmpBufBufCounterI = 0; value0TmpBufBufCounterI < value0TmpBufLength; value0TmpBufBufCounterI++) {
        value0TmpBuf.array[value0TmpBufBufCounterI] = Resource_serializer::read(thisDeserializer);
    }
    Array_Resource value0 = value0TmpBuf;
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_T_Void_Array_I32(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Array_Int32 value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_T_Void_Array_I32))));
    thisDeserializer.readPointer();
    const Ark_Int32 value0TmpBufLength = thisDeserializer.readInt32();
    Array_Int32 value0TmpBuf = {};
    thisDeserializer.resizeArray<std::decay<decltype(value0TmpBuf)>::type,
        std::decay<decltype(*value0TmpBuf.array)>::type>(&value0TmpBuf, value0TmpBufLength);
    for (int value0TmpBufBufCounterI = 0; value0TmpBufBufCounterI < value0TmpBufLength; value0TmpBufBufCounterI++) {
        value0TmpBuf.array[value0TmpBufBufCounterI] = thisDeserializer.readInt32();
    }
    Array_Int32 value0 = value0TmpBuf;
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_T_Void_Array_I32(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Array_Int32 value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_T_Void_Array_I32))));
    const Ark_Int32 value0TmpBufLength = thisDeserializer.readInt32();
    Array_Int32 value0TmpBuf = {};
    thisDeserializer.resizeArray<std::decay<decltype(value0TmpBuf)>::type,
        std::decay<decltype(*value0TmpBuf.array)>::type>(&value0TmpBuf, value0TmpBufLength);
    for (int value0TmpBufBufCounterI = 0; value0TmpBufBufCounterI < value0TmpBufLength; value0TmpBufBufCounterI++) {
        value0TmpBuf.array[value0TmpBufBufCounterI] = thisDeserializer.readInt32();
    }
    Array_Int32 value0 = value0TmpBuf;
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_T_Void_Array_String(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Array_String value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_T_Void_Array_String))));
    thisDeserializer.readPointer();
    const Ark_Int32 value0TmpBufLength = thisDeserializer.readInt32();
    Array_String value0TmpBuf = {};
    thisDeserializer.resizeArray<std::decay<decltype(value0TmpBuf)>::type,
        std::decay<decltype(*value0TmpBuf.array)>::type>(&value0TmpBuf, value0TmpBufLength);
    for (int value0TmpBufBufCounterI = 0; value0TmpBufBufCounterI < value0TmpBufLength; value0TmpBufBufCounterI++) {
        value0TmpBuf.array[value0TmpBufBufCounterI] = static_cast<Ark_String>(thisDeserializer.readString());
    }
    Array_String value0 = value0TmpBuf;
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_T_Void_Array_String(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Array_String value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_T_Void_Array_String))));
    const Ark_Int32 value0TmpBufLength = thisDeserializer.readInt32();
    Array_String value0TmpBuf = {};
    thisDeserializer.resizeArray<std::decay<decltype(value0TmpBuf)>::type,
        std::decay<decltype(*value0TmpBuf.array)>::type>(&value0TmpBuf, value0TmpBufLength);
    for (int value0TmpBufBufCounterI = 0; value0TmpBufBufCounterI < value0TmpBufLength; value0TmpBufBufCounterI++) {
        value0TmpBuf.array[value0TmpBufBufCounterI] = static_cast<Ark_String>(thisDeserializer.readString());
    }
    Array_String value0 = value0TmpBuf;
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_T_Void_Boolean(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_T_Void_Boolean))));
    thisDeserializer.readPointer();
    Ark_Boolean value0 = thisDeserializer.readBoolean();
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_T_Void_Boolean(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_T_Void_Boolean))));
    Ark_Boolean value0 = thisDeserializer.readBoolean();
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_T_Void_Date(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Date value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_T_Void_Date))));
    thisDeserializer.readPointer();
    Ark_Date value0 = thisDeserializer.readInt64();
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_T_Void_Date(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Date value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_T_Void_Date))));
    Ark_Date value0 = thisDeserializer.readInt64();
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_T_Void_F64(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Float64 value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_T_Void_F64))));
    thisDeserializer.readPointer();
    Ark_Float64 value0 = thisDeserializer.readFloat64();
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_T_Void_F64(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Float64 value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_T_Void_F64))));
    Ark_Float64 value0 = thisDeserializer.readFloat64();
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_T_Void_Global_Resource_Resource(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Resource value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_T_Void_Global_Resource_Resource))));
    thisDeserializer.readPointer();
    Ark_Resource value0 = Resource_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_T_Void_Global_Resource_Resource(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Resource value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_T_Void_Global_Resource_Resource))));
    Ark_Resource value0 = Resource_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_T_Void_I32(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Int32 value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_T_Void_I32))));
    thisDeserializer.readPointer();
    Ark_Int32 value0 = thisDeserializer.readInt32();
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_T_Void_I32(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int32 value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_T_Void_I32))));
    Ark_Int32 value0 = thisDeserializer.readInt32();
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_T_Void_Number(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_T_Void_Number))));
    thisDeserializer.readPointer();
    Ark_Number value0 = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_T_Void_Number(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_T_Void_Number))));
    Ark_Number value0 = static_cast<Ark_Number>(thisDeserializer.readNumber());
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_T_Void_String(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_String value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_T_Void_String))));
    thisDeserializer.readPointer();
    Ark_String value0 = static_cast<Ark_String>(thisDeserializer.readString());
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_T_Void_String(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_String value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_T_Void_String))));
    Ark_String value0 = static_cast<Ark_String>(thisDeserializer.readString());
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_TabContentTransitionProxy_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_TabContentTransitionProxy value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_TabContentTransitionProxy_Void))));
    thisDeserializer.readPointer();
    Ark_TabContentTransitionProxy value0 = static_cast<Ark_TabContentTransitionProxy>(TabContentTransitionProxy_serializer::read(thisDeserializer));
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_TabContentTransitionProxy_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_TabContentTransitionProxy value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_TabContentTransitionProxy_Void))));
    Ark_TabContentTransitionProxy value0 = static_cast<Ark_TabContentTransitionProxy>(TabContentTransitionProxy_serializer::read(thisDeserializer));
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_TerminationInfo_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_TerminationInfo value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_TerminationInfo_Void))));
    thisDeserializer.readPointer();
    Ark_TerminationInfo value0 = TerminationInfo_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_TerminationInfo_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_TerminationInfo value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_TerminationInfo_Void))));
    Ark_TerminationInfo value0 = TerminationInfo_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_TextPickerResult_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_TextPickerResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_TextPickerResult_Void))));
    thisDeserializer.readPointer();
    Ark_TextPickerResult value = TextPickerResult_serializer::read(thisDeserializer);
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_TextPickerResult_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_TextPickerResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_TextPickerResult_Void))));
    Ark_TextPickerResult value = TextPickerResult_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallCallback_TextRange_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_TextRange value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_TextRange_Void))));
    thisDeserializer.readPointer();
    Ark_TextRange value0 = TextRange_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_TextRange_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_TextRange value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_TextRange_Void))));
    Ark_TextRange value0 = TextRange_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_TimePickerResult_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_TimePickerResult value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_TimePickerResult_Void))));
    thisDeserializer.readPointer();
    Ark_TimePickerResult value0 = TimePickerResult_serializer::read(thisDeserializer);
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_TimePickerResult_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_TimePickerResult value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_TimePickerResult_Void))));
    Ark_TimePickerResult value0 = TimePickerResult_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_TouchEvent_HitTestMode(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_TouchEvent value0, const Callback_HitTestMode_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_TouchEvent_HitTestMode))));
    thisDeserializer.readPointer();
    Ark_TouchEvent value0 = static_cast<Ark_TouchEvent>(TouchEvent_serializer::read(thisDeserializer));
    Callback_HitTestMode_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_HitTestMode value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_HitTestMode_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_HitTestMode value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_HitTestMode_Void))))};
    _call(_resourceId, value0, continuationResult);
}
void deserializeAndCallSyncCallback_TouchEvent_HitTestMode(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_TouchEvent value0, const Callback_HitTestMode_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_TouchEvent_HitTestMode))));
    Ark_TouchEvent value0 = static_cast<Ark_TouchEvent>(TouchEvent_serializer::read(thisDeserializer));
    Callback_HitTestMode_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_HitTestMode value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_HitTestMode_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_HitTestMode value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_HitTestMode_Void))))};
    callSyncMethod(vmContext, resourceId, value0, continuationResult);
}
void deserializeAndCallCallback_TouchEvent_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_TouchEvent event)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_TouchEvent_Void))));
    thisDeserializer.readPointer();
    Ark_TouchEvent event = static_cast<Ark_TouchEvent>(TouchEvent_serializer::read(thisDeserializer));
    _call(_resourceId, event);
}
void deserializeAndCallSyncCallback_TouchEvent_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_TouchEvent event)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_TouchEvent_Void))));
    Ark_TouchEvent event = static_cast<Ark_TouchEvent>(TouchEvent_serializer::read(thisDeserializer));
    callSyncMethod(vmContext, resourceId, event);
}
void deserializeAndCallCallback_TouchResult_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_TouchResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_TouchResult_Void))));
    thisDeserializer.readPointer();
    Ark_TouchResult value = TouchResult_serializer::read(thisDeserializer);
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_TouchResult_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_TouchResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_TouchResult_Void))));
    Ark_TouchResult value = TouchResult_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallCallback_Tuple_I32_I32_I32_I32_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Tuple_I32_I32_I32_I32 value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Tuple_I32_I32_I32_I32_Void))));
    thisDeserializer.readPointer();
    Ark_Tuple_I32_I32_I32_I32 valueTmpBuf = {};
    valueTmpBuf.value0 = thisDeserializer.readInt32();
    valueTmpBuf.value1 = thisDeserializer.readInt32();
    valueTmpBuf.value2 = thisDeserializer.readInt32();
    valueTmpBuf.value3 = thisDeserializer.readInt32();
    Ark_Tuple_I32_I32_I32_I32 value = valueTmpBuf;
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_Tuple_I32_I32_I32_I32_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Tuple_I32_I32_I32_I32 value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Tuple_I32_I32_I32_I32_Void))));
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
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Tuple_I32_I32 value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Tuple_I32_I32_Void))));
    thisDeserializer.readPointer();
    Ark_Tuple_I32_I32 valueTmpBuf = {};
    valueTmpBuf.value0 = thisDeserializer.readInt32();
    valueTmpBuf.value1 = thisDeserializer.readInt32();
    Ark_Tuple_I32_I32 value = valueTmpBuf;
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_Tuple_I32_I32_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Tuple_I32_I32 value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Tuple_I32_I32_Void))));
    Ark_Tuple_I32_I32 valueTmpBuf = {};
    valueTmpBuf.value0 = thisDeserializer.readInt32();
    valueTmpBuf.value1 = thisDeserializer.readInt32();
    Ark_Tuple_I32_I32 value = valueTmpBuf;
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallCallback_UIExtensionProxy_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_UIExtensionProxy value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_UIExtensionProxy_Void))));
    thisDeserializer.readPointer();
    Ark_UIExtensionProxy value0 = static_cast<Ark_UIExtensionProxy>(UIExtensionProxy_serializer::read(thisDeserializer));
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_UIExtensionProxy_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_UIExtensionProxy value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_UIExtensionProxy_Void))));
    Ark_UIExtensionProxy value0 = static_cast<Ark_UIExtensionProxy>(UIExtensionProxy_serializer::read(thisDeserializer));
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_Union_CustomBuilder_DragItemInfo_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Union_CustomBuilder_DragItemInfo value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Union_CustomBuilder_DragItemInfo_Void))));
    thisDeserializer.readPointer();
    const Ark_Int8 valueTmpBufUnionSelector = thisDeserializer.readInt8();
    Ark_Union_CustomBuilder_DragItemInfo valueTmpBuf = {};
    valueTmpBuf.selector = valueTmpBufUnionSelector;
    if (valueTmpBufUnionSelector == 0) {
        valueTmpBuf.selector = 0;
        valueTmpBuf.value0 = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_CustomNodeBuilder)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_CustomNodeBuilder))))};
    } else if (valueTmpBufUnionSelector == 1) {
        valueTmpBuf.selector = 1;
        valueTmpBuf.value1 = DragItemInfo_serializer::read(thisDeserializer);
    } else {
        INTEROP_FATAL("One of the branches for valueTmpBuf has to be chosen through deserialisation.");
    }
    Ark_Union_CustomBuilder_DragItemInfo value = static_cast<Ark_Union_CustomBuilder_DragItemInfo>(valueTmpBuf);
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_Union_CustomBuilder_DragItemInfo_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Union_CustomBuilder_DragItemInfo value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Union_CustomBuilder_DragItemInfo_Void))));
    const Ark_Int8 valueTmpBufUnionSelector = thisDeserializer.readInt8();
    Ark_Union_CustomBuilder_DragItemInfo valueTmpBuf = {};
    valueTmpBuf.selector = valueTmpBufUnionSelector;
    if (valueTmpBufUnionSelector == 0) {
        valueTmpBuf.selector = 0;
        valueTmpBuf.value0 = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_CustomNodeBuilder)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_CustomNodeBuilder))))};
    } else if (valueTmpBufUnionSelector == 1) {
        valueTmpBuf.selector = 1;
        valueTmpBuf.value1 = DragItemInfo_serializer::read(thisDeserializer);
    } else {
        INTEROP_FATAL("One of the branches for valueTmpBuf has to be chosen through deserialisation.");
    }
    Ark_Union_CustomBuilder_DragItemInfo value = static_cast<Ark_Union_CustomBuilder_DragItemInfo>(valueTmpBuf);
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallCallback_Union_Object_Idlize_Stdlib_Null_Undefined_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_Object value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Union_Object_Idlize_Stdlib_Null_Undefined_Void))));
    thisDeserializer.readPointer();
    const auto value0TmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Object value0TmpBuf = {};
    value0TmpBuf.tag = value0TmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((value0TmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED)) {
        value0TmpBuf.value = static_cast<Ark_Object>(thisDeserializer.readObject());
    }
    Opt_Object value0 = value0TmpBuf;
    _call(_resourceId, value0);
}
void deserializeAndCallSyncCallback_Union_Object_Idlize_Stdlib_Null_Undefined_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_Object value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Union_Object_Idlize_Stdlib_Null_Undefined_Void))));
    const auto value0TmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Object value0TmpBuf = {};
    value0TmpBuf.tag = value0TmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((value0TmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED)) {
        value0TmpBuf.value = static_cast<Ark_Object>(thisDeserializer.readObject());
    }
    Opt_Object value0 = value0TmpBuf;
    callSyncMethod(vmContext, resourceId, value0);
}
void deserializeAndCallCallback_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Void))));
    thisDeserializer.readPointer();
    _call(_resourceId);
}
void deserializeAndCallSyncCallback_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Void))));
    callSyncMethod(vmContext, resourceId);
}
void deserializeAndCallCallback_WebKeyboardOptions_Void(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_WebKeyboardOptions value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_WebKeyboardOptions_Void))));
    thisDeserializer.readPointer();
    Ark_WebKeyboardOptions value = WebKeyboardOptions_serializer::read(thisDeserializer);
    _call(_resourceId, value);
}
void deserializeAndCallSyncCallback_WebKeyboardOptions_Void(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_WebKeyboardOptions value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_WebKeyboardOptions_Void))));
    Ark_WebKeyboardOptions value = WebKeyboardOptions_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallCheckBoxModifierBuilder(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Ark_CheckBoxConfiguration config, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_CheckBoxModifierBuilder))));
    thisDeserializer.readPointer();
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_CheckBoxConfiguration config = CheckBoxConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Pointer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Pointer_Void))))};
    _call(_resourceId, parentNode, config, continuationResult);
}
void deserializeAndCallSyncCheckBoxModifierBuilder(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Ark_CheckBoxConfiguration config, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_CheckBoxModifierBuilder))));
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_CheckBoxConfiguration config = CheckBoxConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Pointer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Pointer_Void))))};
    callSyncMethod(vmContext, resourceId, parentNode, config, continuationResult);
}
void deserializeAndCallContentDidScrollCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number selectedIndex, const Ark_Number index, const Ark_Number position, const Ark_Number mainAxisLength)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_ContentDidScrollCallback))));
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
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number selectedIndex, const Ark_Number index, const Ark_Number position, const Ark_Number mainAxisLength)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_ContentDidScrollCallback))));
    Ark_Number selectedIndex = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number position = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number mainAxisLength = static_cast<Ark_Number>(thisDeserializer.readNumber());
    callSyncMethod(vmContext, resourceId, selectedIndex, index, position, mainAxisLength);
}
void deserializeAndCallContentWillScrollCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_SwiperContentWillScrollResult result, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_ContentWillScrollCallback))));
    thisDeserializer.readPointer();
    Ark_SwiperContentWillScrollResult result = SwiperContentWillScrollResult_serializer::read(thisDeserializer);
    Callback_Boolean_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, result, continuationResult);
}
void deserializeAndCallSyncContentWillScrollCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_SwiperContentWillScrollResult result, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_ContentWillScrollCallback))));
    Ark_SwiperContentWillScrollResult result = SwiperContentWillScrollResult_serializer::read(thisDeserializer);
    Callback_Boolean_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    callSyncMethod(vmContext, resourceId, result, continuationResult);
}
void deserializeAndCallCustomBuilderT_I32(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Int32 t)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_CustomBuilderT_I32))));
    thisDeserializer.readPointer();
    Ark_Int32 t = thisDeserializer.readInt32();
    _call(_resourceId, t);
}
void deserializeAndCallSyncCustomBuilderT_I32(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int32 t)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_CustomBuilderT_I32))));
    Ark_Int32 t = thisDeserializer.readInt32();
    callSyncMethod(vmContext, resourceId, t);
}
void deserializeAndCallCustomNodeBuilder(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_CustomNodeBuilder))));
    thisDeserializer.readPointer();
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Callback_Pointer_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Pointer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Pointer_Void))))};
    _call(_resourceId, parentNode, continuationResult);
}
void deserializeAndCallSyncCustomNodeBuilder(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_CustomNodeBuilder))));
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Callback_Pointer_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Pointer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Pointer_Void))))};
    callSyncMethod(vmContext, resourceId, parentNode, continuationResult);
}
void deserializeAndCallDataPanelModifierBuilder(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Ark_DataPanelConfiguration config, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_DataPanelModifierBuilder))));
    thisDeserializer.readPointer();
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_DataPanelConfiguration config = DataPanelConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Pointer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Pointer_Void))))};
    _call(_resourceId, parentNode, config, continuationResult);
}
void deserializeAndCallSyncDataPanelModifierBuilder(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Ark_DataPanelConfiguration config, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_DataPanelModifierBuilder))));
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_DataPanelConfiguration config = DataPanelConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Pointer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Pointer_Void))))};
    callSyncMethod(vmContext, resourceId, parentNode, config, continuationResult);
}
void deserializeAndCallEditableTextOnChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_String value, const Opt_PreviewText previewText, const Opt_TextChangeOptions options)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_EditableTextOnChangeCallback))));
    thisDeserializer.readPointer();
    Ark_String value = static_cast<Ark_String>(thisDeserializer.readString());
    const auto previewTextTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_PreviewText previewTextTmpBuf = {};
    previewTextTmpBuf.tag = previewTextTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((previewTextTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED)) {
        previewTextTmpBuf.value = PreviewText_serializer::read(thisDeserializer);
    }
    Opt_PreviewText previewText = previewTextTmpBuf;
    const auto optionsTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_TextChangeOptions optionsTmpBuf = {};
    optionsTmpBuf.tag = optionsTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((optionsTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED)) {
        optionsTmpBuf.value = TextChangeOptions_serializer::read(thisDeserializer);
    }
    Opt_TextChangeOptions options = optionsTmpBuf;
    _call(_resourceId, value, previewText, options);
}
void deserializeAndCallSyncEditableTextOnChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_String value, const Opt_PreviewText previewText, const Opt_TextChangeOptions options)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_EditableTextOnChangeCallback))));
    Ark_String value = static_cast<Ark_String>(thisDeserializer.readString());
    const auto previewTextTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_PreviewText previewTextTmpBuf = {};
    previewTextTmpBuf.tag = previewTextTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((previewTextTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED)) {
        previewTextTmpBuf.value = PreviewText_serializer::read(thisDeserializer);
    }
    Opt_PreviewText previewText = previewTextTmpBuf;
    const auto optionsTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_TextChangeOptions optionsTmpBuf = {};
    optionsTmpBuf.tag = optionsTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((optionsTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED)) {
        optionsTmpBuf.value = TextChangeOptions_serializer::read(thisDeserializer);
    }
    Opt_TextChangeOptions options = optionsTmpBuf;
    callSyncMethod(vmContext, resourceId, value, previewText, options);
}
void deserializeAndCallErrorCallback_Ohos_Base_BusinessError(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_BusinessError err)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_ErrorCallback_Ohos_Base_BusinessError))));
    thisDeserializer.readPointer();
    Ark_BusinessError err = static_cast<Ark_BusinessError>(BusinessError_serializer::read(thisDeserializer));
    _call(_resourceId, err);
}
void deserializeAndCallSyncErrorCallback_Ohos_Base_BusinessError(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_BusinessError err)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_ErrorCallback_Ohos_Base_BusinessError))));
    Ark_BusinessError err = static_cast<Ark_BusinessError>(BusinessError_serializer::read(thisDeserializer));
    callSyncMethod(vmContext, resourceId, err);
}
void deserializeAndCallGaugeModifierBuilder(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Ark_GaugeConfiguration config, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_GaugeModifierBuilder))));
    thisDeserializer.readPointer();
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_GaugeConfiguration config = GaugeConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Pointer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Pointer_Void))))};
    _call(_resourceId, parentNode, config, continuationResult);
}
void deserializeAndCallSyncGaugeModifierBuilder(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Ark_GaugeConfiguration config, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_GaugeModifierBuilder))));
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_GaugeConfiguration config = GaugeConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Pointer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Pointer_Void))))};
    callSyncMethod(vmContext, resourceId, parentNode, config, continuationResult);
}
void deserializeAndCallGestureRecognizerJudgeBeginCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_BaseGestureEvent event, const Ark_GestureRecognizer current, const Array_GestureRecognizer recognizers, const Callback_GestureJudgeResult_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_GestureRecognizerJudgeBeginCallback))));
    thisDeserializer.readPointer();
    Ark_BaseGestureEvent event = static_cast<Ark_BaseGestureEvent>(BaseGestureEvent_serializer::read(thisDeserializer));
    Ark_GestureRecognizer current = static_cast<Ark_GestureRecognizer>(GestureRecognizer_serializer::read(thisDeserializer));
    const Ark_Int32 recognizersTmpBufLength = thisDeserializer.readInt32();
    Array_GestureRecognizer recognizersTmpBuf = {};
    thisDeserializer.resizeArray<std::decay<decltype(recognizersTmpBuf)>::type,
        std::decay<decltype(*recognizersTmpBuf.array)>::type>(&recognizersTmpBuf, recognizersTmpBufLength);
    for (int recognizersTmpBufBufCounterI = 0; recognizersTmpBufBufCounterI < recognizersTmpBufLength; recognizersTmpBufBufCounterI++) {
        recognizersTmpBuf.array[recognizersTmpBufBufCounterI] = static_cast<Ark_GestureRecognizer>(GestureRecognizer_serializer::read(thisDeserializer));
    }
    Array_GestureRecognizer recognizers = recognizersTmpBuf;
    Callback_GestureJudgeResult_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_GestureJudgeResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_GestureJudgeResult_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_GestureJudgeResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_GestureJudgeResult_Void))))};
    _call(_resourceId, event, current, recognizers, continuationResult);
}
void deserializeAndCallSyncGestureRecognizerJudgeBeginCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_BaseGestureEvent event, const Ark_GestureRecognizer current, const Array_GestureRecognizer recognizers, const Callback_GestureJudgeResult_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_GestureRecognizerJudgeBeginCallback))));
    Ark_BaseGestureEvent event = static_cast<Ark_BaseGestureEvent>(BaseGestureEvent_serializer::read(thisDeserializer));
    Ark_GestureRecognizer current = static_cast<Ark_GestureRecognizer>(GestureRecognizer_serializer::read(thisDeserializer));
    const Ark_Int32 recognizersTmpBufLength = thisDeserializer.readInt32();
    Array_GestureRecognizer recognizersTmpBuf = {};
    thisDeserializer.resizeArray<std::decay<decltype(recognizersTmpBuf)>::type,
        std::decay<decltype(*recognizersTmpBuf.array)>::type>(&recognizersTmpBuf, recognizersTmpBufLength);
    for (int recognizersTmpBufBufCounterI = 0; recognizersTmpBufBufCounterI < recognizersTmpBufLength; recognizersTmpBufBufCounterI++) {
        recognizersTmpBuf.array[recognizersTmpBufBufCounterI] = static_cast<Ark_GestureRecognizer>(GestureRecognizer_serializer::read(thisDeserializer));
    }
    Array_GestureRecognizer recognizers = recognizersTmpBuf;
    Callback_GestureJudgeResult_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_GestureJudgeResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_GestureJudgeResult_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_GestureJudgeResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_GestureJudgeResult_Void))))};
    callSyncMethod(vmContext, resourceId, event, current, recognizers, continuationResult);
}
void deserializeAndCallGetItemMainSizeByIndex(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Int32 index, const Callback_F64_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_GetItemMainSizeByIndex))));
    thisDeserializer.readPointer();
    Ark_Int32 index = thisDeserializer.readInt32();
    Callback_F64_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Float64 offset)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_F64_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Float64 offset)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_F64_Void))))};
    _call(_resourceId, index, continuationResult);
}
void deserializeAndCallSyncGetItemMainSizeByIndex(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int32 index, const Callback_F64_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_GetItemMainSizeByIndex))));
    Ark_Int32 index = thisDeserializer.readInt32();
    Callback_F64_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Float64 offset)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_F64_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Float64 offset)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_F64_Void))))};
    callSyncMethod(vmContext, resourceId, index, continuationResult);
}
void deserializeAndCallHoverCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean isHover, const Ark_HoverEvent event)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_HoverCallback))));
    thisDeserializer.readPointer();
    Ark_Boolean isHover = thisDeserializer.readBoolean();
    Ark_HoverEvent event = static_cast<Ark_HoverEvent>(HoverEvent_serializer::read(thisDeserializer));
    _call(_resourceId, isHover, event);
}
void deserializeAndCallSyncHoverCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isHover, const Ark_HoverEvent event)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_HoverCallback))));
    Ark_Boolean isHover = thisDeserializer.readBoolean();
    Ark_HoverEvent event = static_cast<Ark_HoverEvent>(HoverEvent_serializer::read(thisDeserializer));
    callSyncMethod(vmContext, resourceId, isHover, event);
}
void deserializeAndCallImageCompleteCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_ImageLoadResult result)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_ImageCompleteCallback))));
    thisDeserializer.readPointer();
    Ark_ImageLoadResult result = ImageLoadResult_serializer::read(thisDeserializer);
    _call(_resourceId, result);
}
void deserializeAndCallSyncImageCompleteCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_ImageLoadResult result)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_ImageCompleteCallback))));
    Ark_ImageLoadResult result = ImageLoadResult_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, result);
}
void deserializeAndCallImageErrorCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_ImageError error)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_ImageErrorCallback))));
    thisDeserializer.readPointer();
    Ark_ImageError error = ImageError_serializer::read(thisDeserializer);
    _call(_resourceId, error);
}
void deserializeAndCallSyncImageErrorCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_ImageError error)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_ImageErrorCallback))));
    Ark_ImageError error = ImageError_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, error);
}
void deserializeAndCallImageOnCompleteCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_ImageCompleteEvent loadEvent)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_ImageOnCompleteCallback))));
    thisDeserializer.readPointer();
    const auto loadEventTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_ImageCompleteEvent loadEventTmpBuf = {};
    loadEventTmpBuf.tag = loadEventTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((loadEventTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED)) {
        loadEventTmpBuf.value = ImageCompleteEvent_serializer::read(thisDeserializer);
    }
    Opt_ImageCompleteEvent loadEvent = loadEventTmpBuf;
    _call(_resourceId, loadEvent);
}
void deserializeAndCallSyncImageOnCompleteCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_ImageCompleteEvent loadEvent)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_ImageOnCompleteCallback))));
    const auto loadEventTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_ImageCompleteEvent loadEventTmpBuf = {};
    loadEventTmpBuf.tag = loadEventTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((loadEventTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED)) {
        loadEventTmpBuf.value = ImageCompleteEvent_serializer::read(thisDeserializer);
    }
    Opt_ImageCompleteEvent loadEvent = loadEventTmpBuf;
    callSyncMethod(vmContext, resourceId, loadEvent);
}
void deserializeAndCallInterceptionModeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_NavigationMode mode)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_InterceptionModeCallback))));
    thisDeserializer.readPointer();
    Ark_NavigationMode mode = static_cast<Ark_NavigationMode>(thisDeserializer.readInt32());
    _call(_resourceId, mode);
}
void deserializeAndCallSyncInterceptionModeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_NavigationMode mode)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_InterceptionModeCallback))));
    Ark_NavigationMode mode = static_cast<Ark_NavigationMode>(thisDeserializer.readInt32());
    callSyncMethod(vmContext, resourceId, mode);
}
void deserializeAndCallInterceptionShowCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Union_NavDestinationContext_NavBar from, const Ark_Union_NavDestinationContext_NavBar to, Ark_NavigationOperation operation, const Ark_Boolean isAnimated)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_InterceptionShowCallback))));
    thisDeserializer.readPointer();
    const Ark_Int8 fromTmpBufUnionSelector = thisDeserializer.readInt8();
    Ark_Union_NavDestinationContext_NavBar fromTmpBuf = {};
    fromTmpBuf.selector = fromTmpBufUnionSelector;
    if (fromTmpBufUnionSelector == 0) {
        fromTmpBuf.selector = 0;
        fromTmpBuf.value0 = static_cast<Ark_NavDestinationContext>(NavDestinationContext_serializer::read(thisDeserializer));
    } else if (fromTmpBufUnionSelector == 1) {
        fromTmpBuf.selector = 1;
        fromTmpBuf.value1 = static_cast<Ark_String>(thisDeserializer.readString());
    } else {
        INTEROP_FATAL("One of the branches for fromTmpBuf has to be chosen through deserialisation.");
    }
    Ark_Union_NavDestinationContext_NavBar from = static_cast<Ark_Union_NavDestinationContext_NavBar>(fromTmpBuf);
    const Ark_Int8 toTmpBufUnionSelector = thisDeserializer.readInt8();
    Ark_Union_NavDestinationContext_NavBar toTmpBuf = {};
    toTmpBuf.selector = toTmpBufUnionSelector;
    if (toTmpBufUnionSelector == 0) {
        toTmpBuf.selector = 0;
        toTmpBuf.value0 = static_cast<Ark_NavDestinationContext>(NavDestinationContext_serializer::read(thisDeserializer));
    } else if (toTmpBufUnionSelector == 1) {
        toTmpBuf.selector = 1;
        toTmpBuf.value1 = static_cast<Ark_String>(thisDeserializer.readString());
    } else {
        INTEROP_FATAL("One of the branches for toTmpBuf has to be chosen through deserialisation.");
    }
    Ark_Union_NavDestinationContext_NavBar to = static_cast<Ark_Union_NavDestinationContext_NavBar>(toTmpBuf);
    Ark_NavigationOperation operation = static_cast<Ark_NavigationOperation>(thisDeserializer.readInt32());
    Ark_Boolean isAnimated = thisDeserializer.readBoolean();
    _call(_resourceId, from, to, operation, isAnimated);
}
void deserializeAndCallSyncInterceptionShowCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Union_NavDestinationContext_NavBar from, const Ark_Union_NavDestinationContext_NavBar to, Ark_NavigationOperation operation, const Ark_Boolean isAnimated)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_InterceptionShowCallback))));
    const Ark_Int8 fromTmpBufUnionSelector = thisDeserializer.readInt8();
    Ark_Union_NavDestinationContext_NavBar fromTmpBuf = {};
    fromTmpBuf.selector = fromTmpBufUnionSelector;
    if (fromTmpBufUnionSelector == 0) {
        fromTmpBuf.selector = 0;
        fromTmpBuf.value0 = static_cast<Ark_NavDestinationContext>(NavDestinationContext_serializer::read(thisDeserializer));
    } else if (fromTmpBufUnionSelector == 1) {
        fromTmpBuf.selector = 1;
        fromTmpBuf.value1 = static_cast<Ark_String>(thisDeserializer.readString());
    } else {
        INTEROP_FATAL("One of the branches for fromTmpBuf has to be chosen through deserialisation.");
    }
    Ark_Union_NavDestinationContext_NavBar from = static_cast<Ark_Union_NavDestinationContext_NavBar>(fromTmpBuf);
    const Ark_Int8 toTmpBufUnionSelector = thisDeserializer.readInt8();
    Ark_Union_NavDestinationContext_NavBar toTmpBuf = {};
    toTmpBuf.selector = toTmpBufUnionSelector;
    if (toTmpBufUnionSelector == 0) {
        toTmpBuf.selector = 0;
        toTmpBuf.value0 = static_cast<Ark_NavDestinationContext>(NavDestinationContext_serializer::read(thisDeserializer));
    } else if (toTmpBufUnionSelector == 1) {
        toTmpBuf.selector = 1;
        toTmpBuf.value1 = static_cast<Ark_String>(thisDeserializer.readString());
    } else {
        INTEROP_FATAL("One of the branches for toTmpBuf has to be chosen through deserialisation.");
    }
    Ark_Union_NavDestinationContext_NavBar to = static_cast<Ark_Union_NavDestinationContext_NavBar>(toTmpBuf);
    Ark_NavigationOperation operation = static_cast<Ark_NavigationOperation>(thisDeserializer.readInt32());
    Ark_Boolean isAnimated = thisDeserializer.readBoolean();
    callSyncMethod(vmContext, resourceId, from, to, operation, isAnimated);
}
void deserializeAndCallLoadingProgressModifierBuilder(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Ark_LoadingProgressConfiguration config, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_LoadingProgressModifierBuilder))));
    thisDeserializer.readPointer();
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_LoadingProgressConfiguration config = LoadingProgressConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Pointer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Pointer_Void))))};
    _call(_resourceId, parentNode, config, continuationResult);
}
void deserializeAndCallSyncLoadingProgressModifierBuilder(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Ark_LoadingProgressConfiguration config, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_LoadingProgressModifierBuilder))));
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_LoadingProgressConfiguration config = LoadingProgressConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Pointer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Pointer_Void))))};
    callSyncMethod(vmContext, resourceId, parentNode, config, continuationResult);
}
void deserializeAndCallMenuCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Int32 start, const Ark_Int32 end)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_MenuCallback))));
    thisDeserializer.readPointer();
    Ark_Int32 start = static_cast<Ark_Int32>(thisDeserializer.readInt32());
    Ark_Int32 end = static_cast<Ark_Int32>(thisDeserializer.readInt32());
    _call(_resourceId, start, end);
}
void deserializeAndCallSyncMenuCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int32 start, const Ark_Int32 end)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_MenuCallback))));
    Ark_Int32 start = static_cast<Ark_Int32>(thisDeserializer.readInt32());
    Ark_Int32 end = static_cast<Ark_Int32>(thisDeserializer.readInt32());
    callSyncMethod(vmContext, resourceId, start, end);
}
void deserializeAndCallMenuItemModifierBuilder(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Ark_MenuItemConfiguration config, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_MenuItemModifierBuilder))));
    thisDeserializer.readPointer();
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_MenuItemConfiguration config = static_cast<Ark_MenuItemConfiguration>(MenuItemConfiguration_serializer::read(thisDeserializer));
    Callback_Pointer_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Pointer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Pointer_Void))))};
    _call(_resourceId, parentNode, config, continuationResult);
}
void deserializeAndCallSyncMenuItemModifierBuilder(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Ark_MenuItemConfiguration config, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_MenuItemModifierBuilder))));
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_MenuItemConfiguration config = static_cast<Ark_MenuItemConfiguration>(MenuItemConfiguration_serializer::read(thisDeserializer));
    Callback_Pointer_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Pointer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Pointer_Void))))};
    callSyncMethod(vmContext, resourceId, parentNode, config, continuationResult);
}
void deserializeAndCallMenuOnAppearCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Int32 start, const Ark_Int32 end)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_MenuOnAppearCallback))));
    thisDeserializer.readPointer();
    Ark_Int32 start = static_cast<Ark_Int32>(thisDeserializer.readInt32());
    Ark_Int32 end = static_cast<Ark_Int32>(thisDeserializer.readInt32());
    _call(_resourceId, start, end);
}
void deserializeAndCallSyncMenuOnAppearCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int32 start, const Ark_Int32 end)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_MenuOnAppearCallback))));
    Ark_Int32 start = static_cast<Ark_Int32>(thisDeserializer.readInt32());
    Ark_Int32 end = static_cast<Ark_Int32>(thisDeserializer.readInt32());
    callSyncMethod(vmContext, resourceId, start, end);
}
void deserializeAndCallModifierKeyStateGetter(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Array_String keys, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_ModifierKeyStateGetter))));
    thisDeserializer.readPointer();
    const Ark_Int32 keysTmpBufLength = thisDeserializer.readInt32();
    Array_String keysTmpBuf = {};
    thisDeserializer.resizeArray<std::decay<decltype(keysTmpBuf)>::type,
        std::decay<decltype(*keysTmpBuf.array)>::type>(&keysTmpBuf, keysTmpBufLength);
    for (int keysTmpBufBufCounterI = 0; keysTmpBufBufCounterI < keysTmpBufLength; keysTmpBufBufCounterI++) {
        keysTmpBuf.array[keysTmpBufBufCounterI] = static_cast<Ark_String>(thisDeserializer.readString());
    }
    Array_String keys = keysTmpBuf;
    Callback_Boolean_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, keys, continuationResult);
}
void deserializeAndCallSyncModifierKeyStateGetter(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Array_String keys, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_ModifierKeyStateGetter))));
    const Ark_Int32 keysTmpBufLength = thisDeserializer.readInt32();
    Array_String keysTmpBuf = {};
    thisDeserializer.resizeArray<std::decay<decltype(keysTmpBuf)>::type,
        std::decay<decltype(*keysTmpBuf.array)>::type>(&keysTmpBuf, keysTmpBufLength);
    for (int keysTmpBufBufCounterI = 0; keysTmpBufBufCounterI < keysTmpBufLength; keysTmpBufBufCounterI++) {
        keysTmpBuf.array[keysTmpBufBufCounterI] = static_cast<Ark_String>(thisDeserializer.readString());
    }
    Array_String keys = keysTmpBuf;
    Callback_Boolean_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    callSyncMethod(vmContext, resourceId, keys, continuationResult);
}
void deserializeAndCallNavDestinationTransitionDelegate(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_NavigationOperation operation, const Ark_Boolean isEnter, const Callback_Opt_Array_NavDestinationTransition_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_NavDestinationTransitionDelegate))));
    thisDeserializer.readPointer();
    Ark_NavigationOperation operation = static_cast<Ark_NavigationOperation>(thisDeserializer.readInt32());
    Ark_Boolean isEnter = thisDeserializer.readBoolean();
    Callback_Opt_Array_NavDestinationTransition_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_Array_NavDestinationTransition value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Opt_Array_NavDestinationTransition_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_Array_NavDestinationTransition value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Opt_Array_NavDestinationTransition_Void))))};
    _call(_resourceId, operation, isEnter, continuationResult);
}
void deserializeAndCallSyncNavDestinationTransitionDelegate(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_NavigationOperation operation, const Ark_Boolean isEnter, const Callback_Opt_Array_NavDestinationTransition_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_NavDestinationTransitionDelegate))));
    Ark_NavigationOperation operation = static_cast<Ark_NavigationOperation>(thisDeserializer.readInt32());
    Ark_Boolean isEnter = thisDeserializer.readBoolean();
    Callback_Opt_Array_NavDestinationTransition_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_Array_NavDestinationTransition value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Opt_Array_NavDestinationTransition_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_Array_NavDestinationTransition value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Opt_Array_NavDestinationTransition_Void))))};
    callSyncMethod(vmContext, resourceId, operation, isEnter, continuationResult);
}
void deserializeAndCallNavExtender_OnUpdateStack(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_NavExtender_OnUpdateStack))));
    thisDeserializer.readPointer();
    _call(_resourceId);
}
void deserializeAndCallSyncNavExtender_OnUpdateStack(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_NavExtender_OnUpdateStack))));
    callSyncMethod(vmContext, resourceId);
}
void deserializeAndCallOnAdsBlockedCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_AdsBlockedDetails details)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_OnAdsBlockedCallback))));
    thisDeserializer.readPointer();
    Ark_AdsBlockedDetails details = AdsBlockedDetails_serializer::read(thisDeserializer);
    _call(_resourceId, details);
}
void deserializeAndCallSyncOnAdsBlockedCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_AdsBlockedDetails details)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_OnAdsBlockedCallback))));
    Ark_AdsBlockedDetails details = AdsBlockedDetails_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, details);
}
void deserializeAndCallOnAlphabetIndexerPopupSelectCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Int32 index)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_OnAlphabetIndexerPopupSelectCallback))));
    thisDeserializer.readPointer();
    Ark_Int32 index = thisDeserializer.readInt32();
    _call(_resourceId, index);
}
void deserializeAndCallSyncOnAlphabetIndexerPopupSelectCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int32 index)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_OnAlphabetIndexerPopupSelectCallback))));
    Ark_Int32 index = thisDeserializer.readInt32();
    callSyncMethod(vmContext, resourceId, index);
}
void deserializeAndCallOnAlphabetIndexerRequestPopupDataCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Int32 index, const Callback_Array_String_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_OnAlphabetIndexerRequestPopupDataCallback))));
    thisDeserializer.readPointer();
    Ark_Int32 index = thisDeserializer.readInt32();
    Callback_Array_String_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Array_String value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Array_String_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Array_String value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Array_String_Void))))};
    _call(_resourceId, index, continuationResult);
}
void deserializeAndCallSyncOnAlphabetIndexerRequestPopupDataCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int32 index, const Callback_Array_String_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_OnAlphabetIndexerRequestPopupDataCallback))));
    Ark_Int32 index = thisDeserializer.readInt32();
    Callback_Array_String_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Array_String value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Array_String_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Array_String value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Array_String_Void))))};
    callSyncMethod(vmContext, resourceId, index, continuationResult);
}
void deserializeAndCallOnAlphabetIndexerSelectCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Int32 index)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_OnAlphabetIndexerSelectCallback))));
    thisDeserializer.readPointer();
    Ark_Int32 index = thisDeserializer.readInt32();
    _call(_resourceId, index);
}
void deserializeAndCallSyncOnAlphabetIndexerSelectCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int32 index)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_OnAlphabetIndexerSelectCallback))));
    Ark_Int32 index = thisDeserializer.readInt32();
    callSyncMethod(vmContext, resourceId, index);
}
void deserializeAndCallOnCheckboxChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_OnCheckboxChangeCallback))));
    thisDeserializer.readPointer();
    Ark_Boolean value = thisDeserializer.readBoolean();
    _call(_resourceId, value);
}
void deserializeAndCallSyncOnCheckboxChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_OnCheckboxChangeCallback))));
    Ark_Boolean value = thisDeserializer.readBoolean();
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallOnCheckboxGroupChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_CheckboxGroupResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_OnCheckboxGroupChangeCallback))));
    thisDeserializer.readPointer();
    Ark_CheckboxGroupResult value = CheckboxGroupResult_serializer::read(thisDeserializer);
    _call(_resourceId, value);
}
void deserializeAndCallSyncOnCheckboxGroupChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_CheckboxGroupResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_OnCheckboxGroupChangeCallback))));
    Ark_CheckboxGroupResult value = CheckboxGroupResult_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallOnContentScrollCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Float64 totalOffsetX, const Ark_Float64 totalOffsetY)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_OnContentScrollCallback))));
    thisDeserializer.readPointer();
    Ark_Float64 totalOffsetX = thisDeserializer.readFloat64();
    Ark_Float64 totalOffsetY = thisDeserializer.readFloat64();
    _call(_resourceId, totalOffsetX, totalOffsetY);
}
void deserializeAndCallSyncOnContentScrollCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Float64 totalOffsetX, const Ark_Float64 totalOffsetY)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_OnContentScrollCallback))));
    Ark_Float64 totalOffsetX = thisDeserializer.readFloat64();
    Ark_Float64 totalOffsetY = thisDeserializer.readFloat64();
    callSyncMethod(vmContext, resourceId, totalOffsetX, totalOffsetY);
}
void deserializeAndCallOnContextMenuHideCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_OnContextMenuHideCallback))));
    thisDeserializer.readPointer();
    _call(_resourceId);
}
void deserializeAndCallSyncOnContextMenuHideCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_OnContextMenuHideCallback))));
    callSyncMethod(vmContext, resourceId);
}
void deserializeAndCallOnCreateMenuCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Array_TextMenuItem menuItems, const Callback_Array_TextMenuItem_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_OnCreateMenuCallback))));
    thisDeserializer.readPointer();
    const Ark_Int32 menuItemsTmpBufLength = thisDeserializer.readInt32();
    Array_TextMenuItem menuItemsTmpBuf = {};
    thisDeserializer.resizeArray<std::decay<decltype(menuItemsTmpBuf)>::type,
        std::decay<decltype(*menuItemsTmpBuf.array)>::type>(&menuItemsTmpBuf, menuItemsTmpBufLength);
    for (int menuItemsTmpBufBufCounterI = 0; menuItemsTmpBufBufCounterI < menuItemsTmpBufLength; menuItemsTmpBufBufCounterI++) {
        menuItemsTmpBuf.array[menuItemsTmpBufBufCounterI] = TextMenuItem_serializer::read(thisDeserializer);
    }
    Array_TextMenuItem menuItems = menuItemsTmpBuf;
    Callback_Array_TextMenuItem_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Array_TextMenuItem value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Array_TextMenuItem_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Array_TextMenuItem value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Array_TextMenuItem_Void))))};
    _call(_resourceId, menuItems, continuationResult);
}
void deserializeAndCallSyncOnCreateMenuCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Array_TextMenuItem menuItems, const Callback_Array_TextMenuItem_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_OnCreateMenuCallback))));
    const Ark_Int32 menuItemsTmpBufLength = thisDeserializer.readInt32();
    Array_TextMenuItem menuItemsTmpBuf = {};
    thisDeserializer.resizeArray<std::decay<decltype(menuItemsTmpBuf)>::type,
        std::decay<decltype(*menuItemsTmpBuf.array)>::type>(&menuItemsTmpBuf, menuItemsTmpBufLength);
    for (int menuItemsTmpBufBufCounterI = 0; menuItemsTmpBufBufCounterI < menuItemsTmpBufLength; menuItemsTmpBufBufCounterI++) {
        menuItemsTmpBuf.array[menuItemsTmpBufBufCounterI] = TextMenuItem_serializer::read(thisDeserializer);
    }
    Array_TextMenuItem menuItems = menuItemsTmpBuf;
    Callback_Array_TextMenuItem_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Array_TextMenuItem value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Array_TextMenuItem_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Array_TextMenuItem value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Array_TextMenuItem_Void))))};
    callSyncMethod(vmContext, resourceId, menuItems, continuationResult);
}
void deserializeAndCallOnDidChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_TextRange rangeBefore, const Ark_TextRange rangeAfter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_OnDidChangeCallback))));
    thisDeserializer.readPointer();
    Ark_TextRange rangeBefore = TextRange_serializer::read(thisDeserializer);
    Ark_TextRange rangeAfter = TextRange_serializer::read(thisDeserializer);
    _call(_resourceId, rangeBefore, rangeAfter);
}
void deserializeAndCallSyncOnDidChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_TextRange rangeBefore, const Ark_TextRange rangeAfter)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_OnDidChangeCallback))));
    Ark_TextRange rangeBefore = TextRange_serializer::read(thisDeserializer);
    Ark_TextRange rangeAfter = TextRange_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, rangeBefore, rangeAfter);
}
void deserializeAndCallOnDragEventCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_DragEvent event, const Opt_String extraParams)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_OnDragEventCallback))));
    thisDeserializer.readPointer();
    Ark_DragEvent event = static_cast<Ark_DragEvent>(DragEvent_serializer::read(thisDeserializer));
    const auto extraParamsTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_String extraParamsTmpBuf = {};
    extraParamsTmpBuf.tag = extraParamsTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((extraParamsTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED)) {
        extraParamsTmpBuf.value = static_cast<Ark_String>(thisDeserializer.readString());
    }
    Opt_String extraParams = extraParamsTmpBuf;
    _call(_resourceId, event, extraParams);
}
void deserializeAndCallSyncOnDragEventCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_DragEvent event, const Opt_String extraParams)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_OnDragEventCallback))));
    Ark_DragEvent event = static_cast<Ark_DragEvent>(DragEvent_serializer::read(thisDeserializer));
    const auto extraParamsTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_String extraParamsTmpBuf = {};
    extraParamsTmpBuf.tag = extraParamsTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((extraParamsTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED)) {
        extraParamsTmpBuf.value = static_cast<Ark_String>(thisDeserializer.readString());
    }
    Opt_String extraParams = extraParamsTmpBuf;
    callSyncMethod(vmContext, resourceId, event, extraParams);
}
void deserializeAndCallOnFirstMeaningfulPaintCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_FirstMeaningfulPaint firstMeaningfulPaint)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_OnFirstMeaningfulPaintCallback))));
    thisDeserializer.readPointer();
    Ark_FirstMeaningfulPaint firstMeaningfulPaint = FirstMeaningfulPaint_serializer::read(thisDeserializer);
    _call(_resourceId, firstMeaningfulPaint);
}
void deserializeAndCallSyncOnFirstMeaningfulPaintCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_FirstMeaningfulPaint firstMeaningfulPaint)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_OnFirstMeaningfulPaintCallback))));
    Ark_FirstMeaningfulPaint firstMeaningfulPaint = FirstMeaningfulPaint_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, firstMeaningfulPaint);
}
void deserializeAndCallOnFoldStatusChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnFoldStatusChangeInfo event)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_OnFoldStatusChangeCallback))));
    thisDeserializer.readPointer();
    Ark_OnFoldStatusChangeInfo event = OnFoldStatusChangeInfo_serializer::read(thisDeserializer);
    _call(_resourceId, event);
}
void deserializeAndCallSyncOnFoldStatusChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnFoldStatusChangeInfo event)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_OnFoldStatusChangeCallback))));
    Ark_OnFoldStatusChangeInfo event = OnFoldStatusChangeInfo_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, event);
}
void deserializeAndCallOnFullScreenEnterCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_FullScreenEnterEvent event)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_OnFullScreenEnterCallback))));
    thisDeserializer.readPointer();
    Ark_FullScreenEnterEvent event = FullScreenEnterEvent_serializer::read(thisDeserializer);
    _call(_resourceId, event);
}
void deserializeAndCallSyncOnFullScreenEnterCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_FullScreenEnterEvent event)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_OnFullScreenEnterCallback))));
    Ark_FullScreenEnterEvent event = FullScreenEnterEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, event);
}
void deserializeAndCallOnHoverCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean status, const Ark_HoverEvent event)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_OnHoverCallback))));
    thisDeserializer.readPointer();
    Ark_Boolean status = thisDeserializer.readBoolean();
    Ark_HoverEvent event = static_cast<Ark_HoverEvent>(HoverEvent_serializer::read(thisDeserializer));
    _call(_resourceId, status, event);
}
void deserializeAndCallSyncOnHoverCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean status, const Ark_HoverEvent event)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_OnHoverCallback))));
    Ark_Boolean status = thisDeserializer.readBoolean();
    Ark_HoverEvent event = static_cast<Ark_HoverEvent>(HoverEvent_serializer::read(thisDeserializer));
    callSyncMethod(vmContext, resourceId, status, event);
}
void deserializeAndCallOnHoverStatusChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_HoverEventParam param)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_OnHoverStatusChangeCallback))));
    thisDeserializer.readPointer();
    Ark_HoverEventParam param = HoverEventParam_serializer::read(thisDeserializer);
    _call(_resourceId, param);
}
void deserializeAndCallSyncOnHoverStatusChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_HoverEventParam param)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_OnHoverStatusChangeCallback))));
    Ark_HoverEventParam param = HoverEventParam_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, param);
}
void deserializeAndCallOnIntelligentTrackingPreventionCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_IntelligentTrackingPreventionDetails details)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_OnIntelligentTrackingPreventionCallback))));
    thisDeserializer.readPointer();
    Ark_IntelligentTrackingPreventionDetails details = IntelligentTrackingPreventionDetails_serializer::read(thisDeserializer);
    _call(_resourceId, details);
}
void deserializeAndCallSyncOnIntelligentTrackingPreventionCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_IntelligentTrackingPreventionDetails details)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_OnIntelligentTrackingPreventionCallback))));
    Ark_IntelligentTrackingPreventionDetails details = IntelligentTrackingPreventionDetails_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, details);
}
void deserializeAndCallOnItemDragStartCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_ItemDragInfo event, const Ark_Int32 itemIndex, const Callback_Opt_CustomBuilder_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_OnItemDragStartCallback))));
    thisDeserializer.readPointer();
    Ark_ItemDragInfo event = ItemDragInfo_serializer::read(thisDeserializer);
    Ark_Int32 itemIndex = thisDeserializer.readInt32();
    Callback_Opt_CustomBuilder_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_CustomNodeBuilder value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Opt_CustomBuilder_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_CustomNodeBuilder value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Opt_CustomBuilder_Void))))};
    _call(_resourceId, event, itemIndex, continuationResult);
}
void deserializeAndCallSyncOnItemDragStartCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_ItemDragInfo event, const Ark_Int32 itemIndex, const Callback_Opt_CustomBuilder_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_OnItemDragStartCallback))));
    Ark_ItemDragInfo event = ItemDragInfo_serializer::read(thisDeserializer);
    Ark_Int32 itemIndex = thisDeserializer.readInt32();
    Callback_Opt_CustomBuilder_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_CustomNodeBuilder value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Opt_CustomBuilder_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_CustomNodeBuilder value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Opt_CustomBuilder_Void))))};
    callSyncMethod(vmContext, resourceId, event, itemIndex, continuationResult);
}
void deserializeAndCallOnLargestContentfulPaintCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_LargestContentfulPaint largestContentfulPaint)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_OnLargestContentfulPaintCallback))));
    thisDeserializer.readPointer();
    Ark_LargestContentfulPaint largestContentfulPaint = LargestContentfulPaint_serializer::read(thisDeserializer);
    _call(_resourceId, largestContentfulPaint);
}
void deserializeAndCallSyncOnLargestContentfulPaintCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_LargestContentfulPaint largestContentfulPaint)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_OnLargestContentfulPaintCallback))));
    Ark_LargestContentfulPaint largestContentfulPaint = LargestContentfulPaint_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, largestContentfulPaint);
}
void deserializeAndCallOnLinearIndicatorChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number index, const Ark_Number progress)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_OnLinearIndicatorChangeCallback))));
    thisDeserializer.readPointer();
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number progress = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _call(_resourceId, index, progress);
}
void deserializeAndCallSyncOnLinearIndicatorChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number index, const Ark_Number progress)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_OnLinearIndicatorChangeCallback))));
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number progress = static_cast<Ark_Number>(thisDeserializer.readNumber());
    callSyncMethod(vmContext, resourceId, index, progress);
}
void deserializeAndCallOnMenuItemClickCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_TextMenuItem menuItem, const Ark_TextRange range, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_OnMenuItemClickCallback))));
    thisDeserializer.readPointer();
    Ark_TextMenuItem menuItem = TextMenuItem_serializer::read(thisDeserializer);
    Ark_TextRange range = TextRange_serializer::read(thisDeserializer);
    Callback_Boolean_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, menuItem, range, continuationResult);
}
void deserializeAndCallSyncOnMenuItemClickCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_TextMenuItem menuItem, const Ark_TextRange range, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_OnMenuItemClickCallback))));
    Ark_TextMenuItem menuItem = TextMenuItem_serializer::read(thisDeserializer);
    Ark_TextRange range = TextRange_serializer::read(thisDeserializer);
    Callback_Boolean_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    callSyncMethod(vmContext, resourceId, menuItem, range, continuationResult);
}
void deserializeAndCallOnMoveHandler(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Int32 from, const Ark_Int32 to)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_OnMoveHandler))));
    thisDeserializer.readPointer();
    Ark_Int32 from = thisDeserializer.readInt32();
    Ark_Int32 to = thisDeserializer.readInt32();
    _call(_resourceId, from, to);
}
void deserializeAndCallSyncOnMoveHandler(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int32 from, const Ark_Int32 to)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_OnMoveHandler))));
    Ark_Int32 from = thisDeserializer.readInt32();
    Ark_Int32 to = thisDeserializer.readInt32();
    callSyncMethod(vmContext, resourceId, from, to);
}
void deserializeAndCallOnNativeEmbedVisibilityChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativeEmbedVisibilityInfo nativeEmbedVisibilityInfo)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_OnNativeEmbedVisibilityChangeCallback))));
    thisDeserializer.readPointer();
    Ark_NativeEmbedVisibilityInfo nativeEmbedVisibilityInfo = NativeEmbedVisibilityInfo_serializer::read(thisDeserializer);
    _call(_resourceId, nativeEmbedVisibilityInfo);
}
void deserializeAndCallSyncOnNativeEmbedVisibilityChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativeEmbedVisibilityInfo nativeEmbedVisibilityInfo)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_OnNativeEmbedVisibilityChangeCallback))));
    Ark_NativeEmbedVisibilityInfo nativeEmbedVisibilityInfo = NativeEmbedVisibilityInfo_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, nativeEmbedVisibilityInfo);
}
void deserializeAndCallOnNavigationEntryCommittedCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_LoadCommittedDetails loadCommittedDetails)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_OnNavigationEntryCommittedCallback))));
    thisDeserializer.readPointer();
    Ark_LoadCommittedDetails loadCommittedDetails = LoadCommittedDetails_serializer::read(thisDeserializer);
    _call(_resourceId, loadCommittedDetails);
}
void deserializeAndCallSyncOnNavigationEntryCommittedCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_LoadCommittedDetails loadCommittedDetails)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_OnNavigationEntryCommittedCallback))));
    Ark_LoadCommittedDetails loadCommittedDetails = LoadCommittedDetails_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, loadCommittedDetails);
}
void deserializeAndCallOnOverrideUrlLoadingCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_WebResourceRequest webResourceRequest, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_OnOverrideUrlLoadingCallback))));
    thisDeserializer.readPointer();
    Ark_WebResourceRequest webResourceRequest = static_cast<Ark_WebResourceRequest>(WebResourceRequest_serializer::read(thisDeserializer));
    Callback_Boolean_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, webResourceRequest, continuationResult);
}
void deserializeAndCallSyncOnOverrideUrlLoadingCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_WebResourceRequest webResourceRequest, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_OnOverrideUrlLoadingCallback))));
    Ark_WebResourceRequest webResourceRequest = static_cast<Ark_WebResourceRequest>(WebResourceRequest_serializer::read(thisDeserializer));
    Callback_Boolean_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    callSyncMethod(vmContext, resourceId, webResourceRequest, continuationResult);
}
void deserializeAndCallOnPasteCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_String content, const Ark_PasteEvent event)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_OnPasteCallback))));
    thisDeserializer.readPointer();
    Ark_String content = static_cast<Ark_String>(thisDeserializer.readString());
    Ark_PasteEvent event = PasteEvent_serializer::read(thisDeserializer);
    _call(_resourceId, content, event);
}
void deserializeAndCallSyncOnPasteCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_String content, const Ark_PasteEvent event)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_OnPasteCallback))));
    Ark_String content = static_cast<Ark_String>(thisDeserializer.readString());
    Ark_PasteEvent event = PasteEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, content, event);
}
void deserializeAndCallOnRadioChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean isChecked)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_OnRadioChangeCallback))));
    thisDeserializer.readPointer();
    Ark_Boolean isChecked = thisDeserializer.readBoolean();
    _call(_resourceId, isChecked);
}
void deserializeAndCallSyncOnRadioChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isChecked)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_OnRadioChangeCallback))));
    Ark_Boolean isChecked = thisDeserializer.readBoolean();
    callSyncMethod(vmContext, resourceId, isChecked);
}
void deserializeAndCallOnRatingChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Float64 rating)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_OnRatingChangeCallback))));
    thisDeserializer.readPointer();
    Ark_Float64 rating = thisDeserializer.readFloat64();
    _call(_resourceId, rating);
}
void deserializeAndCallSyncOnRatingChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Float64 rating)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_OnRatingChangeCallback))));
    Ark_Float64 rating = thisDeserializer.readFloat64();
    callSyncMethod(vmContext, resourceId, rating);
}
void deserializeAndCallOnRenderProcessNotRespondingCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_RenderProcessNotRespondingData data)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_OnRenderProcessNotRespondingCallback))));
    thisDeserializer.readPointer();
    Ark_RenderProcessNotRespondingData data = RenderProcessNotRespondingData_serializer::read(thisDeserializer);
    _call(_resourceId, data);
}
void deserializeAndCallSyncOnRenderProcessNotRespondingCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_RenderProcessNotRespondingData data)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_OnRenderProcessNotRespondingCallback))));
    Ark_RenderProcessNotRespondingData data = RenderProcessNotRespondingData_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, data);
}
void deserializeAndCallOnRenderProcessRespondingCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_OnRenderProcessRespondingCallback))));
    thisDeserializer.readPointer();
    _call(_resourceId);
}
void deserializeAndCallSyncOnRenderProcessRespondingCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_OnRenderProcessRespondingCallback))));
    callSyncMethod(vmContext, resourceId);
}
void deserializeAndCallOnSafeBrowsingCheckResultCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_ThreatType threatType)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_OnSafeBrowsingCheckResultCallback))));
    thisDeserializer.readPointer();
    Ark_ThreatType threatType = static_cast<Ark_ThreatType>(thisDeserializer.readInt32());
    _call(_resourceId, threatType);
}
void deserializeAndCallSyncOnSafeBrowsingCheckResultCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_ThreatType threatType)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_OnSafeBrowsingCheckResultCallback))));
    Ark_ThreatType threatType = static_cast<Ark_ThreatType>(thisDeserializer.readInt32());
    callSyncMethod(vmContext, resourceId, threatType);
}
void deserializeAndCallOnScrollCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Float64 scrollOffset, Ark_ScrollState scrollState)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_OnScrollCallback))));
    thisDeserializer.readPointer();
    Ark_Float64 scrollOffset = thisDeserializer.readFloat64();
    Ark_ScrollState scrollState = static_cast<Ark_ScrollState>(thisDeserializer.readInt32());
    _call(_resourceId, scrollOffset, scrollState);
}
void deserializeAndCallSyncOnScrollCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Float64 scrollOffset, Ark_ScrollState scrollState)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_OnScrollCallback))));
    Ark_Float64 scrollOffset = thisDeserializer.readFloat64();
    Ark_ScrollState scrollState = static_cast<Ark_ScrollState>(thisDeserializer.readInt32());
    callSyncMethod(vmContext, resourceId, scrollOffset, scrollState);
}
void deserializeAndCallOnScrollEdgeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_Edge side)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_OnScrollEdgeCallback))));
    thisDeserializer.readPointer();
    Ark_Edge side = static_cast<Ark_Edge>(thisDeserializer.readInt32());
    _call(_resourceId, side);
}
void deserializeAndCallSyncOnScrollEdgeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_Edge side)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_OnScrollEdgeCallback))));
    Ark_Edge side = static_cast<Ark_Edge>(thisDeserializer.readInt32());
    callSyncMethod(vmContext, resourceId, side);
}
void deserializeAndCallOnScrollFrameBeginCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Float64 offset, Ark_ScrollState state, const Callback_OnScrollFrameBeginHandlerResult_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_OnScrollFrameBeginCallback))));
    thisDeserializer.readPointer();
    Ark_Float64 offset = thisDeserializer.readFloat64();
    Ark_ScrollState state = static_cast<Ark_ScrollState>(thisDeserializer.readInt32());
    Callback_OnScrollFrameBeginHandlerResult_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnScrollFrameBeginHandlerResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_OnScrollFrameBeginHandlerResult_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnScrollFrameBeginHandlerResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_OnScrollFrameBeginHandlerResult_Void))))};
    _call(_resourceId, offset, state, continuationResult);
}
void deserializeAndCallSyncOnScrollFrameBeginCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Float64 offset, Ark_ScrollState state, const Callback_OnScrollFrameBeginHandlerResult_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_OnScrollFrameBeginCallback))));
    Ark_Float64 offset = thisDeserializer.readFloat64();
    Ark_ScrollState state = static_cast<Ark_ScrollState>(thisDeserializer.readInt32());
    Callback_OnScrollFrameBeginHandlerResult_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnScrollFrameBeginHandlerResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_OnScrollFrameBeginHandlerResult_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnScrollFrameBeginHandlerResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_OnScrollFrameBeginHandlerResult_Void))))};
    callSyncMethod(vmContext, resourceId, offset, state, continuationResult);
}
void deserializeAndCallOnScrollVisibleContentChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_VisibleListContentInfo start, const Ark_VisibleListContentInfo end)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_OnScrollVisibleContentChangeCallback))));
    thisDeserializer.readPointer();
    Ark_VisibleListContentInfo start = VisibleListContentInfo_serializer::read(thisDeserializer);
    Ark_VisibleListContentInfo end = VisibleListContentInfo_serializer::read(thisDeserializer);
    _call(_resourceId, start, end);
}
void deserializeAndCallSyncOnScrollVisibleContentChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_VisibleListContentInfo start, const Ark_VisibleListContentInfo end)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_OnScrollVisibleContentChangeCallback))));
    Ark_VisibleListContentInfo start = VisibleListContentInfo_serializer::read(thisDeserializer);
    Ark_VisibleListContentInfo end = VisibleListContentInfo_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, start, end);
}
void deserializeAndCallOnSelectCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Int32 index, const Ark_String selectStr)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_OnSelectCallback))));
    thisDeserializer.readPointer();
    Ark_Int32 index = thisDeserializer.readInt32();
    Ark_String selectStr = static_cast<Ark_String>(thisDeserializer.readString());
    _call(_resourceId, index, selectStr);
}
void deserializeAndCallSyncOnSelectCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int32 index, const Ark_String selectStr)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_OnSelectCallback))));
    Ark_Int32 index = thisDeserializer.readInt32();
    Ark_String selectStr = static_cast<Ark_String>(thisDeserializer.readString());
    callSyncMethod(vmContext, resourceId, index, selectStr);
}
void deserializeAndCallOnSslErrorEventCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_SslErrorEvent sslErrorEvent)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_OnSslErrorEventCallback))));
    thisDeserializer.readPointer();
    Ark_SslErrorEvent sslErrorEvent = SslErrorEvent_serializer::read(thisDeserializer);
    _call(_resourceId, sslErrorEvent);
}
void deserializeAndCallSyncOnSslErrorEventCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_SslErrorEvent sslErrorEvent)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_OnSslErrorEventCallback))));
    Ark_SslErrorEvent sslErrorEvent = SslErrorEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, sslErrorEvent);
}
void deserializeAndCallOnSubmitCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_EnterKeyType enterKey, const Ark_SubmitEvent event)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_OnSubmitCallback))));
    thisDeserializer.readPointer();
    Ark_EnterKeyType enterKey = static_cast<Ark_EnterKeyType>(thisDeserializer.readInt32());
    Ark_SubmitEvent event = static_cast<Ark_SubmitEvent>(SubmitEvent_serializer::read(thisDeserializer));
    _call(_resourceId, enterKey, event);
}
void deserializeAndCallSyncOnSubmitCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_EnterKeyType enterKey, const Ark_SubmitEvent event)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_OnSubmitCallback))));
    Ark_EnterKeyType enterKey = static_cast<Ark_EnterKeyType>(thisDeserializer.readInt32());
    Ark_SubmitEvent event = static_cast<Ark_SubmitEvent>(SubmitEvent_serializer::read(thisDeserializer));
    callSyncMethod(vmContext, resourceId, enterKey, event);
}
void deserializeAndCallOnSwiperAnimationEndCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number index, const Ark_SwiperAnimationEvent extraInfo)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_OnSwiperAnimationEndCallback))));
    thisDeserializer.readPointer();
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_SwiperAnimationEvent extraInfo = SwiperAnimationEvent_serializer::read(thisDeserializer);
    _call(_resourceId, index, extraInfo);
}
void deserializeAndCallSyncOnSwiperAnimationEndCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number index, const Ark_SwiperAnimationEvent extraInfo)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_OnSwiperAnimationEndCallback))));
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_SwiperAnimationEvent extraInfo = SwiperAnimationEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, index, extraInfo);
}
void deserializeAndCallOnSwiperAnimationStartCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number index, const Ark_Number targetIndex, const Ark_SwiperAnimationEvent extraInfo)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_OnSwiperAnimationStartCallback))));
    thisDeserializer.readPointer();
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number targetIndex = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_SwiperAnimationEvent extraInfo = SwiperAnimationEvent_serializer::read(thisDeserializer);
    _call(_resourceId, index, targetIndex, extraInfo);
}
void deserializeAndCallSyncOnSwiperAnimationStartCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number index, const Ark_Number targetIndex, const Ark_SwiperAnimationEvent extraInfo)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_OnSwiperAnimationStartCallback))));
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_Number targetIndex = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_SwiperAnimationEvent extraInfo = SwiperAnimationEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, index, targetIndex, extraInfo);
}
void deserializeAndCallOnSwiperGestureSwipeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number index, const Ark_SwiperAnimationEvent extraInfo)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_OnSwiperGestureSwipeCallback))));
    thisDeserializer.readPointer();
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_SwiperAnimationEvent extraInfo = SwiperAnimationEvent_serializer::read(thisDeserializer);
    _call(_resourceId, index, extraInfo);
}
void deserializeAndCallSyncOnSwiperGestureSwipeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number index, const Ark_SwiperAnimationEvent extraInfo)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_OnSwiperGestureSwipeCallback))));
    Ark_Number index = static_cast<Ark_Number>(thisDeserializer.readNumber());
    Ark_SwiperAnimationEvent extraInfo = SwiperAnimationEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, index, extraInfo);
}
void deserializeAndCallOnTabsAnimationEndCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Int32 index, const Ark_TabsAnimationEvent extraInfo)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_OnTabsAnimationEndCallback))));
    thisDeserializer.readPointer();
    Ark_Int32 index = thisDeserializer.readInt32();
    Ark_TabsAnimationEvent extraInfo = TabsAnimationEvent_serializer::read(thisDeserializer);
    _call(_resourceId, index, extraInfo);
}
void deserializeAndCallSyncOnTabsAnimationEndCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int32 index, const Ark_TabsAnimationEvent extraInfo)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_OnTabsAnimationEndCallback))));
    Ark_Int32 index = thisDeserializer.readInt32();
    Ark_TabsAnimationEvent extraInfo = TabsAnimationEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, index, extraInfo);
}
void deserializeAndCallOnTabsAnimationStartCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Int32 index, const Ark_Int32 targetIndex, const Ark_TabsAnimationEvent extraInfo)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_OnTabsAnimationStartCallback))));
    thisDeserializer.readPointer();
    Ark_Int32 index = thisDeserializer.readInt32();
    Ark_Int32 targetIndex = thisDeserializer.readInt32();
    Ark_TabsAnimationEvent extraInfo = TabsAnimationEvent_serializer::read(thisDeserializer);
    _call(_resourceId, index, targetIndex, extraInfo);
}
void deserializeAndCallSyncOnTabsAnimationStartCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int32 index, const Ark_Int32 targetIndex, const Ark_TabsAnimationEvent extraInfo)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_OnTabsAnimationStartCallback))));
    Ark_Int32 index = thisDeserializer.readInt32();
    Ark_Int32 targetIndex = thisDeserializer.readInt32();
    Ark_TabsAnimationEvent extraInfo = TabsAnimationEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, index, targetIndex, extraInfo);
}
void deserializeAndCallOnTabsContentWillChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Int32 currentIndex, const Ark_Int32 comingIndex, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_OnTabsContentWillChangeCallback))));
    thisDeserializer.readPointer();
    Ark_Int32 currentIndex = thisDeserializer.readInt32();
    Ark_Int32 comingIndex = thisDeserializer.readInt32();
    Callback_Boolean_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    _call(_resourceId, currentIndex, comingIndex, continuationResult);
}
void deserializeAndCallSyncOnTabsContentWillChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int32 currentIndex, const Ark_Int32 comingIndex, const Callback_Boolean_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_OnTabsContentWillChangeCallback))));
    Ark_Int32 currentIndex = thisDeserializer.readInt32();
    Ark_Int32 comingIndex = thisDeserializer.readInt32();
    Callback_Boolean_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Boolean_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean value0)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Boolean_Void))))};
    callSyncMethod(vmContext, resourceId, currentIndex, comingIndex, continuationResult);
}
void deserializeAndCallOnTabsGestureSwipeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Int32 index, const Ark_TabsAnimationEvent extraInfo)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_OnTabsGestureSwipeCallback))));
    thisDeserializer.readPointer();
    Ark_Int32 index = thisDeserializer.readInt32();
    Ark_TabsAnimationEvent extraInfo = TabsAnimationEvent_serializer::read(thisDeserializer);
    _call(_resourceId, index, extraInfo);
}
void deserializeAndCallSyncOnTabsGestureSwipeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int32 index, const Ark_TabsAnimationEvent extraInfo)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_OnTabsGestureSwipeCallback))));
    Ark_Int32 index = thisDeserializer.readInt32();
    Ark_TabsAnimationEvent extraInfo = TabsAnimationEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, index, extraInfo);
}
void deserializeAndCallOnTextPickerChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Union_String_Array_String selectItem, const Ark_Union_I32_Array_I32 index)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_OnTextPickerChangeCallback))));
    thisDeserializer.readPointer();
    const Ark_Int8 selectItemTmpBufUnionSelector = thisDeserializer.readInt8();
    Ark_Union_String_Array_String selectItemTmpBuf = {};
    selectItemTmpBuf.selector = selectItemTmpBufUnionSelector;
    if (selectItemTmpBufUnionSelector == 0) {
        selectItemTmpBuf.selector = 0;
        selectItemTmpBuf.value0 = static_cast<Ark_String>(thisDeserializer.readString());
    } else if (selectItemTmpBufUnionSelector == 1) {
        selectItemTmpBuf.selector = 1;
        const Ark_Int32 selectItemTmpBufBufULength = thisDeserializer.readInt32();
        Array_String selectItemTmpBufBufU = {};
        thisDeserializer.resizeArray<std::decay<decltype(selectItemTmpBufBufU)>::type,
        std::decay<decltype(*selectItemTmpBufBufU.array)>::type>(&selectItemTmpBufBufU, selectItemTmpBufBufULength);
        for (int selectItemTmpBufBufUBufCounterI = 0; selectItemTmpBufBufUBufCounterI < selectItemTmpBufBufULength; selectItemTmpBufBufUBufCounterI++) {
            selectItemTmpBufBufU.array[selectItemTmpBufBufUBufCounterI] = static_cast<Ark_String>(thisDeserializer.readString());
        }
        selectItemTmpBuf.value1 = selectItemTmpBufBufU;
    } else {
        INTEROP_FATAL("One of the branches for selectItemTmpBuf has to be chosen through deserialisation.");
    }
    Ark_Union_String_Array_String selectItem = static_cast<Ark_Union_String_Array_String>(selectItemTmpBuf);
    const Ark_Int8 indexTmpBufUnionSelector = thisDeserializer.readInt8();
    Ark_Union_I32_Array_I32 indexTmpBuf = {};
    indexTmpBuf.selector = indexTmpBufUnionSelector;
    if (indexTmpBufUnionSelector == 0) {
        indexTmpBuf.selector = 0;
        indexTmpBuf.value0 = thisDeserializer.readInt32();
    } else if (indexTmpBufUnionSelector == 1) {
        indexTmpBuf.selector = 1;
        const Ark_Int32 indexTmpBufBufULength = thisDeserializer.readInt32();
        Array_Int32 indexTmpBufBufU = {};
        thisDeserializer.resizeArray<std::decay<decltype(indexTmpBufBufU)>::type,
        std::decay<decltype(*indexTmpBufBufU.array)>::type>(&indexTmpBufBufU, indexTmpBufBufULength);
        for (int indexTmpBufBufUBufCounterI = 0; indexTmpBufBufUBufCounterI < indexTmpBufBufULength; indexTmpBufBufUBufCounterI++) {
            indexTmpBufBufU.array[indexTmpBufBufUBufCounterI] = thisDeserializer.readInt32();
        }
        indexTmpBuf.value1 = indexTmpBufBufU;
    } else {
        INTEROP_FATAL("One of the branches for indexTmpBuf has to be chosen through deserialisation.");
    }
    Ark_Union_I32_Array_I32 index = static_cast<Ark_Union_I32_Array_I32>(indexTmpBuf);
    _call(_resourceId, selectItem, index);
}
void deserializeAndCallSyncOnTextPickerChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Union_String_Array_String selectItem, const Ark_Union_I32_Array_I32 index)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_OnTextPickerChangeCallback))));
    const Ark_Int8 selectItemTmpBufUnionSelector = thisDeserializer.readInt8();
    Ark_Union_String_Array_String selectItemTmpBuf = {};
    selectItemTmpBuf.selector = selectItemTmpBufUnionSelector;
    if (selectItemTmpBufUnionSelector == 0) {
        selectItemTmpBuf.selector = 0;
        selectItemTmpBuf.value0 = static_cast<Ark_String>(thisDeserializer.readString());
    } else if (selectItemTmpBufUnionSelector == 1) {
        selectItemTmpBuf.selector = 1;
        const Ark_Int32 selectItemTmpBufBufULength = thisDeserializer.readInt32();
        Array_String selectItemTmpBufBufU = {};
        thisDeserializer.resizeArray<std::decay<decltype(selectItemTmpBufBufU)>::type,
        std::decay<decltype(*selectItemTmpBufBufU.array)>::type>(&selectItemTmpBufBufU, selectItemTmpBufBufULength);
        for (int selectItemTmpBufBufUBufCounterI = 0; selectItemTmpBufBufUBufCounterI < selectItemTmpBufBufULength; selectItemTmpBufBufUBufCounterI++) {
            selectItemTmpBufBufU.array[selectItemTmpBufBufUBufCounterI] = static_cast<Ark_String>(thisDeserializer.readString());
        }
        selectItemTmpBuf.value1 = selectItemTmpBufBufU;
    } else {
        INTEROP_FATAL("One of the branches for selectItemTmpBuf has to be chosen through deserialisation.");
    }
    Ark_Union_String_Array_String selectItem = static_cast<Ark_Union_String_Array_String>(selectItemTmpBuf);
    const Ark_Int8 indexTmpBufUnionSelector = thisDeserializer.readInt8();
    Ark_Union_I32_Array_I32 indexTmpBuf = {};
    indexTmpBuf.selector = indexTmpBufUnionSelector;
    if (indexTmpBufUnionSelector == 0) {
        indexTmpBuf.selector = 0;
        indexTmpBuf.value0 = thisDeserializer.readInt32();
    } else if (indexTmpBufUnionSelector == 1) {
        indexTmpBuf.selector = 1;
        const Ark_Int32 indexTmpBufBufULength = thisDeserializer.readInt32();
        Array_Int32 indexTmpBufBufU = {};
        thisDeserializer.resizeArray<std::decay<decltype(indexTmpBufBufU)>::type,
        std::decay<decltype(*indexTmpBufBufU.array)>::type>(&indexTmpBufBufU, indexTmpBufBufULength);
        for (int indexTmpBufBufUBufCounterI = 0; indexTmpBufBufUBufCounterI < indexTmpBufBufULength; indexTmpBufBufUBufCounterI++) {
            indexTmpBufBufU.array[indexTmpBufBufUBufCounterI] = thisDeserializer.readInt32();
        }
        indexTmpBuf.value1 = indexTmpBufBufU;
    } else {
        INTEROP_FATAL("One of the branches for indexTmpBuf has to be chosen through deserialisation.");
    }
    Ark_Union_I32_Array_I32 index = static_cast<Ark_Union_I32_Array_I32>(indexTmpBuf);
    callSyncMethod(vmContext, resourceId, selectItem, index);
}
void deserializeAndCallOnTextSelectionChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Int32 selectionStart, const Ark_Int32 selectionEnd)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_OnTextSelectionChangeCallback))));
    thisDeserializer.readPointer();
    Ark_Int32 selectionStart = thisDeserializer.readInt32();
    Ark_Int32 selectionEnd = thisDeserializer.readInt32();
    _call(_resourceId, selectionStart, selectionEnd);
}
void deserializeAndCallSyncOnTextSelectionChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int32 selectionStart, const Ark_Int32 selectionEnd)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_OnTextSelectionChangeCallback))));
    Ark_Int32 selectionStart = thisDeserializer.readInt32();
    Ark_Int32 selectionEnd = thisDeserializer.readInt32();
    callSyncMethod(vmContext, resourceId, selectionStart, selectionEnd);
}
void deserializeAndCallOnTimePickerChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_TimePickerResult result)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_OnTimePickerChangeCallback))));
    thisDeserializer.readPointer();
    Ark_TimePickerResult result = TimePickerResult_serializer::read(thisDeserializer);
    _call(_resourceId, result);
}
void deserializeAndCallSyncOnTimePickerChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_TimePickerResult result)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_OnTimePickerChangeCallback))));
    Ark_TimePickerResult result = TimePickerResult_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, result);
}
void deserializeAndCallOnViewportFitChangedCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_ViewportFit viewportFit)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_OnViewportFitChangedCallback))));
    thisDeserializer.readPointer();
    Ark_ViewportFit viewportFit = static_cast<Ark_ViewportFit>(thisDeserializer.readInt32());
    _call(_resourceId, viewportFit);
}
void deserializeAndCallSyncOnViewportFitChangedCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_ViewportFit viewportFit)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_OnViewportFitChangedCallback))));
    Ark_ViewportFit viewportFit = static_cast<Ark_ViewportFit>(thisDeserializer.readInt32());
    callSyncMethod(vmContext, resourceId, viewportFit);
}
void deserializeAndCallOnWillScrollCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Float64 scrollOffset, Ark_ScrollState scrollState, Ark_ScrollSource scrollSource, const Callback_Opt_ScrollResult_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_OnWillScrollCallback))));
    thisDeserializer.readPointer();
    Ark_Float64 scrollOffset = thisDeserializer.readFloat64();
    Ark_ScrollState scrollState = static_cast<Ark_ScrollState>(thisDeserializer.readInt32());
    Ark_ScrollSource scrollSource = static_cast<Ark_ScrollSource>(thisDeserializer.readInt32());
    Callback_Opt_ScrollResult_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_ScrollResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Opt_ScrollResult_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_ScrollResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Opt_ScrollResult_Void))))};
    _call(_resourceId, scrollOffset, scrollState, scrollSource, continuationResult);
}
void deserializeAndCallSyncOnWillScrollCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Float64 scrollOffset, Ark_ScrollState scrollState, Ark_ScrollSource scrollSource, const Callback_Opt_ScrollResult_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_OnWillScrollCallback))));
    Ark_Float64 scrollOffset = thisDeserializer.readFloat64();
    Ark_ScrollState scrollState = static_cast<Ark_ScrollState>(thisDeserializer.readInt32());
    Ark_ScrollSource scrollSource = static_cast<Ark_ScrollSource>(thisDeserializer.readInt32());
    Callback_Opt_ScrollResult_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_ScrollResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Opt_ScrollResult_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_ScrollResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Opt_ScrollResult_Void))))};
    callSyncMethod(vmContext, resourceId, scrollOffset, scrollState, scrollSource, continuationResult);
}
void deserializeAndCallPageMapBuilder(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_String name, const Opt_Object param)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_PageMapBuilder))));
    thisDeserializer.readPointer();
    Ark_String name = static_cast<Ark_String>(thisDeserializer.readString());
    const auto paramTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Object paramTmpBuf = {};
    paramTmpBuf.tag = paramTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((paramTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED)) {
        paramTmpBuf.value = static_cast<Ark_Object>(thisDeserializer.readObject());
    }
    Opt_Object param = paramTmpBuf;
    _call(_resourceId, name, param);
}
void deserializeAndCallSyncPageMapBuilder(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_String name, const Opt_Object param)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_PageMapBuilder))));
    Ark_String name = static_cast<Ark_String>(thisDeserializer.readString());
    const auto paramTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_Object paramTmpBuf = {};
    paramTmpBuf.tag = paramTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((paramTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED)) {
        paramTmpBuf.value = static_cast<Ark_Object>(thisDeserializer.readObject());
    }
    Opt_Object param = paramTmpBuf;
    callSyncMethod(vmContext, resourceId, name, param);
}
void deserializeAndCallPageTransitionCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call =
        reinterpret_cast<void (*)(const Ark_Int32 resourceId, Ark_RouteType type, const Ark_Float64 progress)>(
            thisDeserializer.readPointerOrDefault(
                reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_PageTransitionCallback))));
    thisDeserializer.readPointer();
    Ark_RouteType type = static_cast<Ark_RouteType>(thisDeserializer.readInt32());
    Ark_Float64 progress = thisDeserializer.readFloat64();
    _call(_resourceId, type, progress);
}
void deserializeAndCallSyncPageTransitionCallback(
    Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void (*)(
        Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_RouteType type, const Ark_Float64 progress)>(
        thisDeserializer.readPointerOrDefault(
            reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_PageTransitionCallback))));
    Ark_RouteType type = static_cast<Ark_RouteType>(thisDeserializer.readInt32());
    Ark_Float64 progress = thisDeserializer.readFloat64();
    callSyncMethod(vmContext, resourceId, type, progress);
}
void deserializeAndCallPasteButtonCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_ClickEvent event, Ark_PasteButtonOnClickResult result, const Opt_BusinessError error)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_PasteButtonCallback))));
    thisDeserializer.readPointer();
    Ark_ClickEvent event = static_cast<Ark_ClickEvent>(ClickEvent_serializer::read(thisDeserializer));
    Ark_PasteButtonOnClickResult result = static_cast<Ark_PasteButtonOnClickResult>(thisDeserializer.readInt32());
    const auto errorTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_BusinessError errorTmpBuf = {};
    errorTmpBuf.tag = errorTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((errorTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED)) {
        errorTmpBuf.value = static_cast<Ark_BusinessError>(BusinessError_serializer::read(thisDeserializer));
    }
    Opt_BusinessError error = errorTmpBuf;
    _call(_resourceId, event, result, error);
}
void deserializeAndCallSyncPasteButtonCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_ClickEvent event, Ark_PasteButtonOnClickResult result, const Opt_BusinessError error)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_PasteButtonCallback))));
    Ark_ClickEvent event = static_cast<Ark_ClickEvent>(ClickEvent_serializer::read(thisDeserializer));
    Ark_PasteButtonOnClickResult result = static_cast<Ark_PasteButtonOnClickResult>(thisDeserializer.readInt32());
    const auto errorTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_BusinessError errorTmpBuf = {};
    errorTmpBuf.tag = errorTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((errorTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED)) {
        errorTmpBuf.value = static_cast<Ark_BusinessError>(BusinessError_serializer::read(thisDeserializer));
    }
    Opt_BusinessError error = errorTmpBuf;
    callSyncMethod(vmContext, resourceId, event, result, error);
}
void deserializeAndCallPasteEventCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_PasteEvent event)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_PasteEventCallback))));
    thisDeserializer.readPointer();
    const auto eventTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_PasteEvent eventTmpBuf = {};
    eventTmpBuf.tag = eventTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((eventTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED)) {
        eventTmpBuf.value = PasteEvent_serializer::read(thisDeserializer);
    }
    Opt_PasteEvent event = eventTmpBuf;
    _call(_resourceId, event);
}
void deserializeAndCallSyncPasteEventCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_PasteEvent event)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_PasteEventCallback))));
    const auto eventTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_PasteEvent eventTmpBuf = {};
    eventTmpBuf.tag = eventTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((eventTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED)) {
        eventTmpBuf.value = PasteEvent_serializer::read(thisDeserializer);
    }
    Opt_PasteEvent event = eventTmpBuf;
    callSyncMethod(vmContext, resourceId, event);
}
void deserializeAndCallPluginErrorCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_PluginErrorData info)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_PluginErrorCallback))));
    thisDeserializer.readPointer();
    Ark_PluginErrorData info = PluginErrorData_serializer::read(thisDeserializer);
    _call(_resourceId, info);
}
void deserializeAndCallSyncPluginErrorCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_PluginErrorData info)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_PluginErrorCallback))));
    Ark_PluginErrorData info = PluginErrorData_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, info);
}
void deserializeAndCallPopupStateChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_PopupStateChangeParam event)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_PopupStateChangeCallback))));
    thisDeserializer.readPointer();
    Ark_PopupStateChangeParam event = PopupStateChangeParam_serializer::read(thisDeserializer);
    _call(_resourceId, event);
}
void deserializeAndCallSyncPopupStateChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_PopupStateChangeParam event)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_PopupStateChangeCallback))));
    Ark_PopupStateChangeParam event = PopupStateChangeParam_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, event);
}
void deserializeAndCallProgressModifierBuilder(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Ark_ProgressConfiguration config, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_ProgressModifierBuilder))));
    thisDeserializer.readPointer();
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_ProgressConfiguration config = ProgressConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Pointer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Pointer_Void))))};
    _call(_resourceId, parentNode, config, continuationResult);
}
void deserializeAndCallSyncProgressModifierBuilder(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Ark_ProgressConfiguration config, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_ProgressModifierBuilder))));
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_ProgressConfiguration config = ProgressConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Pointer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Pointer_Void))))};
    callSyncMethod(vmContext, resourceId, parentNode, config, continuationResult);
}
void deserializeAndCallRadioModifierBuilder(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Ark_RadioConfiguration config, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_RadioModifierBuilder))));
    thisDeserializer.readPointer();
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_RadioConfiguration config = RadioConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Pointer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Pointer_Void))))};
    _call(_resourceId, parentNode, config, continuationResult);
}
void deserializeAndCallSyncRadioModifierBuilder(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Ark_RadioConfiguration config, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_RadioModifierBuilder))));
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_RadioConfiguration config = RadioConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Pointer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Pointer_Void))))};
    callSyncMethod(vmContext, resourceId, parentNode, config, continuationResult);
}
void deserializeAndCallRatingModifierBuilder(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Ark_RatingConfiguration config, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_RatingModifierBuilder))));
    thisDeserializer.readPointer();
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_RatingConfiguration config = RatingConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Pointer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Pointer_Void))))};
    _call(_resourceId, parentNode, config, continuationResult);
}
void deserializeAndCallSyncRatingModifierBuilder(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Ark_RatingConfiguration config, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_RatingModifierBuilder))));
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_RatingConfiguration config = RatingConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Pointer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Pointer_Void))))};
    callSyncMethod(vmContext, resourceId, parentNode, config, continuationResult);
}
void deserializeAndCallRestrictedWorker_onerror_Callback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_ErrorEvent ev)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_RestrictedWorker_onerror_Callback))));
    thisDeserializer.readPointer();
    Ark_ErrorEvent ev = ErrorEvent_serializer::read(thisDeserializer);
    _call(_resourceId, ev);
}
void deserializeAndCallSyncRestrictedWorker_onerror_Callback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_ErrorEvent ev)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_RestrictedWorker_onerror_Callback))));
    Ark_ErrorEvent ev = ErrorEvent_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, ev);
}
void deserializeAndCallRestrictedWorker_onexit_Callback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number code)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_RestrictedWorker_onexit_Callback))));
    thisDeserializer.readPointer();
    Ark_Number code = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _call(_resourceId, code);
}
void deserializeAndCallSyncRestrictedWorker_onexit_Callback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number code)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_RestrictedWorker_onexit_Callback))));
    Ark_Number code = static_cast<Ark_Number>(thisDeserializer.readNumber());
    callSyncMethod(vmContext, resourceId, code);
}
void deserializeAndCallRestrictedWorker_onmessage_Callback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_MessageEvents event)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_RestrictedWorker_onmessage_Callback))));
    thisDeserializer.readPointer();
    Ark_MessageEvents event = MessageEvents_serializer::read(thisDeserializer);
    _call(_resourceId, event);
}
void deserializeAndCallSyncRestrictedWorker_onmessage_Callback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_MessageEvents event)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_RestrictedWorker_onmessage_Callback))));
    Ark_MessageEvents event = MessageEvents_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, event);
}
void deserializeAndCallReuseIdCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Callback_String_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_ReuseIdCallback))));
    thisDeserializer.readPointer();
    Callback_String_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_String breakpoints)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_String_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_String breakpoints)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_String_Void))))};
    _call(_resourceId, continuationResult);
}
void deserializeAndCallSyncReuseIdCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Callback_String_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_ReuseIdCallback))));
    Callback_String_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_String breakpoints)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_String_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_String breakpoints)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_String_Void))))};
    callSyncMethod(vmContext, resourceId, continuationResult);
}
void deserializeAndCallRouterFinishCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_RouterFinishCallback))));
    thisDeserializer.readPointer();
    Ark_NativePointer value = thisDeserializer.readPointer();
    _call(_resourceId, value);
}
void deserializeAndCallSyncRouterFinishCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_RouterFinishCallback))));
    Ark_NativePointer value = thisDeserializer.readPointer();
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallSaveButtonCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_ClickEvent event, Ark_SaveButtonOnClickResult result, const Opt_BusinessError error)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_SaveButtonCallback))));
    thisDeserializer.readPointer();
    Ark_ClickEvent event = static_cast<Ark_ClickEvent>(ClickEvent_serializer::read(thisDeserializer));
    Ark_SaveButtonOnClickResult result = static_cast<Ark_SaveButtonOnClickResult>(thisDeserializer.readInt32());
    const auto errorTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_BusinessError errorTmpBuf = {};
    errorTmpBuf.tag = errorTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((errorTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED)) {
        errorTmpBuf.value = static_cast<Ark_BusinessError>(BusinessError_serializer::read(thisDeserializer));
    }
    Opt_BusinessError error = errorTmpBuf;
    _call(_resourceId, event, result, error);
}
void deserializeAndCallSyncSaveButtonCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_ClickEvent event, Ark_SaveButtonOnClickResult result, const Opt_BusinessError error)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_SaveButtonCallback))));
    Ark_ClickEvent event = static_cast<Ark_ClickEvent>(ClickEvent_serializer::read(thisDeserializer));
    Ark_SaveButtonOnClickResult result = static_cast<Ark_SaveButtonOnClickResult>(thisDeserializer.readInt32());
    const auto errorTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_BusinessError errorTmpBuf = {};
    errorTmpBuf.tag = errorTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((errorTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED)) {
        errorTmpBuf.value = static_cast<Ark_BusinessError>(BusinessError_serializer::read(thisDeserializer));
    }
    Opt_BusinessError error = errorTmpBuf;
    callSyncMethod(vmContext, resourceId, event, result, error);
}
void deserializeAndCallScrollOnScrollCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Float64 xOffset, const Ark_Float64 yOffset, Ark_ScrollState scrollState)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_ScrollOnScrollCallback))));
    thisDeserializer.readPointer();
    Ark_Float64 xOffset = thisDeserializer.readFloat64();
    Ark_Float64 yOffset = thisDeserializer.readFloat64();
    Ark_ScrollState scrollState = static_cast<Ark_ScrollState>(thisDeserializer.readInt32());
    _call(_resourceId, xOffset, yOffset, scrollState);
}
void deserializeAndCallSyncScrollOnScrollCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Float64 xOffset, const Ark_Float64 yOffset, Ark_ScrollState scrollState)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_ScrollOnScrollCallback))));
    Ark_Float64 xOffset = thisDeserializer.readFloat64();
    Ark_Float64 yOffset = thisDeserializer.readFloat64();
    Ark_ScrollState scrollState = static_cast<Ark_ScrollState>(thisDeserializer.readInt32());
    callSyncMethod(vmContext, resourceId, xOffset, yOffset, scrollState);
}
void deserializeAndCallScrollOnWillScrollCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Float64 xOffset, const Ark_Float64 yOffset, Ark_ScrollState scrollState, Ark_ScrollSource scrollSource, const Callback_Opt_OffsetResult_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_ScrollOnWillScrollCallback))));
    thisDeserializer.readPointer();
    Ark_Float64 xOffset = thisDeserializer.readFloat64();
    Ark_Float64 yOffset = thisDeserializer.readFloat64();
    Ark_ScrollState scrollState = static_cast<Ark_ScrollState>(thisDeserializer.readInt32());
    Ark_ScrollSource scrollSource = static_cast<Ark_ScrollSource>(thisDeserializer.readInt32());
    Callback_Opt_OffsetResult_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_OffsetResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Opt_OffsetResult_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_OffsetResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Opt_OffsetResult_Void))))};
    _call(_resourceId, xOffset, yOffset, scrollState, scrollSource, continuationResult);
}
void deserializeAndCallSyncScrollOnWillScrollCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Float64 xOffset, const Ark_Float64 yOffset, Ark_ScrollState scrollState, Ark_ScrollSource scrollSource, const Callback_Opt_OffsetResult_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_ScrollOnWillScrollCallback))));
    Ark_Float64 xOffset = thisDeserializer.readFloat64();
    Ark_Float64 yOffset = thisDeserializer.readFloat64();
    Ark_ScrollState scrollState = static_cast<Ark_ScrollState>(thisDeserializer.readInt32());
    Ark_ScrollSource scrollSource = static_cast<Ark_ScrollSource>(thisDeserializer.readInt32());
    Callback_Opt_OffsetResult_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_OffsetResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Opt_OffsetResult_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_OffsetResult value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Opt_OffsetResult_Void))))};
    callSyncMethod(vmContext, resourceId, xOffset, yOffset, scrollState, scrollSource, continuationResult);
}
void deserializeAndCallSearchSubmitCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_String searchContent, const Opt_SubmitEvent event)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_SearchSubmitCallback))));
    thisDeserializer.readPointer();
    Ark_String searchContent = static_cast<Ark_String>(thisDeserializer.readString());
    const auto eventTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_SubmitEvent eventTmpBuf = {};
    eventTmpBuf.tag = eventTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((eventTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED)) {
        eventTmpBuf.value = static_cast<Ark_SubmitEvent>(SubmitEvent_serializer::read(thisDeserializer));
    }
    Opt_SubmitEvent event = eventTmpBuf;
    _call(_resourceId, searchContent, event);
}
void deserializeAndCallSyncSearchSubmitCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_String searchContent, const Opt_SubmitEvent event)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_SearchSubmitCallback))));
    Ark_String searchContent = static_cast<Ark_String>(thisDeserializer.readString());
    const auto eventTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_SubmitEvent eventTmpBuf = {};
    eventTmpBuf.tag = eventTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((eventTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED)) {
        eventTmpBuf.value = static_cast<Ark_SubmitEvent>(SubmitEvent_serializer::read(thisDeserializer));
    }
    Opt_SubmitEvent event = eventTmpBuf;
    callSyncMethod(vmContext, resourceId, searchContent, event);
}
void deserializeAndCallSearchValueCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_String value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_SearchValueCallback))));
    thisDeserializer.readPointer();
    Ark_String value = static_cast<Ark_String>(thisDeserializer.readString());
    _call(_resourceId, value);
}
void deserializeAndCallSyncSearchValueCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_String value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_SearchValueCallback))));
    Ark_String value = static_cast<Ark_String>(thisDeserializer.readString());
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallShouldBuiltInRecognizerParallelWithCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_GestureRecognizer current, const Array_GestureRecognizer others, const Callback_GestureRecognizer_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_ShouldBuiltInRecognizerParallelWithCallback))));
    thisDeserializer.readPointer();
    Ark_GestureRecognizer current = static_cast<Ark_GestureRecognizer>(GestureRecognizer_serializer::read(thisDeserializer));
    const Ark_Int32 othersTmpBufLength = thisDeserializer.readInt32();
    Array_GestureRecognizer othersTmpBuf = {};
    thisDeserializer.resizeArray<std::decay<decltype(othersTmpBuf)>::type,
        std::decay<decltype(*othersTmpBuf.array)>::type>(&othersTmpBuf, othersTmpBufLength);
    for (int othersTmpBufBufCounterI = 0; othersTmpBufBufCounterI < othersTmpBufLength; othersTmpBufBufCounterI++) {
        othersTmpBuf.array[othersTmpBufBufCounterI] = static_cast<Ark_GestureRecognizer>(GestureRecognizer_serializer::read(thisDeserializer));
    }
    Array_GestureRecognizer others = othersTmpBuf;
    Callback_GestureRecognizer_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_GestureRecognizer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_GestureRecognizer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_GestureRecognizer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_GestureRecognizer_Void))))};
    _call(_resourceId, current, others, continuationResult);
}
void deserializeAndCallSyncShouldBuiltInRecognizerParallelWithCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_GestureRecognizer current, const Array_GestureRecognizer others, const Callback_GestureRecognizer_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_ShouldBuiltInRecognizerParallelWithCallback))));
    Ark_GestureRecognizer current = static_cast<Ark_GestureRecognizer>(GestureRecognizer_serializer::read(thisDeserializer));
    const Ark_Int32 othersTmpBufLength = thisDeserializer.readInt32();
    Array_GestureRecognizer othersTmpBuf = {};
    thisDeserializer.resizeArray<std::decay<decltype(othersTmpBuf)>::type,
        std::decay<decltype(*othersTmpBuf.array)>::type>(&othersTmpBuf, othersTmpBufLength);
    for (int othersTmpBufBufCounterI = 0; othersTmpBufBufCounterI < othersTmpBufLength; othersTmpBufBufCounterI++) {
        othersTmpBuf.array[othersTmpBufBufCounterI] = static_cast<Ark_GestureRecognizer>(GestureRecognizer_serializer::read(thisDeserializer));
    }
    Array_GestureRecognizer others = othersTmpBuf;
    Callback_GestureRecognizer_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_GestureRecognizer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_GestureRecognizer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_GestureRecognizer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_GestureRecognizer_Void))))};
    callSyncMethod(vmContext, resourceId, current, others, continuationResult);
}
void deserializeAndCallSizeChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_SizeOptions oldValue, const Ark_SizeOptions newValue)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_SizeChangeCallback))));
    thisDeserializer.readPointer();
    Ark_SizeOptions oldValue = SizeOptions_serializer::read(thisDeserializer);
    Ark_SizeOptions newValue = SizeOptions_serializer::read(thisDeserializer);
    _call(_resourceId, oldValue, newValue);
}
void deserializeAndCallSyncSizeChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_SizeOptions oldValue, const Ark_SizeOptions newValue)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_SizeChangeCallback))));
    Ark_SizeOptions oldValue = SizeOptions_serializer::read(thisDeserializer);
    Ark_SizeOptions newValue = SizeOptions_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, oldValue, newValue);
}
void deserializeAndCallSliderModifierBuilder(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Ark_SliderConfiguration config, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_SliderModifierBuilder))));
    thisDeserializer.readPointer();
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_SliderConfiguration config = SliderConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Pointer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Pointer_Void))))};
    _call(_resourceId, parentNode, config, continuationResult);
}
void deserializeAndCallSyncSliderModifierBuilder(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Ark_SliderConfiguration config, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_SliderModifierBuilder))));
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_SliderConfiguration config = SliderConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Pointer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Pointer_Void))))};
    callSyncMethod(vmContext, resourceId, parentNode, config, continuationResult);
}
void deserializeAndCallSliderTriggerChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Float64 value, Ark_SliderChangeMode mode)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_SliderTriggerChangeCallback))));
    thisDeserializer.readPointer();
    Ark_Float64 value = thisDeserializer.readFloat64();
    Ark_SliderChangeMode mode = static_cast<Ark_SliderChangeMode>(thisDeserializer.readInt32());
    _call(_resourceId, value, mode);
}
void deserializeAndCallSyncSliderTriggerChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Float64 value, Ark_SliderChangeMode mode)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_SliderTriggerChangeCallback))));
    Ark_Float64 value = thisDeserializer.readFloat64();
    Ark_SliderChangeMode mode = static_cast<Ark_SliderChangeMode>(thisDeserializer.readInt32());
    callSyncMethod(vmContext, resourceId, value, mode);
}
void deserializeAndCallStyledStringMarshallCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_UserDataSpan marshallableVal, const Callback_Buffer_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_StyledStringMarshallCallback))));
    thisDeserializer.readPointer();
    Ark_UserDataSpan marshallableVal = static_cast<Ark_UserDataSpan>(thisDeserializer.readObject());
    Callback_Buffer_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Buffer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Buffer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Buffer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Buffer_Void))))};
    _call(_resourceId, marshallableVal, continuationResult);
}
void deserializeAndCallSyncStyledStringMarshallCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_UserDataSpan marshallableVal, const Callback_Buffer_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_StyledStringMarshallCallback))));
    Ark_UserDataSpan marshallableVal = static_cast<Ark_UserDataSpan>(thisDeserializer.readObject());
    Callback_Buffer_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Buffer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Buffer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Buffer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Buffer_Void))))};
    callSyncMethod(vmContext, resourceId, marshallableVal, continuationResult);
}
void deserializeAndCallStyledStringUnmarshallCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Buffer buf, const Callback_StyledStringMarshallingValue_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_StyledStringUnmarshallCallback))));
    thisDeserializer.readPointer();
    Ark_Buffer buf = static_cast<Ark_Buffer>(thisDeserializer.readBuffer());
    Callback_StyledStringMarshallingValue_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_UserDataSpan value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_StyledStringMarshallingValue_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_UserDataSpan value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_StyledStringMarshallingValue_Void))))};
    _call(_resourceId, buf, continuationResult);
}
void deserializeAndCallSyncStyledStringUnmarshallCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Buffer buf, const Callback_StyledStringMarshallingValue_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_StyledStringUnmarshallCallback))));
    Ark_Buffer buf = static_cast<Ark_Buffer>(thisDeserializer.readBuffer());
    Callback_StyledStringMarshallingValue_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_UserDataSpan value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_StyledStringMarshallingValue_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_UserDataSpan value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_StyledStringMarshallingValue_Void))))};
    callSyncMethod(vmContext, resourceId, buf, continuationResult);
}
void deserializeAndCallSubmitCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_EnterKeyType enterKey, const Ark_SubmitEvent event)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_SubmitCallback))));
    thisDeserializer.readPointer();
    Ark_EnterKeyType enterKey = static_cast<Ark_EnterKeyType>(thisDeserializer.readInt32());
    Ark_SubmitEvent event = static_cast<Ark_SubmitEvent>(SubmitEvent_serializer::read(thisDeserializer));
    _call(_resourceId, enterKey, event);
}
void deserializeAndCallSyncSubmitCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_EnterKeyType enterKey, const Ark_SubmitEvent event)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_SubmitCallback))));
    Ark_EnterKeyType enterKey = static_cast<Ark_EnterKeyType>(thisDeserializer.readInt32());
    Ark_SubmitEvent event = static_cast<Ark_SubmitEvent>(SubmitEvent_serializer::read(thisDeserializer));
    callSyncMethod(vmContext, resourceId, enterKey, event);
}
void deserializeAndCallTabsCustomContentTransitionCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Int32 from, const Ark_Int32 to, const Callback_Opt_TabContentAnimatedTransition_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_TabsCustomContentTransitionCallback))));
    thisDeserializer.readPointer();
    Ark_Int32 from = thisDeserializer.readInt32();
    Ark_Int32 to = thisDeserializer.readInt32();
    Callback_Opt_TabContentAnimatedTransition_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_TabContentAnimatedTransition value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Opt_TabContentAnimatedTransition_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_TabContentAnimatedTransition value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Opt_TabContentAnimatedTransition_Void))))};
    _call(_resourceId, from, to, continuationResult);
}
void deserializeAndCallSyncTabsCustomContentTransitionCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int32 from, const Ark_Int32 to, const Callback_Opt_TabContentAnimatedTransition_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_TabsCustomContentTransitionCallback))));
    Ark_Int32 from = thisDeserializer.readInt32();
    Ark_Int32 to = thisDeserializer.readInt32();
    Callback_Opt_TabContentAnimatedTransition_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_TabContentAnimatedTransition value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Opt_TabContentAnimatedTransition_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_TabContentAnimatedTransition value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Opt_TabContentAnimatedTransition_Void))))};
    callSyncMethod(vmContext, resourceId, from, to, continuationResult);
}
void deserializeAndCallTextAreaSubmitCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, Ark_EnterKeyType enterKeyType, const Opt_SubmitEvent event)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_TextAreaSubmitCallback))));
    thisDeserializer.readPointer();
    Ark_EnterKeyType enterKeyType = static_cast<Ark_EnterKeyType>(thisDeserializer.readInt32());
    const auto eventTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_SubmitEvent eventTmpBuf = {};
    eventTmpBuf.tag = eventTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((eventTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED)) {
        eventTmpBuf.value = static_cast<Ark_SubmitEvent>(SubmitEvent_serializer::read(thisDeserializer));
    }
    Opt_SubmitEvent event = eventTmpBuf;
    _call(_resourceId, enterKeyType, event);
}
void deserializeAndCallSyncTextAreaSubmitCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, Ark_EnterKeyType enterKeyType, const Opt_SubmitEvent event)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_TextAreaSubmitCallback))));
    Ark_EnterKeyType enterKeyType = static_cast<Ark_EnterKeyType>(thisDeserializer.readInt32());
    const auto eventTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_SubmitEvent eventTmpBuf = {};
    eventTmpBuf.tag = eventTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((eventTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED)) {
        eventTmpBuf.value = static_cast<Ark_SubmitEvent>(SubmitEvent_serializer::read(thisDeserializer));
    }
    Opt_SubmitEvent event = eventTmpBuf;
    callSyncMethod(vmContext, resourceId, enterKeyType, event);
}
void deserializeAndCallTextClockModifierBuilder(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Ark_TextClockConfiguration config, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_TextClockModifierBuilder))));
    thisDeserializer.readPointer();
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_TextClockConfiguration config = TextClockConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Pointer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Pointer_Void))))};
    _call(_resourceId, parentNode, config, continuationResult);
}
void deserializeAndCallSyncTextClockModifierBuilder(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Ark_TextClockConfiguration config, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_TextClockModifierBuilder))));
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_TextClockConfiguration config = TextClockConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Pointer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Pointer_Void))))};
    callSyncMethod(vmContext, resourceId, parentNode, config, continuationResult);
}
void deserializeAndCallTextFieldValueCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_ResourceStr value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_TextFieldValueCallback))));
    thisDeserializer.readPointer();
    const Ark_Int8 valueTmpBufUnionSelector = thisDeserializer.readInt8();
    Ark_ResourceStr valueTmpBuf = {};
    valueTmpBuf.selector = valueTmpBufUnionSelector;
    if (valueTmpBufUnionSelector == 0) {
        valueTmpBuf.selector = 0;
        valueTmpBuf.value0 = static_cast<Ark_String>(thisDeserializer.readString());
    } else if (valueTmpBufUnionSelector == 1) {
        valueTmpBuf.selector = 1;
        valueTmpBuf.value1 = Resource_serializer::read(thisDeserializer);
    } else {
        INTEROP_FATAL("One of the branches for valueTmpBuf has to be chosen through deserialisation.");
    }
    Ark_ResourceStr value = static_cast<Ark_ResourceStr>(valueTmpBuf);
    _call(_resourceId, value);
}
void deserializeAndCallSyncTextFieldValueCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_ResourceStr value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_TextFieldValueCallback))));
    const Ark_Int8 valueTmpBufUnionSelector = thisDeserializer.readInt8();
    Ark_ResourceStr valueTmpBuf = {};
    valueTmpBuf.selector = valueTmpBufUnionSelector;
    if (valueTmpBufUnionSelector == 0) {
        valueTmpBuf.selector = 0;
        valueTmpBuf.value0 = static_cast<Ark_String>(thisDeserializer.readString());
    } else if (valueTmpBufUnionSelector == 1) {
        valueTmpBuf.selector = 1;
        valueTmpBuf.value1 = Resource_serializer::read(thisDeserializer);
    } else {
        INTEROP_FATAL("One of the branches for valueTmpBuf has to be chosen through deserialisation.");
    }
    Ark_ResourceStr value = static_cast<Ark_ResourceStr>(valueTmpBuf);
    callSyncMethod(vmContext, resourceId, value);
}
void deserializeAndCallTextPickerEnterSelectedAreaCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Union_String_Array_String value, const Ark_Union_I32_Array_I32 index)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_TextPickerEnterSelectedAreaCallback))));
    thisDeserializer.readPointer();
    const Ark_Int8 valueTmpBufUnionSelector = thisDeserializer.readInt8();
    Ark_Union_String_Array_String valueTmpBuf = {};
    valueTmpBuf.selector = valueTmpBufUnionSelector;
    if (valueTmpBufUnionSelector == 0) {
        valueTmpBuf.selector = 0;
        valueTmpBuf.value0 = static_cast<Ark_String>(thisDeserializer.readString());
    } else if (valueTmpBufUnionSelector == 1) {
        valueTmpBuf.selector = 1;
        const Ark_Int32 valueTmpBufBufULength = thisDeserializer.readInt32();
        Array_String valueTmpBufBufU = {};
        thisDeserializer.resizeArray<std::decay<decltype(valueTmpBufBufU)>::type,
        std::decay<decltype(*valueTmpBufBufU.array)>::type>(&valueTmpBufBufU, valueTmpBufBufULength);
        for (int valueTmpBufBufUBufCounterI = 0; valueTmpBufBufUBufCounterI < valueTmpBufBufULength; valueTmpBufBufUBufCounterI++) {
            valueTmpBufBufU.array[valueTmpBufBufUBufCounterI] = static_cast<Ark_String>(thisDeserializer.readString());
        }
        valueTmpBuf.value1 = valueTmpBufBufU;
    } else {
        INTEROP_FATAL("One of the branches for valueTmpBuf has to be chosen through deserialisation.");
    }
    Ark_Union_String_Array_String value = static_cast<Ark_Union_String_Array_String>(valueTmpBuf);
    const Ark_Int8 indexTmpBufUnionSelector = thisDeserializer.readInt8();
    Ark_Union_I32_Array_I32 indexTmpBuf = {};
    indexTmpBuf.selector = indexTmpBufUnionSelector;
    if (indexTmpBufUnionSelector == 0) {
        indexTmpBuf.selector = 0;
        indexTmpBuf.value0 = thisDeserializer.readInt32();
    } else if (indexTmpBufUnionSelector == 1) {
        indexTmpBuf.selector = 1;
        const Ark_Int32 indexTmpBufBufULength = thisDeserializer.readInt32();
        Array_Int32 indexTmpBufBufU = {};
        thisDeserializer.resizeArray<std::decay<decltype(indexTmpBufBufU)>::type,
        std::decay<decltype(*indexTmpBufBufU.array)>::type>(&indexTmpBufBufU, indexTmpBufBufULength);
        for (int indexTmpBufBufUBufCounterI = 0; indexTmpBufBufUBufCounterI < indexTmpBufBufULength; indexTmpBufBufUBufCounterI++) {
            indexTmpBufBufU.array[indexTmpBufBufUBufCounterI] = thisDeserializer.readInt32();
        }
        indexTmpBuf.value1 = indexTmpBufBufU;
    } else {
        INTEROP_FATAL("One of the branches for indexTmpBuf has to be chosen through deserialisation.");
    }
    Ark_Union_I32_Array_I32 index = static_cast<Ark_Union_I32_Array_I32>(indexTmpBuf);
    _call(_resourceId, value, index);
}
void deserializeAndCallSyncTextPickerEnterSelectedAreaCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Union_String_Array_String value, const Ark_Union_I32_Array_I32 index)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_TextPickerEnterSelectedAreaCallback))));
    const Ark_Int8 valueTmpBufUnionSelector = thisDeserializer.readInt8();
    Ark_Union_String_Array_String valueTmpBuf = {};
    valueTmpBuf.selector = valueTmpBufUnionSelector;
    if (valueTmpBufUnionSelector == 0) {
        valueTmpBuf.selector = 0;
        valueTmpBuf.value0 = static_cast<Ark_String>(thisDeserializer.readString());
    } else if (valueTmpBufUnionSelector == 1) {
        valueTmpBuf.selector = 1;
        const Ark_Int32 valueTmpBufBufULength = thisDeserializer.readInt32();
        Array_String valueTmpBufBufU = {};
        thisDeserializer.resizeArray<std::decay<decltype(valueTmpBufBufU)>::type,
        std::decay<decltype(*valueTmpBufBufU.array)>::type>(&valueTmpBufBufU, valueTmpBufBufULength);
        for (int valueTmpBufBufUBufCounterI = 0; valueTmpBufBufUBufCounterI < valueTmpBufBufULength; valueTmpBufBufUBufCounterI++) {
            valueTmpBufBufU.array[valueTmpBufBufUBufCounterI] = static_cast<Ark_String>(thisDeserializer.readString());
        }
        valueTmpBuf.value1 = valueTmpBufBufU;
    } else {
        INTEROP_FATAL("One of the branches for valueTmpBuf has to be chosen through deserialisation.");
    }
    Ark_Union_String_Array_String value = static_cast<Ark_Union_String_Array_String>(valueTmpBuf);
    const Ark_Int8 indexTmpBufUnionSelector = thisDeserializer.readInt8();
    Ark_Union_I32_Array_I32 indexTmpBuf = {};
    indexTmpBuf.selector = indexTmpBufUnionSelector;
    if (indexTmpBufUnionSelector == 0) {
        indexTmpBuf.selector = 0;
        indexTmpBuf.value0 = thisDeserializer.readInt32();
    } else if (indexTmpBufUnionSelector == 1) {
        indexTmpBuf.selector = 1;
        const Ark_Int32 indexTmpBufBufULength = thisDeserializer.readInt32();
        Array_Int32 indexTmpBufBufU = {};
        thisDeserializer.resizeArray<std::decay<decltype(indexTmpBufBufU)>::type,
        std::decay<decltype(*indexTmpBufBufU.array)>::type>(&indexTmpBufBufU, indexTmpBufBufULength);
        for (int indexTmpBufBufUBufCounterI = 0; indexTmpBufBufUBufCounterI < indexTmpBufBufULength; indexTmpBufBufUBufCounterI++) {
            indexTmpBufBufU.array[indexTmpBufBufUBufCounterI] = thisDeserializer.readInt32();
        }
        indexTmpBuf.value1 = indexTmpBufBufU;
    } else {
        INTEROP_FATAL("One of the branches for indexTmpBuf has to be chosen through deserialisation.");
    }
    Ark_Union_I32_Array_I32 index = static_cast<Ark_Union_I32_Array_I32>(indexTmpBuf);
    callSyncMethod(vmContext, resourceId, value, index);
}
void deserializeAndCallTextPickerScrollStopCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Union_String_Array_String value, const Ark_Union_I32_Array_I32 index)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_TextPickerScrollStopCallback))));
    thisDeserializer.readPointer();
    const Ark_Int8 valueTmpBufUnionSelector = thisDeserializer.readInt8();
    Ark_Union_String_Array_String valueTmpBuf = {};
    valueTmpBuf.selector = valueTmpBufUnionSelector;
    if (valueTmpBufUnionSelector == 0) {
        valueTmpBuf.selector = 0;
        valueTmpBuf.value0 = static_cast<Ark_String>(thisDeserializer.readString());
    } else if (valueTmpBufUnionSelector == 1) {
        valueTmpBuf.selector = 1;
        const Ark_Int32 valueTmpBufBufULength = thisDeserializer.readInt32();
        Array_String valueTmpBufBufU = {};
        thisDeserializer.resizeArray<std::decay<decltype(valueTmpBufBufU)>::type,
        std::decay<decltype(*valueTmpBufBufU.array)>::type>(&valueTmpBufBufU, valueTmpBufBufULength);
        for (int valueTmpBufBufUBufCounterI = 0; valueTmpBufBufUBufCounterI < valueTmpBufBufULength; valueTmpBufBufUBufCounterI++) {
            valueTmpBufBufU.array[valueTmpBufBufUBufCounterI] = static_cast<Ark_String>(thisDeserializer.readString());
        }
        valueTmpBuf.value1 = valueTmpBufBufU;
    } else {
        INTEROP_FATAL("One of the branches for valueTmpBuf has to be chosen through deserialisation.");
    }
    Ark_Union_String_Array_String value = static_cast<Ark_Union_String_Array_String>(valueTmpBuf);
    const Ark_Int8 indexTmpBufUnionSelector = thisDeserializer.readInt8();
    Ark_Union_I32_Array_I32 indexTmpBuf = {};
    indexTmpBuf.selector = indexTmpBufUnionSelector;
    if (indexTmpBufUnionSelector == 0) {
        indexTmpBuf.selector = 0;
        indexTmpBuf.value0 = thisDeserializer.readInt32();
    } else if (indexTmpBufUnionSelector == 1) {
        indexTmpBuf.selector = 1;
        const Ark_Int32 indexTmpBufBufULength = thisDeserializer.readInt32();
        Array_Int32 indexTmpBufBufU = {};
        thisDeserializer.resizeArray<std::decay<decltype(indexTmpBufBufU)>::type,
        std::decay<decltype(*indexTmpBufBufU.array)>::type>(&indexTmpBufBufU, indexTmpBufBufULength);
        for (int indexTmpBufBufUBufCounterI = 0; indexTmpBufBufUBufCounterI < indexTmpBufBufULength; indexTmpBufBufUBufCounterI++) {
            indexTmpBufBufU.array[indexTmpBufBufUBufCounterI] = thisDeserializer.readInt32();
        }
        indexTmpBuf.value1 = indexTmpBufBufU;
    } else {
        INTEROP_FATAL("One of the branches for indexTmpBuf has to be chosen through deserialisation.");
    }
    Ark_Union_I32_Array_I32 index = static_cast<Ark_Union_I32_Array_I32>(indexTmpBuf);
    _call(_resourceId, value, index);
}
void deserializeAndCallSyncTextPickerScrollStopCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Union_String_Array_String value, const Ark_Union_I32_Array_I32 index)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_TextPickerScrollStopCallback))));
    const Ark_Int8 valueTmpBufUnionSelector = thisDeserializer.readInt8();
    Ark_Union_String_Array_String valueTmpBuf = {};
    valueTmpBuf.selector = valueTmpBufUnionSelector;
    if (valueTmpBufUnionSelector == 0) {
        valueTmpBuf.selector = 0;
        valueTmpBuf.value0 = static_cast<Ark_String>(thisDeserializer.readString());
    } else if (valueTmpBufUnionSelector == 1) {
        valueTmpBuf.selector = 1;
        const Ark_Int32 valueTmpBufBufULength = thisDeserializer.readInt32();
        Array_String valueTmpBufBufU = {};
        thisDeserializer.resizeArray<std::decay<decltype(valueTmpBufBufU)>::type,
        std::decay<decltype(*valueTmpBufBufU.array)>::type>(&valueTmpBufBufU, valueTmpBufBufULength);
        for (int valueTmpBufBufUBufCounterI = 0; valueTmpBufBufUBufCounterI < valueTmpBufBufULength; valueTmpBufBufUBufCounterI++) {
            valueTmpBufBufU.array[valueTmpBufBufUBufCounterI] = static_cast<Ark_String>(thisDeserializer.readString());
        }
        valueTmpBuf.value1 = valueTmpBufBufU;
    } else {
        INTEROP_FATAL("One of the branches for valueTmpBuf has to be chosen through deserialisation.");
    }
    Ark_Union_String_Array_String value = static_cast<Ark_Union_String_Array_String>(valueTmpBuf);
    const Ark_Int8 indexTmpBufUnionSelector = thisDeserializer.readInt8();
    Ark_Union_I32_Array_I32 indexTmpBuf = {};
    indexTmpBuf.selector = indexTmpBufUnionSelector;
    if (indexTmpBufUnionSelector == 0) {
        indexTmpBuf.selector = 0;
        indexTmpBuf.value0 = thisDeserializer.readInt32();
    } else if (indexTmpBufUnionSelector == 1) {
        indexTmpBuf.selector = 1;
        const Ark_Int32 indexTmpBufBufULength = thisDeserializer.readInt32();
        Array_Int32 indexTmpBufBufU = {};
        thisDeserializer.resizeArray<std::decay<decltype(indexTmpBufBufU)>::type,
        std::decay<decltype(*indexTmpBufBufU.array)>::type>(&indexTmpBufBufU, indexTmpBufBufULength);
        for (int indexTmpBufBufUBufCounterI = 0; indexTmpBufBufUBufCounterI < indexTmpBufBufULength; indexTmpBufBufUBufCounterI++) {
            indexTmpBufBufU.array[indexTmpBufBufUBufCounterI] = thisDeserializer.readInt32();
        }
        indexTmpBuf.value1 = indexTmpBufBufU;
    } else {
        INTEROP_FATAL("One of the branches for indexTmpBuf has to be chosen through deserialisation.");
    }
    Ark_Union_I32_Array_I32 index = static_cast<Ark_Union_I32_Array_I32>(indexTmpBuf);
    callSyncMethod(vmContext, resourceId, value, index);
}
void deserializeAndCallTextTimerModifierBuilder(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Ark_TextTimerConfiguration config, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_TextTimerModifierBuilder))));
    thisDeserializer.readPointer();
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_TextTimerConfiguration config = TextTimerConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Pointer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Pointer_Void))))};
    _call(_resourceId, parentNode, config, continuationResult);
}
void deserializeAndCallSyncTextTimerModifierBuilder(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Ark_TextTimerConfiguration config, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_TextTimerModifierBuilder))));
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_TextTimerConfiguration config = TextTimerConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Pointer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Pointer_Void))))};
    callSyncMethod(vmContext, resourceId, parentNode, config, continuationResult);
}
void deserializeAndCallTimerCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Int64 utc, const Ark_Int64 elapsedTime)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_TimerCallback))));
    thisDeserializer.readPointer();
    Ark_Int64 utc = thisDeserializer.readInt64();
    Ark_Int64 elapsedTime = thisDeserializer.readInt64();
    _call(_resourceId, utc, elapsedTime);
}
void deserializeAndCallSyncTimerCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int64 utc, const Ark_Int64 elapsedTime)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_TimerCallback))));
    Ark_Int64 utc = thisDeserializer.readInt64();
    Ark_Int64 elapsedTime = thisDeserializer.readInt64();
    callSyncMethod(vmContext, resourceId, utc, elapsedTime);
}
void deserializeAndCallToggleModifierBuilder(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Ark_ToggleConfiguration config, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_ToggleModifierBuilder))));
    thisDeserializer.readPointer();
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_ToggleConfiguration config = ToggleConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Pointer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Pointer_Void))))};
    _call(_resourceId, parentNode, config, continuationResult);
}
void deserializeAndCallSyncToggleModifierBuilder(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer parentNode, const Ark_ToggleConfiguration config, const Callback_Pointer_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_ToggleModifierBuilder))));
    Ark_NativePointer parentNode = thisDeserializer.readPointer();
    Ark_ToggleConfiguration config = ToggleConfiguration_serializer::read(thisDeserializer);
    Callback_Pointer_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Pointer_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NativePointer value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Pointer_Void))))};
    callSyncMethod(vmContext, resourceId, parentNode, config, continuationResult);
}
void deserializeAndCallTransitionFinishCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean transitionIn)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_TransitionFinishCallback))));
    thisDeserializer.readPointer();
    Ark_Boolean transitionIn = thisDeserializer.readBoolean();
    _call(_resourceId, transitionIn);
}
void deserializeAndCallSyncTransitionFinishCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean transitionIn)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_TransitionFinishCallback))));
    Ark_Boolean transitionIn = thisDeserializer.readBoolean();
    callSyncMethod(vmContext, resourceId, transitionIn);
}
void deserializeAndCallType_CommonMethod_onDragStart(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_DragEvent event, const Opt_String extraParams, const Callback_Union_CustomBuilder_DragItemInfo_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Type_CommonMethod_onDragStart))));
    thisDeserializer.readPointer();
    Ark_DragEvent event = static_cast<Ark_DragEvent>(DragEvent_serializer::read(thisDeserializer));
    const auto extraParamsTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_String extraParamsTmpBuf = {};
    extraParamsTmpBuf.tag = extraParamsTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((extraParamsTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED)) {
        extraParamsTmpBuf.value = static_cast<Ark_String>(thisDeserializer.readString());
    }
    Opt_String extraParams = extraParamsTmpBuf;
    Callback_Union_CustomBuilder_DragItemInfo_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Union_CustomBuilder_DragItemInfo value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Union_CustomBuilder_DragItemInfo_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Union_CustomBuilder_DragItemInfo value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Union_CustomBuilder_DragItemInfo_Void))))};
    _call(_resourceId, event, extraParams, continuationResult);
}
void deserializeAndCallSyncType_CommonMethod_onDragStart(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_DragEvent event, const Opt_String extraParams, const Callback_Union_CustomBuilder_DragItemInfo_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Type_CommonMethod_onDragStart))));
    Ark_DragEvent event = static_cast<Ark_DragEvent>(DragEvent_serializer::read(thisDeserializer));
    const auto extraParamsTmpBuf_runtimeType = static_cast<Ark_RuntimeType>(thisDeserializer.readInt8());
    Opt_String extraParamsTmpBuf = {};
    extraParamsTmpBuf.tag = extraParamsTmpBuf_runtimeType == INTEROP_RUNTIME_UNDEFINED ? INTEROP_TAG_UNDEFINED : INTEROP_TAG_OBJECT;
    if ((extraParamsTmpBuf_runtimeType) != (INTEROP_RUNTIME_UNDEFINED)) {
        extraParamsTmpBuf.value = static_cast<Ark_String>(thisDeserializer.readString());
    }
    Opt_String extraParams = extraParamsTmpBuf;
    Callback_Union_CustomBuilder_DragItemInfo_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Union_CustomBuilder_DragItemInfo value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Union_CustomBuilder_DragItemInfo_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Union_CustomBuilder_DragItemInfo value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Union_CustomBuilder_DragItemInfo_Void))))};
    callSyncMethod(vmContext, resourceId, event, extraParams, continuationResult);
}
void deserializeAndCallType_NavigationAttribute_customNavContentTransition(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_NavContentInfo from, const Ark_NavContentInfo to, Ark_NavigationOperation operation, const Callback_Opt_NavigationAnimatedTransition_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Type_NavigationAttribute_customNavContentTransition))));
    thisDeserializer.readPointer();
    Ark_NavContentInfo from = NavContentInfo_serializer::read(thisDeserializer);
    Ark_NavContentInfo to = NavContentInfo_serializer::read(thisDeserializer);
    Ark_NavigationOperation operation = static_cast<Ark_NavigationOperation>(thisDeserializer.readInt32());
    Callback_Opt_NavigationAnimatedTransition_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_NavigationAnimatedTransition value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Opt_NavigationAnimatedTransition_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_NavigationAnimatedTransition value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Opt_NavigationAnimatedTransition_Void))))};
    _call(_resourceId, from, to, operation, continuationResult);
}
void deserializeAndCallSyncType_NavigationAttribute_customNavContentTransition(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_NavContentInfo from, const Ark_NavContentInfo to, Ark_NavigationOperation operation, const Callback_Opt_NavigationAnimatedTransition_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Type_NavigationAttribute_customNavContentTransition))));
    Ark_NavContentInfo from = NavContentInfo_serializer::read(thisDeserializer);
    Ark_NavContentInfo to = NavContentInfo_serializer::read(thisDeserializer);
    Ark_NavigationOperation operation = static_cast<Ark_NavigationOperation>(thisDeserializer.readInt32());
    Callback_Opt_NavigationAnimatedTransition_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_NavigationAnimatedTransition value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Opt_NavigationAnimatedTransition_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_NavigationAnimatedTransition value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Opt_NavigationAnimatedTransition_Void))))};
    callSyncMethod(vmContext, resourceId, from, to, operation, continuationResult);
}
void deserializeAndCallType_WebAttribute_onInterceptRequest(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_OnInterceptRequestEvent value0, const Callback_Opt_WebResourceResponse_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Type_WebAttribute_onInterceptRequest))));
    thisDeserializer.readPointer();
    Ark_OnInterceptRequestEvent value0 = OnInterceptRequestEvent_serializer::read(thisDeserializer);
    Callback_Opt_WebResourceResponse_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_WebResourceResponse value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Opt_WebResourceResponse_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_WebResourceResponse value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Opt_WebResourceResponse_Void))))};
    _call(_resourceId, value0, continuationResult);
}
void deserializeAndCallSyncType_WebAttribute_onInterceptRequest(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_OnInterceptRequestEvent value0, const Callback_Opt_WebResourceResponse_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Type_WebAttribute_onInterceptRequest))));
    Ark_OnInterceptRequestEvent value0 = OnInterceptRequestEvent_serializer::read(thisDeserializer);
    Callback_Opt_WebResourceResponse_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Opt_WebResourceResponse value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_Opt_WebResourceResponse_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Opt_WebResourceResponse value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_Opt_WebResourceResponse_Void))))};
    callSyncMethod(vmContext, resourceId, value0, continuationResult);
}
void deserializeAndCallUpdateTransitionCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Number progress)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_UpdateTransitionCallback))));
    thisDeserializer.readPointer();
    Ark_Number progress = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _call(_resourceId, progress);
}
void deserializeAndCallSyncUpdateTransitionCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Number progress)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_UpdateTransitionCallback))));
    Ark_Number progress = static_cast<Ark_Number>(thisDeserializer.readNumber());
    callSyncMethod(vmContext, resourceId, progress);
}
void deserializeAndCallVisibleAreaChangeCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Boolean isExpanding, const Ark_Number currentRatio)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_VisibleAreaChangeCallback))));
    thisDeserializer.readPointer();
    Ark_Boolean isExpanding = thisDeserializer.readBoolean();
    Ark_Number currentRatio = static_cast<Ark_Number>(thisDeserializer.readNumber());
    _call(_resourceId, isExpanding, currentRatio);
}
void deserializeAndCallSyncVisibleAreaChangeCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Boolean isExpanding, const Ark_Number currentRatio)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_VisibleAreaChangeCallback))));
    Ark_Boolean isExpanding = thisDeserializer.readBoolean();
    Ark_Number currentRatio = static_cast<Ark_Number>(thisDeserializer.readNumber());
    callSyncMethod(vmContext, resourceId, isExpanding, currentRatio);
}
void deserializeAndCallVoidCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_VoidCallback))));
    thisDeserializer.readPointer();
    _call(_resourceId);
}
void deserializeAndCallSyncVoidCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_VoidCallback))));
    callSyncMethod(vmContext, resourceId);
}
void deserializeAndCallWebKeyboardCallback(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_WebKeyboardCallbackInfo keyboardCallbackInfo, const Callback_WebKeyboardOptions_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_WebKeyboardCallback))));
    thisDeserializer.readPointer();
    Ark_WebKeyboardCallbackInfo keyboardCallbackInfo = WebKeyboardCallbackInfo_serializer::read(thisDeserializer);
    Callback_WebKeyboardOptions_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_WebKeyboardOptions value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_WebKeyboardOptions_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_WebKeyboardOptions value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_WebKeyboardOptions_Void))))};
    _call(_resourceId, keyboardCallbackInfo, continuationResult);
}
void deserializeAndCallSyncWebKeyboardCallback(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_WebKeyboardCallbackInfo keyboardCallbackInfo, const Callback_WebKeyboardOptions_Void continuation)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_WebKeyboardCallback))));
    Ark_WebKeyboardCallbackInfo keyboardCallbackInfo = WebKeyboardCallbackInfo_serializer::read(thisDeserializer);
    Callback_WebKeyboardOptions_Void continuationResult = {thisDeserializer.readCallbackResource(), reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_WebKeyboardOptions value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_Callback_WebKeyboardOptions_Void)))), reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_WebKeyboardOptions value)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_Callback_WebKeyboardOptions_Void))))};
    callSyncMethod(vmContext, resourceId, keyboardCallbackInfo, continuationResult);
}
void deserializeAndCallWorkerEventListener(KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 _resourceId = thisDeserializer.readInt32();
    const auto _call = reinterpret_cast<void(*)(const Ark_Int32 resourceId, const Ark_Event event)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCaller(Kind_WorkerEventListener))));
    thisDeserializer.readPointer();
    Ark_Event event = Event_serializer::read(thisDeserializer);
    _call(_resourceId, event);
}
void deserializeAndCallSyncWorkerEventListener(Ark_VMContext vmContext, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    DeserializerBase thisDeserializer = DeserializerBase(thisArray, thisLength);
    const Ark_Int32 resourceId = thisDeserializer.readInt32();
    thisDeserializer.readPointer();
    const auto callSyncMethod = reinterpret_cast<void(*)(Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Event event)>(thisDeserializer.readPointerOrDefault(reinterpret_cast<Ark_NativePointer>(getManagedCallbackCallerSync(Kind_WorkerEventListener))));
    Ark_Event event = Event_serializer::read(thisDeserializer);
    callSyncMethod(vmContext, resourceId, event);
}
void deserializeAndCallCallback(Ark_Int32 kind, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    switch (static_cast<CallbackKind>(kind)) {
        case Kind_AccessibilityActionInterceptCallback: return deserializeAndCallAccessibilityActionInterceptCallback(thisArray, thisLength);
        case Kind_AccessibilityCallback: return deserializeAndCallAccessibilityCallback(thisArray, thisLength);
        case Kind_AccessibilityFocusCallback: return deserializeAndCallAccessibilityFocusCallback(thisArray, thisLength);
        case Kind_AsyncCallback_image_PixelMap_Void: return deserializeAndCallAsyncCallback_image_PixelMap_Void(thisArray, thisLength);
        case Kind_AsyncCallback_Void: return deserializeAndCallAsyncCallback_Void(thisArray, thisLength);
        case Kind_ButtonModifierBuilder: return deserializeAndCallButtonModifierBuilder(thisArray, thisLength);
        case Kind_ButtonTriggerClickCallback: return deserializeAndCallButtonTriggerClickCallback(thisArray, thisLength);
        case Kind_Callback_AccessibilityActionInterceptResult_Void: return deserializeAndCallCallback_AccessibilityActionInterceptResult_Void(thisArray, thisLength);
        case Kind_Callback_Area_Area_Void: return deserializeAndCallCallback_Area_Area_Void(thisArray, thisLength);
        case Kind_Callback_Array_I32_Void: return deserializeAndCallCallback_Array_I32_Void(thisArray, thisLength);
        case Kind_Callback_Array_String_Void: return deserializeAndCallCallback_Array_String_Void(thisArray, thisLength);
        case Kind_Callback_Array_TextMenuItem_Void: return deserializeAndCallCallback_Array_TextMenuItem_Void(thisArray, thisLength);
        case Kind_Callback_Array_TouchTestInfo_TouchResult: return deserializeAndCallCallback_Array_TouchTestInfo_TouchResult(thisArray, thisLength);
        case Kind_Callback_AxisEvent_Void: return deserializeAndCallCallback_AxisEvent_Void(thisArray, thisLength);
        case Kind_Callback_Boolean: return deserializeAndCallCallback_Boolean(thisArray, thisLength);
        case Kind_Callback_Boolean_HoverEvent_Void: return deserializeAndCallCallback_Boolean_HoverEvent_Void(thisArray, thisLength);
        case Kind_Callback_Boolean_Void: return deserializeAndCallCallback_Boolean_Void(thisArray, thisLength);
        case Kind_Callback_Buffer_Void: return deserializeAndCallCallback_Buffer_Void(thisArray, thisLength);
        case Kind_Callback_BusinessError_Void: return deserializeAndCallCallback_BusinessError_Void(thisArray, thisLength);
        case Kind_Callback_ClickEvent_Void: return deserializeAndCallCallback_ClickEvent_Void(thisArray, thisLength);
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
        case Kind_Callback_ErrorInformation_Void: return deserializeAndCallCallback_ErrorInformation_Void(thisArray, thisLength);
        case Kind_Callback_Extender_OnFinish: return deserializeAndCallCallback_Extender_OnFinish(thisArray, thisLength);
        case Kind_Callback_Extender_OnProgress: return deserializeAndCallCallback_Extender_OnProgress(thisArray, thisLength);
        case Kind_Callback_F64_F64_Void: return deserializeAndCallCallback_F64_F64_Void(thisArray, thisLength);
        case Kind_Callback_F64_SliderChangeMode_Void: return deserializeAndCallCallback_F64_SliderChangeMode_Void(thisArray, thisLength);
        case Kind_Callback_F64_Void: return deserializeAndCallCallback_F64_Void(thisArray, thisLength);
        case Kind_Callback_FocusAxisEvent_Void: return deserializeAndCallCallback_FocusAxisEvent_Void(thisArray, thisLength);
        case Kind_Callback_FormCallbackInfo_Void: return deserializeAndCallCallback_FormCallbackInfo_Void(thisArray, thisLength);
        case Kind_Callback_FullscreenInfo_Void: return deserializeAndCallCallback_FullscreenInfo_Void(thisArray, thisLength);
        case Kind_Callback_GestureEvent_Void: return deserializeAndCallCallback_GestureEvent_Void(thisArray, thisLength);
        case Kind_Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult: return deserializeAndCallCallback_GestureInfo_BaseGestureEvent_GestureJudgeResult(thisArray, thisLength);
        case Kind_Callback_GestureJudgeResult_Void: return deserializeAndCallCallback_GestureJudgeResult_Void(thisArray, thisLength);
        case Kind_Callback_GestureRecognizer_Void: return deserializeAndCallCallback_GestureRecognizer_Void(thisArray, thisLength);
        case Kind_Callback_HitTestMode_Void: return deserializeAndCallCallback_HitTestMode_Void(thisArray, thisLength);
        case Kind_Callback_HoverEvent_Void: return deserializeAndCallCallback_HoverEvent_Void(thisArray, thisLength);
        case Kind_Callback_I32_F64_ComputedBarAttribute: return deserializeAndCallCallback_I32_F64_ComputedBarAttribute(thisArray, thisLength);
        case Kind_Callback_I32_I32_Boolean: return deserializeAndCallCallback_I32_I32_Boolean(thisArray, thisLength);
        case Kind_Callback_I32_I32_I32_Void: return deserializeAndCallCallback_I32_I32_I32_Void(thisArray, thisLength);
        case Kind_Callback_I32_I32_Void: return deserializeAndCallCallback_I32_I32_Void(thisArray, thisLength);
        case Kind_Callback_I64_Void: return deserializeAndCallCallback_I64_Void(thisArray, thisLength);
        case Kind_Callback_I32_Tuple_I32_I32: return deserializeAndCallCallback_I32_Tuple_I32_I32(thisArray, thisLength);
        case Kind_Callback_I32_Tuple_I32_I32_I32_I32: return deserializeAndCallCallback_I32_Tuple_I32_I32_I32_I32(thisArray, thisLength);
        case Kind_Callback_I32_Void: return deserializeAndCallCallback_I32_Void(thisArray, thisLength);
        case Kind_Callback_InsertValue_Boolean: return deserializeAndCallCallback_InsertValue_Boolean(thisArray, thisLength);
        case Kind_Callback_InsertValue_Void: return deserializeAndCallCallback_InsertValue_Void(thisArray, thisLength);
        case Kind_Callback_ItemDragInfo_I32_I32_Boolean_Void: return deserializeAndCallCallback_ItemDragInfo_I32_I32_Boolean_Void(thisArray, thisLength);
        case Kind_Callback_ItemDragInfo_I32_I32_Void: return deserializeAndCallCallback_ItemDragInfo_I32_I32_Void(thisArray, thisLength);
        case Kind_Callback_ItemDragInfo_I32_Void: return deserializeAndCallCallback_ItemDragInfo_I32_Void(thisArray, thisLength);
        case Kind_Callback_ItemDragInfo_Void: return deserializeAndCallCallback_ItemDragInfo_Void(thisArray, thisLength);
        case Kind_Callback_KeyEvent_Boolean: return deserializeAndCallCallback_KeyEvent_Boolean(thisArray, thisLength);
        case Kind_Callback_KeyEvent_Void: return deserializeAndCallCallback_KeyEvent_Void(thisArray, thisLength);
        case Kind_Callback_Long_Void: return deserializeAndCallCallback_Long_Void(thisArray, thisLength);
        case Kind_Callback_Map_String_RecordData_Void: return deserializeAndCallCallback_Map_String_RecordData_Void(thisArray, thisLength);
        case Kind_Callback_MarqueeState_Void: return deserializeAndCallCallback_MarqueeState_Void(thisArray, thisLength);
        case Kind_Callback_MouseEvent_Void: return deserializeAndCallCallback_MouseEvent_Void(thisArray, thisLength);
        case Kind_Callback_NativeEmbedDataInfo_Void: return deserializeAndCallCallback_NativeEmbedDataInfo_Void(thisArray, thisLength);
        case Kind_Callback_NativeEmbedTouchInfo_Void: return deserializeAndCallCallback_NativeEmbedTouchInfo_Void(thisArray, thisLength);
        case Kind_Callback_NativeXComponentPointer_Void: return deserializeAndCallCallback_NativeXComponentPointer_Void(thisArray, thisLength);
        case Kind_Callback_NavDestinationActiveReason_Void: return deserializeAndCallCallback_NavDestinationActiveReason_Void(thisArray, thisLength);
        case Kind_Callback_NavDestinationContext_Void: return deserializeAndCallCallback_NavDestinationContext_Void(thisArray, thisLength);
        case Kind_Callback_NavigationMode_Void: return deserializeAndCallCallback_NavigationMode_Void(thisArray, thisLength);
        case Kind_Callback_NavigationTitleMode_Void: return deserializeAndCallCallback_NavigationTitleMode_Void(thisArray, thisLength);
        case Kind_Callback_NavigationTransitionProxy_Void: return deserializeAndCallCallback_NavigationTransitionProxy_Void(thisArray, thisLength);
        case Kind_Callback_Number_Number_Void: return deserializeAndCallCallback_Number_Number_Void(thisArray, thisLength);
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
        case Kind_Callback_OnDestory_Void: return deserializeAndCallCallback_OnDestory_Void(thisArray, thisLength);
        case Kind_Callback_OnDownloadStartEvent_Void: return deserializeAndCallCallback_OnDownloadStartEvent_Void(thisArray, thisLength);
        case Kind_Callback_OnErrorReceiveEvent_Void: return deserializeAndCallCallback_OnErrorReceiveEvent_Void(thisArray, thisLength);
        case Kind_Callback_OnFaviconReceivedEvent_Void: return deserializeAndCallCallback_OnFaviconReceivedEvent_Void(thisArray, thisLength);
        case Kind_Callback_OnFirstContentfulPaintEvent_Void: return deserializeAndCallCallback_OnFirstContentfulPaintEvent_Void(thisArray, thisLength);
        case Kind_Callback_OnGeolocationShowEvent_Void: return deserializeAndCallCallback_OnGeolocationShowEvent_Void(thisArray, thisLength);
        case Kind_Callback_OnHttpAuthRequestEvent_Boolean: return deserializeAndCallCallback_OnHttpAuthRequestEvent_Boolean(thisArray, thisLength);
        case Kind_Callback_OnHttpErrorReceiveEvent_Void: return deserializeAndCallCallback_OnHttpErrorReceiveEvent_Void(thisArray, thisLength);
        case Kind_Callback_OnLoadFinishedEvent_Void: return deserializeAndCallCallback_OnLoadFinishedEvent_Void(thisArray, thisLength);
        case Kind_Callback_OnLoadInterceptEvent_Boolean: return deserializeAndCallCallback_OnLoadInterceptEvent_Boolean(thisArray, thisLength);
        case Kind_Callback_OnLoadStartedEvent_Void: return deserializeAndCallCallback_OnLoadStartedEvent_Void(thisArray, thisLength);
        case Kind_Callback_onMeasureSize_SizeResult: return deserializeAndCallCallback_onMeasureSize_SizeResult(thisArray, thisLength);
        case Kind_Callback_OnMoveFromTo: return deserializeAndCallCallback_OnMoveFromTo(thisArray, thisLength);
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
        case Kind_Callback_Opt_Array_NavDestinationTransition_Void: return deserializeAndCallCallback_Opt_Array_NavDestinationTransition_Void(thisArray, thisLength);
        case Kind_Callback_Opt_Array_String_Void: return deserializeAndCallCallback_Opt_Array_String_Void(thisArray, thisLength);
        case Kind_Callback_Opt_CustomBuilder_Void: return deserializeAndCallCallback_Opt_CustomBuilder_Void(thisArray, thisLength);
        case Kind_Callback_Opt_NavigationAnimatedTransition_Void: return deserializeAndCallCallback_Opt_NavigationAnimatedTransition_Void(thisArray, thisLength);
        case Kind_Callback_Opt_OffsetResult_Void: return deserializeAndCallCallback_Opt_OffsetResult_Void(thisArray, thisLength);
        case Kind_Callback_Opt_ScrollResult_Void: return deserializeAndCallCallback_Opt_ScrollResult_Void(thisArray, thisLength);
        case Kind_Callback_Opt_StyledString_Opt_Array_String_Void: return deserializeAndCallCallback_Opt_StyledString_Opt_Array_String_Void(thisArray, thisLength);
        case Kind_Callback_Opt_TabContentAnimatedTransition_Void: return deserializeAndCallCallback_Opt_TabContentAnimatedTransition_Void(thisArray, thisLength);
        case Kind_Callback_Opt_WebResourceResponse_Void: return deserializeAndCallCallback_Opt_WebResourceResponse_Void(thisArray, thisLength);
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
        case Kind_Callback_SheetDismiss_Void: return deserializeAndCallCallback_SheetDismiss_Void(thisArray, thisLength);
        case Kind_Callback_SheetType_Void: return deserializeAndCallCallback_SheetType_Void(thisArray, thisLength);
        case Kind_Callback_Size_Void: return deserializeAndCallCallback_Size_Void(thisArray, thisLength);
        case Kind_Callback_SizeResult_Void: return deserializeAndCallCallback_SizeResult_Void(thisArray, thisLength);
        case Kind_Callback_SpringBackAction_Void: return deserializeAndCallCallback_SpringBackAction_Void(thisArray, thisLength);
        case Kind_Callback_StateStylesChange: return deserializeAndCallCallback_StateStylesChange(thisArray, thisLength);
        case Kind_Callback_String_PasteEvent_Void: return deserializeAndCallCallback_String_PasteEvent_Void(thisArray, thisLength);
        case Kind_Callback_String_SurfaceRect_Void: return deserializeAndCallCallback_String_SurfaceRect_Void(thisArray, thisLength);
        case Kind_Callback_String_Void: return deserializeAndCallCallback_String_Void(thisArray, thisLength);
        case Kind_Callback_StyledStringChangeValue_Boolean: return deserializeAndCallCallback_StyledStringChangeValue_Boolean(thisArray, thisLength);
        case Kind_Callback_StyledStringMarshallingValue_Void: return deserializeAndCallCallback_StyledStringMarshallingValue_Void(thisArray, thisLength);
        case Kind_Callback_SwipeActionState_Void: return deserializeAndCallCallback_SwipeActionState_Void(thisArray, thisLength);
        case Kind_Callback_SwiperContentTransitionProxy_Void: return deserializeAndCallCallback_SwiperContentTransitionProxy_Void(thisArray, thisLength);
        case Kind_Callback_T_Void_Arkui_Component_Units_Length: return deserializeAndCallCallback_T_Void_Arkui_Component_Units_Length(thisArray, thisLength);
        case Kind_Callback_T_Void_Arkui_Component_Units_ResourceStr: return deserializeAndCallCallback_T_Void_Arkui_Component_Units_ResourceStr(thisArray, thisLength);
        case Kind_Callback_T_Void_Array_Arkui_Component_Units_ResourceStr: return deserializeAndCallCallback_T_Void_Array_Arkui_Component_Units_ResourceStr(thisArray, thisLength);
        case Kind_Callback_T_Void_Array_Global_Resource_Resource: return deserializeAndCallCallback_T_Void_Array_Global_Resource_Resource(thisArray, thisLength);
        case Kind_Callback_T_Void_Array_I32: return deserializeAndCallCallback_T_Void_Array_I32(thisArray, thisLength);
        case Kind_Callback_T_Void_Array_String: return deserializeAndCallCallback_T_Void_Array_String(thisArray, thisLength);
        case Kind_Callback_T_Void_Boolean: return deserializeAndCallCallback_T_Void_Boolean(thisArray, thisLength);
        case Kind_Callback_T_Void_Date: return deserializeAndCallCallback_T_Void_Date(thisArray, thisLength);
        case Kind_Callback_T_Void_F64: return deserializeAndCallCallback_T_Void_F64(thisArray, thisLength);
        case Kind_Callback_T_Void_Global_Resource_Resource: return deserializeAndCallCallback_T_Void_Global_Resource_Resource(thisArray, thisLength);
        case Kind_Callback_T_Void_I32: return deserializeAndCallCallback_T_Void_I32(thisArray, thisLength);
        case Kind_Callback_T_Void_Number: return deserializeAndCallCallback_T_Void_Number(thisArray, thisLength);
        case Kind_Callback_T_Void_String: return deserializeAndCallCallback_T_Void_String(thisArray, thisLength);
        case Kind_Callback_TabContentTransitionProxy_Void: return deserializeAndCallCallback_TabContentTransitionProxy_Void(thisArray, thisLength);
        case Kind_Callback_TerminationInfo_Void: return deserializeAndCallCallback_TerminationInfo_Void(thisArray, thisLength);
        case Kind_Callback_TextPickerResult_Void: return deserializeAndCallCallback_TextPickerResult_Void(thisArray, thisLength);
        case Kind_Callback_TextRange_Void: return deserializeAndCallCallback_TextRange_Void(thisArray, thisLength);
        case Kind_Callback_TimePickerResult_Void: return deserializeAndCallCallback_TimePickerResult_Void(thisArray, thisLength);
        case Kind_Callback_TouchEvent_HitTestMode: return deserializeAndCallCallback_TouchEvent_HitTestMode(thisArray, thisLength);
        case Kind_Callback_TouchEvent_Void: return deserializeAndCallCallback_TouchEvent_Void(thisArray, thisLength);
        case Kind_Callback_TouchResult_Void: return deserializeAndCallCallback_TouchResult_Void(thisArray, thisLength);
        case Kind_Callback_Tuple_I32_I32_I32_I32_Void: return deserializeAndCallCallback_Tuple_I32_I32_I32_I32_Void(thisArray, thisLength);
        case Kind_Callback_Tuple_I32_I32_Void: return deserializeAndCallCallback_Tuple_I32_I32_Void(thisArray, thisLength);
        case Kind_Callback_UIExtensionProxy_Void: return deserializeAndCallCallback_UIExtensionProxy_Void(thisArray, thisLength);
        case Kind_Callback_Union_CustomBuilder_DragItemInfo_Void: return deserializeAndCallCallback_Union_CustomBuilder_DragItemInfo_Void(thisArray, thisLength);
        case Kind_Callback_Union_Object_Idlize_Stdlib_Null_Undefined_Void: return deserializeAndCallCallback_Union_Object_Idlize_Stdlib_Null_Undefined_Void(thisArray, thisLength);
        case Kind_Callback_Void: return deserializeAndCallCallback_Void(thisArray, thisLength);
        case Kind_Callback_WebKeyboardOptions_Void: return deserializeAndCallCallback_WebKeyboardOptions_Void(thisArray, thisLength);
        case Kind_CheckBoxModifierBuilder: return deserializeAndCallCheckBoxModifierBuilder(thisArray, thisLength);
        case Kind_ContentDidScrollCallback: return deserializeAndCallContentDidScrollCallback(thisArray, thisLength);
        case Kind_ContentWillScrollCallback: return deserializeAndCallContentWillScrollCallback(thisArray, thisLength);
        case Kind_CustomBuilderT_I32: return deserializeAndCallCustomBuilderT_I32(thisArray, thisLength);
        case Kind_CustomNodeBuilder: return deserializeAndCallCustomNodeBuilder(thisArray, thisLength);
        case Kind_DataPanelModifierBuilder: return deserializeAndCallDataPanelModifierBuilder(thisArray, thisLength);
        case Kind_EditableTextOnChangeCallback: return deserializeAndCallEditableTextOnChangeCallback(thisArray, thisLength);
        case Kind_ErrorCallback_Ohos_Base_BusinessError: return deserializeAndCallErrorCallback_Ohos_Base_BusinessError(thisArray, thisLength);
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
        case Kind_PasteButtonCallback: return deserializeAndCallPasteButtonCallback(thisArray, thisLength);
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
        case Kind_RouterFinishCallback: return deserializeAndCallRouterFinishCallback(thisArray, thisLength);
        case Kind_SaveButtonCallback: return deserializeAndCallSaveButtonCallback(thisArray, thisLength);
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
        case Kind_TimerCallback: return deserializeAndCallTimerCallback(thisArray, thisLength);
        case Kind_ToggleModifierBuilder: return deserializeAndCallToggleModifierBuilder(thisArray, thisLength);
        case Kind_TransitionFinishCallback: return deserializeAndCallTransitionFinishCallback(thisArray, thisLength);
        case Kind_Type_CommonMethod_onDragStart: return deserializeAndCallType_CommonMethod_onDragStart(thisArray, thisLength);
        case Kind_Type_NavigationAttribute_customNavContentTransition: return deserializeAndCallType_NavigationAttribute_customNavContentTransition(thisArray, thisLength);
        case Kind_Type_WebAttribute_onInterceptRequest: return deserializeAndCallType_WebAttribute_onInterceptRequest(thisArray, thisLength);
        case Kind_UpdateTransitionCallback: return deserializeAndCallUpdateTransitionCallback(thisArray, thisLength);
        case Kind_VisibleAreaChangeCallback: return deserializeAndCallVisibleAreaChangeCallback(thisArray, thisLength);
        case Kind_VoidCallback: return deserializeAndCallVoidCallback(thisArray, thisLength);
        case Kind_WebKeyboardCallback: return deserializeAndCallWebKeyboardCallback(thisArray, thisLength);
        case Kind_WorkerEventListener: return deserializeAndCallWorkerEventListener(thisArray, thisLength);
    }
    INTEROP_FATAL("Unknown callback kind");
}
KOALA_EXECUTE(deserializeAndCallCallback, setCallbackCaller(10, static_cast<Callback_Caller_t>(deserializeAndCallCallback)))
void deserializeAndCallCallbackSync(Ark_VMContext vmContext, Ark_Int32 kind, KSerializerBuffer thisArray, Ark_Int32 thisLength)
{
    switch (kind) {
        case Kind_AccessibilityActionInterceptCallback: return deserializeAndCallSyncAccessibilityActionInterceptCallback(vmContext, thisArray, thisLength);
        case Kind_AccessibilityCallback: return deserializeAndCallSyncAccessibilityCallback(vmContext, thisArray, thisLength);
        case Kind_AccessibilityFocusCallback: return deserializeAndCallSyncAccessibilityFocusCallback(vmContext, thisArray, thisLength);
        case Kind_AsyncCallback_image_PixelMap_Void: return deserializeAndCallSyncAsyncCallback_image_PixelMap_Void(vmContext, thisArray, thisLength);
        case Kind_AsyncCallback_Void: return deserializeAndCallSyncAsyncCallback_Void(vmContext, thisArray, thisLength);
        case Kind_ButtonModifierBuilder: return deserializeAndCallSyncButtonModifierBuilder(vmContext, thisArray, thisLength);
        case Kind_ButtonTriggerClickCallback: return deserializeAndCallSyncButtonTriggerClickCallback(vmContext, thisArray, thisLength);
        case Kind_Callback_AccessibilityActionInterceptResult_Void: return deserializeAndCallSyncCallback_AccessibilityActionInterceptResult_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Area_Area_Void: return deserializeAndCallSyncCallback_Area_Area_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Array_I32_Void: return deserializeAndCallSyncCallback_Array_I32_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Array_String_Void: return deserializeAndCallSyncCallback_Array_String_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Array_TextMenuItem_Void: return deserializeAndCallSyncCallback_Array_TextMenuItem_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Array_TouchTestInfo_TouchResult: return deserializeAndCallSyncCallback_Array_TouchTestInfo_TouchResult(vmContext, thisArray, thisLength);
        case Kind_Callback_AxisEvent_Void: return deserializeAndCallSyncCallback_AxisEvent_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Boolean: return deserializeAndCallSyncCallback_Boolean(vmContext, thisArray, thisLength);
        case Kind_Callback_Boolean_HoverEvent_Void: return deserializeAndCallSyncCallback_Boolean_HoverEvent_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Boolean_Void: return deserializeAndCallSyncCallback_Boolean_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Buffer_Void: return deserializeAndCallSyncCallback_Buffer_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_BusinessError_Void: return deserializeAndCallSyncCallback_BusinessError_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_ClickEvent_Void: return deserializeAndCallSyncCallback_ClickEvent_Void(vmContext, thisArray, thisLength);
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
        case Kind_Callback_ErrorInformation_Void: return deserializeAndCallSyncCallback_ErrorInformation_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Extender_OnFinish: return deserializeAndCallSyncCallback_Extender_OnFinish(vmContext, thisArray, thisLength);
        case Kind_Callback_Extender_OnProgress: return deserializeAndCallSyncCallback_Extender_OnProgress(vmContext, thisArray, thisLength);
        case Kind_Callback_F64_F64_Void: return deserializeAndCallSyncCallback_F64_F64_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_F64_SliderChangeMode_Void: return deserializeAndCallSyncCallback_F64_SliderChangeMode_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_F64_Void: return deserializeAndCallSyncCallback_F64_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_FocusAxisEvent_Void: return deserializeAndCallSyncCallback_FocusAxisEvent_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_FormCallbackInfo_Void: return deserializeAndCallSyncCallback_FormCallbackInfo_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_FullscreenInfo_Void: return deserializeAndCallSyncCallback_FullscreenInfo_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_GestureEvent_Void: return deserializeAndCallSyncCallback_GestureEvent_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult: return deserializeAndCallSyncCallback_GestureInfo_BaseGestureEvent_GestureJudgeResult(vmContext, thisArray, thisLength);
        case Kind_Callback_GestureJudgeResult_Void: return deserializeAndCallSyncCallback_GestureJudgeResult_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_GestureRecognizer_Void: return deserializeAndCallSyncCallback_GestureRecognizer_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_HitTestMode_Void: return deserializeAndCallSyncCallback_HitTestMode_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_HoverEvent_Void: return deserializeAndCallSyncCallback_HoverEvent_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_I32_F64_ComputedBarAttribute: return deserializeAndCallSyncCallback_I32_F64_ComputedBarAttribute(vmContext, thisArray, thisLength);
        case Kind_Callback_I32_I32_Boolean: return deserializeAndCallSyncCallback_I32_I32_Boolean(vmContext, thisArray, thisLength);
        case Kind_Callback_I32_I32_I32_Void: return deserializeAndCallSyncCallback_I32_I32_I32_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_I32_I32_Void: return deserializeAndCallSyncCallback_I32_I32_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_I64_Void: return deserializeAndCallSyncCallback_I64_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_I32_Tuple_I32_I32: return deserializeAndCallSyncCallback_I32_Tuple_I32_I32(vmContext, thisArray, thisLength);
        case Kind_Callback_I32_Tuple_I32_I32_I32_I32: return deserializeAndCallSyncCallback_I32_Tuple_I32_I32_I32_I32(vmContext, thisArray, thisLength);
        case Kind_Callback_I32_Void: return deserializeAndCallSyncCallback_I32_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_InsertValue_Boolean: return deserializeAndCallSyncCallback_InsertValue_Boolean(vmContext, thisArray, thisLength);
        case Kind_Callback_InsertValue_Void: return deserializeAndCallSyncCallback_InsertValue_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_ItemDragInfo_I32_I32_Boolean_Void: return deserializeAndCallSyncCallback_ItemDragInfo_I32_I32_Boolean_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_ItemDragInfo_I32_I32_Void: return deserializeAndCallSyncCallback_ItemDragInfo_I32_I32_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_ItemDragInfo_I32_Void: return deserializeAndCallSyncCallback_ItemDragInfo_I32_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_ItemDragInfo_Void: return deserializeAndCallSyncCallback_ItemDragInfo_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_KeyEvent_Boolean: return deserializeAndCallSyncCallback_KeyEvent_Boolean(vmContext, thisArray, thisLength);
        case Kind_Callback_KeyEvent_Void: return deserializeAndCallSyncCallback_KeyEvent_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Long_Void: return deserializeAndCallSyncCallback_Long_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Map_String_RecordData_Void: return deserializeAndCallSyncCallback_Map_String_RecordData_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_MarqueeState_Void: return deserializeAndCallSyncCallback_MarqueeState_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_MouseEvent_Void: return deserializeAndCallSyncCallback_MouseEvent_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_NativeEmbedDataInfo_Void: return deserializeAndCallSyncCallback_NativeEmbedDataInfo_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_NativeEmbedTouchInfo_Void: return deserializeAndCallSyncCallback_NativeEmbedTouchInfo_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_NativeXComponentPointer_Void: return deserializeAndCallSyncCallback_NativeXComponentPointer_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_NavDestinationActiveReason_Void: return deserializeAndCallSyncCallback_NavDestinationActiveReason_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_NavDestinationContext_Void: return deserializeAndCallSyncCallback_NavDestinationContext_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_NavigationMode_Void: return deserializeAndCallSyncCallback_NavigationMode_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_NavigationTitleMode_Void: return deserializeAndCallSyncCallback_NavigationTitleMode_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_NavigationTransitionProxy_Void: return deserializeAndCallSyncCallback_NavigationTransitionProxy_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Number_Number_Void: return deserializeAndCallSyncCallback_Number_Number_Void(vmContext, thisArray, thisLength);
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
        case Kind_Callback_OnDestory_Void: return deserializeAndCallSyncCallback_OnDestory_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_OnDownloadStartEvent_Void: return deserializeAndCallSyncCallback_OnDownloadStartEvent_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_OnErrorReceiveEvent_Void: return deserializeAndCallSyncCallback_OnErrorReceiveEvent_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_OnFaviconReceivedEvent_Void: return deserializeAndCallSyncCallback_OnFaviconReceivedEvent_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_OnFirstContentfulPaintEvent_Void: return deserializeAndCallSyncCallback_OnFirstContentfulPaintEvent_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_OnGeolocationShowEvent_Void: return deserializeAndCallSyncCallback_OnGeolocationShowEvent_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_OnHttpAuthRequestEvent_Boolean: return deserializeAndCallSyncCallback_OnHttpAuthRequestEvent_Boolean(vmContext, thisArray, thisLength);
        case Kind_Callback_OnHttpErrorReceiveEvent_Void: return deserializeAndCallSyncCallback_OnHttpErrorReceiveEvent_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_OnLoadFinishedEvent_Void: return deserializeAndCallSyncCallback_OnLoadFinishedEvent_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_OnLoadInterceptEvent_Boolean: return deserializeAndCallSyncCallback_OnLoadInterceptEvent_Boolean(vmContext, thisArray, thisLength);
        case Kind_Callback_OnLoadStartedEvent_Void: return deserializeAndCallSyncCallback_OnLoadStartedEvent_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_onMeasureSize_SizeResult: return deserializeAndCallSyncCallback_onMeasureSize_SizeResult(vmContext, thisArray, thisLength);
        case Kind_Callback_OnMoveFromTo: return deserializeAndCallSyncCallback_OnMoveFromTo(vmContext, thisArray, thisLength);
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
        case Kind_Callback_Opt_Array_NavDestinationTransition_Void: return deserializeAndCallSyncCallback_Opt_Array_NavDestinationTransition_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Opt_Array_String_Void: return deserializeAndCallSyncCallback_Opt_Array_String_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Opt_CustomBuilder_Void: return deserializeAndCallSyncCallback_Opt_CustomBuilder_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Opt_NavigationAnimatedTransition_Void: return deserializeAndCallSyncCallback_Opt_NavigationAnimatedTransition_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Opt_OffsetResult_Void: return deserializeAndCallSyncCallback_Opt_OffsetResult_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Opt_ScrollResult_Void: return deserializeAndCallSyncCallback_Opt_ScrollResult_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Opt_StyledString_Opt_Array_String_Void: return deserializeAndCallSyncCallback_Opt_StyledString_Opt_Array_String_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Opt_TabContentAnimatedTransition_Void: return deserializeAndCallSyncCallback_Opt_TabContentAnimatedTransition_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Opt_WebResourceResponse_Void: return deserializeAndCallSyncCallback_Opt_WebResourceResponse_Void(vmContext, thisArray, thisLength);
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
        case Kind_Callback_SheetDismiss_Void: return deserializeAndCallSyncCallback_SheetDismiss_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_SheetType_Void: return deserializeAndCallSyncCallback_SheetType_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Size_Void: return deserializeAndCallSyncCallback_Size_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_SizeResult_Void: return deserializeAndCallSyncCallback_SizeResult_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_SpringBackAction_Void: return deserializeAndCallSyncCallback_SpringBackAction_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_StateStylesChange: return deserializeAndCallSyncCallback_StateStylesChange(vmContext, thisArray, thisLength);
        case Kind_Callback_String_PasteEvent_Void: return deserializeAndCallSyncCallback_String_PasteEvent_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_String_SurfaceRect_Void: return deserializeAndCallSyncCallback_String_SurfaceRect_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_String_Void: return deserializeAndCallSyncCallback_String_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_StyledStringChangeValue_Boolean: return deserializeAndCallSyncCallback_StyledStringChangeValue_Boolean(vmContext, thisArray, thisLength);
        case Kind_Callback_StyledStringMarshallingValue_Void: return deserializeAndCallSyncCallback_StyledStringMarshallingValue_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_SwipeActionState_Void: return deserializeAndCallSyncCallback_SwipeActionState_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_SwiperContentTransitionProxy_Void: return deserializeAndCallSyncCallback_SwiperContentTransitionProxy_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_T_Void_Arkui_Component_Units_Length: return deserializeAndCallSyncCallback_T_Void_Arkui_Component_Units_Length(vmContext, thisArray, thisLength);
        case Kind_Callback_T_Void_Arkui_Component_Units_ResourceStr: return deserializeAndCallSyncCallback_T_Void_Arkui_Component_Units_ResourceStr(vmContext, thisArray, thisLength);
        case Kind_Callback_T_Void_Array_Arkui_Component_Units_ResourceStr: return deserializeAndCallSyncCallback_T_Void_Array_Arkui_Component_Units_ResourceStr(vmContext, thisArray, thisLength);
        case Kind_Callback_T_Void_Array_Global_Resource_Resource: return deserializeAndCallSyncCallback_T_Void_Array_Global_Resource_Resource(vmContext, thisArray, thisLength);
        case Kind_Callback_T_Void_Array_I32: return deserializeAndCallSyncCallback_T_Void_Array_I32(vmContext, thisArray, thisLength);
        case Kind_Callback_T_Void_Array_String: return deserializeAndCallSyncCallback_T_Void_Array_String(vmContext, thisArray, thisLength);
        case Kind_Callback_T_Void_Boolean: return deserializeAndCallSyncCallback_T_Void_Boolean(vmContext, thisArray, thisLength);
        case Kind_Callback_T_Void_Date: return deserializeAndCallSyncCallback_T_Void_Date(vmContext, thisArray, thisLength);
        case Kind_Callback_T_Void_Global_Resource_Resource: return deserializeAndCallSyncCallback_T_Void_Global_Resource_Resource(vmContext, thisArray, thisLength);
        case Kind_Callback_T_Void_I32: return deserializeAndCallSyncCallback_T_Void_I32(vmContext, thisArray, thisLength);
        case Kind_Callback_T_Void_Number: return deserializeAndCallSyncCallback_T_Void_Number(vmContext, thisArray, thisLength);
        case Kind_Callback_T_Void_String: return deserializeAndCallSyncCallback_T_Void_String(vmContext, thisArray, thisLength);
        case Kind_Callback_TabContentTransitionProxy_Void: return deserializeAndCallSyncCallback_TabContentTransitionProxy_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_TerminationInfo_Void: return deserializeAndCallSyncCallback_TerminationInfo_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_TextPickerResult_Void: return deserializeAndCallSyncCallback_TextPickerResult_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_TextRange_Void: return deserializeAndCallSyncCallback_TextRange_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_TimePickerResult_Void: return deserializeAndCallSyncCallback_TimePickerResult_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_TouchEvent_HitTestMode: return deserializeAndCallSyncCallback_TouchEvent_HitTestMode(vmContext, thisArray, thisLength);
        case Kind_Callback_TouchEvent_Void: return deserializeAndCallSyncCallback_TouchEvent_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_TouchResult_Void: return deserializeAndCallSyncCallback_TouchResult_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Tuple_I32_I32_I32_I32_Void: return deserializeAndCallSyncCallback_Tuple_I32_I32_I32_I32_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Tuple_I32_I32_Void: return deserializeAndCallSyncCallback_Tuple_I32_I32_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_UIExtensionProxy_Void: return deserializeAndCallSyncCallback_UIExtensionProxy_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Union_CustomBuilder_DragItemInfo_Void: return deserializeAndCallSyncCallback_Union_CustomBuilder_DragItemInfo_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Union_Object_Idlize_Stdlib_Null_Undefined_Void: return deserializeAndCallSyncCallback_Union_Object_Idlize_Stdlib_Null_Undefined_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_Void: return deserializeAndCallSyncCallback_Void(vmContext, thisArray, thisLength);
        case Kind_Callback_WebKeyboardOptions_Void: return deserializeAndCallSyncCallback_WebKeyboardOptions_Void(vmContext, thisArray, thisLength);
        case Kind_CheckBoxModifierBuilder: return deserializeAndCallSyncCheckBoxModifierBuilder(vmContext, thisArray, thisLength);
        case Kind_ContentDidScrollCallback: return deserializeAndCallSyncContentDidScrollCallback(vmContext, thisArray, thisLength);
        case Kind_ContentWillScrollCallback: return deserializeAndCallSyncContentWillScrollCallback(vmContext, thisArray, thisLength);
        case Kind_CustomBuilderT_I32: return deserializeAndCallSyncCustomBuilderT_I32(vmContext, thisArray, thisLength);
        case Kind_CustomNodeBuilder: return deserializeAndCallSyncCustomNodeBuilder(vmContext, thisArray, thisLength);
        case Kind_DataPanelModifierBuilder: return deserializeAndCallSyncDataPanelModifierBuilder(vmContext, thisArray, thisLength);
        case Kind_EditableTextOnChangeCallback: return deserializeAndCallSyncEditableTextOnChangeCallback(vmContext, thisArray, thisLength);
        case Kind_ErrorCallback_Ohos_Base_BusinessError: return deserializeAndCallSyncErrorCallback_Ohos_Base_BusinessError(vmContext, thisArray, thisLength);
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
        case Kind_PasteButtonCallback: return deserializeAndCallSyncPasteButtonCallback(vmContext, thisArray, thisLength);
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
        case Kind_RouterFinishCallback: return deserializeAndCallSyncRouterFinishCallback(vmContext, thisArray, thisLength);
        case Kind_SaveButtonCallback: return deserializeAndCallSyncSaveButtonCallback(vmContext, thisArray, thisLength);
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
        case Kind_TimerCallback: return deserializeAndCallSyncTimerCallback(vmContext, thisArray, thisLength);
        case Kind_ToggleModifierBuilder: return deserializeAndCallSyncToggleModifierBuilder(vmContext, thisArray, thisLength);
        case Kind_TransitionFinishCallback: return deserializeAndCallSyncTransitionFinishCallback(vmContext, thisArray, thisLength);
        case Kind_Type_CommonMethod_onDragStart: return deserializeAndCallSyncType_CommonMethod_onDragStart(vmContext, thisArray, thisLength);
        case Kind_Type_NavigationAttribute_customNavContentTransition: return deserializeAndCallSyncType_NavigationAttribute_customNavContentTransition(vmContext, thisArray, thisLength);
        case Kind_Type_WebAttribute_onInterceptRequest: return deserializeAndCallSyncType_WebAttribute_onInterceptRequest(vmContext, thisArray, thisLength);
        case Kind_UpdateTransitionCallback: return deserializeAndCallSyncUpdateTransitionCallback(vmContext, thisArray, thisLength);
        case Kind_VisibleAreaChangeCallback: return deserializeAndCallSyncVisibleAreaChangeCallback(vmContext, thisArray, thisLength);
        case Kind_VoidCallback: return deserializeAndCallSyncVoidCallback(vmContext, thisArray, thisLength);
        case Kind_WebKeyboardCallback: return deserializeAndCallSyncWebKeyboardCallback(vmContext, thisArray, thisLength);
        case Kind_WorkerEventListener: return deserializeAndCallSyncWorkerEventListener(vmContext, thisArray, thisLength);
    }
    INTEROP_FATAL("Unknown callback kind");
}
KOALA_EXECUTE(deserializeAndCallCallbackSync, setCallbackCallerSync(10, static_cast<Callback_Caller_Sync_t>(deserializeAndCallCallbackSync)))