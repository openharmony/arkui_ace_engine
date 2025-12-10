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

import { ArkThemeScopeManager } from '#arktheme'
import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer, resourceFinalizerRegister, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from '@koalaui/interop'
import { Bindable_Boolean_serializer, ArkCommonMethodPeer, CommonMethod, Bindable, CommonConfiguration, Callback as arkui_component_common_Callback, ArkCommonMethodComponent } from './common'
import { int32, int64, float32, unsafeCast } from '@koalaui/common'
import { ComponentBase } from './../ComponentBase'
import { PeerNode } from './../PeerNode'
import { ArkUIGeneratedNativeModule } from '#components'
import { ContentModifier, AttributeModifier, hookRadioContentModifier, hookRadioAttributeModifier, AttributeUpdater } from '#handwritten'
import { CallbackKind } from './../framework/peers/CallbackKind'
import { CallbackTransformer } from './../CallbackTransformer'
import { memo, memo_stable, memo_skip } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { CustomBuilder } from './builder'
import { ResourceColor, Resource as arkui_component_units_Resource } from './units'
import { Color as arkui_component_enums_Color } from './enums'
import { Resource as global_resource_Resource } from 'global.resource'
import { RadioModifier } from './../RadioModifier'
import { NodeAttach, remember } from '@koalaui/runtime'
import { ModifierStateManager } from './../CommonModifier'
import { global_resource_Resource_serializer } from './../framework/resource'
export class ArkRadioPeer extends ArkCommonMethodPeer {
    attributeSet?: RadioModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
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
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
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
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as boolean
                thisSerializer.writeBoolean(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof Bindable) {
                thisSerializer.writeInt8((1).toByte())
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
    setRadioOptions(options: RadioOptions): this {
        throw new Error('Unimplemented method setRadioOptions')
    }
    checked(value: boolean | Bindable<boolean> | undefined): this {
        throw new Error('Unimplemented method checked')
    }
    onChange(value: OnRadioChangeCallback | undefined): this {
        throw new Error('Unimplemented method onChange')
    }
    radioStyle(value: RadioStyle | undefined): this {
        throw new Error('Unimplemented method radioStyle')
    }
    contentModifier(value: ContentModifier<RadioConfiguration> | undefined): this {
        throw new Error('Unimplemented method contentModifier')
    }
    attributeModifier(value: AttributeModifier<RadioAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}
export interface RadioConfiguration extends CommonConfiguration<RadioConfiguration> {
    value: string;
    checked: boolean;
    triggerChange: arkui_component_common_Callback<boolean, void>;
}

export class ArkRadioComponent extends ArkCommonMethodComponent implements RadioAttribute {
    getPeer(): ArkRadioPeer {
        return (this.peer as ArkRadioPeer)
    }
    public setRadioOptions(options: RadioOptions): this {
        if (this.checkPriority('setRadioOptions')) {
            const options_casted = options as (RadioOptions)
            this.getPeer()?.setRadioOptionsAttribute(options_casted)
            this.applyOptionsFinish('RadioAttribute');
            return this
        }
        return this
    }
    public checked(value: boolean | Bindable<boolean> | undefined): this {
        if (this.checkPriority('checked')) {
            const value_casted = value as (boolean | Bindable<boolean> | undefined)
            this.getPeer()?.setCheckedAttribute(value_casted)
            return this
        }
        return this
    }
    public onChange(value: OnRadioChangeCallback | undefined): this {
        if (this.checkPriority('onChange')) {
            const value_casted = value as (OnRadioChangeCallback | undefined)
            this.getPeer()?.setOnChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public radioStyle(value: RadioStyle | undefined): this {
        if (this.checkPriority('radioStyle')) {
            const value_casted = value as (RadioStyle | undefined)
            this.getPeer()?.setRadioStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public contentModifier(value: ContentModifier<RadioConfiguration> | undefined): this {
        if (this.checkPriority('contentModifier')) {
            hookRadioContentModifier(this, value)
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<RadioAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookRadioAttributeModifier(this, value);
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
export function RadioImpl(
    @memo @memo_skip
    style: ((attributes: RadioAttribute) => void) | undefined,
    @memo @memo_skip
    content_?: () => void,
): void {
    const receiver = remember<ArkRadioComponent>((): ArkRadioComponent => {
        return new ArkRadioComponent()
    })
    NodeAttach<ArkRadioPeer>((): ArkRadioPeer => ArkRadioPeer.create(receiver), (_: ArkRadioPeer): void => {
        style?.(receiver)
        content_?.()
    })
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
        const triggerChangeTmpBufClosure  = (data: boolean):void => {
            const triggerChangeTmpBufBufArgsSerializer : SerializerBase = SerializerBase.hold();
            triggerChangeTmpBufBufArgsSerializer.writeInt32(triggerChangeTmpBufBufResource.resourceId);
            triggerChangeTmpBufBufArgsSerializer.writePointer(triggerChangeTmpBufBufCall);
            triggerChangeTmpBufBufArgsSerializer.writePointer(triggerChangeTmpBufBufCallSync);
            triggerChangeTmpBufBufArgsSerializer.writeBoolean(data);
            InteropNativeModule._CallCallbackSync(10, -1691789173, triggerChangeTmpBufBufArgsSerializer.asBuffer(), triggerChangeTmpBufBufArgsSerializer.length());
            triggerChangeTmpBufBufArgsSerializer.release();
            return;
        }
        resourceFinalizerRegister(triggerChangeTmpBufClosure, triggerChangeTmpBufBufResource)
        const triggerChangeTmpResult : arkui_component_common_Callback<boolean, void> = triggerChangeTmpBufClosure
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
            valueSerializer.writeInt32(valueHolderForIndicatorTypeTmpValue.valueOf())
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
        const indicatorTypeTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let indicatorTypeTmpBuf : RadioIndicatorType | undefined = undefined
        if ((indicatorTypeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            indicatorTypeTmpBuf = RadioIndicatorType.fromValue(valueDeserializer.readInt32())
        }
        const indicatorTypeTmpResult : RadioIndicatorType | undefined = indicatorTypeTmpBuf
        const indicatorBuilderTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let indicatorBuilderTmpBuf : CustomBuilder | undefined = undefined
        if ((indicatorBuilderTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const indicatorBuilderTmpBufOptBufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const indicatorBuilderTmpBufOptBufCall : KPointer = valueDeserializer.readPointer()
            const indicatorBuilderTmpBufOptBufCallSync : KPointer = valueDeserializer.readPointer()
            const indicatorBuilderTmpBufOptClosure  = ():void => {
                const indicatorBuilderTmpBufOptBufArgsSerializer : SerializerBase = SerializerBase.hold();
                indicatorBuilderTmpBufOptBufArgsSerializer.writeInt32(indicatorBuilderTmpBufOptBufResource.resourceId);
                indicatorBuilderTmpBufOptBufArgsSerializer.writePointer(indicatorBuilderTmpBufOptBufCall);
                indicatorBuilderTmpBufOptBufArgsSerializer.writePointer(indicatorBuilderTmpBufOptBufCallSync);
                InteropNativeModule._CallCallbackSync(10, -1834072896, indicatorBuilderTmpBufOptBufArgsSerializer.asBuffer(), indicatorBuilderTmpBufOptBufArgsSerializer.length());
                indicatorBuilderTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(indicatorBuilderTmpBufOptClosure, indicatorBuilderTmpBufOptBufResource)
            indicatorBuilderTmpBuf = indicatorBuilderTmpBufOptClosure
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
            if (valueHolderForCheckedBackgroundColorTmpValue instanceof arkui_component_enums_Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForCheckedBackgroundColorTmpValueForIdx0  = valueHolderForCheckedBackgroundColorTmpValue as arkui_component_enums_Color
                valueSerializer.writeInt32((valueHolderForCheckedBackgroundColorTmpValueForIdx0.getOrdinal()) % (12))
            } else if (valueHolderForCheckedBackgroundColorTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForCheckedBackgroundColorTmpValueForIdx1  = valueHolderForCheckedBackgroundColorTmpValue as int32
                valueSerializer.writeInt32(valueHolderForCheckedBackgroundColorTmpValueForIdx1)
            } else if (valueHolderForCheckedBackgroundColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForCheckedBackgroundColorTmpValueForIdx2  = valueHolderForCheckedBackgroundColorTmpValue as string
                valueSerializer.writeString(valueHolderForCheckedBackgroundColorTmpValueForIdx2)
            } else if (valueHolderForCheckedBackgroundColorTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForCheckedBackgroundColorTmpValueForIdx3  = valueHolderForCheckedBackgroundColorTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForCheckedBackgroundColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForUncheckedBorderColor  = value.uncheckedBorderColor
        if (valueHolderForUncheckedBorderColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForUncheckedBorderColorTmpValue  = valueHolderForUncheckedBorderColor!
            if (valueHolderForUncheckedBorderColorTmpValue instanceof arkui_component_enums_Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForUncheckedBorderColorTmpValueForIdx0  = valueHolderForUncheckedBorderColorTmpValue as arkui_component_enums_Color
                valueSerializer.writeInt32((valueHolderForUncheckedBorderColorTmpValueForIdx0.getOrdinal()) % (12))
            } else if (valueHolderForUncheckedBorderColorTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForUncheckedBorderColorTmpValueForIdx1  = valueHolderForUncheckedBorderColorTmpValue as int32
                valueSerializer.writeInt32(valueHolderForUncheckedBorderColorTmpValueForIdx1)
            } else if (valueHolderForUncheckedBorderColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForUncheckedBorderColorTmpValueForIdx2  = valueHolderForUncheckedBorderColorTmpValue as string
                valueSerializer.writeString(valueHolderForUncheckedBorderColorTmpValueForIdx2)
            } else if (valueHolderForUncheckedBorderColorTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForUncheckedBorderColorTmpValueForIdx3  = valueHolderForUncheckedBorderColorTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForUncheckedBorderColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForIndicatorColor  = value.indicatorColor
        if (valueHolderForIndicatorColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForIndicatorColorTmpValue  = valueHolderForIndicatorColor!
            if (valueHolderForIndicatorColorTmpValue instanceof arkui_component_enums_Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForIndicatorColorTmpValueForIdx0  = valueHolderForIndicatorColorTmpValue as arkui_component_enums_Color
                valueSerializer.writeInt32((valueHolderForIndicatorColorTmpValueForIdx0.getOrdinal()) % (12))
            } else if (valueHolderForIndicatorColorTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForIndicatorColorTmpValueForIdx1  = valueHolderForIndicatorColorTmpValue as int32
                valueSerializer.writeInt32(valueHolderForIndicatorColorTmpValueForIdx1)
            } else if (valueHolderForIndicatorColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForIndicatorColorTmpValueForIdx2  = valueHolderForIndicatorColorTmpValue as string
                valueSerializer.writeString(valueHolderForIndicatorColorTmpValueForIdx2)
            } else if (valueHolderForIndicatorColorTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForIndicatorColorTmpValueForIdx3  = valueHolderForIndicatorColorTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForIndicatorColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): RadioStyle {
        let valueDeserializer : DeserializerBase = buffer
        const checkedBackgroundColorTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let checkedBackgroundColorTmpBuf : ResourceColor | undefined = undefined
        if ((checkedBackgroundColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const checkedBackgroundColorTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let checkedBackgroundColorTmpBufOpt : arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined
            if (checkedBackgroundColorTmpBufOptUnionSelector == (0).toByte()) {
                checkedBackgroundColorTmpBufOpt = arkui_component_enums_Color.values()[valueDeserializer.readInt32()]
            } else if (checkedBackgroundColorTmpBufOptUnionSelector == (1).toByte()) {
                checkedBackgroundColorTmpBufOpt = valueDeserializer.readInt32()
            } else if (checkedBackgroundColorTmpBufOptUnionSelector == (2).toByte()) {
                checkedBackgroundColorTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (checkedBackgroundColorTmpBufOptUnionSelector == (3).toByte()) {
                checkedBackgroundColorTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for checkedBackgroundColorTmpBufOpt has to be chosen through deserialisation.')
            }
            checkedBackgroundColorTmpBuf = (checkedBackgroundColorTmpBufOpt as arkui_component_enums_Color | int32 | string | arkui_component_units_Resource)
        }
        const checkedBackgroundColorTmpResult : ResourceColor | undefined = checkedBackgroundColorTmpBuf
        const uncheckedBorderColorTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let uncheckedBorderColorTmpBuf : ResourceColor | undefined = undefined
        if ((uncheckedBorderColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const uncheckedBorderColorTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let uncheckedBorderColorTmpBufOpt : arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined
            if (uncheckedBorderColorTmpBufOptUnionSelector == (0).toByte()) {
                uncheckedBorderColorTmpBufOpt = arkui_component_enums_Color.values()[valueDeserializer.readInt32()]
            } else if (uncheckedBorderColorTmpBufOptUnionSelector == (1).toByte()) {
                uncheckedBorderColorTmpBufOpt = valueDeserializer.readInt32()
            } else if (uncheckedBorderColorTmpBufOptUnionSelector == (2).toByte()) {
                uncheckedBorderColorTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (uncheckedBorderColorTmpBufOptUnionSelector == (3).toByte()) {
                uncheckedBorderColorTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for uncheckedBorderColorTmpBufOpt has to be chosen through deserialisation.')
            }
            uncheckedBorderColorTmpBuf = (uncheckedBorderColorTmpBufOpt as arkui_component_enums_Color | int32 | string | arkui_component_units_Resource)
        }
        const uncheckedBorderColorTmpResult : ResourceColor | undefined = uncheckedBorderColorTmpBuf
        const indicatorColorTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let indicatorColorTmpBuf : ResourceColor | undefined = undefined
        if ((indicatorColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const indicatorColorTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let indicatorColorTmpBufOpt : arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined
            if (indicatorColorTmpBufOptUnionSelector == (0).toByte()) {
                indicatorColorTmpBufOpt = arkui_component_enums_Color.values()[valueDeserializer.readInt32()]
            } else if (indicatorColorTmpBufOptUnionSelector == (1).toByte()) {
                indicatorColorTmpBufOpt = valueDeserializer.readInt32()
            } else if (indicatorColorTmpBufOptUnionSelector == (2).toByte()) {
                indicatorColorTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (indicatorColorTmpBufOptUnionSelector == (3).toByte()) {
                indicatorColorTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for indicatorColorTmpBufOpt has to be chosen through deserialisation.')
            }
            indicatorColorTmpBuf = (indicatorColorTmpBufOpt as arkui_component_enums_Color | int32 | string | arkui_component_units_Resource)
        }
        const indicatorColorTmpResult : ResourceColor | undefined = indicatorColorTmpBuf
        let value : RadioStyle = ({checkedBackgroundColor: checkedBackgroundColorTmpResult, uncheckedBorderColor: uncheckedBorderColorTmpResult, indicatorColor: indicatorColorTmpResult} as RadioStyle)
        return value
    }
}
