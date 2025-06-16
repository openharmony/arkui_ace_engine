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

import { CommonConfiguration, ContentModifier } from "./arkui-wrapper-builder"
import { ResourceStr, Font, ResourceColor, Length, Dimension, DividerStyleOptions, Offset, PX, VP, FP, LPX, Percentage, EdgeOutlineWidths, EdgeColors } from "./units"
import { SymbolGlyphModifier, TextModifier } from "./arkui-external"
import { Resource } from "global.resource"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkCommonMethodPeer, CommonMethod, BlurStyle, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { OptionWidthMode, Color } from "./enums"
import { ControlSize } from "./button"
import { DividerOptions } from "./textPicker"
import { NodeAttach, remember } from "@koalaui/runtime"

export interface MenuItemConfiguration {
    value: ResourceStr
    icon?: ResourceStr | undefined
    symbolIcon?: SymbolGlyphModifier | undefined
    selected: boolean
    index: number
    triggerSelect(index: number, value: string): void
}
export class MenuItemConfigurationInternal implements MaterializedBase,CommonConfiguration,MenuItemConfiguration {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get enabled(): boolean {
        return this.getEnabled()
    }
    set enabled(enabled: boolean) {
        this.setEnabled(enabled)
    }
    get contentModifier(): ContentModifier {
        throw new Error("Not implemented")
    }
    set contentModifier(contentModifier: ContentModifier) {
        this.setContentModifier(contentModifier)
    }
    get value(): ResourceStr {
        throw new Error("Not implemented")
    }
    set value(value: ResourceStr) {
        this.setValue(value)
    }
    get icon(): ResourceStr | undefined {
        throw new Error("Not implemented")
    }
    set icon(icon: ResourceStr | undefined) {
        const icon_NonNull  = (icon as ResourceStr)
        this.setIcon(icon_NonNull)
    }
    get symbolIcon(): SymbolGlyphModifier | undefined {
        throw new Error("Not implemented")
    }
    set symbolIcon(symbolIcon: SymbolGlyphModifier | undefined) {
        const symbolIcon_NonNull  = (symbolIcon as SymbolGlyphModifier)
        this.setSymbolIcon(symbolIcon_NonNull)
    }
    get selected(): boolean {
        return this.getSelected()
    }
    set selected(selected: boolean) {
        this.setSelected(selected)
    }
    get index(): number {
        return this.getIndex()
    }
    set index(index: number) {
        this.setIndex(index)
    }
    static ctor_menuitemconfiguration(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._MenuItemConfiguration_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = MenuItemConfigurationInternal.ctor_menuitemconfiguration()
        this.peer = new Finalizable(ctorPtr, MenuItemConfigurationInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._MenuItemConfiguration_getFinalizer()
    }
    public triggerSelect(index: number, value: string): void {
        const index_casted = index as (number)
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
    private getContentModifier(): ContentModifier {
        return this.getContentModifier_serialize()
    }
    private setContentModifier(contentModifier: ContentModifier): void {
        const contentModifier_casted = contentModifier as (ContentModifier)
        this.setContentModifier_serialize(contentModifier_casted)
        return
    }
    private getValue(): ResourceStr {
        return this.getValue_serialize()
    }
    private setValue(value: ResourceStr): void {
        const value_casted = value as (ResourceStr)
        this.setValue_serialize(value_casted)
        return
    }
    private getIcon(): ResourceStr | undefined {
        return this.getIcon_serialize()
    }
    private setIcon(icon: ResourceStr): void {
        const icon_casted = icon as (ResourceStr)
        this.setIcon_serialize(icon_casted)
        return
    }
    private getSymbolIcon(): SymbolGlyphModifier | undefined {
        return this.getSymbolIcon_serialize()
    }
    private setSymbolIcon(symbolIcon: SymbolGlyphModifier): void {
        const symbolIcon_casted = symbolIcon as (SymbolGlyphModifier)
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
    private getIndex(): number {
        return this.getIndex_serialize()
    }
    private setIndex(index: number): void {
        const index_casted = index as (number)
        this.setIndex_serialize(index_casted)
        return
    }
    private triggerSelect_serialize(index: number, value: string): void {
        ArkUIGeneratedNativeModule._MenuItemConfiguration_triggerSelect(this.peer!.ptr, index, value)
    }
    private getEnabled_serialize(): boolean {
        const retval  = ArkUIGeneratedNativeModule._MenuItemConfiguration_getEnabled(this.peer!.ptr)
        return retval
    }
    private setEnabled_serialize(enabled: boolean): void {
        ArkUIGeneratedNativeModule._MenuItemConfiguration_setEnabled(this.peer!.ptr, enabled ? 1 : 0)
    }
    private getContentModifier_serialize(): ContentModifier {
        const retval  = ArkUIGeneratedNativeModule._MenuItemConfiguration_getContentModifier(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const returnResult : ContentModifier = (retvalDeserializer.readObject() as ContentModifier)
        return returnResult
    }
    private setContentModifier_serialize(contentModifier: ContentModifier): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteObject(contentModifier)
        ArkUIGeneratedNativeModule._MenuItemConfiguration_setContentModifier(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getValue_serialize(): ResourceStr {
        const retval  = ArkUIGeneratedNativeModule._MenuItemConfiguration_getValue(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setValue_serialize(value: ResourceStr): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as Resource
            thisSerializer.writeResource(value_1)
        }
        ArkUIGeneratedNativeModule._MenuItemConfiguration_setValue(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getIcon_serialize(): ResourceStr | undefined {
        const retval  = ArkUIGeneratedNativeModule._MenuItemConfiguration_getIcon(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setIcon_serialize(icon: ResourceStr): void {
        const thisSerializer : Serializer = Serializer.hold()
        let icon_type : int32 = RuntimeType.UNDEFINED
        icon_type = runtimeType(icon)
        if (RuntimeType.STRING == icon_type) {
            thisSerializer.writeInt8(0 as int32)
            const icon_0  = icon as string
            thisSerializer.writeString(icon_0)
        }
        else if (RuntimeType.OBJECT == icon_type) {
            thisSerializer.writeInt8(1 as int32)
            const icon_1  = icon as Resource
            thisSerializer.writeResource(icon_1)
        }
        ArkUIGeneratedNativeModule._MenuItemConfiguration_setIcon(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getSymbolIcon_serialize(): SymbolGlyphModifier | undefined {
        const retval  = ArkUIGeneratedNativeModule._MenuItemConfiguration_getSymbolIcon(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setSymbolIcon_serialize(symbolIcon: SymbolGlyphModifier): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeSymbolGlyphModifier(symbolIcon)
        ArkUIGeneratedNativeModule._MenuItemConfiguration_setSymbolIcon(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getSelected_serialize(): boolean {
        const retval  = ArkUIGeneratedNativeModule._MenuItemConfiguration_getSelected(this.peer!.ptr)
        return retval
    }
    private setSelected_serialize(selected: boolean): void {
        ArkUIGeneratedNativeModule._MenuItemConfiguration_setSelected(this.peer!.ptr, selected ? 1 : 0)
    }
    private getIndex_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._MenuItemConfiguration_getIndex(this.peer!.ptr)
        return retval
    }
    private setIndex_serialize(index: number): void {
        ArkUIGeneratedNativeModule._MenuItemConfiguration_setIndex(this.peer!.ptr, index)
    }
    public static fromPtr(ptr: KPointer): MenuItemConfigurationInternal {
        const obj : MenuItemConfigurationInternal = new MenuItemConfigurationInternal()
        obj.peer = new Finalizable(ptr, MenuItemConfigurationInternal.getFinalizer())
        return obj
    }
}
export class ArkSelectPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkSelectPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Select_construct(peerId, flags)
        const _peer  = new ArkSelectPeer(_peerPtr, peerId, "Select", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setSelectOptionsAttribute(options: Array<SelectOption>): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeInt32(options.length as int32)
        for (let i = 0; i < options.length; i++) {
            const options_element : SelectOption = options[i]
            thisSerializer.writeSelectOption(options_element)
        }
        ArkUIGeneratedNativeModule._SelectInterface_setSelectOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    selected0Attribute(value: number | Resource | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as Resource
                thisSerializer.writeResource(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._SelectAttribute_selected0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    selected1Attribute(value: number | Resource | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as Resource
                thisSerializer.writeResource(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._SelectAttribute_selected1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    value0Attribute(value: ResourceStr | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as Resource
                thisSerializer.writeResource(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._SelectAttribute_value0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    value1Attribute(value: ResourceStr | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as Resource
                thisSerializer.writeResource(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._SelectAttribute_value1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    font0Attribute(value: Font | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeFont(value_value)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_font0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    font1Attribute(value: Font | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeFont(value_value)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_font1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontColor0Attribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._SelectAttribute_fontColor0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontColor1Attribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._SelectAttribute_fontColor1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    selectedOptionBgColor0Attribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._SelectAttribute_selectedOptionBgColor0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    selectedOptionBgColor1Attribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._SelectAttribute_selectedOptionBgColor1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    selectedOptionFont0Attribute(value: Font | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeFont(value_value)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_selectedOptionFont0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    selectedOptionFont1Attribute(value: Font | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeFont(value_value)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_selectedOptionFont1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    selectedOptionFontColor0Attribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._SelectAttribute_selectedOptionFontColor0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    selectedOptionFontColor1Attribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._SelectAttribute_selectedOptionFontColor1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    optionBgColor0Attribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._SelectAttribute_optionBgColor0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    optionBgColor1Attribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._SelectAttribute_optionBgColor1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    optionFont0Attribute(value: Font | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeFont(value_value)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_optionFont0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    optionFont1Attribute(value: Font | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeFont(value_value)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_optionFont1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    optionFontColor0Attribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._SelectAttribute_optionFontColor0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    optionFontColor1Attribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._SelectAttribute_optionFontColor1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onSelect0Attribute(value: ((index: number,value: string) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_onSelect0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onSelect1Attribute(value: OnSelectCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_onSelect1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    space0Attribute(value: Length | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeLength(value_value)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_space0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    space1Attribute(value: Length | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeLength(value_value)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_space1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    arrowPosition0Attribute(value: ArrowPosition | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as ArrowPosition)
            thisSerializer.writeInt32(TypeChecker.ArrowPosition_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._SelectAttribute_arrowPosition0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    arrowPosition1Attribute(value: ArrowPosition | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as ArrowPosition)
            thisSerializer.writeInt32(TypeChecker.ArrowPosition_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._SelectAttribute_arrowPosition1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    optionWidth0Attribute(value: Dimension | OptionWidthMode | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isOptionWidthMode(value_value)) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1 = value_value as OptionWidthMode
                thisSerializer.writeInt32(TypeChecker.OptionWidthMode_ToNumeric(value_value_1))
            }
            else if (((RuntimeType.NUMBER) == (value_value_type)) || ((RuntimeType.STRING) == (value_value_type)) ||
                (((RuntimeType.OBJECT) == (value_value_type)) &&
                    (TypeChecker.isResource(value_value, false, false, false, false, false)))) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0 = value_value as Dimension
                thisSerializer.writeLength(value_value_0)
            }
        }
        ArkUIGeneratedNativeModule._SelectAttribute_optionWidth0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    optionWidth1Attribute(value: Dimension | OptionWidthMode | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (((RuntimeType.NUMBER) == (value_value_type)) || ((RuntimeType.STRING) == (value_value_type)) || (((RuntimeType.OBJECT) == (value_value_type)) && (TypeChecker.isResource(value_value, false, false, false, false, false)))) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Dimension
                thisSerializer.writeLength(value_value_0)
            }
            else if (TypeChecker.isOptionWidthMode(value_value)) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as OptionWidthMode
                thisSerializer.writeInt32(TypeChecker.OptionWidthMode_ToNumeric(value_value_1))
            }
        }
        ArkUIGeneratedNativeModule._SelectAttribute_optionWidth1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    optionHeight0Attribute(value: Dimension | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeLength(value_value)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_optionHeight0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    optionHeight1Attribute(value: Dimension | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeLength(value_value)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_optionHeight1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    menuBackgroundColor0Attribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._SelectAttribute_menuBackgroundColor0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    menuBackgroundColor1Attribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._SelectAttribute_menuBackgroundColor1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    menuBackgroundBlurStyle0Attribute(value: BlurStyle | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as BlurStyle)
            thisSerializer.writeInt32(TypeChecker.BlurStyle_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._SelectAttribute_menuBackgroundBlurStyle0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    menuBackgroundBlurStyle1Attribute(value: BlurStyle | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as BlurStyle)
            thisSerializer.writeInt32(TypeChecker.BlurStyle_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._SelectAttribute_menuBackgroundBlurStyle1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    controlSize0Attribute(value: ControlSize | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as ControlSize)
            thisSerializer.writeInt32(TypeChecker.ControlSize_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._SelectAttribute_controlSize0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    controlSize1Attribute(value: ControlSize | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as ControlSize)
            thisSerializer.writeInt32(TypeChecker.ControlSize_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._SelectAttribute_controlSize1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    menuItemContentModifier0Attribute(value: ContentModifier | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteObject(value_value)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_menuItemContentModifier0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    menuItemContentModifier1Attribute(value: ContentModifier | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteObject(value_value)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_menuItemContentModifier1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    dividerAttribute(value: DividerOptions | null | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeDividerOptions(value_value)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_divider(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    textModifierAttribute(value: TextModifier | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeTextModifier(value_value)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_textModifier(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    arrowModifierAttribute(value: SymbolGlyphModifier | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeSymbolGlyphModifier(value_value)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_arrowModifier(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    optionTextModifierAttribute(value: TextModifier | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeTextModifier(value_value)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_optionTextModifier(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    selectedOptionTextModifierAttribute(value: TextModifier | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeTextModifier(value_value)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_selectedOptionTextModifier(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    dividerStyleAttribute(value: DividerStyleOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeDividerStyleOptions(value_value)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_dividerStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    avoidanceAttribute(value: AvoidanceMode | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as AvoidanceMode)
            thisSerializer.writeInt32(TypeChecker.AvoidanceMode_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._SelectAttribute_avoidance(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    menuOutlineAttribute(value: MenuOutlineOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeMenuOutlineOptions(value_value)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_menuOutline(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    menuAlign0Attribute(alignType: MenuAlignType | undefined, offset?: Offset | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let alignType_type : int32 = RuntimeType.UNDEFINED
        alignType_type = runtimeType(alignType)
        thisSerializer.writeInt8(alignType_type as int32)
        if ((RuntimeType.UNDEFINED) != (alignType_type)) {
            const alignType_value  = (alignType as MenuAlignType)
            thisSerializer.writeInt32(TypeChecker.MenuAlignType_ToNumeric(alignType_value))
        }
        let offset_type : int32 = RuntimeType.UNDEFINED
        offset_type = runtimeType(offset)
        thisSerializer.writeInt8(offset_type as int32)
        if ((RuntimeType.UNDEFINED) != (offset_type)) {
            const offset_value  = offset!
            thisSerializer.writeOffset(offset_value)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_menuAlign0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    menuAlign1Attribute(alignType: MenuAlignType | undefined, offset?: Offset): void {
        const thisSerializer : Serializer = Serializer.hold()
        let alignType_type : int32 = RuntimeType.UNDEFINED
        alignType_type = runtimeType(alignType)
        thisSerializer.writeInt8(alignType_type as int32)
        if ((RuntimeType.UNDEFINED) != (alignType_type)) {
            const alignType_value  = (alignType as MenuAlignType)
            thisSerializer.writeInt32(TypeChecker.MenuAlignType_ToNumeric(alignType_value))
        }
        let offset_type : int32 = RuntimeType.UNDEFINED
        offset_type = runtimeType(offset)
        thisSerializer.writeInt8(offset_type as int32)
        if ((RuntimeType.UNDEFINED) != (offset_type)) {
            const offset_value  = offset!
            thisSerializer.writeOffset(offset_value)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_menuAlign1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    _onChangeEvent_selectedAttribute(callback: ((selected: number | Resource | undefined) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(callback)
        ArkUIGeneratedNativeModule._SelectAttribute__onChangeEvent_selected(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    _onChangeEvent_valueAttribute(callback: ((value: ResourceStr | undefined) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(callback)
        ArkUIGeneratedNativeModule._SelectAttribute__onChangeEvent_value(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface SelectOption {
    value: ResourceStr;
    icon?: ResourceStr;
    symbolIcon?: SymbolGlyphModifier;
}
export type SelectInterface = (options: Array<SelectOption>) => SelectAttribute;
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
export type OnSelectCallback = (index: number, selectStr: string) => void;
export interface MenuOutlineOptions {
    width?: Dimension | EdgeOutlineWidths;
    color?: ResourceColor | EdgeColors;
}
export type Callback_Number_String_Void = (index: number, value: string) => void;
export type Callback_Opt_Union_Number_Resource_Void = (selected: number | Resource | undefined) => void;
export type Callback_Opt_ResourceStr_Void = (value: ResourceStr | undefined) => void;
export interface SelectAttribute extends CommonMethod {
    selected(value: number | Resource | undefined): this
    value(value: ResourceStr | undefined): this
    font(value: Font | undefined): this
    fontColor(value: ResourceColor | undefined): this
    selectedOptionBgColor(value: ResourceColor | undefined): this
    selectedOptionFont(value: Font | undefined): this
    selectedOptionFontColor(value: ResourceColor | undefined): this
    optionBgColor(value: ResourceColor | undefined): this
    optionFont(value: Font | undefined): this
    optionFontColor(value: ResourceColor | undefined): this
    onSelect(value: ((index: number,value: string) => void) | undefined | OnSelectCallback | undefined): this
    space(value: Length | undefined): this
    arrowPosition(value: ArrowPosition | undefined): this
    optionWidth(value: Dimension | OptionWidthMode | undefined): this
    optionHeight(value: Dimension | undefined): this
    menuBackgroundColor(value: ResourceColor | undefined): this
    menuBackgroundBlurStyle(value: BlurStyle | undefined): this
    controlSize(value: ControlSize | undefined): this
    menuItemContentModifier(value: ContentModifier | undefined): this
    divider(value: DividerOptions | null | undefined): this
    textModifier(value: TextModifier | undefined): this
    arrowModifier(value: SymbolGlyphModifier | undefined): this
    optionTextModifier(value: TextModifier | undefined): this
    selectedOptionTextModifier(value: TextModifier | undefined): this
    dividerStyle(value: DividerStyleOptions | undefined): this
    avoidance(value: AvoidanceMode | undefined): this
    menuOutline(value: MenuOutlineOptions | undefined): this
    menuAlign(alignType: MenuAlignType | undefined, offset?: Offset): this
    _onChangeEvent_selected(callback: ((selected: number | Resource | undefined) => void)): void
    _onChangeEvent_value(callback: ((value: ResourceStr | undefined) => void)): void
}
export class ArkSelectStyle extends ArkCommonMethodStyle implements SelectAttribute {
    selected_value?: number | Resource | undefined
    value_value?: ResourceStr | undefined
    font_value?: Font | undefined
    fontColor_value?: ResourceColor | undefined
    selectedOptionBgColor_value?: ResourceColor | undefined
    selectedOptionFont_value?: Font | undefined
    selectedOptionFontColor_value?: ResourceColor | undefined
    optionBgColor_value?: ResourceColor | undefined
    optionFont_value?: Font | undefined
    optionFontColor_value?: ResourceColor | undefined
    onSelect_value?: ((index: number,value: string) => void) | undefined
    space_value?: Length | undefined
    arrowPosition_value?: ArrowPosition | undefined
    optionWidth_value?: Dimension | OptionWidthMode | undefined
    optionHeight_value?: Dimension | undefined
    menuBackgroundColor_value?: ResourceColor | undefined
    menuBackgroundBlurStyle_value?: BlurStyle | undefined
    controlSize_value?: ControlSize | undefined
    menuItemContentModifier_value?: ContentModifier | undefined
    divider_value?: DividerOptions | undefined
    textModifier_value?: TextModifier | undefined
    arrowModifier_value?: SymbolGlyphModifier | undefined
    optionTextModifier_value?: TextModifier | undefined
    selectedOptionTextModifier_value?: TextModifier | undefined
    dividerStyle_value?: DividerStyleOptions | undefined
    avoidance_value?: AvoidanceMode | undefined
    menuOutline_value?: MenuOutlineOptions | undefined
    public selected(value: number | Resource | undefined): this {
        return this
    }
    public value(value: ResourceStr | undefined): this {
        return this
    }
    public font(value: Font | undefined): this {
        return this
    }
    public fontColor(value: ResourceColor | undefined): this {
        return this
    }
    public selectedOptionBgColor(value: ResourceColor | undefined): this {
        return this
    }
    public selectedOptionFont(value: Font | undefined): this {
        return this
    }
    public selectedOptionFontColor(value: ResourceColor | undefined): this {
        return this
    }
    public optionBgColor(value: ResourceColor | undefined): this {
        return this
    }
    public optionFont(value: Font | undefined): this {
        return this
    }
    public optionFontColor(value: ResourceColor | undefined): this {
        return this
    }
    public onSelect(value: ((index: number,value: string) => void) | undefined | OnSelectCallback | undefined): this {
        return this
    }
    public space(value: Length | undefined): this {
        return this
    }
    public arrowPosition(value: ArrowPosition | undefined): this {
        return this
    }
    public optionWidth(value: Dimension | OptionWidthMode | undefined): this {
        return this
    }
    public optionHeight(value: Dimension | undefined): this {
        return this
    }
    public menuBackgroundColor(value: ResourceColor | undefined): this {
        return this
    }
    public menuBackgroundBlurStyle(value: BlurStyle | undefined): this {
        return this
    }
    public controlSize(value: ControlSize | undefined): this {
        return this
    }
    public menuItemContentModifier(value: ContentModifier | undefined): this {
        return this
    }
    public divider(value: DividerOptions | null | undefined): this {
        return this
    }
    public textModifier(value: TextModifier | undefined): this {
        return this
    }
    public arrowModifier(value: SymbolGlyphModifier | undefined): this {
        return this
    }
    public optionTextModifier(value: TextModifier | undefined): this {
        return this
    }
    public selectedOptionTextModifier(value: TextModifier | undefined): this {
        return this
    }
    public dividerStyle(value: DividerStyleOptions | undefined): this {
        return this
    }
    public avoidance(value: AvoidanceMode | undefined): this {
        return this
    }
    public menuOutline(value: MenuOutlineOptions | undefined): this {
        return this
    }
    public menuAlign(alignType: MenuAlignType | undefined, offset?: Offset): this {
        return this
    }
    public _onChangeEvent_selected(callback: ((selected: number | Resource | undefined) => void)): void {
        throw new Error("Unimplmented")
    }
    public _onChangeEvent_value(callback: ((value: ResourceStr | undefined) => void)): void {
        throw new Error("Unimplmented")
        }
}
export class ArkSelectComponent extends ArkCommonMethodComponent implements SelectAttribute {
    getPeer(): ArkSelectPeer {
        return (this.peer as ArkSelectPeer)
    }
    public setSelectOptions(options: Array<SelectOption>): this {
        if (this.checkPriority("setSelectOptions")) {
            const options_casted = options as (Array<SelectOption>)
            this.getPeer()?.setSelectOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    public selected(value: number | Resource | undefined): this {
        if (this.checkPriority("selected")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (number | Resource | undefined)
                this.getPeer()?.selected0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (number | Resource | undefined)
                this.getPeer()?.selected1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public value(value: ResourceStr | undefined): this {
        if (this.checkPriority("value")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (ResourceStr | undefined)
                this.getPeer()?.value0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (ResourceStr | undefined)
                this.getPeer()?.value1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public font(value: Font | undefined): this {
        if (this.checkPriority("font")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (Font | undefined)
                this.getPeer()?.font0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (Font | undefined)
                this.getPeer()?.font1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public fontColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("fontColor")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.NUMBER == value_type) || (RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (ResourceColor | undefined)
                this.getPeer()?.fontColor0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.NUMBER == value_type) || (RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (ResourceColor | undefined)
                this.getPeer()?.fontColor1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public selectedOptionBgColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("selectedOptionBgColor")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.NUMBER == value_type) || (RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (ResourceColor | undefined)
                this.getPeer()?.selectedOptionBgColor0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.NUMBER == value_type) || (RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (ResourceColor | undefined)
                this.getPeer()?.selectedOptionBgColor1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public selectedOptionFont(value: Font | undefined): this {
        if (this.checkPriority("selectedOptionFont")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (Font | undefined)
                this.getPeer()?.selectedOptionFont0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (Font | undefined)
                this.getPeer()?.selectedOptionFont1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public selectedOptionFontColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("selectedOptionFontColor")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.NUMBER == value_type) || (RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (ResourceColor | undefined)
                this.getPeer()?.selectedOptionFontColor0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.NUMBER == value_type) || (RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (ResourceColor | undefined)
                this.getPeer()?.selectedOptionFontColor1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public optionBgColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("optionBgColor")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.NUMBER == value_type) || (RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (ResourceColor | undefined)
                this.getPeer()?.optionBgColor0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.NUMBER == value_type) || (RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (ResourceColor | undefined)
                this.getPeer()?.optionBgColor1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public optionFont(value: Font | undefined): this {
        if (this.checkPriority("optionFont")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (Font | undefined)
                this.getPeer()?.optionFont0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (Font | undefined)
                this.getPeer()?.optionFont1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public optionFontColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("optionFontColor")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.NUMBER == value_type) || (RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (ResourceColor | undefined)
                this.getPeer()?.optionFontColor0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.NUMBER == value_type) || (RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (ResourceColor | undefined)
                this.getPeer()?.optionFontColor1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public onSelect(value: ((index: number,value: string) => void) | undefined | OnSelectCallback | undefined): this {
        if (this.checkPriority("onSelect")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.FUNCTION == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (((index: number,value: string) => void) | undefined)
                this.getPeer()?.onSelect0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.FUNCTION == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (OnSelectCallback | undefined)
                this.getPeer()?.onSelect1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public space(value: Length | undefined): this {
        if (this.checkPriority("space")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (Length | undefined)
                this.getPeer()?.space0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (Length | undefined)
                this.getPeer()?.space1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public arrowPosition(value: ArrowPosition | undefined): this {
        if (this.checkPriority("arrowPosition")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (ArrowPosition | undefined)
                this.getPeer()?.arrowPosition0Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public optionWidth(value: Dimension | OptionWidthMode | undefined): this {
        if (this.checkPriority("optionWidth")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.STRING == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (Dimension | OptionWidthMode | undefined)
                this.getPeer()?.optionWidth0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.STRING == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (Dimension | OptionWidthMode | undefined)
                this.getPeer()?.optionWidth1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public optionHeight(value: Dimension | undefined): this {
        if (this.checkPriority("optionHeight")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (Dimension | undefined)
                this.getPeer()?.optionHeight0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (Dimension | undefined)
                this.getPeer()?.optionHeight1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public menuBackgroundColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("menuBackgroundColor")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.NUMBER == value_type) || (RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (ResourceColor | undefined)
                this.getPeer()?.menuBackgroundColor0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.NUMBER == value_type) || (RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (ResourceColor | undefined)
                this.getPeer()?.menuBackgroundColor1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public menuBackgroundBlurStyle(value: BlurStyle | undefined): this {
        if (this.checkPriority("menuBackgroundBlurStyle")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (BlurStyle | undefined)
                this.getPeer()?.menuBackgroundBlurStyle0Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public controlSize(value: ControlSize | undefined): this {
        if (this.checkPriority("controlSize")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.STRING == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (ControlSize | undefined)
                this.getPeer()?.controlSize0Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public menuItemContentModifier(value: ContentModifier | undefined): this {
        if (this.checkPriority("menuItemContentModifier")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.BIGINT == value_type) || (RuntimeType.BOOLEAN == value_type) || (RuntimeType.FUNCTION == value_type) || (RuntimeType.MATERIALIZED == value_type) || (RuntimeType.NUMBER == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.STRING == value_type) || (RuntimeType.SYMBOL == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (ContentModifier | undefined)
                this.getPeer()?.menuItemContentModifier0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.BIGINT == value_type) || (RuntimeType.BOOLEAN == value_type) || (RuntimeType.FUNCTION == value_type) || (RuntimeType.MATERIALIZED == value_type) || (RuntimeType.NUMBER == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.STRING == value_type) || (RuntimeType.SYMBOL == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (ContentModifier | undefined)
                this.getPeer()?.menuItemContentModifier1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public divider(value: DividerOptions | null | undefined): this {
        if (this.checkPriority("divider")) {
            const value_casted = value as (DividerOptions | null | undefined)
            this.getPeer()?.dividerAttribute(value_casted)
            return this
        }
        return this
    }
    public textModifier(value: TextModifier | undefined): this {
        if (this.checkPriority("textModifier")) {
            const value_casted = value as (TextModifier | undefined)
            this.getPeer()?.textModifierAttribute(value_casted)
            return this
        }
        return this
    }
    public arrowModifier(value: SymbolGlyphModifier | undefined): this {
        if (this.checkPriority("arrowModifier")) {
            const value_casted = value as (SymbolGlyphModifier | undefined)
            this.getPeer()?.arrowModifierAttribute(value_casted)
            return this
        }
        return this
    }
    public optionTextModifier(value: TextModifier | undefined): this {
        if (this.checkPriority("optionTextModifier")) {
            const value_casted = value as (TextModifier | undefined)
            this.getPeer()?.optionTextModifierAttribute(value_casted)
            return this
        }
        return this
    }
    public selectedOptionTextModifier(value: TextModifier | undefined): this {
        if (this.checkPriority("selectedOptionTextModifier")) {
            const value_casted = value as (TextModifier | undefined)
            this.getPeer()?.selectedOptionTextModifierAttribute(value_casted)
            return this
        }
        return this
    }
    public dividerStyle(value: DividerStyleOptions | undefined): this {
        if (this.checkPriority("dividerStyle")) {
            const value_casted = value as (DividerStyleOptions | undefined)
            this.getPeer()?.dividerStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public avoidance(value: AvoidanceMode | undefined): this {
        if (this.checkPriority("avoidance")) {
            const value_casted = value as (AvoidanceMode | undefined)
            this.getPeer()?.avoidanceAttribute(value_casted)
            return this
        }
        return this
    }
    public menuOutline(value: MenuOutlineOptions | undefined): this {
        if (this.checkPriority("menuOutline")) {
            const value_casted = value as (MenuOutlineOptions | undefined)
            this.getPeer()?.menuOutlineAttribute(value_casted)
            return this
        }
        return this
    }
    public menuAlign(alignType: MenuAlignType | undefined, offset?: Offset | undefined): this {
        if (this.checkPriority("menuAlign")) {
            const alignType_type = runtimeType(alignType)
            const offset_type = runtimeType(offset)
            if ((RuntimeType.NUMBER == alignType_type) || (RuntimeType.UNDEFINED == alignType_type)) {
                const alignType_casted = alignType as (MenuAlignType | undefined)
                const offset_casted = offset as (Offset | undefined)
                this.getPeer()?.menuAlign0Attribute(alignType_casted, offset_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public _onChangeEvent_selected(callback: ((selected: number | Resource | undefined) => void)): void {
        if (this.checkPriority("_onChangeEvent_selected")) {
            const callback_casted = callback as (((selected: number | Resource | undefined) => void))
            this.getPeer()?._onChangeEvent_selectedAttribute(callback_casted)
            return
        }
        return
    }
    public _onChangeEvent_value(callback: ((value: ResourceStr | undefined) => void)): void {
        if (this.checkPriority("_onChangeEvent_value")) {
            const callback_casted = callback as (((value: ResourceStr | undefined) => void))
            this.getPeer()?._onChangeEvent_valueAttribute(callback_casted)
            return
        }
        return
    }
    
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function Select(
    /** @memo */
    style: ((attributes: SelectAttribute) => void) | undefined,
    options: Array<SelectOption>,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkSelectComponent()
    })
    NodeAttach<ArkSelectPeer>((): ArkSelectPeer => ArkSelectPeer.create(receiver), (_: ArkSelectPeer) => {
        receiver.setSelectOptions(options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
