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
import { AttributeModifier, hookRowSplitAttributeModifier, AttributeUpdater } from "#handwritten"
import { ModifierStateManager } from '../CommonModifier';
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { RowSplitModifier } from "./../RowSplitModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkRowSplitPeer extends ArkCommonMethodPeer {
    attributeSet?: RowSplitModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkRowSplitPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._RowSplit_construct(peerId, flags)
        const _peer  = new ArkRowSplitPeer(_peerPtr, peerId, 'RowSplit', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setRowSplitOptionsAttribute(): void {
        ArkUIGeneratedNativeModule._RowSplitInterface_setRowSplitOptions(this.peer.ptr)
    }
    setResizeableAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RowSplitAttribute_setResizeable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface RowSplitAttribute extends CommonMethod {
    setRowSplitOptions(): this {
        throw new Error("Unimplemented method setRowSplitOptions")
    }
    resizeable(value: boolean | undefined): this {
        throw new Error("Unimplemented method resizeable")
    }
    attributeModifier(value: AttributeModifier<RowSplitAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkRowSplitStyle extends ArkCommonMethodStyle implements RowSplitAttribute {
    resizeable_value?: boolean | undefined
    attributeModifier_value?: AttributeModifier<RowSplitAttribute> | AttributeModifier<CommonMethod> | undefined
    setRowSplitOptions(): this {
        return this
    }
    resizeable(value: boolean | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<RowSplitAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkRowSplitComponent extends ArkCommonMethodComponent implements RowSplitAttribute {
    getPeer(): ArkRowSplitPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkRowSplitPeer)
    }
    public setRowSplitOptions(): this {
        if (this.checkPriority("setRowSplitOptions")) {
            this.getPeer()?.setRowSplitOptionsAttribute()
            this.applyOptionsFinish('RowSplitAttribute');
            return this
        }
        return this
    }
    public resizeable(value: boolean | undefined): this {
        if (this.checkPriority("resizeable")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setResizeableAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<RowSplitAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
          hookRowSplitAttributeModifier(this, value);
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
export function RowSplitImpl(
    @memo
    style: ((attributes: RowSplitAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkRowSplitComponent>((): ArkRowSplitComponent => {
        return new ArkRowSplitComponent()
    })
    NodeAttach<ArkRowSplitPeer>((): ArkRowSplitPeer => ArkRowSplitPeer.create(receiver), (peer: ArkRowSplitPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
    })
}

