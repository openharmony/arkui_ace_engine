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

import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer } from "@koalaui/interop"
import { TextBackgroundStyle_serializer, TextBackgroundStyle } from "./span"
import { int32, int64, float32 } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { AttributeModifier, hookContainerSpanAttributeModifier, AttributeUpdater } from "#handwritten"
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { ContainerSpanModifier } from "./../ContainerSpanModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkContainerSpanPeer extends PeerNode {
    attributeSet?: ContainerSpanModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkContainerSpanPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._ContainerSpan_construct(peerId, flags)
        const _peer  = new ArkContainerSpanPeer(_peerPtr, peerId, 'ContainerSpan', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setContainerSpanOptionsAttribute(): void {
        ArkUIGeneratedNativeModule._ContainerSpanInterface_setContainerSpanOptions(this.peer.ptr)
    }
    setTextBackgroundStyleAttribute(value: TextBackgroundStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            TextBackgroundStyle_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ContainerSpanAttribute_setTextBackgroundStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface ContainerSpanAttribute {
    setContainerSpanOptions(): this {
        throw new Error("Unimplemented method setContainerSpanOptions")
    }
    textBackgroundStyle(value: TextBackgroundStyle | undefined): this {
        throw new Error("Unimplemented method textBackgroundStyle")
    }
    attributeModifier(value: AttributeModifier<ContainerSpanAttribute> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkContainerSpanStyle implements ContainerSpanAttribute {
    textBackgroundStyle_value?: TextBackgroundStyle | undefined
    attributeModifier_value?: AttributeModifier<ContainerSpanAttribute> | undefined
    setContainerSpanOptions(): this {
        return this
    }
    textBackgroundStyle(value: TextBackgroundStyle | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<ContainerSpanAttribute> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkContainerSpanComponent extends ComponentBase implements ContainerSpanAttribute {
    getPeer(): ArkContainerSpanPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkContainerSpanPeer)
    }
    public setContainerSpanOptions(): this {
        if (this.checkPriority("setContainerSpanOptions")) {
            this.getPeer()?.setContainerSpanOptionsAttribute()
            this.applyOptionsFinish('ContainerSpanAttribute');
            return this
        }
        return this
    }
    public textBackgroundStyle(value: TextBackgroundStyle | undefined): this {
        if (this.checkPriority("textBackgroundStyle")) {
            const value_casted = value as (TextBackgroundStyle | undefined)
            this.getPeer()?.setTextBackgroundStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<ContainerSpanAttribute> | undefined): this {
        hookContainerSpanAttributeModifier(this, value);
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
export function ContainerSpanImpl(
    @memo
    style: ((attributes: ContainerSpanAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkContainerSpanComponent>((): ArkContainerSpanComponent => {
        return new ArkContainerSpanComponent()
    })
    NodeAttach<ArkContainerSpanPeer>((): ArkContainerSpanPeer => ArkContainerSpanPeer.create(receiver), (peer: ArkContainerSpanPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
    })
}

