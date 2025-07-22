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

import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, wrapCallback, NativeBuffer } from "@koalaui/interop"
import { int32, int64, float32 } from "@koalaui/common"
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
export class ArkRowSplitPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkRowSplitPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._RowSplit_construct(peerId, flags)
        const _peer  = new ArkRowSplitPeer(_peerPtr, peerId, "RowSplit", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setRowSplitOptionsAttribute(): void {
        ArkUIGeneratedNativeModule._RowSplitInterface_setRowSplitOptions(this.peer.ptr)
    }
    setResizeableAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
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
    public apply(target: RowSplitAttribute): void {
        super.apply(target)
        if (this.resizeable_value !== undefined)
            target.resizeable(this.resizeable_value!)
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
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withRowSplitStyle(receiver: RowSplitAttribute, modifier: AttributeModifier<RowSplitAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkRowSplitStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("RowSplit")
// export function RowSplit(
//     
//     @memo
//     content_?: () => void,
// ): RowSplitAttribute {
//     throw new Error("Not implemented")
// }

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
        withRowSplitStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkRowSplitSet extends ArkCommonMethodSet implements RowSplitAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _resizeable_flag?: boolean
    _resizeable0_value?: boolean | undefined
    applyModifierPatch(component: RowSplitAttribute): void {
        if (this._resizeable_flag)
            component.resizeable((this._resizeable0_value as boolean | undefined))
    }
    public resizeable(value: boolean | undefined): this {
        this._resizeable_flag = true
        this._resizeable0_value = value
        return this
    }
    public attributeModifier(value: AttributeModifier<RowSplitAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
