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

import { SerializerBase, DeserializerBase, CallbackResource, InteropNativeModule, MaterializedBase, Tags, RuntimeType, runtimeType, toPeerPtr, nullptr, KPointer, NativeBuffer, KSerializerBuffer, KUint8ArrayPtr, Finalizable, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { CallbackTransformer } from "./../CallbackTransformer"
import { common2D_Color_serializer, common2D, common2D_Rect_serializer, common2D_Point_serializer } from "./ohos.graphics.common2D"
import { drawing_FontMetrics_serializer, drawing } from "./ohos.graphics.drawing"
import { Resource_serializer, Resource } from "./resource"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { GlobalScope } from "./GlobalScope"
export class text_FontCollection_serializer {
    public static write(buffer: SerializerBase, value: text.FontCollection): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): text.FontCollection {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return text.FontCollectionInternal.fromPtr(ptr)
    }
}
export class text_FontFeature_serializer {
    public static write(buffer: SerializerBase, value: text.FontFeature): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForName  = value.name
        valueSerializer.writeString(valueHolderForName)
        const valueHolderForValue  = value.value
        valueSerializer.writeNumber(valueHolderForValue)
    }
    public static read(buffer: DeserializerBase): text.FontFeature {
        let valueDeserializer : DeserializerBase = buffer
        const nameTmpResult : string = (valueDeserializer.readString() as string)
        const valueTmpResult : number = (valueDeserializer.readNumber() as number)
        let value : text.FontFeature = ({name: nameTmpResult, value: valueTmpResult} as text.FontFeature)
        return value
    }
}
export class text_FontVariation_serializer {
    public static write(buffer: SerializerBase, value: text.FontVariation): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForAxis  = value.axis
        valueSerializer.writeString(valueHolderForAxis)
        const valueHolderForValue  = value.value
        valueSerializer.writeNumber(valueHolderForValue)
    }
    public static read(buffer: DeserializerBase): text.FontVariation {
        let valueDeserializer : DeserializerBase = buffer
        const axisTmpResult : string = (valueDeserializer.readString() as string)
        const valueTmpResult : number = (valueDeserializer.readNumber() as number)
        let value : text.FontVariation = ({axis: axisTmpResult, value: valueTmpResult} as text.FontVariation)
        return value
    }
}
export class text_LineTypeset_serializer {
    public static write(buffer: SerializerBase, value: text.LineTypeset): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): text.LineTypeset {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return text.LineTypesetInternal.fromPtr(ptr)
    }
}
export class text_Paragraph_serializer {
    public static write(buffer: SerializerBase, value: text.Paragraph): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): text.Paragraph {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return text.ParagraphInternal.fromPtr(ptr)
    }
}
export class text_ParagraphBuilder_serializer {
    public static write(buffer: SerializerBase, value: text.ParagraphBuilder): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): text.ParagraphBuilder {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return text.ParagraphBuilderInternal.fromPtr(ptr)
    }
}
export class text_PositionWithAffinity_serializer {
    public static write(buffer: SerializerBase, value: text.PositionWithAffinity): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForPosition  = value.position
        valueSerializer.writeNumber(valueHolderForPosition)
        const valueHolderForAffinity  = value.affinity
        valueSerializer.writeInt32(TypeChecker.text_Affinity_ToNumeric(valueHolderForAffinity))
    }
    public static read(buffer: DeserializerBase): text.PositionWithAffinity {
        let valueDeserializer : DeserializerBase = buffer
        const positionTmpResult : number = (valueDeserializer.readNumber() as number)
        const affinityTmpResult : text.Affinity = TypeChecker.text_Affinity_FromNumeric(valueDeserializer.readInt32())
        let value : text.PositionWithAffinity = ({position: positionTmpResult, affinity: affinityTmpResult} as text.PositionWithAffinity)
        return value
    }
}
export class text_Range_serializer {
    public static write(buffer: SerializerBase, value: text.Range): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForStart  = value.start
        valueSerializer.writeNumber(valueHolderForStart)
        const valueHolderForEnd  = value.end
        valueSerializer.writeNumber(valueHolderForEnd)
    }
    public static read(buffer: DeserializerBase): text.Range {
        let valueDeserializer : DeserializerBase = buffer
        const startTmpResult : number = (valueDeserializer.readNumber() as number)
        const endTmpResult : number = (valueDeserializer.readNumber() as number)
        let value : text.Range = ({start: startTmpResult, end: endTmpResult} as text.Range)
        return value
    }
}
export class text_Run_serializer {
    public static write(buffer: SerializerBase, value: text.Run): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): text.Run {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return text.RunInternal.fromPtr(ptr)
    }
}
export class text_TextLine_serializer {
    public static write(buffer: SerializerBase, value: text.TextLine): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): text.TextLine {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return text.TextLineInternal.fromPtr(ptr)
    }
}
export class text_TextTab_serializer {
    public static write(buffer: SerializerBase, value: text.TextTab): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForAlignment  = value.alignment
        valueSerializer.writeInt32(TypeChecker.text_TextAlign_ToNumeric(valueHolderForAlignment))
        const valueHolderForLocation  = value.location
        valueSerializer.writeNumber(valueHolderForLocation)
    }
    public static read(buffer: DeserializerBase): text.TextTab {
        let valueDeserializer : DeserializerBase = buffer
        const alignmentTmpResult : text.TextAlign = TypeChecker.text_TextAlign_FromNumeric(valueDeserializer.readInt32())
        const locationTmpResult : number = (valueDeserializer.readNumber() as number)
        let value : text.TextTab = ({alignment: alignmentTmpResult, location: locationTmpResult} as text.TextTab)
        return value
    }
}
export class text_TypographicBounds_serializer {
    public static write(buffer: SerializerBase, value: text.TypographicBounds): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForAscent  = value.ascent
        valueSerializer.writeNumber(valueHolderForAscent)
        const valueHolderForDescent  = value.descent
        valueSerializer.writeNumber(valueHolderForDescent)
        const valueHolderForLeading  = value.leading
        valueSerializer.writeNumber(valueHolderForLeading)
        const valueHolderForWidth  = value.width
        valueSerializer.writeNumber(valueHolderForWidth)
    }
    public static read(buffer: DeserializerBase): text.TypographicBounds {
        let valueDeserializer : DeserializerBase = buffer
        const ascentTmpResult : number = (valueDeserializer.readNumber() as number)
        const descentTmpResult : number = (valueDeserializer.readNumber() as number)
        const leadingTmpResult : number = (valueDeserializer.readNumber() as number)
        const widthTmpResult : number = (valueDeserializer.readNumber() as number)
        let value : text.TypographicBounds = ({ascent: ascentTmpResult, descent: descentTmpResult, leading: leadingTmpResult, width: widthTmpResult} as text.TypographicBounds)
        return value
    }
}
export class text_FontDescriptor_serializer {
    public static write(buffer: SerializerBase, value: text.FontDescriptor): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForPath  = value.path
        if (valueHolderForPath !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForPathTmpValue  = valueHolderForPath!
            valueSerializer.writeString(valueHolderForPathTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForPostScriptName  = value.postScriptName
        if (valueHolderForPostScriptName !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForPostScriptNameTmpValue  = valueHolderForPostScriptName!
            valueSerializer.writeString(valueHolderForPostScriptNameTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForFullName  = value.fullName
        if (valueHolderForFullName !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFullNameTmpValue  = valueHolderForFullName!
            valueSerializer.writeString(valueHolderForFullNameTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForFontFamily  = value.fontFamily
        if (valueHolderForFontFamily !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFontFamilyTmpValue  = valueHolderForFontFamily!
            valueSerializer.writeString(valueHolderForFontFamilyTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForFontSubfamily  = value.fontSubfamily
        if (valueHolderForFontSubfamily !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFontSubfamilyTmpValue  = valueHolderForFontSubfamily!
            valueSerializer.writeString(valueHolderForFontSubfamilyTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForWeight  = value.weight
        if (valueHolderForWeight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForWeightTmpValue  = (valueHolderForWeight as text.FontWeight)
            valueSerializer.writeInt32(TypeChecker.text_FontWeight_ToNumeric(valueHolderForWeightTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForWidth  = value.width
        if (valueHolderForWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForWidthTmpValue  = valueHolderForWidth!
            valueSerializer.writeNumber(valueHolderForWidthTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForItalic  = value.italic
        if (valueHolderForItalic !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForItalicTmpValue  = valueHolderForItalic!
            valueSerializer.writeNumber(valueHolderForItalicTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMonoSpace  = value.monoSpace
        if (valueHolderForMonoSpace !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMonoSpaceTmpValue  = valueHolderForMonoSpace!
            valueSerializer.writeBoolean(valueHolderForMonoSpaceTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSymbolic  = value.symbolic
        if (valueHolderForSymbolic !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSymbolicTmpValue  = valueHolderForSymbolic!
            valueSerializer.writeBoolean(valueHolderForSymbolicTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): text.FontDescriptor {
        let valueDeserializer : DeserializerBase = buffer
        const pathTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let pathTmpBuf : string | undefined
        if ((pathTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            pathTmpBuf = (valueDeserializer.readString() as string)
        }
        const pathTmpResult : string | undefined = pathTmpBuf
        const postScriptNameTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let postScriptNameTmpBuf : string | undefined
        if ((postScriptNameTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            postScriptNameTmpBuf = (valueDeserializer.readString() as string)
        }
        const postScriptNameTmpResult : string | undefined = postScriptNameTmpBuf
        const fullNameTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fullNameTmpBuf : string | undefined
        if ((fullNameTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            fullNameTmpBuf = (valueDeserializer.readString() as string)
        }
        const fullNameTmpResult : string | undefined = fullNameTmpBuf
        const fontFamilyTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fontFamilyTmpBuf : string | undefined
        if ((fontFamilyTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            fontFamilyTmpBuf = (valueDeserializer.readString() as string)
        }
        const fontFamilyTmpResult : string | undefined = fontFamilyTmpBuf
        const fontSubfamilyTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fontSubfamilyTmpBuf : string | undefined
        if ((fontSubfamilyTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            fontSubfamilyTmpBuf = (valueDeserializer.readString() as string)
        }
        const fontSubfamilyTmpResult : string | undefined = fontSubfamilyTmpBuf
        const weightTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let weightTmpBuf : text.FontWeight | undefined
        if ((weightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            weightTmpBuf = TypeChecker.text_FontWeight_FromNumeric(valueDeserializer.readInt32())
        }
        const weightTmpResult : text.FontWeight | undefined = weightTmpBuf
        const widthTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let widthTmpBuf : number | undefined
        if ((widthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            widthTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const widthTmpResult : number | undefined = widthTmpBuf
        const italicTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let italicTmpBuf : number | undefined
        if ((italicTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            italicTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const italicTmpResult : number | undefined = italicTmpBuf
        const monoSpaceTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let monoSpaceTmpBuf : boolean | undefined
        if ((monoSpaceTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            monoSpaceTmpBuf = valueDeserializer.readBoolean()
        }
        const monoSpaceTmpResult : boolean | undefined = monoSpaceTmpBuf
        const symbolicTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let symbolicTmpBuf : boolean | undefined
        if ((symbolicTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            symbolicTmpBuf = valueDeserializer.readBoolean()
        }
        const symbolicTmpResult : boolean | undefined = symbolicTmpBuf
        let value : text.FontDescriptor = ({path: pathTmpResult, postScriptName: postScriptNameTmpResult, fullName: fullNameTmpResult, fontFamily: fontFamilyTmpResult, fontSubfamily: fontSubfamilyTmpResult, weight: weightTmpResult, width: widthTmpResult, italic: italicTmpResult, monoSpace: monoSpaceTmpResult, symbolic: symbolicTmpResult} as text.FontDescriptor)
        return value
    }
}
export class text_LineMetrics_serializer {
    public static write(buffer: SerializerBase, value: text.LineMetrics): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForStartIndex  = value.startIndex
        valueSerializer.writeNumber(valueHolderForStartIndex)
        const valueHolderForEndIndex  = value.endIndex
        valueSerializer.writeNumber(valueHolderForEndIndex)
        const valueHolderForAscent  = value.ascent
        valueSerializer.writeNumber(valueHolderForAscent)
        const valueHolderForDescent  = value.descent
        valueSerializer.writeNumber(valueHolderForDescent)
        const valueHolderForHeight  = value.height
        valueSerializer.writeNumber(valueHolderForHeight)
        const valueHolderForWidth  = value.width
        valueSerializer.writeNumber(valueHolderForWidth)
        const valueHolderForLeft  = value.left
        valueSerializer.writeNumber(valueHolderForLeft)
        const valueHolderForBaseline  = value.baseline
        valueSerializer.writeNumber(valueHolderForBaseline)
        const valueHolderForLineNumber  = value.lineNumber
        valueSerializer.writeNumber(valueHolderForLineNumber)
        const valueHolderForTopHeight  = value.topHeight
        valueSerializer.writeNumber(valueHolderForTopHeight)
        const valueHolderForRunMetrics  = value.runMetrics
        valueSerializer.writeInt32((valueHolderForRunMetrics.size).toInt())
        for (const pair of valueHolderForRunMetrics) {
            const valueHolderForRunMetricsKeyVar = pair[0]
            const valueHolderForRunMetricsValueVar = pair[1]
            valueSerializer.writeNumber(valueHolderForRunMetricsKeyVar)
            text_RunMetrics_serializer.write(valueSerializer, valueHolderForRunMetricsValueVar)
        }
    }
    public static read(buffer: DeserializerBase): text.LineMetrics {
        let valueDeserializer : DeserializerBase = buffer
        const startIndexTmpResult : number = (valueDeserializer.readNumber() as number)
        const endIndexTmpResult : number = (valueDeserializer.readNumber() as number)
        const ascentTmpResult : number = (valueDeserializer.readNumber() as number)
        const descentTmpResult : number = (valueDeserializer.readNumber() as number)
        const heightTmpResult : number = (valueDeserializer.readNumber() as number)
        const widthTmpResult : number = (valueDeserializer.readNumber() as number)
        const leftTmpResult : number = (valueDeserializer.readNumber() as number)
        const baselineTmpResult : number = (valueDeserializer.readNumber() as number)
        const lineNumberTmpResult : number = (valueDeserializer.readNumber() as number)
        const topHeightTmpResult : number = (valueDeserializer.readNumber() as number)
        const runMetricsTmpBufSizeVar : int32 = valueDeserializer.readInt32()
        let runMetricsTmpBuf : Map<number, text.RunMetrics> = new Map<number, text.RunMetrics>()
        // TODO: TS map resize
        for (let runMetricsTmpBufIVar = 0; runMetricsTmpBufIVar < runMetricsTmpBufSizeVar; runMetricsTmpBufIVar++) {
            const runMetricsTmpBufKeyVar : number = (valueDeserializer.readNumber() as number)
            const runMetricsTmpBufValueVar : text.RunMetrics = text_RunMetrics_serializer.read(valueDeserializer)
            runMetricsTmpBuf.set(runMetricsTmpBufKeyVar, runMetricsTmpBufValueVar)
        }
        const runMetricsTmpResult : Map<number, text.RunMetrics> = runMetricsTmpBuf
        let value : text.LineMetrics = ({startIndex: startIndexTmpResult, endIndex: endIndexTmpResult, ascent: ascentTmpResult, descent: descentTmpResult, height: heightTmpResult, width: widthTmpResult, left: leftTmpResult, baseline: baselineTmpResult, lineNumber: lineNumberTmpResult, topHeight: topHeightTmpResult, runMetrics: runMetricsTmpResult} as text.LineMetrics)
        return value
    }
}
export class text_PlaceholderSpan_serializer {
    public static write(buffer: SerializerBase, value: text.PlaceholderSpan): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForWidth  = value.width
        valueSerializer.writeNumber(valueHolderForWidth)
        const valueHolderForHeight  = value.height
        valueSerializer.writeNumber(valueHolderForHeight)
        const valueHolderForAlign  = value.align
        valueSerializer.writeInt32(TypeChecker.text_PlaceholderAlignment_ToNumeric(valueHolderForAlign))
        const valueHolderForBaseline  = value.baseline
        valueSerializer.writeInt32(TypeChecker.text_TextBaseline_ToNumeric(valueHolderForBaseline))
        const valueHolderForBaselineOffset  = value.baselineOffset
        valueSerializer.writeNumber(valueHolderForBaselineOffset)
    }
    public static read(buffer: DeserializerBase): text.PlaceholderSpan {
        let valueDeserializer : DeserializerBase = buffer
        const widthTmpResult : number = (valueDeserializer.readNumber() as number)
        const heightTmpResult : number = (valueDeserializer.readNumber() as number)
        const alignTmpResult : text.PlaceholderAlignment = TypeChecker.text_PlaceholderAlignment_FromNumeric(valueDeserializer.readInt32())
        const baselineTmpResult : text.TextBaseline = TypeChecker.text_TextBaseline_FromNumeric(valueDeserializer.readInt32())
        const baselineOffsetTmpResult : number = (valueDeserializer.readNumber() as number)
        let value : text.PlaceholderSpan = ({width: widthTmpResult, height: heightTmpResult, align: alignTmpResult, baseline: baselineTmpResult, baselineOffset: baselineOffsetTmpResult} as text.PlaceholderSpan)
        return value
    }
}
export class text_RectStyle_serializer {
    public static write(buffer: SerializerBase, value: text.RectStyle): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForColor  = value.color
        common2D_Color_serializer.write(valueSerializer, valueHolderForColor)
        const valueHolderForLeftTopRadius  = value.leftTopRadius
        valueSerializer.writeNumber(valueHolderForLeftTopRadius)
        const valueHolderForRightTopRadius  = value.rightTopRadius
        valueSerializer.writeNumber(valueHolderForRightTopRadius)
        const valueHolderForRightBottomRadius  = value.rightBottomRadius
        valueSerializer.writeNumber(valueHolderForRightBottomRadius)
        const valueHolderForLeftBottomRadius  = value.leftBottomRadius
        valueSerializer.writeNumber(valueHolderForLeftBottomRadius)
    }
    public static read(buffer: DeserializerBase): text.RectStyle {
        let valueDeserializer : DeserializerBase = buffer
        const colorTmpResult : common2D.Color = common2D_Color_serializer.read(valueDeserializer)
        const leftTopRadiusTmpResult : number = (valueDeserializer.readNumber() as number)
        const rightTopRadiusTmpResult : number = (valueDeserializer.readNumber() as number)
        const rightBottomRadiusTmpResult : number = (valueDeserializer.readNumber() as number)
        const leftBottomRadiusTmpResult : number = (valueDeserializer.readNumber() as number)
        let value : text.RectStyle = ({color: colorTmpResult, leftTopRadius: leftTopRadiusTmpResult, rightTopRadius: rightTopRadiusTmpResult, rightBottomRadius: rightBottomRadiusTmpResult, leftBottomRadius: leftBottomRadiusTmpResult} as text.RectStyle)
        return value
    }
}
export class text_StrutStyle_serializer {
    public static write(buffer: SerializerBase, value: text.StrutStyle): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForFontFamilies  = value.fontFamilies
        if (valueHolderForFontFamilies !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFontFamiliesTmpValue  = valueHolderForFontFamilies!
            valueSerializer.writeInt32((valueHolderForFontFamiliesTmpValue.length).toInt())
            for (let valueHolderForFontFamiliesTmpValueCounterI = 0; valueHolderForFontFamiliesTmpValueCounterI < valueHolderForFontFamiliesTmpValue.length; valueHolderForFontFamiliesTmpValueCounterI++) {
                const valueHolderForFontFamiliesTmpValueTmpElement : string = valueHolderForFontFamiliesTmpValue[valueHolderForFontFamiliesTmpValueCounterI]
                valueSerializer.writeString(valueHolderForFontFamiliesTmpValueTmpElement)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForFontStyle  = value.fontStyle
        if (valueHolderForFontStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFontStyleTmpValue  = (valueHolderForFontStyle as text.FontStyle)
            valueSerializer.writeInt32(TypeChecker.text_FontStyle_ToNumeric(valueHolderForFontStyleTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForFontWidth  = value.fontWidth
        if (valueHolderForFontWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFontWidthTmpValue  = (valueHolderForFontWidth as text.FontWidth)
            valueSerializer.writeInt32(TypeChecker.text_FontWidth_ToNumeric(valueHolderForFontWidthTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForFontWeight  = value.fontWeight
        if (valueHolderForFontWeight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFontWeightTmpValue  = (valueHolderForFontWeight as text.FontWeight)
            valueSerializer.writeInt32(TypeChecker.text_FontWeight_ToNumeric(valueHolderForFontWeightTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForFontSize  = value.fontSize
        if (valueHolderForFontSize !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFontSizeTmpValue  = valueHolderForFontSize!
            valueSerializer.writeNumber(valueHolderForFontSizeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForHeight  = value.height
        if (valueHolderForHeight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForHeightTmpValue  = valueHolderForHeight!
            valueSerializer.writeNumber(valueHolderForHeightTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLeading  = value.leading
        if (valueHolderForLeading !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLeadingTmpValue  = valueHolderForLeading!
            valueSerializer.writeNumber(valueHolderForLeadingTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForForceHeight  = value.forceHeight
        if (valueHolderForForceHeight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForForceHeightTmpValue  = valueHolderForForceHeight!
            valueSerializer.writeBoolean(valueHolderForForceHeightTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEnabled  = value.enabled
        if (valueHolderForEnabled !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEnabledTmpValue  = valueHolderForEnabled!
            valueSerializer.writeBoolean(valueHolderForEnabledTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForHeightOverride  = value.heightOverride
        if (valueHolderForHeightOverride !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForHeightOverrideTmpValue  = valueHolderForHeightOverride!
            valueSerializer.writeBoolean(valueHolderForHeightOverrideTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForHalfLeading  = value.halfLeading
        if (valueHolderForHalfLeading !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForHalfLeadingTmpValue  = valueHolderForHalfLeading!
            valueSerializer.writeBoolean(valueHolderForHalfLeadingTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): text.StrutStyle {
        let valueDeserializer : DeserializerBase = buffer
        const fontFamiliesTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fontFamiliesTmpBuf : Array<string> | undefined
        if ((fontFamiliesTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const fontFamiliesTmpBuf_Length : int32 = valueDeserializer.readInt32()
            let fontFamiliesTmpBuf_ : Array<string> = new Array<string>(fontFamiliesTmpBuf_Length)
            for (let fontFamiliesTmpBuf_BufCounterI = 0; fontFamiliesTmpBuf_BufCounterI < fontFamiliesTmpBuf_Length; fontFamiliesTmpBuf_BufCounterI++) {
                fontFamiliesTmpBuf_[fontFamiliesTmpBuf_BufCounterI] = (valueDeserializer.readString() as string)
            }
            fontFamiliesTmpBuf = fontFamiliesTmpBuf_
        }
        const fontFamiliesTmpResult : Array<string> | undefined = fontFamiliesTmpBuf
        const fontStyleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fontStyleTmpBuf : text.FontStyle | undefined
        if ((fontStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            fontStyleTmpBuf = TypeChecker.text_FontStyle_FromNumeric(valueDeserializer.readInt32())
        }
        const fontStyleTmpResult : text.FontStyle | undefined = fontStyleTmpBuf
        const fontWidthTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fontWidthTmpBuf : text.FontWidth | undefined
        if ((fontWidthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            fontWidthTmpBuf = TypeChecker.text_FontWidth_FromNumeric(valueDeserializer.readInt32())
        }
        const fontWidthTmpResult : text.FontWidth | undefined = fontWidthTmpBuf
        const fontWeightTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fontWeightTmpBuf : text.FontWeight | undefined
        if ((fontWeightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            fontWeightTmpBuf = TypeChecker.text_FontWeight_FromNumeric(valueDeserializer.readInt32())
        }
        const fontWeightTmpResult : text.FontWeight | undefined = fontWeightTmpBuf
        const fontSizeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fontSizeTmpBuf : number | undefined
        if ((fontSizeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            fontSizeTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const fontSizeTmpResult : number | undefined = fontSizeTmpBuf
        const heightTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let heightTmpBuf : number | undefined
        if ((heightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            heightTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const heightTmpResult : number | undefined = heightTmpBuf
        const leadingTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let leadingTmpBuf : number | undefined
        if ((leadingTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            leadingTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const leadingTmpResult : number | undefined = leadingTmpBuf
        const forceHeightTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let forceHeightTmpBuf : boolean | undefined
        if ((forceHeightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            forceHeightTmpBuf = valueDeserializer.readBoolean()
        }
        const forceHeightTmpResult : boolean | undefined = forceHeightTmpBuf
        const enabledTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let enabledTmpBuf : boolean | undefined
        if ((enabledTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            enabledTmpBuf = valueDeserializer.readBoolean()
        }
        const enabledTmpResult : boolean | undefined = enabledTmpBuf
        const heightOverrideTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let heightOverrideTmpBuf : boolean | undefined
        if ((heightOverrideTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            heightOverrideTmpBuf = valueDeserializer.readBoolean()
        }
        const heightOverrideTmpResult : boolean | undefined = heightOverrideTmpBuf
        const halfLeadingTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let halfLeadingTmpBuf : boolean | undefined
        if ((halfLeadingTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            halfLeadingTmpBuf = valueDeserializer.readBoolean()
        }
        const halfLeadingTmpResult : boolean | undefined = halfLeadingTmpBuf
        let value : text.StrutStyle = ({fontFamilies: fontFamiliesTmpResult, fontStyle: fontStyleTmpResult, fontWidth: fontWidthTmpResult, fontWeight: fontWeightTmpResult, fontSize: fontSizeTmpResult, height: heightTmpResult, leading: leadingTmpResult, forceHeight: forceHeightTmpResult, enabled: enabledTmpResult, heightOverride: heightOverrideTmpResult, halfLeading: halfLeadingTmpResult} as text.StrutStyle)
        return value
    }
}
export class text_TextBox_serializer {
    public static write(buffer: SerializerBase, value: text.TextBox): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForRect  = value.rect
        common2D_Rect_serializer.write(valueSerializer, valueHolderForRect)
        const valueHolderForDirection  = value.direction
        valueSerializer.writeInt32(TypeChecker.text_TextDirection_ToNumeric(valueHolderForDirection))
    }
    public static read(buffer: DeserializerBase): text.TextBox {
        let valueDeserializer : DeserializerBase = buffer
        const rectTmpResult : common2D.Rect = common2D_Rect_serializer.read(valueDeserializer)
        const directionTmpResult : text.TextDirection = TypeChecker.text_TextDirection_FromNumeric(valueDeserializer.readInt32())
        let value : text.TextBox = ({rect: rectTmpResult, direction: directionTmpResult} as text.TextBox)
        return value
    }
}
export class text_Decoration_serializer {
    public static write(buffer: SerializerBase, value: text.Decoration): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForTextDecoration  = value.textDecoration
        if (valueHolderForTextDecoration !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTextDecorationTmpValue  = (valueHolderForTextDecoration as text.TextDecorationType)
            valueSerializer.writeInt32(TypeChecker.text_TextDecorationType_ToNumeric(valueHolderForTextDecorationTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForColor  = value.color
        if (valueHolderForColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForColorTmpValue  = valueHolderForColor!
            common2D_Color_serializer.write(valueSerializer, valueHolderForColorTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForDecorationStyle  = value.decorationStyle
        if (valueHolderForDecorationStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForDecorationStyleTmpValue  = (valueHolderForDecorationStyle as text.TextDecorationStyle)
            valueSerializer.writeInt32(TypeChecker.text_TextDecorationStyle_ToNumeric(valueHolderForDecorationStyleTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForDecorationThicknessScale  = value.decorationThicknessScale
        if (valueHolderForDecorationThicknessScale !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForDecorationThicknessScaleTmpValue  = valueHolderForDecorationThicknessScale!
            valueSerializer.writeNumber(valueHolderForDecorationThicknessScaleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): text.Decoration {
        let valueDeserializer : DeserializerBase = buffer
        const textDecorationTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let textDecorationTmpBuf : text.TextDecorationType | undefined
        if ((textDecorationTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            textDecorationTmpBuf = TypeChecker.text_TextDecorationType_FromNumeric(valueDeserializer.readInt32())
        }
        const textDecorationTmpResult : text.TextDecorationType | undefined = textDecorationTmpBuf
        const colorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let colorTmpBuf : common2D.Color | undefined
        if ((colorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            colorTmpBuf = common2D_Color_serializer.read(valueDeserializer)
        }
        const colorTmpResult : common2D.Color | undefined = colorTmpBuf
        const decorationStyleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let decorationStyleTmpBuf : text.TextDecorationStyle | undefined
        if ((decorationStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            decorationStyleTmpBuf = TypeChecker.text_TextDecorationStyle_FromNumeric(valueDeserializer.readInt32())
        }
        const decorationStyleTmpResult : text.TextDecorationStyle | undefined = decorationStyleTmpBuf
        const decorationThicknessScaleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let decorationThicknessScaleTmpBuf : number | undefined
        if ((decorationThicknessScaleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            decorationThicknessScaleTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const decorationThicknessScaleTmpResult : number | undefined = decorationThicknessScaleTmpBuf
        let value : text.Decoration = ({textDecoration: textDecorationTmpResult, color: colorTmpResult, decorationStyle: decorationStyleTmpResult, decorationThicknessScale: decorationThicknessScaleTmpResult} as text.Decoration)
        return value
    }
}
export class text_TextShadow_serializer {
    public static write(buffer: SerializerBase, value: text.TextShadow): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForColor  = value.color
        if (valueHolderForColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForColorTmpValue  = valueHolderForColor!
            common2D_Color_serializer.write(valueSerializer, valueHolderForColorTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForPoint  = value.point
        if (valueHolderForPoint !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForPointTmpValue  = valueHolderForPoint!
            common2D_Point_serializer.write(valueSerializer, valueHolderForPointTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBlurRadius  = value.blurRadius
        if (valueHolderForBlurRadius !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBlurRadiusTmpValue  = valueHolderForBlurRadius!
            valueSerializer.writeNumber(valueHolderForBlurRadiusTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): text.TextShadow {
        let valueDeserializer : DeserializerBase = buffer
        const colorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let colorTmpBuf : common2D.Color | undefined
        if ((colorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            colorTmpBuf = common2D_Color_serializer.read(valueDeserializer)
        }
        const colorTmpResult : common2D.Color | undefined = colorTmpBuf
        const pointTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let pointTmpBuf : common2D.Point | undefined
        if ((pointTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            pointTmpBuf = common2D_Point_serializer.read(valueDeserializer)
        }
        const pointTmpResult : common2D.Point | undefined = pointTmpBuf
        const blurRadiusTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let blurRadiusTmpBuf : number | undefined
        if ((blurRadiusTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            blurRadiusTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const blurRadiusTmpResult : number | undefined = blurRadiusTmpBuf
        let value : text.TextShadow = ({color: colorTmpResult, point: pointTmpResult, blurRadius: blurRadiusTmpResult} as text.TextShadow)
        return value
    }
}
export class text_TextStyle_serializer {
    public static write(buffer: SerializerBase, value: text.TextStyle): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForDecoration  = value.decoration
        if (valueHolderForDecoration !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForDecorationTmpValue  = valueHolderForDecoration!
            text_Decoration_serializer.write(valueSerializer, valueHolderForDecorationTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForColor  = value.color
        if (valueHolderForColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForColorTmpValue  = valueHolderForColor!
            common2D_Color_serializer.write(valueSerializer, valueHolderForColorTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForFontWeight  = value.fontWeight
        if (valueHolderForFontWeight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFontWeightTmpValue  = (valueHolderForFontWeight as text.FontWeight)
            valueSerializer.writeInt32(TypeChecker.text_FontWeight_ToNumeric(valueHolderForFontWeightTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForFontStyle  = value.fontStyle
        if (valueHolderForFontStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFontStyleTmpValue  = (valueHolderForFontStyle as text.FontStyle)
            valueSerializer.writeInt32(TypeChecker.text_FontStyle_ToNumeric(valueHolderForFontStyleTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBaseline  = value.baseline
        if (valueHolderForBaseline !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBaselineTmpValue  = (valueHolderForBaseline as text.TextBaseline)
            valueSerializer.writeInt32(TypeChecker.text_TextBaseline_ToNumeric(valueHolderForBaselineTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForFontFamilies  = value.fontFamilies
        if (valueHolderForFontFamilies !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFontFamiliesTmpValue  = valueHolderForFontFamilies!
            valueSerializer.writeInt32((valueHolderForFontFamiliesTmpValue.length).toInt())
            for (let valueHolderForFontFamiliesTmpValueCounterI = 0; valueHolderForFontFamiliesTmpValueCounterI < valueHolderForFontFamiliesTmpValue.length; valueHolderForFontFamiliesTmpValueCounterI++) {
                const valueHolderForFontFamiliesTmpValueTmpElement : string = valueHolderForFontFamiliesTmpValue[valueHolderForFontFamiliesTmpValueCounterI]
                valueSerializer.writeString(valueHolderForFontFamiliesTmpValueTmpElement)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForFontSize  = value.fontSize
        if (valueHolderForFontSize !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFontSizeTmpValue  = valueHolderForFontSize!
            valueSerializer.writeNumber(valueHolderForFontSizeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLetterSpacing  = value.letterSpacing
        if (valueHolderForLetterSpacing !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLetterSpacingTmpValue  = valueHolderForLetterSpacing!
            valueSerializer.writeNumber(valueHolderForLetterSpacingTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForWordSpacing  = value.wordSpacing
        if (valueHolderForWordSpacing !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForWordSpacingTmpValue  = valueHolderForWordSpacing!
            valueSerializer.writeNumber(valueHolderForWordSpacingTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForHeightScale  = value.heightScale
        if (valueHolderForHeightScale !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForHeightScaleTmpValue  = valueHolderForHeightScale!
            valueSerializer.writeNumber(valueHolderForHeightScaleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForHalfLeading  = value.halfLeading
        if (valueHolderForHalfLeading !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForHalfLeadingTmpValue  = valueHolderForHalfLeading!
            valueSerializer.writeBoolean(valueHolderForHalfLeadingTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForHeightOnly  = value.heightOnly
        if (valueHolderForHeightOnly !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForHeightOnlyTmpValue  = valueHolderForHeightOnly!
            valueSerializer.writeBoolean(valueHolderForHeightOnlyTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEllipsis  = value.ellipsis
        if (valueHolderForEllipsis !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEllipsisTmpValue  = valueHolderForEllipsis!
            valueSerializer.writeString(valueHolderForEllipsisTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEllipsisMode  = value.ellipsisMode
        if (valueHolderForEllipsisMode !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEllipsisModeTmpValue  = (valueHolderForEllipsisMode as text.EllipsisMode)
            valueSerializer.writeInt32(TypeChecker.text_EllipsisMode_ToNumeric(valueHolderForEllipsisModeTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLocale  = value.locale
        if (valueHolderForLocale !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLocaleTmpValue  = valueHolderForLocale!
            valueSerializer.writeString(valueHolderForLocaleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBaselineShift  = value.baselineShift
        if (valueHolderForBaselineShift !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBaselineShiftTmpValue  = valueHolderForBaselineShift!
            valueSerializer.writeNumber(valueHolderForBaselineShiftTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForFontFeatures  = value.fontFeatures
        if (valueHolderForFontFeatures !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFontFeaturesTmpValue  = valueHolderForFontFeatures!
            valueSerializer.writeInt32((valueHolderForFontFeaturesTmpValue.length).toInt())
            for (let valueHolderForFontFeaturesTmpValueCounterI = 0; valueHolderForFontFeaturesTmpValueCounterI < valueHolderForFontFeaturesTmpValue.length; valueHolderForFontFeaturesTmpValueCounterI++) {
                const valueHolderForFontFeaturesTmpValueTmpElement : text.FontFeature = valueHolderForFontFeaturesTmpValue[valueHolderForFontFeaturesTmpValueCounterI]
                text_FontFeature_serializer.write(valueSerializer, valueHolderForFontFeaturesTmpValueTmpElement)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForTextShadows  = value.textShadows
        if (valueHolderForTextShadows !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTextShadowsTmpValue  = valueHolderForTextShadows!
            valueSerializer.writeInt32((valueHolderForTextShadowsTmpValue.length).toInt())
            for (let valueHolderForTextShadowsTmpValueCounterI = 0; valueHolderForTextShadowsTmpValueCounterI < valueHolderForTextShadowsTmpValue.length; valueHolderForTextShadowsTmpValueCounterI++) {
                const valueHolderForTextShadowsTmpValueTmpElement : text.TextShadow = valueHolderForTextShadowsTmpValue[valueHolderForTextShadowsTmpValueCounterI]
                text_TextShadow_serializer.write(valueSerializer, valueHolderForTextShadowsTmpValueTmpElement)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBackgroundRect  = value.backgroundRect
        if (valueHolderForBackgroundRect !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBackgroundRectTmpValue  = valueHolderForBackgroundRect!
            text_RectStyle_serializer.write(valueSerializer, valueHolderForBackgroundRectTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForFontVariations  = value.fontVariations
        if (valueHolderForFontVariations !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFontVariationsTmpValue  = valueHolderForFontVariations!
            valueSerializer.writeInt32((valueHolderForFontVariationsTmpValue.length).toInt())
            for (let valueHolderForFontVariationsTmpValueCounterI = 0; valueHolderForFontVariationsTmpValueCounterI < valueHolderForFontVariationsTmpValue.length; valueHolderForFontVariationsTmpValueCounterI++) {
                const valueHolderForFontVariationsTmpValueTmpElement : text.FontVariation = valueHolderForFontVariationsTmpValue[valueHolderForFontVariationsTmpValueCounterI]
                text_FontVariation_serializer.write(valueSerializer, valueHolderForFontVariationsTmpValueTmpElement)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): text.TextStyle {
        let valueDeserializer : DeserializerBase = buffer
        const decorationTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let decorationTmpBuf : text.Decoration | undefined
        if ((decorationTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            decorationTmpBuf = text_Decoration_serializer.read(valueDeserializer)
        }
        const decorationTmpResult : text.Decoration | undefined = decorationTmpBuf
        const colorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let colorTmpBuf : common2D.Color | undefined
        if ((colorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            colorTmpBuf = common2D_Color_serializer.read(valueDeserializer)
        }
        const colorTmpResult : common2D.Color | undefined = colorTmpBuf
        const fontWeightTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fontWeightTmpBuf : text.FontWeight | undefined
        if ((fontWeightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            fontWeightTmpBuf = TypeChecker.text_FontWeight_FromNumeric(valueDeserializer.readInt32())
        }
        const fontWeightTmpResult : text.FontWeight | undefined = fontWeightTmpBuf
        const fontStyleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fontStyleTmpBuf : text.FontStyle | undefined
        if ((fontStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            fontStyleTmpBuf = TypeChecker.text_FontStyle_FromNumeric(valueDeserializer.readInt32())
        }
        const fontStyleTmpResult : text.FontStyle | undefined = fontStyleTmpBuf
        const baselineTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let baselineTmpBuf : text.TextBaseline | undefined
        if ((baselineTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            baselineTmpBuf = TypeChecker.text_TextBaseline_FromNumeric(valueDeserializer.readInt32())
        }
        const baselineTmpResult : text.TextBaseline | undefined = baselineTmpBuf
        const fontFamiliesTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fontFamiliesTmpBuf : Array<string> | undefined
        if ((fontFamiliesTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const fontFamiliesTmpBuf_Length : int32 = valueDeserializer.readInt32()
            let fontFamiliesTmpBuf_ : Array<string> = new Array<string>(fontFamiliesTmpBuf_Length)
            for (let fontFamiliesTmpBuf_BufCounterI = 0; fontFamiliesTmpBuf_BufCounterI < fontFamiliesTmpBuf_Length; fontFamiliesTmpBuf_BufCounterI++) {
                fontFamiliesTmpBuf_[fontFamiliesTmpBuf_BufCounterI] = (valueDeserializer.readString() as string)
            }
            fontFamiliesTmpBuf = fontFamiliesTmpBuf_
        }
        const fontFamiliesTmpResult : Array<string> | undefined = fontFamiliesTmpBuf
        const fontSizeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fontSizeTmpBuf : number | undefined
        if ((fontSizeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            fontSizeTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const fontSizeTmpResult : number | undefined = fontSizeTmpBuf
        const letterSpacingTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let letterSpacingTmpBuf : number | undefined
        if ((letterSpacingTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            letterSpacingTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const letterSpacingTmpResult : number | undefined = letterSpacingTmpBuf
        const wordSpacingTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let wordSpacingTmpBuf : number | undefined
        if ((wordSpacingTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            wordSpacingTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const wordSpacingTmpResult : number | undefined = wordSpacingTmpBuf
        const heightScaleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let heightScaleTmpBuf : number | undefined
        if ((heightScaleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            heightScaleTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const heightScaleTmpResult : number | undefined = heightScaleTmpBuf
        const halfLeadingTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let halfLeadingTmpBuf : boolean | undefined
        if ((halfLeadingTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            halfLeadingTmpBuf = valueDeserializer.readBoolean()
        }
        const halfLeadingTmpResult : boolean | undefined = halfLeadingTmpBuf
        const heightOnlyTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let heightOnlyTmpBuf : boolean | undefined
        if ((heightOnlyTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            heightOnlyTmpBuf = valueDeserializer.readBoolean()
        }
        const heightOnlyTmpResult : boolean | undefined = heightOnlyTmpBuf
        const ellipsisTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let ellipsisTmpBuf : string | undefined
        if ((ellipsisTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            ellipsisTmpBuf = (valueDeserializer.readString() as string)
        }
        const ellipsisTmpResult : string | undefined = ellipsisTmpBuf
        const ellipsisModeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let ellipsisModeTmpBuf : text.EllipsisMode | undefined
        if ((ellipsisModeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            ellipsisModeTmpBuf = TypeChecker.text_EllipsisMode_FromNumeric(valueDeserializer.readInt32())
        }
        const ellipsisModeTmpResult : text.EllipsisMode | undefined = ellipsisModeTmpBuf
        const localeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let localeTmpBuf : string | undefined
        if ((localeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            localeTmpBuf = (valueDeserializer.readString() as string)
        }
        const localeTmpResult : string | undefined = localeTmpBuf
        const baselineShiftTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let baselineShiftTmpBuf : number | undefined
        if ((baselineShiftTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            baselineShiftTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const baselineShiftTmpResult : number | undefined = baselineShiftTmpBuf
        const fontFeaturesTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fontFeaturesTmpBuf : Array<text.FontFeature> | undefined
        if ((fontFeaturesTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const fontFeaturesTmpBuf_Length : int32 = valueDeserializer.readInt32()
            let fontFeaturesTmpBuf_ : Array<text.FontFeature> = new Array<text.FontFeature>(fontFeaturesTmpBuf_Length)
            for (let fontFeaturesTmpBuf_BufCounterI = 0; fontFeaturesTmpBuf_BufCounterI < fontFeaturesTmpBuf_Length; fontFeaturesTmpBuf_BufCounterI++) {
                fontFeaturesTmpBuf_[fontFeaturesTmpBuf_BufCounterI] = text_FontFeature_serializer.read(valueDeserializer)
            }
            fontFeaturesTmpBuf = fontFeaturesTmpBuf_
        }
        const fontFeaturesTmpResult : Array<text.FontFeature> | undefined = fontFeaturesTmpBuf
        const textShadowsTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let textShadowsTmpBuf : Array<text.TextShadow> | undefined
        if ((textShadowsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const textShadowsTmpBuf_Length : int32 = valueDeserializer.readInt32()
            let textShadowsTmpBuf_ : Array<text.TextShadow> = new Array<text.TextShadow>(textShadowsTmpBuf_Length)
            for (let textShadowsTmpBuf_BufCounterI = 0; textShadowsTmpBuf_BufCounterI < textShadowsTmpBuf_Length; textShadowsTmpBuf_BufCounterI++) {
                textShadowsTmpBuf_[textShadowsTmpBuf_BufCounterI] = text_TextShadow_serializer.read(valueDeserializer)
            }
            textShadowsTmpBuf = textShadowsTmpBuf_
        }
        const textShadowsTmpResult : Array<text.TextShadow> | undefined = textShadowsTmpBuf
        const backgroundRectTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundRectTmpBuf : text.RectStyle | undefined
        if ((backgroundRectTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            backgroundRectTmpBuf = text_RectStyle_serializer.read(valueDeserializer)
        }
        const backgroundRectTmpResult : text.RectStyle | undefined = backgroundRectTmpBuf
        const fontVariationsTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fontVariationsTmpBuf : Array<text.FontVariation> | undefined
        if ((fontVariationsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const fontVariationsTmpBuf_Length : int32 = valueDeserializer.readInt32()
            let fontVariationsTmpBuf_ : Array<text.FontVariation> = new Array<text.FontVariation>(fontVariationsTmpBuf_Length)
            for (let fontVariationsTmpBuf_BufCounterI = 0; fontVariationsTmpBuf_BufCounterI < fontVariationsTmpBuf_Length; fontVariationsTmpBuf_BufCounterI++) {
                fontVariationsTmpBuf_[fontVariationsTmpBuf_BufCounterI] = text_FontVariation_serializer.read(valueDeserializer)
            }
            fontVariationsTmpBuf = fontVariationsTmpBuf_
        }
        const fontVariationsTmpResult : Array<text.FontVariation> | undefined = fontVariationsTmpBuf
        let value : text.TextStyle = ({decoration: decorationTmpResult, color: colorTmpResult, fontWeight: fontWeightTmpResult, fontStyle: fontStyleTmpResult, baseline: baselineTmpResult, fontFamilies: fontFamiliesTmpResult, fontSize: fontSizeTmpResult, letterSpacing: letterSpacingTmpResult, wordSpacing: wordSpacingTmpResult, heightScale: heightScaleTmpResult, halfLeading: halfLeadingTmpResult, heightOnly: heightOnlyTmpResult, ellipsis: ellipsisTmpResult, ellipsisMode: ellipsisModeTmpResult, locale: localeTmpResult, baselineShift: baselineShiftTmpResult, fontFeatures: fontFeaturesTmpResult, textShadows: textShadowsTmpResult, backgroundRect: backgroundRectTmpResult, fontVariations: fontVariationsTmpResult} as text.TextStyle)
        return value
    }
}
export class text_ParagraphStyle_serializer {
    public static write(buffer: SerializerBase, value: text.ParagraphStyle): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForTextStyle  = value.textStyle
        if (valueHolderForTextStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTextStyleTmpValue  = valueHolderForTextStyle!
            text_TextStyle_serializer.write(valueSerializer, valueHolderForTextStyleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForTextDirection  = value.textDirection
        if (valueHolderForTextDirection !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTextDirectionTmpValue  = (valueHolderForTextDirection as text.TextDirection)
            valueSerializer.writeInt32(TypeChecker.text_TextDirection_ToNumeric(valueHolderForTextDirectionTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForAlign  = value.align
        if (valueHolderForAlign !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForAlignTmpValue  = (valueHolderForAlign as text.TextAlign)
            valueSerializer.writeInt32(TypeChecker.text_TextAlign_ToNumeric(valueHolderForAlignTmpValue))
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
        const valueHolderForMaxLines  = value.maxLines
        if (valueHolderForMaxLines !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMaxLinesTmpValue  = valueHolderForMaxLines!
            valueSerializer.writeNumber(valueHolderForMaxLinesTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBreakStrategy  = value.breakStrategy
        if (valueHolderForBreakStrategy !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBreakStrategyTmpValue  = (valueHolderForBreakStrategy as text.BreakStrategy)
            valueSerializer.writeInt32(TypeChecker.text_BreakStrategy_ToNumeric(valueHolderForBreakStrategyTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForStrutStyle  = value.strutStyle
        if (valueHolderForStrutStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStrutStyleTmpValue  = valueHolderForStrutStyle!
            text_StrutStyle_serializer.write(valueSerializer, valueHolderForStrutStyleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForTextHeightBehavior  = value.textHeightBehavior
        if (valueHolderForTextHeightBehavior !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTextHeightBehaviorTmpValue  = (valueHolderForTextHeightBehavior as text.TextHeightBehavior)
            valueSerializer.writeInt32(TypeChecker.text_TextHeightBehavior_ToNumeric(valueHolderForTextHeightBehaviorTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForTab  = value.tab
        if (valueHolderForTab !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTabTmpValue  = valueHolderForTab!
            text_TextTab_serializer.write(valueSerializer, valueHolderForTabTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): text.ParagraphStyle {
        let valueDeserializer : DeserializerBase = buffer
        const textStyleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let textStyleTmpBuf : text.TextStyle | undefined
        if ((textStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            textStyleTmpBuf = text_TextStyle_serializer.read(valueDeserializer)
        }
        const textStyleTmpResult : text.TextStyle | undefined = textStyleTmpBuf
        const textDirectionTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let textDirectionTmpBuf : text.TextDirection | undefined
        if ((textDirectionTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            textDirectionTmpBuf = TypeChecker.text_TextDirection_FromNumeric(valueDeserializer.readInt32())
        }
        const textDirectionTmpResult : text.TextDirection | undefined = textDirectionTmpBuf
        const alignTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let alignTmpBuf : text.TextAlign | undefined
        if ((alignTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            alignTmpBuf = TypeChecker.text_TextAlign_FromNumeric(valueDeserializer.readInt32())
        }
        const alignTmpResult : text.TextAlign | undefined = alignTmpBuf
        const wordBreakTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let wordBreakTmpBuf : text.WordBreak | undefined
        if ((wordBreakTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            wordBreakTmpBuf = TypeChecker.text_WordBreak_FromNumeric(valueDeserializer.readInt32())
        }
        const wordBreakTmpResult : text.WordBreak | undefined = wordBreakTmpBuf
        const maxLinesTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let maxLinesTmpBuf : number | undefined
        if ((maxLinesTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            maxLinesTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const maxLinesTmpResult : number | undefined = maxLinesTmpBuf
        const breakStrategyTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let breakStrategyTmpBuf : text.BreakStrategy | undefined
        if ((breakStrategyTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            breakStrategyTmpBuf = TypeChecker.text_BreakStrategy_FromNumeric(valueDeserializer.readInt32())
        }
        const breakStrategyTmpResult : text.BreakStrategy | undefined = breakStrategyTmpBuf
        const strutStyleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let strutStyleTmpBuf : text.StrutStyle | undefined
        if ((strutStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            strutStyleTmpBuf = text_StrutStyle_serializer.read(valueDeserializer)
        }
        const strutStyleTmpResult : text.StrutStyle | undefined = strutStyleTmpBuf
        const textHeightBehaviorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let textHeightBehaviorTmpBuf : text.TextHeightBehavior | undefined
        if ((textHeightBehaviorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            textHeightBehaviorTmpBuf = TypeChecker.text_TextHeightBehavior_FromNumeric(valueDeserializer.readInt32())
        }
        const textHeightBehaviorTmpResult : text.TextHeightBehavior | undefined = textHeightBehaviorTmpBuf
        const tabTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let tabTmpBuf : text.TextTab | undefined
        if ((tabTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            tabTmpBuf = text_TextTab_serializer.read(valueDeserializer)
        }
        const tabTmpResult : text.TextTab | undefined = tabTmpBuf
        let value : text.ParagraphStyle = ({textStyle: textStyleTmpResult, textDirection: textDirectionTmpResult, align: alignTmpResult, wordBreak: wordBreakTmpResult, maxLines: maxLinesTmpResult, breakStrategy: breakStrategyTmpResult, strutStyle: strutStyleTmpResult, textHeightBehavior: textHeightBehaviorTmpResult, tab: tabTmpResult} as text.ParagraphStyle)
        return value
    }
}
export class text_RunMetrics_serializer {
    public static write(buffer: SerializerBase, value: text.RunMetrics): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForTextStyle  = value.textStyle
        text_TextStyle_serializer.write(valueSerializer, valueHolderForTextStyle)
        const valueHolderForFontMetrics  = value.fontMetrics
        drawing_FontMetrics_serializer.write(valueSerializer, valueHolderForFontMetrics)
    }
    public static read(buffer: DeserializerBase): text.RunMetrics {
        let valueDeserializer : DeserializerBase = buffer
        const textStyleTmpResult : text.TextStyle = text_TextStyle_serializer.read(valueDeserializer)
        const fontMetricsTmpResult : drawing.FontMetrics = drawing_FontMetrics_serializer.read(valueDeserializer)
        let value : text.RunMetrics = ({textStyle: textStyleTmpResult, fontMetrics: fontMetricsTmpResult} as text.RunMetrics)
        return value
    }
}
export namespace text {
    export class FontCollectionInternal {
        public static fromPtr(ptr: KPointer): text.FontCollection {
            return new text.FontCollection(ptr)
        }
    }
    export class FontCollection implements MaterializedBase {
        peer?: Finalizable | undefined = undefined
        public getPeer(): Finalizable | undefined {
            return this.peer
        }
        constructor(peerPtr: KPointer) {
            this.peer = new Finalizable(peerPtr, FontCollection.getFinalizer())
        }
        constructor() {
            this(FontCollection.construct())
        }
        static construct(): KPointer {
            const retval  = ArkUIGeneratedNativeModule._text_FontCollection_construct()
            return retval
        }
        static getFinalizer(): KPointer {
            return ArkUIGeneratedNativeModule._text_FontCollection_getFinalizer()
        }
        private static getGlobalInstance_serialize(): FontCollection {
            const retval  = ArkUIGeneratedNativeModule._text_FontCollection_getGlobalInstance()
            const obj : FontCollection = text.FontCollectionInternal.fromPtr(retval)
            return obj
        }
        public static getGlobalInstance(): FontCollection {
            return FontCollection.getGlobalInstance_serialize()
        }
        public loadFontSync(name: string, path: string | Resource): void {
            const name_casted = name as (string)
            const path_casted = path as (string | Resource)
            this.loadFontSync_serialize(name_casted, path_casted)
            return
        }
        public loadFont(name: string, path: string | Resource): Promise<void> {
            const name_casted = name as (string)
            const path_casted = path as (string | Resource)
            return this.loadFont_serialize(name_casted, path_casted)
        }
        public clearCaches(): void {
            this.clearCaches_serialize()
            return
        }
        private loadFontSync_serialize(name: string, path: string | Resource): void {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            if (path instanceof string) {
                thisSerializer.writeInt8((0).toChar())
                const pathForIdx0  = path as string
                thisSerializer.writeString(pathForIdx0)
            } else if (path instanceof Resource) {
                thisSerializer.writeInt8((1).toChar())
                const pathForIdx1  = path as Resource
                Resource_serializer.write(thisSerializer, pathForIdx1)
            }
            ArkUIGeneratedNativeModule._text_FontCollection_loadFontSync(this.peer!.ptr, name, thisSerializer.asBuffer(), thisSerializer.length())
            thisSerializer.release()
        }
        private loadFont_serialize(name: string, path: string | Resource): Promise<void> {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            if (path instanceof string) {
                thisSerializer.writeInt8((0).toChar())
                const pathForIdx0  = path as string
                thisSerializer.writeString(pathForIdx0)
            } else if (path instanceof Resource) {
                thisSerializer.writeInt8((1).toChar())
                const pathForIdx1  = path as Resource
                Resource_serializer.write(thisSerializer, pathForIdx1)
            }
            const retval  = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
            ArkUIGeneratedNativeModule._text_FontCollection_loadFont(this.peer!.ptr, name, thisSerializer.asBuffer(), thisSerializer.length())
            thisSerializer.release()
            return retval
        }
        private clearCaches_serialize(): void {
            ArkUIGeneratedNativeModule._text_FontCollection_clearCaches(this.peer!.ptr)
        }
    }
    export class LineTypesetInternal {
        public static fromPtr(ptr: KPointer): text.LineTypeset {
            return new text.LineTypeset(ptr)
        }
    }
    export class LineTypeset implements MaterializedBase {
        peer?: Finalizable | undefined = undefined
        public getPeer(): Finalizable | undefined {
            return this.peer
        }
        constructor(peerPtr: KPointer) {
            this.peer = new Finalizable(peerPtr, LineTypeset.getFinalizer())
        }
        constructor() {
            this(LineTypeset.construct())
        }
        static construct(): KPointer {
            const retval  = ArkUIGeneratedNativeModule._text_LineTypeset_construct()
            return retval
        }
        static getFinalizer(): KPointer {
            return ArkUIGeneratedNativeModule._text_LineTypeset_getFinalizer()
        }
        public getLineBreak(startIndex: number, width: number): number {
            const startIndex_casted = startIndex as (number)
            const width_casted = width as (number)
            return this.getLineBreak_serialize(startIndex_casted, width_casted)
        }
        public createLine(startIndex: number, count: number): TextLine {
            const startIndex_casted = startIndex as (number)
            const count_casted = count as (number)
            return this.createLine_serialize(startIndex_casted, count_casted)
        }
        private getLineBreak_serialize(startIndex: number, width: number): number {
            const retval  = ArkUIGeneratedNativeModule._text_LineTypeset_getLineBreak(this.peer!.ptr, startIndex, width)
            return retval
        }
        private createLine_serialize(startIndex: number, count: number): TextLine {
            const retval  = ArkUIGeneratedNativeModule._text_LineTypeset_createLine(this.peer!.ptr, startIndex, count)
            const obj : TextLine = text.TextLineInternal.fromPtr(retval)
            return obj
        }
    }
    export class ParagraphInternal {
        public static fromPtr(ptr: KPointer): text.Paragraph {
            return new text.Paragraph(ptr)
        }
    }
    export class Paragraph implements MaterializedBase {
        peer?: Finalizable | undefined = undefined
        public getPeer(): Finalizable | undefined {
            return this.peer
        }
        constructor(peerPtr: KPointer) {
            this.peer = new Finalizable(peerPtr, Paragraph.getFinalizer())
        }
        constructor() {
            this(Paragraph.construct())
        }
        static construct(): KPointer {
            const retval  = ArkUIGeneratedNativeModule._text_Paragraph_construct()
            return retval
        }
        static getFinalizer(): KPointer {
            return ArkUIGeneratedNativeModule._text_Paragraph_getFinalizer()
        }
        public layoutSync(width: number): void {
            const width_casted = width as (number)
            this.layoutSync_serialize(width_casted)
            return
        }
        public layout(width: number): Promise<void> {
            const width_casted = width as (number)
            return this.layout_serialize(width_casted)
        }
        public paint(canvas: drawing.Canvas, x: number, y: number): void {
            const canvas_casted = canvas as (drawing.Canvas)
            const x_casted = x as (number)
            const y_casted = y as (number)
            this.paint_serialize(canvas_casted, x_casted, y_casted)
            return
        }
        public paintOnPath(canvas: drawing.Canvas, path: drawing.Path, hOffset: number, vOffset: number): void {
            const canvas_casted = canvas as (drawing.Canvas)
            const path_casted = path as (drawing.Path)
            const hOffset_casted = hOffset as (number)
            const vOffset_casted = vOffset as (number)
            this.paintOnPath_serialize(canvas_casted, path_casted, hOffset_casted, vOffset_casted)
            return
        }
        public getMaxWidth(): number {
            return this.getMaxWidth_serialize()
        }
        public getHeight(): number {
            return this.getHeight_serialize()
        }
        public getLongestLine(): number {
            return this.getLongestLine_serialize()
        }
        public getLongestLineWithIndent(): number {
            return this.getLongestLineWithIndent_serialize()
        }
        public getMinIntrinsicWidth(): number {
            return this.getMinIntrinsicWidth_serialize()
        }
        public getMaxIntrinsicWidth(): number {
            return this.getMaxIntrinsicWidth_serialize()
        }
        public getAlphabeticBaseline(): number {
            return this.getAlphabeticBaseline_serialize()
        }
        public getIdeographicBaseline(): number {
            return this.getIdeographicBaseline_serialize()
        }
        public getRectsForRange(range: Range, widthStyle: RectWidthStyle, heightStyle: RectHeightStyle): Array<TextBox> {
            const range_casted = range as (Range)
            const widthStyle_casted = widthStyle as (RectWidthStyle)
            const heightStyle_casted = heightStyle as (RectHeightStyle)
            return this.getRectsForRange_serialize(range_casted, widthStyle_casted, heightStyle_casted)
        }
        public getRectsForPlaceholders(): Array<TextBox> {
            return this.getRectsForPlaceholders_serialize()
        }
        public getGlyphPositionAtCoordinate(x: number, y: number): PositionWithAffinity {
            const x_casted = x as (number)
            const y_casted = y as (number)
            return this.getGlyphPositionAtCoordinate_serialize(x_casted, y_casted)
        }
        public getWordBoundary(offset: number): Range {
            const offset_casted = offset as (number)
            return this.getWordBoundary_serialize(offset_casted)
        }
        public getLineCount(): number {
            return this.getLineCount_serialize()
        }
        public getLineHeight(line: number): number {
            const line_casted = line as (number)
            return this.getLineHeight_serialize(line_casted)
        }
        public getLineWidth(line: number): number {
            const line_casted = line as (number)
            return this.getLineWidth_serialize(line_casted)
        }
        public didExceedMaxLines(): boolean {
            return this.didExceedMaxLines_serialize()
        }
        public getTextLines(): Array<TextLine> {
            return this.getTextLines_serialize()
        }
        public getActualTextRange(lineNumber: number, includeSpaces: boolean): Range {
            const lineNumber_casted = lineNumber as (number)
            const includeSpaces_casted = includeSpaces as (boolean)
            return this.getActualTextRange_serialize(lineNumber_casted, includeSpaces_casted)
        }
        public getLineMetrics(): Array<LineMetrics> {
            return this.getLineMetrics0_serialize()
        }
        public getLineMetrics(lineNumber: number): LineMetrics | undefined {
            const lineNumber_casted = lineNumber as (number)
            return this.getLineMetrics1_serialize(lineNumber_casted)
        }
        private layoutSync_serialize(width: number): void {
            ArkUIGeneratedNativeModule._text_Paragraph_layoutSync(this.peer!.ptr, width)
        }
        private layout_serialize(width: number): Promise<void> {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            const retval  = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
            ArkUIGeneratedNativeModule._text_Paragraph_layout(this.peer!.ptr, width, thisSerializer.asBuffer(), thisSerializer.length())
            thisSerializer.release()
            return retval
        }
        private paint_serialize(canvas: drawing.Canvas, x: number, y: number): void {
            ArkUIGeneratedNativeModule._text_Paragraph_paint(this.peer!.ptr, toPeerPtr(canvas), x, y)
        }
        private paintOnPath_serialize(canvas: drawing.Canvas, path: drawing.Path, hOffset: number, vOffset: number): void {
            ArkUIGeneratedNativeModule._text_Paragraph_paintOnPath(this.peer!.ptr, toPeerPtr(canvas), toPeerPtr(path), hOffset, vOffset)
        }
        private getMaxWidth_serialize(): number {
            const retval  = ArkUIGeneratedNativeModule._text_Paragraph_getMaxWidth(this.peer!.ptr)
            return retval
        }
        private getHeight_serialize(): number {
            const retval  = ArkUIGeneratedNativeModule._text_Paragraph_getHeight(this.peer!.ptr)
            return retval
        }
        private getLongestLine_serialize(): number {
            const retval  = ArkUIGeneratedNativeModule._text_Paragraph_getLongestLine(this.peer!.ptr)
            return retval
        }
        private getLongestLineWithIndent_serialize(): number {
            const retval  = ArkUIGeneratedNativeModule._text_Paragraph_getLongestLineWithIndent(this.peer!.ptr)
            return retval
        }
        private getMinIntrinsicWidth_serialize(): number {
            const retval  = ArkUIGeneratedNativeModule._text_Paragraph_getMinIntrinsicWidth(this.peer!.ptr)
            return retval
        }
        private getMaxIntrinsicWidth_serialize(): number {
            const retval  = ArkUIGeneratedNativeModule._text_Paragraph_getMaxIntrinsicWidth(this.peer!.ptr)
            return retval
        }
        private getAlphabeticBaseline_serialize(): number {
            const retval  = ArkUIGeneratedNativeModule._text_Paragraph_getAlphabeticBaseline(this.peer!.ptr)
            return retval
        }
        private getIdeographicBaseline_serialize(): number {
            const retval  = ArkUIGeneratedNativeModule._text_Paragraph_getIdeographicBaseline(this.peer!.ptr)
            return retval
        }
        private getRectsForRange_serialize(range: Range, widthStyle: RectWidthStyle, heightStyle: RectHeightStyle): Array<TextBox> {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            text_Range_serializer.write(thisSerializer, range)
            const retval  = ArkUIGeneratedNativeModule._text_Paragraph_getRectsForRange(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length(), TypeChecker.text_RectWidthStyle_ToNumeric(widthStyle), TypeChecker.text_RectHeightStyle_ToNumeric(heightStyle))
            thisSerializer.release()
            let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
            const bufferLength : int32 = retvalDeserializer.readInt32()
            let buffer : Array<TextBox> = new Array<TextBox>(bufferLength)
            for (let bufferBufCounterI = 0; bufferBufCounterI < bufferLength; bufferBufCounterI++) {
                buffer[bufferBufCounterI] = text_TextBox_serializer.read(retvalDeserializer)
            }
            const returnResult : Array<TextBox> = buffer
            return returnResult
        }
        private getRectsForPlaceholders_serialize(): Array<TextBox> {
            const retval  = ArkUIGeneratedNativeModule._text_Paragraph_getRectsForPlaceholders(this.peer!.ptr)
            let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
            const bufferLength : int32 = retvalDeserializer.readInt32()
            let buffer : Array<TextBox> = new Array<TextBox>(bufferLength)
            for (let bufferBufCounterI = 0; bufferBufCounterI < bufferLength; bufferBufCounterI++) {
                buffer[bufferBufCounterI] = text_TextBox_serializer.read(retvalDeserializer)
            }
            const returnResult : Array<TextBox> = buffer
            return returnResult
        }
        private getGlyphPositionAtCoordinate_serialize(x: number, y: number): PositionWithAffinity {
            const retval  = ArkUIGeneratedNativeModule._text_Paragraph_getGlyphPositionAtCoordinate(this.peer!.ptr, x, y)
            let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
            const returnResult : PositionWithAffinity = text_PositionWithAffinity_serializer.read(retvalDeserializer)
            return returnResult
        }
        private getWordBoundary_serialize(offset: number): Range {
            const retval  = ArkUIGeneratedNativeModule._text_Paragraph_getWordBoundary(this.peer!.ptr, offset)
            let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
            const returnResult : Range = text_Range_serializer.read(retvalDeserializer)
            return returnResult
        }
        private getLineCount_serialize(): number {
            const retval  = ArkUIGeneratedNativeModule._text_Paragraph_getLineCount(this.peer!.ptr)
            return retval
        }
        private getLineHeight_serialize(line: number): number {
            const retval  = ArkUIGeneratedNativeModule._text_Paragraph_getLineHeight(this.peer!.ptr, line)
            return retval
        }
        private getLineWidth_serialize(line: number): number {
            const retval  = ArkUIGeneratedNativeModule._text_Paragraph_getLineWidth(this.peer!.ptr, line)
            return retval
        }
        private didExceedMaxLines_serialize(): boolean {
            const retval  = ArkUIGeneratedNativeModule._text_Paragraph_didExceedMaxLines(this.peer!.ptr)
            return retval
        }
        private getTextLines_serialize(): Array<TextLine> {
            const retval  = ArkUIGeneratedNativeModule._text_Paragraph_getTextLines(this.peer!.ptr)
            let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
            const bufferLength : int32 = retvalDeserializer.readInt32()
            let buffer : Array<TextLine> = new Array<TextLine>(bufferLength)
            for (let bufferBufCounterI = 0; bufferBufCounterI < bufferLength; bufferBufCounterI++) {
                buffer[bufferBufCounterI] = (text_TextLine_serializer.read(retvalDeserializer) as text.TextLine)
            }
            const returnResult : Array<TextLine> = buffer
            return returnResult
        }
        private getActualTextRange_serialize(lineNumber: number, includeSpaces: boolean): Range {
            const retval  = ArkUIGeneratedNativeModule._text_Paragraph_getActualTextRange(this.peer!.ptr, lineNumber, includeSpaces ? 1 : 0)
            let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
            const returnResult : Range = text_Range_serializer.read(retvalDeserializer)
            return returnResult
        }
        private getLineMetrics0_serialize(): Array<LineMetrics> {
            const retval  = ArkUIGeneratedNativeModule._text_Paragraph_getLineMetrics0(this.peer!.ptr)
            let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
            const bufferLength : int32 = retvalDeserializer.readInt32()
            let buffer : Array<LineMetrics> = new Array<LineMetrics>(bufferLength)
            for (let bufferBufCounterI = 0; bufferBufCounterI < bufferLength; bufferBufCounterI++) {
                buffer[bufferBufCounterI] = text_LineMetrics_serializer.read(retvalDeserializer)
            }
            const returnResult : Array<LineMetrics> = buffer
            return returnResult
        }
        private getLineMetrics1_serialize(lineNumber: number): LineMetrics | undefined {
            const retval  = ArkUIGeneratedNativeModule._text_Paragraph_getLineMetrics1(this.peer!.ptr, lineNumber)
            let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
            const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
            let buffer : LineMetrics | undefined
            if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
                buffer = text_LineMetrics_serializer.read(retvalDeserializer)
            }
            const returnResult : LineMetrics | undefined = buffer
            return returnResult
        }
    }
    export class ParagraphBuilderInternal {
        public static fromPtr(ptr: KPointer): text.ParagraphBuilder {
            return new text.ParagraphBuilder(false, false, ptr)
        }
    }
    export class ParagraphBuilder implements MaterializedBase {
        peer?: Finalizable | undefined = undefined
        public getPeer(): Finalizable | undefined {
            return this.peer
        }
        constructor(_0: boolean, _1: boolean, peerPtr: KPointer) {
            this.peer = new Finalizable(peerPtr, ParagraphBuilder.getFinalizer())
        }
        constructor(paragraphStyle: ParagraphStyle, fontCollection: FontCollection) {
            this(false, false, ParagraphBuilder.construct(paragraphStyle, fontCollection))
        }
        static construct(paragraphStyle: ParagraphStyle, fontCollection: FontCollection): KPointer {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            text_ParagraphStyle_serializer.write(thisSerializer, paragraphStyle)
            const retval  = ArkUIGeneratedNativeModule._text_ParagraphBuilder_construct(thisSerializer.asBuffer(), thisSerializer.length(), toPeerPtr(fontCollection))
            thisSerializer.release()
            return retval
        }
        static getFinalizer(): KPointer {
            return ArkUIGeneratedNativeModule._text_ParagraphBuilder_getFinalizer()
        }
        public pushStyle(textStyle: TextStyle): void {
            const textStyle_casted = textStyle as (TextStyle)
            this.pushStyle_serialize(textStyle_casted)
            return
        }
        public popStyle(): void {
            this.popStyle_serialize()
            return
        }
        public addText(text: string): void {
            const text_casted = text as (string)
            this.addText_serialize(text_casted)
            return
        }
        public addPlaceholder(placeholderSpan: PlaceholderSpan): void {
            const placeholderSpan_casted = placeholderSpan as (PlaceholderSpan)
            this.addPlaceholder_serialize(placeholderSpan_casted)
            return
        }
        public build(): Paragraph {
            return this.build_serialize()
        }
        public buildLineTypeset(): LineTypeset {
            return this.buildLineTypeset_serialize()
        }
        public addSymbol(symbolId: number): void {
            const symbolId_casted = symbolId as (number)
            this.addSymbol_serialize(symbolId_casted)
            return
        }
        private pushStyle_serialize(textStyle: TextStyle): void {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            text_TextStyle_serializer.write(thisSerializer, textStyle)
            ArkUIGeneratedNativeModule._text_ParagraphBuilder_pushStyle(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
            thisSerializer.release()
        }
        private popStyle_serialize(): void {
            ArkUIGeneratedNativeModule._text_ParagraphBuilder_popStyle(this.peer!.ptr)
        }
        private addText_serialize(text: string): void {
            ArkUIGeneratedNativeModule._text_ParagraphBuilder_addText(this.peer!.ptr, text)
        }
        private addPlaceholder_serialize(placeholderSpan: PlaceholderSpan): void {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            text_PlaceholderSpan_serializer.write(thisSerializer, placeholderSpan)
            ArkUIGeneratedNativeModule._text_ParagraphBuilder_addPlaceholder(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
            thisSerializer.release()
        }
        private build_serialize(): Paragraph {
            const retval  = ArkUIGeneratedNativeModule._text_ParagraphBuilder_build(this.peer!.ptr)
            const obj : Paragraph = text.ParagraphInternal.fromPtr(retval)
            return obj
        }
        private buildLineTypeset_serialize(): LineTypeset {
            const retval  = ArkUIGeneratedNativeModule._text_ParagraphBuilder_buildLineTypeset(this.peer!.ptr)
            const obj : LineTypeset = text.LineTypesetInternal.fromPtr(retval)
            return obj
        }
        private addSymbol_serialize(symbolId: number): void {
            ArkUIGeneratedNativeModule._text_ParagraphBuilder_addSymbol(this.peer!.ptr, symbolId)
        }
    }
    export class RunInternal {
        public static fromPtr(ptr: KPointer): text.Run {
            return new text.Run(ptr)
        }
    }
    export class Run implements MaterializedBase {
        peer?: Finalizable | undefined = undefined
        public getPeer(): Finalizable | undefined {
            return this.peer
        }
        constructor(peerPtr: KPointer) {
            this.peer = new Finalizable(peerPtr, Run.getFinalizer())
        }
        constructor() {
            this(Run.construct())
        }
        static construct(): KPointer {
            const retval  = ArkUIGeneratedNativeModule._text_Run_construct()
            return retval
        }
        static getFinalizer(): KPointer {
            return ArkUIGeneratedNativeModule._text_Run_getFinalizer()
        }
        public getGlyphCount(): number {
            return this.getGlyphCount_serialize()
        }
        public getGlyphs(): Array<number> {
            return this.getGlyphs0_serialize()
        }
        public getGlyphs(range: Range): Array<number> {
            const range_casted = range as (Range)
            return this.getGlyphs1_serialize(range_casted)
        }
        public getPositions(): Array<common2D.Point> {
            return this.getPositions0_serialize()
        }
        public getPositions(range: Range): Array<common2D.Point> {
            const range_casted = range as (Range)
            return this.getPositions1_serialize(range_casted)
        }
        public getOffsets(): Array<common2D.Point> {
            return this.getOffsets_serialize()
        }
        public getFont(): drawing.Font {
            return this.getFont_serialize()
        }
        public paint(canvas: drawing.Canvas, x: number, y: number): void {
            const canvas_casted = canvas as (drawing.Canvas)
            const x_casted = x as (number)
            const y_casted = y as (number)
            this.paint_serialize(canvas_casted, x_casted, y_casted)
            return
        }
        public getStringIndices(range: Range): Array<number> {
            const range_casted = range as (Range)
            return this.getStringIndices_serialize(range_casted)
        }
        public getStringRange(): Range {
            return this.getStringRange_serialize()
        }
        public getTypographicBounds(): TypographicBounds {
            return this.getTypographicBounds_serialize()
        }
        public getImageBounds(): common2D.Rect {
            return this.getImageBounds_serialize()
        }
        private getGlyphCount_serialize(): number {
            const retval  = ArkUIGeneratedNativeModule._text_Run_getGlyphCount(this.peer!.ptr)
            return retval
        }
        private getGlyphs0_serialize(): Array<number> {
            const retval  = ArkUIGeneratedNativeModule._text_Run_getGlyphs0(this.peer!.ptr)
            let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
            const bufferLength : int32 = retvalDeserializer.readInt32()
            let buffer : Array<number> = new Array<number>(bufferLength)
            for (let bufferBufCounterI = 0; bufferBufCounterI < bufferLength; bufferBufCounterI++) {
                buffer[bufferBufCounterI] = (retvalDeserializer.readNumber() as number)
            }
            const returnResult : Array<number> = buffer
            return returnResult
        }
        private getGlyphs1_serialize(range: Range): Array<number> {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            text_Range_serializer.write(thisSerializer, range)
            const retval  = ArkUIGeneratedNativeModule._text_Run_getGlyphs1(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
            thisSerializer.release()
            let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
            const bufferLength : int32 = retvalDeserializer.readInt32()
            let buffer : Array<number> = new Array<number>(bufferLength)
            for (let bufferBufCounterI = 0; bufferBufCounterI < bufferLength; bufferBufCounterI++) {
                buffer[bufferBufCounterI] = (retvalDeserializer.readNumber() as number)
            }
            const returnResult : Array<number> = buffer
            return returnResult
        }
        private getPositions0_serialize(): Array<common2D.Point> {
            const retval  = ArkUIGeneratedNativeModule._text_Run_getPositions0(this.peer!.ptr)
            let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
            const bufferLength : int32 = retvalDeserializer.readInt32()
            let buffer : Array<common2D.Point> = new Array<common2D.Point>(bufferLength)
            for (let bufferBufCounterI = 0; bufferBufCounterI < bufferLength; bufferBufCounterI++) {
                buffer[bufferBufCounterI] = common2D_Point_serializer.read(retvalDeserializer)
            }
            const returnResult : Array<common2D.Point> = buffer
            return returnResult
        }
        private getPositions1_serialize(range: Range): Array<common2D.Point> {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            text_Range_serializer.write(thisSerializer, range)
            const retval  = ArkUIGeneratedNativeModule._text_Run_getPositions1(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
            thisSerializer.release()
            let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
            const bufferLength : int32 = retvalDeserializer.readInt32()
            let buffer : Array<common2D.Point> = new Array<common2D.Point>(bufferLength)
            for (let bufferBufCounterI = 0; bufferBufCounterI < bufferLength; bufferBufCounterI++) {
                buffer[bufferBufCounterI] = common2D_Point_serializer.read(retvalDeserializer)
            }
            const returnResult : Array<common2D.Point> = buffer
            return returnResult
        }
        private getOffsets_serialize(): Array<common2D.Point> {
            const retval  = ArkUIGeneratedNativeModule._text_Run_getOffsets(this.peer!.ptr)
            let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
            const bufferLength : int32 = retvalDeserializer.readInt32()
            let buffer : Array<common2D.Point> = new Array<common2D.Point>(bufferLength)
            for (let bufferBufCounterI = 0; bufferBufCounterI < bufferLength; bufferBufCounterI++) {
                buffer[bufferBufCounterI] = common2D_Point_serializer.read(retvalDeserializer)
            }
            const returnResult : Array<common2D.Point> = buffer
            return returnResult
        }
        private getFont_serialize(): drawing.Font {
            const retval  = ArkUIGeneratedNativeModule._text_Run_getFont(this.peer!.ptr)
            const obj : drawing.Font = drawing.FontInternal.fromPtr(retval)
            return obj
        }
        private paint_serialize(canvas: drawing.Canvas, x: number, y: number): void {
            ArkUIGeneratedNativeModule._text_Run_paint(this.peer!.ptr, toPeerPtr(canvas), x, y)
        }
        private getStringIndices_serialize(range: Range): Array<number> {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            text_Range_serializer.write(thisSerializer, range)
            const retval  = ArkUIGeneratedNativeModule._text_Run_getStringIndices(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
            thisSerializer.release()
            let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
            const bufferLength : int32 = retvalDeserializer.readInt32()
            let buffer : Array<number> = new Array<number>(bufferLength)
            for (let bufferBufCounterI = 0; bufferBufCounterI < bufferLength; bufferBufCounterI++) {
                buffer[bufferBufCounterI] = (retvalDeserializer.readNumber() as number)
            }
            const returnResult : Array<number> = buffer
            return returnResult
        }
        private getStringRange_serialize(): Range {
            const retval  = ArkUIGeneratedNativeModule._text_Run_getStringRange(this.peer!.ptr)
            let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
            const returnResult : Range = text_Range_serializer.read(retvalDeserializer)
            return returnResult
        }
        private getTypographicBounds_serialize(): TypographicBounds {
            const retval  = ArkUIGeneratedNativeModule._text_Run_getTypographicBounds(this.peer!.ptr)
            let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
            const returnResult : TypographicBounds = text_TypographicBounds_serializer.read(retvalDeserializer)
            return returnResult
        }
        private getImageBounds_serialize(): common2D.Rect {
            const retval  = ArkUIGeneratedNativeModule._text_Run_getImageBounds(this.peer!.ptr)
            let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
            const returnResult : common2D.Rect = common2D_Rect_serializer.read(retvalDeserializer)
            return returnResult
        }
    }
    export class TextLineInternal {
        public static fromPtr(ptr: KPointer): text.TextLine {
            return new text.TextLine(ptr)
        }
    }
    export class TextLine implements MaterializedBase {
        peer?: Finalizable | undefined = undefined
        public getPeer(): Finalizable | undefined {
            return this.peer
        }
        constructor(peerPtr: KPointer) {
            this.peer = new Finalizable(peerPtr, TextLine.getFinalizer())
        }
        constructor() {
            this(TextLine.construct())
        }
        static construct(): KPointer {
            const retval  = ArkUIGeneratedNativeModule._text_TextLine_construct()
            return retval
        }
        static getFinalizer(): KPointer {
            return ArkUIGeneratedNativeModule._text_TextLine_getFinalizer()
        }
        public getGlyphCount(): number {
            return this.getGlyphCount_serialize()
        }
        public getTextRange(): Range {
            return this.getTextRange_serialize()
        }
        public getGlyphRuns(): Array<Run> {
            return this.getGlyphRuns_serialize()
        }
        public paint(canvas: drawing.Canvas, x: number, y: number): void {
            const canvas_casted = canvas as (drawing.Canvas)
            const x_casted = x as (number)
            const y_casted = y as (number)
            this.paint_serialize(canvas_casted, x_casted, y_casted)
            return
        }
        public createTruncatedLine(width: number, ellipsisMode: EllipsisMode, ellipsis: string): TextLine {
            const width_casted = width as (number)
            const ellipsisMode_casted = ellipsisMode as (EllipsisMode)
            const ellipsis_casted = ellipsis as (string)
            return this.createTruncatedLine_serialize(width_casted, ellipsisMode_casted, ellipsis_casted)
        }
        public getTypographicBounds(): TypographicBounds {
            return this.getTypographicBounds_serialize()
        }
        public getImageBounds(): common2D.Rect {
            return this.getImageBounds_serialize()
        }
        public getTrailingSpaceWidth(): number {
            return this.getTrailingSpaceWidth_serialize()
        }
        public getStringIndexForPosition(point: common2D.Point): number {
            const point_casted = point as (common2D.Point)
            return this.getStringIndexForPosition_serialize(point_casted)
        }
        public getOffsetForStringIndex(index: number): number {
            const index_casted = index as (number)
            return this.getOffsetForStringIndex_serialize(index_casted)
        }
        public enumerateCaretOffsets(callback_: CaretOffsetsCallback): void {
            const callback__casted = callback_ as (CaretOffsetsCallback)
            this.enumerateCaretOffsets_serialize(callback__casted)
            return
        }
        public getAlignmentOffset(alignmentFactor: number, alignmentWidth: number): number {
            const alignmentFactor_casted = alignmentFactor as (number)
            const alignmentWidth_casted = alignmentWidth as (number)
            return this.getAlignmentOffset_serialize(alignmentFactor_casted, alignmentWidth_casted)
        }
        private getGlyphCount_serialize(): number {
            const retval  = ArkUIGeneratedNativeModule._text_TextLine_getGlyphCount(this.peer!.ptr)
            return retval
        }
        private getTextRange_serialize(): Range {
            const retval  = ArkUIGeneratedNativeModule._text_TextLine_getTextRange(this.peer!.ptr)
            let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
            const returnResult : Range = text_Range_serializer.read(retvalDeserializer)
            return returnResult
        }
        private getGlyphRuns_serialize(): Array<Run> {
            const retval  = ArkUIGeneratedNativeModule._text_TextLine_getGlyphRuns(this.peer!.ptr)
            let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
            const bufferLength : int32 = retvalDeserializer.readInt32()
            let buffer : Array<Run> = new Array<Run>(bufferLength)
            for (let bufferBufCounterI = 0; bufferBufCounterI < bufferLength; bufferBufCounterI++) {
                buffer[bufferBufCounterI] = (text_Run_serializer.read(retvalDeserializer) as text.Run)
            }
            const returnResult : Array<Run> = buffer
            return returnResult
        }
        private paint_serialize(canvas: drawing.Canvas, x: number, y: number): void {
            ArkUIGeneratedNativeModule._text_TextLine_paint(this.peer!.ptr, toPeerPtr(canvas), x, y)
        }
        private createTruncatedLine_serialize(width: number, ellipsisMode: EllipsisMode, ellipsis: string): TextLine {
            const retval  = ArkUIGeneratedNativeModule._text_TextLine_createTruncatedLine(this.peer!.ptr, width, TypeChecker.text_EllipsisMode_ToNumeric(ellipsisMode), ellipsis)
            const obj : TextLine = text.TextLineInternal.fromPtr(retval)
            return obj
        }
        private getTypographicBounds_serialize(): TypographicBounds {
            const retval  = ArkUIGeneratedNativeModule._text_TextLine_getTypographicBounds(this.peer!.ptr)
            let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
            const returnResult : TypographicBounds = text_TypographicBounds_serializer.read(retvalDeserializer)
            return returnResult
        }
        private getImageBounds_serialize(): common2D.Rect {
            const retval  = ArkUIGeneratedNativeModule._text_TextLine_getImageBounds(this.peer!.ptr)
            let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
            const returnResult : common2D.Rect = common2D_Rect_serializer.read(retvalDeserializer)
            return returnResult
        }
        private getTrailingSpaceWidth_serialize(): number {
            const retval  = ArkUIGeneratedNativeModule._text_TextLine_getTrailingSpaceWidth(this.peer!.ptr)
            return retval
        }
        private getStringIndexForPosition_serialize(point: common2D.Point): number {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            common2D_Point_serializer.write(thisSerializer, point)
            const retval  = ArkUIGeneratedNativeModule._text_TextLine_getStringIndexForPosition(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
            thisSerializer.release()
            return retval
        }
        private getOffsetForStringIndex_serialize(index: number): number {
            const retval  = ArkUIGeneratedNativeModule._text_TextLine_getOffsetForStringIndex(this.peer!.ptr, index)
            return retval
        }
        private enumerateCaretOffsets_serialize(callback_: CaretOffsetsCallback): void {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            thisSerializer.holdAndWriteCallback(callback_)
            ArkUIGeneratedNativeModule._text_TextLine_enumerateCaretOffsets(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
            thisSerializer.release()
        }
        private getAlignmentOffset_serialize(alignmentFactor: number, alignmentWidth: number): number {
            const retval  = ArkUIGeneratedNativeModule._text_TextLine_getAlignmentOffset(this.peer!.ptr, alignmentFactor, alignmentWidth)
            return retval
        }
    }
    export enum TextAlign {
        LEFT = 0,
        RIGHT = 1,
        CENTER = 2,
        JUSTIFY = 3,
        START = 4,
        END = 5
    }
    export enum TextDirection {
        RTL = 0,
        LTR = 1
    }
    export enum BreakStrategy {
        GREEDY = 0,
        HIGH_QUALITY = 1,
        BALANCED = 2
    }
    export enum WordBreak {
        NORMAL = 0,
        BREAK_ALL = 1,
        BREAK_WORD = 2
    }
    export interface Decoration {
        textDecoration?: text.TextDecorationType;
        color?: common2D.Color;
        decorationStyle?: text.TextDecorationStyle;
        decorationThicknessScale?: number;
    }
    export enum TextDecorationType {
        NONE = 0,
        UNDERLINE = 1,
        OVERLINE = 2,
        LINE_THROUGH = 3
    }
    export enum TextDecorationStyle {
        SOLID = 0,
        DOUBLE = 1,
        DOTTED = 2,
        DASHED = 3,
        WAVY = 4
    }
    export enum FontWeight {
        W100 = 0,
        W200 = 1,
        W300 = 2,
        W400 = 3,
        W500 = 4,
        W600 = 5,
        W700 = 6,
        W800 = 7,
        W900 = 8
    }
    export enum FontStyle {
        NORMAL = 0,
        ITALIC = 1,
        OBLIQUE = 2
    }
    export enum FontWidth {
        ULTRA_CONDENSED = 1,
        EXTRA_CONDENSED = 2,
        CONDENSED = 3,
        SEMI_CONDENSED = 4,
        NORMAL = 5,
        SEMI_EXPANDED = 6,
        EXPANDED = 7,
        EXTRA_EXPANDED = 8,
        ULTRA_EXPANDED = 9
    }
    export enum TextHeightBehavior {
        ALL = 0,
        DISABLE_FIRST_ASCENT = 1,
        DISABLE_LAST_ASCENT = 2,
        DISABLE_ALL = 3
    }
    export enum TextBaseline {
        ALPHABETIC = 0,
        IDEOGRAPHIC = 1
    }
    export enum EllipsisMode {
        START = 0,
        MIDDLE = 1,
        END = 2
    }
    export interface TextShadow {
        color?: common2D.Color;
        point?: common2D.Point;
        blurRadius?: number;
    }
    export interface RectStyle {
        color: common2D.Color;
        leftTopRadius: number;
        rightTopRadius: number;
        rightBottomRadius: number;
        leftBottomRadius: number;
    }
    export interface FontFeature {
        name: string;
        value: number;
    }
    export interface FontVariation {
        axis: string;
        value: number;
    }
    export interface TextStyle {
        decoration?: text.Decoration;
        color?: common2D.Color;
        fontWeight?: text.FontWeight;
        fontStyle?: text.FontStyle;
        baseline?: text.TextBaseline;
        fontFamilies?: Array<string>;
        fontSize?: number;
        letterSpacing?: number;
        wordSpacing?: number;
        heightScale?: number;
        halfLeading?: boolean;
        heightOnly?: boolean;
        ellipsis?: string;
        ellipsisMode?: text.EllipsisMode;
        locale?: string;
        baselineShift?: number;
        fontFeatures?: Array<text.FontFeature>;
        textShadows?: Array<text.TextShadow>;
        backgroundRect?: text.RectStyle;
        fontVariations?: Array<text.FontVariation>;
    }
    export interface StrutStyle {
        fontFamilies?: Array<string>;
        fontStyle?: text.FontStyle;
        fontWidth?: text.FontWidth;
        fontWeight?: text.FontWeight;
        fontSize?: number;
        height?: number;
        leading?: number;
        forceHeight?: boolean;
        enabled?: boolean;
        heightOverride?: boolean;
        halfLeading?: boolean;
    }
    export interface ParagraphStyle {
        textStyle?: text.TextStyle;
        textDirection?: text.TextDirection;
        align?: text.TextAlign;
        wordBreak?: text.WordBreak;
        maxLines?: number;
        breakStrategy?: text.BreakStrategy;
        strutStyle?: text.StrutStyle;
        textHeightBehavior?: text.TextHeightBehavior;
        tab?: text.TextTab;
    }
    export enum PlaceholderAlignment {
        OFFSET_AT_BASELINE = 0,
        ABOVE_BASELINE = 1,
        BELOW_BASELINE = 2,
        TOP_OF_ROW_BOX = 3,
        BOTTOM_OF_ROW_BOX = 4,
        CENTER_OF_ROW_BOX = 5
    }
    export interface PlaceholderSpan {
        width: number;
        height: number;
        align: text.PlaceholderAlignment;
        baseline: text.TextBaseline;
        baselineOffset: number;
    }
    export interface Range {
        start: number;
        end: number;
    }
    export enum SystemFontType {
        ALL = 0,
        GENERIC = 1,
        STYLISH = 2,
        INSTALLED = 3
    }
    export interface FontDescriptor {
        path?: string;
        postScriptName?: string;
        fullName?: string;
        fontFamily?: string;
        fontSubfamily?: string;
        weight?: text.FontWeight;
        width?: number;
        italic?: number;
        monoSpace?: boolean;
        symbolic?: boolean;
    }
    export interface TextBox {
        rect: common2D.Rect;
        direction: text.TextDirection;
    }
    export interface PositionWithAffinity {
        position: number;
        affinity: text.Affinity;
    }
    export enum RectWidthStyle {
        TIGHT = 0,
        MAX = 1
    }
    export enum RectHeightStyle {
        TIGHT = 0,
        MAX = 1,
        INCLUDE_LINE_SPACE_MIDDLE = 2,
        INCLUDE_LINE_SPACE_TOP = 3,
        INCLUDE_LINE_SPACE_BOTTOM = 4,
        STRUT = 5
    }
    export enum Affinity {
        UPSTREAM = 0,
        DOWNSTREAM = 1
    }
    export interface TypographicBounds {
        ascent: number;
        descent: number;
        leading: number;
        width: number;
    }
    export type CaretOffsetsCallback = ((offset: number,index: number,leadingEdge: boolean) => boolean);
    export interface RunMetrics {
        textStyle: text.TextStyle;
        fontMetrics: drawing.FontMetrics;
    }
    export interface LineMetrics {
        startIndex: number;
        endIndex: number;
        ascent: number;
        descent: number;
        height: number;
        width: number;
        left: number;
        baseline: number;
        lineNumber: number;
        topHeight: number;
        runMetrics: Map<number, text.RunMetrics>;
    }
    export interface TextTab {
        alignment: text.TextAlign;
        location: number;
    }
    export function getSystemFontFullNamesByType(fontType: SystemFontType): Promise<Array<string>> {
        return GlobalScope.text_getSystemFontFullNamesByType(fontType)
    }
    export function getFontDescriptorByFullName(fullName: string, fontType: SystemFontType): Promise<FontDescriptor> {
        return GlobalScope.text_getFontDescriptorByFullName(fullName, fontType)
    }
    export function matchFontDescriptors(desc: FontDescriptor): Promise<Array<FontDescriptor>> {
        return GlobalScope.text_matchFontDescriptors(desc)
    }
}
