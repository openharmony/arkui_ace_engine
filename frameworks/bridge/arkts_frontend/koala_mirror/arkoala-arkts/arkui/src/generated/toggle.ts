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
import { Callback_Boolean_Void } from "./navigation"
import { ContentModifier, CommonConfiguration } from "./arkui-wrapper-builder"
import { ResourceColor } from "./units"
import { Color } from "./enums"
import { Resource } from "./resource"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { UICommonBase, AttributeModifier } from "./../handwritten"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkTogglePeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkTogglePeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Toggle_construct(peerId, flags)
        const _peer  = new ArkTogglePeer(_peerPtr, peerId, "Toggle", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setToggleOptionsAttribute(options: ToggleOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeToggleOptions(options)
        ArkUIGeneratedNativeModule._ToggleInterface_setToggleOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onChangeAttribute(value: ((isVisible: boolean) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ToggleAttribute_onChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    contentModifierAttribute(value: ContentModifier): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteObject(value)
        ArkUIGeneratedNativeModule._ToggleAttribute_contentModifier(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    selectedColorAttribute(value: ResourceColor): void {
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
        ArkUIGeneratedNativeModule._ToggleAttribute_selectedColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    switchPointColorAttribute(value: ResourceColor): void {
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
        ArkUIGeneratedNativeModule._ToggleAttribute_switchPointColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    switchStyleAttribute(value: SwitchStyle): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeSwitchStyle(value)
        ArkUIGeneratedNativeModule._ToggleAttribute_switchStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    _onChangeEvent_isOnAttribute(callback: ((isVisible: boolean) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(callback)
        ArkUIGeneratedNativeModule._ToggleAttribute__onChangeEvent_isOn(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export enum ToggleType {
    CHECKBOX = 0,
    Checkbox = 0,
    SWITCH = 1,
    Switch = 1,
    BUTTON = 2,
    Button = 2
}
export interface SwitchStyle {
    pointRadius?: number | Resource;
    unselectedColor?: ResourceColor;
    pointColor?: ResourceColor;
    trackBorderRadius?: number | Resource;
}
export interface ToggleConfiguration extends CommonConfiguration {
    isOn: boolean;
    enabled: boolean;
    triggerChange: ((isVisible: boolean) => void);
}
export interface ToggleOptions {
    type: ToggleType;
    isOn?: boolean;
}

export interface ToggleAttribute extends CommonMethod {
    onChange(value: ((isVisible: boolean) => void)): this
    contentModifier(value: ContentModifier): this
    selectedColor(value: ResourceColor): this
    switchPointColor(value: ResourceColor): this
    switchStyle(value: SwitchStyle): this
    _onChangeEvent_isOn(callback: ((isVisible: boolean) => void)): void
    attributeModifier(value: AttributeModifier<ToggleAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export interface UIToggleAttribute extends UICommonMethod {
    /** @memo */
    onChange(value: ((isVisible: boolean) => void)): this
    /** @memo */
    contentModifier(value: ContentModifier): this
    /** @memo */
    selectedColor(value: ResourceColor): this
    /** @memo */
    switchPointColor(value: ResourceColor): this
    /** @memo */
    switchStyle(value: SwitchStyle): this
    /** @memo */
    _onChangeEvent_isOn(callback: ((isVisible: boolean) => void)): void
    /** @memo */
    attributeModifier(value: AttributeModifier<ToggleAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkToggleStyle extends ArkCommonMethodStyle implements ToggleAttribute {
    onChange_value?: ((isVisible: boolean) => void)
    contentModifier_value?: ContentModifier
    selectedColor_value?: ResourceColor
    switchPointColor_value?: ResourceColor
    switchStyle_value?: SwitchStyle
    public onChange(value: ((isVisible: boolean) => void)): this {
        return this
    }
    public contentModifier(value: ContentModifier): this {
        return this
    }
    public selectedColor(value: ResourceColor): this {
        return this
    }
    public switchPointColor(value: ResourceColor): this {
        return this
    }
    public switchStyle(value: SwitchStyle): this {
        return this
    }
    public _onChangeEvent_isOn(callback: ((isVisible: boolean) => void)): void {
        throw new Error("Unimplmented")
    }
    public attributeModifier(value: AttributeModifier<ToggleAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
/** @memo:stable */
export class ArkToggleComponent extends ArkCommonMethodComponent implements UIToggleAttribute {
    getPeer(): ArkTogglePeer {
        return (this.peer as ArkTogglePeer)
    }
    /** @memo */
    public setToggleOptions(options: ToggleOptions): this {
        if (this.checkPriority("setToggleOptions")) {
            const options_casted = options as (ToggleOptions)
            this.getPeer()?.setToggleOptionsAttribute(options_casted)
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
    public contentModifier(value: ContentModifier): this {
        if (this.checkPriority("contentModifier")) {
            const value_casted = value as (ContentModifier)
            this.getPeer()?.contentModifierAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public selectedColor(value: ResourceColor): this {
        if (this.checkPriority("selectedColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.selectedColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public switchPointColor(value: ResourceColor): this {
        if (this.checkPriority("switchPointColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.switchPointColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public switchStyle(value: SwitchStyle): this {
        if (this.checkPriority("switchStyle")) {
            const value_casted = value as (SwitchStyle)
            this.getPeer()?.switchStyleAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public _onChangeEvent_isOn(callback: ((isVisible: boolean) => void)): void {
        if (this.checkPriority("_onChangeEvent_isOn")) {
            const callback_casted = callback as (((isVisible: boolean) => void))
            this.getPeer()?._onChangeEvent_isOnAttribute(callback_casted)
            return
        }
        return
    }
    /** @memo */
    public attributeModifier(value: AttributeModifier<ToggleAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function ArkToggle(
    /** @memo */
    style: ((attributes: UIToggleAttribute) => void) | undefined,
    /** @memo */
    content_: (() => void) | undefined,
    options: ToggleOptions,
): void {
    const receiver = remember(() => {
        return new ArkToggleComponent()
    })
    NodeAttach<ArkTogglePeer>((): ArkTogglePeer => ArkTogglePeer.create(receiver), (_: ArkTogglePeer) => {
        receiver.setToggleOptions(options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
