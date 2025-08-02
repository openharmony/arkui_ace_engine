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
import { ResourceColor, Length, ResourceStr } from "./units"
import { FontWeight, FontStyle, Color } from "./enums"
import { Resource } from "global/resource"
import { ContentModifier, CommonConfiguration } from "./arkui-wrapper-builder"
import { LabelStyle } from "./arkui-external"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkButtonPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkButtonPeer {
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
    typeAttribute(value: ButtonType | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as ButtonType)
            thisSerializer.writeInt32(TypeChecker.ButtonType_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._ButtonAttribute_type(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    stateEffectAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._ButtonAttribute_stateEffect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    buttonStyleAttribute(value: ButtonStyleMode | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as ButtonStyleMode)
            thisSerializer.writeInt32(TypeChecker.ButtonStyleMode_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._ButtonAttribute_buttonStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    controlSizeAttribute(value: ControlSize | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as ControlSize)
            thisSerializer.writeInt32(TypeChecker.ControlSize_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._ButtonAttribute_controlSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    roleAttribute(value: ButtonRole | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as ButtonRole)
            thisSerializer.writeInt32(TypeChecker.ButtonRole_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._ButtonAttribute_role(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._ButtonAttribute_fontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
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
        ArkUIGeneratedNativeModule._ButtonAttribute_fontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontWeightAttribute(value: number | FontWeight | string | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (TypeChecker.isFontWeight(value_value)) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as FontWeight
                thisSerializer.writeInt32(TypeChecker.FontWeight_ToNumeric(value_value_1))
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._ButtonAttribute_fontWeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontStyleAttribute(value: FontStyle | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as FontStyle)
            thisSerializer.writeInt32(TypeChecker.FontStyle_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._ButtonAttribute_fontStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontFamilyAttribute(value: string | Resource | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as Resource
                thisSerializer.writeResource(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._ButtonAttribute_fontFamily(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    contentModifierAttribute(value: ContentModifier | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteObject(value_value)
        }
        ArkUIGeneratedNativeModule._ButtonAttribute_contentModifier(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    labelStyleAttribute(value: LabelStyle | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeLabelStyle(value_value)
        }
        ArkUIGeneratedNativeModule._ButtonAttribute_labelStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    minFontScaleAttribute(value: number | Resource | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as Resource
                thisSerializer.writeResource(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._ButtonAttribute_minFontScale(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    maxFontScaleAttribute(value: number | Resource | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as Resource
                thisSerializer.writeResource(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._ButtonAttribute_maxFontScale(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
    type(value: ButtonType | undefined): this
    stateEffect(value: boolean | undefined): this
    buttonStyle(value: ButtonStyleMode | undefined): this
    controlSize(value: ControlSize | undefined): this
    role(value: ButtonRole | undefined): this
    fontColor(value: ResourceColor | undefined): this
    fontSize(value: Length | undefined): this
    fontWeight(value: number | FontWeight | string | undefined): this
    fontStyle(value: FontStyle | undefined): this
    fontFamily(value: string | Resource | undefined): this
    contentModifier(value: ContentModifier | undefined): this
    labelStyle(value: LabelStyle | undefined): this
    minFontScale(value: number | Resource | undefined): this
    maxFontScale(value: number | Resource | undefined): this
}
export class ArkButtonStyle extends ArkCommonMethodStyle implements ButtonAttribute {
    type_value?: ButtonType | undefined
    stateEffect_value?: boolean | undefined
    buttonStyle_value?: ButtonStyleMode | undefined
    controlSize_value?: ControlSize | undefined
    role_value?: ButtonRole | undefined
    fontColor_value?: ResourceColor | undefined
    fontSize_value?: Length | undefined
    fontWeight_value?: number | FontWeight | string | undefined
    fontStyle_value?: FontStyle | undefined
    fontFamily_value?: string | Resource | undefined
    contentModifier_value?: ContentModifier | undefined
    labelStyle_value?: LabelStyle | undefined
    minFontScale_value?: number | Resource | undefined
    maxFontScale_value?: number | Resource | undefined
    public type(value: ButtonType | undefined): this {
        return this
    }
    public stateEffect(value: boolean | undefined): this {
        return this
    }
    public buttonStyle(value: ButtonStyleMode | undefined): this {
        return this
    }
    public controlSize(value: ControlSize | undefined): this {
        return this
    }
    public role(value: ButtonRole | undefined): this {
        return this
    }
    public fontColor(value: ResourceColor | undefined): this {
        return this
    }
    public fontSize(value: Length | undefined): this {
        return this
    }
    public fontWeight(value: number | FontWeight | string | undefined): this {
        return this
    }
    public fontStyle(value: FontStyle | undefined): this {
        return this
    }
    public fontFamily(value: string | Resource | undefined): this {
        return this
    }
    public contentModifier(value: ContentModifier | undefined): this {
        return this
    }
    public labelStyle(value: LabelStyle | undefined): this {
        return this
    }
    public minFontScale(value: number | Resource | undefined): this {
        return this
    }
    public maxFontScale(value: number | Resource | undefined): this {
        return this
    }
}
export class ArkButtonComponent extends ArkCommonMethodComponent implements ButtonAttribute {
    getPeer(): ArkButtonPeer {
        return (this.peer as ArkButtonPeer)
    }
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
    public type(value: ButtonType | undefined): this {
        if (this.checkPriority("type")) {
            const value_casted = value as (ButtonType | undefined)
            this.getPeer()?.typeAttribute(value_casted)
            return this
        }
        return this
    }
    public stateEffect(value: boolean | undefined): this {
        if (this.checkPriority("stateEffect")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.stateEffectAttribute(value_casted)
            return this
        }
        return this
    }
    public buttonStyle(value: ButtonStyleMode | undefined): this {
        if (this.checkPriority("buttonStyle")) {
            const value_casted = value as (ButtonStyleMode | undefined)
            this.getPeer()?.buttonStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public controlSize(value: ControlSize | undefined): this {
        if (this.checkPriority("controlSize")) {
            const value_casted = value as (ControlSize | undefined)
            this.getPeer()?.controlSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public role(value: ButtonRole | undefined): this {
        if (this.checkPriority("role")) {
            const value_casted = value as (ButtonRole | undefined)
            this.getPeer()?.roleAttribute(value_casted)
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
    public fontSize(value: Length | undefined): this {
        if (this.checkPriority("fontSize")) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.fontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public fontWeight(value: number | FontWeight | string | undefined): this {
        if (this.checkPriority("fontWeight")) {
            const value_casted = value as (number | FontWeight | string | undefined)
            this.getPeer()?.fontWeightAttribute(value_casted)
            return this
        }
        return this
    }
    public fontStyle(value: FontStyle | undefined): this {
        if (this.checkPriority("fontStyle")) {
            const value_casted = value as (FontStyle | undefined)
            this.getPeer()?.fontStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public fontFamily(value: string | Resource | undefined): this {
        if (this.checkPriority("fontFamily")) {
            const value_casted = value as (string | Resource | undefined)
            this.getPeer()?.fontFamilyAttribute(value_casted)
            return this
        }
        return this
    }
    public contentModifier(value: ContentModifier | undefined): this {
        if (this.checkPriority("contentModifier")) {
            const value_casted = value as (ContentModifier | undefined)
            this.getPeer()?.contentModifierAttribute(value_casted)
            return this
        }
        return this
    }
    public labelStyle(value: LabelStyle | undefined): this {
        if (this.checkPriority("labelStyle")) {
            const value_casted = value as (LabelStyle | undefined)
            this.getPeer()?.labelStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public minFontScale(value: number | Resource | undefined): this {
        if (this.checkPriority("minFontScale")) {
            const value_casted = value as (number | Resource | undefined)
            this.getPeer()?.minFontScaleAttribute(value_casted)
            return this
        }
        return this
    }
    public maxFontScale(value: number | Resource | undefined): this {
        if (this.checkPriority("maxFontScale")) {
            const value_casted = value as (number | Resource | undefined)
            this.getPeer()?.maxFontScaleAttribute(value_casted)
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
export function Button(
    /** @memo */
    style: ((attributes: ButtonAttribute) => void) | undefined,
    label?: ButtonOptions | ResourceStr, options?: ButtonOptions,
    /** @memo */
    content_?: (() => void) | undefined,
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
