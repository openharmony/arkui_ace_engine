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
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, DeserializerBase, nullptr, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { PickerTextStyle_serializer, ArkCommonMethodPeer, CommonMethod, PickerTextStyle, PickerDialogButtonStyle, Rectangle, BlurStyle, BackgroundBlurStyleOptions, BackgroundEffectOptions, ShadowOptions, ShadowStyle, HoverModeAreaType, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonMethodSet } from "./common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { CrownSensitivity, Color } from "./enums"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { ResourceColor, Offset, VoidCallback } from "./units"
import { Resource } from "./../generated/resource"
import { DialogAlignment } from "./alertDialog"
import { intl } from "./../generated/ohos.intl"
import { NodeAttach, remember } from "@koalaui/runtime"
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
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkDatePickerPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._DatePicker_construct(peerId, flags)
        const _peer  = new ArkDatePickerPeer(_peerPtr, peerId, "DatePicker", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setDatePickerOptionsAttribute(options?: DatePickerOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8((options_type).toChar())
        if ((options_type) != (RuntimeType.UNDEFINED)) {
            const options_value  = options!
            DatePickerOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._DatePickerInterface_setDatePickerOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setLunarAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._DatePickerAttribute_setLunar(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDisappearTextStyleAttribute(value: PickerTextStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            PickerTextStyle_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._DatePickerAttribute_setDisappearTextStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTextStyleAttribute(value: PickerTextStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            PickerTextStyle_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._DatePickerAttribute_setTextStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectedTextStyleAttribute(value: PickerTextStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            PickerTextStyle_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._DatePickerAttribute_setSelectedTextStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnDateChangeAttribute(value: ((value0: Date) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._DatePickerAttribute_setOnDateChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDigitalCrownSensitivityAttribute(value: CrownSensitivity | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as CrownSensitivity)
            thisSerializer.writeInt32(TypeChecker.CrownSensitivity_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._DatePickerAttribute_setDigitalCrownSensitivity(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableHapticFeedbackAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._DatePickerAttribute_setEnableHapticFeedback(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    set_onChangeEvent_selectedAttribute(callback_: ((value0: Date) => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(callback_)
        ArkUIGeneratedNativeModule._DatePickerAttribute_set_onChangeEvent_selected(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface DatePickerResult {
    year?: number;
    month?: number;
    day?: number;
}
export enum DatePickerMode {
    DATE = 0,
    YEAR_AND_MONTH = 1,
    MONTH_AND_DAY = 2
}
export interface DatePickerOptions {
    start?: Date;
    end?: Date;
    selected?: Date;
    mode?: DatePickerMode;
}
export interface DatePickerAttribute extends CommonMethod {
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
    _onChangeEvent_selected(callback_: ((value0: Date) => void)): void {
        throw new Error("Unimplemented method _onChangeEvent_selected")
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
    public lunar(value: boolean | undefined): this {
        return this
    }
    public disappearTextStyle(value: PickerTextStyle | undefined): this {
        return this
    }
    public textStyle(value: PickerTextStyle | undefined): this {
        return this
    }
    public selectedTextStyle(value: PickerTextStyle | undefined): this {
        return this
    }
    public onDateChange(value: ((value0: Date) => void) | undefined): this {
        return this
    }
    public digitalCrownSensitivity(value: CrownSensitivity | undefined): this {
        return this
    }
    public enableHapticFeedback(value: boolean | undefined): this {
        return this
    }
    public _onChangeEvent_selected(callback_: ((value0: Date) => void)): void {
        throw new Error("Unimplemented")
    }
    public attributeModifier(value: AttributeModifier<DatePickerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: DatePickerAttribute): void {
        super.apply(target)
        if (this.lunar_value !== undefined)
            target.lunar(this.lunar_value!)
        if (this.disappearTextStyle_value !== undefined)
            target.disappearTextStyle(this.disappearTextStyle_value!)
        if (this.textStyle_value !== undefined)
            target.textStyle(this.textStyle_value!)
        if (this.selectedTextStyle_value !== undefined)
            target.selectedTextStyle(this.selectedTextStyle_value!)
        if (this.onDateChange_value !== undefined)
            target.onDateChange(this.onDateChange_value!)
        if (this.digitalCrownSensitivity_value !== undefined)
            target.digitalCrownSensitivity(this.digitalCrownSensitivity_value!)
        if (this.enableHapticFeedback_value !== undefined)
            target.enableHapticFeedback(this.enableHapticFeedback_value!)
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
        return (this.peer as ArkDatePickerPeer)
    }
    public setDatePickerOptions(options?: DatePickerOptions): this {
        if (this.checkPriority("setDatePickerOptions")) {
            const options_casted = options as (DatePickerOptions | undefined)
            this.getPeer()?.setDatePickerOptionsAttribute(options_casted)
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
    public _onChangeEvent_selected(callback_: ((value0: Date) => void)): void {
        if (this.checkPriority("_onChangeEvent_selected")) {
            const callback__casted = callback_ as (((value0: Date) => void))
            this.getPeer()?.set_onChangeEvent_selectedAttribute(callback__casted)
            return
        }
        return
    }
    public attributeModifier(value: AttributeModifier<DatePickerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withDatePickerStyle(receiver: DatePickerAttribute, modifier: AttributeModifier<DatePickerAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkDatePickerStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("DatePicker")
// export function DatePicker(
//     options?: DatePickerOptions,
//     @memo
//     content_?: () => void,
// ): DatePickerAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function DatePicker(
    @memo
    style: ((attributes: DatePickerAttribute) => void) | undefined,
    options?: DatePickerOptions,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkDatePickerComponent>((): ArkDatePickerComponent => {
        return new ArkDatePickerComponent()
    })
    NodeAttach<ArkDatePickerPeer>((): ArkDatePickerPeer => ArkDatePickerPeer.create(receiver), (_: ArkDatePickerPeer): void => {
        receiver.setDatePickerOptions(options)
        style?.(receiver)
        withDatePickerStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkDatePickerSet extends ArkCommonMethodSet implements DatePickerAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _lunar_flag?: boolean
    _lunar0_value?: boolean | undefined
    _disappearTextStyle_flag?: boolean
    _disappearTextStyle0_value?: PickerTextStyle | undefined
    _textStyle_flag?: boolean
    _textStyle0_value?: PickerTextStyle | undefined
    _selectedTextStyle_flag?: boolean
    _selectedTextStyle0_value?: PickerTextStyle | undefined
    _onDateChange_flag?: boolean
    _onDateChange0_value?: ((value0: Date) => void) | undefined
    _digitalCrownSensitivity_flag?: boolean
    _digitalCrownSensitivity0_value?: CrownSensitivity | undefined
    _enableHapticFeedback_flag?: boolean
    _enableHapticFeedback0_value?: boolean | undefined
    __onChangeEvent_selected_flag?: boolean
    __onChangeEvent_selected0_value?: ((value0: Date) => void)
    applyModifierPatch(component: DatePickerAttribute): void {
        if (this._lunar_flag)
            component.lunar((this._lunar0_value as boolean | undefined))
        if (this._disappearTextStyle_flag)
            component.disappearTextStyle((this._disappearTextStyle0_value as PickerTextStyle | undefined))
        if (this._textStyle_flag)
            component.textStyle((this._textStyle0_value as PickerTextStyle | undefined))
        if (this._selectedTextStyle_flag)
            component.selectedTextStyle((this._selectedTextStyle0_value as PickerTextStyle | undefined))
        if (this._onDateChange_flag)
            component.onDateChange((this._onDateChange0_value as ((value0: Date) => void) | undefined))
        if (this._digitalCrownSensitivity_flag)
            component.digitalCrownSensitivity((this._digitalCrownSensitivity0_value as CrownSensitivity | undefined))
        if (this._enableHapticFeedback_flag)
            component.enableHapticFeedback((this._enableHapticFeedback0_value as boolean | undefined))
    }
    public lunar(value: boolean | undefined): this {
        this._lunar_flag = true
        this._lunar0_value = value
        return this
    }
    public disappearTextStyle(value: PickerTextStyle | undefined): this {
        this._disappearTextStyle_flag = true
        this._disappearTextStyle0_value = value
        return this
    }
    public textStyle(value: PickerTextStyle | undefined): this {
        this._textStyle_flag = true
        this._textStyle0_value = value
        return this
    }
    public selectedTextStyle(value: PickerTextStyle | undefined): this {
        this._selectedTextStyle_flag = true
        this._selectedTextStyle0_value = value
        return this
    }
    public onDateChange(value: ((value0: Date) => void) | undefined): this {
        this._onDateChange_flag = true
        this._onDateChange0_value = value
        return this
    }
    public digitalCrownSensitivity(value: CrownSensitivity | undefined): this {
        this._digitalCrownSensitivity_flag = true
        this._digitalCrownSensitivity0_value = value
        return this
    }
    public enableHapticFeedback(value: boolean | undefined): this {
        this._enableHapticFeedback_flag = true
        this._enableHapticFeedback0_value = value
        return this
    }
    public _onChangeEvent_selected(callback_: ((value0: Date) => void)): void {
    }
    public attributeModifier(value: AttributeModifier<DatePickerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
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
        const value_start  = value.start
        let value_start_type : int32 = RuntimeType.UNDEFINED
        value_start_type = runtimeType(value_start)
        valueSerializer.writeInt8((value_start_type).toChar())
        if ((value_start_type) != (RuntimeType.UNDEFINED)) {
            const value_start_value  = value_start!
            valueSerializer.writeInt64(value_start_value.getTime().toLong())
        }
        const value_end  = value.end
        let value_end_type : int32 = RuntimeType.UNDEFINED
        value_end_type = runtimeType(value_end)
        valueSerializer.writeInt8((value_end_type).toChar())
        if ((value_end_type) != (RuntimeType.UNDEFINED)) {
            const value_end_value  = value_end!
            valueSerializer.writeInt64(value_end_value.getTime().toLong())
        }
        const value_selected  = value.selected
        let value_selected_type : int32 = RuntimeType.UNDEFINED
        value_selected_type = runtimeType(value_selected)
        valueSerializer.writeInt8((value_selected_type).toChar())
        if ((value_selected_type) != (RuntimeType.UNDEFINED)) {
            const value_selected_value  = value_selected!
            valueSerializer.writeInt64(value_selected_value.getTime().toLong())
        }
        const value_mode  = value.mode
        let value_mode_type : int32 = RuntimeType.UNDEFINED
        value_mode_type = runtimeType(value_mode)
        valueSerializer.writeInt8((value_mode_type).toChar())
        if ((value_mode_type) != (RuntimeType.UNDEFINED)) {
            const value_mode_value  = (value_mode as DatePickerMode)
            valueSerializer.writeInt32(TypeChecker.DatePickerMode_ToNumeric(value_mode_value))
        }
    }
    public static read(buffer: DeserializerBase): DatePickerOptions {
        let valueDeserializer : DeserializerBase = buffer
        const start_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let start_buf : Date | undefined
        if ((start_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            start_buf = new Date(valueDeserializer.readInt64())
        }
        const start_result : Date | undefined = start_buf
        const end_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let end_buf : Date | undefined
        if ((end_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            end_buf = new Date(valueDeserializer.readInt64())
        }
        const end_result : Date | undefined = end_buf
        const selected_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let selected_buf : Date | undefined
        if ((selected_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            selected_buf = new Date(valueDeserializer.readInt64())
        }
        const selected_result : Date | undefined = selected_buf
        const mode_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let mode_buf : DatePickerMode | undefined
        if ((mode_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            mode_buf = TypeChecker.DatePickerMode_FromNumeric(valueDeserializer.readInt32())
        }
        const mode_result : DatePickerMode | undefined = mode_buf
        let value : DatePickerOptions = ({start: start_result, end: end_result, selected: selected_result, mode: mode_result} as DatePickerOptions)
        return value
    }
}
