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

import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import {CustomBuilder, SheetOptions, ContentCoverOptions} from "./common"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, InteropNativeModule, MaterializedBase, NativeBuffer, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"
export class BindSheetOps {
    public static registerSheetShowCallback(node: KPointer, value: boolean, callback: ShowCallback, builder: CustomBuilder | undefined, options?: SheetOptions): KPointer {
        const node_casted = node as (KPointer)
        const value_casted = value as (boolean)
        const callback_casted = callback as (ShowCallback)
        return BindSheetOps.registerSheetShowCallback_serialize(node_casted, value_casted, callback_casted, builder, options)
    }
    private static registerSheetShowCallback_serialize(node: KPointer, value: boolean, callback: ShowCallback, builder: CustomBuilder | undefined, options?: SheetOptions): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(callback)

        let builder_type : int32 = RuntimeType.UNDEFINED
        builder_type = runtimeType(builder)
        thisSerializer.writeInt8(builder_type as int32)
        if ((RuntimeType.UNDEFINED) != (builder_type)) {
            const builder_value  = builder!
            thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(builder_value))
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeSheetOptions(options_value)
        }
        const retval  = ArkUIGeneratedNativeModule._BindSheetOps_registerShowCallback(node, value ? 1 : 0, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }

    public static registerBindContentCoverCallback(node: KPointer, value: boolean, callback: ShowCallback, builder: CustomBuilder | undefined, options?: ContentCoverOptions): KPointer {
        const node_casted = node as (KPointer)
        const value_casted = value as (boolean)
        const callback_casted = callback as (ShowCallback)
        return BindSheetOps.registerBindContentCoverCallback_serialize(node_casted, value_casted, callback_casted, builder, options)
    }

    private static registerBindContentCoverCallback_serialize(node: KPointer, value: boolean, callback: ShowCallback, builder: CustomBuilder | undefined, options?: ContentCoverOptions): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(callback)

        let builder_type : int32 = RuntimeType.UNDEFINED
        builder_type = runtimeType(builder)
        thisSerializer.writeInt8(builder_type as int32)
        if ((RuntimeType.UNDEFINED) != (builder_type)) {
            const builder_value  = builder!
            thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(builder_value))
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeContentCoverOptions(options_value)
        }
        const retval  = ArkUIGeneratedNativeModule._BindSheetOps_registerBindContentCoverCallback(node, value ? 1 : 0, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }

}
export type ShowCallback = (value: boolean) => void;