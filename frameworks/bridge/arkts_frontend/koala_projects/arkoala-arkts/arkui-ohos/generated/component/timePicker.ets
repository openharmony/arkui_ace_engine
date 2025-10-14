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
import { PickerTextStyle_serializer, ArkCommonMethodPeer, CommonMethod, PickerTextStyle, Bindable, PickerDialogButtonStyle, Rectangle, BlurStyle, BackgroundBlurStyleOptions, BackgroundEffectOptions, ShadowOptions, ShadowStyle, HoverModeAreaType, ArkCommonMethodComponent, ArkCommonMethodStyle, Bindable_Date_serializer } from "./common"
import { intl_DateTimeOptions_serializer } from "./../framework/ohos.intl"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { default as intl } from "@ohos.intl"
import { CrownSensitivity, Color } from "./enums"
import { AttributeModifier, hookTimePickerAttributeModifier, AttributeUpdater } from "#handwritten"
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { DialogAlignment } from "./alertDialog"
import { Offset, ResourceColor } from "./units"
import { Resource } from "global.resource"
import { TimePickerModifier } from "./../TimePickerModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
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
        hookTimePickerAttributeModifier(this, value);
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
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
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForSelectedTmpValueForIdx0  = valueHolderForSelectedTmpValue as Date
                valueSerializer.writeInt64(valueHolderForSelectedTmpValueForIdx0.getTime().toLong())
            } else if (valueHolderForSelectedTmpValue instanceof Bindable<Date>) {
                valueSerializer.writeInt8((1).toChar())
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
