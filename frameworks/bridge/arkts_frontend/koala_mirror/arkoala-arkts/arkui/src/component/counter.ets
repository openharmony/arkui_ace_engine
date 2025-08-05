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
import { VoidCallback } from "./units"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
import { AttributeUpdaterFlag } from "./../generated/AttributeUpdater"
export class ArkCounterPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkCounterPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Counter_construct(peerId, flags)
        const _peer  = new ArkCounterPeer(_peerPtr, peerId, 'Counter', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setCounterOptionsAttribute(): void {
        ArkUIGeneratedNativeModule._CounterInterface_setCounterOptions(this.peer.ptr)
    }
    setOnIncAttribute(value: VoidCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._CounterAttribute_setOnInc(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnDecAttribute(value: VoidCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._CounterAttribute_setOnDec(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableDecAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._CounterAttribute_setEnableDec(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableIncAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._CounterAttribute_setEnableInc(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface CounterAttribute extends CommonMethod {
    onInc(value: VoidCallback | undefined): this {
        throw new Error("Unimplemented method onInc")
    }
    onDec(value: VoidCallback | undefined): this {
        throw new Error("Unimplemented method onDec")
    }
    enableDec(value: boolean | undefined): this {
        throw new Error("Unimplemented method enableDec")
    }
    enableInc(value: boolean | undefined): this {
        throw new Error("Unimplemented method enableInc")
    }
    attributeModifier(value: AttributeModifier<CounterAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkCounterStyle extends ArkCommonMethodStyle implements CounterAttribute {
    onInc_value?: VoidCallback | undefined
    onDec_value?: VoidCallback | undefined
    enableDec_value?: boolean | undefined
    enableInc_value?: boolean | undefined
    attributeModifier_value?: AttributeModifier<CounterAttribute> | AttributeModifier<CommonMethod> | undefined
    public onInc(value: VoidCallback | undefined): this {
        return this
    }
    public onDec(value: VoidCallback | undefined): this {
        return this
    }
    public enableDec(value: boolean | undefined): this {
        return this
    }
    public enableInc(value: boolean | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<CounterAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkCounterComponent extends ArkCommonMethodComponent implements CounterAttribute {
    getPeer(): ArkCounterPeer {
        return (this.peer as ArkCounterPeer)
    }
    public setCounterOptions(): this {
        if (this.checkPriority("setCounterOptions")) {
            this.getPeer()?.setCounterOptionsAttribute()
            return this
        }
        return this
    }
    public onInc(value: VoidCallback | undefined): this {
        if (this.checkPriority("onInc")) {
            const value_casted = value as (VoidCallback | undefined)
            this.getPeer()?.setOnIncAttribute(value_casted)
            return this
        }
        return this
    }
    public onDec(value: VoidCallback | undefined): this {
        if (this.checkPriority("onDec")) {
            const value_casted = value as (VoidCallback | undefined)
            this.getPeer()?.setOnDecAttribute(value_casted)
            return this
        }
        return this
    }
    public enableDec(value: boolean | undefined): this {
        if (this.checkPriority("enableDec")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setEnableDecAttribute(value_casted)
            return this
        }
        return this
    }
    public enableInc(value: boolean | undefined): this {
        if (this.checkPriority("enableInc")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setEnableIncAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<CounterAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

@memo
export function Counter(
    @memo
    style: ((attributes: CounterAttribute) => void) | undefined,
    
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkCounterComponent>((): ArkCounterComponent => {
        return new ArkCounterComponent()
    })
    NodeAttach<ArkCounterPeer>((): ArkCounterPeer => ArkCounterPeer.create(receiver), (_: ArkCounterPeer): void => {
        receiver.setCounterOptions()
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class CounterModifier extends CommonMethodModifier implements CounterAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _onInc_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onInc_0_0value?: VoidCallback | undefined
    _onDec_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onDec_0_0value?: VoidCallback | undefined
    _enableDec_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableDec_0_0value?: boolean | undefined
    _enableInc_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableInc_0_0value?: boolean | undefined
    applyModifierPatch(peer: ArkCounterPeer): void {
        super.applyModifierPatch(peer)
        if (this._onInc_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onInc_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnIncAttribute((this._onInc_0_0value as VoidCallback | undefined));
                    this._onInc_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onInc_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onInc_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnIncAttribute((undefined as VoidCallback | undefined));
                }
            }
        }
        if (this._onDec_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onDec_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnDecAttribute((this._onDec_0_0value as VoidCallback | undefined));
                    this._onDec_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onDec_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onDec_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnDecAttribute((undefined as VoidCallback | undefined));
                }
            }
        }
        if (this._enableDec_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableDec_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEnableDecAttribute((this._enableDec_0_0value as boolean | undefined));
                    this._enableDec_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableDec_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableDec_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEnableDecAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._enableInc_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableInc_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEnableIncAttribute((this._enableInc_0_0value as boolean | undefined));
                    this._enableInc_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableInc_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableInc_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEnableIncAttribute((undefined as boolean | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: CounterModifier): void {
        super.mergeModifier(modifier)
        if (modifier._onInc_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onInc_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onInc(modifier._onInc_0_0value);
                    break;
                }
                default: {
                    this.onInc((undefined as VoidCallback | undefined));
                }
            }
        }
        if (modifier._onDec_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onDec_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onDec(modifier._onDec_0_0value);
                    break;
                }
                default: {
                    this.onDec((undefined as VoidCallback | undefined));
                }
            }
        }
        if (modifier._enableDec_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enableDec_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enableDec(modifier._enableDec_0_0value);
                    break;
                }
                default: {
                    this.enableDec((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._enableInc_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enableInc_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enableInc(modifier._enableInc_0_0value);
                    break;
                }
                default: {
                    this.enableInc((undefined as boolean | undefined));
                }
            }
        }
    }
    onInc(value: VoidCallback | undefined): this {
        if (((this._onInc_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onInc_0_flag = AttributeUpdaterFlag.UPDATE
            this._onInc_0_0value = value
        } else
        {
            this._onInc_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onDec(value: VoidCallback | undefined): this {
        if (((this._onDec_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onDec_0_flag = AttributeUpdaterFlag.UPDATE
            this._onDec_0_0value = value
        } else
        {
            this._onDec_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enableDec(value: boolean | undefined): this {
        if (((this._enableDec_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enableDec_0_0value) !== (value)))
        {
            this._enableDec_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableDec_0_0value = value
        } else
        {
            this._enableDec_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enableInc(value: boolean | undefined): this {
        if (((this._enableInc_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enableInc_0_0value) !== (value)))
        {
            this._enableInc_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableInc_0_0value = value
        } else
        {
            this._enableInc_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<CounterAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
