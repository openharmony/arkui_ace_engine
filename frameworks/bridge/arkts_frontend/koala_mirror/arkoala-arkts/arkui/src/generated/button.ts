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
import { ResourceColor, Length, ResourceStr } from "./units"
import { FontWeight, Color } from "./enums"
import { FontStyle } from "./arkui-graphics-text"
import { Resource } from "./resource"
import { ContentModifier, CommonConfiguration } from "./arkui-wrapper-builder"
import { LabelStyle } from "./arkui-external"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { UICommonBase, AttributeModifier } from "./../handwritten"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkButtonPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkButtonPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Button_construct(peerId, flags)
        const _peer  = new ArkButtonPeer(_peerPtr, peerId, "Button", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setButtonOptions0Attribute(): void {
        ArkUIGeneratedNativeModule._ButtonInterface_setButtonOptions0(this.peer.ptr)
    }
    setButtonOptions1Attribute(options: ButtonOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeButtonOptions(options)
        ArkUIGeneratedNativeModule._ButtonInterface_setButtonOptions1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setButtonOptions2Attribute(label: ResourceStr, options?: ButtonOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let label_type : int32 = RuntimeType.UNDEFINED
        label_type = runtimeType(label)
        if (RuntimeType.STRING == label_type) {
            thisSerializer.writeInt8(0 as int32)
            const label_0  = label as string
            thisSerializer.writeString(label_0)
        }
        else if (RuntimeType.OBJECT == label_type) {
            thisSerializer.writeInt8(1 as int32)
            const label_1  = label as Resource
            thisSerializer.writeResource(label_1)
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeButtonOptions(options_value)
        }
        ArkUIGeneratedNativeModule._ButtonInterface_setButtonOptions2(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    typeAttribute(value: ButtonType): void {
        ArkUIGeneratedNativeModule._ButtonAttribute_type(this.peer.ptr, TypeChecker.ButtonType_ToNumeric(value))
    }
    stateEffectAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._ButtonAttribute_stateEffect(this.peer.ptr, value ? 1 : 0)
    }
    buttonStyleAttribute(value: ButtonStyleMode): void {
        ArkUIGeneratedNativeModule._ButtonAttribute_buttonStyle(this.peer.ptr, TypeChecker.ButtonStyleMode_ToNumeric(value))
    }
    controlSizeAttribute(value: ControlSize): void {
        ArkUIGeneratedNativeModule._ButtonAttribute_controlSize(this.peer.ptr, TypeChecker.ControlSize_ToNumeric(value))
    }
    roleAttribute(value: ButtonRole): void {
        ArkUIGeneratedNativeModule._ButtonAttribute_role(this.peer.ptr, TypeChecker.ButtonRole_ToNumeric(value))
    }
    fontColorAttribute(value: ResourceColor): void {
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
        ArkUIGeneratedNativeModule._ButtonAttribute_fontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontSizeAttribute(value: Length): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as Resource
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._ButtonAttribute_fontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontWeightAttribute(value: number | FontWeight | string): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as number
            thisSerializer.writeNumber(value_0)
        }
        else if (TypeChecker.isFontWeight(value)) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as FontWeight
            thisSerializer.writeInt32(TypeChecker.FontWeight_ToNumeric(value_1))
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as string
            thisSerializer.writeString(value_2)
        }
        ArkUIGeneratedNativeModule._ButtonAttribute_fontWeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontStyleAttribute(value: FontStyle): void {
        ArkUIGeneratedNativeModule._ButtonAttribute_fontStyle(this.peer.ptr, TypeChecker.FontStyle_ToNumeric(value))
    }
    fontFamilyAttribute(value: string | Resource): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as Resource
            thisSerializer.writeResource(value_1)
        }
        ArkUIGeneratedNativeModule._ButtonAttribute_fontFamily(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    contentModifierAttribute(value: ContentModifier): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteObject(value)
        ArkUIGeneratedNativeModule._ButtonAttribute_contentModifier(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    labelStyleAttribute(value: LabelStyle): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeLabelStyle(value)
        ArkUIGeneratedNativeModule._ButtonAttribute_labelStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export enum ButtonType {
    CAPSULE = 0,
    Capsule = 0,
    CIRCLE = 1,
    Circle = 1,
    NORMAL = 2,
    Normal = 2,
    ROUNDED_RECTANGLE = 3
}
export enum ButtonStyleMode {
    NORMAL = 0,
    EMPHASIZED = 1,
    TEXTUAL = 2
}
export enum ButtonRole {
    NORMAL = 0,
    ERROR = 1
}
export type ButtonTriggerClickCallback = (xPos: number, yPos: number) => void;
export interface ButtonConfiguration extends CommonConfiguration {
    label: string;
    pressed: boolean;
    triggerClick: ButtonTriggerClickCallback;
}
export enum ControlSize {
    SMALL = "small",
    NORMAL = "normal"
}
export interface ButtonOptions {
    type?: ButtonType;
    stateEffect?: boolean;
    buttonStyle?: ButtonStyleMode;
    controlSize?: ControlSize;
    role?: ButtonRole;
}

export interface ButtonAttribute extends CommonMethod {
    type(value: ButtonType): this
    stateEffect(value: boolean): this
    buttonStyle(value: ButtonStyleMode): this
    controlSize(value: ControlSize): this
    role(value: ButtonRole): this
    fontColor(value: ResourceColor): this
    fontSize(value: Length): this
    fontWeight(value: number | FontWeight | string): this
    fontStyle(value: FontStyle): this
    fontFamily(value: string | Resource): this
    contentModifier(value: ContentModifier): this
    labelStyle(value: LabelStyle): this
    attributeModifier(value: AttributeModifier<ButtonAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export interface UIButtonAttribute extends UICommonMethod {
    /** @memo */
    type(value: ButtonType): this
    /** @memo */
    stateEffect(value: boolean): this
    /** @memo */
    buttonStyle(value: ButtonStyleMode): this
    /** @memo */
    controlSize(value: ControlSize): this
    /** @memo */
    role(value: ButtonRole): this
    /** @memo */
    fontColor(value: ResourceColor): this
    /** @memo */
    fontSize(value: Length): this
    /** @memo */
    fontWeight(value: number | FontWeight | string): this
    /** @memo */
    fontStyle(value: FontStyle): this
    /** @memo */
    fontFamily(value: string | Resource): this
    /** @memo */
    contentModifier(value: ContentModifier): this
    /** @memo */
    labelStyle(value: LabelStyle): this
    /** @memo */
    attributeModifier(value: AttributeModifier<ButtonAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkButtonStyle extends ArkCommonMethodStyle implements ButtonAttribute {
    type_value?: ButtonType
    stateEffect_value?: boolean
    buttonStyle_value?: ButtonStyleMode
    controlSize_value?: ControlSize
    role_value?: ButtonRole
    fontColor_value?: ResourceColor
    fontSize_value?: Length
    fontWeight_value?: number | FontWeight | string
    fontStyle_value?: FontStyle
    fontFamily_value?: string | Resource
    contentModifier_value?: ContentModifier
    labelStyle_value?: LabelStyle
    public type(value: ButtonType): this {
        return this
    }
    public stateEffect(value: boolean): this {
        return this
    }
    public buttonStyle(value: ButtonStyleMode): this {
        return this
    }
    public controlSize(value: ControlSize): this {
        return this
    }
    public role(value: ButtonRole): this {
        return this
    }
    public fontColor(value: ResourceColor): this {
        return this
    }
    public fontSize(value: Length): this {
        return this
    }
    public fontWeight(value: number | FontWeight | string): this {
        return this
    }
    public fontStyle(value: FontStyle): this {
        return this
    }
    public fontFamily(value: string | Resource): this {
        return this
    }
    public contentModifier(value: ContentModifier): this {
        return this
    }
    public labelStyle(value: LabelStyle): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<ButtonAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
/** @memo:stable */
export class ArkButtonComponent extends ArkCommonMethodComponent implements UIButtonAttribute {
    getPeer(): ArkButtonPeer {
        return (this.peer as ArkButtonPeer)
    }
    /** @memo */
    public setButtonOptions(label?: ButtonOptions | ResourceStr, options?: ButtonOptions): this {
        if (this.checkPriority("setButtonOptions")) {
            const label_type = runtimeType(label)
            const options_type = runtimeType(options)
            if (RuntimeType.UNDEFINED == label_type) {
                this.getPeer()?.setButtonOptions0Attribute()
                return this
            }
            if (TypeChecker.isButtonOptions(label, false, false, false, false, false)) {
                const options_casted = label as (ButtonOptions)
                this.getPeer()?.setButtonOptions1Attribute(options_casted)
                return this
            }
            if ((RuntimeType.STRING == label_type) || (RuntimeType.OBJECT == label_type)) {
                const label_casted = label as (ResourceStr)
                const options_casted = options as (ButtonOptions | undefined)
                this.getPeer()?.setButtonOptions2Attribute(label_casted, options_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    /** @memo */
    public type(value: ButtonType): this {
        if (this.checkPriority("type")) {
            const value_casted = value as (ButtonType)
            this.getPeer()?.typeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public stateEffect(value: boolean): this {
        if (this.checkPriority("stateEffect")) {
            const value_casted = value as (boolean)
            this.getPeer()?.stateEffectAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public buttonStyle(value: ButtonStyleMode): this {
        if (this.checkPriority("buttonStyle")) {
            const value_casted = value as (ButtonStyleMode)
            this.getPeer()?.buttonStyleAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public controlSize(value: ControlSize): this {
        if (this.checkPriority("controlSize")) {
            const value_casted = value as (ControlSize)
            this.getPeer()?.controlSizeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public role(value: ButtonRole): this {
        if (this.checkPriority("role")) {
            const value_casted = value as (ButtonRole)
            this.getPeer()?.roleAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public fontColor(value: ResourceColor): this {
        if (this.checkPriority("fontColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.fontColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public fontSize(value: Length): this {
        if (this.checkPriority("fontSize")) {
            const value_casted = value as (Length)
            this.getPeer()?.fontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public fontWeight(value: number | FontWeight | string): this {
        if (this.checkPriority("fontWeight")) {
            const value_casted = value as (number | FontWeight | string)
            this.getPeer()?.fontWeightAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public fontStyle(value: FontStyle): this {
        if (this.checkPriority("fontStyle")) {
            const value_casted = value as (FontStyle)
            this.getPeer()?.fontStyleAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public fontFamily(value: string | Resource): this {
        if (this.checkPriority("fontFamily")) {
            const value_casted = value as (string | Resource)
            this.getPeer()?.fontFamilyAttribute(value_casted)
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
    public labelStyle(value: LabelStyle): this {
        if (this.checkPriority("labelStyle")) {
            const value_casted = value as (LabelStyle)
            this.getPeer()?.labelStyleAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public attributeModifier(value: AttributeModifier<ButtonAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function ArkButton(
    /** @memo */
    style: ((attributes: UIButtonAttribute) => void) | undefined,
    /** @memo */
    content_: (() => void) | undefined,
    label?: ButtonOptions | ResourceStr, options?: ButtonOptions,
): void {
    const receiver = remember(() => {
        return new ArkButtonComponent()
    })
    NodeAttach<ArkButtonPeer>((): ArkButtonPeer => ArkButtonPeer.create(receiver), (_: ArkButtonPeer) => {
        receiver.setButtonOptions(label,options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
