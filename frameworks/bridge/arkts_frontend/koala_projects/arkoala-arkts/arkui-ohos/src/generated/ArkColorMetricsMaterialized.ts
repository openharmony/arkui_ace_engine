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

import { ResourceColor } from "./../component/units"
import { Color } from "./../component/enums"
import { Resource } from "global/resource";
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export class ColorMetricsInternal {
    public static fromPtr(ptr: KPointer): ColorMetrics {
        const obj : ColorMetrics = new ColorMetrics()
        obj.peer = new Finalizable(ptr, ColorMetrics.getFinalizer())
        return obj
    }
}
export class ColorMetrics implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get color(): string {
        return this.getColor()
    }
    get red(): number {
        return this.getRed()
    }
    get green(): number {
        return this.getGreen()
    }
    get blue(): number {
        return this.getBlue()
    }
    get alpha(): number {
        return this.getAlpha()
    }
    static ctor_colormetrics(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._ColorMetrics_ctor()
        return retval
    }
    constructor() {
        // Constructor does not have parameters.
        // It means that the static method call invokes ctor method as well
        // when all arguments are undefined.
        const ctorPtr : KPointer = ColorMetrics.ctor_colormetrics()
        this.peer = new Finalizable(ctorPtr, ColorMetrics.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._ColorMetrics_getFinalizer()
    }
    public static numeric(value: number): ColorMetrics {
        const value_casted = value as (number)
        return ColorMetrics.numeric_serialize(value_casted)
    }
    public static rgba(red: number, green: number, blue: number, alpha?: number): ColorMetrics {
        const red_casted = red as (number)
        const green_casted = green as (number)
        const blue_casted = blue as (number)
        const alpha_casted = alpha as (number | undefined)
        return ColorMetrics.rgba_serialize(red_casted, green_casted, blue_casted, alpha_casted)
    }
    public static resourceColor(color: ResourceColor): ColorMetrics {
        const color_casted = color as (ResourceColor)
        return ColorMetrics.resourceColor_serialize(color_casted)
    }
    public blendColor(overlayColor: ColorMetrics): ColorMetrics {
        const overlayColor_casted = overlayColor as (ColorMetrics)
        return this.blendColor_serialize(overlayColor_casted)
    }
    private getColor(): string {
        return this.getColor_serialize()
    }
    private getRed(): number {
        return this.getRed_serialize()
    }
    private getGreen(): number {
        return this.getGreen_serialize()
    }
    private getBlue(): number {
        return this.getBlue_serialize()
    }
    private getAlpha(): number {
        return this.getAlpha_serialize()
    }
    private static numeric_serialize(value: number): ColorMetrics {
        const retval  = ArkUIGeneratedNativeModule._ColorMetrics_numeric(value)
        const obj : ColorMetrics = ColorMetricsInternal.fromPtr(retval)
        return obj
    }
    private static rgba_serialize(red: number, green: number, blue: number, alpha?: number): ColorMetrics {
        const thisSerializer : Serializer = Serializer.hold()
        let alpha_type : int32 = RuntimeType.UNDEFINED
        alpha_type = runtimeType(alpha)
        thisSerializer.writeInt8(alpha_type as int32)
        if ((RuntimeType.UNDEFINED) != (alpha_type)) {
            const alpha_value  = alpha!
            thisSerializer.writeNumber(alpha_value)
        }
        const retval  = ArkUIGeneratedNativeModule._ColorMetrics_rgba(red, green, blue, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : ColorMetrics = ColorMetricsInternal.fromPtr(retval)
        return obj
    }
    private static resourceColor_serialize(color: ResourceColor): ColorMetrics {
        const thisSerializer : Serializer = Serializer.hold()
        let color_type : int32 = RuntimeType.UNDEFINED
        color_type = runtimeType(color)
        if (TypeChecker.isColor(color)) {
            thisSerializer.writeInt8(0 as int32)
            const color_0  = color as Color
            thisSerializer.writeInt32(color_0.valueOf())
        }
        else if (RuntimeType.NUMBER == color_type) {
            thisSerializer.writeInt8(1 as int32)
            const color_1  = color as number
            thisSerializer.writeNumber(color_1)
        }
        else if (RuntimeType.STRING == color_type) {
            thisSerializer.writeInt8(2 as int32)
            const color_2  = color as string
            thisSerializer.writeString(color_2)
        }
        else if (RuntimeType.OBJECT == color_type) {
            thisSerializer.writeInt8(3 as int32)
            const color_3  = color as Resource
            thisSerializer.writeResource(color_3)
        }
        const retval  = ArkUIGeneratedNativeModule._ColorMetrics_resourceColor(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : ColorMetrics = ColorMetricsInternal.fromPtr(retval)
        return obj
    }
    private blendColor_serialize(overlayColor: ColorMetrics): ColorMetrics {
        const retval  = ArkUIGeneratedNativeModule._ColorMetrics_blendColor(this.peer!.ptr, toPeerPtr(overlayColor))
        const obj : ColorMetrics = ColorMetricsInternal.fromPtr(retval)
        return obj
    }
    private getColor_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._ColorMetrics_getColor(this.peer!.ptr)
        return retval
    }
    private getRed_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._ColorMetrics_getRed(this.peer!.ptr)
        return retval
    }
    private getGreen_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._ColorMetrics_getGreen(this.peer!.ptr)
        return retval
    }
    private getBlue_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._ColorMetrics_getBlue(this.peer!.ptr)
        return retval
    }
    private getAlpha_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._ColorMetrics_getAlpha(this.peer!.ptr)
        return retval
    }
}
