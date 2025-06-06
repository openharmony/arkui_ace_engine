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
import { ArkCommonMethodPeer, CommonMethod, ChildrenMainSize, CustomBuilder, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { ListDividerOptions } from "./list"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"
import { ComponentContent } from "./arkui-custom"

export class ArkListItemGroupPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkListItemGroupPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._ListItemGroup_construct(peerId, flags)
        const _peer  = new ArkListItemGroupPeer(_peerPtr, peerId, "ListItemGroup", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setListItemGroupOptionsAttribute(options?: ListItemGroupOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeListItemGroupOptions(options_value)
        }
        ArkUIGeneratedNativeModule._ListItemGroupInterface_setListItemGroupOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    dividerAttribute(value: ListDividerOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeListDividerOptions(value_value)
        }
        ArkUIGeneratedNativeModule._ListItemGroupAttribute_divider(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    childrenMainSizeAttribute(value: ChildrenMainSize | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeChildrenMainSize(value_value)
        }
        ArkUIGeneratedNativeModule._ListItemGroupAttribute_childrenMainSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export enum ListItemGroupStyle {
    NONE = 0,
    CARD = 1
}
export interface ListItemGroupOptions {
    header?: CustomBuilder;
    headerComponent?: ComponentContent;
    footer?: CustomBuilder;
    footerComponent?: ComponentContent;
    space?: number | string;
    style?: ListItemGroupStyle;
}
export type ListItemGroupInterface = (options?: ListItemGroupOptions) => ListItemGroupAttribute;
export interface ListItemGroupAttribute extends CommonMethod {
    divider(value: ListDividerOptions | undefined): this
    childrenMainSize(value: ChildrenMainSize | undefined): this
}
export class ArkListItemGroupStyle extends ArkCommonMethodStyle implements ListItemGroupAttribute {
    divider_value?: ListDividerOptions | undefined
    childrenMainSize_value?: ChildrenMainSize | undefined
    public divider(value: ListDividerOptions | undefined): this {
        return this
    }
    public childrenMainSize(value: ChildrenMainSize | undefined): this {
        return this
        }
}
export class ArkListItemGroupComponent extends ArkCommonMethodComponent implements ListItemGroupAttribute {
    getPeer(): ArkListItemGroupPeer {
        return (this.peer as ArkListItemGroupPeer)
    }
    public setListItemGroupOptions(options?: ListItemGroupOptions): this {
        if (this.checkPriority("setListItemGroupOptions")) {
            const options_casted = options as (ListItemGroupOptions | undefined)
            this.getPeer()?.setListItemGroupOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    public divider(value: ListDividerOptions | undefined): this {
        if (this.checkPriority("divider")) {
            const value_casted = value as (ListDividerOptions | undefined)
            this.getPeer()?.dividerAttribute(value_casted)
            return this
        }
        return this
    }
    public childrenMainSize(value: ChildrenMainSize | undefined): this {
        if (this.checkPriority("childrenMainSize")) {
            const value_casted = value as (ChildrenMainSize | undefined)
            this.getPeer()?.childrenMainSizeAttribute(value_casted)
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
export function ListItemGroup(
    /** @memo */
    style: ((attributes: ListItemGroupAttribute) => void) | undefined,
    options?: ListItemGroupOptions,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkListItemGroupComponent()
    })
    NodeAttach<ArkListItemGroupPeer>((): ArkListItemGroupPeer => ArkListItemGroupPeer.create(receiver), (_: ArkListItemGroupPeer) => {
        receiver.setListItemGroupOptions(options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
