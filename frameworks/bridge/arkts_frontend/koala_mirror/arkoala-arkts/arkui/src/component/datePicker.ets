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
import { PickerTextStyle_serializer, ArkCommonMethodPeer, CommonMethod, PickerTextStyle, Bindable, PickerDialogButtonStyle, Rectangle, BlurStyle, BackgroundBlurStyleOptions, BackgroundEffectOptions, ShadowOptions, ShadowStyle, HoverModeAreaType, ArkCommonMethodComponent, ArkCommonMethodStyle, CommonMethodModifier, Bindable_Date_serializer } from "./common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { CrownSensitivity, Color } from "./enums"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { ResourceColor, Offset, VoidCallback } from "./units"
import { Resource } from "./../generated/resource"
import { DialogAlignment } from "./alertDialog"
import { intl } from "./../generated/ohos.intl"
import { NodeAttach, remember } from "@koalaui/runtime"
import { AttributeUpdaterFlag } from "./../generated/AttributeUpdater"
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
        const _peer  = new ArkDatePickerPeer(_peerPtr, peerId, 'DatePicker', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setDatePickerOptionsAttribute(options?: DatePickerOptions): void {
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
            thisSerializer.writeInt32(TypeChecker.CrownSensitivity_ToNumeric(valueTmpValue))
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
    selected?: Date | Bindable<Date>;
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
    public attributeModifier(value: AttributeModifier<DatePickerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

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
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class DatePickerModifier extends CommonMethodModifier implements DatePickerAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _lunar_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _lunar_0_0value?: boolean | undefined
    _disappearTextStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _disappearTextStyle_0_0value?: PickerTextStyle | undefined
    _textStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _textStyle_0_0value?: PickerTextStyle | undefined
    _selectedTextStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _selectedTextStyle_0_0value?: PickerTextStyle | undefined
    _onDateChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onDateChange_0_0value?: ((value0: Date) => void) | undefined
    _digitalCrownSensitivity_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _digitalCrownSensitivity_0_0value?: CrownSensitivity | undefined
    _enableHapticFeedback_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableHapticFeedback_0_0value?: boolean | undefined
    applyModifierPatch(peer: ArkDatePickerPeer): void {
        super.applyModifierPatch(peer)
        if (this._lunar_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._lunar_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setLunarAttribute((this._lunar_0_0value as boolean | undefined));
                    this._lunar_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._lunar_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._lunar_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setLunarAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._disappearTextStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._disappearTextStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDisappearTextStyleAttribute((this._disappearTextStyle_0_0value as PickerTextStyle | undefined));
                    this._disappearTextStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._disappearTextStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._disappearTextStyle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDisappearTextStyleAttribute((undefined as PickerTextStyle | undefined));
                }
            }
        }
        if (this._textStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._textStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setTextStyleAttribute((this._textStyle_0_0value as PickerTextStyle | undefined));
                    this._textStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._textStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._textStyle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setTextStyleAttribute((undefined as PickerTextStyle | undefined));
                }
            }
        }
        if (this._selectedTextStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._selectedTextStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSelectedTextStyleAttribute((this._selectedTextStyle_0_0value as PickerTextStyle | undefined));
                    this._selectedTextStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._selectedTextStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._selectedTextStyle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSelectedTextStyleAttribute((undefined as PickerTextStyle | undefined));
                }
            }
        }
        if (this._onDateChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onDateChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnDateChangeAttribute((this._onDateChange_0_0value as ((value0: Date) => void) | undefined));
                    this._onDateChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onDateChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onDateChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnDateChangeAttribute((undefined as ((value0: Date) => void) | undefined));
                }
            }
        }
        if (this._digitalCrownSensitivity_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._digitalCrownSensitivity_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDigitalCrownSensitivityAttribute((this._digitalCrownSensitivity_0_0value as CrownSensitivity | undefined));
                    this._digitalCrownSensitivity_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._digitalCrownSensitivity_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._digitalCrownSensitivity_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDigitalCrownSensitivityAttribute((undefined as CrownSensitivity | undefined));
                }
            }
        }
        if (this._enableHapticFeedback_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableHapticFeedback_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEnableHapticFeedbackAttribute((this._enableHapticFeedback_0_0value as boolean | undefined));
                    this._enableHapticFeedback_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableHapticFeedback_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableHapticFeedback_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEnableHapticFeedbackAttribute((undefined as boolean | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: DatePickerModifier): void {
        super.mergeModifier(modifier)
        if (modifier._lunar_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._lunar_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.lunar(modifier._lunar_0_0value);
                    break;
                }
                default: {
                    this.lunar((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._disappearTextStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._disappearTextStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.disappearTextStyle(modifier._disappearTextStyle_0_0value);
                    break;
                }
                default: {
                    this.disappearTextStyle((undefined as PickerTextStyle | undefined));
                }
            }
        }
        if (modifier._textStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._textStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.textStyle(modifier._textStyle_0_0value);
                    break;
                }
                default: {
                    this.textStyle((undefined as PickerTextStyle | undefined));
                }
            }
        }
        if (modifier._selectedTextStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._selectedTextStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.selectedTextStyle(modifier._selectedTextStyle_0_0value);
                    break;
                }
                default: {
                    this.selectedTextStyle((undefined as PickerTextStyle | undefined));
                }
            }
        }
        if (modifier._onDateChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onDateChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onDateChange(modifier._onDateChange_0_0value);
                    break;
                }
                default: {
                    this.onDateChange((undefined as ((value0: Date) => void) | undefined));
                }
            }
        }
        if (modifier._digitalCrownSensitivity_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._digitalCrownSensitivity_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.digitalCrownSensitivity(modifier._digitalCrownSensitivity_0_0value);
                    break;
                }
                default: {
                    this.digitalCrownSensitivity((undefined as CrownSensitivity | undefined));
                }
            }
        }
        if (modifier._enableHapticFeedback_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enableHapticFeedback_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enableHapticFeedback(modifier._enableHapticFeedback_0_0value);
                    break;
                }
                default: {
                    this.enableHapticFeedback((undefined as boolean | undefined));
                }
            }
        }
    }
    lunar(value: boolean | undefined): this {
        if (((this._lunar_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._lunar_0_0value) !== (value)))
        {
            this._lunar_0_flag = AttributeUpdaterFlag.UPDATE
            this._lunar_0_0value = value
        } else
        {
            this._lunar_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    disappearTextStyle(value: PickerTextStyle | undefined): this {
        if (((this._disappearTextStyle_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._disappearTextStyle_0_flag = AttributeUpdaterFlag.UPDATE
            this._disappearTextStyle_0_0value = value
        } else
        {
            this._disappearTextStyle_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    textStyle(value: PickerTextStyle | undefined): this {
        if (((this._textStyle_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._textStyle_0_flag = AttributeUpdaterFlag.UPDATE
            this._textStyle_0_0value = value
        } else
        {
            this._textStyle_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    selectedTextStyle(value: PickerTextStyle | undefined): this {
        if (((this._selectedTextStyle_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._selectedTextStyle_0_flag = AttributeUpdaterFlag.UPDATE
            this._selectedTextStyle_0_0value = value
        } else
        {
            this._selectedTextStyle_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onDateChange(value: ((value0: Date) => void) | undefined): this {
        if (((this._onDateChange_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onDateChange_0_flag = AttributeUpdaterFlag.UPDATE
            this._onDateChange_0_0value = value
        } else
        {
            this._onDateChange_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    digitalCrownSensitivity(value: CrownSensitivity | undefined): this {
        if (((this._digitalCrownSensitivity_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._digitalCrownSensitivity_0_flag = AttributeUpdaterFlag.UPDATE
            this._digitalCrownSensitivity_0_0value = value
        } else
        {
            this._digitalCrownSensitivity_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enableHapticFeedback(value: boolean | undefined): this {
        if (((this._enableHapticFeedback_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enableHapticFeedback_0_0value) !== (value)))
        {
            this._enableHapticFeedback_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableHapticFeedback_0_0value = value
        } else
        {
            this._enableHapticFeedback_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
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
        const valueHolderForMode  = value.mode
        if (valueHolderForMode !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForModeTmpValue  = (valueHolderForMode as DatePickerMode)
            valueSerializer.writeInt32(TypeChecker.DatePickerMode_ToNumeric(valueHolderForModeTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): DatePickerOptions {
        let valueDeserializer : DeserializerBase = buffer
        const startTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let startTmpBuf : Date | undefined
        if ((startTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            startTmpBuf = new Date(valueDeserializer.readInt64())
        }
        const startTmpResult : Date | undefined = startTmpBuf
        const endTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let endTmpBuf : Date | undefined
        if ((endTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            endTmpBuf = new Date(valueDeserializer.readInt64())
        }
        const endTmpResult : Date | undefined = endTmpBuf
        const selectedTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let selectedTmpBuf : Date | Bindable<Date> | undefined
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
        let modeTmpBuf : DatePickerMode | undefined
        if ((modeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            modeTmpBuf = TypeChecker.DatePickerMode_FromNumeric(valueDeserializer.readInt32())
        }
        const modeTmpResult : DatePickerMode | undefined = modeTmpBuf
        let value : DatePickerOptions = ({start: startTmpResult, end: endTmpResult, selected: selectedTmpResult, mode: modeTmpResult} as DatePickerOptions)
        return value
    }
}
