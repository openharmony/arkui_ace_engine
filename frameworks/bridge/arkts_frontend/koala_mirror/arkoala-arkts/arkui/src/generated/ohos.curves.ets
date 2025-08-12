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
import { GlobalScope } from "./GlobalScope"
export class curves_ICurve_serializer {
    public static write(buffer: SerializerBase, value: curves.ICurve): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): curves.ICurve {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return curves.ICurveInternal.fromPtr(ptr)
    }
}
export namespace curves {
    export interface ICurve {
        interpolate(fraction: number): number
    }
    export class ICurveInternal implements MaterializedBase,ICurve {
        peer?: Finalizable | undefined = undefined
        public getPeer(): Finalizable | undefined {
            return this.peer
        }
        constructor(peerPtr: KPointer) {
            this.peer = new Finalizable(peerPtr, ICurveInternal.getFinalizer())
        }
        constructor() {
            this(ICurveInternal.construct())
        }
        static construct(): KPointer {
            const retval  = ArkUIGeneratedNativeModule._curves_ICurve_construct()
            return retval
        }
        static getFinalizer(): KPointer {
            return ArkUIGeneratedNativeModule._curves_ICurve_getFinalizer()
        }
        public static fromPtr(ptr: KPointer): ICurveInternal {
            return new ICurveInternal(ptr)
        }
        public interpolate(fraction: number): number {
            const fraction_casted = fraction as (number)
            return this.interpolate_serialize(fraction_casted)
        }
        private interpolate_serialize(fraction: number): number {
            const retval  = ArkUIGeneratedNativeModule._curves_ICurve_interpolate(this.peer!.ptr, fraction)
            return retval
        }
    }
    export enum Curve {
        LINEAR = 0,
        Linear = 0,
        EASE = 1,
        Ease = 1,
        EASE_IN = 2,
        EaseIn = 2,
        EASE_OUT = 3,
        EaseOut = 3,
        EASE_IN_OUT = 4,
        EaseInOut = 4,
        FAST_OUT_SLOW_IN = 5,
        FastOutSlowIn = 5,
        LINEAR_OUT_SLOW_IN = 6,
        LinearOutSlowIn = 6,
        FAST_OUT_LINEAR_IN = 7,
        FastOutLinearIn = 7,
        EXTREME_DECELERATION = 8,
        ExtremeDeceleration = 8,
        SHARP = 9,
        Sharp = 9,
        RHYTHM = 10,
        Rhythm = 10,
        SMOOTH = 11,
        Smooth = 11,
        FRICTION = 12,
        Friction = 12
    }
    export function initCurve(curve?: Curve | undefined): ICurve {
        return GlobalScope.curves_initCurve(curve)
    }
    export function stepsCurve(count: number, end: boolean): ICurve {
        return GlobalScope.curves_stepsCurve(count, end)
    }
    export function customCurve(interpolate: ((fraction: number) => number)): ICurve {
        return GlobalScope.curves_customCurve(interpolate)
    }
    export function cubicBezierCurve(x1: number, y1: number, x2: number, y2: number): ICurve {
        return GlobalScope.curves_cubicBezierCurve(x1, y1, x2, y2)
    }
    export function springCurve(velocity: number, mass: number, stiffness: number, damping: number): ICurve {
        return GlobalScope.curves_springCurve(velocity, mass, stiffness, damping)
    }
    export function springMotion(response?: number | undefined, dampingFraction?: number | undefined, overlapDuration?: number | undefined): ICurve {
        return GlobalScope.curves_springMotion(response, dampingFraction, overlapDuration)
    }
    export function responsiveSpringMotion(response?: number | undefined, dampingFraction?: number | undefined, overlapDuration?: number | undefined): ICurve {
        return GlobalScope.curves_responsiveSpringMotion(response, dampingFraction, overlapDuration)
    }
    export function interpolatingSpring(velocity: number, mass: number, stiffness: number, damping: number): ICurve {
        return GlobalScope.curves_interpolatingSpring(velocity, mass, stiffness, damping)
    }
}
