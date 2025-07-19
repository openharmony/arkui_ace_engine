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
import { DrawableDescriptor_serializer, DrawableDescriptor } from "./../generated/ohos.arkui.drawableDescriptor"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkImagePeer, ImageAttribute, ArkImageComponent, ArkImageStyle, ArkImageSet } from "./image"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonMethodSet } from "./common"
import { ResourceStr } from "./units"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkMediaCachedImagePeer extends ArkImagePeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkMediaCachedImagePeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._MediaCachedImage_construct(peerId, flags)
        const _peer  = new ArkMediaCachedImagePeer(_peerPtr, peerId, "MediaCachedImage", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setMediaCachedImageOptionsAttribute(src: image.PixelMap | ResourceStr | DrawableDescriptor | ASTCResource): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let src_type : int32 = RuntimeType.UNDEFINED
        src_type = runtimeType(src)
        if (TypeChecker.isimage_PixelMap(src, false, false)) {
            thisSerializer.writeInt8((0).toChar())
            const src_0  = src as image.PixelMap
            image_PixelMap_serializer.write(thisSerializer, src_0)
        }
        else if ((RuntimeType.STRING == src_type) || (RuntimeType.OBJECT == src_type)) {
            thisSerializer.writeInt8((1).toChar())
            const src_1  = src as ResourceStr
            let src_1_type : int32 = RuntimeType.UNDEFINED
            src_1_type = runtimeType(src_1)
            if (RuntimeType.STRING == src_1_type) {
                thisSerializer.writeInt8((0).toChar())
                const src_1_0  = src_1 as string
                thisSerializer.writeString(src_1_0)
            }
            else if (RuntimeType.OBJECT == src_1_type) {
                thisSerializer.writeInt8((1).toChar())
                const src_1_1  = src_1 as Resource
                Resource_serializer.write(thisSerializer, src_1_1)
            }
        }
        else if (TypeChecker.isDrawableDescriptor(src)) {
            thisSerializer.writeInt8((2).toChar())
            const src_2  = src as DrawableDescriptor
            DrawableDescriptor_serializer.write(thisSerializer, src_2)
        }
        else if (TypeChecker.isASTCResource(src, false, false)) {
            thisSerializer.writeInt8((3).toChar())
            const src_3  = src as ASTCResource
            ASTCResource_serializer.write(thisSerializer, src_3)
        }
        ArkUIGeneratedNativeModule._MediaCachedImageInterface_setMediaCachedImageOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface ASTCResource {
    sources: Array<string>;
    column: number;
}
export interface MediaCachedImageAttribute extends ImageAttribute {
    attributeModifier(value: AttributeModifier<MediaCachedImageAttribute> | AttributeModifier<ImageAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkMediaCachedImageStyle extends ArkImageStyle implements MediaCachedImageAttribute {
    attributeModifier_value?: AttributeModifier<MediaCachedImageAttribute> | AttributeModifier<CommonMethod> | undefined
    public attributeModifier(value: AttributeModifier<MediaCachedImageAttribute> | AttributeModifier<ImageAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: MediaCachedImageAttribute): void {
        super.apply(target)
    }
}

export class ArkMediaCachedImageComponent extends ArkImageComponent implements MediaCachedImageAttribute {
    getPeer(): ArkMediaCachedImagePeer {
        return (this.peer as ArkMediaCachedImagePeer)
    }
    public setMediaCachedImageOptions(src: image.PixelMap | ResourceStr | DrawableDescriptor | ASTCResource): this {
        if (this.checkPriority("setMediaCachedImageOptions")) {
            const src_casted = src as (image.PixelMap | ResourceStr | DrawableDescriptor | ASTCResource)
            this.getPeer()?.setMediaCachedImageOptionsAttribute(src_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<MediaCachedImageAttribute> | AttributeModifier<ImageAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withMediaCachedImageStyle(receiver: MediaCachedImageAttribute, modifier: AttributeModifier<MediaCachedImageAttribute> | AttributeModifier<ImageAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkMediaCachedImageStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("MediaCachedImage")
// export function MediaCachedImage(
//     src: image.PixelMap | ResourceStr | DrawableDescriptor | ASTCResource,
//     @memo
//     content_?: () => void,
// ): MediaCachedImageAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function MediaCachedImage(
    @memo
    style: ((attributes: MediaCachedImageAttribute) => void) | undefined,
    src: image.PixelMap | ResourceStr | DrawableDescriptor | ASTCResource,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkMediaCachedImageComponent>((): ArkMediaCachedImageComponent => {
        return new ArkMediaCachedImageComponent()
    })
    NodeAttach<ArkMediaCachedImagePeer>((): ArkMediaCachedImagePeer => ArkMediaCachedImagePeer.create(receiver), (_: ArkMediaCachedImagePeer): void => {
        receiver.setMediaCachedImageOptions(src)
        style?.(receiver)
        withMediaCachedImageStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkMediaCachedImageSet extends ArkImageSet implements MediaCachedImageAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    applyModifierPatch(component: MediaCachedImageAttribute): void {
    }
    public attributeModifier(value: AttributeModifier<MediaCachedImageAttribute> | AttributeModifier<ImageAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class ASTCResource_serializer {
    public static write(buffer: SerializerBase, value: ASTCResource): void {
        let valueSerializer : SerializerBase = buffer
        const value_sources  = value.sources
        valueSerializer.writeInt32((value_sources.length).toInt())
        for (let value_sources_counter_i = 0; value_sources_counter_i < value_sources.length; value_sources_counter_i++) {
            const value_sources_element : string = value_sources[value_sources_counter_i]
            valueSerializer.writeString(value_sources_element)
        }
        const value_column  = value.column
        valueSerializer.writeNumber(value_column)
    }
    public static read(buffer: DeserializerBase): ASTCResource {
        let valueDeserializer : DeserializerBase = buffer
        const sources_buf_length : int32 = valueDeserializer.readInt32()
        let sources_buf : Array<string> = new Array<string>(sources_buf_length)
        for (let sources_buf_i = 0; sources_buf_i < sources_buf_length; sources_buf_i++) {
            sources_buf[sources_buf_i] = (valueDeserializer.readString() as string)
        }
        const sources_result : Array<string> = sources_buf
        const column_result : number = (valueDeserializer.readNumber() as number)
        let value : ASTCResource = ({sources: sources_result, column: column_result} as ASTCResource)
        return value
    }
}
