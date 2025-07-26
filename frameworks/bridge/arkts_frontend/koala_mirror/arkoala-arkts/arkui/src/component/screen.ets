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
export class ArkScreenPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkScreenPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Screen_construct(peerId, flags)
        const _peer  = new ArkScreenPeer(_peerPtr, peerId, "Screen", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setScreenOptionsAttribute(screenId: number): void {
        ArkUIGeneratedNativeModule._ScreenInterface_setScreenOptions(this.peer.ptr, screenId)
    }
}
export interface ScreenAttribute extends CommonMethod {
    attributeModifier(value: AttributeModifier<ScreenAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkScreenStyle extends ArkCommonMethodStyle implements ScreenAttribute {
    attributeModifier_value?: AttributeModifier<ScreenAttribute> | AttributeModifier<CommonMethod> | undefined
    public attributeModifier(value: AttributeModifier<ScreenAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: ScreenAttribute): void {
        super.apply(target)
    }
}

export class ArkScreenComponent extends ArkCommonMethodComponent implements ScreenAttribute {
    getPeer(): ArkScreenPeer {
        return (this.peer as ArkScreenPeer)
    }
    public setScreenOptions(screenId: number): this {
        if (this.checkPriority("setScreenOptions")) {
            const screenId_casted = screenId as (number)
            this.getPeer()?.setScreenOptionsAttribute(screenId_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<ScreenAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withScreenStyle(receiver: ScreenAttribute, modifier: AttributeModifier<ScreenAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkScreenStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("Screen")
// export function Screen(
//     screenId: number,
//     @memo
//     content_?: () => void,
// ): ScreenAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function Screen(
    @memo
    style: ((attributes: ScreenAttribute) => void) | undefined,
    screenId: number,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkScreenComponent>((): ArkScreenComponent => {
        return new ArkScreenComponent()
    })
    NodeAttach<ArkScreenPeer>((): ArkScreenPeer => ArkScreenPeer.create(receiver), (_: ArkScreenPeer): void => {
        receiver.setScreenOptions(screenId)
        style?.(receiver)
        withScreenStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkScreenSet extends ArkCommonMethodSet implements ScreenAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    applyModifierPatch(component: ScreenAttribute): void {
    }
    public attributeModifier(value: AttributeModifier<ScreenAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
