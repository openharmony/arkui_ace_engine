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

import { ResourceColor } from "./ArkUnitsInterfaces"
import { Color } from "./ArkEnumsInterfaces"
import { Resource } from "./ArkResourceInterfaces"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, isInstanceOf } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { isResource, isPadding } from "./../utils"
import { Deserializer, createDeserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ArkUIGeneratedNativeModule } from "./ArkUIGeneratedNativeModule"
export class ProgressMaskInternal {
    public static fromPtr(ptr: KPointer): ProgressMask {
        const obj: ProgressMask = new ProgressMask(undefined, undefined, undefined)
        obj.peer = new Finalizable(ptr, ProgressMask.getFinalizer())
        return obj
    }
}
export class ProgressMask implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_progressmask(value: number, total: number, color: ResourceColor): KPointer {
        const thisSerializer: Serializer = Serializer.hold()
        let color_type: int32 = RuntimeType.UNDEFINED
        color_type = runtimeType(color)
        if (((RuntimeType.NUMBER) == (color_type)) && ((unsafeCast<int32>(color)) >= (0)) && ((unsafeCast<int32>(color)) <= (11))) {
            thisSerializer.writeInt8(0)
            const color_0 = unsafeCast<Color>(color)
            thisSerializer.writeInt32(color_0)
        }
        else if (RuntimeType.NUMBER == color_type) {
            thisSerializer.writeInt8(1)
            const color_1 = unsafeCast<number>(color)
            thisSerializer.writeNumber(color_1)
        }
        else if (RuntimeType.STRING == color_type) {
            thisSerializer.writeInt8(2)
            const color_2 = unsafeCast<string>(color)
            thisSerializer.writeString(color_2)
        }
        else if (RuntimeType.OBJECT == color_type) {
            thisSerializer.writeInt8(3)
            const color_3 = unsafeCast<Resource>(color)
            thisSerializer.writeResource(color_3)
        }
        const retval = ArkUIGeneratedNativeModule._ProgressMask_ctor(value, total, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
     constructor(value?: number, total?: number, color?: ResourceColor) {
        if (((value) !== (undefined)) || ((total) !== (undefined)) || ((color) !== (undefined)))
        {
            const ctorPtr: KPointer = ProgressMask.ctor_progressmask((value)!, (total)!, (color)!)
            this.peer = new Finalizable(ctorPtr, ProgressMask.getFinalizer())
        }
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._ProgressMask_getFinalizer()
    }
    public updateProgress(value: number): void {
        const value_casted = value as (number)
        this?.updateProgress_serialize(value_casted)
        return
    }
    public updateColor(value: ResourceColor): void {
        const value_casted = value as (ResourceColor)
        this?.updateColor_serialize(value_casted)
        return
    }
    public enableBreathingAnimation(value: boolean): void {
        const value_casted = value as (boolean)
        this?.enableBreathingAnimation_serialize(value_casted)
        return
    }
    private updateProgress_serialize(value: number): void {
        ArkUIGeneratedNativeModule._ProgressMask_updateProgress(this.peer!.ptr, value)
    }
    private updateColor_serialize(value: ResourceColor): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (((RuntimeType.NUMBER) == (value_type)) && ((unsafeCast<int32>(value)) >= (0)) && ((unsafeCast<int32>(value)) <= (11))) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<Color>(value)
            thisSerializer.writeInt32(value_0)
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<number>(value)
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2)
            const value_2 = unsafeCast<string>(value)
            thisSerializer.writeString(value_2)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(3)
            const value_3 = unsafeCast<Resource>(value)
            thisSerializer.writeResource(value_3)
        }
        ArkUIGeneratedNativeModule._ProgressMask_updateColor(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    private enableBreathingAnimation_serialize(value: boolean): void {
        ArkUIGeneratedNativeModule._ProgressMask_enableBreathingAnimation(this.peer!.ptr, +value)
    }
}
