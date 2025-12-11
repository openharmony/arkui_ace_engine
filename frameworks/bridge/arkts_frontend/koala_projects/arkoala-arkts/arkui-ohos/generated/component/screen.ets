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
import { AttributeModifier, hookScreenAttributeModifier, AttributeUpdater } from "#handwritten"
import { ModifierStateManager } from '../CommonModifier';
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { ScreenModifier } from "./../ScreenModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkScreenPeer extends ArkCommonMethodPeer {
    attributeSet?: ScreenModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkScreenPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Screen_construct(peerId, flags)
        const _peer  = new ArkScreenPeer(_peerPtr, peerId, 'Screen', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setScreenOptionsAttribute(screenId: number): void {
        ArkUIGeneratedNativeModule._ScreenInterface_setScreenOptions(this.peer.ptr, screenId)
    }
}
export interface ScreenAttribute extends CommonMethod {
    setScreenOptions(screenId: number): this {
        throw new Error("Unimplemented method setScreenOptions")
    }
    attributeModifier(value: AttributeModifier<ScreenAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkScreenStyle extends ArkCommonMethodStyle implements ScreenAttribute {
    attributeModifier_value?: AttributeModifier<ScreenAttribute> | AttributeModifier<CommonMethod> | undefined
    setScreenOptions(screenId: number): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<ScreenAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkScreenComponent extends ArkCommonMethodComponent implements ScreenAttribute {
    getPeer(): ArkScreenPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkScreenPeer)
    }
    public setScreenOptions(screenId: number): this {
        if (this.checkPriority("setScreenOptions")) {
            const screenId_casted = screenId as (number)
            this.getPeer()?.setScreenOptionsAttribute(screenId_casted)
            this.applyOptionsFinish('ScreenAttribute');
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<ScreenAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
          hookScreenAttributeModifier(this, value);
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
export function ScreenImpl(
    @memo
    style: ((attributes: ScreenAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkScreenComponent>((): ArkScreenComponent => {
        return new ArkScreenComponent()
    })
    NodeAttach<ArkScreenPeer>((): ArkScreenPeer => ArkScreenPeer.create(receiver), (peer: ArkScreenPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
    })
}

