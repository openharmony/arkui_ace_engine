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

import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, wrapCallback, NativeBuffer } from "@koalaui/interop"
import { TextBackgroundStyle_serializer, TextBackgroundStyle } from "./span"
import { int32, int64, float32 } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
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
    setTextBackgroundStyleAttribute(value: TextBackgroundStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            TextBackgroundStyle_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._ContainerSpanAttribute_setTextBackgroundStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface ContainerSpanAttribute {
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
    public textBackgroundStyle(value: TextBackgroundStyle | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<ContainerSpanAttribute> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: ContainerSpanAttribute): void {
        if (this.textBackgroundStyle_value !== undefined)
            target.textBackgroundStyle(this.textBackgroundStyle_value!)
    }
}

export class ArkContainerSpanComponent extends ComponentBase implements ContainerSpanAttribute {
    getPeer(): ArkContainerSpanPeer {
        return (this.peer as ArkContainerSpanPeer)
    }
    public setContainerSpanOptions(): this {
        if (this.checkPriority("setContainerSpanOptions")) {
            this.getPeer()?.setContainerSpanOptionsAttribute()
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
    _modifier?: AttributeModifier<ContainerSpanAttribute> | undefined
    public attributeModifier(value: AttributeModifier<ContainerSpanAttribute> | undefined): this {
        this._modifier = value
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withContainerSpanStyle(receiver: ContainerSpanAttribute, modifier: AttributeModifier<ContainerSpanAttribute> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkContainerSpanStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<ContainerSpanAttribute>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<ContainerSpanAttribute>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("ContainerSpan")
// export function ContainerSpan(
//     
//     @memo
//     content_?: () => void,
// ): ContainerSpanAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function ContainerSpan(
    @memo
    style: ((attributes: ContainerSpanAttribute) => void) | undefined,
    
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkContainerSpanComponent>((): ArkContainerSpanComponent => {
        return new ArkContainerSpanComponent()
    })
    NodeAttach<ArkContainerSpanPeer>((): ArkContainerSpanPeer => ArkContainerSpanPeer.create(receiver), (_: ArkContainerSpanPeer): void => {
        receiver.setContainerSpanOptions()
        style?.(receiver)
        withContainerSpanStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkContainerSpanSet implements ContainerSpanAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _textBackgroundStyle_flag?: boolean
    _textBackgroundStyle0_value?: TextBackgroundStyle | undefined
    applyModifierPatch(component: ContainerSpanAttribute): void {
        if (this._textBackgroundStyle_flag)
            component.textBackgroundStyle((this._textBackgroundStyle0_value as TextBackgroundStyle | undefined))
    }
    public textBackgroundStyle(value: TextBackgroundStyle | undefined): this {
        this._textBackgroundStyle_flag = true
        this._textBackgroundStyle0_value = value
        return this
    }
    public attributeModifier(value: AttributeModifier<ContainerSpanAttribute> | undefined): this {
        throw new Error("Not implemented")
    }
}
