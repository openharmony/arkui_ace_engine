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
import { ArkCommonMethodPeer, CommonMethod, CustomBuilder, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"
import { ResourceStr } from "./units"

export class ArkMenuItemGroupPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkMenuItemGroupPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._MenuItemGroup_construct(peerId, flags)
        const _peer  = new ArkMenuItemGroupPeer(_peerPtr, peerId, "MenuItemGroup", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setMenuItemGroupOptionsAttribute(value?: MenuItemGroupOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeMenuItemGroupOptions(value_value)
        }
        ArkUIGeneratedNativeModule._MenuItemGroupInterface_setMenuItemGroupOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface MenuItemGroupOptions {
    header?: ResourceStr | CustomBuilder;
    footer?: ResourceStr | CustomBuilder;
}
export type MenuItemGroupInterface = (value?: MenuItemGroupOptions) => MenuItemGroupAttribute;
export interface MenuItemGroupAttribute extends CommonMethod {
}
export class ArkMenuItemGroupStyle extends ArkCommonMethodStyle implements MenuItemGroupAttribute {
}
export class ArkMenuItemGroupComponent extends ArkCommonMethodComponent implements MenuItemGroupAttribute {
    getPeer(): ArkMenuItemGroupPeer {
        return (this.peer as ArkMenuItemGroupPeer)
    }
    public setMenuItemGroupOptions(value?: MenuItemGroupOptions): this {
        if (this.checkPriority("setMenuItemGroupOptions")) {
            const value_casted = value as (MenuItemGroupOptions | undefined)
            this.getPeer()?.setMenuItemGroupOptionsAttribute(value_casted)
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
export function MenuItemGroup(
    /** @memo */
    style: ((attributes: MenuItemGroupAttribute) => void) | undefined,
    value?: MenuItemGroupOptions,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkMenuItemGroupComponent()
    })
    NodeAttach<ArkMenuItemGroupPeer>((): ArkMenuItemGroupPeer => ArkMenuItemGroupPeer.create(receiver), (_: ArkMenuItemGroupPeer) => {
        receiver.setMenuItemGroupOptions(value)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
