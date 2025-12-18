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

import { ArkThemeScopeManager } from '#arktheme'
import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from '@koalaui/interop'
import { image_PixelMap_serializer } from './../framework/ohos.multimedia.image'
import { global_resource_Resource_serializer } from './../framework/resource'
import { int32, int64, float32, unsafeCast } from '@koalaui/common'
import { ComponentBase } from './../ComponentBase'
import { PeerNode } from './../PeerNode'
import { ArkUIGeneratedNativeModule } from '#components'
import { ArkCommonMethodPeer, CommonMethod, PixelMap, ArkCommonMethodComponent } from './common'
import { ResourceColor, Resource as arkui_component_units_Resource, Length } from './units'
import { Color as arkui_component_enums_Color, LineCapStyle, LineJoinStyle } from './enums'
import { Resource as global_resource_Resource } from 'global.resource'
import { AttributeModifier, extractors, hookShapeAttributeModifier, AttributeUpdater } from '#handwritten'
import { default as image } from '@ohos.multimedia.image'
import { CallbackKind } from './../framework/peers/CallbackKind'
import { CallbackTransformer } from './../CallbackTransformer'
import { memo, memo_stable, memo_skip } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { ShapeModifier } from './../ShapeModifier'
import { NodeAttach, remember } from '@koalaui/runtime'
import { ModifierStateManager } from './../CommonModifier'
export class ArkShapePeer extends ArkCommonMethodPeer {
    attributeSet?: ShapeModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkShapePeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Shape_construct(peerId, flags)
        const _peer  = new ArkShapePeer(_peerPtr, peerId, 'Shape', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setShapeOptionsAttribute(value?: PixelMap): void {
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
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
            if (valueTmpValue instanceof arkui_component_enums_Color) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as arkui_component_enums_Color
                thisSerializer.writeInt32((valueTmpValueForIdx0.getOrdinal()) % (12))
            } else if (valueTmpValue instanceof int32) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as int32
                thisSerializer.writeInt32(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof arkui_component_units_Resource) {
                thisSerializer.writeInt8((3).toByte())
                const valueTmpValueForIdx3  = valueTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
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
            if (valueTmpValue instanceof arkui_component_enums_Color) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as arkui_component_enums_Color
                thisSerializer.writeInt32((valueTmpValueForIdx0.getOrdinal()) % (12))
            } else if (valueTmpValue instanceof int32) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as int32
                thisSerializer.writeInt32(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof arkui_component_units_Resource) {
                thisSerializer.writeInt8((3).toByte())
                const valueTmpValueForIdx3  = valueTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_setFill(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setStrokeDashOffsetAttribute(value: double | string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof double) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as double
                thisSerializer.writeFloat64(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx1)
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
                    thisSerializer.writeInt8((0).toByte())
                    const valueTmpValueTmpElementForIdx0  = valueTmpValueTmpElement as string
                    thisSerializer.writeString(valueTmpValueTmpElementForIdx0)
                } else if (valueTmpValueTmpElement instanceof double) {
                    thisSerializer.writeInt8((1).toByte())
                    const valueTmpValueTmpElementForIdx1  = valueTmpValueTmpElement as double
                    thisSerializer.writeFloat64(valueTmpValueTmpElementForIdx1)
                } else if (valueTmpValueTmpElement instanceof arkui_component_units_Resource) {
                    thisSerializer.writeInt8((2).toByte())
                    const valueTmpValueTmpElementForIdx2  = valueTmpValueTmpElement as arkui_component_units_Resource
                    global_resource_Resource_serializer.write(thisSerializer, valueTmpValueTmpElementForIdx2)
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
            thisSerializer.writeInt32(valueTmpValue.valueOf())
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
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_setStrokeLineJoin(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setStrokeMiterLimitAttribute(value: double | string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof double) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as double
                thisSerializer.writeFloat64(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_setStrokeMiterLimit(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setStrokeOpacityAttribute(value: double | string | global_resource_Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof double) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as double
                thisSerializer.writeFloat64(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof global_resource_Resource) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as global_resource_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_setStrokeOpacity(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFillOpacityAttribute(value: double | string | global_resource_Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof double) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as double
                thisSerializer.writeFloat64(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof global_resource_Resource) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as global_resource_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_setFillOpacity(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setStrokeWidthAttribute(value: double | string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof double) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as double
                thisSerializer.writeFloat64(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx1)
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
    setMeshAttribute(value: Array<double> | undefined, column: int32 | undefined, row: int32 | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeInt32((valueTmpValue.length).toInt())
            for (let valueTmpValueCounterI = 0; valueTmpValueCounterI < valueTmpValue.length; valueTmpValueCounterI++) {
                const valueTmpValueTmpElement : double = valueTmpValue[valueTmpValueCounterI]
                thisSerializer.writeFloat64(valueTmpValueTmpElement)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (column !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const columnTmpValue  = column!
            thisSerializer.writeInt32(columnTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (row !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const rowTmpValue  = row!
            thisSerializer.writeInt32(rowTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ShapeAttribute_setMesh(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface ViewportRect {
    x?: double | string;
    y?: double | string;
    width?: double | string;
    height?: double | string;
}
export interface ShapeAttribute extends CommonMethod {
    setShapeOptions(value?: PixelMap): this {
        throw new Error('Unimplemented method setShapeOptions')
    }
    viewPort(value: ViewportRect | undefined): this {
        throw new Error('Unimplemented method viewPort')
    }
    stroke(value: ResourceColor | undefined): this {
        throw new Error('Unimplemented method stroke')
    }
    fill(value: ResourceColor | undefined): this {
        throw new Error('Unimplemented method fill')
    }
    strokeDashOffset(value: double | string | undefined): this {
        throw new Error('Unimplemented method strokeDashOffset')
    }
    strokeDashArray(value: Array<Length> | undefined): this {
        throw new Error('Unimplemented method strokeDashArray')
    }
    strokeLineCap(value: LineCapStyle | undefined): this {
        throw new Error('Unimplemented method strokeLineCap')
    }
    strokeLineJoin(value: LineJoinStyle | undefined): this {
        throw new Error('Unimplemented method strokeLineJoin')
    }
    strokeMiterLimit(value: double | string | undefined): this {
        throw new Error('Unimplemented method strokeMiterLimit')
    }
    strokeOpacity(value: double | string | global_resource_Resource | undefined): this {
        throw new Error('Unimplemented method strokeOpacity')
    }
    fillOpacity(value: double | string | global_resource_Resource | undefined): this {
        throw new Error('Unimplemented method fillOpacity')
    }
    strokeWidth(value: double | string | undefined): this {
        throw new Error('Unimplemented method strokeWidth')
    }
    antiAlias(value: boolean | undefined): this {
        throw new Error('Unimplemented method antiAlias')
    }
    mesh(value: Array<double> | undefined, column: int32 | undefined, row: int32 | undefined): this {
        throw new Error('Unimplemented method mesh')
    }
    attributeModifier(value: AttributeModifier<ShapeAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}

export class ArkShapeComponent extends ArkCommonMethodComponent implements ShapeAttribute {
    getPeer(): ArkShapePeer {
        return (this.peer as ArkShapePeer)
    }
    public setShapeOptions(value?: PixelMap): this {
        if (this.checkPriority('setShapeOptions')) {
            const value_casted = value as (PixelMap | undefined)
            this.getPeer()?.setShapeOptionsAttribute(value_casted)
            this.applyOptionsFinish('ShapeAttribute');
            return this
        }
        return this
    }
    public viewPort(value: ViewportRect | undefined): this {
        if (this.checkPriority('viewPort')) {
            const value_casted = value as (ViewportRect | undefined)
            this.getPeer()?.setViewPortAttribute(value_casted)
            return this
        }
        return this
    }
    public stroke(value: ResourceColor | undefined): this {
        if (this.checkPriority('stroke')) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setStrokeAttribute(value_casted)
            return this
        }
        return this
    }
    public fill(value: ResourceColor | undefined): this {
        if (this.checkPriority('fill')) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setFillAttribute(value_casted)
            return this
        }
        return this
    }
    public strokeDashOffset(value: double | string | undefined): this {
        if (this.checkPriority('strokeDashOffset')) {
            const value_casted = value as (double | string | undefined)
            this.getPeer()?.setStrokeDashOffsetAttribute(value_casted)
            return this
        }
        return this
    }
    public strokeDashArray(value: Array<Length> | undefined): this {
        if (this.checkPriority('strokeDashArray')) {
            const value_casted = value as (Array<Length> | undefined)
            this.getPeer()?.setStrokeDashArrayAttribute(value_casted)
            return this
        }
        return this
    }
    public strokeLineCap(value: LineCapStyle | undefined): this {
        if (this.checkPriority('strokeLineCap')) {
            const value_casted = value as (LineCapStyle | undefined)
            this.getPeer()?.setStrokeLineCapAttribute(value_casted)
            return this
        }
        return this
    }
    public strokeLineJoin(value: LineJoinStyle | undefined): this {
        if (this.checkPriority('strokeLineJoin')) {
            const value_casted = value as (LineJoinStyle | undefined)
            this.getPeer()?.setStrokeLineJoinAttribute(value_casted)
            return this
        }
        return this
    }
    public strokeMiterLimit(value: double | string | undefined): this {
        if (this.checkPriority('strokeMiterLimit')) {
            const value_casted = value as (double | string | undefined)
            this.getPeer()?.setStrokeMiterLimitAttribute(value_casted)
            return this
        }
        return this
    }
    public strokeOpacity(value: double | string | global_resource_Resource | undefined): this {
        if (this.checkPriority('strokeOpacity')) {
            const value_casted = value as (double | string | global_resource_Resource | undefined)
            this.getPeer()?.setStrokeOpacityAttribute(value_casted)
            return this
        }
        return this
    }
    public fillOpacity(value: double | string | global_resource_Resource | undefined): this {
        if (this.checkPriority('fillOpacity')) {
            const value_casted = value as (double | string | global_resource_Resource | undefined)
            this.getPeer()?.setFillOpacityAttribute(value_casted)
            return this
        }
        return this
    }
    public strokeWidth(value: double | string | undefined): this {
        if (this.checkPriority('strokeWidth')) {
            const value_casted = value as (double | string | undefined)
            this.getPeer()?.setStrokeWidthAttribute(value_casted)
            return this
        }
        return this
    }
    public antiAlias(value: boolean | undefined): this {
        if (this.checkPriority('antiAlias')) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setAntiAliasAttribute(value_casted)
            return this
        }
        return this
    }
    public mesh(value: Array<double> | undefined, column: int32 | undefined, row: int32 | undefined): this {
        if (this.checkPriority('mesh')) {
            const value_casted = value as (Array<double> | undefined)
            const column_casted = column as (int32 | undefined)
            const row_casted = row as (int32 | undefined)
            this.getPeer()?.setMeshAttribute(value_casted, column_casted, row_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<ShapeAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookShapeAttributeModifier(this, value);
        })
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
    public applyOptionsFinish(traceName: string): void {
        super.applyOptionsFinish(traceName)
    }
}

@memo
export function ShapeImpl(
    @memo @memo_skip
    style: ((attributes: ShapeAttribute) => void) | undefined,
    @memo @memo_skip
    content_?: () => void,
): void {
    const receiver = remember<ArkShapeComponent>((): ArkShapeComponent => {
        return new ArkShapeComponent()
    })
    NodeAttach<ArkShapePeer>((): ArkShapePeer => ArkShapePeer.create(receiver), (_: ArkShapePeer): void => {
        style?.(receiver)
        content_?.()
    })
}

export class ViewportRect_serializer {
    public static write(buffer: SerializerBase, value: ViewportRect): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForX  = value.x
        if (valueHolderForX !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForXTmpValue  = valueHolderForX!
            if (valueHolderForXTmpValue instanceof double) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForXTmpValueForIdx0  = valueHolderForXTmpValue as double
                valueSerializer.writeFloat64(valueHolderForXTmpValueForIdx0)
            } else if (valueHolderForXTmpValue instanceof string) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForXTmpValueForIdx1  = valueHolderForXTmpValue as string
                valueSerializer.writeString(valueHolderForXTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForY  = value.y
        if (valueHolderForY !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForYTmpValue  = valueHolderForY!
            if (valueHolderForYTmpValue instanceof double) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForYTmpValueForIdx0  = valueHolderForYTmpValue as double
                valueSerializer.writeFloat64(valueHolderForYTmpValueForIdx0)
            } else if (valueHolderForYTmpValue instanceof string) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForYTmpValueForIdx1  = valueHolderForYTmpValue as string
                valueSerializer.writeString(valueHolderForYTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForWidth  = value.width
        if (valueHolderForWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForWidthTmpValue  = valueHolderForWidth!
            if (valueHolderForWidthTmpValue instanceof double) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForWidthTmpValueForIdx0  = valueHolderForWidthTmpValue as double
                valueSerializer.writeFloat64(valueHolderForWidthTmpValueForIdx0)
            } else if (valueHolderForWidthTmpValue instanceof string) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForWidthTmpValueForIdx1  = valueHolderForWidthTmpValue as string
                valueSerializer.writeString(valueHolderForWidthTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForHeight  = value.height
        if (valueHolderForHeight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForHeightTmpValue  = valueHolderForHeight!
            if (valueHolderForHeightTmpValue instanceof double) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForHeightTmpValueForIdx0  = valueHolderForHeightTmpValue as double
                valueSerializer.writeFloat64(valueHolderForHeightTmpValueForIdx0)
            } else if (valueHolderForHeightTmpValue instanceof string) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForHeightTmpValueForIdx1  = valueHolderForHeightTmpValue as string
                valueSerializer.writeString(valueHolderForHeightTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ViewportRect {
        let valueDeserializer : DeserializerBase = buffer
        const xTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let xTmpBuf : double | string | undefined = undefined
        if ((xTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const xTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let xTmpBufOpt : double | string | undefined
            if (xTmpBufOptUnionSelector == (0).toByte()) {
                xTmpBufOpt = valueDeserializer.readFloat64()
            } else if (xTmpBufOptUnionSelector == (1).toByte()) {
                xTmpBufOpt = (valueDeserializer.readString() as string)
            } else {
                throw new Error('One of the branches for xTmpBufOpt has to be chosen through deserialisation.')
            }
            xTmpBuf = (xTmpBufOpt as double | string)
        }
        const xTmpResult : double | string | undefined = xTmpBuf
        const yTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let yTmpBuf : double | string | undefined = undefined
        if ((yTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const yTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let yTmpBufOpt : double | string | undefined
            if (yTmpBufOptUnionSelector == (0).toByte()) {
                yTmpBufOpt = valueDeserializer.readFloat64()
            } else if (yTmpBufOptUnionSelector == (1).toByte()) {
                yTmpBufOpt = (valueDeserializer.readString() as string)
            } else {
                throw new Error('One of the branches for yTmpBufOpt has to be chosen through deserialisation.')
            }
            yTmpBuf = (yTmpBufOpt as double | string)
        }
        const yTmpResult : double | string | undefined = yTmpBuf
        const widthTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let widthTmpBuf : double | string | undefined = undefined
        if ((widthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const widthTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let widthTmpBufOpt : double | string | undefined
            if (widthTmpBufOptUnionSelector == (0).toByte()) {
                widthTmpBufOpt = valueDeserializer.readFloat64()
            } else if (widthTmpBufOptUnionSelector == (1).toByte()) {
                widthTmpBufOpt = (valueDeserializer.readString() as string)
            } else {
                throw new Error('One of the branches for widthTmpBufOpt has to be chosen through deserialisation.')
            }
            widthTmpBuf = (widthTmpBufOpt as double | string)
        }
        const widthTmpResult : double | string | undefined = widthTmpBuf
        const heightTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let heightTmpBuf : double | string | undefined = undefined
        if ((heightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const heightTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let heightTmpBufOpt : double | string | undefined
            if (heightTmpBufOptUnionSelector == (0).toByte()) {
                heightTmpBufOpt = valueDeserializer.readFloat64()
            } else if (heightTmpBufOptUnionSelector == (1).toByte()) {
                heightTmpBufOpt = (valueDeserializer.readString() as string)
            } else {
                throw new Error('One of the branches for heightTmpBufOpt has to be chosen through deserialisation.')
            }
            heightTmpBuf = (heightTmpBufOpt as double | string)
        }
        const heightTmpResult : double | string | undefined = heightTmpBuf
        let value : ViewportRect = ({x: xTmpResult, y: yTmpResult, width: widthTmpResult, height: heightTmpResult} as ViewportRect)
        return value
    }
}
