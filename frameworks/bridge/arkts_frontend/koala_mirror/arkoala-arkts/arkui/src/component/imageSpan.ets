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
import { Resource_serializer, Resource } from "./../generated/resource"
import { image_PixelMap_serializer, image } from "./../generated/ohos.multimedia.image"
import { ColorFilter_serializer, ColorFilter, ResourceStr } from "./units"
import { drawing_ColorFilter_serializer, drawing } from "./../generated/ohos.graphics.drawing"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkBaseSpanPeer, BaseSpan, ArkBaseSpanComponent, ArkBaseSpanStyle, ArkBaseSpanSet } from "./span"
import { ImageSpanAlignment, ImageFit } from "./enums"
import { ImageErrorCallback, ImageError } from "./image"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonMethodSet } from "./common"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkImageSpanPeer extends ArkBaseSpanPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkImageSpanPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._ImageSpan_construct(peerId, flags)
        const _peer  = new ArkImageSpanPeer(_peerPtr, peerId, "ImageSpan", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setImageSpanOptionsAttribute(value: ResourceStr | image.PixelMap): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if ((RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type)) {
            thisSerializer.writeInt8((0).toChar())
            const value_0  = value as ResourceStr
            let value_0_type : int32 = RuntimeType.UNDEFINED
            value_0_type = runtimeType(value_0)
            if (RuntimeType.STRING == value_0_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_0_0  = value_0 as string
                thisSerializer.writeString(value_0_0)
            }
            else if (RuntimeType.OBJECT == value_0_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_0_1  = value_0 as Resource
                Resource_serializer.write(thisSerializer, value_0_1)
            }
        }
        else if (TypeChecker.isimage_PixelMap(value, false, false)) {
            thisSerializer.writeInt8((1).toChar())
            const value_1  = value as image.PixelMap
            image_PixelMap_serializer.write(thisSerializer, value_1)
        }
        ArkUIGeneratedNativeModule._ImageSpanInterface_setImageSpanOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setVerticalAlignAttribute(value: ImageSpanAlignment | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as ImageSpanAlignment)
            thisSerializer.writeInt32(TypeChecker.ImageSpanAlignment_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._ImageSpanAttribute_setVerticalAlign(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setColorFilterAttribute(value: ColorFilter | drawing.ColorFilter | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColorFilter(value_value)) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as ColorFilter
                ColorFilter_serializer.write(thisSerializer, value_value_0)
            }
            else if (TypeChecker.isdrawing_ColorFilter(value_value)) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as drawing.ColorFilter
                drawing_ColorFilter_serializer.write(thisSerializer, value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._ImageSpanAttribute_setColorFilter(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setObjectFitAttribute(value: ImageFit | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as ImageFit)
            thisSerializer.writeInt32(TypeChecker.ImageFit_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._ImageSpanAttribute_setObjectFit(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnCompleteAttribute(value: ImageCompleteCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ImageSpanAttribute_setOnComplete(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnErrorAttribute(value: ImageErrorCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ImageSpanAttribute_setOnError(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAltAttribute(value: image.PixelMap | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            image_PixelMap_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._ImageSpanAttribute_setAlt(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface ImageSpanAttribute extends BaseSpan {
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
    public verticalAlign(value: ImageSpanAlignment | undefined): this {
        return this
    }
    public colorFilter(value: ColorFilter | drawing.ColorFilter | undefined): this {
        return this
    }
    public objectFit(value: ImageFit | undefined): this {
        return this
    }
    public onComplete(value: ImageCompleteCallback | undefined): this {
        return this
    }
    public onError(value: ImageErrorCallback | undefined): this {
        return this
    }
    public alt(value: image.PixelMap | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<ImageSpanAttribute> | AttributeModifier<BaseSpan> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: ImageSpanAttribute): void {
        super.apply(target)
        if (this.verticalAlign_value !== undefined)
            target.verticalAlign(this.verticalAlign_value!)
        if (this.colorFilter_value !== undefined)
            target.colorFilter(this.colorFilter_value!)
        if (this.objectFit_value !== undefined)
            target.objectFit(this.objectFit_value!)
        if (this.onComplete_value !== undefined)
            target.onComplete(this.onComplete_value!)
        if (this.onError_value !== undefined)
            target.onError(this.onError_value!)
        if (this.alt_value !== undefined)
            target.alt(this.alt_value!)
    }
}
export type ImageCompleteCallback = (result: ImageLoadResult) => void;
export interface ImageLoadResult {
    width: number;
    height: number;
    componentWidth: number;
    componentHeight: number;
    loadingStatus: number;
    contentWidth: number;
    contentHeight: number;
    contentOffsetX: number;
    contentOffsetY: number;
}

export class ArkImageSpanComponent extends ArkBaseSpanComponent implements ImageSpanAttribute {
    getPeer(): ArkImageSpanPeer {
        return (this.peer as ArkImageSpanPeer)
    }
    public setImageSpanOptions(value: ResourceStr | image.PixelMap): this {
        if (this.checkPriority("setImageSpanOptions")) {
            const value_casted = value as (ResourceStr | image.PixelMap)
            this.getPeer()?.setImageSpanOptionsAttribute(value_casted)
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
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withImageSpanStyle(receiver: ImageSpanAttribute, modifier: AttributeModifier<ImageSpanAttribute> | AttributeModifier<BaseSpan> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkImageSpanStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("ImageSpan")
// export function ImageSpan(
//     value: ResourceStr | image.PixelMap,
//     @memo
//     content_?: () => void,
// ): ImageSpanAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function ImageSpan(
    @memo
    style: ((attributes: ImageSpanAttribute) => void) | undefined,
    value: ResourceStr | image.PixelMap,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkImageSpanComponent>((): ArkImageSpanComponent => {
        return new ArkImageSpanComponent()
    })
    NodeAttach<ArkImageSpanPeer>((): ArkImageSpanPeer => ArkImageSpanPeer.create(receiver), (_: ArkImageSpanPeer): void => {
        receiver.setImageSpanOptions(value)
        style?.(receiver)
        withImageSpanStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkImageSpanSet extends ArkBaseSpanSet implements ImageSpanAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _verticalAlign_flag?: boolean
    _verticalAlign0_value?: ImageSpanAlignment | undefined
    _colorFilter_flag?: boolean
    _colorFilter0_value?: ColorFilter | drawing.ColorFilter | undefined
    _objectFit_flag?: boolean
    _objectFit0_value?: ImageFit | undefined
    _onComplete_flag?: boolean
    _onComplete0_value?: ImageCompleteCallback | undefined
    _onError_flag?: boolean
    _onError0_value?: ImageErrorCallback | undefined
    _alt_flag?: boolean
    _alt0_value?: image.PixelMap | undefined
    applyModifierPatch(component: ImageSpanAttribute): void {
        if (this._verticalAlign_flag)
            component.verticalAlign((this._verticalAlign0_value as ImageSpanAlignment | undefined))
        if (this._colorFilter_flag)
            component.colorFilter((this._colorFilter0_value as ColorFilter | drawing.ColorFilter | undefined))
        if (this._objectFit_flag)
            component.objectFit((this._objectFit0_value as ImageFit | undefined))
        if (this._onComplete_flag)
            component.onComplete((this._onComplete0_value as ImageCompleteCallback | undefined))
        if (this._onError_flag)
            component.onError((this._onError0_value as ImageErrorCallback | undefined))
        if (this._alt_flag)
            component.alt((this._alt0_value as image.PixelMap | undefined))
    }
    public verticalAlign(value: ImageSpanAlignment | undefined): this {
        this._verticalAlign_flag = true
        this._verticalAlign0_value = value
        return this
    }
    public colorFilter(value: ColorFilter | drawing.ColorFilter | undefined): this {
        this._colorFilter_flag = true
        this._colorFilter0_value = value
        return this
    }
    public objectFit(value: ImageFit | undefined): this {
        this._objectFit_flag = true
        this._objectFit0_value = value
        return this
    }
    public onComplete(value: ImageCompleteCallback | undefined): this {
        this._onComplete_flag = true
        this._onComplete0_value = value
        return this
    }
    public onError(value: ImageErrorCallback | undefined): this {
        this._onError_flag = true
        this._onError0_value = value
        return this
    }
    public alt(value: image.PixelMap | undefined): this {
        this._alt_flag = true
        this._alt0_value = value
        return this
    }
    public attributeModifier(value: AttributeModifier<ImageSpanAttribute> | AttributeModifier<BaseSpan> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class ImageLoadResult_serializer {
    public static write(buffer: SerializerBase, value: ImageLoadResult): void {
        let valueSerializer : SerializerBase = buffer
        const value_width  = value.width
        valueSerializer.writeNumber(value_width)
        const value_height  = value.height
        valueSerializer.writeNumber(value_height)
        const value_componentWidth  = value.componentWidth
        valueSerializer.writeNumber(value_componentWidth)
        const value_componentHeight  = value.componentHeight
        valueSerializer.writeNumber(value_componentHeight)
        const value_loadingStatus  = value.loadingStatus
        valueSerializer.writeNumber(value_loadingStatus)
        const value_contentWidth  = value.contentWidth
        valueSerializer.writeNumber(value_contentWidth)
        const value_contentHeight  = value.contentHeight
        valueSerializer.writeNumber(value_contentHeight)
        const value_contentOffsetX  = value.contentOffsetX
        valueSerializer.writeNumber(value_contentOffsetX)
        const value_contentOffsetY  = value.contentOffsetY
        valueSerializer.writeNumber(value_contentOffsetY)
    }
    public static read(buffer: DeserializerBase): ImageLoadResult {
        let valueDeserializer : DeserializerBase = buffer
        const width_result : number = (valueDeserializer.readNumber() as number)
        const height_result : number = (valueDeserializer.readNumber() as number)
        const componentWidth_result : number = (valueDeserializer.readNumber() as number)
        const componentHeight_result : number = (valueDeserializer.readNumber() as number)
        const loadingStatus_result : number = (valueDeserializer.readNumber() as number)
        const contentWidth_result : number = (valueDeserializer.readNumber() as number)
        const contentHeight_result : number = (valueDeserializer.readNumber() as number)
        const contentOffsetX_result : number = (valueDeserializer.readNumber() as number)
        const contentOffsetY_result : number = (valueDeserializer.readNumber() as number)
        let value : ImageLoadResult = ({width: width_result, height: height_result, componentWidth: componentWidth_result, componentHeight: componentHeight_result, loadingStatus: loadingStatus_result, contentWidth: contentWidth_result, contentHeight: contentHeight_result, contentOffsetX: contentOffsetX_result, contentOffsetY: contentOffsetY_result} as ImageLoadResult)
        return value
    }
}
