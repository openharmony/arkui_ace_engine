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
import { Serializer } from "./peers/Serializer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"
import { Dimension } from "./units"

export class ArkColumnSplitPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkColumnSplitPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._ColumnSplit_construct(peerId, flags)
        const _peer  = new ArkColumnSplitPeer(_peerPtr, peerId, "ColumnSplit", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setColumnSplitOptionsAttribute(): void {
        ArkUIGeneratedNativeModule._ColumnSplitInterface_setColumnSplitOptions(this.peer.ptr)
    }
    resizeableAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._ColumnSplitAttribute_resizeable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    dividerAttribute(value: ColumnSplitDividerStyle | null | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeColumnSplitDividerStyle(value_value)
        }
        ArkUIGeneratedNativeModule._ColumnSplitAttribute_divider(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export type ColumnSplitInterface = () => ColumnSplitAttribute;
export interface ColumnSplitDividerStyle {
    startMargin?: Dimension;
    endMargin?: Dimension;
}
export interface ColumnSplitAttribute extends CommonMethod {
    resizeable(value: boolean | undefined): this
    divider(value: ColumnSplitDividerStyle | null | undefined): this
}
export class ArkColumnSplitStyle extends ArkCommonMethodStyle implements ColumnSplitAttribute {
    resizeable_value?: boolean | undefined
    divider_value?: ColumnSplitDividerStyle | null | undefined
    public resizeable(value: boolean | undefined): this {
        return this
    }
    public divider(value: ColumnSplitDividerStyle | null | undefined): this {
        return this
        }
}
export class ArkColumnSplitComponent extends ArkCommonMethodComponent implements ColumnSplitAttribute {
    getPeer(): ArkColumnSplitPeer {
        return (this.peer as ArkColumnSplitPeer)
    }
    public setColumnSplitOptions(): this {
        if (this.checkPriority("setColumnSplitOptions")) {
            this.getPeer()?.setColumnSplitOptionsAttribute()
            return this
        }
        return this
    }
    public resizeable(value: boolean | undefined): this {
        if (this.checkPriority("resizeable")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.resizeableAttribute(value_casted)
            return this
        }
        return this
    }
    public divider(value: ColumnSplitDividerStyle | null | undefined): this {
        if (this.checkPriority("divider")) {
            const value_casted = value as (ColumnSplitDividerStyle | null | undefined)
            this.getPeer()?.dividerAttribute(value_casted)
            return this
        }
        return this
    }
    
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function ColumnSplit(
    /** @memo */
    style: ((attributes: ColumnSplitAttribute) => void) | undefined,
    
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkColumnSplitComponent()
    })
    NodeAttach<ArkColumnSplitPeer>((): ArkColumnSplitPeer => ArkColumnSplitPeer.create(receiver), (_: ArkColumnSplitPeer) => {
        receiver.setColumnSplitOptions()
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
