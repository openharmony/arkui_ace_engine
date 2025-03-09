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
export class CanvasPathInternal {
    public static fromPtr(ptr: KPointer): CanvasPath {
        const obj: CanvasPath = new CanvasPath()
        obj.peer = new Finalizable(ptr, CanvasPath.getFinalizer())
        return obj
    }
}
export class CanvasPath implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_canvaspath(): KPointer {
        const retval = ArkUIGeneratedNativeModule._CanvasPath_ctor()
        return retval
    }
     constructor() {
        const ctorPtr: KPointer = CanvasPath.ctor_canvaspath()
        this.peer = new Finalizable(ctorPtr, CanvasPath.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._CanvasPath_getFinalizer()
    }
    public arc(x: number, y: number, radius: number, startAngle: number, endAngle: number, counterclockwise?: boolean): void {
        const x_casted = x as (number)
        const y_casted = y as (number)
        const radius_casted = radius as (number)
        const startAngle_casted = startAngle as (number)
        const endAngle_casted = endAngle as (number)
        const counterclockwise_casted = counterclockwise as (boolean | undefined)
        this?.arc_serialize(x_casted, y_casted, radius_casted, startAngle_casted, endAngle_casted, counterclockwise_casted)
        return
    }
    public arcTo(x1: number, y1: number, x2: number, y2: number, radius: number): void {
        const x1_casted = x1 as (number)
        const y1_casted = y1 as (number)
        const x2_casted = x2 as (number)
        const y2_casted = y2 as (number)
        const radius_casted = radius as (number)
        this?.arcTo_serialize(x1_casted, y1_casted, x2_casted, y2_casted, radius_casted)
        return
    }
    public bezierCurveTo(cp1x: number, cp1y: number, cp2x: number, cp2y: number, x: number, y: number): void {
        const cp1x_casted = cp1x as (number)
        const cp1y_casted = cp1y as (number)
        const cp2x_casted = cp2x as (number)
        const cp2y_casted = cp2y as (number)
        const x_casted = x as (number)
        const y_casted = y as (number)
        this?.bezierCurveTo_serialize(cp1x_casted, cp1y_casted, cp2x_casted, cp2y_casted, x_casted, y_casted)
        return
    }
    public closePath(): void {
        this?.closePath_serialize()
        return
    }
    public ellipse(x: number, y: number, radiusX: number, radiusY: number, rotation: number, startAngle: number, endAngle: number, counterclockwise?: boolean): void {
        const x_casted = x as (number)
        const y_casted = y as (number)
        const radiusX_casted = radiusX as (number)
        const radiusY_casted = radiusY as (number)
        const rotation_casted = rotation as (number)
        const startAngle_casted = startAngle as (number)
        const endAngle_casted = endAngle as (number)
        const counterclockwise_casted = counterclockwise as (boolean | undefined)
        this?.ellipse_serialize(x_casted, y_casted, radiusX_casted, radiusY_casted, rotation_casted, startAngle_casted, endAngle_casted, counterclockwise_casted)
        return
    }
    public lineTo(x: number, y: number): void {
        const x_casted = x as (number)
        const y_casted = y as (number)
        this?.lineTo_serialize(x_casted, y_casted)
        return
    }
    public moveTo(x: number, y: number): void {
        const x_casted = x as (number)
        const y_casted = y as (number)
        this?.moveTo_serialize(x_casted, y_casted)
        return
    }
    public quadraticCurveTo(cpx: number, cpy: number, x: number, y: number): void {
        const cpx_casted = cpx as (number)
        const cpy_casted = cpy as (number)
        const x_casted = x as (number)
        const y_casted = y as (number)
        this?.quadraticCurveTo_serialize(cpx_casted, cpy_casted, x_casted, y_casted)
        return
    }
    public rect(x: number, y: number, w: number, h: number): void {
        const x_casted = x as (number)
        const y_casted = y as (number)
        const w_casted = w as (number)
        const h_casted = h as (number)
        this?.rect_serialize(x_casted, y_casted, w_casted, h_casted)
        return
    }
    private arc_serialize(x: number, y: number, radius: number, startAngle: number, endAngle: number, counterclockwise?: boolean): void {
        const thisSerializer: Serializer = Serializer.hold()
        let counterclockwise_type: int32 = RuntimeType.UNDEFINED
        counterclockwise_type = runtimeType(counterclockwise)
        thisSerializer.writeInt8(counterclockwise_type)
        if ((RuntimeType.UNDEFINED) != (counterclockwise_type)) {
            const counterclockwise_value = counterclockwise!
            thisSerializer.writeBoolean(counterclockwise_value)
        }
        ArkUIGeneratedNativeModule._CanvasPath_arc(this.peer!.ptr, x, y, radius, startAngle, endAngle, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    private arcTo_serialize(x1: number, y1: number, x2: number, y2: number, radius: number): void {
        ArkUIGeneratedNativeModule._CanvasPath_arcTo(this.peer!.ptr, x1, y1, x2, y2, radius)
    }
    private bezierCurveTo_serialize(cp1x: number, cp1y: number, cp2x: number, cp2y: number, x: number, y: number): void {
        ArkUIGeneratedNativeModule._CanvasPath_bezierCurveTo(this.peer!.ptr, cp1x, cp1y, cp2x, cp2y, x, y)
    }
    private closePath_serialize(): void {
        ArkUIGeneratedNativeModule._CanvasPath_closePath(this.peer!.ptr)
    }
    private ellipse_serialize(x: number, y: number, radiusX: number, radiusY: number, rotation: number, startAngle: number, endAngle: number, counterclockwise?: boolean): void {
        const thisSerializer: Serializer = Serializer.hold()
        let counterclockwise_type: int32 = RuntimeType.UNDEFINED
        counterclockwise_type = runtimeType(counterclockwise)
        thisSerializer.writeInt8(counterclockwise_type)
        if ((RuntimeType.UNDEFINED) != (counterclockwise_type)) {
            const counterclockwise_value = counterclockwise!
            thisSerializer.writeBoolean(counterclockwise_value)
        }
        ArkUIGeneratedNativeModule._CanvasPath_ellipse(this.peer!.ptr, x, y, radiusX, radiusY, rotation, startAngle, endAngle, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    private lineTo_serialize(x: number, y: number): void {
        ArkUIGeneratedNativeModule._CanvasPath_lineTo(this.peer!.ptr, x, y)
    }
    private moveTo_serialize(x: number, y: number): void {
        ArkUIGeneratedNativeModule._CanvasPath_moveTo(this.peer!.ptr, x, y)
    }
    private quadraticCurveTo_serialize(cpx: number, cpy: number, x: number, y: number): void {
        ArkUIGeneratedNativeModule._CanvasPath_quadraticCurveTo(this.peer!.ptr, cpx, cpy, x, y)
    }
    private rect_serialize(x: number, y: number, w: number, h: number): void {
        ArkUIGeneratedNativeModule._CanvasPath_rect(this.peer!.ptr, x, y, w, h)
    }
}
