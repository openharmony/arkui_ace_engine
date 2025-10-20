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
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { AttributeModifier, hookEffectComponentAttributeModifier, AttributeUpdater } from "#handwritten"
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { EffectComponentModifier } from "./../EffectComponentModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkEffectComponentPeer extends ArkCommonMethodPeer {
    attributeSet?: EffectComponentModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
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
    setEffectComponentOptions(): this {
        throw new Error("Unimplemented method setEffectComponentOptions")
    }
    attributeModifier(value: AttributeModifier<EffectComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkEffectComponentStyle extends ArkCommonMethodStyle implements EffectComponentAttribute {
    attributeModifier_value?: AttributeModifier<EffectComponentAttribute> | AttributeModifier<CommonMethod> | undefined
    setEffectComponentOptions(): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<EffectComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkEffectComponentComponent extends ArkCommonMethodComponent implements EffectComponentAttribute {
    getPeer(): ArkEffectComponentPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkEffectComponentPeer)
    }
    public setEffectComponentOptions(): this {
        if (this.checkPriority("setEffectComponentOptions")) {
            this.getPeer()?.setEffectComponentOptionsAttribute()
            this.applyOptionsFinish('EffectComponentAttribute');
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<EffectComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        hookEffectComponentAttributeModifier(this, value);
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
export function EffectComponentImpl(
    @memo
    style: ((attributes: EffectComponentAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkEffectComponentComponent>((): ArkEffectComponentComponent => {
        return new ArkEffectComponentComponent()
    })
    NodeAttach<ArkEffectComponentPeer>((): ArkEffectComponentPeer => ArkEffectComponentPeer.create(receiver), (peer: ArkEffectComponentPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
    })
}

