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
import { int32, int64, float32 } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, CommonMethodModifier } from "./common"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
import { AttributeUpdaterFlag } from "./../generated/AttributeUpdater"
export class ArkRichTextPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkRichTextPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._RichText_construct(peerId, flags)
        const _peer  = new ArkRichTextPeer(_peerPtr, peerId, 'RichText', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setRichTextOptionsAttribute(content: string): void {
        ArkUIGeneratedNativeModule._RichTextInterface_setRichTextOptions(this.peer.ptr, content)
    }
    setOnStartAttribute(value: (() => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RichTextAttribute_setOnStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnCompleteAttribute(value: (() => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RichTextAttribute_setOnComplete(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface RichTextAttribute extends CommonMethod {
    onStart(value: (() => void) | undefined): this {
        throw new Error("Unimplemented method onStart")
    }
    onComplete(value: (() => void) | undefined): this {
        throw new Error("Unimplemented method onComplete")
    }
    attributeModifier(value: AttributeModifier<RichTextAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkRichTextStyle extends ArkCommonMethodStyle implements RichTextAttribute {
    onStart_value?: (() => void) | undefined
    onComplete_value?: (() => void) | undefined
    attributeModifier_value?: AttributeModifier<RichTextAttribute> | AttributeModifier<CommonMethod> | undefined
    public onStart(value: (() => void) | undefined): this {
        return this
    }
    public onComplete(value: (() => void) | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<RichTextAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkRichTextComponent extends ArkCommonMethodComponent implements RichTextAttribute {
    getPeer(): ArkRichTextPeer {
        return (this.peer as ArkRichTextPeer)
    }
    public setRichTextOptions(content: string): this {
        if (this.checkPriority("setRichTextOptions")) {
            const content_casted = content as (string)
            this.getPeer()?.setRichTextOptionsAttribute(content_casted)
            return this
        }
        return this
    }
    public onStart(value: (() => void) | undefined): this {
        if (this.checkPriority("onStart")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.setOnStartAttribute(value_casted)
            return this
        }
        return this
    }
    public onComplete(value: (() => void) | undefined): this {
        if (this.checkPriority("onComplete")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.setOnCompleteAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<RichTextAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

@memo
export function RichText(
    @memo
    style: ((attributes: RichTextAttribute) => void) | undefined,
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

export class RichTextModifier extends CommonMethodModifier implements RichTextAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _onStart_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onStart_0_0value?: (() => void) | undefined
    _onComplete_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onComplete_0_0value?: (() => void) | undefined
    applyModifierPatch(peer: ArkRichTextPeer): void {
        super.applyModifierPatch(peer)
        if (this._onStart_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onStart_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnStartAttribute((this._onStart_0_0value as (() => void) | undefined));
                    this._onStart_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onStart_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onStart_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnStartAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (this._onComplete_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onComplete_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnCompleteAttribute((this._onComplete_0_0value as (() => void) | undefined));
                    this._onComplete_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onComplete_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onComplete_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnCompleteAttribute((undefined as (() => void) | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: RichTextModifier): void {
        super.mergeModifier(modifier)
        if (modifier._onStart_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onStart_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onStart(modifier._onStart_0_0value);
                    break;
                }
                default: {
                    this.onStart((undefined as (() => void) | undefined));
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
                    this.onComplete((undefined as (() => void) | undefined));
                }
            }
        }
    }
    onStart(value: (() => void) | undefined): this {
        if (((this._onStart_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onStart_0_flag = AttributeUpdaterFlag.UPDATE
            this._onStart_0_0value = value
        } else
        {
            this._onStart_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onComplete(value: (() => void) | undefined): this {
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
    public attributeModifier(value: AttributeModifier<RichTextAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
