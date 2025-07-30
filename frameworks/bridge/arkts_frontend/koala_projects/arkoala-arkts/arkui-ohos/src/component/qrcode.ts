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
import { ResourceColor } from "./units"
import { Resource } from "global/resource"
import { Color } from "./enums"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"

export class ArkQRCodePeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkQRCodePeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._QRCode_construct(peerId, flags)
        const _peer  = new ArkQRCodePeer(_peerPtr, peerId, "QRCode", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setQRCodeOptionsAttribute(value: string): void {
        ArkUIGeneratedNativeModule._QRCodeInterface_setQRCodeOptions(this.peer.ptr, value)
    }
    colorAttribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._QRCodeAttribute_color(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    backgroundColorAttribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._QRCodeAttribute_backgroundColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    contentOpacityAttribute(value: number | Resource | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as Resource
                thisSerializer.writeResource(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._QRCodeAttribute_contentOpacity(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export type QRCodeInterface = (value: string) => QRCodeAttribute;
export interface QRCodeAttribute extends CommonMethod {
    color(value: ResourceColor | undefined): this
    backgroundColor(value: ResourceColor | undefined): this
    contentOpacity(value: number | Resource | undefined): this
}
export class ArkQRCodeStyle extends ArkCommonMethodStyle implements QRCodeAttribute {
    color_value?: ResourceColor | undefined
    backgroundColor_value?: ResourceColor | undefined
    contentOpacity_value?: number | Resource | undefined
    public color(value: ResourceColor | undefined): this {
        return this
    }
    public backgroundColor(value: ResourceColor | undefined): this {
        return this
    }
    public contentOpacity(value: number | Resource | undefined): this {
        return this
        }
}
export class ArkQRCodeComponent extends ArkCommonMethodComponent implements QRCodeAttribute {
    getPeer(): ArkQRCodePeer {
        return (this.peer as ArkQRCodePeer)
    }
    public setQRCodeOptions(value: string): this {
        if (this.checkPriority("setQRCodeOptions")) {
            const value_casted = value as (string)
            this.getPeer()?.setQRCodeOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    public color(value: ResourceColor | undefined): this {
        if (this.checkPriority("color")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.colorAttribute(value_casted)
            return this
        }
        return this
    }
    public backgroundColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("backgroundColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.backgroundColorAttribute(value_casted)
            return this
        }
        return this
    }
    public contentOpacity(value: number | Resource | undefined): this {
        if (this.checkPriority("contentOpacity")) {
            const value_casted = value as (number | Resource | undefined)
            this.getPeer()?.contentOpacityAttribute(value_casted)
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
export function QRCode(
    /** @memo */
    style: ((attributes: QRCodeAttribute) => void) | undefined,
    value: string,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkQRCodeComponent()
    })
    NodeAttach<ArkQRCodePeer>((): ArkQRCodePeer => ArkQRCodePeer.create(receiver), (_: ArkQRCodePeer) => {
        receiver.setQRCodeOptions(value)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
