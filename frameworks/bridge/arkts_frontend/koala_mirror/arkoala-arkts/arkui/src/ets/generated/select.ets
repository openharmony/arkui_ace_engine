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
import { ResourceStr, Font, ResourceColor, Length, Dimension, Offset } from "./units"
import { SymbolGlyphModifier } from "./arkui-external"
import { Resource } from "./resource"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./../CallbackTransformer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkCommonMethodPeer, CommonMethod, BlurStyle, ArkCommonMethodComponent, ArkCommonMethodStyle, UICommonMethod } from "./common"
import { OptionWidthMode, Color } from "./enums"
import { ControlSize } from "./button"
import { DividerOptions } from "./text_picker"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { BuilderLambda } from "@koalaui/builderLambda"
import { UICommonBase, AttributeModifier } from "./../handwritten"
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
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length)
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
            thisSerializer.writeInt8(0)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(1)
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
            thisSerializer.writeInt8(0)
            const icon_0  = icon as string
            thisSerializer.writeString(icon_0)
        }
        else if (RuntimeType.OBJECT == icon_type) {
            thisSerializer.writeInt8(1)
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
    public static create(component?: ComponentBase, flags: int32 = 0): ArkSelectPeer {
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
    selectedAttribute(value: number | Resource): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0)
            const value_0  = value as number
            thisSerializer.writeNumber(value_0)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(1)
            const value_1  = value as Resource
            thisSerializer.writeResource(value_1)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_selected(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    valueAttribute(value: ResourceStr): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(1)
            const value_1  = value as Resource
            thisSerializer.writeResource(value_1)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_value(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontAttribute(value: Font): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeFont(value)
        ArkUIGeneratedNativeModule._SelectAttribute_font(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontColorAttribute(value: ResourceColor): void {
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
        ArkUIGeneratedNativeModule._SelectAttribute_fontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    selectedOptionBgColorAttribute(value: ResourceColor): void {
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
        ArkUIGeneratedNativeModule._SelectAttribute_selectedOptionBgColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    selectedOptionFontAttribute(value: Font): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeFont(value)
        ArkUIGeneratedNativeModule._SelectAttribute_selectedOptionFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    selectedOptionFontColorAttribute(value: ResourceColor): void {
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
        ArkUIGeneratedNativeModule._SelectAttribute_selectedOptionFontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    optionBgColorAttribute(value: ResourceColor): void {
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
        ArkUIGeneratedNativeModule._SelectAttribute_optionBgColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    optionFontAttribute(value: Font): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeFont(value)
        ArkUIGeneratedNativeModule._SelectAttribute_optionFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    optionFontColorAttribute(value: ResourceColor): void {
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
        ArkUIGeneratedNativeModule._SelectAttribute_optionFontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onSelectAttribute(value: ((index: number,value: string) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._SelectAttribute_onSelect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    spaceAttribute(value: Length): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2)
            const value_2  = value as Resource
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_space(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    arrowPositionAttribute(value: ArrowPosition): void {
        ArkUIGeneratedNativeModule._SelectAttribute_arrowPosition(this.peer.ptr, TypeChecker.ArrowPosition_ToNumeric(value))
    }
    optionWidthAttribute(value: Dimension | OptionWidthMode): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if ((RuntimeType.STRING == value_type) || (RuntimeType.NUMBER == value_type) || (RuntimeType.OBJECT == value_type)) {
            thisSerializer.writeInt8(0)
            const value_0  = value as Dimension
            let value_0_type : int32 = RuntimeType.UNDEFINED
            value_0_type = runtimeType(value_0)
            if (RuntimeType.STRING == value_0_type) {
                thisSerializer.writeInt8(0)
                const value_0_0  = value_0 as string
                thisSerializer.writeString(value_0_0)
            }
            else if (RuntimeType.NUMBER == value_0_type) {
                thisSerializer.writeInt8(1)
                const value_0_1  = value_0 as number
                thisSerializer.writeNumber(value_0_1)
            }
            else if (RuntimeType.OBJECT == value_0_type) {
                thisSerializer.writeInt8(2)
                const value_0_2  = value_0 as Resource
                thisSerializer.writeResource(value_0_2)
            }
        }
        else if (TypeChecker.isOptionWidthMode(value)) {
            thisSerializer.writeInt8(1)
            const value_1  = value as OptionWidthMode
            thisSerializer.writeInt32(TypeChecker.OptionWidthMode_ToNumeric(value_1))
        }
        ArkUIGeneratedNativeModule._SelectAttribute_optionWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    optionHeightAttribute(value: Dimension): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2)
            const value_2  = value as Resource
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_optionHeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    menuBackgroundColorAttribute(value: ResourceColor): void {
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
        ArkUIGeneratedNativeModule._SelectAttribute_menuBackgroundColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    menuBackgroundBlurStyleAttribute(value: BlurStyle): void {
        ArkUIGeneratedNativeModule._SelectAttribute_menuBackgroundBlurStyle(this.peer.ptr, TypeChecker.BlurStyle_ToNumeric(value))
    }
    controlSizeAttribute(value: ControlSize): void {
        ArkUIGeneratedNativeModule._SelectAttribute_controlSize(this.peer.ptr, TypeChecker.ControlSize_ToNumeric(value))
    }
    menuItemContentModifierAttribute(value: ContentModifier): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteObject(value)
        ArkUIGeneratedNativeModule._SelectAttribute_menuItemContentModifier(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    dividerAttribute(value: DividerOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeDividerOptions(value_value)
        }
        ArkUIGeneratedNativeModule._SelectAttribute_divider(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    menuAlignAttribute(alignType: MenuAlignType, offset?: Offset): void {
        const thisSerializer : Serializer = Serializer.hold()
        let offset_type : int32 = RuntimeType.UNDEFINED
        offset_type = runtimeType(offset)
        thisSerializer.writeInt8(offset_type)
        if ((RuntimeType.UNDEFINED) != (offset_type)) {
            const offset_value  = offset!
            const offset_value_dx  = offset_value.dx
            let offset_value_dx_type : int32 = RuntimeType.UNDEFINED
            offset_value_dx_type = runtimeType(offset_value_dx)
            if (RuntimeType.STRING == offset_value_dx_type) {
                thisSerializer.writeInt8(0)
                const offset_value_dx_0  = offset_value_dx as string
                thisSerializer.writeString(offset_value_dx_0)
            }
            else if (RuntimeType.NUMBER == offset_value_dx_type) {
                thisSerializer.writeInt8(1)
                const offset_value_dx_1  = offset_value_dx as number
                thisSerializer.writeNumber(offset_value_dx_1)
            }
            else if (RuntimeType.OBJECT == offset_value_dx_type) {
                thisSerializer.writeInt8(2)
                const offset_value_dx_2  = offset_value_dx as Resource
                thisSerializer.writeResource(offset_value_dx_2)
            }
            const offset_value_dy  = offset_value.dy
            let offset_value_dy_type : int32 = RuntimeType.UNDEFINED
            offset_value_dy_type = runtimeType(offset_value_dy)
            if (RuntimeType.STRING == offset_value_dy_type) {
                thisSerializer.writeInt8(0)
                const offset_value_dy_0  = offset_value_dy as string
                thisSerializer.writeString(offset_value_dy_0)
            }
            else if (RuntimeType.NUMBER == offset_value_dy_type) {
                thisSerializer.writeInt8(1)
                const offset_value_dy_1  = offset_value_dy as number
                thisSerializer.writeNumber(offset_value_dy_1)
            }
            else if (RuntimeType.OBJECT == offset_value_dy_type) {
                thisSerializer.writeInt8(2)
                const offset_value_dy_2  = offset_value_dy as Resource
                thisSerializer.writeResource(offset_value_dy_2)
            }
        }
        ArkUIGeneratedNativeModule._SelectAttribute_menuAlign(this.peer.ptr, TypeChecker.MenuAlignType_ToNumeric(alignType), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    _onChangeEvent_selectedAttribute(callback: ((selected: number | Resource) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(callback)
        ArkUIGeneratedNativeModule._SelectAttribute__onChangeEvent_selected(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    _onChangeEvent_valueAttribute(callback: ((value: ResourceStr) => void)): void {
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

export enum ArrowPosition {
    END = 0,
    START = 1
}
export enum MenuAlignType {
    START = 0,
    CENTER = 1,
    END = 2
}
export type Callback_Number_String_Void = (index: number, value: string) => void;
export type Callback_Union_Number_Resource_Void = (selected: number | Resource) => void;
export type Callback_ResourceStr_Void = (value: ResourceStr) => void;
export interface SelectAttribute extends CommonMethod {
    selected(value: number | Resource): this
    value(value: ResourceStr): this
    font(value: Font): this
    fontColor(value: ResourceColor): this
    selectedOptionBgColor(value: ResourceColor): this
    selectedOptionFont(value: Font): this
    selectedOptionFontColor(value: ResourceColor): this
    optionBgColor(value: ResourceColor): this
    optionFont(value: Font): this
    optionFontColor(value: ResourceColor): this
    onSelect(value: ((index: number,value: string) => void)): this
    space(value: Length): this
    arrowPosition(value: ArrowPosition): this
    optionWidth(value: Dimension | OptionWidthMode): this
    optionHeight(value: Dimension): this
    menuBackgroundColor(value: ResourceColor): this
    menuBackgroundBlurStyle(value: BlurStyle): this
    controlSize(value: ControlSize): this
    menuItemContentModifier(value: ContentModifier): this
    divider(value: DividerOptions | undefined): this
    menuAlign(alignType: MenuAlignType, offset?: Offset): this
    _onChangeEvent_selected(callback: ((selected: number | Resource) => void)): void
    _onChangeEvent_value(callback: ((value: ResourceStr) => void)): void
    attributeModifier(value: AttributeModifier<SelectAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export interface UISelectAttribute extends UICommonMethod {
    @memo
    selected(value: number | Resource): this
    @memo
    value(value: ResourceStr): this
    @memo
    font(value: Font): this
    @memo
    fontColor(value: ResourceColor): this
    @memo
    selectedOptionBgColor(value: ResourceColor): this
    @memo
    selectedOptionFont(value: Font): this
    @memo
    selectedOptionFontColor(value: ResourceColor): this
    @memo
    optionBgColor(value: ResourceColor): this
    @memo
    optionFont(value: Font): this
    @memo
    optionFontColor(value: ResourceColor): this
    @memo
    onSelect(value: ((index: number,value: string) => void)): this
    @memo
    space(value: Length): this
    @memo
    arrowPosition(value: ArrowPosition): this
    @memo
    optionWidth(value: Dimension | OptionWidthMode): this
    @memo
    optionHeight(value: Dimension): this
    @memo
    menuBackgroundColor(value: ResourceColor): this
    @memo
    menuBackgroundBlurStyle(value: BlurStyle): this
    @memo
    controlSize(value: ControlSize): this
    @memo
    menuItemContentModifier(value: ContentModifier): this
    @memo
    divider(value: DividerOptions | undefined): this
    @memo
    menuAlign(alignType: MenuAlignType, offset?: Offset): this
    @memo
    _onChangeEvent_selected(callback: ((selected: number | Resource) => void)): void
    @memo
    _onChangeEvent_value(callback: ((value: ResourceStr) => void)): void
    @memo
    attributeModifier(value: AttributeModifier<SelectAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkSelectStyle extends ArkCommonMethodStyle implements SelectAttribute {
    selected_value?: number | Resource
    value_value?: ResourceStr
    font_value?: Font
    fontColor_value?: ResourceColor
    selectedOptionBgColor_value?: ResourceColor
    selectedOptionFont_value?: Font
    selectedOptionFontColor_value?: ResourceColor
    optionBgColor_value?: ResourceColor
    optionFont_value?: Font
    optionFontColor_value?: ResourceColor
    onSelect_value?: ((index: number,value: string) => void)
    space_value?: Length
    arrowPosition_value?: ArrowPosition
    optionWidth_value?: Dimension | OptionWidthMode
    optionHeight_value?: Dimension
    menuBackgroundColor_value?: ResourceColor
    menuBackgroundBlurStyle_value?: BlurStyle
    controlSize_value?: ControlSize
    menuItemContentModifier_value?: ContentModifier
    divider_value?: DividerOptions | undefined
    public selected(value: number | Resource): this {
        return this
    }
    public value(value: ResourceStr): this {
        return this
    }
    public font(value: Font): this {
        return this
    }
    public fontColor(value: ResourceColor): this {
        return this
    }
    public selectedOptionBgColor(value: ResourceColor): this {
        return this
    }
    public selectedOptionFont(value: Font): this {
        return this
    }
    public selectedOptionFontColor(value: ResourceColor): this {
        return this
    }
    public optionBgColor(value: ResourceColor): this {
        return this
    }
    public optionFont(value: Font): this {
        return this
    }
    public optionFontColor(value: ResourceColor): this {
        return this
    }
    public onSelect(value: ((index: number,value: string) => void)): this {
        return this
    }
    public space(value: Length): this {
        return this
    }
    public arrowPosition(value: ArrowPosition): this {
        return this
    }
    public optionWidth(value: Dimension | OptionWidthMode): this {
        return this
    }
    public optionHeight(value: Dimension): this {
        return this
    }
    public menuBackgroundColor(value: ResourceColor): this {
        return this
    }
    public menuBackgroundBlurStyle(value: BlurStyle): this {
        return this
    }
    public controlSize(value: ControlSize): this {
        return this
    }
    public menuItemContentModifier(value: ContentModifier): this {
        return this
    }
    public divider(value: DividerOptions | undefined): this {
        return this
    }
    public menuAlign(alignType: MenuAlignType, offset?: Offset): this {
        return this
    }
    public _onChangeEvent_selected(callback: ((selected: number | Resource) => void)): void {
        throw new Error("Unimplmented")
    }
    public _onChangeEvent_value(callback: ((value: ResourceStr) => void)): void {
        throw new Error("Unimplmented")
    }
    public attributeModifier(value: AttributeModifier<SelectAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
@memo_stable
export class ArkSelectComponent extends ArkCommonMethodComponent implements UISelectAttribute {
    getPeer(): ArkSelectPeer {
        return (this.peer as ArkSelectPeer)
    }
    @memo
    public setSelectOptions(options: Array<SelectOption>): this {
        if (this.checkPriority("setSelectOptions")) {
            const options_casted = options as (Array<SelectOption>)
            this.getPeer()?.setSelectOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    @memo
    public selected(value: number | Resource): this {
        if (this.checkPriority("selected")) {
            const value_casted = value as (number | Resource)
            this.getPeer()?.selectedAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public value(value: ResourceStr): this {
        if (this.checkPriority("value")) {
            const value_casted = value as (ResourceStr)
            this.getPeer()?.valueAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public font(value: Font): this {
        if (this.checkPriority("font")) {
            const value_casted = value as (Font)
            this.getPeer()?.fontAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public fontColor(value: ResourceColor): this {
        if (this.checkPriority("fontColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.fontColorAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public selectedOptionBgColor(value: ResourceColor): this {
        if (this.checkPriority("selectedOptionBgColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.selectedOptionBgColorAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public selectedOptionFont(value: Font): this {
        if (this.checkPriority("selectedOptionFont")) {
            const value_casted = value as (Font)
            this.getPeer()?.selectedOptionFontAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public selectedOptionFontColor(value: ResourceColor): this {
        if (this.checkPriority("selectedOptionFontColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.selectedOptionFontColorAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public optionBgColor(value: ResourceColor): this {
        if (this.checkPriority("optionBgColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.optionBgColorAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public optionFont(value: Font): this {
        if (this.checkPriority("optionFont")) {
            const value_casted = value as (Font)
            this.getPeer()?.optionFontAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public optionFontColor(value: ResourceColor): this {
        if (this.checkPriority("optionFontColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.optionFontColorAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onSelect(value: ((index: number,value: string) => void)): this {
        if (this.checkPriority("onSelect")) {
            const value_casted = value as (((index: number,value: string) => void))
            this.getPeer()?.onSelectAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public space(value: Length): this {
        if (this.checkPriority("space")) {
            const value_casted = value as (Length)
            this.getPeer()?.spaceAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public arrowPosition(value: ArrowPosition): this {
        if (this.checkPriority("arrowPosition")) {
            const value_casted = value as (ArrowPosition)
            this.getPeer()?.arrowPositionAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public optionWidth(value: Dimension | OptionWidthMode): this {
        if (this.checkPriority("optionWidth")) {
            const value_casted = value as (Dimension | OptionWidthMode)
            this.getPeer()?.optionWidthAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public optionHeight(value: Dimension): this {
        if (this.checkPriority("optionHeight")) {
            const value_casted = value as (Dimension)
            this.getPeer()?.optionHeightAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public menuBackgroundColor(value: ResourceColor): this {
        if (this.checkPriority("menuBackgroundColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.menuBackgroundColorAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public menuBackgroundBlurStyle(value: BlurStyle): this {
        if (this.checkPriority("menuBackgroundBlurStyle")) {
            const value_casted = value as (BlurStyle)
            this.getPeer()?.menuBackgroundBlurStyleAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public controlSize(value: ControlSize): this {
        if (this.checkPriority("controlSize")) {
            const value_casted = value as (ControlSize)
            this.getPeer()?.controlSizeAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public menuItemContentModifier(value: ContentModifier): this {
        if (this.checkPriority("menuItemContentModifier")) {
            const value_casted = value as (ContentModifier)
            this.getPeer()?.menuItemContentModifierAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public divider(value: DividerOptions | undefined): this {
        if (this.checkPriority("divider")) {
            const value_casted = value as (DividerOptions | undefined)
            this.getPeer()?.dividerAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public menuAlign(alignType: MenuAlignType, offset?: Offset): this {
        if (this.checkPriority("menuAlign")) {
            const alignType_casted = alignType as (MenuAlignType)
            const offset_casted = offset as (Offset | undefined)
            this.getPeer()?.menuAlignAttribute(alignType_casted, offset_casted)
            return this
        }
        return this
    }
    @memo
    public _onChangeEvent_selected(callback: ((selected: number | Resource) => void)): void {
        if (this.checkPriority("_onChangeEvent_selected")) {
            const callback_casted = callback as (((selected: number | Resource) => void))
            this.getPeer()?._onChangeEvent_selectedAttribute(callback_casted)
            return
        }
        return
    }
    @memo
    public _onChangeEvent_value(callback: ((value: ResourceStr) => void)): void {
        if (this.checkPriority("_onChangeEvent_value")) {
            const callback_casted = callback as (((value: ResourceStr) => void))
            this.getPeer()?._onChangeEvent_valueAttribute(callback_casted)
            return
        }
        return
    }
    @memo
    public attributeModifier(value: AttributeModifier<SelectAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
@memo
@BuilderLambda("Select")
export function Select(
    options: Array<SelectOption>,
    @memo
    content_?: () => void,
): SelectAttribute {
    throw new Error("Not implemented")
}

@memo
export function Select(
    @memo
    style: ((attributes: UISelectAttribute) => void) | undefined,
    options: Array<SelectOption>,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkSelectComponent>((): ArkSelectComponent => {
        return new ArkSelectComponent()
    })
    NodeAttach<ArkSelectPeer>((): ArkSelectPeer => ArkSelectPeer.create(receiver), (_: ArkSelectPeer): void => {
        receiver.setSelectOptions(options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
