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
import { ArkBaseSpanPeer, BaseSpan, ArkBaseSpanComponent, ArkBaseSpanStyle, UIBaseSpan } from "./span"
import { ImageSpanAlignment, ImageFit } from "./enums"
import { ColorFilter, ResourceStr } from "./units"
import { DrawingColorFilter } from "./arkui-drawing"
import { ImageErrorCallback, ImageError } from "./image"
import { PixelMap } from "./arkui-pixelmap"
import { Resource } from "./resource"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { BuilderLambda } from "@koalaui/builderLambda"
import { UICommonBase, AttributeModifier } from "./../handwritten"
import { NodeAttach, remember } from "@koalaui/runtime"
import { ArkCommonMethodComponent, ArkCommonMethodStyle, CommonMethod, UICommonMethod } from "./common"
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
    setImageSpanOptionsAttribute(value: ResourceStr | PixelMap): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if ((RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type)) {
            thisSerializer.writeInt8(0)
            const value_0  = value as ResourceStr
            let value_0_type : int32 = RuntimeType.UNDEFINED
            value_0_type = runtimeType(value_0)
            if (RuntimeType.STRING == value_0_type) {
                thisSerializer.writeInt8(0)
                const value_0_0  = value_0 as string
                thisSerializer.writeString(value_0_0)
            }
            else if (RuntimeType.OBJECT == value_0_type) {
                thisSerializer.writeInt8(1)
                const value_0_1  = value_0 as Resource
                thisSerializer.writeResource(value_0_1)
            }
        }
        else if (TypeChecker.isPixelMap(value, false, false)) {
            thisSerializer.writeInt8(1)
            const value_1  = value as PixelMap
            thisSerializer.writePixelMap(value_1)
        }
        ArkUIGeneratedNativeModule._ImageSpanInterface_setImageSpanOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    verticalAlignAttribute(value: ImageSpanAlignment): void {
        ArkUIGeneratedNativeModule._ImageSpanAttribute_verticalAlign(this.peer.ptr, TypeChecker.ImageSpanAlignment_ToNumeric(value))
    }
    colorFilterAttribute(value: ColorFilter | DrawingColorFilter): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isColorFilter(value)) {
            thisSerializer.writeInt8(0)
            const value_0  = value as ColorFilter
            thisSerializer.writeColorFilter(value_0)
        }
        else if (TypeChecker.isDrawingColorFilter(value)) {
            thisSerializer.writeInt8(1)
            const value_1  = value as DrawingColorFilter
            thisSerializer.writeDrawingColorFilter(value_1)
        }
        ArkUIGeneratedNativeModule._ImageSpanAttribute_colorFilter(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    objectFitAttribute(value: ImageFit): void {
        ArkUIGeneratedNativeModule._ImageSpanAttribute_objectFit(this.peer.ptr, TypeChecker.ImageFit_ToNumeric(value))
    }
    onCompleteAttribute(value: ImageCompleteCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ImageSpanAttribute_onComplete(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onErrorAttribute(value: ImageErrorCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ImageSpanAttribute_onError(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    altAttribute(value: PixelMap): void {
        ArkUIGeneratedNativeModule._ImageSpanAttribute_alt(this.peer.ptr, toPeerPtr(value))
    }
}

export interface ImageSpanAttribute extends BaseSpan {
    verticalAlign(value: ImageSpanAlignment): this
    colorFilter(value: ColorFilter | DrawingColorFilter): this
    objectFit(value: ImageFit): this
    onComplete(value: ImageCompleteCallback): this
    onError(value: ImageErrorCallback): this
    alt(value: PixelMap): this
    attributeModifier(value: AttributeModifier<ImageSpanAttribute> | AttributeModifier<BaseSpan> | AttributeModifier<CommonMethod> | undefined): this
}
export interface UIImageSpanAttribute extends UIBaseSpan {
    @memo
    verticalAlign(value: ImageSpanAlignment): this
    @memo
    colorFilter(value: ColorFilter | DrawingColorFilter): this
    @memo
    objectFit(value: ImageFit): this
    @memo
    onComplete(value: ImageCompleteCallback): this
    @memo
    onError(value: ImageErrorCallback): this
    @memo
    alt(value: PixelMap): this
    @memo
    attributeModifier(value: AttributeModifier<ImageSpanAttribute> | AttributeModifier<BaseSpan> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkImageSpanStyle extends ArkBaseSpanStyle implements ImageSpanAttribute {
    verticalAlign_value?: ImageSpanAlignment
    colorFilter_value?: ColorFilter | DrawingColorFilter
    objectFit_value?: ImageFit
    onComplete_value?: ImageCompleteCallback
    onError_value?: ImageErrorCallback
    alt_value?: PixelMap
    public verticalAlign(value: ImageSpanAlignment): this {
        return this
    }
    public colorFilter(value: ColorFilter | DrawingColorFilter): this {
        return this
    }
    public objectFit(value: ImageFit): this {
        return this
    }
    public onComplete(value: ImageCompleteCallback): this {
        return this
    }
    public onError(value: ImageErrorCallback): this {
        return this
    }
    public alt(value: PixelMap): this {
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
@memo_stable
export class ArkImageSpanComponent extends ArkBaseSpanComponent implements UIImageSpanAttribute {
    getPeer(): ArkImageSpanPeer {
        return (this.peer as ArkImageSpanPeer)
    }
    @memo
    public setImageSpanOptions(value: ResourceStr | PixelMap): this {
        if (this.checkPriority("setImageSpanOptions")) {
            const value_casted = value as (ResourceStr | PixelMap)
            this.getPeer()?.setImageSpanOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public verticalAlign(value: ImageSpanAlignment): this {
        if (this.checkPriority("verticalAlign")) {
            const value_casted = value as (ImageSpanAlignment)
            this.getPeer()?.verticalAlignAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public colorFilter(value: ColorFilter | DrawingColorFilter): this {
        if (this.checkPriority("colorFilter")) {
            const value_casted = value as (ColorFilter | DrawingColorFilter)
            this.getPeer()?.colorFilterAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public objectFit(value: ImageFit): this {
        if (this.checkPriority("objectFit")) {
            const value_casted = value as (ImageFit)
            this.getPeer()?.objectFitAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onComplete(value: ImageCompleteCallback): this {
        if (this.checkPriority("onComplete")) {
            const value_casted = value as (ImageCompleteCallback)
            this.getPeer()?.onCompleteAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onError(value: ImageErrorCallback): this {
        if (this.checkPriority("onError")) {
            const value_casted = value as (ImageErrorCallback)
            this.getPeer()?.onErrorAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public alt(value: PixelMap): this {
        if (this.checkPriority("alt")) {
            const value_casted = value as (PixelMap)
            this.getPeer()?.altAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public attributeModifier(value: AttributeModifier<ImageSpanAttribute> | AttributeModifier<BaseSpan> | AttributeModifier<CommonMethod> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
@memo
@BuilderLambda("ImageSpan")
export function ImageSpan(
    value: ResourceStr | PixelMap,
    @memo
    content_?: () => void,
): ImageSpanAttribute {
    throw new Error("Not implemented")
}

@memo
export function ImageSpan(
    @memo
    style: ((attributes: UIImageSpanAttribute) => void) | undefined,
    value: ResourceStr | PixelMap,
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
