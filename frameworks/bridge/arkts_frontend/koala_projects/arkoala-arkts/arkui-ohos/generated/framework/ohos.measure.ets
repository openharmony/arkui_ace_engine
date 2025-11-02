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

import { Resource_serializer } from "./resource"
import { MeasureOptions } from "@ohos.measure"
import { SerializerBase, DeserializerBase, CallbackResource, InteropNativeModule, MaterializedBase, Tags, RuntimeType, runtimeType, toPeerPtr, nullptr, KPointer, NativeBuffer, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { TypeChecker } from "#components"
import { CallbackTransformer } from "./../CallbackTransformer"
import { Resource } from "global.resource"
import { FontStyle, FontWeight, TextAlign, TextOverflow, TextCase, WordBreak } from "./../component/enums"
export class MeasureOptions_serializer {
    public static write(buffer: SerializerBase, value: MeasureOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForTextContent  = value.textContent
        if (valueHolderForTextContent instanceof string) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForTextContentForIdx0  = valueHolderForTextContent as string
            valueSerializer.writeString(valueHolderForTextContentForIdx0)
        } else if (valueHolderForTextContent instanceof Resource) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForTextContentForIdx1  = valueHolderForTextContent as Resource
            Resource_serializer.write(valueSerializer, valueHolderForTextContentForIdx1)
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
            } else if (valueHolderForConstraintWidthTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForConstraintWidthTmpValueForIdx2  = valueHolderForConstraintWidthTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForConstraintWidthTmpValueForIdx2)
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
            } else if (valueHolderForFontSizeTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForFontSizeTmpValueForIdx2  = valueHolderForFontSizeTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForFontSizeTmpValueForIdx2)
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
            } else if (valueHolderForFontFamilyTmpValue instanceof Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForFontFamilyTmpValueForIdx1  = valueHolderForFontFamilyTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForFontFamilyTmpValueForIdx1)
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
            } else if (valueHolderForLineHeightTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForLineHeightTmpValueForIdx2  = valueHolderForLineHeightTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForLineHeightTmpValueForIdx2)
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
        let textContentTmpBuf : string | Resource | undefined
        if (textContentTmpBufUnionSelector == (0).toChar()) {
            textContentTmpBuf = (valueDeserializer.readString() as string)
        } else if (textContentTmpBufUnionSelector == (1).toChar()) {
            textContentTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for textContentTmpBuf has to be chosen through deserialisation.")
        }
        const textContentTmpResult : string | Resource = (textContentTmpBuf as string | Resource)
        const constraintWidthTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let constraintWidthTmpBuf : double | string | Resource | undefined = undefined
        if ((constraintWidthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const constraintWidthTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let constraintWidthTmpBuf_ : double | string | Resource | undefined
            if (constraintWidthTmpBuf_UnionSelector == (0).toChar()) {
                constraintWidthTmpBuf_ = valueDeserializer.readFloat64()
            } else if (constraintWidthTmpBuf_UnionSelector == (1).toChar()) {
                constraintWidthTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (constraintWidthTmpBuf_UnionSelector == (2).toChar()) {
                constraintWidthTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for constraintWidthTmpBuf_ has to be chosen through deserialisation.")
            }
            constraintWidthTmpBuf = (constraintWidthTmpBuf_ as double | string | Resource)
        }
        const constraintWidthTmpResult : double | string | Resource | undefined = constraintWidthTmpBuf
        const fontSizeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fontSizeTmpBuf : double | string | Resource | undefined = undefined
        if ((fontSizeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const fontSizeTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let fontSizeTmpBuf_ : double | string | Resource | undefined
            if (fontSizeTmpBuf_UnionSelector == (0).toChar()) {
                fontSizeTmpBuf_ = valueDeserializer.readFloat64()
            } else if (fontSizeTmpBuf_UnionSelector == (1).toChar()) {
                fontSizeTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (fontSizeTmpBuf_UnionSelector == (2).toChar()) {
                fontSizeTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for fontSizeTmpBuf_ has to be chosen through deserialisation.")
            }
            fontSizeTmpBuf = (fontSizeTmpBuf_ as double | string | Resource)
        }
        const fontSizeTmpResult : double | string | Resource | undefined = fontSizeTmpBuf
        const fontStyleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fontStyleTmpBuf : int32 | FontStyle | undefined = undefined
        if ((fontStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const fontStyleTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let fontStyleTmpBuf_ : int32 | FontStyle | undefined
            if (fontStyleTmpBuf_UnionSelector == (0).toChar()) {
                fontStyleTmpBuf_ = valueDeserializer.readInt32()
            } else if (fontStyleTmpBuf_UnionSelector == (1).toChar()) {
                fontStyleTmpBuf_ = FontStyle.fromValue(valueDeserializer.readInt32())
            } else {
                throw new Error("One of the branches for fontStyleTmpBuf_ has to be chosen through deserialisation.")
            }
            fontStyleTmpBuf = (fontStyleTmpBuf_ as int32 | FontStyle)
        }
        const fontStyleTmpResult : int32 | FontStyle | undefined = fontStyleTmpBuf
        const fontWeightTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fontWeightTmpBuf : int32 | string | FontWeight | undefined = undefined
        if ((fontWeightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const fontWeightTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let fontWeightTmpBuf_ : int32 | string | FontWeight | undefined
            if (fontWeightTmpBuf_UnionSelector == (0).toChar()) {
                fontWeightTmpBuf_ = valueDeserializer.readInt32()
            } else if (fontWeightTmpBuf_UnionSelector == (1).toChar()) {
                fontWeightTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (fontWeightTmpBuf_UnionSelector == (2).toChar()) {
                fontWeightTmpBuf_ = FontWeight.fromValue(valueDeserializer.readInt32())
            } else {
                throw new Error("One of the branches for fontWeightTmpBuf_ has to be chosen through deserialisation.")
            }
            fontWeightTmpBuf = (fontWeightTmpBuf_ as int32 | string | FontWeight)
        }
        const fontWeightTmpResult : int32 | string | FontWeight | undefined = fontWeightTmpBuf
        const fontFamilyTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fontFamilyTmpBuf : string | Resource | undefined = undefined
        if ((fontFamilyTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const fontFamilyTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let fontFamilyTmpBuf_ : string | Resource | undefined
            if (fontFamilyTmpBuf_UnionSelector == (0).toChar()) {
                fontFamilyTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (fontFamilyTmpBuf_UnionSelector == (1).toChar()) {
                fontFamilyTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for fontFamilyTmpBuf_ has to be chosen through deserialisation.")
            }
            fontFamilyTmpBuf = (fontFamilyTmpBuf_ as string | Resource)
        }
        const fontFamilyTmpResult : string | Resource | undefined = fontFamilyTmpBuf
        const letterSpacingTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let letterSpacingTmpBuf : double | string | undefined = undefined
        if ((letterSpacingTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const letterSpacingTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let letterSpacingTmpBuf_ : double | string | undefined
            if (letterSpacingTmpBuf_UnionSelector == (0).toChar()) {
                letterSpacingTmpBuf_ = valueDeserializer.readFloat64()
            } else if (letterSpacingTmpBuf_UnionSelector == (1).toChar()) {
                letterSpacingTmpBuf_ = (valueDeserializer.readString() as string)
            } else {
                throw new Error("One of the branches for letterSpacingTmpBuf_ has to be chosen through deserialisation.")
            }
            letterSpacingTmpBuf = (letterSpacingTmpBuf_ as double | string)
        }
        const letterSpacingTmpResult : double | string | undefined = letterSpacingTmpBuf
        const textAlignTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let textAlignTmpBuf : int32 | TextAlign | undefined = undefined
        if ((textAlignTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const textAlignTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let textAlignTmpBuf_ : int32 | TextAlign | undefined
            if (textAlignTmpBuf_UnionSelector == (0).toChar()) {
                textAlignTmpBuf_ = valueDeserializer.readInt32()
            } else if (textAlignTmpBuf_UnionSelector == (1).toChar()) {
                textAlignTmpBuf_ = TextAlign.fromValue(valueDeserializer.readInt32())
            } else {
                throw new Error("One of the branches for textAlignTmpBuf_ has to be chosen through deserialisation.")
            }
            textAlignTmpBuf = (textAlignTmpBuf_ as int32 | TextAlign)
        }
        const textAlignTmpResult : int32 | TextAlign | undefined = textAlignTmpBuf
        const overflowTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let overflowTmpBuf : int32 | TextOverflow | undefined = undefined
        if ((overflowTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const overflowTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let overflowTmpBuf_ : int32 | TextOverflow | undefined
            if (overflowTmpBuf_UnionSelector == (0).toChar()) {
                overflowTmpBuf_ = valueDeserializer.readInt32()
            } else if (overflowTmpBuf_UnionSelector == (1).toChar()) {
                overflowTmpBuf_ = TextOverflow.fromValue(valueDeserializer.readInt32())
            } else {
                throw new Error("One of the branches for overflowTmpBuf_ has to be chosen through deserialisation.")
            }
            overflowTmpBuf = (overflowTmpBuf_ as int32 | TextOverflow)
        }
        const overflowTmpResult : int32 | TextOverflow | undefined = overflowTmpBuf
        const maxLinesTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let maxLinesTmpBuf : int32 | undefined = undefined
        if ((maxLinesTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            maxLinesTmpBuf = valueDeserializer.readInt32()
        }
        const maxLinesTmpResult : int32 | undefined = maxLinesTmpBuf
        const lineHeightTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let lineHeightTmpBuf : double | string | Resource | undefined = undefined
        if ((lineHeightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const lineHeightTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let lineHeightTmpBuf_ : double | string | Resource | undefined
            if (lineHeightTmpBuf_UnionSelector == (0).toChar()) {
                lineHeightTmpBuf_ = valueDeserializer.readFloat64()
            } else if (lineHeightTmpBuf_UnionSelector == (1).toChar()) {
                lineHeightTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (lineHeightTmpBuf_UnionSelector == (2).toChar()) {
                lineHeightTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for lineHeightTmpBuf_ has to be chosen through deserialisation.")
            }
            lineHeightTmpBuf = (lineHeightTmpBuf_ as double | string | Resource)
        }
        const lineHeightTmpResult : double | string | Resource | undefined = lineHeightTmpBuf
        const baselineOffsetTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let baselineOffsetTmpBuf : double | string | undefined = undefined
        if ((baselineOffsetTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const baselineOffsetTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let baselineOffsetTmpBuf_ : double | string | undefined
            if (baselineOffsetTmpBuf_UnionSelector == (0).toChar()) {
                baselineOffsetTmpBuf_ = valueDeserializer.readFloat64()
            } else if (baselineOffsetTmpBuf_UnionSelector == (1).toChar()) {
                baselineOffsetTmpBuf_ = (valueDeserializer.readString() as string)
            } else {
                throw new Error("One of the branches for baselineOffsetTmpBuf_ has to be chosen through deserialisation.")
            }
            baselineOffsetTmpBuf = (baselineOffsetTmpBuf_ as double | string)
        }
        const baselineOffsetTmpResult : double | string | undefined = baselineOffsetTmpBuf
        const textCaseTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let textCaseTmpBuf : int32 | TextCase | undefined = undefined
        if ((textCaseTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const textCaseTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let textCaseTmpBuf_ : int32 | TextCase | undefined
            if (textCaseTmpBuf_UnionSelector == (0).toChar()) {
                textCaseTmpBuf_ = valueDeserializer.readInt32()
            } else if (textCaseTmpBuf_UnionSelector == (1).toChar()) {
                textCaseTmpBuf_ = TextCase.fromValue(valueDeserializer.readInt32())
            } else {
                throw new Error("One of the branches for textCaseTmpBuf_ has to be chosen through deserialisation.")
            }
            textCaseTmpBuf = (textCaseTmpBuf_ as int32 | TextCase)
        }
        const textCaseTmpResult : int32 | TextCase | undefined = textCaseTmpBuf
        const textIndentTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let textIndentTmpBuf : double | string | undefined = undefined
        if ((textIndentTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const textIndentTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let textIndentTmpBuf_ : double | string | undefined
            if (textIndentTmpBuf_UnionSelector == (0).toChar()) {
                textIndentTmpBuf_ = valueDeserializer.readFloat64()
            } else if (textIndentTmpBuf_UnionSelector == (1).toChar()) {
                textIndentTmpBuf_ = (valueDeserializer.readString() as string)
            } else {
                throw new Error("One of the branches for textIndentTmpBuf_ has to be chosen through deserialisation.")
            }
            textIndentTmpBuf = (textIndentTmpBuf_ as double | string)
        }
        const textIndentTmpResult : double | string | undefined = textIndentTmpBuf
        const wordBreakTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let wordBreakTmpBuf : WordBreak | undefined = undefined
        if ((wordBreakTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            wordBreakTmpBuf = WordBreak.fromValue(valueDeserializer.readInt32())
        }
        const wordBreakTmpResult : WordBreak | undefined = wordBreakTmpBuf
        let value : MeasureOptions = ({textContent: textContentTmpResult, constraintWidth: constraintWidthTmpResult, fontSize: fontSizeTmpResult, fontStyle: fontStyleTmpResult, fontWeight: fontWeightTmpResult, fontFamily: fontFamilyTmpResult, letterSpacing: letterSpacingTmpResult, textAlign: textAlignTmpResult, overflow: overflowTmpResult, maxLines: maxLinesTmpResult, lineHeight: lineHeightTmpResult, baselineOffset: baselineOffsetTmpResult, textCase: textCaseTmpResult, textIndent: textIndentTmpResult, wordBreak: wordBreakTmpResult} as MeasureOptions)
        return value
    }
}
