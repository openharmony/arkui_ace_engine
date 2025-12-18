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
import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer } from '@koalaui/interop'
import { global_resource_Resource_serializer } from './../framework/resource'
import { int32, int64, float32 } from '@koalaui/common'
import { ComponentBase } from './../ComponentBase'
import { PeerNode } from './../PeerNode'
import { ArkUIGeneratedNativeModule } from '#components'
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent } from './common'
import { ResourceColor, Resource as arkui_component_units_Resource, ResourceStr as arkui_component_units_ResourceStr } from './units'
import { Color as arkui_component_enums_Color } from './enums'
import { Resource as global_resource_Resource } from 'global.resource'
import { AttributeModifier, hookQRCodeAttributeModifier, AttributeUpdater } from '#handwritten'
import { CallbackKind } from './../framework/peers/CallbackKind'
import { CallbackTransformer } from './../CallbackTransformer'
import { memo, memo_stable, memo_skip } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { QRCodeModifier } from './../QRCodeModifier'
import { NodeAttach, remember } from '@koalaui/runtime'
import { ModifierStateManager } from './../CommonModifier'
export class ArkQRCodePeer extends ArkCommonMethodPeer {
    attributeSet?: QRCodeModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkQRCodePeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._QRCode_construct(peerId, flags)
        const _peer  = new ArkQRCodePeer(_peerPtr, peerId, 'QRCode', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setQRCodeOptionsAttribute(value: arkui_component_units_ResourceStr): void {
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value instanceof string) {
            thisSerializer.writeInt8((0).toByte())
            const valueForIdx0  = value as string
            thisSerializer.writeString(valueForIdx0)
        } else if (value instanceof arkui_component_units_Resource) {
            thisSerializer.writeInt8((1).toByte())
            const valueForIdx1  = value as arkui_component_units_Resource
            global_resource_Resource_serializer.write(thisSerializer, valueForIdx1)
        }
        ArkUIGeneratedNativeModule._QRCodeInterface_setQRCodeOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
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
        ArkUIGeneratedNativeModule._QRCodeAttribute_setColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBackgroundColorAttribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._QRCodeAttribute_setBackgroundColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setContentOpacityAttribute(value: double | global_resource_Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof double) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as double
                thisSerializer.writeFloat64(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof global_resource_Resource) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as global_resource_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._QRCodeAttribute_setContentOpacity(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface QRCodeAttribute extends CommonMethod {
    setQRCodeOptions(value: arkui_component_units_ResourceStr): this {
        throw new Error('Unimplemented method setQRCodeOptions')
    }
    color(value: ResourceColor | undefined): this {
        throw new Error('Unimplemented method color')
    }
    backgroundColor(value: ResourceColor | undefined): this
    contentOpacity(value: double | global_resource_Resource | undefined): this {
        throw new Error('Unimplemented method contentOpacity')
    }
    attributeModifier(value: AttributeModifier<QRCodeAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}

export class ArkQRCodeComponent extends ArkCommonMethodComponent implements QRCodeAttribute {
    getPeer(): ArkQRCodePeer {
        return (this.peer as ArkQRCodePeer)
    }
    public setQRCodeOptions(value: arkui_component_units_ResourceStr): this {
        if (this.checkPriority('setQRCodeOptions')) {
            const value_casted = value as (arkui_component_units_ResourceStr)
            this.getPeer()?.setQRCodeOptionsAttribute(value_casted)
            this.applyOptionsFinish('QRCodeAttribute');
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
    public backgroundColor(value: ResourceColor | undefined): this {
        if (this.checkPriority('backgroundColor')) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setBackgroundColorAttribute(value_casted)
            return this
        }
        return this
    }
    public contentOpacity(value: double | global_resource_Resource | undefined): this {
        if (this.checkPriority('contentOpacity')) {
            const value_casted = value as (double | global_resource_Resource | undefined)
            this.getPeer()?.setContentOpacityAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<QRCodeAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookQRCodeAttributeModifier(this, value);
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
export function QRCodeImpl(
    @memo @memo_skip
    style: ((attributes: QRCodeAttribute) => void) | undefined,
    @memo @memo_skip
    content_?: () => void,
): void {
    const receiver = remember<ArkQRCodeComponent>((): ArkQRCodeComponent => {
        return new ArkQRCodeComponent()
    })
    NodeAttach<ArkQRCodePeer>((): ArkQRCodePeer => ArkQRCodePeer.create(receiver), (_: ArkQRCodePeer): void => {
        style?.(receiver)
        content_?.()
    })
}

