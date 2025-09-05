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
import { intl_DateTimeOptions_serializer, intl } from "./../generated/ohos.intl"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { CrownSensitivity, Color } from "./enums"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { DialogAlignment } from "./alertDialog"
import { Offset, ResourceColor } from "./units"
import { Resource } from "./../generated/resource"
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
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkTimePickerPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._TimePicker_construct(peerId, flags)
        const _peer  = new ArkTimePickerPeer(_peerPtr, peerId, "TimePicker", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setTimePickerOptionsAttribute(options?: TimePickerOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8((options_type).toChar())
        if ((options_type) != (RuntimeType.UNDEFINED)) {
            const options_value  = options!
            TimePickerOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._TimePickerInterface_setTimePickerOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setUseMilitaryTimeAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._TimePickerAttribute_setUseMilitaryTime(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setLoopAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._TimePickerAttribute_setLoop(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._TimePickerAttribute_setDisappearTextStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._TimePickerAttribute_setTextStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._TimePickerAttribute_setSelectedTextStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDateTimeOptionsAttribute(value: intl.DateTimeOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            intl_DateTimeOptions_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._TimePickerAttribute_setDateTimeOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnChangeAttribute(value: OnTimePickerChangeCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TimePickerAttribute_setOnChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnEnterSelectedAreaAttribute(value: ((value0: TimePickerResult) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TimePickerAttribute_setOnEnterSelectedArea(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._TimePickerAttribute_setEnableHapticFeedback(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._TimePickerAttribute_setDigitalCrownSensitivity(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableCascadeAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._TimePickerAttribute_setEnableCascade(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    set_onChangeEvent_selectedAttribute(callback_: ((selected: Date) => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(callback_)
        ArkUIGeneratedNativeModule._TimePickerAttribute_set_onChangeEvent_selected(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface TimePickerResult {
    hour: number;
    minute: number;
    second: number;
}
export enum TimePickerFormat {
    HOUR_MINUTE = 0,
    HOUR_MINUTE_SECOND = 1
}
export interface TimePickerOptions {
    selected?: Date;
    format?: TimePickerFormat;
    start?: Date;
    end?: Date;
}
export type OnTimePickerChangeCallback = (result: TimePickerResult) => void;
export interface TimePickerAttribute extends CommonMethod {
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
    _onChangeEvent_selected(callback_: ((selected: Date) => void)): void {
        throw new Error("Unimplemented method _onChangeEvent_selected")
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
    public useMilitaryTime(value: boolean | undefined): this {
        return this
    }
    public loop(value: boolean | undefined): this {
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
    public dateTimeOptions(value: intl.DateTimeOptions | undefined): this {
        return this
    }
    public onChange(value: OnTimePickerChangeCallback | undefined): this {
        return this
    }
    public onEnterSelectedArea(value: ((value0: TimePickerResult) => void) | undefined): this {
        return this
    }
    public enableHapticFeedback(value: boolean | undefined): this {
        return this
    }
    public digitalCrownSensitivity(value: CrownSensitivity | undefined): this {
        return this
    }
    public enableCascade(value: boolean | undefined): this {
        return this
    }
    public _onChangeEvent_selected(callback_: ((selected: Date) => void)): void {
        throw new Error("Unimplemented")
    }
    public attributeModifier(value: AttributeModifier<TimePickerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: TimePickerAttribute): void {
        super.apply(target)
        if (this.useMilitaryTime_value !== undefined)
            target.useMilitaryTime(this.useMilitaryTime_value!)
        if (this.loop_value !== undefined)
            target.loop(this.loop_value!)
        if (this.disappearTextStyle_value !== undefined)
            target.disappearTextStyle(this.disappearTextStyle_value!)
        if (this.textStyle_value !== undefined)
            target.textStyle(this.textStyle_value!)
        if (this.selectedTextStyle_value !== undefined)
            target.selectedTextStyle(this.selectedTextStyle_value!)
        if (this.dateTimeOptions_value !== undefined)
            target.dateTimeOptions(this.dateTimeOptions_value!)
        if (this.onChange_value !== undefined)
            target.onChange(this.onChange_value!)
        if (this.onEnterSelectedArea_value !== undefined)
            target.onEnterSelectedArea(this.onEnterSelectedArea_value!)
        if (this.enableHapticFeedback_value !== undefined)
            target.enableHapticFeedback(this.enableHapticFeedback_value!)
        if (this.digitalCrownSensitivity_value !== undefined)
            target.digitalCrownSensitivity(this.digitalCrownSensitivity_value!)
        if (this.enableCascade_value !== undefined)
            target.enableCascade(this.enableCascade_value!)
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
    public _onChangeEvent_selected(callback_: ((selected: Date) => void)): void {
        if (this.checkPriority("_onChangeEvent_selected")) {
            const callback__casted = callback_ as (((selected: Date) => void))
            this.getPeer()?.set_onChangeEvent_selectedAttribute(callback__casted)
            return
        }
        return
    }
    public attributeModifier(value: AttributeModifier<TimePickerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withTimePickerStyle(receiver: TimePickerAttribute, modifier: AttributeModifier<TimePickerAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkTimePickerStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("TimePicker")
// export function TimePicker(
//     options?: TimePickerOptions,
//     @memo
//     content_?: () => void,
// ): TimePickerAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function TimePicker(
    @memo
    style: ((attributes: TimePickerAttribute) => void) | undefined,
    options?: TimePickerOptions,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkTimePickerComponent>((): ArkTimePickerComponent => {
        return new ArkTimePickerComponent()
    })
    NodeAttach<ArkTimePickerPeer>((): ArkTimePickerPeer => ArkTimePickerPeer.create(receiver), (_: ArkTimePickerPeer): void => {
        receiver.setTimePickerOptions(options)
        style?.(receiver)
        withTimePickerStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkTimePickerSet extends ArkCommonMethodSet implements TimePickerAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _useMilitaryTime_flag?: boolean
    _useMilitaryTime0_value?: boolean | undefined
    _loop_flag?: boolean
    _loop0_value?: boolean | undefined
    _disappearTextStyle_flag?: boolean
    _disappearTextStyle0_value?: PickerTextStyle | undefined
    _textStyle_flag?: boolean
    _textStyle0_value?: PickerTextStyle | undefined
    _selectedTextStyle_flag?: boolean
    _selectedTextStyle0_value?: PickerTextStyle | undefined
    _dateTimeOptions_flag?: boolean
    _dateTimeOptions0_value?: intl.DateTimeOptions | undefined
    _onChange_flag?: boolean
    _onChange0_value?: OnTimePickerChangeCallback | undefined
    _onEnterSelectedArea_flag?: boolean
    _onEnterSelectedArea0_value?: ((value0: TimePickerResult) => void) | undefined
    _enableHapticFeedback_flag?: boolean
    _enableHapticFeedback0_value?: boolean | undefined
    _digitalCrownSensitivity_flag?: boolean
    _digitalCrownSensitivity0_value?: CrownSensitivity | undefined
    _enableCascade_flag?: boolean
    _enableCascade0_value?: boolean | undefined
    __onChangeEvent_selected_flag?: boolean
    __onChangeEvent_selected0_value?: ((selected: Date) => void)
    applyModifierPatch(component: TimePickerAttribute): void {
        if (this._useMilitaryTime_flag)
            component.useMilitaryTime((this._useMilitaryTime0_value as boolean | undefined))
        if (this._loop_flag)
            component.loop((this._loop0_value as boolean | undefined))
        if (this._disappearTextStyle_flag)
            component.disappearTextStyle((this._disappearTextStyle0_value as PickerTextStyle | undefined))
        if (this._textStyle_flag)
            component.textStyle((this._textStyle0_value as PickerTextStyle | undefined))
        if (this._selectedTextStyle_flag)
            component.selectedTextStyle((this._selectedTextStyle0_value as PickerTextStyle | undefined))
        if (this._dateTimeOptions_flag)
            component.dateTimeOptions((this._dateTimeOptions0_value as intl.DateTimeOptions | undefined))
        if (this._onChange_flag)
            component.onChange((this._onChange0_value as OnTimePickerChangeCallback | undefined))
        if (this._onEnterSelectedArea_flag)
            component.onEnterSelectedArea((this._onEnterSelectedArea0_value as ((value0: TimePickerResult) => void) | undefined))
        if (this._enableHapticFeedback_flag)
            component.enableHapticFeedback((this._enableHapticFeedback0_value as boolean | undefined))
        if (this._digitalCrownSensitivity_flag)
            component.digitalCrownSensitivity((this._digitalCrownSensitivity0_value as CrownSensitivity | undefined))
        if (this._enableCascade_flag)
            component.enableCascade((this._enableCascade0_value as boolean | undefined))
    }
    public useMilitaryTime(value: boolean | undefined): this {
        this._useMilitaryTime_flag = true
        this._useMilitaryTime0_value = value
        return this
    }
    public loop(value: boolean | undefined): this {
        this._loop_flag = true
        this._loop0_value = value
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
    public dateTimeOptions(value: intl.DateTimeOptions | undefined): this {
        this._dateTimeOptions_flag = true
        this._dateTimeOptions0_value = value
        return this
    }
    public onChange(value: OnTimePickerChangeCallback | undefined): this {
        this._onChange_flag = true
        this._onChange0_value = value
        return this
    }
    public onEnterSelectedArea(value: ((value0: TimePickerResult) => void) | undefined): this {
        this._onEnterSelectedArea_flag = true
        this._onEnterSelectedArea0_value = value
        return this
    }
    public enableHapticFeedback(value: boolean | undefined): this {
        this._enableHapticFeedback_flag = true
        this._enableHapticFeedback0_value = value
        return this
    }
    public digitalCrownSensitivity(value: CrownSensitivity | undefined): this {
        this._digitalCrownSensitivity_flag = true
        this._digitalCrownSensitivity0_value = value
        return this
    }
    public enableCascade(value: boolean | undefined): this {
        this._enableCascade_flag = true
        this._enableCascade0_value = value
        return this
    }
    public _onChangeEvent_selected(callback_: ((selected: Date) => void)): void {
    }
    public attributeModifier(value: AttributeModifier<TimePickerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
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
        const value_hour  = value.hour
        valueSerializer.writeNumber(value_hour)
        const value_minute  = value.minute
        valueSerializer.writeNumber(value_minute)
        const value_second  = value.second
        valueSerializer.writeNumber(value_second)
    }
    public static read(buffer: DeserializerBase): TimePickerResult {
        let valueDeserializer : DeserializerBase = buffer
        const hour_result : number = (valueDeserializer.readNumber() as number)
        const minute_result : number = (valueDeserializer.readNumber() as number)
        const second_result : number = (valueDeserializer.readNumber() as number)
        let value : TimePickerResult = ({hour: hour_result, minute: minute_result, second: second_result} as TimePickerResult)
        return value
    }
}
export class TimePickerOptions_serializer {
    public static write(buffer: SerializerBase, value: TimePickerOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_selected  = value.selected
        let value_selected_type : int32 = RuntimeType.UNDEFINED
        value_selected_type = runtimeType(value_selected)
        valueSerializer.writeInt8((value_selected_type).toChar())
        if ((value_selected_type) != (RuntimeType.UNDEFINED)) {
            const value_selected_value  = value_selected!
            valueSerializer.writeInt64(value_selected_value.getTime().toLong())
        }
        const value_format  = value.format
        let value_format_type : int32 = RuntimeType.UNDEFINED
        value_format_type = runtimeType(value_format)
        valueSerializer.writeInt8((value_format_type).toChar())
        if ((value_format_type) != (RuntimeType.UNDEFINED)) {
            const value_format_value  = (value_format as TimePickerFormat)
            valueSerializer.writeInt32(TypeChecker.TimePickerFormat_ToNumeric(value_format_value))
        }
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
    }
    public static read(buffer: DeserializerBase): TimePickerOptions {
        let valueDeserializer : DeserializerBase = buffer
        const selected_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let selected_buf : Date | undefined
        if ((selected_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            selected_buf = new Date(valueDeserializer.readInt64())
        }
        const selected_result : Date | undefined = selected_buf
        const format_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let format_buf : TimePickerFormat | undefined
        if ((format_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            format_buf = TypeChecker.TimePickerFormat_FromNumeric(valueDeserializer.readInt32())
        }
        const format_result : TimePickerFormat | undefined = format_buf
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
        let value : TimePickerOptions = ({selected: selected_result, format: format_result, start: start_result, end: end_result} as TimePickerOptions)
        return value
    }
}
