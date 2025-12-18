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
import { Resource as global_resource_Resource } from 'global.resource'
import { ResourceColor, Resource as arkui_component_units_Resource } from './units'
import { Color as arkui_component_enums_Color, FontWeight } from './enums'
import { SymbolEffectStrategy, SymbolRenderingStrategy } from './symbolglyph'
import { AttributeModifier, hookSymbolSpanAttributeModifier, AttributeUpdater } from '#handwritten'
import { CallbackKind } from './../framework/peers/CallbackKind'
import { CallbackTransformer } from './../CallbackTransformer'
import { memo, memo_stable, memo_skip } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { SymbolSpanModifier } from './../SymbolSpanModifier'
import { CommonMethod } from './common'
import { NodeAttach, remember } from '@koalaui/runtime'
import { ModifierStateManager } from './../CommonModifier'
export class ArkSymbolSpanPeer extends PeerNode {
    attributeSet?: SymbolSpanModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkSymbolSpanPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._SymbolSpan_construct(peerId, flags)
        const _peer  = new ArkSymbolSpanPeer(_peerPtr, peerId, 'SymbolSpan', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setSymbolSpanOptionsAttribute(value: global_resource_Resource): void {
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
        const thisSerializer : SerializerBase = SerializerBase.hold()
        global_resource_Resource_serializer.write(thisSerializer, value)
        ArkUIGeneratedNativeModule._SymbolSpanInterface_setSymbolSpanOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontSizeAttribute(value: double | string | global_resource_Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof double) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as double
                thisSerializer.writeFloat64(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof global_resource_Resource) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as global_resource_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SymbolSpanAttribute_setFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontColorAttribute(value: Array<ResourceColor> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeInt32((valueTmpValue.length).toInt())
            for (let valueTmpValueCounterI = 0; valueTmpValueCounterI < valueTmpValue.length; valueTmpValueCounterI++) {
                const valueTmpValueTmpElement : ResourceColor = valueTmpValue[valueTmpValueCounterI]
                if (valueTmpValueTmpElement instanceof arkui_component_enums_Color) {
                    thisSerializer.writeInt8((0).toByte())
                    const valueTmpValueTmpElementForIdx0  = valueTmpValueTmpElement as arkui_component_enums_Color
                    thisSerializer.writeInt32((valueTmpValueTmpElementForIdx0.getOrdinal()) % (12))
                } else if (valueTmpValueTmpElement instanceof int32) {
                    thisSerializer.writeInt8((1).toByte())
                    const valueTmpValueTmpElementForIdx1  = valueTmpValueTmpElement as int32
                    thisSerializer.writeInt32(valueTmpValueTmpElementForIdx1)
                } else if (valueTmpValueTmpElement instanceof string) {
                    thisSerializer.writeInt8((2).toByte())
                    const valueTmpValueTmpElementForIdx2  = valueTmpValueTmpElement as string
                    thisSerializer.writeString(valueTmpValueTmpElementForIdx2)
                } else if (valueTmpValueTmpElement instanceof arkui_component_units_Resource) {
                    thisSerializer.writeInt8((3).toByte())
                    const valueTmpValueTmpElementForIdx3  = valueTmpValueTmpElement as arkui_component_units_Resource
                    global_resource_Resource_serializer.write(thisSerializer, valueTmpValueTmpElementForIdx3)
                }
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SymbolSpanAttribute_setFontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontWeightAttribute(value: int32 | FontWeight | string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof int32) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as int32
                thisSerializer.writeInt32(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof FontWeight) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as FontWeight
                thisSerializer.writeInt32(valueTmpValueForIdx1.valueOf())
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SymbolSpanAttribute_setFontWeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEffectStrategyAttribute(value: SymbolEffectStrategy | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as SymbolEffectStrategy)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SymbolSpanAttribute_setEffectStrategy(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setRenderingStrategyAttribute(value: SymbolRenderingStrategy | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as SymbolRenderingStrategy)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SymbolSpanAttribute_setRenderingStrategy(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setKeyAttribute(value: string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeString(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SymbolSpanAttribute_setKey(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setIdAttribute(value: string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeString(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SymbolSpanAttribute_setId(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface SymbolSpanAttribute {
    setSymbolSpanOptions(value: global_resource_Resource): this {
        throw new Error('Unimplemented method setSymbolSpanOptions')
    }
    fontSize(value: double | string | global_resource_Resource | undefined): this {
        throw new Error('Unimplemented method fontSize')
    }
    fontColor(value: Array<ResourceColor> | undefined): this {
        throw new Error('Unimplemented method fontColor')
    }
    fontWeight(value: int32 | FontWeight | string | undefined): this {
        throw new Error('Unimplemented method fontWeight')
    }
    effectStrategy(value: SymbolEffectStrategy | undefined): this {
        throw new Error('Unimplemented method effectStrategy')
    }
    renderingStrategy(value: SymbolRenderingStrategy | undefined): this {
        throw new Error('Unimplemented method renderingStrategy')
    }
    key(value: string | undefined): this {
        throw new Error('Unimplemented method key')
    }
    id(value: string | undefined): this {
        throw new Error('Unimplemented method id')
    }
    attributeModifier(value: AttributeModifier<SymbolSpanAttribute> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}

export class ArkSymbolSpanComponent extends ComponentBase implements SymbolSpanAttribute {
    getPeer(): ArkSymbolSpanPeer {
        return (this.peer as ArkSymbolSpanPeer)
    }
    public setSymbolSpanOptions(value: global_resource_Resource): this {
        if (this.checkPriority('setSymbolSpanOptions')) {
            const value_casted = value as (global_resource_Resource)
            this.getPeer()?.setSymbolSpanOptionsAttribute(value_casted)
            this.applyOptionsFinish('SymbolSpanAttribute');
            return this
        }
        return this
    }
    public fontSize(value: double | string | global_resource_Resource | undefined): this {
        if (this.checkPriority('fontSize')) {
            const value_casted = value as (double | string | global_resource_Resource | undefined)
            this.getPeer()?.setFontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public fontColor(value: Array<ResourceColor> | undefined): this {
        if (this.checkPriority('fontColor')) {
            const value_casted = value as (Array<ResourceColor> | undefined)
            this.getPeer()?.setFontColorAttribute(value_casted)
            return this
        }
        return this
    }
    public fontWeight(value: int32 | FontWeight | string | undefined): this {
        if (this.checkPriority('fontWeight')) {
            const value_casted = value as (int32 | FontWeight | string | undefined)
            this.getPeer()?.setFontWeightAttribute(value_casted)
            return this
        }
        return this
    }
    public effectStrategy(value: SymbolEffectStrategy | undefined): this {
        if (this.checkPriority('effectStrategy')) {
            const value_casted = value as (SymbolEffectStrategy | undefined)
            this.getPeer()?.setEffectStrategyAttribute(value_casted)
            return this
        }
        return this
    }
    public renderingStrategy(value: SymbolRenderingStrategy | undefined): this {
        if (this.checkPriority('renderingStrategy')) {
            const value_casted = value as (SymbolRenderingStrategy | undefined)
            this.getPeer()?.setRenderingStrategyAttribute(value_casted)
            return this
        }
        return this
    }
    public key(value: string | undefined): this {
        if (this.checkPriority('key')) {
            const value_casted = value as (string | undefined)
            this.getPeer()?.setKeyAttribute(value_casted)
            return this
        }
        return this
    }
    public id(value: string | undefined): this {
        if (this.checkPriority('id')) {
            const value_casted = value as (string | undefined)
            this.getPeer()?.setIdAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<SymbolSpanAttribute> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookSymbolSpanAttributeModifier(this, value);
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
export function SymbolSpanImpl(
    @memo @memo_skip
    style: ((attributes: SymbolSpanAttribute) => void) | undefined,
    @memo @memo_skip
    content_?: () => void,
): void {
    const receiver = remember<ArkSymbolSpanComponent>((): ArkSymbolSpanComponent => {
        return new ArkSymbolSpanComponent()
    })
    NodeAttach<ArkSymbolSpanPeer>((): ArkSymbolSpanPeer => ArkSymbolSpanPeer.create(receiver), (_: ArkSymbolSpanPeer): void => {
        style?.(receiver)
        content_?.()
    })
}

