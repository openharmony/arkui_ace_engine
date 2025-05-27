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
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, UICommonMethod } from "./common"
import { Length, Font, ResourceColor, Dimension, BorderRadiuses, DividerStyleOptions } from "./units"
import { Resource } from "./resource"
import { Color } from "./enums"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { BuilderLambda } from "@koalaui/builderLambda"
import { UICommonBase, AttributeModifier } from "./../handwritten"
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
    fontSizeAttribute(value: Length): void {
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
        ArkUIGeneratedNativeModule._MenuAttribute_fontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontAttribute(value: Font): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeFont(value)
        ArkUIGeneratedNativeModule._MenuAttribute_font(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._MenuAttribute_fontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    radiusAttribute(value: Dimension | BorderRadiuses): void {
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
        else if (((RuntimeType.OBJECT) == (value_type)) && (TypeChecker.isBorderRadiuses(value, false, false, false, false))) {
            thisSerializer.writeInt8(1)
            const value_1  = value as BorderRadiuses
            const value_1_topLeft  = value_1.topLeft
            let value_1_topLeft_type : int32 = RuntimeType.UNDEFINED
            value_1_topLeft_type = runtimeType(value_1_topLeft)
            thisSerializer.writeInt8(value_1_topLeft_type)
            if ((RuntimeType.UNDEFINED) != (value_1_topLeft_type)) {
                const value_1_topLeft_value  = value_1_topLeft!
                let value_1_topLeft_value_type : int32 = RuntimeType.UNDEFINED
                value_1_topLeft_value_type = runtimeType(value_1_topLeft_value)
                if (RuntimeType.STRING == value_1_topLeft_value_type) {
                    thisSerializer.writeInt8(0)
                    const value_1_topLeft_value_0  = value_1_topLeft_value as string
                    thisSerializer.writeString(value_1_topLeft_value_0)
                }
                else if (RuntimeType.NUMBER == value_1_topLeft_value_type) {
                    thisSerializer.writeInt8(1)
                    const value_1_topLeft_value_1  = value_1_topLeft_value as number
                    thisSerializer.writeNumber(value_1_topLeft_value_1)
                }
                else if (RuntimeType.OBJECT == value_1_topLeft_value_type) {
                    thisSerializer.writeInt8(2)
                    const value_1_topLeft_value_2  = value_1_topLeft_value as Resource
                    thisSerializer.writeResource(value_1_topLeft_value_2)
                }
            }
            const value_1_topRight  = value_1.topRight
            let value_1_topRight_type : int32 = RuntimeType.UNDEFINED
            value_1_topRight_type = runtimeType(value_1_topRight)
            thisSerializer.writeInt8(value_1_topRight_type)
            if ((RuntimeType.UNDEFINED) != (value_1_topRight_type)) {
                const value_1_topRight_value  = value_1_topRight!
                let value_1_topRight_value_type : int32 = RuntimeType.UNDEFINED
                value_1_topRight_value_type = runtimeType(value_1_topRight_value)
                if (RuntimeType.STRING == value_1_topRight_value_type) {
                    thisSerializer.writeInt8(0)
                    const value_1_topRight_value_0  = value_1_topRight_value as string
                    thisSerializer.writeString(value_1_topRight_value_0)
                }
                else if (RuntimeType.NUMBER == value_1_topRight_value_type) {
                    thisSerializer.writeInt8(1)
                    const value_1_topRight_value_1  = value_1_topRight_value as number
                    thisSerializer.writeNumber(value_1_topRight_value_1)
                }
                else if (RuntimeType.OBJECT == value_1_topRight_value_type) {
                    thisSerializer.writeInt8(2)
                    const value_1_topRight_value_2  = value_1_topRight_value as Resource
                    thisSerializer.writeResource(value_1_topRight_value_2)
                }
            }
            const value_1_bottomLeft  = value_1.bottomLeft
            let value_1_bottomLeft_type : int32 = RuntimeType.UNDEFINED
            value_1_bottomLeft_type = runtimeType(value_1_bottomLeft)
            thisSerializer.writeInt8(value_1_bottomLeft_type)
            if ((RuntimeType.UNDEFINED) != (value_1_bottomLeft_type)) {
                const value_1_bottomLeft_value  = value_1_bottomLeft!
                let value_1_bottomLeft_value_type : int32 = RuntimeType.UNDEFINED
                value_1_bottomLeft_value_type = runtimeType(value_1_bottomLeft_value)
                if (RuntimeType.STRING == value_1_bottomLeft_value_type) {
                    thisSerializer.writeInt8(0)
                    const value_1_bottomLeft_value_0  = value_1_bottomLeft_value as string
                    thisSerializer.writeString(value_1_bottomLeft_value_0)
                }
                else if (RuntimeType.NUMBER == value_1_bottomLeft_value_type) {
                    thisSerializer.writeInt8(1)
                    const value_1_bottomLeft_value_1  = value_1_bottomLeft_value as number
                    thisSerializer.writeNumber(value_1_bottomLeft_value_1)
                }
                else if (RuntimeType.OBJECT == value_1_bottomLeft_value_type) {
                    thisSerializer.writeInt8(2)
                    const value_1_bottomLeft_value_2  = value_1_bottomLeft_value as Resource
                    thisSerializer.writeResource(value_1_bottomLeft_value_2)
                }
            }
            const value_1_bottomRight  = value_1.bottomRight
            let value_1_bottomRight_type : int32 = RuntimeType.UNDEFINED
            value_1_bottomRight_type = runtimeType(value_1_bottomRight)
            thisSerializer.writeInt8(value_1_bottomRight_type)
            if ((RuntimeType.UNDEFINED) != (value_1_bottomRight_type)) {
                const value_1_bottomRight_value  = value_1_bottomRight!
                let value_1_bottomRight_value_type : int32 = RuntimeType.UNDEFINED
                value_1_bottomRight_value_type = runtimeType(value_1_bottomRight_value)
                if (RuntimeType.STRING == value_1_bottomRight_value_type) {
                    thisSerializer.writeInt8(0)
                    const value_1_bottomRight_value_0  = value_1_bottomRight_value as string
                    thisSerializer.writeString(value_1_bottomRight_value_0)
                }
                else if (RuntimeType.NUMBER == value_1_bottomRight_value_type) {
                    thisSerializer.writeInt8(1)
                    const value_1_bottomRight_value_1  = value_1_bottomRight_value as number
                    thisSerializer.writeNumber(value_1_bottomRight_value_1)
                }
                else if (RuntimeType.OBJECT == value_1_bottomRight_value_type) {
                    thisSerializer.writeInt8(2)
                    const value_1_bottomRight_value_2  = value_1_bottomRight_value as Resource
                    thisSerializer.writeResource(value_1_bottomRight_value_2)
                }
            }
        }
        ArkUIGeneratedNativeModule._MenuAttribute_radius(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    menuItemDividerAttribute(value: DividerStyleOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeDividerStyleOptions(value_value)
        }
        ArkUIGeneratedNativeModule._MenuAttribute_menuItemDivider(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    menuItemGroupDividerAttribute(value: DividerStyleOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeDividerStyleOptions(value_value)
        }
        ArkUIGeneratedNativeModule._MenuAttribute_menuItemGroupDivider(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    subMenuExpandingModeAttribute(value: SubMenuExpandingMode): void {
        ArkUIGeneratedNativeModule._MenuAttribute_subMenuExpandingMode(this.peer.ptr, TypeChecker.SubMenuExpandingMode_ToNumeric(value))
    }
}

export enum SubMenuExpandingMode {
    SIDE_EXPAND = 0,
    EMBEDDED_EXPAND = 1,
    STACK_EXPAND = 2
}
export interface MenuAttribute extends CommonMethod {
    fontSize(value: Length): this
    font(value: Font): this
    fontColor(value: ResourceColor): this
    radius(value: Dimension | BorderRadiuses): this
    menuItemDivider(value: DividerStyleOptions | undefined): this
    menuItemGroupDivider(value: DividerStyleOptions | undefined): this
    subMenuExpandingMode(value: SubMenuExpandingMode): this
    attributeModifier(value: AttributeModifier<MenuAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export interface UIMenuAttribute extends UICommonMethod {
    @memo
    fontSize(value: Length): this
    @memo
    font(value: Font): this
    @memo
    fontColor(value: ResourceColor): this
    @memo
    radius(value: Dimension | BorderRadiuses): this
    @memo
    menuItemDivider(value: DividerStyleOptions | undefined): this
    @memo
    menuItemGroupDivider(value: DividerStyleOptions | undefined): this
    @memo
    subMenuExpandingMode(value: SubMenuExpandingMode): this
    @memo
    attributeModifier(value: AttributeModifier<MenuAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkMenuStyle extends ArkCommonMethodStyle implements MenuAttribute {
    fontSize_value?: Length
    font_value?: Font
    fontColor_value?: ResourceColor
    radius_value?: Dimension | BorderRadiuses
    menuItemDivider_value?: DividerStyleOptions | undefined
    menuItemGroupDivider_value?: DividerStyleOptions | undefined
    subMenuExpandingMode_value?: SubMenuExpandingMode
    public fontSize(value: Length): this {
        return this
    }
    public font(value: Font): this {
        return this
    }
    public fontColor(value: ResourceColor): this {
        return this
    }
    public radius(value: Dimension | BorderRadiuses): this {
        return this
    }
    public menuItemDivider(value: DividerStyleOptions | undefined): this {
        return this
    }
    public menuItemGroupDivider(value: DividerStyleOptions | undefined): this {
        return this
    }
    public subMenuExpandingMode(value: SubMenuExpandingMode): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<MenuAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
@memo_stable
export class ArkMenuComponent extends ArkCommonMethodComponent implements UIMenuAttribute {
    getPeer(): ArkMenuPeer {
        return (this.peer as ArkMenuPeer)
    }
    @memo
    public setMenuOptions(): this {
        if (this.checkPriority("setMenuOptions")) {
            this.getPeer()?.setMenuOptionsAttribute()
            return this
        }
        return this
    }
    @memo
    public fontSize(value: Length): this {
        if (this.checkPriority("fontSize")) {
            const value_casted = value as (Length)
            this.getPeer()?.fontSizeAttribute(value_casted)
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
    public radius(value: Dimension | BorderRadiuses): this {
        if (this.checkPriority("radius")) {
            const value_casted = value as (Dimension | BorderRadiuses)
            this.getPeer()?.radiusAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public menuItemDivider(value: DividerStyleOptions | undefined): this {
        if (this.checkPriority("menuItemDivider")) {
            const value_casted = value as (DividerStyleOptions | undefined)
            this.getPeer()?.menuItemDividerAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public menuItemGroupDivider(value: DividerStyleOptions | undefined): this {
        if (this.checkPriority("menuItemGroupDivider")) {
            const value_casted = value as (DividerStyleOptions | undefined)
            this.getPeer()?.menuItemGroupDividerAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public subMenuExpandingMode(value: SubMenuExpandingMode): this {
        if (this.checkPriority("subMenuExpandingMode")) {
            const value_casted = value as (SubMenuExpandingMode)
            this.getPeer()?.subMenuExpandingModeAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public attributeModifier(value: AttributeModifier<MenuAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
@memo
@BuilderLambda("Menu")
export function Menu(
    
    @memo
    content_?: () => void,
): MenuAttribute {
    throw new Error("Not implemented")
}

@memo
export function Menu(
    @memo
    style: ((attributes: UIMenuAttribute) => void) | undefined,
    
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
