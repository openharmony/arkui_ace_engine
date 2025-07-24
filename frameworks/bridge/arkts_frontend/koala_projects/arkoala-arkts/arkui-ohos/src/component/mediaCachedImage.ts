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
import { ArkImagePeer, ImageAttribute, ArkImageComponent, ArkImageStyle } from "./image"
import { PixelMap } from "./arkui-pixelmap"
import { ResourceStr } from "./units"
import { DrawableDescriptor } from "./arkui-drawabledescriptor"
import { Resource } from "global/resource"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"

import { ArkCommonMethodComponent, ArkCommonMethodStyle, CommonMethod } from "./common"
export class ArkMediaCachedImagePeer extends ArkImagePeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkMediaCachedImagePeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._MediaCachedImage_construct(peerId, flags)
        const _peer  = new ArkMediaCachedImagePeer(_peerPtr, peerId, "MediaCachedImage", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setMediaCachedImageOptionsAttribute(src: PixelMap | ResourceStr | DrawableDescriptor | ASTCResource): void {
        const thisSerializer : Serializer = Serializer.hold()
        let src_type : int32 = RuntimeType.UNDEFINED
        src_type = runtimeType(src)
        if (TypeChecker.isPixelMap(src, false, false)) {
            thisSerializer.writeInt8(0 as int32)
            const src_0  = src as PixelMap
            thisSerializer.writePixelMap(src_0)
        }
        else if ((RuntimeType.STRING == src_type) || (RuntimeType.OBJECT == src_type)) {
            thisSerializer.writeInt8(1 as int32)
            const src_1  = src as ResourceStr
            let src_1_type : int32 = RuntimeType.UNDEFINED
            src_1_type = runtimeType(src_1)
            if (RuntimeType.STRING == src_1_type) {
                thisSerializer.writeInt8(0 as int32)
                const src_1_0  = src_1 as string
                thisSerializer.writeString(src_1_0)
            }
            else if (RuntimeType.OBJECT == src_1_type) {
                thisSerializer.writeInt8(1 as int32)
                const src_1_1  = src_1 as Resource
                thisSerializer.writeResource(src_1_1)
            }
        }
        else if (TypeChecker.isDrawableDescriptor(src)) {
            thisSerializer.writeInt8(2 as int32)
            const src_2  = src as DrawableDescriptor
            thisSerializer.writeDrawableDescriptor(src_2)
        }
        else if (TypeChecker.isASTCResource(src, false, false)) {
            thisSerializer.writeInt8(3 as int32)
            const src_3  = src as ASTCResource
            thisSerializer.writeASTCResource(src_3)
        }
        ArkUIGeneratedNativeModule._MediaCachedImageInterface_setMediaCachedImageOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface ASTCResource {
    sources: Array<string>;
    column: number;
}
export type MediaCachedImageInterface = (src: PixelMap | ResourceStr | DrawableDescriptor | ASTCResource) => MediaCachedImageAttribute;
export interface MediaCachedImageAttribute extends ImageAttribute {
}
export class ArkMediaCachedImageStyle extends ArkImageStyle implements MediaCachedImageAttribute {
}
export class ArkMediaCachedImageComponent extends ArkImageComponent implements MediaCachedImageAttribute {
    getPeer(): ArkMediaCachedImagePeer {
        return (this.peer as ArkMediaCachedImagePeer)
    }
    public setMediaCachedImageOptions(src: PixelMap | ResourceStr | DrawableDescriptor | ASTCResource): this {
        if (this.checkPriority("setMediaCachedImageOptions")) {
            const src_casted = src as (PixelMap | ResourceStr | DrawableDescriptor | ASTCResource)
            this.getPeer()?.setMediaCachedImageOptionsAttribute(src_casted)
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
export function MediaCachedImage(
    /** @memo */
    style: ((attributes: MediaCachedImageAttribute) => void) | undefined,
    src: PixelMap | ResourceStr | DrawableDescriptor | ASTCResource,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkMediaCachedImageComponent()
    })
    NodeAttach<ArkMediaCachedImagePeer>((): ArkMediaCachedImagePeer => ArkMediaCachedImagePeer.create(receiver), (_: ArkMediaCachedImagePeer) => {
        receiver.setMediaCachedImageOptions(src)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
