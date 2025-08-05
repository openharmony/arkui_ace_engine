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
import { Resource_serializer, Resource } from "./../generated/resource"
import { image_PixelMap_serializer, image } from "./../generated/ohos.multimedia.image"
import { ColorFilter_serializer, ColorFilter, ResourceStr } from "./units"
import { drawing_ColorFilter_serializer, drawing } from "./../generated/ohos.graphics.drawing"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkBaseSpanPeer, BaseSpan, ArkBaseSpanComponent, ArkBaseSpanStyle, BaseSpanModifier } from "./span"
import { ImageSpanAlignment, ImageFit } from "./enums"
import { ImageErrorCallback, ImageError } from "./image"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, CommonMethodModifier } from "./common"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
import { AttributeUpdaterFlag } from "./../generated/AttributeUpdater"
export class ArkImageSpanPeer extends ArkBaseSpanPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
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
            thisSerializer.writeInt32(TypeChecker.ImageSpanAlignment_ToNumeric(valueTmpValue))
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
            thisSerializer.writeInt32(TypeChecker.ImageFit_ToNumeric(valueTmpValue))
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
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

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
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ImageSpanModifier extends BaseSpanModifier implements ImageSpanAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _verticalAlign_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _verticalAlign_0_0value?: ImageSpanAlignment | undefined
    _colorFilter_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _colorFilter_0_0value?: ColorFilter | drawing.ColorFilter | undefined
    _objectFit_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _objectFit_0_0value?: ImageFit | undefined
    _onComplete_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onComplete_0_0value?: ImageCompleteCallback | undefined
    _onError_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onError_0_0value?: ImageErrorCallback | undefined
    _alt_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _alt_0_0value?: image.PixelMap | undefined
    applyModifierPatch(peer: ArkImageSpanPeer): void {
        super.applyModifierPatch(peer)
        if (this._verticalAlign_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._verticalAlign_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setVerticalAlignAttribute((this._verticalAlign_0_0value as ImageSpanAlignment | undefined));
                    this._verticalAlign_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._verticalAlign_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._verticalAlign_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setVerticalAlignAttribute((undefined as ImageSpanAlignment | undefined));
                }
            }
        }
        if (this._colorFilter_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._colorFilter_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setColorFilterAttribute((this._colorFilter_0_0value as ColorFilter | drawing.ColorFilter | undefined));
                    this._colorFilter_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._colorFilter_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._colorFilter_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setColorFilterAttribute((undefined as ColorFilter | drawing.ColorFilter | undefined));
                }
            }
        }
        if (this._objectFit_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._objectFit_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setObjectFitAttribute((this._objectFit_0_0value as ImageFit | undefined));
                    this._objectFit_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._objectFit_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._objectFit_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setObjectFitAttribute((undefined as ImageFit | undefined));
                }
            }
        }
        if (this._onComplete_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onComplete_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnCompleteAttribute((this._onComplete_0_0value as ImageCompleteCallback | undefined));
                    this._onComplete_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onComplete_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onComplete_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnCompleteAttribute((undefined as ImageCompleteCallback | undefined));
                }
            }
        }
        if (this._onError_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onError_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnErrorAttribute((this._onError_0_0value as ImageErrorCallback | undefined));
                    this._onError_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onError_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onError_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnErrorAttribute((undefined as ImageErrorCallback | undefined));
                }
            }
        }
        if (this._alt_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._alt_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAltAttribute((this._alt_0_0value as image.PixelMap | undefined));
                    this._alt_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._alt_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._alt_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAltAttribute((undefined as image.PixelMap | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: ImageSpanModifier): void {
        super.mergeModifier(modifier)
        if (modifier._verticalAlign_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._verticalAlign_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.verticalAlign(modifier._verticalAlign_0_0value);
                    break;
                }
                default: {
                    this.verticalAlign((undefined as ImageSpanAlignment | undefined));
                }
            }
        }
        if (modifier._colorFilter_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._colorFilter_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.colorFilter(modifier._colorFilter_0_0value);
                    break;
                }
                default: {
                    this.colorFilter((undefined as ColorFilter | drawing.ColorFilter | undefined));
                }
            }
        }
        if (modifier._objectFit_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._objectFit_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.objectFit(modifier._objectFit_0_0value);
                    break;
                }
                default: {
                    this.objectFit((undefined as ImageFit | undefined));
                }
            }
        }
        if (modifier._onComplete_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onComplete_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onComplete(modifier._onComplete_0_0value);
                    break;
                }
                default: {
                    this.onComplete((undefined as ImageCompleteCallback | undefined));
                }
            }
        }
        if (modifier._onError_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onError_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onError(modifier._onError_0_0value);
                    break;
                }
                default: {
                    this.onError((undefined as ImageErrorCallback | undefined));
                }
            }
        }
        if (modifier._alt_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._alt_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.alt(modifier._alt_0_0value);
                    break;
                }
                default: {
                    this.alt((undefined as image.PixelMap | undefined));
                }
            }
        }
    }
    verticalAlign(value: ImageSpanAlignment | undefined): this {
        if (((this._verticalAlign_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._verticalAlign_0_flag = AttributeUpdaterFlag.UPDATE
            this._verticalAlign_0_0value = value
        } else
        {
            this._verticalAlign_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    colorFilter(value: ColorFilter | drawing.ColorFilter | undefined): this {
        if (((this._colorFilter_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._colorFilter_0_flag = AttributeUpdaterFlag.UPDATE
            this._colorFilter_0_0value = value
        } else
        {
            this._colorFilter_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    objectFit(value: ImageFit | undefined): this {
        if (((this._objectFit_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._objectFit_0_flag = AttributeUpdaterFlag.UPDATE
            this._objectFit_0_0value = value
        } else
        {
            this._objectFit_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onComplete(value: ImageCompleteCallback | undefined): this {
        if (((this._onComplete_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onComplete_0_flag = AttributeUpdaterFlag.UPDATE
            this._onComplete_0_0value = value
        } else
        {
            this._onComplete_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onError(value: ImageErrorCallback | undefined): this {
        if (((this._onError_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onError_0_flag = AttributeUpdaterFlag.UPDATE
            this._onError_0_0value = value
        } else
        {
            this._onError_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    alt(value: image.PixelMap | undefined): this {
        if (((this._alt_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._alt_0_flag = AttributeUpdaterFlag.UPDATE
            this._alt_0_0value = value
        } else
        {
            this._alt_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<ImageSpanAttribute> | AttributeModifier<BaseSpan> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class ImageLoadResult_serializer {
    public static write(buffer: SerializerBase, value: ImageLoadResult): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForWidth  = value.width
        valueSerializer.writeNumber(valueHolderForWidth)
        const valueHolderForHeight  = value.height
        valueSerializer.writeNumber(valueHolderForHeight)
        const valueHolderForComponentWidth  = value.componentWidth
        valueSerializer.writeNumber(valueHolderForComponentWidth)
        const valueHolderForComponentHeight  = value.componentHeight
        valueSerializer.writeNumber(valueHolderForComponentHeight)
        const valueHolderForLoadingStatus  = value.loadingStatus
        valueSerializer.writeNumber(valueHolderForLoadingStatus)
        const valueHolderForContentWidth  = value.contentWidth
        valueSerializer.writeNumber(valueHolderForContentWidth)
        const valueHolderForContentHeight  = value.contentHeight
        valueSerializer.writeNumber(valueHolderForContentHeight)
        const valueHolderForContentOffsetX  = value.contentOffsetX
        valueSerializer.writeNumber(valueHolderForContentOffsetX)
        const valueHolderForContentOffsetY  = value.contentOffsetY
        valueSerializer.writeNumber(valueHolderForContentOffsetY)
    }
    public static read(buffer: DeserializerBase): ImageLoadResult {
        let valueDeserializer : DeserializerBase = buffer
        const widthTmpResult : number = (valueDeserializer.readNumber() as number)
        const heightTmpResult : number = (valueDeserializer.readNumber() as number)
        const componentWidthTmpResult : number = (valueDeserializer.readNumber() as number)
        const componentHeightTmpResult : number = (valueDeserializer.readNumber() as number)
        const loadingStatusTmpResult : number = (valueDeserializer.readNumber() as number)
        const contentWidthTmpResult : number = (valueDeserializer.readNumber() as number)
        const contentHeightTmpResult : number = (valueDeserializer.readNumber() as number)
        const contentOffsetXTmpResult : number = (valueDeserializer.readNumber() as number)
        const contentOffsetYTmpResult : number = (valueDeserializer.readNumber() as number)
        let value : ImageLoadResult = ({width: widthTmpResult, height: heightTmpResult, componentWidth: componentWidthTmpResult, componentHeight: componentHeightTmpResult, loadingStatus: loadingStatusTmpResult, contentWidth: contentWidthTmpResult, contentHeight: contentHeightTmpResult, contentOffsetX: contentOffsetXTmpResult, contentOffsetY: contentOffsetYTmpResult} as ImageLoadResult)
        return value
    }
}
