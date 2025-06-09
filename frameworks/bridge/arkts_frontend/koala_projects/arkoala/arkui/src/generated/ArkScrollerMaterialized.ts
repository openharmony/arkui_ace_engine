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

import { ScrollOptions, ScrollEdgeOptions, ScrollPageOptions, OffsetResult, ScrollAlign, ScrollToIndexOptions, ScrollAnimationOptions } from "./ArkScrollInterfaces"
import { Edge, Axis, Curve } from "./ArkEnumsInterfaces"
import { Length } from "./ArkUnitsInterfaces"
import { RectResult } from "./ArkCommonInterfaces"
import { Resource } from "./ArkResourceInterfaces"
import { ICurve, ICurveInternal } from "./ArkICurveMaterialized"
import { LengthMetrics, LengthMetricsInternal } from "./ArkLengthMetricsMaterialized"
import { LengthUnit } from "./ArkArkuiExternalInterfaces"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, isInstanceOf } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { isResource, isPadding } from "./../utils"
import { Deserializer, createDeserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ArkUIGeneratedNativeModule } from "./ArkUIGeneratedNativeModule"
export class ScrollerInternal {
    public static fromPtr(ptr: KPointer): Scroller {
        const obj: Scroller = new Scroller()
        obj.peer = new Finalizable(ptr, Scroller.getFinalizer())
        return obj
    }
}
export class Scroller implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_scroller(): KPointer {
        const retval = ArkUIGeneratedNativeModule._Scroller_ctor()
        return retval
    }
     constructor() {
        const ctorPtr: KPointer = Scroller.ctor_scroller()
        this.peer = new Finalizable(ctorPtr, Scroller.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._Scroller_getFinalizer()
    }
    public scrollTo(options: ScrollOptions): undefined {
        const options_casted = options as (ScrollOptions)
        return this.scrollTo_serialize(options_casted)
    }
    public scrollEdge(value: Edge, options?: ScrollEdgeOptions): undefined {
        const value_casted = value as (Edge)
        const options_casted = options as (ScrollEdgeOptions | undefined)
        return this.scrollEdge_serialize(value_casted, options_casted)
    }
    public fling(velocity: number): void {
        const velocity_casted = velocity as (number)
        this?.fling_serialize(velocity_casted)
        return
    }
    public scrollPage(value: ScrollPageOptions | { next: boolean, direction?: Axis }): undefined {
        const value_type = runtimeType(value)
        if (((RuntimeType.OBJECT) == (value_type)) && ((value!.hasOwnProperty("animation")))) {
            const value_casted = value as (ScrollPageOptions)
            return this.scrollPage0_serialize(value_casted)
        }
        if (((RuntimeType.OBJECT) == (value_type)) && ((value!.hasOwnProperty("direction")))) {
            const value_casted = value as ({ next: boolean, direction?: Axis })
            return this.scrollPage1_serialize(value_casted)
        }
        throw new Error("Can not select appropriate overload")
    }
    public currentOffset(): OffsetResult {
        return this.currentOffset_serialize()
    }
    public scrollToIndex(value: number, smooth?: boolean, align?: ScrollAlign, options?: ScrollToIndexOptions): undefined {
        const value_casted = value as (number)
        const smooth_casted = smooth as (boolean | undefined)
        const align_casted = align as (ScrollAlign | undefined)
        const options_casted = options as (ScrollToIndexOptions | undefined)
        return this.scrollToIndex_serialize(value_casted, smooth_casted, align_casted, options_casted)
    }
    public scrollBy(dx: Length, dy: Length): undefined {
        const dx_casted = dx as (Length)
        const dy_casted = dy as (Length)
        return this.scrollBy_serialize(dx_casted, dy_casted)
    }
    public isAtEnd(): boolean {
        return this.isAtEnd_serialize()
    }
    public getItemRect(index: number): RectResult {
        const index_casted = index as (number)
        return this.getItemRect_serialize(index_casted)
    }
    public getItemIndex(x: number, y: number): number {
        const x_casted = x as (number)
        const y_casted = y as (number)
        return this.getItemIndex_serialize(x_casted, y_casted)
    }
    private scrollTo_serialize(options: ScrollOptions): undefined {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeScrollOptions(options)
        const retval = ArkUIGeneratedNativeModule._Scroller_scrollTo(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private scrollEdge_serialize(value: Edge, options?: ScrollEdgeOptions): undefined {
        const thisSerializer: Serializer = Serializer.hold()
        let options_type: int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value = options!
            thisSerializer.writeScrollEdgeOptions(options_value)
        }
        const retval = ArkUIGeneratedNativeModule._Scroller_scrollEdge(this.peer!.ptr, value, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private fling_serialize(velocity: number): void {
        ArkUIGeneratedNativeModule._Scroller_fling(this.peer!.ptr, velocity)
    }
    private scrollPage0_serialize(value: ScrollPageOptions): undefined {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeScrollPageOptions(value)
        const retval = ArkUIGeneratedNativeModule._Scroller_scrollPage0(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private scrollPage1_serialize(value: { next: boolean, direction?: Axis }): undefined {
        const thisSerializer: Serializer = Serializer.hold()
        const value_next = value.next
        thisSerializer.writeBoolean(value_next)
        const value_direction = value.direction
        let value_direction_type: int32 = RuntimeType.UNDEFINED
        value_direction_type = runtimeType(value_direction)
        thisSerializer.writeInt8(value_direction_type)
        if ((RuntimeType.UNDEFINED) != (value_direction_type)) {
            const value_direction_value = value_direction!
            thisSerializer.writeInt32(value_direction_value)
        }
        const retval = ArkUIGeneratedNativeModule._Scroller_scrollPage1(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private currentOffset_serialize(): OffsetResult {
        const retval = ArkUIGeneratedNativeModule._Scroller_currentOffset(this.peer!.ptr)
        let retvalDeserializer: Deserializer = new Deserializer(retval.buffer, retval.byteLength)
        const returnResult: OffsetResult = retvalDeserializer.readOffsetResult()
        return returnResult
    }
    private scrollToIndex_serialize(value: number, smooth?: boolean, align?: ScrollAlign, options?: ScrollToIndexOptions): undefined {
        const thisSerializer: Serializer = Serializer.hold()
        let smooth_type: int32 = RuntimeType.UNDEFINED
        smooth_type = runtimeType(smooth)
        thisSerializer.writeInt8(smooth_type)
        if ((RuntimeType.UNDEFINED) != (smooth_type)) {
            const smooth_value = smooth!
            thisSerializer.writeBoolean(smooth_value)
        }
        let align_type: int32 = RuntimeType.UNDEFINED
        align_type = runtimeType(align)
        thisSerializer.writeInt8(align_type)
        if ((RuntimeType.UNDEFINED) != (align_type)) {
            const align_value = align!
            thisSerializer.writeInt32(align_value)
        }
        let options_type: int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value = options!
            thisSerializer.writeScrollToIndexOptions(options_value)
        }
        const retval = ArkUIGeneratedNativeModule._Scroller_scrollToIndex(this.peer!.ptr, value, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private scrollBy_serialize(dx: Length, dy: Length): undefined {
        const retval = ArkUIGeneratedNativeModule._Scroller_scrollBy(this.peer!.ptr, dx, dy)
        return retval
    }
    private isAtEnd_serialize(): boolean {
        const retval = ArkUIGeneratedNativeModule._Scroller_isAtEnd(this.peer!.ptr)
        return retval
    }
    private getItemRect_serialize(index: number): RectResult {
        const retval = ArkUIGeneratedNativeModule._Scroller_getItemRect(this.peer!.ptr, index)
        let retvalDeserializer: Deserializer = new Deserializer(retval.buffer, retval.byteLength)
        const returnResult: RectResult = retvalDeserializer.readRectResult()
        return returnResult
    }
    private getItemIndex_serialize(x: number, y: number): number {
        const retval = ArkUIGeneratedNativeModule._Scroller_getItemIndex(this.peer!.ptr, x, y)
        return retval
    }
}
