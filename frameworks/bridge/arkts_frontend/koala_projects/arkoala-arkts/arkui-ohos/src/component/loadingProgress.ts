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
import { ResourceColor } from "./units"
import { ContentModifier, CommonConfiguration } from "./arkui-wrapper-builder"
import { Color } from "./enums"
import { Resource } from "global.resource"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"

export class ArkLoadingProgressPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkLoadingProgressPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._LoadingProgress_construct(peerId, flags)
        const _peer  = new ArkLoadingProgressPeer(_peerPtr, peerId, "LoadingProgress", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setLoadingProgressOptionsAttribute(): void {
        ArkUIGeneratedNativeModule._LoadingProgressInterface_setLoadingProgressOptions(this.peer.ptr)
    }
    colorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(3 as int32)
                const value_value_3  = value_value as Resource
                thisSerializer.writeResource(value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._LoadingProgressAttribute_color(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enableLoadingAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._LoadingProgressAttribute_enableLoading(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    contentModifierAttribute(value: ContentModifier | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteObject(value_value)
        }
        ArkUIGeneratedNativeModule._LoadingProgressAttribute_contentModifier(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export enum LoadingProgressStyle {
    DEFAULT = 0,
    Default = 0,
    CIRCULAR = 1,
    Circular = 1,
    ORBITAL = 2,
    Orbital = 2
}
export type LoadingProgressInterface = () => LoadingProgressAttribute;
export interface LoadingProgressAttribute extends CommonMethod {
    color(value: ResourceColor | undefined): this
    enableLoading(value: boolean | undefined): this
    contentModifier(value: ContentModifier | undefined): this
}
export class ArkLoadingProgressStyle extends ArkCommonMethodStyle implements LoadingProgressAttribute {
    color_value?: ResourceColor | undefined
    enableLoading_value?: boolean | undefined
    contentModifier_value?: ContentModifier | undefined
    public color(value: ResourceColor | undefined): this {
        return this
    }
    public enableLoading(value: boolean | undefined): this {
        return this
    }
    public contentModifier(value: ContentModifier | undefined): this {
        return this
        }
}
export interface LoadingProgressConfiguration extends CommonConfiguration {
    enableLoading: boolean;
}
export class ArkLoadingProgressComponent extends ArkCommonMethodComponent implements LoadingProgressAttribute {
    getPeer(): ArkLoadingProgressPeer {
        return (this.peer as ArkLoadingProgressPeer)
    }
    public setLoadingProgressOptions(): this {
        if (this.checkPriority("setLoadingProgressOptions")) {
            this.getPeer()?.setLoadingProgressOptionsAttribute()
            return this
        }
        return this
    }
    public color(value: ResourceColor | undefined): this {
        if (this.checkPriority("color")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.colorAttribute(value_casted)
            return this
        }
        return this
    }
    public enableLoading(value: boolean | undefined): this {
        if (this.checkPriority("enableLoading")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.enableLoadingAttribute(value_casted)
            return this
        }
        return this
    }
    public contentModifier(value: ContentModifier | undefined): this {
        if (this.checkPriority("contentModifier")) {
            const value_casted = value as (ContentModifier | undefined)
            this.getPeer()?.contentModifierAttribute(value_casted)
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
export function LoadingProgress(
    /** @memo */
    style: ((attributes: LoadingProgressAttribute) => void) | undefined,
    
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkLoadingProgressComponent()
    })
    NodeAttach<ArkLoadingProgressPeer>((): ArkLoadingProgressPeer => ArkLoadingProgressPeer.create(receiver), (_: ArkLoadingProgressPeer) => {
        receiver.setLoadingProgressOptions()
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
