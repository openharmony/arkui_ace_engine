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
import { ResourceStr, Font, ResourceColor } from "./units"
import { SymbolGlyphModifier } from "./arkui-external"
import { Callback_Boolean_Void } from "./navigation"
import { Callback_Opt_Boolean_Void } from "./checkbox"
import { Resource } from "global/resource"
import { Color } from "./enums"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"

export class ArkMenuItemPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkMenuItemPeer {
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
    selectedAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._MenuItemAttribute_selected(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    selectIconAttribute(value: boolean | ResourceStr | SymbolGlyphModifier | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.BOOLEAN == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as boolean
                thisSerializer.writeBoolean(value_value_0)
            }
            else if ((RuntimeType.STRING == value_value_type) || (RuntimeType.OBJECT == value_value_type)) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as ResourceStr
                let value_value_1_type : int32 = RuntimeType.UNDEFINED
                value_value_1_type = runtimeType(value_value_1)
                if (RuntimeType.STRING == value_value_1_type) {
                    thisSerializer.writeInt8(0 as int32)
                    const value_value_1_0  = value_value_1 as string
                    thisSerializer.writeString(value_value_1_0)
                }
                else if (RuntimeType.OBJECT == value_value_1_type) {
                    thisSerializer.writeInt8(1 as int32)
                    const value_value_1_1  = value_value_1 as Resource
                    thisSerializer.writeResource(value_value_1_1)
                }
            }
            else if (TypeChecker.isSymbolGlyphModifier(value_value)) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as SymbolGlyphModifier
                thisSerializer.writeSymbolGlyphModifier(value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._MenuItemAttribute_selectIcon(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onChangeAttribute(value: ((isVisible: boolean) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._MenuItemAttribute_onChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    contentFontAttribute(value: Font | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeFont(value_value)
        }
        ArkUIGeneratedNativeModule._MenuItemAttribute_contentFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    contentFontColorAttribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._MenuItemAttribute_contentFontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    labelFontAttribute(value: Font | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeFont(value_value)
        }
        ArkUIGeneratedNativeModule._MenuItemAttribute_labelFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    labelFontColorAttribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._MenuItemAttribute_labelFontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    _onChangeEvent_selectedAttribute(callback: ((select: boolean | undefined) => void)): void {
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
export type MenuItemInterface = (value?: MenuItemOptions | CustomBuilder) => MenuItemAttribute;
export interface MenuItemAttribute extends CommonMethod {
    selected(value: boolean | undefined): this
    selectIcon(value: boolean | ResourceStr | SymbolGlyphModifier | undefined): this
    onChange(value: ((isVisible: boolean) => void) | undefined): this
    contentFont(value: Font | undefined): this
    contentFontColor(value: ResourceColor | undefined): this
    labelFont(value: Font | undefined): this
    labelFontColor(value: ResourceColor | undefined): this
    _onChangeEvent_selected(callback: ((select: boolean | undefined) => void)): void
}
export class ArkMenuItemStyle extends ArkCommonMethodStyle implements MenuItemAttribute {
    selected_value?: boolean | undefined
    selectIcon_value?: boolean | ResourceStr | SymbolGlyphModifier | undefined
    onChange_value?: ((isVisible: boolean) => void) | undefined
    contentFont_value?: Font | undefined
    contentFontColor_value?: ResourceColor | undefined
    labelFont_value?: Font | undefined
    labelFontColor_value?: ResourceColor | undefined
    public selected(value: boolean | undefined): this {
        return this
    }
    public selectIcon(value: boolean | ResourceStr | SymbolGlyphModifier | undefined): this {
        return this
    }
    public onChange(value: ((isVisible: boolean) => void) | undefined): this {
        return this
    }
    public contentFont(value: Font | undefined): this {
        return this
    }
    public contentFontColor(value: ResourceColor | undefined): this {
        return this
    }
    public labelFont(value: Font | undefined): this {
        return this
    }
    public labelFontColor(value: ResourceColor | undefined): this {
        return this
    }
    public _onChangeEvent_selected(callback: ((select: boolean | undefined) => void)): void {
        throw new Error("Unimplmented")
        }
}
export class ArkMenuItemComponent extends ArkCommonMethodComponent implements MenuItemAttribute {
    getPeer(): ArkMenuItemPeer {
        return (this.peer as ArkMenuItemPeer)
    }
    public setMenuItemOptions(value?: MenuItemOptions | CustomBuilder): this {
        if (this.checkPriority("setMenuItemOptions")) {
            const value_casted = value as (MenuItemOptions | CustomBuilder | undefined)
            this.getPeer()?.setMenuItemOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    public selected(value: boolean | undefined): this {
        if (this.checkPriority("selected")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.selectedAttribute(value_casted)
            return this
        }
        return this
    }
    public selectIcon(value: boolean | ResourceStr | SymbolGlyphModifier | undefined): this {
        if (this.checkPriority("selectIcon")) {
            const value_casted = value as (boolean | ResourceStr | SymbolGlyphModifier | undefined)
            this.getPeer()?.selectIconAttribute(value_casted)
            return this
        }
        return this
    }
    public onChange(value: ((isVisible: boolean) => void) | undefined): this {
        if (this.checkPriority("onChange")) {
            const value_casted = value as (((isVisible: boolean) => void) | undefined)
            this.getPeer()?.onChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public contentFont(value: Font | undefined): this {
        if (this.checkPriority("contentFont")) {
            const value_casted = value as (Font | undefined)
            this.getPeer()?.contentFontAttribute(value_casted)
            return this
        }
        return this
    }
    public contentFontColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("contentFontColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.contentFontColorAttribute(value_casted)
            return this
        }
        return this
    }
    public labelFont(value: Font | undefined): this {
        if (this.checkPriority("labelFont")) {
            const value_casted = value as (Font | undefined)
            this.getPeer()?.labelFontAttribute(value_casted)
            return this
        }
        return this
    }
    public labelFontColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("labelFontColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.labelFontColorAttribute(value_casted)
            return this
        }
        return this
    }
    public _onChangeEvent_selected(callback: ((select: boolean | undefined) => void)): void {
        if (this.checkPriority("_onChangeEvent_selected")) {
            const callback_casted = callback as (((select: boolean | undefined) => void))
            this.getPeer()?._onChangeEvent_selectedAttribute(callback_casted)
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
export function MenuItem(
    /** @memo */
    style: ((attributes: MenuItemAttribute) => void) | undefined,
    value?: MenuItemOptions | CustomBuilder,
    /** @memo */
    content_?: (() => void) | undefined,
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
