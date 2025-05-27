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
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, UICommonMethod } from "./common"
import { ResourceColor, Length } from "./units"
import { LineCapStyle, LineJoinStyle, Color } from "./enums"
import { Resource } from "./resource"
import { PixelMap } from "./arkui-pixelmap"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { BuilderLambda } from "@koalaui/builderLambda"
import { UICommonBase, AttributeModifier } from "./../handwritten"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkShapePeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkShapePeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Shape_construct(peerId, flags)
        const _peer  = new ArkShapePeer(_peerPtr, peerId, "Shape", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setShapeOptions0Attribute(value: PixelMap): void {
        ArkUIGeneratedNativeModule._ShapeInterface_setShapeOptions0(this.peer.ptr, toPeerPtr(value))
    }
    setShapeOptions1Attribute(): void {
        ArkUIGeneratedNativeModule._ShapeInterface_setShapeOptions1(this.peer.ptr)
    }
    viewPortAttribute(value: ViewportRect): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeViewportRect(value)
        ArkUIGeneratedNativeModule._ShapeAttribute_viewPort(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    strokeAttribute(value: ResourceColor): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isColor(value)) {
            thisSerializer.writeInt8(0)
            const value_0  = value as Color
            thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_0))
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2)
            const value_2  = value as string
            thisSerializer.writeString(value_2)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(3)
            const value_3  = value as Resource
            thisSerializer.writeResource(value_3)
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_stroke(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fillAttribute(value: ResourceColor): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isColor(value)) {
            thisSerializer.writeInt8(0)
            const value_0  = value as Color
            thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_0))
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2)
            const value_2  = value as string
            thisSerializer.writeString(value_2)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(3)
            const value_3  = value as Resource
            thisSerializer.writeResource(value_3)
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_fill(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    strokeDashOffsetAttribute(value: number | string): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0)
            const value_0  = value as number
            thisSerializer.writeNumber(value_0)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(1)
            const value_1  = value as string
            thisSerializer.writeString(value_1)
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_strokeDashOffset(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    strokeDashArrayAttribute(value: Array<Length>): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeInt32(value.length as int32)
        for (let i = 0; i < value.length; i++) {
            const value_element : Length = value[i]
            let value_element_type : int32 = RuntimeType.UNDEFINED
            value_element_type = runtimeType(value_element)
            if (RuntimeType.STRING == value_element_type) {
                thisSerializer.writeInt8(0)
                const value_element_0  = value_element as string
                thisSerializer.writeString(value_element_0)
            }
            else if (RuntimeType.NUMBER == value_element_type) {
                thisSerializer.writeInt8(1)
                const value_element_1  = value_element as number
                thisSerializer.writeNumber(value_element_1)
            }
            else if (RuntimeType.OBJECT == value_element_type) {
                thisSerializer.writeInt8(2)
                const value_element_2  = value_element as Resource
                thisSerializer.writeResource(value_element_2)
            }
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_strokeDashArray(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    strokeLineCapAttribute(value: LineCapStyle): void {
        ArkUIGeneratedNativeModule._ShapeAttribute_strokeLineCap(this.peer.ptr, TypeChecker.LineCapStyle_ToNumeric(value))
    }
    strokeLineJoinAttribute(value: LineJoinStyle): void {
        ArkUIGeneratedNativeModule._ShapeAttribute_strokeLineJoin(this.peer.ptr, TypeChecker.LineJoinStyle_ToNumeric(value))
    }
    strokeMiterLimitAttribute(value: number | string): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0)
            const value_0  = value as number
            thisSerializer.writeNumber(value_0)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(1)
            const value_1  = value as string
            thisSerializer.writeString(value_1)
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_strokeMiterLimit(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    strokeOpacityAttribute(value: number | string | Resource): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0)
            const value_0  = value as number
            thisSerializer.writeNumber(value_0)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(1)
            const value_1  = value as string
            thisSerializer.writeString(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2)
            const value_2  = value as Resource
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_strokeOpacity(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fillOpacityAttribute(value: number | string | Resource): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0)
            const value_0  = value as number
            thisSerializer.writeNumber(value_0)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(1)
            const value_1  = value as string
            thisSerializer.writeString(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2)
            const value_2  = value as Resource
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_fillOpacity(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    strokeWidthAttribute(value: number | string): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0)
            const value_0  = value as number
            thisSerializer.writeNumber(value_0)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(1)
            const value_1  = value as string
            thisSerializer.writeString(value_1)
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_strokeWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    antiAliasAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._ShapeAttribute_antiAlias(this.peer.ptr, value ? 1 : 0)
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
    viewPort(value: ViewportRect): this
    stroke(value: ResourceColor): this
    fill(value: ResourceColor): this
    strokeDashOffset(value: number | string): this
    strokeDashArray(value: Array<Length>): this
    strokeLineCap(value: LineCapStyle): this
    strokeLineJoin(value: LineJoinStyle): this
    strokeMiterLimit(value: number | string): this
    strokeOpacity(value: number | string | Resource): this
    fillOpacity(value: number | string | Resource): this
    strokeWidth(value: number | string): this
    antiAlias(value: boolean): this
    mesh(value: Array<number>, column: number, row: number): this
    attributeModifier(value: AttributeModifier<ShapeAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export interface UIShapeAttribute extends UICommonMethod {
    @memo
    viewPort(value: ViewportRect): this
    @memo
    stroke(value: ResourceColor): this
    @memo
    fill(value: ResourceColor): this
    @memo
    strokeDashOffset(value: number | string): this
    @memo
    strokeDashArray(value: Array<Length>): this
    @memo
    strokeLineCap(value: LineCapStyle): this
    @memo
    strokeLineJoin(value: LineJoinStyle): this
    @memo
    strokeMiterLimit(value: number | string): this
    @memo
    strokeOpacity(value: number | string | Resource): this
    @memo
    fillOpacity(value: number | string | Resource): this
    @memo
    strokeWidth(value: number | string): this
    @memo
    antiAlias(value: boolean): this
    @memo
    mesh(value: Array<number>, column: number, row: number): this
    @memo
    attributeModifier(value: AttributeModifier<ShapeAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkShapeStyle extends ArkCommonMethodStyle implements ShapeAttribute {
    viewPort_value?: ViewportRect
    stroke_value?: ResourceColor
    fill_value?: ResourceColor
    strokeDashOffset_value?: number | string
    strokeDashArray_value?: Array<Length>
    strokeLineCap_value?: LineCapStyle
    strokeLineJoin_value?: LineJoinStyle
    strokeMiterLimit_value?: number | string
    strokeOpacity_value?: number | string | Resource
    fillOpacity_value?: number | string | Resource
    strokeWidth_value?: number | string
    antiAlias_value?: boolean
    public viewPort(value: ViewportRect): this {
        return this
    }
    public stroke(value: ResourceColor): this {
        return this
    }
    public fill(value: ResourceColor): this {
        return this
    }
    public strokeDashOffset(value: number | string): this {
        return this
    }
    public strokeDashArray(value: Array<Length>): this {
        return this
    }
    public strokeLineCap(value: LineCapStyle): this {
        return this
    }
    public strokeLineJoin(value: LineJoinStyle): this {
        return this
    }
    public strokeMiterLimit(value: number | string): this {
        return this
    }
    public strokeOpacity(value: number | string | Resource): this {
        return this
    }
    public fillOpacity(value: number | string | Resource): this {
        return this
    }
    public strokeWidth(value: number | string): this {
        return this
    }
    public antiAlias(value: boolean): this {
        return this
    }
    public mesh(value: Array<number>, column: number, row: number): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<ShapeAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
@memo_stable
export class ArkShapeComponent extends ArkCommonMethodComponent implements UIShapeAttribute {
    getPeer(): ArkShapePeer {
        return (this.peer as ArkShapePeer)
    }
    @memo
    public setShapeOptions(value?: PixelMap): this {
        if (this.checkPriority("setShapeOptions")) {
            const value_type = runtimeType(value)
            this.getPeer()?.setShapeOptions1Attribute()
            return this
        }
        return this
    }
    @memo
    public viewPort(value: ViewportRect): this {
        if (this.checkPriority("viewPort")) {
            const value_casted = value as (ViewportRect)
            this.getPeer()?.viewPortAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public stroke(value: ResourceColor): this {
        if (this.checkPriority("stroke")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.strokeAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public fill(value: ResourceColor): this {
        if (this.checkPriority("fill")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.fillAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public strokeDashOffset(value: number | string): this {
        if (this.checkPriority("strokeDashOffset")) {
            const value_casted = value as (number | string)
            this.getPeer()?.strokeDashOffsetAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public strokeDashArray(value: Array<Length>): this {
        if (this.checkPriority("strokeDashArray")) {
            const value_casted = value as (Array<Length>)
            this.getPeer()?.strokeDashArrayAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public strokeLineCap(value: LineCapStyle): this {
        if (this.checkPriority("strokeLineCap")) {
            const value_casted = value as (LineCapStyle)
            this.getPeer()?.strokeLineCapAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public strokeLineJoin(value: LineJoinStyle): this {
        if (this.checkPriority("strokeLineJoin")) {
            const value_casted = value as (LineJoinStyle)
            this.getPeer()?.strokeLineJoinAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public strokeMiterLimit(value: number | string): this {
        if (this.checkPriority("strokeMiterLimit")) {
            const value_casted = value as (number | string)
            this.getPeer()?.strokeMiterLimitAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public strokeOpacity(value: number | string | Resource): this {
        if (this.checkPriority("strokeOpacity")) {
            const value_casted = value as (number | string | Resource)
            this.getPeer()?.strokeOpacityAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public fillOpacity(value: number | string | Resource): this {
        if (this.checkPriority("fillOpacity")) {
            const value_casted = value as (number | string | Resource)
            this.getPeer()?.fillOpacityAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public strokeWidth(value: number | string): this {
        if (this.checkPriority("strokeWidth")) {
            const value_casted = value as (number | string)
            this.getPeer()?.strokeWidthAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public antiAlias(value: boolean): this {
        if (this.checkPriority("antiAlias")) {
            const value_casted = value as (boolean)
            this.getPeer()?.antiAliasAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public mesh(value: Array<number>, column: number, row: number): this {
        if (this.checkPriority("mesh")) {
            const value_casted = value as (Array<number>)
            const column_casted = column as (number)
            const row_casted = row as (number)
            this.getPeer()?.meshAttribute(value_casted, column_casted, row_casted)
            return this
        }
        return this
    }
    @memo
    public attributeModifier(value: AttributeModifier<ShapeAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
@memo
@BuilderLambda("Shape")
export function Shape(
    value?: PixelMap,
    @memo
    content_?: () => void,
): ShapeAttribute {
    throw new Error("Not implemented")
}

@memo
export function Shape(
    @memo
    style: ((attributes: UIShapeAttribute) => void) | undefined,
    value?: PixelMap,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkShapeComponent>((): ArkShapeComponent => {
        return new ArkShapeComponent()
    })
    NodeAttach<ArkShapePeer>((): ArkShapePeer => ArkShapePeer.create(receiver), (_: ArkShapePeer): void => {
        receiver.setShapeOptions(value)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
