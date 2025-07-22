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
import { int32, int64, float32 } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonMethodSet } from "./common"
import { VoidCallback } from "./units"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkCounterPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkCounterPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Counter_construct(peerId, flags)
        const _peer  = new ArkCounterPeer(_peerPtr, peerId, "Counter", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setCounterOptionsAttribute(): void {
        ArkUIGeneratedNativeModule._CounterInterface_setCounterOptions(this.peer.ptr)
    }
    setOnIncAttribute(value: VoidCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._CounterAttribute_setOnInc(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnDecAttribute(value: VoidCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._CounterAttribute_setOnDec(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableDecAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._CounterAttribute_setEnableDec(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableIncAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
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
    public apply(target: CounterAttribute): void {
        super.apply(target)
        if (this.onInc_value !== undefined)
            target.onInc(this.onInc_value!)
        if (this.onDec_value !== undefined)
            target.onDec(this.onDec_value!)
        if (this.enableDec_value !== undefined)
            target.enableDec(this.enableDec_value!)
        if (this.enableInc_value !== undefined)
            target.enableInc(this.enableInc_value!)
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
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withCounterStyle(receiver: CounterAttribute, modifier: AttributeModifier<CounterAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkCounterStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("Counter")
// export function Counter(
//     
//     @memo
//     content_?: () => void,
// ): CounterAttribute {
//     throw new Error("Not implemented")
// }

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
        withCounterStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkCounterSet extends ArkCommonMethodSet implements CounterAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _onInc_flag?: boolean
    _onInc0_value?: VoidCallback | undefined
    _onDec_flag?: boolean
    _onDec0_value?: VoidCallback | undefined
    _enableDec_flag?: boolean
    _enableDec0_value?: boolean | undefined
    _enableInc_flag?: boolean
    _enableInc0_value?: boolean | undefined
    applyModifierPatch(component: CounterAttribute): void {
        if (this._onInc_flag)
            component.onInc((this._onInc0_value as VoidCallback | undefined))
        if (this._onDec_flag)
            component.onDec((this._onDec0_value as VoidCallback | undefined))
        if (this._enableDec_flag)
            component.enableDec((this._enableDec0_value as boolean | undefined))
        if (this._enableInc_flag)
            component.enableInc((this._enableInc0_value as boolean | undefined))
    }
    public onInc(value: VoidCallback | undefined): this {
        this._onInc_flag = true
        this._onInc0_value = value
        return this
    }
    public onDec(value: VoidCallback | undefined): this {
        this._onDec_flag = true
        this._onDec0_value = value
        return this
    }
    public enableDec(value: boolean | undefined): this {
        this._enableDec_flag = true
        this._enableDec0_value = value
        return this
    }
    public enableInc(value: boolean | undefined): this {
        this._enableInc_flag = true
        this._enableInc0_value = value
        return this
    }
    public attributeModifier(value: AttributeModifier<CounterAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
