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

import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, wrapCallback, NativeBuffer } from "@koalaui/interop"
import { Font_serializer, BorderRadiuses_serializer, DividerStyleOptions_serializer, Font, ResourceColor, Dimension, BorderRadiuses, DividerStyleOptions } from "./units"
import { Resource_serializer, Resource } from "./../generated/resource"
import { int32, int64, float32 } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonMethodSet } from "./common"
import { Color } from "./enums"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkMenuPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkMenuPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Menu_construct(peerId, flags)
        const _peer  = new ArkMenuPeer(_peerPtr, peerId, "Menu", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setMenuOptionsAttribute(): void {
        ArkUIGeneratedNativeModule._MenuInterface_setMenuOptions(this.peer.ptr)
    }
    setFontAttribute(value: Font | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            Font_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._MenuAttribute_setFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontColorAttribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._MenuAttribute_setFontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setRadiusAttribute(value: Dimension | BorderRadiuses | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if ((RuntimeType.STRING == value_value_type) || (RuntimeType.NUMBER == value_value_type) || (RuntimeType.OBJECT == value_value_type)) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as Dimension
                let value_value_0_type : int32 = RuntimeType.UNDEFINED
                value_value_0_type = runtimeType(value_value_0)
                if (RuntimeType.STRING == value_value_0_type) {
                    thisSerializer.writeInt8((0).toChar())
                    const value_value_0_0  = value_value_0 as string
                    thisSerializer.writeString(value_value_0_0)
                }
                else if (RuntimeType.NUMBER == value_value_0_type) {
                    thisSerializer.writeInt8((1).toChar())
                    const value_value_0_1  = value_value_0 as number
                    thisSerializer.writeNumber(value_value_0_1)
                }
                else if (RuntimeType.OBJECT == value_value_0_type) {
                    thisSerializer.writeInt8((2).toChar())
                    const value_value_0_2  = value_value_0 as Resource
                    Resource_serializer.write(thisSerializer, value_value_0_2)
                }
            }
            else if (TypeChecker.isBorderRadiuses(value_value, false, false, false, false)) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as BorderRadiuses
                BorderRadiuses_serializer.write(thisSerializer, value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._MenuAttribute_setRadius(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMenuItemDividerAttribute(value: DividerStyleOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            DividerStyleOptions_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._MenuAttribute_setMenuItemDivider(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMenuItemGroupDividerAttribute(value: DividerStyleOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            DividerStyleOptions_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._MenuAttribute_setMenuItemGroupDivider(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSubMenuExpandingModeAttribute(value: SubMenuExpandingMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as SubMenuExpandingMode)
            thisSerializer.writeInt32(TypeChecker.SubMenuExpandingMode_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._MenuAttribute_setSubMenuExpandingMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export enum SubMenuExpandingMode {
    SIDE_EXPAND = 0,
    EMBEDDED_EXPAND = 1,
    STACK_EXPAND = 2
}
export interface MenuAttribute extends CommonMethod {
    font(value: Font | undefined): this {
        throw new Error("Unimplemented method font")
    }
    fontColor(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method fontColor")
    }
    radius(value: Dimension | BorderRadiuses | undefined): this {
        throw new Error("Unimplemented method radius")
    }
    menuItemDivider(value: DividerStyleOptions | undefined): this {
        throw new Error("Unimplemented method menuItemDivider")
    }
    menuItemGroupDivider(value: DividerStyleOptions | undefined): this {
        throw new Error("Unimplemented method menuItemGroupDivider")
    }
    subMenuExpandingMode(value: SubMenuExpandingMode | undefined): this {
        throw new Error("Unimplemented method subMenuExpandingMode")
    }
    attributeModifier(value: AttributeModifier<MenuAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkMenuStyle extends ArkCommonMethodStyle implements MenuAttribute {
    font_value?: Font | undefined
    fontColor_value?: ResourceColor | undefined
    radius_value?: Dimension | BorderRadiuses | undefined
    menuItemDivider_value?: DividerStyleOptions | undefined
    menuItemGroupDivider_value?: DividerStyleOptions | undefined
    subMenuExpandingMode_value?: SubMenuExpandingMode | undefined
    attributeModifier_value?: AttributeModifier<MenuAttribute> | AttributeModifier<CommonMethod> | undefined
    public font(value: Font | undefined): this {
        return this
    }
    public fontColor(value: ResourceColor | undefined): this {
        return this
    }
    public radius(value: Dimension | BorderRadiuses | undefined): this {
        return this
    }
    public menuItemDivider(value: DividerStyleOptions | undefined): this {
        return this
    }
    public menuItemGroupDivider(value: DividerStyleOptions | undefined): this {
        return this
    }
    public subMenuExpandingMode(value: SubMenuExpandingMode | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<MenuAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: MenuAttribute): void {
        super.apply(target)
        if (this.font_value !== undefined)
            target.font(this.font_value!)
        if (this.fontColor_value !== undefined)
            target.fontColor(this.fontColor_value!)
        if (this.radius_value !== undefined)
            target.radius(this.radius_value!)
        if (this.menuItemDivider_value !== undefined)
            target.menuItemDivider(this.menuItemDivider_value!)
        if (this.menuItemGroupDivider_value !== undefined)
            target.menuItemGroupDivider(this.menuItemGroupDivider_value!)
        if (this.subMenuExpandingMode_value !== undefined)
            target.subMenuExpandingMode(this.subMenuExpandingMode_value!)
    }
}

export class ArkMenuComponent extends ArkCommonMethodComponent implements MenuAttribute {
    getPeer(): ArkMenuPeer {
        return (this.peer as ArkMenuPeer)
    }
    public setMenuOptions(): this {
        if (this.checkPriority("setMenuOptions")) {
            this.getPeer()?.setMenuOptionsAttribute()
            return this
        }
        return this
    }
    public font(value: Font | undefined): this {
        if (this.checkPriority("font")) {
            const value_casted = value as (Font | undefined)
            this.getPeer()?.setFontAttribute(value_casted)
            return this
        }
        return this
    }
    public fontColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("fontColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setFontColorAttribute(value_casted)
            return this
        }
        return this
    }
    public radius(value: Dimension | BorderRadiuses | undefined): this {
        if (this.checkPriority("radius")) {
            const value_casted = value as (Dimension | BorderRadiuses | undefined)
            this.getPeer()?.setRadiusAttribute(value_casted)
            return this
        }
        return this
    }
    public menuItemDivider(value: DividerStyleOptions | undefined): this {
        if (this.checkPriority("menuItemDivider")) {
            const value_casted = value as (DividerStyleOptions | undefined)
            this.getPeer()?.setMenuItemDividerAttribute(value_casted)
            return this
        }
        return this
    }
    public menuItemGroupDivider(value: DividerStyleOptions | undefined): this {
        if (this.checkPriority("menuItemGroupDivider")) {
            const value_casted = value as (DividerStyleOptions | undefined)
            this.getPeer()?.setMenuItemGroupDividerAttribute(value_casted)
            return this
        }
        return this
    }
    public subMenuExpandingMode(value: SubMenuExpandingMode | undefined): this {
        if (this.checkPriority("subMenuExpandingMode")) {
            const value_casted = value as (SubMenuExpandingMode | undefined)
            this.getPeer()?.setSubMenuExpandingModeAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<MenuAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withMenuStyle(receiver: MenuAttribute, modifier: AttributeModifier<MenuAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkMenuStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("Menu")
// export function Menu(
//     
//     @memo
//     content_?: () => void,
// ): MenuAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function Menu(
    @memo
    style: ((attributes: MenuAttribute) => void) | undefined,
    
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkMenuComponent>((): ArkMenuComponent => {
        return new ArkMenuComponent()
    })
    NodeAttach<ArkMenuPeer>((): ArkMenuPeer => ArkMenuPeer.create(receiver), (_: ArkMenuPeer): void => {
        receiver.setMenuOptions()
        style?.(receiver)
        withMenuStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkMenuSet extends ArkCommonMethodSet implements MenuAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _font_flag?: boolean
    _font0_value?: Font | undefined
    _fontColor_flag?: boolean
    _fontColor0_value?: ResourceColor | undefined
    _radius_flag?: boolean
    _radius0_value?: Dimension | BorderRadiuses | undefined
    _menuItemDivider_flag?: boolean
    _menuItemDivider0_value?: DividerStyleOptions | undefined
    _menuItemGroupDivider_flag?: boolean
    _menuItemGroupDivider0_value?: DividerStyleOptions | undefined
    _subMenuExpandingMode_flag?: boolean
    _subMenuExpandingMode0_value?: SubMenuExpandingMode | undefined
    applyModifierPatch(component: MenuAttribute): void {
        if (this._font_flag)
            component.font((this._font0_value as Font | undefined))
        if (this._fontColor_flag)
            component.fontColor((this._fontColor0_value as ResourceColor | undefined))
        if (this._radius_flag)
            component.radius((this._radius0_value as Dimension | BorderRadiuses | undefined))
        if (this._menuItemDivider_flag)
            component.menuItemDivider((this._menuItemDivider0_value as DividerStyleOptions | undefined))
        if (this._menuItemGroupDivider_flag)
            component.menuItemGroupDivider((this._menuItemGroupDivider0_value as DividerStyleOptions | undefined))
        if (this._subMenuExpandingMode_flag)
            component.subMenuExpandingMode((this._subMenuExpandingMode0_value as SubMenuExpandingMode | undefined))
    }
    public font(value: Font | undefined): this {
        this._font_flag = true
        this._font0_value = value
        return this
    }
    public fontColor(value: ResourceColor | undefined): this {
        this._fontColor_flag = true
        this._fontColor0_value = value
        return this
    }
    public radius(value: Dimension | BorderRadiuses | undefined): this {
        this._radius_flag = true
        this._radius0_value = value
        return this
    }
    public menuItemDivider(value: DividerStyleOptions | undefined): this {
        this._menuItemDivider_flag = true
        this._menuItemDivider0_value = value
        return this
    }
    public menuItemGroupDivider(value: DividerStyleOptions | undefined): this {
        this._menuItemGroupDivider_flag = true
        this._menuItemGroupDivider0_value = value
        return this
    }
    public subMenuExpandingMode(value: SubMenuExpandingMode | undefined): this {
        this._subMenuExpandingMode_flag = true
        this._subMenuExpandingMode0_value = value
        return this
    }
    public attributeModifier(value: AttributeModifier<MenuAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
