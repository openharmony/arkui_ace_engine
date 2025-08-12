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
import { Color } from "./enums"
import { Resource } from "global.resource"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"

export class ArkHyperlinkPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkHyperlinkPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Hyperlink_construct(peerId, flags)
        const _peer  = new ArkHyperlinkPeer(_peerPtr, peerId, "Hyperlink", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setHyperlinkOptionsAttribute(address: string | Resource, content?: string | Resource): void {
        const thisSerializer : Serializer = Serializer.hold()
        let address_type : int32 = RuntimeType.UNDEFINED
        address_type = runtimeType(address)
        if (RuntimeType.STRING == address_type) {
            thisSerializer.writeInt8(0 as int32)
            const address_0  = address as string
            thisSerializer.writeString(address_0)
        }
        else if (RuntimeType.OBJECT == address_type) {
            thisSerializer.writeInt8(1 as int32)
            const address_1  = address as Resource
            thisSerializer.writeResource(address_1)
        }
        let content_type : int32 = RuntimeType.UNDEFINED
        content_type = runtimeType(content)
        thisSerializer.writeInt8(content_type as int32)
        if ((RuntimeType.UNDEFINED) != (content_type)) {
            const content_value  = content!
            let content_value_type : int32 = RuntimeType.UNDEFINED
            content_value_type = runtimeType(content_value)
            if (RuntimeType.STRING == content_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const content_value_0  = content_value as string
                thisSerializer.writeString(content_value_0)
            }
            else if (RuntimeType.OBJECT == content_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const content_value_1  = content_value as Resource
                thisSerializer.writeResource(content_value_1)
            }
        }
        ArkUIGeneratedNativeModule._HyperlinkInterface_setHyperlinkOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    colorAttribute(value: Color | number | string | Resource | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(3 as int32)
                const value_value_3  = value_value as Resource
                thisSerializer.writeResource(value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._HyperlinkAttribute_color(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export type HyperlinkInterface = (address: string | Resource, content?: string | Resource) => HyperlinkAttribute;
export interface HyperlinkAttribute extends CommonMethod {
    color(value: Color | number | string | Resource | undefined): this
}
export class ArkHyperlinkStyle extends ArkCommonMethodStyle implements HyperlinkAttribute {
    color_value?: Color | number | string | Resource | undefined
    public color(value: Color | number | string | Resource | undefined): this {
        return this
        }
}
export class ArkHyperlinkComponent extends ArkCommonMethodComponent implements HyperlinkAttribute {
    getPeer(): ArkHyperlinkPeer {
        return (this.peer as ArkHyperlinkPeer)
    }
    public setHyperlinkOptions(address: string | Resource, content?: string | Resource): this {
        if (this.checkPriority("setHyperlinkOptions")) {
            const address_casted = address as (string | Resource)
            const content_casted = content as (string | Resource | undefined)
            this.getPeer()?.setHyperlinkOptionsAttribute(address_casted, content_casted)
            return this
        }
        return this
    }
    public color(value: Color | number | string | Resource | undefined): this {
        if (this.checkPriority("color")) {
            const value_casted = value as (Color | number | string | Resource | undefined)
            this.getPeer()?.colorAttribute(value_casted)
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
export function Hyperlink(
    /** @memo */
    style: ((attributes: HyperlinkAttribute) => void) | undefined,
    address: string | Resource, content?: string | Resource,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkHyperlinkComponent()
    })
    NodeAttach<ArkHyperlinkPeer>((): ArkHyperlinkPeer => ArkHyperlinkPeer.create(receiver), (_: ArkHyperlinkPeer) => {
        receiver.setHyperlinkOptions(address,content)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
