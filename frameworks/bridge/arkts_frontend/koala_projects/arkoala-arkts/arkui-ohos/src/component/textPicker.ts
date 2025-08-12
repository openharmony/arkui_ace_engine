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
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkCommonMethodPeer, CommonMethod, PickerTextStyle, PickerDialogButtonStyle, Rectangle, BlurStyle, BackgroundBlurStyleOptions, BackgroundEffectOptions, ShadowOptions, ShadowStyle, HoverModeAreaType, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { Dimension, PX, VP, FP, LPX, Percentage, ResourceColor, Offset } from "./units"
import { CrownSensitivity, TextOverflow } from "./enums"
import { Resource } from "global.resource"
import { NodeAttach, remember } from "@koalaui/runtime"
import { LengthMetrics } from "../Graphics"
import { DialogAlignment } from "./alertDialog"

export class TextPickerDialog {
    public static show(options?: TextPickerDialogOptions): undefined {
        const options_casted = options as (TextPickerDialogOptions | undefined)
        return TextPickerDialog.show_serialize(options_casted)
    }
    private static show_serialize(options?: TextPickerDialogOptions): undefined {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeTextPickerDialogOptions(options_value)
        }
        const retval  = ArkUIGeneratedNativeModule._TextPickerDialog_show(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
}
export class ArkTextPickerPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkTextPickerPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._TextPicker_construct(peerId, flags)
        const _peer  = new ArkTextPickerPeer(_peerPtr, peerId, "TextPicker", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setTextPickerOptionsAttribute(options?: TextPickerOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeTextPickerOptions(options_value)
        }
        ArkUIGeneratedNativeModule._TextPickerInterface_setTextPickerOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    defaultPickerItemHeight0Attribute(value: number | string | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._TextPickerAttribute_defaultPickerItemHeight0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    defaultPickerItemHeight1Attribute(value: number | string | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._TextPickerAttribute_defaultPickerItemHeight1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    canLoop0Attribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._TextPickerAttribute_canLoop0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    canLoop1Attribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._TextPickerAttribute_canLoop1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    disappearTextStyle0Attribute(value: PickerTextStyle | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writePickerTextStyle(value_value)
        }
        ArkUIGeneratedNativeModule._TextPickerAttribute_disappearTextStyle0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    disappearTextStyle1Attribute(value: PickerTextStyle | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writePickerTextStyle(value_value)
        }
        ArkUIGeneratedNativeModule._TextPickerAttribute_disappearTextStyle1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    textStyle0Attribute(value: PickerTextStyle | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writePickerTextStyle(value_value)
        }
        ArkUIGeneratedNativeModule._TextPickerAttribute_textStyle0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    textStyle1Attribute(value: PickerTextStyle | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writePickerTextStyle(value_value)
        }
        ArkUIGeneratedNativeModule._TextPickerAttribute_textStyle1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    selectedTextStyle0Attribute(value: PickerTextStyle | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writePickerTextStyle(value_value)
        }
        ArkUIGeneratedNativeModule._TextPickerAttribute_selectedTextStyle0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    selectedTextStyle1Attribute(value: PickerTextStyle | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writePickerTextStyle(value_value)
        }
        ArkUIGeneratedNativeModule._TextPickerAttribute_selectedTextStyle1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    disableTextStyleAnimationAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._TextPickerAttribute_disableTextStyleAnimation(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    defaultTextStyleAttribute(value: TextPickerTextStyle | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeTextPickerTextStyle(value_value)
        }
        ArkUIGeneratedNativeModule._TextPickerAttribute_defaultTextStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onAcceptAttribute(value: ((value: string,index: number) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TextPickerAttribute_onAccept(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onCancelAttribute(value: (() => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TextPickerAttribute_onCancel(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onChange0Attribute(value: ((value: string | Array<string>,index: number | Array<number>) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TextPickerAttribute_onChange0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onChange1Attribute(value: OnTextPickerChangeCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TextPickerAttribute_onChange1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollStop0Attribute(value: TextPickerScrollStopCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TextPickerAttribute_onScrollStop0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollStop1Attribute(value: TextPickerScrollStopCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TextPickerAttribute_onScrollStop1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onEnterSelectedAreaAttribute(value: TextPickerEnterSelectedAreaCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TextPickerAttribute_onEnterSelectedArea(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    selectedIndex0Attribute(value: number | Array<number> | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as Array<number>
                thisSerializer.writeInt32(value_value_1.length as int32)
                for (let i = 0; i < value_value_1.length; i++) {
                    const value_value_1_element : number = value_value_1[i]
                    thisSerializer.writeNumber(value_value_1_element)
                }
            }
        }
        ArkUIGeneratedNativeModule._TextPickerAttribute_selectedIndex0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    selectedIndex1Attribute(value: number | Array<number> | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as Array<number>
                thisSerializer.writeInt32(value_value_1.length as int32)
                for (let i = 0; i < value_value_1.length; i++) {
                    const value_value_1_element : number = value_value_1[i]
                    thisSerializer.writeNumber(value_value_1_element)
                }
            }
        }
        ArkUIGeneratedNativeModule._TextPickerAttribute_selectedIndex1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    divider0Attribute(value: DividerOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeDividerOptions(value_value)
        }
        ArkUIGeneratedNativeModule._TextPickerAttribute_divider0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    divider1Attribute(value: DividerOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeDividerOptions(value_value)
        }
        ArkUIGeneratedNativeModule._TextPickerAttribute_divider1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    gradientHeight0Attribute(value: Dimension | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeLength(value_value)
        }
        ArkUIGeneratedNativeModule._TextPickerAttribute_gradientHeight0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    gradientHeight1Attribute(value: Dimension | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeLength(value_value)
        }
        ArkUIGeneratedNativeModule._TextPickerAttribute_gradientHeight1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enableHapticFeedbackAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._TextPickerAttribute_enableHapticFeedback(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    digitalCrownSensitivityAttribute(value: CrownSensitivity | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as CrownSensitivity)
            thisSerializer.writeInt32(TypeChecker.CrownSensitivity_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TextPickerAttribute_digitalCrownSensitivity(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    _onChangeEvent_selectedAttribute(callback: ((selected: number | Array<number>) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(callback)
        ArkUIGeneratedNativeModule._TextPickerAttribute__onChangeEvent_selected(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    _onChangeEvent_valueAttribute(callback: ((value: string | Array<string>) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(callback)
        ArkUIGeneratedNativeModule._TextPickerAttribute__onChangeEvent_value(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface TextPickerRangeContent {
    icon: string | Resource;
    text?: string | Resource;
}
export interface TextCascadePickerRangeContent {
    text: string | Resource;
    children?: Array<TextCascadePickerRangeContent>;
}
export interface TextPickerOptions {
    range: Array<string> | Array<Array<string>> | Resource | Array<TextPickerRangeContent> | Array<TextCascadePickerRangeContent>;
    value?: string | Array<string>;
    selected?: number | Array<number>;
    columnWidths?: Array<LengthMetrics>;
}
export type TextPickerInterface = (options?: TextPickerOptions) => TextPickerAttribute;
export interface DividerOptions {
    strokeWidth?: Dimension;
    color?: ResourceColor;
    startMargin?: Dimension;
    endMargin?: Dimension;
}
export interface TextPickerTextStyle extends PickerTextStyle {
    minFontSize?: number | string | Resource;
    maxFontSize?: number | string | Resource;
    overflow?: TextOverflow;
}
export type TextPickerScrollStopCallback = (value: string | Array<string>, index: number | Array<number>) => void;
export type OnTextPickerChangeCallback = (selectItem: string | Array<string>, index: number | Array<number>) => void;
export type TextPickerEnterSelectedAreaCallback = (value: string | Array<string>, index: number | Array<number>) => void;
export type Callback_String_Number_Void = (value: string, index: number) => void;
export type Type_TextPickerAttribute_onChange_callback = (value: string | Array<string>, index: number | Array<number>) => void;
export type Callback_Union_Number_Array_Number_Void = (selected: number | Array<number>) => void;
export type Callback_Union_String_Array_String_Void = (value: string | Array<string>) => void;
export interface TextPickerAttribute extends CommonMethod {
    defaultPickerItemHeight(value: number | string | undefined): this
    canLoop(value: boolean | undefined): this
    disappearTextStyle(value: PickerTextStyle | undefined): this
    textStyle(value: PickerTextStyle | undefined): this
    selectedTextStyle(value: PickerTextStyle | undefined): this
    disableTextStyleAnimation(value: boolean | undefined): this
    defaultTextStyle(value: TextPickerTextStyle | undefined): this
    onAccept(value: ((value: string,index: number) => void) | undefined): this
    onCancel(value: (() => void) | undefined): this
    onChange(value: ((value: string | Array<string>,index: number | Array<number>) => void) | undefined | OnTextPickerChangeCallback | undefined): this
    onScrollStop(value: TextPickerScrollStopCallback | undefined): this
    onEnterSelectedArea(value: TextPickerEnterSelectedAreaCallback | undefined): this
    selectedIndex(value: number | Array<number> | undefined): this
    divider(value: DividerOptions | undefined): this
    gradientHeight(value: Dimension | undefined): this
    enableHapticFeedback(value: boolean | undefined): this
    digitalCrownSensitivity(value: CrownSensitivity | undefined): this
    _onChangeEvent_selected(callback: ((selected: number | Array<number>) => void)): void
    _onChangeEvent_value(callback: ((value: string | Array<string>) => void)): void
}
export class ArkTextPickerStyle extends ArkCommonMethodStyle implements TextPickerAttribute {
    defaultPickerItemHeight_value?: number | string | undefined
    canLoop_value?: boolean | undefined
    disappearTextStyle_value?: PickerTextStyle | undefined
    textStyle_value?: PickerTextStyle | undefined
    selectedTextStyle_value?: PickerTextStyle | undefined
    disableTextStyleAnimation_value?: boolean | undefined
    defaultTextStyle_value?: TextPickerTextStyle | undefined
    onAccept_value?: ((value: string,index: number) => void) | undefined
    onCancel_value?: (() => void) | undefined
    onChange_value?: ((value: string | Array<string>,index: number | Array<number>) => void) | undefined
    onScrollStop_value?: TextPickerScrollStopCallback | undefined
    onEnterSelectedArea_value?: TextPickerEnterSelectedAreaCallback | undefined
    selectedIndex_value?: number | Array<number> | undefined
    divider_value?: DividerOptions | undefined
    gradientHeight_value?: Dimension | undefined
    enableHapticFeedback_value?: boolean | undefined
    digitalCrownSensitivity_value?: CrownSensitivity | undefined
    public defaultPickerItemHeight(value: number | string | undefined): this {
        return this
    }
    public canLoop(value: boolean | undefined): this {
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
    public disableTextStyleAnimation(value: boolean | undefined): this {
        return this
    }
    public defaultTextStyle(value: TextPickerTextStyle | undefined): this {
        return this
    }
    public onAccept(value: ((value: string,index: number) => void) | undefined): this {
        return this
    }
    public onCancel(value: (() => void) | undefined): this {
        return this
    }
    public onChange(value: ((value: string | Array<string>,index: number | Array<number>) => void) | undefined | OnTextPickerChangeCallback | undefined): this {
        return this
    }
    public onScrollStop(value: TextPickerScrollStopCallback | undefined): this {
        return this
    }
    public onEnterSelectedArea(value: TextPickerEnterSelectedAreaCallback | undefined): this {
        return this
    }
    public selectedIndex(value: number | Array<number> | undefined): this {
        return this
    }
    public divider(value: DividerOptions | undefined): this {
        return this
    }
    public gradientHeight(value: Dimension | undefined): this {
        return this
    }
    public enableHapticFeedback(value: boolean | undefined): this {
        return this
    }
    public digitalCrownSensitivity(value: CrownSensitivity | undefined): this {
        return this
    }
    public _onChangeEvent_selected(callback: ((selected: number | Array<number>) => void)): void {
        throw new Error("Unimplmented")
    }
    public _onChangeEvent_value(callback: ((value: string | Array<string>) => void)): void {
        throw new Error("Unimplmented")
        }
}
export interface TextPickerResult {
    value: string | Array<string>;
    index: number | Array<number>;
}
export type Callback_TextPickerResult_Void = (value: TextPickerResult) => void;
export interface TextPickerDialogOptions extends TextPickerOptions {
    defaultPickerItemHeight?: number | string;
    canLoop?: boolean;
    disappearTextStyle?: PickerTextStyle;
    textStyle?: PickerTextStyle;
    acceptButtonStyle?: PickerDialogButtonStyle;
    cancelButtonStyle?: PickerDialogButtonStyle;
    selectedTextStyle?: PickerTextStyle;
    disableTextStyleAnimation?: boolean;
    defaultTextStyle?: TextPickerTextStyle;
    onAccept?: ((value: TextPickerResult) => void);
    onCancel?: (() => void);
    onChange?: ((value: TextPickerResult) => void);
    onScrollStop?: ((value: TextPickerResult) => void);
    onEnterSelectedArea?: ((value: TextPickerResult) => void);
    maskRect?: Rectangle;
    alignment?: DialogAlignment;
    offset?: Offset;
    backgroundColor?: ResourceColor;
    backgroundBlurStyle?: BlurStyle;
    backgroundBlurStyleOptions?: BackgroundBlurStyleOptions;
    backgroundEffect?: BackgroundEffectOptions;
    onDidAppear?: (() => void);
    onDidDisappear?: (() => void);
    onWillAppear?: (() => void);
    onWillDisappear?: (() => void);
    shadow?: ShadowOptions | ShadowStyle;
    enableHoverMode?: boolean;
    hoverModeArea?: HoverModeAreaType;
    enableHapticFeedback?: boolean;
}
export class ArkTextPickerComponent extends ArkCommonMethodComponent implements TextPickerAttribute {
    getPeer(): ArkTextPickerPeer {
        return (this.peer as ArkTextPickerPeer)
    }
    public setTextPickerOptions(options?: TextPickerOptions): this {
        if (this.checkPriority("setTextPickerOptions")) {
            const options_casted = options as (TextPickerOptions | undefined)
            this.getPeer()?.setTextPickerOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    public defaultPickerItemHeight(value: number | string | undefined): this {
        if (this.checkPriority("defaultPickerItemHeight")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.STRING == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (number | string | undefined)
                this.getPeer()?.defaultPickerItemHeight0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.STRING == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (number | string | undefined)
                this.getPeer()?.defaultPickerItemHeight1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public canLoop(value: boolean | undefined): this {
        if (this.checkPriority("canLoop")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.BOOLEAN == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (boolean | undefined)
                this.getPeer()?.canLoop0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.BOOLEAN == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (boolean | undefined)
                this.getPeer()?.canLoop1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public disappearTextStyle(value: PickerTextStyle | undefined): this {
        if (this.checkPriority("disappearTextStyle")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (PickerTextStyle | undefined)
                this.getPeer()?.disappearTextStyle0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (PickerTextStyle | undefined)
                this.getPeer()?.disappearTextStyle1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public textStyle(value: PickerTextStyle | undefined): this {
        if (this.checkPriority("textStyle")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (PickerTextStyle | undefined)
                this.getPeer()?.textStyle0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (PickerTextStyle | undefined)
                this.getPeer()?.textStyle1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public selectedTextStyle(value: PickerTextStyle | undefined): this {
        if (this.checkPriority("selectedTextStyle")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (PickerTextStyle | undefined)
                this.getPeer()?.selectedTextStyle0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (PickerTextStyle | undefined)
                this.getPeer()?.selectedTextStyle1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public disableTextStyleAnimation(value: boolean | undefined): this {
        if (this.checkPriority("disableTextStyleAnimation")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.disableTextStyleAnimationAttribute(value_casted)
            return this
        }
        return this
    }
    public defaultTextStyle(value: TextPickerTextStyle | undefined): this {
        if (this.checkPriority("defaultTextStyle")) {
            const value_casted = value as (TextPickerTextStyle | undefined)
            this.getPeer()?.defaultTextStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public onAccept(value: ((value: string,index: number) => void) | undefined): this {
        if (this.checkPriority("onAccept")) {
            const value_casted = value as (((value: string,index: number) => void) | undefined)
            this.getPeer()?.onAcceptAttribute(value_casted)
            return this
        }
        return this
    }
    public onCancel(value: (() => void) | undefined): this {
        if (this.checkPriority("onCancel")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.onCancelAttribute(value_casted)
            return this
        }
        return this
    }
    public onChange(value: ((value: string | Array<string>,index: number | Array<number>) => void) | undefined | OnTextPickerChangeCallback | undefined): this {
        if (this.checkPriority("onChange")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.FUNCTION == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (((value: string | Array<string>,index: number | Array<number>) => void) | undefined)
                this.getPeer()?.onChange0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.FUNCTION == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (OnTextPickerChangeCallback | undefined)
                this.getPeer()?.onChange1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public onScrollStop(value: TextPickerScrollStopCallback | undefined): this {
        if (this.checkPriority("onScrollStop")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.FUNCTION == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (TextPickerScrollStopCallback | undefined)
                this.getPeer()?.onScrollStop0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.FUNCTION == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (TextPickerScrollStopCallback | undefined)
                this.getPeer()?.onScrollStop1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public onEnterSelectedArea(value: TextPickerEnterSelectedAreaCallback | undefined): this {
        if (this.checkPriority("onEnterSelectedArea")) {
            const value_casted = value as (TextPickerEnterSelectedAreaCallback | undefined)
            this.getPeer()?.onEnterSelectedAreaAttribute(value_casted)
            return this
        }
        return this
    }
    public selectedIndex(value: number | Array<number> | undefined): this {
        if (this.checkPriority("selectedIndex")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (number | Array<number> | undefined)
                this.getPeer()?.selectedIndex0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (number | Array<number> | undefined)
                this.getPeer()?.selectedIndex1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public divider(value: DividerOptions | undefined): this {
        if (this.checkPriority("divider")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (DividerOptions | undefined)
                this.getPeer()?.divider0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (DividerOptions | undefined)
                this.getPeer()?.divider1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public gradientHeight(value: Dimension | undefined): this {
        if (this.checkPriority("gradientHeight")) {
            const value_type = runtimeType(value)
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (Dimension | undefined)
                this.getPeer()?.gradientHeight0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.NUMBER == value_type) || (RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type) || (RuntimeType.UNDEFINED == value_type)) {
                const value_casted = value as (Dimension | undefined)
                this.getPeer()?.gradientHeight1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public enableHapticFeedback(value: boolean | undefined): this {
        if (this.checkPriority("enableHapticFeedback")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.enableHapticFeedbackAttribute(value_casted)
            return this
        }
        return this
    }
    public digitalCrownSensitivity(value: CrownSensitivity | undefined): this {
        if (this.checkPriority("digitalCrownSensitivity")) {
            const value_casted = value as (CrownSensitivity | undefined)
            this.getPeer()?.digitalCrownSensitivityAttribute(value_casted)
            return this
        }
        return this
    }
    public _onChangeEvent_selected(callback: ((selected: number | Array<number>) => void)): void {
        if (this.checkPriority("_onChangeEvent_selected")) {
            const callback_casted = callback as (((selected: number | Array<number>) => void))
            this.getPeer()?._onChangeEvent_selectedAttribute(callback_casted)
            return
        }
        return
    }
    public _onChangeEvent_value(callback: ((value: string | Array<string>) => void)): void {
        if (this.checkPriority("_onChangeEvent_value")) {
            const callback_casted = callback as (((value: string | Array<string>) => void))
            this.getPeer()?._onChangeEvent_valueAttribute(callback_casted)
            return
        }
        return
    }
    
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function TextPicker(
    /** @memo */
    style: ((attributes: TextPickerAttribute) => void) | undefined,
    options?: TextPickerOptions,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkTextPickerComponent()
    })
    NodeAttach<ArkTextPickerPeer>((): ArkTextPickerPeer => ArkTextPickerPeer.create(receiver), (_: ArkTextPickerPeer) => {
        receiver.setTextPickerOptions(options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
