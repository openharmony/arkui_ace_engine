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
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, UICommonMethod } from "./common"
import { ResourceColor } from "./units"
import { ContentModifier, CommonConfiguration } from "./arkui-wrapper-builder"
import { Color } from "./enums"
import { Resource } from "./resource"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { BuilderLambda } from "@koalaui/builderLambda"
import { UICommonBase, AttributeModifier } from "./../handwritten"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkLoadingProgressPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkLoadingProgressPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._LoadingProgress_construct(peerId, flags)
        const _peer  = new ArkLoadingProgressPeer(_peerPtr, peerId, "LoadingProgress", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setLoadingProgressOptionsAttribute(): void {
        ArkUIGeneratedNativeModule._LoadingProgressInterface_setLoadingProgressOptions(this.peer.ptr)
    }
    colorAttribute(value: ResourceColor): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isColor(value)) {
            thisSerializer.writeInt8(0)
            const value_0  = value as Color
            thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_0))
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2)
            const value_2  = value as string
            thisSerializer.writeString(value_2)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(3)
            const value_3  = value as Resource
            thisSerializer.writeResource(value_3)
        }
        ArkUIGeneratedNativeModule._LoadingProgressAttribute_color(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enableLoadingAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._LoadingProgressAttribute_enableLoading(this.peer.ptr, value ? 1 : 0)
    }
    contentModifierAttribute(value: ContentModifier): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteObject(value)
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

export interface LoadingProgressAttribute extends CommonMethod {
    color(value: ResourceColor): this
    enableLoading(value: boolean): this
    contentModifier(value: ContentModifier): this
    attributeModifier(value: AttributeModifier<LoadingProgressAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export interface UILoadingProgressAttribute extends UICommonMethod {
    @memo
    color(value: ResourceColor): this
    @memo
    enableLoading(value: boolean): this
    @memo
    contentModifier(value: ContentModifier): this
    @memo
    attributeModifier(value: AttributeModifier<LoadingProgressAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkLoadingProgressStyle extends ArkCommonMethodStyle implements LoadingProgressAttribute {
    color_value?: ResourceColor
    enableLoading_value?: boolean
    contentModifier_value?: ContentModifier
    public color(value: ResourceColor): this {
        return this
    }
    public enableLoading(value: boolean): this {
        return this
    }
    public contentModifier(value: ContentModifier): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<LoadingProgressAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export interface LoadingProgressConfiguration extends CommonConfiguration {
    enableLoading: boolean;
}
@memo_stable
export class ArkLoadingProgressComponent extends ArkCommonMethodComponent implements UILoadingProgressAttribute {
    getPeer(): ArkLoadingProgressPeer {
        return (this.peer as ArkLoadingProgressPeer)
    }
    @memo
    public setLoadingProgressOptions(): this {
        if (this.checkPriority("setLoadingProgressOptions")) {
            this.getPeer()?.setLoadingProgressOptionsAttribute()
            return this
        }
        return this
    }
    @memo
    public color(value: ResourceColor): this {
        if (this.checkPriority("color")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.colorAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public enableLoading(value: boolean): this {
        if (this.checkPriority("enableLoading")) {
            const value_casted = value as (boolean)
            this.getPeer()?.enableLoadingAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public contentModifier(value: ContentModifier): this {
        if (this.checkPriority("contentModifier")) {
            const value_casted = value as (ContentModifier)
            this.getPeer()?.contentModifierAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public attributeModifier(value: AttributeModifier<LoadingProgressAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
@memo
@BuilderLambda("LoadingProgress")
export function LoadingProgress(
    
    @memo
    content_?: () => void,
): LoadingProgressAttribute {
    throw new Error("Not implemented")
}

@memo
export function LoadingProgress(
    @memo
    style: ((attributes: UILoadingProgressAttribute) => void) | undefined,
    
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkLoadingProgressComponent>((): ArkLoadingProgressComponent => {
        return new ArkLoadingProgressComponent()
    })
    NodeAttach<ArkLoadingProgressPeer>((): ArkLoadingProgressPeer => ArkLoadingProgressPeer.create(receiver), (_: ArkLoadingProgressPeer): void => {
        receiver.setLoadingProgressOptions()
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
