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
import { ArkCommonShapeMethodPeer, CommonShapeMethod, ArkCommonShapeMethodComponent, ArkCommonShapeMethodStyle, UICommonShapeMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, CommonMethod, UICommonMethod } from "./common"
import { common2D } from "./ohos.graphics.common2D"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { UICommonBase, AttributeModifier } from "./../handwritten"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkPolylinePeer extends ArkCommonShapeMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkPolylinePeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Polyline_construct(peerId, flags)
        const _peer  = new ArkPolylinePeer(_peerPtr, peerId, "Polyline", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setPolylineOptionsAttribute(options?: PolylineOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writePolylineOptions(options_value)
        }
        ArkUIGeneratedNativeModule._PolylineInterface_setPolylineOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    pointsAttribute(value: Array<common2D.Point>): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeInt32(value.length as int32)
        for (let i = 0; i < value.length; i++) {
            const value_element : common2D.Point = value[i]
            thisSerializer.writecommon2D_Point(value_element)
        }
        ArkUIGeneratedNativeModule._PolylineAttribute_points(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface PolylineOptions {
    width?: string | number;
    height?: string | number;
}

export interface PolylineAttribute extends CommonShapeMethod {
    points(value: Array<common2D.Point>): this
    attributeModifier(value: AttributeModifier<PolylineAttribute> | AttributeModifier<CommonShapeMethod> | AttributeModifier<CommonMethod> | undefined): this
}
export interface UIPolylineAttribute extends UICommonShapeMethod {
    /** @memo */
    points(value: Array<common2D.Point>): this
    /** @memo */
    attributeModifier(value: AttributeModifier<PolylineAttribute> | AttributeModifier<CommonShapeMethod> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkPolylineStyle extends ArkCommonShapeMethodStyle implements PolylineAttribute {
    points_value?: Array<common2D.Point>
    public points(value: Array<common2D.Point>): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<PolylineAttribute> | AttributeModifier<CommonShapeMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
/** @memo:stable */
export class ArkPolylineComponent extends ArkCommonShapeMethodComponent implements UIPolylineAttribute {
    getPeer(): ArkPolylinePeer {
        return (this.peer as ArkPolylinePeer)
    }
    /** @memo */
    public setPolylineOptions(options?: PolylineOptions): this {
        if (this.checkPriority("setPolylineOptions")) {
            const options_casted = options as (PolylineOptions | undefined)
            this.getPeer()?.setPolylineOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    /** @memo */
    public points(value: Array<common2D.Point>): this {
        if (this.checkPriority("points")) {
            const value_casted = value as (Array<common2D.Point>)
            this.getPeer()?.pointsAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public attributeModifier(value: AttributeModifier<PolylineAttribute> | AttributeModifier<CommonShapeMethod> | AttributeModifier<CommonMethod> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function ArkPolyline(
    /** @memo */
    style: ((attributes: UIPolylineAttribute) => void) | undefined,
    /** @memo */
    content_: (() => void) | undefined,
    options?: PolylineOptions,
): void {
    const receiver = remember(() => {
        return new ArkPolylineComponent()
    })
    NodeAttach<ArkPolylinePeer>((): ArkPolylinePeer => ArkPolylinePeer.create(receiver), (_: ArkPolylinePeer) => {
        receiver.setPolylineOptions(options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
