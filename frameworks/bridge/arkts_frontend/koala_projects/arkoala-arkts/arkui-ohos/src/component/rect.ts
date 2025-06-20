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
import { ArkCommonShapeMethodPeer, CommonShapeMethod, ArkCommonShapeMethodComponent, ArkCommonShapeMethodStyle, ArkCommonMethodComponent, ArkCommonMethodStyle, CommonMethod } from "./common"
import { Length } from "./units"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"

export type RadiusItem = [
    Length,
    Length
]

export class ArkRectPeer extends ArkCommonShapeMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkRectPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Rect_construct(peerId, flags)
        const _peer  = new ArkRectPeer(_peerPtr, peerId, "Rect", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setRectOptionsAttribute(options?: RectOptions | RoundedRectOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            let options_value_type : int32 = RuntimeType.UNDEFINED
            options_value_type = runtimeType(options_value)
            if (TypeChecker.isRectOptions(options_value, true, true, false)) {
                thisSerializer.writeInt8(0 as int32)
                const options_value_0  = options_value as RectOptions
                thisSerializer.writeRectOptions(options_value_0)
            }
            else if (TypeChecker.isRoundedRectOptions(options_value, true, true, false, false)) {
                thisSerializer.writeInt8(1 as int32)
                const options_value_1  = options_value as RoundedRectOptions
                thisSerializer.writeRoundedRectOptions(options_value_1)
            }
        }
        ArkUIGeneratedNativeModule._RectInterface_setRectOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    radiusWidthAttribute(value: number | string | undefined): void {
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
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._RectAttribute_radiusWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    radiusHeightAttribute(value: number | string | undefined): void {
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
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._RectAttribute_radiusHeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    radiusAttribute(value: number | string | Array<number | string> | undefined): void {
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
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as Array<number | string>
                thisSerializer.writeInt32(value_value_2.length as int32)
                for (let i = 0; i < value_value_2.length; i++) {
                    const value_value_2_element : number | string = value_value_2[i]
                    let value_value_2_element_type : int32 = RuntimeType.UNDEFINED
                    value_value_2_element_type = runtimeType(value_value_2_element)
                    if (RuntimeType.NUMBER == value_value_2_element_type) {
                        thisSerializer.writeInt8(0 as int32)
                        const value_value_2_element_0  = value_value_2_element as number
                        thisSerializer.writeNumber(value_value_2_element_0)
                    }
                    else if (RuntimeType.STRING == value_value_2_element_type) {
                        thisSerializer.writeInt8(1 as int32)
                        const value_value_2_element_1  = value_value_2_element as string
                        thisSerializer.writeString(value_value_2_element_1)
                    }
                }
            }
        }
        ArkUIGeneratedNativeModule._RectAttribute_radius(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface RectOptions {
    width?: number | string;
    height?: number | string;
    radius?: Length | Array<RadiusItem>;
}
export interface RoundedRectOptions {
    width?: number | string;
    height?: number | string;
    radiusWidth?: number | string;
    radiusHeight?: number | string;
}
export type RectInterface = (options?: RectOptions | RoundedRectOptions) => RectAttribute;
export interface RectAttribute extends CommonShapeMethod {
    radiusWidth(value: number | string | undefined): this
    radiusHeight(value: number | string | undefined): this
    radius(value: number | string | Array<number | string> | undefined): this
}
export class ArkRectStyle extends ArkCommonShapeMethodStyle implements RectAttribute {
    radiusWidth_value?: number | string | undefined
    radiusHeight_value?: number | string | undefined
    radius_value?: number | string | Array<number | string> | undefined
    public radiusWidth(value: number | string | undefined): this {
        return this
    }
    public radiusHeight(value: number | string | undefined): this {
        return this
    }
    public radius(value: number | string | Array<number | string> | undefined): this {
        return this
        }
}
export class ArkRectComponent extends ArkCommonShapeMethodComponent implements RectAttribute {
    getPeer(): ArkRectPeer {
        return (this.peer as ArkRectPeer)
    }
    public setRectOptions(options?: RectOptions | RoundedRectOptions): this {
        if (this.checkPriority("setRectOptions")) {
            const options_casted = options as (RectOptions | RoundedRectOptions | undefined)
            this.getPeer()?.setRectOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    public radiusWidth(value: number | string | undefined): this {
        if (this.checkPriority("radiusWidth")) {
            const value_casted = value as (number | string | undefined)
            this.getPeer()?.radiusWidthAttribute(value_casted)
            return this
        }
        return this
    }
    public radiusHeight(value: number | string | undefined): this {
        if (this.checkPriority("radiusHeight")) {
            const value_casted = value as (number | string | undefined)
            this.getPeer()?.radiusHeightAttribute(value_casted)
            return this
        }
        return this
    }
    public radius(value: number | string | Array<number | string> | undefined): this {
        if (this.checkPriority("radius")) {
            const value_casted = value as (number | string | Array<number | string> | undefined)
            this.getPeer()?.radiusAttribute(value_casted)
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
export function Rect(
    /** @memo */
    style: ((attributes: RectAttribute) => void) | undefined,
    options?: RectOptions | RoundedRectOptions,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkRectComponent()
    })
    NodeAttach<ArkRectPeer>((): ArkRectPeer => ArkRectPeer.create(receiver), (_: ArkRectPeer) => {
        receiver.setRectOptions(options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
