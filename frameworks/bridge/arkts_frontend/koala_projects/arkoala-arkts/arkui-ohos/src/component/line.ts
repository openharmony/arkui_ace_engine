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
import { Length } from "./units"
import { Resource } from "global/resource"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"

export class ArkLinePeer extends ArkCommonShapeMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkLinePeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Line_construct(peerId, flags)
        const _peer  = new ArkLinePeer(_peerPtr, peerId, "Line", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setLineOptionsAttribute(options?: LineOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeLineOptions(options_value)
        }
        ArkUIGeneratedNativeModule._LineInterface_setLineOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    startPointAttribute(value: Array<Length> | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeInt32(value_value.length as int32)
            for (let i = 0; i < value_value.length; i++) {
                const value_value_element : Length = value_value[i]
                thisSerializer.writeLength(value_value_element)
            }
        }
        ArkUIGeneratedNativeModule._LineAttribute_startPoint(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    endPointAttribute(value: Array<Length> | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeInt32(value_value.length as int32)
            for (let i = 0; i < value_value.length; i++) {
                const value_value_element : Length = value_value[i]
                thisSerializer.writeLength(value_value_element)
            }
        }
        ArkUIGeneratedNativeModule._LineAttribute_endPoint(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface LineOptions {
    width?: string | number;
    height?: string | number;
}
export type LineInterface = (options?: LineOptions) => LineAttribute;
export interface LineAttribute extends CommonShapeMethod {
    startPoint(value: Array<Length> | undefined): this
    endPoint(value: Array<Length> | undefined): this
}
export interface UILineAttribute extends UICommonShapeMethod {
    /** @memo */
    startPoint(value: Array<Length> | undefined): this
    /** @memo */
    endPoint(value: Array<Length> | undefined): this
    /** @memo */
}
export class ArkLineStyle extends ArkCommonShapeMethodStyle implements LineAttribute {
    startPoint_value?: Array<Length> | undefined
    endPoint_value?: Array<Length> | undefined
    public startPoint(value: Array<Length> | undefined): this {
        return this
    }
    public endPoint(value: Array<Length> | undefined): this {
        return this
        }
}
/** @memo:stable */
export class ArkLineComponent extends ArkCommonShapeMethodComponent implements UILineAttribute {
    getPeer(): ArkLinePeer {
        return (this.peer as ArkLinePeer)
    }
    /** @memo */
    public setLineOptions(options?: LineOptions): this {
        if (this.checkPriority("setLineOptions")) {
            const options_casted = options as (LineOptions | undefined)
            this.getPeer()?.setLineOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    /** @memo */
    public startPoint(value: Array<Length> | undefined): this {
        if (this.checkPriority("startPoint")) {
            const value_casted = value as (Array<Length> | undefined)
            this.getPeer()?.startPointAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public endPoint(value: Array<Length> | undefined): this {
        if (this.checkPriority("endPoint")) {
            const value_casted = value as (Array<Length> | undefined)
            this.getPeer()?.endPointAttribute(value_casted)
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
export function Line(
    /** @memo */
    style: ((attributes: UILineAttribute) => void) | undefined,
    options?: LineOptions,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkLineComponent()
    })
    NodeAttach<ArkLinePeer>((): ArkLinePeer => ArkLinePeer.create(receiver), (_: ArkLinePeer) => {
        receiver.setLineOptions(options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
