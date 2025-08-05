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

import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { KInt, KPointer, KBoolean, NativeBuffer, KStringPtr, SerializerBase, DeserializerBase, CallbackResource, InteropNativeModule, MaterializedBase, Tags, RuntimeType, runtimeType, toPeerPtr, nullptr, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { Resource, Resource_serializer } from "./resource"
import { FontStyle, FontWeight, TextOverflow, TextCase } from "./../component/enums"
import { text } from "./ohos.graphics.text"
import { TypeChecker } from "#components"
import { CallbackTransformer } from "./../CallbackTransformer"
export interface MeasureOptions {
    textContent: string | Resource;
    constraintWidth?: number | string | Resource;
    fontSize?: number | string | Resource;
    fontStyle?: number | FontStyle;
    fontWeight?: number | string | FontWeight;
    fontFamily?: string | Resource;
    letterSpacing?: number | string;
    textAlign?: text.TextAlign;
    overflow?: number | TextOverflow;
    maxLines?: number;
    lineHeight?: number | string | Resource;
    baselineOffset?: number | string;
    textCase?: number | TextCase;
    textIndent?: number | string;
    wordBreak?: text.WordBreak;
}
export class MeasureOptions_serializer {
    public static write(buffer: SerializerBase, value: MeasureOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForTextContent  = value.textContent
        if (valueHolderForTextContent instanceof string) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForTextContentForIdx0  = valueHolderForTextContent as string
            valueSerializer.writeString(valueHolderForTextContentForIdx0)
        } else if (valueHolderForTextContent instanceof Resource) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForTextContentForIdx1  = valueHolderForTextContent as Resource
            Resource_serializer.write(valueSerializer, valueHolderForTextContentForIdx1)
        }
        const valueHolderForConstraintWidth  = value.constraintWidth
        if (valueHolderForConstraintWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForConstraintWidthTmpValue  = valueHolderForConstraintWidth!
            if (valueHolderForConstraintWidthTmpValue instanceof number) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForConstraintWidthTmpValueForIdx0  = valueHolderForConstraintWidthTmpValue as number
                valueSerializer.writeNumber(valueHolderForConstraintWidthTmpValueForIdx0)
            } else if (valueHolderForConstraintWidthTmpValue instanceof string) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForConstraintWidthTmpValueForIdx1  = valueHolderForConstraintWidthTmpValue as string
                valueSerializer.writeString(valueHolderForConstraintWidthTmpValueForIdx1)
            } else if (valueHolderForConstraintWidthTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toChar())
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
            if (valueHolderForFontSizeTmpValue instanceof number) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForFontSizeTmpValueForIdx0  = valueHolderForFontSizeTmpValue as number
                valueSerializer.writeNumber(valueHolderForFontSizeTmpValueForIdx0)
            } else if (valueHolderForFontSizeTmpValue instanceof string) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForFontSizeTmpValueForIdx1  = valueHolderForFontSizeTmpValue as string
                valueSerializer.writeString(valueHolderForFontSizeTmpValueForIdx1)
            } else if (valueHolderForFontSizeTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toChar())
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
            if (valueHolderForFontStyleTmpValue instanceof number) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForFontStyleTmpValueForIdx0  = valueHolderForFontStyleTmpValue as number
                valueSerializer.writeNumber(valueHolderForFontStyleTmpValueForIdx0)
            } else if (valueHolderForFontStyleTmpValue instanceof FontStyle) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForFontStyleTmpValueForIdx1  = valueHolderForFontStyleTmpValue as FontStyle
                valueSerializer.writeInt32(TypeChecker.FontStyle_ToNumeric(valueHolderForFontStyleTmpValueForIdx1))
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForFontWeight  = value.fontWeight
        if (valueHolderForFontWeight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFontWeightTmpValue  = valueHolderForFontWeight!
            if (valueHolderForFontWeightTmpValue instanceof number) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForFontWeightTmpValueForIdx0  = valueHolderForFontWeightTmpValue as number
                valueSerializer.writeNumber(valueHolderForFontWeightTmpValueForIdx0)
            } else if (valueHolderForFontWeightTmpValue instanceof string) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForFontWeightTmpValueForIdx1  = valueHolderForFontWeightTmpValue as string
                valueSerializer.writeString(valueHolderForFontWeightTmpValueForIdx1)
            } else if (valueHolderForFontWeightTmpValue instanceof FontWeight) {
                valueSerializer.writeInt8((2).toChar())
                const valueHolderForFontWeightTmpValueForIdx2  = valueHolderForFontWeightTmpValue as FontWeight
                valueSerializer.writeInt32(TypeChecker.FontWeight_ToNumeric(valueHolderForFontWeightTmpValueForIdx2))
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForFontFamily  = value.fontFamily
        if (valueHolderForFontFamily !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFontFamilyTmpValue  = valueHolderForFontFamily!
            if (valueHolderForFontFamilyTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForFontFamilyTmpValueForIdx0  = valueHolderForFontFamilyTmpValue as string
                valueSerializer.writeString(valueHolderForFontFamilyTmpValueForIdx0)
            } else if (valueHolderForFontFamilyTmpValue instanceof Resource) {
                valueSerializer.writeInt8((1).toChar())
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
            if (valueHolderForLetterSpacingTmpValue instanceof number) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForLetterSpacingTmpValueForIdx0  = valueHolderForLetterSpacingTmpValue as number
                valueSerializer.writeNumber(valueHolderForLetterSpacingTmpValueForIdx0)
            } else if (valueHolderForLetterSpacingTmpValue instanceof string) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForLetterSpacingTmpValueForIdx1  = valueHolderForLetterSpacingTmpValue as string
                valueSerializer.writeString(valueHolderForLetterSpacingTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForTextAlign  = value.textAlign
        if (valueHolderForTextAlign !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTextAlignTmpValue  = (valueHolderForTextAlign as text.TextAlign)
            valueSerializer.writeInt32(TypeChecker.text_TextAlign_ToNumeric(valueHolderForTextAlignTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOverflow  = value.overflow
        if (valueHolderForOverflow !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOverflowTmpValue  = valueHolderForOverflow!
            if (valueHolderForOverflowTmpValue instanceof number) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForOverflowTmpValueForIdx0  = valueHolderForOverflowTmpValue as number
                valueSerializer.writeNumber(valueHolderForOverflowTmpValueForIdx0)
            } else if (valueHolderForOverflowTmpValue instanceof TextOverflow) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForOverflowTmpValueForIdx1  = valueHolderForOverflowTmpValue as TextOverflow
                valueSerializer.writeInt32(TypeChecker.TextOverflow_ToNumeric(valueHolderForOverflowTmpValueForIdx1))
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMaxLines  = value.maxLines
        if (valueHolderForMaxLines !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMaxLinesTmpValue  = valueHolderForMaxLines!
            valueSerializer.writeNumber(valueHolderForMaxLinesTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLineHeight  = value.lineHeight
        if (valueHolderForLineHeight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLineHeightTmpValue  = valueHolderForLineHeight!
            if (valueHolderForLineHeightTmpValue instanceof number) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForLineHeightTmpValueForIdx0  = valueHolderForLineHeightTmpValue as number
                valueSerializer.writeNumber(valueHolderForLineHeightTmpValueForIdx0)
            } else if (valueHolderForLineHeightTmpValue instanceof string) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForLineHeightTmpValueForIdx1  = valueHolderForLineHeightTmpValue as string
                valueSerializer.writeString(valueHolderForLineHeightTmpValueForIdx1)
            } else if (valueHolderForLineHeightTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toChar())
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
            if (valueHolderForBaselineOffsetTmpValue instanceof number) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForBaselineOffsetTmpValueForIdx0  = valueHolderForBaselineOffsetTmpValue as number
                valueSerializer.writeNumber(valueHolderForBaselineOffsetTmpValueForIdx0)
            } else if (valueHolderForBaselineOffsetTmpValue instanceof string) {
                valueSerializer.writeInt8((1).toChar())
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
            if (valueHolderForTextCaseTmpValue instanceof number) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForTextCaseTmpValueForIdx0  = valueHolderForTextCaseTmpValue as number
                valueSerializer.writeNumber(valueHolderForTextCaseTmpValueForIdx0)
            } else if (valueHolderForTextCaseTmpValue instanceof TextCase) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForTextCaseTmpValueForIdx1  = valueHolderForTextCaseTmpValue as TextCase
                valueSerializer.writeInt32(TypeChecker.TextCase_ToNumeric(valueHolderForTextCaseTmpValueForIdx1))
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForTextIndent  = value.textIndent
        if (valueHolderForTextIndent !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTextIndentTmpValue  = valueHolderForTextIndent!
            if (valueHolderForTextIndentTmpValue instanceof number) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForTextIndentTmpValueForIdx0  = valueHolderForTextIndentTmpValue as number
                valueSerializer.writeNumber(valueHolderForTextIndentTmpValueForIdx0)
            } else if (valueHolderForTextIndentTmpValue instanceof string) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForTextIndentTmpValueForIdx1  = valueHolderForTextIndentTmpValue as string
                valueSerializer.writeString(valueHolderForTextIndentTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForWordBreak  = value.wordBreak
        if (valueHolderForWordBreak !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForWordBreakTmpValue  = (valueHolderForWordBreak as text.WordBreak)
            valueSerializer.writeInt32(TypeChecker.text_WordBreak_ToNumeric(valueHolderForWordBreakTmpValue))
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
        let constraintWidthTmpBuf : number | string | Resource | undefined
        if ((constraintWidthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const constraintWidthTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let constraintWidthTmpBuf_ : number | string | Resource | undefined
            if (constraintWidthTmpBuf_UnionSelector == (0).toChar()) {
                constraintWidthTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (constraintWidthTmpBuf_UnionSelector == (1).toChar()) {
                constraintWidthTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (constraintWidthTmpBuf_UnionSelector == (2).toChar()) {
                constraintWidthTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for constraintWidthTmpBuf_ has to be chosen through deserialisation.")
            }
            constraintWidthTmpBuf = (constraintWidthTmpBuf_ as number | string | Resource)
        }
        const constraintWidthTmpResult : number | string | Resource | undefined = constraintWidthTmpBuf
        const fontSizeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fontSizeTmpBuf : number | string | Resource | undefined
        if ((fontSizeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const fontSizeTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let fontSizeTmpBuf_ : number | string | Resource | undefined
            if (fontSizeTmpBuf_UnionSelector == (0).toChar()) {
                fontSizeTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (fontSizeTmpBuf_UnionSelector == (1).toChar()) {
                fontSizeTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (fontSizeTmpBuf_UnionSelector == (2).toChar()) {
                fontSizeTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for fontSizeTmpBuf_ has to be chosen through deserialisation.")
            }
            fontSizeTmpBuf = (fontSizeTmpBuf_ as number | string | Resource)
        }
        const fontSizeTmpResult : number | string | Resource | undefined = fontSizeTmpBuf
        const fontStyleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fontStyleTmpBuf : number | FontStyle | undefined
        if ((fontStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const fontStyleTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let fontStyleTmpBuf_ : number | FontStyle | undefined
            if (fontStyleTmpBuf_UnionSelector == (0).toChar()) {
                fontStyleTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (fontStyleTmpBuf_UnionSelector == (1).toChar()) {
                fontStyleTmpBuf_ = TypeChecker.FontStyle_FromNumeric(valueDeserializer.readInt32())
            } else {
                throw new Error("One of the branches for fontStyleTmpBuf_ has to be chosen through deserialisation.")
            }
            fontStyleTmpBuf = (fontStyleTmpBuf_ as number | FontStyle)
        }
        const fontStyleTmpResult : number | FontStyle | undefined = fontStyleTmpBuf
        const fontWeightTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fontWeightTmpBuf : number | string | FontWeight | undefined
        if ((fontWeightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const fontWeightTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let fontWeightTmpBuf_ : number | string | FontWeight | undefined
            if (fontWeightTmpBuf_UnionSelector == (0).toChar()) {
                fontWeightTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (fontWeightTmpBuf_UnionSelector == (1).toChar()) {
                fontWeightTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (fontWeightTmpBuf_UnionSelector == (2).toChar()) {
                fontWeightTmpBuf_ = TypeChecker.FontWeight_FromNumeric(valueDeserializer.readInt32())
            } else {
                throw new Error("One of the branches for fontWeightTmpBuf_ has to be chosen through deserialisation.")
            }
            fontWeightTmpBuf = (fontWeightTmpBuf_ as number | string | FontWeight)
        }
        const fontWeightTmpResult : number | string | FontWeight | undefined = fontWeightTmpBuf
        const fontFamilyTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fontFamilyTmpBuf : string | Resource | undefined
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
        let letterSpacingTmpBuf : number | string | undefined
        if ((letterSpacingTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const letterSpacingTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let letterSpacingTmpBuf_ : number | string | undefined
            if (letterSpacingTmpBuf_UnionSelector == (0).toChar()) {
                letterSpacingTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (letterSpacingTmpBuf_UnionSelector == (1).toChar()) {
                letterSpacingTmpBuf_ = (valueDeserializer.readString() as string)
            } else {
                throw new Error("One of the branches for letterSpacingTmpBuf_ has to be chosen through deserialisation.")
            }
            letterSpacingTmpBuf = (letterSpacingTmpBuf_ as number | string)
        }
        const letterSpacingTmpResult : number | string | undefined = letterSpacingTmpBuf
        const textAlignTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let textAlignTmpBuf : text.TextAlign | undefined
        if ((textAlignTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            textAlignTmpBuf = TypeChecker.text_TextAlign_FromNumeric(valueDeserializer.readInt32())
        }
        const textAlignTmpResult : text.TextAlign | undefined = textAlignTmpBuf
        const overflowTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let overflowTmpBuf : number | TextOverflow | undefined
        if ((overflowTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const overflowTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let overflowTmpBuf_ : number | TextOverflow | undefined
            if (overflowTmpBuf_UnionSelector == (0).toChar()) {
                overflowTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (overflowTmpBuf_UnionSelector == (1).toChar()) {
                overflowTmpBuf_ = TypeChecker.TextOverflow_FromNumeric(valueDeserializer.readInt32())
            } else {
                throw new Error("One of the branches for overflowTmpBuf_ has to be chosen through deserialisation.")
            }
            overflowTmpBuf = (overflowTmpBuf_ as number | TextOverflow)
        }
        const overflowTmpResult : number | TextOverflow | undefined = overflowTmpBuf
        const maxLinesTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let maxLinesTmpBuf : number | undefined
        if ((maxLinesTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            maxLinesTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const maxLinesTmpResult : number | undefined = maxLinesTmpBuf
        const lineHeightTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let lineHeightTmpBuf : number | string | Resource | undefined
        if ((lineHeightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const lineHeightTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let lineHeightTmpBuf_ : number | string | Resource | undefined
            if (lineHeightTmpBuf_UnionSelector == (0).toChar()) {
                lineHeightTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (lineHeightTmpBuf_UnionSelector == (1).toChar()) {
                lineHeightTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (lineHeightTmpBuf_UnionSelector == (2).toChar()) {
                lineHeightTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for lineHeightTmpBuf_ has to be chosen through deserialisation.")
            }
            lineHeightTmpBuf = (lineHeightTmpBuf_ as number | string | Resource)
        }
        const lineHeightTmpResult : number | string | Resource | undefined = lineHeightTmpBuf
        const baselineOffsetTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let baselineOffsetTmpBuf : number | string | undefined
        if ((baselineOffsetTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const baselineOffsetTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let baselineOffsetTmpBuf_ : number | string | undefined
            if (baselineOffsetTmpBuf_UnionSelector == (0).toChar()) {
                baselineOffsetTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (baselineOffsetTmpBuf_UnionSelector == (1).toChar()) {
                baselineOffsetTmpBuf_ = (valueDeserializer.readString() as string)
            } else {
                throw new Error("One of the branches for baselineOffsetTmpBuf_ has to be chosen through deserialisation.")
            }
            baselineOffsetTmpBuf = (baselineOffsetTmpBuf_ as number | string)
        }
        const baselineOffsetTmpResult : number | string | undefined = baselineOffsetTmpBuf
        const textCaseTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let textCaseTmpBuf : number | TextCase | undefined
        if ((textCaseTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const textCaseTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let textCaseTmpBuf_ : number | TextCase | undefined
            if (textCaseTmpBuf_UnionSelector == (0).toChar()) {
                textCaseTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (textCaseTmpBuf_UnionSelector == (1).toChar()) {
                textCaseTmpBuf_ = TypeChecker.TextCase_FromNumeric(valueDeserializer.readInt32())
            } else {
                throw new Error("One of the branches for textCaseTmpBuf_ has to be chosen through deserialisation.")
            }
            textCaseTmpBuf = (textCaseTmpBuf_ as number | TextCase)
        }
        const textCaseTmpResult : number | TextCase | undefined = textCaseTmpBuf
        const textIndentTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let textIndentTmpBuf : number | string | undefined
        if ((textIndentTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const textIndentTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let textIndentTmpBuf_ : number | string | undefined
            if (textIndentTmpBuf_UnionSelector == (0).toChar()) {
                textIndentTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (textIndentTmpBuf_UnionSelector == (1).toChar()) {
                textIndentTmpBuf_ = (valueDeserializer.readString() as string)
            } else {
                throw new Error("One of the branches for textIndentTmpBuf_ has to be chosen through deserialisation.")
            }
            textIndentTmpBuf = (textIndentTmpBuf_ as number | string)
        }
        const textIndentTmpResult : number | string | undefined = textIndentTmpBuf
        const wordBreakTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let wordBreakTmpBuf : text.WordBreak | undefined
        if ((wordBreakTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            wordBreakTmpBuf = TypeChecker.text_WordBreak_FromNumeric(valueDeserializer.readInt32())
        }
        const wordBreakTmpResult : text.WordBreak | undefined = wordBreakTmpBuf
        let value : MeasureOptions = ({textContent: textContentTmpResult, constraintWidth: constraintWidthTmpResult, fontSize: fontSizeTmpResult, fontStyle: fontStyleTmpResult, fontWeight: fontWeightTmpResult, fontFamily: fontFamilyTmpResult, letterSpacing: letterSpacingTmpResult, textAlign: textAlignTmpResult, overflow: overflowTmpResult, maxLines: maxLinesTmpResult, lineHeight: lineHeightTmpResult, baselineOffset: baselineOffsetTmpResult, textCase: textCaseTmpResult, textIndent: textIndentTmpResult, wordBreak: wordBreakTmpResult} as MeasureOptions)
        return value
    }
}
