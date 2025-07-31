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
export class ArkFlowItemPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkFlowItemPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._FlowItem_construct(peerId, flags)
        const _peer  = new ArkFlowItemPeer(_peerPtr, peerId, "FlowItem", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setFlowItemOptionsAttribute(): void {
        ArkUIGeneratedNativeModule._FlowItemInterface_setFlowItemOptions(this.peer.ptr)
    }
}
export interface FlowItemAttribute extends CommonMethod {
    attributeModifier(value: AttributeModifier<FlowItemAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkFlowItemStyle extends ArkCommonMethodStyle implements FlowItemAttribute {
    attributeModifier_value?: AttributeModifier<FlowItemAttribute> | AttributeModifier<CommonMethod> | undefined
    public attributeModifier(value: AttributeModifier<FlowItemAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: FlowItemAttribute): void {
        super.apply(target)
    }
}

export class ArkFlowItemComponent extends ArkCommonMethodComponent implements FlowItemAttribute {
    getPeer(): ArkFlowItemPeer {
        return (this.peer as ArkFlowItemPeer)
    }
    public setFlowItemOptions(): this {
        if (this.checkPriority("setFlowItemOptions")) {
            this.getPeer()?.setFlowItemOptionsAttribute()
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<FlowItemAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withFlowItemStyle(receiver: FlowItemAttribute, modifier: AttributeModifier<FlowItemAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkFlowItemStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("FlowItem")
// export function FlowItem(
//     
//     @memo
//     content_?: () => void,
// ): FlowItemAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function FlowItem(
    @memo
    style: ((attributes: FlowItemAttribute) => void) | undefined,
    
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkFlowItemComponent>((): ArkFlowItemComponent => {
        return new ArkFlowItemComponent()
    })
    NodeAttach<ArkFlowItemPeer>((): ArkFlowItemPeer => ArkFlowItemPeer.create(receiver), (_: ArkFlowItemPeer): void => {
        receiver.setFlowItemOptions()
        style?.(receiver)
        withFlowItemStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkFlowItemSet extends ArkCommonMethodSet implements FlowItemAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    applyModifierPatch(component: FlowItemAttribute): void {
    }
    public attributeModifier(value: AttributeModifier<FlowItemAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
