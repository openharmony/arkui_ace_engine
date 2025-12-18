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
import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr, resourceFinalizerRegister } from '@koalaui/interop'
import { PickerTextStyle_serializer, ArkCommonMethodPeer, CommonMethod, PickerTextStyle, Callback as arkui_component_common_Callback, Bindable, PickerDialogButtonStyle, Rectangle, BlurStyle, BackgroundBlurStyleOptions, BackgroundEffectOptions, ShadowOptions, ShadowStyle, DateTimeOptions, HoverModeAreaType, ArkCommonMethodComponent, Bindable_Date_serializer, PickerDialogButtonStyle_serializer, Rectangle_serializer, BackgroundBlurStyleOptions_serializer, BackgroundEffectOptions_serializer, ShadowOptions_serializer } from './common'
import { int32, int64, float32, unsafeCast } from '@koalaui/common'
import { ComponentBase } from './../ComponentBase'
import { PeerNode } from './../PeerNode'
import { ArkUIGeneratedNativeModule } from '#components'
import { CrownSensitivity, Color as arkui_component_enums_Color } from './enums'
import { AttributeModifier, hookDatePickerAttributeModifier, AttributeUpdater } from '#handwritten'
import { CallbackKind } from './../framework/peers/CallbackKind'
import { CallbackTransformer } from './../CallbackTransformer'
import { memo, memo_stable, memo_skip } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { ResourceColor, Resource as arkui_component_units_Resource, Offset, VoidCallback, Offset_serializer } from './units'
import { Resource as global_resource_Resource } from 'global.resource'
import { DialogAlignment } from './alertDialog'
import { default as intl } from '@ohos.intl'
import { DatePickerModifier } from './../DatePickerModifier'
import { NodeAttach, remember } from '@koalaui/runtime'
import { ModifierStateManager } from './../CommonModifier'
import { global_resource_Resource_serializer } from './../framework/resource'
import { intl_DateTimeOptions_serializer } from './../framework/ohos.intl'
export class ArkDatePickerPeer extends ArkCommonMethodPeer {
    attributeSet?: DatePickerModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkDatePickerPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._DatePicker_construct(peerId, flags)
        const _peer  = new ArkDatePickerPeer(_peerPtr, peerId, 'DatePicker', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setDatePickerOptionsAttribute(options?: DatePickerOptions): void {
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            DatePickerOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._DatePickerInterface_setDatePickerOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setLunarAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._DatePickerAttribute_setLunar(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDisappearTextStyleAttribute(value: PickerTextStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            PickerTextStyle_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._DatePickerAttribute_setDisappearTextStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTextStyleAttribute(value: PickerTextStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            PickerTextStyle_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._DatePickerAttribute_setTextStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectedTextStyleAttribute(value: PickerTextStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            PickerTextStyle_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._DatePickerAttribute_setSelectedTextStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnDateChangeAttribute(value: arkui_component_common_Callback<Date, void> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._DatePickerAttribute_setOnDateChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDigitalCrownSensitivityAttribute(value: CrownSensitivity | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as CrownSensitivity)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._DatePickerAttribute_setDigitalCrownSensitivity(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableHapticFeedbackAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._DatePickerAttribute_setEnableHapticFeedback(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface DatePickerResult {
    year?: int32;
    month?: int32;
    day?: int32;
}
export enum DatePickerMode {
    DATE = 0,
    YEAR_AND_MONTH = 1,
    MONTH_AND_DAY = 2
}
export interface DatePickerOptions {
    start?: Date;
    end?: Date;
    selected?: Date | Bindable<Date>;
    mode?: DatePickerMode;
}
export interface DatePickerAttribute extends CommonMethod {
    setDatePickerOptions(options?: DatePickerOptions): this {
        throw new Error('Unimplemented method setDatePickerOptions')
    }
    lunar(value: boolean | undefined): this {
        throw new Error('Unimplemented method lunar')
    }
    disappearTextStyle(value: PickerTextStyle | undefined): this {
        throw new Error('Unimplemented method disappearTextStyle')
    }
    textStyle(value: PickerTextStyle | undefined): this {
        throw new Error('Unimplemented method textStyle')
    }
    selectedTextStyle(value: PickerTextStyle | undefined): this {
        throw new Error('Unimplemented method selectedTextStyle')
    }
    onDateChange(value: arkui_component_common_Callback<Date, void> | undefined): this {
        throw new Error('Unimplemented method onDateChange')
    }
    digitalCrownSensitivity(value: CrownSensitivity | undefined): this {
        throw new Error('Unimplemented method digitalCrownSensitivity')
    }
    enableHapticFeedback(value: boolean | undefined): this {
        throw new Error('Unimplemented method enableHapticFeedback')
    }
    attributeModifier(value: AttributeModifier<DatePickerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}
export interface LunarSwitchStyle {
    selectedColor?: ResourceColor;
    unselectedColor?: ResourceColor;
    strokeColor?: ResourceColor;
}
export interface DatePickerDialogOptions extends DatePickerOptions {
    lunar?: boolean;
    lunarSwitch?: boolean;
    lunarSwitchStyle?: LunarSwitchStyle;
    showTime?: boolean;
    useMilitaryTime?: boolean;
    disappearTextStyle?: PickerTextStyle;
    textStyle?: PickerTextStyle;
    acceptButtonStyle?: PickerDialogButtonStyle;
    cancelButtonStyle?: PickerDialogButtonStyle;
    selectedTextStyle?: PickerTextStyle;
    maskRect?: Rectangle;
    alignment?: DialogAlignment;
    offset?: Offset;
    onCancel?: VoidCallback;
    onDateAccept?: arkui_component_common_Callback<Date, void>;
    onDateChange?: arkui_component_common_Callback<Date, void>;
    backgroundColor?: ResourceColor;
    backgroundBlurStyle?: BlurStyle;
    backgroundBlurStyleOptions?: BackgroundBlurStyleOptions;
    backgroundEffect?: BackgroundEffectOptions;
    onDidAppear?: VoidCallback;
    onDidDisappear?: VoidCallback;
    onWillAppear?: VoidCallback;
    onWillDisappear?: VoidCallback;
    shadow?: ShadowOptions | ShadowStyle;
    dateTimeOptions?: DateTimeOptions;
    enableHoverMode?: boolean;
    hoverModeArea?: HoverModeAreaType;
    enableHapticFeedback?: boolean;
}

export class ArkDatePickerComponent extends ArkCommonMethodComponent implements DatePickerAttribute {
    getPeer(): ArkDatePickerPeer {
        return (this.peer as ArkDatePickerPeer)
    }
    public setDatePickerOptions(options?: DatePickerOptions): this {
        if (this.checkPriority('setDatePickerOptions')) {
            const options_casted = options as (DatePickerOptions | undefined)
            this.getPeer()?.setDatePickerOptionsAttribute(options_casted)
            this.applyOptionsFinish('DatePickerAttribute');
            return this
        }
        return this
    }
    public lunar(value: boolean | undefined): this {
        if (this.checkPriority('lunar')) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setLunarAttribute(value_casted)
            return this
        }
        return this
    }
    public disappearTextStyle(value: PickerTextStyle | undefined): this {
        if (this.checkPriority('disappearTextStyle')) {
            const value_casted = value as (PickerTextStyle | undefined)
            this.getPeer()?.setDisappearTextStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public textStyle(value: PickerTextStyle | undefined): this {
        if (this.checkPriority('textStyle')) {
            const value_casted = value as (PickerTextStyle | undefined)
            this.getPeer()?.setTextStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public selectedTextStyle(value: PickerTextStyle | undefined): this {
        if (this.checkPriority('selectedTextStyle')) {
            const value_casted = value as (PickerTextStyle | undefined)
            this.getPeer()?.setSelectedTextStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public onDateChange(value: arkui_component_common_Callback<Date, void> | undefined): this {
        if (this.checkPriority('onDateChange')) {
            const value_casted = value as (arkui_component_common_Callback<Date, void> | undefined)
            this.getPeer()?.setOnDateChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public digitalCrownSensitivity(value: CrownSensitivity | undefined): this {
        if (this.checkPriority('digitalCrownSensitivity')) {
            const value_casted = value as (CrownSensitivity | undefined)
            this.getPeer()?.setDigitalCrownSensitivityAttribute(value_casted)
            return this
        }
        return this
    }
    public enableHapticFeedback(value: boolean | undefined): this {
        if (this.checkPriority('enableHapticFeedback')) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setEnableHapticFeedbackAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<DatePickerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookDatePickerAttributeModifier(this, value);
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
export function DatePickerImpl(
    @memo @memo_skip
    style: ((attributes: DatePickerAttribute) => void) | undefined,
    @memo @memo_skip
    content_?: () => void,
): void {
    const receiver = remember<ArkDatePickerComponent>((): ArkDatePickerComponent => {
        return new ArkDatePickerComponent()
    })
    NodeAttach<ArkDatePickerPeer>((): ArkDatePickerPeer => ArkDatePickerPeer.create(receiver), (_: ArkDatePickerPeer): void => {
        style?.(receiver)
        content_?.()
    })
}

export class DatePickerOptions_serializer {
    public static write(buffer: SerializerBase, value: DatePickerOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForStart  = value.start
        if (valueHolderForStart !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStartTmpValue  = valueHolderForStart!
            valueSerializer.writeInt64(valueHolderForStartTmpValue.getTime()!.toLong())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEnd  = value.end
        if (valueHolderForEnd !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEndTmpValue  = valueHolderForEnd!
            valueSerializer.writeInt64(valueHolderForEndTmpValue.getTime()!.toLong())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSelected  = value.selected
        if (valueHolderForSelected !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSelectedTmpValue  = valueHolderForSelected!
            if (valueHolderForSelectedTmpValue instanceof Date) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForSelectedTmpValueForIdx0  = valueHolderForSelectedTmpValue as Date
                valueSerializer.writeInt64(valueHolderForSelectedTmpValueForIdx0.getTime()!.toLong())
            } else if (valueHolderForSelectedTmpValue instanceof Bindable) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForSelectedTmpValueForIdx1  = valueHolderForSelectedTmpValue as Bindable<Date>
                Bindable_Date_serializer.write(valueSerializer, valueHolderForSelectedTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMode  = value.mode
        if (valueHolderForMode !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForModeTmpValue  = (valueHolderForMode as DatePickerMode)
            valueSerializer.writeInt32(valueHolderForModeTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): DatePickerOptions {
        let valueDeserializer : DeserializerBase = buffer
        const startTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let startTmpBuf : Date | undefined = undefined
        if ((startTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            startTmpBuf = new Date(valueDeserializer.readInt64())
        }
        const startTmpResult : Date | undefined = startTmpBuf
        const endTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let endTmpBuf : Date | undefined = undefined
        if ((endTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            endTmpBuf = new Date(valueDeserializer.readInt64())
        }
        const endTmpResult : Date | undefined = endTmpBuf
        const selectedTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let selectedTmpBuf : Date | Bindable<Date> | undefined = undefined
        if ((selectedTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const selectedTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let selectedTmpBufOpt : Date | Bindable<Date> | undefined
            if (selectedTmpBufOptUnionSelector == (0).toByte()) {
                selectedTmpBufOpt = new Date(valueDeserializer.readInt64())
            } else if (selectedTmpBufOptUnionSelector == (1).toByte()) {
                selectedTmpBufOpt = Bindable_Date_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for selectedTmpBufOpt has to be chosen through deserialisation.')
            }
            selectedTmpBuf = (selectedTmpBufOpt as Date | Bindable<Date>)
        }
        const selectedTmpResult : Date | Bindable<Date> | undefined = selectedTmpBuf
        const modeTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let modeTmpBuf : DatePickerMode | undefined = undefined
        if ((modeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            modeTmpBuf = DatePickerMode.fromValue(valueDeserializer.readInt32())
        }
        const modeTmpResult : DatePickerMode | undefined = modeTmpBuf
        let value : DatePickerOptions = ({start: startTmpResult, end: endTmpResult, selected: selectedTmpResult, mode: modeTmpResult} as DatePickerOptions)
        return value
    }
}
export class LunarSwitchStyle_serializer {
    public static write(buffer: SerializerBase, value: LunarSwitchStyle): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForSelectedColor  = value.selectedColor
        if (valueHolderForSelectedColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSelectedColorTmpValue  = valueHolderForSelectedColor!
            if (valueHolderForSelectedColorTmpValue instanceof arkui_component_enums_Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForSelectedColorTmpValueForIdx0  = valueHolderForSelectedColorTmpValue as arkui_component_enums_Color
                valueSerializer.writeInt32((valueHolderForSelectedColorTmpValueForIdx0.getOrdinal()) % (12))
            } else if (valueHolderForSelectedColorTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForSelectedColorTmpValueForIdx1  = valueHolderForSelectedColorTmpValue as int32
                valueSerializer.writeInt32(valueHolderForSelectedColorTmpValueForIdx1)
            } else if (valueHolderForSelectedColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForSelectedColorTmpValueForIdx2  = valueHolderForSelectedColorTmpValue as string
                valueSerializer.writeString(valueHolderForSelectedColorTmpValueForIdx2)
            } else if (valueHolderForSelectedColorTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForSelectedColorTmpValueForIdx3  = valueHolderForSelectedColorTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForSelectedColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForUnselectedColor  = value.unselectedColor
        if (valueHolderForUnselectedColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForUnselectedColorTmpValue  = valueHolderForUnselectedColor!
            if (valueHolderForUnselectedColorTmpValue instanceof arkui_component_enums_Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForUnselectedColorTmpValueForIdx0  = valueHolderForUnselectedColorTmpValue as arkui_component_enums_Color
                valueSerializer.writeInt32((valueHolderForUnselectedColorTmpValueForIdx0.getOrdinal()) % (12))
            } else if (valueHolderForUnselectedColorTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForUnselectedColorTmpValueForIdx1  = valueHolderForUnselectedColorTmpValue as int32
                valueSerializer.writeInt32(valueHolderForUnselectedColorTmpValueForIdx1)
            } else if (valueHolderForUnselectedColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForUnselectedColorTmpValueForIdx2  = valueHolderForUnselectedColorTmpValue as string
                valueSerializer.writeString(valueHolderForUnselectedColorTmpValueForIdx2)
            } else if (valueHolderForUnselectedColorTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForUnselectedColorTmpValueForIdx3  = valueHolderForUnselectedColorTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForUnselectedColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForStrokeColor  = value.strokeColor
        if (valueHolderForStrokeColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStrokeColorTmpValue  = valueHolderForStrokeColor!
            if (valueHolderForStrokeColorTmpValue instanceof arkui_component_enums_Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForStrokeColorTmpValueForIdx0  = valueHolderForStrokeColorTmpValue as arkui_component_enums_Color
                valueSerializer.writeInt32((valueHolderForStrokeColorTmpValueForIdx0.getOrdinal()) % (12))
            } else if (valueHolderForStrokeColorTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForStrokeColorTmpValueForIdx1  = valueHolderForStrokeColorTmpValue as int32
                valueSerializer.writeInt32(valueHolderForStrokeColorTmpValueForIdx1)
            } else if (valueHolderForStrokeColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForStrokeColorTmpValueForIdx2  = valueHolderForStrokeColorTmpValue as string
                valueSerializer.writeString(valueHolderForStrokeColorTmpValueForIdx2)
            } else if (valueHolderForStrokeColorTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForStrokeColorTmpValueForIdx3  = valueHolderForStrokeColorTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForStrokeColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): LunarSwitchStyle {
        let valueDeserializer : DeserializerBase = buffer
        const selectedColorTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let selectedColorTmpBuf : ResourceColor | undefined = undefined
        if ((selectedColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const selectedColorTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let selectedColorTmpBufOpt : arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined
            if (selectedColorTmpBufOptUnionSelector == (0).toByte()) {
                selectedColorTmpBufOpt = arkui_component_enums_Color.values()[valueDeserializer.readInt32()]
            } else if (selectedColorTmpBufOptUnionSelector == (1).toByte()) {
                selectedColorTmpBufOpt = valueDeserializer.readInt32()
            } else if (selectedColorTmpBufOptUnionSelector == (2).toByte()) {
                selectedColorTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (selectedColorTmpBufOptUnionSelector == (3).toByte()) {
                selectedColorTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for selectedColorTmpBufOpt has to be chosen through deserialisation.')
            }
            selectedColorTmpBuf = (selectedColorTmpBufOpt as arkui_component_enums_Color | int32 | string | arkui_component_units_Resource)
        }
        const selectedColorTmpResult : ResourceColor | undefined = selectedColorTmpBuf
        const unselectedColorTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let unselectedColorTmpBuf : ResourceColor | undefined = undefined
        if ((unselectedColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const unselectedColorTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let unselectedColorTmpBufOpt : arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined
            if (unselectedColorTmpBufOptUnionSelector == (0).toByte()) {
                unselectedColorTmpBufOpt = arkui_component_enums_Color.values()[valueDeserializer.readInt32()]
            } else if (unselectedColorTmpBufOptUnionSelector == (1).toByte()) {
                unselectedColorTmpBufOpt = valueDeserializer.readInt32()
            } else if (unselectedColorTmpBufOptUnionSelector == (2).toByte()) {
                unselectedColorTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (unselectedColorTmpBufOptUnionSelector == (3).toByte()) {
                unselectedColorTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for unselectedColorTmpBufOpt has to be chosen through deserialisation.')
            }
            unselectedColorTmpBuf = (unselectedColorTmpBufOpt as arkui_component_enums_Color | int32 | string | arkui_component_units_Resource)
        }
        const unselectedColorTmpResult : ResourceColor | undefined = unselectedColorTmpBuf
        const strokeColorTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let strokeColorTmpBuf : ResourceColor | undefined = undefined
        if ((strokeColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const strokeColorTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let strokeColorTmpBufOpt : arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined
            if (strokeColorTmpBufOptUnionSelector == (0).toByte()) {
                strokeColorTmpBufOpt = arkui_component_enums_Color.values()[valueDeserializer.readInt32()]
            } else if (strokeColorTmpBufOptUnionSelector == (1).toByte()) {
                strokeColorTmpBufOpt = valueDeserializer.readInt32()
            } else if (strokeColorTmpBufOptUnionSelector == (2).toByte()) {
                strokeColorTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (strokeColorTmpBufOptUnionSelector == (3).toByte()) {
                strokeColorTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for strokeColorTmpBufOpt has to be chosen through deserialisation.')
            }
            strokeColorTmpBuf = (strokeColorTmpBufOpt as arkui_component_enums_Color | int32 | string | arkui_component_units_Resource)
        }
        const strokeColorTmpResult : ResourceColor | undefined = strokeColorTmpBuf
        let value : LunarSwitchStyle = ({selectedColor: selectedColorTmpResult, unselectedColor: unselectedColorTmpResult, strokeColor: strokeColorTmpResult} as LunarSwitchStyle)
        return value
    }
}
export class DatePickerDialogOptions_serializer {
    public static write(buffer: SerializerBase, value: DatePickerDialogOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForStart  = value.start
        if (valueHolderForStart !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStartTmpValue  = valueHolderForStart!
            valueSerializer.writeInt64(valueHolderForStartTmpValue.getTime()!.toLong())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEnd  = value.end
        if (valueHolderForEnd !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEndTmpValue  = valueHolderForEnd!
            valueSerializer.writeInt64(valueHolderForEndTmpValue.getTime()!.toLong())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSelected  = value.selected
        if (valueHolderForSelected !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSelectedTmpValue  = valueHolderForSelected!
            if (valueHolderForSelectedTmpValue instanceof Date) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForSelectedTmpValueForIdx0  = valueHolderForSelectedTmpValue as Date
                valueSerializer.writeInt64(valueHolderForSelectedTmpValueForIdx0.getTime()!.toLong())
            } else if (valueHolderForSelectedTmpValue instanceof Bindable) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForSelectedTmpValueForIdx1  = valueHolderForSelectedTmpValue as Bindable<Date>
                Bindable_Date_serializer.write(valueSerializer, valueHolderForSelectedTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMode  = value.mode
        if (valueHolderForMode !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForModeTmpValue  = (valueHolderForMode as DatePickerMode)
            valueSerializer.writeInt32(valueHolderForModeTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLunar  = value.lunar
        if (valueHolderForLunar !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLunarTmpValue  = valueHolderForLunar!
            valueSerializer.writeBoolean(valueHolderForLunarTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLunarSwitch  = value.lunarSwitch
        if (valueHolderForLunarSwitch !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLunarSwitchTmpValue  = valueHolderForLunarSwitch!
            valueSerializer.writeBoolean(valueHolderForLunarSwitchTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLunarSwitchStyle  = value.lunarSwitchStyle
        if (valueHolderForLunarSwitchStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLunarSwitchStyleTmpValue  = valueHolderForLunarSwitchStyle!
            LunarSwitchStyle_serializer.write(valueSerializer, valueHolderForLunarSwitchStyleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForShowTime  = value.showTime
        if (valueHolderForShowTime !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForShowTimeTmpValue  = valueHolderForShowTime!
            valueSerializer.writeBoolean(valueHolderForShowTimeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForUseMilitaryTime  = value.useMilitaryTime
        if (valueHolderForUseMilitaryTime !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForUseMilitaryTimeTmpValue  = valueHolderForUseMilitaryTime!
            valueSerializer.writeBoolean(valueHolderForUseMilitaryTimeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForDisappearTextStyle  = value.disappearTextStyle
        if (valueHolderForDisappearTextStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForDisappearTextStyleTmpValue  = valueHolderForDisappearTextStyle!
            PickerTextStyle_serializer.write(valueSerializer, valueHolderForDisappearTextStyleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForTextStyle  = value.textStyle
        if (valueHolderForTextStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTextStyleTmpValue  = valueHolderForTextStyle!
            PickerTextStyle_serializer.write(valueSerializer, valueHolderForTextStyleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForAcceptButtonStyle  = value.acceptButtonStyle
        if (valueHolderForAcceptButtonStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForAcceptButtonStyleTmpValue  = valueHolderForAcceptButtonStyle!
            PickerDialogButtonStyle_serializer.write(valueSerializer, valueHolderForAcceptButtonStyleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForCancelButtonStyle  = value.cancelButtonStyle
        if (valueHolderForCancelButtonStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForCancelButtonStyleTmpValue  = valueHolderForCancelButtonStyle!
            PickerDialogButtonStyle_serializer.write(valueSerializer, valueHolderForCancelButtonStyleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSelectedTextStyle  = value.selectedTextStyle
        if (valueHolderForSelectedTextStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSelectedTextStyleTmpValue  = valueHolderForSelectedTextStyle!
            PickerTextStyle_serializer.write(valueSerializer, valueHolderForSelectedTextStyleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMaskRect  = value.maskRect
        if (valueHolderForMaskRect !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMaskRectTmpValue  = valueHolderForMaskRect!
            Rectangle_serializer.write(valueSerializer, valueHolderForMaskRectTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForAlignment  = value.alignment
        if (valueHolderForAlignment !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForAlignmentTmpValue  = (valueHolderForAlignment as DialogAlignment)
            valueSerializer.writeInt32(valueHolderForAlignmentTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOffset  = value.offset
        if (valueHolderForOffset !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOffsetTmpValue  = valueHolderForOffset!
            Offset_serializer.write(valueSerializer, valueHolderForOffsetTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnCancel  = value.onCancel
        if (valueHolderForOnCancel !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnCancelTmpValue  = valueHolderForOnCancel!
            valueSerializer.holdAndWriteCallback(valueHolderForOnCancelTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnDateAccept  = value.onDateAccept
        if (valueHolderForOnDateAccept !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnDateAcceptTmpValue  = valueHolderForOnDateAccept!
            valueSerializer.holdAndWriteCallback(valueHolderForOnDateAcceptTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnDateChange  = value.onDateChange
        if (valueHolderForOnDateChange !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnDateChangeTmpValue  = valueHolderForOnDateChange!
            valueSerializer.holdAndWriteCallback(valueHolderForOnDateChangeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBackgroundColor  = value.backgroundColor
        if (valueHolderForBackgroundColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBackgroundColorTmpValue  = valueHolderForBackgroundColor!
            if (valueHolderForBackgroundColorTmpValue instanceof arkui_component_enums_Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx0  = valueHolderForBackgroundColorTmpValue as arkui_component_enums_Color
                valueSerializer.writeInt32((valueHolderForBackgroundColorTmpValueForIdx0.getOrdinal()) % (12))
            } else if (valueHolderForBackgroundColorTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx1  = valueHolderForBackgroundColorTmpValue as int32
                valueSerializer.writeInt32(valueHolderForBackgroundColorTmpValueForIdx1)
            } else if (valueHolderForBackgroundColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx2  = valueHolderForBackgroundColorTmpValue as string
                valueSerializer.writeString(valueHolderForBackgroundColorTmpValueForIdx2)
            } else if (valueHolderForBackgroundColorTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx3  = valueHolderForBackgroundColorTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForBackgroundColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBackgroundBlurStyle  = value.backgroundBlurStyle
        if (valueHolderForBackgroundBlurStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBackgroundBlurStyleTmpValue  = (valueHolderForBackgroundBlurStyle as BlurStyle)
            valueSerializer.writeInt32(valueHolderForBackgroundBlurStyleTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBackgroundBlurStyleOptions  = value.backgroundBlurStyleOptions
        if (valueHolderForBackgroundBlurStyleOptions !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBackgroundBlurStyleOptionsTmpValue  = valueHolderForBackgroundBlurStyleOptions!
            BackgroundBlurStyleOptions_serializer.write(valueSerializer, valueHolderForBackgroundBlurStyleOptionsTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBackgroundEffect  = value.backgroundEffect
        if (valueHolderForBackgroundEffect !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBackgroundEffectTmpValue  = valueHolderForBackgroundEffect!
            BackgroundEffectOptions_serializer.write(valueSerializer, valueHolderForBackgroundEffectTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnDidAppear  = value.onDidAppear
        if (valueHolderForOnDidAppear !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnDidAppearTmpValue  = valueHolderForOnDidAppear!
            valueSerializer.holdAndWriteCallback(valueHolderForOnDidAppearTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnDidDisappear  = value.onDidDisappear
        if (valueHolderForOnDidDisappear !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnDidDisappearTmpValue  = valueHolderForOnDidDisappear!
            valueSerializer.holdAndWriteCallback(valueHolderForOnDidDisappearTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnWillAppear  = value.onWillAppear
        if (valueHolderForOnWillAppear !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnWillAppearTmpValue  = valueHolderForOnWillAppear!
            valueSerializer.holdAndWriteCallback(valueHolderForOnWillAppearTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnWillDisappear  = value.onWillDisappear
        if (valueHolderForOnWillDisappear !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnWillDisappearTmpValue  = valueHolderForOnWillDisappear!
            valueSerializer.holdAndWriteCallback(valueHolderForOnWillDisappearTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForShadow  = value.shadow
        if (valueHolderForShadow !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForShadowTmpValue  = valueHolderForShadow!
            if (valueHolderForShadowTmpValue instanceof ShadowOptions) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForShadowTmpValueForIdx0  = valueHolderForShadowTmpValue as ShadowOptions
                ShadowOptions_serializer.write(valueSerializer, valueHolderForShadowTmpValueForIdx0)
            } else if (valueHolderForShadowTmpValue instanceof ShadowStyle) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForShadowTmpValueForIdx1  = valueHolderForShadowTmpValue as ShadowStyle
                valueSerializer.writeInt32(valueHolderForShadowTmpValueForIdx1.valueOf())
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForDateTimeOptions  = value.dateTimeOptions
        if (valueHolderForDateTimeOptions !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForDateTimeOptionsTmpValue  = valueHolderForDateTimeOptions!
            intl_DateTimeOptions_serializer.write(valueSerializer, valueHolderForDateTimeOptionsTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEnableHoverMode  = value.enableHoverMode
        if (valueHolderForEnableHoverMode !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEnableHoverModeTmpValue  = valueHolderForEnableHoverMode!
            valueSerializer.writeBoolean(valueHolderForEnableHoverModeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForHoverModeArea  = value.hoverModeArea
        if (valueHolderForHoverModeArea !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForHoverModeAreaTmpValue  = (valueHolderForHoverModeArea as HoverModeAreaType)
            valueSerializer.writeInt32(valueHolderForHoverModeAreaTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEnableHapticFeedback  = value.enableHapticFeedback
        if (valueHolderForEnableHapticFeedback !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEnableHapticFeedbackTmpValue  = valueHolderForEnableHapticFeedback!
            valueSerializer.writeBoolean(valueHolderForEnableHapticFeedbackTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): DatePickerDialogOptions {
        let valueDeserializer : DeserializerBase = buffer
        const startTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let startTmpBuf : Date | undefined = undefined
        if ((startTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            startTmpBuf = new Date(valueDeserializer.readInt64())
        }
        const startTmpResult : Date | undefined = startTmpBuf
        const endTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let endTmpBuf : Date | undefined = undefined
        if ((endTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            endTmpBuf = new Date(valueDeserializer.readInt64())
        }
        const endTmpResult : Date | undefined = endTmpBuf
        const selectedTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let selectedTmpBuf : Date | Bindable<Date> | undefined = undefined
        if ((selectedTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const selectedTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let selectedTmpBufOpt : Date | Bindable<Date> | undefined
            if (selectedTmpBufOptUnionSelector == (0).toByte()) {
                selectedTmpBufOpt = new Date(valueDeserializer.readInt64())
            } else if (selectedTmpBufOptUnionSelector == (1).toByte()) {
                selectedTmpBufOpt = Bindable_Date_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for selectedTmpBufOpt has to be chosen through deserialisation.')
            }
            selectedTmpBuf = (selectedTmpBufOpt as Date | Bindable<Date>)
        }
        const selectedTmpResult : Date | Bindable<Date> | undefined = selectedTmpBuf
        const modeTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let modeTmpBuf : DatePickerMode | undefined = undefined
        if ((modeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            modeTmpBuf = DatePickerMode.fromValue(valueDeserializer.readInt32())
        }
        const modeTmpResult : DatePickerMode | undefined = modeTmpBuf
        const lunarTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let lunarTmpBuf : boolean | undefined = undefined
        if ((lunarTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            lunarTmpBuf = valueDeserializer.readBoolean()
        }
        const lunarTmpResult : boolean | undefined = lunarTmpBuf
        const lunarSwitchTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let lunarSwitchTmpBuf : boolean | undefined = undefined
        if ((lunarSwitchTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            lunarSwitchTmpBuf = valueDeserializer.readBoolean()
        }
        const lunarSwitchTmpResult : boolean | undefined = lunarSwitchTmpBuf
        const lunarSwitchStyleTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let lunarSwitchStyleTmpBuf : LunarSwitchStyle | undefined = undefined
        if ((lunarSwitchStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            lunarSwitchStyleTmpBuf = LunarSwitchStyle_serializer.read(valueDeserializer)
        }
        const lunarSwitchStyleTmpResult : LunarSwitchStyle | undefined = lunarSwitchStyleTmpBuf
        const showTimeTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let showTimeTmpBuf : boolean | undefined = undefined
        if ((showTimeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            showTimeTmpBuf = valueDeserializer.readBoolean()
        }
        const showTimeTmpResult : boolean | undefined = showTimeTmpBuf
        const useMilitaryTimeTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let useMilitaryTimeTmpBuf : boolean | undefined = undefined
        if ((useMilitaryTimeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            useMilitaryTimeTmpBuf = valueDeserializer.readBoolean()
        }
        const useMilitaryTimeTmpResult : boolean | undefined = useMilitaryTimeTmpBuf
        const disappearTextStyleTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let disappearTextStyleTmpBuf : PickerTextStyle | undefined = undefined
        if ((disappearTextStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            disappearTextStyleTmpBuf = PickerTextStyle_serializer.read(valueDeserializer)
        }
        const disappearTextStyleTmpResult : PickerTextStyle | undefined = disappearTextStyleTmpBuf
        const textStyleTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let textStyleTmpBuf : PickerTextStyle | undefined = undefined
        if ((textStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            textStyleTmpBuf = PickerTextStyle_serializer.read(valueDeserializer)
        }
        const textStyleTmpResult : PickerTextStyle | undefined = textStyleTmpBuf
        const acceptButtonStyleTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let acceptButtonStyleTmpBuf : PickerDialogButtonStyle | undefined = undefined
        if ((acceptButtonStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            acceptButtonStyleTmpBuf = PickerDialogButtonStyle_serializer.read(valueDeserializer)
        }
        const acceptButtonStyleTmpResult : PickerDialogButtonStyle | undefined = acceptButtonStyleTmpBuf
        const cancelButtonStyleTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let cancelButtonStyleTmpBuf : PickerDialogButtonStyle | undefined = undefined
        if ((cancelButtonStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            cancelButtonStyleTmpBuf = PickerDialogButtonStyle_serializer.read(valueDeserializer)
        }
        const cancelButtonStyleTmpResult : PickerDialogButtonStyle | undefined = cancelButtonStyleTmpBuf
        const selectedTextStyleTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let selectedTextStyleTmpBuf : PickerTextStyle | undefined = undefined
        if ((selectedTextStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            selectedTextStyleTmpBuf = PickerTextStyle_serializer.read(valueDeserializer)
        }
        const selectedTextStyleTmpResult : PickerTextStyle | undefined = selectedTextStyleTmpBuf
        const maskRectTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let maskRectTmpBuf : Rectangle | undefined = undefined
        if ((maskRectTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            maskRectTmpBuf = Rectangle_serializer.read(valueDeserializer)
        }
        const maskRectTmpResult : Rectangle | undefined = maskRectTmpBuf
        const alignmentTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let alignmentTmpBuf : DialogAlignment | undefined = undefined
        if ((alignmentTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            alignmentTmpBuf = DialogAlignment.fromValue(valueDeserializer.readInt32())
        }
        const alignmentTmpResult : DialogAlignment | undefined = alignmentTmpBuf
        const offsetTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let offsetTmpBuf : Offset | undefined = undefined
        if ((offsetTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            offsetTmpBuf = Offset_serializer.read(valueDeserializer)
        }
        const offsetTmpResult : Offset | undefined = offsetTmpBuf
        const onCancelTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let onCancelTmpBuf : VoidCallback | undefined = undefined
        if ((onCancelTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onCancelTmpBufOptBufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onCancelTmpBufOptBufCall : KPointer = valueDeserializer.readPointer()
            const onCancelTmpBufOptBufCallSync : KPointer = valueDeserializer.readPointer()
            const onCancelTmpBufOptClosure  = ():void => {
                const onCancelTmpBufOptBufArgsSerializer : SerializerBase = SerializerBase.hold();
                onCancelTmpBufOptBufArgsSerializer.writeInt32(onCancelTmpBufOptBufResource.resourceId);
                onCancelTmpBufOptBufArgsSerializer.writePointer(onCancelTmpBufOptBufCall);
                onCancelTmpBufOptBufArgsSerializer.writePointer(onCancelTmpBufOptBufCallSync);
                InteropNativeModule._CallCallbackSync(10, 553494831, onCancelTmpBufOptBufArgsSerializer.asBuffer(), onCancelTmpBufOptBufArgsSerializer.length());
                onCancelTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(onCancelTmpBufOptClosure, onCancelTmpBufOptBufResource)
            onCancelTmpBuf = onCancelTmpBufOptClosure
        }
        const onCancelTmpResult : VoidCallback | undefined = onCancelTmpBuf
        const onDateAcceptTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let onDateAcceptTmpBuf : arkui_component_common_Callback<Date, void> | undefined = undefined
        if ((onDateAcceptTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onDateAcceptTmpBufOptBufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onDateAcceptTmpBufOptBufCall : KPointer = valueDeserializer.readPointer()
            const onDateAcceptTmpBufOptBufCallSync : KPointer = valueDeserializer.readPointer()
            const onDateAcceptTmpBufOptClosure  = (data: Date):void => {
                const onDateAcceptTmpBufOptBufArgsSerializer : SerializerBase = SerializerBase.hold();
                onDateAcceptTmpBufOptBufArgsSerializer.writeInt32(onDateAcceptTmpBufOptBufResource.resourceId);
                onDateAcceptTmpBufOptBufArgsSerializer.writePointer(onDateAcceptTmpBufOptBufCall);
                onDateAcceptTmpBufOptBufArgsSerializer.writePointer(onDateAcceptTmpBufOptBufCallSync);
                onDateAcceptTmpBufOptBufArgsSerializer.writeInt64(data.getTime()!.toLong());
                InteropNativeModule._CallCallbackSync(10, -1865664613, onDateAcceptTmpBufOptBufArgsSerializer.asBuffer(), onDateAcceptTmpBufOptBufArgsSerializer.length());
                onDateAcceptTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(onDateAcceptTmpBufOptClosure, onDateAcceptTmpBufOptBufResource)
            onDateAcceptTmpBuf = onDateAcceptTmpBufOptClosure
        }
        const onDateAcceptTmpResult : arkui_component_common_Callback<Date, void> | undefined = onDateAcceptTmpBuf
        const onDateChangeTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let onDateChangeTmpBuf : arkui_component_common_Callback<Date, void> | undefined = undefined
        if ((onDateChangeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onDateChangeTmpBufOptBufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onDateChangeTmpBufOptBufCall : KPointer = valueDeserializer.readPointer()
            const onDateChangeTmpBufOptBufCallSync : KPointer = valueDeserializer.readPointer()
            const onDateChangeTmpBufOptClosure  = (data: Date):void => {
                const onDateChangeTmpBufOptBufArgsSerializer : SerializerBase = SerializerBase.hold();
                onDateChangeTmpBufOptBufArgsSerializer.writeInt32(onDateChangeTmpBufOptBufResource.resourceId);
                onDateChangeTmpBufOptBufArgsSerializer.writePointer(onDateChangeTmpBufOptBufCall);
                onDateChangeTmpBufOptBufArgsSerializer.writePointer(onDateChangeTmpBufOptBufCallSync);
                onDateChangeTmpBufOptBufArgsSerializer.writeInt64(data.getTime()!.toLong());
                InteropNativeModule._CallCallbackSync(10, -1865664613, onDateChangeTmpBufOptBufArgsSerializer.asBuffer(), onDateChangeTmpBufOptBufArgsSerializer.length());
                onDateChangeTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(onDateChangeTmpBufOptClosure, onDateChangeTmpBufOptBufResource)
            onDateChangeTmpBuf = onDateChangeTmpBufOptClosure
        }
        const onDateChangeTmpResult : arkui_component_common_Callback<Date, void> | undefined = onDateChangeTmpBuf
        const backgroundColorTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let backgroundColorTmpBuf : ResourceColor | undefined = undefined
        if ((backgroundColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const backgroundColorTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let backgroundColorTmpBufOpt : arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined
            if (backgroundColorTmpBufOptUnionSelector == (0).toByte()) {
                backgroundColorTmpBufOpt = arkui_component_enums_Color.values()[valueDeserializer.readInt32()]
            } else if (backgroundColorTmpBufOptUnionSelector == (1).toByte()) {
                backgroundColorTmpBufOpt = valueDeserializer.readInt32()
            } else if (backgroundColorTmpBufOptUnionSelector == (2).toByte()) {
                backgroundColorTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (backgroundColorTmpBufOptUnionSelector == (3).toByte()) {
                backgroundColorTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for backgroundColorTmpBufOpt has to be chosen through deserialisation.')
            }
            backgroundColorTmpBuf = (backgroundColorTmpBufOpt as arkui_component_enums_Color | int32 | string | arkui_component_units_Resource)
        }
        const backgroundColorTmpResult : ResourceColor | undefined = backgroundColorTmpBuf
        const backgroundBlurStyleTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let backgroundBlurStyleTmpBuf : BlurStyle | undefined = undefined
        if ((backgroundBlurStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            backgroundBlurStyleTmpBuf = BlurStyle.fromValue(valueDeserializer.readInt32())
        }
        const backgroundBlurStyleTmpResult : BlurStyle | undefined = backgroundBlurStyleTmpBuf
        const backgroundBlurStyleOptionsTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let backgroundBlurStyleOptionsTmpBuf : BackgroundBlurStyleOptions | undefined = undefined
        if ((backgroundBlurStyleOptionsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            backgroundBlurStyleOptionsTmpBuf = BackgroundBlurStyleOptions_serializer.read(valueDeserializer)
        }
        const backgroundBlurStyleOptionsTmpResult : BackgroundBlurStyleOptions | undefined = backgroundBlurStyleOptionsTmpBuf
        const backgroundEffectTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let backgroundEffectTmpBuf : BackgroundEffectOptions | undefined = undefined
        if ((backgroundEffectTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            backgroundEffectTmpBuf = BackgroundEffectOptions_serializer.read(valueDeserializer)
        }
        const backgroundEffectTmpResult : BackgroundEffectOptions | undefined = backgroundEffectTmpBuf
        const onDidAppearTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let onDidAppearTmpBuf : VoidCallback | undefined = undefined
        if ((onDidAppearTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onDidAppearTmpBufOptBufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onDidAppearTmpBufOptBufCall : KPointer = valueDeserializer.readPointer()
            const onDidAppearTmpBufOptBufCallSync : KPointer = valueDeserializer.readPointer()
            const onDidAppearTmpBufOptClosure  = ():void => {
                const onDidAppearTmpBufOptBufArgsSerializer : SerializerBase = SerializerBase.hold();
                onDidAppearTmpBufOptBufArgsSerializer.writeInt32(onDidAppearTmpBufOptBufResource.resourceId);
                onDidAppearTmpBufOptBufArgsSerializer.writePointer(onDidAppearTmpBufOptBufCall);
                onDidAppearTmpBufOptBufArgsSerializer.writePointer(onDidAppearTmpBufOptBufCallSync);
                InteropNativeModule._CallCallbackSync(10, 553494831, onDidAppearTmpBufOptBufArgsSerializer.asBuffer(), onDidAppearTmpBufOptBufArgsSerializer.length());
                onDidAppearTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(onDidAppearTmpBufOptClosure, onDidAppearTmpBufOptBufResource)
            onDidAppearTmpBuf = onDidAppearTmpBufOptClosure
        }
        const onDidAppearTmpResult : VoidCallback | undefined = onDidAppearTmpBuf
        const onDidDisappearTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let onDidDisappearTmpBuf : VoidCallback | undefined = undefined
        if ((onDidDisappearTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onDidDisappearTmpBufOptBufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onDidDisappearTmpBufOptBufCall : KPointer = valueDeserializer.readPointer()
            const onDidDisappearTmpBufOptBufCallSync : KPointer = valueDeserializer.readPointer()
            const onDidDisappearTmpBufOptClosure  = ():void => {
                const onDidDisappearTmpBufOptBufArgsSerializer : SerializerBase = SerializerBase.hold();
                onDidDisappearTmpBufOptBufArgsSerializer.writeInt32(onDidDisappearTmpBufOptBufResource.resourceId);
                onDidDisappearTmpBufOptBufArgsSerializer.writePointer(onDidDisappearTmpBufOptBufCall);
                onDidDisappearTmpBufOptBufArgsSerializer.writePointer(onDidDisappearTmpBufOptBufCallSync);
                InteropNativeModule._CallCallbackSync(10, 553494831, onDidDisappearTmpBufOptBufArgsSerializer.asBuffer(), onDidDisappearTmpBufOptBufArgsSerializer.length());
                onDidDisappearTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(onDidDisappearTmpBufOptClosure, onDidDisappearTmpBufOptBufResource)
            onDidDisappearTmpBuf = onDidDisappearTmpBufOptClosure
        }
        const onDidDisappearTmpResult : VoidCallback | undefined = onDidDisappearTmpBuf
        const onWillAppearTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let onWillAppearTmpBuf : VoidCallback | undefined = undefined
        if ((onWillAppearTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onWillAppearTmpBufOptBufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onWillAppearTmpBufOptBufCall : KPointer = valueDeserializer.readPointer()
            const onWillAppearTmpBufOptBufCallSync : KPointer = valueDeserializer.readPointer()
            const onWillAppearTmpBufOptClosure  = ():void => {
                const onWillAppearTmpBufOptBufArgsSerializer : SerializerBase = SerializerBase.hold();
                onWillAppearTmpBufOptBufArgsSerializer.writeInt32(onWillAppearTmpBufOptBufResource.resourceId);
                onWillAppearTmpBufOptBufArgsSerializer.writePointer(onWillAppearTmpBufOptBufCall);
                onWillAppearTmpBufOptBufArgsSerializer.writePointer(onWillAppearTmpBufOptBufCallSync);
                InteropNativeModule._CallCallbackSync(10, 553494831, onWillAppearTmpBufOptBufArgsSerializer.asBuffer(), onWillAppearTmpBufOptBufArgsSerializer.length());
                onWillAppearTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(onWillAppearTmpBufOptClosure, onWillAppearTmpBufOptBufResource)
            onWillAppearTmpBuf = onWillAppearTmpBufOptClosure
        }
        const onWillAppearTmpResult : VoidCallback | undefined = onWillAppearTmpBuf
        const onWillDisappearTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let onWillDisappearTmpBuf : VoidCallback | undefined = undefined
        if ((onWillDisappearTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onWillDisappearTmpBufOptBufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onWillDisappearTmpBufOptBufCall : KPointer = valueDeserializer.readPointer()
            const onWillDisappearTmpBufOptBufCallSync : KPointer = valueDeserializer.readPointer()
            const onWillDisappearTmpBufOptClosure  = ():void => {
                const onWillDisappearTmpBufOptBufArgsSerializer : SerializerBase = SerializerBase.hold();
                onWillDisappearTmpBufOptBufArgsSerializer.writeInt32(onWillDisappearTmpBufOptBufResource.resourceId);
                onWillDisappearTmpBufOptBufArgsSerializer.writePointer(onWillDisappearTmpBufOptBufCall);
                onWillDisappearTmpBufOptBufArgsSerializer.writePointer(onWillDisappearTmpBufOptBufCallSync);
                InteropNativeModule._CallCallbackSync(10, 553494831, onWillDisappearTmpBufOptBufArgsSerializer.asBuffer(), onWillDisappearTmpBufOptBufArgsSerializer.length());
                onWillDisappearTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(onWillDisappearTmpBufOptClosure, onWillDisappearTmpBufOptBufResource)
            onWillDisappearTmpBuf = onWillDisappearTmpBufOptClosure
        }
        const onWillDisappearTmpResult : VoidCallback | undefined = onWillDisappearTmpBuf
        const shadowTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let shadowTmpBuf : ShadowOptions | ShadowStyle | undefined = undefined
        if ((shadowTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const shadowTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let shadowTmpBufOpt : ShadowOptions | ShadowStyle | undefined
            if (shadowTmpBufOptUnionSelector == (0).toByte()) {
                shadowTmpBufOpt = ShadowOptions_serializer.read(valueDeserializer)
            } else if (shadowTmpBufOptUnionSelector == (1).toByte()) {
                shadowTmpBufOpt = ShadowStyle.fromValue(valueDeserializer.readInt32())
            } else {
                throw new Error('One of the branches for shadowTmpBufOpt has to be chosen through deserialisation.')
            }
            shadowTmpBuf = (shadowTmpBufOpt as ShadowOptions | ShadowStyle)
        }
        const shadowTmpResult : ShadowOptions | ShadowStyle | undefined = shadowTmpBuf
        const dateTimeOptionsTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let dateTimeOptionsTmpBuf : DateTimeOptions | undefined = undefined
        if ((dateTimeOptionsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            dateTimeOptionsTmpBuf = intl_DateTimeOptions_serializer.read(valueDeserializer)
        }
        const dateTimeOptionsTmpResult : DateTimeOptions | undefined = dateTimeOptionsTmpBuf
        const enableHoverModeTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let enableHoverModeTmpBuf : boolean | undefined = undefined
        if ((enableHoverModeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            enableHoverModeTmpBuf = valueDeserializer.readBoolean()
        }
        const enableHoverModeTmpResult : boolean | undefined = enableHoverModeTmpBuf
        const hoverModeAreaTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let hoverModeAreaTmpBuf : HoverModeAreaType | undefined = undefined
        if ((hoverModeAreaTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            hoverModeAreaTmpBuf = HoverModeAreaType.fromValue(valueDeserializer.readInt32())
        }
        const hoverModeAreaTmpResult : HoverModeAreaType | undefined = hoverModeAreaTmpBuf
        const enableHapticFeedbackTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let enableHapticFeedbackTmpBuf : boolean | undefined = undefined
        if ((enableHapticFeedbackTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            enableHapticFeedbackTmpBuf = valueDeserializer.readBoolean()
        }
        const enableHapticFeedbackTmpResult : boolean | undefined = enableHapticFeedbackTmpBuf
        let value : DatePickerDialogOptions = ({start: startTmpResult, end: endTmpResult, selected: selectedTmpResult, mode: modeTmpResult, lunar: lunarTmpResult, lunarSwitch: lunarSwitchTmpResult, lunarSwitchStyle: lunarSwitchStyleTmpResult, showTime: showTimeTmpResult, useMilitaryTime: useMilitaryTimeTmpResult, disappearTextStyle: disappearTextStyleTmpResult, textStyle: textStyleTmpResult, acceptButtonStyle: acceptButtonStyleTmpResult, cancelButtonStyle: cancelButtonStyleTmpResult, selectedTextStyle: selectedTextStyleTmpResult, maskRect: maskRectTmpResult, alignment: alignmentTmpResult, offset: offsetTmpResult, onCancel: onCancelTmpResult, onDateAccept: onDateAcceptTmpResult, onDateChange: onDateChangeTmpResult, backgroundColor: backgroundColorTmpResult, backgroundBlurStyle: backgroundBlurStyleTmpResult, backgroundBlurStyleOptions: backgroundBlurStyleOptionsTmpResult, backgroundEffect: backgroundEffectTmpResult, onDidAppear: onDidAppearTmpResult, onDidDisappear: onDidDisappearTmpResult, onWillAppear: onWillAppearTmpResult, onWillDisappear: onWillDisappearTmpResult, shadow: shadowTmpResult, dateTimeOptions: dateTimeOptionsTmpResult, enableHoverMode: enableHoverModeTmpResult, hoverModeArea: hoverModeAreaTmpResult, enableHapticFeedback: enableHapticFeedbackTmpResult} as DatePickerDialogOptions)
        return value
    }
}
