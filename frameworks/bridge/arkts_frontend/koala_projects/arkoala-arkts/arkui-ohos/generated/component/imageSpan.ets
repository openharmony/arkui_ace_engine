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
import { global_resource_Resource_serializer } from './../framework/resource'
import { image_PixelMap_serializer } from './../framework/ohos.multimedia.image'
import { ColorFilter_serializer, ColorFilter, ResourceStr as arkui_component_units_ResourceStr, Resource as arkui_component_units_Resource } from './units'
import { drawing_ColorFilter_serializer } from './../framework/ohos.graphics.drawing'
import { int32, int64, float32, unsafeCast } from '@koalaui/common'
import { ComponentBase } from './../ComponentBase'
import { PeerNode } from './../PeerNode'
import { ArkUIGeneratedNativeModule } from '#components'
import { ArkBaseSpanPeer, BaseSpan, ArkBaseSpanComponent } from './span'
import { ImageSpanAlignment, ImageFit } from './enums'
import { DrawingColorFilter, ImageErrorCallback, ImageError } from './image'
import { extractors, AttributeModifier, hookImageSpanAttributeModifier, AttributeUpdater } from '#handwritten'
import { default as drawing } from '@ohos.graphics.drawing'
import { PixelMap, CommonMethod, ArkCommonMethodComponent } from './common'
import { default as image } from '@ohos.multimedia.image'
import { Resource as global_resource_Resource } from 'global.resource'
import { CallbackKind } from './../framework/peers/CallbackKind'
import { CallbackTransformer } from './../CallbackTransformer'
import { memo, memo_stable, memo_skip } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { ImageSpanModifier } from './../ImageSpanModifier'
import { NodeAttach, remember } from '@koalaui/runtime'
import { ModifierStateManager } from './../CommonModifier'
export class ArkImageSpanPeer extends ArkBaseSpanPeer {
    attributeSet?: ImageSpanModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkImageSpanPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._ImageSpan_construct(peerId, flags)
        const _peer  = new ArkImageSpanPeer(_peerPtr, peerId, 'ImageSpan', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setImageSpanOptionsAttribute(value: arkui_component_units_ResourceStr | PixelMap): void {
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value instanceof arkui_component_units_ResourceStr) {
            thisSerializer.writeInt8((0).toByte())
            const valueForIdx0  = value as arkui_component_units_ResourceStr
            if (valueForIdx0 instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const valueForIdx0ForIdx0  = valueForIdx0 as string
                thisSerializer.writeString(valueForIdx0ForIdx0)
            } else if (valueForIdx0 instanceof arkui_component_units_Resource) {
                thisSerializer.writeInt8((1).toByte())
                const valueForIdx0ForIdx1  = valueForIdx0 as arkui_component_units_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueForIdx0ForIdx1)
            }
        } else if (value instanceof PixelMap) {
            thisSerializer.writeInt8((1).toByte())
            const valueForIdx1  = value as PixelMap
            image_PixelMap_serializer.write(thisSerializer, valueForIdx1)
        }
        ArkUIGeneratedNativeModule._ImageSpanInterface_setImageSpanOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setVerticalAlignAttribute(value: ImageSpanAlignment | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as ImageSpanAlignment)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageSpanAttribute_setVerticalAlign(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setColorFilterAttribute(value: ColorFilter | DrawingColorFilter | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof ColorFilter) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as ColorFilter
                ColorFilter_serializer.write(thisSerializer, valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof DrawingColorFilter) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as DrawingColorFilter
                drawing_ColorFilter_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageSpanAttribute_setColorFilter(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setObjectFitAttribute(value: ImageFit | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as ImageFit)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageSpanAttribute_setObjectFit(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnCompleteAttribute(value: ImageCompleteCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageSpanAttribute_setOnComplete(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnErrorAttribute(value: ImageErrorCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageSpanAttribute_setOnError(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAltAttribute(value: PixelMap | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            image_PixelMap_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ImageSpanAttribute_setAlt(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface ImageSpanAttribute extends BaseSpan {
    setImageSpanOptions(value: arkui_component_units_ResourceStr | PixelMap): this {
        throw new Error('Unimplemented method setImageSpanOptions')
    }
    verticalAlign(value: ImageSpanAlignment | undefined): this {
        throw new Error('Unimplemented method verticalAlign')
    }
    colorFilter(value: ColorFilter | DrawingColorFilter | undefined): this {
        throw new Error('Unimplemented method colorFilter')
    }
    objectFit(value: ImageFit | undefined): this {
        throw new Error('Unimplemented method objectFit')
    }
    onComplete(value: ImageCompleteCallback | undefined): this {
        throw new Error('Unimplemented method onComplete')
    }
    onError(value: ImageErrorCallback | undefined): this {
        throw new Error('Unimplemented method onError')
    }
    alt(value: PixelMap | undefined): this {
        throw new Error('Unimplemented method alt')
    }
    attributeModifier(value: AttributeModifier<ImageSpanAttribute> | AttributeModifier<BaseSpan> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}
export type ImageCompleteCallback = (result: ImageLoadResult) => void;
export interface ImageLoadResult {
    width: double;
    height: double;
    componentWidth: double;
    componentHeight: double;
    loadingStatus: double;
    contentWidth: double;
    contentHeight: double;
    contentOffsetX: double;
    contentOffsetY: double;
}

export class ArkImageSpanComponent extends ArkBaseSpanComponent implements ImageSpanAttribute {
    getPeer(): ArkImageSpanPeer {
        return (this.peer as ArkImageSpanPeer)
    }
    public setImageSpanOptions(value: arkui_component_units_ResourceStr | PixelMap): this {
        if (this.checkPriority('setImageSpanOptions')) {
            const value_casted = value as (arkui_component_units_ResourceStr | PixelMap)
            this.getPeer()?.setImageSpanOptionsAttribute(value_casted)
            this.applyOptionsFinish('ImageSpanAttribute');
            return this
        }
        return this
    }
    public verticalAlign(value: ImageSpanAlignment | undefined): this {
        if (this.checkPriority('verticalAlign')) {
            const value_casted = value as (ImageSpanAlignment | undefined)
            this.getPeer()?.setVerticalAlignAttribute(value_casted)
            return this
        }
        return this
    }
    public colorFilter(value: ColorFilter | DrawingColorFilter | undefined): this {
        if (this.checkPriority('colorFilter')) {
            const value_casted = value as (ColorFilter | DrawingColorFilter | undefined)
            this.getPeer()?.setColorFilterAttribute(value_casted)
            return this
        }
        return this
    }
    public objectFit(value: ImageFit | undefined): this {
        if (this.checkPriority('objectFit')) {
            const value_casted = value as (ImageFit | undefined)
            this.getPeer()?.setObjectFitAttribute(value_casted)
            return this
        }
        return this
    }
    public onComplete(value: ImageCompleteCallback | undefined): this {
        if (this.checkPriority('onComplete')) {
            const value_casted = value as (ImageCompleteCallback | undefined)
            this.getPeer()?.setOnCompleteAttribute(value_casted)
            return this
        }
        return this
    }
    public onError(value: ImageErrorCallback | undefined): this {
        if (this.checkPriority('onError')) {
            const value_casted = value as (ImageErrorCallback | undefined)
            this.getPeer()?.setOnErrorAttribute(value_casted)
            return this
        }
        return this
    }
    public alt(value: PixelMap | undefined): this {
        if (this.checkPriority('alt')) {
            const value_casted = value as (PixelMap | undefined)
            this.getPeer()?.setAltAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<ImageSpanAttribute> | AttributeModifier<BaseSpan> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookImageSpanAttributeModifier(this, value);
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
export function ImageSpanImpl(
    @memo @memo_skip
    style: ((attributes: ImageSpanAttribute) => void) | undefined,
    @memo @memo_skip
    content_?: () => void,
): void {
    const receiver = remember<ArkImageSpanComponent>((): ArkImageSpanComponent => {
        return new ArkImageSpanComponent()
    })
    NodeAttach<ArkImageSpanPeer>((): ArkImageSpanPeer => ArkImageSpanPeer.create(receiver), (_: ArkImageSpanPeer): void => {
        style?.(receiver)
        content_?.()
    })
}

export class ImageLoadResult_serializer {
    public static write(buffer: SerializerBase, value: ImageLoadResult): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForWidth  = value.width
        valueSerializer.writeFloat64(valueHolderForWidth)
        const valueHolderForHeight  = value.height
        valueSerializer.writeFloat64(valueHolderForHeight)
        const valueHolderForComponentWidth  = value.componentWidth
        valueSerializer.writeFloat64(valueHolderForComponentWidth)
        const valueHolderForComponentHeight  = value.componentHeight
        valueSerializer.writeFloat64(valueHolderForComponentHeight)
        const valueHolderForLoadingStatus  = value.loadingStatus
        valueSerializer.writeFloat64(valueHolderForLoadingStatus)
        const valueHolderForContentWidth  = value.contentWidth
        valueSerializer.writeFloat64(valueHolderForContentWidth)
        const valueHolderForContentHeight  = value.contentHeight
        valueSerializer.writeFloat64(valueHolderForContentHeight)
        const valueHolderForContentOffsetX  = value.contentOffsetX
        valueSerializer.writeFloat64(valueHolderForContentOffsetX)
        const valueHolderForContentOffsetY  = value.contentOffsetY
        valueSerializer.writeFloat64(valueHolderForContentOffsetY)
    }
    public static read(buffer: DeserializerBase): ImageLoadResult {
        let valueDeserializer : DeserializerBase = buffer
        const widthTmpResult : double = valueDeserializer.readFloat64()
        const heightTmpResult : double = valueDeserializer.readFloat64()
        const componentWidthTmpResult : double = valueDeserializer.readFloat64()
        const componentHeightTmpResult : double = valueDeserializer.readFloat64()
        const loadingStatusTmpResult : double = valueDeserializer.readFloat64()
        const contentWidthTmpResult : double = valueDeserializer.readFloat64()
        const contentHeightTmpResult : double = valueDeserializer.readFloat64()
        const contentOffsetXTmpResult : double = valueDeserializer.readFloat64()
        const contentOffsetYTmpResult : double = valueDeserializer.readFloat64()
        let value : ImageLoadResult = ({width: widthTmpResult, height: heightTmpResult, componentWidth: componentWidthTmpResult, componentHeight: componentHeightTmpResult, loadingStatus: loadingStatusTmpResult, contentWidth: contentWidthTmpResult, contentHeight: contentHeightTmpResult, contentOffsetX: contentOffsetXTmpResult, contentOffsetY: contentOffsetYTmpResult} as ImageLoadResult)
        return value
    }
}
