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
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"

export class ArkCirclePeer extends ArkCommonShapeMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkCirclePeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Circle_construct(peerId, flags)
        const _peer  = new ArkCirclePeer(_peerPtr, peerId, "Circle", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setCircleOptionsAttribute(value?: CircleOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeCircleOptions(value_value)
        }
        ArkUIGeneratedNativeModule._CircleInterface_setCircleOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface CircleOptions {
    width?: string | number;
    height?: string | number;
}
export type CircleInterface = (value?: CircleOptions) => CircleAttribute;
export interface CircleAttribute extends CommonShapeMethod {
}
export class ArkCircleStyle extends ArkCommonShapeMethodStyle implements CircleAttribute {
}
export class ArkCircleComponent extends ArkCommonShapeMethodComponent implements CircleAttribute {
    getPeer(): ArkCirclePeer {
        return (this.peer as ArkCirclePeer)
    }
    public setCircleOptions(value?: CircleOptions): this {
        if (this.checkPriority("setCircleOptions")) {
            const value_casted = value as (CircleOptions | undefined)
            this.getPeer()?.setCircleOptionsAttribute(value_casted)
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
export function Circle(
    /** @memo */
    style: ((attributes: CircleAttribute) => void) | undefined,
    value?: CircleOptions,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkCircleComponent()
    })
    NodeAttach<ArkCirclePeer>((): ArkCirclePeer => ArkCirclePeer.create(receiver), (_: ArkCirclePeer) => {
        receiver.setCircleOptions(value)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
