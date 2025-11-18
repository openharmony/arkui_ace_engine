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
import { Resource_serializer } from "./../framework/resource"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, CommonConfiguration, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { ResourceColor, Length, ResourceStr, Font, Font_serializer } from "./units"
import { Color, FontWeight, FontStyle, TextOverflow, TextHeightAdaptivePolicy } from "./enums"
import { Resource } from "global.resource"
import { ContentModifier, AttributeModifier, hookButtonContentModifier, hookButtonAttributeModifier, AttributeUpdater } from "#handwritten"
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { ButtonModifier } from "./../ButtonModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkButtonPeer extends ArkCommonMethodPeer {
    attributeSet?: ButtonModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkButtonPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Button_construct(peerId, flags)
        const _peer  = new ArkButtonPeer(_peerPtr, peerId, 'Button', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setButtonOptions0Attribute(label: ResourceStr, options?: ButtonOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (label instanceof string) {
            thisSerializer.writeInt8((0).toByte())
            const labelForIdx0  = label as string
            thisSerializer.writeString(labelForIdx0)
        } else if (label instanceof Resource) {
            thisSerializer.writeInt8((1).toByte())
            const labelForIdx1  = label as Resource
            Resource_serializer.write(thisSerializer, labelForIdx1)
        }
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            ButtonOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ButtonInterface_setButtonOptions0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setButtonOptions1Attribute(options?: ButtonOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            ButtonOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ButtonInterface_setButtonOptions1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTypeAttribute(value: ButtonType | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as ButtonType)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
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
            thisSerializer.writeInt32(valueTmpValue.valueOf())
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
            thisSerializer.writeInt32(valueTmpValue.getOrdinal())
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
            thisSerializer.writeInt32(valueTmpValue.valueOf())
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
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as Color
                thisSerializer.writeInt32(valueTmpValueForIdx0.getOrdinal())
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
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
        ArkUIGeneratedNativeModule._ButtonAttribute_setFontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontSizeAttribute(value: Length | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ButtonAttribute_setFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontWeightAttribute(value: int32 | FontWeight | string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof int32) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as int32
                thisSerializer.writeInt32(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof FontWeight) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as FontWeight
                thisSerializer.writeInt32(valueTmpValueForIdx1.valueOf())
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toByte())
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
            thisSerializer.writeInt32(valueTmpValue.valueOf())
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
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((1).toByte())
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
    setMinFontScaleAttribute(value: double | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof double) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as double
                thisSerializer.writeFloat64(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ButtonAttribute_setMinFontScale(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMaxFontScaleAttribute(value: double | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof double) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as double
                thisSerializer.writeFloat64(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((1).toByte())
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
export type ButtonTriggerClickCallback = (xPos: double, yPos: double) => void;
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
    maxLines?: int32;
    minFontSize?: double | ResourceStr;
    maxFontSize?: double | ResourceStr;
    heightAdaptivePolicy?: TextHeightAdaptivePolicy;
    font?: Font;
}
export interface ButtonAttribute extends CommonMethod {
    setButtonOptions(label: ResourceStr, options?: ButtonOptions): this {
        throw new Error("Unimplemented method setButtonOptions")
    }
    setButtonOptions(options?: ButtonOptions): this {
        throw new Error("Unimplemented method setButtonOptions")
    }
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
    fontWeight(value: int32 | FontWeight | string | undefined): this {
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
    minFontScale(value: double | Resource | undefined): this {
        throw new Error("Unimplemented method minFontScale")
    }
    maxFontScale(value: double | Resource | undefined): this {
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
    fontWeight_value?: int32 | FontWeight | string | undefined
    fontStyle_value?: FontStyle | undefined
    fontFamily_value?: string | Resource | undefined
    contentModifier_value?: ContentModifier<ButtonConfiguration> | undefined
    labelStyle_value?: ButtonLabelStyle | undefined
    minFontScale_value?: double | Resource | undefined
    maxFontScale_value?: double | Resource | undefined
    attributeModifier_value?: AttributeModifier<ButtonAttribute> | AttributeModifier<CommonMethod> | undefined
    setButtonOptions(label: ResourceStr, options?: ButtonOptions): this {
        return this
    }
    setButtonOptions(options?: ButtonOptions): this {
        return this
    }
    type(value: ButtonType | undefined): this {
        return this
    }
    stateEffect(value: boolean | undefined): this {
        return this
    }
    buttonStyle(value: ButtonStyleMode | undefined): this {
        return this
    }
    controlSize(value: ControlSize | undefined): this {
        return this
    }
    role(value: ButtonRole | undefined): this {
        return this
    }
    fontColor(value: ResourceColor | undefined): this {
        return this
    }
    fontSize(value: Length | undefined): this {
        return this
    }
    fontWeight(value: int32 | FontWeight | string | undefined): this {
        return this
    }
    fontStyle(value: FontStyle | undefined): this {
        return this
    }
    fontFamily(value: string | Resource | undefined): this {
        return this
    }
    contentModifier(value: ContentModifier<ButtonConfiguration> | undefined): this {
        return this
    }
    labelStyle(value: ButtonLabelStyle | undefined): this {
        return this
    }
    minFontScale(value: double | Resource | undefined): this {
        return this
    }
    maxFontScale(value: double | Resource | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<ButtonAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkButtonComponent extends ArkCommonMethodComponent implements ButtonAttribute {
    getPeer(): ArkButtonPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkButtonPeer)
    }
    public setButtonOptions(label: ResourceStr, options?: ButtonOptions): this {
        if (this.checkPriority("setButtonOptions")) {
            const label_casted = label as (ResourceStr)
            const options_casted = options as (ButtonOptions | undefined)
            this.getPeer()?.setButtonOptions0Attribute(label_casted, options_casted)
            this.applyOptionsFinish('ButtonAttribute');
            return this
        }
        return this
    }
    public setButtonOptions(options?: ButtonOptions): this {
        if (this.checkPriority("setButtonOptions")) {
            const options_casted = options as (ButtonOptions | undefined)
            this.getPeer()?.setButtonOptions1Attribute(options_casted)
            this.applyOptionsFinish('ButtonAttribute');
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
    public fontWeight(value: int32 | FontWeight | string | undefined): this {
        if (this.checkPriority("fontWeight")) {
            const value_casted = value as (int32 | FontWeight | string | undefined)
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
    public minFontScale(value: double | Resource | undefined): this {
        if (this.checkPriority("minFontScale")) {
            const value_casted = value as (double | Resource | undefined)
            this.getPeer()?.setMinFontScaleAttribute(value_casted)
            return this
        }
        return this
    }
    public maxFontScale(value: double | Resource | undefined): this {
        if (this.checkPriority("maxFontScale")) {
            const value_casted = value as (double | Resource | undefined)
            this.getPeer()?.setMaxFontScaleAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<ButtonAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        hookButtonAttributeModifier(this, value);
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
export function ButtonImpl(
    @memo
    style: ((attributes: ButtonAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkButtonComponent>((): ArkButtonComponent => {
        return new ArkButtonComponent()
    })
    NodeAttach<ArkButtonPeer>((): ArkButtonPeer => ArkButtonPeer.create(receiver), (peer: ArkButtonPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
    })
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
        const triggerClickTmpResult : ButtonTriggerClickCallback = (xPos: double, yPos: double):void => {
            const triggerClickTmpBufBufArgsSerializer : SerializerBase = SerializerBase.hold();
            triggerClickTmpBufBufArgsSerializer.writeInt32(triggerClickTmpBufBufResource.resourceId);
            triggerClickTmpBufBufArgsSerializer.writePointer(triggerClickTmpBufBufCall);
            triggerClickTmpBufBufArgsSerializer.writePointer(triggerClickTmpBufBufCallSync);
            triggerClickTmpBufBufArgsSerializer.writeFloat64(xPos);
            triggerClickTmpBufBufArgsSerializer.writeFloat64(yPos);
            InteropNativeModule._CallCallbackSync(10, -1964292933, triggerClickTmpBufBufArgsSerializer.asBuffer(), triggerClickTmpBufBufArgsSerializer.length());
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
            valueSerializer.writeInt32(valueHolderForTypeTmpValue.valueOf())
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
            valueSerializer.writeInt32(valueHolderForButtonStyleTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForControlSize  = value.controlSize
        if (valueHolderForControlSize !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForControlSizeTmpValue  = (valueHolderForControlSize as ControlSize)
            valueSerializer.writeInt32(valueHolderForControlSizeTmpValue.getOrdinal())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForRole  = value.role
        if (valueHolderForRole !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForRoleTmpValue  = (valueHolderForRole as ButtonRole)
            valueSerializer.writeInt32(valueHolderForRoleTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ButtonOptions {
        let valueDeserializer : DeserializerBase = buffer
        const typeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let typeTmpBuf : ButtonType | undefined = undefined
        if ((typeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            typeTmpBuf = ButtonType.fromValue(valueDeserializer.readInt32())
        }
        const typeTmpResult : ButtonType | undefined = typeTmpBuf
        const stateEffectTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let stateEffectTmpBuf : boolean | undefined = undefined
        if ((stateEffectTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            stateEffectTmpBuf = valueDeserializer.readBoolean()
        }
        const stateEffectTmpResult : boolean | undefined = stateEffectTmpBuf
        const buttonStyleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let buttonStyleTmpBuf : ButtonStyleMode | undefined = undefined
        if ((buttonStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            buttonStyleTmpBuf = ButtonStyleMode.fromValue(valueDeserializer.readInt32())
        }
        const buttonStyleTmpResult : ButtonStyleMode | undefined = buttonStyleTmpBuf
        const controlSizeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let controlSizeTmpBuf : ControlSize | undefined = undefined
        if ((controlSizeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            controlSizeTmpBuf = ControlSize.values()[valueDeserializer.readInt32()]
        }
        const controlSizeTmpResult : ControlSize | undefined = controlSizeTmpBuf
        const roleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let roleTmpBuf : ButtonRole | undefined = undefined
        if ((roleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            roleTmpBuf = ButtonRole.fromValue(valueDeserializer.readInt32())
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
            valueSerializer.writeInt32(valueHolderForOverflowTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMaxLines  = value.maxLines
        if (valueHolderForMaxLines !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMaxLinesTmpValue  = valueHolderForMaxLines!
            valueSerializer.writeInt32(valueHolderForMaxLinesTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMinFontSize  = value.minFontSize
        if (valueHolderForMinFontSize !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMinFontSizeTmpValue  = valueHolderForMinFontSize!
            if (valueHolderForMinFontSizeTmpValue instanceof double) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForMinFontSizeTmpValueForIdx0  = valueHolderForMinFontSizeTmpValue as double
                valueSerializer.writeFloat64(valueHolderForMinFontSizeTmpValueForIdx0)
            } else if (valueHolderForMinFontSizeTmpValue instanceof ResourceStr) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForMinFontSizeTmpValueForIdx1  = valueHolderForMinFontSizeTmpValue as ResourceStr
                if (valueHolderForMinFontSizeTmpValueForIdx1 instanceof string) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForMinFontSizeTmpValueForIdx1ForIdx0  = valueHolderForMinFontSizeTmpValueForIdx1 as string
                    valueSerializer.writeString(valueHolderForMinFontSizeTmpValueForIdx1ForIdx0)
                } else if (valueHolderForMinFontSizeTmpValueForIdx1 instanceof Resource) {
                    valueSerializer.writeInt8((1).toByte())
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
            if (valueHolderForMaxFontSizeTmpValue instanceof double) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForMaxFontSizeTmpValueForIdx0  = valueHolderForMaxFontSizeTmpValue as double
                valueSerializer.writeFloat64(valueHolderForMaxFontSizeTmpValueForIdx0)
            } else if (valueHolderForMaxFontSizeTmpValue instanceof ResourceStr) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForMaxFontSizeTmpValueForIdx1  = valueHolderForMaxFontSizeTmpValue as ResourceStr
                if (valueHolderForMaxFontSizeTmpValueForIdx1 instanceof string) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForMaxFontSizeTmpValueForIdx1ForIdx0  = valueHolderForMaxFontSizeTmpValueForIdx1 as string
                    valueSerializer.writeString(valueHolderForMaxFontSizeTmpValueForIdx1ForIdx0)
                } else if (valueHolderForMaxFontSizeTmpValueForIdx1 instanceof Resource) {
                    valueSerializer.writeInt8((1).toByte())
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
            valueSerializer.writeInt32(valueHolderForHeightAdaptivePolicyTmpValue.valueOf())
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
        let overflowTmpBuf : TextOverflow | undefined = undefined
        if ((overflowTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            overflowTmpBuf = TextOverflow.fromValue(valueDeserializer.readInt32())
        }
        const overflowTmpResult : TextOverflow | undefined = overflowTmpBuf
        const maxLinesTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let maxLinesTmpBuf : int32 | undefined = undefined
        if ((maxLinesTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            maxLinesTmpBuf = valueDeserializer.readInt32()
        }
        const maxLinesTmpResult : int32 | undefined = maxLinesTmpBuf
        const minFontSizeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let minFontSizeTmpBuf : double | ResourceStr | undefined = undefined
        if ((minFontSizeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const minFontSizeTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let minFontSizeTmpBuf_ : double | ResourceStr | undefined
            if (minFontSizeTmpBuf_UnionSelector == (0).toChar()) {
                minFontSizeTmpBuf_ = valueDeserializer.readFloat64()
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
            minFontSizeTmpBuf = (minFontSizeTmpBuf_ as double | ResourceStr)
        }
        const minFontSizeTmpResult : double | ResourceStr | undefined = minFontSizeTmpBuf
        const maxFontSizeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let maxFontSizeTmpBuf : double | ResourceStr | undefined = undefined
        if ((maxFontSizeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const maxFontSizeTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let maxFontSizeTmpBuf_ : double | ResourceStr | undefined
            if (maxFontSizeTmpBuf_UnionSelector == (0).toChar()) {
                maxFontSizeTmpBuf_ = valueDeserializer.readFloat64()
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
            maxFontSizeTmpBuf = (maxFontSizeTmpBuf_ as double | ResourceStr)
        }
        const maxFontSizeTmpResult : double | ResourceStr | undefined = maxFontSizeTmpBuf
        const heightAdaptivePolicyTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let heightAdaptivePolicyTmpBuf : TextHeightAdaptivePolicy | undefined = undefined
        if ((heightAdaptivePolicyTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            heightAdaptivePolicyTmpBuf = TextHeightAdaptivePolicy.fromValue(valueDeserializer.readInt32())
        }
        const heightAdaptivePolicyTmpResult : TextHeightAdaptivePolicy | undefined = heightAdaptivePolicyTmpBuf
        const fontTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fontTmpBuf : Font | undefined = undefined
        if ((fontTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            fontTmpBuf = Font_serializer.read(valueDeserializer)
        }
        const fontTmpResult : Font | undefined = fontTmpBuf
        let value : ButtonLabelStyle = ({overflow: overflowTmpResult, maxLines: maxLinesTmpResult, minFontSize: minFontSizeTmpResult, maxFontSize: maxFontSizeTmpResult, heightAdaptivePolicy: heightAdaptivePolicyTmpResult, font: fontTmpResult} as ButtonLabelStyle)
        return value
    }
}
