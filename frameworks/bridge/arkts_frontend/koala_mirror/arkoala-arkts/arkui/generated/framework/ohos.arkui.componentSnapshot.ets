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

import { SerializerBase, DeserializerBase, CallbackResource, InteropNativeModule, MaterializedBase, Tags, RuntimeType, runtimeType, toPeerPtr, nullptr, KPointer, NativeBuffer, KSerializerBuffer, KUint8ArrayPtr, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { TypeChecker } from "#components"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { extractors } from "#handwritten"
import { image } from "@ohos.multimedia.image"
import { GlobalScope } from "./GlobalScope"
export class componentSnapshot_LocalizedSnapshotRegion_serializer {
    public static write(buffer: SerializerBase, value: componentSnapshot.LocalizedSnapshotRegion): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForStart  = value.start
        valueSerializer.writeNumber(valueHolderForStart)
        const valueHolderForEnd  = value.end
        valueSerializer.writeNumber(valueHolderForEnd)
        const valueHolderForTop  = value.top
        valueSerializer.writeNumber(valueHolderForTop)
        const valueHolderForBottom  = value.bottom
        valueSerializer.writeNumber(valueHolderForBottom)
    }
    public static read(buffer: DeserializerBase): componentSnapshot.LocalizedSnapshotRegion {
        let valueDeserializer : DeserializerBase = buffer
        const startTmpResult : number = (valueDeserializer.readNumber() as number)
        const endTmpResult : number = (valueDeserializer.readNumber() as number)
        const topTmpResult : number = (valueDeserializer.readNumber() as number)
        const bottomTmpResult : number = (valueDeserializer.readNumber() as number)
        let value : componentSnapshot.LocalizedSnapshotRegion = ({start: startTmpResult, end: endTmpResult, top: topTmpResult, bottom: bottomTmpResult} as componentSnapshot.LocalizedSnapshotRegion)
        return value
    }
}
export class componentSnapshot_SnapshotRegion_serializer {
    public static write(buffer: SerializerBase, value: componentSnapshot.SnapshotRegion): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForLeft  = value.left
        valueSerializer.writeNumber(valueHolderForLeft)
        const valueHolderForRight  = value.right
        valueSerializer.writeNumber(valueHolderForRight)
        const valueHolderForTop  = value.top
        valueSerializer.writeNumber(valueHolderForTop)
        const valueHolderForBottom  = value.bottom
        valueSerializer.writeNumber(valueHolderForBottom)
    }
    public static read(buffer: DeserializerBase): componentSnapshot.SnapshotRegion {
        let valueDeserializer : DeserializerBase = buffer
        const leftTmpResult : number = (valueDeserializer.readNumber() as number)
        const rightTmpResult : number = (valueDeserializer.readNumber() as number)
        const topTmpResult : number = (valueDeserializer.readNumber() as number)
        const bottomTmpResult : number = (valueDeserializer.readNumber() as number)
        let value : componentSnapshot.SnapshotRegion = ({left: leftTmpResult, right: rightTmpResult, top: topTmpResult, bottom: bottomTmpResult} as componentSnapshot.SnapshotRegion)
        return value
    }
}
export class componentSnapshot_SnapshotOptions_serializer {
    public static write(buffer: SerializerBase, value: componentSnapshot.SnapshotOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForScale  = value.scale
        if (valueHolderForScale !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForScaleTmpValue  = valueHolderForScale!
            valueSerializer.writeNumber(valueHolderForScaleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForWaitUntilRenderFinished  = value.waitUntilRenderFinished
        if (valueHolderForWaitUntilRenderFinished !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForWaitUntilRenderFinishedTmpValue  = valueHolderForWaitUntilRenderFinished!
            valueSerializer.writeBoolean(valueHolderForWaitUntilRenderFinishedTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForRegion  = value.region
        if (valueHolderForRegion !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForRegionTmpValue  = valueHolderForRegion!
            if (valueHolderForRegionTmpValue instanceof componentSnapshot.SnapshotRegion) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForRegionTmpValueForIdx0  = valueHolderForRegionTmpValue as componentSnapshot.SnapshotRegion
                componentSnapshot_SnapshotRegion_serializer.write(valueSerializer, valueHolderForRegionTmpValueForIdx0)
            } else if (valueHolderForRegionTmpValue instanceof componentSnapshot.LocalizedSnapshotRegion) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForRegionTmpValueForIdx1  = valueHolderForRegionTmpValue as componentSnapshot.LocalizedSnapshotRegion
                componentSnapshot_LocalizedSnapshotRegion_serializer.write(valueSerializer, valueHolderForRegionTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): componentSnapshot.SnapshotOptions {
        let valueDeserializer : DeserializerBase = buffer
        const scaleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let scaleTmpBuf : number | undefined
        if ((scaleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            scaleTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const scaleTmpResult : number | undefined = scaleTmpBuf
        const waitUntilRenderFinishedTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let waitUntilRenderFinishedTmpBuf : boolean | undefined
        if ((waitUntilRenderFinishedTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            waitUntilRenderFinishedTmpBuf = valueDeserializer.readBoolean()
        }
        const waitUntilRenderFinishedTmpResult : boolean | undefined = waitUntilRenderFinishedTmpBuf
        const regionTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let regionTmpBuf : componentSnapshot.SnapshotRegionType | undefined
        if ((regionTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const regionTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let regionTmpBuf_ : componentSnapshot.SnapshotRegion | componentSnapshot.LocalizedSnapshotRegion | undefined
            if (regionTmpBuf_UnionSelector == (0).toChar()) {
                regionTmpBuf_ = componentSnapshot_SnapshotRegion_serializer.read(valueDeserializer)
            } else if (regionTmpBuf_UnionSelector == (1).toChar()) {
                regionTmpBuf_ = componentSnapshot_LocalizedSnapshotRegion_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for regionTmpBuf_ has to be chosen through deserialisation.")
            }
            regionTmpBuf = (regionTmpBuf_ as componentSnapshot.SnapshotRegion | componentSnapshot.LocalizedSnapshotRegion)
        }
        const regionTmpResult : componentSnapshot.SnapshotRegionType | undefined = regionTmpBuf
        let value : componentSnapshot.SnapshotOptions = ({scale: scaleTmpResult, waitUntilRenderFinished: waitUntilRenderFinishedTmpResult, region: regionTmpResult} as componentSnapshot.SnapshotOptions)
        return value
    }
}
export namespace componentSnapshot {
    export interface SnapshotRegion {
        left: number;
        right: number;
        top: number;
        bottom: number;
    }
    export interface LocalizedSnapshotRegion {
        start: number;
        end: number;
        top: number;
        bottom: number;
    }
    export type SnapshotRegionType = componentSnapshot.SnapshotRegion | componentSnapshot.LocalizedSnapshotRegion;
    export interface SnapshotOptions {
        scale?: number;
        waitUntilRenderFinished?: boolean;
        region?: componentSnapshot.SnapshotRegionType;
    }
    export function getSync(id: string, options?: SnapshotOptions | undefined): image.PixelMap {
        return GlobalScope.componentSnapshot_getSync(id, options)
    }
}
