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
import { ArkCommonMethodPeer, CommonMethod, PointLightStyle, ArkCommonMethodComponent, ArkCommonMethodStyle, UICommonMethod } from "./common"
import { VerticalAlign, FlexAlign } from "./enums"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { UICommonBase, AttributeModifier } from "./../handwritten"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkRowPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkRowPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Row_construct(peerId, flags)
        const _peer  = new ArkRowPeer(_peerPtr, peerId, "Row", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setRowOptionsAttribute(options?: RowOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeRowOptions(options_value)
        }
        ArkUIGeneratedNativeModule._RowInterface_setRowOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    alignItemsAttribute(value: VerticalAlign): void {
        ArkUIGeneratedNativeModule._RowAttribute_alignItems(this.peer.ptr, TypeChecker.VerticalAlign_ToNumeric(value))
    }
    justifyContentAttribute(value: FlexAlign): void {
        ArkUIGeneratedNativeModule._RowAttribute_justifyContent(this.peer.ptr, TypeChecker.FlexAlign_ToNumeric(value))
    }
    pointLightAttribute(value: PointLightStyle): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writePointLightStyle(value)
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

export interface RowAttribute extends CommonMethod {
    alignItems(value: VerticalAlign): this
    justifyContent(value: FlexAlign): this
    pointLight(value: PointLightStyle): this
    reverse(value: boolean | undefined): this
    attributeModifier(value: AttributeModifier<RowAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export interface UIRowAttribute extends UICommonMethod {
    /** @memo */
    alignItems(value: VerticalAlign): this
    /** @memo */
    justifyContent(value: FlexAlign): this
    /** @memo */
    pointLight(value: PointLightStyle): this
    /** @memo */
    reverse(value: boolean | undefined): this
    /** @memo */
    attributeModifier(value: AttributeModifier<RowAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkRowStyle extends ArkCommonMethodStyle implements RowAttribute {
    alignItems_value?: VerticalAlign
    justifyContent_value?: FlexAlign
    pointLight_value?: PointLightStyle
    reverse_value?: boolean | undefined
    public alignItems(value: VerticalAlign): this {
        return this
    }
    public justifyContent(value: FlexAlign): this {
        return this
    }
    public pointLight(value: PointLightStyle): this {
        return this
    }
    public reverse(value: boolean | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<RowAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
/** @memo:stable */
export class ArkRowComponent extends ArkCommonMethodComponent implements UIRowAttribute {
    getPeer(): ArkRowPeer {
        return (this.peer as ArkRowPeer)
    }
    /** @memo */
    public setRowOptions(options?: RowOptions): this {
        if (this.checkPriority("setRowOptions")) {
            const options_casted = options as (RowOptions | undefined)
            this.getPeer()?.setRowOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    /** @memo */
    public alignItems(value: VerticalAlign): this {
        if (this.checkPriority("alignItems")) {
            const value_casted = value as (VerticalAlign)
            this.getPeer()?.alignItemsAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public justifyContent(value: FlexAlign): this {
        if (this.checkPriority("justifyContent")) {
            const value_casted = value as (FlexAlign)
            this.getPeer()?.justifyContentAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public pointLight(value: PointLightStyle): this {
        if (this.checkPriority("pointLight")) {
            const value_casted = value as (PointLightStyle)
            this.getPeer()?.pointLightAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public reverse(value: boolean | undefined): this {
        if (this.checkPriority("reverse")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.reverseAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public attributeModifier(value: AttributeModifier<RowAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function ArkRow(
    /** @memo */
    style: ((attributes: UIRowAttribute) => void) | undefined,
    /** @memo */
    content_: (() => void) | undefined,
    options?: RowOptions,
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
