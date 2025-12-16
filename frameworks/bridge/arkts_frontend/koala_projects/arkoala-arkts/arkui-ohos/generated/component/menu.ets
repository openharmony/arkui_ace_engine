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

import { ArkThemeScopeManager } from "#arktheme"
import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer } from "@koalaui/interop"
import { Font_serializer, BorderRadiuses_serializer, DividerStyleOptions_serializer, Font, ResourceColor, Dimension, BorderRadiuses, DividerStyleOptions } from "./units"
import { Resource_serializer } from "./../framework/resource"
import { SymbolGlyphModifier_serializer } from "./../SymbolGlyphModifier"
import { int32, int64, float32 } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { Color } from "./enums"
import { Resource } from "global.resource"
import { extractors, AttributeModifier, hookMenuAttributeModifier, AttributeUpdater } from "#handwritten"
import { SymbolGlyphModifier } from "arkui.SymbolGlyphModifier"
import { ModifierStateManager } from '../CommonModifier';
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { MenuModifier } from "./../MenuModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkMenuPeer extends ArkCommonMethodPeer {
    attributeSet?: MenuModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
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
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
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
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as Color
                thisSerializer.writeInt32(valueTmpValueForIdx0.getOrdinal())
            } else if (valueTmpValue instanceof int32) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as int32
                thisSerializer.writeInt32(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((3).toByte())
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
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as Dimension
                if (valueTmpValueForIdx0 instanceof string) {
                    thisSerializer.writeInt8((0).toByte())
                    const valueTmpValueForIdx0ForIdx0  = valueTmpValueForIdx0 as string
                    thisSerializer.writeString(valueTmpValueForIdx0ForIdx0)
                } else if (valueTmpValueForIdx0 instanceof number) {
                    thisSerializer.writeInt8((1).toByte())
                    const valueTmpValueForIdx0ForIdx1  = valueTmpValueForIdx0 as number
                    thisSerializer.writeNumber(valueTmpValueForIdx0ForIdx1)
                } else if (valueTmpValueForIdx0 instanceof Resource) {
                    thisSerializer.writeInt8((2).toByte())
                    const valueTmpValueForIdx0ForIdx2  = valueTmpValueForIdx0 as Resource
                    Resource_serializer.write(thisSerializer, valueTmpValueForIdx0ForIdx2)
                }
            } else if (valueTmpValue instanceof BorderRadiuses) {
                thisSerializer.writeInt8((1).toByte())
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
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._MenuAttribute_setSubMenuExpandingMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSubMenuExpandSymbolAttribute(value: SymbolGlyphModifier | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            SymbolGlyphModifier_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._MenuAttribute_setSubMenuExpandSymbol(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export enum SubMenuExpandingMode {
    SIDE_EXPAND = 0,
    EMBEDDED_EXPAND = 1,
    STACK_EXPAND = 2
}
export interface MenuAttribute extends CommonMethod {
    setMenuOptions(): this {
        throw new Error("Unimplemented method setMenuOptions")
    }
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
    subMenuExpandSymbol(value: SymbolGlyphModifier | undefined): this {
        throw new Error("Unimplemented method subMenuExpandSymbol")
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
    subMenuExpandSymbol_value?: SymbolGlyphModifier | undefined
    attributeModifier_value?: AttributeModifier<MenuAttribute> | AttributeModifier<CommonMethod> | undefined
    setMenuOptions(): this {
        return this
    }
    font(value: Font | undefined): this {
        return this
    }
    fontColor(value: ResourceColor | undefined): this {
        return this
    }
    radius(value: Dimension | BorderRadiuses | undefined): this {
        return this
    }
    menuItemDivider(value: DividerStyleOptions | undefined): this {
        return this
    }
    menuItemGroupDivider(value: DividerStyleOptions | undefined): this {
        return this
    }
    subMenuExpandingMode(value: SubMenuExpandingMode | undefined): this {
        return this
    }
    subMenuExpandSymbol(value: SymbolGlyphModifier | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<MenuAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkMenuComponent extends ArkCommonMethodComponent implements MenuAttribute {
    getPeer(): ArkMenuPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkMenuPeer)
    }
    public setMenuOptions(): this {
        if (this.checkPriority("setMenuOptions")) {
            this.getPeer()?.setMenuOptionsAttribute()
            this.applyOptionsFinish('MenuAttribute');
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
    public subMenuExpandSymbol(value: SymbolGlyphModifier | undefined): this {
        if (this.checkPriority("subMenuExpandSymbol")) {
            const value_casted = value as (SymbolGlyphModifier | undefined)
            this.getPeer()?.setSubMenuExpandSymbolAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<MenuAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
          hookMenuAttributeModifier(this, value);
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

@memo
export function MenuImpl(
    @memo
    style: ((attributes: MenuAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkMenuComponent>((): ArkMenuComponent => {
        return new ArkMenuComponent()
    })
    NodeAttach<ArkMenuPeer>((): ArkMenuPeer => ArkMenuPeer.create(receiver), (peer: ArkMenuPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
    })
}

