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

import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, isInstanceOf } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { isResource, isPadding } from "./../utils"
import { Deserializer, createDeserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ArkUIGeneratedNativeModule } from "./ArkUIGeneratedNativeModule"
export class UnifiedDataInternal {
    public static fromPtr(ptr: KPointer): UnifiedData {
        const obj: UnifiedData = new UnifiedData()
        obj.peer = new Finalizable(ptr, UnifiedData.getFinalizer())
        return obj
    }
}
export class UnifiedData implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_unifieddata(): KPointer {
        const retval = ArkUIGeneratedNativeModule._UnifiedData_ctor()
        return retval
    }
     constructor() {
        const ctorPtr: KPointer = UnifiedData.ctor_unifieddata()
        this.peer = new Finalizable(ctorPtr, UnifiedData.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._UnifiedData_getFinalizer()
    }
    public hasType(UnifiedData_type: string): boolean {
        const UnifiedData_type_casted = UnifiedData_type as (string)
        return this.hasType_serialize(UnifiedData_type_casted)
    }
    public getTypes(): Array<string> {
        return this.getTypes_serialize()
    }
    private hasType_serialize(UnifiedData_type: string): boolean {
        const retval = ArkUIGeneratedNativeModule._UnifiedData_hasType(this.peer!.ptr, UnifiedData_type)
        return retval
    }
    private getTypes_serialize(): Array<string> {
        const retval = ArkUIGeneratedNativeModule._UnifiedData_getTypes(this.peer!.ptr)
        let retvalDeserializer: Deserializer = new Deserializer(retval.buffer, retval.byteLength)
        const buffer_length: int32 = retvalDeserializer.readInt32()
        let buffer: Array<string> = new Array<string>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            buffer[buffer_i] = (retvalDeserializer.readString() as string)
        }
        const returnResult: Array<string> = buffer
        return returnResult
    }
}
