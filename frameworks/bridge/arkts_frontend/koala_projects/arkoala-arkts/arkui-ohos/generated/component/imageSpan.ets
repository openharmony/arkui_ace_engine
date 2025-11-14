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
import { Resource_serializer } from "./../framework/resource"
import { image_PixelMap_serializer } from "./../framework/ohos.multimedia.image"
import { ColorFilter_serializer, ColorFilter, ResourceStr } from "./units"
import { drawing_ColorFilter_serializer } from "./../framework/ohos.graphics.drawing"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkBaseSpanPeer, BaseSpan, ArkBaseSpanComponent, ArkBaseSpanStyle } from "./span"
import { ImageSpanAlignment, ImageFit } from "./enums"
import { extractors, AttributeModifier, hookImageSpanAttributeModifier, AttributeUpdater } from "#handwritten"
import { default as drawing } from "@ohos.graphics.drawing"
import { ImageErrorCallback, ImageError } from "./image"
import { default as image } from "@ohos.multimedia.image"
import { CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { Resource } from "global.resource"
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { ImageSpanModifier } from "./../ImageSpanModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
import { ModifierStateManager } from '../CommonModifier';
export class ArkImageSpanPeer extends ArkBaseSpanPeer {
    attributeSet?: ImageSpanModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkImageSpanPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._ImageSpan_construct(peerId, flags)
        const _peer  = new ArkImageSpanPeer(_peerPtr, peerId, 'ImageSpan', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setImageSpanOptionsAttribute(value: ResourceStr | image.PixelMap): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value instanceof ResourceStr) {
            thisSerializer.writeInt8((0).toChar())
            const valueForIdx0  = value as ResourceStr
            if (valueForIdx0 instanceof string) {
                thisSerializer.writeInt8((0).toChar())
                const valueForIdx0ForIdx0  = valueForIdx0 as string
                thisSerializer.writeString(valueForIdx0ForIdx0)
            } else if (valueForIdx0 instanceof Resource) {
                thisSerializer.writeInt8((1).toChar())
                const valueForIdx0ForIdx1  = valueForIdx0 as Resource
                Resource_serializer.write(thisSerializer, valueForIdx0ForIdx1)
            }
        } else if (value instanceof image.PixelMap) {
            thisSerializer.writeInt8((1).toChar())
            const valueForIdx1  = value as image.PixelMap
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
    setColorFilterAttribute(value: ColorFilter | drawing.ColorFilter | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof ColorFilter) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as ColorFilter
                ColorFilter_serializer.write(thisSerializer, valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof drawing.ColorFilter) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as drawing.ColorFilter
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
    setAltAttribute(value: image.PixelMap | undefined): void {
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
    setImageSpanOptions(value: ResourceStr | image.PixelMap): this {
        throw new Error("Unimplemented method setImageSpanOptions")
    }
    verticalAlign(value: ImageSpanAlignment | undefined): this {
        throw new Error("Unimplemented method verticalAlign")
    }
    colorFilter(value: ColorFilter | drawing.ColorFilter | undefined): this {
        throw new Error("Unimplemented method colorFilter")
    }
    objectFit(value: ImageFit | undefined): this {
        throw new Error("Unimplemented method objectFit")
    }
    onComplete(value: ImageCompleteCallback | undefined): this {
        throw new Error("Unimplemented method onComplete")
    }
    onError(value: ImageErrorCallback | undefined): this {
        throw new Error("Unimplemented method onError")
    }
    alt(value: image.PixelMap | undefined): this {
        throw new Error("Unimplemented method alt")
    }
    attributeModifier(value: AttributeModifier<ImageSpanAttribute> | AttributeModifier<BaseSpan> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkImageSpanStyle extends ArkBaseSpanStyle implements ImageSpanAttribute {
    verticalAlign_value?: ImageSpanAlignment | undefined
    colorFilter_value?: ColorFilter | drawing.ColorFilter | undefined
    objectFit_value?: ImageFit | undefined
    onComplete_value?: ImageCompleteCallback | undefined
    onError_value?: ImageErrorCallback | undefined
    alt_value?: image.PixelMap | undefined
    attributeModifier_value?: AttributeModifier<ImageSpanAttribute> | AttributeModifier<CommonMethod> | undefined
    setImageSpanOptions(value: ResourceStr | image.PixelMap): this {
        return this
    }
    verticalAlign(value: ImageSpanAlignment | undefined): this {
        return this
    }
    colorFilter(value: ColorFilter | drawing.ColorFilter | undefined): this {
        return this
    }
    objectFit(value: ImageFit | undefined): this {
        return this
    }
    onComplete(value: ImageCompleteCallback | undefined): this {
        return this
    }
    onError(value: ImageErrorCallback | undefined): this {
        return this
    }
    alt(value: image.PixelMap | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<ImageSpanAttribute> | AttributeModifier<BaseSpan> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
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
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkImageSpanPeer)
    }
    public setImageSpanOptions(value: ResourceStr | image.PixelMap): this {
        if (this.checkPriority("setImageSpanOptions")) {
            const value_casted = value as (ResourceStr | image.PixelMap)
            this.getPeer()?.setImageSpanOptionsAttribute(value_casted)
            this.applyOptionsFinish('ImageSpanAttribute');
            return this
        }
        return this
    }
    public verticalAlign(value: ImageSpanAlignment | undefined): this {
        if (this.checkPriority("verticalAlign")) {
            const value_casted = value as (ImageSpanAlignment | undefined)
            this.getPeer()?.setVerticalAlignAttribute(value_casted)
            return this
        }
        return this
    }
    public colorFilter(value: ColorFilter | drawing.ColorFilter | undefined): this {
        if (this.checkPriority("colorFilter")) {
            const value_casted = value as (ColorFilter | drawing.ColorFilter | undefined)
            this.getPeer()?.setColorFilterAttribute(value_casted)
            return this
        }
        return this
    }
    public objectFit(value: ImageFit | undefined): this {
        if (this.checkPriority("objectFit")) {
            const value_casted = value as (ImageFit | undefined)
            this.getPeer()?.setObjectFitAttribute(value_casted)
            return this
        }
        return this
    }
    public onComplete(value: ImageCompleteCallback | undefined): this {
        if (this.checkPriority("onComplete")) {
            const value_casted = value as (ImageCompleteCallback | undefined)
            this.getPeer()?.setOnCompleteAttribute(value_casted)
            return this
        }
        return this
    }
    public onError(value: ImageErrorCallback | undefined): this {
        if (this.checkPriority("onError")) {
            const value_casted = value as (ImageErrorCallback | undefined)
            this.getPeer()?.setOnErrorAttribute(value_casted)
            return this
        }
        return this
    }
    public alt(value: image.PixelMap | undefined): this {
        if (this.checkPriority("alt")) {
            const value_casted = value as (image.PixelMap | undefined)
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
    @memo
    style: ((attributes: ImageSpanAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkImageSpanComponent>((): ArkImageSpanComponent => {
        return new ArkImageSpanComponent()
    })
    NodeAttach<ArkImageSpanPeer>((): ArkImageSpanPeer => ArkImageSpanPeer.create(receiver), (peer: ArkImageSpanPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
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
