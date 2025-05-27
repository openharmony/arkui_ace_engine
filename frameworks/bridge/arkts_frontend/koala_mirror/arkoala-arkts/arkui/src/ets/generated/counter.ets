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
import { VoidCallback } from "./units"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { BuilderLambda } from "@koalaui/builderLambda"
import { UICommonBase, AttributeModifier } from "./../handwritten"
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
    onIncAttribute(value: VoidCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CounterAttribute_onInc(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onDecAttribute(value: VoidCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CounterAttribute_onDec(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enableDecAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._CounterAttribute_enableDec(this.peer.ptr, value ? 1 : 0)
    }
    enableIncAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._CounterAttribute_enableInc(this.peer.ptr, value ? 1 : 0)
    }
}

export interface CounterAttribute extends CommonMethod {
    onInc(value: VoidCallback): this
    onDec(value: VoidCallback): this
    enableDec(value: boolean): this
    enableInc(value: boolean): this
    attributeModifier(value: AttributeModifier<CounterAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export interface UICounterAttribute extends UICommonMethod {
    @memo
    onInc(value: VoidCallback): this
    @memo
    onDec(value: VoidCallback): this
    @memo
    enableDec(value: boolean): this
    @memo
    enableInc(value: boolean): this
    @memo
    attributeModifier(value: AttributeModifier<CounterAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkCounterStyle extends ArkCommonMethodStyle implements CounterAttribute {
    onInc_value?: VoidCallback
    onDec_value?: VoidCallback
    enableDec_value?: boolean
    enableInc_value?: boolean
    public onInc(value: VoidCallback): this {
        return this
    }
    public onDec(value: VoidCallback): this {
        return this
    }
    public enableDec(value: boolean): this {
        return this
    }
    public enableInc(value: boolean): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<CounterAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
@memo_stable
export class ArkCounterComponent extends ArkCommonMethodComponent implements UICounterAttribute {
    getPeer(): ArkCounterPeer {
        return (this.peer as ArkCounterPeer)
    }
    @memo
    public setCounterOptions(): this {
        if (this.checkPriority("setCounterOptions")) {
            this.getPeer()?.setCounterOptionsAttribute()
            return this
        }
        return this
    }
    @memo
    public onInc(value: VoidCallback): this {
        if (this.checkPriority("onInc")) {
            const value_casted = value as (VoidCallback)
            this.getPeer()?.onIncAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onDec(value: VoidCallback): this {
        if (this.checkPriority("onDec")) {
            const value_casted = value as (VoidCallback)
            this.getPeer()?.onDecAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public enableDec(value: boolean): this {
        if (this.checkPriority("enableDec")) {
            const value_casted = value as (boolean)
            this.getPeer()?.enableDecAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public enableInc(value: boolean): this {
        if (this.checkPriority("enableInc")) {
            const value_casted = value as (boolean)
            this.getPeer()?.enableIncAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public attributeModifier(value: AttributeModifier<CounterAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
@memo
@BuilderLambda("Counter")
export function Counter(
    
    @memo
    content_?: () => void,
): CounterAttribute {
    throw new Error("Not implemented")
}

@memo
export function Counter(
    @memo
    style: ((attributes: UICounterAttribute) => void) | undefined,
    
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
