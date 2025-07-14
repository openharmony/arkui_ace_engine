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

import { int32, int64, float32 } from "@koalaui/common"
import { nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, wrapCallback, NativeBuffer } from "@koalaui/interop"
import { Serializer } from "./peers/Serializer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, CustomBuilder, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { Resource } from "global.resource"
import { ComponentContent } from "./arkui-custom"
import { VoidCallback, Length, ResourceColor, ResourceStr, Padding, Dimension, LocalizedPadding, Font } from "./units"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"
import { SymbolGlyphModifier } from "./arkui-external"
import { VerticalAlign, TextOverflow, TextHeightAdaptivePolicy } from "./enums"
export class ArkTabContentPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkTabContentPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._TabContent_construct(peerId, flags)
        const _peer  = new ArkTabContentPeer(_peerPtr, peerId, "TabContent", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setTabContentOptionsAttribute(): void {
        ArkUIGeneratedNativeModule._TabContentInterface_setTabContentOptions(this.peer.ptr)
    }
    tabBar0Attribute(value: string | Resource | CustomBuilder | TabBarOptions | undefined): void {
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
            else if (TypeChecker.isResource(value_value, false, false, false, false, false)) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as Resource
                thisSerializer.writeResource(value_value_1)
            }
            else if (RuntimeType.FUNCTION == value_value_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as CustomBuilder
                thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value_value_2))
            }
            else if (TypeChecker.isTabBarOptions(value_value, false, false)) {
                thisSerializer.writeInt8(3 as int32)
                const value_value_3  = value_value as TabBarOptions
                thisSerializer.writeTabBarOptions(value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._TabContentAttribute_tabBar0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    tabBar1Attribute(value: SubTabBarStyle | BottomTabBarStyle | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (((RuntimeType.OBJECT) == (value_value_type)) && (TypeChecker.isSubTabBarStyle(value_value))) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as SubTabBarStyle
                thisSerializer.writeSubTabBarStyle(value_value_0)
            }
            else if (((RuntimeType.OBJECT) == (value_value_type)) && (TypeChecker.isBottomTabBarStyle(value_value))) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as BottomTabBarStyle
                thisSerializer.writeBottomTabBarStyle(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._TabContentAttribute_tabBar1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    tabBar2Attribute(value: ComponentContent | SubTabBarStyle | BottomTabBarStyle | string | Resource | CustomBuilder | TabBarOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isComponentContent(value_value)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as ComponentContent
                thisSerializer.writeComponentContent(value_value_0)
            }
            else if (((RuntimeType.OBJECT) == (value_value_type)) && (TypeChecker.isSubTabBarStyle(value_value))) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as SubTabBarStyle
                thisSerializer.writeSubTabBarStyle(value_value_1)
            }
            else if (((RuntimeType.OBJECT) == (value_value_type)) && (TypeChecker.isBottomTabBarStyle(value_value))) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as BottomTabBarStyle
                thisSerializer.writeBottomTabBarStyle(value_value_2)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(3 as int32)
                const value_value_3  = value_value as string
                thisSerializer.writeString(value_value_3)
            }
            else if (TypeChecker.isResource(value_value, false, false, false, false, false)) {
                thisSerializer.writeInt8(4 as int32)
                const value_value_4  = value_value as Resource
                thisSerializer.writeResource(value_value_4)
            }
            else if (RuntimeType.FUNCTION == value_value_type) {
                thisSerializer.writeInt8(5 as int32)
                const value_value_5  = value_value as CustomBuilder
                thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value_value_5))
            }
            else if (TypeChecker.isTabBarOptions(value_value, false, false)) {
                thisSerializer.writeInt8(6 as int32)
                const value_value_6  = value_value as TabBarOptions
                thisSerializer.writeTabBarOptions(value_value_6)
            }
        }
        ArkUIGeneratedNativeModule._TabContentAttribute_tabBar2(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onWillShowAttribute(value: VoidCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TabContentAttribute_onWillShow(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onWillHideAttribute(value: VoidCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TabContentAttribute_onWillHide(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
    color?: ResourceColor,
    height?: Length,
    width?: Length,
    borderRadius?: Length,
    marginTop?: Length
}
export interface BoardStyle {
    borderRadius?: Length;
}
export interface TabBarLabelStyle {
    overflow?: TextOverflow,
    maxLines?: number,
    minFontSize?: number | ResourceStr,
    maxFontSize?: number | ResourceStr,
    heightAdaptivePolicy?: TextHeightAdaptivePolicy,
    font?: Font,
    selectedColor?: ResourceColor,
    unselectedColor?: ResourceColor
}
export interface TabBarIconStyle {
    selectedColor?: ResourceColor;
    unselectedColor?: ResourceColor;
}
export interface TabBarSymbol {
    normal: SymbolGlyphModifier;
    selected?: SymbolGlyphModifier;
}
export interface TabBarOptions {
    icon?: string | Resource;
    text?: string | Resource;
}
export type TabContentInterface = () => TabContentAttribute;
export interface TabContentAttribute extends CommonMethod {
    tabBar(value: string | Resource | CustomBuilder | TabBarOptions | undefined | SubTabBarStyle | BottomTabBarStyle | undefined | ComponentContent | SubTabBarStyle | BottomTabBarStyle | string | Resource | CustomBuilder | TabBarOptions | undefined): this
    onWillShow(value: VoidCallback | undefined): this
    onWillHide(value: VoidCallback | undefined): this
}
export class ArkTabContentStyle extends ArkCommonMethodStyle implements TabContentAttribute {
    tabBar_value?: string | Resource | CustomBuilder | TabBarOptions | undefined
    onWillShow_value?: VoidCallback | undefined
    onWillHide_value?: VoidCallback | undefined
    public tabBar(value: string | Resource | CustomBuilder | TabBarOptions | undefined | SubTabBarStyle | BottomTabBarStyle | undefined | ComponentContent | SubTabBarStyle | BottomTabBarStyle | string | Resource | CustomBuilder | TabBarOptions | undefined): this {
        return this
    }
    public onWillShow(value: VoidCallback | undefined): this {
        return this
    }
    public onWillHide(value: VoidCallback | undefined): this {
        return this
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
    public tabBar(value: SubTabBarStyle | BottomTabBarStyle | undefined | string | Resource | CustomBuilder | TabBarOptions | undefined | ComponentContent | SubTabBarStyle | BottomTabBarStyle | string | Resource | CustomBuilder | TabBarOptions | undefined): this {
        if (this.checkPriority("tabBar")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (SubTabBarStyle | BottomTabBarStyle | undefined)
                this.getPeer()?.tabBar1Attribute(value_casted)
                return this
            }
            if ((RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.FUNCTION == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (string | Resource | CustomBuilder | TabBarOptions | undefined)
                this.getPeer()?.tabBar0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.FUNCTION == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (ComponentContent | SubTabBarStyle | BottomTabBarStyle | string | Resource | CustomBuilder | TabBarOptions | undefined)
                this.getPeer()?.tabBar2Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public onWillShow(value: VoidCallback | undefined): this {
        if (this.checkPriority("onWillShow")) {
            const value_casted = value as (VoidCallback | undefined)
            this.getPeer()?.onWillShowAttribute(value_casted)
            return this
        }
        return this
    }
    public onWillHide(value: VoidCallback | undefined): this {
        if (this.checkPriority("onWillHide")) {
            const value_casted = value as (VoidCallback | undefined)
            this.getPeer()?.onWillHideAttribute(value_casted)
            return this
        }
        return this
    }
    
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function TabContent(
    /** @memo */
    style: ((attributes: TabContentAttribute) => void) | undefined,
    
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkTabContentComponent()
    })
    NodeAttach<ArkTabContentPeer>((): ArkTabContentPeer => ArkTabContentPeer.create(receiver), (_: ArkTabContentPeer) => {
        receiver.setTabContentOptions()
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
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
    public static of(content: ResourceStr | ResourceStr | ComponentContent): SubTabBarStyle {
        return new SubTabBarStyle(content)
    }
    indicator(value: SubTabBarIndicatorStyle): this {
        this._indicator = value
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
    labelStyle(value: TabBarLabelStyle): this {
        this._labelStyle = value
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
    labelStyle(value: TabBarLabelStyle): this {
        this._labelStyle = value
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
