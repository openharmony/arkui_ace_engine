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
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { hookStepperItemAttributeModifier, AttributeModifier, AttributeUpdater } from "#handwritten"
import { ModifierStateManager } from '../CommonModifier';
import { StepperItemModifier } from "./../StepperItemModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkStepperItemPeer extends ArkCommonMethodPeer {
    attributeSet?: StepperItemModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
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
            thisSerializer.writeInt32(valueTmpValue.valueOf())
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
    setStepperItemOptions(): this {
        throw new Error("Unimplemented method setStepperItemOptions")
    }
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
    setStepperItemOptions(): this {
        return this
    }
    prevLabel(value: string | undefined): this {
        return this
    }
    nextLabel(value: string | undefined): this {
        return this
    }
    status(value: ItemState | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<StepperItemAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkStepperItemComponent extends ArkCommonMethodComponent implements StepperItemAttribute {
    getPeer(): ArkStepperItemPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkStepperItemPeer)
    }
    public setStepperItemOptions(): this {
        if (this.checkPriority("setStepperItemOptions")) {
            this.getPeer()?.setStepperItemOptionsAttribute()
            this.applyOptionsFinish('StepperItemAttribute');
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
        ModifierStateManager.INSTANCE.scope(() => {
          hookStepperItemAttributeModifier(this, value);
        })
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
    public applyOptionsFinish(traceName: string): void {
        super.applyOptionsFinish(traceName)
    }
}

@memo
export function StepperItemImpl(
    @memo
    style: ((attributes: StepperItemAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkStepperItemComponent>((): ArkStepperItemComponent => {
        return new ArkStepperItemComponent()
    })
    NodeAttach<ArkStepperItemPeer>((): ArkStepperItemPeer => ArkStepperItemPeer.create(receiver), (peer: ArkStepperItemPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
    })
}

