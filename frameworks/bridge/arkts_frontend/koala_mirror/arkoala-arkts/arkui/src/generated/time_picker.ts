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
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./../CallbackTransformer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkCommonMethodPeer, CommonMethod, PickerTextStyle, PickerDialogButtonStyle, Rectangle, BlurStyle, ShadowOptions, ShadowStyle, HoverModeAreaType, ArkCommonMethodComponent, ArkCommonMethodStyle, UICommonMethod } from "./common"
import { DateTimeOptions } from "./arkui-intl"
import { Callback_Date_Void } from "./calendar_picker"
import { DialogAlignment } from "./alert_dialog"
import { Offset, ResourceColor } from "./units"
import { Callback_Void } from "./ability_component"
import { UICommonBase, AttributeModifier } from "./../handwritten"
import { NodeAttach, remember } from "@koalaui/runtime"
export class TimePickerDialog {
    public static show(options?: TimePickerDialogOptions): void {
        const options_casted = options as (TimePickerDialogOptions | undefined)
        TimePickerDialog.show_serialize(options_casted)
        return
    }
    private static show_serialize(options?: TimePickerDialogOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeTimePickerDialogOptions(options_value)
        }
        ArkUIGeneratedNativeModule._TimePickerDialog_show(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
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
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeTimePickerOptions(options_value)
        }
        ArkUIGeneratedNativeModule._TimePickerInterface_setTimePickerOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    useMilitaryTimeAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._TimePickerAttribute_useMilitaryTime(this.peer.ptr, value ? 1 : 0)
    }
    loopAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._TimePickerAttribute_loop(this.peer.ptr, value ? 1 : 0)
    }
    disappearTextStyleAttribute(value: PickerTextStyle): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writePickerTextStyle(value)
        ArkUIGeneratedNativeModule._TimePickerAttribute_disappearTextStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    textStyleAttribute(value: PickerTextStyle): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writePickerTextStyle(value)
        ArkUIGeneratedNativeModule._TimePickerAttribute_textStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    selectedTextStyleAttribute(value: PickerTextStyle): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writePickerTextStyle(value)
        ArkUIGeneratedNativeModule._TimePickerAttribute_selectedTextStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    dateTimeOptionsAttribute(value: DateTimeOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeDateTimeOptions(value)
        ArkUIGeneratedNativeModule._TimePickerAttribute_dateTimeOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onChangeAttribute(value: ((value: TimePickerResult) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._TimePickerAttribute_onChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enableHapticFeedbackAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._TimePickerAttribute_enableHapticFeedback(this.peer.ptr, value ? 1 : 0)
    }
    _onChangeEvent_selectedAttribute(callback: ((parameter: Date) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(callback)
        ArkUIGeneratedNativeModule._TimePickerAttribute__onChangeEvent_selected(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
}

export type Callback_TimePickerResult_Void = (value: TimePickerResult) => void;
export interface TimePickerAttribute extends CommonMethod {
    useMilitaryTime(value: boolean): this
    loop(value: boolean): this
    disappearTextStyle(value: PickerTextStyle): this
    textStyle(value: PickerTextStyle): this
    selectedTextStyle(value: PickerTextStyle): this
    dateTimeOptions(value: DateTimeOptions): this
    onChange(value: ((value: TimePickerResult) => void)): this
    enableHapticFeedback(value: boolean): this
    _onChangeEvent_selected(callback: ((parameter: Date) => void)): void
    attributeModifier(value: AttributeModifier<TimePickerAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export interface UITimePickerAttribute extends UICommonMethod {
    /** @memo */
    useMilitaryTime(value: boolean): this
    /** @memo */
    loop(value: boolean): this
    /** @memo */
    disappearTextStyle(value: PickerTextStyle): this
    /** @memo */
    textStyle(value: PickerTextStyle): this
    /** @memo */
    selectedTextStyle(value: PickerTextStyle): this
    /** @memo */
    dateTimeOptions(value: DateTimeOptions): this
    /** @memo */
    onChange(value: ((value: TimePickerResult) => void)): this
    /** @memo */
    enableHapticFeedback(value: boolean): this
    /** @memo */
    _onChangeEvent_selected(callback: ((parameter: Date) => void)): void
    /** @memo */
    attributeModifier(value: AttributeModifier<TimePickerAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkTimePickerStyle extends ArkCommonMethodStyle implements TimePickerAttribute {
    useMilitaryTime_value?: boolean
    loop_value?: boolean
    disappearTextStyle_value?: PickerTextStyle
    textStyle_value?: PickerTextStyle
    selectedTextStyle_value?: PickerTextStyle
    dateTimeOptions_value?: DateTimeOptions
    onChange_value?: ((value: TimePickerResult) => void)
    enableHapticFeedback_value?: boolean
    public useMilitaryTime(value: boolean): this {
        return this
    }
    public loop(value: boolean): this {
        return this
    }
    public disappearTextStyle(value: PickerTextStyle): this {
        return this
    }
    public textStyle(value: PickerTextStyle): this {
        return this
    }
    public selectedTextStyle(value: PickerTextStyle): this {
        return this
    }
    public dateTimeOptions(value: DateTimeOptions): this {
        return this
    }
    public onChange(value: ((value: TimePickerResult) => void)): this {
        return this
    }
    public enableHapticFeedback(value: boolean): this {
        return this
    }
    public _onChangeEvent_selected(callback: ((parameter: Date) => void)): void {
        throw new Error("Unimplmented")
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
    onAccept?: ((value: TimePickerResult) => void);
    onCancel?: (() => void);
    onChange?: ((value: TimePickerResult) => void);
    backgroundColor?: ResourceColor;
    backgroundBlurStyle?: BlurStyle;
    onDidAppear?: (() => void);
    onDidDisappear?: (() => void);
    onWillAppear?: (() => void);
    onWillDisappear?: (() => void);
    shadow?: ShadowOptions | ShadowStyle;
    dateTimeOptions?: DateTimeOptions;
    enableHoverMode?: boolean;
    hoverModeArea?: HoverModeAreaType;
}
/** @memo:stable */
export class ArkTimePickerComponent extends ArkCommonMethodComponent implements UITimePickerAttribute {
    getPeer(): ArkTimePickerPeer {
        return (this.peer as ArkTimePickerPeer)
    }
    /** @memo */
    public setTimePickerOptions(options?: TimePickerOptions): this {
        if (this.checkPriority("setTimePickerOptions")) {
            const options_casted = options as (TimePickerOptions | undefined)
            this.getPeer()?.setTimePickerOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    /** @memo */
    public useMilitaryTime(value: boolean): this {
        if (this.checkPriority("useMilitaryTime")) {
            const value_casted = value as (boolean)
            this.getPeer()?.useMilitaryTimeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public loop(value: boolean): this {
        if (this.checkPriority("loop")) {
            const value_casted = value as (boolean)
            this.getPeer()?.loopAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public disappearTextStyle(value: PickerTextStyle): this {
        if (this.checkPriority("disappearTextStyle")) {
            const value_casted = value as (PickerTextStyle)
            this.getPeer()?.disappearTextStyleAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public textStyle(value: PickerTextStyle): this {
        if (this.checkPriority("textStyle")) {
            const value_casted = value as (PickerTextStyle)
            this.getPeer()?.textStyleAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public selectedTextStyle(value: PickerTextStyle): this {
        if (this.checkPriority("selectedTextStyle")) {
            const value_casted = value as (PickerTextStyle)
            this.getPeer()?.selectedTextStyleAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public dateTimeOptions(value: DateTimeOptions): this {
        if (this.checkPriority("dateTimeOptions")) {
            const value_casted = value as (DateTimeOptions)
            this.getPeer()?.dateTimeOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onChange(value: ((value: TimePickerResult) => void)): this {
        if (this.checkPriority("onChange")) {
            const value_casted = value as (((value: TimePickerResult) => void))
            this.getPeer()?.onChangeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public enableHapticFeedback(value: boolean): this {
        if (this.checkPriority("enableHapticFeedback")) {
            const value_casted = value as (boolean)
            this.getPeer()?.enableHapticFeedbackAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public _onChangeEvent_selected(callback: ((parameter: Date) => void)): void {
        if (this.checkPriority("_onChangeEvent_selected")) {
            const callback_casted = callback as (((parameter: Date) => void))
            this.getPeer()?._onChangeEvent_selectedAttribute(callback_casted)
            return
        }
        return
    }
    /** @memo */
    public attributeModifier(value: AttributeModifier<TimePickerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function ArkTimePicker(
    /** @memo */
    style: ((attributes: UITimePickerAttribute) => void) | undefined,
    /** @memo */
    content_: (() => void) | undefined,
    options?: TimePickerOptions,
): void {
    const receiver = remember(() => {
        return new ArkTimePickerComponent()
    })
    NodeAttach<ArkTimePickerPeer>((): ArkTimePickerPeer => ArkTimePickerPeer.create(receiver), (_: ArkTimePickerPeer) => {
        receiver.setTimePickerOptions(options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
