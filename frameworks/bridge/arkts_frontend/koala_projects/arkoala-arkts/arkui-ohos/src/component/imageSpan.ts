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
import { ArkBaseSpanPeer, BaseSpan, ArkBaseSpanComponent, ArkBaseSpanStyle } from "./span"
import { ImageSpanAlignment, ImageFit } from "./enums"
import { ColorFilter, ResourceStr } from "./units"
import { DrawingColorFilter } from "./arkui-drawing"
import { ImageErrorCallback, ImageError } from "./image"
import { PixelMap } from "./arkui-pixelmap"
import { Resource } from "global/resource"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"

import { ArkCommonMethodComponent, ArkCommonMethodStyle, CommonMethod } from "./common"
export class ArkImageSpanPeer extends ArkBaseSpanPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkImageSpanPeer {
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
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as ResourceStr
            let value_0_type : int32 = RuntimeType.UNDEFINED
            value_0_type = runtimeType(value_0)
            if (RuntimeType.STRING == value_0_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_0_0  = value_0 as string
                thisSerializer.writeString(value_0_0)
            }
            else if (RuntimeType.OBJECT == value_0_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_0_1  = value_0 as Resource
                thisSerializer.writeResource(value_0_1)
            }
        }
        else if (TypeChecker.isPixelMap(value, false, false)) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as PixelMap
            thisSerializer.writePixelMap(value_1)
        }
        ArkUIGeneratedNativeModule._ImageSpanInterface_setImageSpanOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    verticalAlignAttribute(value: ImageSpanAlignment | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as ImageSpanAlignment)
            thisSerializer.writeInt32(TypeChecker.ImageSpanAlignment_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._ImageSpanAttribute_verticalAlign(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    colorFilterAttribute(value: ColorFilter | DrawingColorFilter | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColorFilter(value_value)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as ColorFilter
                thisSerializer.writeColorFilter(value_value_0)
            }
            else if (TypeChecker.isDrawingColorFilter(value_value)) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as DrawingColorFilter
                thisSerializer.writeDrawingColorFilter(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._ImageSpanAttribute_colorFilter(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    objectFitAttribute(value: ImageFit | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as ImageFit)
            thisSerializer.writeInt32(TypeChecker.ImageFit_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._ImageSpanAttribute_objectFit(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onCompleteAttribute(value: ImageCompleteCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ImageSpanAttribute_onComplete(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onErrorAttribute(value: ImageErrorCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ImageSpanAttribute_onError(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    altAttribute(value: PixelMap | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writePixelMap(value_value)
        }
        ArkUIGeneratedNativeModule._ImageSpanAttribute_alt(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export type ImageSpanInterface = (value: ResourceStr | PixelMap) => ImageSpanAttribute;
export interface ImageSpanAttribute extends BaseSpan {
    verticalAlign(value: ImageSpanAlignment | undefined): this
    colorFilter(value: ColorFilter | DrawingColorFilter | undefined): this
    objectFit(value: ImageFit | undefined): this
    onComplete(value: ImageCompleteCallback | undefined): this
    onError(value: ImageErrorCallback | undefined): this
    alt(value: PixelMap | undefined): this
}
export class ArkImageSpanStyle extends ArkBaseSpanStyle implements ImageSpanAttribute {
    verticalAlign_value?: ImageSpanAlignment | undefined
    colorFilter_value?: ColorFilter | DrawingColorFilter | undefined
    objectFit_value?: ImageFit | undefined
    onComplete_value?: ImageCompleteCallback | undefined
    onError_value?: ImageErrorCallback | undefined
    alt_value?: PixelMap | undefined
    public verticalAlign(value: ImageSpanAlignment | undefined): this {
        return this
    }
    public colorFilter(value: ColorFilter | DrawingColorFilter | undefined): this {
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
    public alt(value: PixelMap | undefined): this {
        return this
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
    public setImageSpanOptions(value: ResourceStr | PixelMap): this {
        if (this.checkPriority("setImageSpanOptions")) {
            const value_casted = value as (ResourceStr | PixelMap)
            this.getPeer()?.setImageSpanOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    public verticalAlign(value: ImageSpanAlignment | undefined): this {
        if (this.checkPriority("verticalAlign")) {
            const value_casted = value as (ImageSpanAlignment | undefined)
            this.getPeer()?.verticalAlignAttribute(value_casted)
            return this
        }
        return this
    }
    public colorFilter(value: ColorFilter | DrawingColorFilter | undefined): this {
        if (this.checkPriority("colorFilter")) {
            const value_casted = value as (ColorFilter | DrawingColorFilter | undefined)
            this.getPeer()?.colorFilterAttribute(value_casted)
            return this
        }
        return this
    }
    public objectFit(value: ImageFit | undefined): this {
        if (this.checkPriority("objectFit")) {
            const value_casted = value as (ImageFit | undefined)
            this.getPeer()?.objectFitAttribute(value_casted)
            return this
        }
        return this
    }
    public onComplete(value: ImageCompleteCallback | undefined): this {
        if (this.checkPriority("onComplete")) {
            const value_casted = value as (ImageCompleteCallback | undefined)
            this.getPeer()?.onCompleteAttribute(value_casted)
            return this
        }
        return this
    }
    public onError(value: ImageErrorCallback | undefined): this {
        if (this.checkPriority("onError")) {
            const value_casted = value as (ImageErrorCallback | undefined)
            this.getPeer()?.onErrorAttribute(value_casted)
            return this
        }
        return this
    }
    public alt(value: PixelMap | undefined): this {
        if (this.checkPriority("alt")) {
            const value_casted = value as (PixelMap | undefined)
            this.getPeer()?.altAttribute(value_casted)
            return this
        }
        return this
    }
    
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function ImageSpan(
    /** @memo */
    style: ((attributes: ImageSpanAttribute) => void) | undefined,
    value: ResourceStr | PixelMap,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkImageSpanComponent()
    })
    NodeAttach<ArkImageSpanPeer>((): ArkImageSpanPeer => ArkImageSpanPeer.create(receiver), (_: ArkImageSpanPeer) => {
        receiver.setImageSpanOptions(value)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
