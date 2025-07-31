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
