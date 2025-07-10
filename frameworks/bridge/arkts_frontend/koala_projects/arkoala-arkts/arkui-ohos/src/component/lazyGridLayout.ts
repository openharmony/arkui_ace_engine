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
import { LengthMetrics } from "../Graphics"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"

export class ArkLazyGridLayoutPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkLazyGridLayoutPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._LazyGridLayout_construct(peerId, flags)
        const _peer  = new ArkLazyGridLayoutPeer(_peerPtr, peerId, "LazyGridLayout", flags)
        component?.setPeer(_peer)
        return _peer
    }
    rowsGapAttribute(value: LengthMetrics | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeLengthMetrics(value_value)
        }
        ArkUIGeneratedNativeModule._LazyGridLayoutAttribute_rowsGap(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    columnsGapAttribute(value: LengthMetrics | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeLengthMetrics(value_value)
        }
        ArkUIGeneratedNativeModule._LazyGridLayoutAttribute_columnsGap(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class ArkLazyVGridLayoutPeer extends ArkLazyGridLayoutPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkLazyVGridLayoutPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._LazyVGridLayout_construct(peerId, flags)
        const _peer  = new ArkLazyVGridLayoutPeer(_peerPtr, peerId, "LazyVGridLayout", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setLazyVGridLayoutOptionsAttribute(): void {
        ArkUIGeneratedNativeModule._LazyVGridLayoutInterface_setLazyVGridLayoutOptions(this.peer.ptr)
    }
    columnsTemplateAttribute(value: string | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeString(value_value)
        }
        ArkUIGeneratedNativeModule._LazyVGridLayoutAttribute_columnsTemplate(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export type LazyVGridLayoutInterface = () => LazyVGridLayoutAttribute;
export interface LazyGridLayoutAttribute extends CommonMethod {
    rowsGap(value: LengthMetrics | undefined): this
    columnsGap(value: LengthMetrics | undefined): this
}
export class ArkLazyGridLayoutStyle extends ArkCommonMethodStyle implements LazyGridLayoutAttribute {
    rowsGap_value?: LengthMetrics | undefined
    columnsGap_value?: LengthMetrics | undefined
    public rowsGap(value: LengthMetrics | undefined): this {
        return this
    }
    public columnsGap(value: LengthMetrics | undefined): this {
        return this
        }
}
export interface LazyVGridLayoutAttribute extends LazyGridLayoutAttribute {
    columnsTemplate(value: string | undefined): this
}
export class ArkLazyVGridLayoutStyle extends ArkLazyGridLayoutStyle implements LazyVGridLayoutAttribute {
    columnsTemplate_value?: string | undefined
    public columnsTemplate(value: string | undefined): this {
        return this
        }
}
export class ArkLazyGridLayoutComponent extends ArkCommonMethodComponent implements LazyGridLayoutAttribute {
    getPeer(): ArkLazyGridLayoutPeer {
        return (this.peer as ArkLazyGridLayoutPeer)
    }
    public rowsGap(value: LengthMetrics | undefined): this {
        if (this.checkPriority("rowsGap")) {
            const value_casted = value as (LengthMetrics | undefined)
            this.getPeer()?.rowsGapAttribute(value_casted)
            return this
        }
        return this
    }
    public columnsGap(value: LengthMetrics | undefined): this {
        if (this.checkPriority("columnsGap")) {
            const value_casted = value as (LengthMetrics | undefined)
            this.getPeer()?.columnsGapAttribute(value_casted)
            return this
        }
        return this
    }
    
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export class ArkLazyVGridLayoutComponent extends ArkLazyGridLayoutComponent implements LazyVGridLayoutAttribute {
    getPeer(): ArkLazyVGridLayoutPeer {
        return (this.peer as ArkLazyVGridLayoutPeer)
    }
    public setLazyVGridLayoutOptions(): this {
        if (this.checkPriority("setLazyVGridLayoutOptions")) {
            this.getPeer()?.setLazyVGridLayoutOptionsAttribute()
            return this
        }
        return this
    }
    public columnsTemplate(value: string | undefined): this {
        if (this.checkPriority("columnsTemplate")) {
            const value_casted = value as (string | undefined)
            this.getPeer()?.columnsTemplateAttribute(value_casted)
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
export function LazyVGridLayout(
    /** @memo */
    style: ((attributes: LazyVGridLayoutAttribute) => void) | undefined,
    
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkLazyVGridLayoutComponent()
    })
    NodeAttach<ArkLazyVGridLayoutPeer>((): ArkLazyVGridLayoutPeer => ArkLazyVGridLayoutPeer.create(receiver), (_: ArkLazyVGridLayoutPeer) => {
        receiver.setLazyVGridLayoutOptions()
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
