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
import { Point } from "./point"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"
import { ShapePoint } from "./line"
import { Length } from "./units"

export class ArkPolygonPeer extends ArkCommonShapeMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkPolygonPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Polygon_construct(peerId, flags)
        const _peer  = new ArkPolygonPeer(_peerPtr, peerId, "Polygon", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setPolygonOptionsAttribute(options?: PolygonOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writePolygonOptions(options_value)
        }
        ArkUIGeneratedNativeModule._PolygonInterface_setPolygonOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    pointsAttribute(value: Array<ShapePoint> | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeInt32(value_value.length as int32)
            for (let i = 0; i < value_value.length; i++) {
                const value_value_element : [ Length, Length ] = value_value[i]
                const value_value_element_0  = value_value_element[0]
                thisSerializer.writeLength(value_value_element_0)
                const value_value_element_1  = value_value_element[1]
                thisSerializer.writeLength(value_value_element_1)
            }
        }
        ArkUIGeneratedNativeModule._PolygonAttribute_points(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface PolygonOptions {
    width?: string | number;
    height?: string | number;
}
export type PolygonInterface = (options?: PolygonOptions) => PolygonAttribute;
export interface PolygonAttribute extends CommonShapeMethod {
    points(value: Array<ShapePoint> | undefined): this
}
export class ArkPolygonStyle extends ArkCommonShapeMethodStyle implements PolygonAttribute {
    points_value?: Array<ShapePoint> | undefined
    public points(value: Array<ShapePoint> | undefined): this {
        return this
        }
}
export class ArkPolygonComponent extends ArkCommonShapeMethodComponent implements PolygonAttribute {
    getPeer(): ArkPolygonPeer {
        return (this.peer as ArkPolygonPeer)
    }
    public setPolygonOptions(options?: PolygonOptions): this {
        if (this.checkPriority("setPolygonOptions")) {
            const options_casted = options as (PolygonOptions | undefined)
            this.getPeer()?.setPolygonOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    public points(value: Array<ShapePoint> | undefined): this {
        if (this.checkPriority("points")) {
            const value_casted = value as (Array<ShapePoint> | undefined)
            this.getPeer()?.pointsAttribute(value_casted)
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
export function Polygon(
    /** @memo */
    style: ((attributes: PolygonAttribute) => void) | undefined,
    options?: PolygonOptions,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkPolygonComponent()
    })
    NodeAttach<ArkPolygonPeer>((): ArkPolygonPeer => ArkPolygonPeer.create(receiver), (_: ArkPolygonPeer) => {
        receiver.setPolygonOptions(options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
