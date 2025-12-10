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
import { PickerTextStyle_serializer, ArkCommonMethodPeer, CommonMethod, PickerTextStyle, DateTimeOptions, Callback as arkui_component_common_Callback, Bindable, PickerDialogButtonStyle, Rectangle, BlurStyle, BackgroundBlurStyleOptions, BackgroundEffectOptions, ShadowOptions, ShadowStyle, HoverModeAreaType, ArkCommonMethodComponent, Bindable_Date_serializer, PickerDialogButtonStyle_serializer, Rectangle_serializer, BackgroundBlurStyleOptions_serializer, BackgroundEffectOptions_serializer, ShadowOptions_serializer } from './common'
import { intl_DateTimeOptions_serializer } from './../framework/ohos.intl'
import { int32, int64, float32, unsafeCast } from '@koalaui/common'
import { ComponentBase } from './../ComponentBase'
import { PeerNode } from './../PeerNode'
import { ArkUIGeneratedNativeModule } from '#components'
import { default as intl } from '@ohos.intl'
import { CrownSensitivity, Color as arkui_component_enums_Color } from './enums'
import { AttributeModifier, hookTimePickerAttributeModifier, AttributeUpdater } from '#handwritten'
import { CallbackKind } from './../framework/peers/CallbackKind'
import { CallbackTransformer } from './../CallbackTransformer'
import { memo, memo_stable, memo_skip } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { DialogAlignment } from './alertDialog'
import { Offset, VoidCallback, ResourceColor, Resource as arkui_component_units_Resource, Offset_serializer } from './units'
import { Resource as global_resource_Resource } from 'global.resource'
import { TimePickerModifier } from './../TimePickerModifier'
import { NodeAttach, remember } from '@koalaui/runtime'
import { ModifierStateManager } from './../CommonModifier'
import { global_resource_Resource_serializer } from './../framework/resource'
export class ArkTimePickerPeer extends ArkCommonMethodPeer {
    attributeSet?: TimePickerModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkTimePickerPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._TimePicker_construct(peerId, flags)
        const _peer  = new ArkTimePickerPeer(_peerPtr, peerId, 'TimePicker', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setTimePickerOptionsAttribute(options?: TimePickerOptions): void {
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            TimePickerOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TimePickerInterface_setTimePickerOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setUseMilitaryTimeAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TimePickerAttribute_setUseMilitaryTime(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setLoopAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TimePickerAttribute_setLoop(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._TimePickerAttribute_setDisappearTextStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._TimePickerAttribute_setTextStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._TimePickerAttribute_setSelectedTextStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDateTimeOptionsAttribute(value: DateTimeOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            intl_DateTimeOptions_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TimePickerAttribute_setDateTimeOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnChangeAttribute(value: OnTimePickerChangeCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TimePickerAttribute_setOnChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnEnterSelectedAreaAttribute(value: arkui_component_common_Callback<TimePickerResult, void> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TimePickerAttribute_setOnEnterSelectedArea(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._TimePickerAttribute_setEnableHapticFeedback(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._TimePickerAttribute_setDigitalCrownSensitivity(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableCascadeAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TimePickerAttribute_setEnableCascade(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface TimePickerResult {
    hour: int32;
    minute: int32;
    second: int32;
}
export enum TimePickerFormat {
    HOUR_MINUTE = 0,
    HOUR_MINUTE_SECOND = 1
}
export interface TimePickerOptions {
    selected?: Date | Bindable<Date>;
    format?: TimePickerFormat;
    start?: Date;
    end?: Date;
}
export type OnTimePickerChangeCallback = (result: TimePickerResult) => void;
export interface TimePickerAttribute extends CommonMethod {
    setTimePickerOptions(options?: TimePickerOptions): this {
        throw new Error('Unimplemented method setTimePickerOptions')
    }
    useMilitaryTime(value: boolean | undefined): this {
        throw new Error('Unimplemented method useMilitaryTime')
    }
    loop(value: boolean | undefined): this {
        throw new Error('Unimplemented method loop')
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
    dateTimeOptions(value: DateTimeOptions | undefined): this {
        throw new Error('Unimplemented method dateTimeOptions')
    }
    onChange(value: OnTimePickerChangeCallback | undefined): this {
        throw new Error('Unimplemented method onChange')
    }
    onEnterSelectedArea(value: arkui_component_common_Callback<TimePickerResult, void> | undefined): this {
        throw new Error('Unimplemented method onEnterSelectedArea')
    }
    enableHapticFeedback(value: boolean | undefined): this {
        throw new Error('Unimplemented method enableHapticFeedback')
    }
    digitalCrownSensitivity(value: CrownSensitivity | undefined): this {
        throw new Error('Unimplemented method digitalCrownSensitivity')
    }
    enableCascade(value: boolean | undefined): this {
        throw new Error('Unimplemented method enableCascade')
    }
    attributeModifier(value: AttributeModifier<TimePickerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}
export interface TimePickerDialogOptions extends TimePickerOptions {
    useMilitaryTime?: boolean;
    disappearTextStyle?: PickerTextStyle;
    textStyle?: PickerTextStyle;
    acceptButtonStyle?: PickerDialogButtonStyle;
    cancelButtonStyle?: PickerDialogButtonStyle;
    selectedTextStyle?: PickerTextStyle;
    maskRect?: Rectangle;
    alignment?: DialogAlignment;
    offset?: Offset;
    onAccept?: ((value: TimePickerResult) => void);
    onCancel?: VoidCallback;
    onChange?: ((value: TimePickerResult) => void);
    onEnterSelectedArea?: arkui_component_common_Callback<TimePickerResult, void>;
    backgroundColor?: ResourceColor;
    backgroundBlurStyle?: BlurStyle;
    backgroundBlurStyleOptions?: BackgroundBlurStyleOptions;
    backgroundEffect?: BackgroundEffectOptions;
    enableCascade?: boolean;
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

export class ArkTimePickerComponent extends ArkCommonMethodComponent implements TimePickerAttribute {
    getPeer(): ArkTimePickerPeer {
        return (this.peer as ArkTimePickerPeer)
    }
    public setTimePickerOptions(options?: TimePickerOptions): this {
        if (this.checkPriority('setTimePickerOptions')) {
            const options_casted = options as (TimePickerOptions | undefined)
            this.getPeer()?.setTimePickerOptionsAttribute(options_casted)
            this.applyOptionsFinish('TimePickerAttribute');
            return this
        }
        return this
    }
    public useMilitaryTime(value: boolean | undefined): this {
        if (this.checkPriority('useMilitaryTime')) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setUseMilitaryTimeAttribute(value_casted)
            return this
        }
        return this
    }
    public loop(value: boolean | undefined): this {
        if (this.checkPriority('loop')) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setLoopAttribute(value_casted)
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
    public dateTimeOptions(value: DateTimeOptions | undefined): this {
        if (this.checkPriority('dateTimeOptions')) {
            const value_casted = value as (DateTimeOptions | undefined)
            this.getPeer()?.setDateTimeOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    public onChange(value: OnTimePickerChangeCallback | undefined): this {
        if (this.checkPriority('onChange')) {
            const value_casted = value as (OnTimePickerChangeCallback | undefined)
            this.getPeer()?.setOnChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public onEnterSelectedArea(value: arkui_component_common_Callback<TimePickerResult, void> | undefined): this {
        if (this.checkPriority('onEnterSelectedArea')) {
            const value_casted = value as (arkui_component_common_Callback<TimePickerResult, void> | undefined)
            this.getPeer()?.setOnEnterSelectedAreaAttribute(value_casted)
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
    public digitalCrownSensitivity(value: CrownSensitivity | undefined): this {
        if (this.checkPriority('digitalCrownSensitivity')) {
            const value_casted = value as (CrownSensitivity | undefined)
            this.getPeer()?.setDigitalCrownSensitivityAttribute(value_casted)
            return this
        }
        return this
    }
    public enableCascade(value: boolean | undefined): this {
        if (this.checkPriority('enableCascade')) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setEnableCascadeAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<TimePickerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookTimePickerAttributeModifier(this, value);
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
export function TimePickerImpl(
    @memo @memo_skip
    style: ((attributes: TimePickerAttribute) => void) | undefined,
    @memo @memo_skip
    content_?: () => void,
): void {
    const receiver = remember<ArkTimePickerComponent>((): ArkTimePickerComponent => {
        return new ArkTimePickerComponent()
    })
    NodeAttach<ArkTimePickerPeer>((): ArkTimePickerPeer => ArkTimePickerPeer.create(receiver), (_: ArkTimePickerPeer): void => {
        style?.(receiver)
        content_?.()
    })
}

export class TimePickerResult_serializer {
    public static write(buffer: SerializerBase, value: TimePickerResult): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForHour  = value.hour
        valueSerializer.writeInt32(valueHolderForHour)
        const valueHolderForMinute  = value.minute
        valueSerializer.writeInt32(valueHolderForMinute)
        const valueHolderForSecond  = value.second
        valueSerializer.writeInt32(valueHolderForSecond)
    }
    public static read(buffer: DeserializerBase): TimePickerResult {
        let valueDeserializer : DeserializerBase = buffer
        const hourTmpResult : int32 = valueDeserializer.readInt32()
        const minuteTmpResult : int32 = valueDeserializer.readInt32()
        const secondTmpResult : int32 = valueDeserializer.readInt32()
        let value : TimePickerResult = ({hour: hourTmpResult, minute: minuteTmpResult, second: secondTmpResult} as TimePickerResult)
        return value
    }
}
export class TimePickerOptions_serializer {
    public static write(buffer: SerializerBase, value: TimePickerOptions): void {
        let valueSerializer : SerializerBase = buffer
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
        const valueHolderForFormat  = value.format
        if (valueHolderForFormat !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFormatTmpValue  = (valueHolderForFormat as TimePickerFormat)
            valueSerializer.writeInt32(valueHolderForFormatTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
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
    }
    public static read(buffer: DeserializerBase): TimePickerOptions {
        let valueDeserializer : DeserializerBase = buffer
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
        const formatTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let formatTmpBuf : TimePickerFormat | undefined = undefined
        if ((formatTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            formatTmpBuf = TimePickerFormat.fromValue(valueDeserializer.readInt32())
        }
        const formatTmpResult : TimePickerFormat | undefined = formatTmpBuf
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
        let value : TimePickerOptions = ({selected: selectedTmpResult, format: formatTmpResult, start: startTmpResult, end: endTmpResult} as TimePickerOptions)
        return value
    }
}
export class TimePickerDialogOptions_serializer {
    public static write(buffer: SerializerBase, value: TimePickerDialogOptions): void {
        let valueSerializer : SerializerBase = buffer
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
        const valueHolderForFormat  = value.format
        if (valueHolderForFormat !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFormatTmpValue  = (valueHolderForFormat as TimePickerFormat)
            valueSerializer.writeInt32(valueHolderForFormatTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
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
        const valueHolderForOnAccept  = value.onAccept
        if (valueHolderForOnAccept !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnAcceptTmpValue  = valueHolderForOnAccept!
            valueSerializer.holdAndWriteCallback(valueHolderForOnAcceptTmpValue)
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
        const valueHolderForOnChange  = value.onChange
        if (valueHolderForOnChange !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnChangeTmpValue  = valueHolderForOnChange!
            valueSerializer.holdAndWriteCallback(valueHolderForOnChangeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnEnterSelectedArea  = value.onEnterSelectedArea
        if (valueHolderForOnEnterSelectedArea !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnEnterSelectedAreaTmpValue  = valueHolderForOnEnterSelectedArea!
            valueSerializer.holdAndWriteCallback(valueHolderForOnEnterSelectedAreaTmpValue)
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
        const valueHolderForEnableCascade  = value.enableCascade
        if (valueHolderForEnableCascade !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEnableCascadeTmpValue  = valueHolderForEnableCascade!
            valueSerializer.writeBoolean(valueHolderForEnableCascadeTmpValue)
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
    public static read(buffer: DeserializerBase): TimePickerDialogOptions {
        let valueDeserializer : DeserializerBase = buffer
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
        const formatTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let formatTmpBuf : TimePickerFormat | undefined = undefined
        if ((formatTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            formatTmpBuf = TimePickerFormat.fromValue(valueDeserializer.readInt32())
        }
        const formatTmpResult : TimePickerFormat | undefined = formatTmpBuf
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
        const onAcceptTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let onAcceptTmpBuf : ((value: TimePickerResult) => void) | undefined = undefined
        if ((onAcceptTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onAcceptTmpBufOptBufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onAcceptTmpBufOptBufCall : KPointer = valueDeserializer.readPointer()
            const onAcceptTmpBufOptBufCallSync : KPointer = valueDeserializer.readPointer()
            const onAcceptTmpBufOptClosure  = (value: TimePickerResult):void => {
                const onAcceptTmpBufOptBufArgsSerializer : SerializerBase = SerializerBase.hold();
                onAcceptTmpBufOptBufArgsSerializer.writeInt32(onAcceptTmpBufOptBufResource.resourceId);
                onAcceptTmpBufOptBufArgsSerializer.writePointer(onAcceptTmpBufOptBufCall);
                onAcceptTmpBufOptBufArgsSerializer.writePointer(onAcceptTmpBufOptBufCallSync);
                TimePickerResult_serializer.write(onAcceptTmpBufOptBufArgsSerializer, value);
                InteropNativeModule._CallCallbackSync(10, -250027639, onAcceptTmpBufOptBufArgsSerializer.asBuffer(), onAcceptTmpBufOptBufArgsSerializer.length());
                onAcceptTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(onAcceptTmpBufOptClosure, onAcceptTmpBufOptBufResource)
            onAcceptTmpBuf = onAcceptTmpBufOptClosure
        }
        const onAcceptTmpResult : ((value: TimePickerResult) => void) | undefined = onAcceptTmpBuf
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
        const onChangeTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let onChangeTmpBuf : ((value: TimePickerResult) => void) | undefined = undefined
        if ((onChangeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onChangeTmpBufOptBufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onChangeTmpBufOptBufCall : KPointer = valueDeserializer.readPointer()
            const onChangeTmpBufOptBufCallSync : KPointer = valueDeserializer.readPointer()
            const onChangeTmpBufOptClosure  = (value: TimePickerResult):void => {
                const onChangeTmpBufOptBufArgsSerializer : SerializerBase = SerializerBase.hold();
                onChangeTmpBufOptBufArgsSerializer.writeInt32(onChangeTmpBufOptBufResource.resourceId);
                onChangeTmpBufOptBufArgsSerializer.writePointer(onChangeTmpBufOptBufCall);
                onChangeTmpBufOptBufArgsSerializer.writePointer(onChangeTmpBufOptBufCallSync);
                TimePickerResult_serializer.write(onChangeTmpBufOptBufArgsSerializer, value);
                InteropNativeModule._CallCallbackSync(10, -250027639, onChangeTmpBufOptBufArgsSerializer.asBuffer(), onChangeTmpBufOptBufArgsSerializer.length());
                onChangeTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(onChangeTmpBufOptClosure, onChangeTmpBufOptBufResource)
            onChangeTmpBuf = onChangeTmpBufOptClosure
        }
        const onChangeTmpResult : ((value: TimePickerResult) => void) | undefined = onChangeTmpBuf
        const onEnterSelectedAreaTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let onEnterSelectedAreaTmpBuf : arkui_component_common_Callback<TimePickerResult, void> | undefined = undefined
        if ((onEnterSelectedAreaTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onEnterSelectedAreaTmpBufOptBufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onEnterSelectedAreaTmpBufOptBufCall : KPointer = valueDeserializer.readPointer()
            const onEnterSelectedAreaTmpBufOptBufCallSync : KPointer = valueDeserializer.readPointer()
            const onEnterSelectedAreaTmpBufOptClosure  = (data: TimePickerResult):void => {
                const onEnterSelectedAreaTmpBufOptBufArgsSerializer : SerializerBase = SerializerBase.hold();
                onEnterSelectedAreaTmpBufOptBufArgsSerializer.writeInt32(onEnterSelectedAreaTmpBufOptBufResource.resourceId);
                onEnterSelectedAreaTmpBufOptBufArgsSerializer.writePointer(onEnterSelectedAreaTmpBufOptBufCall);
                onEnterSelectedAreaTmpBufOptBufArgsSerializer.writePointer(onEnterSelectedAreaTmpBufOptBufCallSync);
                TimePickerResult_serializer.write(onEnterSelectedAreaTmpBufOptBufArgsSerializer, data);
                InteropNativeModule._CallCallbackSync(10, -91394219, onEnterSelectedAreaTmpBufOptBufArgsSerializer.asBuffer(), onEnterSelectedAreaTmpBufOptBufArgsSerializer.length());
                onEnterSelectedAreaTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(onEnterSelectedAreaTmpBufOptClosure, onEnterSelectedAreaTmpBufOptBufResource)
            onEnterSelectedAreaTmpBuf = onEnterSelectedAreaTmpBufOptClosure
        }
        const onEnterSelectedAreaTmpResult : arkui_component_common_Callback<TimePickerResult, void> | undefined = onEnterSelectedAreaTmpBuf
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
        const enableCascadeTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let enableCascadeTmpBuf : boolean | undefined = undefined
        if ((enableCascadeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            enableCascadeTmpBuf = valueDeserializer.readBoolean()
        }
        const enableCascadeTmpResult : boolean | undefined = enableCascadeTmpBuf
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
        let value : TimePickerDialogOptions = ({selected: selectedTmpResult, format: formatTmpResult, start: startTmpResult, end: endTmpResult, useMilitaryTime: useMilitaryTimeTmpResult, disappearTextStyle: disappearTextStyleTmpResult, textStyle: textStyleTmpResult, acceptButtonStyle: acceptButtonStyleTmpResult, cancelButtonStyle: cancelButtonStyleTmpResult, selectedTextStyle: selectedTextStyleTmpResult, maskRect: maskRectTmpResult, alignment: alignmentTmpResult, offset: offsetTmpResult, onAccept: onAcceptTmpResult, onCancel: onCancelTmpResult, onChange: onChangeTmpResult, onEnterSelectedArea: onEnterSelectedAreaTmpResult, backgroundColor: backgroundColorTmpResult, backgroundBlurStyle: backgroundBlurStyleTmpResult, backgroundBlurStyleOptions: backgroundBlurStyleOptionsTmpResult, backgroundEffect: backgroundEffectTmpResult, enableCascade: enableCascadeTmpResult, onDidAppear: onDidAppearTmpResult, onDidDisappear: onDidDisappearTmpResult, onWillAppear: onWillAppearTmpResult, onWillDisappear: onWillDisappearTmpResult, shadow: shadowTmpResult, dateTimeOptions: dateTimeOptionsTmpResult, enableHoverMode: enableHoverModeTmpResult, hoverModeArea: hoverModeAreaTmpResult, enableHapticFeedback: enableHapticFeedbackTmpResult} as TimePickerDialogOptions)
        return value
    }
}
