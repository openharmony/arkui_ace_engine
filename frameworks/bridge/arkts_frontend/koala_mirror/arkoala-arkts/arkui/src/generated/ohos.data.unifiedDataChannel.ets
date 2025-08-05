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

import { SerializerBase, DeserializerBase, CallbackResource, InteropNativeModule, MaterializedBase, Tags, RuntimeType, runtimeType, toPeerPtr, nullptr, KPointer, NativeBuffer, KSerializerBuffer, KUint8ArrayPtr, Finalizable, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
export class unifiedDataChannel_UnifiedData_serializer {
    public static write(buffer: SerializerBase, value: unifiedDataChannel.UnifiedData): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): unifiedDataChannel.UnifiedData {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return unifiedDataChannel.UnifiedDataInternal.fromPtr(ptr)
    }
}
export class unifiedDataChannel_Summary_serializer {
    public static write(buffer: SerializerBase, value: unifiedDataChannel.Summary): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForSummary  = value.summary
        valueSerializer.writeInt32((valueHolderForSummary.size).toInt())
        for (const pair of valueHolderForSummary) {
            const valueHolderForSummaryKeyVar = pair[0]
            const valueHolderForSummaryValueVar = pair[1]
            valueSerializer.writeString(valueHolderForSummaryKeyVar)
            valueSerializer.writeInt64(valueHolderForSummaryValueVar)
        }
        const valueHolderForTotalSize  = value.totalSize
        valueSerializer.writeInt64(valueHolderForTotalSize)
    }
    public static read(buffer: DeserializerBase): unifiedDataChannel.Summary {
        let valueDeserializer : DeserializerBase = buffer
        const summaryTmpBufSizeVar : int32 = valueDeserializer.readInt32()
        let summaryTmpBuf : Map<string, int64> = new Map<string, int64>()
        // TODO: TS map resize
        for (let summaryTmpBufIVar = 0; summaryTmpBufIVar < summaryTmpBufSizeVar; summaryTmpBufIVar++) {
            const summaryTmpBufKeyVar : string = (valueDeserializer.readString() as string)
            const summaryTmpBufValueVar : int64 = valueDeserializer.readInt64()
            summaryTmpBuf.set(summaryTmpBufKeyVar, summaryTmpBufValueVar)
        }
        const summaryTmpResult : Map<string, int64> = summaryTmpBuf
        const totalSizeTmpResult : int64 = valueDeserializer.readInt64()
        let value : unifiedDataChannel.Summary = ({summary: summaryTmpResult, totalSize: totalSizeTmpResult} as unifiedDataChannel.Summary)
        return value
    }
}
export namespace unifiedDataChannel {
    export class UnifiedDataInternal {
        public static fromPtr(ptr: KPointer): unifiedDataChannel.UnifiedData {
            return new unifiedDataChannel.UnifiedData(ptr)
        }
    }
    export class UnifiedData implements MaterializedBase {
        peer?: Finalizable | undefined = undefined
        public getPeer(): Finalizable | undefined {
            return this.peer
        }
        constructor(peerPtr: KPointer) {
            this.peer = new Finalizable(peerPtr, UnifiedData.getFinalizer())
        }
        constructor() {
            this(UnifiedData.construct())
        }
        static construct(): KPointer {
            const retval  = ArkUIGeneratedNativeModule._unifiedDataChannel_UnifiedData_construct()
            return retval
        }
        static getFinalizer(): KPointer {
            return ArkUIGeneratedNativeModule._unifiedDataChannel_UnifiedData_getFinalizer()
        }
        public hasType(UnifiedData_type: string): boolean {
            const UnifiedData_type_casted = UnifiedData_type as (string)
            return this.hasType_serialize(UnifiedData_type_casted)
        }
        public getTypes(): Array<string> {
            return this.getTypes_serialize()
        }
        private hasType_serialize(UnifiedData_type: string): boolean {
            const retval  = ArkUIGeneratedNativeModule._unifiedDataChannel_UnifiedData_hasType(this.peer!.ptr, UnifiedData_type)
            return retval
        }
        private getTypes_serialize(): Array<string> {
            const retval  = ArkUIGeneratedNativeModule._unifiedDataChannel_UnifiedData_getTypes(this.peer!.ptr)
            let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
            const bufferLength : int32 = retvalDeserializer.readInt32()
            let buffer : Array<string> = new Array<string>(bufferLength)
            for (let bufferBufCounterI = 0; bufferBufCounterI < bufferLength; bufferBufCounterI++) {
                buffer[bufferBufCounterI] = (retvalDeserializer.readString() as string)
            }
            const returnResult : Array<string> = buffer
            return returnResult
        }
    }
    export interface Summary {
        summary: Map<string, int64>;
        totalSize: int64;
    }
    export interface GetDataParams {
        destUri?: string;
    }
}
