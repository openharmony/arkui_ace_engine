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
import { TextBackgroundStyle } from "./span"
import { AttributeModifier, UICommonBase } from "./../handwritten"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkContainerSpanPeer extends PeerNode {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkContainerSpanPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._ContainerSpan_construct(peerId, flags)
        const _peer  = new ArkContainerSpanPeer(_peerPtr, peerId, "ContainerSpan", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setContainerSpanOptionsAttribute(): void {
        ArkUIGeneratedNativeModule._ContainerSpanInterface_setContainerSpanOptions(this.peer.ptr)
    }
    textBackgroundStyleAttribute(value: TextBackgroundStyle): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeTextBackgroundStyle(value)
        ArkUIGeneratedNativeModule._ContainerSpanAttribute_textBackgroundStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}

export interface ContainerSpanAttribute {
    textBackgroundStyle(value: TextBackgroundStyle): this
    attributeModifier(value: AttributeModifier<ContainerSpanAttribute> | undefined): this
}
export interface UIContainerSpanAttribute {
    /** @memo */
    textBackgroundStyle(value: TextBackgroundStyle): this
    /** @memo */
    attributeModifier(value: AttributeModifier<ContainerSpanAttribute> | undefined): this
}
export class ArkContainerSpanStyle implements ContainerSpanAttribute {
    textBackgroundStyle_value?: TextBackgroundStyle
    attributeModifier_value?: AttributeModifier<ContainerSpanAttribute>
    public textBackgroundStyle(value: TextBackgroundStyle): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<ContainerSpanAttribute> | undefined): this {
        throw new Error("Not implemented")
    }
}
/** @memo:stable */
export class ArkContainerSpanComponent extends ComponentBase implements UIContainerSpanAttribute {
    getPeer(): ArkContainerSpanPeer {
        return (this.peer as ArkContainerSpanPeer)
    }
    /** @memo */
    public setContainerSpanOptions(): this {
        if (this.checkPriority("setContainerSpanOptions")) {
            this.getPeer()?.setContainerSpanOptionsAttribute()
            return this
        }
        return this
    }
    /** @memo */
    public textBackgroundStyle(value: TextBackgroundStyle): this {
        if (this.checkPriority("textBackgroundStyle")) {
            const value_casted = value as (TextBackgroundStyle)
            this.getPeer()?.textBackgroundStyleAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public attributeModifier(value: AttributeModifier<ContainerSpanAttribute> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function ArkContainerSpan(
    /** @memo */
    style: ((attributes: UIContainerSpanAttribute) => void) | undefined,
    /** @memo */
    content_: (() => void) | undefined,
    
): void {
    const receiver = remember(() => {
        return new ArkContainerSpanComponent()
    })
    NodeAttach<ArkContainerSpanPeer>((): ArkContainerSpanPeer => ArkContainerSpanPeer.create(receiver), (_: ArkContainerSpanPeer) => {
        receiver.setContainerSpanOptions()
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
