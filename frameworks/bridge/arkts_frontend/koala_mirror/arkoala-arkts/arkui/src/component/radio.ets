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
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, CommonConfiguration, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonMethodSet } from "./common"
import { ContentModifier, AttributeModifier, hookRadioContentModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { CustomBuilder } from "./builder"
import { ResourceColor } from "./units"
import { Color } from "./enums"
import { Resource, Resource_serializer } from "./../generated/resource"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkRadioPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkRadioPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Radio_construct(peerId, flags)
        const _peer  = new ArkRadioPeer(_peerPtr, peerId, "Radio", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setRadioOptionsAttribute(options: RadioOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        RadioOptions_serializer.write(thisSerializer, options)
        ArkUIGeneratedNativeModule._RadioInterface_setRadioOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCheckedAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._RadioAttribute_setChecked(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnChangeAttribute(value: OnRadioChangeCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._RadioAttribute_setOnChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setRadioStyleAttribute(value: RadioStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            RadioStyle_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._RadioAttribute_setRadioStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setContentModifierAttribute(value: ContentModifier<RadioConfiguration> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteObject(value_value)
        }
        ArkUIGeneratedNativeModule._RadioAttribute_setContentModifier(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    set_onChangeEvent_checkedAttribute(callback_: ((checked: boolean | undefined) => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(callback_)
        ArkUIGeneratedNativeModule._RadioAttribute_set_onChangeEvent_checked(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export enum RadioIndicatorType {
    TICK = 0,
    DOT = 1,
    CUSTOM = 2
}
export interface RadioOptions {
    group: string;
    value: string;
    indicatorType?: RadioIndicatorType;
    indicatorBuilder?: CustomBuilder;
}
export interface RadioStyle {
    checkedBackgroundColor?: ResourceColor;
    uncheckedBorderColor?: ResourceColor;
    indicatorColor?: ResourceColor;
}
export type OnRadioChangeCallback = (isChecked: boolean) => void;
export interface RadioAttribute extends CommonMethod {
    checked(value: boolean | undefined): this {
        throw new Error("Unimplemented method checked")
    }
    onChange(value: OnRadioChangeCallback | undefined): this {
        throw new Error("Unimplemented method onChange")
    }
    radioStyle(value: RadioStyle | undefined): this {
        throw new Error("Unimplemented method radioStyle")
    }
    contentModifier(value: ContentModifier<RadioConfiguration> | undefined): this {
        throw new Error("Unimplemented method contentModifier")
    }
    _onChangeEvent_checked(callback_: ((checked: boolean | undefined) => void)): void {
        throw new Error("Unimplemented method _onChangeEvent_checked")
    }
    attributeModifier(value: AttributeModifier<RadioAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkRadioStyle extends ArkCommonMethodStyle implements RadioAttribute {
    checked_value?: boolean | undefined
    onChange_value?: OnRadioChangeCallback | undefined
    radioStyle_value?: RadioStyle | undefined
    contentModifier_value?: ContentModifier<RadioConfiguration> | undefined
    attributeModifier_value?: AttributeModifier<RadioAttribute> | AttributeModifier<CommonMethod> | undefined
    public checked(value: boolean | undefined): this {
        return this
    }
    public onChange(value: OnRadioChangeCallback | undefined): this {
        return this
    }
    public radioStyle(value: RadioStyle | undefined): this {
        return this
    }
    public contentModifier(value: ContentModifier<RadioConfiguration> | undefined): this {
        return this
    }
    public _onChangeEvent_checked(callback_: ((checked: boolean | undefined) => void)): void {
        throw new Error("Unimplemented")
    }
    public attributeModifier(value: AttributeModifier<RadioAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: RadioAttribute): void {
        super.apply(target)
        if (this.checked_value !== undefined)
            target.checked(this.checked_value!)
        if (this.onChange_value !== undefined)
            target.onChange(this.onChange_value!)
        if (this.radioStyle_value !== undefined)
            target.radioStyle(this.radioStyle_value!)
        if (this.contentModifier_value !== undefined)
            target.contentModifier(this.contentModifier_value!)
    }
}
export interface RadioConfiguration extends CommonConfiguration<RadioConfiguration> {
    value: string;
    checked: boolean;
    triggerChange: ((value0: boolean) => void);
}

export class ArkRadioComponent extends ArkCommonMethodComponent implements RadioAttribute {
    getPeer(): ArkRadioPeer {
        return (this.peer as ArkRadioPeer)
    }
    public setRadioOptions(options: RadioOptions): this {
        if (this.checkPriority("setRadioOptions")) {
            const options_casted = options as (RadioOptions)
            this.getPeer()?.setRadioOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    public checked(value: boolean | undefined): this {
        if (this.checkPriority("checked")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setCheckedAttribute(value_casted)
            return this
        }
        return this
    }
    public onChange(value: OnRadioChangeCallback | undefined): this {
        if (this.checkPriority("onChange")) {
            const value_casted = value as (OnRadioChangeCallback | undefined)
            this.getPeer()?.setOnChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public radioStyle(value: RadioStyle | undefined): this {
        if (this.checkPriority("radioStyle")) {
            const value_casted = value as (RadioStyle | undefined)
            this.getPeer()?.setRadioStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public contentModifier(value: ContentModifier<RadioConfiguration> | undefined): this {
        if (this.checkPriority("contentModifier")) {
            const value_casted = value as (ContentModifier<RadioConfiguration> | undefined)
            this.getPeer()?.setContentModifierAttribute(value_casted)
            return this
        }
        return this
    }
    public _onChangeEvent_checked(callback_: ((checked: boolean | undefined) => void)): void {
        if (this.checkPriority("_onChangeEvent_checked")) {
            const callback__casted = callback_ as (((checked: boolean | undefined) => void))
            this.getPeer()?.set_onChangeEvent_checkedAttribute(callback__casted)
            return
        }
        return
    }
    public attributeModifier(value: AttributeModifier<RadioAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withRadioStyle(receiver: RadioAttribute, modifier: AttributeModifier<RadioAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkRadioStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("Radio")
// export function Radio(
//     options: RadioOptions,
//     @memo
//     content_?: () => void,
// ): RadioAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function Radio(
    @memo
    style: ((attributes: RadioAttribute) => void) | undefined,
    options: RadioOptions,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkRadioComponent>((): ArkRadioComponent => {
        return new ArkRadioComponent()
    })
    NodeAttach<ArkRadioPeer>((): ArkRadioPeer => ArkRadioPeer.create(receiver), (_: ArkRadioPeer): void => {
        receiver.setRadioOptions(options)
        style?.(receiver)
        withRadioStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkRadioSet extends ArkCommonMethodSet implements RadioAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _checked_flag?: boolean
    _checked0_value?: boolean | undefined
    _onChange_flag?: boolean
    _onChange0_value?: OnRadioChangeCallback | undefined
    _radioStyle_flag?: boolean
    _radioStyle0_value?: RadioStyle | undefined
    _contentModifier_flag?: boolean
    _contentModifier0_value?: ContentModifier<RadioConfiguration> | undefined
    __onChangeEvent_checked_flag?: boolean
    __onChangeEvent_checked0_value?: ((checked: boolean | undefined) => void)
    applyModifierPatch(component: RadioAttribute): void {
        if (this._checked_flag)
            component.checked((this._checked0_value as boolean | undefined))
        if (this._onChange_flag)
            component.onChange((this._onChange0_value as OnRadioChangeCallback | undefined))
        if (this._radioStyle_flag)
            component.radioStyle((this._radioStyle0_value as RadioStyle | undefined))
        if (this._contentModifier_flag)
            component.contentModifier((this._contentModifier0_value as ContentModifier<RadioConfiguration> | undefined))
    }
    public checked(value: boolean | undefined): this {
        this._checked_flag = true
        this._checked0_value = value
        return this
    }
    public onChange(value: OnRadioChangeCallback | undefined): this {
        this._onChange_flag = true
        this._onChange0_value = value
        return this
    }
    public radioStyle(value: RadioStyle | undefined): this {
        this._radioStyle_flag = true
        this._radioStyle0_value = value
        return this
    }
    public contentModifier(value: ContentModifier<RadioConfiguration> | undefined): this {
        this._contentModifier_flag = true
        this._contentModifier0_value = value
        return this
    }
    public _onChangeEvent_checked(callback_: ((checked: boolean | undefined) => void)): void {
    }
    public attributeModifier(value: AttributeModifier<RadioAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class RadioConfiguration_serializer {
    public static write(buffer: SerializerBase, value: RadioConfiguration): void {
        let valueSerializer : SerializerBase = buffer
        const value_enabled  = value.enabled
        valueSerializer.writeBoolean(value_enabled)
        const value_contentModifier  = value.contentModifier
        valueSerializer.holdAndWriteObject(value_contentModifier)
        const value_value  = value.value
        valueSerializer.writeString(value_value)
        const value_checked  = value.checked
        valueSerializer.writeBoolean(value_checked)
        const value_triggerChange  = value.triggerChange
        valueSerializer.holdAndWriteCallback(value_triggerChange)
    }
    public static read(buffer: DeserializerBase): RadioConfiguration {
        let valueDeserializer : DeserializerBase = buffer
        const enabled_result : boolean = valueDeserializer.readBoolean()
        const contentModifier_result : ContentModifier<RadioConfiguration> = (valueDeserializer.readObject() as ContentModifier<RadioConfiguration>)
        const value_result : string = (valueDeserializer.readString() as string)
        const checked_result : boolean = valueDeserializer.readBoolean()
        const triggerChange_buf_resource : CallbackResource = valueDeserializer.readCallbackResource()
        const triggerChange_buf_call : KPointer = valueDeserializer.readPointer()
        const triggerChange_buf_callSync : KPointer = valueDeserializer.readPointer()
        const triggerChange_result : ((value0: boolean) => void) = (value0: boolean):void => { 
    const triggerChange_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    triggerChange_buf_argsSerializer.writeInt32(triggerChange_buf_resource.resourceId);
    triggerChange_buf_argsSerializer.writePointer(triggerChange_buf_call);
    triggerChange_buf_argsSerializer.writePointer(triggerChange_buf_callSync);
    triggerChange_buf_argsSerializer.writeBoolean(value0);
    InteropNativeModule._CallCallback(313269291, triggerChange_buf_argsSerializer.asBuffer(), triggerChange_buf_argsSerializer.length());
    triggerChange_buf_argsSerializer.release();
    return; }
        let value : RadioConfiguration = ({enabled: enabled_result, contentModifier: contentModifier_result, value: value_result, checked: checked_result, triggerChange: triggerChange_result} as RadioConfiguration)
        return value
    }
}
export class RadioOptions_serializer {
    public static write(buffer: SerializerBase, value: RadioOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_group  = value.group
        valueSerializer.writeString(value_group)
        const value_value  = value.value
        valueSerializer.writeString(value_value)
        const value_indicatorType  = value.indicatorType
        let value_indicatorType_type : int32 = RuntimeType.UNDEFINED
        value_indicatorType_type = runtimeType(value_indicatorType)
        valueSerializer.writeInt8((value_indicatorType_type).toChar())
        if ((value_indicatorType_type) != (RuntimeType.UNDEFINED)) {
            const value_indicatorType_value  = (value_indicatorType as RadioIndicatorType)
            valueSerializer.writeInt32(TypeChecker.RadioIndicatorType_ToNumeric(value_indicatorType_value))
        }
        const value_indicatorBuilder  = value.indicatorBuilder
        let value_indicatorBuilder_type : int32 = RuntimeType.UNDEFINED
        value_indicatorBuilder_type = runtimeType(value_indicatorBuilder)
        valueSerializer.writeInt8((value_indicatorBuilder_type).toChar())
        if ((value_indicatorBuilder_type) != (RuntimeType.UNDEFINED)) {
            const value_indicatorBuilder_value  = value_indicatorBuilder!
            valueSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value_indicatorBuilder_value))
        }
    }
    public static read(buffer: DeserializerBase): RadioOptions {
        let valueDeserializer : DeserializerBase = buffer
        const group_result : string = (valueDeserializer.readString() as string)
        const value_result : string = (valueDeserializer.readString() as string)
        const indicatorType_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let indicatorType_buf : RadioIndicatorType | undefined
        if ((indicatorType_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            indicatorType_buf = TypeChecker.RadioIndicatorType_FromNumeric(valueDeserializer.readInt32())
        }
        const indicatorType_result : RadioIndicatorType | undefined = indicatorType_buf
        const indicatorBuilder_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let indicatorBuilder_buf : CustomBuilder | undefined
        if ((indicatorBuilder_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const indicatorBuilder_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const indicatorBuilder_buf__call : KPointer = valueDeserializer.readPointer()
            const indicatorBuilder_buf__callSync : KPointer = valueDeserializer.readPointer()
            indicatorBuilder_buf = ():void => { 
    const indicatorBuilder_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    indicatorBuilder_buf__argsSerializer.writeInt32(indicatorBuilder_buf__resource.resourceId);
    indicatorBuilder_buf__argsSerializer.writePointer(indicatorBuilder_buf__call);
    indicatorBuilder_buf__argsSerializer.writePointer(indicatorBuilder_buf__callSync);
    InteropNativeModule._CallCallback(737226752, indicatorBuilder_buf__argsSerializer.asBuffer(), indicatorBuilder_buf__argsSerializer.length());
    indicatorBuilder_buf__argsSerializer.release();
    return; }
        }
        const indicatorBuilder_result : CustomBuilder | undefined = indicatorBuilder_buf
        let value : RadioOptions = ({group: group_result, value: value_result, indicatorType: indicatorType_result, indicatorBuilder: indicatorBuilder_result} as RadioOptions)
        return value
    }
}
export class RadioStyle_serializer {
    public static write(buffer: SerializerBase, value: RadioStyle): void {
        let valueSerializer : SerializerBase = buffer
        const value_checkedBackgroundColor  = value.checkedBackgroundColor
        let value_checkedBackgroundColor_type : int32 = RuntimeType.UNDEFINED
        value_checkedBackgroundColor_type = runtimeType(value_checkedBackgroundColor)
        valueSerializer.writeInt8((value_checkedBackgroundColor_type).toChar())
        if ((value_checkedBackgroundColor_type) != (RuntimeType.UNDEFINED)) {
            const value_checkedBackgroundColor_value  = value_checkedBackgroundColor!
            let value_checkedBackgroundColor_value_type : int32 = RuntimeType.UNDEFINED
            value_checkedBackgroundColor_value_type = runtimeType(value_checkedBackgroundColor_value)
            if (TypeChecker.isColor(value_checkedBackgroundColor_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value_checkedBackgroundColor_value_0  = value_checkedBackgroundColor_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_checkedBackgroundColor_value_0))
            }
            else if (RuntimeType.NUMBER == value_checkedBackgroundColor_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_checkedBackgroundColor_value_1  = value_checkedBackgroundColor_value as number
                valueSerializer.writeNumber(value_checkedBackgroundColor_value_1)
            }
            else if (RuntimeType.STRING == value_checkedBackgroundColor_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_checkedBackgroundColor_value_2  = value_checkedBackgroundColor_value as string
                valueSerializer.writeString(value_checkedBackgroundColor_value_2)
            }
            else if (RuntimeType.OBJECT == value_checkedBackgroundColor_value_type) {
                valueSerializer.writeInt8((3).toChar())
                const value_checkedBackgroundColor_value_3  = value_checkedBackgroundColor_value as Resource
                Resource_serializer.write(valueSerializer, value_checkedBackgroundColor_value_3)
            }
        }
        const value_uncheckedBorderColor  = value.uncheckedBorderColor
        let value_uncheckedBorderColor_type : int32 = RuntimeType.UNDEFINED
        value_uncheckedBorderColor_type = runtimeType(value_uncheckedBorderColor)
        valueSerializer.writeInt8((value_uncheckedBorderColor_type).toChar())
        if ((value_uncheckedBorderColor_type) != (RuntimeType.UNDEFINED)) {
            const value_uncheckedBorderColor_value  = value_uncheckedBorderColor!
            let value_uncheckedBorderColor_value_type : int32 = RuntimeType.UNDEFINED
            value_uncheckedBorderColor_value_type = runtimeType(value_uncheckedBorderColor_value)
            if (TypeChecker.isColor(value_uncheckedBorderColor_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value_uncheckedBorderColor_value_0  = value_uncheckedBorderColor_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_uncheckedBorderColor_value_0))
            }
            else if (RuntimeType.NUMBER == value_uncheckedBorderColor_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_uncheckedBorderColor_value_1  = value_uncheckedBorderColor_value as number
                valueSerializer.writeNumber(value_uncheckedBorderColor_value_1)
            }
            else if (RuntimeType.STRING == value_uncheckedBorderColor_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_uncheckedBorderColor_value_2  = value_uncheckedBorderColor_value as string
                valueSerializer.writeString(value_uncheckedBorderColor_value_2)
            }
            else if (RuntimeType.OBJECT == value_uncheckedBorderColor_value_type) {
                valueSerializer.writeInt8((3).toChar())
                const value_uncheckedBorderColor_value_3  = value_uncheckedBorderColor_value as Resource
                Resource_serializer.write(valueSerializer, value_uncheckedBorderColor_value_3)
            }
        }
        const value_indicatorColor  = value.indicatorColor
        let value_indicatorColor_type : int32 = RuntimeType.UNDEFINED
        value_indicatorColor_type = runtimeType(value_indicatorColor)
        valueSerializer.writeInt8((value_indicatorColor_type).toChar())
        if ((value_indicatorColor_type) != (RuntimeType.UNDEFINED)) {
            const value_indicatorColor_value  = value_indicatorColor!
            let value_indicatorColor_value_type : int32 = RuntimeType.UNDEFINED
            value_indicatorColor_value_type = runtimeType(value_indicatorColor_value)
            if (TypeChecker.isColor(value_indicatorColor_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value_indicatorColor_value_0  = value_indicatorColor_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_indicatorColor_value_0))
            }
            else if (RuntimeType.NUMBER == value_indicatorColor_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_indicatorColor_value_1  = value_indicatorColor_value as number
                valueSerializer.writeNumber(value_indicatorColor_value_1)
            }
            else if (RuntimeType.STRING == value_indicatorColor_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_indicatorColor_value_2  = value_indicatorColor_value as string
                valueSerializer.writeString(value_indicatorColor_value_2)
            }
            else if (RuntimeType.OBJECT == value_indicatorColor_value_type) {
                valueSerializer.writeInt8((3).toChar())
                const value_indicatorColor_value_3  = value_indicatorColor_value as Resource
                Resource_serializer.write(valueSerializer, value_indicatorColor_value_3)
            }
        }
    }
    public static read(buffer: DeserializerBase): RadioStyle {
        let valueDeserializer : DeserializerBase = buffer
        const checkedBackgroundColor_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let checkedBackgroundColor_buf : ResourceColor | undefined
        if ((checkedBackgroundColor_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const checkedBackgroundColor_buf__selector : int32 = valueDeserializer.readInt8()
            let checkedBackgroundColor_buf_ : Color | number | string | Resource | undefined
            if (checkedBackgroundColor_buf__selector == (0).toChar()) {
                checkedBackgroundColor_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (checkedBackgroundColor_buf__selector == (1).toChar()) {
                checkedBackgroundColor_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (checkedBackgroundColor_buf__selector == (2).toChar()) {
                checkedBackgroundColor_buf_ = (valueDeserializer.readString() as string)
            }
            else if (checkedBackgroundColor_buf__selector == (3).toChar()) {
                checkedBackgroundColor_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for checkedBackgroundColor_buf_ has to be chosen through deserialisation.")
            }
            checkedBackgroundColor_buf = (checkedBackgroundColor_buf_ as Color | number | string | Resource)
        }
        const checkedBackgroundColor_result : ResourceColor | undefined = checkedBackgroundColor_buf
        const uncheckedBorderColor_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let uncheckedBorderColor_buf : ResourceColor | undefined
        if ((uncheckedBorderColor_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const uncheckedBorderColor_buf__selector : int32 = valueDeserializer.readInt8()
            let uncheckedBorderColor_buf_ : Color | number | string | Resource | undefined
            if (uncheckedBorderColor_buf__selector == (0).toChar()) {
                uncheckedBorderColor_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (uncheckedBorderColor_buf__selector == (1).toChar()) {
                uncheckedBorderColor_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (uncheckedBorderColor_buf__selector == (2).toChar()) {
                uncheckedBorderColor_buf_ = (valueDeserializer.readString() as string)
            }
            else if (uncheckedBorderColor_buf__selector == (3).toChar()) {
                uncheckedBorderColor_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for uncheckedBorderColor_buf_ has to be chosen through deserialisation.")
            }
            uncheckedBorderColor_buf = (uncheckedBorderColor_buf_ as Color | number | string | Resource)
        }
        const uncheckedBorderColor_result : ResourceColor | undefined = uncheckedBorderColor_buf
        const indicatorColor_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let indicatorColor_buf : ResourceColor | undefined
        if ((indicatorColor_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const indicatorColor_buf__selector : int32 = valueDeserializer.readInt8()
            let indicatorColor_buf_ : Color | number | string | Resource | undefined
            if (indicatorColor_buf__selector == (0).toChar()) {
                indicatorColor_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (indicatorColor_buf__selector == (1).toChar()) {
                indicatorColor_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (indicatorColor_buf__selector == (2).toChar()) {
                indicatorColor_buf_ = (valueDeserializer.readString() as string)
            }
            else if (indicatorColor_buf__selector == (3).toChar()) {
                indicatorColor_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for indicatorColor_buf_ has to be chosen through deserialisation.")
            }
            indicatorColor_buf = (indicatorColor_buf_ as Color | number | string | Resource)
        }
        const indicatorColor_result : ResourceColor | undefined = indicatorColor_buf
        let value : RadioStyle = ({checkedBackgroundColor: checkedBackgroundColor_result, uncheckedBorderColor: uncheckedBorderColor_result, indicatorColor: indicatorColor_result} as RadioStyle)
        return value
    }
}
