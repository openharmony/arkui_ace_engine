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

import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, wrapCallback, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { image_PixelMap_serializer, image } from "./../generated/ohos.multimedia.image"
import { Resource_serializer, Resource } from "./../generated/resource"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonMethodSet } from "./common"
import { ResourceColor, Length } from "./units"
import { Color, LineCapStyle, LineJoinStyle } from "./enums"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
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
    setShapeOptionsAttribute(value?: image.PixelMap): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            image_PixelMap_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._ShapeInterface_setShapeOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setViewPortAttribute(value: ViewportRect | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            ViewportRect_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_setViewPort(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setStrokeAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((3).toChar())
                const value_value_3  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_setStroke(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFillAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((3).toChar())
                const value_value_3  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_setFill(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setStrokeDashOffsetAttribute(value: Length | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_setStrokeDashOffset(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setStrokeDashArrayAttribute(value: Array<Length> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeInt32((value_value.length).toInt())
            for (let value_value_counter_i = 0; value_value_counter_i < value_value.length; value_value_counter_i++) {
                const value_value_element : Length = value_value[value_value_counter_i]
                let value_value_element_type : int32 = RuntimeType.UNDEFINED
                value_value_element_type = runtimeType(value_value_element)
                if (RuntimeType.STRING == value_value_element_type) {
                    thisSerializer.writeInt8((0).toChar())
                    const value_value_element_0  = value_value_element as string
                    thisSerializer.writeString(value_value_element_0)
                }
                else if (RuntimeType.NUMBER == value_value_element_type) {
                    thisSerializer.writeInt8((1).toChar())
                    const value_value_element_1  = value_value_element as number
                    thisSerializer.writeNumber(value_value_element_1)
                }
                else if (RuntimeType.OBJECT == value_value_element_type) {
                    thisSerializer.writeInt8((2).toChar())
                    const value_value_element_2  = value_value_element as Resource
                    Resource_serializer.write(thisSerializer, value_value_element_2)
                }
            }
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_setStrokeDashArray(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setStrokeLineCapAttribute(value: LineCapStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as LineCapStyle)
            thisSerializer.writeInt32(TypeChecker.LineCapStyle_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_setStrokeLineCap(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setStrokeLineJoinAttribute(value: LineJoinStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as LineJoinStyle)
            thisSerializer.writeInt32(TypeChecker.LineJoinStyle_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_setStrokeLineJoin(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setStrokeMiterLimitAttribute(value: Length | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_setStrokeMiterLimit(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setStrokeOpacityAttribute(value: number | string | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_setStrokeOpacity(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFillOpacityAttribute(value: number | string | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_setFillOpacity(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setStrokeWidthAttribute(value: Length | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_setStrokeWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAntiAliasAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_setAntiAlias(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMeshAttribute(value: Array<number> | undefined, column: number | undefined, row: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeInt32((value_value.length).toInt())
            for (let value_value_counter_i = 0; value_value_counter_i < value_value.length; value_value_counter_i++) {
                const value_value_element : number = value_value[value_value_counter_i]
                thisSerializer.writeNumber(value_value_element)
            }
        }
        let column_type : int32 = RuntimeType.UNDEFINED
        column_type = runtimeType(column)
        thisSerializer.writeInt8((column_type).toChar())
        if ((column_type) != (RuntimeType.UNDEFINED)) {
            const column_value  = column!
            thisSerializer.writeNumber(column_value)
        }
        let row_type : int32 = RuntimeType.UNDEFINED
        row_type = runtimeType(row)
        thisSerializer.writeInt8((row_type).toChar())
        if ((row_type) != (RuntimeType.UNDEFINED)) {
            const row_value  = row!
            thisSerializer.writeNumber(row_value)
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_setMesh(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface ViewportRect {
    x?: Length;
    y?: Length;
    width?: Length;
    height?: Length;
}
export interface ShapeAttribute extends CommonMethod {
    viewPort(value: ViewportRect | undefined): this {
        throw new Error("Unimplemented method viewPort")
    }
    stroke(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method stroke")
    }
    fill(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method fill")
    }
    strokeDashOffset(value: Length | undefined): this {
        throw new Error("Unimplemented method strokeDashOffset")
    }
    strokeDashArray(value: Array<Length> | undefined): this {
        throw new Error("Unimplemented method strokeDashArray")
    }
    strokeLineCap(value: LineCapStyle | undefined): this {
        throw new Error("Unimplemented method strokeLineCap")
    }
    strokeLineJoin(value: LineJoinStyle | undefined): this {
        throw new Error("Unimplemented method strokeLineJoin")
    }
    strokeMiterLimit(value: Length | undefined): this {
        throw new Error("Unimplemented method strokeMiterLimit")
    }
    strokeOpacity(value: number | string | Resource | undefined): this {
        throw new Error("Unimplemented method strokeOpacity")
    }
    fillOpacity(value: number | string | Resource | undefined): this {
        throw new Error("Unimplemented method fillOpacity")
    }
    strokeWidth(value: Length | undefined): this {
        throw new Error("Unimplemented method strokeWidth")
    }
    antiAlias(value: boolean | undefined): this {
        throw new Error("Unimplemented method antiAlias")
    }
    mesh(value: Array<number> | undefined, column: number | undefined, row: number | undefined): this {
        throw new Error("Unimplemented method mesh")
    }
    attributeModifier(value: AttributeModifier<ShapeAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkShapeStyle extends ArkCommonMethodStyle implements ShapeAttribute {
    viewPort_value?: ViewportRect | undefined
    stroke_value?: ResourceColor | undefined
    fill_value?: ResourceColor | undefined
    strokeDashOffset_value?: Length | undefined
    strokeDashArray_value?: Array<Length> | undefined
    strokeLineCap_value?: LineCapStyle | undefined
    strokeLineJoin_value?: LineJoinStyle | undefined
    strokeMiterLimit_value?: Length | undefined
    strokeOpacity_value?: number | string | Resource | undefined
    fillOpacity_value?: number | string | Resource | undefined
    strokeWidth_value?: Length | undefined
    antiAlias_value?: boolean | undefined
    attributeModifier_value?: AttributeModifier<ShapeAttribute> | AttributeModifier<CommonMethod> | undefined
    public viewPort(value: ViewportRect | undefined): this {
        return this
    }
    public stroke(value: ResourceColor | undefined): this {
        return this
    }
    public fill(value: ResourceColor | undefined): this {
        return this
    }
    public strokeDashOffset(value: Length | undefined): this {
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
    public strokeMiterLimit(value: Length | undefined): this {
        return this
    }
    public strokeOpacity(value: number | string | Resource | undefined): this {
        return this
    }
    public fillOpacity(value: number | string | Resource | undefined): this {
        return this
    }
    public strokeWidth(value: Length | undefined): this {
        return this
    }
    public antiAlias(value: boolean | undefined): this {
        return this
    }
    public mesh(value: Array<number> | undefined, column: number | undefined, row: number | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<ShapeAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: ShapeAttribute): void {
        super.apply(target)
        if (this.viewPort_value !== undefined)
            target.viewPort(this.viewPort_value!)
        if (this.stroke_value !== undefined)
            target.stroke(this.stroke_value!)
        if (this.fill_value !== undefined)
            target.fill(this.fill_value!)
        if (this.strokeDashOffset_value !== undefined)
            target.strokeDashOffset(this.strokeDashOffset_value!)
        if (this.strokeDashArray_value !== undefined)
            target.strokeDashArray(this.strokeDashArray_value!)
        if (this.strokeLineCap_value !== undefined)
            target.strokeLineCap(this.strokeLineCap_value!)
        if (this.strokeLineJoin_value !== undefined)
            target.strokeLineJoin(this.strokeLineJoin_value!)
        if (this.strokeMiterLimit_value !== undefined)
            target.strokeMiterLimit(this.strokeMiterLimit_value!)
        if (this.strokeOpacity_value !== undefined)
            target.strokeOpacity(this.strokeOpacity_value!)
        if (this.fillOpacity_value !== undefined)
            target.fillOpacity(this.fillOpacity_value!)
        if (this.strokeWidth_value !== undefined)
            target.strokeWidth(this.strokeWidth_value!)
        if (this.antiAlias_value !== undefined)
            target.antiAlias(this.antiAlias_value!)
    }
}

export class ArkShapeComponent extends ArkCommonMethodComponent implements ShapeAttribute {
    getPeer(): ArkShapePeer {
        return (this.peer as ArkShapePeer)
    }
    public setShapeOptions(value?: image.PixelMap): this {
        if (this.checkPriority("setShapeOptions")) {
            const value_casted = value as (image.PixelMap | undefined)
            this.getPeer()?.setShapeOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    public viewPort(value: ViewportRect | undefined): this {
        if (this.checkPriority("viewPort")) {
            const value_casted = value as (ViewportRect | undefined)
            this.getPeer()?.setViewPortAttribute(value_casted)
            return this
        }
        return this
    }
    public stroke(value: ResourceColor | undefined): this {
        if (this.checkPriority("stroke")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setStrokeAttribute(value_casted)
            return this
        }
        return this
    }
    public fill(value: ResourceColor | undefined): this {
        if (this.checkPriority("fill")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setFillAttribute(value_casted)
            return this
        }
        return this
    }
    public strokeDashOffset(value: Length | undefined): this {
        if (this.checkPriority("strokeDashOffset")) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.setStrokeDashOffsetAttribute(value_casted)
            return this
        }
        return this
    }
    public strokeDashArray(value: Array<Length> | undefined): this {
        if (this.checkPriority("strokeDashArray")) {
            const value_casted = value as (Array<Length> | undefined)
            this.getPeer()?.setStrokeDashArrayAttribute(value_casted)
            return this
        }
        return this
    }
    public strokeLineCap(value: LineCapStyle | undefined): this {
        if (this.checkPriority("strokeLineCap")) {
            const value_casted = value as (LineCapStyle | undefined)
            this.getPeer()?.setStrokeLineCapAttribute(value_casted)
            return this
        }
        return this
    }
    public strokeLineJoin(value: LineJoinStyle | undefined): this {
        if (this.checkPriority("strokeLineJoin")) {
            const value_casted = value as (LineJoinStyle | undefined)
            this.getPeer()?.setStrokeLineJoinAttribute(value_casted)
            return this
        }
        return this
    }
    public strokeMiterLimit(value: Length | undefined): this {
        if (this.checkPriority("strokeMiterLimit")) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.setStrokeMiterLimitAttribute(value_casted)
            return this
        }
        return this
    }
    public strokeOpacity(value: number | string | Resource | undefined): this {
        if (this.checkPriority("strokeOpacity")) {
            const value_casted = value as (number | string | Resource | undefined)
            this.getPeer()?.setStrokeOpacityAttribute(value_casted)
            return this
        }
        return this
    }
    public fillOpacity(value: number | string | Resource | undefined): this {
        if (this.checkPriority("fillOpacity")) {
            const value_casted = value as (number | string | Resource | undefined)
            this.getPeer()?.setFillOpacityAttribute(value_casted)
            return this
        }
        return this
    }
    public strokeWidth(value: Length | undefined): this {
        if (this.checkPriority("strokeWidth")) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.setStrokeWidthAttribute(value_casted)
            return this
        }
        return this
    }
    public antiAlias(value: boolean | undefined): this {
        if (this.checkPriority("antiAlias")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setAntiAliasAttribute(value_casted)
            return this
        }
        return this
    }
    public mesh(value: Array<number> | undefined, column: number | undefined, row: number | undefined): this {
        if (this.checkPriority("mesh")) {
            const value_casted = value as (Array<number> | undefined)
            const column_casted = column as (number | undefined)
            const row_casted = row as (number | undefined)
            this.getPeer()?.setMeshAttribute(value_casted, column_casted, row_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<ShapeAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withShapeStyle(receiver: ShapeAttribute, modifier: AttributeModifier<ShapeAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkShapeStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("Shape")
// export function Shape(
//     value?: image.PixelMap,
//     @memo
//     content_?: () => void,
// ): ShapeAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function Shape(
    @memo
    style: ((attributes: ShapeAttribute) => void) | undefined,
    value?: image.PixelMap,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkShapeComponent>((): ArkShapeComponent => {
        return new ArkShapeComponent()
    })
    NodeAttach<ArkShapePeer>((): ArkShapePeer => ArkShapePeer.create(receiver), (_: ArkShapePeer): void => {
        receiver.setShapeOptions(value)
        style?.(receiver)
        withShapeStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkShapeSet extends ArkCommonMethodSet implements ShapeAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _viewPort_flag?: boolean
    _viewPort0_value?: ViewportRect | undefined
    _stroke_flag?: boolean
    _stroke0_value?: ResourceColor | undefined
    _fill_flag?: boolean
    _fill0_value?: ResourceColor | undefined
    _strokeDashOffset_flag?: boolean
    _strokeDashOffset0_value?: Length | undefined
    _strokeDashArray_flag?: boolean
    _strokeDashArray0_value?: Array<Length> | undefined
    _strokeLineCap_flag?: boolean
    _strokeLineCap0_value?: LineCapStyle | undefined
    _strokeLineJoin_flag?: boolean
    _strokeLineJoin0_value?: LineJoinStyle | undefined
    _strokeMiterLimit_flag?: boolean
    _strokeMiterLimit0_value?: Length | undefined
    _strokeOpacity_flag?: boolean
    _strokeOpacity0_value?: number | string | Resource | undefined
    _fillOpacity_flag?: boolean
    _fillOpacity0_value?: number | string | Resource | undefined
    _strokeWidth_flag?: boolean
    _strokeWidth0_value?: Length | undefined
    _antiAlias_flag?: boolean
    _antiAlias0_value?: boolean | undefined
    _mesh_flag?: boolean
    _mesh0_value?: Array<number> | undefined
    _mesh1_value?: number | undefined
    _mesh2_value?: number | undefined
    applyModifierPatch(component: ShapeAttribute): void {
        if (this._viewPort_flag)
            component.viewPort((this._viewPort0_value as ViewportRect | undefined))
        if (this._stroke_flag)
            component.stroke((this._stroke0_value as ResourceColor | undefined))
        if (this._fill_flag)
            component.fill((this._fill0_value as ResourceColor | undefined))
        if (this._strokeDashOffset_flag)
            component.strokeDashOffset((this._strokeDashOffset0_value as Length | undefined))
        if (this._strokeDashArray_flag)
            component.strokeDashArray((this._strokeDashArray0_value as Array<Length> | undefined))
        if (this._strokeLineCap_flag)
            component.strokeLineCap((this._strokeLineCap0_value as LineCapStyle | undefined))
        if (this._strokeLineJoin_flag)
            component.strokeLineJoin((this._strokeLineJoin0_value as LineJoinStyle | undefined))
        if (this._strokeMiterLimit_flag)
            component.strokeMiterLimit((this._strokeMiterLimit0_value as Length | undefined))
        if (this._strokeOpacity_flag)
            component.strokeOpacity((this._strokeOpacity0_value as number | string | Resource | undefined))
        if (this._fillOpacity_flag)
            component.fillOpacity((this._fillOpacity0_value as number | string | Resource | undefined))
        if (this._strokeWidth_flag)
            component.strokeWidth((this._strokeWidth0_value as Length | undefined))
        if (this._antiAlias_flag)
            component.antiAlias((this._antiAlias0_value as boolean | undefined))
        if (this._mesh_flag)
            component.mesh((this._mesh0_value as Array<number> | undefined), (this._mesh1_value as number | undefined), (this._mesh2_value as number | undefined))
    }
    public viewPort(value: ViewportRect | undefined): this {
        this._viewPort_flag = true
        this._viewPort0_value = value
        return this
    }
    public stroke(value: ResourceColor | undefined): this {
        this._stroke_flag = true
        this._stroke0_value = value
        return this
    }
    public fill(value: ResourceColor | undefined): this {
        this._fill_flag = true
        this._fill0_value = value
        return this
    }
    public strokeDashOffset(value: Length | undefined): this {
        this._strokeDashOffset_flag = true
        this._strokeDashOffset0_value = value
        return this
    }
    public strokeDashArray(value: Array<Length> | undefined): this {
        this._strokeDashArray_flag = true
        this._strokeDashArray0_value = value
        return this
    }
    public strokeLineCap(value: LineCapStyle | undefined): this {
        this._strokeLineCap_flag = true
        this._strokeLineCap0_value = value
        return this
    }
    public strokeLineJoin(value: LineJoinStyle | undefined): this {
        this._strokeLineJoin_flag = true
        this._strokeLineJoin0_value = value
        return this
    }
    public strokeMiterLimit(value: Length | undefined): this {
        this._strokeMiterLimit_flag = true
        this._strokeMiterLimit0_value = value
        return this
    }
    public strokeOpacity(value: number | string | Resource | undefined): this {
        this._strokeOpacity_flag = true
        this._strokeOpacity0_value = value
        return this
    }
    public fillOpacity(value: number | string | Resource | undefined): this {
        this._fillOpacity_flag = true
        this._fillOpacity0_value = value
        return this
    }
    public strokeWidth(value: Length | undefined): this {
        this._strokeWidth_flag = true
        this._strokeWidth0_value = value
        return this
    }
    public antiAlias(value: boolean | undefined): this {
        this._antiAlias_flag = true
        this._antiAlias0_value = value
        return this
    }
    public mesh(value: Array<number> | undefined, column: number | undefined, row: number | undefined): this {
        this._mesh_flag = true
        this._mesh0_value = value
        this._mesh1_value = column
        this._mesh2_value = row
        return this
    }
    public attributeModifier(value: AttributeModifier<ShapeAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class ViewportRect_serializer {
    public static write(buffer: SerializerBase, value: ViewportRect): void {
        let valueSerializer : SerializerBase = buffer
        const value_x  = value.x
        let value_x_type : int32 = RuntimeType.UNDEFINED
        value_x_type = runtimeType(value_x)
        valueSerializer.writeInt8((value_x_type).toChar())
        if ((value_x_type) != (RuntimeType.UNDEFINED)) {
            const value_x_value  = value_x!
            let value_x_value_type : int32 = RuntimeType.UNDEFINED
            value_x_value_type = runtimeType(value_x_value)
            if (RuntimeType.STRING == value_x_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_x_value_0  = value_x_value as string
                valueSerializer.writeString(value_x_value_0)
            }
            else if (RuntimeType.NUMBER == value_x_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_x_value_1  = value_x_value as number
                valueSerializer.writeNumber(value_x_value_1)
            }
            else if (RuntimeType.OBJECT == value_x_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_x_value_2  = value_x_value as Resource
                Resource_serializer.write(valueSerializer, value_x_value_2)
            }
        }
        const value_y  = value.y
        let value_y_type : int32 = RuntimeType.UNDEFINED
        value_y_type = runtimeType(value_y)
        valueSerializer.writeInt8((value_y_type).toChar())
        if ((value_y_type) != (RuntimeType.UNDEFINED)) {
            const value_y_value  = value_y!
            let value_y_value_type : int32 = RuntimeType.UNDEFINED
            value_y_value_type = runtimeType(value_y_value)
            if (RuntimeType.STRING == value_y_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_y_value_0  = value_y_value as string
                valueSerializer.writeString(value_y_value_0)
            }
            else if (RuntimeType.NUMBER == value_y_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_y_value_1  = value_y_value as number
                valueSerializer.writeNumber(value_y_value_1)
            }
            else if (RuntimeType.OBJECT == value_y_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_y_value_2  = value_y_value as Resource
                Resource_serializer.write(valueSerializer, value_y_value_2)
            }
        }
        const value_width  = value.width
        let value_width_type : int32 = RuntimeType.UNDEFINED
        value_width_type = runtimeType(value_width)
        valueSerializer.writeInt8((value_width_type).toChar())
        if ((value_width_type) != (RuntimeType.UNDEFINED)) {
            const value_width_value  = value_width!
            let value_width_value_type : int32 = RuntimeType.UNDEFINED
            value_width_value_type = runtimeType(value_width_value)
            if (RuntimeType.STRING == value_width_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_width_value_0  = value_width_value as string
                valueSerializer.writeString(value_width_value_0)
            }
            else if (RuntimeType.NUMBER == value_width_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_width_value_1  = value_width_value as number
                valueSerializer.writeNumber(value_width_value_1)
            }
            else if (RuntimeType.OBJECT == value_width_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_width_value_2  = value_width_value as Resource
                Resource_serializer.write(valueSerializer, value_width_value_2)
            }
        }
        const value_height  = value.height
        let value_height_type : int32 = RuntimeType.UNDEFINED
        value_height_type = runtimeType(value_height)
        valueSerializer.writeInt8((value_height_type).toChar())
        if ((value_height_type) != (RuntimeType.UNDEFINED)) {
            const value_height_value  = value_height!
            let value_height_value_type : int32 = RuntimeType.UNDEFINED
            value_height_value_type = runtimeType(value_height_value)
            if (RuntimeType.STRING == value_height_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_height_value_0  = value_height_value as string
                valueSerializer.writeString(value_height_value_0)
            }
            else if (RuntimeType.NUMBER == value_height_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_height_value_1  = value_height_value as number
                valueSerializer.writeNumber(value_height_value_1)
            }
            else if (RuntimeType.OBJECT == value_height_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_height_value_2  = value_height_value as Resource
                Resource_serializer.write(valueSerializer, value_height_value_2)
            }
        }
    }
    public static read(buffer: DeserializerBase): ViewportRect {
        let valueDeserializer : DeserializerBase = buffer
        const x_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let x_buf : Length | undefined
        if ((x_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const x_buf__selector : int32 = valueDeserializer.readInt8()
            let x_buf_ : string | number | Resource | undefined
            if (x_buf__selector == (0).toChar()) {
                x_buf_ = (valueDeserializer.readString() as string)
            }
            else if (x_buf__selector == (1).toChar()) {
                x_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (x_buf__selector == (2).toChar()) {
                x_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for x_buf_ has to be chosen through deserialisation.")
            }
            x_buf = (x_buf_ as string | number | Resource)
        }
        const x_result : Length | undefined = x_buf
        const y_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let y_buf : Length | undefined
        if ((y_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const y_buf__selector : int32 = valueDeserializer.readInt8()
            let y_buf_ : string | number | Resource | undefined
            if (y_buf__selector == (0).toChar()) {
                y_buf_ = (valueDeserializer.readString() as string)
            }
            else if (y_buf__selector == (1).toChar()) {
                y_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (y_buf__selector == (2).toChar()) {
                y_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for y_buf_ has to be chosen through deserialisation.")
            }
            y_buf = (y_buf_ as string | number | Resource)
        }
        const y_result : Length | undefined = y_buf
        const width_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let width_buf : Length | undefined
        if ((width_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const width_buf__selector : int32 = valueDeserializer.readInt8()
            let width_buf_ : string | number | Resource | undefined
            if (width_buf__selector == (0).toChar()) {
                width_buf_ = (valueDeserializer.readString() as string)
            }
            else if (width_buf__selector == (1).toChar()) {
                width_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (width_buf__selector == (2).toChar()) {
                width_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for width_buf_ has to be chosen through deserialisation.")
            }
            width_buf = (width_buf_ as string | number | Resource)
        }
        const width_result : Length | undefined = width_buf
        const height_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let height_buf : Length | undefined
        if ((height_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const height_buf__selector : int32 = valueDeserializer.readInt8()
            let height_buf_ : string | number | Resource | undefined
            if (height_buf__selector == (0).toChar()) {
                height_buf_ = (valueDeserializer.readString() as string)
            }
            else if (height_buf__selector == (1).toChar()) {
                height_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (height_buf__selector == (2).toChar()) {
                height_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for height_buf_ has to be chosen through deserialisation.")
            }
            height_buf = (height_buf_ as string | number | Resource)
        }
        const height_result : Length | undefined = height_buf
        let value : ViewportRect = ({x: x_result, y: y_result, width: width_result, height: height_result} as ViewportRect)
        return value
    }
}
