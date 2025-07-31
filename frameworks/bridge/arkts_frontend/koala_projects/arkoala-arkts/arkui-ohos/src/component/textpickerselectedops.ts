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
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"
export class TextPickerSelectedOps {
    public static registerTextPickerSelectedCallback(node: KPointer, selected: number | Array<number>, callback: TextPickerSelectedCallback): KPointer {
        const node_casted = node as (KPointer)
        const selected_casted = selected as (number | Array<number>)
        const callback_casted = callback as (TextPickerSelectedCallback)
        return TextPickerSelectedOps.registerTextPickerSelectedCallback_serialize(node_casted, selected_casted, callback_casted)
    }
    private static registerTextPickerSelectedCallback_serialize(node: KPointer, selected: number | Array<number>, callback: TextPickerSelectedCallback): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        let selected_type : int32 = RuntimeType.UNDEFINED
        selected_type = runtimeType(selected)
        if (RuntimeType.NUMBER == selected_type) {
            thisSerializer.writeInt8(0 as int32)
            const selected_0  = selected as number
            thisSerializer.writeNumber(selected_0)
        }
        else if (RuntimeType.OBJECT == selected_type) {
            thisSerializer.writeInt8(1 as int32)
            const selected_1  = selected as Array<number>
            thisSerializer.writeInt32(selected_1.length as int32)
            for (let i = 0; i < selected_1.length; i++) {
                const selected_1_element : number = selected_1[i]
                thisSerializer.writeNumber(selected_1_element)
            }
        }
        thisSerializer.holdAndWriteCallback(callback)
        const retval  = ArkUIGeneratedNativeModule._TextPickerSelectedOps_registerTextPickerSelectedCallback(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
}
export type TextPickerSelectedCallback = (selected: number | Array<number>) => void;
