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
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"

export class ArkGridColPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkGridColPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._GridCol_construct(peerId, flags)
        const _peer  = new ArkGridColPeer(_peerPtr, peerId, "GridCol", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setGridColOptionsAttribute(option?: GridColOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let option_type : int32 = RuntimeType.UNDEFINED
        option_type = runtimeType(option)
        thisSerializer.writeInt8(option_type as int32)
        if ((RuntimeType.UNDEFINED) != (option_type)) {
            const option_value  = option!
            thisSerializer.writeGridColOptions(option_value)
        }
        ArkUIGeneratedNativeModule._GridColInterface_setGridColOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    spanAttribute(value: number | GridColColumnOption | undefined): void {
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
                const value_value_1  = value_value as GridColColumnOption
                thisSerializer.writeGridColColumnOption(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._GridColAttribute_span(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    gridColOffsetAttribute(value: number | GridColColumnOption | undefined): void {
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
                const value_value_1  = value_value as GridColColumnOption
                thisSerializer.writeGridColColumnOption(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._GridColAttribute_gridColOffset(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    orderAttribute(value: number | GridColColumnOption | undefined): void {
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
                const value_value_1  = value_value as GridColColumnOption
                thisSerializer.writeGridColColumnOption(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._GridColAttribute_order(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface GridColColumnOption {
    xs?: number;
    sm?: number;
    md?: number;
    lg?: number;
    xl?: number;
    xxl?: number;
}
export interface GridColOptions {
    span?: number | GridColColumnOption;
    offset?: number | GridColColumnOption;
    order?: number | GridColColumnOption;
}
export type GridColInterface = (option?: GridColOptions) => GridColAttribute;
export interface GridColAttribute extends CommonMethod {
    span(value: number | GridColColumnOption | undefined): this
    gridColOffset(value: number | GridColColumnOption | undefined): this
    order(value: number | GridColColumnOption | undefined): this
}
export class ArkGridColStyle extends ArkCommonMethodStyle implements GridColAttribute {
    span_value?: number | GridColColumnOption | undefined
    gridColOffset_value?: number | GridColColumnOption | undefined
    order_value?: number | GridColColumnOption | undefined
    public span(value: number | GridColColumnOption | undefined): this {
        return this
    }
    public gridColOffset(value: number | GridColColumnOption | undefined): this {
        return this
    }
    public order(value: number | GridColColumnOption | undefined): this {
        return this
        }
}
export class ArkGridColComponent extends ArkCommonMethodComponent implements GridColAttribute {
    getPeer(): ArkGridColPeer {
        return (this.peer as ArkGridColPeer)
    }
    public setGridColOptions(option?: GridColOptions): this {
        if (this.checkPriority("setGridColOptions")) {
            const option_casted = option as (GridColOptions | undefined)
            this.getPeer()?.setGridColOptionsAttribute(option_casted)
            return this
        }
        return this
    }
    public span(value: number | GridColColumnOption | undefined): this {
        if (this.checkPriority("span")) {
            const value_casted = value as (number | GridColColumnOption | undefined)
            this.getPeer()?.spanAttribute(value_casted)
            return this
        }
        return this
    }
    public gridColOffset(value: number | GridColColumnOption | undefined): this {
        if (this.checkPriority("gridColOffset")) {
            const value_casted = value as (number | GridColColumnOption | undefined)
            this.getPeer()?.gridColOffsetAttribute(value_casted)
            return this
        }
        return this
    }
    public order(value: number | GridColColumnOption | undefined): this {
        if (this.checkPriority("order")) {
            const value_casted = value as (number | GridColColumnOption | undefined)
            this.getPeer()?.orderAttribute(value_casted)
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
export function GridCol(
    /** @memo */
    style: ((attributes: GridColAttribute) => void) | undefined,
    option?: GridColOptions,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkGridColComponent()
    })
    NodeAttach<ArkGridColPeer>((): ArkGridColPeer => ArkGridColPeer.create(receiver), (_: ArkGridColPeer) => {
        receiver.setGridColOptions(option)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
