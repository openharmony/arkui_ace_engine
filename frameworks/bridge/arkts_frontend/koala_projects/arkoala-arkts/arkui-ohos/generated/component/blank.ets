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
import { ResourceColor, Resource as arkui_component_units_Resource } from './units'
import { Color as arkui_component_enums_Color } from './enums'
import { Resource as global_resource_Resource } from 'global.resource'
import { AttributeModifier, hookBlankAttributeModifier, AttributeUpdater } from '#handwritten'
import { CallbackKind } from './../framework/peers/CallbackKind'
import { CallbackTransformer } from './../CallbackTransformer'
import { memo, memo_stable, memo_skip } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { BlankModifier } from './../BlankModifier'
import { NodeAttach, remember } from '@koalaui/runtime'
import { ModifierStateManager } from './../CommonModifier'
export class ArkBlankPeer extends ArkCommonMethodPeer {
    attributeSet?: BlankModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkBlankPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Blank_construct(peerId, flags)
        const _peer  = new ArkBlankPeer(_peerPtr, peerId, 'Blank', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setBlankOptionsAttribute(min?: double | string): void {
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (min !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const minTmpValue  = min!
            if (minTmpValue instanceof double) {
                thisSerializer.writeInt8((0).toByte())
                const minTmpValueForIdx0  = minTmpValue as double
                thisSerializer.writeFloat64(minTmpValueForIdx0)
            } else if (minTmpValue instanceof string) {
                thisSerializer.writeInt8((1).toByte())
                const minTmpValueForIdx1  = minTmpValue as string
                thisSerializer.writeString(minTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._BlankInterface_setBlankOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._BlankAttribute_setColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface BlankAttribute extends CommonMethod {
    setBlankOptions(min?: double | string): this {
        throw new Error('Unimplemented method setBlankOptions')
    }
    color(value: ResourceColor | undefined): this {
        throw new Error('Unimplemented method color')
    }
    attributeModifier(value: AttributeModifier<BlankAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}

export class ArkBlankComponent extends ArkCommonMethodComponent implements BlankAttribute {
    getPeer(): ArkBlankPeer {
        return (this.peer as ArkBlankPeer)
    }
    public setBlankOptions(min?: double | string): this {
        if (this.checkPriority('setBlankOptions')) {
            const min_casted = min as (double | string | undefined)
            this.getPeer()?.setBlankOptionsAttribute(min_casted)
            this.applyOptionsFinish('BlankAttribute');
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
    public attributeModifier(value: AttributeModifier<BlankAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookBlankAttributeModifier(this, value);
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
export function BlankImpl(
    @memo @memo_skip
    style: ((attributes: BlankAttribute) => void) | undefined,
    @memo @memo_skip
    content_?: () => void,
): void {
    const receiver = remember<ArkBlankComponent>((): ArkBlankComponent => {
        return new ArkBlankComponent()
    })
    NodeAttach<ArkBlankPeer>((): ArkBlankPeer => ArkBlankPeer.create(receiver), (_: ArkBlankPeer): void => {
        style?.(receiver)
        content_?.()
    })
}

