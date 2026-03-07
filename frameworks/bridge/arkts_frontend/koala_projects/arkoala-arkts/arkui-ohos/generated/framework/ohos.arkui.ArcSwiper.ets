/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

// WARNING! THIS FILE IS AUTO-GENERATED, DO NOT MAKE CHANGES, THEY WILL BE LOST ON NEXT GENERATION!

import { extractors } from '#handwritten'
import { ArcSwiperContentTransitionProxy, ArcSwiperContentAnimatedTransition } from '@ohos.arkui.ArcSwiper'
import { SerializerBase, DeserializerBase, CallbackResource, InteropNativeModule, MaterializedBase, Tags, RuntimeType, toPeerPtr, nullptr, KPointer, NativeBuffer, KSerializerBuffer, KUint8ArrayPtr, resourceFinalizerRegister } from '@koalaui/interop'
import { int32, int64, float32, unsafeCast } from '@koalaui/common'
import { CallbackTransformer } from './../CallbackTransformer'
import { Callback as ohos_base_Callback } from '@ohos.base'
export class ArcSwiperContentTransitionProxy_serializer {
    public static write(buffer: SerializerBase, value: ArcSwiperContentTransitionProxy): void {
        let valueSerializer: SerializerBase = buffer
        valueSerializer.writePointer(extractors.toArcSwiperContentTransitionProxyPtr(value))
    }
    public static read(buffer: DeserializerBase): ArcSwiperContentTransitionProxy {
        let valueDeserializer: DeserializerBase = buffer
        let ptr: KPointer = valueDeserializer.readPointer()
        return extractors.fromArcSwiperContentTransitionProxyPtr(ptr)
    }
}
export class ArcSwiperContentAnimatedTransition_serializer {
    public static write(buffer: SerializerBase, value: ArcSwiperContentAnimatedTransition): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForTimeout = value.timeout
        if (valueHolderForTimeout !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTimeoutTmpValue = valueHolderForTimeout!
            valueSerializer.writeInt32(valueHolderForTimeoutTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForTransition = value.transition
        valueSerializer.holdAndWriteCallback(valueHolderForTransition)
    }
    public static read(buffer: DeserializerBase): ArcSwiperContentAnimatedTransition {
        let valueDeserializer: DeserializerBase = buffer
        const timeoutTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let timeoutTmpBuf: int32 | undefined = undefined
        if ((timeoutTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            timeoutTmpBuf = valueDeserializer.readInt32()
        }
        const timeoutTmpResult: int32 | undefined = timeoutTmpBuf
        const transitionTmpBufBufResource: CallbackResource = valueDeserializer.readCallbackResource()
        const transitionTmpBufBufCall: KPointer = valueDeserializer.readPointer()
        const transitionTmpBufBufCallSync: KPointer = valueDeserializer.readPointer()
        const transitionTmpBufClosure = (data: ArcSwiperContentTransitionProxy):void => {
            const transitionTmpBufBufArgsSerializer: SerializerBase = SerializerBase.hold();
            transitionTmpBufBufArgsSerializer.writeInt32(transitionTmpBufBufResource.resourceId);
            transitionTmpBufBufArgsSerializer.writePointer(transitionTmpBufBufCall);
            transitionTmpBufBufArgsSerializer.writePointer(transitionTmpBufBufCallSync);
            ArcSwiperContentTransitionProxy_serializer.write(transitionTmpBufBufArgsSerializer, data);
            InteropNativeModule._CallCallbackSync(10, -1938076268, transitionTmpBufBufArgsSerializer.asBuffer(), transitionTmpBufBufArgsSerializer.length());
            transitionTmpBufBufArgsSerializer.release();
            return;
        }
        resourceFinalizerRegister(transitionTmpBufClosure, transitionTmpBufBufResource)
        const transitionTmpResult: ohos_base_Callback<ArcSwiperContentTransitionProxy> = transitionTmpBufClosure
        let value: ArcSwiperContentAnimatedTransition = ({timeout: timeoutTmpResult, transition: transitionTmpResult} as ArcSwiperContentAnimatedTransition)
        return value
    }
}
