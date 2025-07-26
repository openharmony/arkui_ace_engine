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
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, CommonConfiguration, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonMethodSet } from "./common"
import { ResourceColor, Length, ResourceStr, Font, Font_serializer } from "./units"
import { Color, FontWeight, FontStyle, TextOverflow, TextHeightAdaptivePolicy } from "./enums"
import { ContentModifier, AttributeModifier, hookButtonContentModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
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
        const thisSerializer : SerializerBase = SerializerBase.hold()
        ButtonOptions_serializer.write(thisSerializer, options)
        ArkUIGeneratedNativeModule._ButtonInterface_setButtonOptions1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setButtonOptions2Attribute(label: ResourceStr, options?: ButtonOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let label_type : int32 = RuntimeType.UNDEFINED
        label_type = runtimeType(label)
        if (RuntimeType.STRING == label_type) {
            thisSerializer.writeInt8((0).toChar())
            const label_0  = label as string
            thisSerializer.writeString(label_0)
        }
        else if (RuntimeType.OBJECT == label_type) {
            thisSerializer.writeInt8((1).toChar())
            const label_1  = label as Resource
            Resource_serializer.write(thisSerializer, label_1)
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8((options_type).toChar())
        if ((options_type) != (RuntimeType.UNDEFINED)) {
            const options_value  = options!
            ButtonOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._ButtonInterface_setButtonOptions2(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTypeAttribute(value: ButtonType | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as ButtonType)
            thisSerializer.writeInt32(TypeChecker.ButtonType_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._ButtonAttribute_setType(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setStateEffectAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._ButtonAttribute_setStateEffect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setButtonStyleAttribute(value: ButtonStyleMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as ButtonStyleMode)
            thisSerializer.writeInt32(TypeChecker.ButtonStyleMode_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._ButtonAttribute_setButtonStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setControlSizeAttribute(value: ControlSize | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as ControlSize)
            thisSerializer.writeInt32(TypeChecker.ControlSize_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._ButtonAttribute_setControlSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setRoleAttribute(value: ButtonRole | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as ButtonRole)
            thisSerializer.writeInt32(TypeChecker.ButtonRole_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._ButtonAttribute_setRole(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._ButtonAttribute_setFontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontSizeAttribute(value: Length | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._ButtonAttribute_setFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontWeightAttribute(value: number | FontWeight | string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (TypeChecker.isFontWeight(value_value)) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as FontWeight
                thisSerializer.writeInt32(TypeChecker.FontWeight_ToNumeric(value_value_1))
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._ButtonAttribute_setFontWeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontStyleAttribute(value: FontStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as FontStyle)
            thisSerializer.writeInt32(TypeChecker.FontStyle_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._ButtonAttribute_setFontStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontFamilyAttribute(value: string | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._ButtonAttribute_setFontFamily(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setContentModifierAttribute(value: ContentModifier<ButtonConfiguration> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteObject(value_value)
        }
        ArkUIGeneratedNativeModule._ButtonAttribute_setContentModifier(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setLabelStyleAttribute(value: ButtonLabelStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            ButtonLabelStyle_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._ButtonAttribute_setLabelStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMinFontScaleAttribute(value: number | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._ButtonAttribute_setMinFontScale(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMaxFontScaleAttribute(value: number | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._ButtonAttribute_setMaxFontScale(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
export interface ButtonConfiguration extends CommonConfiguration<ButtonConfiguration> {
    label: string;
    pressed: boolean;
    triggerClick: ButtonTriggerClickCallback;
}
export enum ControlSize {
    SMALL = "'small'",
    NORMAL = "'normal'"
}
export interface ButtonOptions {
    type?: ButtonType;
    stateEffect?: boolean;
    buttonStyle?: ButtonStyleMode;
    controlSize?: ControlSize;
    role?: ButtonRole;
}
export interface ButtonLabelStyle {
    overflow?: TextOverflow;
    maxLines?: number;
    minFontSize?: number | ResourceStr;
    maxFontSize?: number | ResourceStr;
    heightAdaptivePolicy?: TextHeightAdaptivePolicy;
    font?: Font;
}
export interface ButtonAttribute extends CommonMethod {
    type(value: ButtonType | undefined): this {
        throw new Error("Unimplemented method type")
    }
    stateEffect(value: boolean | undefined): this {
        throw new Error("Unimplemented method stateEffect")
    }
    buttonStyle(value: ButtonStyleMode | undefined): this {
        throw new Error("Unimplemented method buttonStyle")
    }
    controlSize(value: ControlSize | undefined): this {
        throw new Error("Unimplemented method controlSize")
    }
    role(value: ButtonRole | undefined): this {
        throw new Error("Unimplemented method role")
    }
    fontColor(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method fontColor")
    }
    fontSize(value: Length | undefined): this {
        throw new Error("Unimplemented method fontSize")
    }
    fontWeight(value: number | FontWeight | string | undefined): this {
        throw new Error("Unimplemented method fontWeight")
    }
    fontStyle(value: FontStyle | undefined): this {
        throw new Error("Unimplemented method fontStyle")
    }
    fontFamily(value: string | Resource | undefined): this {
        throw new Error("Unimplemented method fontFamily")
    }
    contentModifier(value: ContentModifier<ButtonConfiguration> | undefined): this {
        throw new Error("Unimplemented method contentModifier")
    }
    labelStyle(value: ButtonLabelStyle | undefined): this {
        throw new Error("Unimplemented method labelStyle")
    }
    minFontScale(value: number | Resource | undefined): this {
        throw new Error("Unimplemented method minFontScale")
    }
    maxFontScale(value: number | Resource | undefined): this {
        throw new Error("Unimplemented method maxFontScale")
    }
    attributeModifier(value: AttributeModifier<ButtonAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
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
    contentModifier_value?: ContentModifier<ButtonConfiguration> | undefined
    labelStyle_value?: ButtonLabelStyle | undefined
    minFontScale_value?: number | Resource | undefined
    maxFontScale_value?: number | Resource | undefined
    attributeModifier_value?: AttributeModifier<ButtonAttribute> | AttributeModifier<CommonMethod> | undefined
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
    public contentModifier(value: ContentModifier<ButtonConfiguration> | undefined): this {
        return this
    }
    public labelStyle(value: ButtonLabelStyle | undefined): this {
        return this
    }
    public minFontScale(value: number | Resource | undefined): this {
        return this
    }
    public maxFontScale(value: number | Resource | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<ButtonAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: ButtonAttribute): void {
        super.apply(target)
        if (this.type_value !== undefined)
            target.type(this.type_value!)
        if (this.stateEffect_value !== undefined)
            target.stateEffect(this.stateEffect_value!)
        if (this.buttonStyle_value !== undefined)
            target.buttonStyle(this.buttonStyle_value!)
        if (this.controlSize_value !== undefined)
            target.controlSize(this.controlSize_value!)
        if (this.role_value !== undefined)
            target.role(this.role_value!)
        if (this.fontColor_value !== undefined)
            target.fontColor(this.fontColor_value!)
        if (this.fontSize_value !== undefined)
            target.fontSize(this.fontSize_value!)
        if (this.fontWeight_value !== undefined)
            target.fontWeight(this.fontWeight_value!)
        if (this.fontStyle_value !== undefined)
            target.fontStyle(this.fontStyle_value!)
        if (this.fontFamily_value !== undefined)
            target.fontFamily(this.fontFamily_value!)
        if (this.contentModifier_value !== undefined)
            target.contentModifier(this.contentModifier_value!)
        if (this.labelStyle_value !== undefined)
            target.labelStyle(this.labelStyle_value!)
        if (this.minFontScale_value !== undefined)
            target.minFontScale(this.minFontScale_value!)
        if (this.maxFontScale_value !== undefined)
            target.maxFontScale(this.maxFontScale_value!)
    }
}

export class ArkButtonComponent extends ArkCommonMethodComponent implements ButtonAttribute {
    getPeer(): ArkButtonPeer {
        return (this.peer as ArkButtonPeer)
    }
    public setButtonOptions(): this {
        if (this.checkPriority("setButtonOptions")) {
            this.getPeer()?.setButtonOptions0Attribute()
            return this
        }
        return this
    }
    public setButtonOptions(options: ButtonOptions): this {
        if (this.checkPriority("setButtonOptions")) {
            const options_casted = options as (ButtonOptions)
            this.getPeer()?.setButtonOptions1Attribute(options_casted)
            return this
        }
        return this
    }
    public setButtonOptions(label: ResourceStr, options?: ButtonOptions): this {
        if (this.checkPriority("setButtonOptions")) {
            const label_casted = label as (ResourceStr)
            const options_casted = options as (ButtonOptions | undefined)
            this.getPeer()?.setButtonOptions2Attribute(label_casted, options_casted)
            return this
        }
        return this
    }
    public type(value: ButtonType | undefined): this {
        if (this.checkPriority("type")) {
            const value_casted = value as (ButtonType | undefined)
            this.getPeer()?.setTypeAttribute(value_casted)
            return this
        }
        return this
    }
    public stateEffect(value: boolean | undefined): this {
        if (this.checkPriority("stateEffect")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setStateEffectAttribute(value_casted)
            return this
        }
        return this
    }
    public buttonStyle(value: ButtonStyleMode | undefined): this {
        if (this.checkPriority("buttonStyle")) {
            const value_casted = value as (ButtonStyleMode | undefined)
            this.getPeer()?.setButtonStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public controlSize(value: ControlSize | undefined): this {
        if (this.checkPriority("controlSize")) {
            const value_casted = value as (ControlSize | undefined)
            this.getPeer()?.setControlSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public role(value: ButtonRole | undefined): this {
        if (this.checkPriority("role")) {
            const value_casted = value as (ButtonRole | undefined)
            this.getPeer()?.setRoleAttribute(value_casted)
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
    public fontSize(value: Length | undefined): this {
        if (this.checkPriority("fontSize")) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.setFontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public fontWeight(value: number | FontWeight | string | undefined): this {
        if (this.checkPriority("fontWeight")) {
            const value_casted = value as (number | FontWeight | string | undefined)
            this.getPeer()?.setFontWeightAttribute(value_casted)
            return this
        }
        return this
    }
    public fontStyle(value: FontStyle | undefined): this {
        if (this.checkPriority("fontStyle")) {
            const value_casted = value as (FontStyle | undefined)
            this.getPeer()?.setFontStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public fontFamily(value: string | Resource | undefined): this {
        if (this.checkPriority("fontFamily")) {
            const value_casted = value as (string | Resource | undefined)
            this.getPeer()?.setFontFamilyAttribute(value_casted)
            return this
        }
        return this
    }
    public contentModifier(value: ContentModifier<ButtonConfiguration> | undefined): this {
        if (this.checkPriority("contentModifier")) {
            const value_casted = value as (ContentModifier<ButtonConfiguration> | undefined)
            this.getPeer()?.setContentModifierAttribute(value_casted)
            return this
        }
        return this
    }
    public labelStyle(value: ButtonLabelStyle | undefined): this {
        if (this.checkPriority("labelStyle")) {
            const value_casted = value as (ButtonLabelStyle | undefined)
            this.getPeer()?.setLabelStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public minFontScale(value: number | Resource | undefined): this {
        if (this.checkPriority("minFontScale")) {
            const value_casted = value as (number | Resource | undefined)
            this.getPeer()?.setMinFontScaleAttribute(value_casted)
            return this
        }
        return this
    }
    public maxFontScale(value: number | Resource | undefined): this {
        if (this.checkPriority("maxFontScale")) {
            const value_casted = value as (number | Resource | undefined)
            this.getPeer()?.setMaxFontScaleAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<ButtonAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withButtonStyle(receiver: ButtonAttribute, modifier: AttributeModifier<ButtonAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkButtonStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("Button")
// export function Button(
//     
//     @memo
//     content_?: () => void,
// ): ButtonAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function Button(
    @memo
    style: ((attributes: ButtonAttribute) => void) | undefined,
    
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkButtonComponent>((): ArkButtonComponent => {
        return new ArkButtonComponent()
    })
    NodeAttach<ArkButtonPeer>((): ArkButtonPeer => ArkButtonPeer.create(receiver), (_: ArkButtonPeer): void => {
        receiver.setButtonOptions()
        style?.(receiver)
        withButtonStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

// @memo
// @BuilderLambda("Button")
// export function Button(
//     options: ButtonOptions,
//     @memo
//     content_?: () => void,
// ): ButtonAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function Button(
    @memo
    style: ((attributes: ButtonAttribute) => void) | undefined,
    options: ButtonOptions,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkButtonComponent>((): ArkButtonComponent => {
        return new ArkButtonComponent()
    })
    NodeAttach<ArkButtonPeer>((): ArkButtonPeer => ArkButtonPeer.create(receiver), (_: ArkButtonPeer): void => {
        receiver.setButtonOptions(options)
        style?.(receiver)
        withButtonStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

// @memo
// @BuilderLambda("Button")
// export function Button(
//     label: ResourceStr, options?: ButtonOptions,
//     @memo
//     content_?: () => void,
// ): ButtonAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function Button(
    @memo
    style: ((attributes: ButtonAttribute) => void) | undefined,
    label: ResourceStr, options?: ButtonOptions,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkButtonComponent>((): ArkButtonComponent => {
        return new ArkButtonComponent()
    })
    NodeAttach<ArkButtonPeer>((): ArkButtonPeer => ArkButtonPeer.create(receiver), (_: ArkButtonPeer): void => {
        receiver.setButtonOptions(label,options)
        style?.(receiver)
        withButtonStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkButtonSet extends ArkCommonMethodSet implements ButtonAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _type_flag?: boolean
    _type0_value?: ButtonType | undefined
    _stateEffect_flag?: boolean
    _stateEffect0_value?: boolean | undefined
    _buttonStyle_flag?: boolean
    _buttonStyle0_value?: ButtonStyleMode | undefined
    _controlSize_flag?: boolean
    _controlSize0_value?: ControlSize | undefined
    _role_flag?: boolean
    _role0_value?: ButtonRole | undefined
    _fontColor_flag?: boolean
    _fontColor0_value?: ResourceColor | undefined
    _fontSize_flag?: boolean
    _fontSize0_value?: Length | undefined
    _fontWeight_flag?: boolean
    _fontWeight0_value?: number | FontWeight | string | undefined
    _fontStyle_flag?: boolean
    _fontStyle0_value?: FontStyle | undefined
    _fontFamily_flag?: boolean
    _fontFamily0_value?: string | Resource | undefined
    _contentModifier_flag?: boolean
    _contentModifier0_value?: ContentModifier<ButtonConfiguration> | undefined
    _labelStyle_flag?: boolean
    _labelStyle0_value?: ButtonLabelStyle | undefined
    _minFontScale_flag?: boolean
    _minFontScale0_value?: number | Resource | undefined
    _maxFontScale_flag?: boolean
    _maxFontScale0_value?: number | Resource | undefined
    applyModifierPatch(component: ButtonAttribute): void {
        if (this._type_flag)
            component.type((this._type0_value as ButtonType | undefined))
        if (this._stateEffect_flag)
            component.stateEffect((this._stateEffect0_value as boolean | undefined))
        if (this._buttonStyle_flag)
            component.buttonStyle((this._buttonStyle0_value as ButtonStyleMode | undefined))
        if (this._controlSize_flag)
            component.controlSize((this._controlSize0_value as ControlSize | undefined))
        if (this._role_flag)
            component.role((this._role0_value as ButtonRole | undefined))
        if (this._fontColor_flag)
            component.fontColor((this._fontColor0_value as ResourceColor | undefined))
        if (this._fontSize_flag)
            component.fontSize((this._fontSize0_value as Length | undefined))
        if (this._fontWeight_flag)
            component.fontWeight((this._fontWeight0_value as number | FontWeight | string | undefined))
        if (this._fontStyle_flag)
            component.fontStyle((this._fontStyle0_value as FontStyle | undefined))
        if (this._fontFamily_flag)
            component.fontFamily((this._fontFamily0_value as string | Resource | undefined))
        if (this._contentModifier_flag)
            component.contentModifier((this._contentModifier0_value as ContentModifier<ButtonConfiguration> | undefined))
        if (this._labelStyle_flag)
            component.labelStyle((this._labelStyle0_value as ButtonLabelStyle | undefined))
        if (this._minFontScale_flag)
            component.minFontScale((this._minFontScale0_value as number | Resource | undefined))
        if (this._maxFontScale_flag)
            component.maxFontScale((this._maxFontScale0_value as number | Resource | undefined))
    }
    public type(value: ButtonType | undefined): this {
        this._type_flag = true
        this._type0_value = value
        return this
    }
    public stateEffect(value: boolean | undefined): this {
        this._stateEffect_flag = true
        this._stateEffect0_value = value
        return this
    }
    public buttonStyle(value: ButtonStyleMode | undefined): this {
        this._buttonStyle_flag = true
        this._buttonStyle0_value = value
        return this
    }
    public controlSize(value: ControlSize | undefined): this {
        this._controlSize_flag = true
        this._controlSize0_value = value
        return this
    }
    public role(value: ButtonRole | undefined): this {
        this._role_flag = true
        this._role0_value = value
        return this
    }
    public fontColor(value: ResourceColor | undefined): this {
        this._fontColor_flag = true
        this._fontColor0_value = value
        return this
    }
    public fontSize(value: Length | undefined): this {
        this._fontSize_flag = true
        this._fontSize0_value = value
        return this
    }
    public fontWeight(value: number | FontWeight | string | undefined): this {
        this._fontWeight_flag = true
        this._fontWeight0_value = value
        return this
    }
    public fontStyle(value: FontStyle | undefined): this {
        this._fontStyle_flag = true
        this._fontStyle0_value = value
        return this
    }
    public fontFamily(value: string | Resource | undefined): this {
        this._fontFamily_flag = true
        this._fontFamily0_value = value
        return this
    }
    public contentModifier(value: ContentModifier<ButtonConfiguration> | undefined): this {
        this._contentModifier_flag = true
        this._contentModifier0_value = value
        return this
    }
    public labelStyle(value: ButtonLabelStyle | undefined): this {
        this._labelStyle_flag = true
        this._labelStyle0_value = value
        return this
    }
    public minFontScale(value: number | Resource | undefined): this {
        this._minFontScale_flag = true
        this._minFontScale0_value = value
        return this
    }
    public maxFontScale(value: number | Resource | undefined): this {
        this._maxFontScale_flag = true
        this._maxFontScale0_value = value
        return this
    }
    public attributeModifier(value: AttributeModifier<ButtonAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class ButtonConfiguration_serializer {
    public static write(buffer: SerializerBase, value: ButtonConfiguration): void {
        let valueSerializer : SerializerBase = buffer
        const value_enabled  = value.enabled
        valueSerializer.writeBoolean(value_enabled)
        const value_contentModifier  = value.contentModifier
        valueSerializer.holdAndWriteObject(value_contentModifier)
        const value_label  = value.label
        valueSerializer.writeString(value_label)
        const value_pressed  = value.pressed
        valueSerializer.writeBoolean(value_pressed)
        const value_triggerClick  = value.triggerClick
        valueSerializer.holdAndWriteCallback(value_triggerClick)
    }
    public static read(buffer: DeserializerBase): ButtonConfiguration {
        let valueDeserializer : DeserializerBase = buffer
        const enabled_result : boolean = valueDeserializer.readBoolean()
        const contentModifier_result : ContentModifier<ButtonConfiguration> = (valueDeserializer.readObject() as ContentModifier<ButtonConfiguration>)
        const label_result : string = (valueDeserializer.readString() as string)
        const pressed_result : boolean = valueDeserializer.readBoolean()
        const triggerClick_buf_resource : CallbackResource = valueDeserializer.readCallbackResource()
        const triggerClick_buf_call : KPointer = valueDeserializer.readPointer()
        const triggerClick_buf_callSync : KPointer = valueDeserializer.readPointer()
        const triggerClick_result : ButtonTriggerClickCallback = (xPos: number, yPos: number):void => { 
    const triggerClick_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    triggerClick_buf_argsSerializer.writeInt32(triggerClick_buf_resource.resourceId);
    triggerClick_buf_argsSerializer.writePointer(triggerClick_buf_call);
    triggerClick_buf_argsSerializer.writePointer(triggerClick_buf_callSync);
    triggerClick_buf_argsSerializer.writeNumber(xPos);
    triggerClick_buf_argsSerializer.writeNumber(yPos);
    InteropNativeModule._CallCallback(-1964292933, triggerClick_buf_argsSerializer.asBuffer(), triggerClick_buf_argsSerializer.length());
    triggerClick_buf_argsSerializer.release();
    return; }
        let value : ButtonConfiguration = ({enabled: enabled_result, contentModifier: contentModifier_result, label: label_result, pressed: pressed_result, triggerClick: triggerClick_result} as ButtonConfiguration)
        return value
    }
}
export class ButtonOptions_serializer {
    public static write(buffer: SerializerBase, value: ButtonOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_type  = value.type
        let value_type_type : int32 = RuntimeType.UNDEFINED
        value_type_type = runtimeType(value_type)
        valueSerializer.writeInt8((value_type_type).toChar())
        if ((value_type_type) != (RuntimeType.UNDEFINED)) {
            const value_type_value  = (value_type as ButtonType)
            valueSerializer.writeInt32(TypeChecker.ButtonType_ToNumeric(value_type_value))
        }
        const value_stateEffect  = value.stateEffect
        let value_stateEffect_type : int32 = RuntimeType.UNDEFINED
        value_stateEffect_type = runtimeType(value_stateEffect)
        valueSerializer.writeInt8((value_stateEffect_type).toChar())
        if ((value_stateEffect_type) != (RuntimeType.UNDEFINED)) {
            const value_stateEffect_value  = value_stateEffect!
            valueSerializer.writeBoolean(value_stateEffect_value)
        }
        const value_buttonStyle  = value.buttonStyle
        let value_buttonStyle_type : int32 = RuntimeType.UNDEFINED
        value_buttonStyle_type = runtimeType(value_buttonStyle)
        valueSerializer.writeInt8((value_buttonStyle_type).toChar())
        if ((value_buttonStyle_type) != (RuntimeType.UNDEFINED)) {
            const value_buttonStyle_value  = (value_buttonStyle as ButtonStyleMode)
            valueSerializer.writeInt32(TypeChecker.ButtonStyleMode_ToNumeric(value_buttonStyle_value))
        }
        const value_controlSize  = value.controlSize
        let value_controlSize_type : int32 = RuntimeType.UNDEFINED
        value_controlSize_type = runtimeType(value_controlSize)
        valueSerializer.writeInt8((value_controlSize_type).toChar())
        if ((value_controlSize_type) != (RuntimeType.UNDEFINED)) {
            const value_controlSize_value  = (value_controlSize as ControlSize)
            valueSerializer.writeInt32(TypeChecker.ControlSize_ToNumeric(value_controlSize_value))
        }
        const value_role  = value.role
        let value_role_type : int32 = RuntimeType.UNDEFINED
        value_role_type = runtimeType(value_role)
        valueSerializer.writeInt8((value_role_type).toChar())
        if ((value_role_type) != (RuntimeType.UNDEFINED)) {
            const value_role_value  = (value_role as ButtonRole)
            valueSerializer.writeInt32(TypeChecker.ButtonRole_ToNumeric(value_role_value))
        }
    }
    public static read(buffer: DeserializerBase): ButtonOptions {
        let valueDeserializer : DeserializerBase = buffer
        const type_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let type_buf : ButtonType | undefined
        if ((type_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            type_buf = TypeChecker.ButtonType_FromNumeric(valueDeserializer.readInt32())
        }
        const type_result : ButtonType | undefined = type_buf
        const stateEffect_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let stateEffect_buf : boolean | undefined
        if ((stateEffect_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            stateEffect_buf = valueDeserializer.readBoolean()
        }
        const stateEffect_result : boolean | undefined = stateEffect_buf
        const buttonStyle_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let buttonStyle_buf : ButtonStyleMode | undefined
        if ((buttonStyle_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            buttonStyle_buf = TypeChecker.ButtonStyleMode_FromNumeric(valueDeserializer.readInt32())
        }
        const buttonStyle_result : ButtonStyleMode | undefined = buttonStyle_buf
        const controlSize_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let controlSize_buf : ControlSize | undefined
        if ((controlSize_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            controlSize_buf = TypeChecker.ControlSize_FromNumeric(valueDeserializer.readInt32())
        }
        const controlSize_result : ControlSize | undefined = controlSize_buf
        const role_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let role_buf : ButtonRole | undefined
        if ((role_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            role_buf = TypeChecker.ButtonRole_FromNumeric(valueDeserializer.readInt32())
        }
        const role_result : ButtonRole | undefined = role_buf
        let value : ButtonOptions = ({type: type_result, stateEffect: stateEffect_result, buttonStyle: buttonStyle_result, controlSize: controlSize_result, role: role_result} as ButtonOptions)
        return value
    }
}
export class ButtonLabelStyle_serializer {
    public static write(buffer: SerializerBase, value: ButtonLabelStyle): void {
        let valueSerializer : SerializerBase = buffer
        const value_overflow  = value.overflow
        let value_overflow_type : int32 = RuntimeType.UNDEFINED
        value_overflow_type = runtimeType(value_overflow)
        valueSerializer.writeInt8((value_overflow_type).toChar())
        if ((value_overflow_type) != (RuntimeType.UNDEFINED)) {
            const value_overflow_value  = (value_overflow as TextOverflow)
            valueSerializer.writeInt32(TypeChecker.TextOverflow_ToNumeric(value_overflow_value))
        }
        const value_maxLines  = value.maxLines
        let value_maxLines_type : int32 = RuntimeType.UNDEFINED
        value_maxLines_type = runtimeType(value_maxLines)
        valueSerializer.writeInt8((value_maxLines_type).toChar())
        if ((value_maxLines_type) != (RuntimeType.UNDEFINED)) {
            const value_maxLines_value  = value_maxLines!
            valueSerializer.writeNumber(value_maxLines_value)
        }
        const value_minFontSize  = value.minFontSize
        let value_minFontSize_type : int32 = RuntimeType.UNDEFINED
        value_minFontSize_type = runtimeType(value_minFontSize)
        valueSerializer.writeInt8((value_minFontSize_type).toChar())
        if ((value_minFontSize_type) != (RuntimeType.UNDEFINED)) {
            const value_minFontSize_value  = value_minFontSize!
            let value_minFontSize_value_type : int32 = RuntimeType.UNDEFINED
            value_minFontSize_value_type = runtimeType(value_minFontSize_value)
            if (RuntimeType.NUMBER == value_minFontSize_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_minFontSize_value_0  = value_minFontSize_value as number
                valueSerializer.writeNumber(value_minFontSize_value_0)
            }
            else if ((RuntimeType.STRING == value_minFontSize_value_type) || (RuntimeType.OBJECT == value_minFontSize_value_type)) {
                valueSerializer.writeInt8((1).toChar())
                const value_minFontSize_value_1  = value_minFontSize_value as ResourceStr
                let value_minFontSize_value_1_type : int32 = RuntimeType.UNDEFINED
                value_minFontSize_value_1_type = runtimeType(value_minFontSize_value_1)
                if (RuntimeType.STRING == value_minFontSize_value_1_type) {
                    valueSerializer.writeInt8((0).toChar())
                    const value_minFontSize_value_1_0  = value_minFontSize_value_1 as string
                    valueSerializer.writeString(value_minFontSize_value_1_0)
                }
                else if (RuntimeType.OBJECT == value_minFontSize_value_1_type) {
                    valueSerializer.writeInt8((1).toChar())
                    const value_minFontSize_value_1_1  = value_minFontSize_value_1 as Resource
                    Resource_serializer.write(valueSerializer, value_minFontSize_value_1_1)
                }
            }
        }
        const value_maxFontSize  = value.maxFontSize
        let value_maxFontSize_type : int32 = RuntimeType.UNDEFINED
        value_maxFontSize_type = runtimeType(value_maxFontSize)
        valueSerializer.writeInt8((value_maxFontSize_type).toChar())
        if ((value_maxFontSize_type) != (RuntimeType.UNDEFINED)) {
            const value_maxFontSize_value  = value_maxFontSize!
            let value_maxFontSize_value_type : int32 = RuntimeType.UNDEFINED
            value_maxFontSize_value_type = runtimeType(value_maxFontSize_value)
            if (RuntimeType.NUMBER == value_maxFontSize_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_maxFontSize_value_0  = value_maxFontSize_value as number
                valueSerializer.writeNumber(value_maxFontSize_value_0)
            }
            else if ((RuntimeType.STRING == value_maxFontSize_value_type) || (RuntimeType.OBJECT == value_maxFontSize_value_type)) {
                valueSerializer.writeInt8((1).toChar())
                const value_maxFontSize_value_1  = value_maxFontSize_value as ResourceStr
                let value_maxFontSize_value_1_type : int32 = RuntimeType.UNDEFINED
                value_maxFontSize_value_1_type = runtimeType(value_maxFontSize_value_1)
                if (RuntimeType.STRING == value_maxFontSize_value_1_type) {
                    valueSerializer.writeInt8((0).toChar())
                    const value_maxFontSize_value_1_0  = value_maxFontSize_value_1 as string
                    valueSerializer.writeString(value_maxFontSize_value_1_0)
                }
                else if (RuntimeType.OBJECT == value_maxFontSize_value_1_type) {
                    valueSerializer.writeInt8((1).toChar())
                    const value_maxFontSize_value_1_1  = value_maxFontSize_value_1 as Resource
                    Resource_serializer.write(valueSerializer, value_maxFontSize_value_1_1)
                }
            }
        }
        const value_heightAdaptivePolicy  = value.heightAdaptivePolicy
        let value_heightAdaptivePolicy_type : int32 = RuntimeType.UNDEFINED
        value_heightAdaptivePolicy_type = runtimeType(value_heightAdaptivePolicy)
        valueSerializer.writeInt8((value_heightAdaptivePolicy_type).toChar())
        if ((value_heightAdaptivePolicy_type) != (RuntimeType.UNDEFINED)) {
            const value_heightAdaptivePolicy_value  = (value_heightAdaptivePolicy as TextHeightAdaptivePolicy)
            valueSerializer.writeInt32(TypeChecker.TextHeightAdaptivePolicy_ToNumeric(value_heightAdaptivePolicy_value))
        }
        const value_font  = value.font
        let value_font_type : int32 = RuntimeType.UNDEFINED
        value_font_type = runtimeType(value_font)
        valueSerializer.writeInt8((value_font_type).toChar())
        if ((value_font_type) != (RuntimeType.UNDEFINED)) {
            const value_font_value  = value_font!
            Font_serializer.write(valueSerializer, value_font_value)
        }
    }
    public static read(buffer: DeserializerBase): ButtonLabelStyle {
        let valueDeserializer : DeserializerBase = buffer
        const overflow_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let overflow_buf : TextOverflow | undefined
        if ((overflow_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            overflow_buf = TypeChecker.TextOverflow_FromNumeric(valueDeserializer.readInt32())
        }
        const overflow_result : TextOverflow | undefined = overflow_buf
        const maxLines_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let maxLines_buf : number | undefined
        if ((maxLines_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            maxLines_buf = (valueDeserializer.readNumber() as number)
        }
        const maxLines_result : number | undefined = maxLines_buf
        const minFontSize_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let minFontSize_buf : number | ResourceStr | undefined
        if ((minFontSize_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const minFontSize_buf__selector : int32 = valueDeserializer.readInt8()
            let minFontSize_buf_ : number | ResourceStr | undefined
            if (minFontSize_buf__selector == (0).toChar()) {
                minFontSize_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (minFontSize_buf__selector == (1).toChar()) {
                const minFontSize_buf__u_selector : int32 = valueDeserializer.readInt8()
                let minFontSize_buf__u : string | Resource | undefined
                if (minFontSize_buf__u_selector == (0).toChar()) {
                    minFontSize_buf__u = (valueDeserializer.readString() as string)
                }
                else if (minFontSize_buf__u_selector == (1).toChar()) {
                    minFontSize_buf__u = Resource_serializer.read(valueDeserializer)
                }
                else {
                    throw new Error("One of the branches for minFontSize_buf__u has to be chosen through deserialisation.")
                }
                minFontSize_buf_ = (minFontSize_buf__u as string | Resource)
            }
            else {
                throw new Error("One of the branches for minFontSize_buf_ has to be chosen through deserialisation.")
            }
            minFontSize_buf = (minFontSize_buf_ as number | ResourceStr)
        }
        const minFontSize_result : number | ResourceStr | undefined = minFontSize_buf
        const maxFontSize_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let maxFontSize_buf : number | ResourceStr | undefined
        if ((maxFontSize_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const maxFontSize_buf__selector : int32 = valueDeserializer.readInt8()
            let maxFontSize_buf_ : number | ResourceStr | undefined
            if (maxFontSize_buf__selector == (0).toChar()) {
                maxFontSize_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (maxFontSize_buf__selector == (1).toChar()) {
                const maxFontSize_buf__u_selector : int32 = valueDeserializer.readInt8()
                let maxFontSize_buf__u : string | Resource | undefined
                if (maxFontSize_buf__u_selector == (0).toChar()) {
                    maxFontSize_buf__u = (valueDeserializer.readString() as string)
                }
                else if (maxFontSize_buf__u_selector == (1).toChar()) {
                    maxFontSize_buf__u = Resource_serializer.read(valueDeserializer)
                }
                else {
                    throw new Error("One of the branches for maxFontSize_buf__u has to be chosen through deserialisation.")
                }
                maxFontSize_buf_ = (maxFontSize_buf__u as string | Resource)
            }
            else {
                throw new Error("One of the branches for maxFontSize_buf_ has to be chosen through deserialisation.")
            }
            maxFontSize_buf = (maxFontSize_buf_ as number | ResourceStr)
        }
        const maxFontSize_result : number | ResourceStr | undefined = maxFontSize_buf
        const heightAdaptivePolicy_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let heightAdaptivePolicy_buf : TextHeightAdaptivePolicy | undefined
        if ((heightAdaptivePolicy_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            heightAdaptivePolicy_buf = TypeChecker.TextHeightAdaptivePolicy_FromNumeric(valueDeserializer.readInt32())
        }
        const heightAdaptivePolicy_result : TextHeightAdaptivePolicy | undefined = heightAdaptivePolicy_buf
        const font_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let font_buf : Font | undefined
        if ((font_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            font_buf = Font_serializer.read(valueDeserializer)
        }
        const font_result : Font | undefined = font_buf
        let value : ButtonLabelStyle = ({overflow: overflow_result, maxLines: maxLines_result, minFontSize: minFontSize_result, maxFontSize: maxFontSize_result, heightAdaptivePolicy: heightAdaptivePolicy_result, font: font_result} as ButtonLabelStyle)
        return value
    }
}
