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

import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, wrapCallback, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { Resource_serializer, Resource } from "./../generated/resource"
import { SymbolGlyphModifier_serializer, SymbolGlyphModifier } from "./../generated/arkui.SymbolGlyphModifier"
import { Font_serializer, ResourceStr, Font, ResourceColor } from "./units"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonMethodSet } from "./common"
import { Color } from "./enums"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CustomBuilder } from "./builder"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
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
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as MenuItemOptions
                MenuItemOptions_serializer.write(thisSerializer, value_value_0)
            }
            else if (RuntimeType.FUNCTION == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as CustomBuilder
                thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value_value_1))
            }
        }
        ArkUIGeneratedNativeModule._MenuItemInterface_setMenuItemOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectedAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._MenuItemAttribute_setSelected(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectIconAttribute(value: boolean | ResourceStr | SymbolGlyphModifier | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.BOOLEAN == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as boolean
                thisSerializer.writeBoolean(value_value_0)
            }
            else if ((RuntimeType.STRING == value_value_type) || (RuntimeType.OBJECT == value_value_type)) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as ResourceStr
                let value_value_1_type : int32 = RuntimeType.UNDEFINED
                value_value_1_type = runtimeType(value_value_1)
                if (RuntimeType.STRING == value_value_1_type) {
                    thisSerializer.writeInt8((0).toChar())
                    const value_value_1_0  = value_value_1 as string
                    thisSerializer.writeString(value_value_1_0)
                }
                else if (RuntimeType.OBJECT == value_value_1_type) {
                    thisSerializer.writeInt8((1).toChar())
                    const value_value_1_1  = value_value_1 as Resource
                    Resource_serializer.write(thisSerializer, value_value_1_1)
                }
            }
            else if (TypeChecker.isSymbolGlyphModifier(value_value)) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as SymbolGlyphModifier
                SymbolGlyphModifier_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._MenuItemAttribute_setSelectIcon(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnChangeAttribute(value: ((selected: boolean) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._MenuItemAttribute_setOnChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setContentFontAttribute(value: Font | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            Font_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._MenuItemAttribute_setContentFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setContentFontColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((3).toChar())
                const value_value_3  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._MenuItemAttribute_setContentFontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setLabelFontAttribute(value: Font | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            Font_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._MenuItemAttribute_setLabelFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setLabelFontColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((3).toChar())
                const value_value_3  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._MenuItemAttribute_setLabelFontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    set_onChangeEvent_selectedAttribute(callback_: ((selected: boolean | undefined) => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(callback_)
        ArkUIGeneratedNativeModule._MenuItemAttribute_set_onChangeEvent_selected(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
    selected(value: boolean | undefined): this {
        throw new Error("Unimplemented method selected")
    }
    selectIcon(value: boolean | ResourceStr | SymbolGlyphModifier | undefined): this {
        throw new Error("Unimplemented method selectIcon")
    }
    onChange(value: ((selected: boolean) => void) | undefined): this {
        throw new Error("Unimplemented method onChange")
    }
    contentFont(value: Font | undefined): this {
        throw new Error("Unimplemented method contentFont")
    }
    contentFontColor(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method contentFontColor")
    }
    labelFont(value: Font | undefined): this {
        throw new Error("Unimplemented method labelFont")
    }
    labelFontColor(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method labelFontColor")
    }
    _onChangeEvent_selected(callback_: ((selected: boolean | undefined) => void)): void {
        throw new Error("Unimplemented method _onChangeEvent_selected")
    }
    attributeModifier(value: AttributeModifier<MenuItemAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkMenuItemStyle extends ArkCommonMethodStyle implements MenuItemAttribute {
    selected_value?: boolean | undefined
    selectIcon_value?: boolean | ResourceStr | SymbolGlyphModifier | undefined
    onChange_value?: ((selected: boolean) => void) | undefined
    contentFont_value?: Font | undefined
    contentFontColor_value?: ResourceColor | undefined
    labelFont_value?: Font | undefined
    labelFontColor_value?: ResourceColor | undefined
    attributeModifier_value?: AttributeModifier<MenuItemAttribute> | AttributeModifier<CommonMethod> | undefined
    public selected(value: boolean | undefined): this {
        return this
    }
    public selectIcon(value: boolean | ResourceStr | SymbolGlyphModifier | undefined): this {
        return this
    }
    public onChange(value: ((selected: boolean) => void) | undefined): this {
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
    public _onChangeEvent_selected(callback_: ((selected: boolean | undefined) => void)): void {
        throw new Error("Unimplemented")
    }
    public attributeModifier(value: AttributeModifier<MenuItemAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: MenuItemAttribute): void {
        super.apply(target)
        if (this.selected_value !== undefined)
            target.selected(this.selected_value!)
        if (this.selectIcon_value !== undefined)
            target.selectIcon(this.selectIcon_value!)
        if (this.onChange_value !== undefined)
            target.onChange(this.onChange_value!)
        if (this.contentFont_value !== undefined)
            target.contentFont(this.contentFont_value!)
        if (this.contentFontColor_value !== undefined)
            target.contentFontColor(this.contentFontColor_value!)
        if (this.labelFont_value !== undefined)
            target.labelFont(this.labelFont_value!)
        if (this.labelFontColor_value !== undefined)
            target.labelFontColor(this.labelFontColor_value!)
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
            this.getPeer()?.setSelectedAttribute(value_casted)
            return this
        }
        return this
    }
    public selectIcon(value: boolean | ResourceStr | SymbolGlyphModifier | undefined): this {
        if (this.checkPriority("selectIcon")) {
            const value_casted = value as (boolean | ResourceStr | SymbolGlyphModifier | undefined)
            this.getPeer()?.setSelectIconAttribute(value_casted)
            return this
        }
        return this
    }
    public onChange(value: ((selected: boolean) => void) | undefined): this {
        if (this.checkPriority("onChange")) {
            const value_casted = value as (((selected: boolean) => void) | undefined)
            this.getPeer()?.setOnChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public contentFont(value: Font | undefined): this {
        if (this.checkPriority("contentFont")) {
            const value_casted = value as (Font | undefined)
            this.getPeer()?.setContentFontAttribute(value_casted)
            return this
        }
        return this
    }
    public contentFontColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("contentFontColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setContentFontColorAttribute(value_casted)
            return this
        }
        return this
    }
    public labelFont(value: Font | undefined): this {
        if (this.checkPriority("labelFont")) {
            const value_casted = value as (Font | undefined)
            this.getPeer()?.setLabelFontAttribute(value_casted)
            return this
        }
        return this
    }
    public labelFontColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("labelFontColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setLabelFontColorAttribute(value_casted)
            return this
        }
        return this
    }
    public _onChangeEvent_selected(callback_: ((selected: boolean | undefined) => void)): void {
        if (this.checkPriority("_onChangeEvent_selected")) {
            const callback__casted = callback_ as (((selected: boolean | undefined) => void))
            this.getPeer()?.set_onChangeEvent_selectedAttribute(callback__casted)
            return
        }
        return
    }
    public attributeModifier(value: AttributeModifier<MenuItemAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withMenuItemStyle(receiver: MenuItemAttribute, modifier: AttributeModifier<MenuItemAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkMenuItemStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("MenuItem")
// export function MenuItem(
//     value?: MenuItemOptions | CustomBuilder,
//     @memo
//     content_?: () => void,
// ): MenuItemAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function MenuItem(
    @memo
    style: ((attributes: MenuItemAttribute) => void) | undefined,
    value?: MenuItemOptions | CustomBuilder,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkMenuItemComponent>((): ArkMenuItemComponent => {
        return new ArkMenuItemComponent()
    })
    NodeAttach<ArkMenuItemPeer>((): ArkMenuItemPeer => ArkMenuItemPeer.create(receiver), (_: ArkMenuItemPeer): void => {
        receiver.setMenuItemOptions(value)
        style?.(receiver)
        withMenuItemStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkMenuItemSet extends ArkCommonMethodSet implements MenuItemAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _selected_flag?: boolean
    _selected0_value?: boolean | undefined
    _selectIcon_flag?: boolean
    _selectIcon0_value?: boolean | ResourceStr | SymbolGlyphModifier | undefined
    _onChange_flag?: boolean
    _onChange0_value?: ((selected: boolean) => void) | undefined
    _contentFont_flag?: boolean
    _contentFont0_value?: Font | undefined
    _contentFontColor_flag?: boolean
    _contentFontColor0_value?: ResourceColor | undefined
    _labelFont_flag?: boolean
    _labelFont0_value?: Font | undefined
    _labelFontColor_flag?: boolean
    _labelFontColor0_value?: ResourceColor | undefined
    __onChangeEvent_selected_flag?: boolean
    __onChangeEvent_selected0_value?: ((selected: boolean | undefined) => void)
    applyModifierPatch(component: MenuItemAttribute): void {
        if (this._selected_flag)
            component.selected((this._selected0_value as boolean | undefined))
        if (this._selectIcon_flag)
            component.selectIcon((this._selectIcon0_value as boolean | ResourceStr | SymbolGlyphModifier | undefined))
        if (this._onChange_flag)
            component.onChange((this._onChange0_value as ((selected: boolean) => void) | undefined))
        if (this._contentFont_flag)
            component.contentFont((this._contentFont0_value as Font | undefined))
        if (this._contentFontColor_flag)
            component.contentFontColor((this._contentFontColor0_value as ResourceColor | undefined))
        if (this._labelFont_flag)
            component.labelFont((this._labelFont0_value as Font | undefined))
        if (this._labelFontColor_flag)
            component.labelFontColor((this._labelFontColor0_value as ResourceColor | undefined))
    }
    public selected(value: boolean | undefined): this {
        this._selected_flag = true
        this._selected0_value = value
        return this
    }
    public selectIcon(value: boolean | ResourceStr | SymbolGlyphModifier | undefined): this {
        this._selectIcon_flag = true
        this._selectIcon0_value = value
        return this
    }
    public onChange(value: ((selected: boolean) => void) | undefined): this {
        this._onChange_flag = true
        this._onChange0_value = value
        return this
    }
    public contentFont(value: Font | undefined): this {
        this._contentFont_flag = true
        this._contentFont0_value = value
        return this
    }
    public contentFontColor(value: ResourceColor | undefined): this {
        this._contentFontColor_flag = true
        this._contentFontColor0_value = value
        return this
    }
    public labelFont(value: Font | undefined): this {
        this._labelFont_flag = true
        this._labelFont0_value = value
        return this
    }
    public labelFontColor(value: ResourceColor | undefined): this {
        this._labelFontColor_flag = true
        this._labelFontColor0_value = value
        return this
    }
    public _onChangeEvent_selected(callback_: ((selected: boolean | undefined) => void)): void {
    }
    public attributeModifier(value: AttributeModifier<MenuItemAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class MenuItemOptions_serializer {
    public static write(buffer: SerializerBase, value: MenuItemOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_startIcon  = value.startIcon
        let value_startIcon_type : int32 = RuntimeType.UNDEFINED
        value_startIcon_type = runtimeType(value_startIcon)
        valueSerializer.writeInt8((value_startIcon_type).toChar())
        if ((value_startIcon_type) != (RuntimeType.UNDEFINED)) {
            const value_startIcon_value  = value_startIcon!
            let value_startIcon_value_type : int32 = RuntimeType.UNDEFINED
            value_startIcon_value_type = runtimeType(value_startIcon_value)
            if (RuntimeType.STRING == value_startIcon_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_startIcon_value_0  = value_startIcon_value as string
                valueSerializer.writeString(value_startIcon_value_0)
            }
            else if (RuntimeType.OBJECT == value_startIcon_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_startIcon_value_1  = value_startIcon_value as Resource
                Resource_serializer.write(valueSerializer, value_startIcon_value_1)
            }
        }
        const value_symbolStartIcon  = value.symbolStartIcon
        let value_symbolStartIcon_type : int32 = RuntimeType.UNDEFINED
        value_symbolStartIcon_type = runtimeType(value_symbolStartIcon)
        valueSerializer.writeInt8((value_symbolStartIcon_type).toChar())
        if ((value_symbolStartIcon_type) != (RuntimeType.UNDEFINED)) {
            const value_symbolStartIcon_value  = value_symbolStartIcon!
            SymbolGlyphModifier_serializer.write(valueSerializer, value_symbolStartIcon_value)
        }
        const value_content  = value.content
        let value_content_type : int32 = RuntimeType.UNDEFINED
        value_content_type = runtimeType(value_content)
        valueSerializer.writeInt8((value_content_type).toChar())
        if ((value_content_type) != (RuntimeType.UNDEFINED)) {
            const value_content_value  = value_content!
            let value_content_value_type : int32 = RuntimeType.UNDEFINED
            value_content_value_type = runtimeType(value_content_value)
            if (RuntimeType.STRING == value_content_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_content_value_0  = value_content_value as string
                valueSerializer.writeString(value_content_value_0)
            }
            else if (RuntimeType.OBJECT == value_content_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_content_value_1  = value_content_value as Resource
                Resource_serializer.write(valueSerializer, value_content_value_1)
            }
        }
        const value_endIcon  = value.endIcon
        let value_endIcon_type : int32 = RuntimeType.UNDEFINED
        value_endIcon_type = runtimeType(value_endIcon)
        valueSerializer.writeInt8((value_endIcon_type).toChar())
        if ((value_endIcon_type) != (RuntimeType.UNDEFINED)) {
            const value_endIcon_value  = value_endIcon!
            let value_endIcon_value_type : int32 = RuntimeType.UNDEFINED
            value_endIcon_value_type = runtimeType(value_endIcon_value)
            if (RuntimeType.STRING == value_endIcon_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_endIcon_value_0  = value_endIcon_value as string
                valueSerializer.writeString(value_endIcon_value_0)
            }
            else if (RuntimeType.OBJECT == value_endIcon_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_endIcon_value_1  = value_endIcon_value as Resource
                Resource_serializer.write(valueSerializer, value_endIcon_value_1)
            }
        }
        const value_symbolEndIcon  = value.symbolEndIcon
        let value_symbolEndIcon_type : int32 = RuntimeType.UNDEFINED
        value_symbolEndIcon_type = runtimeType(value_symbolEndIcon)
        valueSerializer.writeInt8((value_symbolEndIcon_type).toChar())
        if ((value_symbolEndIcon_type) != (RuntimeType.UNDEFINED)) {
            const value_symbolEndIcon_value  = value_symbolEndIcon!
            SymbolGlyphModifier_serializer.write(valueSerializer, value_symbolEndIcon_value)
        }
        const value_labelInfo  = value.labelInfo
        let value_labelInfo_type : int32 = RuntimeType.UNDEFINED
        value_labelInfo_type = runtimeType(value_labelInfo)
        valueSerializer.writeInt8((value_labelInfo_type).toChar())
        if ((value_labelInfo_type) != (RuntimeType.UNDEFINED)) {
            const value_labelInfo_value  = value_labelInfo!
            let value_labelInfo_value_type : int32 = RuntimeType.UNDEFINED
            value_labelInfo_value_type = runtimeType(value_labelInfo_value)
            if (RuntimeType.STRING == value_labelInfo_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_labelInfo_value_0  = value_labelInfo_value as string
                valueSerializer.writeString(value_labelInfo_value_0)
            }
            else if (RuntimeType.OBJECT == value_labelInfo_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_labelInfo_value_1  = value_labelInfo_value as Resource
                Resource_serializer.write(valueSerializer, value_labelInfo_value_1)
            }
        }
        const value_builder  = value.builder
        let value_builder_type : int32 = RuntimeType.UNDEFINED
        value_builder_type = runtimeType(value_builder)
        valueSerializer.writeInt8((value_builder_type).toChar())
        if ((value_builder_type) != (RuntimeType.UNDEFINED)) {
            const value_builder_value  = value_builder!
            valueSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value_builder_value))
        }
    }
    public static read(buffer: DeserializerBase): MenuItemOptions {
        let valueDeserializer : DeserializerBase = buffer
        const startIcon_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let startIcon_buf : ResourceStr | undefined
        if ((startIcon_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const startIcon_buf__selector : int32 = valueDeserializer.readInt8()
            let startIcon_buf_ : string | Resource | undefined
            if (startIcon_buf__selector == (0).toChar()) {
                startIcon_buf_ = (valueDeserializer.readString() as string)
            }
            else if (startIcon_buf__selector == (1).toChar()) {
                startIcon_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for startIcon_buf_ has to be chosen through deserialisation.")
            }
            startIcon_buf = (startIcon_buf_ as string | Resource)
        }
        const startIcon_result : ResourceStr | undefined = startIcon_buf
        const symbolStartIcon_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let symbolStartIcon_buf : SymbolGlyphModifier | undefined
        if ((symbolStartIcon_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            symbolStartIcon_buf = SymbolGlyphModifier_serializer.read(valueDeserializer)
        }
        const symbolStartIcon_result : SymbolGlyphModifier | undefined = symbolStartIcon_buf
        const content_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let content_buf : ResourceStr | undefined
        if ((content_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const content_buf__selector : int32 = valueDeserializer.readInt8()
            let content_buf_ : string | Resource | undefined
            if (content_buf__selector == (0).toChar()) {
                content_buf_ = (valueDeserializer.readString() as string)
            }
            else if (content_buf__selector == (1).toChar()) {
                content_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for content_buf_ has to be chosen through deserialisation.")
            }
            content_buf = (content_buf_ as string | Resource)
        }
        const content_result : ResourceStr | undefined = content_buf
        const endIcon_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let endIcon_buf : ResourceStr | undefined
        if ((endIcon_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const endIcon_buf__selector : int32 = valueDeserializer.readInt8()
            let endIcon_buf_ : string | Resource | undefined
            if (endIcon_buf__selector == (0).toChar()) {
                endIcon_buf_ = (valueDeserializer.readString() as string)
            }
            else if (endIcon_buf__selector == (1).toChar()) {
                endIcon_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for endIcon_buf_ has to be chosen through deserialisation.")
            }
            endIcon_buf = (endIcon_buf_ as string | Resource)
        }
        const endIcon_result : ResourceStr | undefined = endIcon_buf
        const symbolEndIcon_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let symbolEndIcon_buf : SymbolGlyphModifier | undefined
        if ((symbolEndIcon_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            symbolEndIcon_buf = SymbolGlyphModifier_serializer.read(valueDeserializer)
        }
        const symbolEndIcon_result : SymbolGlyphModifier | undefined = symbolEndIcon_buf
        const labelInfo_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let labelInfo_buf : ResourceStr | undefined
        if ((labelInfo_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const labelInfo_buf__selector : int32 = valueDeserializer.readInt8()
            let labelInfo_buf_ : string | Resource | undefined
            if (labelInfo_buf__selector == (0).toChar()) {
                labelInfo_buf_ = (valueDeserializer.readString() as string)
            }
            else if (labelInfo_buf__selector == (1).toChar()) {
                labelInfo_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for labelInfo_buf_ has to be chosen through deserialisation.")
            }
            labelInfo_buf = (labelInfo_buf_ as string | Resource)
        }
        const labelInfo_result : ResourceStr | undefined = labelInfo_buf
        const builder_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let builder_buf : CustomBuilder | undefined
        if ((builder_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const builder_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const builder_buf__call : KPointer = valueDeserializer.readPointer()
            const builder_buf__callSync : KPointer = valueDeserializer.readPointer()
            builder_buf = ():void => { 
    const builder_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    builder_buf__argsSerializer.writeInt32(builder_buf__resource.resourceId);
    builder_buf__argsSerializer.writePointer(builder_buf__call);
    builder_buf__argsSerializer.writePointer(builder_buf__callSync);
    InteropNativeModule._CallCallback(737226752, builder_buf__argsSerializer.asBuffer(), builder_buf__argsSerializer.length());
    builder_buf__argsSerializer.release();
    return; }
        }
        const builder_result : CustomBuilder | undefined = builder_buf
        let value : MenuItemOptions = ({startIcon: startIcon_result, symbolStartIcon: symbolStartIcon_result, content: content_result, endIcon: endIcon_result, symbolEndIcon: symbolEndIcon_result, labelInfo: labelInfo_result, builder: builder_result} as MenuItemOptions)
        return value
    }
}
