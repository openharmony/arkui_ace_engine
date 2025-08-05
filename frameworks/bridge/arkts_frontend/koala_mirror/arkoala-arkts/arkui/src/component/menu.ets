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

import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer } from "@koalaui/interop"
import { Font_serializer, BorderRadiuses_serializer, DividerStyleOptions_serializer, Font, ResourceColor, Dimension, BorderRadiuses, DividerStyleOptions } from "./units"
import { Resource_serializer, Resource } from "./../generated/resource"
import { int32, int64, float32 } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, CommonMethodModifier } from "./common"
import { Color } from "./enums"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
import { AttributeUpdaterFlag } from "./../generated/AttributeUpdater"
export class ArkMenuPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkMenuPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Menu_construct(peerId, flags)
        const _peer  = new ArkMenuPeer(_peerPtr, peerId, 'Menu', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setMenuOptionsAttribute(): void {
        ArkUIGeneratedNativeModule._MenuInterface_setMenuOptions(this.peer.ptr)
    }
    setFontAttribute(value: Font | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            Font_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._MenuAttribute_setFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof Color) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueTmpValueForIdx0))
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((3).toChar())
                const valueTmpValueForIdx3  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._MenuAttribute_setFontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setRadiusAttribute(value: Dimension | BorderRadiuses | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof Dimension) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as Dimension
                if (valueTmpValueForIdx0 instanceof string) {
                    thisSerializer.writeInt8((0).toChar())
                    const valueTmpValueForIdx0ForIdx0  = valueTmpValueForIdx0 as string
                    thisSerializer.writeString(valueTmpValueForIdx0ForIdx0)
                } else if (valueTmpValueForIdx0 instanceof number) {
                    thisSerializer.writeInt8((1).toChar())
                    const valueTmpValueForIdx0ForIdx1  = valueTmpValueForIdx0 as number
                    thisSerializer.writeNumber(valueTmpValueForIdx0ForIdx1)
                } else if (valueTmpValueForIdx0 instanceof Resource) {
                    thisSerializer.writeInt8((2).toChar())
                    const valueTmpValueForIdx0ForIdx2  = valueTmpValueForIdx0 as Resource
                    Resource_serializer.write(thisSerializer, valueTmpValueForIdx0ForIdx2)
                }
            } else if (valueTmpValue instanceof BorderRadiuses) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as BorderRadiuses
                BorderRadiuses_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._MenuAttribute_setRadius(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMenuItemDividerAttribute(value: DividerStyleOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            DividerStyleOptions_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._MenuAttribute_setMenuItemDivider(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMenuItemGroupDividerAttribute(value: DividerStyleOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            DividerStyleOptions_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._MenuAttribute_setMenuItemGroupDivider(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSubMenuExpandingModeAttribute(value: SubMenuExpandingMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as SubMenuExpandingMode)
            thisSerializer.writeInt32(TypeChecker.SubMenuExpandingMode_ToNumeric(valueTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
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
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

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
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class MenuModifier extends CommonMethodModifier implements MenuAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _font_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _font_0_0value?: Font | undefined
    _fontColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontColor_0_0value?: ResourceColor | undefined
    _radius_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _radius_0_0value?: Dimension | BorderRadiuses | undefined
    _menuItemDivider_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _menuItemDivider_0_0value?: DividerStyleOptions | undefined
    _menuItemGroupDivider_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _menuItemGroupDivider_0_0value?: DividerStyleOptions | undefined
    _subMenuExpandingMode_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _subMenuExpandingMode_0_0value?: SubMenuExpandingMode | undefined
    applyModifierPatch(peer: ArkMenuPeer): void {
        super.applyModifierPatch(peer)
        if (this._font_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._font_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFontAttribute((this._font_0_0value as Font | undefined));
                    this._font_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._font_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._font_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFontAttribute((undefined as Font | undefined));
                }
            }
        }
        if (this._fontColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fontColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFontColorAttribute((this._fontColor_0_0value as ResourceColor | undefined));
                    this._fontColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fontColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fontColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFontColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._radius_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._radius_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setRadiusAttribute((this._radius_0_0value as Dimension | BorderRadiuses | undefined));
                    this._radius_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._radius_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._radius_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setRadiusAttribute((undefined as Dimension | BorderRadiuses | undefined));
                }
            }
        }
        if (this._menuItemDivider_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._menuItemDivider_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMenuItemDividerAttribute((this._menuItemDivider_0_0value as DividerStyleOptions | undefined));
                    this._menuItemDivider_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._menuItemDivider_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._menuItemDivider_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMenuItemDividerAttribute((undefined as DividerStyleOptions | undefined));
                }
            }
        }
        if (this._menuItemGroupDivider_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._menuItemGroupDivider_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMenuItemGroupDividerAttribute((this._menuItemGroupDivider_0_0value as DividerStyleOptions | undefined));
                    this._menuItemGroupDivider_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._menuItemGroupDivider_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._menuItemGroupDivider_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMenuItemGroupDividerAttribute((undefined as DividerStyleOptions | undefined));
                }
            }
        }
        if (this._subMenuExpandingMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._subMenuExpandingMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSubMenuExpandingModeAttribute((this._subMenuExpandingMode_0_0value as SubMenuExpandingMode | undefined));
                    this._subMenuExpandingMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._subMenuExpandingMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._subMenuExpandingMode_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSubMenuExpandingModeAttribute((undefined as SubMenuExpandingMode | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: MenuModifier): void {
        super.mergeModifier(modifier)
        if (modifier._font_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._font_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.font(modifier._font_0_0value);
                    break;
                }
                default: {
                    this.font((undefined as Font | undefined));
                }
            }
        }
        if (modifier._fontColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._fontColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.fontColor(modifier._fontColor_0_0value);
                    break;
                }
                default: {
                    this.fontColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._radius_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._radius_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.radius(modifier._radius_0_0value);
                    break;
                }
                default: {
                    this.radius((undefined as Dimension | BorderRadiuses | undefined));
                }
            }
        }
        if (modifier._menuItemDivider_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._menuItemDivider_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.menuItemDivider(modifier._menuItemDivider_0_0value);
                    break;
                }
                default: {
                    this.menuItemDivider((undefined as DividerStyleOptions | undefined));
                }
            }
        }
        if (modifier._menuItemGroupDivider_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._menuItemGroupDivider_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.menuItemGroupDivider(modifier._menuItemGroupDivider_0_0value);
                    break;
                }
                default: {
                    this.menuItemGroupDivider((undefined as DividerStyleOptions | undefined));
                }
            }
        }
        if (modifier._subMenuExpandingMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._subMenuExpandingMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.subMenuExpandingMode(modifier._subMenuExpandingMode_0_0value);
                    break;
                }
                default: {
                    this.subMenuExpandingMode((undefined as SubMenuExpandingMode | undefined));
                }
            }
        }
    }
    font(value: Font | undefined): this {
        if (((this._font_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._font_0_flag = AttributeUpdaterFlag.UPDATE
            this._font_0_0value = value
        } else
        {
            this._font_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    fontColor(value: ResourceColor | undefined): this {
        if (((this._fontColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._fontColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._fontColor_0_0value = value
        } else
        {
            this._fontColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    radius(value: Dimension | BorderRadiuses | undefined): this {
        if (((this._radius_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._radius_0_flag = AttributeUpdaterFlag.UPDATE
            this._radius_0_0value = value
        } else
        {
            this._radius_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    menuItemDivider(value: DividerStyleOptions | undefined): this {
        if (((this._menuItemDivider_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._menuItemDivider_0_flag = AttributeUpdaterFlag.UPDATE
            this._menuItemDivider_0_0value = value
        } else
        {
            this._menuItemDivider_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    menuItemGroupDivider(value: DividerStyleOptions | undefined): this {
        if (((this._menuItemGroupDivider_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._menuItemGroupDivider_0_flag = AttributeUpdaterFlag.UPDATE
            this._menuItemGroupDivider_0_0value = value
        } else
        {
            this._menuItemGroupDivider_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    subMenuExpandingMode(value: SubMenuExpandingMode | undefined): this {
        if (((this._subMenuExpandingMode_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._subMenuExpandingMode_0_flag = AttributeUpdaterFlag.UPDATE
            this._subMenuExpandingMode_0_0value = value
        } else
        {
            this._subMenuExpandingMode_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<MenuAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
