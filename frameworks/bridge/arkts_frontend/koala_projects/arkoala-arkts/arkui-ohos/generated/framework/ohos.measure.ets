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

import { global_resource_Resource_serializer } from './resource'
import { MeasureOptions } from '@ohos.measure'
import { SerializerBase, DeserializerBase, CallbackResource, InteropNativeModule, MaterializedBase, Tags, RuntimeType, toPeerPtr, nullptr, KPointer, NativeBuffer, KSerializerBuffer, KUint8ArrayPtr } from '@koalaui/interop'
import { int32, int64, float32, unsafeCast } from '@koalaui/common'
import { CallbackTransformer } from './../CallbackTransformer'
import { Resource as global_resource_Resource } from 'global.resource'
import { FontStyle, FontWeight, TextAlign, TextOverflow, TextCase, WordBreak } from './../component/enums'
export class MeasureOptions_serializer {
    public static write(buffer: SerializerBase, value: MeasureOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForTextContent  = value.textContent
        if (valueHolderForTextContent instanceof string) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForTextContentForIdx0  = valueHolderForTextContent as string
            valueSerializer.writeString(valueHolderForTextContentForIdx0)
        } else if (valueHolderForTextContent instanceof global_resource_Resource) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForTextContentForIdx1  = valueHolderForTextContent as global_resource_Resource
            global_resource_Resource_serializer.write(valueSerializer, valueHolderForTextContentForIdx1)
        }
        const valueHolderForConstraintWidth  = value.constraintWidth
        if (valueHolderForConstraintWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForConstraintWidthTmpValue  = valueHolderForConstraintWidth!
            if (valueHolderForConstraintWidthTmpValue instanceof double) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForConstraintWidthTmpValueForIdx0  = valueHolderForConstraintWidthTmpValue as double
                valueSerializer.writeFloat64(valueHolderForConstraintWidthTmpValueForIdx0)
            } else if (valueHolderForConstraintWidthTmpValue instanceof string) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForConstraintWidthTmpValueForIdx1  = valueHolderForConstraintWidthTmpValue as string
                valueSerializer.writeString(valueHolderForConstraintWidthTmpValueForIdx1)
            } else if (valueHolderForConstraintWidthTmpValue instanceof global_resource_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForConstraintWidthTmpValueForIdx2  = valueHolderForConstraintWidthTmpValue as global_resource_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForConstraintWidthTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForFontSize  = value.fontSize
        if (valueHolderForFontSize !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFontSizeTmpValue  = valueHolderForFontSize!
            if (valueHolderForFontSizeTmpValue instanceof double) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForFontSizeTmpValueForIdx0  = valueHolderForFontSizeTmpValue as double
                valueSerializer.writeFloat64(valueHolderForFontSizeTmpValueForIdx0)
            } else if (valueHolderForFontSizeTmpValue instanceof string) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForFontSizeTmpValueForIdx1  = valueHolderForFontSizeTmpValue as string
                valueSerializer.writeString(valueHolderForFontSizeTmpValueForIdx1)
            } else if (valueHolderForFontSizeTmpValue instanceof global_resource_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForFontSizeTmpValueForIdx2  = valueHolderForFontSizeTmpValue as global_resource_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForFontSizeTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForFontStyle  = value.fontStyle
        if (valueHolderForFontStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFontStyleTmpValue  = valueHolderForFontStyle!
            if (valueHolderForFontStyleTmpValue instanceof int32) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForFontStyleTmpValueForIdx0  = valueHolderForFontStyleTmpValue as int32
                valueSerializer.writeInt32(valueHolderForFontStyleTmpValueForIdx0)
            } else if (valueHolderForFontStyleTmpValue instanceof FontStyle) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForFontStyleTmpValueForIdx1  = valueHolderForFontStyleTmpValue as FontStyle
                valueSerializer.writeInt32(valueHolderForFontStyleTmpValueForIdx1.valueOf())
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForFontWeight  = value.fontWeight
        if (valueHolderForFontWeight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFontWeightTmpValue  = valueHolderForFontWeight!
            if (valueHolderForFontWeightTmpValue instanceof int32) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForFontWeightTmpValueForIdx0  = valueHolderForFontWeightTmpValue as int32
                valueSerializer.writeInt32(valueHolderForFontWeightTmpValueForIdx0)
            } else if (valueHolderForFontWeightTmpValue instanceof string) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForFontWeightTmpValueForIdx1  = valueHolderForFontWeightTmpValue as string
                valueSerializer.writeString(valueHolderForFontWeightTmpValueForIdx1)
            } else if (valueHolderForFontWeightTmpValue instanceof FontWeight) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForFontWeightTmpValueForIdx2  = valueHolderForFontWeightTmpValue as FontWeight
                valueSerializer.writeInt32(valueHolderForFontWeightTmpValueForIdx2.valueOf())
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForFontFamily  = value.fontFamily
        if (valueHolderForFontFamily !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFontFamilyTmpValue  = valueHolderForFontFamily!
            if (valueHolderForFontFamilyTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForFontFamilyTmpValueForIdx0  = valueHolderForFontFamilyTmpValue as string
                valueSerializer.writeString(valueHolderForFontFamilyTmpValueForIdx0)
            } else if (valueHolderForFontFamilyTmpValue instanceof global_resource_Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForFontFamilyTmpValueForIdx1  = valueHolderForFontFamilyTmpValue as global_resource_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForFontFamilyTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLetterSpacing  = value.letterSpacing
        if (valueHolderForLetterSpacing !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLetterSpacingTmpValue  = valueHolderForLetterSpacing!
            if (valueHolderForLetterSpacingTmpValue instanceof double) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForLetterSpacingTmpValueForIdx0  = valueHolderForLetterSpacingTmpValue as double
                valueSerializer.writeFloat64(valueHolderForLetterSpacingTmpValueForIdx0)
            } else if (valueHolderForLetterSpacingTmpValue instanceof string) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForLetterSpacingTmpValueForIdx1  = valueHolderForLetterSpacingTmpValue as string
                valueSerializer.writeString(valueHolderForLetterSpacingTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForTextAlign  = value.textAlign
        if (valueHolderForTextAlign !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTextAlignTmpValue  = valueHolderForTextAlign!
            if (valueHolderForTextAlignTmpValue instanceof int32) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForTextAlignTmpValueForIdx0  = valueHolderForTextAlignTmpValue as int32
                valueSerializer.writeInt32(valueHolderForTextAlignTmpValueForIdx0)
            } else if (valueHolderForTextAlignTmpValue instanceof TextAlign) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForTextAlignTmpValueForIdx1  = valueHolderForTextAlignTmpValue as TextAlign
                valueSerializer.writeInt32(valueHolderForTextAlignTmpValueForIdx1.valueOf())
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOverflow  = value.overflow
        if (valueHolderForOverflow !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOverflowTmpValue  = valueHolderForOverflow!
            if (valueHolderForOverflowTmpValue instanceof int32) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForOverflowTmpValueForIdx0  = valueHolderForOverflowTmpValue as int32
                valueSerializer.writeInt32(valueHolderForOverflowTmpValueForIdx0)
            } else if (valueHolderForOverflowTmpValue instanceof TextOverflow) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForOverflowTmpValueForIdx1  = valueHolderForOverflowTmpValue as TextOverflow
                valueSerializer.writeInt32(valueHolderForOverflowTmpValueForIdx1.valueOf())
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMaxLines  = value.maxLines
        if (valueHolderForMaxLines !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMaxLinesTmpValue  = valueHolderForMaxLines!
            valueSerializer.writeInt32(valueHolderForMaxLinesTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLineHeight  = value.lineHeight
        if (valueHolderForLineHeight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLineHeightTmpValue  = valueHolderForLineHeight!
            if (valueHolderForLineHeightTmpValue instanceof double) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForLineHeightTmpValueForIdx0  = valueHolderForLineHeightTmpValue as double
                valueSerializer.writeFloat64(valueHolderForLineHeightTmpValueForIdx0)
            } else if (valueHolderForLineHeightTmpValue instanceof string) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForLineHeightTmpValueForIdx1  = valueHolderForLineHeightTmpValue as string
                valueSerializer.writeString(valueHolderForLineHeightTmpValueForIdx1)
            } else if (valueHolderForLineHeightTmpValue instanceof global_resource_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForLineHeightTmpValueForIdx2  = valueHolderForLineHeightTmpValue as global_resource_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForLineHeightTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBaselineOffset  = value.baselineOffset
        if (valueHolderForBaselineOffset !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBaselineOffsetTmpValue  = valueHolderForBaselineOffset!
            if (valueHolderForBaselineOffsetTmpValue instanceof double) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForBaselineOffsetTmpValueForIdx0  = valueHolderForBaselineOffsetTmpValue as double
                valueSerializer.writeFloat64(valueHolderForBaselineOffsetTmpValueForIdx0)
            } else if (valueHolderForBaselineOffsetTmpValue instanceof string) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForBaselineOffsetTmpValueForIdx1  = valueHolderForBaselineOffsetTmpValue as string
                valueSerializer.writeString(valueHolderForBaselineOffsetTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForTextCase  = value.textCase
        if (valueHolderForTextCase !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTextCaseTmpValue  = valueHolderForTextCase!
            if (valueHolderForTextCaseTmpValue instanceof int32) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForTextCaseTmpValueForIdx0  = valueHolderForTextCaseTmpValue as int32
                valueSerializer.writeInt32(valueHolderForTextCaseTmpValueForIdx0)
            } else if (valueHolderForTextCaseTmpValue instanceof TextCase) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForTextCaseTmpValueForIdx1  = valueHolderForTextCaseTmpValue as TextCase
                valueSerializer.writeInt32(valueHolderForTextCaseTmpValueForIdx1.valueOf())
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForTextIndent  = value.textIndent
        if (valueHolderForTextIndent !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTextIndentTmpValue  = valueHolderForTextIndent!
            if (valueHolderForTextIndentTmpValue instanceof double) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForTextIndentTmpValueForIdx0  = valueHolderForTextIndentTmpValue as double
                valueSerializer.writeFloat64(valueHolderForTextIndentTmpValueForIdx0)
            } else if (valueHolderForTextIndentTmpValue instanceof string) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForTextIndentTmpValueForIdx1  = valueHolderForTextIndentTmpValue as string
                valueSerializer.writeString(valueHolderForTextIndentTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForWordBreak  = value.wordBreak
        if (valueHolderForWordBreak !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForWordBreakTmpValue  = (valueHolderForWordBreak as WordBreak)
            valueSerializer.writeInt32(valueHolderForWordBreakTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): MeasureOptions {
        let valueDeserializer : DeserializerBase = buffer
        const textContentTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let textContentTmpBuf : string | global_resource_Resource | undefined
        if (textContentTmpBufUnionSelector == (0).toByte()) {
            textContentTmpBuf = (valueDeserializer.readString() as string)
        } else if (textContentTmpBufUnionSelector == (1).toByte()) {
            textContentTmpBuf = global_resource_Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error('One of the branches for textContentTmpBuf has to be chosen through deserialisation.')
        }
        const textContentTmpResult : string | global_resource_Resource = (textContentTmpBuf as string | global_resource_Resource)
        const constraintWidthTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let constraintWidthTmpBuf : double | string | global_resource_Resource | undefined = undefined
        if ((constraintWidthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const constraintWidthTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let constraintWidthTmpBufOpt : double | string | global_resource_Resource | undefined
            if (constraintWidthTmpBufOptUnionSelector == (0).toByte()) {
                constraintWidthTmpBufOpt = valueDeserializer.readFloat64()
            } else if (constraintWidthTmpBufOptUnionSelector == (1).toByte()) {
                constraintWidthTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (constraintWidthTmpBufOptUnionSelector == (2).toByte()) {
                constraintWidthTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for constraintWidthTmpBufOpt has to be chosen through deserialisation.')
            }
            constraintWidthTmpBuf = (constraintWidthTmpBufOpt as double | string | global_resource_Resource)
        }
        const constraintWidthTmpResult : double | string | global_resource_Resource | undefined = constraintWidthTmpBuf
        const fontSizeTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let fontSizeTmpBuf : double | string | global_resource_Resource | undefined = undefined
        if ((fontSizeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const fontSizeTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let fontSizeTmpBufOpt : double | string | global_resource_Resource | undefined
            if (fontSizeTmpBufOptUnionSelector == (0).toByte()) {
                fontSizeTmpBufOpt = valueDeserializer.readFloat64()
            } else if (fontSizeTmpBufOptUnionSelector == (1).toByte()) {
                fontSizeTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (fontSizeTmpBufOptUnionSelector == (2).toByte()) {
                fontSizeTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for fontSizeTmpBufOpt has to be chosen through deserialisation.')
            }
            fontSizeTmpBuf = (fontSizeTmpBufOpt as double | string | global_resource_Resource)
        }
        const fontSizeTmpResult : double | string | global_resource_Resource | undefined = fontSizeTmpBuf
        const fontStyleTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let fontStyleTmpBuf : int32 | FontStyle | undefined = undefined
        if ((fontStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const fontStyleTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let fontStyleTmpBufOpt : int32 | FontStyle | undefined
            if (fontStyleTmpBufOptUnionSelector == (0).toByte()) {
                fontStyleTmpBufOpt = valueDeserializer.readInt32()
            } else if (fontStyleTmpBufOptUnionSelector == (1).toByte()) {
                fontStyleTmpBufOpt = FontStyle.fromValue(valueDeserializer.readInt32())
            } else {
                throw new Error('One of the branches for fontStyleTmpBufOpt has to be chosen through deserialisation.')
            }
            fontStyleTmpBuf = (fontStyleTmpBufOpt as int32 | FontStyle)
        }
        const fontStyleTmpResult : int32 | FontStyle | undefined = fontStyleTmpBuf
        const fontWeightTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let fontWeightTmpBuf : int32 | string | FontWeight | undefined = undefined
        if ((fontWeightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const fontWeightTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let fontWeightTmpBufOpt : int32 | string | FontWeight | undefined
            if (fontWeightTmpBufOptUnionSelector == (0).toByte()) {
                fontWeightTmpBufOpt = valueDeserializer.readInt32()
            } else if (fontWeightTmpBufOptUnionSelector == (1).toByte()) {
                fontWeightTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (fontWeightTmpBufOptUnionSelector == (2).toByte()) {
                fontWeightTmpBufOpt = FontWeight.fromValue(valueDeserializer.readInt32())
            } else {
                throw new Error('One of the branches for fontWeightTmpBufOpt has to be chosen through deserialisation.')
            }
            fontWeightTmpBuf = (fontWeightTmpBufOpt as int32 | string | FontWeight)
        }
        const fontWeightTmpResult : int32 | string | FontWeight | undefined = fontWeightTmpBuf
        const fontFamilyTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let fontFamilyTmpBuf : string | global_resource_Resource | undefined = undefined
        if ((fontFamilyTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const fontFamilyTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let fontFamilyTmpBufOpt : string | global_resource_Resource | undefined
            if (fontFamilyTmpBufOptUnionSelector == (0).toByte()) {
                fontFamilyTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (fontFamilyTmpBufOptUnionSelector == (1).toByte()) {
                fontFamilyTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for fontFamilyTmpBufOpt has to be chosen through deserialisation.')
            }
            fontFamilyTmpBuf = (fontFamilyTmpBufOpt as string | global_resource_Resource)
        }
        const fontFamilyTmpResult : string | global_resource_Resource | undefined = fontFamilyTmpBuf
        const letterSpacingTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let letterSpacingTmpBuf : double | string | undefined = undefined
        if ((letterSpacingTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const letterSpacingTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let letterSpacingTmpBufOpt : double | string | undefined
            if (letterSpacingTmpBufOptUnionSelector == (0).toByte()) {
                letterSpacingTmpBufOpt = valueDeserializer.readFloat64()
            } else if (letterSpacingTmpBufOptUnionSelector == (1).toByte()) {
                letterSpacingTmpBufOpt = (valueDeserializer.readString() as string)
            } else {
                throw new Error('One of the branches for letterSpacingTmpBufOpt has to be chosen through deserialisation.')
            }
            letterSpacingTmpBuf = (letterSpacingTmpBufOpt as double | string)
        }
        const letterSpacingTmpResult : double | string | undefined = letterSpacingTmpBuf
        const textAlignTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let textAlignTmpBuf : int32 | TextAlign | undefined = undefined
        if ((textAlignTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const textAlignTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let textAlignTmpBufOpt : int32 | TextAlign | undefined
            if (textAlignTmpBufOptUnionSelector == (0).toByte()) {
                textAlignTmpBufOpt = valueDeserializer.readInt32()
            } else if (textAlignTmpBufOptUnionSelector == (1).toByte()) {
                textAlignTmpBufOpt = TextAlign.fromValue(valueDeserializer.readInt32())
            } else {
                throw new Error('One of the branches for textAlignTmpBufOpt has to be chosen through deserialisation.')
            }
            textAlignTmpBuf = (textAlignTmpBufOpt as int32 | TextAlign)
        }
        const textAlignTmpResult : int32 | TextAlign | undefined = textAlignTmpBuf
        const overflowTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let overflowTmpBuf : int32 | TextOverflow | undefined = undefined
        if ((overflowTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const overflowTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let overflowTmpBufOpt : int32 | TextOverflow | undefined
            if (overflowTmpBufOptUnionSelector == (0).toByte()) {
                overflowTmpBufOpt = valueDeserializer.readInt32()
            } else if (overflowTmpBufOptUnionSelector == (1).toByte()) {
                overflowTmpBufOpt = TextOverflow.fromValue(valueDeserializer.readInt32())
            } else {
                throw new Error('One of the branches for overflowTmpBufOpt has to be chosen through deserialisation.')
            }
            overflowTmpBuf = (overflowTmpBufOpt as int32 | TextOverflow)
        }
        const overflowTmpResult : int32 | TextOverflow | undefined = overflowTmpBuf
        const maxLinesTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let maxLinesTmpBuf : int32 | undefined = undefined
        if ((maxLinesTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            maxLinesTmpBuf = valueDeserializer.readInt32()
        }
        const maxLinesTmpResult : int32 | undefined = maxLinesTmpBuf
        const lineHeightTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let lineHeightTmpBuf : double | string | global_resource_Resource | undefined = undefined
        if ((lineHeightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const lineHeightTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let lineHeightTmpBufOpt : double | string | global_resource_Resource | undefined
            if (lineHeightTmpBufOptUnionSelector == (0).toByte()) {
                lineHeightTmpBufOpt = valueDeserializer.readFloat64()
            } else if (lineHeightTmpBufOptUnionSelector == (1).toByte()) {
                lineHeightTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (lineHeightTmpBufOptUnionSelector == (2).toByte()) {
                lineHeightTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for lineHeightTmpBufOpt has to be chosen through deserialisation.')
            }
            lineHeightTmpBuf = (lineHeightTmpBufOpt as double | string | global_resource_Resource)
        }
        const lineHeightTmpResult : double | string | global_resource_Resource | undefined = lineHeightTmpBuf
        const baselineOffsetTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let baselineOffsetTmpBuf : double | string | undefined = undefined
        if ((baselineOffsetTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const baselineOffsetTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let baselineOffsetTmpBufOpt : double | string | undefined
            if (baselineOffsetTmpBufOptUnionSelector == (0).toByte()) {
                baselineOffsetTmpBufOpt = valueDeserializer.readFloat64()
            } else if (baselineOffsetTmpBufOptUnionSelector == (1).toByte()) {
                baselineOffsetTmpBufOpt = (valueDeserializer.readString() as string)
            } else {
                throw new Error('One of the branches for baselineOffsetTmpBufOpt has to be chosen through deserialisation.')
            }
            baselineOffsetTmpBuf = (baselineOffsetTmpBufOpt as double | string)
        }
        const baselineOffsetTmpResult : double | string | undefined = baselineOffsetTmpBuf
        const textCaseTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let textCaseTmpBuf : int32 | TextCase | undefined = undefined
        if ((textCaseTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const textCaseTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let textCaseTmpBufOpt : int32 | TextCase | undefined
            if (textCaseTmpBufOptUnionSelector == (0).toByte()) {
                textCaseTmpBufOpt = valueDeserializer.readInt32()
            } else if (textCaseTmpBufOptUnionSelector == (1).toByte()) {
                textCaseTmpBufOpt = TextCase.fromValue(valueDeserializer.readInt32())
            } else {
                throw new Error('One of the branches for textCaseTmpBufOpt has to be chosen through deserialisation.')
            }
            textCaseTmpBuf = (textCaseTmpBufOpt as int32 | TextCase)
        }
        const textCaseTmpResult : int32 | TextCase | undefined = textCaseTmpBuf
        const textIndentTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let textIndentTmpBuf : double | string | undefined = undefined
        if ((textIndentTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const textIndentTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let textIndentTmpBufOpt : double | string | undefined
            if (textIndentTmpBufOptUnionSelector == (0).toByte()) {
                textIndentTmpBufOpt = valueDeserializer.readFloat64()
            } else if (textIndentTmpBufOptUnionSelector == (1).toByte()) {
                textIndentTmpBufOpt = (valueDeserializer.readString() as string)
            } else {
                throw new Error('One of the branches for textIndentTmpBufOpt has to be chosen through deserialisation.')
            }
            textIndentTmpBuf = (textIndentTmpBufOpt as double | string)
        }
        const textIndentTmpResult : double | string | undefined = textIndentTmpBuf
        const wordBreakTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let wordBreakTmpBuf : WordBreak | undefined = undefined
        if ((wordBreakTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            wordBreakTmpBuf = WordBreak.fromValue(valueDeserializer.readInt32())
        }
        const wordBreakTmpResult : WordBreak | undefined = wordBreakTmpBuf
        let value : MeasureOptions = ({textContent: textContentTmpResult, constraintWidth: constraintWidthTmpResult, fontSize: fontSizeTmpResult, fontStyle: fontStyleTmpResult, fontWeight: fontWeightTmpResult, fontFamily: fontFamilyTmpResult, letterSpacing: letterSpacingTmpResult, textAlign: textAlignTmpResult, overflow: overflowTmpResult, maxLines: maxLinesTmpResult, lineHeight: lineHeightTmpResult, baselineOffset: baselineOffsetTmpResult, textCase: textCaseTmpResult, textIndent: textIndentTmpResult, wordBreak: wordBreakTmpResult} as MeasureOptions)
        return value
    }
}
