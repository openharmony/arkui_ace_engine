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
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkStepperItemPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkStepperItemPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._StepperItem_construct(peerId, flags)
        const _peer  = new ArkStepperItemPeer(_peerPtr, peerId, "StepperItem", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setStepperItemOptionsAttribute(): void {
        ArkUIGeneratedNativeModule._StepperItemInterface_setStepperItemOptions(this.peer.ptr)
    }
    setPrevLabelAttribute(value: string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeString(value_value)
        }
        ArkUIGeneratedNativeModule._StepperItemAttribute_setPrevLabel(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setNextLabelAttribute(value: string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeString(value_value)
        }
        ArkUIGeneratedNativeModule._StepperItemAttribute_setNextLabel(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setStatusAttribute(value: ItemState | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as ItemState)
            thisSerializer.writeInt32(TypeChecker.ItemState_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._StepperItemAttribute_setStatus(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
export interface StepperItemAttribute extends CommonMethod {
    prevLabel(value: string | undefined): this {
        throw new Error("Unimplemented method prevLabel")
    }
    nextLabel(value: string | undefined): this {
        throw new Error("Unimplemented method nextLabel")
    }
    status(value: ItemState | undefined): this {
        throw new Error("Unimplemented method status")
    }
    attributeModifier(value: AttributeModifier<StepperItemAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkStepperItemStyle extends ArkCommonMethodStyle implements StepperItemAttribute {
    prevLabel_value?: string | undefined
    nextLabel_value?: string | undefined
    status_value?: ItemState | undefined
    attributeModifier_value?: AttributeModifier<StepperItemAttribute> | AttributeModifier<CommonMethod> | undefined
    public prevLabel(value: string | undefined): this {
        return this
    }
    public nextLabel(value: string | undefined): this {
        return this
    }
    public status(value: ItemState | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<StepperItemAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: StepperItemAttribute): void {
        super.apply(target)
        if (this.prevLabel_value !== undefined)
            target.prevLabel(this.prevLabel_value!)
        if (this.nextLabel_value !== undefined)
            target.nextLabel(this.nextLabel_value!)
        if (this.status_value !== undefined)
            target.status(this.status_value!)
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
            this.getPeer()?.setPrevLabelAttribute(value_casted)
            return this
        }
        return this
    }
    public nextLabel(value: string | undefined): this {
        if (this.checkPriority("nextLabel")) {
            const value_casted = value as (string | undefined)
            this.getPeer()?.setNextLabelAttribute(value_casted)
            return this
        }
        return this
    }
    public status(value: ItemState | undefined): this {
        if (this.checkPriority("status")) {
            const value_casted = value as (ItemState | undefined)
            this.getPeer()?.setStatusAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<StepperItemAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withStepperItemStyle(receiver: StepperItemAttribute, modifier: AttributeModifier<StepperItemAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkStepperItemStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("StepperItem")
// export function StepperItem(
//     
//     @memo
//     content_?: () => void,
// ): StepperItemAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function StepperItem(
    @memo
    style: ((attributes: StepperItemAttribute) => void) | undefined,
    
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkStepperItemComponent>((): ArkStepperItemComponent => {
        return new ArkStepperItemComponent()
    })
    NodeAttach<ArkStepperItemPeer>((): ArkStepperItemPeer => ArkStepperItemPeer.create(receiver), (_: ArkStepperItemPeer): void => {
        receiver.setStepperItemOptions()
        style?.(receiver)
        withStepperItemStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkStepperItemSet extends ArkCommonMethodSet implements StepperItemAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _prevLabel_flag?: boolean
    _prevLabel0_value?: string | undefined
    _nextLabel_flag?: boolean
    _nextLabel0_value?: string | undefined
    _status_flag?: boolean
    _status0_value?: ItemState | undefined
    applyModifierPatch(component: StepperItemAttribute): void {
        if (this._prevLabel_flag)
            component.prevLabel((this._prevLabel0_value as string | undefined))
        if (this._nextLabel_flag)
            component.nextLabel((this._nextLabel0_value as string | undefined))
        if (this._status_flag)
            component.status((this._status0_value as ItemState | undefined))
    }
    public prevLabel(value: string | undefined): this {
        this._prevLabel_flag = true
        this._prevLabel0_value = value
        return this
    }
    public nextLabel(value: string | undefined): this {
        this._nextLabel_flag = true
        this._nextLabel0_value = value
        return this
    }
    public status(value: ItemState | undefined): this {
        this._status_flag = true
        this._status0_value = value
        return this
    }
    public attributeModifier(value: AttributeModifier<StepperItemAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
