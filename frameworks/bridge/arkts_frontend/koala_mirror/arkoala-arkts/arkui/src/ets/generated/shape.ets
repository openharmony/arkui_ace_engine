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
import { image_PixelMap_serializer, image } from "./ohos.multimedia.image"
import { Resource_serializer, Resource } from "./resource"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { ResourceColor, Length } from "./units"
import { Color, LineCapStyle, LineJoinStyle } from "./enums"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { BuilderLambda } from "@koalaui/builderLambda"
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
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            image_PixelMap_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._ShapeInterface_setShapeOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    viewPortAttribute(value: ViewportRect | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            ViewportRect_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_viewPort(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    strokeAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(2)
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(3)
                const value_value_3  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_stroke(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fillAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(2)
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(3)
                const value_value_3  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_fill(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    strokeDashOffsetAttribute(value: number | string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_strokeDashOffset(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    strokeDashArrayAttribute(value: Array<Length> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeInt32(value_value.length as int32)
            for (let i = 0; i < value_value.length; i++) {
                const value_value_element : Length = value_value[i]
                let value_value_element_type : int32 = RuntimeType.UNDEFINED
                value_value_element_type = runtimeType(value_value_element)
                if (RuntimeType.STRING == value_value_element_type) {
                    thisSerializer.writeInt8(0)
                    const value_value_element_0  = value_value_element as string
                    thisSerializer.writeString(value_value_element_0)
                }
                else if (RuntimeType.NUMBER == value_value_element_type) {
                    thisSerializer.writeInt8(1)
                    const value_value_element_1  = value_value_element as number
                    thisSerializer.writeNumber(value_value_element_1)
                }
                else if (RuntimeType.OBJECT == value_value_element_type) {
                    thisSerializer.writeInt8(2)
                    const value_value_element_2  = value_value_element as Resource
                    Resource_serializer.write(thisSerializer, value_value_element_2)
                }
            }
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_strokeDashArray(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    strokeLineCapAttribute(value: LineCapStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as LineCapStyle)
            thisSerializer.writeInt32(TypeChecker.LineCapStyle_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_strokeLineCap(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    strokeLineJoinAttribute(value: LineJoinStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as LineJoinStyle)
            thisSerializer.writeInt32(TypeChecker.LineJoinStyle_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_strokeLineJoin(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    strokeMiterLimitAttribute(value: number | string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_strokeMiterLimit(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    strokeOpacityAttribute(value: number | string | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(2)
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_strokeOpacity(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fillOpacityAttribute(value: number | string | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(2)
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_fillOpacity(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    strokeWidthAttribute(value: number | string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_strokeWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    antiAliasAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_antiAlias(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    meshAttribute(value: Array<number> | undefined, column: number | undefined, row: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeInt32(value_value.length as int32)
            for (let i = 0; i < value_value.length; i++) {
                const value_value_element : number = value_value[i]
                thisSerializer.writeNumber(value_value_element)
            }
        }
        let column_type : int32 = RuntimeType.UNDEFINED
        column_type = runtimeType(column)
        thisSerializer.writeInt8(column_type)
        if ((RuntimeType.UNDEFINED) != (column_type)) {
            const column_value  = column!
            thisSerializer.writeNumber(column_value)
        }
        let row_type : int32 = RuntimeType.UNDEFINED
        row_type = runtimeType(row)
        thisSerializer.writeInt8(row_type)
        if ((RuntimeType.UNDEFINED) != (row_type)) {
            const row_value  = row!
            thisSerializer.writeNumber(row_value)
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_mesh(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
    attributeModifier(value: AttributeModifier<ShapeAttribute> | AttributeModifier<CommonMethod> | undefined): this
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
        if (this.checkPriority("mesh")) {
            const value_casted = value as (Array<number> | undefined)
            const column_casted = column as (number | undefined)
            const row_casted = row as (number | undefined)
            this.getPeer()?.meshAttribute(value_casted, column_casted, row_casted)
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
        if (modifier!.isUpdater)
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
@memo
@BuilderLambda("ShapeImpl")
export function Shape(
    value?: image.PixelMap | undefined,
    @memo
    content_?: () => void,
): ShapeAttribute {
    throw new Error("Not implemented")
}

@memo
export function ShapeImpl(
    @memo
    style: ((attributes: ShapeAttribute) => void) | undefined,
    value?: image.PixelMap | undefined,
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

export class ViewportRect_serializer {
    public static write(buffer: SerializerBase, value: ViewportRect): void {
        let valueSerializer : SerializerBase = buffer
        const value_x  = value.x
        let value_x_type : int32 = RuntimeType.UNDEFINED
        value_x_type = runtimeType(value_x)
        valueSerializer.writeInt8(value_x_type)
        if ((RuntimeType.UNDEFINED) != (value_x_type)) {
            const value_x_value  = value_x!
            let value_x_value_type : int32 = RuntimeType.UNDEFINED
            value_x_value_type = runtimeType(value_x_value)
            if (RuntimeType.NUMBER == value_x_value_type) {
                valueSerializer.writeInt8(0)
                const value_x_value_0  = value_x_value as number
                valueSerializer.writeNumber(value_x_value_0)
            }
            else if (RuntimeType.STRING == value_x_value_type) {
                valueSerializer.writeInt8(1)
                const value_x_value_1  = value_x_value as string
                valueSerializer.writeString(value_x_value_1)
            }
        }
        const value_y  = value.y
        let value_y_type : int32 = RuntimeType.UNDEFINED
        value_y_type = runtimeType(value_y)
        valueSerializer.writeInt8(value_y_type)
        if ((RuntimeType.UNDEFINED) != (value_y_type)) {
            const value_y_value  = value_y!
            let value_y_value_type : int32 = RuntimeType.UNDEFINED
            value_y_value_type = runtimeType(value_y_value)
            if (RuntimeType.NUMBER == value_y_value_type) {
                valueSerializer.writeInt8(0)
                const value_y_value_0  = value_y_value as number
                valueSerializer.writeNumber(value_y_value_0)
            }
            else if (RuntimeType.STRING == value_y_value_type) {
                valueSerializer.writeInt8(1)
                const value_y_value_1  = value_y_value as string
                valueSerializer.writeString(value_y_value_1)
            }
        }
        const value_width  = value.width
        let value_width_type : int32 = RuntimeType.UNDEFINED
        value_width_type = runtimeType(value_width)
        valueSerializer.writeInt8(value_width_type)
        if ((RuntimeType.UNDEFINED) != (value_width_type)) {
            const value_width_value  = value_width!
            let value_width_value_type : int32 = RuntimeType.UNDEFINED
            value_width_value_type = runtimeType(value_width_value)
            if (RuntimeType.NUMBER == value_width_value_type) {
                valueSerializer.writeInt8(0)
                const value_width_value_0  = value_width_value as number
                valueSerializer.writeNumber(value_width_value_0)
            }
            else if (RuntimeType.STRING == value_width_value_type) {
                valueSerializer.writeInt8(1)
                const value_width_value_1  = value_width_value as string
                valueSerializer.writeString(value_width_value_1)
            }
        }
        const value_height  = value.height
        let value_height_type : int32 = RuntimeType.UNDEFINED
        value_height_type = runtimeType(value_height)
        valueSerializer.writeInt8(value_height_type)
        if ((RuntimeType.UNDEFINED) != (value_height_type)) {
            const value_height_value  = value_height!
            let value_height_value_type : int32 = RuntimeType.UNDEFINED
            value_height_value_type = runtimeType(value_height_value)
            if (RuntimeType.NUMBER == value_height_value_type) {
                valueSerializer.writeInt8(0)
                const value_height_value_0  = value_height_value as number
                valueSerializer.writeNumber(value_height_value_0)
            }
            else if (RuntimeType.STRING == value_height_value_type) {
                valueSerializer.writeInt8(1)
                const value_height_value_1  = value_height_value as string
                valueSerializer.writeString(value_height_value_1)
            }
        }
    }
    public static read(buffer: DeserializerBase): ViewportRect {
        let valueDeserializer : DeserializerBase = buffer
        const x_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let x_buf : number | string | undefined
        if ((RuntimeType.UNDEFINED) != (x_buf_runtimeType))
        {
            const x_buf__selector : int32 = valueDeserializer.readInt8()
            let x_buf_ : number | string | undefined
            if (x_buf__selector == 0) {
                x_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (x_buf__selector == 1) {
                x_buf_ = (valueDeserializer.readString() as string)
            }
            else {
                throw new Error("One of the branches for x_buf_ has to be chosen through deserialisation.")
            }
            x_buf = (x_buf_ as number | string)
        }
        const x_result : number | string | undefined = x_buf
        const y_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let y_buf : number | string | undefined
        if ((RuntimeType.UNDEFINED) != (y_buf_runtimeType))
        {
            const y_buf__selector : int32 = valueDeserializer.readInt8()
            let y_buf_ : number | string | undefined
            if (y_buf__selector == 0) {
                y_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (y_buf__selector == 1) {
                y_buf_ = (valueDeserializer.readString() as string)
            }
            else {
                throw new Error("One of the branches for y_buf_ has to be chosen through deserialisation.")
            }
            y_buf = (y_buf_ as number | string)
        }
        const y_result : number | string | undefined = y_buf
        const width_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let width_buf : number | string | undefined
        if ((RuntimeType.UNDEFINED) != (width_buf_runtimeType))
        {
            const width_buf__selector : int32 = valueDeserializer.readInt8()
            let width_buf_ : number | string | undefined
            if (width_buf__selector == 0) {
                width_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (width_buf__selector == 1) {
                width_buf_ = (valueDeserializer.readString() as string)
            }
            else {
                throw new Error("One of the branches for width_buf_ has to be chosen through deserialisation.")
            }
            width_buf = (width_buf_ as number | string)
        }
        const width_result : number | string | undefined = width_buf
        const height_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let height_buf : number | string | undefined
        if ((RuntimeType.UNDEFINED) != (height_buf_runtimeType))
        {
            const height_buf__selector : int32 = valueDeserializer.readInt8()
            let height_buf_ : number | string | undefined
            if (height_buf__selector == 0) {
                height_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (height_buf__selector == 1) {
                height_buf_ = (valueDeserializer.readString() as string)
            }
            else {
                throw new Error("One of the branches for height_buf_ has to be chosen through deserialisation.")
            }
            height_buf = (height_buf_ as number | string)
        }
        const height_result : number | string | undefined = height_buf
        let value : ViewportRect = ({x: x_result, y: y_result, width: width_result, height: height_result} as ViewportRect)
        return value
    }
}
