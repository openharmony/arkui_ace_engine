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

import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { Resource_serializer, Resource } from "./../generated/resource"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, CommonConfiguration, ArkCommonMethodComponent, ArkCommonMethodStyle, CommonMethodModifier } from "./common"
import { ResourceColor, Length, ResourceStr, Font, Font_serializer } from "./units"
import { Color, FontWeight, FontStyle, TextOverflow, TextHeightAdaptivePolicy } from "./enums"
import { ContentModifier, AttributeModifier, hookButtonContentModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
import { AttributeUpdaterFlag } from "./../generated/AttributeUpdater"
export class ArkButtonPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkButtonPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Button_construct(peerId, flags)
        const _peer  = new ArkButtonPeer(_peerPtr, peerId, 'Button', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setButtonOptionsAttribute(label: ButtonOptions | ResourceStr, options?: ButtonOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (label instanceof ButtonOptions) {
            thisSerializer.writeInt8((0).toChar())
            const labelForIdx0  = label as ButtonOptions
            ButtonOptions_serializer.write(thisSerializer, labelForIdx0)
        } else if (label instanceof ResourceStr) {
            thisSerializer.writeInt8((1).toChar())
            const labelForIdx1  = label as ResourceStr
            if (labelForIdx1 instanceof string) {
                thisSerializer.writeInt8((0).toChar())
                const labelForIdx1ForIdx0  = labelForIdx1 as string
                thisSerializer.writeString(labelForIdx1ForIdx0)
            } else if (labelForIdx1 instanceof Resource) {
                thisSerializer.writeInt8((1).toChar())
                const labelForIdx1ForIdx1  = labelForIdx1 as Resource
                Resource_serializer.write(thisSerializer, labelForIdx1ForIdx1)
            }
        }
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            ButtonOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ButtonInterface_setButtonOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTypeAttribute(value: ButtonType | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as ButtonType)
            thisSerializer.writeInt32(TypeChecker.ButtonType_ToNumeric(valueTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ButtonAttribute_setType(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setStateEffectAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ButtonAttribute_setStateEffect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setButtonStyleAttribute(value: ButtonStyleMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as ButtonStyleMode)
            thisSerializer.writeInt32(TypeChecker.ButtonStyleMode_ToNumeric(valueTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ButtonAttribute_setButtonStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setControlSizeAttribute(value: ControlSize | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as ControlSize)
            thisSerializer.writeInt32(TypeChecker.ControlSize_ToNumeric(valueTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ButtonAttribute_setControlSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setRoleAttribute(value: ButtonRole | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as ButtonRole)
            thisSerializer.writeInt32(TypeChecker.ButtonRole_ToNumeric(valueTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ButtonAttribute_setRole(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._ButtonAttribute_setFontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontSizeAttribute(value: Length | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValueForIdx2  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ButtonAttribute_setFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontWeightAttribute(value: number | FontWeight | string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof FontWeight) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as FontWeight
                thisSerializer.writeInt32(TypeChecker.FontWeight_ToNumeric(valueTmpValueForIdx1))
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ButtonAttribute_setFontWeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontStyleAttribute(value: FontStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as FontStyle)
            thisSerializer.writeInt32(TypeChecker.FontStyle_ToNumeric(valueTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ButtonAttribute_setFontStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontFamilyAttribute(value: string | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ButtonAttribute_setFontFamily(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setLabelStyleAttribute(value: ButtonLabelStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            ButtonLabelStyle_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ButtonAttribute_setLabelStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMinFontScaleAttribute(value: number | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ButtonAttribute_setMinFontScale(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMaxFontScaleAttribute(value: number | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
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
}

export class ArkButtonComponent extends ArkCommonMethodComponent implements ButtonAttribute {
    getPeer(): ArkButtonPeer {
        return (this.peer as ArkButtonPeer)
    }
    public setButtonOptions(label: ButtonOptions | ResourceStr, options?: ButtonOptions): this {
        if (this.checkPriority("setButtonOptions")) {
            const label_casted = label as (ButtonOptions | ResourceStr)
            const options_casted = options as (ButtonOptions | undefined)
            this.getPeer()?.setButtonOptionsAttribute(label_casted, options_casted)
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
            hookButtonContentModifier(this, value)
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
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

@memo
export function Button(
    @memo
    style: ((attributes: ButtonAttribute) => void) | undefined,
    label: ButtonOptions | ResourceStr, options?: ButtonOptions,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkButtonComponent>((): ArkButtonComponent => {
        return new ArkButtonComponent()
    })
    NodeAttach<ArkButtonPeer>((): ArkButtonPeer => ArkButtonPeer.create(receiver), (_: ArkButtonPeer): void => {
        receiver.setButtonOptions(label,options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ButtonModifier extends CommonMethodModifier implements ButtonAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _type_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _type_0_0value?: ButtonType | undefined
    _stateEffect_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _stateEffect_0_0value?: boolean | undefined
    _buttonStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _buttonStyle_0_0value?: ButtonStyleMode | undefined
    _controlSize_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _controlSize_0_0value?: ControlSize | undefined
    _role_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _role_0_0value?: ButtonRole | undefined
    _fontColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontColor_0_0value?: ResourceColor | undefined
    _fontSize_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontSize_0_0value?: Length | undefined
    _fontWeight_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontWeight_0_0value?: number | FontWeight | string | undefined
    _fontStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontStyle_0_0value?: FontStyle | undefined
    _fontFamily_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontFamily_0_0value?: string | Resource | undefined
    _labelStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _labelStyle_0_0value?: ButtonLabelStyle | undefined
    _minFontScale_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _minFontScale_0_0value?: number | Resource | undefined
    _maxFontScale_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _maxFontScale_0_0value?: number | Resource | undefined
    applyModifierPatch(peer: ArkButtonPeer): void {
        super.applyModifierPatch(peer)
        if (this._type_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._type_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setTypeAttribute((this._type_0_0value as ButtonType | undefined));
                    this._type_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._type_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._type_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setTypeAttribute((undefined as ButtonType | undefined));
                }
            }
        }
        if (this._stateEffect_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._stateEffect_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setStateEffectAttribute((this._stateEffect_0_0value as boolean | undefined));
                    this._stateEffect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._stateEffect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._stateEffect_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setStateEffectAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._buttonStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._buttonStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setButtonStyleAttribute((this._buttonStyle_0_0value as ButtonStyleMode | undefined));
                    this._buttonStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._buttonStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._buttonStyle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setButtonStyleAttribute((undefined as ButtonStyleMode | undefined));
                }
            }
        }
        if (this._controlSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._controlSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setControlSizeAttribute((this._controlSize_0_0value as ControlSize | undefined));
                    this._controlSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._controlSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._controlSize_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setControlSizeAttribute((undefined as ControlSize | undefined));
                }
            }
        }
        if (this._role_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._role_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setRoleAttribute((this._role_0_0value as ButtonRole | undefined));
                    this._role_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._role_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._role_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setRoleAttribute((undefined as ButtonRole | undefined));
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
        if (this._fontSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fontSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFontSizeAttribute((this._fontSize_0_0value as Length | undefined));
                    this._fontSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fontSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fontSize_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFontSizeAttribute((undefined as Length | undefined));
                }
            }
        }
        if (this._fontWeight_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fontWeight_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFontWeightAttribute((this._fontWeight_0_0value as number | FontWeight | string | undefined));
                    this._fontWeight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fontWeight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fontWeight_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFontWeightAttribute((undefined as number | FontWeight | string | undefined));
                }
            }
        }
        if (this._fontStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fontStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFontStyleAttribute((this._fontStyle_0_0value as FontStyle | undefined));
                    this._fontStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fontStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fontStyle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFontStyleAttribute((undefined as FontStyle | undefined));
                }
            }
        }
        if (this._fontFamily_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fontFamily_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFontFamilyAttribute((this._fontFamily_0_0value as string | Resource | undefined));
                    this._fontFamily_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fontFamily_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fontFamily_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFontFamilyAttribute((undefined as string | Resource | undefined));
                }
            }
        }
        if (this._labelStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._labelStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setLabelStyleAttribute((this._labelStyle_0_0value as ButtonLabelStyle | undefined));
                    this._labelStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._labelStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._labelStyle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setLabelStyleAttribute((undefined as ButtonLabelStyle | undefined));
                }
            }
        }
        if (this._minFontScale_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._minFontScale_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMinFontScaleAttribute((this._minFontScale_0_0value as number | Resource | undefined));
                    this._minFontScale_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._minFontScale_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._minFontScale_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMinFontScaleAttribute((undefined as number | Resource | undefined));
                }
            }
        }
        if (this._maxFontScale_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._maxFontScale_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMaxFontScaleAttribute((this._maxFontScale_0_0value as number | Resource | undefined));
                    this._maxFontScale_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._maxFontScale_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._maxFontScale_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMaxFontScaleAttribute((undefined as number | Resource | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: ButtonModifier): void {
        super.mergeModifier(modifier)
        if (modifier._type_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._type_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.type(modifier._type_0_0value);
                    break;
                }
                default: {
                    this.type((undefined as ButtonType | undefined));
                }
            }
        }
        if (modifier._stateEffect_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._stateEffect_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.stateEffect(modifier._stateEffect_0_0value);
                    break;
                }
                default: {
                    this.stateEffect((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._buttonStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._buttonStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.buttonStyle(modifier._buttonStyle_0_0value);
                    break;
                }
                default: {
                    this.buttonStyle((undefined as ButtonStyleMode | undefined));
                }
            }
        }
        if (modifier._controlSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._controlSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.controlSize(modifier._controlSize_0_0value);
                    break;
                }
                default: {
                    this.controlSize((undefined as ControlSize | undefined));
                }
            }
        }
        if (modifier._role_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._role_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.role(modifier._role_0_0value);
                    break;
                }
                default: {
                    this.role((undefined as ButtonRole | undefined));
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
        if (modifier._fontSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._fontSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.fontSize(modifier._fontSize_0_0value);
                    break;
                }
                default: {
                    this.fontSize((undefined as Length | undefined));
                }
            }
        }
        if (modifier._fontWeight_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._fontWeight_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.fontWeight(modifier._fontWeight_0_0value);
                    break;
                }
                default: {
                    this.fontWeight((undefined as number | FontWeight | string | undefined));
                }
            }
        }
        if (modifier._fontStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._fontStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.fontStyle(modifier._fontStyle_0_0value);
                    break;
                }
                default: {
                    this.fontStyle((undefined as FontStyle | undefined));
                }
            }
        }
        if (modifier._fontFamily_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._fontFamily_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.fontFamily(modifier._fontFamily_0_0value);
                    break;
                }
                default: {
                    this.fontFamily((undefined as string | Resource | undefined));
                }
            }
        }
        if (modifier._labelStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._labelStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.labelStyle(modifier._labelStyle_0_0value);
                    break;
                }
                default: {
                    this.labelStyle((undefined as ButtonLabelStyle | undefined));
                }
            }
        }
        if (modifier._minFontScale_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._minFontScale_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.minFontScale(modifier._minFontScale_0_0value);
                    break;
                }
                default: {
                    this.minFontScale((undefined as number | Resource | undefined));
                }
            }
        }
        if (modifier._maxFontScale_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._maxFontScale_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.maxFontScale(modifier._maxFontScale_0_0value);
                    break;
                }
                default: {
                    this.maxFontScale((undefined as number | Resource | undefined));
                }
            }
        }
    }
    type(value: ButtonType | undefined): this {
        if (((this._type_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._type_0_flag = AttributeUpdaterFlag.UPDATE
            this._type_0_0value = value
        } else
        {
            this._type_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    stateEffect(value: boolean | undefined): this {
        if (((this._stateEffect_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._stateEffect_0_0value) !== (value)))
        {
            this._stateEffect_0_flag = AttributeUpdaterFlag.UPDATE
            this._stateEffect_0_0value = value
        } else
        {
            this._stateEffect_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    buttonStyle(value: ButtonStyleMode | undefined): this {
        if (((this._buttonStyle_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._buttonStyle_0_flag = AttributeUpdaterFlag.UPDATE
            this._buttonStyle_0_0value = value
        } else
        {
            this._buttonStyle_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    controlSize(value: ControlSize | undefined): this {
        if (((this._controlSize_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._controlSize_0_flag = AttributeUpdaterFlag.UPDATE
            this._controlSize_0_0value = value
        } else
        {
            this._controlSize_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    role(value: ButtonRole | undefined): this {
        if (((this._role_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._role_0_flag = AttributeUpdaterFlag.UPDATE
            this._role_0_0value = value
        } else
        {
            this._role_0_flag = AttributeUpdaterFlag.SKIP
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
    fontSize(value: Length | undefined): this {
        if (((this._fontSize_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._fontSize_0_flag = AttributeUpdaterFlag.UPDATE
            this._fontSize_0_0value = value
        } else
        {
            this._fontSize_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    fontWeight(value: number | FontWeight | string | undefined): this {
        if (((this._fontWeight_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._fontWeight_0_flag = AttributeUpdaterFlag.UPDATE
            this._fontWeight_0_0value = value
        } else
        {
            this._fontWeight_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    fontStyle(value: FontStyle | undefined): this {
        if (((this._fontStyle_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._fontStyle_0_flag = AttributeUpdaterFlag.UPDATE
            this._fontStyle_0_0value = value
        } else
        {
            this._fontStyle_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    fontFamily(value: string | Resource | undefined): this {
        if (((this._fontFamily_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._fontFamily_0_flag = AttributeUpdaterFlag.UPDATE
            this._fontFamily_0_0value = value
        } else
        {
            this._fontFamily_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    labelStyle(value: ButtonLabelStyle | undefined): this {
        if (((this._labelStyle_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._labelStyle_0_flag = AttributeUpdaterFlag.UPDATE
            this._labelStyle_0_0value = value
        } else
        {
            this._labelStyle_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    minFontScale(value: number | Resource | undefined): this {
        if (((this._minFontScale_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._minFontScale_0_flag = AttributeUpdaterFlag.UPDATE
            this._minFontScale_0_0value = value
        } else
        {
            this._minFontScale_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    maxFontScale(value: number | Resource | undefined): this {
        if (((this._maxFontScale_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._maxFontScale_0_flag = AttributeUpdaterFlag.UPDATE
            this._maxFontScale_0_0value = value
        } else
        {
            this._maxFontScale_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<ButtonAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class ButtonConfiguration_serializer {
    public static write(buffer: SerializerBase, value: ButtonConfiguration): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForEnabled  = value.enabled
        valueSerializer.writeBoolean(valueHolderForEnabled)
        const valueHolderForContentModifier  = value.contentModifier
        valueSerializer.holdAndWriteObject(valueHolderForContentModifier)
        const valueHolderForLabel  = value.label
        valueSerializer.writeString(valueHolderForLabel)
        const valueHolderForPressed  = value.pressed
        valueSerializer.writeBoolean(valueHolderForPressed)
        const valueHolderForTriggerClick  = value.triggerClick
        valueSerializer.holdAndWriteCallback(valueHolderForTriggerClick)
    }
    public static read(buffer: DeserializerBase): ButtonConfiguration {
        let valueDeserializer : DeserializerBase = buffer
        const enabledTmpResult : boolean = valueDeserializer.readBoolean()
        const contentModifierTmpResult : ContentModifier<ButtonConfiguration> = (valueDeserializer.readObject() as ContentModifier<ButtonConfiguration>)
        const labelTmpResult : string = (valueDeserializer.readString() as string)
        const pressedTmpResult : boolean = valueDeserializer.readBoolean()
        const triggerClickTmpBufBufResource : CallbackResource = valueDeserializer.readCallbackResource()
        const triggerClickTmpBufBufCall : KPointer = valueDeserializer.readPointer()
        const triggerClickTmpBufBufCallSync : KPointer = valueDeserializer.readPointer()
        const triggerClickTmpResult : ButtonTriggerClickCallback = (xPos: number, yPos: number):void => {
            const triggerClickTmpBufBufArgsSerializer : SerializerBase = SerializerBase.hold();
            triggerClickTmpBufBufArgsSerializer.writeInt32(triggerClickTmpBufBufResource.resourceId);
            triggerClickTmpBufBufArgsSerializer.writePointer(triggerClickTmpBufBufCall);
            triggerClickTmpBufBufArgsSerializer.writePointer(triggerClickTmpBufBufCallSync);
            triggerClickTmpBufBufArgsSerializer.writeNumber(xPos);
            triggerClickTmpBufBufArgsSerializer.writeNumber(yPos);
            InteropNativeModule._CallCallback(-1964292933, triggerClickTmpBufBufArgsSerializer.asBuffer(), triggerClickTmpBufBufArgsSerializer.length());
            triggerClickTmpBufBufArgsSerializer.release();
            return;
        }
        let value : ButtonConfiguration = ({enabled: enabledTmpResult, contentModifier: contentModifierTmpResult, label: labelTmpResult, pressed: pressedTmpResult, triggerClick: triggerClickTmpResult} as ButtonConfiguration)
        return value
    }
}
export class ButtonOptions_serializer {
    public static write(buffer: SerializerBase, value: ButtonOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForType  = value.type
        if (valueHolderForType !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTypeTmpValue  = (valueHolderForType as ButtonType)
            valueSerializer.writeInt32(TypeChecker.ButtonType_ToNumeric(valueHolderForTypeTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForStateEffect  = value.stateEffect
        if (valueHolderForStateEffect !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStateEffectTmpValue  = valueHolderForStateEffect!
            valueSerializer.writeBoolean(valueHolderForStateEffectTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForButtonStyle  = value.buttonStyle
        if (valueHolderForButtonStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForButtonStyleTmpValue  = (valueHolderForButtonStyle as ButtonStyleMode)
            valueSerializer.writeInt32(TypeChecker.ButtonStyleMode_ToNumeric(valueHolderForButtonStyleTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForControlSize  = value.controlSize
        if (valueHolderForControlSize !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForControlSizeTmpValue  = (valueHolderForControlSize as ControlSize)
            valueSerializer.writeInt32(TypeChecker.ControlSize_ToNumeric(valueHolderForControlSizeTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForRole  = value.role
        if (valueHolderForRole !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForRoleTmpValue  = (valueHolderForRole as ButtonRole)
            valueSerializer.writeInt32(TypeChecker.ButtonRole_ToNumeric(valueHolderForRoleTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ButtonOptions {
        let valueDeserializer : DeserializerBase = buffer
        const typeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let typeTmpBuf : ButtonType | undefined
        if ((typeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            typeTmpBuf = TypeChecker.ButtonType_FromNumeric(valueDeserializer.readInt32())
        }
        const typeTmpResult : ButtonType | undefined = typeTmpBuf
        const stateEffectTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let stateEffectTmpBuf : boolean | undefined
        if ((stateEffectTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            stateEffectTmpBuf = valueDeserializer.readBoolean()
        }
        const stateEffectTmpResult : boolean | undefined = stateEffectTmpBuf
        const buttonStyleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let buttonStyleTmpBuf : ButtonStyleMode | undefined
        if ((buttonStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            buttonStyleTmpBuf = TypeChecker.ButtonStyleMode_FromNumeric(valueDeserializer.readInt32())
        }
        const buttonStyleTmpResult : ButtonStyleMode | undefined = buttonStyleTmpBuf
        const controlSizeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let controlSizeTmpBuf : ControlSize | undefined
        if ((controlSizeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            controlSizeTmpBuf = TypeChecker.ControlSize_FromNumeric(valueDeserializer.readInt32())
        }
        const controlSizeTmpResult : ControlSize | undefined = controlSizeTmpBuf
        const roleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let roleTmpBuf : ButtonRole | undefined
        if ((roleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            roleTmpBuf = TypeChecker.ButtonRole_FromNumeric(valueDeserializer.readInt32())
        }
        const roleTmpResult : ButtonRole | undefined = roleTmpBuf
        let value : ButtonOptions = ({type: typeTmpResult, stateEffect: stateEffectTmpResult, buttonStyle: buttonStyleTmpResult, controlSize: controlSizeTmpResult, role: roleTmpResult} as ButtonOptions)
        return value
    }
}
export class ButtonLabelStyle_serializer {
    public static write(buffer: SerializerBase, value: ButtonLabelStyle): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForOverflow  = value.overflow
        if (valueHolderForOverflow !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOverflowTmpValue  = (valueHolderForOverflow as TextOverflow)
            valueSerializer.writeInt32(TypeChecker.TextOverflow_ToNumeric(valueHolderForOverflowTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMaxLines  = value.maxLines
        if (valueHolderForMaxLines !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMaxLinesTmpValue  = valueHolderForMaxLines!
            valueSerializer.writeNumber(valueHolderForMaxLinesTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMinFontSize  = value.minFontSize
        if (valueHolderForMinFontSize !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMinFontSizeTmpValue  = valueHolderForMinFontSize!
            if (valueHolderForMinFontSizeTmpValue instanceof number) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForMinFontSizeTmpValueForIdx0  = valueHolderForMinFontSizeTmpValue as number
                valueSerializer.writeNumber(valueHolderForMinFontSizeTmpValueForIdx0)
            } else if (valueHolderForMinFontSizeTmpValue instanceof ResourceStr) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForMinFontSizeTmpValueForIdx1  = valueHolderForMinFontSizeTmpValue as ResourceStr
                if (valueHolderForMinFontSizeTmpValueForIdx1 instanceof string) {
                    valueSerializer.writeInt8((0).toChar())
                    const valueHolderForMinFontSizeTmpValueForIdx1ForIdx0  = valueHolderForMinFontSizeTmpValueForIdx1 as string
                    valueSerializer.writeString(valueHolderForMinFontSizeTmpValueForIdx1ForIdx0)
                } else if (valueHolderForMinFontSizeTmpValueForIdx1 instanceof Resource) {
                    valueSerializer.writeInt8((1).toChar())
                    const valueHolderForMinFontSizeTmpValueForIdx1ForIdx1  = valueHolderForMinFontSizeTmpValueForIdx1 as Resource
                    Resource_serializer.write(valueSerializer, valueHolderForMinFontSizeTmpValueForIdx1ForIdx1)
                }
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMaxFontSize  = value.maxFontSize
        if (valueHolderForMaxFontSize !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMaxFontSizeTmpValue  = valueHolderForMaxFontSize!
            if (valueHolderForMaxFontSizeTmpValue instanceof number) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForMaxFontSizeTmpValueForIdx0  = valueHolderForMaxFontSizeTmpValue as number
                valueSerializer.writeNumber(valueHolderForMaxFontSizeTmpValueForIdx0)
            } else if (valueHolderForMaxFontSizeTmpValue instanceof ResourceStr) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForMaxFontSizeTmpValueForIdx1  = valueHolderForMaxFontSizeTmpValue as ResourceStr
                if (valueHolderForMaxFontSizeTmpValueForIdx1 instanceof string) {
                    valueSerializer.writeInt8((0).toChar())
                    const valueHolderForMaxFontSizeTmpValueForIdx1ForIdx0  = valueHolderForMaxFontSizeTmpValueForIdx1 as string
                    valueSerializer.writeString(valueHolderForMaxFontSizeTmpValueForIdx1ForIdx0)
                } else if (valueHolderForMaxFontSizeTmpValueForIdx1 instanceof Resource) {
                    valueSerializer.writeInt8((1).toChar())
                    const valueHolderForMaxFontSizeTmpValueForIdx1ForIdx1  = valueHolderForMaxFontSizeTmpValueForIdx1 as Resource
                    Resource_serializer.write(valueSerializer, valueHolderForMaxFontSizeTmpValueForIdx1ForIdx1)
                }
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForHeightAdaptivePolicy  = value.heightAdaptivePolicy
        if (valueHolderForHeightAdaptivePolicy !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForHeightAdaptivePolicyTmpValue  = (valueHolderForHeightAdaptivePolicy as TextHeightAdaptivePolicy)
            valueSerializer.writeInt32(TypeChecker.TextHeightAdaptivePolicy_ToNumeric(valueHolderForHeightAdaptivePolicyTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForFont  = value.font
        if (valueHolderForFont !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFontTmpValue  = valueHolderForFont!
            Font_serializer.write(valueSerializer, valueHolderForFontTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ButtonLabelStyle {
        let valueDeserializer : DeserializerBase = buffer
        const overflowTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let overflowTmpBuf : TextOverflow | undefined
        if ((overflowTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            overflowTmpBuf = TypeChecker.TextOverflow_FromNumeric(valueDeserializer.readInt32())
        }
        const overflowTmpResult : TextOverflow | undefined = overflowTmpBuf
        const maxLinesTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let maxLinesTmpBuf : number | undefined
        if ((maxLinesTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            maxLinesTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const maxLinesTmpResult : number | undefined = maxLinesTmpBuf
        const minFontSizeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let minFontSizeTmpBuf : number | ResourceStr | undefined
        if ((minFontSizeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const minFontSizeTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let minFontSizeTmpBuf_ : number | ResourceStr | undefined
            if (minFontSizeTmpBuf_UnionSelector == (0).toChar()) {
                minFontSizeTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (minFontSizeTmpBuf_UnionSelector == (1).toChar()) {
                const minFontSizeTmpBuf_BufUUnionSelector : int32 = valueDeserializer.readInt8()
                let minFontSizeTmpBuf_BufU : string | Resource | undefined
                if (minFontSizeTmpBuf_BufUUnionSelector == (0).toChar()) {
                    minFontSizeTmpBuf_BufU = (valueDeserializer.readString() as string)
                } else if (minFontSizeTmpBuf_BufUUnionSelector == (1).toChar()) {
                    minFontSizeTmpBuf_BufU = Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error("One of the branches for minFontSizeTmpBuf_BufU has to be chosen through deserialisation.")
                }
                minFontSizeTmpBuf_ = (minFontSizeTmpBuf_BufU as string | Resource)
            } else {
                throw new Error("One of the branches for minFontSizeTmpBuf_ has to be chosen through deserialisation.")
            }
            minFontSizeTmpBuf = (minFontSizeTmpBuf_ as number | ResourceStr)
        }
        const minFontSizeTmpResult : number | ResourceStr | undefined = minFontSizeTmpBuf
        const maxFontSizeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let maxFontSizeTmpBuf : number | ResourceStr | undefined
        if ((maxFontSizeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const maxFontSizeTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let maxFontSizeTmpBuf_ : number | ResourceStr | undefined
            if (maxFontSizeTmpBuf_UnionSelector == (0).toChar()) {
                maxFontSizeTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (maxFontSizeTmpBuf_UnionSelector == (1).toChar()) {
                const maxFontSizeTmpBuf_BufUUnionSelector : int32 = valueDeserializer.readInt8()
                let maxFontSizeTmpBuf_BufU : string | Resource | undefined
                if (maxFontSizeTmpBuf_BufUUnionSelector == (0).toChar()) {
                    maxFontSizeTmpBuf_BufU = (valueDeserializer.readString() as string)
                } else if (maxFontSizeTmpBuf_BufUUnionSelector == (1).toChar()) {
                    maxFontSizeTmpBuf_BufU = Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error("One of the branches for maxFontSizeTmpBuf_BufU has to be chosen through deserialisation.")
                }
                maxFontSizeTmpBuf_ = (maxFontSizeTmpBuf_BufU as string | Resource)
            } else {
                throw new Error("One of the branches for maxFontSizeTmpBuf_ has to be chosen through deserialisation.")
            }
            maxFontSizeTmpBuf = (maxFontSizeTmpBuf_ as number | ResourceStr)
        }
        const maxFontSizeTmpResult : number | ResourceStr | undefined = maxFontSizeTmpBuf
        const heightAdaptivePolicyTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let heightAdaptivePolicyTmpBuf : TextHeightAdaptivePolicy | undefined
        if ((heightAdaptivePolicyTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            heightAdaptivePolicyTmpBuf = TypeChecker.TextHeightAdaptivePolicy_FromNumeric(valueDeserializer.readInt32())
        }
        const heightAdaptivePolicyTmpResult : TextHeightAdaptivePolicy | undefined = heightAdaptivePolicyTmpBuf
        const fontTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fontTmpBuf : Font | undefined
        if ((fontTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            fontTmpBuf = Font_serializer.read(valueDeserializer)
        }
        const fontTmpResult : Font | undefined = fontTmpBuf
        let value : ButtonLabelStyle = ({overflow: overflowTmpResult, maxLines: maxLinesTmpResult, minFontSize: minFontSizeTmpResult, maxFontSize: maxFontSizeTmpResult, heightAdaptivePolicy: heightAdaptivePolicyTmpResult, font: fontTmpResult} as ButtonLabelStyle)
        return value
    }
}
