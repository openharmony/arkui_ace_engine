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
import { Scroller } from "./scroll"
import { BarState } from "./enums"

export class ArkScrollBarPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkScrollBarPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._ScrollBar_construct(peerId, flags)
        const _peer  = new ArkScrollBarPeer(_peerPtr, peerId, "ScrollBar", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setScrollBarOptionsAttribute(value: ScrollBarOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeScrollBarOptions(value)
        ArkUIGeneratedNativeModule._ScrollBarInterface_setScrollBarOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enableNestedScrollAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._ScrollBarAttribute_enableNestedScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export enum ScrollBarDirection {
    VERTICAL = 0,
    Vertical = 0,
    HORIZONTAL = 1,
    Horizontal = 1
}
export interface ScrollBarOptions {
    scroller: Scroller;
    direction?: ScrollBarDirection;
    state?: BarState;
}
export type ScrollBarInterface = (value: ScrollBarOptions) => ScrollBarAttribute;
export interface ScrollBarAttribute extends CommonMethod {
    enableNestedScroll(value: boolean | undefined): this
}
export class ArkScrollBarStyle extends ArkCommonMethodStyle implements ScrollBarAttribute {
    enableNestedScroll_value?: boolean | undefined
    public enableNestedScroll(value: boolean | undefined): this {
        return this
        }
}
export class ArkScrollBarComponent extends ArkCommonMethodComponent implements ScrollBarAttribute {
    getPeer(): ArkScrollBarPeer {
        return (this.peer as ArkScrollBarPeer)
    }
    public setScrollBarOptions(value: ScrollBarOptions): this {
        if (this.checkPriority("setScrollBarOptions")) {
            const value_casted = value as (ScrollBarOptions)
            this.getPeer()?.setScrollBarOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    public enableNestedScroll(value: boolean | undefined): this {
        if (this.checkPriority("enableNestedScroll")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.enableNestedScrollAttribute(value_casted)
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
export function ScrollBar(
    /** @memo */
    style: ((attributes: ScrollBarAttribute) => void) | undefined,
    value: ScrollBarOptions,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkScrollBarComponent()
    })
    NodeAttach<ArkScrollBarPeer>((): ArkScrollBarPeer => ArkScrollBarPeer.create(receiver), (_: ArkScrollBarPeer) => {
        receiver.setScrollBarOptions(value)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
