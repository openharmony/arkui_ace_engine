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
import { Tuple_Number_Number_Number } from "./arkui-synthetics"
export interface Filter {
    pixelStretch(stretchSizes: Array<number>, tileMode: TileMode): Filter
    blur(blurRadius: number): Filter
    waterRipple(progress: number, waveCount: number, x: number, y: number, rippleMode: WaterRippleMode): Filter
    flyInFlyOutEffect(degree: number, flyMode: FlyMode): Filter
    distort(distortionK: number): Filter
}
export class FilterInternal implements MaterializedBase,Filter {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_filter(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._Filter_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = FilterInternal.ctor_filter()
        this.peer = new Finalizable(ctorPtr, FilterInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._Filter_getFinalizer()
    }
    public pixelStretch(stretchSizes: Array<number>, tileMode: TileMode): Filter {
        const stretchSizes_casted = stretchSizes as (Array<number>)
        const tileMode_casted = tileMode as (TileMode)
        return this.pixelStretch_serialize(stretchSizes_casted, tileMode_casted)
    }
    public blur(blurRadius: number): Filter {
        const blurRadius_casted = blurRadius as (number)
        return this.blur_serialize(blurRadius_casted)
    }
    public waterRipple(progress: number, waveCount: number, x: number, y: number, rippleMode: WaterRippleMode): Filter {
        const progress_casted = progress as (number)
        const waveCount_casted = waveCount as (number)
        const x_casted = x as (number)
        const y_casted = y as (number)
        const rippleMode_casted = rippleMode as (WaterRippleMode)
        return this.waterRipple_serialize(progress_casted, waveCount_casted, x_casted, y_casted, rippleMode_casted)
    }
    public flyInFlyOutEffect(degree: number, flyMode: FlyMode): Filter {
        const degree_casted = degree as (number)
        const flyMode_casted = flyMode as (FlyMode)
        return this.flyInFlyOutEffect_serialize(degree_casted, flyMode_casted)
    }
    public distort(distortionK: number): Filter {
        const distortionK_casted = distortionK as (number)
        return this.distort_serialize(distortionK_casted)
    }
    private pixelStretch_serialize(stretchSizes: Array<number>, tileMode: TileMode): Filter {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeInt32(stretchSizes.length as int32)
        for (let i = 0; i < stretchSizes.length; i++) {
            const stretchSizes_element : number = stretchSizes[i]
            thisSerializer.writeNumber(stretchSizes_element)
        }
        const retval  = ArkUIGeneratedNativeModule._Filter_pixelStretch(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length(), TypeChecker.TileMode_ToNumeric(tileMode))
        thisSerializer.release()
        const obj : Filter = FilterInternal.fromPtr(retval)
        return obj
    }
    private blur_serialize(blurRadius: number): Filter {
        const retval  = ArkUIGeneratedNativeModule._Filter_blur(this.peer!.ptr, blurRadius)
        const obj : Filter = FilterInternal.fromPtr(retval)
        return obj
    }
    private waterRipple_serialize(progress: number, waveCount: number, x: number, y: number, rippleMode: WaterRippleMode): Filter {
        const retval  = ArkUIGeneratedNativeModule._Filter_waterRipple(this.peer!.ptr, progress, waveCount, x, y, TypeChecker.WaterRippleMode_ToNumeric(rippleMode))
        const obj : Filter = FilterInternal.fromPtr(retval)
        return obj
    }
    private flyInFlyOutEffect_serialize(degree: number, flyMode: FlyMode): Filter {
        const retval  = ArkUIGeneratedNativeModule._Filter_flyInFlyOutEffect(this.peer!.ptr, degree, TypeChecker.FlyMode_ToNumeric(flyMode))
        const obj : Filter = FilterInternal.fromPtr(retval)
        return obj
    }
    private distort_serialize(distortionK: number): Filter {
        const retval  = ArkUIGeneratedNativeModule._Filter_distort(this.peer!.ptr, distortionK)
        const obj : Filter = FilterInternal.fromPtr(retval)
        return obj
    }
    public static fromPtr(ptr: KPointer): FilterInternal {
        const obj : FilterInternal = new FilterInternal()
        obj.peer = new Finalizable(ptr, FilterInternal.getFinalizer())
        return obj
    }
}
export interface VisualEffect {
    backgroundColorBlender(blender: BrightnessBlender): VisualEffect
}
export class VisualEffectInternal implements MaterializedBase,VisualEffect {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_visualeffect(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._VisualEffect_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = VisualEffectInternal.ctor_visualeffect()
        this.peer = new Finalizable(ctorPtr, VisualEffectInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._VisualEffect_getFinalizer()
    }
    public backgroundColorBlender(blender: BrightnessBlender): VisualEffect {
        const blender_casted = blender as (BrightnessBlender)
        return this.backgroundColorBlender_serialize(blender_casted)
    }
    private backgroundColorBlender_serialize(blender: BrightnessBlender): VisualEffect {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeBrightnessBlender(blender)
        const retval  = ArkUIGeneratedNativeModule._VisualEffect_backgroundColorBlender(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : VisualEffect = VisualEffectInternal.fromPtr(retval)
        return obj
    }
    public static fromPtr(ptr: KPointer): VisualEffectInternal {
        const obj : VisualEffectInternal = new VisualEffectInternal()
        obj.peer = new Finalizable(ptr, VisualEffectInternal.getFinalizer())
        return obj
    }
}
export enum TileMode {
    CLAMP = 0,
    REPEAT = 1,
    MIRROR = 2,
    DECAL = 3
}
export enum WaterRippleMode {
    SMALL2MEDIUM_RECV = 0,
    SMALL2MEDIUM_SEND = 1,
    SMALL2SMALL = 2
}
export enum FlyMode {
    BOTTOM = 0,
    TOP = 1
}
export interface BrightnessBlender {
    cubicRate: number;
    quadraticRate: number;
    linearRate: number;
    degree: number;
    saturation: number;
    positiveCoefficient: [ number, number, number ];
    negativeCoefficient: [ number, number, number ];
    fraction: number;
}
export type Blender = BrightnessBlender;
