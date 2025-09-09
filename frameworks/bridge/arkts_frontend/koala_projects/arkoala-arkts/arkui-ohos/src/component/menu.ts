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
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { Length, Font, ResourceColor, Dimension, BorderRadiuses, DividerStyleOptions, PX, VP, FP, LPX, Percentage } from "./units"
import { Resource } from "global.resource"
import { Color } from "./enums"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"

export class ArkMenuPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkMenuPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Menu_construct(peerId, flags)
        const _peer  = new ArkMenuPeer(_peerPtr, peerId, "Menu", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setMenuOptionsAttribute(): void {
        ArkUIGeneratedNativeModule._MenuInterface_setMenuOptions(this.peer.ptr)
    }
    fontSizeAttribute(value: Length | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeLength(value_value)
        }
        ArkUIGeneratedNativeModule._MenuAttribute_fontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontAttribute(value: Font | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeFont(value_value)
        }
        ArkUIGeneratedNativeModule._MenuAttribute_font(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontColorAttribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._MenuAttribute_fontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    radiusAttribute(value: Dimension | BorderRadiuses | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (((RuntimeType.NUMBER) == (value_value_type)) || ((RuntimeType.STRING) == (value_value_type)) || (((RuntimeType.OBJECT) == (value_value_type)) && (TypeChecker.isResource(value_value, false, false, false, false, false)))) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Dimension
                thisSerializer.writeLength(value_value_0)
            }
            else if (TypeChecker.isBorderRadiuses(value_value, false, false, false, false)) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as BorderRadiuses
                thisSerializer.writeBorderRadiuses(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._MenuAttribute_radius(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    menuItemDividerAttribute(value: DividerStyleOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
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
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeDividerStyleOptions(value_value)
        }
        ArkUIGeneratedNativeModule._MenuAttribute_menuItemGroupDivider(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    subMenuExpandingModeAttribute(value: SubMenuExpandingMode | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as SubMenuExpandingMode)
            thisSerializer.writeInt32(TypeChecker.SubMenuExpandingMode_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._MenuAttribute_subMenuExpandingMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export type MenuInterface = () => MenuAttribute;
export enum SubMenuExpandingMode {
    SIDE_EXPAND = 0,
    EMBEDDED_EXPAND = 1,
    STACK_EXPAND = 2
}
export interface MenuAttribute extends CommonMethod {
    fontSize(value: Length | undefined): this
    font(value: Font | undefined): this
    fontColor(value: ResourceColor | undefined): this
    radius(value: Dimension | BorderRadiuses | undefined): this
    menuItemDivider(value: DividerStyleOptions | undefined): this
    menuItemGroupDivider(value: DividerStyleOptions | undefined): this
    subMenuExpandingMode(value: SubMenuExpandingMode | undefined): this
}
export class ArkMenuStyle extends ArkCommonMethodStyle implements MenuAttribute {
    fontSize_value?: Length | undefined
    font_value?: Font | undefined
    fontColor_value?: ResourceColor | undefined
    radius_value?: Dimension | BorderRadiuses | undefined
    menuItemDivider_value?: DividerStyleOptions | undefined
    menuItemGroupDivider_value?: DividerStyleOptions | undefined
    subMenuExpandingMode_value?: SubMenuExpandingMode | undefined
    public fontSize(value: Length | undefined): this {
        return this
    }
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
    public fontSize(value: Length | undefined): this {
        if (this.checkPriority("fontSize")) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.fontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public font(value: Font | undefined): this {
        if (this.checkPriority("font")) {
            const value_casted = value as (Font | undefined)
            this.getPeer()?.fontAttribute(value_casted)
            return this
        }
        return this
    }
    public fontColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("fontColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.fontColorAttribute(value_casted)
            return this
        }
        return this
    }
    public radius(value: Dimension | BorderRadiuses | undefined): this {
        if (this.checkPriority("radius")) {
            const value_casted = value as (Dimension | BorderRadiuses | undefined)
            this.getPeer()?.radiusAttribute(value_casted)
            return this
        }
        return this
    }
    public menuItemDivider(value: DividerStyleOptions | undefined): this {
        if (this.checkPriority("menuItemDivider")) {
            const value_casted = value as (DividerStyleOptions | undefined)
            this.getPeer()?.menuItemDividerAttribute(value_casted)
            return this
        }
        return this
    }
    public menuItemGroupDivider(value: DividerStyleOptions | undefined): this {
        if (this.checkPriority("menuItemGroupDivider")) {
            const value_casted = value as (DividerStyleOptions | undefined)
            this.getPeer()?.menuItemGroupDividerAttribute(value_casted)
            return this
        }
        return this
    }
    public subMenuExpandingMode(value: SubMenuExpandingMode | undefined): this {
        if (this.checkPriority("subMenuExpandingMode")) {
            const value_casted = value as (SubMenuExpandingMode | undefined)
            this.getPeer()?.subMenuExpandingModeAttribute(value_casted)
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
export function Menu(
    /** @memo */
    style: ((attributes: MenuAttribute) => void) | undefined,
    
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkMenuComponent()
    })
    NodeAttach<ArkMenuPeer>((): ArkMenuPeer => ArkMenuPeer.create(receiver), (_: ArkMenuPeer) => {
        receiver.setMenuOptions()
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
