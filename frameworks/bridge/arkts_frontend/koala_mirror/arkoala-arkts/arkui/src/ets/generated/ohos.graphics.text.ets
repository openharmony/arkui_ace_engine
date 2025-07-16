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

import { SerializerBase, DeserializerBase, CallbackResource, InteropNativeModule, MaterializedBase, Tags, RuntimeType, runtimeType, toPeerPtr, nullptr, KPointer, NativeBuffer, KSerializerBuffer, KUint8ArrayPtr, Finalizable, registerCallback, wrapCallback, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { CallbackKind } from "./peers/CallbackKind"
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
        const value_name  = value.name
        valueSerializer.writeString(value_name)
        const value_value  = value.value
        valueSerializer.writeNumber(value_value)
    }
    public static read(buffer: DeserializerBase): text.FontFeature {
        let valueDeserializer : DeserializerBase = buffer
        const name_result : string = (valueDeserializer.readString() as string)
        const value_result : number = (valueDeserializer.readNumber() as number)
        let value : text.FontFeature = ({name: name_result, value: value_result} as text.FontFeature)
        return value
    }
}
export class text_FontVariation_serializer {
    public static write(buffer: SerializerBase, value: text.FontVariation): void {
        let valueSerializer : SerializerBase = buffer
        const value_axis  = value.axis
        valueSerializer.writeString(value_axis)
        const value_value  = value.value
        valueSerializer.writeNumber(value_value)
    }
    public static read(buffer: DeserializerBase): text.FontVariation {
        let valueDeserializer : DeserializerBase = buffer
        const axis_result : string = (valueDeserializer.readString() as string)
        const value_result : number = (valueDeserializer.readNumber() as number)
        let value : text.FontVariation = ({axis: axis_result, value: value_result} as text.FontVariation)
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
        const value_position  = value.position
        valueSerializer.writeNumber(value_position)
        const value_affinity  = value.affinity
        valueSerializer.writeInt32(TypeChecker.text_Affinity_ToNumeric(value_affinity))
    }
    public static read(buffer: DeserializerBase): text.PositionWithAffinity {
        let valueDeserializer : DeserializerBase = buffer
        const position_result : number = (valueDeserializer.readNumber() as number)
        const affinity_result : text.Affinity = TypeChecker.text_Affinity_FromNumeric(valueDeserializer.readInt32())
        let value : text.PositionWithAffinity = ({position: position_result, affinity: affinity_result} as text.PositionWithAffinity)
        return value
    }
}
export class text_Range_serializer {
    public static write(buffer: SerializerBase, value: text.Range): void {
        let valueSerializer : SerializerBase = buffer
        const value_start  = value.start
        valueSerializer.writeNumber(value_start)
        const value_end  = value.end
        valueSerializer.writeNumber(value_end)
    }
    public static read(buffer: DeserializerBase): text.Range {
        let valueDeserializer : DeserializerBase = buffer
        const start_result : number = (valueDeserializer.readNumber() as number)
        const end_result : number = (valueDeserializer.readNumber() as number)
        let value : text.Range = ({start: start_result, end: end_result} as text.Range)
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
        const value_alignment  = value.alignment
        valueSerializer.writeInt32(TypeChecker.text_TextAlign_ToNumeric(value_alignment))
        const value_location  = value.location
        valueSerializer.writeNumber(value_location)
    }
    public static read(buffer: DeserializerBase): text.TextTab {
        let valueDeserializer : DeserializerBase = buffer
        const alignment_result : text.TextAlign = TypeChecker.text_TextAlign_FromNumeric(valueDeserializer.readInt32())
        const location_result : number = (valueDeserializer.readNumber() as number)
        let value : text.TextTab = ({alignment: alignment_result, location: location_result} as text.TextTab)
        return value
    }
}
export class text_TypographicBounds_serializer {
    public static write(buffer: SerializerBase, value: text.TypographicBounds): void {
        let valueSerializer : SerializerBase = buffer
        const value_ascent  = value.ascent
        valueSerializer.writeNumber(value_ascent)
        const value_descent  = value.descent
        valueSerializer.writeNumber(value_descent)
        const value_leading  = value.leading
        valueSerializer.writeNumber(value_leading)
        const value_width  = value.width
        valueSerializer.writeNumber(value_width)
    }
    public static read(buffer: DeserializerBase): text.TypographicBounds {
        let valueDeserializer : DeserializerBase = buffer
        const ascent_result : number = (valueDeserializer.readNumber() as number)
        const descent_result : number = (valueDeserializer.readNumber() as number)
        const leading_result : number = (valueDeserializer.readNumber() as number)
        const width_result : number = (valueDeserializer.readNumber() as number)
        let value : text.TypographicBounds = ({ascent: ascent_result, descent: descent_result, leading: leading_result, width: width_result} as text.TypographicBounds)
        return value
    }
}
export class text_FontDescriptor_serializer {
    public static write(buffer: SerializerBase, value: text.FontDescriptor): void {
        let valueSerializer : SerializerBase = buffer
        const value_path  = value.path
        let value_path_type : int32 = RuntimeType.UNDEFINED
        value_path_type = runtimeType(value_path)
        valueSerializer.writeInt8((value_path_type).toChar())
        if ((value_path_type) != (RuntimeType.UNDEFINED)) {
            const value_path_value  = value_path!
            valueSerializer.writeString(value_path_value)
        }
        const value_postScriptName  = value.postScriptName
        let value_postScriptName_type : int32 = RuntimeType.UNDEFINED
        value_postScriptName_type = runtimeType(value_postScriptName)
        valueSerializer.writeInt8((value_postScriptName_type).toChar())
        if ((value_postScriptName_type) != (RuntimeType.UNDEFINED)) {
            const value_postScriptName_value  = value_postScriptName!
            valueSerializer.writeString(value_postScriptName_value)
        }
        const value_fullName  = value.fullName
        let value_fullName_type : int32 = RuntimeType.UNDEFINED
        value_fullName_type = runtimeType(value_fullName)
        valueSerializer.writeInt8((value_fullName_type).toChar())
        if ((value_fullName_type) != (RuntimeType.UNDEFINED)) {
            const value_fullName_value  = value_fullName!
            valueSerializer.writeString(value_fullName_value)
        }
        const value_fontFamily  = value.fontFamily
        let value_fontFamily_type : int32 = RuntimeType.UNDEFINED
        value_fontFamily_type = runtimeType(value_fontFamily)
        valueSerializer.writeInt8((value_fontFamily_type).toChar())
        if ((value_fontFamily_type) != (RuntimeType.UNDEFINED)) {
            const value_fontFamily_value  = value_fontFamily!
            valueSerializer.writeString(value_fontFamily_value)
        }
        const value_fontSubfamily  = value.fontSubfamily
        let value_fontSubfamily_type : int32 = RuntimeType.UNDEFINED
        value_fontSubfamily_type = runtimeType(value_fontSubfamily)
        valueSerializer.writeInt8((value_fontSubfamily_type).toChar())
        if ((value_fontSubfamily_type) != (RuntimeType.UNDEFINED)) {
            const value_fontSubfamily_value  = value_fontSubfamily!
            valueSerializer.writeString(value_fontSubfamily_value)
        }
        const value_weight  = value.weight
        let value_weight_type : int32 = RuntimeType.UNDEFINED
        value_weight_type = runtimeType(value_weight)
        valueSerializer.writeInt8((value_weight_type).toChar())
        if ((value_weight_type) != (RuntimeType.UNDEFINED)) {
            const value_weight_value  = (value_weight as text.FontWeight)
            valueSerializer.writeInt32(TypeChecker.text_FontWeight_ToNumeric(value_weight_value))
        }
        const value_width  = value.width
        let value_width_type : int32 = RuntimeType.UNDEFINED
        value_width_type = runtimeType(value_width)
        valueSerializer.writeInt8((value_width_type).toChar())
        if ((value_width_type) != (RuntimeType.UNDEFINED)) {
            const value_width_value  = value_width!
            valueSerializer.writeNumber(value_width_value)
        }
        const value_italic  = value.italic
        let value_italic_type : int32 = RuntimeType.UNDEFINED
        value_italic_type = runtimeType(value_italic)
        valueSerializer.writeInt8((value_italic_type).toChar())
        if ((value_italic_type) != (RuntimeType.UNDEFINED)) {
            const value_italic_value  = value_italic!
            valueSerializer.writeNumber(value_italic_value)
        }
        const value_monoSpace  = value.monoSpace
        let value_monoSpace_type : int32 = RuntimeType.UNDEFINED
        value_monoSpace_type = runtimeType(value_monoSpace)
        valueSerializer.writeInt8((value_monoSpace_type).toChar())
        if ((value_monoSpace_type) != (RuntimeType.UNDEFINED)) {
            const value_monoSpace_value  = value_monoSpace!
            valueSerializer.writeBoolean(value_monoSpace_value)
        }
        const value_symbolic  = value.symbolic
        let value_symbolic_type : int32 = RuntimeType.UNDEFINED
        value_symbolic_type = runtimeType(value_symbolic)
        valueSerializer.writeInt8((value_symbolic_type).toChar())
        if ((value_symbolic_type) != (RuntimeType.UNDEFINED)) {
            const value_symbolic_value  = value_symbolic!
            valueSerializer.writeBoolean(value_symbolic_value)
        }
    }
    public static read(buffer: DeserializerBase): text.FontDescriptor {
        let valueDeserializer : DeserializerBase = buffer
        const path_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let path_buf : string | undefined
        if ((path_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            path_buf = (valueDeserializer.readString() as string)
        }
        const path_result : string | undefined = path_buf
        const postScriptName_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let postScriptName_buf : string | undefined
        if ((postScriptName_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            postScriptName_buf = (valueDeserializer.readString() as string)
        }
        const postScriptName_result : string | undefined = postScriptName_buf
        const fullName_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fullName_buf : string | undefined
        if ((fullName_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            fullName_buf = (valueDeserializer.readString() as string)
        }
        const fullName_result : string | undefined = fullName_buf
        const fontFamily_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fontFamily_buf : string | undefined
        if ((fontFamily_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            fontFamily_buf = (valueDeserializer.readString() as string)
        }
        const fontFamily_result : string | undefined = fontFamily_buf
        const fontSubfamily_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fontSubfamily_buf : string | undefined
        if ((fontSubfamily_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            fontSubfamily_buf = (valueDeserializer.readString() as string)
        }
        const fontSubfamily_result : string | undefined = fontSubfamily_buf
        const weight_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let weight_buf : text.FontWeight | undefined
        if ((weight_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            weight_buf = TypeChecker.text_FontWeight_FromNumeric(valueDeserializer.readInt32())
        }
        const weight_result : text.FontWeight | undefined = weight_buf
        const width_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let width_buf : number | undefined
        if ((width_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            width_buf = (valueDeserializer.readNumber() as number)
        }
        const width_result : number | undefined = width_buf
        const italic_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let italic_buf : number | undefined
        if ((italic_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            italic_buf = (valueDeserializer.readNumber() as number)
        }
        const italic_result : number | undefined = italic_buf
        const monoSpace_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let monoSpace_buf : boolean | undefined
        if ((monoSpace_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            monoSpace_buf = valueDeserializer.readBoolean()
        }
        const monoSpace_result : boolean | undefined = monoSpace_buf
        const symbolic_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let symbolic_buf : boolean | undefined
        if ((symbolic_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            symbolic_buf = valueDeserializer.readBoolean()
        }
        const symbolic_result : boolean | undefined = symbolic_buf
        let value : text.FontDescriptor = ({path: path_result, postScriptName: postScriptName_result, fullName: fullName_result, fontFamily: fontFamily_result, fontSubfamily: fontSubfamily_result, weight: weight_result, width: width_result, italic: italic_result, monoSpace: monoSpace_result, symbolic: symbolic_result} as text.FontDescriptor)
        return value
    }
}
export class text_LineMetrics_serializer {
    public static write(buffer: SerializerBase, value: text.LineMetrics): void {
        let valueSerializer : SerializerBase = buffer
        const value_startIndex  = value.startIndex
        valueSerializer.writeNumber(value_startIndex)
        const value_endIndex  = value.endIndex
        valueSerializer.writeNumber(value_endIndex)
        const value_ascent  = value.ascent
        valueSerializer.writeNumber(value_ascent)
        const value_descent  = value.descent
        valueSerializer.writeNumber(value_descent)
        const value_height  = value.height
        valueSerializer.writeNumber(value_height)
        const value_width  = value.width
        valueSerializer.writeNumber(value_width)
        const value_left  = value.left
        valueSerializer.writeNumber(value_left)
        const value_baseline  = value.baseline
        valueSerializer.writeNumber(value_baseline)
        const value_lineNumber  = value.lineNumber
        valueSerializer.writeNumber(value_lineNumber)
        const value_topHeight  = value.topHeight
        valueSerializer.writeNumber(value_topHeight)
        const value_runMetrics  = value.runMetrics
        valueSerializer.writeInt32((value_runMetrics.size).toInt())
        for (const pair of value_runMetrics) {
            const value_runMetrics_key = pair[0]
            const value_runMetrics_value = pair[1]
            valueSerializer.writeNumber(value_runMetrics_key)
            text_RunMetrics_serializer.write(valueSerializer, value_runMetrics_value)
        }
    }
    public static read(buffer: DeserializerBase): text.LineMetrics {
        let valueDeserializer : DeserializerBase = buffer
        const startIndex_result : number = (valueDeserializer.readNumber() as number)
        const endIndex_result : number = (valueDeserializer.readNumber() as number)
        const ascent_result : number = (valueDeserializer.readNumber() as number)
        const descent_result : number = (valueDeserializer.readNumber() as number)
        const height_result : number = (valueDeserializer.readNumber() as number)
        const width_result : number = (valueDeserializer.readNumber() as number)
        const left_result : number = (valueDeserializer.readNumber() as number)
        const baseline_result : number = (valueDeserializer.readNumber() as number)
        const lineNumber_result : number = (valueDeserializer.readNumber() as number)
        const topHeight_result : number = (valueDeserializer.readNumber() as number)
        const runMetrics_buf_size : int32 = valueDeserializer.readInt32()
        let runMetrics_buf : Map<number, text.RunMetrics> = new Map<number, text.RunMetrics>()
        // TODO: TS map resize
        for (let runMetrics_buf_i = 0; runMetrics_buf_i < runMetrics_buf_size; runMetrics_buf_i++) {
            const runMetrics_buf_key : number = (valueDeserializer.readNumber() as number)
            const runMetrics_buf_value : text.RunMetrics = text_RunMetrics_serializer.read(valueDeserializer)
            runMetrics_buf.set(runMetrics_buf_key, runMetrics_buf_value)
        }
        const runMetrics_result : Map<number, text.RunMetrics> = runMetrics_buf
        let value : text.LineMetrics = ({startIndex: startIndex_result, endIndex: endIndex_result, ascent: ascent_result, descent: descent_result, height: height_result, width: width_result, left: left_result, baseline: baseline_result, lineNumber: lineNumber_result, topHeight: topHeight_result, runMetrics: runMetrics_result} as text.LineMetrics)
        return value
    }
}
export class text_PlaceholderSpan_serializer {
    public static write(buffer: SerializerBase, value: text.PlaceholderSpan): void {
        let valueSerializer : SerializerBase = buffer
        const value_width  = value.width
        valueSerializer.writeNumber(value_width)
        const value_height  = value.height
        valueSerializer.writeNumber(value_height)
        const value_align  = value.align
        valueSerializer.writeInt32(TypeChecker.text_PlaceholderAlignment_ToNumeric(value_align))
        const value_baseline  = value.baseline
        valueSerializer.writeInt32(TypeChecker.text_TextBaseline_ToNumeric(value_baseline))
        const value_baselineOffset  = value.baselineOffset
        valueSerializer.writeNumber(value_baselineOffset)
    }
    public static read(buffer: DeserializerBase): text.PlaceholderSpan {
        let valueDeserializer : DeserializerBase = buffer
        const width_result : number = (valueDeserializer.readNumber() as number)
        const height_result : number = (valueDeserializer.readNumber() as number)
        const align_result : text.PlaceholderAlignment = TypeChecker.text_PlaceholderAlignment_FromNumeric(valueDeserializer.readInt32())
        const baseline_result : text.TextBaseline = TypeChecker.text_TextBaseline_FromNumeric(valueDeserializer.readInt32())
        const baselineOffset_result : number = (valueDeserializer.readNumber() as number)
        let value : text.PlaceholderSpan = ({width: width_result, height: height_result, align: align_result, baseline: baseline_result, baselineOffset: baselineOffset_result} as text.PlaceholderSpan)
        return value
    }
}
export class text_RectStyle_serializer {
    public static write(buffer: SerializerBase, value: text.RectStyle): void {
        let valueSerializer : SerializerBase = buffer
        const value_color  = value.color
        common2D_Color_serializer.write(valueSerializer, value_color)
        const value_leftTopRadius  = value.leftTopRadius
        valueSerializer.writeNumber(value_leftTopRadius)
        const value_rightTopRadius  = value.rightTopRadius
        valueSerializer.writeNumber(value_rightTopRadius)
        const value_rightBottomRadius  = value.rightBottomRadius
        valueSerializer.writeNumber(value_rightBottomRadius)
        const value_leftBottomRadius  = value.leftBottomRadius
        valueSerializer.writeNumber(value_leftBottomRadius)
    }
    public static read(buffer: DeserializerBase): text.RectStyle {
        let valueDeserializer : DeserializerBase = buffer
        const color_result : common2D.Color = common2D_Color_serializer.read(valueDeserializer)
        const leftTopRadius_result : number = (valueDeserializer.readNumber() as number)
        const rightTopRadius_result : number = (valueDeserializer.readNumber() as number)
        const rightBottomRadius_result : number = (valueDeserializer.readNumber() as number)
        const leftBottomRadius_result : number = (valueDeserializer.readNumber() as number)
        let value : text.RectStyle = ({color: color_result, leftTopRadius: leftTopRadius_result, rightTopRadius: rightTopRadius_result, rightBottomRadius: rightBottomRadius_result, leftBottomRadius: leftBottomRadius_result} as text.RectStyle)
        return value
    }
}
export class text_StrutStyle_serializer {
    public static write(buffer: SerializerBase, value: text.StrutStyle): void {
        let valueSerializer : SerializerBase = buffer
        const value_fontFamilies  = value.fontFamilies
        let value_fontFamilies_type : int32 = RuntimeType.UNDEFINED
        value_fontFamilies_type = runtimeType(value_fontFamilies)
        valueSerializer.writeInt8((value_fontFamilies_type).toChar())
        if ((value_fontFamilies_type) != (RuntimeType.UNDEFINED)) {
            const value_fontFamilies_value  = value_fontFamilies!
            valueSerializer.writeInt32((value_fontFamilies_value.length).toInt())
            for (let value_fontFamilies_value_counter_i = 0; value_fontFamilies_value_counter_i < value_fontFamilies_value.length; value_fontFamilies_value_counter_i++) {
                const value_fontFamilies_value_element : string = value_fontFamilies_value[value_fontFamilies_value_counter_i]
                valueSerializer.writeString(value_fontFamilies_value_element)
            }
        }
        const value_fontStyle  = value.fontStyle
        let value_fontStyle_type : int32 = RuntimeType.UNDEFINED
        value_fontStyle_type = runtimeType(value_fontStyle)
        valueSerializer.writeInt8((value_fontStyle_type).toChar())
        if ((value_fontStyle_type) != (RuntimeType.UNDEFINED)) {
            const value_fontStyle_value  = (value_fontStyle as text.FontStyle)
            valueSerializer.writeInt32(TypeChecker.text_FontStyle_ToNumeric(value_fontStyle_value))
        }
        const value_fontWidth  = value.fontWidth
        let value_fontWidth_type : int32 = RuntimeType.UNDEFINED
        value_fontWidth_type = runtimeType(value_fontWidth)
        valueSerializer.writeInt8((value_fontWidth_type).toChar())
        if ((value_fontWidth_type) != (RuntimeType.UNDEFINED)) {
            const value_fontWidth_value  = (value_fontWidth as text.FontWidth)
            valueSerializer.writeInt32(TypeChecker.text_FontWidth_ToNumeric(value_fontWidth_value))
        }
        const value_fontWeight  = value.fontWeight
        let value_fontWeight_type : int32 = RuntimeType.UNDEFINED
        value_fontWeight_type = runtimeType(value_fontWeight)
        valueSerializer.writeInt8((value_fontWeight_type).toChar())
        if ((value_fontWeight_type) != (RuntimeType.UNDEFINED)) {
            const value_fontWeight_value  = (value_fontWeight as text.FontWeight)
            valueSerializer.writeInt32(TypeChecker.text_FontWeight_ToNumeric(value_fontWeight_value))
        }
        const value_fontSize  = value.fontSize
        let value_fontSize_type : int32 = RuntimeType.UNDEFINED
        value_fontSize_type = runtimeType(value_fontSize)
        valueSerializer.writeInt8((value_fontSize_type).toChar())
        if ((value_fontSize_type) != (RuntimeType.UNDEFINED)) {
            const value_fontSize_value  = value_fontSize!
            valueSerializer.writeNumber(value_fontSize_value)
        }
        const value_height  = value.height
        let value_height_type : int32 = RuntimeType.UNDEFINED
        value_height_type = runtimeType(value_height)
        valueSerializer.writeInt8((value_height_type).toChar())
        if ((value_height_type) != (RuntimeType.UNDEFINED)) {
            const value_height_value  = value_height!
            valueSerializer.writeNumber(value_height_value)
        }
        const value_leading  = value.leading
        let value_leading_type : int32 = RuntimeType.UNDEFINED
        value_leading_type = runtimeType(value_leading)
        valueSerializer.writeInt8((value_leading_type).toChar())
        if ((value_leading_type) != (RuntimeType.UNDEFINED)) {
            const value_leading_value  = value_leading!
            valueSerializer.writeNumber(value_leading_value)
        }
        const value_forceHeight  = value.forceHeight
        let value_forceHeight_type : int32 = RuntimeType.UNDEFINED
        value_forceHeight_type = runtimeType(value_forceHeight)
        valueSerializer.writeInt8((value_forceHeight_type).toChar())
        if ((value_forceHeight_type) != (RuntimeType.UNDEFINED)) {
            const value_forceHeight_value  = value_forceHeight!
            valueSerializer.writeBoolean(value_forceHeight_value)
        }
        const value_enabled  = value.enabled
        let value_enabled_type : int32 = RuntimeType.UNDEFINED
        value_enabled_type = runtimeType(value_enabled)
        valueSerializer.writeInt8((value_enabled_type).toChar())
        if ((value_enabled_type) != (RuntimeType.UNDEFINED)) {
            const value_enabled_value  = value_enabled!
            valueSerializer.writeBoolean(value_enabled_value)
        }
        const value_heightOverride  = value.heightOverride
        let value_heightOverride_type : int32 = RuntimeType.UNDEFINED
        value_heightOverride_type = runtimeType(value_heightOverride)
        valueSerializer.writeInt8((value_heightOverride_type).toChar())
        if ((value_heightOverride_type) != (RuntimeType.UNDEFINED)) {
            const value_heightOverride_value  = value_heightOverride!
            valueSerializer.writeBoolean(value_heightOverride_value)
        }
        const value_halfLeading  = value.halfLeading
        let value_halfLeading_type : int32 = RuntimeType.UNDEFINED
        value_halfLeading_type = runtimeType(value_halfLeading)
        valueSerializer.writeInt8((value_halfLeading_type).toChar())
        if ((value_halfLeading_type) != (RuntimeType.UNDEFINED)) {
            const value_halfLeading_value  = value_halfLeading!
            valueSerializer.writeBoolean(value_halfLeading_value)
        }
    }
    public static read(buffer: DeserializerBase): text.StrutStyle {
        let valueDeserializer : DeserializerBase = buffer
        const fontFamilies_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fontFamilies_buf : Array<string> | undefined
        if ((fontFamilies_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const fontFamilies_buf__length : int32 = valueDeserializer.readInt32()
            let fontFamilies_buf_ : Array<string> = new Array<string>(fontFamilies_buf__length)
            for (let fontFamilies_buf__i = 0; fontFamilies_buf__i < fontFamilies_buf__length; fontFamilies_buf__i++) {
                fontFamilies_buf_[fontFamilies_buf__i] = (valueDeserializer.readString() as string)
            }
            fontFamilies_buf = fontFamilies_buf_
        }
        const fontFamilies_result : Array<string> | undefined = fontFamilies_buf
        const fontStyle_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fontStyle_buf : text.FontStyle | undefined
        if ((fontStyle_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            fontStyle_buf = TypeChecker.text_FontStyle_FromNumeric(valueDeserializer.readInt32())
        }
        const fontStyle_result : text.FontStyle | undefined = fontStyle_buf
        const fontWidth_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fontWidth_buf : text.FontWidth | undefined
        if ((fontWidth_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            fontWidth_buf = TypeChecker.text_FontWidth_FromNumeric(valueDeserializer.readInt32())
        }
        const fontWidth_result : text.FontWidth | undefined = fontWidth_buf
        const fontWeight_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fontWeight_buf : text.FontWeight | undefined
        if ((fontWeight_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            fontWeight_buf = TypeChecker.text_FontWeight_FromNumeric(valueDeserializer.readInt32())
        }
        const fontWeight_result : text.FontWeight | undefined = fontWeight_buf
        const fontSize_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fontSize_buf : number | undefined
        if ((fontSize_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            fontSize_buf = (valueDeserializer.readNumber() as number)
        }
        const fontSize_result : number | undefined = fontSize_buf
        const height_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let height_buf : number | undefined
        if ((height_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            height_buf = (valueDeserializer.readNumber() as number)
        }
        const height_result : number | undefined = height_buf
        const leading_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let leading_buf : number | undefined
        if ((leading_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            leading_buf = (valueDeserializer.readNumber() as number)
        }
        const leading_result : number | undefined = leading_buf
        const forceHeight_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let forceHeight_buf : boolean | undefined
        if ((forceHeight_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            forceHeight_buf = valueDeserializer.readBoolean()
        }
        const forceHeight_result : boolean | undefined = forceHeight_buf
        const enabled_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let enabled_buf : boolean | undefined
        if ((enabled_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            enabled_buf = valueDeserializer.readBoolean()
        }
        const enabled_result : boolean | undefined = enabled_buf
        const heightOverride_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let heightOverride_buf : boolean | undefined
        if ((heightOverride_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            heightOverride_buf = valueDeserializer.readBoolean()
        }
        const heightOverride_result : boolean | undefined = heightOverride_buf
        const halfLeading_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let halfLeading_buf : boolean | undefined
        if ((halfLeading_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            halfLeading_buf = valueDeserializer.readBoolean()
        }
        const halfLeading_result : boolean | undefined = halfLeading_buf
        let value : text.StrutStyle = ({fontFamilies: fontFamilies_result, fontStyle: fontStyle_result, fontWidth: fontWidth_result, fontWeight: fontWeight_result, fontSize: fontSize_result, height: height_result, leading: leading_result, forceHeight: forceHeight_result, enabled: enabled_result, heightOverride: heightOverride_result, halfLeading: halfLeading_result} as text.StrutStyle)
        return value
    }
}
export class text_TextBox_serializer {
    public static write(buffer: SerializerBase, value: text.TextBox): void {
        let valueSerializer : SerializerBase = buffer
        const value_rect  = value.rect
        common2D_Rect_serializer.write(valueSerializer, value_rect)
        const value_direction  = value.direction
        valueSerializer.writeInt32(TypeChecker.text_TextDirection_ToNumeric(value_direction))
    }
    public static read(buffer: DeserializerBase): text.TextBox {
        let valueDeserializer : DeserializerBase = buffer
        const rect_result : common2D.Rect = common2D_Rect_serializer.read(valueDeserializer)
        const direction_result : text.TextDirection = TypeChecker.text_TextDirection_FromNumeric(valueDeserializer.readInt32())
        let value : text.TextBox = ({rect: rect_result, direction: direction_result} as text.TextBox)
        return value
    }
}
export class text_Decoration_serializer {
    public static write(buffer: SerializerBase, value: text.Decoration): void {
        let valueSerializer : SerializerBase = buffer
        const value_textDecoration  = value.textDecoration
        let value_textDecoration_type : int32 = RuntimeType.UNDEFINED
        value_textDecoration_type = runtimeType(value_textDecoration)
        valueSerializer.writeInt8((value_textDecoration_type).toChar())
        if ((value_textDecoration_type) != (RuntimeType.UNDEFINED)) {
            const value_textDecoration_value  = (value_textDecoration as text.TextDecorationType)
            valueSerializer.writeInt32(TypeChecker.text_TextDecorationType_ToNumeric(value_textDecoration_value))
        }
        const value_color  = value.color
        let value_color_type : int32 = RuntimeType.UNDEFINED
        value_color_type = runtimeType(value_color)
        valueSerializer.writeInt8((value_color_type).toChar())
        if ((value_color_type) != (RuntimeType.UNDEFINED)) {
            const value_color_value  = value_color!
            common2D_Color_serializer.write(valueSerializer, value_color_value)
        }
        const value_decorationStyle  = value.decorationStyle
        let value_decorationStyle_type : int32 = RuntimeType.UNDEFINED
        value_decorationStyle_type = runtimeType(value_decorationStyle)
        valueSerializer.writeInt8((value_decorationStyle_type).toChar())
        if ((value_decorationStyle_type) != (RuntimeType.UNDEFINED)) {
            const value_decorationStyle_value  = (value_decorationStyle as text.TextDecorationStyle)
            valueSerializer.writeInt32(TypeChecker.text_TextDecorationStyle_ToNumeric(value_decorationStyle_value))
        }
        const value_decorationThicknessScale  = value.decorationThicknessScale
        let value_decorationThicknessScale_type : int32 = RuntimeType.UNDEFINED
        value_decorationThicknessScale_type = runtimeType(value_decorationThicknessScale)
        valueSerializer.writeInt8((value_decorationThicknessScale_type).toChar())
        if ((value_decorationThicknessScale_type) != (RuntimeType.UNDEFINED)) {
            const value_decorationThicknessScale_value  = value_decorationThicknessScale!
            valueSerializer.writeNumber(value_decorationThicknessScale_value)
        }
    }
    public static read(buffer: DeserializerBase): text.Decoration {
        let valueDeserializer : DeserializerBase = buffer
        const textDecoration_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let textDecoration_buf : text.TextDecorationType | undefined
        if ((textDecoration_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            textDecoration_buf = TypeChecker.text_TextDecorationType_FromNumeric(valueDeserializer.readInt32())
        }
        const textDecoration_result : text.TextDecorationType | undefined = textDecoration_buf
        const color_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let color_buf : common2D.Color | undefined
        if ((color_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            color_buf = common2D_Color_serializer.read(valueDeserializer)
        }
        const color_result : common2D.Color | undefined = color_buf
        const decorationStyle_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let decorationStyle_buf : text.TextDecorationStyle | undefined
        if ((decorationStyle_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            decorationStyle_buf = TypeChecker.text_TextDecorationStyle_FromNumeric(valueDeserializer.readInt32())
        }
        const decorationStyle_result : text.TextDecorationStyle | undefined = decorationStyle_buf
        const decorationThicknessScale_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let decorationThicknessScale_buf : number | undefined
        if ((decorationThicknessScale_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            decorationThicknessScale_buf = (valueDeserializer.readNumber() as number)
        }
        const decorationThicknessScale_result : number | undefined = decorationThicknessScale_buf
        let value : text.Decoration = ({textDecoration: textDecoration_result, color: color_result, decorationStyle: decorationStyle_result, decorationThicknessScale: decorationThicknessScale_result} as text.Decoration)
        return value
    }
}
export class text_TextShadow_serializer {
    public static write(buffer: SerializerBase, value: text.TextShadow): void {
        let valueSerializer : SerializerBase = buffer
        const value_color  = value.color
        let value_color_type : int32 = RuntimeType.UNDEFINED
        value_color_type = runtimeType(value_color)
        valueSerializer.writeInt8((value_color_type).toChar())
        if ((value_color_type) != (RuntimeType.UNDEFINED)) {
            const value_color_value  = value_color!
            common2D_Color_serializer.write(valueSerializer, value_color_value)
        }
        const value_point  = value.point
        let value_point_type : int32 = RuntimeType.UNDEFINED
        value_point_type = runtimeType(value_point)
        valueSerializer.writeInt8((value_point_type).toChar())
        if ((value_point_type) != (RuntimeType.UNDEFINED)) {
            const value_point_value  = value_point!
            common2D_Point_serializer.write(valueSerializer, value_point_value)
        }
        const value_blurRadius  = value.blurRadius
        let value_blurRadius_type : int32 = RuntimeType.UNDEFINED
        value_blurRadius_type = runtimeType(value_blurRadius)
        valueSerializer.writeInt8((value_blurRadius_type).toChar())
        if ((value_blurRadius_type) != (RuntimeType.UNDEFINED)) {
            const value_blurRadius_value  = value_blurRadius!
            valueSerializer.writeNumber(value_blurRadius_value)
        }
    }
    public static read(buffer: DeserializerBase): text.TextShadow {
        let valueDeserializer : DeserializerBase = buffer
        const color_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let color_buf : common2D.Color | undefined
        if ((color_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            color_buf = common2D_Color_serializer.read(valueDeserializer)
        }
        const color_result : common2D.Color | undefined = color_buf
        const point_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let point_buf : common2D.Point | undefined
        if ((point_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            point_buf = common2D_Point_serializer.read(valueDeserializer)
        }
        const point_result : common2D.Point | undefined = point_buf
        const blurRadius_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let blurRadius_buf : number | undefined
        if ((blurRadius_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            blurRadius_buf = (valueDeserializer.readNumber() as number)
        }
        const blurRadius_result : number | undefined = blurRadius_buf
        let value : text.TextShadow = ({color: color_result, point: point_result, blurRadius: blurRadius_result} as text.TextShadow)
        return value
    }
}
export class text_TextStyle_serializer {
    public static write(buffer: SerializerBase, value: text.TextStyle): void {
        let valueSerializer : SerializerBase = buffer
        const value_decoration  = value.decoration
        let value_decoration_type : int32 = RuntimeType.UNDEFINED
        value_decoration_type = runtimeType(value_decoration)
        valueSerializer.writeInt8((value_decoration_type).toChar())
        if ((value_decoration_type) != (RuntimeType.UNDEFINED)) {
            const value_decoration_value  = value_decoration!
            text_Decoration_serializer.write(valueSerializer, value_decoration_value)
        }
        const value_color  = value.color
        let value_color_type : int32 = RuntimeType.UNDEFINED
        value_color_type = runtimeType(value_color)
        valueSerializer.writeInt8((value_color_type).toChar())
        if ((value_color_type) != (RuntimeType.UNDEFINED)) {
            const value_color_value  = value_color!
            common2D_Color_serializer.write(valueSerializer, value_color_value)
        }
        const value_fontWeight  = value.fontWeight
        let value_fontWeight_type : int32 = RuntimeType.UNDEFINED
        value_fontWeight_type = runtimeType(value_fontWeight)
        valueSerializer.writeInt8((value_fontWeight_type).toChar())
        if ((value_fontWeight_type) != (RuntimeType.UNDEFINED)) {
            const value_fontWeight_value  = (value_fontWeight as text.FontWeight)
            valueSerializer.writeInt32(TypeChecker.text_FontWeight_ToNumeric(value_fontWeight_value))
        }
        const value_fontStyle  = value.fontStyle
        let value_fontStyle_type : int32 = RuntimeType.UNDEFINED
        value_fontStyle_type = runtimeType(value_fontStyle)
        valueSerializer.writeInt8((value_fontStyle_type).toChar())
        if ((value_fontStyle_type) != (RuntimeType.UNDEFINED)) {
            const value_fontStyle_value  = (value_fontStyle as text.FontStyle)
            valueSerializer.writeInt32(TypeChecker.text_FontStyle_ToNumeric(value_fontStyle_value))
        }
        const value_baseline  = value.baseline
        let value_baseline_type : int32 = RuntimeType.UNDEFINED
        value_baseline_type = runtimeType(value_baseline)
        valueSerializer.writeInt8((value_baseline_type).toChar())
        if ((value_baseline_type) != (RuntimeType.UNDEFINED)) {
            const value_baseline_value  = (value_baseline as text.TextBaseline)
            valueSerializer.writeInt32(TypeChecker.text_TextBaseline_ToNumeric(value_baseline_value))
        }
        const value_fontFamilies  = value.fontFamilies
        let value_fontFamilies_type : int32 = RuntimeType.UNDEFINED
        value_fontFamilies_type = runtimeType(value_fontFamilies)
        valueSerializer.writeInt8((value_fontFamilies_type).toChar())
        if ((value_fontFamilies_type) != (RuntimeType.UNDEFINED)) {
            const value_fontFamilies_value  = value_fontFamilies!
            valueSerializer.writeInt32((value_fontFamilies_value.length).toInt())
            for (let value_fontFamilies_value_counter_i = 0; value_fontFamilies_value_counter_i < value_fontFamilies_value.length; value_fontFamilies_value_counter_i++) {
                const value_fontFamilies_value_element : string = value_fontFamilies_value[value_fontFamilies_value_counter_i]
                valueSerializer.writeString(value_fontFamilies_value_element)
            }
        }
        const value_fontSize  = value.fontSize
        let value_fontSize_type : int32 = RuntimeType.UNDEFINED
        value_fontSize_type = runtimeType(value_fontSize)
        valueSerializer.writeInt8((value_fontSize_type).toChar())
        if ((value_fontSize_type) != (RuntimeType.UNDEFINED)) {
            const value_fontSize_value  = value_fontSize!
            valueSerializer.writeNumber(value_fontSize_value)
        }
        const value_letterSpacing  = value.letterSpacing
        let value_letterSpacing_type : int32 = RuntimeType.UNDEFINED
        value_letterSpacing_type = runtimeType(value_letterSpacing)
        valueSerializer.writeInt8((value_letterSpacing_type).toChar())
        if ((value_letterSpacing_type) != (RuntimeType.UNDEFINED)) {
            const value_letterSpacing_value  = value_letterSpacing!
            valueSerializer.writeNumber(value_letterSpacing_value)
        }
        const value_wordSpacing  = value.wordSpacing
        let value_wordSpacing_type : int32 = RuntimeType.UNDEFINED
        value_wordSpacing_type = runtimeType(value_wordSpacing)
        valueSerializer.writeInt8((value_wordSpacing_type).toChar())
        if ((value_wordSpacing_type) != (RuntimeType.UNDEFINED)) {
            const value_wordSpacing_value  = value_wordSpacing!
            valueSerializer.writeNumber(value_wordSpacing_value)
        }
        const value_heightScale  = value.heightScale
        let value_heightScale_type : int32 = RuntimeType.UNDEFINED
        value_heightScale_type = runtimeType(value_heightScale)
        valueSerializer.writeInt8((value_heightScale_type).toChar())
        if ((value_heightScale_type) != (RuntimeType.UNDEFINED)) {
            const value_heightScale_value  = value_heightScale!
            valueSerializer.writeNumber(value_heightScale_value)
        }
        const value_halfLeading  = value.halfLeading
        let value_halfLeading_type : int32 = RuntimeType.UNDEFINED
        value_halfLeading_type = runtimeType(value_halfLeading)
        valueSerializer.writeInt8((value_halfLeading_type).toChar())
        if ((value_halfLeading_type) != (RuntimeType.UNDEFINED)) {
            const value_halfLeading_value  = value_halfLeading!
            valueSerializer.writeBoolean(value_halfLeading_value)
        }
        const value_heightOnly  = value.heightOnly
        let value_heightOnly_type : int32 = RuntimeType.UNDEFINED
        value_heightOnly_type = runtimeType(value_heightOnly)
        valueSerializer.writeInt8((value_heightOnly_type).toChar())
        if ((value_heightOnly_type) != (RuntimeType.UNDEFINED)) {
            const value_heightOnly_value  = value_heightOnly!
            valueSerializer.writeBoolean(value_heightOnly_value)
        }
        const value_ellipsis  = value.ellipsis
        let value_ellipsis_type : int32 = RuntimeType.UNDEFINED
        value_ellipsis_type = runtimeType(value_ellipsis)
        valueSerializer.writeInt8((value_ellipsis_type).toChar())
        if ((value_ellipsis_type) != (RuntimeType.UNDEFINED)) {
            const value_ellipsis_value  = value_ellipsis!
            valueSerializer.writeString(value_ellipsis_value)
        }
        const value_ellipsisMode  = value.ellipsisMode
        let value_ellipsisMode_type : int32 = RuntimeType.UNDEFINED
        value_ellipsisMode_type = runtimeType(value_ellipsisMode)
        valueSerializer.writeInt8((value_ellipsisMode_type).toChar())
        if ((value_ellipsisMode_type) != (RuntimeType.UNDEFINED)) {
            const value_ellipsisMode_value  = (value_ellipsisMode as text.EllipsisMode)
            valueSerializer.writeInt32(TypeChecker.text_EllipsisMode_ToNumeric(value_ellipsisMode_value))
        }
        const value_locale  = value.locale
        let value_locale_type : int32 = RuntimeType.UNDEFINED
        value_locale_type = runtimeType(value_locale)
        valueSerializer.writeInt8((value_locale_type).toChar())
        if ((value_locale_type) != (RuntimeType.UNDEFINED)) {
            const value_locale_value  = value_locale!
            valueSerializer.writeString(value_locale_value)
        }
        const value_baselineShift  = value.baselineShift
        let value_baselineShift_type : int32 = RuntimeType.UNDEFINED
        value_baselineShift_type = runtimeType(value_baselineShift)
        valueSerializer.writeInt8((value_baselineShift_type).toChar())
        if ((value_baselineShift_type) != (RuntimeType.UNDEFINED)) {
            const value_baselineShift_value  = value_baselineShift!
            valueSerializer.writeNumber(value_baselineShift_value)
        }
        const value_fontFeatures  = value.fontFeatures
        let value_fontFeatures_type : int32 = RuntimeType.UNDEFINED
        value_fontFeatures_type = runtimeType(value_fontFeatures)
        valueSerializer.writeInt8((value_fontFeatures_type).toChar())
        if ((value_fontFeatures_type) != (RuntimeType.UNDEFINED)) {
            const value_fontFeatures_value  = value_fontFeatures!
            valueSerializer.writeInt32((value_fontFeatures_value.length).toInt())
            for (let value_fontFeatures_value_counter_i = 0; value_fontFeatures_value_counter_i < value_fontFeatures_value.length; value_fontFeatures_value_counter_i++) {
                const value_fontFeatures_value_element : text.FontFeature = value_fontFeatures_value[value_fontFeatures_value_counter_i]
                text_FontFeature_serializer.write(valueSerializer, value_fontFeatures_value_element)
            }
        }
        const value_textShadows  = value.textShadows
        let value_textShadows_type : int32 = RuntimeType.UNDEFINED
        value_textShadows_type = runtimeType(value_textShadows)
        valueSerializer.writeInt8((value_textShadows_type).toChar())
        if ((value_textShadows_type) != (RuntimeType.UNDEFINED)) {
            const value_textShadows_value  = value_textShadows!
            valueSerializer.writeInt32((value_textShadows_value.length).toInt())
            for (let value_textShadows_value_counter_i = 0; value_textShadows_value_counter_i < value_textShadows_value.length; value_textShadows_value_counter_i++) {
                const value_textShadows_value_element : text.TextShadow = value_textShadows_value[value_textShadows_value_counter_i]
                text_TextShadow_serializer.write(valueSerializer, value_textShadows_value_element)
            }
        }
        const value_backgroundRect  = value.backgroundRect
        let value_backgroundRect_type : int32 = RuntimeType.UNDEFINED
        value_backgroundRect_type = runtimeType(value_backgroundRect)
        valueSerializer.writeInt8((value_backgroundRect_type).toChar())
        if ((value_backgroundRect_type) != (RuntimeType.UNDEFINED)) {
            const value_backgroundRect_value  = value_backgroundRect!
            text_RectStyle_serializer.write(valueSerializer, value_backgroundRect_value)
        }
        const value_fontVariations  = value.fontVariations
        let value_fontVariations_type : int32 = RuntimeType.UNDEFINED
        value_fontVariations_type = runtimeType(value_fontVariations)
        valueSerializer.writeInt8((value_fontVariations_type).toChar())
        if ((value_fontVariations_type) != (RuntimeType.UNDEFINED)) {
            const value_fontVariations_value  = value_fontVariations!
            valueSerializer.writeInt32((value_fontVariations_value.length).toInt())
            for (let value_fontVariations_value_counter_i = 0; value_fontVariations_value_counter_i < value_fontVariations_value.length; value_fontVariations_value_counter_i++) {
                const value_fontVariations_value_element : text.FontVariation = value_fontVariations_value[value_fontVariations_value_counter_i]
                text_FontVariation_serializer.write(valueSerializer, value_fontVariations_value_element)
            }
        }
    }
    public static read(buffer: DeserializerBase): text.TextStyle {
        let valueDeserializer : DeserializerBase = buffer
        const decoration_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let decoration_buf : text.Decoration | undefined
        if ((decoration_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            decoration_buf = text_Decoration_serializer.read(valueDeserializer)
        }
        const decoration_result : text.Decoration | undefined = decoration_buf
        const color_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let color_buf : common2D.Color | undefined
        if ((color_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            color_buf = common2D_Color_serializer.read(valueDeserializer)
        }
        const color_result : common2D.Color | undefined = color_buf
        const fontWeight_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fontWeight_buf : text.FontWeight | undefined
        if ((fontWeight_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            fontWeight_buf = TypeChecker.text_FontWeight_FromNumeric(valueDeserializer.readInt32())
        }
        const fontWeight_result : text.FontWeight | undefined = fontWeight_buf
        const fontStyle_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fontStyle_buf : text.FontStyle | undefined
        if ((fontStyle_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            fontStyle_buf = TypeChecker.text_FontStyle_FromNumeric(valueDeserializer.readInt32())
        }
        const fontStyle_result : text.FontStyle | undefined = fontStyle_buf
        const baseline_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let baseline_buf : text.TextBaseline | undefined
        if ((baseline_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            baseline_buf = TypeChecker.text_TextBaseline_FromNumeric(valueDeserializer.readInt32())
        }
        const baseline_result : text.TextBaseline | undefined = baseline_buf
        const fontFamilies_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fontFamilies_buf : Array<string> | undefined
        if ((fontFamilies_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const fontFamilies_buf__length : int32 = valueDeserializer.readInt32()
            let fontFamilies_buf_ : Array<string> = new Array<string>(fontFamilies_buf__length)
            for (let fontFamilies_buf__i = 0; fontFamilies_buf__i < fontFamilies_buf__length; fontFamilies_buf__i++) {
                fontFamilies_buf_[fontFamilies_buf__i] = (valueDeserializer.readString() as string)
            }
            fontFamilies_buf = fontFamilies_buf_
        }
        const fontFamilies_result : Array<string> | undefined = fontFamilies_buf
        const fontSize_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fontSize_buf : number | undefined
        if ((fontSize_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            fontSize_buf = (valueDeserializer.readNumber() as number)
        }
        const fontSize_result : number | undefined = fontSize_buf
        const letterSpacing_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let letterSpacing_buf : number | undefined
        if ((letterSpacing_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            letterSpacing_buf = (valueDeserializer.readNumber() as number)
        }
        const letterSpacing_result : number | undefined = letterSpacing_buf
        const wordSpacing_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let wordSpacing_buf : number | undefined
        if ((wordSpacing_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            wordSpacing_buf = (valueDeserializer.readNumber() as number)
        }
        const wordSpacing_result : number | undefined = wordSpacing_buf
        const heightScale_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let heightScale_buf : number | undefined
        if ((heightScale_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            heightScale_buf = (valueDeserializer.readNumber() as number)
        }
        const heightScale_result : number | undefined = heightScale_buf
        const halfLeading_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let halfLeading_buf : boolean | undefined
        if ((halfLeading_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            halfLeading_buf = valueDeserializer.readBoolean()
        }
        const halfLeading_result : boolean | undefined = halfLeading_buf
        const heightOnly_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let heightOnly_buf : boolean | undefined
        if ((heightOnly_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            heightOnly_buf = valueDeserializer.readBoolean()
        }
        const heightOnly_result : boolean | undefined = heightOnly_buf
        const ellipsis_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let ellipsis_buf : string | undefined
        if ((ellipsis_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            ellipsis_buf = (valueDeserializer.readString() as string)
        }
        const ellipsis_result : string | undefined = ellipsis_buf
        const ellipsisMode_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let ellipsisMode_buf : text.EllipsisMode | undefined
        if ((ellipsisMode_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            ellipsisMode_buf = TypeChecker.text_EllipsisMode_FromNumeric(valueDeserializer.readInt32())
        }
        const ellipsisMode_result : text.EllipsisMode | undefined = ellipsisMode_buf
        const locale_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let locale_buf : string | undefined
        if ((locale_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            locale_buf = (valueDeserializer.readString() as string)
        }
        const locale_result : string | undefined = locale_buf
        const baselineShift_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let baselineShift_buf : number | undefined
        if ((baselineShift_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            baselineShift_buf = (valueDeserializer.readNumber() as number)
        }
        const baselineShift_result : number | undefined = baselineShift_buf
        const fontFeatures_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fontFeatures_buf : Array<text.FontFeature> | undefined
        if ((fontFeatures_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const fontFeatures_buf__length : int32 = valueDeserializer.readInt32()
            let fontFeatures_buf_ : Array<text.FontFeature> = new Array<text.FontFeature>(fontFeatures_buf__length)
            for (let fontFeatures_buf__i = 0; fontFeatures_buf__i < fontFeatures_buf__length; fontFeatures_buf__i++) {
                fontFeatures_buf_[fontFeatures_buf__i] = text_FontFeature_serializer.read(valueDeserializer)
            }
            fontFeatures_buf = fontFeatures_buf_
        }
        const fontFeatures_result : Array<text.FontFeature> | undefined = fontFeatures_buf
        const textShadows_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let textShadows_buf : Array<text.TextShadow> | undefined
        if ((textShadows_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const textShadows_buf__length : int32 = valueDeserializer.readInt32()
            let textShadows_buf_ : Array<text.TextShadow> = new Array<text.TextShadow>(textShadows_buf__length)
            for (let textShadows_buf__i = 0; textShadows_buf__i < textShadows_buf__length; textShadows_buf__i++) {
                textShadows_buf_[textShadows_buf__i] = text_TextShadow_serializer.read(valueDeserializer)
            }
            textShadows_buf = textShadows_buf_
        }
        const textShadows_result : Array<text.TextShadow> | undefined = textShadows_buf
        const backgroundRect_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundRect_buf : text.RectStyle | undefined
        if ((backgroundRect_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            backgroundRect_buf = text_RectStyle_serializer.read(valueDeserializer)
        }
        const backgroundRect_result : text.RectStyle | undefined = backgroundRect_buf
        const fontVariations_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fontVariations_buf : Array<text.FontVariation> | undefined
        if ((fontVariations_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const fontVariations_buf__length : int32 = valueDeserializer.readInt32()
            let fontVariations_buf_ : Array<text.FontVariation> = new Array<text.FontVariation>(fontVariations_buf__length)
            for (let fontVariations_buf__i = 0; fontVariations_buf__i < fontVariations_buf__length; fontVariations_buf__i++) {
                fontVariations_buf_[fontVariations_buf__i] = text_FontVariation_serializer.read(valueDeserializer)
            }
            fontVariations_buf = fontVariations_buf_
        }
        const fontVariations_result : Array<text.FontVariation> | undefined = fontVariations_buf
        let value : text.TextStyle = ({decoration: decoration_result, color: color_result, fontWeight: fontWeight_result, fontStyle: fontStyle_result, baseline: baseline_result, fontFamilies: fontFamilies_result, fontSize: fontSize_result, letterSpacing: letterSpacing_result, wordSpacing: wordSpacing_result, heightScale: heightScale_result, halfLeading: halfLeading_result, heightOnly: heightOnly_result, ellipsis: ellipsis_result, ellipsisMode: ellipsisMode_result, locale: locale_result, baselineShift: baselineShift_result, fontFeatures: fontFeatures_result, textShadows: textShadows_result, backgroundRect: backgroundRect_result, fontVariations: fontVariations_result} as text.TextStyle)
        return value
    }
}
export class text_ParagraphStyle_serializer {
    public static write(buffer: SerializerBase, value: text.ParagraphStyle): void {
        let valueSerializer : SerializerBase = buffer
        const value_textStyle  = value.textStyle
        let value_textStyle_type : int32 = RuntimeType.UNDEFINED
        value_textStyle_type = runtimeType(value_textStyle)
        valueSerializer.writeInt8((value_textStyle_type).toChar())
        if ((value_textStyle_type) != (RuntimeType.UNDEFINED)) {
            const value_textStyle_value  = value_textStyle!
            text_TextStyle_serializer.write(valueSerializer, value_textStyle_value)
        }
        const value_textDirection  = value.textDirection
        let value_textDirection_type : int32 = RuntimeType.UNDEFINED
        value_textDirection_type = runtimeType(value_textDirection)
        valueSerializer.writeInt8((value_textDirection_type).toChar())
        if ((value_textDirection_type) != (RuntimeType.UNDEFINED)) {
            const value_textDirection_value  = (value_textDirection as text.TextDirection)
            valueSerializer.writeInt32(TypeChecker.text_TextDirection_ToNumeric(value_textDirection_value))
        }
        const value_align  = value.align
        let value_align_type : int32 = RuntimeType.UNDEFINED
        value_align_type = runtimeType(value_align)
        valueSerializer.writeInt8((value_align_type).toChar())
        if ((value_align_type) != (RuntimeType.UNDEFINED)) {
            const value_align_value  = (value_align as text.TextAlign)
            valueSerializer.writeInt32(TypeChecker.text_TextAlign_ToNumeric(value_align_value))
        }
        const value_wordBreak  = value.wordBreak
        let value_wordBreak_type : int32 = RuntimeType.UNDEFINED
        value_wordBreak_type = runtimeType(value_wordBreak)
        valueSerializer.writeInt8((value_wordBreak_type).toChar())
        if ((value_wordBreak_type) != (RuntimeType.UNDEFINED)) {
            const value_wordBreak_value  = (value_wordBreak as text.WordBreak)
            valueSerializer.writeInt32(TypeChecker.text_WordBreak_ToNumeric(value_wordBreak_value))
        }
        const value_maxLines  = value.maxLines
        let value_maxLines_type : int32 = RuntimeType.UNDEFINED
        value_maxLines_type = runtimeType(value_maxLines)
        valueSerializer.writeInt8((value_maxLines_type).toChar())
        if ((value_maxLines_type) != (RuntimeType.UNDEFINED)) {
            const value_maxLines_value  = value_maxLines!
            valueSerializer.writeNumber(value_maxLines_value)
        }
        const value_breakStrategy  = value.breakStrategy
        let value_breakStrategy_type : int32 = RuntimeType.UNDEFINED
        value_breakStrategy_type = runtimeType(value_breakStrategy)
        valueSerializer.writeInt8((value_breakStrategy_type).toChar())
        if ((value_breakStrategy_type) != (RuntimeType.UNDEFINED)) {
            const value_breakStrategy_value  = (value_breakStrategy as text.BreakStrategy)
            valueSerializer.writeInt32(TypeChecker.text_BreakStrategy_ToNumeric(value_breakStrategy_value))
        }
        const value_strutStyle  = value.strutStyle
        let value_strutStyle_type : int32 = RuntimeType.UNDEFINED
        value_strutStyle_type = runtimeType(value_strutStyle)
        valueSerializer.writeInt8((value_strutStyle_type).toChar())
        if ((value_strutStyle_type) != (RuntimeType.UNDEFINED)) {
            const value_strutStyle_value  = value_strutStyle!
            text_StrutStyle_serializer.write(valueSerializer, value_strutStyle_value)
        }
        const value_textHeightBehavior  = value.textHeightBehavior
        let value_textHeightBehavior_type : int32 = RuntimeType.UNDEFINED
        value_textHeightBehavior_type = runtimeType(value_textHeightBehavior)
        valueSerializer.writeInt8((value_textHeightBehavior_type).toChar())
        if ((value_textHeightBehavior_type) != (RuntimeType.UNDEFINED)) {
            const value_textHeightBehavior_value  = (value_textHeightBehavior as text.TextHeightBehavior)
            valueSerializer.writeInt32(TypeChecker.text_TextHeightBehavior_ToNumeric(value_textHeightBehavior_value))
        }
        const value_tab  = value.tab
        let value_tab_type : int32 = RuntimeType.UNDEFINED
        value_tab_type = runtimeType(value_tab)
        valueSerializer.writeInt8((value_tab_type).toChar())
        if ((value_tab_type) != (RuntimeType.UNDEFINED)) {
            const value_tab_value  = value_tab!
            text_TextTab_serializer.write(valueSerializer, value_tab_value)
        }
    }
    public static read(buffer: DeserializerBase): text.ParagraphStyle {
        let valueDeserializer : DeserializerBase = buffer
        const textStyle_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let textStyle_buf : text.TextStyle | undefined
        if ((textStyle_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            textStyle_buf = text_TextStyle_serializer.read(valueDeserializer)
        }
        const textStyle_result : text.TextStyle | undefined = textStyle_buf
        const textDirection_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let textDirection_buf : text.TextDirection | undefined
        if ((textDirection_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            textDirection_buf = TypeChecker.text_TextDirection_FromNumeric(valueDeserializer.readInt32())
        }
        const textDirection_result : text.TextDirection | undefined = textDirection_buf
        const align_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let align_buf : text.TextAlign | undefined
        if ((align_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            align_buf = TypeChecker.text_TextAlign_FromNumeric(valueDeserializer.readInt32())
        }
        const align_result : text.TextAlign | undefined = align_buf
        const wordBreak_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let wordBreak_buf : text.WordBreak | undefined
        if ((wordBreak_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            wordBreak_buf = TypeChecker.text_WordBreak_FromNumeric(valueDeserializer.readInt32())
        }
        const wordBreak_result : text.WordBreak | undefined = wordBreak_buf
        const maxLines_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let maxLines_buf : number | undefined
        if ((maxLines_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            maxLines_buf = (valueDeserializer.readNumber() as number)
        }
        const maxLines_result : number | undefined = maxLines_buf
        const breakStrategy_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let breakStrategy_buf : text.BreakStrategy | undefined
        if ((breakStrategy_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            breakStrategy_buf = TypeChecker.text_BreakStrategy_FromNumeric(valueDeserializer.readInt32())
        }
        const breakStrategy_result : text.BreakStrategy | undefined = breakStrategy_buf
        const strutStyle_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let strutStyle_buf : text.StrutStyle | undefined
        if ((strutStyle_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            strutStyle_buf = text_StrutStyle_serializer.read(valueDeserializer)
        }
        const strutStyle_result : text.StrutStyle | undefined = strutStyle_buf
        const textHeightBehavior_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let textHeightBehavior_buf : text.TextHeightBehavior | undefined
        if ((textHeightBehavior_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            textHeightBehavior_buf = TypeChecker.text_TextHeightBehavior_FromNumeric(valueDeserializer.readInt32())
        }
        const textHeightBehavior_result : text.TextHeightBehavior | undefined = textHeightBehavior_buf
        const tab_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let tab_buf : text.TextTab | undefined
        if ((tab_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            tab_buf = text_TextTab_serializer.read(valueDeserializer)
        }
        const tab_result : text.TextTab | undefined = tab_buf
        let value : text.ParagraphStyle = ({textStyle: textStyle_result, textDirection: textDirection_result, align: align_result, wordBreak: wordBreak_result, maxLines: maxLines_result, breakStrategy: breakStrategy_result, strutStyle: strutStyle_result, textHeightBehavior: textHeightBehavior_result, tab: tab_result} as text.ParagraphStyle)
        return value
    }
}
export class text_RunMetrics_serializer {
    public static write(buffer: SerializerBase, value: text.RunMetrics): void {
        let valueSerializer : SerializerBase = buffer
        const value_textStyle  = value.textStyle
        text_TextStyle_serializer.write(valueSerializer, value_textStyle)
        const value_fontMetrics  = value.fontMetrics
        drawing_FontMetrics_serializer.write(valueSerializer, value_fontMetrics)
    }
    public static read(buffer: DeserializerBase): text.RunMetrics {
        let valueDeserializer : DeserializerBase = buffer
        const textStyle_result : text.TextStyle = text_TextStyle_serializer.read(valueDeserializer)
        const fontMetrics_result : drawing.FontMetrics = drawing_FontMetrics_serializer.read(valueDeserializer)
        let value : text.RunMetrics = ({textStyle: textStyle_result, fontMetrics: fontMetrics_result} as text.RunMetrics)
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
            let path_type : int32 = RuntimeType.UNDEFINED
            path_type = runtimeType(path)
            if (RuntimeType.STRING == path_type) {
                thisSerializer.writeInt8((0).toChar())
                const path_0  = path as string
                thisSerializer.writeString(path_0)
            }
            else if (RuntimeType.OBJECT == path_type) {
                thisSerializer.writeInt8((1).toChar())
                const path_1  = path as Resource
                Resource_serializer.write(thisSerializer, path_1)
            }
            ArkUIGeneratedNativeModule._text_FontCollection_loadFontSync(this.peer!.ptr, name, thisSerializer.asBuffer(), thisSerializer.length())
            thisSerializer.release()
        }
        private loadFont_serialize(name: string, path: string | Resource): Promise<void> {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            let path_type : int32 = RuntimeType.UNDEFINED
            path_type = runtimeType(path)
            if (RuntimeType.STRING == path_type) {
                thisSerializer.writeInt8((0).toChar())
                const path_0  = path as string
                thisSerializer.writeString(path_0)
            }
            else if (RuntimeType.OBJECT == path_type) {
                thisSerializer.writeInt8((1).toChar())
                const path_1  = path as Resource
                Resource_serializer.write(thisSerializer, path_1)
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
            const buffer_length : int32 = retvalDeserializer.readInt32()
            let buffer : Array<TextBox> = new Array<TextBox>(buffer_length)
            for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
                buffer[buffer_i] = text_TextBox_serializer.read(retvalDeserializer)
            }
            const returnResult : Array<TextBox> = buffer
            return returnResult
        }
        private getRectsForPlaceholders_serialize(): Array<TextBox> {
            const retval  = ArkUIGeneratedNativeModule._text_Paragraph_getRectsForPlaceholders(this.peer!.ptr)
            let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
            const buffer_length : int32 = retvalDeserializer.readInt32()
            let buffer : Array<TextBox> = new Array<TextBox>(buffer_length)
            for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
                buffer[buffer_i] = text_TextBox_serializer.read(retvalDeserializer)
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
            const buffer_length : int32 = retvalDeserializer.readInt32()
            let buffer : Array<TextLine> = new Array<TextLine>(buffer_length)
            for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
                buffer[buffer_i] = (text_TextLine_serializer.read(retvalDeserializer) as text.TextLine)
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
            const buffer_length : int32 = retvalDeserializer.readInt32()
            let buffer : Array<LineMetrics> = new Array<LineMetrics>(buffer_length)
            for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
                buffer[buffer_i] = text_LineMetrics_serializer.read(retvalDeserializer)
            }
            const returnResult : Array<LineMetrics> = buffer
            return returnResult
        }
        private getLineMetrics1_serialize(lineNumber: number): LineMetrics | undefined {
            const retval  = ArkUIGeneratedNativeModule._text_Paragraph_getLineMetrics1(this.peer!.ptr, lineNumber)
            let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
            const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
            let buffer : LineMetrics | undefined
            if ((buffer_runtimeType) != (RuntimeType.UNDEFINED))
            {
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
            const buffer_length : int32 = retvalDeserializer.readInt32()
            let buffer : Array<number> = new Array<number>(buffer_length)
            for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
                buffer[buffer_i] = (retvalDeserializer.readNumber() as number)
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
            const buffer_length : int32 = retvalDeserializer.readInt32()
            let buffer : Array<number> = new Array<number>(buffer_length)
            for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
                buffer[buffer_i] = (retvalDeserializer.readNumber() as number)
            }
            const returnResult : Array<number> = buffer
            return returnResult
        }
        private getPositions0_serialize(): Array<common2D.Point> {
            const retval  = ArkUIGeneratedNativeModule._text_Run_getPositions0(this.peer!.ptr)
            let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
            const buffer_length : int32 = retvalDeserializer.readInt32()
            let buffer : Array<common2D.Point> = new Array<common2D.Point>(buffer_length)
            for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
                buffer[buffer_i] = common2D_Point_serializer.read(retvalDeserializer)
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
            const buffer_length : int32 = retvalDeserializer.readInt32()
            let buffer : Array<common2D.Point> = new Array<common2D.Point>(buffer_length)
            for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
                buffer[buffer_i] = common2D_Point_serializer.read(retvalDeserializer)
            }
            const returnResult : Array<common2D.Point> = buffer
            return returnResult
        }
        private getOffsets_serialize(): Array<common2D.Point> {
            const retval  = ArkUIGeneratedNativeModule._text_Run_getOffsets(this.peer!.ptr)
            let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
            const buffer_length : int32 = retvalDeserializer.readInt32()
            let buffer : Array<common2D.Point> = new Array<common2D.Point>(buffer_length)
            for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
                buffer[buffer_i] = common2D_Point_serializer.read(retvalDeserializer)
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
            const buffer_length : int32 = retvalDeserializer.readInt32()
            let buffer : Array<number> = new Array<number>(buffer_length)
            for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
                buffer[buffer_i] = (retvalDeserializer.readNumber() as number)
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
            const buffer_length : int32 = retvalDeserializer.readInt32()
            let buffer : Array<Run> = new Array<Run>(buffer_length)
            for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
                buffer[buffer_i] = (text_Run_serializer.read(retvalDeserializer) as text.Run)
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
