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
import { image_PixelMap_serializer, image } from "./../generated/ohos.multimedia.image"
import { Resource_serializer, Resource } from "./../generated/resource"
import { DrawableDescriptor_serializer, DrawableDescriptor } from "./../generated/ohos.arkui.drawableDescriptor"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkImagePeer, ImageAttribute, ArkImageComponent, ArkImageStyle, ImageModifier } from "./image"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, CommonMethodModifier } from "./common"
import { ResourceStr } from "./units"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
import { AttributeUpdaterFlag } from "./../generated/AttributeUpdater"
export class ArkMediaCachedImagePeer extends ArkImagePeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkMediaCachedImagePeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._MediaCachedImage_construct(peerId, flags)
        const _peer  = new ArkMediaCachedImagePeer(_peerPtr, peerId, 'MediaCachedImage', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setMediaCachedImageOptionsAttribute(src: image.PixelMap | ResourceStr | DrawableDescriptor | ASTCResource): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (src instanceof image.PixelMap) {
            thisSerializer.writeInt8((0).toChar())
            const srcForIdx0  = src as image.PixelMap
            image_PixelMap_serializer.write(thisSerializer, srcForIdx0)
        } else if (src instanceof ResourceStr) {
            thisSerializer.writeInt8((1).toChar())
            const srcForIdx1  = src as ResourceStr
            if (srcForIdx1 instanceof string) {
                thisSerializer.writeInt8((0).toChar())
                const srcForIdx1ForIdx0  = srcForIdx1 as string
                thisSerializer.writeString(srcForIdx1ForIdx0)
            } else if (srcForIdx1 instanceof Resource) {
                thisSerializer.writeInt8((1).toChar())
                const srcForIdx1ForIdx1  = srcForIdx1 as Resource
                Resource_serializer.write(thisSerializer, srcForIdx1ForIdx1)
            }
        } else if (src instanceof DrawableDescriptor) {
            thisSerializer.writeInt8((2).toChar())
            const srcForIdx2  = src as DrawableDescriptor
            DrawableDescriptor_serializer.write(thisSerializer, srcForIdx2)
        } else if (src instanceof ASTCResource) {
            thisSerializer.writeInt8((3).toChar())
            const srcForIdx3  = src as ASTCResource
            ASTCResource_serializer.write(thisSerializer, srcForIdx3)
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
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

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
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class MediaCachedImageModifier extends ImageModifier implements MediaCachedImageAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    applyModifierPatch(peer: ArkMediaCachedImagePeer): void {
        super.applyModifierPatch(peer)
    }
    mergeModifier(modifier: MediaCachedImageModifier): void {
        super.mergeModifier(modifier)
    }
    public attributeModifier(value: AttributeModifier<MediaCachedImageAttribute> | AttributeModifier<ImageAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class ASTCResource_serializer {
    public static write(buffer: SerializerBase, value: ASTCResource): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForSources  = value.sources
        valueSerializer.writeInt32((valueHolderForSources.length).toInt())
        for (let valueHolderForSourcesCounterI = 0; valueHolderForSourcesCounterI < valueHolderForSources.length; valueHolderForSourcesCounterI++) {
            const valueHolderForSourcesTmpElement : string = valueHolderForSources[valueHolderForSourcesCounterI]
            valueSerializer.writeString(valueHolderForSourcesTmpElement)
        }
        const valueHolderForColumn  = value.column
        valueSerializer.writeNumber(valueHolderForColumn)
    }
    public static read(buffer: DeserializerBase): ASTCResource {
        let valueDeserializer : DeserializerBase = buffer
        const sourcesTmpBufLength : int32 = valueDeserializer.readInt32()
        let sourcesTmpBuf : Array<string> = new Array<string>(sourcesTmpBufLength)
        for (let sourcesTmpBufBufCounterI = 0; sourcesTmpBufBufCounterI < sourcesTmpBufLength; sourcesTmpBufBufCounterI++) {
            sourcesTmpBuf[sourcesTmpBufBufCounterI] = (valueDeserializer.readString() as string)
        }
        const sourcesTmpResult : Array<string> = sourcesTmpBuf
        const columnTmpResult : number = (valueDeserializer.readNumber() as number)
        let value : ASTCResource = ({sources: sourcesTmpResult, column: columnTmpResult} as ASTCResource)
        return value
    }
}
