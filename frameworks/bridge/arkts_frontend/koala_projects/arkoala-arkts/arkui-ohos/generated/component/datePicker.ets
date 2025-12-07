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
import { ArkThemeScopeManager } from "#arktheme"
import { PickerTextStyle_serializer, ArkCommonMethodPeer, CommonMethod, PickerTextStyle, Bindable, PickerDialogButtonStyle, Rectangle, BlurStyle, BackgroundBlurStyleOptions, BackgroundEffectOptions, ShadowOptions, ShadowStyle, HoverModeAreaType, ArkCommonMethodComponent, ArkCommonMethodStyle, Bindable_Date_serializer, PickerDialogButtonStyle_serializer, Rectangle_serializer, BackgroundBlurStyleOptions_serializer, BackgroundEffectOptions_serializer, ShadowOptions_serializer } from "./common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { CrownSensitivity, Color } from "./enums"
import { AttributeModifier, hookDatePickerAttributeModifier, AttributeUpdater } from "#handwritten"
import { ModifierStateManager } from '../CommonModifier';
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { ResourceColor, Offset, VoidCallback, Offset_serializer } from "./units"
import { Resource } from "global.resource"
import { DialogAlignment } from "./alertDialog"
import { default as intl } from "@ohos.intl"
import { DatePickerModifier } from "./../DatePickerModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
import { Resource_serializer } from "./../framework/resource"
import { intl_DateTimeOptions_serializer } from "./../framework/ohos.intl"
export class DatePickerDialogInternal {
    public static fromPtr(ptr: KPointer): DatePickerDialog {
        return new DatePickerDialog(ptr)
    }
}
export class DatePickerDialog implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, DatePickerDialog.getFinalizer())
    }
    constructor() {
        this(DatePickerDialog.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._DatePickerDialog_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._DatePickerDialog_getFinalizer()
    }
}
export class ArkDatePickerPeer extends ArkCommonMethodPeer {
    attributeSet?: DatePickerModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
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
    setOnDateChangeAttribute(value: ((value0: Date) => void) | undefined): void {
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
        throw new Error("Unimplemented method setDatePickerOptions")
    }
    lunar(value: boolean | undefined): this {
        throw new Error("Unimplemented method lunar")
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
    onDateChange(value: ((value0: Date) => void) | undefined): this {
        throw new Error("Unimplemented method onDateChange")
    }
    digitalCrownSensitivity(value: CrownSensitivity | undefined): this {
        throw new Error("Unimplemented method digitalCrownSensitivity")
    }
    enableHapticFeedback(value: boolean | undefined): this {
        throw new Error("Unimplemented method enableHapticFeedback")
    }
    attributeModifier(value: AttributeModifier<DatePickerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkDatePickerStyle extends ArkCommonMethodStyle implements DatePickerAttribute {
    lunar_value?: boolean | undefined
    disappearTextStyle_value?: PickerTextStyle | undefined
    textStyle_value?: PickerTextStyle | undefined
    selectedTextStyle_value?: PickerTextStyle | undefined
    onDateChange_value?: ((value0: Date) => void) | undefined
    digitalCrownSensitivity_value?: CrownSensitivity | undefined
    enableHapticFeedback_value?: boolean | undefined
    attributeModifier_value?: AttributeModifier<DatePickerAttribute> | AttributeModifier<CommonMethod> | undefined
    setDatePickerOptions(options?: DatePickerOptions): this {
        return this
    }
    lunar(value: boolean | undefined): this {
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
    onDateChange(value: ((value0: Date) => void) | undefined): this {
        return this
    }
    digitalCrownSensitivity(value: CrownSensitivity | undefined): this {
        return this
    }
    enableHapticFeedback(value: boolean | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<DatePickerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
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
    onDateAccept?: ((value0: Date) => void);
    onDateChange?: ((value0: Date) => void);
    backgroundColor?: ResourceColor;
    backgroundBlurStyle?: BlurStyle;
    backgroundBlurStyleOptions?: BackgroundBlurStyleOptions;
    backgroundEffect?: BackgroundEffectOptions;
    onDidAppear?: VoidCallback;
    onDidDisappear?: VoidCallback;
    onWillAppear?: VoidCallback;
    onWillDisappear?: VoidCallback;
    shadow?: ShadowOptions | ShadowStyle;
    dateTimeOptions?: intl.DateTimeOptions;
    enableHoverMode?: boolean;
    hoverModeArea?: HoverModeAreaType;
    enableHapticFeedback?: boolean;
}

export class ArkDatePickerComponent extends ArkCommonMethodComponent implements DatePickerAttribute {
    getPeer(): ArkDatePickerPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkDatePickerPeer)
    }
    public setDatePickerOptions(options?: DatePickerOptions): this {
        if (this.checkPriority("setDatePickerOptions")) {
            const options_casted = options as (DatePickerOptions | undefined)
            this.getPeer()?.setDatePickerOptionsAttribute(options_casted)
            this.applyOptionsFinish('DatePickerAttribute');
            return this
        }
        return this
    }
    public lunar(value: boolean | undefined): this {
        if (this.checkPriority("lunar")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setLunarAttribute(value_casted)
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
    public onDateChange(value: ((value0: Date) => void) | undefined): this {
        if (this.checkPriority("onDateChange")) {
            const value_casted = value as (((value0: Date) => void) | undefined)
            this.getPeer()?.setOnDateChangeAttribute(value_casted)
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
    public enableHapticFeedback(value: boolean | undefined): this {
        if (this.checkPriority("enableHapticFeedback")) {
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
    @memo
    style: ((attributes: DatePickerAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkDatePickerComponent>((): ArkDatePickerComponent => {
        return new ArkDatePickerComponent()
    })
    NodeAttach<ArkDatePickerPeer>((): ArkDatePickerPeer => ArkDatePickerPeer.create(receiver), (peer: ArkDatePickerPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
    })
}

export class DatePickerDialog_serializer {
    public static write(buffer: SerializerBase, value: DatePickerDialog): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): DatePickerDialog {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return DatePickerDialogInternal.fromPtr(ptr)
    }
}
export class DatePickerOptions_serializer {
    public static write(buffer: SerializerBase, value: DatePickerOptions): void {
        let valueSerializer : SerializerBase = buffer
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
        const modeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
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
            if (valueHolderForSelectedColorTmpValue instanceof Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForSelectedColorTmpValueForIdx0  = valueHolderForSelectedColorTmpValue as Color
                valueSerializer.writeInt32(valueHolderForSelectedColorTmpValueForIdx0.getOrdinal())
            } else if (valueHolderForSelectedColorTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForSelectedColorTmpValueForIdx1  = valueHolderForSelectedColorTmpValue as int32
                valueSerializer.writeInt32(valueHolderForSelectedColorTmpValueForIdx1)
            } else if (valueHolderForSelectedColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForSelectedColorTmpValueForIdx2  = valueHolderForSelectedColorTmpValue as string
                valueSerializer.writeString(valueHolderForSelectedColorTmpValueForIdx2)
            } else if (valueHolderForSelectedColorTmpValue instanceof Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForSelectedColorTmpValueForIdx3  = valueHolderForSelectedColorTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForSelectedColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForUnselectedColor  = value.unselectedColor
        if (valueHolderForUnselectedColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForUnselectedColorTmpValue  = valueHolderForUnselectedColor!
            if (valueHolderForUnselectedColorTmpValue instanceof Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForUnselectedColorTmpValueForIdx0  = valueHolderForUnselectedColorTmpValue as Color
                valueSerializer.writeInt32(valueHolderForUnselectedColorTmpValueForIdx0.getOrdinal())
            } else if (valueHolderForUnselectedColorTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForUnselectedColorTmpValueForIdx1  = valueHolderForUnselectedColorTmpValue as int32
                valueSerializer.writeInt32(valueHolderForUnselectedColorTmpValueForIdx1)
            } else if (valueHolderForUnselectedColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForUnselectedColorTmpValueForIdx2  = valueHolderForUnselectedColorTmpValue as string
                valueSerializer.writeString(valueHolderForUnselectedColorTmpValueForIdx2)
            } else if (valueHolderForUnselectedColorTmpValue instanceof Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForUnselectedColorTmpValueForIdx3  = valueHolderForUnselectedColorTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForUnselectedColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForStrokeColor  = value.strokeColor
        if (valueHolderForStrokeColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStrokeColorTmpValue  = valueHolderForStrokeColor!
            if (valueHolderForStrokeColorTmpValue instanceof Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForStrokeColorTmpValueForIdx0  = valueHolderForStrokeColorTmpValue as Color
                valueSerializer.writeInt32(valueHolderForStrokeColorTmpValueForIdx0.getOrdinal())
            } else if (valueHolderForStrokeColorTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForStrokeColorTmpValueForIdx1  = valueHolderForStrokeColorTmpValue as int32
                valueSerializer.writeInt32(valueHolderForStrokeColorTmpValueForIdx1)
            } else if (valueHolderForStrokeColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForStrokeColorTmpValueForIdx2  = valueHolderForStrokeColorTmpValue as string
                valueSerializer.writeString(valueHolderForStrokeColorTmpValueForIdx2)
            } else if (valueHolderForStrokeColorTmpValue instanceof Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForStrokeColorTmpValueForIdx3  = valueHolderForStrokeColorTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForStrokeColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): LunarSwitchStyle {
        let valueDeserializer : DeserializerBase = buffer
        const selectedColorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let selectedColorTmpBuf : ResourceColor | undefined = undefined
        if ((selectedColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const selectedColorTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let selectedColorTmpBuf_ : Color | int32 | string | Resource | undefined
            if (selectedColorTmpBuf_UnionSelector == (0).toChar()) {
                selectedColorTmpBuf_ = Color.values()[valueDeserializer.readInt32()]
            } else if (selectedColorTmpBuf_UnionSelector == (1).toChar()) {
                selectedColorTmpBuf_ = valueDeserializer.readInt32()
            } else if (selectedColorTmpBuf_UnionSelector == (2).toChar()) {
                selectedColorTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (selectedColorTmpBuf_UnionSelector == (3).toChar()) {
                selectedColorTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for selectedColorTmpBuf_ has to be chosen through deserialisation.")
            }
            selectedColorTmpBuf = (selectedColorTmpBuf_ as Color | int32 | string | Resource)
        }
        const selectedColorTmpResult : ResourceColor | undefined = selectedColorTmpBuf
        const unselectedColorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let unselectedColorTmpBuf : ResourceColor | undefined = undefined
        if ((unselectedColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const unselectedColorTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let unselectedColorTmpBuf_ : Color | int32 | string | Resource | undefined
            if (unselectedColorTmpBuf_UnionSelector == (0).toChar()) {
                unselectedColorTmpBuf_ = Color.values()[valueDeserializer.readInt32()]
            } else if (unselectedColorTmpBuf_UnionSelector == (1).toChar()) {
                unselectedColorTmpBuf_ = valueDeserializer.readInt32()
            } else if (unselectedColorTmpBuf_UnionSelector == (2).toChar()) {
                unselectedColorTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (unselectedColorTmpBuf_UnionSelector == (3).toChar()) {
                unselectedColorTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for unselectedColorTmpBuf_ has to be chosen through deserialisation.")
            }
            unselectedColorTmpBuf = (unselectedColorTmpBuf_ as Color | int32 | string | Resource)
        }
        const unselectedColorTmpResult : ResourceColor | undefined = unselectedColorTmpBuf
        const strokeColorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let strokeColorTmpBuf : ResourceColor | undefined = undefined
        if ((strokeColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const strokeColorTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let strokeColorTmpBuf_ : Color | int32 | string | Resource | undefined
            if (strokeColorTmpBuf_UnionSelector == (0).toChar()) {
                strokeColorTmpBuf_ = Color.values()[valueDeserializer.readInt32()]
            } else if (strokeColorTmpBuf_UnionSelector == (1).toChar()) {
                strokeColorTmpBuf_ = valueDeserializer.readInt32()
            } else if (strokeColorTmpBuf_UnionSelector == (2).toChar()) {
                strokeColorTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (strokeColorTmpBuf_UnionSelector == (3).toChar()) {
                strokeColorTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for strokeColorTmpBuf_ has to be chosen through deserialisation.")
            }
            strokeColorTmpBuf = (strokeColorTmpBuf_ as Color | int32 | string | Resource)
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
            if (valueHolderForBackgroundColorTmpValue instanceof Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx0  = valueHolderForBackgroundColorTmpValue as Color
                valueSerializer.writeInt32(valueHolderForBackgroundColorTmpValueForIdx0.getOrdinal())
            } else if (valueHolderForBackgroundColorTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx1  = valueHolderForBackgroundColorTmpValue as int32
                valueSerializer.writeInt32(valueHolderForBackgroundColorTmpValueForIdx1)
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
        const modeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let modeTmpBuf : DatePickerMode | undefined = undefined
        if ((modeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            modeTmpBuf = DatePickerMode.fromValue(valueDeserializer.readInt32())
        }
        const modeTmpResult : DatePickerMode | undefined = modeTmpBuf
        const lunarTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let lunarTmpBuf : boolean | undefined = undefined
        if ((lunarTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            lunarTmpBuf = valueDeserializer.readBoolean()
        }
        const lunarTmpResult : boolean | undefined = lunarTmpBuf
        const lunarSwitchTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let lunarSwitchTmpBuf : boolean | undefined = undefined
        if ((lunarSwitchTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            lunarSwitchTmpBuf = valueDeserializer.readBoolean()
        }
        const lunarSwitchTmpResult : boolean | undefined = lunarSwitchTmpBuf
        const lunarSwitchStyleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let lunarSwitchStyleTmpBuf : LunarSwitchStyle | undefined = undefined
        if ((lunarSwitchStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            lunarSwitchStyleTmpBuf = LunarSwitchStyle_serializer.read(valueDeserializer)
        }
        const lunarSwitchStyleTmpResult : LunarSwitchStyle | undefined = lunarSwitchStyleTmpBuf
        const showTimeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let showTimeTmpBuf : boolean | undefined = undefined
        if ((showTimeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            showTimeTmpBuf = valueDeserializer.readBoolean()
        }
        const showTimeTmpResult : boolean | undefined = showTimeTmpBuf
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
        const onCancelTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onCancelTmpBuf : VoidCallback | undefined = undefined
        if ((onCancelTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onCancelTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onCancelTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onCancelTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onCancelTmpBuf = ():void => {
                const onCancelTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onCancelTmpBuf_BufArgsSerializer.writeInt32(onCancelTmpBuf_BufResource.resourceId);
                onCancelTmpBuf_BufArgsSerializer.writePointer(onCancelTmpBuf_BufCall);
                onCancelTmpBuf_BufArgsSerializer.writePointer(onCancelTmpBuf_BufCallSync);
                InteropNativeModule._CallCallbackSync(10, -2038961969, onCancelTmpBuf_BufArgsSerializer.asBuffer(), onCancelTmpBuf_BufArgsSerializer.length());
                onCancelTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onCancelTmpResult : VoidCallback | undefined = onCancelTmpBuf
        const onDateAcceptTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onDateAcceptTmpBuf : ((value0: Date) => void) | undefined = undefined
        if ((onDateAcceptTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onDateAcceptTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onDateAcceptTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onDateAcceptTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onDateAcceptTmpBuf = (value0: Date):void => {
                const onDateAcceptTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onDateAcceptTmpBuf_BufArgsSerializer.writeInt32(onDateAcceptTmpBuf_BufResource.resourceId);
                onDateAcceptTmpBuf_BufArgsSerializer.writePointer(onDateAcceptTmpBuf_BufCall);
                onDateAcceptTmpBuf_BufArgsSerializer.writePointer(onDateAcceptTmpBuf_BufCallSync);
                onDateAcceptTmpBuf_BufArgsSerializer.writeInt64(value0.getTime().toLong());
                InteropNativeModule._CallCallbackSync(10, 1405382363, onDateAcceptTmpBuf_BufArgsSerializer.asBuffer(), onDateAcceptTmpBuf_BufArgsSerializer.length());
                onDateAcceptTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onDateAcceptTmpResult : ((value0: Date) => void) | undefined = onDateAcceptTmpBuf
        const onDateChangeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onDateChangeTmpBuf : ((value0: Date) => void) | undefined = undefined
        if ((onDateChangeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onDateChangeTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onDateChangeTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onDateChangeTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onDateChangeTmpBuf = (value0: Date):void => {
                const onDateChangeTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onDateChangeTmpBuf_BufArgsSerializer.writeInt32(onDateChangeTmpBuf_BufResource.resourceId);
                onDateChangeTmpBuf_BufArgsSerializer.writePointer(onDateChangeTmpBuf_BufCall);
                onDateChangeTmpBuf_BufArgsSerializer.writePointer(onDateChangeTmpBuf_BufCallSync);
                onDateChangeTmpBuf_BufArgsSerializer.writeInt64(value0.getTime().toLong());
                InteropNativeModule._CallCallbackSync(10, 1405382363, onDateChangeTmpBuf_BufArgsSerializer.asBuffer(), onDateChangeTmpBuf_BufArgsSerializer.length());
                onDateChangeTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onDateChangeTmpResult : ((value0: Date) => void) | undefined = onDateChangeTmpBuf
        const backgroundColorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundColorTmpBuf : ResourceColor | undefined = undefined
        if ((backgroundColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const backgroundColorTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let backgroundColorTmpBuf_ : Color | int32 | string | Resource | undefined
            if (backgroundColorTmpBuf_UnionSelector == (0).toChar()) {
                backgroundColorTmpBuf_ = Color.values()[valueDeserializer.readInt32()]
            } else if (backgroundColorTmpBuf_UnionSelector == (1).toChar()) {
                backgroundColorTmpBuf_ = valueDeserializer.readInt32()
            } else if (backgroundColorTmpBuf_UnionSelector == (2).toChar()) {
                backgroundColorTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (backgroundColorTmpBuf_UnionSelector == (3).toChar()) {
                backgroundColorTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for backgroundColorTmpBuf_ has to be chosen through deserialisation.")
            }
            backgroundColorTmpBuf = (backgroundColorTmpBuf_ as Color | int32 | string | Resource)
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
        const onDidAppearTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onDidAppearTmpBuf : VoidCallback | undefined = undefined
        if ((onDidAppearTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onDidAppearTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onDidAppearTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onDidAppearTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onDidAppearTmpBuf = ():void => {
                const onDidAppearTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onDidAppearTmpBuf_BufArgsSerializer.writeInt32(onDidAppearTmpBuf_BufResource.resourceId);
                onDidAppearTmpBuf_BufArgsSerializer.writePointer(onDidAppearTmpBuf_BufCall);
                onDidAppearTmpBuf_BufArgsSerializer.writePointer(onDidAppearTmpBuf_BufCallSync);
                InteropNativeModule._CallCallbackSync(10, -2038961969, onDidAppearTmpBuf_BufArgsSerializer.asBuffer(), onDidAppearTmpBuf_BufArgsSerializer.length());
                onDidAppearTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onDidAppearTmpResult : VoidCallback | undefined = onDidAppearTmpBuf
        const onDidDisappearTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onDidDisappearTmpBuf : VoidCallback | undefined = undefined
        if ((onDidDisappearTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onDidDisappearTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onDidDisappearTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onDidDisappearTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onDidDisappearTmpBuf = ():void => {
                const onDidDisappearTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onDidDisappearTmpBuf_BufArgsSerializer.writeInt32(onDidDisappearTmpBuf_BufResource.resourceId);
                onDidDisappearTmpBuf_BufArgsSerializer.writePointer(onDidDisappearTmpBuf_BufCall);
                onDidDisappearTmpBuf_BufArgsSerializer.writePointer(onDidDisappearTmpBuf_BufCallSync);
                InteropNativeModule._CallCallbackSync(10, -2038961969, onDidDisappearTmpBuf_BufArgsSerializer.asBuffer(), onDidDisappearTmpBuf_BufArgsSerializer.length());
                onDidDisappearTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onDidDisappearTmpResult : VoidCallback | undefined = onDidDisappearTmpBuf
        const onWillAppearTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onWillAppearTmpBuf : VoidCallback | undefined = undefined
        if ((onWillAppearTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onWillAppearTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onWillAppearTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onWillAppearTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onWillAppearTmpBuf = ():void => {
                const onWillAppearTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onWillAppearTmpBuf_BufArgsSerializer.writeInt32(onWillAppearTmpBuf_BufResource.resourceId);
                onWillAppearTmpBuf_BufArgsSerializer.writePointer(onWillAppearTmpBuf_BufCall);
                onWillAppearTmpBuf_BufArgsSerializer.writePointer(onWillAppearTmpBuf_BufCallSync);
                InteropNativeModule._CallCallbackSync(10, -2038961969, onWillAppearTmpBuf_BufArgsSerializer.asBuffer(), onWillAppearTmpBuf_BufArgsSerializer.length());
                onWillAppearTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onWillAppearTmpResult : VoidCallback | undefined = onWillAppearTmpBuf
        const onWillDisappearTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onWillDisappearTmpBuf : VoidCallback | undefined = undefined
        if ((onWillDisappearTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onWillDisappearTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onWillDisappearTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onWillDisappearTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onWillDisappearTmpBuf = ():void => {
                const onWillDisappearTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onWillDisappearTmpBuf_BufArgsSerializer.writeInt32(onWillDisappearTmpBuf_BufResource.resourceId);
                onWillDisappearTmpBuf_BufArgsSerializer.writePointer(onWillDisappearTmpBuf_BufCall);
                onWillDisappearTmpBuf_BufArgsSerializer.writePointer(onWillDisappearTmpBuf_BufCallSync);
                InteropNativeModule._CallCallbackSync(10, -2038961969, onWillDisappearTmpBuf_BufArgsSerializer.asBuffer(), onWillDisappearTmpBuf_BufArgsSerializer.length());
                onWillDisappearTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onWillDisappearTmpResult : VoidCallback | undefined = onWillDisappearTmpBuf
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
        let value : DatePickerDialogOptions = ({start: startTmpResult, end: endTmpResult, selected: selectedTmpResult, mode: modeTmpResult, lunar: lunarTmpResult, lunarSwitch: lunarSwitchTmpResult, lunarSwitchStyle: lunarSwitchStyleTmpResult, showTime: showTimeTmpResult, useMilitaryTime: useMilitaryTimeTmpResult, disappearTextStyle: disappearTextStyleTmpResult, textStyle: textStyleTmpResult, acceptButtonStyle: acceptButtonStyleTmpResult, cancelButtonStyle: cancelButtonStyleTmpResult, selectedTextStyle: selectedTextStyleTmpResult, maskRect: maskRectTmpResult, alignment: alignmentTmpResult, offset: offsetTmpResult, onCancel: onCancelTmpResult, onDateAccept: onDateAcceptTmpResult, onDateChange: onDateChangeTmpResult, backgroundColor: backgroundColorTmpResult, backgroundBlurStyle: backgroundBlurStyleTmpResult, backgroundBlurStyleOptions: backgroundBlurStyleOptionsTmpResult, backgroundEffect: backgroundEffectTmpResult, onDidAppear: onDidAppearTmpResult, onDidDisappear: onDidDisappearTmpResult, onWillAppear: onWillAppearTmpResult, onWillDisappear: onWillDisappearTmpResult, shadow: shadowTmpResult, dateTimeOptions: dateTimeOptionsTmpResult, enableHoverMode: enableHoverModeTmpResult, hoverModeArea: hoverModeAreaTmpResult, enableHapticFeedback: enableHapticFeedbackTmpResult} as DatePickerDialogOptions)
        return value
    }
}
