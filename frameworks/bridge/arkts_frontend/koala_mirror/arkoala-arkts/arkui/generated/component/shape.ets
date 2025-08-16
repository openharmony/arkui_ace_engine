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

import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { image_PixelMap_serializer } from "./../framework/ohos.multimedia.image"
import { Resource_serializer } from "./../framework/resource"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { ResourceColor, Length } from "./units"
import { Color, LineCapStyle, LineJoinStyle } from "./enums"
import { Resource } from "global.resource"
import { AttributeModifier, AttributeUpdater, extractors } from "#handwritten"
import { default as image } from "@ohos.multimedia.image"
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkShapePeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkShapePeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Shape_construct(peerId, flags)
        const _peer  = new ArkShapePeer(_peerPtr, peerId, 'Shape', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setShapeOptionsAttribute(value?: image.PixelMap): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            image_PixelMap_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ShapeInterface_setShapeOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setViewPortAttribute(value: ViewportRect | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            ViewportRect_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_setViewPort(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setStrokeAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof Color) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueTmpValueForIdx0))
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((3).toChar())
                const valueTmpValueForIdx3  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_setStroke(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFillAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof Color) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueTmpValueForIdx0))
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((3).toChar())
                const valueTmpValueForIdx3  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_setFill(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setStrokeDashOffsetAttribute(value: Length | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValueForIdx2  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_setStrokeDashOffset(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setStrokeDashArrayAttribute(value: Array<Length> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeInt32((valueTmpValue.length).toInt())
            for (let valueTmpValueCounterI = 0; valueTmpValueCounterI < valueTmpValue.length; valueTmpValueCounterI++) {
                const valueTmpValueTmpElement : Length = valueTmpValue[valueTmpValueCounterI]
                if (valueTmpValueTmpElement instanceof string) {
                    thisSerializer.writeInt8((0).toChar())
                    const valueTmpValueTmpElementForIdx0  = valueTmpValueTmpElement as string
                    thisSerializer.writeString(valueTmpValueTmpElementForIdx0)
                } else if (valueTmpValueTmpElement instanceof number) {
                    thisSerializer.writeInt8((1).toChar())
                    const valueTmpValueTmpElementForIdx1  = valueTmpValueTmpElement as number
                    thisSerializer.writeNumber(valueTmpValueTmpElementForIdx1)
                } else if (valueTmpValueTmpElement instanceof Resource) {
                    thisSerializer.writeInt8((2).toChar())
                    const valueTmpValueTmpElementForIdx2  = valueTmpValueTmpElement as Resource
                    Resource_serializer.write(thisSerializer, valueTmpValueTmpElementForIdx2)
                }
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_setStrokeDashArray(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setStrokeLineCapAttribute(value: LineCapStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as LineCapStyle)
            thisSerializer.writeInt32(TypeChecker.LineCapStyle_ToNumeric(valueTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_setStrokeLineCap(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setStrokeLineJoinAttribute(value: LineJoinStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as LineJoinStyle)
            thisSerializer.writeInt32(TypeChecker.LineJoinStyle_ToNumeric(valueTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_setStrokeLineJoin(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setStrokeMiterLimitAttribute(value: Length | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValueForIdx2  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_setStrokeMiterLimit(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setStrokeOpacityAttribute(value: number | string | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValueForIdx2  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_setStrokeOpacity(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFillOpacityAttribute(value: number | string | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValueForIdx2  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_setFillOpacity(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setStrokeWidthAttribute(value: Length | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValueForIdx2  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_setStrokeWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAntiAliasAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_setAntiAlias(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMeshAttribute(value: Array<number> | undefined, column: number | undefined, row: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeInt32((valueTmpValue.length).toInt())
            for (let valueTmpValueCounterI = 0; valueTmpValueCounterI < valueTmpValue.length; valueTmpValueCounterI++) {
                const valueTmpValueTmpElement : number = valueTmpValue[valueTmpValueCounterI]
                thisSerializer.writeNumber(valueTmpValueTmpElement)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (column !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const columnTmpValue  = column!
            thisSerializer.writeNumber(columnTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (row !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const rowTmpValue  = row!
            thisSerializer.writeNumber(rowTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
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
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

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
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ViewportRect_serializer {
    public static write(buffer: SerializerBase, value: ViewportRect): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForX  = value.x
        if (valueHolderForX !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForXTmpValue  = valueHolderForX!
            if (valueHolderForXTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForXTmpValueForIdx0  = valueHolderForXTmpValue as string
                valueSerializer.writeString(valueHolderForXTmpValueForIdx0)
            } else if (valueHolderForXTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForXTmpValueForIdx1  = valueHolderForXTmpValue as number
                valueSerializer.writeNumber(valueHolderForXTmpValueForIdx1)
            } else if (valueHolderForXTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toChar())
                const valueHolderForXTmpValueForIdx2  = valueHolderForXTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForXTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForY  = value.y
        if (valueHolderForY !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForYTmpValue  = valueHolderForY!
            if (valueHolderForYTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForYTmpValueForIdx0  = valueHolderForYTmpValue as string
                valueSerializer.writeString(valueHolderForYTmpValueForIdx0)
            } else if (valueHolderForYTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForYTmpValueForIdx1  = valueHolderForYTmpValue as number
                valueSerializer.writeNumber(valueHolderForYTmpValueForIdx1)
            } else if (valueHolderForYTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toChar())
                const valueHolderForYTmpValueForIdx2  = valueHolderForYTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForYTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForWidth  = value.width
        if (valueHolderForWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForWidthTmpValue  = valueHolderForWidth!
            if (valueHolderForWidthTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForWidthTmpValueForIdx0  = valueHolderForWidthTmpValue as string
                valueSerializer.writeString(valueHolderForWidthTmpValueForIdx0)
            } else if (valueHolderForWidthTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForWidthTmpValueForIdx1  = valueHolderForWidthTmpValue as number
                valueSerializer.writeNumber(valueHolderForWidthTmpValueForIdx1)
            } else if (valueHolderForWidthTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toChar())
                const valueHolderForWidthTmpValueForIdx2  = valueHolderForWidthTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForWidthTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForHeight  = value.height
        if (valueHolderForHeight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForHeightTmpValue  = valueHolderForHeight!
            if (valueHolderForHeightTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForHeightTmpValueForIdx0  = valueHolderForHeightTmpValue as string
                valueSerializer.writeString(valueHolderForHeightTmpValueForIdx0)
            } else if (valueHolderForHeightTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForHeightTmpValueForIdx1  = valueHolderForHeightTmpValue as number
                valueSerializer.writeNumber(valueHolderForHeightTmpValueForIdx1)
            } else if (valueHolderForHeightTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toChar())
                const valueHolderForHeightTmpValueForIdx2  = valueHolderForHeightTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForHeightTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ViewportRect {
        let valueDeserializer : DeserializerBase = buffer
        const xTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let xTmpBuf : Length | undefined
        if ((xTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const xTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let xTmpBuf_ : string | number | Resource | undefined
            if (xTmpBuf_UnionSelector == (0).toChar()) {
                xTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (xTmpBuf_UnionSelector == (1).toChar()) {
                xTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (xTmpBuf_UnionSelector == (2).toChar()) {
                xTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for xTmpBuf_ has to be chosen through deserialisation.")
            }
            xTmpBuf = (xTmpBuf_ as string | number | Resource)
        }
        const xTmpResult : Length | undefined = xTmpBuf
        const yTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let yTmpBuf : Length | undefined
        if ((yTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const yTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let yTmpBuf_ : string | number | Resource | undefined
            if (yTmpBuf_UnionSelector == (0).toChar()) {
                yTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (yTmpBuf_UnionSelector == (1).toChar()) {
                yTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (yTmpBuf_UnionSelector == (2).toChar()) {
                yTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for yTmpBuf_ has to be chosen through deserialisation.")
            }
            yTmpBuf = (yTmpBuf_ as string | number | Resource)
        }
        const yTmpResult : Length | undefined = yTmpBuf
        const widthTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let widthTmpBuf : Length | undefined
        if ((widthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const widthTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let widthTmpBuf_ : string | number | Resource | undefined
            if (widthTmpBuf_UnionSelector == (0).toChar()) {
                widthTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (widthTmpBuf_UnionSelector == (1).toChar()) {
                widthTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (widthTmpBuf_UnionSelector == (2).toChar()) {
                widthTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for widthTmpBuf_ has to be chosen through deserialisation.")
            }
            widthTmpBuf = (widthTmpBuf_ as string | number | Resource)
        }
        const widthTmpResult : Length | undefined = widthTmpBuf
        const heightTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let heightTmpBuf : Length | undefined
        if ((heightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const heightTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let heightTmpBuf_ : string | number | Resource | undefined
            if (heightTmpBuf_UnionSelector == (0).toChar()) {
                heightTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (heightTmpBuf_UnionSelector == (1).toChar()) {
                heightTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (heightTmpBuf_UnionSelector == (2).toChar()) {
                heightTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for heightTmpBuf_ has to be chosen through deserialisation.")
            }
            heightTmpBuf = (heightTmpBuf_ as string | number | Resource)
        }
        const heightTmpResult : Length | undefined = heightTmpBuf
        let value : ViewportRect = ({x: xTmpResult, y: yTmpResult, width: widthTmpResult, height: heightTmpResult} as ViewportRect)
        return value
    }
}
