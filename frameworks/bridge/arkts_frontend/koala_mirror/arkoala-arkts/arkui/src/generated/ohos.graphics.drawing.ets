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
import { common2D_Color_serializer, common2D, common2D_Rect_serializer, common2D_Point3d_serializer, common2D_Point_serializer } from "./ohos.graphics.common2D"
import { image } from "./ohos.multimedia.image"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
export class drawing_Brush_serializer {
    public static write(buffer: SerializerBase, value: drawing.Brush): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): drawing.Brush {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return drawing.BrushInternal.fromPtr(ptr)
    }
}
export class drawing_Canvas_serializer {
    public static write(buffer: SerializerBase, value: drawing.Canvas): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): drawing.Canvas {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return drawing.CanvasInternal.fromPtr(ptr)
    }
}
export class drawing_ColorFilter_serializer {
    public static write(buffer: SerializerBase, value: drawing.ColorFilter): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): drawing.ColorFilter {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return drawing.ColorFilterInternal.fromPtr(ptr)
    }
}
export class drawing_Font_serializer {
    public static write(buffer: SerializerBase, value: drawing.Font): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): drawing.Font {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return drawing.FontInternal.fromPtr(ptr)
    }
}
export class drawing_ImageFilter_serializer {
    public static write(buffer: SerializerBase, value: drawing.ImageFilter): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): drawing.ImageFilter {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return drawing.ImageFilterInternal.fromPtr(ptr)
    }
}
export class drawing_Lattice_serializer {
    public static write(buffer: SerializerBase, value: drawing.Lattice): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): drawing.Lattice {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return drawing.LatticeInternal.fromPtr(ptr)
    }
}
export class drawing_MaskFilter_serializer {
    public static write(buffer: SerializerBase, value: drawing.MaskFilter): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): drawing.MaskFilter {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return drawing.MaskFilterInternal.fromPtr(ptr)
    }
}
export class drawing_Matrix_serializer {
    public static write(buffer: SerializerBase, value: drawing.Matrix): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): drawing.Matrix {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return drawing.MatrixInternal.fromPtr(ptr)
    }
}
export class drawing_Path_serializer {
    public static write(buffer: SerializerBase, value: drawing.Path): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): drawing.Path {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return drawing.PathInternal.fromPtr(ptr)
    }
}
export class drawing_PathEffect_serializer {
    public static write(buffer: SerializerBase, value: drawing.PathEffect): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): drawing.PathEffect {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return drawing.PathEffectInternal.fromPtr(ptr)
    }
}
export class drawing_Pen_serializer {
    public static write(buffer: SerializerBase, value: drawing.Pen): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): drawing.Pen {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return drawing.PenInternal.fromPtr(ptr)
    }
}
export class drawing_Region_serializer {
    public static write(buffer: SerializerBase, value: drawing.Region): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): drawing.Region {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return drawing.RegionInternal.fromPtr(ptr)
    }
}
export class drawing_RoundRect_serializer {
    public static write(buffer: SerializerBase, value: drawing.RoundRect): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): drawing.RoundRect {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return drawing.RoundRectInternal.fromPtr(ptr)
    }
}
export class drawing_SamplingOptions_serializer {
    public static write(buffer: SerializerBase, value: drawing.SamplingOptions): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): drawing.SamplingOptions {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return drawing.SamplingOptionsInternal.fromPtr(ptr)
    }
}
export class drawing_ShaderEffect_serializer {
    public static write(buffer: SerializerBase, value: drawing.ShaderEffect): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): drawing.ShaderEffect {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return drawing.ShaderEffectInternal.fromPtr(ptr)
    }
}
export class drawing_ShadowLayer_serializer {
    public static write(buffer: SerializerBase, value: drawing.ShadowLayer): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): drawing.ShadowLayer {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return drawing.ShadowLayerInternal.fromPtr(ptr)
    }
}
export class drawing_TextBlob_serializer {
    public static write(buffer: SerializerBase, value: drawing.TextBlob): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): drawing.TextBlob {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return drawing.TextBlobInternal.fromPtr(ptr)
    }
}
export class drawing_Typeface_serializer {
    public static write(buffer: SerializerBase, value: drawing.Typeface): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): drawing.Typeface {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return drawing.TypefaceInternal.fromPtr(ptr)
    }
}
export class drawing_FontMetrics_serializer {
    public static write(buffer: SerializerBase, value: drawing.FontMetrics): void {
        let valueSerializer : SerializerBase = buffer
        const value_flags  = value.flags
        let value_flags_type : int32 = RuntimeType.UNDEFINED
        value_flags_type = runtimeType(value_flags)
        valueSerializer.writeInt8((value_flags_type).toChar())
        if ((value_flags_type) != (RuntimeType.UNDEFINED)) {
            const value_flags_value  = (value_flags as drawing.FontMetricsFlags)
            valueSerializer.writeInt32(TypeChecker.drawing_FontMetricsFlags_ToNumeric(value_flags_value))
        }
        const value_top  = value.top
        valueSerializer.writeNumber(value_top)
        const value_ascent  = value.ascent
        valueSerializer.writeNumber(value_ascent)
        const value_descent  = value.descent
        valueSerializer.writeNumber(value_descent)
        const value_bottom  = value.bottom
        valueSerializer.writeNumber(value_bottom)
        const value_leading  = value.leading
        valueSerializer.writeNumber(value_leading)
        const value_avgCharWidth  = value.avgCharWidth
        let value_avgCharWidth_type : int32 = RuntimeType.UNDEFINED
        value_avgCharWidth_type = runtimeType(value_avgCharWidth)
        valueSerializer.writeInt8((value_avgCharWidth_type).toChar())
        if ((value_avgCharWidth_type) != (RuntimeType.UNDEFINED)) {
            const value_avgCharWidth_value  = value_avgCharWidth!
            valueSerializer.writeNumber(value_avgCharWidth_value)
        }
        const value_maxCharWidth  = value.maxCharWidth
        let value_maxCharWidth_type : int32 = RuntimeType.UNDEFINED
        value_maxCharWidth_type = runtimeType(value_maxCharWidth)
        valueSerializer.writeInt8((value_maxCharWidth_type).toChar())
        if ((value_maxCharWidth_type) != (RuntimeType.UNDEFINED)) {
            const value_maxCharWidth_value  = value_maxCharWidth!
            valueSerializer.writeNumber(value_maxCharWidth_value)
        }
        const value_xMin  = value.xMin
        let value_xMin_type : int32 = RuntimeType.UNDEFINED
        value_xMin_type = runtimeType(value_xMin)
        valueSerializer.writeInt8((value_xMin_type).toChar())
        if ((value_xMin_type) != (RuntimeType.UNDEFINED)) {
            const value_xMin_value  = value_xMin!
            valueSerializer.writeNumber(value_xMin_value)
        }
        const value_xMax  = value.xMax
        let value_xMax_type : int32 = RuntimeType.UNDEFINED
        value_xMax_type = runtimeType(value_xMax)
        valueSerializer.writeInt8((value_xMax_type).toChar())
        if ((value_xMax_type) != (RuntimeType.UNDEFINED)) {
            const value_xMax_value  = value_xMax!
            valueSerializer.writeNumber(value_xMax_value)
        }
        const value_xHeight  = value.xHeight
        let value_xHeight_type : int32 = RuntimeType.UNDEFINED
        value_xHeight_type = runtimeType(value_xHeight)
        valueSerializer.writeInt8((value_xHeight_type).toChar())
        if ((value_xHeight_type) != (RuntimeType.UNDEFINED)) {
            const value_xHeight_value  = value_xHeight!
            valueSerializer.writeNumber(value_xHeight_value)
        }
        const value_capHeight  = value.capHeight
        let value_capHeight_type : int32 = RuntimeType.UNDEFINED
        value_capHeight_type = runtimeType(value_capHeight)
        valueSerializer.writeInt8((value_capHeight_type).toChar())
        if ((value_capHeight_type) != (RuntimeType.UNDEFINED)) {
            const value_capHeight_value  = value_capHeight!
            valueSerializer.writeNumber(value_capHeight_value)
        }
        const value_underlineThickness  = value.underlineThickness
        let value_underlineThickness_type : int32 = RuntimeType.UNDEFINED
        value_underlineThickness_type = runtimeType(value_underlineThickness)
        valueSerializer.writeInt8((value_underlineThickness_type).toChar())
        if ((value_underlineThickness_type) != (RuntimeType.UNDEFINED)) {
            const value_underlineThickness_value  = value_underlineThickness!
            valueSerializer.writeNumber(value_underlineThickness_value)
        }
        const value_underlinePosition  = value.underlinePosition
        let value_underlinePosition_type : int32 = RuntimeType.UNDEFINED
        value_underlinePosition_type = runtimeType(value_underlinePosition)
        valueSerializer.writeInt8((value_underlinePosition_type).toChar())
        if ((value_underlinePosition_type) != (RuntimeType.UNDEFINED)) {
            const value_underlinePosition_value  = value_underlinePosition!
            valueSerializer.writeNumber(value_underlinePosition_value)
        }
        const value_strikethroughThickness  = value.strikethroughThickness
        let value_strikethroughThickness_type : int32 = RuntimeType.UNDEFINED
        value_strikethroughThickness_type = runtimeType(value_strikethroughThickness)
        valueSerializer.writeInt8((value_strikethroughThickness_type).toChar())
        if ((value_strikethroughThickness_type) != (RuntimeType.UNDEFINED)) {
            const value_strikethroughThickness_value  = value_strikethroughThickness!
            valueSerializer.writeNumber(value_strikethroughThickness_value)
        }
        const value_strikethroughPosition  = value.strikethroughPosition
        let value_strikethroughPosition_type : int32 = RuntimeType.UNDEFINED
        value_strikethroughPosition_type = runtimeType(value_strikethroughPosition)
        valueSerializer.writeInt8((value_strikethroughPosition_type).toChar())
        if ((value_strikethroughPosition_type) != (RuntimeType.UNDEFINED)) {
            const value_strikethroughPosition_value  = value_strikethroughPosition!
            valueSerializer.writeNumber(value_strikethroughPosition_value)
        }
    }
    public static read(buffer: DeserializerBase): drawing.FontMetrics {
        let valueDeserializer : DeserializerBase = buffer
        const flags_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let flags_buf : drawing.FontMetricsFlags | undefined
        if ((flags_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            flags_buf = TypeChecker.drawing_FontMetricsFlags_FromNumeric(valueDeserializer.readInt32())
        }
        const flags_result : drawing.FontMetricsFlags | undefined = flags_buf
        const top_result : number = (valueDeserializer.readNumber() as number)
        const ascent_result : number = (valueDeserializer.readNumber() as number)
        const descent_result : number = (valueDeserializer.readNumber() as number)
        const bottom_result : number = (valueDeserializer.readNumber() as number)
        const leading_result : number = (valueDeserializer.readNumber() as number)
        const avgCharWidth_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let avgCharWidth_buf : number | undefined
        if ((avgCharWidth_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            avgCharWidth_buf = (valueDeserializer.readNumber() as number)
        }
        const avgCharWidth_result : number | undefined = avgCharWidth_buf
        const maxCharWidth_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let maxCharWidth_buf : number | undefined
        if ((maxCharWidth_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            maxCharWidth_buf = (valueDeserializer.readNumber() as number)
        }
        const maxCharWidth_result : number | undefined = maxCharWidth_buf
        const xMin_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let xMin_buf : number | undefined
        if ((xMin_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            xMin_buf = (valueDeserializer.readNumber() as number)
        }
        const xMin_result : number | undefined = xMin_buf
        const xMax_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let xMax_buf : number | undefined
        if ((xMax_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            xMax_buf = (valueDeserializer.readNumber() as number)
        }
        const xMax_result : number | undefined = xMax_buf
        const xHeight_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let xHeight_buf : number | undefined
        if ((xHeight_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            xHeight_buf = (valueDeserializer.readNumber() as number)
        }
        const xHeight_result : number | undefined = xHeight_buf
        const capHeight_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let capHeight_buf : number | undefined
        if ((capHeight_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            capHeight_buf = (valueDeserializer.readNumber() as number)
        }
        const capHeight_result : number | undefined = capHeight_buf
        const underlineThickness_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let underlineThickness_buf : number | undefined
        if ((underlineThickness_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            underlineThickness_buf = (valueDeserializer.readNumber() as number)
        }
        const underlineThickness_result : number | undefined = underlineThickness_buf
        const underlinePosition_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let underlinePosition_buf : number | undefined
        if ((underlinePosition_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            underlinePosition_buf = (valueDeserializer.readNumber() as number)
        }
        const underlinePosition_result : number | undefined = underlinePosition_buf
        const strikethroughThickness_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let strikethroughThickness_buf : number | undefined
        if ((strikethroughThickness_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            strikethroughThickness_buf = (valueDeserializer.readNumber() as number)
        }
        const strikethroughThickness_result : number | undefined = strikethroughThickness_buf
        const strikethroughPosition_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let strikethroughPosition_buf : number | undefined
        if ((strikethroughPosition_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            strikethroughPosition_buf = (valueDeserializer.readNumber() as number)
        }
        const strikethroughPosition_result : number | undefined = strikethroughPosition_buf
        let value : drawing.FontMetrics = ({flags: flags_result, top: top_result, ascent: ascent_result, descent: descent_result, bottom: bottom_result, leading: leading_result, avgCharWidth: avgCharWidth_result, maxCharWidth: maxCharWidth_result, xMin: xMin_result, xMax: xMax_result, xHeight: xHeight_result, capHeight: capHeight_result, underlineThickness: underlineThickness_result, underlinePosition: underlinePosition_result, strikethroughThickness: strikethroughThickness_result, strikethroughPosition: strikethroughPosition_result} as drawing.FontMetrics)
        return value
    }
}
export class drawing_TextBlobRunBuffer_serializer {
    public static write(buffer: SerializerBase, value: drawing.TextBlobRunBuffer): void {
        let valueSerializer : SerializerBase = buffer
        const value_glyph  = value.glyph
        valueSerializer.writeNumber(value_glyph)
        const value_positionX  = value.positionX
        valueSerializer.writeNumber(value_positionX)
        const value_positionY  = value.positionY
        valueSerializer.writeNumber(value_positionY)
    }
    public static read(buffer: DeserializerBase): drawing.TextBlobRunBuffer {
        let valueDeserializer : DeserializerBase = buffer
        const glyph_result : number = (valueDeserializer.readNumber() as number)
        const positionX_result : number = (valueDeserializer.readNumber() as number)
        const positionY_result : number = (valueDeserializer.readNumber() as number)
        let value : drawing.TextBlobRunBuffer = ({glyph: glyph_result, positionX: positionX_result, positionY: positionY_result} as drawing.TextBlobRunBuffer)
        return value
    }
}
export namespace drawing {
    export class BrushInternal {
        public static fromPtr(ptr: KPointer): drawing.Brush {
            return new drawing.Brush(false, ptr)
        }
    }
    export class Brush implements MaterializedBase {
        peer?: Finalizable | undefined = undefined
        public getPeer(): Finalizable | undefined {
            return this.peer
        }
        constructor(_0: boolean, peerPtr: KPointer) {
            this.peer = new Finalizable(peerPtr, Brush.getFinalizer())
        }
        constructor() {
            this(false, Brush.construct0())
        }
        constructor(brush: Brush) {
            this(false, Brush.construct1(brush))
        }
        static construct0(): KPointer {
            const retval  = ArkUIGeneratedNativeModule._drawing_Brush_construct0()
            return retval
        }
        static construct1(brush: Brush): KPointer {
            const retval  = ArkUIGeneratedNativeModule._drawing_Brush_construct1(toPeerPtr(brush))
            return retval
        }
        static getFinalizer(): KPointer {
            return ArkUIGeneratedNativeModule._drawing_Brush_getFinalizer()
        }
        public setColor(color: common2D.Color): void {
            const color_casted = color as (common2D.Color)
            this.setColor0_serialize(color_casted)
            return
        }
        public setColor(color: number): void {
            const color_casted = color as (number)
            this.setColor1_serialize(color_casted)
            return
        }
        public setColor(alpha: number, red: number, green: number, blue: number): void {
            const alpha_casted = alpha as (number)
            const red_casted = red as (number)
            const green_casted = green as (number)
            const blue_casted = blue as (number)
            this.setColor2_serialize(alpha_casted, red_casted, green_casted, blue_casted)
            return
        }
        public getColor(): common2D.Color {
            return this.getColor_serialize()
        }
        public getHexColor(): number {
            return this.getHexColor_serialize()
        }
        public setAntiAlias(aa: boolean): void {
            const aa_casted = aa as (boolean)
            this.setAntiAlias_serialize(aa_casted)
            return
        }
        public isAntiAlias(): boolean {
            return this.isAntiAlias_serialize()
        }
        public setAlpha(alpha: number): void {
            const alpha_casted = alpha as (number)
            this.setAlpha_serialize(alpha_casted)
            return
        }
        public getAlpha(): number {
            return this.getAlpha_serialize()
        }
        public setColorFilter(filter: ColorFilter): void {
            const filter_casted = filter as (ColorFilter)
            this.setColorFilter_serialize(filter_casted)
            return
        }
        public getColorFilter(): ColorFilter {
            return this.getColorFilter_serialize()
        }
        public setImageFilter(filter: ImageFilter | undefined): void {
            const filter_casted = filter as (ImageFilter | undefined)
            this.setImageFilter_serialize(filter_casted)
            return
        }
        public setMaskFilter(filter: MaskFilter): void {
            const filter_casted = filter as (MaskFilter)
            this.setMaskFilter_serialize(filter_casted)
            return
        }
        public setShadowLayer(shadowLayer: ShadowLayer): void {
            const shadowLayer_casted = shadowLayer as (ShadowLayer)
            this.setShadowLayer_serialize(shadowLayer_casted)
            return
        }
        public setShaderEffect(shaderEffect: ShaderEffect): void {
            const shaderEffect_casted = shaderEffect as (ShaderEffect)
            this.setShaderEffect_serialize(shaderEffect_casted)
            return
        }
        public setBlendMode(mode: BlendMode): void {
            const mode_casted = mode as (BlendMode)
            this.setBlendMode_serialize(mode_casted)
            return
        }
        public reset(): void {
            this.reset_serialize()
            return
        }
        private setColor0_serialize(color: common2D.Color): void {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            common2D_Color_serializer.write(thisSerializer, color)
            ArkUIGeneratedNativeModule._drawing_Brush_setColor0(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
            thisSerializer.release()
        }
        private setColor1_serialize(color: number): void {
            ArkUIGeneratedNativeModule._drawing_Brush_setColor1(this.peer!.ptr, color)
        }
        private setColor2_serialize(alpha: number, red: number, green: number, blue: number): void {
            ArkUIGeneratedNativeModule._drawing_Brush_setColor2(this.peer!.ptr, alpha, red, green, blue)
        }
        private getColor_serialize(): common2D.Color {
            const retval  = ArkUIGeneratedNativeModule._drawing_Brush_getColor(this.peer!.ptr)
            let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
            const returnResult : common2D.Color = common2D_Color_serializer.read(retvalDeserializer)
            return returnResult
        }
        private getHexColor_serialize(): number {
            const retval  = ArkUIGeneratedNativeModule._drawing_Brush_getHexColor(this.peer!.ptr)
            return retval
        }
        private setAntiAlias_serialize(aa: boolean): void {
            ArkUIGeneratedNativeModule._drawing_Brush_setAntiAlias(this.peer!.ptr, aa ? 1 : 0)
        }
        private isAntiAlias_serialize(): boolean {
            const retval  = ArkUIGeneratedNativeModule._drawing_Brush_isAntiAlias(this.peer!.ptr)
            return retval
        }
        private setAlpha_serialize(alpha: number): void {
            ArkUIGeneratedNativeModule._drawing_Brush_setAlpha(this.peer!.ptr, alpha)
        }
        private getAlpha_serialize(): number {
            const retval  = ArkUIGeneratedNativeModule._drawing_Brush_getAlpha(this.peer!.ptr)
            return retval
        }
        private setColorFilter_serialize(filter: ColorFilter): void {
            ArkUIGeneratedNativeModule._drawing_Brush_setColorFilter(this.peer!.ptr, toPeerPtr(filter))
        }
        private getColorFilter_serialize(): ColorFilter {
            const retval  = ArkUIGeneratedNativeModule._drawing_Brush_getColorFilter(this.peer!.ptr)
            const obj : ColorFilter = drawing.ColorFilterInternal.fromPtr(retval)
            return obj
        }
        private setImageFilter_serialize(filter: ImageFilter | undefined): void {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            let filter_type : int32 = RuntimeType.UNDEFINED
            filter_type = runtimeType(filter)
            thisSerializer.writeInt8((filter_type).toChar())
            if ((filter_type) != (RuntimeType.UNDEFINED)) {
                const filter_value  = filter!
                drawing_ImageFilter_serializer.write(thisSerializer, filter_value)
            }
            ArkUIGeneratedNativeModule._drawing_Brush_setImageFilter(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
            thisSerializer.release()
        }
        private setMaskFilter_serialize(filter: MaskFilter): void {
            ArkUIGeneratedNativeModule._drawing_Brush_setMaskFilter(this.peer!.ptr, toPeerPtr(filter))
        }
        private setShadowLayer_serialize(shadowLayer: ShadowLayer): void {
            ArkUIGeneratedNativeModule._drawing_Brush_setShadowLayer(this.peer!.ptr, toPeerPtr(shadowLayer))
        }
        private setShaderEffect_serialize(shaderEffect: ShaderEffect): void {
            ArkUIGeneratedNativeModule._drawing_Brush_setShaderEffect(this.peer!.ptr, toPeerPtr(shaderEffect))
        }
        private setBlendMode_serialize(mode: BlendMode): void {
            ArkUIGeneratedNativeModule._drawing_Brush_setBlendMode(this.peer!.ptr, TypeChecker.drawing_BlendMode_ToNumeric(mode))
        }
        private reset_serialize(): void {
            ArkUIGeneratedNativeModule._drawing_Brush_reset(this.peer!.ptr)
        }
    }
    export class CanvasInternal {
        public static fromPtr(ptr: KPointer): drawing.Canvas {
            return new drawing.Canvas(false, ptr)
        }
    }
    export class Canvas implements MaterializedBase {
        peer?: Finalizable | undefined = undefined
        public getPeer(): Finalizable | undefined {
            return this.peer
        }
        constructor(_0: boolean, peerPtr: KPointer) {
            this.peer = new Finalizable(peerPtr, Canvas.getFinalizer())
        }
        constructor(pixelmap: image.PixelMap) {
            this(false, Canvas.construct(pixelmap))
        }
        static construct(pixelmap: image.PixelMap): KPointer {
            const retval  = ArkUIGeneratedNativeModule._drawing_Canvas_construct(toPeerPtr(pixelmap))
            return retval
        }
        static getFinalizer(): KPointer {
            return ArkUIGeneratedNativeModule._drawing_Canvas_getFinalizer()
        }
        public drawRect(rect: common2D.Rect): void {
            const rect_casted = rect as (common2D.Rect)
            this.drawRect0_serialize(rect_casted)
            return
        }
        public drawRect(left: number, top: number, right: number, bottom: number): void {
            const left_casted = left as (number)
            const top_casted = top as (number)
            const right_casted = right as (number)
            const bottom_casted = bottom as (number)
            this.drawRect1_serialize(left_casted, top_casted, right_casted, bottom_casted)
            return
        }
        public drawRoundRect(roundRect: RoundRect): void {
            const roundRect_casted = roundRect as (RoundRect)
            this.drawRoundRect_serialize(roundRect_casted)
            return
        }
        public drawNestedRoundRect(outer: RoundRect, inner: RoundRect): void {
            const outer_casted = outer as (RoundRect)
            const inner_casted = inner as (RoundRect)
            this.drawNestedRoundRect_serialize(outer_casted, inner_casted)
            return
        }
        public drawBackground(brush: Brush): void {
            const brush_casted = brush as (Brush)
            this.drawBackground_serialize(brush_casted)
            return
        }
        public drawShadow(path: Path, planeParams: common2D.Point3d, devLightPos: common2D.Point3d, lightRadius: number, ambientColor: common2D.Color, spotColor: common2D.Color, flag: ShadowFlag): void {
            const path_casted = path as (Path)
            const planeParams_casted = planeParams as (common2D.Point3d)
            const devLightPos_casted = devLightPos as (common2D.Point3d)
            const lightRadius_casted = lightRadius as (number)
            const ambientColor_casted = ambientColor as (common2D.Color)
            const spotColor_casted = spotColor as (common2D.Color)
            const flag_casted = flag as (ShadowFlag)
            this.drawShadow0_serialize(path_casted, planeParams_casted, devLightPos_casted, lightRadius_casted, ambientColor_casted, spotColor_casted, flag_casted)
            return
        }
        public drawShadow(path: Path, planeParams: common2D.Point3d, devLightPos: common2D.Point3d, lightRadius: number, ambientColor: number, spotColor: number, flag: ShadowFlag): void {
            const path_casted = path as (Path)
            const planeParams_casted = planeParams as (common2D.Point3d)
            const devLightPos_casted = devLightPos as (common2D.Point3d)
            const lightRadius_casted = lightRadius as (number)
            const ambientColor_casted = ambientColor as (number)
            const spotColor_casted = spotColor as (number)
            const flag_casted = flag as (ShadowFlag)
            this.drawShadow1_serialize(path_casted, planeParams_casted, devLightPos_casted, lightRadius_casted, ambientColor_casted, spotColor_casted, flag_casted)
            return
        }
        public drawCircle(x: number, y: number, radius: number): void {
            const x_casted = x as (number)
            const y_casted = y as (number)
            const radius_casted = radius as (number)
            this.drawCircle_serialize(x_casted, y_casted, radius_casted)
            return
        }
        public drawImage(pixelmap: image.PixelMap, left: number, top: number, samplingOptions: SamplingOptions): void {
            const pixelmap_casted = pixelmap as (image.PixelMap)
            const left_casted = left as (number)
            const top_casted = top as (number)
            const samplingOptions_casted = samplingOptions as (SamplingOptions)
            this.drawImage_serialize(pixelmap_casted, left_casted, top_casted, samplingOptions_casted)
            return
        }
        public drawImageRect(pixelmap: image.PixelMap, dstRect: common2D.Rect, samplingOptions: SamplingOptions): void {
            const pixelmap_casted = pixelmap as (image.PixelMap)
            const dstRect_casted = dstRect as (common2D.Rect)
            const samplingOptions_casted = samplingOptions as (SamplingOptions)
            this.drawImageRect_serialize(pixelmap_casted, dstRect_casted, samplingOptions_casted)
            return
        }
        public drawImageRectWithSrc(pixelmap: image.PixelMap, srcRect: common2D.Rect, dstRect: common2D.Rect, samplingOptions: SamplingOptions, constraint: SrcRectConstraint): void {
            const pixelmap_casted = pixelmap as (image.PixelMap)
            const srcRect_casted = srcRect as (common2D.Rect)
            const dstRect_casted = dstRect as (common2D.Rect)
            const samplingOptions_casted = samplingOptions as (SamplingOptions)
            const constraint_casted = constraint as (SrcRectConstraint)
            this.drawImageRectWithSrc_serialize(pixelmap_casted, srcRect_casted, dstRect_casted, samplingOptions_casted, constraint_casted)
            return
        }
        public drawColor(color: common2D.Color, blendMode: BlendMode): void {
            const color_casted = color as (common2D.Color)
            const blendMode_casted = blendMode as (BlendMode)
            this.drawColor0_serialize(color_casted, blendMode_casted)
            return
        }
        public drawColor(color: number, blendMode: BlendMode): void {
            const color_casted = color as (number)
            const blendMode_casted = blendMode as (BlendMode)
            this.drawColor1_serialize(color_casted, blendMode_casted)
            return
        }
        public drawColor(alpha: number, red: number, green: number, blue: number, blendMode: BlendMode): void {
            const alpha_casted = alpha as (number)
            const red_casted = red as (number)
            const green_casted = green as (number)
            const blue_casted = blue as (number)
            const blendMode_casted = blendMode as (BlendMode)
            this.drawColor2_serialize(alpha_casted, red_casted, green_casted, blue_casted, blendMode_casted)
            return
        }
        public drawOval(oval: common2D.Rect): void {
            const oval_casted = oval as (common2D.Rect)
            this.drawOval_serialize(oval_casted)
            return
        }
        public drawArc(arc: common2D.Rect, startAngle: number, sweepAngle: number): void {
            const arc_casted = arc as (common2D.Rect)
            const startAngle_casted = startAngle as (number)
            const sweepAngle_casted = sweepAngle as (number)
            this.drawArc_serialize(arc_casted, startAngle_casted, sweepAngle_casted)
            return
        }
        public drawPoint(x: number, y: number): void {
            const x_casted = x as (number)
            const y_casted = y as (number)
            this.drawPoint_serialize(x_casted, y_casted)
            return
        }
        public drawPoints(points: Array<common2D.Point>, mode: PointMode): void {
            const points_casted = points as (Array<common2D.Point>)
            const mode_casted = mode as (PointMode)
            this.drawPoints_serialize(points_casted, mode_casted)
            return
        }
        public drawPath(path: Path): void {
            const path_casted = path as (Path)
            this.drawPath_serialize(path_casted)
            return
        }
        public drawLine(x0: number, y0: number, x1: number, y1: number): void {
            const x0_casted = x0 as (number)
            const y0_casted = y0 as (number)
            const x1_casted = x1 as (number)
            const y1_casted = y1 as (number)
            this.drawLine_serialize(x0_casted, y0_casted, x1_casted, y1_casted)
            return
        }
        public drawSingleCharacter(text: string, font: Font, x: number, y: number): void {
            const text_casted = text as (string)
            const font_casted = font as (Font)
            const x_casted = x as (number)
            const y_casted = y as (number)
            this.drawSingleCharacter_serialize(text_casted, font_casted, x_casted, y_casted)
            return
        }
        public drawTextBlob(blob: TextBlob, x: number, y: number): void {
            const blob_casted = blob as (TextBlob)
            const x_casted = x as (number)
            const y_casted = y as (number)
            this.drawTextBlob_serialize(blob_casted, x_casted, y_casted)
            return
        }
        public drawPixelMapMesh(pixelmap: image.PixelMap, meshWidth: number, meshHeight: number, vertices: Array<number>, vertOffset: number, colors: Array<number>, colorOffset: number): void {
            const pixelmap_casted = pixelmap as (image.PixelMap)
            const meshWidth_casted = meshWidth as (number)
            const meshHeight_casted = meshHeight as (number)
            const vertices_casted = vertices as (Array<number>)
            const vertOffset_casted = vertOffset as (number)
            const colors_casted = colors as (Array<number>)
            const colorOffset_casted = colorOffset as (number)
            this.drawPixelMapMesh_serialize(pixelmap_casted, meshWidth_casted, meshHeight_casted, vertices_casted, vertOffset_casted, colors_casted, colorOffset_casted)
            return
        }
        public drawRegion(region: Region): void {
            const region_casted = region as (Region)
            this.drawRegion_serialize(region_casted)
            return
        }
        public attachPen(pen: Pen): void {
            const pen_casted = pen as (Pen)
            this.attachPen_serialize(pen_casted)
            return
        }
        public attachBrush(brush: Brush): void {
            const brush_casted = brush as (Brush)
            this.attachBrush_serialize(brush_casted)
            return
        }
        public detachPen(): void {
            this.detachPen_serialize()
            return
        }
        public detachBrush(): void {
            this.detachBrush_serialize()
            return
        }
        public save(): number {
            return this.save_serialize()
        }
        public saveLayer(rect: common2D.Rect | undefined, brush: Brush | undefined): number {
            const rect_casted = rect as (common2D.Rect | undefined)
            const brush_casted = brush as (Brush | undefined)
            return this.saveLayer_serialize(rect_casted, brush_casted)
        }
        public clear(color: common2D.Color): void {
            const color_casted = color as (common2D.Color)
            this.clear0_serialize(color_casted)
            return
        }
        public clear(color: number): void {
            const color_casted = color as (number)
            this.clear1_serialize(color_casted)
            return
        }
        public restore(): void {
            this.restore_serialize()
            return
        }
        public restoreToCount(count: number): void {
            const count_casted = count as (number)
            this.restoreToCount_serialize(count_casted)
            return
        }
        public getSaveCount(): number {
            return this.getSaveCount_serialize()
        }
        public getWidth(): number {
            return this.getWidth_serialize()
        }
        public getHeight(): number {
            return this.getHeight_serialize()
        }
        public getLocalClipBounds(): common2D.Rect {
            return this.getLocalClipBounds_serialize()
        }
        public getTotalMatrix(): Matrix {
            return this.getTotalMatrix_serialize()
        }
        public scale(sx: number, sy: number): void {
            const sx_casted = sx as (number)
            const sy_casted = sy as (number)
            this.scale_serialize(sx_casted, sy_casted)
            return
        }
        public skew(sx: number, sy: number): void {
            const sx_casted = sx as (number)
            const sy_casted = sy as (number)
            this.skew_serialize(sx_casted, sy_casted)
            return
        }
        public rotate(degrees: number, sx: number, sy: number): void {
            const degrees_casted = degrees as (number)
            const sx_casted = sx as (number)
            const sy_casted = sy as (number)
            this.rotate_serialize(degrees_casted, sx_casted, sy_casted)
            return
        }
        public translate(dx: number, dy: number): void {
            const dx_casted = dx as (number)
            const dy_casted = dy as (number)
            this.translate_serialize(dx_casted, dy_casted)
            return
        }
        public clipPath(path: Path, clipOp: ClipOp, doAntiAlias: boolean): void {
            const path_casted = path as (Path)
            const clipOp_casted = clipOp as (ClipOp)
            const doAntiAlias_casted = doAntiAlias as (boolean)
            this.clipPath_serialize(path_casted, clipOp_casted, doAntiAlias_casted)
            return
        }
        public clipRect(rect: common2D.Rect, clipOp: ClipOp, doAntiAlias: boolean): void {
            const rect_casted = rect as (common2D.Rect)
            const clipOp_casted = clipOp as (ClipOp)
            const doAntiAlias_casted = doAntiAlias as (boolean)
            this.clipRect_serialize(rect_casted, clipOp_casted, doAntiAlias_casted)
            return
        }
        public concatMatrix(matrix: Matrix): void {
            const matrix_casted = matrix as (Matrix)
            this.concatMatrix_serialize(matrix_casted)
            return
        }
        public clipRegion(region: Region, clipOp: ClipOp): void {
            const region_casted = region as (Region)
            const clipOp_casted = clipOp as (ClipOp)
            this.clipRegion_serialize(region_casted, clipOp_casted)
            return
        }
        public clipRoundRect(roundRect: RoundRect, clipOp: ClipOp, doAntiAlias: boolean): void {
            const roundRect_casted = roundRect as (RoundRect)
            const clipOp_casted = clipOp as (ClipOp)
            const doAntiAlias_casted = doAntiAlias as (boolean)
            this.clipRoundRect_serialize(roundRect_casted, clipOp_casted, doAntiAlias_casted)
            return
        }
        public isClipEmpty(): boolean {
            return this.isClipEmpty_serialize()
        }
        public setMatrix(matrix: Matrix): void {
            const matrix_casted = matrix as (Matrix)
            this.setMatrix_serialize(matrix_casted)
            return
        }
        public resetMatrix(): void {
            this.resetMatrix_serialize()
            return
        }
        private drawRect0_serialize(rect: common2D.Rect): void {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            common2D_Rect_serializer.write(thisSerializer, rect)
            ArkUIGeneratedNativeModule._drawing_Canvas_drawRect0(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
            thisSerializer.release()
        }
        private drawRect1_serialize(left: number, top: number, right: number, bottom: number): void {
            ArkUIGeneratedNativeModule._drawing_Canvas_drawRect1(this.peer!.ptr, left, top, right, bottom)
        }
        private drawRoundRect_serialize(roundRect: RoundRect): void {
            ArkUIGeneratedNativeModule._drawing_Canvas_drawRoundRect(this.peer!.ptr, toPeerPtr(roundRect))
        }
        private drawNestedRoundRect_serialize(outer: RoundRect, inner: RoundRect): void {
            ArkUIGeneratedNativeModule._drawing_Canvas_drawNestedRoundRect(this.peer!.ptr, toPeerPtr(outer), toPeerPtr(inner))
        }
        private drawBackground_serialize(brush: Brush): void {
            ArkUIGeneratedNativeModule._drawing_Canvas_drawBackground(this.peer!.ptr, toPeerPtr(brush))
        }
        private drawShadow0_serialize(path: Path, planeParams: common2D.Point3d, devLightPos: common2D.Point3d, lightRadius: number, ambientColor: common2D.Color, spotColor: common2D.Color, flag: ShadowFlag): void {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            common2D_Point3d_serializer.write(thisSerializer, planeParams)
            common2D_Point3d_serializer.write(thisSerializer, devLightPos)
            common2D_Color_serializer.write(thisSerializer, ambientColor)
            common2D_Color_serializer.write(thisSerializer, spotColor)
            ArkUIGeneratedNativeModule._drawing_Canvas_drawShadow0(this.peer!.ptr, toPeerPtr(path), thisSerializer.asBuffer(), thisSerializer.length(), lightRadius, TypeChecker.drawing_ShadowFlag_ToNumeric(flag))
            thisSerializer.release()
        }
        private drawShadow1_serialize(path: Path, planeParams: common2D.Point3d, devLightPos: common2D.Point3d, lightRadius: number, ambientColor: number, spotColor: number, flag: ShadowFlag): void {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            common2D_Point3d_serializer.write(thisSerializer, planeParams)
            common2D_Point3d_serializer.write(thisSerializer, devLightPos)
            ArkUIGeneratedNativeModule._drawing_Canvas_drawShadow1(this.peer!.ptr, toPeerPtr(path), thisSerializer.asBuffer(), thisSerializer.length(), lightRadius, ambientColor, spotColor, TypeChecker.drawing_ShadowFlag_ToNumeric(flag))
            thisSerializer.release()
        }
        private drawCircle_serialize(x: number, y: number, radius: number): void {
            ArkUIGeneratedNativeModule._drawing_Canvas_drawCircle(this.peer!.ptr, x, y, radius)
        }
        private drawImage_serialize(pixelmap: image.PixelMap, left: number, top: number, samplingOptions: SamplingOptions): void {
            ArkUIGeneratedNativeModule._drawing_Canvas_drawImage(this.peer!.ptr, toPeerPtr(pixelmap), left, top, toPeerPtr(samplingOptions))
        }
        private drawImageRect_serialize(pixelmap: image.PixelMap, dstRect: common2D.Rect, samplingOptions: SamplingOptions): void {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            common2D_Rect_serializer.write(thisSerializer, dstRect)
            ArkUIGeneratedNativeModule._drawing_Canvas_drawImageRect(this.peer!.ptr, toPeerPtr(pixelmap), thisSerializer.asBuffer(), thisSerializer.length(), toPeerPtr(samplingOptions))
            thisSerializer.release()
        }
        private drawImageRectWithSrc_serialize(pixelmap: image.PixelMap, srcRect: common2D.Rect, dstRect: common2D.Rect, samplingOptions: SamplingOptions, constraint: SrcRectConstraint): void {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            common2D_Rect_serializer.write(thisSerializer, srcRect)
            common2D_Rect_serializer.write(thisSerializer, dstRect)
            ArkUIGeneratedNativeModule._drawing_Canvas_drawImageRectWithSrc(this.peer!.ptr, toPeerPtr(pixelmap), thisSerializer.asBuffer(), thisSerializer.length(), toPeerPtr(samplingOptions), TypeChecker.drawing_SrcRectConstraint_ToNumeric(constraint))
            thisSerializer.release()
        }
        private drawColor0_serialize(color: common2D.Color, blendMode: BlendMode): void {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            common2D_Color_serializer.write(thisSerializer, color)
            ArkUIGeneratedNativeModule._drawing_Canvas_drawColor0(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length(), TypeChecker.drawing_BlendMode_ToNumeric(blendMode))
            thisSerializer.release()
        }
        private drawColor1_serialize(color: number, blendMode: BlendMode): void {
            ArkUIGeneratedNativeModule._drawing_Canvas_drawColor1(this.peer!.ptr, color, TypeChecker.drawing_BlendMode_ToNumeric(blendMode))
        }
        private drawColor2_serialize(alpha: number, red: number, green: number, blue: number, blendMode: BlendMode): void {
            ArkUIGeneratedNativeModule._drawing_Canvas_drawColor2(this.peer!.ptr, alpha, red, green, blue, TypeChecker.drawing_BlendMode_ToNumeric(blendMode))
        }
        private drawOval_serialize(oval: common2D.Rect): void {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            common2D_Rect_serializer.write(thisSerializer, oval)
            ArkUIGeneratedNativeModule._drawing_Canvas_drawOval(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
            thisSerializer.release()
        }
        private drawArc_serialize(arc: common2D.Rect, startAngle: number, sweepAngle: number): void {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            common2D_Rect_serializer.write(thisSerializer, arc)
            ArkUIGeneratedNativeModule._drawing_Canvas_drawArc(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length(), startAngle, sweepAngle)
            thisSerializer.release()
        }
        private drawPoint_serialize(x: number, y: number): void {
            ArkUIGeneratedNativeModule._drawing_Canvas_drawPoint(this.peer!.ptr, x, y)
        }
        private drawPoints_serialize(points: Array<common2D.Point>, mode: PointMode): void {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            thisSerializer.writeInt32((points.length).toInt())
            for (let points_counter_i = 0; points_counter_i < points.length; points_counter_i++) {
                const points_element : common2D.Point = points[points_counter_i]
                common2D_Point_serializer.write(thisSerializer, points_element)
            }
            ArkUIGeneratedNativeModule._drawing_Canvas_drawPoints(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length(), TypeChecker.drawing_PointMode_ToNumeric(mode))
            thisSerializer.release()
        }
        private drawPath_serialize(path: Path): void {
            ArkUIGeneratedNativeModule._drawing_Canvas_drawPath(this.peer!.ptr, toPeerPtr(path))
        }
        private drawLine_serialize(x0: number, y0: number, x1: number, y1: number): void {
            ArkUIGeneratedNativeModule._drawing_Canvas_drawLine(this.peer!.ptr, x0, y0, x1, y1)
        }
        private drawSingleCharacter_serialize(text: string, font: Font, x: number, y: number): void {
            ArkUIGeneratedNativeModule._drawing_Canvas_drawSingleCharacter(this.peer!.ptr, text, toPeerPtr(font), x, y)
        }
        private drawTextBlob_serialize(blob: TextBlob, x: number, y: number): void {
            ArkUIGeneratedNativeModule._drawing_Canvas_drawTextBlob(this.peer!.ptr, toPeerPtr(blob), x, y)
        }
        private drawPixelMapMesh_serialize(pixelmap: image.PixelMap, meshWidth: number, meshHeight: number, vertices: Array<number>, vertOffset: number, colors: Array<number>, colorOffset: number): void {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            thisSerializer.writeInt32((vertices.length).toInt())
            for (let vertices_counter_i = 0; vertices_counter_i < vertices.length; vertices_counter_i++) {
                const vertices_element : number = vertices[vertices_counter_i]
                thisSerializer.writeNumber(vertices_element)
            }
            thisSerializer.writeInt32((colors.length).toInt())
            for (let colors_counter_i = 0; colors_counter_i < colors.length; colors_counter_i++) {
                const colors_element : number = colors[colors_counter_i]
                thisSerializer.writeNumber(colors_element)
            }
            ArkUIGeneratedNativeModule._drawing_Canvas_drawPixelMapMesh(this.peer!.ptr, toPeerPtr(pixelmap), meshWidth, meshHeight, thisSerializer.asBuffer(), thisSerializer.length(), vertOffset, colorOffset)
            thisSerializer.release()
        }
        private drawRegion_serialize(region: Region): void {
            ArkUIGeneratedNativeModule._drawing_Canvas_drawRegion(this.peer!.ptr, toPeerPtr(region))
        }
        private attachPen_serialize(pen: Pen): void {
            ArkUIGeneratedNativeModule._drawing_Canvas_attachPen(this.peer!.ptr, toPeerPtr(pen))
        }
        private attachBrush_serialize(brush: Brush): void {
            ArkUIGeneratedNativeModule._drawing_Canvas_attachBrush(this.peer!.ptr, toPeerPtr(brush))
        }
        private detachPen_serialize(): void {
            ArkUIGeneratedNativeModule._drawing_Canvas_detachPen(this.peer!.ptr)
        }
        private detachBrush_serialize(): void {
            ArkUIGeneratedNativeModule._drawing_Canvas_detachBrush(this.peer!.ptr)
        }
        private save_serialize(): number {
            const retval  = ArkUIGeneratedNativeModule._drawing_Canvas_save(this.peer!.ptr)
            return retval
        }
        private saveLayer_serialize(rect: common2D.Rect | undefined, brush: Brush | undefined): number {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            let rect_type : int32 = RuntimeType.UNDEFINED
            rect_type = runtimeType(rect)
            thisSerializer.writeInt8((rect_type).toChar())
            if ((rect_type) != (RuntimeType.UNDEFINED)) {
                const rect_value  = rect!
                common2D_Rect_serializer.write(thisSerializer, rect_value)
            }
            let brush_type : int32 = RuntimeType.UNDEFINED
            brush_type = runtimeType(brush)
            thisSerializer.writeInt8((brush_type).toChar())
            if ((brush_type) != (RuntimeType.UNDEFINED)) {
                const brush_value  = brush!
                drawing_Brush_serializer.write(thisSerializer, brush_value)
            }
            const retval  = ArkUIGeneratedNativeModule._drawing_Canvas_saveLayer(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
            thisSerializer.release()
            return retval
        }
        private clear0_serialize(color: common2D.Color): void {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            common2D_Color_serializer.write(thisSerializer, color)
            ArkUIGeneratedNativeModule._drawing_Canvas_clear0(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
            thisSerializer.release()
        }
        private clear1_serialize(color: number): void {
            ArkUIGeneratedNativeModule._drawing_Canvas_clear1(this.peer!.ptr, color)
        }
        private restore_serialize(): void {
            ArkUIGeneratedNativeModule._drawing_Canvas_restore(this.peer!.ptr)
        }
        private restoreToCount_serialize(count: number): void {
            ArkUIGeneratedNativeModule._drawing_Canvas_restoreToCount(this.peer!.ptr, count)
        }
        private getSaveCount_serialize(): number {
            const retval  = ArkUIGeneratedNativeModule._drawing_Canvas_getSaveCount(this.peer!.ptr)
            return retval
        }
        private getWidth_serialize(): number {
            const retval  = ArkUIGeneratedNativeModule._drawing_Canvas_getWidth(this.peer!.ptr)
            return retval
        }
        private getHeight_serialize(): number {
            const retval  = ArkUIGeneratedNativeModule._drawing_Canvas_getHeight(this.peer!.ptr)
            return retval
        }
        private getLocalClipBounds_serialize(): common2D.Rect {
            const retval  = ArkUIGeneratedNativeModule._drawing_Canvas_getLocalClipBounds(this.peer!.ptr)
            let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
            const returnResult : common2D.Rect = common2D_Rect_serializer.read(retvalDeserializer)
            return returnResult
        }
        private getTotalMatrix_serialize(): Matrix {
            const retval  = ArkUIGeneratedNativeModule._drawing_Canvas_getTotalMatrix(this.peer!.ptr)
            const obj : Matrix = drawing.MatrixInternal.fromPtr(retval)
            return obj
        }
        private scale_serialize(sx: number, sy: number): void {
            ArkUIGeneratedNativeModule._drawing_Canvas_scale(this.peer!.ptr, sx, sy)
        }
        private skew_serialize(sx: number, sy: number): void {
            ArkUIGeneratedNativeModule._drawing_Canvas_skew(this.peer!.ptr, sx, sy)
        }
        private rotate_serialize(degrees: number, sx: number, sy: number): void {
            ArkUIGeneratedNativeModule._drawing_Canvas_rotate(this.peer!.ptr, degrees, sx, sy)
        }
        private translate_serialize(dx: number, dy: number): void {
            ArkUIGeneratedNativeModule._drawing_Canvas_translate(this.peer!.ptr, dx, dy)
        }
        private clipPath_serialize(path: Path, clipOp: ClipOp, doAntiAlias: boolean): void {
            ArkUIGeneratedNativeModule._drawing_Canvas_clipPath(this.peer!.ptr, toPeerPtr(path), TypeChecker.drawing_ClipOp_ToNumeric(clipOp), doAntiAlias ? 1 : 0)
        }
        private clipRect_serialize(rect: common2D.Rect, clipOp: ClipOp, doAntiAlias: boolean): void {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            common2D_Rect_serializer.write(thisSerializer, rect)
            ArkUIGeneratedNativeModule._drawing_Canvas_clipRect(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length(), TypeChecker.drawing_ClipOp_ToNumeric(clipOp), doAntiAlias ? 1 : 0)
            thisSerializer.release()
        }
        private concatMatrix_serialize(matrix: Matrix): void {
            ArkUIGeneratedNativeModule._drawing_Canvas_concatMatrix(this.peer!.ptr, toPeerPtr(matrix))
        }
        private clipRegion_serialize(region: Region, clipOp: ClipOp): void {
            ArkUIGeneratedNativeModule._drawing_Canvas_clipRegion(this.peer!.ptr, toPeerPtr(region), TypeChecker.drawing_ClipOp_ToNumeric(clipOp))
        }
        private clipRoundRect_serialize(roundRect: RoundRect, clipOp: ClipOp, doAntiAlias: boolean): void {
            ArkUIGeneratedNativeModule._drawing_Canvas_clipRoundRect(this.peer!.ptr, toPeerPtr(roundRect), TypeChecker.drawing_ClipOp_ToNumeric(clipOp), doAntiAlias ? 1 : 0)
        }
        private isClipEmpty_serialize(): boolean {
            const retval  = ArkUIGeneratedNativeModule._drawing_Canvas_isClipEmpty(this.peer!.ptr)
            return retval
        }
        private setMatrix_serialize(matrix: Matrix): void {
            ArkUIGeneratedNativeModule._drawing_Canvas_setMatrix(this.peer!.ptr, toPeerPtr(matrix))
        }
        private resetMatrix_serialize(): void {
            ArkUIGeneratedNativeModule._drawing_Canvas_resetMatrix(this.peer!.ptr)
        }
    }
    export class ColorFilterInternal {
        public static fromPtr(ptr: KPointer): drawing.ColorFilter {
            return new drawing.ColorFilter(ptr)
        }
    }
    export class ColorFilter implements MaterializedBase {
        peer?: Finalizable | undefined = undefined
        public getPeer(): Finalizable | undefined {
            return this.peer
        }
        constructor(peerPtr: KPointer) {
            this.peer = new Finalizable(peerPtr, ColorFilter.getFinalizer())
        }
        constructor() {
            this(ColorFilter.construct())
        }
        static construct(): KPointer {
            const retval  = ArkUIGeneratedNativeModule._drawing_ColorFilter_construct()
            return retval
        }
        static getFinalizer(): KPointer {
            return ArkUIGeneratedNativeModule._drawing_ColorFilter_getFinalizer()
        }
        private static createBlendModeColorFilter0_serialize(color: common2D.Color, mode: BlendMode): ColorFilter {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            common2D_Color_serializer.write(thisSerializer, color)
            const retval  = ArkUIGeneratedNativeModule._drawing_ColorFilter_createBlendModeColorFilter0(thisSerializer.asBuffer(), thisSerializer.length(), TypeChecker.drawing_BlendMode_ToNumeric(mode))
            thisSerializer.release()
            const obj : ColorFilter = drawing.ColorFilterInternal.fromPtr(retval)
            return obj
        }
        private static createBlendModeColorFilter1_serialize(color: number, mode: BlendMode): ColorFilter {
            const retval  = ArkUIGeneratedNativeModule._drawing_ColorFilter_createBlendModeColorFilter1(color, TypeChecker.drawing_BlendMode_ToNumeric(mode))
            const obj : ColorFilter = drawing.ColorFilterInternal.fromPtr(retval)
            return obj
        }
        private static createComposeColorFilter_serialize(outer: ColorFilter, inner: ColorFilter): ColorFilter {
            const retval  = ArkUIGeneratedNativeModule._drawing_ColorFilter_createComposeColorFilter(toPeerPtr(outer), toPeerPtr(inner))
            const obj : ColorFilter = drawing.ColorFilterInternal.fromPtr(retval)
            return obj
        }
        private static createLinearToSRGBGamma_serialize(): ColorFilter {
            const retval  = ArkUIGeneratedNativeModule._drawing_ColorFilter_createLinearToSRGBGamma()
            const obj : ColorFilter = drawing.ColorFilterInternal.fromPtr(retval)
            return obj
        }
        private static createSRGBGammaToLinear_serialize(): ColorFilter {
            const retval  = ArkUIGeneratedNativeModule._drawing_ColorFilter_createSRGBGammaToLinear()
            const obj : ColorFilter = drawing.ColorFilterInternal.fromPtr(retval)
            return obj
        }
        private static createLumaColorFilter_serialize(): ColorFilter {
            const retval  = ArkUIGeneratedNativeModule._drawing_ColorFilter_createLumaColorFilter()
            const obj : ColorFilter = drawing.ColorFilterInternal.fromPtr(retval)
            return obj
        }
        private static createMatrixColorFilter_serialize(matrix: Array<number>): ColorFilter {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            thisSerializer.writeInt32((matrix.length).toInt())
            for (let matrix_counter_i = 0; matrix_counter_i < matrix.length; matrix_counter_i++) {
                const matrix_element : number = matrix[matrix_counter_i]
                thisSerializer.writeNumber(matrix_element)
            }
            const retval  = ArkUIGeneratedNativeModule._drawing_ColorFilter_createMatrixColorFilter(thisSerializer.asBuffer(), thisSerializer.length())
            thisSerializer.release()
            const obj : ColorFilter = drawing.ColorFilterInternal.fromPtr(retval)
            return obj
        }
        public static createBlendModeColorFilter(color: common2D.Color, mode: BlendMode): ColorFilter {
            const color_casted = color as (common2D.Color)
            const mode_casted = mode as (BlendMode)
            return ColorFilter.createBlendModeColorFilter0_serialize(color_casted, mode_casted)
        }
        public static createBlendModeColorFilter(color: number, mode: BlendMode): ColorFilter {
            const color_casted = color as (number)
            const mode_casted = mode as (BlendMode)
            return ColorFilter.createBlendModeColorFilter1_serialize(color_casted, mode_casted)
        }
        public static createComposeColorFilter(outer: ColorFilter, inner: ColorFilter): ColorFilter {
            const outer_casted = outer as (ColorFilter)
            const inner_casted = inner as (ColorFilter)
            return ColorFilter.createComposeColorFilter_serialize(outer_casted, inner_casted)
        }
        public static createLinearToSRGBGamma(): ColorFilter {
            return ColorFilter.createLinearToSRGBGamma_serialize()
        }
        public static createSRGBGammaToLinear(): ColorFilter {
            return ColorFilter.createSRGBGammaToLinear_serialize()
        }
        public static createLumaColorFilter(): ColorFilter {
            return ColorFilter.createLumaColorFilter_serialize()
        }
        public static createMatrixColorFilter(matrix: Array<number>): ColorFilter {
            const matrix_casted = matrix as (Array<number>)
            return ColorFilter.createMatrixColorFilter_serialize(matrix_casted)
        }
    }
    export class FontInternal {
        public static fromPtr(ptr: KPointer): drawing.Font {
            return new drawing.Font(ptr)
        }
    }
    export class Font implements MaterializedBase {
        peer?: Finalizable | undefined = undefined
        public getPeer(): Finalizable | undefined {
            return this.peer
        }
        constructor(peerPtr: KPointer) {
            this.peer = new Finalizable(peerPtr, Font.getFinalizer())
        }
        constructor() {
            this(Font.construct())
        }
        static construct(): KPointer {
            const retval  = ArkUIGeneratedNativeModule._drawing_Font_construct()
            return retval
        }
        static getFinalizer(): KPointer {
            return ArkUIGeneratedNativeModule._drawing_Font_getFinalizer()
        }
        public enableSubpixel(isSubpixel: boolean): void {
            const isSubpixel_casted = isSubpixel as (boolean)
            this.enableSubpixel_serialize(isSubpixel_casted)
            return
        }
        public enableEmbolden(isEmbolden: boolean): void {
            const isEmbolden_casted = isEmbolden as (boolean)
            this.enableEmbolden_serialize(isEmbolden_casted)
            return
        }
        public enableLinearMetrics(isLinearMetrics: boolean): void {
            const isLinearMetrics_casted = isLinearMetrics as (boolean)
            this.enableLinearMetrics_serialize(isLinearMetrics_casted)
            return
        }
        public setSize(textSize: number): void {
            const textSize_casted = textSize as (number)
            this.setSize_serialize(textSize_casted)
            return
        }
        public getSize(): number {
            return this.getSize_serialize()
        }
        public setTypeface(typeface: Typeface): void {
            const typeface_casted = typeface as (Typeface)
            this.setTypeface_serialize(typeface_casted)
            return
        }
        public getTypeface(): Typeface {
            return this.getTypeface_serialize()
        }
        public getMetrics(): FontMetrics {
            return this.getMetrics_serialize()
        }
        public measureSingleCharacter(text: string): number {
            const text_casted = text as (string)
            return this.measureSingleCharacter_serialize(text_casted)
        }
        public measureText(text: string, encoding: TextEncoding): number {
            const text_casted = text as (string)
            const encoding_casted = encoding as (TextEncoding)
            return this.measureText_serialize(text_casted, encoding_casted)
        }
        public setScaleX(scaleX: number): void {
            const scaleX_casted = scaleX as (number)
            this.setScaleX_serialize(scaleX_casted)
            return
        }
        public setSkewX(skewX: number): void {
            const skewX_casted = skewX as (number)
            this.setSkewX_serialize(skewX_casted)
            return
        }
        public setEdging(edging: FontEdging): void {
            const edging_casted = edging as (FontEdging)
            this.setEdging_serialize(edging_casted)
            return
        }
        public setHinting(hinting: FontHinting): void {
            const hinting_casted = hinting as (FontHinting)
            this.setHinting_serialize(hinting_casted)
            return
        }
        public countText(text: string): number {
            const text_casted = text as (string)
            return this.countText_serialize(text_casted)
        }
        public setBaselineSnap(isBaselineSnap: boolean): void {
            const isBaselineSnap_casted = isBaselineSnap as (boolean)
            this.setBaselineSnap_serialize(isBaselineSnap_casted)
            return
        }
        public isBaselineSnap(): boolean {
            return this.isBaselineSnap_serialize()
        }
        public setEmbeddedBitmaps(isEmbeddedBitmaps: boolean): void {
            const isEmbeddedBitmaps_casted = isEmbeddedBitmaps as (boolean)
            this.setEmbeddedBitmaps_serialize(isEmbeddedBitmaps_casted)
            return
        }
        public isEmbeddedBitmaps(): boolean {
            return this.isEmbeddedBitmaps_serialize()
        }
        public setForceAutoHinting(isForceAutoHinting: boolean): void {
            const isForceAutoHinting_casted = isForceAutoHinting as (boolean)
            this.setForceAutoHinting_serialize(isForceAutoHinting_casted)
            return
        }
        public isForceAutoHinting(): boolean {
            return this.isForceAutoHinting_serialize()
        }
        public getWidths(glyphs: Array<number>): Array<number> {
            const glyphs_casted = glyphs as (Array<number>)
            return this.getWidths_serialize(glyphs_casted)
        }
        public textToGlyphs(text: string, glyphCount: number): Array<number> {
            const text_casted = text as (string)
            const glyphCount_casted = glyphCount as (number)
            return this.textToGlyphs_serialize(text_casted, glyphCount_casted)
        }
        public isSubpixel(): boolean {
            return this.isSubpixel_serialize()
        }
        public isLinearMetrics(): boolean {
            return this.isLinearMetrics_serialize()
        }
        public getSkewX(): number {
            return this.getSkewX_serialize()
        }
        public isEmbolden(): boolean {
            return this.isEmbolden_serialize()
        }
        public getScaleX(): number {
            return this.getScaleX_serialize()
        }
        public getHinting(): FontHinting {
            return this.getHinting_serialize()
        }
        public getEdging(): FontEdging {
            return this.getEdging_serialize()
        }
        public createPathForGlyph(index: number): Path {
            const index_casted = index as (number)
            return this.createPathForGlyph_serialize(index_casted)
        }
        public getBounds(glyphs: Array<number>): Array<common2D.Rect> {
            const glyphs_casted = glyphs as (Array<number>)
            return this.getBounds_serialize(glyphs_casted)
        }
        public getTextPath(text: string, byteLength: number, x: number, y: number): Path {
            const text_casted = text as (string)
            const byteLength_casted = byteLength as (number)
            const x_casted = x as (number)
            const y_casted = y as (number)
            return this.getTextPath_serialize(text_casted, byteLength_casted, x_casted, y_casted)
        }
        private enableSubpixel_serialize(isSubpixel: boolean): void {
            ArkUIGeneratedNativeModule._drawing_Font_enableSubpixel(this.peer!.ptr, isSubpixel ? 1 : 0)
        }
        private enableEmbolden_serialize(isEmbolden: boolean): void {
            ArkUIGeneratedNativeModule._drawing_Font_enableEmbolden(this.peer!.ptr, isEmbolden ? 1 : 0)
        }
        private enableLinearMetrics_serialize(isLinearMetrics: boolean): void {
            ArkUIGeneratedNativeModule._drawing_Font_enableLinearMetrics(this.peer!.ptr, isLinearMetrics ? 1 : 0)
        }
        private setSize_serialize(textSize: number): void {
            ArkUIGeneratedNativeModule._drawing_Font_setSize(this.peer!.ptr, textSize)
        }
        private getSize_serialize(): number {
            const retval  = ArkUIGeneratedNativeModule._drawing_Font_getSize(this.peer!.ptr)
            return retval
        }
        private setTypeface_serialize(typeface: Typeface): void {
            ArkUIGeneratedNativeModule._drawing_Font_setTypeface(this.peer!.ptr, toPeerPtr(typeface))
        }
        private getTypeface_serialize(): Typeface {
            const retval  = ArkUIGeneratedNativeModule._drawing_Font_getTypeface(this.peer!.ptr)
            const obj : Typeface = drawing.TypefaceInternal.fromPtr(retval)
            return obj
        }
        private getMetrics_serialize(): FontMetrics {
            const retval  = ArkUIGeneratedNativeModule._drawing_Font_getMetrics(this.peer!.ptr)
            let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
            const returnResult : FontMetrics = drawing_FontMetrics_serializer.read(retvalDeserializer)
            return returnResult
        }
        private measureSingleCharacter_serialize(text: string): number {
            const retval  = ArkUIGeneratedNativeModule._drawing_Font_measureSingleCharacter(this.peer!.ptr, text)
            return retval
        }
        private measureText_serialize(text: string, encoding: TextEncoding): number {
            const retval  = ArkUIGeneratedNativeModule._drawing_Font_measureText(this.peer!.ptr, text, TypeChecker.drawing_TextEncoding_ToNumeric(encoding))
            return retval
        }
        private setScaleX_serialize(scaleX: number): void {
            ArkUIGeneratedNativeModule._drawing_Font_setScaleX(this.peer!.ptr, scaleX)
        }
        private setSkewX_serialize(skewX: number): void {
            ArkUIGeneratedNativeModule._drawing_Font_setSkewX(this.peer!.ptr, skewX)
        }
        private setEdging_serialize(edging: FontEdging): void {
            ArkUIGeneratedNativeModule._drawing_Font_setEdging(this.peer!.ptr, TypeChecker.drawing_FontEdging_ToNumeric(edging))
        }
        private setHinting_serialize(hinting: FontHinting): void {
            ArkUIGeneratedNativeModule._drawing_Font_setHinting(this.peer!.ptr, TypeChecker.drawing_FontHinting_ToNumeric(hinting))
        }
        private countText_serialize(text: string): number {
            const retval  = ArkUIGeneratedNativeModule._drawing_Font_countText(this.peer!.ptr, text)
            return retval
        }
        private setBaselineSnap_serialize(isBaselineSnap: boolean): void {
            ArkUIGeneratedNativeModule._drawing_Font_setBaselineSnap(this.peer!.ptr, isBaselineSnap ? 1 : 0)
        }
        private isBaselineSnap_serialize(): boolean {
            const retval  = ArkUIGeneratedNativeModule._drawing_Font_isBaselineSnap(this.peer!.ptr)
            return retval
        }
        private setEmbeddedBitmaps_serialize(isEmbeddedBitmaps: boolean): void {
            ArkUIGeneratedNativeModule._drawing_Font_setEmbeddedBitmaps(this.peer!.ptr, isEmbeddedBitmaps ? 1 : 0)
        }
        private isEmbeddedBitmaps_serialize(): boolean {
            const retval  = ArkUIGeneratedNativeModule._drawing_Font_isEmbeddedBitmaps(this.peer!.ptr)
            return retval
        }
        private setForceAutoHinting_serialize(isForceAutoHinting: boolean): void {
            ArkUIGeneratedNativeModule._drawing_Font_setForceAutoHinting(this.peer!.ptr, isForceAutoHinting ? 1 : 0)
        }
        private isForceAutoHinting_serialize(): boolean {
            const retval  = ArkUIGeneratedNativeModule._drawing_Font_isForceAutoHinting(this.peer!.ptr)
            return retval
        }
        private getWidths_serialize(glyphs: Array<number>): Array<number> {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            thisSerializer.writeInt32((glyphs.length).toInt())
            for (let glyphs_counter_i = 0; glyphs_counter_i < glyphs.length; glyphs_counter_i++) {
                const glyphs_element : number = glyphs[glyphs_counter_i]
                thisSerializer.writeNumber(glyphs_element)
            }
            const retval  = ArkUIGeneratedNativeModule._drawing_Font_getWidths(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        private textToGlyphs_serialize(text: string, glyphCount: number): Array<number> {
            const retval  = ArkUIGeneratedNativeModule._drawing_Font_textToGlyphs(this.peer!.ptr, text, glyphCount)
            let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
            const buffer_length : int32 = retvalDeserializer.readInt32()
            let buffer : Array<number> = new Array<number>(buffer_length)
            for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
                buffer[buffer_i] = (retvalDeserializer.readNumber() as number)
            }
            const returnResult : Array<number> = buffer
            return returnResult
        }
        private isSubpixel_serialize(): boolean {
            const retval  = ArkUIGeneratedNativeModule._drawing_Font_isSubpixel(this.peer!.ptr)
            return retval
        }
        private isLinearMetrics_serialize(): boolean {
            const retval  = ArkUIGeneratedNativeModule._drawing_Font_isLinearMetrics(this.peer!.ptr)
            return retval
        }
        private getSkewX_serialize(): number {
            const retval  = ArkUIGeneratedNativeModule._drawing_Font_getSkewX(this.peer!.ptr)
            return retval
        }
        private isEmbolden_serialize(): boolean {
            const retval  = ArkUIGeneratedNativeModule._drawing_Font_isEmbolden(this.peer!.ptr)
            return retval
        }
        private getScaleX_serialize(): number {
            const retval  = ArkUIGeneratedNativeModule._drawing_Font_getScaleX(this.peer!.ptr)
            return retval
        }
        private getHinting_serialize(): FontHinting {
            const retval  = ArkUIGeneratedNativeModule._drawing_Font_getHinting(this.peer!.ptr)
            return TypeChecker.drawing_FontHinting_FromNumeric(retval)
        }
        private getEdging_serialize(): FontEdging {
            const retval  = ArkUIGeneratedNativeModule._drawing_Font_getEdging(this.peer!.ptr)
            return TypeChecker.drawing_FontEdging_FromNumeric(retval)
        }
        private createPathForGlyph_serialize(index: number): Path {
            const retval  = ArkUIGeneratedNativeModule._drawing_Font_createPathForGlyph(this.peer!.ptr, index)
            const obj : Path = drawing.PathInternal.fromPtr(retval)
            return obj
        }
        private getBounds_serialize(glyphs: Array<number>): Array<common2D.Rect> {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            thisSerializer.writeInt32((glyphs.length).toInt())
            for (let glyphs_counter_i = 0; glyphs_counter_i < glyphs.length; glyphs_counter_i++) {
                const glyphs_element : number = glyphs[glyphs_counter_i]
                thisSerializer.writeNumber(glyphs_element)
            }
            const retval  = ArkUIGeneratedNativeModule._drawing_Font_getBounds(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
            thisSerializer.release()
            let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
            const buffer_length : int32 = retvalDeserializer.readInt32()
            let buffer : Array<common2D.Rect> = new Array<common2D.Rect>(buffer_length)
            for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
                buffer[buffer_i] = common2D_Rect_serializer.read(retvalDeserializer)
            }
            const returnResult : Array<common2D.Rect> = buffer
            return returnResult
        }
        private getTextPath_serialize(text: string, byteLength: number, x: number, y: number): Path {
            const retval  = ArkUIGeneratedNativeModule._drawing_Font_getTextPath(this.peer!.ptr, text, byteLength, x, y)
            const obj : Path = drawing.PathInternal.fromPtr(retval)
            return obj
        }
    }
    export class ImageFilterInternal {
        public static fromPtr(ptr: KPointer): drawing.ImageFilter {
            return new drawing.ImageFilter(ptr)
        }
    }
    export class ImageFilter implements MaterializedBase {
        peer?: Finalizable | undefined = undefined
        public getPeer(): Finalizable | undefined {
            return this.peer
        }
        constructor(peerPtr: KPointer) {
            this.peer = new Finalizable(peerPtr, ImageFilter.getFinalizer())
        }
        constructor() {
            this(ImageFilter.construct())
        }
        static construct(): KPointer {
            const retval  = ArkUIGeneratedNativeModule._drawing_ImageFilter_construct()
            return retval
        }
        static getFinalizer(): KPointer {
            return ArkUIGeneratedNativeModule._drawing_ImageFilter_getFinalizer()
        }
        private static createBlurImageFilter_serialize(sigmaX: number, sigmaY: number, tileMode: TileMode, imageFilter: ImageFilter | undefined): ImageFilter {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            let imageFilter_type : int32 = RuntimeType.UNDEFINED
            imageFilter_type = runtimeType(imageFilter)
            thisSerializer.writeInt8((imageFilter_type).toChar())
            if ((imageFilter_type) != (RuntimeType.UNDEFINED)) {
                const imageFilter_value  = imageFilter!
                drawing_ImageFilter_serializer.write(thisSerializer, imageFilter_value)
            }
            const retval  = ArkUIGeneratedNativeModule._drawing_ImageFilter_createBlurImageFilter(sigmaX, sigmaY, TypeChecker.drawing_TileMode_ToNumeric(tileMode), thisSerializer.asBuffer(), thisSerializer.length())
            thisSerializer.release()
            const obj : ImageFilter = drawing.ImageFilterInternal.fromPtr(retval)
            return obj
        }
        private static createFromColorFilter_serialize(colorFilter: ColorFilter, imageFilter: ImageFilter | undefined): ImageFilter {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            let imageFilter_type : int32 = RuntimeType.UNDEFINED
            imageFilter_type = runtimeType(imageFilter)
            thisSerializer.writeInt8((imageFilter_type).toChar())
            if ((imageFilter_type) != (RuntimeType.UNDEFINED)) {
                const imageFilter_value  = imageFilter!
                drawing_ImageFilter_serializer.write(thisSerializer, imageFilter_value)
            }
            const retval  = ArkUIGeneratedNativeModule._drawing_ImageFilter_createFromColorFilter(toPeerPtr(colorFilter), thisSerializer.asBuffer(), thisSerializer.length())
            thisSerializer.release()
            const obj : ImageFilter = drawing.ImageFilterInternal.fromPtr(retval)
            return obj
        }
        public static createBlurImageFilter(sigmaX: number, sigmaY: number, tileMode: TileMode, imageFilter: ImageFilter | undefined): ImageFilter {
            const sigmaX_casted = sigmaX as (number)
            const sigmaY_casted = sigmaY as (number)
            const tileMode_casted = tileMode as (TileMode)
            const imageFilter_casted = imageFilter as (ImageFilter | undefined)
            return ImageFilter.createBlurImageFilter_serialize(sigmaX_casted, sigmaY_casted, tileMode_casted, imageFilter_casted)
        }
        public static createFromColorFilter(colorFilter: ColorFilter, imageFilter: ImageFilter | undefined): ImageFilter {
            const colorFilter_casted = colorFilter as (ColorFilter)
            const imageFilter_casted = imageFilter as (ImageFilter | undefined)
            return ImageFilter.createFromColorFilter_serialize(colorFilter_casted, imageFilter_casted)
        }
    }
    export class LatticeInternal {
        public static fromPtr(ptr: KPointer): drawing.Lattice {
            return new drawing.Lattice(ptr)
        }
    }
    export class Lattice implements MaterializedBase {
        peer?: Finalizable | undefined = undefined
        public getPeer(): Finalizable | undefined {
            return this.peer
        }
        constructor(peerPtr: KPointer) {
            this.peer = new Finalizable(peerPtr, Lattice.getFinalizer())
        }
        constructor() {
            this(Lattice.construct())
        }
        static construct(): KPointer {
            const retval  = ArkUIGeneratedNativeModule._drawing_Lattice_construct()
            return retval
        }
        static getFinalizer(): KPointer {
            return ArkUIGeneratedNativeModule._drawing_Lattice_getFinalizer()
        }
        private static createImageLattice_serialize<T>(xDivs: Array<number>, yDivs: Array<number>, fXCount: number, fYCount: number, fBounds: common2D.Rect | undefined, fRectTypes: Array<RectType> | undefined, fColors: Array<T> | undefined): Lattice {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            thisSerializer.writeInt32((xDivs.length).toInt())
            for (let xDivs_counter_i = 0; xDivs_counter_i < xDivs.length; xDivs_counter_i++) {
                const xDivs_element : number = xDivs[xDivs_counter_i]
                thisSerializer.writeNumber(xDivs_element)
            }
            thisSerializer.writeInt32((yDivs.length).toInt())
            for (let yDivs_counter_i = 0; yDivs_counter_i < yDivs.length; yDivs_counter_i++) {
                const yDivs_element : number = yDivs[yDivs_counter_i]
                thisSerializer.writeNumber(yDivs_element)
            }
            let fBounds_type : int32 = RuntimeType.UNDEFINED
            fBounds_type = runtimeType(fBounds)
            thisSerializer.writeInt8((fBounds_type).toChar())
            if ((fBounds_type) != (RuntimeType.UNDEFINED)) {
                const fBounds_value  = fBounds!
                common2D_Rect_serializer.write(thisSerializer, fBounds_value)
            }
            let fRectTypes_type : int32 = RuntimeType.UNDEFINED
            fRectTypes_type = runtimeType(fRectTypes)
            thisSerializer.writeInt8((fRectTypes_type).toChar())
            if ((fRectTypes_type) != (RuntimeType.UNDEFINED)) {
                const fRectTypes_value  = fRectTypes!
                thisSerializer.writeInt32((fRectTypes_value.length).toInt())
                for (let fRectTypes_value_counter_i = 0; fRectTypes_value_counter_i < fRectTypes_value.length; fRectTypes_value_counter_i++) {
                    const fRectTypes_value_element : RectType = fRectTypes_value[fRectTypes_value_counter_i]
                    thisSerializer.writeInt32(TypeChecker.drawing_RectType_ToNumeric(fRectTypes_value_element))
                }
            }
            let fColors_type : int32 = RuntimeType.UNDEFINED
            fColors_type = runtimeType(fColors)
            thisSerializer.writeInt8((fColors_type).toChar())
            if ((fColors_type) != (RuntimeType.UNDEFINED)) {
                const fColors_value  = fColors!
                thisSerializer.writeInt32((fColors_value.length).toInt())
                for (let fColors_value_counter_i = 0; fColors_value_counter_i < fColors_value.length; fColors_value_counter_i++) {
                    const fColors_value_element : T = fColors_value[fColors_value_counter_i]
                    thisSerializer.writeCustomObject("T", (fColors_value_element as Object))
                }
            }
            const retval  = ArkUIGeneratedNativeModule._drawing_Lattice_createImageLattice(thisSerializer.asBuffer(), thisSerializer.length(), fXCount, fYCount)
            thisSerializer.release()
            const obj : Lattice = drawing.LatticeInternal.fromPtr(retval)
            return obj
        }
        public static createImageLattice<T>(xDivs: Array<number>, yDivs: Array<number>, fXCount: number, fYCount: number, fBounds: common2D.Rect | undefined, fRectTypes: Array<RectType> | undefined, fColors: Array<T> | undefined): Lattice {
            const xDivs_casted = xDivs as (Array<number>)
            const yDivs_casted = yDivs as (Array<number>)
            const fXCount_casted = fXCount as (number)
            const fYCount_casted = fYCount as (number)
            const fBounds_casted = fBounds as (common2D.Rect | undefined)
            const fRectTypes_casted = fRectTypes as (Array<RectType> | undefined)
            const fColors_casted = fColors as (Array<T> | undefined)
            return Lattice.createImageLattice_serialize(xDivs_casted, yDivs_casted, fXCount_casted, fYCount_casted, fBounds_casted, fRectTypes_casted, fColors_casted)
        }
    }
    export class MaskFilterInternal {
        public static fromPtr(ptr: KPointer): drawing.MaskFilter {
            return new drawing.MaskFilter(ptr)
        }
    }
    export class MaskFilter implements MaterializedBase {
        peer?: Finalizable | undefined = undefined
        public getPeer(): Finalizable | undefined {
            return this.peer
        }
        constructor(peerPtr: KPointer) {
            this.peer = new Finalizable(peerPtr, MaskFilter.getFinalizer())
        }
        constructor() {
            this(MaskFilter.construct())
        }
        static construct(): KPointer {
            const retval  = ArkUIGeneratedNativeModule._drawing_MaskFilter_construct()
            return retval
        }
        static getFinalizer(): KPointer {
            return ArkUIGeneratedNativeModule._drawing_MaskFilter_getFinalizer()
        }
        private static createBlurMaskFilter_serialize(blurType: BlurType, sigma: number): MaskFilter {
            const retval  = ArkUIGeneratedNativeModule._drawing_MaskFilter_createBlurMaskFilter(TypeChecker.drawing_BlurType_ToNumeric(blurType), sigma)
            const obj : MaskFilter = drawing.MaskFilterInternal.fromPtr(retval)
            return obj
        }
        public static createBlurMaskFilter(blurType: BlurType, sigma: number): MaskFilter {
            const blurType_casted = blurType as (BlurType)
            const sigma_casted = sigma as (number)
            return MaskFilter.createBlurMaskFilter_serialize(blurType_casted, sigma_casted)
        }
    }
    export class MatrixInternal {
        public static fromPtr(ptr: KPointer): drawing.Matrix {
            return new drawing.Matrix(ptr)
        }
    }
    export class Matrix implements MaterializedBase {
        peer?: Finalizable | undefined = undefined
        public getPeer(): Finalizable | undefined {
            return this.peer
        }
        constructor(peerPtr: KPointer) {
            this.peer = new Finalizable(peerPtr, Matrix.getFinalizer())
        }
        constructor() {
            this(Matrix.construct())
        }
        static construct(): KPointer {
            const retval  = ArkUIGeneratedNativeModule._drawing_Matrix_construct()
            return retval
        }
        static getFinalizer(): KPointer {
            return ArkUIGeneratedNativeModule._drawing_Matrix_getFinalizer()
        }
        public setRotation(degree: number, px: number, py: number): void {
            const degree_casted = degree as (number)
            const px_casted = px as (number)
            const py_casted = py as (number)
            this.setRotation_serialize(degree_casted, px_casted, py_casted)
            return
        }
        public setScale(sx: number, sy: number, px: number, py: number): void {
            const sx_casted = sx as (number)
            const sy_casted = sy as (number)
            const px_casted = px as (number)
            const py_casted = py as (number)
            this.setScale_serialize(sx_casted, sy_casted, px_casted, py_casted)
            return
        }
        public setTranslation(dx: number, dy: number): void {
            const dx_casted = dx as (number)
            const dy_casted = dy as (number)
            this.setTranslation_serialize(dx_casted, dy_casted)
            return
        }
        public setMatrix(values: Array<number>): void {
            const values_casted = values as (Array<number>)
            this.setMatrix_serialize(values_casted)
            return
        }
        public preConcat(matrix: Matrix): void {
            const matrix_casted = matrix as (Matrix)
            this.preConcat_serialize(matrix_casted)
            return
        }
        public isEqual(matrix: Matrix): boolean {
            const matrix_casted = matrix as (Matrix)
            return this.isEqual_serialize(matrix_casted)
        }
        public invert(matrix: Matrix): boolean {
            const matrix_casted = matrix as (Matrix)
            return this.invert_serialize(matrix_casted)
        }
        public isIdentity(): boolean {
            return this.isIdentity_serialize()
        }
        public getValue(index: number): number {
            const index_casted = index as (number)
            return this.getValue_serialize(index_casted)
        }
        public postRotate(degree: number, px: number, py: number): void {
            const degree_casted = degree as (number)
            const px_casted = px as (number)
            const py_casted = py as (number)
            this.postRotate_serialize(degree_casted, px_casted, py_casted)
            return
        }
        public postScale(sx: number, sy: number, px: number, py: number): void {
            const sx_casted = sx as (number)
            const sy_casted = sy as (number)
            const px_casted = px as (number)
            const py_casted = py as (number)
            this.postScale_serialize(sx_casted, sy_casted, px_casted, py_casted)
            return
        }
        public postTranslate(dx: number, dy: number): void {
            const dx_casted = dx as (number)
            const dy_casted = dy as (number)
            this.postTranslate_serialize(dx_casted, dy_casted)
            return
        }
        public preRotate(degree: number, px: number, py: number): void {
            const degree_casted = degree as (number)
            const px_casted = px as (number)
            const py_casted = py as (number)
            this.preRotate_serialize(degree_casted, px_casted, py_casted)
            return
        }
        public preScale(sx: number, sy: number, px: number, py: number): void {
            const sx_casted = sx as (number)
            const sy_casted = sy as (number)
            const px_casted = px as (number)
            const py_casted = py as (number)
            this.preScale_serialize(sx_casted, sy_casted, px_casted, py_casted)
            return
        }
        public preTranslate(dx: number, dy: number): void {
            const dx_casted = dx as (number)
            const dy_casted = dy as (number)
            this.preTranslate_serialize(dx_casted, dy_casted)
            return
        }
        public reset(): void {
            this.reset_serialize()
            return
        }
        public mapPoints(src: Array<common2D.Point>): Array<common2D.Point> {
            const src_casted = src as (Array<common2D.Point>)
            return this.mapPoints_serialize(src_casted)
        }
        public getAll(): Array<number> {
            return this.getAll_serialize()
        }
        public mapRect(dst: common2D.Rect, src: common2D.Rect): boolean {
            const dst_casted = dst as (common2D.Rect)
            const src_casted = src as (common2D.Rect)
            return this.mapRect_serialize(dst_casted, src_casted)
        }
        public setRectToRect(src: common2D.Rect, dst: common2D.Rect, scaleToFit: ScaleToFit): boolean {
            const src_casted = src as (common2D.Rect)
            const dst_casted = dst as (common2D.Rect)
            const scaleToFit_casted = scaleToFit as (ScaleToFit)
            return this.setRectToRect_serialize(src_casted, dst_casted, scaleToFit_casted)
        }
        public setPolyToPoly(src: Array<common2D.Point>, dst: Array<common2D.Point>, count: number): boolean {
            const src_casted = src as (Array<common2D.Point>)
            const dst_casted = dst as (Array<common2D.Point>)
            const count_casted = count as (number)
            return this.setPolyToPoly_serialize(src_casted, dst_casted, count_casted)
        }
        private setRotation_serialize(degree: number, px: number, py: number): void {
            ArkUIGeneratedNativeModule._drawing_Matrix_setRotation(this.peer!.ptr, degree, px, py)
        }
        private setScale_serialize(sx: number, sy: number, px: number, py: number): void {
            ArkUIGeneratedNativeModule._drawing_Matrix_setScale(this.peer!.ptr, sx, sy, px, py)
        }
        private setTranslation_serialize(dx: number, dy: number): void {
            ArkUIGeneratedNativeModule._drawing_Matrix_setTranslation(this.peer!.ptr, dx, dy)
        }
        private setMatrix_serialize(values: Array<number>): void {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            thisSerializer.writeInt32((values.length).toInt())
            for (let values_counter_i = 0; values_counter_i < values.length; values_counter_i++) {
                const values_element : number = values[values_counter_i]
                thisSerializer.writeNumber(values_element)
            }
            ArkUIGeneratedNativeModule._drawing_Matrix_setMatrix(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
            thisSerializer.release()
        }
        private preConcat_serialize(matrix: Matrix): void {
            ArkUIGeneratedNativeModule._drawing_Matrix_preConcat(this.peer!.ptr, toPeerPtr(matrix))
        }
        private isEqual_serialize(matrix: Matrix): boolean {
            const retval  = ArkUIGeneratedNativeModule._drawing_Matrix_isEqual(this.peer!.ptr, toPeerPtr(matrix))
            return retval
        }
        private invert_serialize(matrix: Matrix): boolean {
            const retval  = ArkUIGeneratedNativeModule._drawing_Matrix_invert(this.peer!.ptr, toPeerPtr(matrix))
            return retval
        }
        private isIdentity_serialize(): boolean {
            const retval  = ArkUIGeneratedNativeModule._drawing_Matrix_isIdentity(this.peer!.ptr)
            return retval
        }
        private getValue_serialize(index: number): number {
            const retval  = ArkUIGeneratedNativeModule._drawing_Matrix_getValue(this.peer!.ptr, index)
            return retval
        }
        private postRotate_serialize(degree: number, px: number, py: number): void {
            ArkUIGeneratedNativeModule._drawing_Matrix_postRotate(this.peer!.ptr, degree, px, py)
        }
        private postScale_serialize(sx: number, sy: number, px: number, py: number): void {
            ArkUIGeneratedNativeModule._drawing_Matrix_postScale(this.peer!.ptr, sx, sy, px, py)
        }
        private postTranslate_serialize(dx: number, dy: number): void {
            ArkUIGeneratedNativeModule._drawing_Matrix_postTranslate(this.peer!.ptr, dx, dy)
        }
        private preRotate_serialize(degree: number, px: number, py: number): void {
            ArkUIGeneratedNativeModule._drawing_Matrix_preRotate(this.peer!.ptr, degree, px, py)
        }
        private preScale_serialize(sx: number, sy: number, px: number, py: number): void {
            ArkUIGeneratedNativeModule._drawing_Matrix_preScale(this.peer!.ptr, sx, sy, px, py)
        }
        private preTranslate_serialize(dx: number, dy: number): void {
            ArkUIGeneratedNativeModule._drawing_Matrix_preTranslate(this.peer!.ptr, dx, dy)
        }
        private reset_serialize(): void {
            ArkUIGeneratedNativeModule._drawing_Matrix_reset(this.peer!.ptr)
        }
        private mapPoints_serialize(src: Array<common2D.Point>): Array<common2D.Point> {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            thisSerializer.writeInt32((src.length).toInt())
            for (let src_counter_i = 0; src_counter_i < src.length; src_counter_i++) {
                const src_element : common2D.Point = src[src_counter_i]
                common2D_Point_serializer.write(thisSerializer, src_element)
            }
            const retval  = ArkUIGeneratedNativeModule._drawing_Matrix_mapPoints(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        private getAll_serialize(): Array<number> {
            const retval  = ArkUIGeneratedNativeModule._drawing_Matrix_getAll(this.peer!.ptr)
            let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
            const buffer_length : int32 = retvalDeserializer.readInt32()
            let buffer : Array<number> = new Array<number>(buffer_length)
            for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
                buffer[buffer_i] = (retvalDeserializer.readNumber() as number)
            }
            const returnResult : Array<number> = buffer
            return returnResult
        }
        private mapRect_serialize(dst: common2D.Rect, src: common2D.Rect): boolean {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            common2D_Rect_serializer.write(thisSerializer, dst)
            common2D_Rect_serializer.write(thisSerializer, src)
            const retval  = ArkUIGeneratedNativeModule._drawing_Matrix_mapRect(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
            thisSerializer.release()
            return retval
        }
        private setRectToRect_serialize(src: common2D.Rect, dst: common2D.Rect, scaleToFit: ScaleToFit): boolean {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            common2D_Rect_serializer.write(thisSerializer, src)
            common2D_Rect_serializer.write(thisSerializer, dst)
            const retval  = ArkUIGeneratedNativeModule._drawing_Matrix_setRectToRect(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length(), TypeChecker.drawing_ScaleToFit_ToNumeric(scaleToFit))
            thisSerializer.release()
            return retval
        }
        private setPolyToPoly_serialize(src: Array<common2D.Point>, dst: Array<common2D.Point>, count: number): boolean {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            thisSerializer.writeInt32((src.length).toInt())
            for (let src_counter_i = 0; src_counter_i < src.length; src_counter_i++) {
                const src_element : common2D.Point = src[src_counter_i]
                common2D_Point_serializer.write(thisSerializer, src_element)
            }
            thisSerializer.writeInt32((dst.length).toInt())
            for (let dst_counter_i = 0; dst_counter_i < dst.length; dst_counter_i++) {
                const dst_element : common2D.Point = dst[dst_counter_i]
                common2D_Point_serializer.write(thisSerializer, dst_element)
            }
            const retval  = ArkUIGeneratedNativeModule._drawing_Matrix_setPolyToPoly(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length(), count)
            thisSerializer.release()
            return retval
        }
    }
    export class PathInternal {
        public static fromPtr(ptr: KPointer): drawing.Path {
            return new drawing.Path(false, ptr)
        }
    }
    export class Path implements MaterializedBase {
        peer?: Finalizable | undefined = undefined
        public getPeer(): Finalizable | undefined {
            return this.peer
        }
        constructor(_0: boolean, peerPtr: KPointer) {
            this.peer = new Finalizable(peerPtr, Path.getFinalizer())
        }
        constructor() {
            this(false, Path.construct0())
        }
        constructor(path: Path) {
            this(false, Path.construct1(path))
        }
        static construct0(): KPointer {
            const retval  = ArkUIGeneratedNativeModule._drawing_Path_construct0()
            return retval
        }
        static construct1(path: Path): KPointer {
            const retval  = ArkUIGeneratedNativeModule._drawing_Path_construct1(toPeerPtr(path))
            return retval
        }
        static getFinalizer(): KPointer {
            return ArkUIGeneratedNativeModule._drawing_Path_getFinalizer()
        }
        public moveTo(x: number, y: number): void {
            const x_casted = x as (number)
            const y_casted = y as (number)
            this.moveTo_serialize(x_casted, y_casted)
            return
        }
        public lineTo(x: number, y: number): void {
            const x_casted = x as (number)
            const y_casted = y as (number)
            this.lineTo_serialize(x_casted, y_casted)
            return
        }
        public arcTo(x1: number, y1: number, x2: number, y2: number, startDeg: number, sweepDeg: number): void {
            const x1_casted = x1 as (number)
            const y1_casted = y1 as (number)
            const x2_casted = x2 as (number)
            const y2_casted = y2 as (number)
            const startDeg_casted = startDeg as (number)
            const sweepDeg_casted = sweepDeg as (number)
            this.arcTo_serialize(x1_casted, y1_casted, x2_casted, y2_casted, startDeg_casted, sweepDeg_casted)
            return
        }
        public quadTo(ctrlX: number, ctrlY: number, endX: number, endY: number): void {
            const ctrlX_casted = ctrlX as (number)
            const ctrlY_casted = ctrlY as (number)
            const endX_casted = endX as (number)
            const endY_casted = endY as (number)
            this.quadTo_serialize(ctrlX_casted, ctrlY_casted, endX_casted, endY_casted)
            return
        }
        public conicTo(ctrlX: number, ctrlY: number, endX: number, endY: number, weight: number): void {
            const ctrlX_casted = ctrlX as (number)
            const ctrlY_casted = ctrlY as (number)
            const endX_casted = endX as (number)
            const endY_casted = endY as (number)
            const weight_casted = weight as (number)
            this.conicTo_serialize(ctrlX_casted, ctrlY_casted, endX_casted, endY_casted, weight_casted)
            return
        }
        public cubicTo(ctrlX1: number, ctrlY1: number, ctrlX2: number, ctrlY2: number, endX: number, endY: number): void {
            const ctrlX1_casted = ctrlX1 as (number)
            const ctrlY1_casted = ctrlY1 as (number)
            const ctrlX2_casted = ctrlX2 as (number)
            const ctrlY2_casted = ctrlY2 as (number)
            const endX_casted = endX as (number)
            const endY_casted = endY as (number)
            this.cubicTo_serialize(ctrlX1_casted, ctrlY1_casted, ctrlX2_casted, ctrlY2_casted, endX_casted, endY_casted)
            return
        }
        public rMoveTo(dx: number, dy: number): void {
            const dx_casted = dx as (number)
            const dy_casted = dy as (number)
            this.rMoveTo_serialize(dx_casted, dy_casted)
            return
        }
        public rLineTo(dx: number, dy: number): void {
            const dx_casted = dx as (number)
            const dy_casted = dy as (number)
            this.rLineTo_serialize(dx_casted, dy_casted)
            return
        }
        public rQuadTo(dx1: number, dy1: number, dx2: number, dy2: number): void {
            const dx1_casted = dx1 as (number)
            const dy1_casted = dy1 as (number)
            const dx2_casted = dx2 as (number)
            const dy2_casted = dy2 as (number)
            this.rQuadTo_serialize(dx1_casted, dy1_casted, dx2_casted, dy2_casted)
            return
        }
        public rConicTo(ctrlX: number, ctrlY: number, endX: number, endY: number, weight: number): void {
            const ctrlX_casted = ctrlX as (number)
            const ctrlY_casted = ctrlY as (number)
            const endX_casted = endX as (number)
            const endY_casted = endY as (number)
            const weight_casted = weight as (number)
            this.rConicTo_serialize(ctrlX_casted, ctrlY_casted, endX_casted, endY_casted, weight_casted)
            return
        }
        public rCubicTo(ctrlX1: number, ctrlY1: number, ctrlX2: number, ctrlY2: number, endX: number, endY: number): void {
            const ctrlX1_casted = ctrlX1 as (number)
            const ctrlY1_casted = ctrlY1 as (number)
            const ctrlX2_casted = ctrlX2 as (number)
            const ctrlY2_casted = ctrlY2 as (number)
            const endX_casted = endX as (number)
            const endY_casted = endY as (number)
            this.rCubicTo_serialize(ctrlX1_casted, ctrlY1_casted, ctrlX2_casted, ctrlY2_casted, endX_casted, endY_casted)
            return
        }
        public addPolygon(points: Array<common2D.Point>, close: boolean): void {
            const points_casted = points as (Array<common2D.Point>)
            const close_casted = close as (boolean)
            this.addPolygon_serialize(points_casted, close_casted)
            return
        }
        public op(path: Path, pathOp: PathOp): boolean {
            const path_casted = path as (Path)
            const pathOp_casted = pathOp as (PathOp)
            return this.op_serialize(path_casted, pathOp_casted)
        }
        public addArc(rect: common2D.Rect, startAngle: number, sweepAngle: number): void {
            const rect_casted = rect as (common2D.Rect)
            const startAngle_casted = startAngle as (number)
            const sweepAngle_casted = sweepAngle as (number)
            this.addArc_serialize(rect_casted, startAngle_casted, sweepAngle_casted)
            return
        }
        public addCircle(x: number, y: number, radius: number, pathDirection: PathDirection): void {
            const x_casted = x as (number)
            const y_casted = y as (number)
            const radius_casted = radius as (number)
            const pathDirection_casted = pathDirection as (PathDirection)
            this.addCircle_serialize(x_casted, y_casted, radius_casted, pathDirection_casted)
            return
        }
        public addOval(rect: common2D.Rect, start: number, pathDirection: PathDirection): void {
            const rect_casted = rect as (common2D.Rect)
            const start_casted = start as (number)
            const pathDirection_casted = pathDirection as (PathDirection)
            this.addOval_serialize(rect_casted, start_casted, pathDirection_casted)
            return
        }
        public addRect(rect: common2D.Rect, pathDirection: PathDirection): void {
            const rect_casted = rect as (common2D.Rect)
            const pathDirection_casted = pathDirection as (PathDirection)
            this.addRect_serialize(rect_casted, pathDirection_casted)
            return
        }
        public addRoundRect(roundRect: RoundRect, pathDirection: PathDirection): void {
            const roundRect_casted = roundRect as (RoundRect)
            const pathDirection_casted = pathDirection as (PathDirection)
            this.addRoundRect_serialize(roundRect_casted, pathDirection_casted)
            return
        }
        public addPath(path: Path, matrix: Matrix | undefined): void {
            const path_casted = path as (Path)
            const matrix_casted = matrix as (Matrix | undefined)
            this.addPath_serialize(path_casted, matrix_casted)
            return
        }
        public transform(matrix: Matrix): void {
            const matrix_casted = matrix as (Matrix)
            this.transform_serialize(matrix_casted)
            return
        }
        public contains(x: number, y: number): boolean {
            const x_casted = x as (number)
            const y_casted = y as (number)
            return this.contains_serialize(x_casted, y_casted)
        }
        public setFillType(pathFillType: PathFillType): void {
            const pathFillType_casted = pathFillType as (PathFillType)
            this.setFillType_serialize(pathFillType_casted)
            return
        }
        public getBounds(): common2D.Rect {
            return this.getBounds_serialize()
        }
        public close(): void {
            this.close_serialize()
            return
        }
        public offset(dx: number, dy: number): Path {
            const dx_casted = dx as (number)
            const dy_casted = dy as (number)
            return this.offset_serialize(dx_casted, dy_casted)
        }
        public reset(): void {
            this.reset_serialize()
            return
        }
        public getLength(forceClosed: boolean): number {
            const forceClosed_casted = forceClosed as (boolean)
            return this.getLength_serialize(forceClosed_casted)
        }
        public getPositionAndTangent(forceClosed: boolean, distance: number, position: common2D.Point, tangent: common2D.Point): boolean {
            const forceClosed_casted = forceClosed as (boolean)
            const distance_casted = distance as (number)
            const position_casted = position as (common2D.Point)
            const tangent_casted = tangent as (common2D.Point)
            return this.getPositionAndTangent_serialize(forceClosed_casted, distance_casted, position_casted, tangent_casted)
        }
        public isClosed(): boolean {
            return this.isClosed_serialize()
        }
        public getMatrix(forceClosed: boolean, distance: number, matrix: Matrix, flags: PathMeasureMatrixFlags): boolean {
            const forceClosed_casted = forceClosed as (boolean)
            const distance_casted = distance as (number)
            const matrix_casted = matrix as (Matrix)
            const flags_casted = flags as (PathMeasureMatrixFlags)
            return this.getMatrix_serialize(forceClosed_casted, distance_casted, matrix_casted, flags_casted)
        }
        public buildFromSvgString(str: string): boolean {
            const str_casted = str as (string)
            return this.buildFromSvgString_serialize(str_casted)
        }
        private moveTo_serialize(x: number, y: number): void {
            ArkUIGeneratedNativeModule._drawing_Path_moveTo(this.peer!.ptr, x, y)
        }
        private lineTo_serialize(x: number, y: number): void {
            ArkUIGeneratedNativeModule._drawing_Path_lineTo(this.peer!.ptr, x, y)
        }
        private arcTo_serialize(x1: number, y1: number, x2: number, y2: number, startDeg: number, sweepDeg: number): void {
            ArkUIGeneratedNativeModule._drawing_Path_arcTo(this.peer!.ptr, x1, y1, x2, y2, startDeg, sweepDeg)
        }
        private quadTo_serialize(ctrlX: number, ctrlY: number, endX: number, endY: number): void {
            ArkUIGeneratedNativeModule._drawing_Path_quadTo(this.peer!.ptr, ctrlX, ctrlY, endX, endY)
        }
        private conicTo_serialize(ctrlX: number, ctrlY: number, endX: number, endY: number, weight: number): void {
            ArkUIGeneratedNativeModule._drawing_Path_conicTo(this.peer!.ptr, ctrlX, ctrlY, endX, endY, weight)
        }
        private cubicTo_serialize(ctrlX1: number, ctrlY1: number, ctrlX2: number, ctrlY2: number, endX: number, endY: number): void {
            ArkUIGeneratedNativeModule._drawing_Path_cubicTo(this.peer!.ptr, ctrlX1, ctrlY1, ctrlX2, ctrlY2, endX, endY)
        }
        private rMoveTo_serialize(dx: number, dy: number): void {
            ArkUIGeneratedNativeModule._drawing_Path_rMoveTo(this.peer!.ptr, dx, dy)
        }
        private rLineTo_serialize(dx: number, dy: number): void {
            ArkUIGeneratedNativeModule._drawing_Path_rLineTo(this.peer!.ptr, dx, dy)
        }
        private rQuadTo_serialize(dx1: number, dy1: number, dx2: number, dy2: number): void {
            ArkUIGeneratedNativeModule._drawing_Path_rQuadTo(this.peer!.ptr, dx1, dy1, dx2, dy2)
        }
        private rConicTo_serialize(ctrlX: number, ctrlY: number, endX: number, endY: number, weight: number): void {
            ArkUIGeneratedNativeModule._drawing_Path_rConicTo(this.peer!.ptr, ctrlX, ctrlY, endX, endY, weight)
        }
        private rCubicTo_serialize(ctrlX1: number, ctrlY1: number, ctrlX2: number, ctrlY2: number, endX: number, endY: number): void {
            ArkUIGeneratedNativeModule._drawing_Path_rCubicTo(this.peer!.ptr, ctrlX1, ctrlY1, ctrlX2, ctrlY2, endX, endY)
        }
        private addPolygon_serialize(points: Array<common2D.Point>, close: boolean): void {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            thisSerializer.writeInt32((points.length).toInt())
            for (let points_counter_i = 0; points_counter_i < points.length; points_counter_i++) {
                const points_element : common2D.Point = points[points_counter_i]
                common2D_Point_serializer.write(thisSerializer, points_element)
            }
            ArkUIGeneratedNativeModule._drawing_Path_addPolygon(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length(), close ? 1 : 0)
            thisSerializer.release()
        }
        private op_serialize(path: Path, pathOp: PathOp): boolean {
            const retval  = ArkUIGeneratedNativeModule._drawing_Path_op(this.peer!.ptr, toPeerPtr(path), TypeChecker.drawing_PathOp_ToNumeric(pathOp))
            return retval
        }
        private addArc_serialize(rect: common2D.Rect, startAngle: number, sweepAngle: number): void {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            common2D_Rect_serializer.write(thisSerializer, rect)
            ArkUIGeneratedNativeModule._drawing_Path_addArc(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length(), startAngle, sweepAngle)
            thisSerializer.release()
        }
        private addCircle_serialize(x: number, y: number, radius: number, pathDirection: PathDirection): void {
            ArkUIGeneratedNativeModule._drawing_Path_addCircle(this.peer!.ptr, x, y, radius, TypeChecker.drawing_PathDirection_ToNumeric(pathDirection))
        }
        private addOval_serialize(rect: common2D.Rect, start: number, pathDirection: PathDirection): void {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            common2D_Rect_serializer.write(thisSerializer, rect)
            ArkUIGeneratedNativeModule._drawing_Path_addOval(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length(), start, TypeChecker.drawing_PathDirection_ToNumeric(pathDirection))
            thisSerializer.release()
        }
        private addRect_serialize(rect: common2D.Rect, pathDirection: PathDirection): void {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            common2D_Rect_serializer.write(thisSerializer, rect)
            ArkUIGeneratedNativeModule._drawing_Path_addRect(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length(), TypeChecker.drawing_PathDirection_ToNumeric(pathDirection))
            thisSerializer.release()
        }
        private addRoundRect_serialize(roundRect: RoundRect, pathDirection: PathDirection): void {
            ArkUIGeneratedNativeModule._drawing_Path_addRoundRect(this.peer!.ptr, toPeerPtr(roundRect), TypeChecker.drawing_PathDirection_ToNumeric(pathDirection))
        }
        private addPath_serialize(path: Path, matrix: Matrix | undefined): void {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            let matrix_type : int32 = RuntimeType.UNDEFINED
            matrix_type = runtimeType(matrix)
            thisSerializer.writeInt8((matrix_type).toChar())
            if ((matrix_type) != (RuntimeType.UNDEFINED)) {
                const matrix_value  = matrix!
                drawing_Matrix_serializer.write(thisSerializer, matrix_value)
            }
            ArkUIGeneratedNativeModule._drawing_Path_addPath(this.peer!.ptr, toPeerPtr(path), thisSerializer.asBuffer(), thisSerializer.length())
            thisSerializer.release()
        }
        private transform_serialize(matrix: Matrix): void {
            ArkUIGeneratedNativeModule._drawing_Path_transform(this.peer!.ptr, toPeerPtr(matrix))
        }
        private contains_serialize(x: number, y: number): boolean {
            const retval  = ArkUIGeneratedNativeModule._drawing_Path_contains(this.peer!.ptr, x, y)
            return retval
        }
        private setFillType_serialize(pathFillType: PathFillType): void {
            ArkUIGeneratedNativeModule._drawing_Path_setFillType(this.peer!.ptr, TypeChecker.drawing_PathFillType_ToNumeric(pathFillType))
        }
        private getBounds_serialize(): common2D.Rect {
            const retval  = ArkUIGeneratedNativeModule._drawing_Path_getBounds(this.peer!.ptr)
            let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
            const returnResult : common2D.Rect = common2D_Rect_serializer.read(retvalDeserializer)
            return returnResult
        }
        private close_serialize(): void {
            ArkUIGeneratedNativeModule._drawing_Path_close(this.peer!.ptr)
        }
        private offset_serialize(dx: number, dy: number): Path {
            const retval  = ArkUIGeneratedNativeModule._drawing_Path_offset(this.peer!.ptr, dx, dy)
            const obj : Path = drawing.PathInternal.fromPtr(retval)
            return obj
        }
        private reset_serialize(): void {
            ArkUIGeneratedNativeModule._drawing_Path_reset(this.peer!.ptr)
        }
        private getLength_serialize(forceClosed: boolean): number {
            const retval  = ArkUIGeneratedNativeModule._drawing_Path_getLength(this.peer!.ptr, forceClosed ? 1 : 0)
            return retval
        }
        private getPositionAndTangent_serialize(forceClosed: boolean, distance: number, position: common2D.Point, tangent: common2D.Point): boolean {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            common2D_Point_serializer.write(thisSerializer, position)
            common2D_Point_serializer.write(thisSerializer, tangent)
            const retval  = ArkUIGeneratedNativeModule._drawing_Path_getPositionAndTangent(this.peer!.ptr, forceClosed ? 1 : 0, distance, thisSerializer.asBuffer(), thisSerializer.length())
            thisSerializer.release()
            return retval
        }
        private isClosed_serialize(): boolean {
            const retval  = ArkUIGeneratedNativeModule._drawing_Path_isClosed(this.peer!.ptr)
            return retval
        }
        private getMatrix_serialize(forceClosed: boolean, distance: number, matrix: Matrix, flags: PathMeasureMatrixFlags): boolean {
            const retval  = ArkUIGeneratedNativeModule._drawing_Path_getMatrix(this.peer!.ptr, forceClosed ? 1 : 0, distance, toPeerPtr(matrix), TypeChecker.drawing_PathMeasureMatrixFlags_ToNumeric(flags))
            return retval
        }
        private buildFromSvgString_serialize(str: string): boolean {
            const retval  = ArkUIGeneratedNativeModule._drawing_Path_buildFromSvgString(this.peer!.ptr, str)
            return retval
        }
    }
    export class PathEffectInternal {
        public static fromPtr(ptr: KPointer): drawing.PathEffect {
            return new drawing.PathEffect(ptr)
        }
    }
    export class PathEffect implements MaterializedBase {
        peer?: Finalizable | undefined = undefined
        public getPeer(): Finalizable | undefined {
            return this.peer
        }
        constructor(peerPtr: KPointer) {
            this.peer = new Finalizable(peerPtr, PathEffect.getFinalizer())
        }
        constructor() {
            this(PathEffect.construct())
        }
        static construct(): KPointer {
            const retval  = ArkUIGeneratedNativeModule._drawing_PathEffect_construct()
            return retval
        }
        static getFinalizer(): KPointer {
            return ArkUIGeneratedNativeModule._drawing_PathEffect_getFinalizer()
        }
        private static createDashPathEffect_serialize(intervals: Array<number>, phase: number): PathEffect {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            thisSerializer.writeInt32((intervals.length).toInt())
            for (let intervals_counter_i = 0; intervals_counter_i < intervals.length; intervals_counter_i++) {
                const intervals_element : number = intervals[intervals_counter_i]
                thisSerializer.writeNumber(intervals_element)
            }
            const retval  = ArkUIGeneratedNativeModule._drawing_PathEffect_createDashPathEffect(thisSerializer.asBuffer(), thisSerializer.length(), phase)
            thisSerializer.release()
            const obj : PathEffect = drawing.PathEffectInternal.fromPtr(retval)
            return obj
        }
        private static createCornerPathEffect_serialize(radius: number): PathEffect {
            const retval  = ArkUIGeneratedNativeModule._drawing_PathEffect_createCornerPathEffect(radius)
            const obj : PathEffect = drawing.PathEffectInternal.fromPtr(retval)
            return obj
        }
        public static createDashPathEffect(intervals: Array<number>, phase: number): PathEffect {
            const intervals_casted = intervals as (Array<number>)
            const phase_casted = phase as (number)
            return PathEffect.createDashPathEffect_serialize(intervals_casted, phase_casted)
        }
        public static createCornerPathEffect(radius: number): PathEffect {
            const radius_casted = radius as (number)
            return PathEffect.createCornerPathEffect_serialize(radius_casted)
        }
    }
    export class PenInternal {
        public static fromPtr(ptr: KPointer): drawing.Pen {
            return new drawing.Pen(false, ptr)
        }
    }
    export class Pen implements MaterializedBase {
        peer?: Finalizable | undefined = undefined
        public getPeer(): Finalizable | undefined {
            return this.peer
        }
        constructor(_0: boolean, peerPtr: KPointer) {
            this.peer = new Finalizable(peerPtr, Pen.getFinalizer())
        }
        constructor() {
            this(false, Pen.construct0())
        }
        constructor(pen: Pen) {
            this(false, Pen.construct1(pen))
        }
        static construct0(): KPointer {
            const retval  = ArkUIGeneratedNativeModule._drawing_Pen_construct0()
            return retval
        }
        static construct1(pen: Pen): KPointer {
            const retval  = ArkUIGeneratedNativeModule._drawing_Pen_construct1(toPeerPtr(pen))
            return retval
        }
        static getFinalizer(): KPointer {
            return ArkUIGeneratedNativeModule._drawing_Pen_getFinalizer()
        }
        public setMiterLimit(miter: number): void {
            const miter_casted = miter as (number)
            this.setMiterLimit_serialize(miter_casted)
            return
        }
        public getMiterLimit(): number {
            return this.getMiterLimit_serialize()
        }
        public setShaderEffect(shaderEffect: ShaderEffect): void {
            const shaderEffect_casted = shaderEffect as (ShaderEffect)
            this.setShaderEffect_serialize(shaderEffect_casted)
            return
        }
        public setColor(color: common2D.Color): void {
            const color_casted = color as (common2D.Color)
            this.setColor0_serialize(color_casted)
            return
        }
        public setColor(color: number): void {
            const color_casted = color as (number)
            this.setColor1_serialize(color_casted)
            return
        }
        public setColor(alpha: number, red: number, green: number, blue: number): void {
            const alpha_casted = alpha as (number)
            const red_casted = red as (number)
            const green_casted = green as (number)
            const blue_casted = blue as (number)
            this.setColor2_serialize(alpha_casted, red_casted, green_casted, blue_casted)
            return
        }
        public getColor(): common2D.Color {
            return this.getColor_serialize()
        }
        public getHexColor(): number {
            return this.getHexColor_serialize()
        }
        public setStrokeWidth(width: number): void {
            const width_casted = width as (number)
            this.setStrokeWidth_serialize(width_casted)
            return
        }
        public getWidth(): number {
            return this.getWidth_serialize()
        }
        public setAntiAlias(aa: boolean): void {
            const aa_casted = aa as (boolean)
            this.setAntiAlias_serialize(aa_casted)
            return
        }
        public isAntiAlias(): boolean {
            return this.isAntiAlias_serialize()
        }
        public setAlpha(alpha: number): void {
            const alpha_casted = alpha as (number)
            this.setAlpha_serialize(alpha_casted)
            return
        }
        public getAlpha(): number {
            return this.getAlpha_serialize()
        }
        public setColorFilter(filter: ColorFilter): void {
            const filter_casted = filter as (ColorFilter)
            this.setColorFilter_serialize(filter_casted)
            return
        }
        public getColorFilter(): ColorFilter {
            return this.getColorFilter_serialize()
        }
        public setImageFilter(filter: ImageFilter | undefined): void {
            const filter_casted = filter as (ImageFilter | undefined)
            this.setImageFilter_serialize(filter_casted)
            return
        }
        public setMaskFilter(filter: MaskFilter): void {
            const filter_casted = filter as (MaskFilter)
            this.setMaskFilter_serialize(filter_casted)
            return
        }
        public setPathEffect(effect: PathEffect): void {
            const effect_casted = effect as (PathEffect)
            this.setPathEffect_serialize(effect_casted)
            return
        }
        public setShadowLayer(shadowLayer: ShadowLayer): void {
            const shadowLayer_casted = shadowLayer as (ShadowLayer)
            this.setShadowLayer_serialize(shadowLayer_casted)
            return
        }
        public setBlendMode(mode: BlendMode): void {
            const mode_casted = mode as (BlendMode)
            this.setBlendMode_serialize(mode_casted)
            return
        }
        public setDither(dither: boolean): void {
            const dither_casted = dither as (boolean)
            this.setDither_serialize(dither_casted)
            return
        }
        public setJoinStyle(style: JoinStyle): void {
            const style_casted = style as (JoinStyle)
            this.setJoinStyle_serialize(style_casted)
            return
        }
        public getJoinStyle(): JoinStyle {
            return this.getJoinStyle_serialize()
        }
        public setCapStyle(style: CapStyle): void {
            const style_casted = style as (CapStyle)
            this.setCapStyle_serialize(style_casted)
            return
        }
        public getCapStyle(): CapStyle {
            return this.getCapStyle_serialize()
        }
        public reset(): void {
            this.reset_serialize()
            return
        }
        public getFillPath(src: Path, dst: Path): boolean {
            const src_casted = src as (Path)
            const dst_casted = dst as (Path)
            return this.getFillPath_serialize(src_casted, dst_casted)
        }
        private setMiterLimit_serialize(miter: number): void {
            ArkUIGeneratedNativeModule._drawing_Pen_setMiterLimit(this.peer!.ptr, miter)
        }
        private getMiterLimit_serialize(): number {
            const retval  = ArkUIGeneratedNativeModule._drawing_Pen_getMiterLimit(this.peer!.ptr)
            return retval
        }
        private setShaderEffect_serialize(shaderEffect: ShaderEffect): void {
            ArkUIGeneratedNativeModule._drawing_Pen_setShaderEffect(this.peer!.ptr, toPeerPtr(shaderEffect))
        }
        private setColor0_serialize(color: common2D.Color): void {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            common2D_Color_serializer.write(thisSerializer, color)
            ArkUIGeneratedNativeModule._drawing_Pen_setColor0(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
            thisSerializer.release()
        }
        private setColor1_serialize(color: number): void {
            ArkUIGeneratedNativeModule._drawing_Pen_setColor1(this.peer!.ptr, color)
        }
        private setColor2_serialize(alpha: number, red: number, green: number, blue: number): void {
            ArkUIGeneratedNativeModule._drawing_Pen_setColor2(this.peer!.ptr, alpha, red, green, blue)
        }
        private getColor_serialize(): common2D.Color {
            const retval  = ArkUIGeneratedNativeModule._drawing_Pen_getColor(this.peer!.ptr)
            let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
            const returnResult : common2D.Color = common2D_Color_serializer.read(retvalDeserializer)
            return returnResult
        }
        private getHexColor_serialize(): number {
            const retval  = ArkUIGeneratedNativeModule._drawing_Pen_getHexColor(this.peer!.ptr)
            return retval
        }
        private setStrokeWidth_serialize(width: number): void {
            ArkUIGeneratedNativeModule._drawing_Pen_setStrokeWidth(this.peer!.ptr, width)
        }
        private getWidth_serialize(): number {
            const retval  = ArkUIGeneratedNativeModule._drawing_Pen_getWidth(this.peer!.ptr)
            return retval
        }
        private setAntiAlias_serialize(aa: boolean): void {
            ArkUIGeneratedNativeModule._drawing_Pen_setAntiAlias(this.peer!.ptr, aa ? 1 : 0)
        }
        private isAntiAlias_serialize(): boolean {
            const retval  = ArkUIGeneratedNativeModule._drawing_Pen_isAntiAlias(this.peer!.ptr)
            return retval
        }
        private setAlpha_serialize(alpha: number): void {
            ArkUIGeneratedNativeModule._drawing_Pen_setAlpha(this.peer!.ptr, alpha)
        }
        private getAlpha_serialize(): number {
            const retval  = ArkUIGeneratedNativeModule._drawing_Pen_getAlpha(this.peer!.ptr)
            return retval
        }
        private setColorFilter_serialize(filter: ColorFilter): void {
            ArkUIGeneratedNativeModule._drawing_Pen_setColorFilter(this.peer!.ptr, toPeerPtr(filter))
        }
        private getColorFilter_serialize(): ColorFilter {
            const retval  = ArkUIGeneratedNativeModule._drawing_Pen_getColorFilter(this.peer!.ptr)
            const obj : ColorFilter = drawing.ColorFilterInternal.fromPtr(retval)
            return obj
        }
        private setImageFilter_serialize(filter: ImageFilter | undefined): void {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            let filter_type : int32 = RuntimeType.UNDEFINED
            filter_type = runtimeType(filter)
            thisSerializer.writeInt8((filter_type).toChar())
            if ((filter_type) != (RuntimeType.UNDEFINED)) {
                const filter_value  = filter!
                drawing_ImageFilter_serializer.write(thisSerializer, filter_value)
            }
            ArkUIGeneratedNativeModule._drawing_Pen_setImageFilter(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
            thisSerializer.release()
        }
        private setMaskFilter_serialize(filter: MaskFilter): void {
            ArkUIGeneratedNativeModule._drawing_Pen_setMaskFilter(this.peer!.ptr, toPeerPtr(filter))
        }
        private setPathEffect_serialize(effect: PathEffect): void {
            ArkUIGeneratedNativeModule._drawing_Pen_setPathEffect(this.peer!.ptr, toPeerPtr(effect))
        }
        private setShadowLayer_serialize(shadowLayer: ShadowLayer): void {
            ArkUIGeneratedNativeModule._drawing_Pen_setShadowLayer(this.peer!.ptr, toPeerPtr(shadowLayer))
        }
        private setBlendMode_serialize(mode: BlendMode): void {
            ArkUIGeneratedNativeModule._drawing_Pen_setBlendMode(this.peer!.ptr, TypeChecker.drawing_BlendMode_ToNumeric(mode))
        }
        private setDither_serialize(dither: boolean): void {
            ArkUIGeneratedNativeModule._drawing_Pen_setDither(this.peer!.ptr, dither ? 1 : 0)
        }
        private setJoinStyle_serialize(style: JoinStyle): void {
            ArkUIGeneratedNativeModule._drawing_Pen_setJoinStyle(this.peer!.ptr, TypeChecker.drawing_JoinStyle_ToNumeric(style))
        }
        private getJoinStyle_serialize(): JoinStyle {
            const retval  = ArkUIGeneratedNativeModule._drawing_Pen_getJoinStyle(this.peer!.ptr)
            return TypeChecker.drawing_JoinStyle_FromNumeric(retval)
        }
        private setCapStyle_serialize(style: CapStyle): void {
            ArkUIGeneratedNativeModule._drawing_Pen_setCapStyle(this.peer!.ptr, TypeChecker.drawing_CapStyle_ToNumeric(style))
        }
        private getCapStyle_serialize(): CapStyle {
            const retval  = ArkUIGeneratedNativeModule._drawing_Pen_getCapStyle(this.peer!.ptr)
            return TypeChecker.drawing_CapStyle_FromNumeric(retval)
        }
        private reset_serialize(): void {
            ArkUIGeneratedNativeModule._drawing_Pen_reset(this.peer!.ptr)
        }
        private getFillPath_serialize(src: Path, dst: Path): boolean {
            const retval  = ArkUIGeneratedNativeModule._drawing_Pen_getFillPath(this.peer!.ptr, toPeerPtr(src), toPeerPtr(dst))
            return retval
        }
    }
    export class RegionInternal {
        public static fromPtr(ptr: KPointer): drawing.Region {
            return new drawing.Region(ptr)
        }
    }
    export class Region implements MaterializedBase {
        peer?: Finalizable | undefined = undefined
        public getPeer(): Finalizable | undefined {
            return this.peer
        }
        constructor(peerPtr: KPointer) {
            this.peer = new Finalizable(peerPtr, Region.getFinalizer())
        }
        constructor() {
            this(Region.construct())
        }
        static construct(): KPointer {
            const retval  = ArkUIGeneratedNativeModule._drawing_Region_construct()
            return retval
        }
        static getFinalizer(): KPointer {
            return ArkUIGeneratedNativeModule._drawing_Region_getFinalizer()
        }
        public isPointContained(x: number, y: number): boolean {
            const x_casted = x as (number)
            const y_casted = y as (number)
            return this.isPointContained_serialize(x_casted, y_casted)
        }
        public isRegionContained(other: Region): boolean {
            const other_casted = other as (Region)
            return this.isRegionContained_serialize(other_casted)
        }
        public op(region: Region, regionOp: RegionOp): boolean {
            const region_casted = region as (Region)
            const regionOp_casted = regionOp as (RegionOp)
            return this.op_serialize(region_casted, regionOp_casted)
        }
        public quickReject(left: number, top: number, right: number, bottom: number): boolean {
            const left_casted = left as (number)
            const top_casted = top as (number)
            const right_casted = right as (number)
            const bottom_casted = bottom as (number)
            return this.quickReject_serialize(left_casted, top_casted, right_casted, bottom_casted)
        }
        public setPath(path: Path, clip: Region): boolean {
            const path_casted = path as (Path)
            const clip_casted = clip as (Region)
            return this.setPath_serialize(path_casted, clip_casted)
        }
        public setRect(left: number, top: number, right: number, bottom: number): boolean {
            const left_casted = left as (number)
            const top_casted = top as (number)
            const right_casted = right as (number)
            const bottom_casted = bottom as (number)
            return this.setRect_serialize(left_casted, top_casted, right_casted, bottom_casted)
        }
        private isPointContained_serialize(x: number, y: number): boolean {
            const retval  = ArkUIGeneratedNativeModule._drawing_Region_isPointContained(this.peer!.ptr, x, y)
            return retval
        }
        private isRegionContained_serialize(other: Region): boolean {
            const retval  = ArkUIGeneratedNativeModule._drawing_Region_isRegionContained(this.peer!.ptr, toPeerPtr(other))
            return retval
        }
        private op_serialize(region: Region, regionOp: RegionOp): boolean {
            const retval  = ArkUIGeneratedNativeModule._drawing_Region_op(this.peer!.ptr, toPeerPtr(region), TypeChecker.drawing_RegionOp_ToNumeric(regionOp))
            return retval
        }
        private quickReject_serialize(left: number, top: number, right: number, bottom: number): boolean {
            const retval  = ArkUIGeneratedNativeModule._drawing_Region_quickReject(this.peer!.ptr, left, top, right, bottom)
            return retval
        }
        private setPath_serialize(path: Path, clip: Region): boolean {
            const retval  = ArkUIGeneratedNativeModule._drawing_Region_setPath(this.peer!.ptr, toPeerPtr(path), toPeerPtr(clip))
            return retval
        }
        private setRect_serialize(left: number, top: number, right: number, bottom: number): boolean {
            const retval  = ArkUIGeneratedNativeModule._drawing_Region_setRect(this.peer!.ptr, left, top, right, bottom)
            return retval
        }
    }
    export class RoundRectInternal {
        public static fromPtr(ptr: KPointer): drawing.RoundRect {
            return new drawing.RoundRect(false, false, false, ptr)
        }
    }
    export class RoundRect implements MaterializedBase {
        peer?: Finalizable | undefined = undefined
        public getPeer(): Finalizable | undefined {
            return this.peer
        }
        constructor(_0: boolean, _1: boolean, _2: boolean, peerPtr: KPointer) {
            this.peer = new Finalizable(peerPtr, RoundRect.getFinalizer())
        }
        constructor(rect: common2D.Rect, xRadii: number, yRadii: number) {
            this(false, false, false, RoundRect.construct(rect, xRadii, yRadii))
        }
        static construct(rect: common2D.Rect, xRadii: number, yRadii: number): KPointer {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            common2D_Rect_serializer.write(thisSerializer, rect)
            const retval  = ArkUIGeneratedNativeModule._drawing_RoundRect_construct(thisSerializer.asBuffer(), thisSerializer.length(), xRadii, yRadii)
            thisSerializer.release()
            return retval
        }
        static getFinalizer(): KPointer {
            return ArkUIGeneratedNativeModule._drawing_RoundRect_getFinalizer()
        }
        public setCorner(pos: CornerPos, x: number, y: number): void {
            const pos_casted = pos as (CornerPos)
            const x_casted = x as (number)
            const y_casted = y as (number)
            this.setCorner_serialize(pos_casted, x_casted, y_casted)
            return
        }
        public getCorner(pos: CornerPos): common2D.Point {
            const pos_casted = pos as (CornerPos)
            return this.getCorner_serialize(pos_casted)
        }
        public offset(dx: number, dy: number): void {
            const dx_casted = dx as (number)
            const dy_casted = dy as (number)
            this.offset_serialize(dx_casted, dy_casted)
            return
        }
        private setCorner_serialize(pos: CornerPos, x: number, y: number): void {
            ArkUIGeneratedNativeModule._drawing_RoundRect_setCorner(this.peer!.ptr, TypeChecker.drawing_CornerPos_ToNumeric(pos), x, y)
        }
        private getCorner_serialize(pos: CornerPos): common2D.Point {
            const retval  = ArkUIGeneratedNativeModule._drawing_RoundRect_getCorner(this.peer!.ptr, TypeChecker.drawing_CornerPos_ToNumeric(pos))
            let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
            const returnResult : common2D.Point = common2D_Point_serializer.read(retvalDeserializer)
            return returnResult
        }
        private offset_serialize(dx: number, dy: number): void {
            ArkUIGeneratedNativeModule._drawing_RoundRect_offset(this.peer!.ptr, dx, dy)
        }
    }
    export class SamplingOptionsInternal {
        public static fromPtr(ptr: KPointer): drawing.SamplingOptions {
            return new drawing.SamplingOptions(false, ptr)
        }
    }
    export class SamplingOptions implements MaterializedBase {
        peer?: Finalizable | undefined = undefined
        public getPeer(): Finalizable | undefined {
            return this.peer
        }
        constructor(_0: boolean, peerPtr: KPointer) {
            this.peer = new Finalizable(peerPtr, SamplingOptions.getFinalizer())
        }
        constructor() {
            this(false, SamplingOptions.construct0())
        }
        constructor(filterMode: FilterMode) {
            this(false, SamplingOptions.construct1(filterMode))
        }
        static construct0(): KPointer {
            const retval  = ArkUIGeneratedNativeModule._drawing_SamplingOptions_construct0()
            return retval
        }
        static construct1(filterMode: FilterMode): KPointer {
            const retval  = ArkUIGeneratedNativeModule._drawing_SamplingOptions_construct1(TypeChecker.drawing_FilterMode_ToNumeric(filterMode))
            return retval
        }
        static getFinalizer(): KPointer {
            return ArkUIGeneratedNativeModule._drawing_SamplingOptions_getFinalizer()
        }
    }
    export class ShaderEffectInternal {
        public static fromPtr(ptr: KPointer): drawing.ShaderEffect {
            return new drawing.ShaderEffect(ptr)
        }
    }
    export class ShaderEffect implements MaterializedBase {
        peer?: Finalizable | undefined = undefined
        public getPeer(): Finalizable | undefined {
            return this.peer
        }
        constructor(peerPtr: KPointer) {
            this.peer = new Finalizable(peerPtr, ShaderEffect.getFinalizer())
        }
        constructor() {
            this(ShaderEffect.construct())
        }
        static construct(): KPointer {
            const retval  = ArkUIGeneratedNativeModule._drawing_ShaderEffect_construct()
            return retval
        }
        static getFinalizer(): KPointer {
            return ArkUIGeneratedNativeModule._drawing_ShaderEffect_getFinalizer()
        }
        private static createColorShader_serialize(color: number): ShaderEffect {
            const retval  = ArkUIGeneratedNativeModule._drawing_ShaderEffect_createColorShader(color)
            const obj : ShaderEffect = drawing.ShaderEffectInternal.fromPtr(retval)
            return obj
        }
        private static createLinearGradient_serialize(startPt: common2D.Point, endPt: common2D.Point, colors: Array<number>, mode: TileMode, pos: Array<number> | undefined, matrix: Matrix | undefined): ShaderEffect {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            common2D_Point_serializer.write(thisSerializer, startPt)
            common2D_Point_serializer.write(thisSerializer, endPt)
            thisSerializer.writeInt32((colors.length).toInt())
            for (let colors_counter_i = 0; colors_counter_i < colors.length; colors_counter_i++) {
                const colors_element : number = colors[colors_counter_i]
                thisSerializer.writeNumber(colors_element)
            }
            let pos_type : int32 = RuntimeType.UNDEFINED
            pos_type = runtimeType(pos)
            thisSerializer.writeInt8((pos_type).toChar())
            if ((pos_type) != (RuntimeType.UNDEFINED)) {
                const pos_value  = pos!
                thisSerializer.writeInt32((pos_value.length).toInt())
                for (let pos_value_counter_i = 0; pos_value_counter_i < pos_value.length; pos_value_counter_i++) {
                    const pos_value_element : number = pos_value[pos_value_counter_i]
                    thisSerializer.writeNumber(pos_value_element)
                }
            }
            let matrix_type : int32 = RuntimeType.UNDEFINED
            matrix_type = runtimeType(matrix)
            thisSerializer.writeInt8((matrix_type).toChar())
            if ((matrix_type) != (RuntimeType.UNDEFINED)) {
                const matrix_value  = matrix!
                drawing_Matrix_serializer.write(thisSerializer, matrix_value)
            }
            const retval  = ArkUIGeneratedNativeModule._drawing_ShaderEffect_createLinearGradient(thisSerializer.asBuffer(), thisSerializer.length(), TypeChecker.drawing_TileMode_ToNumeric(mode))
            thisSerializer.release()
            const obj : ShaderEffect = drawing.ShaderEffectInternal.fromPtr(retval)
            return obj
        }
        private static createRadialGradient_serialize(centerPt: common2D.Point, radius: number, colors: Array<number>, mode: TileMode, pos: Array<number> | undefined, matrix: Matrix | undefined): ShaderEffect {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            common2D_Point_serializer.write(thisSerializer, centerPt)
            thisSerializer.writeInt32((colors.length).toInt())
            for (let colors_counter_i = 0; colors_counter_i < colors.length; colors_counter_i++) {
                const colors_element : number = colors[colors_counter_i]
                thisSerializer.writeNumber(colors_element)
            }
            let pos_type : int32 = RuntimeType.UNDEFINED
            pos_type = runtimeType(pos)
            thisSerializer.writeInt8((pos_type).toChar())
            if ((pos_type) != (RuntimeType.UNDEFINED)) {
                const pos_value  = pos!
                thisSerializer.writeInt32((pos_value.length).toInt())
                for (let pos_value_counter_i = 0; pos_value_counter_i < pos_value.length; pos_value_counter_i++) {
                    const pos_value_element : number = pos_value[pos_value_counter_i]
                    thisSerializer.writeNumber(pos_value_element)
                }
            }
            let matrix_type : int32 = RuntimeType.UNDEFINED
            matrix_type = runtimeType(matrix)
            thisSerializer.writeInt8((matrix_type).toChar())
            if ((matrix_type) != (RuntimeType.UNDEFINED)) {
                const matrix_value  = matrix!
                drawing_Matrix_serializer.write(thisSerializer, matrix_value)
            }
            const retval  = ArkUIGeneratedNativeModule._drawing_ShaderEffect_createRadialGradient(thisSerializer.asBuffer(), thisSerializer.length(), radius, TypeChecker.drawing_TileMode_ToNumeric(mode))
            thisSerializer.release()
            const obj : ShaderEffect = drawing.ShaderEffectInternal.fromPtr(retval)
            return obj
        }
        private static createSweepGradient_serialize(centerPt: common2D.Point, colors: Array<number>, mode: TileMode, startAngle: number, endAngle: number, pos: Array<number> | undefined, matrix: Matrix | undefined): ShaderEffect {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            common2D_Point_serializer.write(thisSerializer, centerPt)
            thisSerializer.writeInt32((colors.length).toInt())
            for (let colors_counter_i = 0; colors_counter_i < colors.length; colors_counter_i++) {
                const colors_element : number = colors[colors_counter_i]
                thisSerializer.writeNumber(colors_element)
            }
            let pos_type : int32 = RuntimeType.UNDEFINED
            pos_type = runtimeType(pos)
            thisSerializer.writeInt8((pos_type).toChar())
            if ((pos_type) != (RuntimeType.UNDEFINED)) {
                const pos_value  = pos!
                thisSerializer.writeInt32((pos_value.length).toInt())
                for (let pos_value_counter_i = 0; pos_value_counter_i < pos_value.length; pos_value_counter_i++) {
                    const pos_value_element : number = pos_value[pos_value_counter_i]
                    thisSerializer.writeNumber(pos_value_element)
                }
            }
            let matrix_type : int32 = RuntimeType.UNDEFINED
            matrix_type = runtimeType(matrix)
            thisSerializer.writeInt8((matrix_type).toChar())
            if ((matrix_type) != (RuntimeType.UNDEFINED)) {
                const matrix_value  = matrix!
                drawing_Matrix_serializer.write(thisSerializer, matrix_value)
            }
            const retval  = ArkUIGeneratedNativeModule._drawing_ShaderEffect_createSweepGradient(thisSerializer.asBuffer(), thisSerializer.length(), TypeChecker.drawing_TileMode_ToNumeric(mode), startAngle, endAngle)
            thisSerializer.release()
            const obj : ShaderEffect = drawing.ShaderEffectInternal.fromPtr(retval)
            return obj
        }
        private static createConicalGradient_serialize(startPt: common2D.Point, startRadius: number, endPt: common2D.Point, endRadius: number, colors: Array<number>, mode: TileMode, pos: Array<number> | undefined, matrix: Matrix | undefined): ShaderEffect {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            common2D_Point_serializer.write(thisSerializer, startPt)
            common2D_Point_serializer.write(thisSerializer, endPt)
            thisSerializer.writeInt32((colors.length).toInt())
            for (let colors_counter_i = 0; colors_counter_i < colors.length; colors_counter_i++) {
                const colors_element : number = colors[colors_counter_i]
                thisSerializer.writeNumber(colors_element)
            }
            let pos_type : int32 = RuntimeType.UNDEFINED
            pos_type = runtimeType(pos)
            thisSerializer.writeInt8((pos_type).toChar())
            if ((pos_type) != (RuntimeType.UNDEFINED)) {
                const pos_value  = pos!
                thisSerializer.writeInt32((pos_value.length).toInt())
                for (let pos_value_counter_i = 0; pos_value_counter_i < pos_value.length; pos_value_counter_i++) {
                    const pos_value_element : number = pos_value[pos_value_counter_i]
                    thisSerializer.writeNumber(pos_value_element)
                }
            }
            let matrix_type : int32 = RuntimeType.UNDEFINED
            matrix_type = runtimeType(matrix)
            thisSerializer.writeInt8((matrix_type).toChar())
            if ((matrix_type) != (RuntimeType.UNDEFINED)) {
                const matrix_value  = matrix!
                drawing_Matrix_serializer.write(thisSerializer, matrix_value)
            }
            const retval  = ArkUIGeneratedNativeModule._drawing_ShaderEffect_createConicalGradient(thisSerializer.asBuffer(), thisSerializer.length(), startRadius, endRadius, TypeChecker.drawing_TileMode_ToNumeric(mode))
            thisSerializer.release()
            const obj : ShaderEffect = drawing.ShaderEffectInternal.fromPtr(retval)
            return obj
        }
        public static createColorShader(color: number): ShaderEffect {
            const color_casted = color as (number)
            return ShaderEffect.createColorShader_serialize(color_casted)
        }
        public static createLinearGradient(startPt: common2D.Point, endPt: common2D.Point, colors: Array<number>, mode: TileMode, pos: Array<number> | undefined, matrix: Matrix | undefined): ShaderEffect {
            const startPt_casted = startPt as (common2D.Point)
            const endPt_casted = endPt as (common2D.Point)
            const colors_casted = colors as (Array<number>)
            const mode_casted = mode as (TileMode)
            const pos_casted = pos as (Array<number> | undefined)
            const matrix_casted = matrix as (Matrix | undefined)
            return ShaderEffect.createLinearGradient_serialize(startPt_casted, endPt_casted, colors_casted, mode_casted, pos_casted, matrix_casted)
        }
        public static createRadialGradient(centerPt: common2D.Point, radius: number, colors: Array<number>, mode: TileMode, pos: Array<number> | undefined, matrix: Matrix | undefined): ShaderEffect {
            const centerPt_casted = centerPt as (common2D.Point)
            const radius_casted = radius as (number)
            const colors_casted = colors as (Array<number>)
            const mode_casted = mode as (TileMode)
            const pos_casted = pos as (Array<number> | undefined)
            const matrix_casted = matrix as (Matrix | undefined)
            return ShaderEffect.createRadialGradient_serialize(centerPt_casted, radius_casted, colors_casted, mode_casted, pos_casted, matrix_casted)
        }
        public static createSweepGradient(centerPt: common2D.Point, colors: Array<number>, mode: TileMode, startAngle: number, endAngle: number, pos: Array<number> | undefined, matrix: Matrix | undefined): ShaderEffect {
            const centerPt_casted = centerPt as (common2D.Point)
            const colors_casted = colors as (Array<number>)
            const mode_casted = mode as (TileMode)
            const startAngle_casted = startAngle as (number)
            const endAngle_casted = endAngle as (number)
            const pos_casted = pos as (Array<number> | undefined)
            const matrix_casted = matrix as (Matrix | undefined)
            return ShaderEffect.createSweepGradient_serialize(centerPt_casted, colors_casted, mode_casted, startAngle_casted, endAngle_casted, pos_casted, matrix_casted)
        }
        public static createConicalGradient(startPt: common2D.Point, startRadius: number, endPt: common2D.Point, endRadius: number, colors: Array<number>, mode: TileMode, pos: Array<number> | undefined, matrix: Matrix | undefined): ShaderEffect {
            const startPt_casted = startPt as (common2D.Point)
            const startRadius_casted = startRadius as (number)
            const endPt_casted = endPt as (common2D.Point)
            const endRadius_casted = endRadius as (number)
            const colors_casted = colors as (Array<number>)
            const mode_casted = mode as (TileMode)
            const pos_casted = pos as (Array<number> | undefined)
            const matrix_casted = matrix as (Matrix | undefined)
            return ShaderEffect.createConicalGradient_serialize(startPt_casted, startRadius_casted, endPt_casted, endRadius_casted, colors_casted, mode_casted, pos_casted, matrix_casted)
        }
    }
    export class ShadowLayerInternal {
        public static fromPtr(ptr: KPointer): drawing.ShadowLayer {
            return new drawing.ShadowLayer(ptr)
        }
    }
    export class ShadowLayer implements MaterializedBase {
        peer?: Finalizable | undefined = undefined
        public getPeer(): Finalizable | undefined {
            return this.peer
        }
        constructor(peerPtr: KPointer) {
            this.peer = new Finalizable(peerPtr, ShadowLayer.getFinalizer())
        }
        constructor() {
            this(ShadowLayer.construct())
        }
        static construct(): KPointer {
            const retval  = ArkUIGeneratedNativeModule._drawing_ShadowLayer_construct()
            return retval
        }
        static getFinalizer(): KPointer {
            return ArkUIGeneratedNativeModule._drawing_ShadowLayer_getFinalizer()
        }
        private static create0_serialize(blurRadius: number, x: number, y: number, color: common2D.Color): ShadowLayer {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            common2D_Color_serializer.write(thisSerializer, color)
            const retval  = ArkUIGeneratedNativeModule._drawing_ShadowLayer_create0(blurRadius, x, y, thisSerializer.asBuffer(), thisSerializer.length())
            thisSerializer.release()
            const obj : ShadowLayer = drawing.ShadowLayerInternal.fromPtr(retval)
            return obj
        }
        private static create1_serialize(blurRadius: number, x: number, y: number, color: number): ShadowLayer {
            const retval  = ArkUIGeneratedNativeModule._drawing_ShadowLayer_create1(blurRadius, x, y, color)
            const obj : ShadowLayer = drawing.ShadowLayerInternal.fromPtr(retval)
            return obj
        }
        public static create(blurRadius: number, x: number, y: number, color: common2D.Color): ShadowLayer {
            const blurRadius_casted = blurRadius as (number)
            const x_casted = x as (number)
            const y_casted = y as (number)
            const color_casted = color as (common2D.Color)
            return ShadowLayer.create0_serialize(blurRadius_casted, x_casted, y_casted, color_casted)
        }
        public static create(blurRadius: number, x: number, y: number, color: number): ShadowLayer {
            const blurRadius_casted = blurRadius as (number)
            const x_casted = x as (number)
            const y_casted = y as (number)
            const color_casted = color as (number)
            return ShadowLayer.create1_serialize(blurRadius_casted, x_casted, y_casted, color_casted)
        }
    }
    export class TextBlobInternal {
        public static fromPtr(ptr: KPointer): drawing.TextBlob {
            return new drawing.TextBlob(ptr)
        }
    }
    export class TextBlob implements MaterializedBase {
        peer?: Finalizable | undefined = undefined
        public getPeer(): Finalizable | undefined {
            return this.peer
        }
        constructor(peerPtr: KPointer) {
            this.peer = new Finalizable(peerPtr, TextBlob.getFinalizer())
        }
        constructor() {
            this(TextBlob.construct())
        }
        static construct(): KPointer {
            const retval  = ArkUIGeneratedNativeModule._drawing_TextBlob_construct()
            return retval
        }
        static getFinalizer(): KPointer {
            return ArkUIGeneratedNativeModule._drawing_TextBlob_getFinalizer()
        }
        private static makeFromString_serialize(text: string, font: Font, encoding: TextEncoding): TextBlob {
            const retval  = ArkUIGeneratedNativeModule._drawing_TextBlob_makeFromString(text, toPeerPtr(font), TypeChecker.drawing_TextEncoding_ToNumeric(encoding))
            const obj : TextBlob = drawing.TextBlobInternal.fromPtr(retval)
            return obj
        }
        private static makeFromPosText_serialize(text: string, len: number, points: Array<common2D.Point>, font: Font): TextBlob {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            thisSerializer.writeInt32((points.length).toInt())
            for (let points_counter_i = 0; points_counter_i < points.length; points_counter_i++) {
                const points_element : common2D.Point = points[points_counter_i]
                common2D_Point_serializer.write(thisSerializer, points_element)
            }
            const retval  = ArkUIGeneratedNativeModule._drawing_TextBlob_makeFromPosText(text, len, thisSerializer.asBuffer(), thisSerializer.length(), toPeerPtr(font))
            thisSerializer.release()
            const obj : TextBlob = drawing.TextBlobInternal.fromPtr(retval)
            return obj
        }
        private static makeFromRunBuffer_serialize(pos: Array<TextBlobRunBuffer>, font: Font, bounds: common2D.Rect): TextBlob {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            thisSerializer.writeInt32((pos.length).toInt())
            for (let pos_counter_i = 0; pos_counter_i < pos.length; pos_counter_i++) {
                const pos_element : TextBlobRunBuffer = pos[pos_counter_i]
                drawing_TextBlobRunBuffer_serializer.write(thisSerializer, pos_element)
            }
            common2D_Rect_serializer.write(thisSerializer, bounds)
            const retval  = ArkUIGeneratedNativeModule._drawing_TextBlob_makeFromRunBuffer(thisSerializer.asBuffer(), thisSerializer.length(), toPeerPtr(font))
            thisSerializer.release()
            const obj : TextBlob = drawing.TextBlobInternal.fromPtr(retval)
            return obj
        }
        public static makeFromString(text: string, font: Font, encoding: TextEncoding): TextBlob {
            const text_casted = text as (string)
            const font_casted = font as (Font)
            const encoding_casted = encoding as (TextEncoding)
            return TextBlob.makeFromString_serialize(text_casted, font_casted, encoding_casted)
        }
        public static makeFromPosText(text: string, len: number, points: Array<common2D.Point>, font: Font): TextBlob {
            const text_casted = text as (string)
            const len_casted = len as (number)
            const points_casted = points as (Array<common2D.Point>)
            const font_casted = font as (Font)
            return TextBlob.makeFromPosText_serialize(text_casted, len_casted, points_casted, font_casted)
        }
        public static makeFromRunBuffer(pos: Array<TextBlobRunBuffer>, font: Font, bounds: common2D.Rect): TextBlob {
            const pos_casted = pos as (Array<TextBlobRunBuffer>)
            const font_casted = font as (Font)
            const bounds_casted = bounds as (common2D.Rect)
            return TextBlob.makeFromRunBuffer_serialize(pos_casted, font_casted, bounds_casted)
        }
        public bounds(): common2D.Rect {
            return this.bounds_serialize()
        }
        public uniqueID(): number {
            return this.uniqueID_serialize()
        }
        private bounds_serialize(): common2D.Rect {
            const retval  = ArkUIGeneratedNativeModule._drawing_TextBlob_bounds(this.peer!.ptr)
            let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
            const returnResult : common2D.Rect = common2D_Rect_serializer.read(retvalDeserializer)
            return returnResult
        }
        private uniqueID_serialize(): number {
            const retval  = ArkUIGeneratedNativeModule._drawing_TextBlob_uniqueID(this.peer!.ptr)
            return retval
        }
    }
    export class TypefaceInternal {
        public static fromPtr(ptr: KPointer): drawing.Typeface {
            return new drawing.Typeface(ptr)
        }
    }
    export class Typeface implements MaterializedBase {
        peer?: Finalizable | undefined = undefined
        public getPeer(): Finalizable | undefined {
            return this.peer
        }
        constructor(peerPtr: KPointer) {
            this.peer = new Finalizable(peerPtr, Typeface.getFinalizer())
        }
        constructor() {
            this(Typeface.construct())
        }
        static construct(): KPointer {
            const retval  = ArkUIGeneratedNativeModule._drawing_Typeface_construct()
            return retval
        }
        static getFinalizer(): KPointer {
            return ArkUIGeneratedNativeModule._drawing_Typeface_getFinalizer()
        }
        private static makeFromFile_serialize(filePath: string): Typeface {
            const retval  = ArkUIGeneratedNativeModule._drawing_Typeface_makeFromFile(filePath)
            const obj : Typeface = drawing.TypefaceInternal.fromPtr(retval)
            return obj
        }
        public getFamilyName(): string {
            return this.getFamilyName_serialize()
        }
        public static makeFromFile(filePath: string): Typeface {
            const filePath_casted = filePath as (string)
            return Typeface.makeFromFile_serialize(filePath_casted)
        }
        private getFamilyName_serialize(): string {
            const retval  = ArkUIGeneratedNativeModule._drawing_Typeface_getFamilyName(this.peer!.ptr)
            return retval
        }
    }
    export enum BlendMode {
        CLEAR = 0,
        SRC = 1,
        DST = 2,
        SRC_OVER = 3,
        DST_OVER = 4,
        SRC_IN = 5,
        DST_IN = 6,
        SRC_OUT = 7,
        DST_OUT = 8,
        SRC_ATOP = 9,
        DST_ATOP = 10,
        XOR = 11,
        PLUS = 12,
        MODULATE = 13,
        SCREEN = 14,
        OVERLAY = 15,
        DARKEN = 16,
        LIGHTEN = 17,
        COLOR_DODGE = 18,
        COLOR_BURN = 19,
        HARD_LIGHT = 20,
        SOFT_LIGHT = 21,
        DIFFERENCE = 22,
        EXCLUSION = 23,
        MULTIPLY = 24,
        HUE = 25,
        SATURATION = 26,
        COLOR = 27,
        LUMINOSITY = 28
    }
    export enum PathDirection {
        CLOCKWISE = 0,
        COUNTER_CLOCKWISE = 1
    }
    export enum PathFillType {
        WINDING = 0,
        EVEN_ODD = 1,
        INVERSE_WINDING = 2,
        INVERSE_EVEN_ODD = 3
    }
    export enum PathMeasureMatrixFlags {
        GET_POSITION_MATRIX = 0,
        GET_TANGENT_MATRIX = 1,
        GET_POSITION_AND_TANGENT_MATRIX = 2
    }
    export enum PathOp {
        DIFFERENCE = 0,
        INTERSECT = 1,
        UNION = 2,
        XOR = 3,
        REVERSE_DIFFERENCE = 4
    }
    export enum PointMode {
        POINTS = 0,
        LINES = 1,
        POLYGON = 2
    }
    export enum FilterMode {
        FILTER_MODE_NEAREST = 0,
        FILTER_MODE_LINEAR = 1
    }
    export enum ShadowFlag {
        NONE = 0,
        TRANSPARENT_OCCLUDER = 1,
        GEOMETRIC_ONLY = 2,
        ALL = 3
    }
    export enum ClipOp {
        DIFFERENCE = 0,
        INTERSECT = 1
    }
    export interface TextBlobRunBuffer {
        glyph: number;
        positionX: number;
        positionY: number;
    }
    export enum TextEncoding {
        TEXT_ENCODING_UTF8 = 0,
        TEXT_ENCODING_UTF16 = 1,
        TEXT_ENCODING_UTF32 = 2,
        TEXT_ENCODING_GLYPH_ID = 3
    }
    export enum FontEdging {
        ALIAS = 0,
        ANTI_ALIAS = 1,
        SUBPIXEL_ANTI_ALIAS = 2
    }
    export enum FontHinting {
        NONE = 0,
        SLIGHT = 1,
        NORMAL = 2,
        FULL = 3
    }
    export enum FontMetricsFlags {
        UNDERLINE_THICKNESS_VALID = 0,
        UNDERLINE_POSITION_VALID = 1,
        STRIKETHROUGH_THICKNESS_VALID = 2,
        STRIKETHROUGH_POSITION_VALID = 3,
        BOUNDS_INVALID = 4
    }
    export interface FontMetrics {
        flags?: drawing.FontMetricsFlags;
        top: number;
        ascent: number;
        descent: number;
        bottom: number;
        leading: number;
        avgCharWidth?: number;
        maxCharWidth?: number;
        xMin?: number;
        xMax?: number;
        xHeight?: number;
        capHeight?: number;
        underlineThickness?: number;
        underlinePosition?: number;
        strikethroughThickness?: number;
        strikethroughPosition?: number;
    }
    export enum RectType {
        DEFAULT = 0,
        TRANSPARENT = 1,
        FIXEDCOLOR = 2
    }
    export enum TileMode {
        CLAMP = 0,
        REPEAT = 1,
        MIRROR = 2,
        DECAL = 3
    }
    export enum JoinStyle {
        MITER_JOIN = 0,
        ROUND_JOIN = 1,
        BEVEL_JOIN = 2
    }
    export enum CapStyle {
        FLAT_CAP = 0,
        SQUARE_CAP = 1,
        ROUND_CAP = 2
    }
    export enum BlurType {
        NORMAL = 0,
        SOLID = 1,
        OUTER = 2,
        INNER = 3
    }
    export enum ScaleToFit {
        FILL_SCALE_TO_FIT = 0,
        START_SCALE_TO_FIT = 1,
        CENTER_SCALE_TO_FIT = 2,
        END_SCALE_TO_FIT = 3
    }
    export enum RegionOp {
        DIFFERENCE = 0,
        INTERSECT = 1,
        UNION = 2,
        XOR = 3,
        REVERSE_DIFFERENCE = 4,
        REPLACE = 5
    }
    export enum CornerPos {
        TOP_LEFT_POS = 0,
        TOP_RIGHT_POS = 1,
        BOTTOM_RIGHT_POS = 2,
        BOTTOM_LEFT_POS = 3
    }
    export enum SrcRectConstraint {
        STRICT = 0,
        FAST = 1
    }
}
