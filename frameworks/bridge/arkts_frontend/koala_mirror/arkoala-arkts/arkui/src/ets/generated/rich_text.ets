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
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, UICommonMethod } from "./common"
import { Callback_Void } from "./ability_component"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { BuilderLambda } from "@koalaui/builderLambda"
import { UICommonBase, AttributeModifier } from "./../handwritten"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkRichTextPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkRichTextPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._RichText_construct(peerId, flags)
        const _peer  = new ArkRichTextPeer(_peerPtr, peerId, "RichText", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setRichTextOptionsAttribute(content: string): void {
        ArkUIGeneratedNativeModule._RichTextInterface_setRichTextOptions(this.peer.ptr, content)
    }
    onStartAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._RichTextAttribute_onStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onCompleteAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._RichTextAttribute_onComplete(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}

export interface RichTextAttribute extends CommonMethod {
    onStart(value: (() => void)): this
    onComplete(value: (() => void)): this
    attributeModifier(value: AttributeModifier<RichTextAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export interface UIRichTextAttribute extends UICommonMethod {
    @memo
    onStart(value: (() => void)): this
    @memo
    onComplete(value: (() => void)): this
    @memo
    attributeModifier(value: AttributeModifier<RichTextAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkRichTextStyle extends ArkCommonMethodStyle implements RichTextAttribute {
    onStart_value?: (() => void)
    onComplete_value?: (() => void)
    public onStart(value: (() => void)): this {
        return this
    }
    public onComplete(value: (() => void)): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<RichTextAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
@memo_stable
export class ArkRichTextComponent extends ArkCommonMethodComponent implements UIRichTextAttribute {
    getPeer(): ArkRichTextPeer {
        return (this.peer as ArkRichTextPeer)
    }
    @memo
    public setRichTextOptions(content: string): this {
        if (this.checkPriority("setRichTextOptions")) {
            const content_casted = content as (string)
            this.getPeer()?.setRichTextOptionsAttribute(content_casted)
            return this
        }
        return this
    }
    @memo
    public onStart(value: (() => void)): this {
        if (this.checkPriority("onStart")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onStartAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onComplete(value: (() => void)): this {
        if (this.checkPriority("onComplete")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onCompleteAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public attributeModifier(value: AttributeModifier<RichTextAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
@memo
@BuilderLambda("RichText")
export function RichText(
    content: string,
    @memo
    content_?: () => void,
): RichTextAttribute {
    throw new Error("Not implemented")
}

@memo
export function RichText(
    @memo
    style: ((attributes: UIRichTextAttribute) => void) | undefined,
    content: string,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkRichTextComponent>((): ArkRichTextComponent => {
        return new ArkRichTextComponent()
    })
    NodeAttach<ArkRichTextPeer>((): ArkRichTextPeer => ArkRichTextPeer.create(receiver), (_: ArkRichTextPeer): void => {
        receiver.setRichTextOptions(content)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
