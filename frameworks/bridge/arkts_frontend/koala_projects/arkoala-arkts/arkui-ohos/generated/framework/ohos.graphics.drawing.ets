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

import { extractors } from "#handwritten"
import { default as drawing } from "@ohos.graphics.drawing"
import { SerializerBase, DeserializerBase, CallbackResource, InteropNativeModule, MaterializedBase, Tags, RuntimeType, runtimeType, toPeerPtr, nullptr, KPointer, NativeBuffer, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { TypeChecker } from "#components"
import { CallbackTransformer } from "./../CallbackTransformer"
export class drawing_Canvas_serializer {
    public static write(buffer: SerializerBase, value: drawing.Canvas): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(extractors.toDrawingCanvasPtr(value))
    }
    public static read(buffer: DeserializerBase): drawing.Canvas {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return extractors.fromDrawingCanvasPtr(ptr)
    }
}
export class drawing_ColorFilter_serializer {
    public static write(buffer: SerializerBase, value: drawing.ColorFilter): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(extractors.toDrawingColorFilterPtr(value))
    }
    public static read(buffer: DeserializerBase): drawing.ColorFilter {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return extractors.fromDrawingColorFilterPtr(ptr)
    }
}
export class drawing_Lattice_serializer {
    public static write(buffer: SerializerBase, value: drawing.Lattice): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(extractors.toDrawingLatticePtr(value))
    }
    public static read(buffer: DeserializerBase): drawing.Lattice {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return extractors.fromDrawingLatticePtr(ptr)
    }
}
export class drawing_FontMetrics_serializer {
    public static write(buffer: SerializerBase, value: drawing.FontMetrics): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForFlags  = value.flags
        if (valueHolderForFlags !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFlagsTmpValue  = valueHolderForFlags!
            valueSerializer.writeInt32(valueHolderForFlagsTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForTop  = value.top
        valueSerializer.writeFloat64(valueHolderForTop)
        const valueHolderForAscent  = value.ascent
        valueSerializer.writeFloat64(valueHolderForAscent)
        const valueHolderForDescent  = value.descent
        valueSerializer.writeFloat64(valueHolderForDescent)
        const valueHolderForBottom  = value.bottom
        valueSerializer.writeFloat64(valueHolderForBottom)
        const valueHolderForLeading  = value.leading
        valueSerializer.writeFloat64(valueHolderForLeading)
        const valueHolderForAvgCharWidth  = value.avgCharWidth
        if (valueHolderForAvgCharWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForAvgCharWidthTmpValue  = valueHolderForAvgCharWidth!
            valueSerializer.writeFloat64(valueHolderForAvgCharWidthTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMaxCharWidth  = value.maxCharWidth
        if (valueHolderForMaxCharWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMaxCharWidthTmpValue  = valueHolderForMaxCharWidth!
            valueSerializer.writeFloat64(valueHolderForMaxCharWidthTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForXMin  = value.xMin
        if (valueHolderForXMin !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForXMinTmpValue  = valueHolderForXMin!
            valueSerializer.writeFloat64(valueHolderForXMinTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForXMax  = value.xMax
        if (valueHolderForXMax !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForXMaxTmpValue  = valueHolderForXMax!
            valueSerializer.writeFloat64(valueHolderForXMaxTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForXHeight  = value.xHeight
        if (valueHolderForXHeight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForXHeightTmpValue  = valueHolderForXHeight!
            valueSerializer.writeFloat64(valueHolderForXHeightTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForCapHeight  = value.capHeight
        if (valueHolderForCapHeight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForCapHeightTmpValue  = valueHolderForCapHeight!
            valueSerializer.writeFloat64(valueHolderForCapHeightTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForUnderlineThickness  = value.underlineThickness
        if (valueHolderForUnderlineThickness !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForUnderlineThicknessTmpValue  = valueHolderForUnderlineThickness!
            valueSerializer.writeFloat64(valueHolderForUnderlineThicknessTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForUnderlinePosition  = value.underlinePosition
        if (valueHolderForUnderlinePosition !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForUnderlinePositionTmpValue  = valueHolderForUnderlinePosition!
            valueSerializer.writeFloat64(valueHolderForUnderlinePositionTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForStrikethroughThickness  = value.strikethroughThickness
        if (valueHolderForStrikethroughThickness !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStrikethroughThicknessTmpValue  = valueHolderForStrikethroughThickness!
            valueSerializer.writeFloat64(valueHolderForStrikethroughThicknessTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForStrikethroughPosition  = value.strikethroughPosition
        if (valueHolderForStrikethroughPosition !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStrikethroughPositionTmpValue  = valueHolderForStrikethroughPosition!
            valueSerializer.writeFloat64(valueHolderForStrikethroughPositionTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): drawing.FontMetrics {
        let valueDeserializer : DeserializerBase = buffer
        const flagsTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let flagsTmpBuf : int32 | undefined = undefined
        if ((flagsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            flagsTmpBuf = valueDeserializer.readInt32()
        }
        const flagsTmpResult : int32 | undefined = flagsTmpBuf
        const topTmpResult : double = valueDeserializer.readFloat64()
        const ascentTmpResult : double = valueDeserializer.readFloat64()
        const descentTmpResult : double = valueDeserializer.readFloat64()
        const bottomTmpResult : double = valueDeserializer.readFloat64()
        const leadingTmpResult : double = valueDeserializer.readFloat64()
        const avgCharWidthTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let avgCharWidthTmpBuf : double | undefined = undefined
        if ((avgCharWidthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            avgCharWidthTmpBuf = valueDeserializer.readFloat64()
        }
        const avgCharWidthTmpResult : double | undefined = avgCharWidthTmpBuf
        const maxCharWidthTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let maxCharWidthTmpBuf : double | undefined = undefined
        if ((maxCharWidthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            maxCharWidthTmpBuf = valueDeserializer.readFloat64()
        }
        const maxCharWidthTmpResult : double | undefined = maxCharWidthTmpBuf
        const xMinTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let xMinTmpBuf : double | undefined = undefined
        if ((xMinTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            xMinTmpBuf = valueDeserializer.readFloat64()
        }
        const xMinTmpResult : double | undefined = xMinTmpBuf
        const xMaxTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let xMaxTmpBuf : double | undefined = undefined
        if ((xMaxTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            xMaxTmpBuf = valueDeserializer.readFloat64()
        }
        const xMaxTmpResult : double | undefined = xMaxTmpBuf
        const xHeightTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let xHeightTmpBuf : double | undefined = undefined
        if ((xHeightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            xHeightTmpBuf = valueDeserializer.readFloat64()
        }
        const xHeightTmpResult : double | undefined = xHeightTmpBuf
        const capHeightTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let capHeightTmpBuf : double | undefined = undefined
        if ((capHeightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            capHeightTmpBuf = valueDeserializer.readFloat64()
        }
        const capHeightTmpResult : double | undefined = capHeightTmpBuf
        const underlineThicknessTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let underlineThicknessTmpBuf : double | undefined = undefined
        if ((underlineThicknessTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            underlineThicknessTmpBuf = valueDeserializer.readFloat64()
        }
        const underlineThicknessTmpResult : double | undefined = underlineThicknessTmpBuf
        const underlinePositionTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let underlinePositionTmpBuf : double | undefined = undefined
        if ((underlinePositionTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            underlinePositionTmpBuf = valueDeserializer.readFloat64()
        }
        const underlinePositionTmpResult : double | undefined = underlinePositionTmpBuf
        const strikethroughThicknessTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let strikethroughThicknessTmpBuf : double | undefined = undefined
        if ((strikethroughThicknessTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            strikethroughThicknessTmpBuf = valueDeserializer.readFloat64()
        }
        const strikethroughThicknessTmpResult : double | undefined = strikethroughThicknessTmpBuf
        const strikethroughPositionTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let strikethroughPositionTmpBuf : double | undefined = undefined
        if ((strikethroughPositionTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            strikethroughPositionTmpBuf = valueDeserializer.readFloat64()
        }
        const strikethroughPositionTmpResult : double | undefined = strikethroughPositionTmpBuf
        let value : drawing.FontMetrics = ({flags: flagsTmpResult, top: topTmpResult, ascent: ascentTmpResult, descent: descentTmpResult, bottom: bottomTmpResult, leading: leadingTmpResult, avgCharWidth: avgCharWidthTmpResult, maxCharWidth: maxCharWidthTmpResult, xMin: xMinTmpResult, xMax: xMaxTmpResult, xHeight: xHeightTmpResult, capHeight: capHeightTmpResult, underlineThickness: underlineThicknessTmpResult, underlinePosition: underlinePositionTmpResult, strikethroughThickness: strikethroughThicknessTmpResult, strikethroughPosition: strikethroughPositionTmpResult} as drawing.FontMetrics)
        return value
    }
}
