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

import { ArkThemeScopeManager } from '#arktheme'
import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from '@koalaui/interop'
import { global_resource_Resource_serializer } from './../framework/resource'
import { int32, int64, float32, unsafeCast } from '@koalaui/common'
import { ComponentBase } from './../ComponentBase'
import { PeerNode } from './../PeerNode'
import { ArkUIGeneratedNativeModule } from '#components'
import { ArkCommonMethodPeer, CommonMethod, CommonConfiguration, ArkCommonMethodComponent } from './common'
import { ResourceColor, Resource as arkui_component_units_Resource } from './units'
import { Color as arkui_component_enums_Color } from './enums'
import { Resource as global_resource_Resource } from 'global.resource'
import { ContentModifier, AttributeModifier, hookLoadingProgressContentModifier, hookLoadingProgressAttributeModifier, AttributeUpdater } from '#handwritten'
import { CallbackKind } from './../framework/peers/CallbackKind'
import { CallbackTransformer } from './../CallbackTransformer'
import { memo, memo_stable, memo_skip } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { LoadingProgressModifier } from './../LoadingProgressModifier'
import { NodeAttach, remember } from '@koalaui/runtime'
import { ModifierStateManager } from './../CommonModifier'
export class ArkLoadingProgressPeer extends ArkCommonMethodPeer {
    attributeSet?: LoadingProgressModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkLoadingProgressPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._LoadingProgress_construct(peerId, flags)
        const _peer  = new ArkLoadingProgressPeer(_peerPtr, peerId, 'LoadingProgress', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setLoadingProgressOptionsAttribute(): void {
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
        ArkUIGeneratedNativeModule._LoadingProgressInterface_setLoadingProgressOptions(this.peer.ptr)
    }
    setColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof arkui_component_enums_Color) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as arkui_component_enums_Color
                thisSerializer.writeInt32((valueTmpValueForIdx0.getOrdinal()) % (12))
            } else if (valueTmpValue instanceof int32) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as int32
                thisSerializer.writeInt32(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof arkui_component_units_Resource) {
                thisSerializer.writeInt8((3).toByte())
                const valueTmpValueForIdx3  = valueTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._LoadingProgressAttribute_setColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableLoadingAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._LoadingProgressAttribute_setEnableLoading(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export enum LoadingProgressStyle {
    Default = 0,
    Circular = 1,
    Orbital = 2,
    DEFAULT = 0,
    CIRCULAR = 1,
    ORBITAL = 2
}
export interface LoadingProgressAttribute extends CommonMethod {
    setLoadingProgressOptions(): this {
        throw new Error('Unimplemented method setLoadingProgressOptions')
    }
    color(value: ResourceColor | undefined): this {
        throw new Error('Unimplemented method color')
    }
    enableLoading(value: boolean | undefined): this {
        throw new Error('Unimplemented method enableLoading')
    }
    contentModifier(value: ContentModifier<LoadingProgressConfiguration> | undefined): this {
        throw new Error('Unimplemented method contentModifier')
    }
    attributeModifier(value: AttributeModifier<LoadingProgressAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
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
        if (this.checkPriority('setLoadingProgressOptions')) {
            this.getPeer()?.setLoadingProgressOptionsAttribute()
            this.applyOptionsFinish('LoadingProgressAttribute');
            return this
        }
        return this
    }
    public color(value: ResourceColor | undefined): this {
        if (this.checkPriority('color')) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setColorAttribute(value_casted)
            return this
        }
        return this
    }
    public enableLoading(value: boolean | undefined): this {
        if (this.checkPriority('enableLoading')) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setEnableLoadingAttribute(value_casted)
            return this
        }
        return this
    }
    public contentModifier(value: ContentModifier<LoadingProgressConfiguration> | undefined): this {
        if (this.checkPriority('contentModifier')) {
            hookLoadingProgressContentModifier(this, value)
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<LoadingProgressAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookLoadingProgressAttributeModifier(this, value);
        })
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
    public applyOptionsFinish(traceName: string): void {
        super.applyOptionsFinish(traceName)
    }
}

@memo
export function LoadingProgressImpl(
    @memo @memo_skip
    style: ((attributes: LoadingProgressAttribute) => void) | undefined,
    @memo @memo_skip
    content_?: () => void,
): void {
    const receiver = remember<ArkLoadingProgressComponent>((): ArkLoadingProgressComponent => {
        return new ArkLoadingProgressComponent()
    })
    NodeAttach<ArkLoadingProgressPeer>((): ArkLoadingProgressPeer => ArkLoadingProgressPeer.create(receiver), (_: ArkLoadingProgressPeer): void => {
        style?.(receiver)
        content_?.()
    })
}

export class LoadingProgressConfiguration_serializer {
    public static write(buffer: SerializerBase, value: LoadingProgressConfiguration): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForEnabled  = value.enabled
        valueSerializer.writeBoolean(valueHolderForEnabled)
        const valueHolderForContentModifier  = value.contentModifier
        valueSerializer.holdAndWriteObject(valueHolderForContentModifier)
        const valueHolderForEnableLoading  = value.enableLoading
        valueSerializer.writeBoolean(valueHolderForEnableLoading)
    }
    public static read(buffer: DeserializerBase): LoadingProgressConfiguration {
        let valueDeserializer : DeserializerBase = buffer
        const enabledTmpResult : boolean = valueDeserializer.readBoolean()
        const contentModifierTmpResult : ContentModifier<LoadingProgressConfiguration> = (valueDeserializer.readObject() as ContentModifier<LoadingProgressConfiguration>)
        const enableLoadingTmpResult : boolean = valueDeserializer.readBoolean()
        let value : LoadingProgressConfiguration = ({enabled: enabledTmpResult, contentModifier: contentModifierTmpResult, enableLoading: enableLoadingTmpResult} as LoadingProgressConfiguration)
        return value
    }
}
