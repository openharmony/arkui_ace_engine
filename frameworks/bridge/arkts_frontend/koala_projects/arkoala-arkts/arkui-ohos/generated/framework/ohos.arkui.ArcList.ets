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


// WARNING! THIS FILE IS AUTO-GENERATED, DO NOT MAKE CHANGES, THEY WILL BE LOST ON NEXT GENERATION!

import { Scroller_serializer, Scroller } from "./../component/scroll"
import { ComponentContentBase_serializer } from "./../ComponentContent"
import { ArkListOptions } from "@ohos.arkui.ArcList"
import { SerializerBase, DeserializerBase, CallbackResource, InteropNativeModule, MaterializedBase, Tags, RuntimeType, runtimeType, toPeerPtr, nullptr, KPointer, NativeBuffer, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { TypeChecker } from "#components"
import { CallbackTransformer } from "./../CallbackTransformer"
import { extractors } from "#handwritten"
import { ComponentContentBase } from "arkui.ComponentContent"
export class ArkListOptions_serializer {
    public static write(buffer: SerializerBase, value: ArkListOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForInitialIndex  = value.initialIndex
        if (valueHolderForInitialIndex !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForInitialIndexTmpValue  = valueHolderForInitialIndex!
            valueSerializer.writeInt32(valueHolderForInitialIndexTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForScroller  = value.scroller
        if (valueHolderForScroller !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForScrollerTmpValue  = valueHolderForScroller!
            Scroller_serializer.write(valueSerializer, valueHolderForScrollerTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForHeader  = value.header
        if (valueHolderForHeader !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForHeaderTmpValue  = valueHolderForHeader!
            ComponentContentBase_serializer.write(valueSerializer, valueHolderForHeaderTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ArkListOptions {
        let valueDeserializer : DeserializerBase = buffer
        const initialIndexTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let initialIndexTmpBuf : int32 | undefined = undefined
        if ((initialIndexTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            initialIndexTmpBuf = valueDeserializer.readInt32()
        }
        const initialIndexTmpResult : int32 | undefined = initialIndexTmpBuf
        const scrollerTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let scrollerTmpBuf : Scroller | undefined = undefined
        if ((scrollerTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            scrollerTmpBuf = (Scroller_serializer.read(valueDeserializer) as Scroller)
        }
        const scrollerTmpResult : Scroller | undefined = scrollerTmpBuf
        const headerTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let headerTmpBuf : ComponentContentBase | undefined = undefined
        if ((headerTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            headerTmpBuf = (ComponentContentBase_serializer.read(valueDeserializer) as ComponentContentBase)
        }
        const headerTmpResult : ComponentContentBase | undefined = headerTmpBuf
        let value : ArkListOptions = ({initialIndex: initialIndexTmpResult, scroller: scrollerTmpResult, header: headerTmpResult} as ArkListOptions)
        return value
    }
}
