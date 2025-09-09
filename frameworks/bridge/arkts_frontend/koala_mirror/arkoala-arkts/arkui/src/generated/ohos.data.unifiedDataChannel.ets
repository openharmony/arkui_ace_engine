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

import { SerializerBase, DeserializerBase, CallbackResource, InteropNativeModule, MaterializedBase, Tags, RuntimeType, runtimeType, toPeerPtr, nullptr, KPointer, NativeBuffer, KSerializerBuffer, KUint8ArrayPtr, Finalizable, registerCallback, wrapCallback, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { CallbackKind } from "./peers/CallbackKind"
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
        const value_summary  = value.summary
        valueSerializer.writeInt32((value_summary.size).toInt())
        for (const pair of value_summary) {
            const value_summary_key = pair[0]
            const value_summary_value = pair[1]
            valueSerializer.writeString(value_summary_key)
            valueSerializer.writeInt64(value_summary_value)
        }
        const value_totalSize  = value.totalSize
        valueSerializer.writeInt64(value_totalSize)
    }
    public static read(buffer: DeserializerBase): unifiedDataChannel.Summary {
        let valueDeserializer : DeserializerBase = buffer
        const summary_buf_size : int32 = valueDeserializer.readInt32()
        let summary_buf : Map<string, int64> = new Map<string, int64>()
        // TODO: TS map resize
        for (let summary_buf_i = 0; summary_buf_i < summary_buf_size; summary_buf_i++) {
            const summary_buf_key : string = (valueDeserializer.readString() as string)
            const summary_buf_value : int64 = valueDeserializer.readInt64()
            summary_buf.set(summary_buf_key, summary_buf_value)
        }
        const summary_result : Map<string, int64> = summary_buf
        const totalSize_result : int64 = valueDeserializer.readInt64()
        let value : unifiedDataChannel.Summary = ({summary: summary_result, totalSize: totalSize_result} as unifiedDataChannel.Summary)
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
            const buffer_length : int32 = retvalDeserializer.readInt32()
            let buffer : Array<string> = new Array<string>(buffer_length)
            for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
                buffer[buffer_i] = (retvalDeserializer.readString() as string)
            }
            const returnResult : Array<string> = buffer
            return returnResult
        }
    }
    export interface Summary {
        summary: Map<string, int64>;
        totalSize: int64;
    }
}
