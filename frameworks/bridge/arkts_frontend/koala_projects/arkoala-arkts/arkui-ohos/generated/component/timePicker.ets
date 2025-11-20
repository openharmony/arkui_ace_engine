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

import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, DeserializerBase, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackTransformer } from "./../CallbackTransformer"
import { PickerTextStyle_serializer, ArkCommonMethodPeer, CommonMethod, PickerTextStyle, Bindable, PickerDialogButtonStyle, Rectangle, BlurStyle, BackgroundBlurStyleOptions, BackgroundEffectOptions, ShadowOptions, ShadowStyle, HoverModeAreaType, ArkCommonMethodComponent, ArkCommonMethodStyle, Bindable_Date_serializer, PickerDialogButtonStyle_serializer, Rectangle_serializer, BackgroundBlurStyleOptions_serializer, BackgroundEffectOptions_serializer, ShadowOptions_serializer } from "./common"
import { intl_DateTimeOptions_serializer } from "./../framework/ohos.intl"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { default as intl } from "@ohos.intl"
import { CrownSensitivity, Color } from "./enums"
import { AttributeModifier, hookTimePickerAttributeModifier, AttributeUpdater } from "#handwritten"
import { ModifierStateManager } from '../CommonModifier';
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { DialogAlignment } from "./alertDialog"
import { Offset, ResourceColor, Offset_serializer } from "./units"
import { Resource } from "global.resource"
import { TimePickerModifier } from "./../TimePickerModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
import { Resource_serializer } from "./../framework/resource"
export class TimePickerDialogInternal {
    public static fromPtr(ptr: KPointer): TimePickerDialog {
        return new TimePickerDialog(ptr)
    }
}
export class TimePickerDialog implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, TimePickerDialog.getFinalizer())
    }
    constructor() {
        this(TimePickerDialog.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._TimePickerDialog_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._TimePickerDialog_getFinalizer()
    }
}
export class ArkTimePickerPeer extends ArkCommonMethodPeer {
    attributeSet?: TimePickerModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
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
    setDateTimeOptionsAttribute(value: intl.DateTimeOptions | undefined): void {
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
    setOnEnterSelectedAreaAttribute(value: ((value0: TimePickerResult) => void) | undefined): void {
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
        throw new Error("Unimplemented method setTimePickerOptions")
    }
    useMilitaryTime(value: boolean | undefined): this {
        throw new Error("Unimplemented method useMilitaryTime")
    }
    loop(value: boolean | undefined): this {
        throw new Error("Unimplemented method loop")
    }
    disappearTextStyle(value: PickerTextStyle | undefined): this {
        throw new Error("Unimplemented method disappearTextStyle")
    }
    textStyle(value: PickerTextStyle | undefined): this {
        throw new Error("Unimplemented method textStyle")
    }
    selectedTextStyle(value: PickerTextStyle | undefined): this {
        throw new Error("Unimplemented method selectedTextStyle")
    }
    dateTimeOptions(value: intl.DateTimeOptions | undefined): this {
        throw new Error("Unimplemented method dateTimeOptions")
    }
    onChange(value: OnTimePickerChangeCallback | undefined): this {
        throw new Error("Unimplemented method onChange")
    }
    onEnterSelectedArea(value: ((value0: TimePickerResult) => void) | undefined): this {
        throw new Error("Unimplemented method onEnterSelectedArea")
    }
    enableHapticFeedback(value: boolean | undefined): this {
        throw new Error("Unimplemented method enableHapticFeedback")
    }
    digitalCrownSensitivity(value: CrownSensitivity | undefined): this {
        throw new Error("Unimplemented method digitalCrownSensitivity")
    }
    enableCascade(value: boolean | undefined): this {
        throw new Error("Unimplemented method enableCascade")
    }
    attributeModifier(value: AttributeModifier<TimePickerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkTimePickerStyle extends ArkCommonMethodStyle implements TimePickerAttribute {
    useMilitaryTime_value?: boolean | undefined
    loop_value?: boolean | undefined
    disappearTextStyle_value?: PickerTextStyle | undefined
    textStyle_value?: PickerTextStyle | undefined
    selectedTextStyle_value?: PickerTextStyle | undefined
    dateTimeOptions_value?: intl.DateTimeOptions | undefined
    onChange_value?: OnTimePickerChangeCallback | undefined
    onEnterSelectedArea_value?: ((value0: TimePickerResult) => void) | undefined
    enableHapticFeedback_value?: boolean | undefined
    digitalCrownSensitivity_value?: CrownSensitivity | undefined
    enableCascade_value?: boolean | undefined
    attributeModifier_value?: AttributeModifier<TimePickerAttribute> | AttributeModifier<CommonMethod> | undefined
    setTimePickerOptions(options?: TimePickerOptions): this {
        return this
    }
    useMilitaryTime(value: boolean | undefined): this {
        return this
    }
    loop(value: boolean | undefined): this {
        return this
    }
    disappearTextStyle(value: PickerTextStyle | undefined): this {
        return this
    }
    textStyle(value: PickerTextStyle | undefined): this {
        return this
    }
    selectedTextStyle(value: PickerTextStyle | undefined): this {
        return this
    }
    dateTimeOptions(value: intl.DateTimeOptions | undefined): this {
        return this
    }
    onChange(value: OnTimePickerChangeCallback | undefined): this {
        return this
    }
    onEnterSelectedArea(value: ((value0: TimePickerResult) => void) | undefined): this {
        return this
    }
    enableHapticFeedback(value: boolean | undefined): this {
        return this
    }
    digitalCrownSensitivity(value: CrownSensitivity | undefined): this {
        return this
    }
    enableCascade(value: boolean | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<TimePickerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
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
    onAccept?: ((value0: TimePickerResult) => void);
    onCancel?: (() => void);
    onChange?: ((value0: TimePickerResult) => void);
    onEnterSelectedArea?: ((value0: TimePickerResult) => void);
    backgroundColor?: ResourceColor;
    backgroundBlurStyle?: BlurStyle;
    backgroundBlurStyleOptions?: BackgroundBlurStyleOptions;
    backgroundEffect?: BackgroundEffectOptions;
    enableCascade?: boolean;
    onDidAppear?: (() => void);
    onDidDisappear?: (() => void);
    onWillAppear?: (() => void);
    onWillDisappear?: (() => void);
    shadow?: ShadowOptions | ShadowStyle;
    dateTimeOptions?: intl.DateTimeOptions;
    enableHoverMode?: boolean;
    hoverModeArea?: HoverModeAreaType;
    enableHapticFeedback?: boolean;
}

export class ArkTimePickerComponent extends ArkCommonMethodComponent implements TimePickerAttribute {
    getPeer(): ArkTimePickerPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkTimePickerPeer)
    }
    public setTimePickerOptions(options?: TimePickerOptions): this {
        if (this.checkPriority("setTimePickerOptions")) {
            const options_casted = options as (TimePickerOptions | undefined)
            this.getPeer()?.setTimePickerOptionsAttribute(options_casted)
            this.applyOptionsFinish('TimePickerAttribute');
            return this
        }
        return this
    }
    public useMilitaryTime(value: boolean | undefined): this {
        if (this.checkPriority("useMilitaryTime")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setUseMilitaryTimeAttribute(value_casted)
            return this
        }
        return this
    }
    public loop(value: boolean | undefined): this {
        if (this.checkPriority("loop")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setLoopAttribute(value_casted)
            return this
        }
        return this
    }
    public disappearTextStyle(value: PickerTextStyle | undefined): this {
        if (this.checkPriority("disappearTextStyle")) {
            const value_casted = value as (PickerTextStyle | undefined)
            this.getPeer()?.setDisappearTextStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public textStyle(value: PickerTextStyle | undefined): this {
        if (this.checkPriority("textStyle")) {
            const value_casted = value as (PickerTextStyle | undefined)
            this.getPeer()?.setTextStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public selectedTextStyle(value: PickerTextStyle | undefined): this {
        if (this.checkPriority("selectedTextStyle")) {
            const value_casted = value as (PickerTextStyle | undefined)
            this.getPeer()?.setSelectedTextStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public dateTimeOptions(value: intl.DateTimeOptions | undefined): this {
        if (this.checkPriority("dateTimeOptions")) {
            const value_casted = value as (intl.DateTimeOptions | undefined)
            this.getPeer()?.setDateTimeOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    public onChange(value: OnTimePickerChangeCallback | undefined): this {
        if (this.checkPriority("onChange")) {
            const value_casted = value as (OnTimePickerChangeCallback | undefined)
            this.getPeer()?.setOnChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public onEnterSelectedArea(value: ((value0: TimePickerResult) => void) | undefined): this {
        if (this.checkPriority("onEnterSelectedArea")) {
            const value_casted = value as (((value0: TimePickerResult) => void) | undefined)
            this.getPeer()?.setOnEnterSelectedAreaAttribute(value_casted)
            return this
        }
        return this
    }
    public enableHapticFeedback(value: boolean | undefined): this {
        if (this.checkPriority("enableHapticFeedback")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setEnableHapticFeedbackAttribute(value_casted)
            return this
        }
        return this
    }
    public digitalCrownSensitivity(value: CrownSensitivity | undefined): this {
        if (this.checkPriority("digitalCrownSensitivity")) {
            const value_casted = value as (CrownSensitivity | undefined)
            this.getPeer()?.setDigitalCrownSensitivityAttribute(value_casted)
            return this
        }
        return this
    }
    public enableCascade(value: boolean | undefined): this {
        if (this.checkPriority("enableCascade")) {
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
    @memo
    style: ((attributes: TimePickerAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkTimePickerComponent>((): ArkTimePickerComponent => {
        return new ArkTimePickerComponent()
    })
    NodeAttach<ArkTimePickerPeer>((): ArkTimePickerPeer => ArkTimePickerPeer.create(receiver), (peer: ArkTimePickerPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
    })
}

export class TimePickerDialog_serializer {
    public static write(buffer: SerializerBase, value: TimePickerDialog): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): TimePickerDialog {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return TimePickerDialogInternal.fromPtr(ptr)
    }
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
                valueSerializer.writeInt64(valueHolderForSelectedTmpValueForIdx0.getTime().toLong())
            } else if (valueHolderForSelectedTmpValue instanceof Bindable<Date>) {
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
            valueSerializer.writeInt64(valueHolderForStartTmpValue.getTime().toLong())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEnd  = value.end
        if (valueHolderForEnd !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEndTmpValue  = valueHolderForEnd!
            valueSerializer.writeInt64(valueHolderForEndTmpValue.getTime().toLong())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): TimePickerOptions {
        let valueDeserializer : DeserializerBase = buffer
        const selectedTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let selectedTmpBuf : Date | Bindable<Date> | undefined = undefined
        if ((selectedTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const selectedTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let selectedTmpBuf_ : Date | Bindable<Date> | undefined
            if (selectedTmpBuf_UnionSelector == (0).toChar()) {
                selectedTmpBuf_ = new Date(valueDeserializer.readInt64())
            } else if (selectedTmpBuf_UnionSelector == (1).toChar()) {
                selectedTmpBuf_ = Bindable_Date_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for selectedTmpBuf_ has to be chosen through deserialisation.")
            }
            selectedTmpBuf = (selectedTmpBuf_ as Date | Bindable<Date>)
        }
        const selectedTmpResult : Date | Bindable<Date> | undefined = selectedTmpBuf
        const formatTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let formatTmpBuf : TimePickerFormat | undefined = undefined
        if ((formatTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            formatTmpBuf = TimePickerFormat.fromValue(valueDeserializer.readInt32())
        }
        const formatTmpResult : TimePickerFormat | undefined = formatTmpBuf
        const startTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let startTmpBuf : Date | undefined = undefined
        if ((startTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            startTmpBuf = new Date(valueDeserializer.readInt64())
        }
        const startTmpResult : Date | undefined = startTmpBuf
        const endTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
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
                valueSerializer.writeInt64(valueHolderForSelectedTmpValueForIdx0.getTime().toLong())
            } else if (valueHolderForSelectedTmpValue instanceof Bindable<Date>) {
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
            valueSerializer.writeInt64(valueHolderForStartTmpValue.getTime().toLong())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEnd  = value.end
        if (valueHolderForEnd !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEndTmpValue  = valueHolderForEnd!
            valueSerializer.writeInt64(valueHolderForEndTmpValue.getTime().toLong())
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
            if (valueHolderForBackgroundColorTmpValue instanceof Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx0  = valueHolderForBackgroundColorTmpValue as Color
                valueSerializer.writeInt32(valueHolderForBackgroundColorTmpValueForIdx0.getOrdinal())
            } else if (valueHolderForBackgroundColorTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx1  = valueHolderForBackgroundColorTmpValue as number
                valueSerializer.writeNumber(valueHolderForBackgroundColorTmpValueForIdx1)
            } else if (valueHolderForBackgroundColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx2  = valueHolderForBackgroundColorTmpValue as string
                valueSerializer.writeString(valueHolderForBackgroundColorTmpValueForIdx2)
            } else if (valueHolderForBackgroundColorTmpValue instanceof Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx3  = valueHolderForBackgroundColorTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForBackgroundColorTmpValueForIdx3)
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
        const selectedTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let selectedTmpBuf : Date | Bindable<Date> | undefined = undefined
        if ((selectedTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const selectedTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let selectedTmpBuf_ : Date | Bindable<Date> | undefined
            if (selectedTmpBuf_UnionSelector == (0).toChar()) {
                selectedTmpBuf_ = new Date(valueDeserializer.readInt64())
            } else if (selectedTmpBuf_UnionSelector == (1).toChar()) {
                selectedTmpBuf_ = Bindable_Date_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for selectedTmpBuf_ has to be chosen through deserialisation.")
            }
            selectedTmpBuf = (selectedTmpBuf_ as Date | Bindable<Date>)
        }
        const selectedTmpResult : Date | Bindable<Date> | undefined = selectedTmpBuf
        const formatTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let formatTmpBuf : TimePickerFormat | undefined = undefined
        if ((formatTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            formatTmpBuf = TimePickerFormat.fromValue(valueDeserializer.readInt32())
        }
        const formatTmpResult : TimePickerFormat | undefined = formatTmpBuf
        const startTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let startTmpBuf : Date | undefined = undefined
        if ((startTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            startTmpBuf = new Date(valueDeserializer.readInt64())
        }
        const startTmpResult : Date | undefined = startTmpBuf
        const endTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let endTmpBuf : Date | undefined = undefined
        if ((endTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            endTmpBuf = new Date(valueDeserializer.readInt64())
        }
        const endTmpResult : Date | undefined = endTmpBuf
        const useMilitaryTimeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let useMilitaryTimeTmpBuf : boolean | undefined = undefined
        if ((useMilitaryTimeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            useMilitaryTimeTmpBuf = valueDeserializer.readBoolean()
        }
        const useMilitaryTimeTmpResult : boolean | undefined = useMilitaryTimeTmpBuf
        const disappearTextStyleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let disappearTextStyleTmpBuf : PickerTextStyle | undefined = undefined
        if ((disappearTextStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            disappearTextStyleTmpBuf = PickerTextStyle_serializer.read(valueDeserializer)
        }
        const disappearTextStyleTmpResult : PickerTextStyle | undefined = disappearTextStyleTmpBuf
        const textStyleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let textStyleTmpBuf : PickerTextStyle | undefined = undefined
        if ((textStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            textStyleTmpBuf = PickerTextStyle_serializer.read(valueDeserializer)
        }
        const textStyleTmpResult : PickerTextStyle | undefined = textStyleTmpBuf
        const acceptButtonStyleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let acceptButtonStyleTmpBuf : PickerDialogButtonStyle | undefined = undefined
        if ((acceptButtonStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            acceptButtonStyleTmpBuf = PickerDialogButtonStyle_serializer.read(valueDeserializer)
        }
        const acceptButtonStyleTmpResult : PickerDialogButtonStyle | undefined = acceptButtonStyleTmpBuf
        const cancelButtonStyleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let cancelButtonStyleTmpBuf : PickerDialogButtonStyle | undefined = undefined
        if ((cancelButtonStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            cancelButtonStyleTmpBuf = PickerDialogButtonStyle_serializer.read(valueDeserializer)
        }
        const cancelButtonStyleTmpResult : PickerDialogButtonStyle | undefined = cancelButtonStyleTmpBuf
        const selectedTextStyleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let selectedTextStyleTmpBuf : PickerTextStyle | undefined = undefined
        if ((selectedTextStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            selectedTextStyleTmpBuf = PickerTextStyle_serializer.read(valueDeserializer)
        }
        const selectedTextStyleTmpResult : PickerTextStyle | undefined = selectedTextStyleTmpBuf
        const maskRectTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let maskRectTmpBuf : Rectangle | undefined = undefined
        if ((maskRectTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            maskRectTmpBuf = Rectangle_serializer.read(valueDeserializer)
        }
        const maskRectTmpResult : Rectangle | undefined = maskRectTmpBuf
        const alignmentTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let alignmentTmpBuf : DialogAlignment | undefined = undefined
        if ((alignmentTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            alignmentTmpBuf = DialogAlignment.fromValue(valueDeserializer.readInt32())
        }
        const alignmentTmpResult : DialogAlignment | undefined = alignmentTmpBuf
        const offsetTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let offsetTmpBuf : Offset | undefined = undefined
        if ((offsetTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            offsetTmpBuf = Offset_serializer.read(valueDeserializer)
        }
        const offsetTmpResult : Offset | undefined = offsetTmpBuf
        const onAcceptTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onAcceptTmpBuf : ((value0: TimePickerResult) => void) | undefined = undefined
        if ((onAcceptTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onAcceptTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onAcceptTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onAcceptTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onAcceptTmpBuf = (value0: TimePickerResult):void => {
                const onAcceptTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onAcceptTmpBuf_BufArgsSerializer.writeInt32(onAcceptTmpBuf_BufResource.resourceId);
                onAcceptTmpBuf_BufArgsSerializer.writePointer(onAcceptTmpBuf_BufCall);
                onAcceptTmpBuf_BufArgsSerializer.writePointer(onAcceptTmpBuf_BufCallSync);
                TimePickerResult_serializer.write(onAcceptTmpBuf_BufArgsSerializer, value0);
                InteropNativeModule._CallCallbackSync(10, 1557859605, onAcceptTmpBuf_BufArgsSerializer.asBuffer(), onAcceptTmpBuf_BufArgsSerializer.length());
                onAcceptTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onAcceptTmpResult : ((value0: TimePickerResult) => void) | undefined = onAcceptTmpBuf
        const onCancelTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onCancelTmpBuf : (() => void) | undefined = undefined
        if ((onCancelTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onCancelTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onCancelTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onCancelTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onCancelTmpBuf = ():void => {
                const onCancelTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onCancelTmpBuf_BufArgsSerializer.writeInt32(onCancelTmpBuf_BufResource.resourceId);
                onCancelTmpBuf_BufArgsSerializer.writePointer(onCancelTmpBuf_BufCall);
                onCancelTmpBuf_BufArgsSerializer.writePointer(onCancelTmpBuf_BufCallSync);
                InteropNativeModule._CallCallbackSync(10, -1867723152, onCancelTmpBuf_BufArgsSerializer.asBuffer(), onCancelTmpBuf_BufArgsSerializer.length());
                onCancelTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onCancelTmpResult : (() => void) | undefined = onCancelTmpBuf
        const onChangeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onChangeTmpBuf : ((value0: TimePickerResult) => void) | undefined = undefined
        if ((onChangeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onChangeTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onChangeTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onChangeTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onChangeTmpBuf = (value0: TimePickerResult):void => {
                const onChangeTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onChangeTmpBuf_BufArgsSerializer.writeInt32(onChangeTmpBuf_BufResource.resourceId);
                onChangeTmpBuf_BufArgsSerializer.writePointer(onChangeTmpBuf_BufCall);
                onChangeTmpBuf_BufArgsSerializer.writePointer(onChangeTmpBuf_BufCallSync);
                TimePickerResult_serializer.write(onChangeTmpBuf_BufArgsSerializer, value0);
                InteropNativeModule._CallCallbackSync(10, 1557859605, onChangeTmpBuf_BufArgsSerializer.asBuffer(), onChangeTmpBuf_BufArgsSerializer.length());
                onChangeTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onChangeTmpResult : ((value0: TimePickerResult) => void) | undefined = onChangeTmpBuf
        const onEnterSelectedAreaTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onEnterSelectedAreaTmpBuf : ((value0: TimePickerResult) => void) | undefined = undefined
        if ((onEnterSelectedAreaTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onEnterSelectedAreaTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onEnterSelectedAreaTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onEnterSelectedAreaTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onEnterSelectedAreaTmpBuf = (value0: TimePickerResult):void => {
                const onEnterSelectedAreaTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onEnterSelectedAreaTmpBuf_BufArgsSerializer.writeInt32(onEnterSelectedAreaTmpBuf_BufResource.resourceId);
                onEnterSelectedAreaTmpBuf_BufArgsSerializer.writePointer(onEnterSelectedAreaTmpBuf_BufCall);
                onEnterSelectedAreaTmpBuf_BufArgsSerializer.writePointer(onEnterSelectedAreaTmpBuf_BufCallSync);
                TimePickerResult_serializer.write(onEnterSelectedAreaTmpBuf_BufArgsSerializer, value0);
                InteropNativeModule._CallCallbackSync(10, 1557859605, onEnterSelectedAreaTmpBuf_BufArgsSerializer.asBuffer(), onEnterSelectedAreaTmpBuf_BufArgsSerializer.length());
                onEnterSelectedAreaTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onEnterSelectedAreaTmpResult : ((value0: TimePickerResult) => void) | undefined = onEnterSelectedAreaTmpBuf
        const backgroundColorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundColorTmpBuf : ResourceColor | undefined = undefined
        if ((backgroundColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const backgroundColorTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let backgroundColorTmpBuf_ : Color | number | string | Resource | undefined
            if (backgroundColorTmpBuf_UnionSelector == (0).toChar()) {
                backgroundColorTmpBuf_ = Color.values()[valueDeserializer.readInt32()]
            } else if (backgroundColorTmpBuf_UnionSelector == (1).toChar()) {
                backgroundColorTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (backgroundColorTmpBuf_UnionSelector == (2).toChar()) {
                backgroundColorTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (backgroundColorTmpBuf_UnionSelector == (3).toChar()) {
                backgroundColorTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for backgroundColorTmpBuf_ has to be chosen through deserialisation.")
            }
            backgroundColorTmpBuf = (backgroundColorTmpBuf_ as Color | number | string | Resource)
        }
        const backgroundColorTmpResult : ResourceColor | undefined = backgroundColorTmpBuf
        const backgroundBlurStyleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundBlurStyleTmpBuf : BlurStyle | undefined = undefined
        if ((backgroundBlurStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            backgroundBlurStyleTmpBuf = BlurStyle.fromValue(valueDeserializer.readInt32())
        }
        const backgroundBlurStyleTmpResult : BlurStyle | undefined = backgroundBlurStyleTmpBuf
        const backgroundBlurStyleOptionsTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundBlurStyleOptionsTmpBuf : BackgroundBlurStyleOptions | undefined = undefined
        if ((backgroundBlurStyleOptionsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            backgroundBlurStyleOptionsTmpBuf = BackgroundBlurStyleOptions_serializer.read(valueDeserializer)
        }
        const backgroundBlurStyleOptionsTmpResult : BackgroundBlurStyleOptions | undefined = backgroundBlurStyleOptionsTmpBuf
        const backgroundEffectTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundEffectTmpBuf : BackgroundEffectOptions | undefined = undefined
        if ((backgroundEffectTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            backgroundEffectTmpBuf = BackgroundEffectOptions_serializer.read(valueDeserializer)
        }
        const backgroundEffectTmpResult : BackgroundEffectOptions | undefined = backgroundEffectTmpBuf
        const enableCascadeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let enableCascadeTmpBuf : boolean | undefined = undefined
        if ((enableCascadeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            enableCascadeTmpBuf = valueDeserializer.readBoolean()
        }
        const enableCascadeTmpResult : boolean | undefined = enableCascadeTmpBuf
        const onDidAppearTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onDidAppearTmpBuf : (() => void) | undefined = undefined
        if ((onDidAppearTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onDidAppearTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onDidAppearTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onDidAppearTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onDidAppearTmpBuf = ():void => {
                const onDidAppearTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onDidAppearTmpBuf_BufArgsSerializer.writeInt32(onDidAppearTmpBuf_BufResource.resourceId);
                onDidAppearTmpBuf_BufArgsSerializer.writePointer(onDidAppearTmpBuf_BufCall);
                onDidAppearTmpBuf_BufArgsSerializer.writePointer(onDidAppearTmpBuf_BufCallSync);
                InteropNativeModule._CallCallbackSync(10, -1867723152, onDidAppearTmpBuf_BufArgsSerializer.asBuffer(), onDidAppearTmpBuf_BufArgsSerializer.length());
                onDidAppearTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onDidAppearTmpResult : (() => void) | undefined = onDidAppearTmpBuf
        const onDidDisappearTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onDidDisappearTmpBuf : (() => void) | undefined = undefined
        if ((onDidDisappearTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onDidDisappearTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onDidDisappearTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onDidDisappearTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onDidDisappearTmpBuf = ():void => {
                const onDidDisappearTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onDidDisappearTmpBuf_BufArgsSerializer.writeInt32(onDidDisappearTmpBuf_BufResource.resourceId);
                onDidDisappearTmpBuf_BufArgsSerializer.writePointer(onDidDisappearTmpBuf_BufCall);
                onDidDisappearTmpBuf_BufArgsSerializer.writePointer(onDidDisappearTmpBuf_BufCallSync);
                InteropNativeModule._CallCallbackSync(10, -1867723152, onDidDisappearTmpBuf_BufArgsSerializer.asBuffer(), onDidDisappearTmpBuf_BufArgsSerializer.length());
                onDidDisappearTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onDidDisappearTmpResult : (() => void) | undefined = onDidDisappearTmpBuf
        const onWillAppearTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onWillAppearTmpBuf : (() => void) | undefined = undefined
        if ((onWillAppearTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onWillAppearTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onWillAppearTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onWillAppearTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onWillAppearTmpBuf = ():void => {
                const onWillAppearTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onWillAppearTmpBuf_BufArgsSerializer.writeInt32(onWillAppearTmpBuf_BufResource.resourceId);
                onWillAppearTmpBuf_BufArgsSerializer.writePointer(onWillAppearTmpBuf_BufCall);
                onWillAppearTmpBuf_BufArgsSerializer.writePointer(onWillAppearTmpBuf_BufCallSync);
                InteropNativeModule._CallCallbackSync(10, -1867723152, onWillAppearTmpBuf_BufArgsSerializer.asBuffer(), onWillAppearTmpBuf_BufArgsSerializer.length());
                onWillAppearTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onWillAppearTmpResult : (() => void) | undefined = onWillAppearTmpBuf
        const onWillDisappearTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onWillDisappearTmpBuf : (() => void) | undefined = undefined
        if ((onWillDisappearTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onWillDisappearTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onWillDisappearTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onWillDisappearTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onWillDisappearTmpBuf = ():void => {
                const onWillDisappearTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onWillDisappearTmpBuf_BufArgsSerializer.writeInt32(onWillDisappearTmpBuf_BufResource.resourceId);
                onWillDisappearTmpBuf_BufArgsSerializer.writePointer(onWillDisappearTmpBuf_BufCall);
                onWillDisappearTmpBuf_BufArgsSerializer.writePointer(onWillDisappearTmpBuf_BufCallSync);
                InteropNativeModule._CallCallbackSync(10, -1867723152, onWillDisappearTmpBuf_BufArgsSerializer.asBuffer(), onWillDisappearTmpBuf_BufArgsSerializer.length());
                onWillDisappearTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onWillDisappearTmpResult : (() => void) | undefined = onWillDisappearTmpBuf
        const shadowTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let shadowTmpBuf : ShadowOptions | ShadowStyle | undefined = undefined
        if ((shadowTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const shadowTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let shadowTmpBuf_ : ShadowOptions | ShadowStyle | undefined
            if (shadowTmpBuf_UnionSelector == (0).toChar()) {
                shadowTmpBuf_ = ShadowOptions_serializer.read(valueDeserializer)
            } else if (shadowTmpBuf_UnionSelector == (1).toChar()) {
                shadowTmpBuf_ = ShadowStyle.fromValue(valueDeserializer.readInt32())
            } else {
                throw new Error("One of the branches for shadowTmpBuf_ has to be chosen through deserialisation.")
            }
            shadowTmpBuf = (shadowTmpBuf_ as ShadowOptions | ShadowStyle)
        }
        const shadowTmpResult : ShadowOptions | ShadowStyle | undefined = shadowTmpBuf
        const dateTimeOptionsTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let dateTimeOptionsTmpBuf : intl.DateTimeOptions | undefined = undefined
        if ((dateTimeOptionsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            dateTimeOptionsTmpBuf = intl_DateTimeOptions_serializer.read(valueDeserializer)
        }
        const dateTimeOptionsTmpResult : intl.DateTimeOptions | undefined = dateTimeOptionsTmpBuf
        const enableHoverModeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let enableHoverModeTmpBuf : boolean | undefined = undefined
        if ((enableHoverModeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            enableHoverModeTmpBuf = valueDeserializer.readBoolean()
        }
        const enableHoverModeTmpResult : boolean | undefined = enableHoverModeTmpBuf
        const hoverModeAreaTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let hoverModeAreaTmpBuf : HoverModeAreaType | undefined = undefined
        if ((hoverModeAreaTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            hoverModeAreaTmpBuf = HoverModeAreaType.fromValue(valueDeserializer.readInt32())
        }
        const hoverModeAreaTmpResult : HoverModeAreaType | undefined = hoverModeAreaTmpBuf
        const enableHapticFeedbackTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let enableHapticFeedbackTmpBuf : boolean | undefined = undefined
        if ((enableHapticFeedbackTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            enableHapticFeedbackTmpBuf = valueDeserializer.readBoolean()
        }
        const enableHapticFeedbackTmpResult : boolean | undefined = enableHapticFeedbackTmpBuf
        let value : TimePickerDialogOptions = ({selected: selectedTmpResult, format: formatTmpResult, start: startTmpResult, end: endTmpResult, useMilitaryTime: useMilitaryTimeTmpResult, disappearTextStyle: disappearTextStyleTmpResult, textStyle: textStyleTmpResult, acceptButtonStyle: acceptButtonStyleTmpResult, cancelButtonStyle: cancelButtonStyleTmpResult, selectedTextStyle: selectedTextStyleTmpResult, maskRect: maskRectTmpResult, alignment: alignmentTmpResult, offset: offsetTmpResult, onAccept: onAcceptTmpResult, onCancel: onCancelTmpResult, onChange: onChangeTmpResult, onEnterSelectedArea: onEnterSelectedAreaTmpResult, backgroundColor: backgroundColorTmpResult, backgroundBlurStyle: backgroundBlurStyleTmpResult, backgroundBlurStyleOptions: backgroundBlurStyleOptionsTmpResult, backgroundEffect: backgroundEffectTmpResult, enableCascade: enableCascadeTmpResult, onDidAppear: onDidAppearTmpResult, onDidDisappear: onDidDisappearTmpResult, onWillAppear: onWillAppearTmpResult, onWillDisappear: onWillDisappearTmpResult, shadow: shadowTmpResult, dateTimeOptions: dateTimeOptionsTmpResult, enableHoverMode: enableHoverModeTmpResult, hoverModeArea: hoverModeAreaTmpResult, enableHapticFeedback: enableHapticFeedbackTmpResult} as TimePickerDialogOptions)
        return value
    }
}
