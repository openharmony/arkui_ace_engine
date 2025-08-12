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
export class ArkRowSplitPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
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
    public resizeable(value: boolean | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<RowSplitAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkRowSplitComponent extends ArkCommonMethodComponent implements RowSplitAttribute {
    getPeer(): ArkRowSplitPeer {
        return (this.peer as ArkRowSplitPeer)
    }
    public setRowSplitOptions(): this {
        if (this.checkPriority("setRowSplitOptions")) {
            this.getPeer()?.setRowSplitOptionsAttribute()
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
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

@memo
export function RowSplit(
    @memo
    style: ((attributes: RowSplitAttribute) => void) | undefined,
    
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkRowSplitComponent>((): ArkRowSplitComponent => {
        return new ArkRowSplitComponent()
    })
    NodeAttach<ArkRowSplitPeer>((): ArkRowSplitPeer => ArkRowSplitPeer.create(receiver), (_: ArkRowSplitPeer): void => {
        receiver.setRowSplitOptions()
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class RowSplitModifier extends CommonMethodModifier implements RowSplitAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _resizeable_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _resizeable_0_0value?: boolean | undefined
    applyModifierPatch(peer: ArkRowSplitPeer): void {
        super.applyModifierPatch(peer)
        if (this._resizeable_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._resizeable_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setResizeableAttribute((this._resizeable_0_0value as boolean | undefined));
                    this._resizeable_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._resizeable_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._resizeable_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setResizeableAttribute((undefined as boolean | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: RowSplitModifier): void {
        super.mergeModifier(modifier)
        if (modifier._resizeable_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._resizeable_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.resizeable(modifier._resizeable_0_0value);
                    break;
                }
                default: {
                    this.resizeable((undefined as boolean | undefined));
                }
            }
        }
    }
    resizeable(value: boolean | undefined): this {
        if (((this._resizeable_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._resizeable_0_0value) !== (value)))
        {
            this._resizeable_0_flag = AttributeUpdaterFlag.UPDATE
            this._resizeable_0_0value = value
        } else
        {
            this._resizeable_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<RowSplitAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
