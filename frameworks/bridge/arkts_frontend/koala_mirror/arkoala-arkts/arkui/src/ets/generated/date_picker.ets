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
import { Callback_Date_Void } from "./calendar_picker"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { BuilderLambda } from "@koalaui/builderLambda"
import { ResourceColor, Offset, VoidCallback } from "./units"
import { DialogAlignment } from "./alert_dialog"
import { DateTimeOptions } from "./arkui-intl"
import { UICommonBase, AttributeModifier } from "./../handwritten"
import { NodeAttach, remember } from "@koalaui/runtime"
export class DatePickerDialog {
    public static show(options?: DatePickerDialogOptions): void {
        const options_casted = options as (DatePickerDialogOptions | undefined)
        DatePickerDialog.show_serialize(options_casted)
        return
    }
    private static show_serialize(options?: DatePickerDialogOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeDatePickerDialogOptions(options_value)
        }
        ArkUIGeneratedNativeModule._DatePickerDialog_show(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
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
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeDatePickerOptions(options_value)
        }
        ArkUIGeneratedNativeModule._DatePickerInterface_setDatePickerOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    lunarAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._DatePickerAttribute_lunar(this.peer.ptr, value ? 1 : 0)
    }
    disappearTextStyleAttribute(value: PickerTextStyle): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writePickerTextStyle(value)
        ArkUIGeneratedNativeModule._DatePickerAttribute_disappearTextStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    textStyleAttribute(value: PickerTextStyle): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writePickerTextStyle(value)
        ArkUIGeneratedNativeModule._DatePickerAttribute_textStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    selectedTextStyleAttribute(value: PickerTextStyle): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writePickerTextStyle(value)
        ArkUIGeneratedNativeModule._DatePickerAttribute_selectedTextStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onChangeAttribute(value: ((value: DatePickerResult) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._DatePickerAttribute_onChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onDateChangeAttribute(value: ((parameter: Date) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._DatePickerAttribute_onDateChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    _onChangeEvent_selectedAttribute(callback: ((parameter: Date) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(callback)
        ArkUIGeneratedNativeModule._DatePickerAttribute__onChangeEvent_selected(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface DatePickerResult {
    year?: number;
    month?: number;
    day?: number;
}
export interface DatePickerOptions {
    start?: Date;
    end?: Date;
    selected?: Date;
}

export type Callback_DatePickerResult_Void = (value: DatePickerResult) => void;
export interface DatePickerAttribute extends CommonMethod {
    lunar(value: boolean): this
    disappearTextStyle(value: PickerTextStyle): this
    textStyle(value: PickerTextStyle): this
    selectedTextStyle(value: PickerTextStyle): this
    onChange(value: ((value: DatePickerResult) => void)): this
    onDateChange(value: ((parameter: Date) => void)): this
    _onChangeEvent_selected(callback: ((parameter: Date) => void)): void
    attributeModifier(value: AttributeModifier<DatePickerAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export interface UIDatePickerAttribute extends UICommonMethod {
    @memo
    lunar(value: boolean): this
    @memo
    disappearTextStyle(value: PickerTextStyle): this
    @memo
    textStyle(value: PickerTextStyle): this
    @memo
    selectedTextStyle(value: PickerTextStyle): this
    @memo
    onChange(value: ((value: DatePickerResult) => void)): this
    @memo
    onDateChange(value: ((parameter: Date) => void)): this
    @memo
    _onChangeEvent_selected(callback: ((parameter: Date) => void)): void
    @memo
    attributeModifier(value: AttributeModifier<DatePickerAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkDatePickerStyle extends ArkCommonMethodStyle implements DatePickerAttribute {
    lunar_value?: boolean
    disappearTextStyle_value?: PickerTextStyle
    textStyle_value?: PickerTextStyle
    selectedTextStyle_value?: PickerTextStyle
    onChange_value?: ((value: DatePickerResult) => void)
    onDateChange_value?: ((parameter: Date) => void)
    public lunar(value: boolean): this {
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
    public onChange(value: ((value: DatePickerResult) => void)): this {
        return this
    }
    public onDateChange(value: ((parameter: Date) => void)): this {
        return this
    }
    public _onChangeEvent_selected(callback: ((parameter: Date) => void)): void {
        throw new Error("Unimplmented")
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
    onAccept?: ((value: DatePickerResult) => void);
    onCancel?: VoidCallback;
    onChange?: ((value: DatePickerResult) => void);
    onDateAccept?: ((parameter: Date) => void);
    onDateChange?: ((parameter: Date) => void);
    backgroundColor?: ResourceColor;
    backgroundBlurStyle?: BlurStyle;
    onDidAppear?: VoidCallback;
    onDidDisappear?: VoidCallback;
    onWillAppear?: VoidCallback;
    onWillDisappear?: VoidCallback;
    shadow?: ShadowOptions | ShadowStyle;
    dateTimeOptions?: DateTimeOptions;
    enableHoverMode?: boolean;
    hoverModeArea?: HoverModeAreaType;
}
@memo_stable
export class ArkDatePickerComponent extends ArkCommonMethodComponent implements UIDatePickerAttribute {
    getPeer(): ArkDatePickerPeer {
        return (this.peer as ArkDatePickerPeer)
    }
    @memo
    public setDatePickerOptions(options?: DatePickerOptions): this {
        if (this.checkPriority("setDatePickerOptions")) {
            const options_casted = options as (DatePickerOptions | undefined)
            this.getPeer()?.setDatePickerOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    @memo
    public lunar(value: boolean): this {
        if (this.checkPriority("lunar")) {
            const value_casted = value as (boolean)
            this.getPeer()?.lunarAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public disappearTextStyle(value: PickerTextStyle): this {
        if (this.checkPriority("disappearTextStyle")) {
            const value_casted = value as (PickerTextStyle)
            this.getPeer()?.disappearTextStyleAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public textStyle(value: PickerTextStyle): this {
        if (this.checkPriority("textStyle")) {
            const value_casted = value as (PickerTextStyle)
            this.getPeer()?.textStyleAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public selectedTextStyle(value: PickerTextStyle): this {
        if (this.checkPriority("selectedTextStyle")) {
            const value_casted = value as (PickerTextStyle)
            this.getPeer()?.selectedTextStyleAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onChange(value: ((value: DatePickerResult) => void)): this {
        if (this.checkPriority("onChange")) {
            const value_casted = value as (((value: DatePickerResult) => void))
            this.getPeer()?.onChangeAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onDateChange(value: ((parameter: Date) => void)): this {
        if (this.checkPriority("onDateChange")) {
            const value_casted = value as (((parameter: Date) => void))
            this.getPeer()?.onDateChangeAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public _onChangeEvent_selected(callback: ((parameter: Date) => void)): void {
        if (this.checkPriority("_onChangeEvent_selected")) {
            const callback_casted = callback as (((parameter: Date) => void))
            this.getPeer()?._onChangeEvent_selectedAttribute(callback_casted)
            return
        }
        return
    }
    @memo
    public attributeModifier(value: AttributeModifier<DatePickerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
@memo
@BuilderLambda("DatePicker")
export function DatePicker(
    options?: DatePickerOptions,
    @memo
    content_?: () => void,
): DatePickerAttribute {
    throw new Error("Not implemented")
}

@memo
export function DatePicker(
    @memo
    style: ((attributes: UIDatePickerAttribute) => void) | undefined,
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
