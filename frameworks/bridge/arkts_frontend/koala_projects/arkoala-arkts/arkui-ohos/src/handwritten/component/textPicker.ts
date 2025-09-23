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

import { TypeChecker, ArkUIGeneratedNativeModule, Bindable } from "#components"
import { runtimeType, RuntimeType } from "@koalaui/interop"
import { int32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { Resource } from "global.resource"
import { LengthMetrics } from "../Graphics"
import { TextPickerSelectedOps } from "./textpickerselectedops"
import { TextPickerValueOps } from "./textpickervalueops"
import { Color } from "./enums"

class CheckTextPickerOptions {
    static isArray_String(value: Object | string | number | undefined): boolean {
        if (value instanceof Array<string> && value.length) {
            return value[0] instanceof string
        }
        return false
    }

    static isArray_Array_String(value: Object | string | number | undefined): boolean {
        if (value instanceof Array<Array<string>> && value.length) {
            return value[0] instanceof Array<string>
        }
        return false
    }

    static isArray_TextCascadePickerRangeContent(value: Object | string | number | undefined): boolean {
        if (value instanceof Array<TextCascadePickerRangeContent> && value.length) {
            return value[0] instanceof TextCascadePickerRangeContent
        }
        return false
    }

    static isArray_TextPickerRangeContent(value: Object | string | number | undefined): boolean {
        if (value instanceof Array<TextPickerRangeContent> && value.length) {
            return value[0] instanceof TextPickerRangeContent
        }
        return false
    }

    static IsTextPickerOptionBindable(optionIndex: number, options?: TextPickerOptions): boolean {
        if (RuntimeType.UNDEFINED != runtimeType(options)) {
            const options_value = (optionIndex == 0 ? options!.selected : options!.value)
            if (RuntimeType.UNDEFINED != runtimeType(options_value)) {
                const options_value_value = options_value!
                const isBindable: boolean = (optionIndex == 0 ? (TypeChecker.isBindableNumber(options_value_value) | TypeChecker.isBindableArrayNumber(options_value_value))
                    : (TypeChecker.isBindableString(options_value_value) | TypeChecker.isBindableArrayString(options_value_value)))
                return isBindable
            }
        }
        return false
    }
}

function writeTextPickerOptions(valueSerializer: Serializer, value: TextPickerOptions): void {
    const value_range  = value.range
    let value_range_type : int32 = RuntimeType.UNDEFINED
    value_range_type = runtimeType(value_range)
    if (((RuntimeType.OBJECT) == (value_range_type)) && (CheckTextPickerOptions.isArray_String(value_range))) {
        valueSerializer.writeInt8(0 as int32)
        const value_range_0  = value_range as Array<string>
        valueSerializer.writeInt32(value_range_0.length as int32)
        for (let i = 0; i < value_range_0.length; i++) {
            const value_range_0_element : string = value_range_0[i]
            valueSerializer.writeString(value_range_0_element)
        }
    }
    else if (((RuntimeType.OBJECT) == (value_range_type)) && (CheckTextPickerOptions.isArray_Array_String(value_range))) {
        valueSerializer.writeInt8(1 as int32)
        const value_range_1  = value_range as Array<Array<string>>
        valueSerializer.writeInt32(value_range_1.length as int32)
        for (let i = 0; i < value_range_1.length; i++) {
            const value_range_1_element : Array<string> = value_range_1[i]
            valueSerializer.writeInt32(value_range_1_element.length as int32)
            for (let i = 0; i < value_range_1_element.length; i++) {
                const value_range_1_element_element : string = value_range_1_element[i]
                valueSerializer.writeString(value_range_1_element_element)
            }
        }
    }
    else if (TypeChecker.isResource(value_range, false, false, false, false, false)) {
        valueSerializer.writeInt8(2 as int32)
        const value_range_2  = value_range as Resource
        valueSerializer.writeResource(value_range_2)
    }
    else if (((RuntimeType.OBJECT) == (value_range_type)) && (CheckTextPickerOptions.isArray_TextPickerRangeContent(value_range))) {
        valueSerializer.writeInt8(3 as int32)
        const value_range_3  = value_range as Array<TextPickerRangeContent>
        valueSerializer.writeInt32(value_range_3.length as int32)
        for (let i = 0; i < value_range_3.length; i++) {
            const value_range_3_element : TextPickerRangeContent = value_range_3[i]
            valueSerializer.writeTextPickerRangeContent(value_range_3_element)
        }
    }
    else if (((RuntimeType.OBJECT) == (value_range_type)) && (CheckTextPickerOptions.isArray_TextCascadePickerRangeContent(value_range))) {
        valueSerializer.writeInt8(4 as int32)
        const value_range_4  = value_range as Array<TextCascadePickerRangeContent>
        valueSerializer.writeInt32(value_range_4.length as int32)
        for (let i = 0; i < value_range_4.length; i++) {
            const value_range_4_element : TextCascadePickerRangeContent = value_range_4[i]
            valueSerializer.writeTextCascadePickerRangeContent(value_range_4_element)
        }
    }
    const value_value  = value.value
    let value_value_type : int32 = RuntimeType.UNDEFINED
    value_value_type = runtimeType(value_value)
    valueSerializer.writeInt8(value_value_type as int32)
    if ((RuntimeType.UNDEFINED) != (value_value_type)) {
        const value_value_value  = value_value!
        let value_value_value_type : int32 = RuntimeType.UNDEFINED
        value_value_value_type = runtimeType(value_value_value)
        if (RuntimeType.STRING == value_value_value_type) {
            valueSerializer.writeInt8(0 as int32)
            const value_value_value_0  = value_value_value as string
            valueSerializer.writeString(value_value_value_0)
        }
        else if (TypeChecker.isBindableString(value_value) || TypeChecker.isBindableArrayString(value_value)) {
            valueSerializer.writeInt8(3 as int32)
        }
        else if (RuntimeType.OBJECT == value_value_value_type) {
            valueSerializer.writeInt8(1 as int32)
            const value_value_value_1  = value_value_value as Array<string>
            valueSerializer.writeInt32(value_value_value_1.length as int32)
            for (let i = 0; i < value_value_value_1.length; i++) {
                const value_value_value_1_element : string = value_value_value_1[i]
                valueSerializer.writeString(value_value_value_1_element)
            }
        }
    }
    const value_selected  = value.selected
    let value_selected_type : int32 = RuntimeType.UNDEFINED
    value_selected_type = runtimeType(value_selected)
    valueSerializer.writeInt8(value_selected_type as int32)
    if ((RuntimeType.UNDEFINED) != (value_selected_type)) {
        const value_selected_value  = value_selected!
        let value_selected_value_type : int32 = RuntimeType.UNDEFINED
        value_selected_value_type = runtimeType(value_selected_value)
        if (RuntimeType.NUMBER == value_selected_value_type) {
            valueSerializer.writeInt8(0 as int32)
            const value_selected_value_0  = value_selected_value as number
            valueSerializer.writeNumber(value_selected_value_0)
        }
        else if (TypeChecker.isBindableNumber(value_selected) || TypeChecker.isBindableArrayNumber(value_selected)) {
            valueSerializer.writeInt8(3 as int32)
        }
        else if (RuntimeType.OBJECT == value_selected_value_type) {
            valueSerializer.writeInt8(1 as int32)
            const value_selected_value_1  = value_selected_value as Array<number>
            valueSerializer.writeInt32(value_selected_value_1.length as int32)
            for (let i = 0; i < value_selected_value_1.length; i++) {
                const value_selected_value_1_element : number = value_selected_value_1[i]
                valueSerializer.writeNumber(value_selected_value_1_element)
            }
        }
    }
    const value_columnWidths  = value.columnWidths
    let value_columnWidths_type : int32 = RuntimeType.UNDEFINED
    value_columnWidths_type = runtimeType(value_columnWidths)
    valueSerializer.writeInt8(value_columnWidths_type as int32)
    if ((RuntimeType.UNDEFINED) != (value_columnWidths_type)) {
        const value_columnWidths_value  = value_columnWidths!
        valueSerializer.writeInt32(value_columnWidths_value.length as int32)
        for (let i = 0; i < value_columnWidths_value.length; i++) {
            const value_columnWidths_value_element : LengthMetrics = value_columnWidths_value[i]
            valueSerializer.writeLengthMetrics(value_columnWidths_value_element)
        }
    }
}

function hookSetTextPickerOptions(peer: ArkTextPickerPeer, options?: TextPickerOptions): void {
    const thisSerializer : Serializer = Serializer.hold()
    let options_type : int32 = RuntimeType.UNDEFINED
    options_type = runtimeType(options)
    thisSerializer.writeInt8(options_type as int32)
    if ((RuntimeType.UNDEFINED) != (options_type)) {
        const options_value  = options!
        writeTextPickerOptions(thisSerializer, options_value)
    }
    ArkUIGeneratedNativeModule._TextPickerInterface_setTextPickerOptions(peer.getPeerPtr(), thisSerializer.asBuffer(), thisSerializer.length())
    thisSerializer.release()

    if (CheckTextPickerOptions.IsTextPickerOptionBindable(0, options)) {
        TextPickerOpsHandWritten.hookTextPickerSelectedImpl(peer, (options!.selected as Bindable<number | Array<number>>))
    }

    if (CheckTextPickerOptions.IsTextPickerOptionBindable(1, options)) {
        TextPickerOpsHandWritten.hookTextPickerValueImpl(peer, (options!.value as Bindable<string | Array<string>>))
    }
}
function HookWriteTextPickerDialogOptions(valueSerializer : Serializer, value: TextPickerDialogOptions): void {
    const value_range  = value.range
    let value_range_type : int32 = RuntimeType.UNDEFINED
    value_range_type = runtimeType(value_range)
    if (((RuntimeType.OBJECT) == (value_range_type)) && (CheckTextPickerOptions.isArray_String(value_range))) {
        valueSerializer.writeInt8(0 as int32)
        const value_range_0  = value_range as Array<string>
        valueSerializer.writeInt32(value_range_0.length as int32)
        for (let i = 0; i < value_range_0.length; i++) {
            const value_range_0_element : string = value_range_0[i]
            valueSerializer.writeString(value_range_0_element)
        }
    }
    else if (((RuntimeType.OBJECT) == (value_range_type)) && (CheckTextPickerOptions.isArray_Array_String(value_range))) {
        valueSerializer.writeInt8(1 as int32)
        const value_range_1  = value_range as Array<Array<string>>
        valueSerializer.writeInt32(value_range_1.length as int32)
        for (let i = 0; i < value_range_1.length; i++) {
            const value_range_1_element : Array<string> = value_range_1[i]
            valueSerializer.writeInt32(value_range_1_element.length as int32)
            for (let i = 0; i < value_range_1_element.length; i++) {
                const value_range_1_element_element : string = value_range_1_element[i]
                valueSerializer.writeString(value_range_1_element_element)
            }
        }
    }
    else if (TypeChecker.isResource(value_range, false, false, false, false, false)) {
        valueSerializer.writeInt8(2 as int32)
        const value_range_2  = value_range as Resource
        valueSerializer.writeResource(value_range_2)
    }
    else if (((RuntimeType.OBJECT) == (value_range_type)) && (CheckTextPickerOptions.isArray_TextPickerRangeContent(value_range))) {
        valueSerializer.writeInt8(3 as int32)
        const value_range_3  = value_range as Array<TextPickerRangeContent>
        valueSerializer.writeInt32(value_range_3.length as int32)
        for (let i = 0; i < value_range_3.length; i++) {
            const value_range_3_element : TextPickerRangeContent = value_range_3[i]
            valueSerializer.writeTextPickerRangeContent(value_range_3_element)
        }
    }
    else if (((RuntimeType.OBJECT) == (value_range_type)) && (CheckTextPickerOptions.isArray_TextCascadePickerRangeContent(value_range))) {
        valueSerializer.writeInt8(4 as int32)
        const value_range_4  = value_range as Array<TextCascadePickerRangeContent>
        valueSerializer.writeInt32(value_range_4.length as int32)
        for (let i = 0; i < value_range_4.length; i++) {
            const value_range_4_element : TextCascadePickerRangeContent = value_range_4[i]
            valueSerializer.writeTextCascadePickerRangeContent(value_range_4_element)
        }
    }
    const value_value  = value.value
    let value_value_type : int32 = RuntimeType.UNDEFINED
    value_value_type = runtimeType(value_value)
    valueSerializer.writeInt8(value_value_type as int32)
    if ((RuntimeType.UNDEFINED) != (value_value_type)) {
        const value_value_value  = value_value!
        let value_value_value_type : int32 = RuntimeType.UNDEFINED
        value_value_value_type = runtimeType(value_value_value)
        if (RuntimeType.STRING == value_value_value_type) {
            valueSerializer.writeInt8(0 as int32)
            const value_value_value_0  = value_value_value as string
            valueSerializer.writeString(value_value_value_0)
        }
        else if (TypeChecker.isBindableString(value_value) || TypeChecker.isBindableArrayString(value_value)) {
            valueSerializer.writeInt8(3 as int32)
        }
        else if (RuntimeType.OBJECT == value_value_value_type) {
            valueSerializer.writeInt8(1 as int32)
            const value_value_value_1  = value_value_value as Array<string>
            valueSerializer.writeInt32(value_value_value_1.length as int32)
            for (let i = 0; i < value_value_value_1.length; i++) {
                const value_value_value_1_element : string = value_value_value_1[i]
                valueSerializer.writeString(value_value_value_1_element)
            }
        }
    }
    const value_selected  = value.selected
    let value_selected_type : int32 = RuntimeType.UNDEFINED
    value_selected_type = runtimeType(value_selected)
    valueSerializer.writeInt8(value_selected_type as int32)
    if ((RuntimeType.UNDEFINED) != (value_selected_type)) {
        const value_selected_value  = value_selected!
        let value_selected_value_type : int32 = RuntimeType.UNDEFINED
        value_selected_value_type = runtimeType(value_selected_value)
        if (RuntimeType.NUMBER == value_selected_value_type) {
            valueSerializer.writeInt8(0 as int32)
            const value_selected_value_0  = value_selected_value as number
            valueSerializer.writeNumber(value_selected_value_0)
        }
        else if (TypeChecker.isBindableNumber(value_value) || TypeChecker.isBindableArrayNumber(value_value)) {
            valueSerializer.writeInt8(3 as int32)
        }
        else if (RuntimeType.OBJECT == value_selected_value_type) {
            valueSerializer.writeInt8(1 as int32)
            const value_selected_value_1  = value_selected_value as Array<number>
            valueSerializer.writeInt32(value_selected_value_1.length as int32)
            for (let i = 0; i < value_selected_value_1.length; i++) {
                const value_selected_value_1_element : number = value_selected_value_1[i]
                valueSerializer.writeNumber(value_selected_value_1_element)
            }
        }
    }
    const value_columnWidths  = value.columnWidths
    let value_columnWidths_type : int32 = RuntimeType.UNDEFINED
    value_columnWidths_type = runtimeType(value_columnWidths)
    valueSerializer.writeInt8(value_columnWidths_type as int32)
    if ((RuntimeType.UNDEFINED) != (value_columnWidths_type)) {
        const value_columnWidths_value  = value_columnWidths!
        valueSerializer.writeInt32(value_columnWidths_value.length as int32)
        for (let i = 0; i < value_columnWidths_value.length; i++) {
            const value_columnWidths_value_element : LengthMetrics = value_columnWidths_value[i]
            valueSerializer.writeLengthMetrics(value_columnWidths_value_element)
        }
    }
    const value_defaultPickerItemHeight  = value.defaultPickerItemHeight
    let value_defaultPickerItemHeight_type : int32 = RuntimeType.UNDEFINED
    value_defaultPickerItemHeight_type = runtimeType(value_defaultPickerItemHeight)
    valueSerializer.writeInt8(value_defaultPickerItemHeight_type as int32)
    if ((RuntimeType.UNDEFINED) != (value_defaultPickerItemHeight_type)) {
        const value_defaultPickerItemHeight_value  = value_defaultPickerItemHeight!
        let value_defaultPickerItemHeight_value_type : int32 = RuntimeType.UNDEFINED
        value_defaultPickerItemHeight_value_type = runtimeType(value_defaultPickerItemHeight_value)
        if (RuntimeType.NUMBER == value_defaultPickerItemHeight_value_type) {
            valueSerializer.writeInt8(0 as int32)
            const value_defaultPickerItemHeight_value_0  = value_defaultPickerItemHeight_value as number
            valueSerializer.writeNumber(value_defaultPickerItemHeight_value_0)
        }
        else if (RuntimeType.STRING == value_defaultPickerItemHeight_value_type) {
            valueSerializer.writeInt8(1 as int32)
            const value_defaultPickerItemHeight_value_1  = value_defaultPickerItemHeight_value as string
            valueSerializer.writeString(value_defaultPickerItemHeight_value_1)
        }
    }
    const value_canLoop  = value.canLoop
    let value_canLoop_type : int32 = RuntimeType.UNDEFINED
    value_canLoop_type = runtimeType(value_canLoop)
    valueSerializer.writeInt8(value_canLoop_type as int32)
    if ((RuntimeType.UNDEFINED) != (value_canLoop_type)) {
        const value_canLoop_value  = value_canLoop!
        valueSerializer.writeBoolean(value_canLoop_value)
    }
    const value_disappearTextStyle  = value.disappearTextStyle
    let value_disappearTextStyle_type : int32 = RuntimeType.UNDEFINED
    value_disappearTextStyle_type = runtimeType(value_disappearTextStyle)
    valueSerializer.writeInt8(value_disappearTextStyle_type as int32)
    if ((RuntimeType.UNDEFINED) != (value_disappearTextStyle_type)) {
        const value_disappearTextStyle_value  = value_disappearTextStyle!
        valueSerializer.writePickerTextStyle(value_disappearTextStyle_value)
    }
    const value_textStyle  = value.textStyle
    let value_textStyle_type : int32 = RuntimeType.UNDEFINED
    value_textStyle_type = runtimeType(value_textStyle)
    valueSerializer.writeInt8(value_textStyle_type as int32)
    if ((RuntimeType.UNDEFINED) != (value_textStyle_type)) {
        const value_textStyle_value  = value_textStyle!
        valueSerializer.writePickerTextStyle(value_textStyle_value)
    }
    const value_acceptButtonStyle  = value.acceptButtonStyle
    let value_acceptButtonStyle_type : int32 = RuntimeType.UNDEFINED
    value_acceptButtonStyle_type = runtimeType(value_acceptButtonStyle)
    valueSerializer.writeInt8(value_acceptButtonStyle_type as int32)
    if ((RuntimeType.UNDEFINED) != (value_acceptButtonStyle_type)) {
        const value_acceptButtonStyle_value  = value_acceptButtonStyle!
        valueSerializer.writePickerDialogButtonStyle(value_acceptButtonStyle_value)
    }
    const value_cancelButtonStyle  = value.cancelButtonStyle
    let value_cancelButtonStyle_type : int32 = RuntimeType.UNDEFINED
    value_cancelButtonStyle_type = runtimeType(value_cancelButtonStyle)
    valueSerializer.writeInt8(value_cancelButtonStyle_type as int32)
    if ((RuntimeType.UNDEFINED) != (value_cancelButtonStyle_type)) {
        const value_cancelButtonStyle_value  = value_cancelButtonStyle!
        valueSerializer.writePickerDialogButtonStyle(value_cancelButtonStyle_value)
    }
    const value_selectedTextStyle  = value.selectedTextStyle
    let value_selectedTextStyle_type : int32 = RuntimeType.UNDEFINED
    value_selectedTextStyle_type = runtimeType(value_selectedTextStyle)
    valueSerializer.writeInt8(value_selectedTextStyle_type as int32)
    if ((RuntimeType.UNDEFINED) != (value_selectedTextStyle_type)) {
        const value_selectedTextStyle_value  = value_selectedTextStyle!
        valueSerializer.writePickerTextStyle(value_selectedTextStyle_value)
    }
    const value_disableTextStyleAnimation  = value.disableTextStyleAnimation
    let value_disableTextStyleAnimation_type : int32 = RuntimeType.UNDEFINED
    value_disableTextStyleAnimation_type = runtimeType(value_disableTextStyleAnimation)
    valueSerializer.writeInt8(value_disableTextStyleAnimation_type as int32)
    if ((RuntimeType.UNDEFINED) != (value_disableTextStyleAnimation_type)) {
        const value_disableTextStyleAnimation_value  = value_disableTextStyleAnimation!
        valueSerializer.writeBoolean(value_disableTextStyleAnimation_value)
    }
    const value_defaultTextStyle  = value.defaultTextStyle
    let value_defaultTextStyle_type : int32 = RuntimeType.UNDEFINED
    value_defaultTextStyle_type = runtimeType(value_defaultTextStyle)
    valueSerializer.writeInt8(value_defaultTextStyle_type as int32)
    if ((RuntimeType.UNDEFINED) != (value_defaultTextStyle_type)) {
        const value_defaultTextStyle_value  = value_defaultTextStyle!
        valueSerializer.writeTextPickerTextStyle(value_defaultTextStyle_value)
    }
    const value_onAccept  = value.onAccept
    let value_onAccept_type : int32 = RuntimeType.UNDEFINED
    value_onAccept_type = runtimeType(value_onAccept)
    valueSerializer.writeInt8(value_onAccept_type as int32)
    if ((RuntimeType.UNDEFINED) != (value_onAccept_type)) {
        const value_onAccept_value  = value_onAccept!
        valueSerializer.holdAndWriteCallback(value_onAccept_value)
    }
    const value_onCancel  = value.onCancel
    let value_onCancel_type : int32 = RuntimeType.UNDEFINED
    value_onCancel_type = runtimeType(value_onCancel)
    valueSerializer.writeInt8(value_onCancel_type as int32)
    if ((RuntimeType.UNDEFINED) != (value_onCancel_type)) {
        const value_onCancel_value  = value_onCancel!
        valueSerializer.holdAndWriteCallback(value_onCancel_value)
    }
    const value_onChange  = value.onChange
    let value_onChange_type : int32 = RuntimeType.UNDEFINED
    value_onChange_type = runtimeType(value_onChange)
    valueSerializer.writeInt8(value_onChange_type as int32)
    if ((RuntimeType.UNDEFINED) != (value_onChange_type)) {
        const value_onChange_value  = value_onChange!
        valueSerializer.holdAndWriteCallback(value_onChange_value)
    }
    const value_onScrollStop  = value.onScrollStop
    let value_onScrollStop_type : int32 = RuntimeType.UNDEFINED
    value_onScrollStop_type = runtimeType(value_onScrollStop)
    valueSerializer.writeInt8(value_onScrollStop_type as int32)
    if ((RuntimeType.UNDEFINED) != (value_onScrollStop_type)) {
        const value_onScrollStop_value  = value_onScrollStop!
        valueSerializer.holdAndWriteCallback(value_onScrollStop_value)
    }
    const value_onEnterSelectedArea  = value.onEnterSelectedArea
    let value_onEnterSelectedArea_type : int32 = RuntimeType.UNDEFINED
    value_onEnterSelectedArea_type = runtimeType(value_onEnterSelectedArea)
    valueSerializer.writeInt8(value_onEnterSelectedArea_type as int32)
    if ((RuntimeType.UNDEFINED) != (value_onEnterSelectedArea_type)) {
        const value_onEnterSelectedArea_value  = value_onEnterSelectedArea!
        valueSerializer.holdAndWriteCallback(value_onEnterSelectedArea_value)
    }
    const value_maskRect  = value.maskRect
    let value_maskRect_type : int32 = RuntimeType.UNDEFINED
    value_maskRect_type = runtimeType(value_maskRect)
    valueSerializer.writeInt8(value_maskRect_type as int32)
    if ((RuntimeType.UNDEFINED) != (value_maskRect_type)) {
        const value_maskRect_value  = value_maskRect!
        valueSerializer.writeRectangle(value_maskRect_value)
    }
    const value_alignment  = value.alignment
    let value_alignment_type : int32 = RuntimeType.UNDEFINED
    value_alignment_type = runtimeType(value_alignment)
    valueSerializer.writeInt8(value_alignment_type as int32)
    if ((RuntimeType.UNDEFINED) != (value_alignment_type)) {
        const value_alignment_value  = (value_alignment as DialogAlignment)
        valueSerializer.writeInt32(TypeChecker.DialogAlignment_ToNumeric(value_alignment_value))
    }
    const value_offset  = value.offset
    let value_offset_type : int32 = RuntimeType.UNDEFINED
    value_offset_type = runtimeType(value_offset)
    valueSerializer.writeInt8(value_offset_type as int32)
    if ((RuntimeType.UNDEFINED) != (value_offset_type)) {
        const value_offset_value  = value_offset!
        valueSerializer.writeOffset(value_offset_value)
    }
    const value_backgroundColor  = value.backgroundColor
    let value_backgroundColor_type : int32 = RuntimeType.UNDEFINED
    value_backgroundColor_type = runtimeType(value_backgroundColor)
    valueSerializer.writeInt8(value_backgroundColor_type as int32)
    if ((RuntimeType.UNDEFINED) != (value_backgroundColor_type)) {
        const value_backgroundColor_value  = value_backgroundColor!
        let value_backgroundColor_value_type : int32 = RuntimeType.UNDEFINED
        value_backgroundColor_value_type = runtimeType(value_backgroundColor_value)
        if (TypeChecker.isColor(value_backgroundColor_value)) {
            valueSerializer.writeInt8(0 as int32)
            const value_backgroundColor_value_0  = value_backgroundColor_value as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_backgroundColor_value_0))
        }
        else if (RuntimeType.NUMBER == value_backgroundColor_value_type) {
            valueSerializer.writeInt8(1 as int32)
            const value_backgroundColor_value_1  = value_backgroundColor_value as number
            valueSerializer.writeNumber(value_backgroundColor_value_1)
        }
        else if (RuntimeType.STRING == value_backgroundColor_value_type) {
            valueSerializer.writeInt8(2 as int32)
            const value_backgroundColor_value_2  = value_backgroundColor_value as string
            valueSerializer.writeString(value_backgroundColor_value_2)
        }
        else if (RuntimeType.OBJECT == value_backgroundColor_value_type) {
            valueSerializer.writeInt8(3 as int32)
            const value_backgroundColor_value_3  = value_backgroundColor_value as Resource
            valueSerializer.writeResource(value_backgroundColor_value_3)
        }
    }
    const value_backgroundBlurStyle  = value.backgroundBlurStyle
    let value_backgroundBlurStyle_type : int32 = RuntimeType.UNDEFINED
    value_backgroundBlurStyle_type = runtimeType(value_backgroundBlurStyle)
    valueSerializer.writeInt8(value_backgroundBlurStyle_type as int32)
    if ((RuntimeType.UNDEFINED) != (value_backgroundBlurStyle_type)) {
        const value_backgroundBlurStyle_value  = (value_backgroundBlurStyle as BlurStyle)
        valueSerializer.writeInt32(TypeChecker.BlurStyle_ToNumeric(value_backgroundBlurStyle_value))
    }
    const value_backgroundBlurStyleOptions  = value.backgroundBlurStyleOptions
    let value_backgroundBlurStyleOptions_type : int32 = RuntimeType.UNDEFINED
    value_backgroundBlurStyleOptions_type = runtimeType(value_backgroundBlurStyleOptions)
    valueSerializer.writeInt8(value_backgroundBlurStyleOptions_type as int32)
    if ((RuntimeType.UNDEFINED) != (value_backgroundBlurStyleOptions_type)) {
        const value_backgroundBlurStyleOptions_value  = value_backgroundBlurStyleOptions!
        valueSerializer.writeBackgroundBlurStyleOptions(value_backgroundBlurStyleOptions_value)
    }
    const value_backgroundEffect  = value.backgroundEffect
    let value_backgroundEffect_type : int32 = RuntimeType.UNDEFINED
    value_backgroundEffect_type = runtimeType(value_backgroundEffect)
    valueSerializer.writeInt8(value_backgroundEffect_type as int32)
    if ((RuntimeType.UNDEFINED) != (value_backgroundEffect_type)) {
        const value_backgroundEffect_value  = value_backgroundEffect!
        valueSerializer.writeBackgroundEffectOptions(value_backgroundEffect_value)
    }
    const value_onDidAppear  = value.onDidAppear
    let value_onDidAppear_type : int32 = RuntimeType.UNDEFINED
    value_onDidAppear_type = runtimeType(value_onDidAppear)
    valueSerializer.writeInt8(value_onDidAppear_type as int32)
    if ((RuntimeType.UNDEFINED) != (value_onDidAppear_type)) {
        const value_onDidAppear_value  = value_onDidAppear!
        valueSerializer.holdAndWriteCallback(value_onDidAppear_value)
    }
    const value_onDidDisappear  = value.onDidDisappear
    let value_onDidDisappear_type : int32 = RuntimeType.UNDEFINED
    value_onDidDisappear_type = runtimeType(value_onDidDisappear)
    valueSerializer.writeInt8(value_onDidDisappear_type as int32)
    if ((RuntimeType.UNDEFINED) != (value_onDidDisappear_type)) {
        const value_onDidDisappear_value  = value_onDidDisappear!
        valueSerializer.holdAndWriteCallback(value_onDidDisappear_value)
    }
    const value_onWillAppear  = value.onWillAppear
    let value_onWillAppear_type : int32 = RuntimeType.UNDEFINED
    value_onWillAppear_type = runtimeType(value_onWillAppear)
    valueSerializer.writeInt8(value_onWillAppear_type as int32)
    if ((RuntimeType.UNDEFINED) != (value_onWillAppear_type)) {
        const value_onWillAppear_value  = value_onWillAppear!
        valueSerializer.holdAndWriteCallback(value_onWillAppear_value)
    }
    const value_onWillDisappear  = value.onWillDisappear
    let value_onWillDisappear_type : int32 = RuntimeType.UNDEFINED
    value_onWillDisappear_type = runtimeType(value_onWillDisappear)
    valueSerializer.writeInt8(value_onWillDisappear_type as int32)
    if ((RuntimeType.UNDEFINED) != (value_onWillDisappear_type)) {
        const value_onWillDisappear_value  = value_onWillDisappear!
        valueSerializer.holdAndWriteCallback(value_onWillDisappear_value)
    }
    const value_shadow  = value.shadow
    let value_shadow_type : int32 = RuntimeType.UNDEFINED
    value_shadow_type = runtimeType(value_shadow)
    valueSerializer.writeInt8(value_shadow_type as int32)
    if ((RuntimeType.UNDEFINED) != (value_shadow_type)) {
        const value_shadow_value  = value_shadow!
        let value_shadow_value_type : int32 = RuntimeType.UNDEFINED
        value_shadow_value_type = runtimeType(value_shadow_value)
        if (TypeChecker.isShadowOptions(value_shadow_value_type, false, false, false, false, false, false)) {
            valueSerializer.writeInt8(0 as int32)
            const value_shadow_value_0  = value_shadow_value as ShadowOptions
            valueSerializer.writeShadowOptions(value_shadow_value_0)
        }
        else if (TypeChecker.isShadowStyle(value_shadow_value)) {
            valueSerializer.writeInt8(1 as int32)
            const value_shadow_value_1  = value_shadow_value as ShadowStyle
            valueSerializer.writeInt32(TypeChecker.ShadowStyle_ToNumeric(value_shadow_value_1))
        }
    }
    const value_enableHoverMode  = value.enableHoverMode
    let value_enableHoverMode_type : int32 = RuntimeType.UNDEFINED
    value_enableHoverMode_type = runtimeType(value_enableHoverMode)
    valueSerializer.writeInt8(value_enableHoverMode_type as int32)
    if ((RuntimeType.UNDEFINED) != (value_enableHoverMode_type)) {
        const value_enableHoverMode_value  = value_enableHoverMode!
        valueSerializer.writeBoolean(value_enableHoverMode_value)
    }
    const value_hoverModeArea  = value.hoverModeArea
    let value_hoverModeArea_type : int32 = RuntimeType.UNDEFINED
    value_hoverModeArea_type = runtimeType(value_hoverModeArea)
    valueSerializer.writeInt8(value_hoverModeArea_type as int32)
    if ((RuntimeType.UNDEFINED) != (value_hoverModeArea_type)) {
        const value_hoverModeArea_value  = (value_hoverModeArea as HoverModeAreaType)
        valueSerializer.writeInt32(TypeChecker.HoverModeAreaType_ToNumeric(value_hoverModeArea_value))
    }
    const value_enableHapticFeedback  = value.enableHapticFeedback
    let value_enableHapticFeedback_type : int32 = RuntimeType.UNDEFINED
    value_enableHapticFeedback_type = runtimeType(value_enableHapticFeedback)
    valueSerializer.writeInt8(value_enableHapticFeedback_type as int32)
    if ((RuntimeType.UNDEFINED) != (value_enableHapticFeedback_type)) {
        const value_enableHapticFeedback_value  = value_enableHapticFeedback!
        valueSerializer.writeBoolean(value_enableHapticFeedback_value)
    }
}

class TextPickerOpsHandWritten {
    static hookTextPickerSelectedImpl(peer: ArkTextPickerPeer, value: Bindable<number | Array<number>>) {
        TextPickerSelectedOps.registerTextPickerSelectedCallback(peer.getPeerPtr(), value.value, (v) => {
	        value.onChange(v)
	    });
    }

    static hookTextPickerValueImpl(peer: ArkTextPickerPeer, value: Bindable<string | Array<string>>) {
        TextPickerValueOps.registerTextPickerValueCallback(peer.getPeerPtr(), value.value, (v) => {
	        value.onChange(v)
	    });
    }
}

export type TextPickerValueCallback = (value: string | Array<string>) => void;
export type TextPickerSelectedCallback = (selected: number | Array<number>) => void;
