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

import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr } from "@koalaui/interop"
import { ArcScrollBarOptions_serializer } from "./framework/ohos.arkui.ArcScrollBar"
import { int32, int64, float32 } from "@koalaui/common"
import { ComponentBase } from "./ComponentBase"
import { PeerNode } from "./PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./component/common"
import { AttributeModifier, hookArcScrollBarAttributeModifier, AttributeUpdater } from "#handwritten"
import { CallbackKind } from "./framework/peers/CallbackKind"
import { CallbackTransformer } from "./CallbackTransformer"
import { ArcScrollBarModifier } from "./ArcScrollBarModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
export class ArkArcScrollBarPeer extends ArkCommonMethodPeer {
    attributeSet?: ArcScrollBarModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkArcScrollBarPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._ArcScrollBar_construct(peerId, flags)
        const _peer  = new ArkArcScrollBarPeer(_peerPtr, peerId, 'ArcScrollBar', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setArcScrollBarOptionsAttribute(options: ArcScrollBarOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        ArcScrollBarOptions_serializer.write(thisSerializer, options)
        ArkUIGeneratedNativeModule._ArcScrollBarInterface_setArcScrollBarOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class ArkArcScrollBarComponent extends ArkCommonMethodComponent implements ArcScrollBarAttribute {
    getPeer(): ArkArcScrollBarPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkArcScrollBarPeer)
    }
    public setArcScrollBarOptions(options: ArcScrollBarOptions): this {
        if (this.checkPriority("setArcScrollBarOptions")) {
            const options_casted = options as (ArcScrollBarOptions)
            this.getPeer()?.setArcScrollBarOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<ArcScrollBarAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        hookArcScrollBarAttributeModifier(this, value);
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

@memo
export function ArcScrollBarImpl(
    @memo
    style: ((attributes: ArcScrollBarAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkArcScrollBarComponent>((): ArkArcScrollBarComponent => {
        return new ArkArcScrollBarComponent()
    })
    NodeAttach<ArkArcScrollBarPeer>((): ArkArcScrollBarPeer => ArkArcScrollBarPeer.create(receiver), (peer: ArkArcScrollBarPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
    })
}
