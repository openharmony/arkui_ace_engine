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
import { ArkCommonMethodPeer, CommonMethod, PointLightStyle, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { VerticalAlign, FlexAlign } from "./enums"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"

export class ArkRowPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkRowPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Row_construct(peerId, flags)
        const _peer  = new ArkRowPeer(_peerPtr, peerId, "Row", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setRowOptions0Attribute(options?: RowOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeRowOptions(options_value)
        }
        ArkUIGeneratedNativeModule._RowInterface_setRowOptions0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setRowOptions1Attribute(options?: RowOptions | RowOptionsV2): void {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            let options_value_type : int32 = RuntimeType.UNDEFINED
            options_value_type = runtimeType(options_value)
            if (TypeChecker.isRowOptions(options_value, false)) {
                thisSerializer.writeInt8(0 as int32)
                const options_value_0  = options_value as RowOptions
                thisSerializer.writeRowOptions(options_value_0)
            }
            else if (TypeChecker.isRowOptionsV2(options_value, false)) {
                thisSerializer.writeInt8(1 as int32)
                const options_value_1  = options_value as RowOptionsV2
                thisSerializer.writeRowOptionsV2(options_value_1)
            }
        }
        ArkUIGeneratedNativeModule._RowInterface_setRowOptions1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    alignItemsAttribute(value: VerticalAlign | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as VerticalAlign)
            thisSerializer.writeInt32(TypeChecker.VerticalAlign_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._RowAttribute_alignItems(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    justifyContentAttribute(value: FlexAlign | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as FlexAlign)
            thisSerializer.writeInt32(TypeChecker.FlexAlign_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._RowAttribute_justifyContent(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    pointLightAttribute(value: PointLightStyle | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writePointLightStyle(value_value)
        }
        ArkUIGeneratedNativeModule._RowAttribute_pointLight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    reverseAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._RowAttribute_reverse(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface RowOptions {
    space?: string | number;
}
export interface RowOptionsV2 {
    stub: string;
}
export interface RowAttribute extends CommonMethod {
    alignItems(value: VerticalAlign | undefined): this
    justifyContent(value: FlexAlign | undefined): this
    pointLight(value: PointLightStyle | undefined): this
    reverse(value: boolean | undefined): this
}
export class ArkRowStyle extends ArkCommonMethodStyle implements RowAttribute {
    alignItems_value?: VerticalAlign | undefined
    justifyContent_value?: FlexAlign | undefined
    pointLight_value?: PointLightStyle | undefined
    reverse_value?: boolean | undefined
    public alignItems(value: VerticalAlign | undefined): this {
        return this
    }
    public justifyContent(value: FlexAlign | undefined): this {
        return this
    }
    public pointLight(value: PointLightStyle | undefined): this {
        return this
    }
    public reverse(value: boolean | undefined): this {
        return this
        }
}
export class ArkRowComponent extends ArkCommonMethodComponent implements RowAttribute {
    getPeer(): ArkRowPeer {
        return (this.peer as ArkRowPeer)
    }
    public setRowOptions(options?: RowOptions | RowOptions | RowOptionsV2): this {
        if (this.checkPriority("setRowOptions")) {
            const options_type = runtimeType(options)
            if ((RuntimeType.OBJECT == options_type) || (RuntimeType.UNDEFINED == options_type)) {
                const options_casted = options as (RowOptions | undefined)
                this.getPeer()?.setRowOptions0Attribute(options_casted)
                return this
            }
            if ((RuntimeType.OBJECT == options_type) || (RuntimeType.OBJECT == options_type) || (RuntimeType.UNDEFINED == options_type)) {
                const options_casted = options as (RowOptions | RowOptionsV2 | undefined)
                this.getPeer()?.setRowOptions1Attribute(options_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public alignItems(value: VerticalAlign | undefined): this {
        if (this.checkPriority("alignItems")) {
            const value_casted = value as (VerticalAlign | undefined)
            this.getPeer()?.alignItemsAttribute(value_casted)
            return this
        }
        return this
    }
    public justifyContent(value: FlexAlign | undefined): this {
        if (this.checkPriority("justifyContent")) {
            const value_casted = value as (FlexAlign | undefined)
            this.getPeer()?.justifyContentAttribute(value_casted)
            return this
        }
        return this
    }
    public pointLight(value: PointLightStyle | undefined): this {
        if (this.checkPriority("pointLight")) {
            const value_casted = value as (PointLightStyle | undefined)
            this.getPeer()?.pointLightAttribute(value_casted)
            return this
        }
        return this
    }
    public reverse(value: boolean | undefined): this {
        if (this.checkPriority("reverse")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.reverseAttribute(value_casted)
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
export function Row(
    /** @memo */
    style: ((attributes: RowAttribute) => void) | undefined,
    options?: RowOptions | RowOptions | RowOptionsV2,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkRowComponent()
    })
    NodeAttach<ArkRowPeer>((): ArkRowPeer => ArkRowPeer.create(receiver), (_: ArkRowPeer) => {
        receiver.setRowOptions(options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
