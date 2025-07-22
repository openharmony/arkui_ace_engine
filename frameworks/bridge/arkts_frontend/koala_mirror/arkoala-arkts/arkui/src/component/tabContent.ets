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

import { SymbolGlyphModifier_serializer, SymbolGlyphModifier } from "./../generated/arkui.SymbolGlyphModifier"
import { SerializerBase, DeserializerBase, Finalizable, runtimeType, RuntimeType, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { ComponentContent_serializer, ComponentContent } from "./../generated/arkui.ComponentContent"
import { Resource_serializer, Resource } from "./../generated/resource"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonMethodSet } from "./common"
import { CustomBuilder } from "./builder"
import { VoidCallback, ResourceColor, Length, ResourceStr, Font, Padding, Dimension, LocalizedPadding, Font_serializer, Padding_serializer, LocalizedPadding_serializer } from "./units"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { Color, TextOverflow, TextHeightAdaptivePolicy, VerticalAlign } from "./enums"
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
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : SymbolGlyphModifier = SymbolGlyphModifier_serializer.read(retvalDeserializer)
        return returnResult
    }
    private setNormal_serialize(normal: SymbolGlyphModifier): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        SymbolGlyphModifier_serializer.write(thisSerializer, normal)
        ArkUIGeneratedNativeModule._TabBarSymbol_setNormal(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getSelected_serialize(): SymbolGlyphModifier | undefined {
        const retval  = ArkUIGeneratedNativeModule._TabBarSymbol_getSelected(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : SymbolGlyphModifier | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED))
        {
            buffer = SymbolGlyphModifier_serializer.read(retvalDeserializer)
        }
        const returnResult : SymbolGlyphModifier | undefined = buffer
        return returnResult
    }
    private setSelected_serialize(selected: SymbolGlyphModifier | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let selected_type : int32 = RuntimeType.UNDEFINED
        selected_type = runtimeType(selected)
        thisSerializer.writeInt8((selected_type).toChar())
        if ((selected_type) != (RuntimeType.UNDEFINED)) {
            const selected_value  = selected!
            SymbolGlyphModifier_serializer.write(thisSerializer, selected_value)
        }
        ArkUIGeneratedNativeModule._TabBarSymbol_setSelected(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class ArkTabContentPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkTabContentPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._TabContent_construct(peerId, flags)
        const _peer  = new ArkTabContentPeer(_peerPtr, peerId, "TabContent", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setTabContentOptionsAttribute(): void {
        ArkUIGeneratedNativeModule._TabContentInterface_setTabContentOptions(this.peer.ptr)
    }
    setTabBarAttribute(value: ComponentContent | SubTabBarStyle | BottomTabBarStyle | string | Resource | CustomBuilder | TabBarOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isComponentContent(value_value)) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as ComponentContent
                ComponentContent_serializer.write(thisSerializer, value_value_0)
            }
            else if (((RuntimeType.OBJECT) == (value_value_type)) && (TypeChecker.isSubTabBarStyle(value_value))) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as SubTabBarStyle
                SubTabBarStyle_serializer.write(thisSerializer, value_value_1)
            }
            else if (((RuntimeType.OBJECT) == (value_value_type)) && (TypeChecker.isBottomTabBarStyle(value_value))) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as BottomTabBarStyle
                BottomTabBarStyle_serializer.write(thisSerializer, value_value_2)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((3).toChar())
                const value_value_3  = value_value as string
                thisSerializer.writeString(value_value_3)
            }
            else if (TypeChecker.isResource(value_value, false, false, false, false, false)) {
                thisSerializer.writeInt8((4).toChar())
                const value_value_4  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_4)
            }
            else if (RuntimeType.FUNCTION == value_value_type) {
                thisSerializer.writeInt8((5).toChar())
                const value_value_5  = value_value as CustomBuilder
                thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value_value_5))
            }
            else if (TypeChecker.isTabBarOptions(value_value, false, false)) {
                thisSerializer.writeInt8((6).toChar())
                const value_value_6  = value_value as TabBarOptions
                TabBarOptions_serializer.write(thisSerializer, value_value_6)
            }
        }
        ArkUIGeneratedNativeModule._TabContentAttribute_setTabBar(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnWillShowAttribute(value: VoidCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TabContentAttribute_setOnWillShow(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnWillHideAttribute(value: VoidCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
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
    maxLines?: number;
    minFontSize?: number | ResourceStr;
    maxFontSize?: number | ResourceStr;
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
    tabBar(value: ComponentContent | SubTabBarStyle | BottomTabBarStyle | string | Resource | CustomBuilder | TabBarOptions | undefined): this {
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
    tabBar_value?: ComponentContent | SubTabBarStyle | BottomTabBarStyle | string | Resource | CustomBuilder | TabBarOptions | undefined
    onWillShow_value?: VoidCallback | undefined
    onWillHide_value?: VoidCallback | undefined
    attributeModifier_value?: AttributeModifier<TabContentAttribute> | AttributeModifier<CommonMethod> | undefined
    public tabBar(value: ComponentContent | SubTabBarStyle | BottomTabBarStyle | string | Resource | CustomBuilder | TabBarOptions | undefined): this {
        return this
    }
    public onWillShow(value: VoidCallback | undefined): this {
        return this
    }
    public onWillHide(value: VoidCallback | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<TabContentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: TabContentAttribute): void {
        super.apply(target)
        if (this.tabBar_value !== undefined)
            target.tabBar(this.tabBar_value!)
        if (this.onWillShow_value !== undefined)
            target.onWillShow(this.onWillShow_value!)
        if (this.onWillHide_value !== undefined)
            target.onWillHide(this.onWillHide_value!)
    }
}

export class ArkTabContentComponent extends ArkCommonMethodComponent implements TabContentAttribute {
    getPeer(): ArkTabContentPeer {
        return (this.peer as ArkTabContentPeer)
    }
    public setTabContentOptions(): this {
        if (this.checkPriority("setTabContentOptions")) {
            this.getPeer()?.setTabContentOptionsAttribute()
            return this
        }
        return this
    }
    public tabBar(value: ComponentContent | SubTabBarStyle | BottomTabBarStyle | string | Resource | CustomBuilder | TabBarOptions | undefined): this {
        if (this.checkPriority("tabBar")) {
            const value_casted = value as (ComponentContent | SubTabBarStyle | BottomTabBarStyle | string | Resource | CustomBuilder | TabBarOptions | undefined)
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
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withTabContentStyle(receiver: TabContentAttribute, modifier: AttributeModifier<TabContentAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkTabContentStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("TabContent")
// export function TabContent(
//     
//     @memo
//     content_?: () => void,
// ): TabContentAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function TabContent(
    @memo
    style: ((attributes: TabContentAttribute) => void) | undefined,
    
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkTabContentComponent>((): ArkTabContentComponent => {
        return new ArkTabContentComponent()
    })
    NodeAttach<ArkTabContentPeer>((): ArkTabContentPeer => ArkTabContentPeer.create(receiver), (_: ArkTabContentPeer): void => {
        receiver.setTabContentOptions()
        style?.(receiver)
        withTabContentStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkTabContentSet extends ArkCommonMethodSet implements TabContentAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _tabBar_flag?: boolean
    _tabBar0_value?: ComponentContent | SubTabBarStyle | BottomTabBarStyle | string | Resource | CustomBuilder | TabBarOptions | undefined
    _onWillShow_flag?: boolean
    _onWillShow0_value?: VoidCallback | undefined
    _onWillHide_flag?: boolean
    _onWillHide0_value?: VoidCallback | undefined
    applyModifierPatch(component: TabContentAttribute): void {
        if (this._tabBar_flag)
            component.tabBar((this._tabBar0_value as ComponentContent | SubTabBarStyle | BottomTabBarStyle | string | Resource | CustomBuilder | TabBarOptions | undefined))
        if (this._onWillShow_flag)
            component.onWillShow((this._onWillShow0_value as VoidCallback | undefined))
        if (this._onWillHide_flag)
            component.onWillHide((this._onWillHide0_value as VoidCallback | undefined))
    }
    public tabBar(value: ComponentContent | SubTabBarStyle | BottomTabBarStyle | string | Resource | CustomBuilder | TabBarOptions | undefined): this {
        this._tabBar_flag = true
        this._tabBar0_value = value
        return this
    }
    public onWillShow(value: VoidCallback | undefined): this {
        this._onWillShow_flag = true
        this._onWillShow0_value = value
        return this
    }
    public onWillHide(value: VoidCallback | undefined): this {
        this._onWillHide_flag = true
        this._onWillHide0_value = value
        return this
    }
    public attributeModifier(value: AttributeModifier<TabContentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class SubTabBarStyle {
    _content?: ResourceStr | ResourceStr | ComponentContent | undefined
    _indicator?: SubTabBarIndicatorStyle | undefined
    _selectedMode?: SelectedMode | undefined
    _board?: BoardStyle | undefined
    _labelStyle?: TabBarLabelStyle | undefined
    _padding?: Padding | Dimension | LocalizedPadding | undefined
    _id?: string | undefined
    constructor(content: ResourceStr | ResourceStr | ComponentContent) {
        this._content = content
    }
    static of(content: ResourceStr | ComponentContent): SubTabBarStyle {
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
    public padding(value: Padding | Dimension | LocalizedPadding): this {
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
        const value_selectedColor  = value.selectedColor
        let value_selectedColor_type : int32 = RuntimeType.UNDEFINED
        value_selectedColor_type = runtimeType(value_selectedColor)
        valueSerializer.writeInt8((value_selectedColor_type).toChar())
        if ((value_selectedColor_type) != (RuntimeType.UNDEFINED)) {
            const value_selectedColor_value  = value_selectedColor!
            let value_selectedColor_value_type : int32 = RuntimeType.UNDEFINED
            value_selectedColor_value_type = runtimeType(value_selectedColor_value)
            if (TypeChecker.isColor(value_selectedColor_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value_selectedColor_value_0  = value_selectedColor_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_selectedColor_value_0))
            }
            else if (RuntimeType.NUMBER == value_selectedColor_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_selectedColor_value_1  = value_selectedColor_value as number
                valueSerializer.writeNumber(value_selectedColor_value_1)
            }
            else if (RuntimeType.STRING == value_selectedColor_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_selectedColor_value_2  = value_selectedColor_value as string
                valueSerializer.writeString(value_selectedColor_value_2)
            }
            else if (RuntimeType.OBJECT == value_selectedColor_value_type) {
                valueSerializer.writeInt8((3).toChar())
                const value_selectedColor_value_3  = value_selectedColor_value as Resource
                Resource_serializer.write(valueSerializer, value_selectedColor_value_3)
            }
        }
        const value_unselectedColor  = value.unselectedColor
        let value_unselectedColor_type : int32 = RuntimeType.UNDEFINED
        value_unselectedColor_type = runtimeType(value_unselectedColor)
        valueSerializer.writeInt8((value_unselectedColor_type).toChar())
        if ((value_unselectedColor_type) != (RuntimeType.UNDEFINED)) {
            const value_unselectedColor_value  = value_unselectedColor!
            let value_unselectedColor_value_type : int32 = RuntimeType.UNDEFINED
            value_unselectedColor_value_type = runtimeType(value_unselectedColor_value)
            if (TypeChecker.isColor(value_unselectedColor_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value_unselectedColor_value_0  = value_unselectedColor_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_unselectedColor_value_0))
            }
            else if (RuntimeType.NUMBER == value_unselectedColor_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_unselectedColor_value_1  = value_unselectedColor_value as number
                valueSerializer.writeNumber(value_unselectedColor_value_1)
            }
            else if (RuntimeType.STRING == value_unselectedColor_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_unselectedColor_value_2  = value_unselectedColor_value as string
                valueSerializer.writeString(value_unselectedColor_value_2)
            }
            else if (RuntimeType.OBJECT == value_unselectedColor_value_type) {
                valueSerializer.writeInt8((3).toChar())
                const value_unselectedColor_value_3  = value_unselectedColor_value as Resource
                Resource_serializer.write(valueSerializer, value_unselectedColor_value_3)
            }
        }
    }
    public static read(buffer: DeserializerBase): TabBarIconStyle {
        let valueDeserializer : DeserializerBase = buffer
        const selectedColor_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let selectedColor_buf : ResourceColor | undefined
        if ((selectedColor_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const selectedColor_buf__selector : int32 = valueDeserializer.readInt8()
            let selectedColor_buf_ : Color | number | string | Resource | undefined
            if (selectedColor_buf__selector == (0).toChar()) {
                selectedColor_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (selectedColor_buf__selector == (1).toChar()) {
                selectedColor_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (selectedColor_buf__selector == (2).toChar()) {
                selectedColor_buf_ = (valueDeserializer.readString() as string)
            }
            else if (selectedColor_buf__selector == (3).toChar()) {
                selectedColor_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for selectedColor_buf_ has to be chosen through deserialisation.")
            }
            selectedColor_buf = (selectedColor_buf_ as Color | number | string | Resource)
        }
        const selectedColor_result : ResourceColor | undefined = selectedColor_buf
        const unselectedColor_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let unselectedColor_buf : ResourceColor | undefined
        if ((unselectedColor_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const unselectedColor_buf__selector : int32 = valueDeserializer.readInt8()
            let unselectedColor_buf_ : Color | number | string | Resource | undefined
            if (unselectedColor_buf__selector == (0).toChar()) {
                unselectedColor_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (unselectedColor_buf__selector == (1).toChar()) {
                unselectedColor_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (unselectedColor_buf__selector == (2).toChar()) {
                unselectedColor_buf_ = (valueDeserializer.readString() as string)
            }
            else if (unselectedColor_buf__selector == (3).toChar()) {
                unselectedColor_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for unselectedColor_buf_ has to be chosen through deserialisation.")
            }
            unselectedColor_buf = (unselectedColor_buf_ as Color | number | string | Resource)
        }
        const unselectedColor_result : ResourceColor | undefined = unselectedColor_buf
        let value : TabBarIconStyle = ({selectedColor: selectedColor_result, unselectedColor: unselectedColor_result} as TabBarIconStyle)
        return value
    }
}
export class TabBarOptions_serializer {
    public static write(buffer: SerializerBase, value: TabBarOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_icon  = value.icon
        let value_icon_type : int32 = RuntimeType.UNDEFINED
        value_icon_type = runtimeType(value_icon)
        valueSerializer.writeInt8((value_icon_type).toChar())
        if ((value_icon_type) != (RuntimeType.UNDEFINED)) {
            const value_icon_value  = value_icon!
            let value_icon_value_type : int32 = RuntimeType.UNDEFINED
            value_icon_value_type = runtimeType(value_icon_value)
            if (RuntimeType.STRING == value_icon_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_icon_value_0  = value_icon_value as string
                valueSerializer.writeString(value_icon_value_0)
            }
            else if (RuntimeType.OBJECT == value_icon_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_icon_value_1  = value_icon_value as Resource
                Resource_serializer.write(valueSerializer, value_icon_value_1)
            }
        }
        const value_text  = value.text
        let value_text_type : int32 = RuntimeType.UNDEFINED
        value_text_type = runtimeType(value_text)
        valueSerializer.writeInt8((value_text_type).toChar())
        if ((value_text_type) != (RuntimeType.UNDEFINED)) {
            const value_text_value  = value_text!
            let value_text_value_type : int32 = RuntimeType.UNDEFINED
            value_text_value_type = runtimeType(value_text_value)
            if (RuntimeType.STRING == value_text_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_text_value_0  = value_text_value as string
                valueSerializer.writeString(value_text_value_0)
            }
            else if (RuntimeType.OBJECT == value_text_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_text_value_1  = value_text_value as Resource
                Resource_serializer.write(valueSerializer, value_text_value_1)
            }
        }
    }
    public static read(buffer: DeserializerBase): TabBarOptions {
        let valueDeserializer : DeserializerBase = buffer
        const icon_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let icon_buf : string | Resource | undefined
        if ((icon_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const icon_buf__selector : int32 = valueDeserializer.readInt8()
            let icon_buf_ : string | Resource | undefined
            if (icon_buf__selector == (0).toChar()) {
                icon_buf_ = (valueDeserializer.readString() as string)
            }
            else if (icon_buf__selector == (1).toChar()) {
                icon_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for icon_buf_ has to be chosen through deserialisation.")
            }
            icon_buf = (icon_buf_ as string | Resource)
        }
        const icon_result : string | Resource | undefined = icon_buf
        const text_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let text_buf : string | Resource | undefined
        if ((text_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const text_buf__selector : int32 = valueDeserializer.readInt8()
            let text_buf_ : string | Resource | undefined
            if (text_buf__selector == (0).toChar()) {
                text_buf_ = (valueDeserializer.readString() as string)
            }
            else if (text_buf__selector == (1).toChar()) {
                text_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for text_buf_ has to be chosen through deserialisation.")
            }
            text_buf = (text_buf_ as string | Resource)
        }
        const text_result : string | Resource | undefined = text_buf
        let value : TabBarOptions = ({icon: icon_result, text: text_result} as TabBarOptions)
        return value
    }
}
export class BoardStyle_serializer {
    public static write(buffer: SerializerBase, value: BoardStyle): void {
        let valueSerializer : SerializerBase = buffer
        const value_borderRadius  = value.borderRadius
        let value_borderRadius_type : int32 = RuntimeType.UNDEFINED
        value_borderRadius_type = runtimeType(value_borderRadius)
        valueSerializer.writeInt8((value_borderRadius_type).toChar())
        if ((value_borderRadius_type) != (RuntimeType.UNDEFINED)) {
            const value_borderRadius_value  = value_borderRadius!
            let value_borderRadius_value_type : int32 = RuntimeType.UNDEFINED
            value_borderRadius_value_type = runtimeType(value_borderRadius_value)
            if (RuntimeType.STRING == value_borderRadius_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_borderRadius_value_0  = value_borderRadius_value as string
                valueSerializer.writeString(value_borderRadius_value_0)
            }
            else if (RuntimeType.NUMBER == value_borderRadius_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_borderRadius_value_1  = value_borderRadius_value as number
                valueSerializer.writeNumber(value_borderRadius_value_1)
            }
            else if (RuntimeType.OBJECT == value_borderRadius_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_borderRadius_value_2  = value_borderRadius_value as Resource
                Resource_serializer.write(valueSerializer, value_borderRadius_value_2)
            }
        }
    }
    public static read(buffer: DeserializerBase): BoardStyle {
        let valueDeserializer : DeserializerBase = buffer
        const borderRadius_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let borderRadius_buf : Length | undefined
        if ((borderRadius_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const borderRadius_buf__selector : int32 = valueDeserializer.readInt8()
            let borderRadius_buf_ : string | number | Resource | undefined
            if (borderRadius_buf__selector == (0).toChar()) {
                borderRadius_buf_ = (valueDeserializer.readString() as string)
            }
            else if (borderRadius_buf__selector == (1).toChar()) {
                borderRadius_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (borderRadius_buf__selector == (2).toChar()) {
                borderRadius_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for borderRadius_buf_ has to be chosen through deserialisation.")
            }
            borderRadius_buf = (borderRadius_buf_ as string | number | Resource)
        }
        const borderRadius_result : Length | undefined = borderRadius_buf
        let value : BoardStyle = ({borderRadius: borderRadius_result} as BoardStyle)
        return value
    }
}
export class SubTabBarIndicatorStyle_serializer {
    public static write(buffer: SerializerBase, value: SubTabBarIndicatorStyle): void {
        let valueSerializer : SerializerBase = buffer
        const value_color  = value.color
        let value_color_type : int32 = RuntimeType.UNDEFINED
        value_color_type = runtimeType(value_color)
        valueSerializer.writeInt8((value_color_type).toChar())
        if ((value_color_type) != (RuntimeType.UNDEFINED)) {
            const value_color_value  = value_color!
            let value_color_value_type : int32 = RuntimeType.UNDEFINED
            value_color_value_type = runtimeType(value_color_value)
            if (TypeChecker.isColor(value_color_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value_color_value_0  = value_color_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_color_value_0))
            }
            else if (RuntimeType.NUMBER == value_color_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_color_value_1  = value_color_value as number
                valueSerializer.writeNumber(value_color_value_1)
            }
            else if (RuntimeType.STRING == value_color_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_color_value_2  = value_color_value as string
                valueSerializer.writeString(value_color_value_2)
            }
            else if (RuntimeType.OBJECT == value_color_value_type) {
                valueSerializer.writeInt8((3).toChar())
                const value_color_value_3  = value_color_value as Resource
                Resource_serializer.write(valueSerializer, value_color_value_3)
            }
        }
        const value_height  = value.height
        let value_height_type : int32 = RuntimeType.UNDEFINED
        value_height_type = runtimeType(value_height)
        valueSerializer.writeInt8((value_height_type).toChar())
        if ((value_height_type) != (RuntimeType.UNDEFINED)) {
            const value_height_value  = value_height!
            let value_height_value_type : int32 = RuntimeType.UNDEFINED
            value_height_value_type = runtimeType(value_height_value)
            if (RuntimeType.STRING == value_height_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_height_value_0  = value_height_value as string
                valueSerializer.writeString(value_height_value_0)
            }
            else if (RuntimeType.NUMBER == value_height_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_height_value_1  = value_height_value as number
                valueSerializer.writeNumber(value_height_value_1)
            }
            else if (RuntimeType.OBJECT == value_height_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_height_value_2  = value_height_value as Resource
                Resource_serializer.write(valueSerializer, value_height_value_2)
            }
        }
        const value_width  = value.width
        let value_width_type : int32 = RuntimeType.UNDEFINED
        value_width_type = runtimeType(value_width)
        valueSerializer.writeInt8((value_width_type).toChar())
        if ((value_width_type) != (RuntimeType.UNDEFINED)) {
            const value_width_value  = value_width!
            let value_width_value_type : int32 = RuntimeType.UNDEFINED
            value_width_value_type = runtimeType(value_width_value)
            if (RuntimeType.STRING == value_width_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_width_value_0  = value_width_value as string
                valueSerializer.writeString(value_width_value_0)
            }
            else if (RuntimeType.NUMBER == value_width_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_width_value_1  = value_width_value as number
                valueSerializer.writeNumber(value_width_value_1)
            }
            else if (RuntimeType.OBJECT == value_width_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_width_value_2  = value_width_value as Resource
                Resource_serializer.write(valueSerializer, value_width_value_2)
            }
        }
        const value_borderRadius  = value.borderRadius
        let value_borderRadius_type : int32 = RuntimeType.UNDEFINED
        value_borderRadius_type = runtimeType(value_borderRadius)
        valueSerializer.writeInt8((value_borderRadius_type).toChar())
        if ((value_borderRadius_type) != (RuntimeType.UNDEFINED)) {
            const value_borderRadius_value  = value_borderRadius!
            let value_borderRadius_value_type : int32 = RuntimeType.UNDEFINED
            value_borderRadius_value_type = runtimeType(value_borderRadius_value)
            if (RuntimeType.STRING == value_borderRadius_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_borderRadius_value_0  = value_borderRadius_value as string
                valueSerializer.writeString(value_borderRadius_value_0)
            }
            else if (RuntimeType.NUMBER == value_borderRadius_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_borderRadius_value_1  = value_borderRadius_value as number
                valueSerializer.writeNumber(value_borderRadius_value_1)
            }
            else if (RuntimeType.OBJECT == value_borderRadius_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_borderRadius_value_2  = value_borderRadius_value as Resource
                Resource_serializer.write(valueSerializer, value_borderRadius_value_2)
            }
        }
        const value_marginTop  = value.marginTop
        let value_marginTop_type : int32 = RuntimeType.UNDEFINED
        value_marginTop_type = runtimeType(value_marginTop)
        valueSerializer.writeInt8((value_marginTop_type).toChar())
        if ((value_marginTop_type) != (RuntimeType.UNDEFINED)) {
            const value_marginTop_value  = value_marginTop!
            let value_marginTop_value_type : int32 = RuntimeType.UNDEFINED
            value_marginTop_value_type = runtimeType(value_marginTop_value)
            if (RuntimeType.STRING == value_marginTop_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_marginTop_value_0  = value_marginTop_value as string
                valueSerializer.writeString(value_marginTop_value_0)
            }
            else if (RuntimeType.NUMBER == value_marginTop_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_marginTop_value_1  = value_marginTop_value as number
                valueSerializer.writeNumber(value_marginTop_value_1)
            }
            else if (RuntimeType.OBJECT == value_marginTop_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_marginTop_value_2  = value_marginTop_value as Resource
                Resource_serializer.write(valueSerializer, value_marginTop_value_2)
            }
        }
    }
    public static read(buffer: DeserializerBase): SubTabBarIndicatorStyle {
        let valueDeserializer : DeserializerBase = buffer
        const color_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let color_buf : ResourceColor | undefined
        if ((color_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const color_buf__selector : int32 = valueDeserializer.readInt8()
            let color_buf_ : Color | number | string | Resource | undefined
            if (color_buf__selector == (0).toChar()) {
                color_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (color_buf__selector == (1).toChar()) {
                color_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (color_buf__selector == (2).toChar()) {
                color_buf_ = (valueDeserializer.readString() as string)
            }
            else if (color_buf__selector == (3).toChar()) {
                color_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for color_buf_ has to be chosen through deserialisation.")
            }
            color_buf = (color_buf_ as Color | number | string | Resource)
        }
        const color_result : ResourceColor | undefined = color_buf
        const height_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let height_buf : Length | undefined
        if ((height_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const height_buf__selector : int32 = valueDeserializer.readInt8()
            let height_buf_ : string | number | Resource | undefined
            if (height_buf__selector == (0).toChar()) {
                height_buf_ = (valueDeserializer.readString() as string)
            }
            else if (height_buf__selector == (1).toChar()) {
                height_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (height_buf__selector == (2).toChar()) {
                height_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for height_buf_ has to be chosen through deserialisation.")
            }
            height_buf = (height_buf_ as string | number | Resource)
        }
        const height_result : Length | undefined = height_buf
        const width_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let width_buf : Length | undefined
        if ((width_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const width_buf__selector : int32 = valueDeserializer.readInt8()
            let width_buf_ : string | number | Resource | undefined
            if (width_buf__selector == (0).toChar()) {
                width_buf_ = (valueDeserializer.readString() as string)
            }
            else if (width_buf__selector == (1).toChar()) {
                width_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (width_buf__selector == (2).toChar()) {
                width_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for width_buf_ has to be chosen through deserialisation.")
            }
            width_buf = (width_buf_ as string | number | Resource)
        }
        const width_result : Length | undefined = width_buf
        const borderRadius_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let borderRadius_buf : Length | undefined
        if ((borderRadius_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const borderRadius_buf__selector : int32 = valueDeserializer.readInt8()
            let borderRadius_buf_ : string | number | Resource | undefined
            if (borderRadius_buf__selector == (0).toChar()) {
                borderRadius_buf_ = (valueDeserializer.readString() as string)
            }
            else if (borderRadius_buf__selector == (1).toChar()) {
                borderRadius_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (borderRadius_buf__selector == (2).toChar()) {
                borderRadius_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for borderRadius_buf_ has to be chosen through deserialisation.")
            }
            borderRadius_buf = (borderRadius_buf_ as string | number | Resource)
        }
        const borderRadius_result : Length | undefined = borderRadius_buf
        const marginTop_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let marginTop_buf : Length | undefined
        if ((marginTop_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const marginTop_buf__selector : int32 = valueDeserializer.readInt8()
            let marginTop_buf_ : string | number | Resource | undefined
            if (marginTop_buf__selector == (0).toChar()) {
                marginTop_buf_ = (valueDeserializer.readString() as string)
            }
            else if (marginTop_buf__selector == (1).toChar()) {
                marginTop_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (marginTop_buf__selector == (2).toChar()) {
                marginTop_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for marginTop_buf_ has to be chosen through deserialisation.")
            }
            marginTop_buf = (marginTop_buf_ as string | number | Resource)
        }
        const marginTop_result : Length | undefined = marginTop_buf
        let value : SubTabBarIndicatorStyle = ({color: color_result, height: height_result, width: width_result, borderRadius: borderRadius_result, marginTop: marginTop_result} as SubTabBarIndicatorStyle)
        return value
    }
}
export class TabBarLabelStyle_serializer {
    public static write(buffer: SerializerBase, value: TabBarLabelStyle): void {
        let valueSerializer : SerializerBase = buffer
        const value_overflow  = value.overflow
        let value_overflow_type : int32 = RuntimeType.UNDEFINED
        value_overflow_type = runtimeType(value_overflow)
        valueSerializer.writeInt8((value_overflow_type).toChar())
        if ((value_overflow_type) != (RuntimeType.UNDEFINED)) {
            const value_overflow_value  = (value_overflow as TextOverflow)
            valueSerializer.writeInt32(TypeChecker.TextOverflow_ToNumeric(value_overflow_value))
        }
        const value_maxLines  = value.maxLines
        let value_maxLines_type : int32 = RuntimeType.UNDEFINED
        value_maxLines_type = runtimeType(value_maxLines)
        valueSerializer.writeInt8((value_maxLines_type).toChar())
        if ((value_maxLines_type) != (RuntimeType.UNDEFINED)) {
            const value_maxLines_value  = value_maxLines!
            valueSerializer.writeNumber(value_maxLines_value)
        }
        const value_minFontSize  = value.minFontSize
        let value_minFontSize_type : int32 = RuntimeType.UNDEFINED
        value_minFontSize_type = runtimeType(value_minFontSize)
        valueSerializer.writeInt8((value_minFontSize_type).toChar())
        if ((value_minFontSize_type) != (RuntimeType.UNDEFINED)) {
            const value_minFontSize_value  = value_minFontSize!
            let value_minFontSize_value_type : int32 = RuntimeType.UNDEFINED
            value_minFontSize_value_type = runtimeType(value_minFontSize_value)
            if (RuntimeType.NUMBER == value_minFontSize_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_minFontSize_value_0  = value_minFontSize_value as number
                valueSerializer.writeNumber(value_minFontSize_value_0)
            }
            else if ((RuntimeType.STRING == value_minFontSize_value_type) || (RuntimeType.OBJECT == value_minFontSize_value_type)) {
                valueSerializer.writeInt8((1).toChar())
                const value_minFontSize_value_1  = value_minFontSize_value as ResourceStr
                let value_minFontSize_value_1_type : int32 = RuntimeType.UNDEFINED
                value_minFontSize_value_1_type = runtimeType(value_minFontSize_value_1)
                if (RuntimeType.STRING == value_minFontSize_value_1_type) {
                    valueSerializer.writeInt8((0).toChar())
                    const value_minFontSize_value_1_0  = value_minFontSize_value_1 as string
                    valueSerializer.writeString(value_minFontSize_value_1_0)
                }
                else if (RuntimeType.OBJECT == value_minFontSize_value_1_type) {
                    valueSerializer.writeInt8((1).toChar())
                    const value_minFontSize_value_1_1  = value_minFontSize_value_1 as Resource
                    Resource_serializer.write(valueSerializer, value_minFontSize_value_1_1)
                }
            }
        }
        const value_maxFontSize  = value.maxFontSize
        let value_maxFontSize_type : int32 = RuntimeType.UNDEFINED
        value_maxFontSize_type = runtimeType(value_maxFontSize)
        valueSerializer.writeInt8((value_maxFontSize_type).toChar())
        if ((value_maxFontSize_type) != (RuntimeType.UNDEFINED)) {
            const value_maxFontSize_value  = value_maxFontSize!
            let value_maxFontSize_value_type : int32 = RuntimeType.UNDEFINED
            value_maxFontSize_value_type = runtimeType(value_maxFontSize_value)
            if (RuntimeType.NUMBER == value_maxFontSize_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_maxFontSize_value_0  = value_maxFontSize_value as number
                valueSerializer.writeNumber(value_maxFontSize_value_0)
            }
            else if ((RuntimeType.STRING == value_maxFontSize_value_type) || (RuntimeType.OBJECT == value_maxFontSize_value_type)) {
                valueSerializer.writeInt8((1).toChar())
                const value_maxFontSize_value_1  = value_maxFontSize_value as ResourceStr
                let value_maxFontSize_value_1_type : int32 = RuntimeType.UNDEFINED
                value_maxFontSize_value_1_type = runtimeType(value_maxFontSize_value_1)
                if (RuntimeType.STRING == value_maxFontSize_value_1_type) {
                    valueSerializer.writeInt8((0).toChar())
                    const value_maxFontSize_value_1_0  = value_maxFontSize_value_1 as string
                    valueSerializer.writeString(value_maxFontSize_value_1_0)
                }
                else if (RuntimeType.OBJECT == value_maxFontSize_value_1_type) {
                    valueSerializer.writeInt8((1).toChar())
                    const value_maxFontSize_value_1_1  = value_maxFontSize_value_1 as Resource
                    Resource_serializer.write(valueSerializer, value_maxFontSize_value_1_1)
                }
            }
        }
        const value_heightAdaptivePolicy  = value.heightAdaptivePolicy
        let value_heightAdaptivePolicy_type : int32 = RuntimeType.UNDEFINED
        value_heightAdaptivePolicy_type = runtimeType(value_heightAdaptivePolicy)
        valueSerializer.writeInt8((value_heightAdaptivePolicy_type).toChar())
        if ((value_heightAdaptivePolicy_type) != (RuntimeType.UNDEFINED)) {
            const value_heightAdaptivePolicy_value  = (value_heightAdaptivePolicy as TextHeightAdaptivePolicy)
            valueSerializer.writeInt32(TypeChecker.TextHeightAdaptivePolicy_ToNumeric(value_heightAdaptivePolicy_value))
        }
        const value_font  = value.font
        let value_font_type : int32 = RuntimeType.UNDEFINED
        value_font_type = runtimeType(value_font)
        valueSerializer.writeInt8((value_font_type).toChar())
        if ((value_font_type) != (RuntimeType.UNDEFINED)) {
            const value_font_value  = value_font!
            Font_serializer.write(valueSerializer, value_font_value)
        }
        const value_selectedColor  = value.selectedColor
        let value_selectedColor_type : int32 = RuntimeType.UNDEFINED
        value_selectedColor_type = runtimeType(value_selectedColor)
        valueSerializer.writeInt8((value_selectedColor_type).toChar())
        if ((value_selectedColor_type) != (RuntimeType.UNDEFINED)) {
            const value_selectedColor_value  = value_selectedColor!
            let value_selectedColor_value_type : int32 = RuntimeType.UNDEFINED
            value_selectedColor_value_type = runtimeType(value_selectedColor_value)
            if (TypeChecker.isColor(value_selectedColor_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value_selectedColor_value_0  = value_selectedColor_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_selectedColor_value_0))
            }
            else if (RuntimeType.NUMBER == value_selectedColor_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_selectedColor_value_1  = value_selectedColor_value as number
                valueSerializer.writeNumber(value_selectedColor_value_1)
            }
            else if (RuntimeType.STRING == value_selectedColor_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_selectedColor_value_2  = value_selectedColor_value as string
                valueSerializer.writeString(value_selectedColor_value_2)
            }
            else if (RuntimeType.OBJECT == value_selectedColor_value_type) {
                valueSerializer.writeInt8((3).toChar())
                const value_selectedColor_value_3  = value_selectedColor_value as Resource
                Resource_serializer.write(valueSerializer, value_selectedColor_value_3)
            }
        }
        const value_unselectedColor  = value.unselectedColor
        let value_unselectedColor_type : int32 = RuntimeType.UNDEFINED
        value_unselectedColor_type = runtimeType(value_unselectedColor)
        valueSerializer.writeInt8((value_unselectedColor_type).toChar())
        if ((value_unselectedColor_type) != (RuntimeType.UNDEFINED)) {
            const value_unselectedColor_value  = value_unselectedColor!
            let value_unselectedColor_value_type : int32 = RuntimeType.UNDEFINED
            value_unselectedColor_value_type = runtimeType(value_unselectedColor_value)
            if (TypeChecker.isColor(value_unselectedColor_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value_unselectedColor_value_0  = value_unselectedColor_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_unselectedColor_value_0))
            }
            else if (RuntimeType.NUMBER == value_unselectedColor_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_unselectedColor_value_1  = value_unselectedColor_value as number
                valueSerializer.writeNumber(value_unselectedColor_value_1)
            }
            else if (RuntimeType.STRING == value_unselectedColor_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_unselectedColor_value_2  = value_unselectedColor_value as string
                valueSerializer.writeString(value_unselectedColor_value_2)
            }
            else if (RuntimeType.OBJECT == value_unselectedColor_value_type) {
                valueSerializer.writeInt8((3).toChar())
                const value_unselectedColor_value_3  = value_unselectedColor_value as Resource
                Resource_serializer.write(valueSerializer, value_unselectedColor_value_3)
            }
        }
    }
    public static read(buffer: DeserializerBase): TabBarLabelStyle {
        let valueDeserializer : DeserializerBase = buffer
        const overflow_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let overflow_buf : TextOverflow | undefined
        if ((overflow_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            overflow_buf = TypeChecker.TextOverflow_FromNumeric(valueDeserializer.readInt32())
        }
        const overflow_result : TextOverflow | undefined = overflow_buf
        const maxLines_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let maxLines_buf : number | undefined
        if ((maxLines_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            maxLines_buf = (valueDeserializer.readNumber() as number)
        }
        const maxLines_result : number | undefined = maxLines_buf
        const minFontSize_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let minFontSize_buf : number | ResourceStr | undefined
        if ((minFontSize_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const minFontSize_buf__selector : int32 = valueDeserializer.readInt8()
            let minFontSize_buf_ : number | ResourceStr | undefined
            if (minFontSize_buf__selector == (0).toChar()) {
                minFontSize_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (minFontSize_buf__selector == (1).toChar()) {
                const minFontSize_buf__u_selector : int32 = valueDeserializer.readInt8()
                let minFontSize_buf__u : string | Resource | undefined
                if (minFontSize_buf__u_selector == (0).toChar()) {
                    minFontSize_buf__u = (valueDeserializer.readString() as string)
                }
                else if (minFontSize_buf__u_selector == (1).toChar()) {
                    minFontSize_buf__u = Resource_serializer.read(valueDeserializer)
                }
                else {
                    throw new Error("One of the branches for minFontSize_buf__u has to be chosen through deserialisation.")
                }
                minFontSize_buf_ = (minFontSize_buf__u as string | Resource)
            }
            else {
                throw new Error("One of the branches for minFontSize_buf_ has to be chosen through deserialisation.")
            }
            minFontSize_buf = (minFontSize_buf_ as number | ResourceStr)
        }
        const minFontSize_result : number | ResourceStr | undefined = minFontSize_buf
        const maxFontSize_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let maxFontSize_buf : number | ResourceStr | undefined
        if ((maxFontSize_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const maxFontSize_buf__selector : int32 = valueDeserializer.readInt8()
            let maxFontSize_buf_ : number | ResourceStr | undefined
            if (maxFontSize_buf__selector == (0).toChar()) {
                maxFontSize_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (maxFontSize_buf__selector == (1).toChar()) {
                const maxFontSize_buf__u_selector : int32 = valueDeserializer.readInt8()
                let maxFontSize_buf__u : string | Resource | undefined
                if (maxFontSize_buf__u_selector == (0).toChar()) {
                    maxFontSize_buf__u = (valueDeserializer.readString() as string)
                }
                else if (maxFontSize_buf__u_selector == (1).toChar()) {
                    maxFontSize_buf__u = Resource_serializer.read(valueDeserializer)
                }
                else {
                    throw new Error("One of the branches for maxFontSize_buf__u has to be chosen through deserialisation.")
                }
                maxFontSize_buf_ = (maxFontSize_buf__u as string | Resource)
            }
            else {
                throw new Error("One of the branches for maxFontSize_buf_ has to be chosen through deserialisation.")
            }
            maxFontSize_buf = (maxFontSize_buf_ as number | ResourceStr)
        }
        const maxFontSize_result : number | ResourceStr | undefined = maxFontSize_buf
        const heightAdaptivePolicy_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let heightAdaptivePolicy_buf : TextHeightAdaptivePolicy | undefined
        if ((heightAdaptivePolicy_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            heightAdaptivePolicy_buf = TypeChecker.TextHeightAdaptivePolicy_FromNumeric(valueDeserializer.readInt32())
        }
        const heightAdaptivePolicy_result : TextHeightAdaptivePolicy | undefined = heightAdaptivePolicy_buf
        const font_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let font_buf : Font | undefined
        if ((font_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            font_buf = Font_serializer.read(valueDeserializer)
        }
        const font_result : Font | undefined = font_buf
        const selectedColor_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let selectedColor_buf : ResourceColor | undefined
        if ((selectedColor_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const selectedColor_buf__selector : int32 = valueDeserializer.readInt8()
            let selectedColor_buf_ : Color | number | string | Resource | undefined
            if (selectedColor_buf__selector == (0).toChar()) {
                selectedColor_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (selectedColor_buf__selector == (1).toChar()) {
                selectedColor_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (selectedColor_buf__selector == (2).toChar()) {
                selectedColor_buf_ = (valueDeserializer.readString() as string)
            }
            else if (selectedColor_buf__selector == (3).toChar()) {
                selectedColor_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for selectedColor_buf_ has to be chosen through deserialisation.")
            }
            selectedColor_buf = (selectedColor_buf_ as Color | number | string | Resource)
        }
        const selectedColor_result : ResourceColor | undefined = selectedColor_buf
        const unselectedColor_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let unselectedColor_buf : ResourceColor | undefined
        if ((unselectedColor_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const unselectedColor_buf__selector : int32 = valueDeserializer.readInt8()
            let unselectedColor_buf_ : Color | number | string | Resource | undefined
            if (unselectedColor_buf__selector == (0).toChar()) {
                unselectedColor_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (unselectedColor_buf__selector == (1).toChar()) {
                unselectedColor_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (unselectedColor_buf__selector == (2).toChar()) {
                unselectedColor_buf_ = (valueDeserializer.readString() as string)
            }
            else if (unselectedColor_buf__selector == (3).toChar()) {
                unselectedColor_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for unselectedColor_buf_ has to be chosen through deserialisation.")
            }
            unselectedColor_buf = (unselectedColor_buf_ as Color | number | string | Resource)
        }
        const unselectedColor_result : ResourceColor | undefined = unselectedColor_buf
        let value : TabBarLabelStyle = ({overflow: overflow_result, maxLines: maxLines_result, minFontSize: minFontSize_result, maxFontSize: maxFontSize_result, heightAdaptivePolicy: heightAdaptivePolicy_result, font: font_result, selectedColor: selectedColor_result, unselectedColor: unselectedColor_result} as TabBarLabelStyle)
        return value
    }
}
export class BottomTabBarStyle_serializer {
    public static write(buffer: SerializerBase, value: BottomTabBarStyle): void {
        let valueSerializer : SerializerBase = buffer
        const value__icon  = value._icon
        let value__icon_type : int32 = RuntimeType.UNDEFINED
        value__icon_type = runtimeType(value__icon)
        valueSerializer.writeInt8((value__icon_type).toChar())
        if ((value__icon_type) != (RuntimeType.UNDEFINED)) {
            const value__icon_value  = value__icon!
            let value__icon_value_type : int32 = RuntimeType.UNDEFINED
            value__icon_value_type = runtimeType(value__icon_value)
            if ((RuntimeType.STRING == value__icon_value_type) || (RuntimeType.OBJECT == value__icon_value_type)) {
                valueSerializer.writeInt8((0).toChar())
                const value__icon_value_0  = value__icon_value as ResourceStr
                let value__icon_value_0_type : int32 = RuntimeType.UNDEFINED
                value__icon_value_0_type = runtimeType(value__icon_value_0)
                if (RuntimeType.STRING == value__icon_value_0_type) {
                    valueSerializer.writeInt8((0).toChar())
                    const value__icon_value_0_0  = value__icon_value_0 as string
                    valueSerializer.writeString(value__icon_value_0_0)
                }
                else if (RuntimeType.OBJECT == value__icon_value_0_type) {
                    valueSerializer.writeInt8((1).toChar())
                    const value__icon_value_0_1  = value__icon_value_0 as Resource
                    Resource_serializer.write(valueSerializer, value__icon_value_0_1)
                }
            }
            else if (TypeChecker.isTabBarSymbol(value__icon_value, false, false)) {
                valueSerializer.writeInt8((1).toChar())
                const value__icon_value_1  = value__icon_value as TabBarSymbol
                TabBarSymbol_serializer.write(valueSerializer, value__icon_value_1)
            }
        }
        const value__text  = value._text
        let value__text_type : int32 = RuntimeType.UNDEFINED
        value__text_type = runtimeType(value__text)
        valueSerializer.writeInt8((value__text_type).toChar())
        if ((value__text_type) != (RuntimeType.UNDEFINED)) {
            const value__text_value  = value__text!
            let value__text_value_type : int32 = RuntimeType.UNDEFINED
            value__text_value_type = runtimeType(value__text_value)
            if (RuntimeType.STRING == value__text_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value__text_value_0  = value__text_value as string
                valueSerializer.writeString(value__text_value_0)
            }
            else if (RuntimeType.OBJECT == value__text_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value__text_value_1  = value__text_value as Resource
                Resource_serializer.write(valueSerializer, value__text_value_1)
            }
        }
        const value__labelStyle  = value._labelStyle
        let value__labelStyle_type : int32 = RuntimeType.UNDEFINED
        value__labelStyle_type = runtimeType(value__labelStyle)
        valueSerializer.writeInt8((value__labelStyle_type).toChar())
        if ((value__labelStyle_type) != (RuntimeType.UNDEFINED)) {
            const value__labelStyle_value  = value__labelStyle!
            TabBarLabelStyle_serializer.write(valueSerializer, value__labelStyle_value)
        }
        const value__padding  = value._padding
        let value__padding_type : int32 = RuntimeType.UNDEFINED
        value__padding_type = runtimeType(value__padding)
        valueSerializer.writeInt8((value__padding_type).toChar())
        if ((value__padding_type) != (RuntimeType.UNDEFINED)) {
            const value__padding_value  = value__padding!
            let value__padding_value_type : int32 = RuntimeType.UNDEFINED
            value__padding_value_type = runtimeType(value__padding_value)
            if (TypeChecker.isPadding(value__padding_value, true, false, true, false)) {
                valueSerializer.writeInt8((0).toChar())
                const value__padding_value_0  = value__padding_value as Padding
                Padding_serializer.write(valueSerializer, value__padding_value_0)
            }
            else if ((RuntimeType.STRING == value__padding_value_type) || (RuntimeType.NUMBER == value__padding_value_type) || (RuntimeType.OBJECT == value__padding_value_type)) {
                valueSerializer.writeInt8((1).toChar())
                const value__padding_value_1  = value__padding_value as Dimension
                let value__padding_value_1_type : int32 = RuntimeType.UNDEFINED
                value__padding_value_1_type = runtimeType(value__padding_value_1)
                if (RuntimeType.STRING == value__padding_value_1_type) {
                    valueSerializer.writeInt8((0).toChar())
                    const value__padding_value_1_0  = value__padding_value_1 as string
                    valueSerializer.writeString(value__padding_value_1_0)
                }
                else if (RuntimeType.NUMBER == value__padding_value_1_type) {
                    valueSerializer.writeInt8((1).toChar())
                    const value__padding_value_1_1  = value__padding_value_1 as number
                    valueSerializer.writeNumber(value__padding_value_1_1)
                }
                else if (RuntimeType.OBJECT == value__padding_value_1_type) {
                    valueSerializer.writeInt8((2).toChar())
                    const value__padding_value_1_2  = value__padding_value_1 as Resource
                    Resource_serializer.write(valueSerializer, value__padding_value_1_2)
                }
            }
            else if (TypeChecker.isLocalizedPadding(value__padding_value, true, false, true, false)) {
                valueSerializer.writeInt8((2).toChar())
                const value__padding_value_2  = value__padding_value as LocalizedPadding
                LocalizedPadding_serializer.write(valueSerializer, value__padding_value_2)
            }
        }
        const value__layoutMode  = value._layoutMode
        let value__layoutMode_type : int32 = RuntimeType.UNDEFINED
        value__layoutMode_type = runtimeType(value__layoutMode)
        valueSerializer.writeInt8((value__layoutMode_type).toChar())
        if ((value__layoutMode_type) != (RuntimeType.UNDEFINED)) {
            const value__layoutMode_value  = (value__layoutMode as LayoutMode)
            valueSerializer.writeInt32(TypeChecker.LayoutMode_ToNumeric(value__layoutMode_value))
        }
        const value__verticalAlign  = value._verticalAlign
        let value__verticalAlign_type : int32 = RuntimeType.UNDEFINED
        value__verticalAlign_type = runtimeType(value__verticalAlign)
        valueSerializer.writeInt8((value__verticalAlign_type).toChar())
        if ((value__verticalAlign_type) != (RuntimeType.UNDEFINED)) {
            const value__verticalAlign_value  = (value__verticalAlign as VerticalAlign)
            valueSerializer.writeInt32(TypeChecker.VerticalAlign_ToNumeric(value__verticalAlign_value))
        }
        const value__symmetricExtensible  = value._symmetricExtensible
        let value__symmetricExtensible_type : int32 = RuntimeType.UNDEFINED
        value__symmetricExtensible_type = runtimeType(value__symmetricExtensible)
        valueSerializer.writeInt8((value__symmetricExtensible_type).toChar())
        if ((value__symmetricExtensible_type) != (RuntimeType.UNDEFINED)) {
            const value__symmetricExtensible_value  = value__symmetricExtensible!
            valueSerializer.writeBoolean(value__symmetricExtensible_value)
        }
        const value__id  = value._id
        let value__id_type : int32 = RuntimeType.UNDEFINED
        value__id_type = runtimeType(value__id)
        valueSerializer.writeInt8((value__id_type).toChar())
        if ((value__id_type) != (RuntimeType.UNDEFINED)) {
            const value__id_value  = value__id!
            valueSerializer.writeString(value__id_value)
        }
        const value__iconStyle  = value._iconStyle
        let value__iconStyle_type : int32 = RuntimeType.UNDEFINED
        value__iconStyle_type = runtimeType(value__iconStyle)
        valueSerializer.writeInt8((value__iconStyle_type).toChar())
        if ((value__iconStyle_type) != (RuntimeType.UNDEFINED)) {
            const value__iconStyle_value  = value__iconStyle!
            TabBarIconStyle_serializer.write(valueSerializer, value__iconStyle_value)
        }
    }
    public static read(buffer: DeserializerBase): BottomTabBarStyle {
        throw new Error("Can not deserialize builder class")
    }
}
export class SubTabBarStyle_serializer {
    public static write(buffer: SerializerBase, value: SubTabBarStyle): void {
        let valueSerializer : SerializerBase = buffer
        const value__content  = value._content
        let value__content_type : int32 = RuntimeType.UNDEFINED
        value__content_type = runtimeType(value__content)
        valueSerializer.writeInt8((value__content_type).toChar())
        if ((value__content_type) != (RuntimeType.UNDEFINED)) {
            const value__content_value  = value__content!
            let value__content_value_type : int32 = RuntimeType.UNDEFINED
            value__content_value_type = runtimeType(value__content_value)
            if (RuntimeType.STRING == value__content_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value__content_value_0  = value__content_value as string
                valueSerializer.writeString(value__content_value_0)
            }
            else if (TypeChecker.isResource(value__content_value, false, false, false, false, false)) {
                valueSerializer.writeInt8((1).toChar())
                const value__content_value_1  = value__content_value as Resource
                Resource_serializer.write(valueSerializer, value__content_value_1)
            }
            else if (TypeChecker.isComponentContent(value__content_value)) {
                valueSerializer.writeInt8((2).toChar())
                const value__content_value_2  = value__content_value as ComponentContent
                ComponentContent_serializer.write(valueSerializer, value__content_value_2)
            }
        }
        const value__indicator  = value._indicator
        let value__indicator_type : int32 = RuntimeType.UNDEFINED
        value__indicator_type = runtimeType(value__indicator)
        valueSerializer.writeInt8((value__indicator_type).toChar())
        if ((value__indicator_type) != (RuntimeType.UNDEFINED)) {
            const value__indicator_value  = value__indicator!
            SubTabBarIndicatorStyle_serializer.write(valueSerializer, value__indicator_value)
        }
        const value__selectedMode  = value._selectedMode
        let value__selectedMode_type : int32 = RuntimeType.UNDEFINED
        value__selectedMode_type = runtimeType(value__selectedMode)
        valueSerializer.writeInt8((value__selectedMode_type).toChar())
        if ((value__selectedMode_type) != (RuntimeType.UNDEFINED)) {
            const value__selectedMode_value  = (value__selectedMode as SelectedMode)
            valueSerializer.writeInt32(TypeChecker.SelectedMode_ToNumeric(value__selectedMode_value))
        }
        const value__board  = value._board
        let value__board_type : int32 = RuntimeType.UNDEFINED
        value__board_type = runtimeType(value__board)
        valueSerializer.writeInt8((value__board_type).toChar())
        if ((value__board_type) != (RuntimeType.UNDEFINED)) {
            const value__board_value  = value__board!
            BoardStyle_serializer.write(valueSerializer, value__board_value)
        }
        const value__labelStyle  = value._labelStyle
        let value__labelStyle_type : int32 = RuntimeType.UNDEFINED
        value__labelStyle_type = runtimeType(value__labelStyle)
        valueSerializer.writeInt8((value__labelStyle_type).toChar())
        if ((value__labelStyle_type) != (RuntimeType.UNDEFINED)) {
            const value__labelStyle_value  = value__labelStyle!
            TabBarLabelStyle_serializer.write(valueSerializer, value__labelStyle_value)
        }
        const value__padding  = value._padding
        let value__padding_type : int32 = RuntimeType.UNDEFINED
        value__padding_type = runtimeType(value__padding)
        valueSerializer.writeInt8((value__padding_type).toChar())
        if ((value__padding_type) != (RuntimeType.UNDEFINED)) {
            const value__padding_value  = value__padding!
            let value__padding_value_type : int32 = RuntimeType.UNDEFINED
            value__padding_value_type = runtimeType(value__padding_value)
            if ((TypeChecker.isPadding(value__padding_value, false, false, false, false)) || ((RuntimeType.STRING == value__padding_value_type) || (RuntimeType.NUMBER == value__padding_value_type) || (RuntimeType.OBJECT == value__padding_value_type))) {
                valueSerializer.writeInt8((0).toChar())
                const value__padding_value_0  = value__padding_value as Padding | Dimension
                let value__padding_value_0_type : int32 = RuntimeType.UNDEFINED
                value__padding_value_0_type = runtimeType(value__padding_value_0)
                if (TypeChecker.isPadding(value__padding_value_0, false, false, false, false)) {
                    valueSerializer.writeInt8((0).toChar())
                    const value__padding_value_0_0  = value__padding_value_0 as Padding
                    Padding_serializer.write(valueSerializer, value__padding_value_0_0)
                }
                else if ((RuntimeType.STRING == value__padding_value_0_type) || (RuntimeType.NUMBER == value__padding_value_0_type) || (RuntimeType.OBJECT == value__padding_value_0_type)) {
                    valueSerializer.writeInt8((1).toChar())
                    const value__padding_value_0_1  = value__padding_value_0 as Dimension
                    let value__padding_value_0_1_type : int32 = RuntimeType.UNDEFINED
                    value__padding_value_0_1_type = runtimeType(value__padding_value_0_1)
                    if (RuntimeType.STRING == value__padding_value_0_1_type) {
                        valueSerializer.writeInt8((0).toChar())
                        const value__padding_value_0_1_0  = value__padding_value_0_1 as string
                        valueSerializer.writeString(value__padding_value_0_1_0)
                    }
                    else if (RuntimeType.NUMBER == value__padding_value_0_1_type) {
                        valueSerializer.writeInt8((1).toChar())
                        const value__padding_value_0_1_1  = value__padding_value_0_1 as number
                        valueSerializer.writeNumber(value__padding_value_0_1_1)
                    }
                    else if (RuntimeType.OBJECT == value__padding_value_0_1_type) {
                        valueSerializer.writeInt8((2).toChar())
                        const value__padding_value_0_1_2  = value__padding_value_0_1 as Resource
                        Resource_serializer.write(valueSerializer, value__padding_value_0_1_2)
                    }
                }
            }
            else if (TypeChecker.isLocalizedPadding(value__padding_value, false, false, false, false)) {
                valueSerializer.writeInt8((1).toChar())
                const value__padding_value_1  = value__padding_value as LocalizedPadding
                LocalizedPadding_serializer.write(valueSerializer, value__padding_value_1)
            }
        }
        const value__id  = value._id
        let value__id_type : int32 = RuntimeType.UNDEFINED
        value__id_type = runtimeType(value__id)
        valueSerializer.writeInt8((value__id_type).toChar())
        if ((value__id_type) != (RuntimeType.UNDEFINED)) {
            const value__id_value  = value__id!
            valueSerializer.writeString(value__id_value)
        }
    }
    public static read(buffer: DeserializerBase): SubTabBarStyle {
        throw new Error("Can not deserialize builder class")
    }
}
