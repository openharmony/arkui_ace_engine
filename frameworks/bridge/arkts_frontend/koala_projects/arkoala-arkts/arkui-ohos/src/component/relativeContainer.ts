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
import { Dimension } from "./units"
import { Axis } from "./enums"

export class ArkRelativeContainerPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkRelativeContainerPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._RelativeContainer_construct(peerId, flags)
        const _peer  = new ArkRelativeContainerPeer(_peerPtr, peerId, "RelativeContainer", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setRelativeContainerOptionsAttribute(): void {
        ArkUIGeneratedNativeModule._RelativeContainerInterface_setRelativeContainerOptions(this.peer.ptr)
    }
    guideLineAttribute(value: Array<GuideLineStyle> | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeInt32(value_value.length as int32)
            for (let i = 0; i < value_value.length; i++) {
                const value_value_element : GuideLineStyle = value_value[i]
                thisSerializer.writeGuideLineStyle(value_value_element)
            }
        }
        ArkUIGeneratedNativeModule._RelativeContainerAttribute_guideLine(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    barrier0Attribute(value: Array<BarrierStyle> | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeInt32(value_value.length as int32)
            for (let i = 0; i < value_value.length; i++) {
                const value_value_element : BarrierStyle = value_value[i]
                thisSerializer.writeBarrierStyle(value_value_element)
            }
        }
        ArkUIGeneratedNativeModule._RelativeContainerAttribute_barrier0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    barrier1Attribute(value: Array<LocalizedBarrierStyle> | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeInt32(value_value.length as int32)
            for (let i = 0; i < value_value.length; i++) {
                const value_value_element : LocalizedBarrierStyle = value_value[i]
                thisSerializer.writeLocalizedBarrierStyle(value_value_element)
            }
        }
        ArkUIGeneratedNativeModule._RelativeContainerAttribute_barrier1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export type RelativeContainerInterface = () => RelativeContainerAttribute;
export interface GuideLinePosition {
    start?: Dimension;
    end?: Dimension;
}
export interface GuideLineStyle {
    id: string;
    direction: Axis;
    position: GuideLinePosition;
}
export enum BarrierDirection {
    LEFT = 0,
    RIGHT = 1,
    TOP = 2,
    BOTTOM = 3
}
export enum LocalizedBarrierDirection {
    START = 0,
    END = 1,
    TOP = 2,
    BOTTOM = 3
}
export interface BarrierStyle {
    id: string;
    direction: BarrierDirection;
    referencedId: Array<string>;
}
export interface LocalizedBarrierStyle {
    id: string;
    localizedDirection: LocalizedBarrierDirection;
    referencedId: Array<string>;
}
export interface RelativeContainerAttribute extends CommonMethod {
    guideLine(value: Array<GuideLineStyle> | undefined): this
    barrier(value: Array<BarrierStyle> | undefined | Array<LocalizedBarrierStyle> | undefined): this
}
export class ArkRelativeContainerStyle extends ArkCommonMethodStyle implements RelativeContainerAttribute {
    guideLine_value?: Array<GuideLineStyle> | undefined
    barrier_value?: Array<BarrierStyle> | undefined
    public guideLine(value: Array<GuideLineStyle> | undefined): this {
        return this
    }
    public barrier(value: Array<BarrierStyle> | undefined | Array<LocalizedBarrierStyle> | undefined): this {
        return this
        }
}
export class ArkRelativeContainerComponent extends ArkCommonMethodComponent implements RelativeContainerAttribute {
    getPeer(): ArkRelativeContainerPeer {
        return (this.peer as ArkRelativeContainerPeer)
    }
    public setRelativeContainerOptions(): this {
        if (this.checkPriority("setRelativeContainerOptions")) {
            this.getPeer()?.setRelativeContainerOptionsAttribute()
            return this
        }
        return this
    }
    public guideLine(value: Array<GuideLineStyle> | undefined): this {
        if (this.checkPriority("guideLine")) {
            const value_casted = value as (Array<GuideLineStyle> | undefined)
            this.getPeer()?.guideLineAttribute(value_casted)
            return this
        }
        return this
    }
    public barrier(value: Array<BarrierStyle> | undefined | Array<LocalizedBarrierStyle> | undefined): this {
        if (this.checkPriority("barrier")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.OBJECT == value_type && TypeChecker.isArray_BarrierStyle(value)) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (Array<BarrierStyle> | undefined)
                this.getPeer()?.barrier0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.OBJECT == value_type && TypeChecker.isArray_LocalizedBarrierStyle(value)) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (Array<LocalizedBarrierStyle> | undefined)
                this.getPeer()?.barrier1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function RelativeContainer(
    /** @memo */
    style: ((attributes: RelativeContainerAttribute) => void) | undefined,
    
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkRelativeContainerComponent()
    })
    NodeAttach<ArkRelativeContainerPeer>((): ArkRelativeContainerPeer => ArkRelativeContainerPeer.create(receiver), (_: ArkRelativeContainerPeer) => {
        receiver.setRelativeContainerOptions()
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
