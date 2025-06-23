/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import { Resource } from "global.resource"
import { ResourceStr } from "./units"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"
export class SelectOps {
    public static registerSelectedCallback(node: KPointer, numCount: number | Resource, callback: SelectSelectedCallback): KPointer {
        const node_casted = node as (KPointer)
        const numCount_casted = numCount as (number | Resource)
        const callback_casted = callback as (SelectSelectedCallback)
        return SelectOps.registerSelectedCallback_serialize(node_casted, numCount_casted, callback_casted)
    }
    public static registerValueCallback(node: KPointer, resStr: ResourceStr, callback: SelectValueCallback): KPointer {
        const node_casted = node as (KPointer)
        const resStr_casted = resStr as (ResourceStr)
        const callback_casted = callback as (SelectValueCallback)
        return SelectOps.registerValueCallback_serialize(node_casted, resStr_casted, callback_casted)
    }
    private static registerSelectedCallback_serialize(node: KPointer, numCount: number | Resource, callback: SelectSelectedCallback): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        let numCount_type : int32 = RuntimeType.UNDEFINED
        numCount_type = runtimeType(numCount)
        if (RuntimeType.NUMBER == numCount_type) {
            thisSerializer.writeInt8(0 as int32)
            const numCount_0  = numCount as number
            thisSerializer.writeNumber(numCount_0)
        }
        else if (RuntimeType.OBJECT == numCount_type) {
            thisSerializer.writeInt8(1 as int32)
            const numCount_1  = numCount as Resource
            thisSerializer.writeResource(numCount_1)
        }
        thisSerializer.holdAndWriteCallback(callback)
        const retval  = ArkUIGeneratedNativeModule._SelectOps_registerSelectedCallback(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private static registerValueCallback_serialize(node: KPointer, resStr: ResourceStr, callback: SelectValueCallback): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        let resStr_type : int32 = RuntimeType.UNDEFINED
        resStr_type = runtimeType(resStr)
        if (RuntimeType.STRING == resStr_type) {
            thisSerializer.writeInt8(0 as int32)
            const resStr_0  = resStr as string
            thisSerializer.writeString(resStr_0)
        }
        else if (RuntimeType.OBJECT == resStr_type) {
            thisSerializer.writeInt8(1 as int32)
            const resStr_1  = resStr as Resource
            thisSerializer.writeResource(resStr_1)
        }
        thisSerializer.holdAndWriteCallback(callback)
        const retval  = ArkUIGeneratedNativeModule._SelectOps_registerValueCallback(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
}
export type SelectSelectedCallback = (selected: number | Resource) => void;
export type SelectValueCallback = (value: ResourceStr) => void;
