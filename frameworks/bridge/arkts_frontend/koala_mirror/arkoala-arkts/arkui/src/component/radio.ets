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
import { Bindable_Boolean_serializer, ArkCommonMethodPeer, CommonMethod, Bindable, CommonConfiguration, ArkCommonMethodComponent, ArkCommonMethodStyle, CommonMethodModifier } from "./common"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
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
import { AttributeUpdaterFlag } from "./../generated/AttributeUpdater"
export class ArkRadioPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkRadioPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Radio_construct(peerId, flags)
        const _peer  = new ArkRadioPeer(_peerPtr, peerId, 'Radio', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setRadioOptionsAttribute(options: RadioOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        RadioOptions_serializer.write(thisSerializer, options)
        ArkUIGeneratedNativeModule._RadioInterface_setRadioOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCheckedAttribute(value: boolean | Bindable<boolean> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof boolean) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as boolean
                thisSerializer.writeBoolean(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof Bindable<boolean>) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as Bindable<boolean>
                Bindable_Boolean_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RadioAttribute_setChecked(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnChangeAttribute(value: OnRadioChangeCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RadioAttribute_setOnChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setRadioStyleAttribute(value: RadioStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            RadioStyle_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RadioAttribute_setRadioStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
    checked(value: boolean | Bindable<boolean> | undefined): this {
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
    attributeModifier(value: AttributeModifier<RadioAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkRadioStyle extends ArkCommonMethodStyle implements RadioAttribute {
    checked_value?: boolean | Bindable<boolean> | undefined
    onChange_value?: OnRadioChangeCallback | undefined
    radioStyle_value?: RadioStyle | undefined
    contentModifier_value?: ContentModifier<RadioConfiguration> | undefined
    attributeModifier_value?: AttributeModifier<RadioAttribute> | AttributeModifier<CommonMethod> | undefined
    public checked(value: boolean | Bindable<boolean> | undefined): this {
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
    public attributeModifier(value: AttributeModifier<RadioAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
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
    public checked(value: boolean | Bindable<boolean> | undefined): this {
        if (this.checkPriority("checked")) {
            const value_casted = value as (boolean | Bindable<boolean> | undefined)
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
            hookRadioContentModifier(this, value)
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<RadioAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

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
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class RadioModifier extends CommonMethodModifier implements RadioAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _checked_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _checked_0_0value?: boolean | Bindable<boolean> | undefined
    _onChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onChange_0_0value?: OnRadioChangeCallback | undefined
    _radioStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _radioStyle_0_0value?: RadioStyle | undefined
    applyModifierPatch(peer: ArkRadioPeer): void {
        super.applyModifierPatch(peer)
        if (this._checked_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._checked_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setCheckedAttribute((this._checked_0_0value as boolean | Bindable<boolean> | undefined));
                    this._checked_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._checked_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._checked_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setCheckedAttribute((undefined as boolean | Bindable<boolean> | undefined));
                }
            }
        }
        if (this._onChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnChangeAttribute((this._onChange_0_0value as OnRadioChangeCallback | undefined));
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnChangeAttribute((undefined as OnRadioChangeCallback | undefined));
                }
            }
        }
        if (this._radioStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._radioStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setRadioStyleAttribute((this._radioStyle_0_0value as RadioStyle | undefined));
                    this._radioStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._radioStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._radioStyle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setRadioStyleAttribute((undefined as RadioStyle | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: RadioModifier): void {
        super.mergeModifier(modifier)
        if (modifier._checked_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._checked_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.checked(modifier._checked_0_0value);
                    break;
                }
                default: {
                    this.checked((undefined as boolean | Bindable<boolean> | undefined));
                }
            }
        }
        if (modifier._onChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onChange(modifier._onChange_0_0value);
                    break;
                }
                default: {
                    this.onChange((undefined as OnRadioChangeCallback | undefined));
                }
            }
        }
        if (modifier._radioStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._radioStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.radioStyle(modifier._radioStyle_0_0value);
                    break;
                }
                default: {
                    this.radioStyle((undefined as RadioStyle | undefined));
                }
            }
        }
    }
    checked(value: boolean | Bindable<boolean> | undefined): this {
        if (((this._checked_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._checked_0_flag = AttributeUpdaterFlag.UPDATE
            this._checked_0_0value = value
        } else
        {
            this._checked_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onChange(value: OnRadioChangeCallback | undefined): this {
        if (((this._onChange_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onChange_0_flag = AttributeUpdaterFlag.UPDATE
            this._onChange_0_0value = value
        } else
        {
            this._onChange_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    radioStyle(value: RadioStyle | undefined): this {
        if (((this._radioStyle_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._radioStyle_0_flag = AttributeUpdaterFlag.UPDATE
            this._radioStyle_0_0value = value
        } else
        {
            this._radioStyle_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<RadioAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class RadioConfiguration_serializer {
    public static write(buffer: SerializerBase, value: RadioConfiguration): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForEnabled  = value.enabled
        valueSerializer.writeBoolean(valueHolderForEnabled)
        const valueHolderForContentModifier  = value.contentModifier
        valueSerializer.holdAndWriteObject(valueHolderForContentModifier)
        const valueHolderForValue  = value.value
        valueSerializer.writeString(valueHolderForValue)
        const valueHolderForChecked  = value.checked
        valueSerializer.writeBoolean(valueHolderForChecked)
        const valueHolderForTriggerChange  = value.triggerChange
        valueSerializer.holdAndWriteCallback(valueHolderForTriggerChange)
    }
    public static read(buffer: DeserializerBase): RadioConfiguration {
        let valueDeserializer : DeserializerBase = buffer
        const enabledTmpResult : boolean = valueDeserializer.readBoolean()
        const contentModifierTmpResult : ContentModifier<RadioConfiguration> = (valueDeserializer.readObject() as ContentModifier<RadioConfiguration>)
        const valueTmpResult : string = (valueDeserializer.readString() as string)
        const checkedTmpResult : boolean = valueDeserializer.readBoolean()
        const triggerChangeTmpBufBufResource : CallbackResource = valueDeserializer.readCallbackResource()
        const triggerChangeTmpBufBufCall : KPointer = valueDeserializer.readPointer()
        const triggerChangeTmpBufBufCallSync : KPointer = valueDeserializer.readPointer()
        const triggerChangeTmpResult : ((value0: boolean) => void) = (value0: boolean):void => {
            const triggerChangeTmpBufBufArgsSerializer : SerializerBase = SerializerBase.hold();
            triggerChangeTmpBufBufArgsSerializer.writeInt32(triggerChangeTmpBufBufResource.resourceId);
            triggerChangeTmpBufBufArgsSerializer.writePointer(triggerChangeTmpBufBufCall);
            triggerChangeTmpBufBufArgsSerializer.writePointer(triggerChangeTmpBufBufCallSync);
            triggerChangeTmpBufBufArgsSerializer.writeBoolean(value0);
            InteropNativeModule._CallCallback(313269291, triggerChangeTmpBufBufArgsSerializer.asBuffer(), triggerChangeTmpBufBufArgsSerializer.length());
            triggerChangeTmpBufBufArgsSerializer.release();
            return;
        }
        let value : RadioConfiguration = ({enabled: enabledTmpResult, contentModifier: contentModifierTmpResult, value: valueTmpResult, checked: checkedTmpResult, triggerChange: triggerChangeTmpResult} as RadioConfiguration)
        return value
    }
}
export class RadioOptions_serializer {
    public static write(buffer: SerializerBase, value: RadioOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForGroup  = value.group
        valueSerializer.writeString(valueHolderForGroup)
        const valueHolderForValue  = value.value
        valueSerializer.writeString(valueHolderForValue)
        const valueHolderForIndicatorType  = value.indicatorType
        if (valueHolderForIndicatorType !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForIndicatorTypeTmpValue  = (valueHolderForIndicatorType as RadioIndicatorType)
            valueSerializer.writeInt32(TypeChecker.RadioIndicatorType_ToNumeric(valueHolderForIndicatorTypeTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForIndicatorBuilder  = value.indicatorBuilder
        if (valueHolderForIndicatorBuilder !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForIndicatorBuilderTmpValue  = valueHolderForIndicatorBuilder!
            valueSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(valueHolderForIndicatorBuilderTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): RadioOptions {
        let valueDeserializer : DeserializerBase = buffer
        const groupTmpResult : string = (valueDeserializer.readString() as string)
        const valueTmpResult : string = (valueDeserializer.readString() as string)
        const indicatorTypeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let indicatorTypeTmpBuf : RadioIndicatorType | undefined
        if ((indicatorTypeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            indicatorTypeTmpBuf = TypeChecker.RadioIndicatorType_FromNumeric(valueDeserializer.readInt32())
        }
        const indicatorTypeTmpResult : RadioIndicatorType | undefined = indicatorTypeTmpBuf
        const indicatorBuilderTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let indicatorBuilderTmpBuf : CustomBuilder | undefined
        if ((indicatorBuilderTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const indicatorBuilderTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const indicatorBuilderTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const indicatorBuilderTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            indicatorBuilderTmpBuf = ():void => {
                const indicatorBuilderTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                indicatorBuilderTmpBuf_BufArgsSerializer.writeInt32(indicatorBuilderTmpBuf_BufResource.resourceId);
                indicatorBuilderTmpBuf_BufArgsSerializer.writePointer(indicatorBuilderTmpBuf_BufCall);
                indicatorBuilderTmpBuf_BufArgsSerializer.writePointer(indicatorBuilderTmpBuf_BufCallSync);
                InteropNativeModule._CallCallback(737226752, indicatorBuilderTmpBuf_BufArgsSerializer.asBuffer(), indicatorBuilderTmpBuf_BufArgsSerializer.length());
                indicatorBuilderTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const indicatorBuilderTmpResult : CustomBuilder | undefined = indicatorBuilderTmpBuf
        let value : RadioOptions = ({group: groupTmpResult, value: valueTmpResult, indicatorType: indicatorTypeTmpResult, indicatorBuilder: indicatorBuilderTmpResult} as RadioOptions)
        return value
    }
}
export class RadioStyle_serializer {
    public static write(buffer: SerializerBase, value: RadioStyle): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForCheckedBackgroundColor  = value.checkedBackgroundColor
        if (valueHolderForCheckedBackgroundColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForCheckedBackgroundColorTmpValue  = valueHolderForCheckedBackgroundColor!
            if (valueHolderForCheckedBackgroundColorTmpValue instanceof Color) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForCheckedBackgroundColorTmpValueForIdx0  = valueHolderForCheckedBackgroundColorTmpValue as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForCheckedBackgroundColorTmpValueForIdx0))
            } else if (valueHolderForCheckedBackgroundColorTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForCheckedBackgroundColorTmpValueForIdx1  = valueHolderForCheckedBackgroundColorTmpValue as number
                valueSerializer.writeNumber(valueHolderForCheckedBackgroundColorTmpValueForIdx1)
            } else if (valueHolderForCheckedBackgroundColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toChar())
                const valueHolderForCheckedBackgroundColorTmpValueForIdx2  = valueHolderForCheckedBackgroundColorTmpValue as string
                valueSerializer.writeString(valueHolderForCheckedBackgroundColorTmpValueForIdx2)
            } else if (valueHolderForCheckedBackgroundColorTmpValue instanceof Resource) {
                valueSerializer.writeInt8((3).toChar())
                const valueHolderForCheckedBackgroundColorTmpValueForIdx3  = valueHolderForCheckedBackgroundColorTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForCheckedBackgroundColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForUncheckedBorderColor  = value.uncheckedBorderColor
        if (valueHolderForUncheckedBorderColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForUncheckedBorderColorTmpValue  = valueHolderForUncheckedBorderColor!
            if (valueHolderForUncheckedBorderColorTmpValue instanceof Color) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForUncheckedBorderColorTmpValueForIdx0  = valueHolderForUncheckedBorderColorTmpValue as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForUncheckedBorderColorTmpValueForIdx0))
            } else if (valueHolderForUncheckedBorderColorTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForUncheckedBorderColorTmpValueForIdx1  = valueHolderForUncheckedBorderColorTmpValue as number
                valueSerializer.writeNumber(valueHolderForUncheckedBorderColorTmpValueForIdx1)
            } else if (valueHolderForUncheckedBorderColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toChar())
                const valueHolderForUncheckedBorderColorTmpValueForIdx2  = valueHolderForUncheckedBorderColorTmpValue as string
                valueSerializer.writeString(valueHolderForUncheckedBorderColorTmpValueForIdx2)
            } else if (valueHolderForUncheckedBorderColorTmpValue instanceof Resource) {
                valueSerializer.writeInt8((3).toChar())
                const valueHolderForUncheckedBorderColorTmpValueForIdx3  = valueHolderForUncheckedBorderColorTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForUncheckedBorderColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForIndicatorColor  = value.indicatorColor
        if (valueHolderForIndicatorColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForIndicatorColorTmpValue  = valueHolderForIndicatorColor!
            if (valueHolderForIndicatorColorTmpValue instanceof Color) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForIndicatorColorTmpValueForIdx0  = valueHolderForIndicatorColorTmpValue as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForIndicatorColorTmpValueForIdx0))
            } else if (valueHolderForIndicatorColorTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForIndicatorColorTmpValueForIdx1  = valueHolderForIndicatorColorTmpValue as number
                valueSerializer.writeNumber(valueHolderForIndicatorColorTmpValueForIdx1)
            } else if (valueHolderForIndicatorColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toChar())
                const valueHolderForIndicatorColorTmpValueForIdx2  = valueHolderForIndicatorColorTmpValue as string
                valueSerializer.writeString(valueHolderForIndicatorColorTmpValueForIdx2)
            } else if (valueHolderForIndicatorColorTmpValue instanceof Resource) {
                valueSerializer.writeInt8((3).toChar())
                const valueHolderForIndicatorColorTmpValueForIdx3  = valueHolderForIndicatorColorTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForIndicatorColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): RadioStyle {
        let valueDeserializer : DeserializerBase = buffer
        const checkedBackgroundColorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let checkedBackgroundColorTmpBuf : ResourceColor | undefined
        if ((checkedBackgroundColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const checkedBackgroundColorTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let checkedBackgroundColorTmpBuf_ : Color | number | string | Resource | undefined
            if (checkedBackgroundColorTmpBuf_UnionSelector == (0).toChar()) {
                checkedBackgroundColorTmpBuf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            } else if (checkedBackgroundColorTmpBuf_UnionSelector == (1).toChar()) {
                checkedBackgroundColorTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (checkedBackgroundColorTmpBuf_UnionSelector == (2).toChar()) {
                checkedBackgroundColorTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (checkedBackgroundColorTmpBuf_UnionSelector == (3).toChar()) {
                checkedBackgroundColorTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for checkedBackgroundColorTmpBuf_ has to be chosen through deserialisation.")
            }
            checkedBackgroundColorTmpBuf = (checkedBackgroundColorTmpBuf_ as Color | number | string | Resource)
        }
        const checkedBackgroundColorTmpResult : ResourceColor | undefined = checkedBackgroundColorTmpBuf
        const uncheckedBorderColorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let uncheckedBorderColorTmpBuf : ResourceColor | undefined
        if ((uncheckedBorderColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const uncheckedBorderColorTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let uncheckedBorderColorTmpBuf_ : Color | number | string | Resource | undefined
            if (uncheckedBorderColorTmpBuf_UnionSelector == (0).toChar()) {
                uncheckedBorderColorTmpBuf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            } else if (uncheckedBorderColorTmpBuf_UnionSelector == (1).toChar()) {
                uncheckedBorderColorTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (uncheckedBorderColorTmpBuf_UnionSelector == (2).toChar()) {
                uncheckedBorderColorTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (uncheckedBorderColorTmpBuf_UnionSelector == (3).toChar()) {
                uncheckedBorderColorTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for uncheckedBorderColorTmpBuf_ has to be chosen through deserialisation.")
            }
            uncheckedBorderColorTmpBuf = (uncheckedBorderColorTmpBuf_ as Color | number | string | Resource)
        }
        const uncheckedBorderColorTmpResult : ResourceColor | undefined = uncheckedBorderColorTmpBuf
        const indicatorColorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let indicatorColorTmpBuf : ResourceColor | undefined
        if ((indicatorColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const indicatorColorTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let indicatorColorTmpBuf_ : Color | number | string | Resource | undefined
            if (indicatorColorTmpBuf_UnionSelector == (0).toChar()) {
                indicatorColorTmpBuf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            } else if (indicatorColorTmpBuf_UnionSelector == (1).toChar()) {
                indicatorColorTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (indicatorColorTmpBuf_UnionSelector == (2).toChar()) {
                indicatorColorTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (indicatorColorTmpBuf_UnionSelector == (3).toChar()) {
                indicatorColorTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for indicatorColorTmpBuf_ has to be chosen through deserialisation.")
            }
            indicatorColorTmpBuf = (indicatorColorTmpBuf_ as Color | number | string | Resource)
        }
        const indicatorColorTmpResult : ResourceColor | undefined = indicatorColorTmpBuf
        let value : RadioStyle = ({checkedBackgroundColor: checkedBackgroundColorTmpResult, uncheckedBorderColor: uncheckedBorderColorTmpResult, indicatorColor: indicatorColorTmpResult} as RadioStyle)
        return value
    }
}
