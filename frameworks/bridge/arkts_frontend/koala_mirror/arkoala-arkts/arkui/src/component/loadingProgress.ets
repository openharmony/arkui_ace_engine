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

import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, wrapCallback, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { Resource_serializer, Resource } from "./../generated/resource"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, CommonConfiguration, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonMethodSet } from "./common"
import { ResourceColor } from "./units"
import { Color } from "./enums"
import { ContentModifier, AttributeModifier, hookLoadingProgressContentModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
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
    setColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((3).toChar())
                const value_value_3  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._LoadingProgressAttribute_setColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableLoadingAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._LoadingProgressAttribute_setEnableLoading(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setContentModifierAttribute(value: ContentModifier<LoadingProgressConfiguration> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteObject(value_value)
        }
        ArkUIGeneratedNativeModule._LoadingProgressAttribute_setContentModifier(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
    color(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method color")
    }
    enableLoading(value: boolean | undefined): this {
        throw new Error("Unimplemented method enableLoading")
    }
    contentModifier(value: ContentModifier<LoadingProgressConfiguration> | undefined): this {
        throw new Error("Unimplemented method contentModifier")
    }
    attributeModifier(value: AttributeModifier<LoadingProgressAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkLoadingProgressStyle extends ArkCommonMethodStyle implements LoadingProgressAttribute {
    color_value?: ResourceColor | undefined
    enableLoading_value?: boolean | undefined
    contentModifier_value?: ContentModifier<LoadingProgressConfiguration> | undefined
    attributeModifier_value?: AttributeModifier<LoadingProgressAttribute> | AttributeModifier<CommonMethod> | undefined
    public color(value: ResourceColor | undefined): this {
        return this
    }
    public enableLoading(value: boolean | undefined): this {
        return this
    }
    public contentModifier(value: ContentModifier<LoadingProgressConfiguration> | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<LoadingProgressAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: LoadingProgressAttribute): void {
        super.apply(target)
        if (this.color_value !== undefined)
            target.color(this.color_value!)
        if (this.enableLoading_value !== undefined)
            target.enableLoading(this.enableLoading_value!)
        if (this.contentModifier_value !== undefined)
            target.contentModifier(this.contentModifier_value!)
    }
}
export interface LoadingProgressConfiguration extends CommonConfiguration<LoadingProgressConfiguration> {
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
            this.getPeer()?.setColorAttribute(value_casted)
            return this
        }
        return this
    }
    public enableLoading(value: boolean | undefined): this {
        if (this.checkPriority("enableLoading")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setEnableLoadingAttribute(value_casted)
            return this
        }
        return this
    }
    public contentModifier(value: ContentModifier<LoadingProgressConfiguration> | undefined): this {
        if (this.checkPriority("contentModifier")) {
            const value_casted = value as (ContentModifier<LoadingProgressConfiguration> | undefined)
            this.getPeer()?.setContentModifierAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<LoadingProgressAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withLoadingProgressStyle(receiver: LoadingProgressAttribute, modifier: AttributeModifier<LoadingProgressAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkLoadingProgressStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("LoadingProgress")
// export function LoadingProgress(
//     
//     @memo
//     content_?: () => void,
// ): LoadingProgressAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function LoadingProgress(
    @memo
    style: ((attributes: LoadingProgressAttribute) => void) | undefined,
    
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkLoadingProgressComponent>((): ArkLoadingProgressComponent => {
        return new ArkLoadingProgressComponent()
    })
    NodeAttach<ArkLoadingProgressPeer>((): ArkLoadingProgressPeer => ArkLoadingProgressPeer.create(receiver), (_: ArkLoadingProgressPeer): void => {
        receiver.setLoadingProgressOptions()
        style?.(receiver)
        withLoadingProgressStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkLoadingProgressSet extends ArkCommonMethodSet implements LoadingProgressAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _color_flag?: boolean
    _color0_value?: ResourceColor | undefined
    _enableLoading_flag?: boolean
    _enableLoading0_value?: boolean | undefined
    _contentModifier_flag?: boolean
    _contentModifier0_value?: ContentModifier<LoadingProgressConfiguration> | undefined
    applyModifierPatch(component: LoadingProgressAttribute): void {
        if (this._color_flag)
            component.color((this._color0_value as ResourceColor | undefined))
        if (this._enableLoading_flag)
            component.enableLoading((this._enableLoading0_value as boolean | undefined))
        if (this._contentModifier_flag)
            component.contentModifier((this._contentModifier0_value as ContentModifier<LoadingProgressConfiguration> | undefined))
    }
    public color(value: ResourceColor | undefined): this {
        this._color_flag = true
        this._color0_value = value
        return this
    }
    public enableLoading(value: boolean | undefined): this {
        this._enableLoading_flag = true
        this._enableLoading0_value = value
        return this
    }
    public contentModifier(value: ContentModifier<LoadingProgressConfiguration> | undefined): this {
        this._contentModifier_flag = true
        this._contentModifier0_value = value
        return this
    }
    public attributeModifier(value: AttributeModifier<LoadingProgressAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class LoadingProgressConfiguration_serializer {
    public static write(buffer: SerializerBase, value: LoadingProgressConfiguration): void {
        let valueSerializer : SerializerBase = buffer
        const value_enabled  = value.enabled
        valueSerializer.writeBoolean(value_enabled)
        const value_contentModifier  = value.contentModifier
        valueSerializer.holdAndWriteObject(value_contentModifier)
        const value_enableLoading  = value.enableLoading
        valueSerializer.writeBoolean(value_enableLoading)
    }
    public static read(buffer: DeserializerBase): LoadingProgressConfiguration {
        let valueDeserializer : DeserializerBase = buffer
        const enabled_result : boolean = valueDeserializer.readBoolean()
        const contentModifier_result : ContentModifier<LoadingProgressConfiguration> = (valueDeserializer.readObject() as ContentModifier<LoadingProgressConfiguration>)
        const enableLoading_result : boolean = valueDeserializer.readBoolean()
        let value : LoadingProgressConfiguration = ({enabled: enabled_result, contentModifier: contentModifier_result, enableLoading: enableLoading_result} as LoadingProgressConfiguration)
        return value
    }
}
