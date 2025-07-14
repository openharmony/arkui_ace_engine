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
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"

export class ArkStepperItemPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkStepperItemPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._StepperItem_construct(peerId, flags)
        const _peer  = new ArkStepperItemPeer(_peerPtr, peerId, "StepperItem", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setStepperItemOptionsAttribute(): void {
        ArkUIGeneratedNativeModule._StepperItemInterface_setStepperItemOptions(this.peer.ptr)
    }
    prevLabelAttribute(value: string | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeString(value_value)
        }
        ArkUIGeneratedNativeModule._StepperItemAttribute_prevLabel(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    nextLabelAttribute(value: string | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeString(value_value)
        }
        ArkUIGeneratedNativeModule._StepperItemAttribute_nextLabel(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    statusAttribute(value: ItemState | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as ItemState)
            thisSerializer.writeInt32(TypeChecker.ItemState_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._StepperItemAttribute_status(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export enum ItemState {
    NORMAL = 0,
    Normal = 0,
    DISABLED = 1,
    Disabled = 1,
    WAITING = 2,
    Waiting = 2,
    SKIP = 3,
    Skip = 3
}
export type StepperItemInterface = () => StepperItemAttribute;
export interface StepperItemAttribute extends CommonMethod {
    prevLabel(value: string | undefined): this
    nextLabel(value: string | undefined): this
    status(value: ItemState | undefined): this
}
export class ArkStepperItemStyle extends ArkCommonMethodStyle implements StepperItemAttribute {
    prevLabel_value?: string | undefined
    nextLabel_value?: string | undefined
    status_value?: ItemState
    public prevLabel(value: string | undefined): this {
        return this
    }
    public nextLabel(value: string | undefined): this {
        return this
    }
    public status(value: ItemState | undefined): this {
        return this
        }
}
export class ArkStepperItemComponent extends ArkCommonMethodComponent implements StepperItemAttribute {
    getPeer(): ArkStepperItemPeer {
        return (this.peer as ArkStepperItemPeer)
    }
    public setStepperItemOptions(): this {
        if (this.checkPriority("setStepperItemOptions")) {
            this.getPeer()?.setStepperItemOptionsAttribute()
            return this
        }
        return this
    }
    public prevLabel(value: string | undefined): this {
        if (this.checkPriority("prevLabel")) {
            const value_casted = value as (string | undefined)
            this.getPeer()?.prevLabelAttribute(value_casted)
            return this
        }
        return this
    }
    public nextLabel(value: string | undefined): this {
        if (this.checkPriority("nextLabel")) {
            const value_casted = value as (string | undefined)
            this.getPeer()?.nextLabelAttribute(value_casted)
            return this
        }
        return this
    }
    public status(value: ItemState | undefined): this {
        if (this.checkPriority("status")) {
            const value_casted = value as (ItemState | undefined)
            this.getPeer()?.statusAttribute(value_casted)
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
export function StepperItem(
    /** @memo */
    style: ((attributes: StepperItemAttribute) => void) | undefined,
    
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkStepperItemComponent()
    })
    NodeAttach<ArkStepperItemPeer>((): ArkStepperItemPeer => ArkStepperItemPeer.create(receiver), (_: ArkStepperItemPeer) => {
        receiver.setStepperItemOptions()
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
