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

import { SymbolGlyphModifier_serializer } from "./../SymbolGlyphModifier"
import { SerializerBase, DeserializerBase, Finalizable, runtimeType, RuntimeType, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { extractors, AttributeModifier, hookTabContentAttributeModifier, AttributeUpdater } from "#handwritten"
import { ModifierStateManager } from '../CommonModifier';
import { SymbolGlyphModifier } from "arkui.SymbolGlyphModifier"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackTransformer } from "./../CallbackTransformer"
import { ComponentContentBase_serializer } from "./../ComponentContent"
import { ArkThemeScopeManager } from "#arktheme"
import { Resource_serializer } from "./../framework/resource"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { ComponentContentBase } from "arkui.ComponentContent"
import { Resource } from "global.resource"
import { CustomBuilder } from "./builder"
import { VoidCallback, ResourceColor, Length, ResourceStr, Font, Padding, Dimension, LocalizedPadding, Font_serializer, Padding_serializer, LocalizedPadding_serializer } from "./units"
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { Color, TextOverflow, TextHeightAdaptivePolicy, VerticalAlign } from "./enums"
import { TabContentModifier } from "./../TabContentModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
export class TabBarSymbolInternal {
    public static fromPtr(ptr: KPointer): TabBarSymbol {
        return new TabBarSymbol(ptr)
    }
}
export class TabBarSymbol implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get normal(): SymbolGlyphModifier {
        return this.getNormal()
    }
    set normal(normal: SymbolGlyphModifier) {
        this.setNormal(normal)
    }
    get selected(): SymbolGlyphModifier | undefined {
        return this.getSelected()
    }
    set selected(selected: SymbolGlyphModifier | undefined) {
        const selected_NonNull  = (selected as SymbolGlyphModifier | undefined)
        this.setSelected(selected_NonNull)
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, TabBarSymbol.getFinalizer())
    }
    constructor() {
        this(TabBarSymbol.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._TabBarSymbol_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._TabBarSymbol_getFinalizer()
    }
    private getNormal(): SymbolGlyphModifier {
        return this.getNormal_serialize()
    }
    private setNormal(normal: SymbolGlyphModifier): void {
        const normal_casted = normal as (SymbolGlyphModifier)
        this.setNormal_serialize(normal_casted)
        return
    }
    private getSelected(): SymbolGlyphModifier | undefined {
        return this.getSelected_serialize()
    }
    private setSelected(selected: SymbolGlyphModifier | undefined): void {
        const selected_casted = selected as (SymbolGlyphModifier | undefined)
        this.setSelected_serialize(selected_casted)
        return
    }
    private getNormal_serialize(): SymbolGlyphModifier {
        const retval  = ArkUIGeneratedNativeModule._TabBarSymbol_getNormal(this.peer!.ptr)
        const obj : SymbolGlyphModifier = extractors.fromSymbolGlyphModifierPtr(retval)
        return obj
    }
    private setNormal_serialize(normal: SymbolGlyphModifier): void {
        ArkUIGeneratedNativeModule._TabBarSymbol_setNormal(this.peer!.ptr, extractors.toSymbolGlyphModifierPtr(normal))
    }
    private getSelected_serialize(): SymbolGlyphModifier | undefined {
        const retval  = ArkUIGeneratedNativeModule._TabBarSymbol_getSelected(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : SymbolGlyphModifier | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = (SymbolGlyphModifier_serializer.read(retvalDeserializer) as SymbolGlyphModifier)
        }
        const returnResult : SymbolGlyphModifier | undefined = buffer
        return returnResult
    }
    private setSelected_serialize(selected: SymbolGlyphModifier | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (selected !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const selectedTmpValue  = selected!
            SymbolGlyphModifier_serializer.write(thisSerializer, selectedTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TabBarSymbol_setSelected(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class ArkTabContentPeer extends ArkCommonMethodPeer {
    attributeSet?: TabContentModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkTabContentPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._TabContent_construct(peerId, flags)
        const _peer  = new ArkTabContentPeer(_peerPtr, peerId, 'TabContent', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setTabContentOptionsAttribute(): void {
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
        ArkUIGeneratedNativeModule._TabContentInterface_setTabContentOptions(this.peer.ptr)
    }
    setTabBarAttribute(value: ComponentContentBase | SubTabBarStyle | BottomTabBarStyle | string | Resource | CustomBuilder | TabBarOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof ComponentContentBase) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as ComponentContentBase
                ComponentContentBase_serializer.write(thisSerializer, valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof SubTabBarStyle) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as SubTabBarStyle
                SubTabBarStyle_serializer.write(thisSerializer, valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof BottomTabBarStyle) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as BottomTabBarStyle
                BottomTabBarStyle_serializer.write(thisSerializer, valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((3).toByte())
                const valueTmpValueForIdx3  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx3)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((4).toByte())
                const valueTmpValueForIdx4  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx4)
            } else if (valueTmpValue instanceof CustomBuilder) {
                thisSerializer.writeInt8((5).toByte())
                const valueTmpValueForIdx5  = valueTmpValue as CustomBuilder
                thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(valueTmpValueForIdx5))
            } else if (valueTmpValue instanceof TabBarOptions) {
                thisSerializer.writeInt8((6).toByte())
                const valueTmpValueForIdx6  = valueTmpValue as TabBarOptions
                TabBarOptions_serializer.write(thisSerializer, valueTmpValueForIdx6)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TabContentAttribute_setTabBar(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnWillShowAttribute(value: VoidCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TabContentAttribute_setOnWillShow(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnWillHideAttribute(value: VoidCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TabContentAttribute_setOnWillHide(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export enum SelectedMode {
    INDICATOR = 0,
    BOARD = 1
}
export enum LayoutMode {
    AUTO = 0,
    VERTICAL = 1,
    HORIZONTAL = 2
}
export interface SubTabBarIndicatorStyle {
    color?: ResourceColor;
    height?: Length;
    width?: Length;
    borderRadius?: Length;
    marginTop?: Length;
}
export interface BoardStyle {
    borderRadius?: Length;
}
export interface TabBarLabelStyle {
    overflow?: TextOverflow;
    maxLines?: int32;
    minFontSize?: double | ResourceStr;
    maxFontSize?: double | ResourceStr;
    heightAdaptivePolicy?: TextHeightAdaptivePolicy;
    font?: Font;
    selectedColor?: ResourceColor;
    unselectedColor?: ResourceColor;
}
export interface TabBarIconStyle {
    selectedColor?: ResourceColor;
    unselectedColor?: ResourceColor;
}
export interface TabBarOptions {
    icon?: string | Resource;
    text?: string | Resource;
}
export interface TabContentAttribute extends CommonMethod {
    setTabContentOptions(): this {
        throw new Error("Unimplemented method setTabContentOptions")
    }
    tabBar(value: ComponentContentBase | SubTabBarStyle | BottomTabBarStyle | string | Resource | CustomBuilder | TabBarOptions | undefined): this {
        throw new Error("Unimplemented method tabBar")
    }
    onWillShow(value: VoidCallback | undefined): this {
        throw new Error("Unimplemented method onWillShow")
    }
    onWillHide(value: VoidCallback | undefined): this {
        throw new Error("Unimplemented method onWillHide")
    }
    attributeModifier(value: AttributeModifier<TabContentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkTabContentStyle extends ArkCommonMethodStyle implements TabContentAttribute {
    tabBar_value?: ComponentContentBase | SubTabBarStyle | BottomTabBarStyle | string | Resource | CustomBuilder | TabBarOptions | undefined
    onWillShow_value?: VoidCallback | undefined
    onWillHide_value?: VoidCallback | undefined
    attributeModifier_value?: AttributeModifier<TabContentAttribute> | AttributeModifier<CommonMethod> | undefined
    setTabContentOptions(): this {
        return this
    }
    tabBar(value: ComponentContentBase | SubTabBarStyle | BottomTabBarStyle | string | Resource | CustomBuilder | TabBarOptions | undefined): this {
        return this
    }
    onWillShow(value: VoidCallback | undefined): this {
        return this
    }
    onWillHide(value: VoidCallback | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<TabContentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkTabContentComponent extends ArkCommonMethodComponent implements TabContentAttribute {
    getPeer(): ArkTabContentPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkTabContentPeer)
    }
    public setTabContentOptions(): this {
        if (this.checkPriority("setTabContentOptions")) {
            this.getPeer()?.setTabContentOptionsAttribute()
            this.applyOptionsFinish('TabContentAttribute');
            return this
        }
        return this
    }
    public tabBar(value: ComponentContentBase | SubTabBarStyle | BottomTabBarStyle | string | Resource | CustomBuilder | TabBarOptions | undefined): this {
        if (this.checkPriority("tabBar")) {
            const value_casted = value as (ComponentContentBase | SubTabBarStyle | BottomTabBarStyle | string | Resource | CustomBuilder | TabBarOptions | undefined)
            this.getPeer()?.setTabBarAttribute(value_casted)
            return this
        }
        return this
    }
    public onWillShow(value: VoidCallback | undefined): this {
        if (this.checkPriority("onWillShow")) {
            const value_casted = value as (VoidCallback | undefined)
            this.getPeer()?.setOnWillShowAttribute(value_casted)
            return this
        }
        return this
    }
    public onWillHide(value: VoidCallback | undefined): this {
        if (this.checkPriority("onWillHide")) {
            const value_casted = value as (VoidCallback | undefined)
            this.getPeer()?.setOnWillHideAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<TabContentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
          hookTabContentAttributeModifier(this, value);
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
export class SubTabBarStyle {
    _content?: ResourceStr | ResourceStr | ComponentContentBase | undefined
    _indicator?: SubTabBarIndicatorStyle | undefined
    _selectedMode?: SelectedMode | undefined
    _board?: BoardStyle | undefined
    _labelStyle?: TabBarLabelStyle | undefined
    _padding?: Padding | Dimension | LocalizedPadding | undefined
    _id?: string | undefined
    constructor(content: ResourceStr | ResourceStr | ComponentContentBase) {
        this._content = content
    }
    static of(content: ResourceStr | ComponentContentBase): SubTabBarStyle {
        return new SubTabBarStyle(content)
    }
    indicator(style: SubTabBarIndicatorStyle): this {
        this._indicator = style
        return this
    }
    selectedMode(value: SelectedMode): this {
        this._selectedMode = value
        return this
    }
    board(value: BoardStyle): this {
        this._board = value
        return this
    }
    labelStyle(style: TabBarLabelStyle): this {
        this._labelStyle = style
        return this
    }
    public padding(value: Padding | Dimension): this {
        this._padding = value
        return this
    }
    public padding(value: LocalizedPadding): this {
        this._padding = value
        return this
    }
    id(value: string): this {
        this._id = value
        return this
    }
}
export class BottomTabBarStyle {
    _icon?: ResourceStr | TabBarSymbol | undefined
    _text?: ResourceStr | undefined
    _labelStyle?: TabBarLabelStyle | undefined
    _padding?: Padding | Dimension | LocalizedPadding | undefined
    _layoutMode?: LayoutMode | undefined
    _verticalAlign?: VerticalAlign | undefined
    _symmetricExtensible?: boolean | undefined
    _id?: string | undefined
    _iconStyle?: TabBarIconStyle | undefined
    constructor(icon: ResourceStr | TabBarSymbol, text: ResourceStr) {
        this._icon = icon
        this._text = text
    }
    static of(icon: ResourceStr | TabBarSymbol, text: ResourceStr): BottomTabBarStyle {
        return new BottomTabBarStyle(icon, text)
    }
    labelStyle(style: TabBarLabelStyle): this {
        this._labelStyle = style
        return this
    }
    padding(value: Padding | Dimension | LocalizedPadding): this {
        this._padding = value
        return this
    }
    layoutMode(value: LayoutMode): this {
        this._layoutMode = value
        return this
    }
    verticalAlign(value: VerticalAlign): this {
        this._verticalAlign = value
        return this
    }
    symmetricExtensible(value: boolean): this {
        this._symmetricExtensible = value
        return this
    }
    id(value: string): this {
        this._id = value
        return this
    }
    iconStyle(style: TabBarIconStyle): this {
        this._iconStyle = style
        return this
    }
}
export class TabBarSymbol_serializer {
    public static write(buffer: SerializerBase, value: TabBarSymbol): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): TabBarSymbol {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return TabBarSymbolInternal.fromPtr(ptr)
    }
}
export class TabBarIconStyle_serializer {
    public static write(buffer: SerializerBase, value: TabBarIconStyle): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForSelectedColor  = value.selectedColor
        if (valueHolderForSelectedColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSelectedColorTmpValue  = valueHolderForSelectedColor!
            if (valueHolderForSelectedColorTmpValue instanceof Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForSelectedColorTmpValueForIdx0  = valueHolderForSelectedColorTmpValue as Color
                valueSerializer.writeInt32(valueHolderForSelectedColorTmpValueForIdx0.getOrdinal())
            } else if (valueHolderForSelectedColorTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForSelectedColorTmpValueForIdx1  = valueHolderForSelectedColorTmpValue as int32
                valueSerializer.writeInt32(valueHolderForSelectedColorTmpValueForIdx1)
            } else if (valueHolderForSelectedColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForSelectedColorTmpValueForIdx2  = valueHolderForSelectedColorTmpValue as string
                valueSerializer.writeString(valueHolderForSelectedColorTmpValueForIdx2)
            } else if (valueHolderForSelectedColorTmpValue instanceof Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForSelectedColorTmpValueForIdx3  = valueHolderForSelectedColorTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForSelectedColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForUnselectedColor  = value.unselectedColor
        if (valueHolderForUnselectedColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForUnselectedColorTmpValue  = valueHolderForUnselectedColor!
            if (valueHolderForUnselectedColorTmpValue instanceof Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForUnselectedColorTmpValueForIdx0  = valueHolderForUnselectedColorTmpValue as Color
                valueSerializer.writeInt32(valueHolderForUnselectedColorTmpValueForIdx0.getOrdinal())
            } else if (valueHolderForUnselectedColorTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForUnselectedColorTmpValueForIdx1  = valueHolderForUnselectedColorTmpValue as int32
                valueSerializer.writeInt32(valueHolderForUnselectedColorTmpValueForIdx1)
            } else if (valueHolderForUnselectedColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForUnselectedColorTmpValueForIdx2  = valueHolderForUnselectedColorTmpValue as string
                valueSerializer.writeString(valueHolderForUnselectedColorTmpValueForIdx2)
            } else if (valueHolderForUnselectedColorTmpValue instanceof Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForUnselectedColorTmpValueForIdx3  = valueHolderForUnselectedColorTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForUnselectedColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): TabBarIconStyle {
        let valueDeserializer : DeserializerBase = buffer
        const selectedColorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let selectedColorTmpBuf : ResourceColor | undefined = undefined
        if ((selectedColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const selectedColorTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let selectedColorTmpBuf_ : Color | int32 | string | Resource | undefined
            if (selectedColorTmpBuf_UnionSelector == (0).toChar()) {
                selectedColorTmpBuf_ = Color.values()[valueDeserializer.readInt32()]
            } else if (selectedColorTmpBuf_UnionSelector == (1).toChar()) {
                selectedColorTmpBuf_ = valueDeserializer.readInt32()
            } else if (selectedColorTmpBuf_UnionSelector == (2).toChar()) {
                selectedColorTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (selectedColorTmpBuf_UnionSelector == (3).toChar()) {
                selectedColorTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for selectedColorTmpBuf_ has to be chosen through deserialisation.")
            }
            selectedColorTmpBuf = (selectedColorTmpBuf_ as Color | int32 | string | Resource)
        }
        const selectedColorTmpResult : ResourceColor | undefined = selectedColorTmpBuf
        const unselectedColorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let unselectedColorTmpBuf : ResourceColor | undefined = undefined
        if ((unselectedColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const unselectedColorTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let unselectedColorTmpBuf_ : Color | int32 | string | Resource | undefined
            if (unselectedColorTmpBuf_UnionSelector == (0).toChar()) {
                unselectedColorTmpBuf_ = Color.values()[valueDeserializer.readInt32()]
            } else if (unselectedColorTmpBuf_UnionSelector == (1).toChar()) {
                unselectedColorTmpBuf_ = valueDeserializer.readInt32()
            } else if (unselectedColorTmpBuf_UnionSelector == (2).toChar()) {
                unselectedColorTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (unselectedColorTmpBuf_UnionSelector == (3).toChar()) {
                unselectedColorTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for unselectedColorTmpBuf_ has to be chosen through deserialisation.")
            }
            unselectedColorTmpBuf = (unselectedColorTmpBuf_ as Color | int32 | string | Resource)
        }
        const unselectedColorTmpResult : ResourceColor | undefined = unselectedColorTmpBuf
        let value : TabBarIconStyle = ({selectedColor: selectedColorTmpResult, unselectedColor: unselectedColorTmpResult} as TabBarIconStyle)
        return value
    }
}
export class TabBarOptions_serializer {
    public static write(buffer: SerializerBase, value: TabBarOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForIcon  = value.icon
        if (valueHolderForIcon !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForIconTmpValue  = valueHolderForIcon!
            if (valueHolderForIconTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForIconTmpValueForIdx0  = valueHolderForIconTmpValue as string
                valueSerializer.writeString(valueHolderForIconTmpValueForIdx0)
            } else if (valueHolderForIconTmpValue instanceof Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForIconTmpValueForIdx1  = valueHolderForIconTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForIconTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForText  = value.text
        if (valueHolderForText !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTextTmpValue  = valueHolderForText!
            if (valueHolderForTextTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForTextTmpValueForIdx0  = valueHolderForTextTmpValue as string
                valueSerializer.writeString(valueHolderForTextTmpValueForIdx0)
            } else if (valueHolderForTextTmpValue instanceof Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForTextTmpValueForIdx1  = valueHolderForTextTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForTextTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): TabBarOptions {
        let valueDeserializer : DeserializerBase = buffer
        const iconTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let iconTmpBuf : string | Resource | undefined = undefined
        if ((iconTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const iconTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let iconTmpBuf_ : string | Resource | undefined
            if (iconTmpBuf_UnionSelector == (0).toChar()) {
                iconTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (iconTmpBuf_UnionSelector == (1).toChar()) {
                iconTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for iconTmpBuf_ has to be chosen through deserialisation.")
            }
            iconTmpBuf = (iconTmpBuf_ as string | Resource)
        }
        const iconTmpResult : string | Resource | undefined = iconTmpBuf
        const textTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let textTmpBuf : string | Resource | undefined = undefined
        if ((textTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const textTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let textTmpBuf_ : string | Resource | undefined
            if (textTmpBuf_UnionSelector == (0).toChar()) {
                textTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (textTmpBuf_UnionSelector == (1).toChar()) {
                textTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for textTmpBuf_ has to be chosen through deserialisation.")
            }
            textTmpBuf = (textTmpBuf_ as string | Resource)
        }
        const textTmpResult : string | Resource | undefined = textTmpBuf
        let value : TabBarOptions = ({icon: iconTmpResult, text: textTmpResult} as TabBarOptions)
        return value
    }
}
export class BoardStyle_serializer {
    public static write(buffer: SerializerBase, value: BoardStyle): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForBorderRadius  = value.borderRadius
        if (valueHolderForBorderRadius !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBorderRadiusTmpValue  = valueHolderForBorderRadius!
            if (valueHolderForBorderRadiusTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForBorderRadiusTmpValueForIdx0  = valueHolderForBorderRadiusTmpValue as string
                valueSerializer.writeString(valueHolderForBorderRadiusTmpValueForIdx0)
            } else if (valueHolderForBorderRadiusTmpValue instanceof double) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForBorderRadiusTmpValueForIdx1  = valueHolderForBorderRadiusTmpValue as double
                valueSerializer.writeFloat64(valueHolderForBorderRadiusTmpValueForIdx1)
            } else if (valueHolderForBorderRadiusTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForBorderRadiusTmpValueForIdx2  = valueHolderForBorderRadiusTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForBorderRadiusTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): BoardStyle {
        let valueDeserializer : DeserializerBase = buffer
        const borderRadiusTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let borderRadiusTmpBuf : Length | undefined = undefined
        if ((borderRadiusTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const borderRadiusTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let borderRadiusTmpBuf_ : string | double | Resource | undefined
            if (borderRadiusTmpBuf_UnionSelector == (0).toChar()) {
                borderRadiusTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (borderRadiusTmpBuf_UnionSelector == (1).toChar()) {
                borderRadiusTmpBuf_ = valueDeserializer.readFloat64()
            } else if (borderRadiusTmpBuf_UnionSelector == (2).toChar()) {
                borderRadiusTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for borderRadiusTmpBuf_ has to be chosen through deserialisation.")
            }
            borderRadiusTmpBuf = (borderRadiusTmpBuf_ as string | double | Resource)
        }
        const borderRadiusTmpResult : Length | undefined = borderRadiusTmpBuf
        let value : BoardStyle = ({borderRadius: borderRadiusTmpResult} as BoardStyle)
        return value
    }
}
export class SubTabBarIndicatorStyle_serializer {
    public static write(buffer: SerializerBase, value: SubTabBarIndicatorStyle): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForColor  = value.color
        if (valueHolderForColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForColorTmpValue  = valueHolderForColor!
            if (valueHolderForColorTmpValue instanceof Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForColorTmpValueForIdx0  = valueHolderForColorTmpValue as Color
                valueSerializer.writeInt32(valueHolderForColorTmpValueForIdx0.getOrdinal())
            } else if (valueHolderForColorTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForColorTmpValueForIdx1  = valueHolderForColorTmpValue as int32
                valueSerializer.writeInt32(valueHolderForColorTmpValueForIdx1)
            } else if (valueHolderForColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForColorTmpValueForIdx2  = valueHolderForColorTmpValue as string
                valueSerializer.writeString(valueHolderForColorTmpValueForIdx2)
            } else if (valueHolderForColorTmpValue instanceof Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForColorTmpValueForIdx3  = valueHolderForColorTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForHeight  = value.height
        if (valueHolderForHeight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForHeightTmpValue  = valueHolderForHeight!
            if (valueHolderForHeightTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForHeightTmpValueForIdx0  = valueHolderForHeightTmpValue as string
                valueSerializer.writeString(valueHolderForHeightTmpValueForIdx0)
            } else if (valueHolderForHeightTmpValue instanceof double) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForHeightTmpValueForIdx1  = valueHolderForHeightTmpValue as double
                valueSerializer.writeFloat64(valueHolderForHeightTmpValueForIdx1)
            } else if (valueHolderForHeightTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForHeightTmpValueForIdx2  = valueHolderForHeightTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForHeightTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForWidth  = value.width
        if (valueHolderForWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForWidthTmpValue  = valueHolderForWidth!
            if (valueHolderForWidthTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForWidthTmpValueForIdx0  = valueHolderForWidthTmpValue as string
                valueSerializer.writeString(valueHolderForWidthTmpValueForIdx0)
            } else if (valueHolderForWidthTmpValue instanceof double) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForWidthTmpValueForIdx1  = valueHolderForWidthTmpValue as double
                valueSerializer.writeFloat64(valueHolderForWidthTmpValueForIdx1)
            } else if (valueHolderForWidthTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForWidthTmpValueForIdx2  = valueHolderForWidthTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForWidthTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBorderRadius  = value.borderRadius
        if (valueHolderForBorderRadius !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBorderRadiusTmpValue  = valueHolderForBorderRadius!
            if (valueHolderForBorderRadiusTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForBorderRadiusTmpValueForIdx0  = valueHolderForBorderRadiusTmpValue as string
                valueSerializer.writeString(valueHolderForBorderRadiusTmpValueForIdx0)
            } else if (valueHolderForBorderRadiusTmpValue instanceof double) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForBorderRadiusTmpValueForIdx1  = valueHolderForBorderRadiusTmpValue as double
                valueSerializer.writeFloat64(valueHolderForBorderRadiusTmpValueForIdx1)
            } else if (valueHolderForBorderRadiusTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForBorderRadiusTmpValueForIdx2  = valueHolderForBorderRadiusTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForBorderRadiusTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMarginTop  = value.marginTop
        if (valueHolderForMarginTop !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMarginTopTmpValue  = valueHolderForMarginTop!
            if (valueHolderForMarginTopTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForMarginTopTmpValueForIdx0  = valueHolderForMarginTopTmpValue as string
                valueSerializer.writeString(valueHolderForMarginTopTmpValueForIdx0)
            } else if (valueHolderForMarginTopTmpValue instanceof double) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForMarginTopTmpValueForIdx1  = valueHolderForMarginTopTmpValue as double
                valueSerializer.writeFloat64(valueHolderForMarginTopTmpValueForIdx1)
            } else if (valueHolderForMarginTopTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForMarginTopTmpValueForIdx2  = valueHolderForMarginTopTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForMarginTopTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): SubTabBarIndicatorStyle {
        let valueDeserializer : DeserializerBase = buffer
        const colorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let colorTmpBuf : ResourceColor | undefined = undefined
        if ((colorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const colorTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let colorTmpBuf_ : Color | int32 | string | Resource | undefined
            if (colorTmpBuf_UnionSelector == (0).toChar()) {
                colorTmpBuf_ = Color.values()[valueDeserializer.readInt32()]
            } else if (colorTmpBuf_UnionSelector == (1).toChar()) {
                colorTmpBuf_ = valueDeserializer.readInt32()
            } else if (colorTmpBuf_UnionSelector == (2).toChar()) {
                colorTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (colorTmpBuf_UnionSelector == (3).toChar()) {
                colorTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for colorTmpBuf_ has to be chosen through deserialisation.")
            }
            colorTmpBuf = (colorTmpBuf_ as Color | int32 | string | Resource)
        }
        const colorTmpResult : ResourceColor | undefined = colorTmpBuf
        const heightTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let heightTmpBuf : Length | undefined = undefined
        if ((heightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const heightTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let heightTmpBuf_ : string | double | Resource | undefined
            if (heightTmpBuf_UnionSelector == (0).toChar()) {
                heightTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (heightTmpBuf_UnionSelector == (1).toChar()) {
                heightTmpBuf_ = valueDeserializer.readFloat64()
            } else if (heightTmpBuf_UnionSelector == (2).toChar()) {
                heightTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for heightTmpBuf_ has to be chosen through deserialisation.")
            }
            heightTmpBuf = (heightTmpBuf_ as string | double | Resource)
        }
        const heightTmpResult : Length | undefined = heightTmpBuf
        const widthTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let widthTmpBuf : Length | undefined = undefined
        if ((widthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const widthTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let widthTmpBuf_ : string | double | Resource | undefined
            if (widthTmpBuf_UnionSelector == (0).toChar()) {
                widthTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (widthTmpBuf_UnionSelector == (1).toChar()) {
                widthTmpBuf_ = valueDeserializer.readFloat64()
            } else if (widthTmpBuf_UnionSelector == (2).toChar()) {
                widthTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for widthTmpBuf_ has to be chosen through deserialisation.")
            }
            widthTmpBuf = (widthTmpBuf_ as string | double | Resource)
        }
        const widthTmpResult : Length | undefined = widthTmpBuf
        const borderRadiusTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let borderRadiusTmpBuf : Length | undefined = undefined
        if ((borderRadiusTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const borderRadiusTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let borderRadiusTmpBuf_ : string | double | Resource | undefined
            if (borderRadiusTmpBuf_UnionSelector == (0).toChar()) {
                borderRadiusTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (borderRadiusTmpBuf_UnionSelector == (1).toChar()) {
                borderRadiusTmpBuf_ = valueDeserializer.readFloat64()
            } else if (borderRadiusTmpBuf_UnionSelector == (2).toChar()) {
                borderRadiusTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for borderRadiusTmpBuf_ has to be chosen through deserialisation.")
            }
            borderRadiusTmpBuf = (borderRadiusTmpBuf_ as string | double | Resource)
        }
        const borderRadiusTmpResult : Length | undefined = borderRadiusTmpBuf
        const marginTopTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let marginTopTmpBuf : Length | undefined = undefined
        if ((marginTopTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const marginTopTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let marginTopTmpBuf_ : string | double | Resource | undefined
            if (marginTopTmpBuf_UnionSelector == (0).toChar()) {
                marginTopTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (marginTopTmpBuf_UnionSelector == (1).toChar()) {
                marginTopTmpBuf_ = valueDeserializer.readFloat64()
            } else if (marginTopTmpBuf_UnionSelector == (2).toChar()) {
                marginTopTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for marginTopTmpBuf_ has to be chosen through deserialisation.")
            }
            marginTopTmpBuf = (marginTopTmpBuf_ as string | double | Resource)
        }
        const marginTopTmpResult : Length | undefined = marginTopTmpBuf
        let value : SubTabBarIndicatorStyle = ({color: colorTmpResult, height: heightTmpResult, width: widthTmpResult, borderRadius: borderRadiusTmpResult, marginTop: marginTopTmpResult} as SubTabBarIndicatorStyle)
        return value
    }
}
export class TabBarLabelStyle_serializer {
    public static write(buffer: SerializerBase, value: TabBarLabelStyle): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForOverflow  = value.overflow
        if (valueHolderForOverflow !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOverflowTmpValue  = (valueHolderForOverflow as TextOverflow)
            valueSerializer.writeInt32(valueHolderForOverflowTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMaxLines  = value.maxLines
        if (valueHolderForMaxLines !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMaxLinesTmpValue  = valueHolderForMaxLines!
            valueSerializer.writeInt32(valueHolderForMaxLinesTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMinFontSize  = value.minFontSize
        if (valueHolderForMinFontSize !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMinFontSizeTmpValue  = valueHolderForMinFontSize!
            if (valueHolderForMinFontSizeTmpValue instanceof double) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForMinFontSizeTmpValueForIdx0  = valueHolderForMinFontSizeTmpValue as double
                valueSerializer.writeFloat64(valueHolderForMinFontSizeTmpValueForIdx0)
            } else if (valueHolderForMinFontSizeTmpValue instanceof ResourceStr) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForMinFontSizeTmpValueForIdx1  = valueHolderForMinFontSizeTmpValue as ResourceStr
                if (valueHolderForMinFontSizeTmpValueForIdx1 instanceof string) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForMinFontSizeTmpValueForIdx1ForIdx0  = valueHolderForMinFontSizeTmpValueForIdx1 as string
                    valueSerializer.writeString(valueHolderForMinFontSizeTmpValueForIdx1ForIdx0)
                } else if (valueHolderForMinFontSizeTmpValueForIdx1 instanceof Resource) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForMinFontSizeTmpValueForIdx1ForIdx1  = valueHolderForMinFontSizeTmpValueForIdx1 as Resource
                    Resource_serializer.write(valueSerializer, valueHolderForMinFontSizeTmpValueForIdx1ForIdx1)
                }
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMaxFontSize  = value.maxFontSize
        if (valueHolderForMaxFontSize !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMaxFontSizeTmpValue  = valueHolderForMaxFontSize!
            if (valueHolderForMaxFontSizeTmpValue instanceof double) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForMaxFontSizeTmpValueForIdx0  = valueHolderForMaxFontSizeTmpValue as double
                valueSerializer.writeFloat64(valueHolderForMaxFontSizeTmpValueForIdx0)
            } else if (valueHolderForMaxFontSizeTmpValue instanceof ResourceStr) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForMaxFontSizeTmpValueForIdx1  = valueHolderForMaxFontSizeTmpValue as ResourceStr
                if (valueHolderForMaxFontSizeTmpValueForIdx1 instanceof string) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForMaxFontSizeTmpValueForIdx1ForIdx0  = valueHolderForMaxFontSizeTmpValueForIdx1 as string
                    valueSerializer.writeString(valueHolderForMaxFontSizeTmpValueForIdx1ForIdx0)
                } else if (valueHolderForMaxFontSizeTmpValueForIdx1 instanceof Resource) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForMaxFontSizeTmpValueForIdx1ForIdx1  = valueHolderForMaxFontSizeTmpValueForIdx1 as Resource
                    Resource_serializer.write(valueSerializer, valueHolderForMaxFontSizeTmpValueForIdx1ForIdx1)
                }
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForHeightAdaptivePolicy  = value.heightAdaptivePolicy
        if (valueHolderForHeightAdaptivePolicy !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForHeightAdaptivePolicyTmpValue  = (valueHolderForHeightAdaptivePolicy as TextHeightAdaptivePolicy)
            valueSerializer.writeInt32(valueHolderForHeightAdaptivePolicyTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForFont  = value.font
        if (valueHolderForFont !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFontTmpValue  = valueHolderForFont!
            Font_serializer.write(valueSerializer, valueHolderForFontTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSelectedColor  = value.selectedColor
        if (valueHolderForSelectedColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSelectedColorTmpValue  = valueHolderForSelectedColor!
            if (valueHolderForSelectedColorTmpValue instanceof Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForSelectedColorTmpValueForIdx0  = valueHolderForSelectedColorTmpValue as Color
                valueSerializer.writeInt32(valueHolderForSelectedColorTmpValueForIdx0.getOrdinal())
            } else if (valueHolderForSelectedColorTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForSelectedColorTmpValueForIdx1  = valueHolderForSelectedColorTmpValue as int32
                valueSerializer.writeInt32(valueHolderForSelectedColorTmpValueForIdx1)
            } else if (valueHolderForSelectedColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForSelectedColorTmpValueForIdx2  = valueHolderForSelectedColorTmpValue as string
                valueSerializer.writeString(valueHolderForSelectedColorTmpValueForIdx2)
            } else if (valueHolderForSelectedColorTmpValue instanceof Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForSelectedColorTmpValueForIdx3  = valueHolderForSelectedColorTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForSelectedColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForUnselectedColor  = value.unselectedColor
        if (valueHolderForUnselectedColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForUnselectedColorTmpValue  = valueHolderForUnselectedColor!
            if (valueHolderForUnselectedColorTmpValue instanceof Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForUnselectedColorTmpValueForIdx0  = valueHolderForUnselectedColorTmpValue as Color
                valueSerializer.writeInt32(valueHolderForUnselectedColorTmpValueForIdx0.getOrdinal())
            } else if (valueHolderForUnselectedColorTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForUnselectedColorTmpValueForIdx1  = valueHolderForUnselectedColorTmpValue as int32
                valueSerializer.writeInt32(valueHolderForUnselectedColorTmpValueForIdx1)
            } else if (valueHolderForUnselectedColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForUnselectedColorTmpValueForIdx2  = valueHolderForUnselectedColorTmpValue as string
                valueSerializer.writeString(valueHolderForUnselectedColorTmpValueForIdx2)
            } else if (valueHolderForUnselectedColorTmpValue instanceof Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForUnselectedColorTmpValueForIdx3  = valueHolderForUnselectedColorTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForUnselectedColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): TabBarLabelStyle {
        let valueDeserializer : DeserializerBase = buffer
        const overflowTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let overflowTmpBuf : TextOverflow | undefined = undefined
        if ((overflowTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            overflowTmpBuf = TextOverflow.fromValue(valueDeserializer.readInt32())
        }
        const overflowTmpResult : TextOverflow | undefined = overflowTmpBuf
        const maxLinesTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let maxLinesTmpBuf : int32 | undefined = undefined
        if ((maxLinesTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            maxLinesTmpBuf = valueDeserializer.readInt32()
        }
        const maxLinesTmpResult : int32 | undefined = maxLinesTmpBuf
        const minFontSizeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let minFontSizeTmpBuf : double | ResourceStr | undefined = undefined
        if ((minFontSizeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const minFontSizeTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let minFontSizeTmpBuf_ : double | ResourceStr | undefined
            if (minFontSizeTmpBuf_UnionSelector == (0).toChar()) {
                minFontSizeTmpBuf_ = valueDeserializer.readFloat64()
            } else if (minFontSizeTmpBuf_UnionSelector == (1).toChar()) {
                const minFontSizeTmpBuf_BufUUnionSelector : int32 = valueDeserializer.readInt8()
                let minFontSizeTmpBuf_BufU : string | Resource | undefined
                if (minFontSizeTmpBuf_BufUUnionSelector == (0).toChar()) {
                    minFontSizeTmpBuf_BufU = (valueDeserializer.readString() as string)
                } else if (minFontSizeTmpBuf_BufUUnionSelector == (1).toChar()) {
                    minFontSizeTmpBuf_BufU = Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error("One of the branches for minFontSizeTmpBuf_BufU has to be chosen through deserialisation.")
                }
                minFontSizeTmpBuf_ = (minFontSizeTmpBuf_BufU as string | Resource)
            } else {
                throw new Error("One of the branches for minFontSizeTmpBuf_ has to be chosen through deserialisation.")
            }
            minFontSizeTmpBuf = (minFontSizeTmpBuf_ as double | ResourceStr)
        }
        const minFontSizeTmpResult : double | ResourceStr | undefined = minFontSizeTmpBuf
        const maxFontSizeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let maxFontSizeTmpBuf : double | ResourceStr | undefined = undefined
        if ((maxFontSizeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const maxFontSizeTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let maxFontSizeTmpBuf_ : double | ResourceStr | undefined
            if (maxFontSizeTmpBuf_UnionSelector == (0).toChar()) {
                maxFontSizeTmpBuf_ = valueDeserializer.readFloat64()
            } else if (maxFontSizeTmpBuf_UnionSelector == (1).toChar()) {
                const maxFontSizeTmpBuf_BufUUnionSelector : int32 = valueDeserializer.readInt8()
                let maxFontSizeTmpBuf_BufU : string | Resource | undefined
                if (maxFontSizeTmpBuf_BufUUnionSelector == (0).toChar()) {
                    maxFontSizeTmpBuf_BufU = (valueDeserializer.readString() as string)
                } else if (maxFontSizeTmpBuf_BufUUnionSelector == (1).toChar()) {
                    maxFontSizeTmpBuf_BufU = Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error("One of the branches for maxFontSizeTmpBuf_BufU has to be chosen through deserialisation.")
                }
                maxFontSizeTmpBuf_ = (maxFontSizeTmpBuf_BufU as string | Resource)
            } else {
                throw new Error("One of the branches for maxFontSizeTmpBuf_ has to be chosen through deserialisation.")
            }
            maxFontSizeTmpBuf = (maxFontSizeTmpBuf_ as double | ResourceStr)
        }
        const maxFontSizeTmpResult : double | ResourceStr | undefined = maxFontSizeTmpBuf
        const heightAdaptivePolicyTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let heightAdaptivePolicyTmpBuf : TextHeightAdaptivePolicy | undefined = undefined
        if ((heightAdaptivePolicyTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            heightAdaptivePolicyTmpBuf = TextHeightAdaptivePolicy.fromValue(valueDeserializer.readInt32())
        }
        const heightAdaptivePolicyTmpResult : TextHeightAdaptivePolicy | undefined = heightAdaptivePolicyTmpBuf
        const fontTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fontTmpBuf : Font | undefined = undefined
        if ((fontTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            fontTmpBuf = Font_serializer.read(valueDeserializer)
        }
        const fontTmpResult : Font | undefined = fontTmpBuf
        const selectedColorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let selectedColorTmpBuf : ResourceColor | undefined = undefined
        if ((selectedColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const selectedColorTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let selectedColorTmpBuf_ : Color | int32 | string | Resource | undefined
            if (selectedColorTmpBuf_UnionSelector == (0).toChar()) {
                selectedColorTmpBuf_ = Color.values()[valueDeserializer.readInt32()]
            } else if (selectedColorTmpBuf_UnionSelector == (1).toChar()) {
                selectedColorTmpBuf_ = valueDeserializer.readInt32()
            } else if (selectedColorTmpBuf_UnionSelector == (2).toChar()) {
                selectedColorTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (selectedColorTmpBuf_UnionSelector == (3).toChar()) {
                selectedColorTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for selectedColorTmpBuf_ has to be chosen through deserialisation.")
            }
            selectedColorTmpBuf = (selectedColorTmpBuf_ as Color | int32 | string | Resource)
        }
        const selectedColorTmpResult : ResourceColor | undefined = selectedColorTmpBuf
        const unselectedColorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let unselectedColorTmpBuf : ResourceColor | undefined = undefined
        if ((unselectedColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const unselectedColorTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let unselectedColorTmpBuf_ : Color | int32 | string | Resource | undefined
            if (unselectedColorTmpBuf_UnionSelector == (0).toChar()) {
                unselectedColorTmpBuf_ = Color.values()[valueDeserializer.readInt32()]
            } else if (unselectedColorTmpBuf_UnionSelector == (1).toChar()) {
                unselectedColorTmpBuf_ = valueDeserializer.readInt32()
            } else if (unselectedColorTmpBuf_UnionSelector == (2).toChar()) {
                unselectedColorTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (unselectedColorTmpBuf_UnionSelector == (3).toChar()) {
                unselectedColorTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for unselectedColorTmpBuf_ has to be chosen through deserialisation.")
            }
            unselectedColorTmpBuf = (unselectedColorTmpBuf_ as Color | int32 | string | Resource)
        }
        const unselectedColorTmpResult : ResourceColor | undefined = unselectedColorTmpBuf
        let value : TabBarLabelStyle = ({overflow: overflowTmpResult, maxLines: maxLinesTmpResult, minFontSize: minFontSizeTmpResult, maxFontSize: maxFontSizeTmpResult, heightAdaptivePolicy: heightAdaptivePolicyTmpResult, font: fontTmpResult, selectedColor: selectedColorTmpResult, unselectedColor: unselectedColorTmpResult} as TabBarLabelStyle)
        return value
    }
}
export class BottomTabBarStyle_serializer {
    public static write(buffer: SerializerBase, value: BottomTabBarStyle): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderFor_icon  = value._icon
        if (valueHolderFor_icon !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderFor_iconTmpValue  = valueHolderFor_icon!
            if (valueHolderFor_iconTmpValue instanceof ResourceStr) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderFor_iconTmpValueForIdx0  = valueHolderFor_iconTmpValue as ResourceStr
                if (valueHolderFor_iconTmpValueForIdx0 instanceof string) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderFor_iconTmpValueForIdx0ForIdx0  = valueHolderFor_iconTmpValueForIdx0 as string
                    valueSerializer.writeString(valueHolderFor_iconTmpValueForIdx0ForIdx0)
                } else if (valueHolderFor_iconTmpValueForIdx0 instanceof Resource) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderFor_iconTmpValueForIdx0ForIdx1  = valueHolderFor_iconTmpValueForIdx0 as Resource
                    Resource_serializer.write(valueSerializer, valueHolderFor_iconTmpValueForIdx0ForIdx1)
                }
            } else if (valueHolderFor_iconTmpValue instanceof TabBarSymbol) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderFor_iconTmpValueForIdx1  = valueHolderFor_iconTmpValue as TabBarSymbol
                TabBarSymbol_serializer.write(valueSerializer, valueHolderFor_iconTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderFor_text  = value._text
        if (valueHolderFor_text !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderFor_textTmpValue  = valueHolderFor_text!
            if (valueHolderFor_textTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderFor_textTmpValueForIdx0  = valueHolderFor_textTmpValue as string
                valueSerializer.writeString(valueHolderFor_textTmpValueForIdx0)
            } else if (valueHolderFor_textTmpValue instanceof Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderFor_textTmpValueForIdx1  = valueHolderFor_textTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderFor_textTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderFor_labelStyle  = value._labelStyle
        if (valueHolderFor_labelStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderFor_labelStyleTmpValue  = valueHolderFor_labelStyle!
            TabBarLabelStyle_serializer.write(valueSerializer, valueHolderFor_labelStyleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderFor_padding  = value._padding
        if (valueHolderFor_padding !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderFor_paddingTmpValue  = valueHolderFor_padding!
            if (valueHolderFor_paddingTmpValue instanceof Padding) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderFor_paddingTmpValueForIdx0  = valueHolderFor_paddingTmpValue as Padding
                Padding_serializer.write(valueSerializer, valueHolderFor_paddingTmpValueForIdx0)
            } else if (valueHolderFor_paddingTmpValue instanceof Dimension) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderFor_paddingTmpValueForIdx1  = valueHolderFor_paddingTmpValue as Dimension
                if (valueHolderFor_paddingTmpValueForIdx1 instanceof string) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderFor_paddingTmpValueForIdx1ForIdx0  = valueHolderFor_paddingTmpValueForIdx1 as string
                    valueSerializer.writeString(valueHolderFor_paddingTmpValueForIdx1ForIdx0)
                } else if (valueHolderFor_paddingTmpValueForIdx1 instanceof number) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderFor_paddingTmpValueForIdx1ForIdx1  = valueHolderFor_paddingTmpValueForIdx1 as number
                    valueSerializer.writeNumber(valueHolderFor_paddingTmpValueForIdx1ForIdx1)
                } else if (valueHolderFor_paddingTmpValueForIdx1 instanceof Resource) {
                    valueSerializer.writeInt8((2).toByte())
                    const valueHolderFor_paddingTmpValueForIdx1ForIdx2  = valueHolderFor_paddingTmpValueForIdx1 as Resource
                    Resource_serializer.write(valueSerializer, valueHolderFor_paddingTmpValueForIdx1ForIdx2)
                }
            } else if (valueHolderFor_paddingTmpValue instanceof LocalizedPadding) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderFor_paddingTmpValueForIdx2  = valueHolderFor_paddingTmpValue as LocalizedPadding
                LocalizedPadding_serializer.write(valueSerializer, valueHolderFor_paddingTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderFor_layoutMode  = value._layoutMode
        if (valueHolderFor_layoutMode !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderFor_layoutModeTmpValue  = (valueHolderFor_layoutMode as LayoutMode)
            valueSerializer.writeInt32(valueHolderFor_layoutModeTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderFor_verticalAlign  = value._verticalAlign
        if (valueHolderFor_verticalAlign !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderFor_verticalAlignTmpValue  = (valueHolderFor_verticalAlign as VerticalAlign)
            valueSerializer.writeInt32(valueHolderFor_verticalAlignTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderFor_symmetricExtensible  = value._symmetricExtensible
        if (valueHolderFor_symmetricExtensible !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderFor_symmetricExtensibleTmpValue  = valueHolderFor_symmetricExtensible!
            valueSerializer.writeBoolean(valueHolderFor_symmetricExtensibleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderFor_id  = value._id
        if (valueHolderFor_id !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderFor_idTmpValue  = valueHolderFor_id!
            valueSerializer.writeString(valueHolderFor_idTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderFor_iconStyle  = value._iconStyle
        if (valueHolderFor_iconStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderFor_iconStyleTmpValue  = valueHolderFor_iconStyle!
            TabBarIconStyle_serializer.write(valueSerializer, valueHolderFor_iconStyleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): BottomTabBarStyle {
        throw new Error("Can not deserialize builder class")
    }
}
export class SubTabBarStyle_serializer {
    public static write(buffer: SerializerBase, value: SubTabBarStyle): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderFor_content  = value._content
        if (valueHolderFor_content !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderFor_contentTmpValue  = valueHolderFor_content!
            if (valueHolderFor_contentTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderFor_contentTmpValueForIdx0  = valueHolderFor_contentTmpValue as string
                valueSerializer.writeString(valueHolderFor_contentTmpValueForIdx0)
            } else if (valueHolderFor_contentTmpValue instanceof Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderFor_contentTmpValueForIdx1  = valueHolderFor_contentTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderFor_contentTmpValueForIdx1)
            } else if (valueHolderFor_contentTmpValue instanceof ComponentContentBase) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderFor_contentTmpValueForIdx2  = valueHolderFor_contentTmpValue as ComponentContentBase
                ComponentContentBase_serializer.write(valueSerializer, valueHolderFor_contentTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderFor_indicator  = value._indicator
        if (valueHolderFor_indicator !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderFor_indicatorTmpValue  = valueHolderFor_indicator!
            SubTabBarIndicatorStyle_serializer.write(valueSerializer, valueHolderFor_indicatorTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderFor_selectedMode  = value._selectedMode
        if (valueHolderFor_selectedMode !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderFor_selectedModeTmpValue  = (valueHolderFor_selectedMode as SelectedMode)
            valueSerializer.writeInt32(valueHolderFor_selectedModeTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderFor_board  = value._board
        if (valueHolderFor_board !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderFor_boardTmpValue  = valueHolderFor_board!
            BoardStyle_serializer.write(valueSerializer, valueHolderFor_boardTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderFor_labelStyle  = value._labelStyle
        if (valueHolderFor_labelStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderFor_labelStyleTmpValue  = valueHolderFor_labelStyle!
            TabBarLabelStyle_serializer.write(valueSerializer, valueHolderFor_labelStyleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderFor_padding  = value._padding
        if (valueHolderFor_padding !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderFor_paddingTmpValue  = valueHolderFor_padding!
            if (valueHolderFor_paddingTmpValue instanceof Padding | Dimension) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderFor_paddingTmpValueForIdx0  = valueHolderFor_paddingTmpValue as Padding | Dimension
                if (valueHolderFor_paddingTmpValueForIdx0 instanceof Padding) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderFor_paddingTmpValueForIdx0ForIdx0  = valueHolderFor_paddingTmpValueForIdx0 as Padding
                    Padding_serializer.write(valueSerializer, valueHolderFor_paddingTmpValueForIdx0ForIdx0)
                } else if (valueHolderFor_paddingTmpValueForIdx0 instanceof Dimension) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderFor_paddingTmpValueForIdx0ForIdx1  = valueHolderFor_paddingTmpValueForIdx0 as Dimension
                    if (valueHolderFor_paddingTmpValueForIdx0ForIdx1 instanceof string) {
                        valueSerializer.writeInt8((0).toByte())
                        const valueHolderFor_paddingTmpValueForIdx0ForIdx1ForIdx0  = valueHolderFor_paddingTmpValueForIdx0ForIdx1 as string
                        valueSerializer.writeString(valueHolderFor_paddingTmpValueForIdx0ForIdx1ForIdx0)
                    } else if (valueHolderFor_paddingTmpValueForIdx0ForIdx1 instanceof number) {
                        valueSerializer.writeInt8((1).toByte())
                        const valueHolderFor_paddingTmpValueForIdx0ForIdx1ForIdx1  = valueHolderFor_paddingTmpValueForIdx0ForIdx1 as number
                        valueSerializer.writeNumber(valueHolderFor_paddingTmpValueForIdx0ForIdx1ForIdx1)
                    } else if (valueHolderFor_paddingTmpValueForIdx0ForIdx1 instanceof Resource) {
                        valueSerializer.writeInt8((2).toByte())
                        const valueHolderFor_paddingTmpValueForIdx0ForIdx1ForIdx2  = valueHolderFor_paddingTmpValueForIdx0ForIdx1 as Resource
                        Resource_serializer.write(valueSerializer, valueHolderFor_paddingTmpValueForIdx0ForIdx1ForIdx2)
                    }
                }
            } else if (valueHolderFor_paddingTmpValue instanceof LocalizedPadding) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderFor_paddingTmpValueForIdx1  = valueHolderFor_paddingTmpValue as LocalizedPadding
                LocalizedPadding_serializer.write(valueSerializer, valueHolderFor_paddingTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderFor_id  = value._id
        if (valueHolderFor_id !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderFor_idTmpValue  = valueHolderFor_id!
            valueSerializer.writeString(valueHolderFor_idTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): SubTabBarStyle {
        throw new Error("Can not deserialize builder class")
    }
}
