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

import { SerializerBase, DeserializerBase, Finalizable, RuntimeType, toPeerPtr, KPointer, MaterializedBase, MaterializedBaseTag, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from '@koalaui/interop'
import { global_resource_Resource_serializer } from './../framework/resource'
import { SymbolGlyphModifier_serializer } from './../framework/SymbolGlyphModifier'
import { CommonConfiguration, Bindable_I32_serializer, Bindable_Resource_serializer, Bindable_String_serializer, ArkCommonMethodPeer, CommonMethod, Bindable, BlurStyle, ArkCommonMethodComponent } from './common'
import { ResourceStr as arkui_component_units_ResourceStr, Resource as arkui_component_units_Resource, arkui_component_units_Font_serializer, DividerStyleOptions_serializer, Offset_serializer, Font as arkui_component_units_Font, ResourceColor, Length, Dimension, DividerStyleOptions, Offset, EdgeOutlineWidths, EdgeColors, EdgeOutlineWidths_serializer, EdgeColors_serializer } from './units'
import { Resource as global_resource_Resource } from 'global.resource'
import { extractors, ContentModifier, AttributeModifier, hookSelectContentModifier, hookSelectSetDividerMethod, hookSelectAttributeModifier, AttributeUpdater } from '#handwritten'
import { SymbolGlyphModifier } from '@arkui.SymbolGlyphModifier'
import { unsafeCast, int32, int64, float32 } from '@koalaui/common'
import { ArkUIGeneratedNativeModule } from '#components'
import { CallbackTransformer } from './../CallbackTransformer'
import { ArkThemeScopeManager } from '#arktheme'
import { TextModifier_serializer } from './../framework/TextModifier'
import { ComponentBase } from './../ComponentBase'
import { PeerNode } from './../PeerNode'
import { Color as arkui_component_enums_Color, OptionWidthMode } from './enums'
import { ControlSize } from './button'
import { DividerOptions } from './textPicker'
import { TextModifier } from 'arkui.TextModifier'
import { CallbackKind } from './../framework/peers/CallbackKind'
import { memo, memo_stable, memo_skip } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { SelectModifier } from './../SelectModifier'
import { NodeAttach, remember } from '@koalaui/runtime'
import { ModifierStateManager } from './../CommonModifier'
export interface MenuItemConfiguration {
    enabled: boolean
    contentModifier: ContentModifier<MenuItemConfiguration>
    value: arkui_component_units_ResourceStr
    icon?: arkui_component_units_ResourceStr | undefined
    symbolIcon?: SymbolGlyphModifier | undefined
    selected: boolean
    index: int32
    triggerSelect(index: int32, value: string): void
}
export class MenuItemConfigurationInternal implements MaterializedBase,CommonConfiguration<MenuItemConfiguration>,MenuItemConfiguration {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    public enabled: boolean
    public contentModifier: ContentModifier<MenuItemConfiguration>
    public value: arkui_component_units_ResourceStr
    public icon?: arkui_component_units_ResourceStr | undefined
    public symbolIcon?: SymbolGlyphModifier | undefined
    public selected: boolean
    public index: int32
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, MenuItemConfigurationInternal.getFinalizer())
        this.enabled = this.getEnabled()
        this.contentModifier = this.getContentModifier()
        this.value = this.getValue()
        this.icon = this.getIcon()
        this.symbolIcon = this.getSymbolIcon()
        this.selected = this.getSelected()
        this.index = this.getIndex()
    }
    constructor() {
        this(MaterializedBaseTag.NOP, MenuItemConfigurationInternal.construct())
        this.enabled = this.getEnabled()
        this.contentModifier = this.getContentModifier()
        this.value = this.getValue()
        this.icon = this.getIcon()
        this.symbolIcon = this.getSymbolIcon()
        this.selected = this.getSelected()
        this.index = this.getIndex()
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._MenuItemConfiguration_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._MenuItemConfiguration_getFinalizer()
    }
    public static fromPtr(ptr: KPointer): MenuItemConfigurationInternal {
        return new MenuItemConfigurationInternal(MaterializedBaseTag.NOP, ptr)
    }
    public triggerSelect(index: int32, value: string): void {
        const index_casted = index as (int32)
        const value_casted = value as (string)
        this.triggerSelect_serialize(index_casted, value_casted)
        return
    }
    private getEnabled(): boolean {
        return this.getEnabled_serialize()
    }
    private setEnabled(enabled: boolean): void {
        const enabled_casted = enabled as (boolean)
        this.setEnabled_serialize(enabled_casted)
        return
    }
    private getContentModifier(): ContentModifier<MenuItemConfiguration> {
        return this.getContentModifier_serialize()
    }
    private setContentModifier(contentModifier: ContentModifier<MenuItemConfiguration>): void {
        const contentModifier_casted = contentModifier as (ContentModifier<MenuItemConfiguration>)
        this.setContentModifier_serialize(contentModifier_casted)
        return
    }
    private getValue(): arkui_component_units_ResourceStr {
        return this.getValue_serialize()
    }
    private setValue(value: arkui_component_units_ResourceStr): void {
        const value_casted = value as (arkui_component_units_ResourceStr)
        this.setValue_serialize(value_casted)
        return
    }
    private getIcon(): arkui_component_units_ResourceStr | undefined {
        return this.getIcon_serialize()
    }
    private setIcon(icon: arkui_component_units_ResourceStr | undefined): void {
        const icon_casted = icon as (arkui_component_units_ResourceStr | undefined)
        this.setIcon_serialize(icon_casted)
        return
    }
    private getSymbolIcon(): SymbolGlyphModifier | undefined {
        return this.getSymbolIcon_serialize()
    }
    private setSymbolIcon(symbolIcon: SymbolGlyphModifier | undefined): void {
        const symbolIcon_casted = symbolIcon as (SymbolGlyphModifier | undefined)
        this.setSymbolIcon_serialize(symbolIcon_casted)
        return
    }
    private getSelected(): boolean {
        return this.getSelected_serialize()
    }
    private setSelected(selected: boolean): void {
        const selected_casted = selected as (boolean)
        this.setSelected_serialize(selected_casted)
        return
    }
    private getIndex(): int32 {
        return this.getIndex_serialize()
    }
    private setIndex(index: int32): void {
        const index_casted = index as (int32)
        this.setIndex_serialize(index_casted)
        return
    }
    private triggerSelect_serialize(index: int32, value: string): void {
        ArkUIGeneratedNativeModule._MenuItemConfiguration_triggerSelect(this.peer!.ptr, index, value)
    }
    private getEnabled_serialize(): boolean {
        const retval  = ArkUIGeneratedNativeModule._MenuItemConfiguration_getEnabled(this.peer!.ptr)
        return retval
    }
    private setEnabled_serialize(enabled: boolean): void {
        ArkUIGeneratedNativeModule._MenuItemConfiguration_setEnabled(this.peer!.ptr, enabled ? true : false)
    }
    private getContentModifier_serialize(): ContentModifier<MenuItemConfiguration> {
        const retval  = ArkUIGeneratedNativeModule._MenuItemConfiguration_getContentModifier(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : ContentModifier<MenuItemConfiguration> = (retvalDeserializer.readObject() as ContentModifier<MenuItemConfiguration>)
        return returnResult
    }
    private setContentModifier_serialize(contentModifier: ContentModifier<MenuItemConfiguration>): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(contentModifier)
        ArkUIGeneratedNativeModule._MenuItemConfiguration_setContentModifier(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getValue_serialize(): arkui_component_units_ResourceStr {
        const retval  = ArkUIGeneratedNativeModule._MenuItemConfiguration_getValue(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const bufferUnionSelector : int32 = retvalDeserializer.readInt8()
        let buffer : string | arkui_component_units_Resource | undefined
        if (bufferUnionSelector == (0).toByte()) {
            buffer = (retvalDeserializer.readString() as string)
        } else if (bufferUnionSelector == (1).toByte()) {
            buffer = global_resource_Resource_serializer.read(retvalDeserializer)
        } else {
            throw new Error('One of the branches for buffer has to be chosen through deserialisation.')
        }
        const returnResult : arkui_component_units_ResourceStr = (buffer as string | arkui_component_units_Resource)
        return returnResult
    }
    private setValue_serialize(value: arkui_component_units_ResourceStr): void {
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
        ArkUIGeneratedNativeModule._MenuItemConfiguration_setValue(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getIcon_serialize(): arkui_component_units_ResourceStr | undefined {
        const retval  = ArkUIGeneratedNativeModule._MenuItemConfiguration_getIcon(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8()!.toInt()
        let buffer : arkui_component_units_ResourceStr | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            const bufferOptUnionSelector : int32 = retvalDeserializer.readInt8()
            let bufferOpt : string | arkui_component_units_Resource | undefined
            if (bufferOptUnionSelector == (0).toByte()) {
                bufferOpt = (retvalDeserializer.readString() as string)
            } else if (bufferOptUnionSelector == (1).toByte()) {
                bufferOpt = global_resource_Resource_serializer.read(retvalDeserializer)
            } else {
                throw new Error('One of the branches for bufferOpt has to be chosen through deserialisation.')
            }
            buffer = (bufferOpt as string | arkui_component_units_Resource)
        }
        const returnResult : arkui_component_units_ResourceStr | undefined = buffer
        return returnResult
    }
    private setIcon_serialize(icon: arkui_component_units_ResourceStr | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (icon !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const iconTmpValue  = icon!
            if (iconTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const iconTmpValueForIdx0  = iconTmpValue as string
                thisSerializer.writeString(iconTmpValueForIdx0)
            } else if (iconTmpValue instanceof arkui_component_units_Resource) {
                thisSerializer.writeInt8((1).toByte())
                const iconTmpValueForIdx1  = iconTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(thisSerializer, iconTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._MenuItemConfiguration_setIcon(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getSymbolIcon_serialize(): SymbolGlyphModifier | undefined {
        const retval  = ArkUIGeneratedNativeModule._MenuItemConfiguration_getSymbolIcon(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8()!.toInt()
        let buffer : SymbolGlyphModifier | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = (SymbolGlyphModifier_serializer.read(retvalDeserializer) as SymbolGlyphModifier)
        }
        const returnResult : SymbolGlyphModifier | undefined = buffer
        return returnResult
    }
    private setSymbolIcon_serialize(symbolIcon: SymbolGlyphModifier | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (symbolIcon !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const symbolIconTmpValue  = symbolIcon!
            SymbolGlyphModifier_serializer.write(thisSerializer, symbolIconTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._MenuItemConfiguration_setSymbolIcon(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getSelected_serialize(): boolean {
        const retval  = ArkUIGeneratedNativeModule._MenuItemConfiguration_getSelected(this.peer!.ptr)
        return retval
    }
    private setSelected_serialize(selected: boolean): void {
        ArkUIGeneratedNativeModule._MenuItemConfiguration_setSelected(this.peer!.ptr, selected ? true : false)
    }
    private getIndex_serialize(): int32 {
        const retval  = ArkUIGeneratedNativeModule._MenuItemConfiguration_getIndex(this.peer!.ptr)
        return retval
    }
    private setIndex_serialize(index: int32): void {
        ArkUIGeneratedNativeModule._MenuItemConfiguration_setIndex(this.peer!.ptr, index)
    }
}
export class ArkSelectPeer extends ArkCommonMethodPeer {
    attributeSet?: SelectModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkSelectPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Select_construct(peerId, flags)
        const _peer  = new ArkSelectPeer(_peerPtr, peerId, 'Select', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setSelectOptionsAttribute(options: Array<SelectOption>): void {
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.writeInt32((options.length).toInt())
        for (let optionsCounterI = 0; optionsCounterI < options.length; optionsCounterI++) {
            const optionsTmpElement : SelectOption = options[optionsCounterI]
            SelectOption_serializer.write(thisSerializer, optionsTmpElement)
        }
        ArkUIGeneratedNativeModule._SelectInterface_setSelectOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectedAttribute(value: int32 | arkui_component_units_Resource | Bindable<int32> | Bindable<global_resource_Resource> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof int32) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as int32
                thisSerializer.writeInt32(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof arkui_component_units_Resource) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Bindable) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as Bindable<int32>
                Bindable_I32_serializer.write(thisSerializer, valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof Bindable) {
                thisSerializer.writeInt8((3).toByte())
                const valueTmpValueForIdx3  = valueTmpValue as Bindable<global_resource_Resource>
                Bindable_Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setSelected(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setValueAttribute(value: arkui_component_units_ResourceStr | Bindable<string> | Bindable<global_resource_Resource> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof arkui_component_units_ResourceStr) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as arkui_component_units_ResourceStr
                if (valueTmpValueForIdx0 instanceof string) {
                    thisSerializer.writeInt8((0).toByte())
                    const valueTmpValueForIdx0ForIdx0  = valueTmpValueForIdx0 as string
                    thisSerializer.writeString(valueTmpValueForIdx0ForIdx0)
                } else if (valueTmpValueForIdx0 instanceof arkui_component_units_Resource) {
                    thisSerializer.writeInt8((1).toByte())
                    const valueTmpValueForIdx0ForIdx1  = valueTmpValueForIdx0 as arkui_component_units_Resource
                    global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx0ForIdx1)
                }
            } else if (valueTmpValue instanceof Bindable) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as Bindable<string>
                Bindable_String_serializer.write(thisSerializer, valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Bindable) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as Bindable<global_resource_Resource>
                Bindable_Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setValue(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontAttribute(value: arkui_component_units_Font | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            arkui_component_units_Font_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontColorAttribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._SelectAttribute_setFontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectedOptionBgColorAttribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._SelectAttribute_setSelectedOptionBgColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectedOptionFontAttribute(value: arkui_component_units_Font | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            arkui_component_units_Font_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setSelectedOptionFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectedOptionFontColorAttribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._SelectAttribute_setSelectedOptionFontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOptionBgColorAttribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._SelectAttribute_setOptionBgColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOptionFontAttribute(value: arkui_component_units_Font | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            arkui_component_units_Font_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setOptionFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOptionFontColorAttribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._SelectAttribute_setOptionFontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnSelectAttribute(value: OnSelectCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setOnSelect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSpaceAttribute(value: Length | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof double) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as double
                thisSerializer.writeFloat64(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof arkui_component_units_Resource) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setSpace(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setArrowPositionAttribute(value: ArrowPosition | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as ArrowPosition)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setArrowPosition(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOptionWidthAttribute(value: Dimension | OptionWidthMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof Dimension) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as Dimension
                if (valueTmpValueForIdx0 instanceof string) {
                    thisSerializer.writeInt8((0).toByte())
                    const valueTmpValueForIdx0ForIdx0  = valueTmpValueForIdx0 as string
                    thisSerializer.writeString(valueTmpValueForIdx0ForIdx0)
                } else if (valueTmpValueForIdx0 instanceof number) {
                    thisSerializer.writeInt8((1).toByte())
                    const valueTmpValueForIdx0ForIdx1  = valueTmpValueForIdx0 as number
                    thisSerializer.writeNumber(valueTmpValueForIdx0ForIdx1)
                } else if (valueTmpValueForIdx0 instanceof global_resource_Resource) {
                    thisSerializer.writeInt8((2).toByte())
                    const valueTmpValueForIdx0ForIdx2  = valueTmpValueForIdx0 as global_resource_Resource
                    global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx0ForIdx2)
                }
            } else if (valueTmpValue instanceof OptionWidthMode) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as OptionWidthMode
                thisSerializer.writeInt32(valueTmpValueForIdx1.getOrdinal())
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setOptionWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOptionHeightAttribute(value: Dimension | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof global_resource_Resource) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as global_resource_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setOptionHeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMenuBackgroundColorAttribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._SelectAttribute_setMenuBackgroundColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMenuBackgroundBlurStyleAttribute(value: BlurStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as BlurStyle)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setMenuBackgroundBlurStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setControlSizeAttribute(value: ControlSize | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as ControlSize)
            thisSerializer.writeInt32(valueTmpValue.getOrdinal())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setControlSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTextModifierAttribute(value: TextModifier | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            TextModifier_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setTextModifier(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setArrowModifierAttribute(value: SymbolGlyphModifier | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            SymbolGlyphModifier_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setArrowModifier(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOptionTextModifierAttribute(value: TextModifier | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            TextModifier_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setOptionTextModifier(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectedOptionTextModifierAttribute(value: TextModifier | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            TextModifier_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setSelectedOptionTextModifier(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDividerStyleAttribute(value: DividerStyleOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            DividerStyleOptions_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setDividerStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAvoidanceAttribute(value: AvoidanceMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as AvoidanceMode)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setAvoidance(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMenuOutlineAttribute(value: MenuOutlineOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            MenuOutlineOptions_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setMenuOutline(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMenuAlignAttribute(alignType: MenuAlignType | undefined, offset?: Offset): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (alignType !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const alignTypeTmpValue  = (alignType as MenuAlignType)
            thisSerializer.writeInt32(alignTypeTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (offset !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const offsetTmpValue  = offset!
            Offset_serializer.write(thisSerializer, offsetTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_setMenuAlign(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface SelectOption {
    value: arkui_component_units_ResourceStr;
    icon?: arkui_component_units_ResourceStr;
    symbolIcon?: SymbolGlyphModifier;
}
export enum ArrowPosition {
    END = 0,
    START = 1
}
export enum MenuAlignType {
    START = 0,
    CENTER = 1,
    END = 2
}
export enum AvoidanceMode {
    COVER_TARGET = 0,
    AVOID_AROUND_TARGET = 1
}
export type OnSelectCallback = (index: int32, selectStr: string) => void;
export interface MenuOutlineOptions {
    width?: Dimension | EdgeOutlineWidths;
    color?: ResourceColor | EdgeColors;
}
export interface SelectAttribute extends CommonMethod {
    setSelectOptions(options: Array<SelectOption>): this {
        throw new Error('Unimplemented method setSelectOptions')
    }
    selected(value: int32 | arkui_component_units_Resource | Bindable<int32> | Bindable<global_resource_Resource> | undefined): this {
        throw new Error('Unimplemented method selected')
    }
    value(value: arkui_component_units_ResourceStr | Bindable<string> | Bindable<global_resource_Resource> | undefined): this {
        throw new Error('Unimplemented method value')
    }
    font(value: arkui_component_units_Font | undefined): this {
        throw new Error('Unimplemented method font')
    }
    fontColor(value: ResourceColor | undefined): this {
        throw new Error('Unimplemented method fontColor')
    }
    selectedOptionBgColor(value: ResourceColor | undefined): this {
        throw new Error('Unimplemented method selectedOptionBgColor')
    }
    selectedOptionFont(value: arkui_component_units_Font | undefined): this {
        throw new Error('Unimplemented method selectedOptionFont')
    }
    selectedOptionFontColor(value: ResourceColor | undefined): this {
        throw new Error('Unimplemented method selectedOptionFontColor')
    }
    optionBgColor(value: ResourceColor | undefined): this {
        throw new Error('Unimplemented method optionBgColor')
    }
    optionFont(value: arkui_component_units_Font | undefined): this {
        throw new Error('Unimplemented method optionFont')
    }
    optionFontColor(value: ResourceColor | undefined): this {
        throw new Error('Unimplemented method optionFontColor')
    }
    onSelect(value: OnSelectCallback | undefined): this {
        throw new Error('Unimplemented method onSelect')
    }
    space(value: Length | undefined): this {
        throw new Error('Unimplemented method space')
    }
    arrowPosition(value: ArrowPosition | undefined): this {
        throw new Error('Unimplemented method arrowPosition')
    }
    optionWidth(value: Dimension | OptionWidthMode | undefined): this {
        throw new Error('Unimplemented method optionWidth')
    }
    optionHeight(value: Dimension | undefined): this {
        throw new Error('Unimplemented method optionHeight')
    }
    menuBackgroundColor(value: ResourceColor | undefined): this {
        throw new Error('Unimplemented method menuBackgroundColor')
    }
    menuBackgroundBlurStyle(value: BlurStyle | undefined): this {
        throw new Error('Unimplemented method menuBackgroundBlurStyle')
    }
    controlSize(value: ControlSize | undefined): this {
        throw new Error('Unimplemented method controlSize')
    }
    menuItemContentModifier(value: ContentModifier<MenuItemConfiguration> | undefined): this {
        throw new Error('Unimplemented method menuItemContentModifier')
    }
    divider(value: DividerOptions | null | undefined): this {
        throw new Error('Unimplemented method divider')
    }
    textModifier(value: TextModifier | undefined): this {
        throw new Error('Unimplemented method textModifier')
    }
    arrowModifier(value: SymbolGlyphModifier | undefined): this {
        throw new Error('Unimplemented method arrowModifier')
    }
    optionTextModifier(value: TextModifier | undefined): this {
        throw new Error('Unimplemented method optionTextModifier')
    }
    selectedOptionTextModifier(value: TextModifier | undefined): this {
        throw new Error('Unimplemented method selectedOptionTextModifier')
    }
    dividerStyle(value: DividerStyleOptions | undefined): this {
        throw new Error('Unimplemented method dividerStyle')
    }
    avoidance(value: AvoidanceMode | undefined): this {
        throw new Error('Unimplemented method avoidance')
    }
    menuOutline(value: MenuOutlineOptions | undefined): this {
        throw new Error('Unimplemented method menuOutline')
    }
    menuAlign(alignType: MenuAlignType | undefined, offset?: Offset): this {
        throw new Error('Unimplemented method menuAlign')
    }
    attributeModifier(value: AttributeModifier<SelectAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}

export class ArkSelectComponent extends ArkCommonMethodComponent implements SelectAttribute {
    getPeer(): ArkSelectPeer {
        return (this.peer as ArkSelectPeer)
    }
    public setSelectOptions(options: Array<SelectOption>): this {
        if (this.checkPriority('setSelectOptions')) {
            const options_casted = options as (Array<SelectOption>)
            this.getPeer()?.setSelectOptionsAttribute(options_casted)
            this.applyOptionsFinish('SelectAttribute');
            return this
        }
        return this
    }
    public selected(value: int32 | arkui_component_units_Resource | Bindable<int32> | Bindable<global_resource_Resource> | undefined): this {
        if (this.checkPriority('selected')) {
            const value_casted = value as (int32 | arkui_component_units_Resource | Bindable<int32> | Bindable<global_resource_Resource> | undefined)
            this.getPeer()?.setSelectedAttribute(value_casted)
            return this
        }
        return this
    }
    public value(value: arkui_component_units_ResourceStr | Bindable<string> | Bindable<global_resource_Resource> | undefined): this {
        if (this.checkPriority('value')) {
            const value_casted = value as (arkui_component_units_ResourceStr | Bindable<string> | Bindable<global_resource_Resource> | undefined)
            this.getPeer()?.setValueAttribute(value_casted)
            return this
        }
        return this
    }
    public font(value: arkui_component_units_Font | undefined): this {
        if (this.checkPriority('font')) {
            const value_casted = value as (arkui_component_units_Font | undefined)
            this.getPeer()?.setFontAttribute(value_casted)
            return this
        }
        return this
    }
    public fontColor(value: ResourceColor | undefined): this {
        if (this.checkPriority('fontColor')) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setFontColorAttribute(value_casted)
            return this
        }
        return this
    }
    public selectedOptionBgColor(value: ResourceColor | undefined): this {
        if (this.checkPriority('selectedOptionBgColor')) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setSelectedOptionBgColorAttribute(value_casted)
            return this
        }
        return this
    }
    public selectedOptionFont(value: arkui_component_units_Font | undefined): this {
        if (this.checkPriority('selectedOptionFont')) {
            const value_casted = value as (arkui_component_units_Font | undefined)
            this.getPeer()?.setSelectedOptionFontAttribute(value_casted)
            return this
        }
        return this
    }
    public selectedOptionFontColor(value: ResourceColor | undefined): this {
        if (this.checkPriority('selectedOptionFontColor')) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setSelectedOptionFontColorAttribute(value_casted)
            return this
        }
        return this
    }
    public optionBgColor(value: ResourceColor | undefined): this {
        if (this.checkPriority('optionBgColor')) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setOptionBgColorAttribute(value_casted)
            return this
        }
        return this
    }
    public optionFont(value: arkui_component_units_Font | undefined): this {
        if (this.checkPriority('optionFont')) {
            const value_casted = value as (arkui_component_units_Font | undefined)
            this.getPeer()?.setOptionFontAttribute(value_casted)
            return this
        }
        return this
    }
    public optionFontColor(value: ResourceColor | undefined): this {
        if (this.checkPriority('optionFontColor')) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setOptionFontColorAttribute(value_casted)
            return this
        }
        return this
    }
    public onSelect(value: OnSelectCallback | undefined): this {
        if (this.checkPriority('onSelect')) {
            const value_casted = value as (OnSelectCallback | undefined)
            this.getPeer()?.setOnSelectAttribute(value_casted)
            return this
        }
        return this
    }
    public space(value: Length | undefined): this {
        if (this.checkPriority('space')) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.setSpaceAttribute(value_casted)
            return this
        }
        return this
    }
    public arrowPosition(value: ArrowPosition | undefined): this {
        if (this.checkPriority('arrowPosition')) {
            const value_casted = value as (ArrowPosition | undefined)
            this.getPeer()?.setArrowPositionAttribute(value_casted)
            return this
        }
        return this
    }
    public optionWidth(value: Dimension | OptionWidthMode | undefined): this {
        if (this.checkPriority('optionWidth')) {
            const value_casted = value as (Dimension | OptionWidthMode | undefined)
            this.getPeer()?.setOptionWidthAttribute(value_casted)
            return this
        }
        return this
    }
    public optionHeight(value: Dimension | undefined): this {
        if (this.checkPriority('optionHeight')) {
            const value_casted = value as (Dimension | undefined)
            this.getPeer()?.setOptionHeightAttribute(value_casted)
            return this
        }
        return this
    }
    public menuBackgroundColor(value: ResourceColor | undefined): this {
        if (this.checkPriority('menuBackgroundColor')) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setMenuBackgroundColorAttribute(value_casted)
            return this
        }
        return this
    }
    public menuBackgroundBlurStyle(value: BlurStyle | undefined): this {
        if (this.checkPriority('menuBackgroundBlurStyle')) {
            const value_casted = value as (BlurStyle | undefined)
            this.getPeer()?.setMenuBackgroundBlurStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public controlSize(value: ControlSize | undefined): this {
        if (this.checkPriority('controlSize')) {
            const value_casted = value as (ControlSize | undefined)
            this.getPeer()?.setControlSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public menuItemContentModifier(value: ContentModifier<MenuItemConfiguration> | undefined): this {
        if (this.checkPriority('menuItemContentModifier')) {
            hookSelectContentModifier(this, value)
        }
        return this
    }
    public divider(value: DividerOptions | null | undefined): this {
        if (this.checkPriority('divider')) {
            hookSelectSetDividerMethod(this, value)
        }
        return this
    }
    public textModifier(value: TextModifier | undefined): this {
        if (this.checkPriority('textModifier')) {
            const value_casted = value as (TextModifier | undefined)
            this.getPeer()?.setTextModifierAttribute(value_casted)
            return this
        }
        return this
    }
    public arrowModifier(value: SymbolGlyphModifier | undefined): this {
        if (this.checkPriority('arrowModifier')) {
            const value_casted = value as (SymbolGlyphModifier | undefined)
            this.getPeer()?.setArrowModifierAttribute(value_casted)
            return this
        }
        return this
    }
    public optionTextModifier(value: TextModifier | undefined): this {
        if (this.checkPriority('optionTextModifier')) {
            const value_casted = value as (TextModifier | undefined)
            this.getPeer()?.setOptionTextModifierAttribute(value_casted)
            return this
        }
        return this
    }
    public selectedOptionTextModifier(value: TextModifier | undefined): this {
        if (this.checkPriority('selectedOptionTextModifier')) {
            const value_casted = value as (TextModifier | undefined)
            this.getPeer()?.setSelectedOptionTextModifierAttribute(value_casted)
            return this
        }
        return this
    }
    public dividerStyle(value: DividerStyleOptions | undefined): this {
        if (this.checkPriority('dividerStyle')) {
            const value_casted = value as (DividerStyleOptions | undefined)
            this.getPeer()?.setDividerStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public avoidance(value: AvoidanceMode | undefined): this {
        if (this.checkPriority('avoidance')) {
            const value_casted = value as (AvoidanceMode | undefined)
            this.getPeer()?.setAvoidanceAttribute(value_casted)
            return this
        }
        return this
    }
    public menuOutline(value: MenuOutlineOptions | undefined): this {
        if (this.checkPriority('menuOutline')) {
            const value_casted = value as (MenuOutlineOptions | undefined)
            this.getPeer()?.setMenuOutlineAttribute(value_casted)
            return this
        }
        return this
    }
    public menuAlign(alignType: MenuAlignType | undefined, offset?: Offset): this {
        if (this.checkPriority('menuAlign')) {
            const alignType_casted = alignType as (MenuAlignType | undefined)
            const offset_casted = offset as (Offset | undefined)
            this.getPeer()?.setMenuAlignAttribute(alignType_casted, offset_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<SelectAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookSelectAttributeModifier(this, value);
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
export function SelectImpl(
    @memo @memo_skip
    style: ((attributes: SelectAttribute) => void) | undefined,
    @memo @memo_skip
    content_?: () => void,
): void {
    const receiver = remember<ArkSelectComponent>((): ArkSelectComponent => {
        return new ArkSelectComponent()
    })
    NodeAttach<ArkSelectPeer>((): ArkSelectPeer => ArkSelectPeer.create(receiver), (_: ArkSelectPeer): void => {
        style?.(receiver)
        content_?.()
    })
}

export class MenuItemConfiguration_serializer {
    public static write(buffer: SerializerBase, value: MenuItemConfiguration): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): MenuItemConfiguration {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return MenuItemConfigurationInternal.fromPtr(ptr)
    }
}
export class SelectOption_serializer {
    public static write(buffer: SerializerBase, value: SelectOption): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForValue  = value.value
        if (valueHolderForValue instanceof string) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForValueForIdx0  = valueHolderForValue as string
            valueSerializer.writeString(valueHolderForValueForIdx0)
        } else if (valueHolderForValue instanceof arkui_component_units_Resource) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForValueForIdx1  = valueHolderForValue as arkui_component_units_Resource
            global_resource_Resource_serializer.write(valueSerializer, valueHolderForValueForIdx1)
        }
        const valueHolderForIcon  = value.icon
        if (valueHolderForIcon !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForIconTmpValue  = valueHolderForIcon!
            if (valueHolderForIconTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForIconTmpValueForIdx0  = valueHolderForIconTmpValue as string
                valueSerializer.writeString(valueHolderForIconTmpValueForIdx0)
            } else if (valueHolderForIconTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForIconTmpValueForIdx1  = valueHolderForIconTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForIconTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSymbolIcon  = value.symbolIcon
        if (valueHolderForSymbolIcon !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSymbolIconTmpValue  = valueHolderForSymbolIcon!
            SymbolGlyphModifier_serializer.write(valueSerializer, valueHolderForSymbolIconTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): SelectOption {
        let valueDeserializer : DeserializerBase = buffer
        const valueTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let valueTmpBuf : string | arkui_component_units_Resource | undefined
        if (valueTmpBufUnionSelector == (0).toByte()) {
            valueTmpBuf = (valueDeserializer.readString() as string)
        } else if (valueTmpBufUnionSelector == (1).toByte()) {
            valueTmpBuf = global_resource_Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error('One of the branches for valueTmpBuf has to be chosen through deserialisation.')
        }
        const valueTmpResult : arkui_component_units_ResourceStr = (valueTmpBuf as string | arkui_component_units_Resource)
        const iconTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let iconTmpBuf : arkui_component_units_ResourceStr | undefined = undefined
        if ((iconTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const iconTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let iconTmpBufOpt : string | arkui_component_units_Resource | undefined
            if (iconTmpBufOptUnionSelector == (0).toByte()) {
                iconTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (iconTmpBufOptUnionSelector == (1).toByte()) {
                iconTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for iconTmpBufOpt has to be chosen through deserialisation.')
            }
            iconTmpBuf = (iconTmpBufOpt as string | arkui_component_units_Resource)
        }
        const iconTmpResult : arkui_component_units_ResourceStr | undefined = iconTmpBuf
        const symbolIconTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let symbolIconTmpBuf : SymbolGlyphModifier | undefined = undefined
        if ((symbolIconTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            symbolIconTmpBuf = (SymbolGlyphModifier_serializer.read(valueDeserializer) as SymbolGlyphModifier)
        }
        const symbolIconTmpResult : SymbolGlyphModifier | undefined = symbolIconTmpBuf
        let value : SelectOption = ({value: valueTmpResult, icon: iconTmpResult, symbolIcon: symbolIconTmpResult} as SelectOption)
        return value
    }
}
export class MenuOutlineOptions_serializer {
    public static write(buffer: SerializerBase, value: MenuOutlineOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForWidth  = value.width
        if (valueHolderForWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForWidthTmpValue  = valueHolderForWidth!
            if (valueHolderForWidthTmpValue instanceof Dimension) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForWidthTmpValueForIdx0  = valueHolderForWidthTmpValue as Dimension
                if (valueHolderForWidthTmpValueForIdx0 instanceof string) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForWidthTmpValueForIdx0ForIdx0  = valueHolderForWidthTmpValueForIdx0 as string
                    valueSerializer.writeString(valueHolderForWidthTmpValueForIdx0ForIdx0)
                } else if (valueHolderForWidthTmpValueForIdx0 instanceof number) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForWidthTmpValueForIdx0ForIdx1  = valueHolderForWidthTmpValueForIdx0 as number
                    valueSerializer.writeNumber(valueHolderForWidthTmpValueForIdx0ForIdx1)
                } else if (valueHolderForWidthTmpValueForIdx0 instanceof global_resource_Resource) {
                    valueSerializer.writeInt8((2).toByte())
                    const valueHolderForWidthTmpValueForIdx0ForIdx2  = valueHolderForWidthTmpValueForIdx0 as global_resource_Resource
                    global_resource_Resource_serializer.write(valueSerializer, valueHolderForWidthTmpValueForIdx0ForIdx2)
                }
            } else if (valueHolderForWidthTmpValue instanceof EdgeOutlineWidths) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForWidthTmpValueForIdx1  = valueHolderForWidthTmpValue as EdgeOutlineWidths
                EdgeOutlineWidths_serializer.write(valueSerializer, valueHolderForWidthTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForColor  = value.color
        if (valueHolderForColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForColorTmpValue  = valueHolderForColor!
            if (valueHolderForColorTmpValue instanceof ResourceColor) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForColorTmpValueForIdx0  = valueHolderForColorTmpValue as ResourceColor
                if (valueHolderForColorTmpValueForIdx0 instanceof arkui_component_enums_Color) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForColorTmpValueForIdx0ForIdx0  = valueHolderForColorTmpValueForIdx0 as arkui_component_enums_Color
                    valueSerializer.writeInt32((valueHolderForColorTmpValueForIdx0ForIdx0.getOrdinal()) % (12))
                } else if (valueHolderForColorTmpValueForIdx0 instanceof int32) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForColorTmpValueForIdx0ForIdx1  = valueHolderForColorTmpValueForIdx0 as int32
                    valueSerializer.writeInt32(valueHolderForColorTmpValueForIdx0ForIdx1)
                } else if (valueHolderForColorTmpValueForIdx0 instanceof string) {
                    valueSerializer.writeInt8((2).toByte())
                    const valueHolderForColorTmpValueForIdx0ForIdx2  = valueHolderForColorTmpValueForIdx0 as string
                    valueSerializer.writeString(valueHolderForColorTmpValueForIdx0ForIdx2)
                } else if (valueHolderForColorTmpValueForIdx0 instanceof arkui_component_units_Resource) {
                    valueSerializer.writeInt8((3).toByte())
                    const valueHolderForColorTmpValueForIdx0ForIdx3  = valueHolderForColorTmpValueForIdx0 as arkui_component_units_Resource
                    global_resource_Resource_serializer.write(valueSerializer, valueHolderForColorTmpValueForIdx0ForIdx3)
                }
            } else if (valueHolderForColorTmpValue instanceof EdgeColors) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForColorTmpValueForIdx1  = valueHolderForColorTmpValue as EdgeColors
                EdgeColors_serializer.write(valueSerializer, valueHolderForColorTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): MenuOutlineOptions {
        let valueDeserializer : DeserializerBase = buffer
        const widthTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let widthTmpBuf : Dimension | EdgeOutlineWidths | undefined = undefined
        if ((widthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const widthTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let widthTmpBufOpt : Dimension | EdgeOutlineWidths | undefined
            if (widthTmpBufOptUnionSelector == (0).toByte()) {
                const widthTmpBufOptBufUUnionSelector : int32 = valueDeserializer.readInt8()
                let widthTmpBufOptBufU : string | number | global_resource_Resource | undefined
                if (widthTmpBufOptBufUUnionSelector == (0).toByte()) {
                    widthTmpBufOptBufU = (valueDeserializer.readString() as string)
                } else if (widthTmpBufOptBufUUnionSelector == (1).toByte()) {
                    widthTmpBufOptBufU = (valueDeserializer.readNumber() as number)
                } else if (widthTmpBufOptBufUUnionSelector == (2).toByte()) {
                    widthTmpBufOptBufU = global_resource_Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error('One of the branches for widthTmpBufOptBufU has to be chosen through deserialisation.')
                }
                widthTmpBufOpt = (widthTmpBufOptBufU as string | number | global_resource_Resource)
            } else if (widthTmpBufOptUnionSelector == (1).toByte()) {
                widthTmpBufOpt = EdgeOutlineWidths_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for widthTmpBufOpt has to be chosen through deserialisation.')
            }
            widthTmpBuf = (widthTmpBufOpt as Dimension | EdgeOutlineWidths)
        }
        const widthTmpResult : Dimension | EdgeOutlineWidths | undefined = widthTmpBuf
        const colorTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let colorTmpBuf : ResourceColor | EdgeColors | undefined = undefined
        if ((colorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const colorTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let colorTmpBufOpt : ResourceColor | EdgeColors | undefined
            if (colorTmpBufOptUnionSelector == (0).toByte()) {
                const colorTmpBufOptBufUUnionSelector : int32 = valueDeserializer.readInt8()
                let colorTmpBufOptBufU : arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined
                if (colorTmpBufOptBufUUnionSelector == (0).toByte()) {
                    colorTmpBufOptBufU = arkui_component_enums_Color.values()[valueDeserializer.readInt32()]
                } else if (colorTmpBufOptBufUUnionSelector == (1).toByte()) {
                    colorTmpBufOptBufU = valueDeserializer.readInt32()
                } else if (colorTmpBufOptBufUUnionSelector == (2).toByte()) {
                    colorTmpBufOptBufU = (valueDeserializer.readString() as string)
                } else if (colorTmpBufOptBufUUnionSelector == (3).toByte()) {
                    colorTmpBufOptBufU = global_resource_Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error('One of the branches for colorTmpBufOptBufU has to be chosen through deserialisation.')
                }
                colorTmpBufOpt = (colorTmpBufOptBufU as arkui_component_enums_Color | int32 | string | arkui_component_units_Resource)
            } else if (colorTmpBufOptUnionSelector == (1).toByte()) {
                colorTmpBufOpt = EdgeColors_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for colorTmpBufOpt has to be chosen through deserialisation.')
            }
            colorTmpBuf = (colorTmpBufOpt as ResourceColor | EdgeColors)
        }
        const colorTmpResult : ResourceColor | EdgeColors | undefined = colorTmpBuf
        let value : MenuOutlineOptions = ({width: widthTmpResult, color: colorTmpResult} as MenuOutlineOptions)
        return value
    }
}
