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
import { ArkCommonMethodPeer, CommonMethod, CustomBuilder, ArkCommonMethodComponent, ArkCommonMethodStyle, UICommonMethod } from "./common"
import { ResourceStr, Font, ResourceColor } from "./units"
import { SymbolGlyphModifier } from "./arkui-external"
import { Callback_Boolean_Void } from "./navigation"
import { Resource } from "./resource"
import { Color } from "./enums"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { UICommonBase, AttributeModifier } from "./../handwritten"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkMenuItemPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkMenuItemPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._MenuItem_construct(peerId, flags)
        const _peer  = new ArkMenuItemPeer(_peerPtr, peerId, "MenuItem", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setMenuItemOptionsAttribute(value?: MenuItemOptions | CustomBuilder): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as MenuItemOptions
                thisSerializer.writeMenuItemOptions(value_value_0)
            }
            else if (RuntimeType.FUNCTION == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as CustomBuilder
                thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value_value_1))
            }
        }
        ArkUIGeneratedNativeModule._MenuItemInterface_setMenuItemOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    selectedAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._MenuItemAttribute_selected(this.peer.ptr, value ? 1 : 0)
    }
    selectIconAttribute(value: boolean | ResourceStr | SymbolGlyphModifier): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.BOOLEAN == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as boolean
            thisSerializer.writeBoolean(value_0)
        }
        else if ((RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type)) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as ResourceStr
            let value_1_type : int32 = RuntimeType.UNDEFINED
            value_1_type = runtimeType(value_1)
            if (RuntimeType.STRING == value_1_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_1_0  = value_1 as string
                thisSerializer.writeString(value_1_0)
            }
            else if (RuntimeType.OBJECT == value_1_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_1_1  = value_1 as Resource
                thisSerializer.writeResource(value_1_1)
            }
        }
        else if (TypeChecker.isSymbolGlyphModifier(value)) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as SymbolGlyphModifier
            thisSerializer.writeSymbolGlyphModifier(value_2)
        }
        ArkUIGeneratedNativeModule._MenuItemAttribute_selectIcon(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onChangeAttribute(value: ((isVisible: boolean) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._MenuItemAttribute_onChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    contentFontAttribute(value: Font): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeFont(value)
        ArkUIGeneratedNativeModule._MenuItemAttribute_contentFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    contentFontColorAttribute(value: ResourceColor): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isColor(value)) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as Color
            thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_0))
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as string
            thisSerializer.writeString(value_2)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(3 as int32)
            const value_3  = value as Resource
            thisSerializer.writeResource(value_3)
        }
        ArkUIGeneratedNativeModule._MenuItemAttribute_contentFontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    labelFontAttribute(value: Font): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeFont(value)
        ArkUIGeneratedNativeModule._MenuItemAttribute_labelFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    labelFontColorAttribute(value: ResourceColor): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isColor(value)) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as Color
            thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_0))
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as string
            thisSerializer.writeString(value_2)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(3 as int32)
            const value_3  = value as Resource
            thisSerializer.writeResource(value_3)
        }
        ArkUIGeneratedNativeModule._MenuItemAttribute_labelFontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    _onChangeEvent_selectedAttribute(callback: ((isVisible: boolean) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(callback)
        ArkUIGeneratedNativeModule._MenuItemAttribute__onChangeEvent_selected(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface MenuItemOptions {
    startIcon?: ResourceStr;
    symbolStartIcon?: SymbolGlyphModifier;
    content?: ResourceStr;
    endIcon?: ResourceStr;
    symbolEndIcon?: SymbolGlyphModifier;
    labelInfo?: ResourceStr;
    builder?: CustomBuilder;
}

export interface MenuItemAttribute extends CommonMethod {
    selected(value: boolean): this
    selectIcon(value: boolean | ResourceStr | SymbolGlyphModifier): this
    onChange(value: ((isVisible: boolean) => void)): this
    contentFont(value: Font): this
    contentFontColor(value: ResourceColor): this
    labelFont(value: Font): this
    labelFontColor(value: ResourceColor): this
    _onChangeEvent_selected(callback: ((isVisible: boolean) => void)): void
    attributeModifier(value: AttributeModifier<MenuItemAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export interface UIMenuItemAttribute extends UICommonMethod {
    /** @memo */
    selected(value: boolean): this
    /** @memo */
    selectIcon(value: boolean | ResourceStr | SymbolGlyphModifier): this
    /** @memo */
    onChange(value: ((isVisible: boolean) => void)): this
    /** @memo */
    contentFont(value: Font): this
    /** @memo */
    contentFontColor(value: ResourceColor): this
    /** @memo */
    labelFont(value: Font): this
    /** @memo */
    labelFontColor(value: ResourceColor): this
    /** @memo */
    _onChangeEvent_selected(callback: ((isVisible: boolean) => void)): void
    /** @memo */
    attributeModifier(value: AttributeModifier<MenuItemAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkMenuItemStyle extends ArkCommonMethodStyle implements MenuItemAttribute {
    selected_value?: boolean
    selectIcon_value?: boolean | ResourceStr | SymbolGlyphModifier
    onChange_value?: ((isVisible: boolean) => void)
    contentFont_value?: Font
    contentFontColor_value?: ResourceColor
    labelFont_value?: Font
    labelFontColor_value?: ResourceColor
    public selected(value: boolean): this {
        return this
    }
    public selectIcon(value: boolean | ResourceStr | SymbolGlyphModifier): this {
        return this
    }
    public onChange(value: ((isVisible: boolean) => void)): this {
        return this
    }
    public contentFont(value: Font): this {
        return this
    }
    public contentFontColor(value: ResourceColor): this {
        return this
    }
    public labelFont(value: Font): this {
        return this
    }
    public labelFontColor(value: ResourceColor): this {
        return this
    }
    public _onChangeEvent_selected(callback: ((isVisible: boolean) => void)): void {
        throw new Error("Unimplmented")
    }
    public attributeModifier(value: AttributeModifier<MenuItemAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
/** @memo:stable */
export class ArkMenuItemComponent extends ArkCommonMethodComponent implements UIMenuItemAttribute {
    getPeer(): ArkMenuItemPeer {
        return (this.peer as ArkMenuItemPeer)
    }
    /** @memo */
    public setMenuItemOptions(value?: MenuItemOptions | CustomBuilder): this {
        if (this.checkPriority("setMenuItemOptions")) {
            const value_casted = value as (MenuItemOptions | CustomBuilder | undefined)
            this.getPeer()?.setMenuItemOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public selected(value: boolean): this {
        if (this.checkPriority("selected")) {
            const value_casted = value as (boolean)
            this.getPeer()?.selectedAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public selectIcon(value: boolean | ResourceStr | SymbolGlyphModifier): this {
        if (this.checkPriority("selectIcon")) {
            const value_casted = value as (boolean | ResourceStr | SymbolGlyphModifier)
            this.getPeer()?.selectIconAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onChange(value: ((isVisible: boolean) => void)): this {
        if (this.checkPriority("onChange")) {
            const value_casted = value as (((isVisible: boolean) => void))
            this.getPeer()?.onChangeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public contentFont(value: Font): this {
        if (this.checkPriority("contentFont")) {
            const value_casted = value as (Font)
            this.getPeer()?.contentFontAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public contentFontColor(value: ResourceColor): this {
        if (this.checkPriority("contentFontColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.contentFontColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public labelFont(value: Font): this {
        if (this.checkPriority("labelFont")) {
            const value_casted = value as (Font)
            this.getPeer()?.labelFontAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public labelFontColor(value: ResourceColor): this {
        if (this.checkPriority("labelFontColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.labelFontColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public _onChangeEvent_selected(callback: ((isVisible: boolean) => void)): void {
        if (this.checkPriority("_onChangeEvent_selected")) {
            const callback_casted = callback as (((isVisible: boolean) => void))
            this.getPeer()?._onChangeEvent_selectedAttribute(callback_casted)
            return
        }
        return
    }
    /** @memo */
    public attributeModifier(value: AttributeModifier<MenuItemAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function ArkMenuItem(
    /** @memo */
    style: ((attributes: UIMenuItemAttribute) => void) | undefined,
    /** @memo */
    content_: (() => void) | undefined,
    value?: MenuItemOptions | CustomBuilder,
): void {
    const receiver = remember(() => {
        return new ArkMenuItemComponent()
    })
    NodeAttach<ArkMenuItemPeer>((): ArkMenuItemPeer => ArkMenuItemPeer.create(receiver), (_: ArkMenuItemPeer) => {
        receiver.setMenuItemOptions(value)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
