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

import { default as text } from '@ohos.graphics.text'
import { SerializerBase, DeserializerBase, CallbackResource, InteropNativeModule, MaterializedBase, Tags, RuntimeType, toPeerPtr, nullptr, KPointer, NativeBuffer, KSerializerBuffer, KUint8ArrayPtr } from '@koalaui/interop'
import { int32, int64, float32, unsafeCast } from '@koalaui/common'
import { CallbackTransformer } from './../CallbackTransformer'
import { common2D_Color_serializer, common2D_Rect_serializer, common2D_Point_serializer } from './ohos.graphics.common2D'
import { default as common2D } from '@ohos.graphics.common2D'
import { drawing_FontMetrics_serializer } from './ohos.graphics.drawing'
import { default as drawing } from '@ohos.graphics.drawing'
export class text_FontFeature_serializer {
    public static write(buffer: SerializerBase, value: text.FontFeature): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForName  = value.name
        valueSerializer.writeString(valueHolderForName)
        const valueHolderForValue  = value.value
        valueSerializer.writeInt32(valueHolderForValue)
    }
    public static read(buffer: DeserializerBase): text.FontFeature {
        let valueDeserializer : DeserializerBase = buffer
        const nameTmpResult : string = (valueDeserializer.readString() as string)
        const valueTmpResult : int32 = valueDeserializer.readInt32()
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
        valueSerializer.writeFloat64(valueHolderForValue)
    }
    public static read(buffer: DeserializerBase): text.FontVariation {
        let valueDeserializer : DeserializerBase = buffer
        const axisTmpResult : string = (valueDeserializer.readString() as string)
        const valueTmpResult : double = valueDeserializer.readFloat64()
        let value : text.FontVariation = ({axis: axisTmpResult, value: valueTmpResult} as text.FontVariation)
        return value
    }
}
export class text_LineMetrics_serializer {
    public static write(buffer: SerializerBase, value: text.LineMetrics): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForStartIndex  = value.startIndex
        valueSerializer.writeInt32(valueHolderForStartIndex)
        const valueHolderForEndIndex  = value.endIndex
        valueSerializer.writeInt32(valueHolderForEndIndex)
        const valueHolderForAscent  = value.ascent
        valueSerializer.writeFloat64(valueHolderForAscent)
        const valueHolderForDescent  = value.descent
        valueSerializer.writeFloat64(valueHolderForDescent)
        const valueHolderForHeight  = value.height
        valueSerializer.writeFloat64(valueHolderForHeight)
        const valueHolderForWidth  = value.width
        valueSerializer.writeFloat64(valueHolderForWidth)
        const valueHolderForLeft  = value.left
        valueSerializer.writeFloat64(valueHolderForLeft)
        const valueHolderForBaseline  = value.baseline
        valueSerializer.writeFloat64(valueHolderForBaseline)
        const valueHolderForLineNumber  = value.lineNumber
        valueSerializer.writeInt32(valueHolderForLineNumber)
        const valueHolderForTopHeight  = value.topHeight
        valueSerializer.writeFloat64(valueHolderForTopHeight)
        const valueHolderForRunMetrics  = value.runMetrics
        valueSerializer.writeInt32((valueHolderForRunMetrics.size).toInt())
        for (const pair of valueHolderForRunMetrics) {
            const valueHolderForRunMetricsKeyVar = pair[0]
            const valueHolderForRunMetricsValueVar = pair[1]
            valueSerializer.writeInt32(valueHolderForRunMetricsKeyVar)
            text_RunMetrics_serializer.write(valueSerializer, valueHolderForRunMetricsValueVar)
        }
    }
    public static read(buffer: DeserializerBase): text.LineMetrics {
        let valueDeserializer : DeserializerBase = buffer
        const startIndexTmpResult : int32 = valueDeserializer.readInt32()
        const endIndexTmpResult : int32 = valueDeserializer.readInt32()
        const ascentTmpResult : double = valueDeserializer.readFloat64()
        const descentTmpResult : double = valueDeserializer.readFloat64()
        const heightTmpResult : double = valueDeserializer.readFloat64()
        const widthTmpResult : double = valueDeserializer.readFloat64()
        const leftTmpResult : double = valueDeserializer.readFloat64()
        const baselineTmpResult : double = valueDeserializer.readFloat64()
        const lineNumberTmpResult : int32 = valueDeserializer.readInt32()
        const topHeightTmpResult : double = valueDeserializer.readFloat64()
        const runMetricsTmpBufSizeVar : int32 = valueDeserializer.readInt32()
        let runMetricsTmpBuf : Map<int32, text.RunMetrics> = new Map<int32, text.RunMetrics>()
        // TODO: TS map resize
        for (let runMetricsTmpBufIVar = 0; runMetricsTmpBufIVar < runMetricsTmpBufSizeVar; runMetricsTmpBufIVar++) {
            const runMetricsTmpBufKeyVar : int32 = valueDeserializer.readInt32()
            const runMetricsTmpBufValueVar : text.RunMetrics = text_RunMetrics_serializer.read(valueDeserializer)
            runMetricsTmpBuf.set(runMetricsTmpBufKeyVar, runMetricsTmpBufValueVar)
        }
        const runMetricsTmpResult : Map<int32, text.RunMetrics> = runMetricsTmpBuf
        let value : text.LineMetrics = ({startIndex: startIndexTmpResult, endIndex: endIndexTmpResult, ascent: ascentTmpResult, descent: descentTmpResult, height: heightTmpResult, width: widthTmpResult, left: leftTmpResult, baseline: baselineTmpResult, lineNumber: lineNumberTmpResult, topHeight: topHeightTmpResult, runMetrics: runMetricsTmpResult} as text.LineMetrics)
        return value
    }
}
export class text_RectStyle_serializer {
    public static write(buffer: SerializerBase, value: text.RectStyle): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForColor  = value.color
        common2D_Color_serializer.write(valueSerializer, valueHolderForColor)
        const valueHolderForLeftTopRadius  = value.leftTopRadius
        valueSerializer.writeFloat64(valueHolderForLeftTopRadius)
        const valueHolderForRightTopRadius  = value.rightTopRadius
        valueSerializer.writeFloat64(valueHolderForRightTopRadius)
        const valueHolderForRightBottomRadius  = value.rightBottomRadius
        valueSerializer.writeFloat64(valueHolderForRightBottomRadius)
        const valueHolderForLeftBottomRadius  = value.leftBottomRadius
        valueSerializer.writeFloat64(valueHolderForLeftBottomRadius)
    }
    public static read(buffer: DeserializerBase): text.RectStyle {
        let valueDeserializer : DeserializerBase = buffer
        const colorTmpResult : common2D.Color = common2D_Color_serializer.read(valueDeserializer)
        const leftTopRadiusTmpResult : double = valueDeserializer.readFloat64()
        const rightTopRadiusTmpResult : double = valueDeserializer.readFloat64()
        const rightBottomRadiusTmpResult : double = valueDeserializer.readFloat64()
        const leftBottomRadiusTmpResult : double = valueDeserializer.readFloat64()
        let value : text.RectStyle = ({color: colorTmpResult, leftTopRadius: leftTopRadiusTmpResult, rightTopRadius: rightTopRadiusTmpResult, rightBottomRadius: rightBottomRadiusTmpResult, leftBottomRadius: leftBottomRadiusTmpResult} as text.RectStyle)
        return value
    }
}
export class text_TextBox_serializer {
    public static write(buffer: SerializerBase, value: text.TextBox): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForRect  = value.rect
        common2D_Rect_serializer.write(valueSerializer, valueHolderForRect)
        const valueHolderForDirection  = value.direction
        valueSerializer.writeInt32(valueHolderForDirection.valueOf())
    }
    public static read(buffer: DeserializerBase): text.TextBox {
        let valueDeserializer : DeserializerBase = buffer
        const rectTmpResult : common2D.Rect = common2D_Rect_serializer.read(valueDeserializer)
        const directionTmpResult : text.TextDirection = text.TextDirection.fromValue(valueDeserializer.readInt32())
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
            valueSerializer.writeInt32(valueHolderForTextDecorationTmpValue.valueOf())
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
            valueSerializer.writeInt32(valueHolderForDecorationStyleTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForDecorationThicknessScale  = value.decorationThicknessScale
        if (valueHolderForDecorationThicknessScale !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForDecorationThicknessScaleTmpValue  = valueHolderForDecorationThicknessScale!
            valueSerializer.writeFloat64(valueHolderForDecorationThicknessScaleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): text.Decoration {
        let valueDeserializer : DeserializerBase = buffer
        const textDecorationTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let textDecorationTmpBuf : text.TextDecorationType | undefined = undefined
        if ((textDecorationTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            textDecorationTmpBuf = text.TextDecorationType.fromValue(valueDeserializer.readInt32())
        }
        const textDecorationTmpResult : text.TextDecorationType | undefined = textDecorationTmpBuf
        const colorTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let colorTmpBuf : common2D.Color | undefined = undefined
        if ((colorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            colorTmpBuf = common2D_Color_serializer.read(valueDeserializer)
        }
        const colorTmpResult : common2D.Color | undefined = colorTmpBuf
        const decorationStyleTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let decorationStyleTmpBuf : text.TextDecorationStyle | undefined = undefined
        if ((decorationStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            decorationStyleTmpBuf = text.TextDecorationStyle.fromValue(valueDeserializer.readInt32())
        }
        const decorationStyleTmpResult : text.TextDecorationStyle | undefined = decorationStyleTmpBuf
        const decorationThicknessScaleTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let decorationThicknessScaleTmpBuf : double | undefined = undefined
        if ((decorationThicknessScaleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            decorationThicknessScaleTmpBuf = valueDeserializer.readFloat64()
        }
        const decorationThicknessScaleTmpResult : double | undefined = decorationThicknessScaleTmpBuf
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
            valueSerializer.writeFloat64(valueHolderForBlurRadiusTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): text.TextShadow {
        let valueDeserializer : DeserializerBase = buffer
        const colorTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let colorTmpBuf : common2D.Color | undefined = undefined
        if ((colorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            colorTmpBuf = common2D_Color_serializer.read(valueDeserializer)
        }
        const colorTmpResult : common2D.Color | undefined = colorTmpBuf
        const pointTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let pointTmpBuf : common2D.Point | undefined = undefined
        if ((pointTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            pointTmpBuf = common2D_Point_serializer.read(valueDeserializer)
        }
        const pointTmpResult : common2D.Point | undefined = pointTmpBuf
        const blurRadiusTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let blurRadiusTmpBuf : double | undefined = undefined
        if ((blurRadiusTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            blurRadiusTmpBuf = valueDeserializer.readFloat64()
        }
        const blurRadiusTmpResult : double | undefined = blurRadiusTmpBuf
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
            valueSerializer.writeInt32(valueHolderForFontWeightTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForFontStyle  = value.fontStyle
        if (valueHolderForFontStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFontStyleTmpValue  = (valueHolderForFontStyle as text.FontStyle)
            valueSerializer.writeInt32(valueHolderForFontStyleTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBaseline  = value.baseline
        if (valueHolderForBaseline !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBaselineTmpValue  = (valueHolderForBaseline as text.TextBaseline)
            valueSerializer.writeInt32(valueHolderForBaselineTmpValue.valueOf())
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
            valueSerializer.writeFloat64(valueHolderForFontSizeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLetterSpacing  = value.letterSpacing
        if (valueHolderForLetterSpacing !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLetterSpacingTmpValue  = valueHolderForLetterSpacing!
            valueSerializer.writeFloat64(valueHolderForLetterSpacingTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForWordSpacing  = value.wordSpacing
        if (valueHolderForWordSpacing !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForWordSpacingTmpValue  = valueHolderForWordSpacing!
            valueSerializer.writeFloat64(valueHolderForWordSpacingTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForHeightScale  = value.heightScale
        if (valueHolderForHeightScale !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForHeightScaleTmpValue  = valueHolderForHeightScale!
            valueSerializer.writeFloat64(valueHolderForHeightScaleTmpValue)
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
            valueSerializer.writeInt32(valueHolderForEllipsisModeTmpValue.valueOf())
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
            valueSerializer.writeFloat64(valueHolderForBaselineShiftTmpValue)
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
        const decorationTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let decorationTmpBuf : text.Decoration | undefined = undefined
        if ((decorationTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            decorationTmpBuf = text_Decoration_serializer.read(valueDeserializer)
        }
        const decorationTmpResult : text.Decoration | undefined = decorationTmpBuf
        const colorTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let colorTmpBuf : common2D.Color | undefined = undefined
        if ((colorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            colorTmpBuf = common2D_Color_serializer.read(valueDeserializer)
        }
        const colorTmpResult : common2D.Color | undefined = colorTmpBuf
        const fontWeightTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let fontWeightTmpBuf : text.FontWeight | undefined = undefined
        if ((fontWeightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            fontWeightTmpBuf = text.FontWeight.fromValue(valueDeserializer.readInt32())
        }
        const fontWeightTmpResult : text.FontWeight | undefined = fontWeightTmpBuf
        const fontStyleTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let fontStyleTmpBuf : text.FontStyle | undefined = undefined
        if ((fontStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            fontStyleTmpBuf = text.FontStyle.fromValue(valueDeserializer.readInt32())
        }
        const fontStyleTmpResult : text.FontStyle | undefined = fontStyleTmpBuf
        const baselineTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let baselineTmpBuf : text.TextBaseline | undefined = undefined
        if ((baselineTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            baselineTmpBuf = text.TextBaseline.fromValue(valueDeserializer.readInt32())
        }
        const baselineTmpResult : text.TextBaseline | undefined = baselineTmpBuf
        const fontFamiliesTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let fontFamiliesTmpBuf : Array<string> | undefined = undefined
        if ((fontFamiliesTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const fontFamiliesTmpBufOptLength : int32 = valueDeserializer.readInt32()
            let fontFamiliesTmpBufOpt : Array<string> = new Array<string>(fontFamiliesTmpBufOptLength)
            for (let fontFamiliesTmpBufOptBufCounterI = 0; fontFamiliesTmpBufOptBufCounterI < fontFamiliesTmpBufOptLength; fontFamiliesTmpBufOptBufCounterI++) {
                fontFamiliesTmpBufOpt[fontFamiliesTmpBufOptBufCounterI] = (valueDeserializer.readString() as string)
            }
            fontFamiliesTmpBuf = fontFamiliesTmpBufOpt
        }
        const fontFamiliesTmpResult : Array<string> | undefined = fontFamiliesTmpBuf
        const fontSizeTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let fontSizeTmpBuf : double | undefined = undefined
        if ((fontSizeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            fontSizeTmpBuf = valueDeserializer.readFloat64()
        }
        const fontSizeTmpResult : double | undefined = fontSizeTmpBuf
        const letterSpacingTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let letterSpacingTmpBuf : double | undefined = undefined
        if ((letterSpacingTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            letterSpacingTmpBuf = valueDeserializer.readFloat64()
        }
        const letterSpacingTmpResult : double | undefined = letterSpacingTmpBuf
        const wordSpacingTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let wordSpacingTmpBuf : double | undefined = undefined
        if ((wordSpacingTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            wordSpacingTmpBuf = valueDeserializer.readFloat64()
        }
        const wordSpacingTmpResult : double | undefined = wordSpacingTmpBuf
        const heightScaleTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let heightScaleTmpBuf : double | undefined = undefined
        if ((heightScaleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            heightScaleTmpBuf = valueDeserializer.readFloat64()
        }
        const heightScaleTmpResult : double | undefined = heightScaleTmpBuf
        const halfLeadingTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let halfLeadingTmpBuf : boolean | undefined = undefined
        if ((halfLeadingTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            halfLeadingTmpBuf = valueDeserializer.readBoolean()
        }
        const halfLeadingTmpResult : boolean | undefined = halfLeadingTmpBuf
        const heightOnlyTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let heightOnlyTmpBuf : boolean | undefined = undefined
        if ((heightOnlyTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            heightOnlyTmpBuf = valueDeserializer.readBoolean()
        }
        const heightOnlyTmpResult : boolean | undefined = heightOnlyTmpBuf
        const ellipsisTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let ellipsisTmpBuf : string | undefined = undefined
        if ((ellipsisTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            ellipsisTmpBuf = (valueDeserializer.readString() as string)
        }
        const ellipsisTmpResult : string | undefined = ellipsisTmpBuf
        const ellipsisModeTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let ellipsisModeTmpBuf : text.EllipsisMode | undefined = undefined
        if ((ellipsisModeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            ellipsisModeTmpBuf = text.EllipsisMode.fromValue(valueDeserializer.readInt32())
        }
        const ellipsisModeTmpResult : text.EllipsisMode | undefined = ellipsisModeTmpBuf
        const localeTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let localeTmpBuf : string | undefined = undefined
        if ((localeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            localeTmpBuf = (valueDeserializer.readString() as string)
        }
        const localeTmpResult : string | undefined = localeTmpBuf
        const baselineShiftTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let baselineShiftTmpBuf : double | undefined = undefined
        if ((baselineShiftTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            baselineShiftTmpBuf = valueDeserializer.readFloat64()
        }
        const baselineShiftTmpResult : double | undefined = baselineShiftTmpBuf
        const fontFeaturesTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let fontFeaturesTmpBuf : Array<text.FontFeature> | undefined = undefined
        if ((fontFeaturesTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const fontFeaturesTmpBufOptLength : int32 = valueDeserializer.readInt32()
            let fontFeaturesTmpBufOpt : Array<text.FontFeature> = new Array<text.FontFeature>(fontFeaturesTmpBufOptLength)
            for (let fontFeaturesTmpBufOptBufCounterI = 0; fontFeaturesTmpBufOptBufCounterI < fontFeaturesTmpBufOptLength; fontFeaturesTmpBufOptBufCounterI++) {
                fontFeaturesTmpBufOpt[fontFeaturesTmpBufOptBufCounterI] = text_FontFeature_serializer.read(valueDeserializer)
            }
            fontFeaturesTmpBuf = fontFeaturesTmpBufOpt
        }
        const fontFeaturesTmpResult : Array<text.FontFeature> | undefined = fontFeaturesTmpBuf
        const textShadowsTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let textShadowsTmpBuf : Array<text.TextShadow> | undefined = undefined
        if ((textShadowsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const textShadowsTmpBufOptLength : int32 = valueDeserializer.readInt32()
            let textShadowsTmpBufOpt : Array<text.TextShadow> = new Array<text.TextShadow>(textShadowsTmpBufOptLength)
            for (let textShadowsTmpBufOptBufCounterI = 0; textShadowsTmpBufOptBufCounterI < textShadowsTmpBufOptLength; textShadowsTmpBufOptBufCounterI++) {
                textShadowsTmpBufOpt[textShadowsTmpBufOptBufCounterI] = text_TextShadow_serializer.read(valueDeserializer)
            }
            textShadowsTmpBuf = textShadowsTmpBufOpt
        }
        const textShadowsTmpResult : Array<text.TextShadow> | undefined = textShadowsTmpBuf
        const backgroundRectTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let backgroundRectTmpBuf : text.RectStyle | undefined = undefined
        if ((backgroundRectTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            backgroundRectTmpBuf = text_RectStyle_serializer.read(valueDeserializer)
        }
        const backgroundRectTmpResult : text.RectStyle | undefined = backgroundRectTmpBuf
        const fontVariationsTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let fontVariationsTmpBuf : Array<text.FontVariation> | undefined = undefined
        if ((fontVariationsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const fontVariationsTmpBufOptLength : int32 = valueDeserializer.readInt32()
            let fontVariationsTmpBufOpt : Array<text.FontVariation> = new Array<text.FontVariation>(fontVariationsTmpBufOptLength)
            for (let fontVariationsTmpBufOptBufCounterI = 0; fontVariationsTmpBufOptBufCounterI < fontVariationsTmpBufOptLength; fontVariationsTmpBufOptBufCounterI++) {
                fontVariationsTmpBufOpt[fontVariationsTmpBufOptBufCounterI] = text_FontVariation_serializer.read(valueDeserializer)
            }
            fontVariationsTmpBuf = fontVariationsTmpBufOpt
        }
        const fontVariationsTmpResult : Array<text.FontVariation> | undefined = fontVariationsTmpBuf
        let value : text.TextStyle = ({decoration: decorationTmpResult, color: colorTmpResult, fontWeight: fontWeightTmpResult, fontStyle: fontStyleTmpResult, baseline: baselineTmpResult, fontFamilies: fontFamiliesTmpResult, fontSize: fontSizeTmpResult, letterSpacing: letterSpacingTmpResult, wordSpacing: wordSpacingTmpResult, heightScale: heightScaleTmpResult, halfLeading: halfLeadingTmpResult, heightOnly: heightOnlyTmpResult, ellipsis: ellipsisTmpResult, ellipsisMode: ellipsisModeTmpResult, locale: localeTmpResult, baselineShift: baselineShiftTmpResult, fontFeatures: fontFeaturesTmpResult, textShadows: textShadowsTmpResult, backgroundRect: backgroundRectTmpResult, fontVariations: fontVariationsTmpResult} as text.TextStyle)
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
