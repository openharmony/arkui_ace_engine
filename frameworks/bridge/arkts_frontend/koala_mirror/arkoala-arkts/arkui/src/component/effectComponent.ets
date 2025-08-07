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
import { nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer } from "@koalaui/interop"
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
export class ArkEffectComponentPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkEffectComponentPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._EffectComponent_construct(peerId, flags)
        const _peer  = new ArkEffectComponentPeer(_peerPtr, peerId, 'EffectComponent', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setEffectComponentOptionsAttribute(): void {
        ArkUIGeneratedNativeModule._EffectComponentInterface_setEffectComponentOptions(this.peer.ptr)
    }
}
export interface EffectComponentAttribute extends CommonMethod {
    attributeModifier(value: AttributeModifier<EffectComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkEffectComponentStyle extends ArkCommonMethodStyle implements EffectComponentAttribute {
    attributeModifier_value?: AttributeModifier<EffectComponentAttribute> | AttributeModifier<CommonMethod> | undefined
    public attributeModifier(value: AttributeModifier<EffectComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkEffectComponentComponent extends ArkCommonMethodComponent implements EffectComponentAttribute {
    getPeer(): ArkEffectComponentPeer {
        return (this.peer as ArkEffectComponentPeer)
    }
    public setEffectComponentOptions(): this {
        if (this.checkPriority("setEffectComponentOptions")) {
            this.getPeer()?.setEffectComponentOptionsAttribute()
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<EffectComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

@memo
export function EffectComponent(
    @memo
    style: ((attributes: EffectComponentAttribute) => void) | undefined,
    
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkEffectComponentComponent>((): ArkEffectComponentComponent => {
        return new ArkEffectComponentComponent()
    })
    NodeAttach<ArkEffectComponentPeer>((): ArkEffectComponentPeer => ArkEffectComponentPeer.create(receiver), (_: ArkEffectComponentPeer): void => {
        receiver.setEffectComponentOptions()
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class EffectComponentModifier extends CommonMethodModifier implements EffectComponentAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    applyModifierPatch(peer: ArkEffectComponentPeer): void {
        super.applyModifierPatch(peer)
    }
    mergeModifier(modifier: EffectComponentModifier): void {
        super.mergeModifier(modifier)
    }
    public attributeModifier(value: AttributeModifier<EffectComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
