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
import { ArkColumnPeer, ColumnAttribute, ArkColumnComponent, ArkColumnStyle } from "./column"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"

import { ArkCommonMethodComponent, ArkCommonMethodStyle, CommonMethod } from "./common"
export class ArkGridContainerPeer extends ArkColumnPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkGridContainerPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._GridContainer_construct(peerId, flags)
        const _peer  = new ArkGridContainerPeer(_peerPtr, peerId, "GridContainer", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setGridContainerOptionsAttribute(value?: GridContainerOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeGridContainerOptions(value_value)
        }
        ArkUIGeneratedNativeModule._GridContainerInterface_setGridContainerOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export enum SizeType {
    AUTO = 0,
    Auto = 0,
    XS = 1,
    SM = 2,
    MD = 3,
    LG = 4
}
export interface GridContainerOptions {
    columns?: number | string;
    sizeType?: SizeType;
    gutter?: number | string;
    margin?: number | string;
}
export type GridContainerInterface = (value?: GridContainerOptions) => GridContainerAttribute;
export interface GridContainerAttribute extends ColumnAttribute {
}
export class ArkGridContainerStyle extends ArkColumnStyle implements GridContainerAttribute {
}
export class ArkGridContainerComponent extends ArkColumnComponent implements GridContainerAttribute {
    getPeer(): ArkGridContainerPeer {
        return (this.peer as ArkGridContainerPeer)
    }
    public setGridContainerOptions(value?: GridContainerOptions): this {
        if (this.checkPriority("setGridContainerOptions")) {
            const value_casted = value as (GridContainerOptions | undefined)
            this.getPeer()?.setGridContainerOptionsAttribute(value_casted)
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
export function GridContainer(
    /** @memo */
    style: ((attributes: GridContainerAttribute) => void) | undefined,
    value?: GridContainerOptions,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkGridContainerComponent()
    })
    NodeAttach<ArkGridContainerPeer>((): ArkGridContainerPeer => ArkGridContainerPeer.create(receiver), (_: ArkGridContainerPeer) => {
        receiver.setGridContainerOptions(value)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
