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
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { VoidCallback } from "./units"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"

export class ArkCounterPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkCounterPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Counter_construct(peerId, flags)
        const _peer  = new ArkCounterPeer(_peerPtr, peerId, "Counter", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setCounterOptionsAttribute(): void {
        ArkUIGeneratedNativeModule._CounterInterface_setCounterOptions(this.peer.ptr)
    }
    onIncAttribute(value: VoidCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._CounterAttribute_onInc(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onDecAttribute(value: VoidCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._CounterAttribute_onDec(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enableDecAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._CounterAttribute_enableDec(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enableIncAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._CounterAttribute_enableInc(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export type CounterInterface = () => CounterAttribute;
export interface CounterAttribute extends CommonMethod {
    onInc(value: VoidCallback | undefined): this
    onDec(value: VoidCallback | undefined): this
    enableDec(value: boolean | undefined): this
    enableInc(value: boolean | undefined): this
}
export class ArkCounterStyle extends ArkCommonMethodStyle implements CounterAttribute {
    onInc_value?: VoidCallback | undefined
    onDec_value?: VoidCallback | undefined
    enableDec_value?: boolean | undefined
    enableInc_value?: boolean | undefined
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
            this.getPeer()?.onIncAttribute(value_casted)
            return this
        }
        return this
    }
    public onDec(value: VoidCallback | undefined): this {
        if (this.checkPriority("onDec")) {
            const value_casted = value as (VoidCallback | undefined)
            this.getPeer()?.onDecAttribute(value_casted)
            return this
        }
        return this
    }
    public enableDec(value: boolean | undefined): this {
        if (this.checkPriority("enableDec")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.enableDecAttribute(value_casted)
            return this
        }
        return this
    }
    public enableInc(value: boolean | undefined): this {
        if (this.checkPriority("enableInc")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.enableIncAttribute(value_casted)
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
export function Counter(
    /** @memo */
    style: ((attributes: CounterAttribute) => void) | undefined,
    
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkCounterComponent()
    })
    NodeAttach<ArkCounterPeer>((): ArkCounterPeer => ArkCounterPeer.create(receiver), (_: ArkCounterPeer) => {
        receiver.setCounterOptions()
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
