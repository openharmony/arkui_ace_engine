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

import { int32, int64, float32 } from "@koalaui/common"
import { nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, wrapCallback, NativeBuffer } from "@koalaui/interop"
import { Serializer } from "./peers/Serializer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { ResourceColor, Length } from "./units"
import { LineCapStyle, LineJoinStyle, Color } from "./enums"
import { Resource } from "global.resource"
import { PixelMap } from "#external"
import { ArkUIAniModule } from "arkui.ani"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"

export class ArkShapePeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkShapePeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Shape_construct(peerId, flags)
        const _peer  = new ArkShapePeer(_peerPtr, peerId, "Shape", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setShapeOptions0Attribute(value: PixelMap): void {
        let ptr = ArkUIAniModule._ConvertUtils_ConvertFromPixelMapAni(value);
        const ptr_value = ptr as KPointer;
        ArkUIGeneratedNativeModule._ShapeInterface_setShapeOptions0(this.peer.ptr, ptr_value)
    }
    setShapeOptions1Attribute(): void {
        ArkUIGeneratedNativeModule._ShapeInterface_setShapeOptions1(this.peer.ptr)
    }
    viewPortAttribute(value: ViewportRect | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeViewportRect(value_value)
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_viewPort(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    strokeAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(3 as int32)
                const value_value_3  = value_value as Resource
                thisSerializer.writeResource(value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_stroke(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fillAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(3 as int32)
                const value_value_3  = value_value as Resource
                thisSerializer.writeResource(value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_fill(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    strokeDashOffsetAttribute(value: number | string | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_strokeDashOffset(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    strokeDashArrayAttribute(value: Array<Length> | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeInt32(value_value.length as int32)
            for (let i = 0; i < value_value.length; i++) {
                const value_value_element : Length = value_value[i]
                thisSerializer.writeLength(value_value_element)
            }
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_strokeDashArray(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    strokeLineCapAttribute(value: LineCapStyle | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as LineCapStyle)
            thisSerializer.writeInt32(TypeChecker.LineCapStyle_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_strokeLineCap(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    strokeLineJoinAttribute(value: LineJoinStyle | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as LineJoinStyle)
            thisSerializer.writeInt32(TypeChecker.LineJoinStyle_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_strokeLineJoin(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    strokeMiterLimitAttribute(value: number | string | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_strokeMiterLimit(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    strokeOpacityAttribute(value: number | string | Resource | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as Resource
                thisSerializer.writeResource(value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_strokeOpacity(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fillOpacityAttribute(value: number | string | Resource | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as Resource
                thisSerializer.writeResource(value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_fillOpacity(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    strokeWidthAttribute(value: number | string | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_strokeWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    antiAliasAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_antiAlias(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    meshAttribute(value: Array<number>, column: number, row: number): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeInt32(value.length as int32)
        for (let i = 0; i < value.length; i++) {
            const value_element : number = value[i]
            thisSerializer.writeNumber(value_element)
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_mesh(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length(), column, row)
        thisSerializer.release()
    }
}
export interface ViewportRect {
    x?: number | string;
    y?: number | string;
    width?: number | string;
    height?: number | string;
}
export interface ShapeAttribute extends CommonMethod {
    viewPort(value: ViewportRect | undefined): this
    stroke(value: ResourceColor | undefined): this
    fill(value: ResourceColor | undefined): this
    strokeDashOffset(value: number | string | undefined): this
    strokeDashArray(value: Array<Length> | undefined): this
    strokeLineCap(value: LineCapStyle | undefined): this
    strokeLineJoin(value: LineJoinStyle | undefined): this
    strokeMiterLimit(value: number | string | undefined): this
    strokeOpacity(value: number | string | Resource | undefined): this
    fillOpacity(value: number | string | Resource | undefined): this
    strokeWidth(value: number | string | undefined): this
    antiAlias(value: boolean | undefined): this
    mesh(value: Array<number> | undefined, column: number | undefined, row: number | undefined): this
}
export class ArkShapeStyle extends ArkCommonMethodStyle implements ShapeAttribute {
    viewPort_value?: ViewportRect | undefined
    stroke_value?: ResourceColor | undefined
    fill_value?: ResourceColor | undefined
    strokeDashOffset_value?: number | string | undefined
    strokeDashArray_value?: Array<Length> | undefined
    strokeLineCap_value?: LineCapStyle | undefined
    strokeLineJoin_value?: LineJoinStyle | undefined
    strokeMiterLimit_value?: number | string | undefined
    strokeOpacity_value?: number | string | Resource | undefined
    fillOpacity_value?: number | string | Resource | undefined
    strokeWidth_value?: number | string | undefined
    antiAlias_value?: boolean | undefined
    public viewPort(value: ViewportRect | undefined): this {
        return this
    }
    public stroke(value: ResourceColor | undefined): this {
        return this
    }
    public fill(value: ResourceColor | undefined): this {
        return this
    }
    public strokeDashOffset(value: number | string | undefined): this {
        return this
    }
    public strokeDashArray(value: Array<Length> | undefined): this {
        return this
    }
    public strokeLineCap(value: LineCapStyle | undefined): this {
        return this
    }
    public strokeLineJoin(value: LineJoinStyle | undefined): this {
        return this
    }
    public strokeMiterLimit(value: number | string | undefined): this {
        return this
    }
    public strokeOpacity(value: number | string | Resource | undefined): this {
        return this
    }
    public fillOpacity(value: number | string | Resource | undefined): this {
        return this
    }
    public strokeWidth(value: number | string | undefined): this {
        return this
    }
    public antiAlias(value: boolean | undefined): this {
        return this
    }
    public mesh(value: Array<number> | undefined, column: number | undefined, row: number | undefined): this {
        return this
        }
}
export class ArkShapeComponent extends ArkCommonMethodComponent implements ShapeAttribute {
    getPeer(): ArkShapePeer {
        return (this.peer as ArkShapePeer)
    }
    public setShapeOptions(value?: PixelMap): this {
        if (this.checkPriority("setShapeOptions")) {
            const value_casted = value as (PixelMap | undefined);
            const value_type = runtimeType(value)
            if ((RuntimeType.UNDEFINED) != (value_type)) {
                const pixelMap = value_casted as PixelMap;
                this.getPeer()?.setShapeOptions0Attribute(pixelMap)
            } else {
                this.getPeer()?.setShapeOptions1Attribute()
            }
            return this
        }
        return this
    }
    public viewPort(value: ViewportRect | undefined): this {
        if (this.checkPriority("viewPort")) {
            const value_casted = value as (ViewportRect | undefined)
            this.getPeer()?.viewPortAttribute(value_casted)
            return this
        }
        return this
    }
    public stroke(value: ResourceColor | undefined): this {
        if (this.checkPriority("stroke")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.strokeAttribute(value_casted)
            return this
        }
        return this
    }
    public fill(value: ResourceColor | undefined): this {
        if (this.checkPriority("fill")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.fillAttribute(value_casted)
            return this
        }
        return this
    }
    public strokeDashOffset(value: number | string | undefined): this {
        if (this.checkPriority("strokeDashOffset")) {
            const value_casted = value as (number | string | undefined)
            this.getPeer()?.strokeDashOffsetAttribute(value_casted)
            return this
        }
        return this
    }
    public strokeDashArray(value: Array<Length> | undefined): this {
        if (this.checkPriority("strokeDashArray")) {
            const value_casted = value as (Array<Length> | undefined)
            this.getPeer()?.strokeDashArrayAttribute(value_casted)
            return this
        }
        return this
    }
    public strokeLineCap(value: LineCapStyle | undefined): this {
        if (this.checkPriority("strokeLineCap")) {
            const value_casted = value as (LineCapStyle | undefined)
            this.getPeer()?.strokeLineCapAttribute(value_casted)
            return this
        }
        return this
    }
    public strokeLineJoin(value: LineJoinStyle | undefined): this {
        if (this.checkPriority("strokeLineJoin")) {
            const value_casted = value as (LineJoinStyle | undefined)
            this.getPeer()?.strokeLineJoinAttribute(value_casted)
            return this
        }
        return this
    }
    public strokeMiterLimit(value: number | string | undefined): this {
        if (this.checkPriority("strokeMiterLimit")) {
            const value_casted = value as (number | string | undefined)
            this.getPeer()?.strokeMiterLimitAttribute(value_casted)
            return this
        }
        return this
    }
    public strokeOpacity(value: number | string | Resource | undefined): this {
        if (this.checkPriority("strokeOpacity")) {
            const value_casted = value as (number | string | Resource | undefined)
            this.getPeer()?.strokeOpacityAttribute(value_casted)
            return this
        }
        return this
    }
    public fillOpacity(value: number | string | Resource | undefined): this {
        if (this.checkPriority("fillOpacity")) {
            const value_casted = value as (number | string | Resource | undefined)
            this.getPeer()?.fillOpacityAttribute(value_casted)
            return this
        }
        return this
    }
    public strokeWidth(value: number | string | undefined): this {
        if (this.checkPriority("strokeWidth")) {
            const value_casted = value as (number | string | undefined)
            this.getPeer()?.strokeWidthAttribute(value_casted)
            return this
        }
        return this
    }
    public antiAlias(value: boolean | undefined): this {
        if (this.checkPriority("antiAlias")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.antiAliasAttribute(value_casted)
            return this
        }
        return this
    }
    public mesh(value: Array<number> | undefined, column: number | undefined, row: number | undefined): this {
        if (value == undefined || column == undefined || row == undefined) {
            return this;
        }
        if (this.checkPriority("mesh")) {
            const value_casted = value as (Array<number>)
            const column_casted = column as (number)
            const row_casted = row as (number)
            this.getPeer()?.meshAttribute(value_casted, column_casted, row_casted)
            return this
        }
        return this
    }
    
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function Shape(
    /** @memo */
    style: ((attributes: ShapeAttribute) => void) | undefined,
    value?: PixelMap,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkShapeComponent()
    })
    NodeAttach<ArkShapePeer>((): ArkShapePeer => ArkShapePeer.create(receiver), (_: ArkShapePeer) => {
        receiver.setShapeOptions(value)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
