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
export class ArkStepperItemPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkStepperItemPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._StepperItem_construct(peerId, flags)
        const _peer  = new ArkStepperItemPeer(_peerPtr, peerId, 'StepperItem', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setStepperItemOptionsAttribute(): void {
        ArkUIGeneratedNativeModule._StepperItemInterface_setStepperItemOptions(this.peer.ptr)
    }
    setPrevLabelAttribute(value: string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeString(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._StepperItemAttribute_setPrevLabel(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setNextLabelAttribute(value: string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeString(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._StepperItemAttribute_setNextLabel(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setStatusAttribute(value: ItemState | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as ItemState)
            thisSerializer.writeInt32(TypeChecker.ItemState_ToNumeric(valueTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
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
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

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
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class StepperItemModifier extends CommonMethodModifier implements StepperItemAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _prevLabel_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _prevLabel_0_0value?: string | undefined
    _nextLabel_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _nextLabel_0_0value?: string | undefined
    _status_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _status_0_0value?: ItemState | undefined
    applyModifierPatch(peer: ArkStepperItemPeer): void {
        super.applyModifierPatch(peer)
        if (this._prevLabel_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._prevLabel_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setPrevLabelAttribute((this._prevLabel_0_0value as string | undefined));
                    this._prevLabel_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._prevLabel_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._prevLabel_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setPrevLabelAttribute((undefined as string | undefined));
                }
            }
        }
        if (this._nextLabel_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._nextLabel_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setNextLabelAttribute((this._nextLabel_0_0value as string | undefined));
                    this._nextLabel_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._nextLabel_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._nextLabel_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setNextLabelAttribute((undefined as string | undefined));
                }
            }
        }
        if (this._status_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._status_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setStatusAttribute((this._status_0_0value as ItemState | undefined));
                    this._status_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._status_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._status_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setStatusAttribute((undefined as ItemState | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: StepperItemModifier): void {
        super.mergeModifier(modifier)
        if (modifier._prevLabel_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._prevLabel_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.prevLabel(modifier._prevLabel_0_0value);
                    break;
                }
                default: {
                    this.prevLabel((undefined as string | undefined));
                }
            }
        }
        if (modifier._nextLabel_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._nextLabel_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.nextLabel(modifier._nextLabel_0_0value);
                    break;
                }
                default: {
                    this.nextLabel((undefined as string | undefined));
                }
            }
        }
        if (modifier._status_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._status_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.status(modifier._status_0_0value);
                    break;
                }
                default: {
                    this.status((undefined as ItemState | undefined));
                }
            }
        }
    }
    prevLabel(value: string | undefined): this {
        if (((this._prevLabel_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._prevLabel_0_0value) !== (value)))
        {
            this._prevLabel_0_flag = AttributeUpdaterFlag.UPDATE
            this._prevLabel_0_0value = value
        } else
        {
            this._prevLabel_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    nextLabel(value: string | undefined): this {
        if (((this._nextLabel_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._nextLabel_0_0value) !== (value)))
        {
            this._nextLabel_0_flag = AttributeUpdaterFlag.UPDATE
            this._nextLabel_0_0value = value
        } else
        {
            this._nextLabel_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    status(value: ItemState | undefined): this {
        if (((this._status_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._status_0_flag = AttributeUpdaterFlag.UPDATE
            this._status_0_0value = value
        } else
        {
            this._status_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<StepperItemAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
