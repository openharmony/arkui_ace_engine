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

import { CanvasPath, CanvasPathInternal } from "./ArkCanvasPathMaterialized"
import { CanvasGradient, CanvasGradientInternal } from "./ArkCanvasGradientMaterialized"
import { CanvasPattern, CanvasPatternInternal } from "./ArkCanvasPatternMaterialized"
import { ImageSmoothingQuality, CanvasLineCap, CanvasLineJoin, CanvasDirection, CanvasTextAlign, CanvasTextBaseline, CanvasFillRule, TextMetrics } from "./ArkCanvasInterfaces"
import { ImageBitmap, ImageBitmapInternal } from "./ArkImageBitmapMaterialized"
import { PixelMap, PixelMapInternal } from "./ArkPixelMapMaterialized"
import { Path2D, Path2DInternal } from "./ArkPath2DMaterialized"
import { ImageData, ImageDataInternal } from "./ArkImageDataMaterialized"
import { Matrix2D, Matrix2DInternal } from "./ArkMatrix2DMaterialized"
import { LengthMetricsUnit } from "./ArkUnitsInterfaces"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, isInstanceOf } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { isResource, isPadding } from "./../utils"
import { Deserializer, createDeserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ArkUIGeneratedNativeModule } from "./ArkUIGeneratedNativeModule"
export class CanvasRendererInternal {
    public static fromPtr(ptr: KPointer): CanvasRenderer {
        const obj: CanvasRenderer = new CanvasRenderer()
        obj.peer = new Finalizable(ptr, CanvasRenderer.getFinalizer())
        return obj
    }
}
export class CanvasRenderer extends CanvasPath implements MaterializedBase {
    get globalAlpha(): number {
        return this.getGlobalAlpha()
    }
    set globalAlpha(globalAlpha: number) {
        this.setGlobalAlpha(globalAlpha)
    }
    get globalCompositeOperation(): string {
        return this.getGlobalCompositeOperation()
    }
    set globalCompositeOperation(globalCompositeOperation: string) {
        this.setGlobalCompositeOperation(globalCompositeOperation)
    }
    get fillStyle(): string | number | CanvasGradient | CanvasPattern {
        throw new Error("Not implemented")
    }
    set fillStyle(fillStyle: string | number | CanvasGradient | CanvasPattern) {
        this.setFillStyle(fillStyle)
    }
    get strokeStyle(): string | number | CanvasGradient | CanvasPattern {
        throw new Error("Not implemented")
    }
    set strokeStyle(strokeStyle: string | number | CanvasGradient | CanvasPattern) {
        this.setStrokeStyle(strokeStyle)
    }
    get filter(): string {
        return this.getFilter()
    }
    set filter(filter: string) {
        this.setFilter(filter)
    }
    get imageSmoothingEnabled(): boolean {
        return this.getImageSmoothingEnabled()
    }
    set imageSmoothingEnabled(imageSmoothingEnabled: boolean) {
        this.setImageSmoothingEnabled(imageSmoothingEnabled)
    }
    get imageSmoothingQuality(): ImageSmoothingQuality {
        return this.getImageSmoothingQuality()
    }
    set imageSmoothingQuality(imageSmoothingQuality: ImageSmoothingQuality) {
        this.setImageSmoothingQuality(imageSmoothingQuality)
    }
    get lineCap(): CanvasLineCap {
        return this.getLineCap()
    }
    set lineCap(lineCap: CanvasLineCap) {
        this.setLineCap(lineCap)
    }
    get lineDashOffset(): number {
        return this.getLineDashOffset()
    }
    set lineDashOffset(lineDashOffset: number) {
        this.setLineDashOffset(lineDashOffset)
    }
    get lineJoin(): CanvasLineJoin {
        return this.getLineJoin()
    }
    set lineJoin(lineJoin: CanvasLineJoin) {
        this.setLineJoin(lineJoin)
    }
    get lineWidth(): number {
        return this.getLineWidth()
    }
    set lineWidth(lineWidth: number) {
        this.setLineWidth(lineWidth)
    }
    get miterLimit(): number {
        return this.getMiterLimit()
    }
    set miterLimit(miterLimit: number) {
        this.setMiterLimit(miterLimit)
    }
    get shadowBlur(): number {
        return this.getShadowBlur()
    }
    set shadowBlur(shadowBlur: number) {
        this.setShadowBlur(shadowBlur)
    }
    get shadowColor(): string {
        return this.getShadowColor()
    }
    set shadowColor(shadowColor: string) {
        this.setShadowColor(shadowColor)
    }
    get shadowOffsetX(): number {
        return this.getShadowOffsetX()
    }
    set shadowOffsetX(shadowOffsetX: number) {
        this.setShadowOffsetX(shadowOffsetX)
    }
    get shadowOffsetY(): number {
        return this.getShadowOffsetY()
    }
    set shadowOffsetY(shadowOffsetY: number) {
        this.setShadowOffsetY(shadowOffsetY)
    }
    get direction(): CanvasDirection {
        return this.getDirection()
    }
    set direction(direction: CanvasDirection) {
        this.setDirection(direction)
    }
    get font(): string {
        return this.getFont()
    }
    set font(font: string) {
        this.setFont(font)
    }
    get textAlign(): CanvasTextAlign {
        return this.getTextAlign()
    }
    set textAlign(textAlign: CanvasTextAlign) {
        this.setTextAlign(textAlign)
    }
    get textBaseline(): CanvasTextBaseline {
        return this.getTextBaseline()
    }
    set textBaseline(textBaseline: CanvasTextBaseline) {
        this.setTextBaseline(textBaseline)
    }
    static ctor_canvasrenderer(): KPointer {
        const retval = ArkUIGeneratedNativeModule._CanvasRenderer_ctor()
        return retval
    }
     constructor() {
        super()
        const ctorPtr: KPointer = CanvasRenderer.ctor_canvasrenderer()
        this.peer = new Finalizable(ctorPtr, CanvasRenderer.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._CanvasRenderer_getFinalizer()
    }
    public drawImage(image: ImageBitmap | PixelMap, sx: number, sy: number, sw?: number, sh?: number, dx?: number, dy?: number, dw?: number, dh?: number): void {
        const image_type = runtimeType(image)
        const sx_type = runtimeType(sx)
        const sy_type = runtimeType(sy)
        const sw_type = runtimeType(sw)
        const sh_type = runtimeType(sh)
        const dx_type = runtimeType(dx)
        const dy_type = runtimeType(dy)
        const dw_type = runtimeType(dw)
        const dh_type = runtimeType(dh)
        if (((((RuntimeType.OBJECT) == (image_type)) && (image instanceof ImageBitmap)) || (((RuntimeType.OBJECT) == (image_type)) && ((image!.hasOwnProperty("isEditable"))))) && (RuntimeType.UNDEFINED == sw_type) && (RuntimeType.UNDEFINED == sh_type) && (RuntimeType.UNDEFINED == dx_type) && (RuntimeType.UNDEFINED == dy_type) && (RuntimeType.UNDEFINED == dw_type) && (RuntimeType.UNDEFINED == dh_type)) {
            const image_casted = image as (ImageBitmap | PixelMap)
            const dx_casted = sx as (number)
            const dy_casted = sy as (number)
            this?.drawImage0_serialize(image_casted, dx_casted, dy_casted)
            return
        }
        if (((((RuntimeType.OBJECT) == (image_type)) && (image instanceof ImageBitmap)) || (((RuntimeType.OBJECT) == (image_type)) && ((image!.hasOwnProperty("isEditable"))))) && (RuntimeType.NUMBER == sw_type) && (RuntimeType.NUMBER == sh_type) && (RuntimeType.UNDEFINED == dx_type) && (RuntimeType.UNDEFINED == dy_type) && (RuntimeType.UNDEFINED == dw_type) && (RuntimeType.UNDEFINED == dh_type)) {
            const image_casted = image as (ImageBitmap | PixelMap)
            const dx_casted = sx as (number)
            const dy_casted = sy as (number)
            const dw_casted = sw as (number)
            const dh_casted = sh as (number)
            this?.drawImage1_serialize(image_casted, dx_casted, dy_casted, dw_casted, dh_casted)
            return
        }
        if (((((RuntimeType.OBJECT) == (image_type)) && (image instanceof ImageBitmap)) || (((RuntimeType.OBJECT) == (image_type)) && ((image!.hasOwnProperty("isEditable"))))) && (RuntimeType.NUMBER == sw_type) && (RuntimeType.NUMBER == sh_type) && (RuntimeType.NUMBER == dx_type) && (RuntimeType.NUMBER == dy_type) && (RuntimeType.NUMBER == dw_type) && (RuntimeType.NUMBER == dh_type)) {
            const image_casted = image as (ImageBitmap | PixelMap)
            const sx_casted = sx as (number)
            const sy_casted = sy as (number)
            const sw_casted = sw as (number)
            const sh_casted = sh as (number)
            const dx_casted = dx as (number)
            const dy_casted = dy as (number)
            const dw_casted = dw as (number)
            const dh_casted = dh as (number)
            this?.drawImage2_serialize(image_casted, sx_casted, sy_casted, sw_casted, sh_casted, dx_casted, dy_casted, dw_casted, dh_casted)
            return
        }
        throw new Error("Can not select appropriate overload")
    }
    public beginPath(): void {
        this?.beginPath_serialize()
        return
    }
    public clip(path?: CanvasFillRule | undefined | Path2D, fillRule?: CanvasFillRule): void {
        const path_type = runtimeType(path)
        const fillRule_type = runtimeType(fillRule)
        if (((RuntimeType.STRING == path_type) || (RuntimeType.UNDEFINED == path_type)) && (RuntimeType.UNDEFINED == fillRule_type)) {
            const fillRule_casted = path as (CanvasFillRule | undefined)
            this?.clip0_serialize(fillRule_casted)
            return
        }
        if ((RuntimeType.OBJECT == path_type) && ((RuntimeType.STRING == fillRule_type) || (RuntimeType.UNDEFINED == fillRule_type))) {
            const path_casted = path as (Path2D)
            const fillRule_casted = fillRule as (CanvasFillRule | undefined)
            this?.clip1_serialize(path_casted, fillRule_casted)
            return
        }
        throw new Error("Can not select appropriate overload")
    }
    public fill(path?: CanvasFillRule | undefined | Path2D, fillRule?: CanvasFillRule): void {
        const path_type = runtimeType(path)
        const fillRule_type = runtimeType(fillRule)
        if (((RuntimeType.STRING == path_type) || (RuntimeType.UNDEFINED == path_type)) && (RuntimeType.UNDEFINED == fillRule_type)) {
            const fillRule_casted = path as (CanvasFillRule | undefined)
            this?.fill0_serialize(fillRule_casted)
            return
        }
        if ((RuntimeType.OBJECT == path_type) && ((RuntimeType.STRING == fillRule_type) || (RuntimeType.UNDEFINED == fillRule_type))) {
            const path_casted = path as (Path2D)
            const fillRule_casted = fillRule as (CanvasFillRule | undefined)
            this?.fill1_serialize(path_casted, fillRule_casted)
            return
        }
        throw new Error("Can not select appropriate overload")
    }
    public stroke(path?: Path2D): void {
        const path_type = runtimeType(path)
        if (RuntimeType.UNDEFINED == path_type) {
            this?.stroke0_serialize()
            return
        }
        if (RuntimeType.OBJECT == path_type) {
            const path_casted = path as (Path2D)
            this?.stroke1_serialize(path_casted)
            return
        }
        throw new Error("Can not select appropriate overload")
    }
    public createLinearGradient(x0: number, y0: number, x1: number, y1: number): CanvasGradient {
        const x0_casted = x0 as (number)
        const y0_casted = y0 as (number)
        const x1_casted = x1 as (number)
        const y1_casted = y1 as (number)
        return this.createLinearGradient_serialize(x0_casted, y0_casted, x1_casted, y1_casted)
    }
    public createPattern(image: ImageBitmap, repetition?: string): CanvasPattern | undefined {
        const image_casted = image as (ImageBitmap)
        const repetition_casted = repetition as (string | undefined)
        return this.createPattern_serialize(image_casted, repetition_casted)
    }
    public createRadialGradient(x0: number, y0: number, r0: number, x1: number, y1: number, r1: number): CanvasGradient {
        const x0_casted = x0 as (number)
        const y0_casted = y0 as (number)
        const r0_casted = r0 as (number)
        const x1_casted = x1 as (number)
        const y1_casted = y1 as (number)
        const r1_casted = r1 as (number)
        return this.createRadialGradient_serialize(x0_casted, y0_casted, r0_casted, x1_casted, y1_casted, r1_casted)
    }
    public createConicGradient(startAngle: number, x: number, y: number): CanvasGradient {
        const startAngle_casted = startAngle as (number)
        const x_casted = x as (number)
        const y_casted = y as (number)
        return this.createConicGradient_serialize(startAngle_casted, x_casted, y_casted)
    }
    public createImageData(sw: ImageData | number, sh?: number): ImageData {
        const sw_type = runtimeType(sw)
        const sh_type = runtimeType(sh)
        if ((RuntimeType.OBJECT == sw_type) && (RuntimeType.UNDEFINED == sh_type)) {
            const imagedata_casted = sw as (ImageData)
            return this.createImageData1_serialize(imagedata_casted)
        }
        if ((RuntimeType.NUMBER == sw_type) && (RuntimeType.NUMBER == sh_type)) {
            const sw_casted = sw as (number)
            const sh_casted = sh as (number)
            return this.createImageData0_serialize(sw_casted, sh_casted)
        }
        throw new Error("Can not select appropriate overload")
    }
    public getImageData(sx: number, sy: number, sw: number, sh: number): ImageData {
        const sx_casted = sx as (number)
        const sy_casted = sy as (number)
        const sw_casted = sw as (number)
        const sh_casted = sh as (number)
        return this.getImageData_serialize(sx_casted, sy_casted, sw_casted, sh_casted)
    }
    public getPixelMap(sx: number, sy: number, sw: number, sh: number): PixelMap {
        const sx_casted = sx as (number)
        const sy_casted = sy as (number)
        const sw_casted = sw as (number)
        const sh_casted = sh as (number)
        return this.getPixelMap_serialize(sx_casted, sy_casted, sw_casted, sh_casted)
    }
    public putImageData(imagedata: ImageData, dx: number | string, dy: number | string, dirtyX?: number | string, dirtyY?: number | string, dirtyWidth?: number | string, dirtyHeight?: number | string): void {
        const imagedata_type = runtimeType(imagedata)
        const dx_type = runtimeType(dx)
        const dy_type = runtimeType(dy)
        const dirtyX_type = runtimeType(dirtyX)
        const dirtyY_type = runtimeType(dirtyY)
        const dirtyWidth_type = runtimeType(dirtyWidth)
        const dirtyHeight_type = runtimeType(dirtyHeight)
        if (((RuntimeType.NUMBER == dx_type) || (RuntimeType.STRING == dx_type)) && ((RuntimeType.NUMBER == dy_type) || (RuntimeType.STRING == dy_type)) && (RuntimeType.UNDEFINED == dirtyX_type) && (RuntimeType.UNDEFINED == dirtyY_type) && (RuntimeType.UNDEFINED == dirtyWidth_type) && (RuntimeType.UNDEFINED == dirtyHeight_type)) {
            const imagedata_casted = imagedata as (ImageData)
            const dx_casted = dx as (number | string)
            const dy_casted = dy as (number | string)
            this?.putImageData0_serialize(imagedata_casted, dx_casted, dy_casted)
            return
        }
        if (((RuntimeType.NUMBER == dx_type) || (RuntimeType.STRING == dx_type)) && ((RuntimeType.NUMBER == dy_type) || (RuntimeType.STRING == dy_type)) && ((RuntimeType.NUMBER == dirtyX_type) || (RuntimeType.STRING == dirtyX_type)) && ((RuntimeType.NUMBER == dirtyY_type) || (RuntimeType.STRING == dirtyY_type)) && ((RuntimeType.NUMBER == dirtyWidth_type) || (RuntimeType.STRING == dirtyWidth_type)) && ((RuntimeType.NUMBER == dirtyHeight_type) || (RuntimeType.STRING == dirtyHeight_type))) {
            const imagedata_casted = imagedata as (ImageData)
            const dx_casted = dx as (number | string)
            const dy_casted = dy as (number | string)
            const dirtyX_casted = dirtyX as (number | string)
            const dirtyY_casted = dirtyY as (number | string)
            const dirtyWidth_casted = dirtyWidth as (number | string)
            const dirtyHeight_casted = dirtyHeight as (number | string)
            this?.putImageData1_serialize(imagedata_casted, dx_casted, dy_casted, dirtyX_casted, dirtyY_casted, dirtyWidth_casted, dirtyHeight_casted)
            return
        }
        throw new Error("Can not select appropriate overload")
    }
    public getLineDash(): Array<number> {
        return this.getLineDash_serialize()
    }
    public setLineDash(segments: Array<number>): void {
        const segments_casted = segments as (Array<number>)
        this?.setLineDash_serialize(segments_casted)
        return
    }
    public clearRect(x: number, y: number, w: number, h: number): void {
        const x_casted = x as (number)
        const y_casted = y as (number)
        const w_casted = w as (number)
        const h_casted = h as (number)
        this?.clearRect_serialize(x_casted, y_casted, w_casted, h_casted)
        return
    }
    public fillRect(x: number, y: number, w: number, h: number): void {
        const x_casted = x as (number)
        const y_casted = y as (number)
        const w_casted = w as (number)
        const h_casted = h as (number)
        this?.fillRect_serialize(x_casted, y_casted, w_casted, h_casted)
        return
    }
    public strokeRect(x: number, y: number, w: number, h: number): void {
        const x_casted = x as (number)
        const y_casted = y as (number)
        const w_casted = w as (number)
        const h_casted = h as (number)
        this?.strokeRect_serialize(x_casted, y_casted, w_casted, h_casted)
        return
    }
    public restore(): void {
        this?.restore_serialize()
        return
    }
    public save(): void {
        this?.save_serialize()
        return
    }
    public fillText(text: string, x: number, y: number, maxWidth?: number): void {
        const text_casted = text as (string)
        const x_casted = x as (number)
        const y_casted = y as (number)
        const maxWidth_casted = maxWidth as (number | undefined)
        this?.fillText_serialize(text_casted, x_casted, y_casted, maxWidth_casted)
        return
    }
    public measureText(text: string): TextMetrics {
        const text_casted = text as (string)
        return this.measureText_serialize(text_casted)
    }
    public strokeText(text: string, x: number, y: number, maxWidth?: number): void {
        const text_casted = text as (string)
        const x_casted = x as (number)
        const y_casted = y as (number)
        const maxWidth_casted = maxWidth as (number | undefined)
        this?.strokeText_serialize(text_casted, x_casted, y_casted, maxWidth_casted)
        return
    }
    public getTransform(): Matrix2D {
        return this.getTransform_serialize()
    }
    public resetTransform(): void {
        this?.resetTransform_serialize()
        return
    }
    public rotate(angle: number): void {
        const angle_casted = angle as (number)
        this?.rotate_serialize(angle_casted)
        return
    }
    public scale(x: number, y: number): void {
        const x_casted = x as (number)
        const y_casted = y as (number)
        this?.scale_serialize(x_casted, y_casted)
        return
    }
    public setTransform(a?: Matrix2D | undefined | number, b?: number, c?: number, d?: number, e?: number, f?: number): void {
        const a_type = runtimeType(a)
        const b_type = runtimeType(b)
        const c_type = runtimeType(c)
        const d_type = runtimeType(d)
        const e_type = runtimeType(e)
        const f_type = runtimeType(f)
        if (((RuntimeType.OBJECT == a_type) || (RuntimeType.UNDEFINED == a_type)) && (RuntimeType.UNDEFINED == b_type) && (RuntimeType.UNDEFINED == c_type) && (RuntimeType.UNDEFINED == d_type) && (RuntimeType.UNDEFINED == e_type) && (RuntimeType.UNDEFINED == f_type)) {
            const transform_casted = a as (Matrix2D | undefined)
            this?.setTransform1_serialize(transform_casted)
            return
        }
        if ((RuntimeType.NUMBER == a_type) && (RuntimeType.NUMBER == b_type) && (RuntimeType.NUMBER == c_type) && (RuntimeType.NUMBER == d_type) && (RuntimeType.NUMBER == e_type) && (RuntimeType.NUMBER == f_type)) {
            const a_casted = a as (number)
            const b_casted = b as (number)
            const c_casted = c as (number)
            const d_casted = d as (number)
            const e_casted = e as (number)
            const f_casted = f as (number)
            this?.setTransform0_serialize(a_casted, b_casted, c_casted, d_casted, e_casted, f_casted)
            return
        }
        throw new Error("Can not select appropriate overload")
    }
    public transform(a: number, b: number, c: number, d: number, e: number, f: number): void {
        const a_casted = a as (number)
        const b_casted = b as (number)
        const c_casted = c as (number)
        const d_casted = d as (number)
        const e_casted = e as (number)
        const f_casted = f as (number)
        this?.transform_serialize(a_casted, b_casted, c_casted, d_casted, e_casted, f_casted)
        return
    }
    public translate(x: number, y: number): void {
        const x_casted = x as (number)
        const y_casted = y as (number)
        this?.translate_serialize(x_casted, y_casted)
        return
    }
    public setPixelMap(value?: PixelMap): void {
        const value_casted = value as (PixelMap | undefined)
        this?.setPixelMap_serialize(value_casted)
        return
    }
    public transferFromImageBitmap(bitmap: ImageBitmap): void {
        const bitmap_casted = bitmap as (ImageBitmap)
        this?.transferFromImageBitmap_serialize(bitmap_casted)
        return
    }
    public saveLayer(): void {
        this?.saveLayer_serialize()
        return
    }
    public restoreLayer(): void {
        this?.restoreLayer_serialize()
        return
    }
    public reset(): void {
        this?.reset_serialize()
        return
    }
    private getGlobalAlpha(): number {
        return this.getGlobalAlpha_serialize()
    }
    private setGlobalAlpha(globalAlpha: number): void {
        const globalAlpha_casted = globalAlpha as (number)
        this?.setGlobalAlpha_serialize(globalAlpha_casted)
        return
    }
    private getGlobalCompositeOperation(): string {
        return this.getGlobalCompositeOperation_serialize()
    }
    private setGlobalCompositeOperation(globalCompositeOperation: string): void {
        const globalCompositeOperation_casted = globalCompositeOperation as (string)
        this?.setGlobalCompositeOperation_serialize(globalCompositeOperation_casted)
        return
    }
    private setFillStyle(fillStyle: string | number | CanvasGradient | CanvasPattern): void {
        const fillStyle_casted = fillStyle as (string | number | CanvasGradient | CanvasPattern)
        this?.setFillStyle_serialize(fillStyle_casted)
        return
    }
    private setStrokeStyle(strokeStyle: string | number | CanvasGradient | CanvasPattern): void {
        const strokeStyle_casted = strokeStyle as (string | number | CanvasGradient | CanvasPattern)
        this?.setStrokeStyle_serialize(strokeStyle_casted)
        return
    }
    private getFilter(): string {
        return this.getFilter_serialize()
    }
    private setFilter(filter: string): void {
        const filter_casted = filter as (string)
        this?.setFilter_serialize(filter_casted)
        return
    }
    private getImageSmoothingEnabled(): boolean {
        return this.getImageSmoothingEnabled_serialize()
    }
    private setImageSmoothingEnabled(imageSmoothingEnabled: boolean): void {
        const imageSmoothingEnabled_casted = imageSmoothingEnabled as (boolean)
        this?.setImageSmoothingEnabled_serialize(imageSmoothingEnabled_casted)
        return
    }
    private getImageSmoothingQuality(): ImageSmoothingQuality {
        return this.getImageSmoothingQuality_serialize()
    }
    private setImageSmoothingQuality(imageSmoothingQuality: ImageSmoothingQuality): void {
        const imageSmoothingQuality_casted = imageSmoothingQuality as (ImageSmoothingQuality)
        this?.setImageSmoothingQuality_serialize(imageSmoothingQuality_casted)
        return
    }
    private getLineCap(): CanvasLineCap {
        return this.getLineCap_serialize()
    }
    private setLineCap(lineCap: CanvasLineCap): void {
        const lineCap_casted = lineCap as (CanvasLineCap)
        this?.setLineCap_serialize(lineCap_casted)
        return
    }
    private getLineDashOffset(): number {
        return this.getLineDashOffset_serialize()
    }
    private setLineDashOffset(lineDashOffset: number): void {
        const lineDashOffset_casted = lineDashOffset as (number)
        this?.setLineDashOffset_serialize(lineDashOffset_casted)
        return
    }
    private getLineJoin(): CanvasLineJoin {
        return this.getLineJoin_serialize()
    }
    private setLineJoin(lineJoin: CanvasLineJoin): void {
        const lineJoin_casted = lineJoin as (CanvasLineJoin)
        this?.setLineJoin_serialize(lineJoin_casted)
        return
    }
    private getLineWidth(): number {
        return this.getLineWidth_serialize()
    }
    private setLineWidth(lineWidth: number): void {
        const lineWidth_casted = lineWidth as (number)
        this?.setLineWidth_serialize(lineWidth_casted)
        return
    }
    private getMiterLimit(): number {
        return this.getMiterLimit_serialize()
    }
    private setMiterLimit(miterLimit: number): void {
        const miterLimit_casted = miterLimit as (number)
        this?.setMiterLimit_serialize(miterLimit_casted)
        return
    }
    private getShadowBlur(): number {
        return this.getShadowBlur_serialize()
    }
    private setShadowBlur(shadowBlur: number): void {
        const shadowBlur_casted = shadowBlur as (number)
        this?.setShadowBlur_serialize(shadowBlur_casted)
        return
    }
    private getShadowColor(): string {
        return this.getShadowColor_serialize()
    }
    private setShadowColor(shadowColor: string): void {
        const shadowColor_casted = shadowColor as (string)
        this?.setShadowColor_serialize(shadowColor_casted)
        return
    }
    private getShadowOffsetX(): number {
        return this.getShadowOffsetX_serialize()
    }
    private setShadowOffsetX(shadowOffsetX: number): void {
        const shadowOffsetX_casted = shadowOffsetX as (number)
        this?.setShadowOffsetX_serialize(shadowOffsetX_casted)
        return
    }
    private getShadowOffsetY(): number {
        return this.getShadowOffsetY_serialize()
    }
    private setShadowOffsetY(shadowOffsetY: number): void {
        const shadowOffsetY_casted = shadowOffsetY as (number)
        this?.setShadowOffsetY_serialize(shadowOffsetY_casted)
        return
    }
    private getDirection(): CanvasDirection {
        return this.getDirection_serialize()
    }
    private setDirection(direction: CanvasDirection): void {
        const direction_casted = direction as (CanvasDirection)
        this?.setDirection_serialize(direction_casted)
        return
    }
    private getFont(): string {
        return this.getFont_serialize()
    }
    private setFont(font: string): void {
        const font_casted = font as (string)
        this?.setFont_serialize(font_casted)
        return
    }
    private getTextAlign(): CanvasTextAlign {
        return this.getTextAlign_serialize()
    }
    private setTextAlign(textAlign: CanvasTextAlign): void {
        const textAlign_casted = textAlign as (CanvasTextAlign)
        this?.setTextAlign_serialize(textAlign_casted)
        return
    }
    private getTextBaseline(): CanvasTextBaseline {
        return this.getTextBaseline_serialize()
    }
    private setTextBaseline(textBaseline: CanvasTextBaseline): void {
        const textBaseline_casted = textBaseline as (CanvasTextBaseline)
        this?.setTextBaseline_serialize(textBaseline_casted)
        return
    }
    private drawImage0_serialize(image: ImageBitmap | PixelMap, dx: number, dy: number): void {
        const thisSerializer: Serializer = Serializer.hold()
        let image_type: int32 = RuntimeType.UNDEFINED
        image_type = runtimeType(image)
        if (((RuntimeType.OBJECT) == (image_type)) && (image instanceof ImageBitmap)) {
            thisSerializer.writeInt8(0)
            const image_0 = unsafeCast<ImageBitmap>(image)
            thisSerializer.writeImageBitmap(image_0)
        }
        else if (((RuntimeType.OBJECT) == (image_type)) && ((image!.hasOwnProperty("isEditable")))) {
            thisSerializer.writeInt8(1)
            const image_1 = unsafeCast<PixelMap>(image)
            thisSerializer.writePixelMap(image_1)
        }
        ArkUIGeneratedNativeModule._CanvasRenderer_drawImage0(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length(), dx, dy)
        thisSerializer.release()
    }
    private drawImage1_serialize(image: ImageBitmap | PixelMap, dx: number, dy: number, dw: number, dh: number): void {
        const thisSerializer: Serializer = Serializer.hold()
        let image_type: int32 = RuntimeType.UNDEFINED
        image_type = runtimeType(image)
        if (((RuntimeType.OBJECT) == (image_type)) && (image instanceof ImageBitmap)) {
            thisSerializer.writeInt8(0)
            const image_0 = unsafeCast<ImageBitmap>(image)
            thisSerializer.writeImageBitmap(image_0)
        }
        else if (((RuntimeType.OBJECT) == (image_type)) && ((image!.hasOwnProperty("isEditable")))) {
            thisSerializer.writeInt8(1)
            const image_1 = unsafeCast<PixelMap>(image)
            thisSerializer.writePixelMap(image_1)
        }
        ArkUIGeneratedNativeModule._CanvasRenderer_drawImage1(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length(), dx, dy, dw, dh)
        thisSerializer.release()
    }
    private drawImage2_serialize(image: ImageBitmap | PixelMap, sx: number, sy: number, sw: number, sh: number, dx: number, dy: number, dw: number, dh: number): void {
        const thisSerializer: Serializer = Serializer.hold()
        let image_type: int32 = RuntimeType.UNDEFINED
        image_type = runtimeType(image)
        if (((RuntimeType.OBJECT) == (image_type)) && (image instanceof ImageBitmap)) {
            thisSerializer.writeInt8(0)
            const image_0 = unsafeCast<ImageBitmap>(image)
            thisSerializer.writeImageBitmap(image_0)
        }
        else if (((RuntimeType.OBJECT) == (image_type)) && ((image!.hasOwnProperty("isEditable")))) {
            thisSerializer.writeInt8(1)
            const image_1 = unsafeCast<PixelMap>(image)
            thisSerializer.writePixelMap(image_1)
        }
        ArkUIGeneratedNativeModule._CanvasRenderer_drawImage2(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length(), sx, sy, sw, sh, dx, dy, dw, dh)
        thisSerializer.release()
    }
    private beginPath_serialize(): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_beginPath(this.peer!.ptr)
    }
    private clip0_serialize(fillRule?: CanvasFillRule): void {
        const thisSerializer: Serializer = Serializer.hold()
        let fillRule_type: int32 = RuntimeType.UNDEFINED
        fillRule_type = runtimeType(fillRule)
        thisSerializer.writeInt8(fillRule_type)
        if ((RuntimeType.UNDEFINED) != (fillRule_type)) {
            const fillRule_value = fillRule!
            thisSerializer.writeString(fillRule_value)
        }
        ArkUIGeneratedNativeModule._CanvasRenderer_clip0(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    private clip1_serialize(path: Path2D, fillRule?: CanvasFillRule): void {
        const thisSerializer: Serializer = Serializer.hold()
        let fillRule_type: int32 = RuntimeType.UNDEFINED
        fillRule_type = runtimeType(fillRule)
        thisSerializer.writeInt8(fillRule_type)
        if ((RuntimeType.UNDEFINED) != (fillRule_type)) {
            const fillRule_value = fillRule!
            thisSerializer.writeString(fillRule_value)
        }
        ArkUIGeneratedNativeModule._CanvasRenderer_clip1(this.peer!.ptr, toPeerPtr(path), thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    private fill0_serialize(fillRule?: CanvasFillRule): void {
        const thisSerializer: Serializer = Serializer.hold()
        let fillRule_type: int32 = RuntimeType.UNDEFINED
        fillRule_type = runtimeType(fillRule)
        thisSerializer.writeInt8(fillRule_type)
        if ((RuntimeType.UNDEFINED) != (fillRule_type)) {
            const fillRule_value = fillRule!
            thisSerializer.writeString(fillRule_value)
        }
        ArkUIGeneratedNativeModule._CanvasRenderer_fill0(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    private fill1_serialize(path: Path2D, fillRule?: CanvasFillRule): void {
        const thisSerializer: Serializer = Serializer.hold()
        let fillRule_type: int32 = RuntimeType.UNDEFINED
        fillRule_type = runtimeType(fillRule)
        thisSerializer.writeInt8(fillRule_type)
        if ((RuntimeType.UNDEFINED) != (fillRule_type)) {
            const fillRule_value = fillRule!
            thisSerializer.writeString(fillRule_value)
        }
        ArkUIGeneratedNativeModule._CanvasRenderer_fill1(this.peer!.ptr, toPeerPtr(path), thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    private stroke0_serialize(): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_stroke0(this.peer!.ptr)
    }
    private stroke1_serialize(path: Path2D): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_stroke1(this.peer!.ptr, toPeerPtr(path))
    }
    private createLinearGradient_serialize(x0: number, y0: number, x1: number, y1: number): CanvasGradient {
        const retval = ArkUIGeneratedNativeModule._CanvasRenderer_createLinearGradient(this.peer!.ptr, x0, y0, x1, y1)
        const obj: CanvasGradient = CanvasGradientInternal.fromPtr(retval)
        return obj
    }
    private createPattern_serialize(image: ImageBitmap, repetition?: string): CanvasPattern | undefined {
        const thisSerializer: Serializer = Serializer.hold()
        let repetition_type: int32 = RuntimeType.UNDEFINED
        repetition_type = runtimeType(repetition)
        thisSerializer.writeInt8(repetition_type)
        if ((RuntimeType.UNDEFINED) != (repetition_type)) {
            const repetition_value = repetition!
            thisSerializer.writeString(repetition_value)
        }
        const retval = ArkUIGeneratedNativeModule._CanvasRenderer_createPattern(this.peer!.ptr, toPeerPtr(image), thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length);
        let retval_type : int32 = retvalDeserializer.readInt8() as int32
        if ((RuntimeType.UNDEFINED) != (retval_type)) {
            const pattern = retvalDeserializer.readCanvasPattern();
            return pattern;
        }
        return undefined;
    }
    private createRadialGradient_serialize(x0: number, y0: number, r0: number, x1: number, y1: number, r1: number): CanvasGradient {
        const retval = ArkUIGeneratedNativeModule._CanvasRenderer_createRadialGradient(this.peer!.ptr, x0, y0, r0, x1, y1, r1)
        const obj: CanvasGradient = CanvasGradientInternal.fromPtr(retval)
        return obj
    }
    private createConicGradient_serialize(startAngle: number, x: number, y: number): CanvasGradient {
        const retval = ArkUIGeneratedNativeModule._CanvasRenderer_createConicGradient(this.peer!.ptr, startAngle, x, y)
        const obj: CanvasGradient = CanvasGradientInternal.fromPtr(retval)
        return obj
    }
    private createImageData0_serialize(sw: number, sh: number): ImageData {
        const retval = ArkUIGeneratedNativeModule._CanvasRenderer_createImageData0(this.peer!.ptr, sw, sh)
        const obj: ImageData = ImageDataInternal.fromPtr(retval)
        return obj
    }
    private createImageData1_serialize(imagedata: ImageData): ImageData {
        const retval = ArkUIGeneratedNativeModule._CanvasRenderer_createImageData1(this.peer!.ptr, toPeerPtr(imagedata))
        const obj: ImageData = ImageDataInternal.fromPtr(retval)
        return obj
    }
    private getImageData_serialize(sx: number, sy: number, sw: number, sh: number): ImageData {
        const retval = ArkUIGeneratedNativeModule._CanvasRenderer_getImageData(this.peer!.ptr, sx, sy, sw, sh)
        const obj: ImageData = ImageDataInternal.fromPtr(retval)
        return obj
    }
    private getPixelMap_serialize(sx: number, sy: number, sw: number, sh: number): PixelMap {
        const retval = ArkUIGeneratedNativeModule._CanvasRenderer_getPixelMap(this.peer!.ptr, sx, sy, sw, sh)
        const obj: PixelMap = PixelMapInternal.fromPtr(retval)
        return obj
    }
    private putImageData0_serialize(imagedata: ImageData, dx: number | string, dy: number | string): void {
        const thisSerializer: Serializer = Serializer.hold()
        let dx_type: int32 = RuntimeType.UNDEFINED
        dx_type = runtimeType(dx)
        if (RuntimeType.NUMBER == dx_type) {
            thisSerializer.writeInt8(0)
            const dx_0 = unsafeCast<number>(dx)
            thisSerializer.writeNumber(dx_0)
        }
        else if (RuntimeType.STRING == dx_type) {
            thisSerializer.writeInt8(1)
            const dx_1 = unsafeCast<string>(dx)
            thisSerializer.writeString(dx_1)
        }
        let dy_type: int32 = RuntimeType.UNDEFINED
        dy_type = runtimeType(dy)
        if (RuntimeType.NUMBER == dy_type) {
            thisSerializer.writeInt8(0)
            const dy_0 = unsafeCast<number>(dy)
            thisSerializer.writeNumber(dy_0)
        }
        else if (RuntimeType.STRING == dy_type) {
            thisSerializer.writeInt8(1)
            const dy_1 = unsafeCast<string>(dy)
            thisSerializer.writeString(dy_1)
        }
        ArkUIGeneratedNativeModule._CanvasRenderer_putImageData0(this.peer!.ptr, toPeerPtr(imagedata), thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    private putImageData1_serialize(imagedata: ImageData, dx: number | string, dy: number | string, dirtyX: number | string, dirtyY: number | string, dirtyWidth: number | string, dirtyHeight: number | string): void {
        const thisSerializer: Serializer = Serializer.hold()
        let dx_type: int32 = RuntimeType.UNDEFINED
        dx_type = runtimeType(dx)
        if (RuntimeType.NUMBER == dx_type) {
            thisSerializer.writeInt8(0)
            const dx_0 = unsafeCast<number>(dx)
            thisSerializer.writeNumber(dx_0)
        }
        else if (RuntimeType.STRING == dx_type) {
            thisSerializer.writeInt8(1)
            const dx_1 = unsafeCast<string>(dx)
            thisSerializer.writeString(dx_1)
        }
        let dy_type: int32 = RuntimeType.UNDEFINED
        dy_type = runtimeType(dy)
        if (RuntimeType.NUMBER == dy_type) {
            thisSerializer.writeInt8(0)
            const dy_0 = unsafeCast<number>(dy)
            thisSerializer.writeNumber(dy_0)
        }
        else if (RuntimeType.STRING == dy_type) {
            thisSerializer.writeInt8(1)
            const dy_1 = unsafeCast<string>(dy)
            thisSerializer.writeString(dy_1)
        }
        let dirtyX_type: int32 = RuntimeType.UNDEFINED
        dirtyX_type = runtimeType(dirtyX)
        if (RuntimeType.NUMBER == dirtyX_type) {
            thisSerializer.writeInt8(0)
            const dirtyX_0 = unsafeCast<number>(dirtyX)
            thisSerializer.writeNumber(dirtyX_0)
        }
        else if (RuntimeType.STRING == dirtyX_type) {
            thisSerializer.writeInt8(1)
            const dirtyX_1 = unsafeCast<string>(dirtyX)
            thisSerializer.writeString(dirtyX_1)
        }
        let dirtyY_type: int32 = RuntimeType.UNDEFINED
        dirtyY_type = runtimeType(dirtyY)
        if (RuntimeType.NUMBER == dirtyY_type) {
            thisSerializer.writeInt8(0)
            const dirtyY_0 = unsafeCast<number>(dirtyY)
            thisSerializer.writeNumber(dirtyY_0)
        }
        else if (RuntimeType.STRING == dirtyY_type) {
            thisSerializer.writeInt8(1)
            const dirtyY_1 = unsafeCast<string>(dirtyY)
            thisSerializer.writeString(dirtyY_1)
        }
        let dirtyWidth_type: int32 = RuntimeType.UNDEFINED
        dirtyWidth_type = runtimeType(dirtyWidth)
        if (RuntimeType.NUMBER == dirtyWidth_type) {
            thisSerializer.writeInt8(0)
            const dirtyWidth_0 = unsafeCast<number>(dirtyWidth)
            thisSerializer.writeNumber(dirtyWidth_0)
        }
        else if (RuntimeType.STRING == dirtyWidth_type) {
            thisSerializer.writeInt8(1)
            const dirtyWidth_1 = unsafeCast<string>(dirtyWidth)
            thisSerializer.writeString(dirtyWidth_1)
        }
        let dirtyHeight_type: int32 = RuntimeType.UNDEFINED
        dirtyHeight_type = runtimeType(dirtyHeight)
        if (RuntimeType.NUMBER == dirtyHeight_type) {
            thisSerializer.writeInt8(0)
            const dirtyHeight_0 = unsafeCast<number>(dirtyHeight)
            thisSerializer.writeNumber(dirtyHeight_0)
        }
        else if (RuntimeType.STRING == dirtyHeight_type) {
            thisSerializer.writeInt8(1)
            const dirtyHeight_1 = unsafeCast<string>(dirtyHeight)
            thisSerializer.writeString(dirtyHeight_1)
        }
        ArkUIGeneratedNativeModule._CanvasRenderer_putImageData1(this.peer!.ptr, toPeerPtr(imagedata), thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    private getLineDash_serialize(): Array<number> {
        const retval = ArkUIGeneratedNativeModule._CanvasRenderer_getLineDash(this.peer!.ptr)
        let retvalDeserializer: Deserializer = new Deserializer(retval.buffer, retval.byteLength)
        const buffer_length: int32 = retvalDeserializer.readInt32()
        let buffer: Array<number> = new Array<number>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            buffer[buffer_i] = (retvalDeserializer.readNumber() as number)
        }
        const returnResult: Array<number> = buffer
        return returnResult
    }
    private setLineDash_serialize(segments: Array<number>): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeInt32(segments.length)
        for (let i = 0; i < segments.length; i++) {
            const segments_element: number = segments[i]
            thisSerializer.writeNumber(segments_element)
        }
        ArkUIGeneratedNativeModule._CanvasRenderer_setLineDash(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    private clearRect_serialize(x: number, y: number, w: number, h: number): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_clearRect(this.peer!.ptr, x, y, w, h)
    }
    private fillRect_serialize(x: number, y: number, w: number, h: number): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_fillRect(this.peer!.ptr, x, y, w, h)
    }
    private strokeRect_serialize(x: number, y: number, w: number, h: number): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_strokeRect(this.peer!.ptr, x, y, w, h)
    }
    private restore_serialize(): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_restore(this.peer!.ptr)
    }
    private save_serialize(): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_save(this.peer!.ptr)
    }
    private fillText_serialize(text: string, x: number, y: number, maxWidth?: number): void {
        const thisSerializer: Serializer = Serializer.hold()
        let maxWidth_type: int32 = RuntimeType.UNDEFINED
        maxWidth_type = runtimeType(maxWidth)
        thisSerializer.writeInt8(maxWidth_type)
        if ((RuntimeType.UNDEFINED) != (maxWidth_type)) {
            const maxWidth_value = maxWidth!
            thisSerializer.writeNumber(maxWidth_value)
        }
        ArkUIGeneratedNativeModule._CanvasRenderer_fillText(this.peer!.ptr, text, x, y, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    private measureText_serialize(text: string): TextMetrics {
        const retval = ArkUIGeneratedNativeModule._CanvasRenderer_measureText(this.peer!.ptr, text)
        let retvalDeserializer: Deserializer = new Deserializer(retval.buffer, retval.byteLength)
        const returnResult: TextMetrics = retvalDeserializer.readTextMetrics()
        return returnResult
    }
    private strokeText_serialize(text: string, x: number, y: number, maxWidth?: number): void {
        const thisSerializer: Serializer = Serializer.hold()
        let maxWidth_type: int32 = RuntimeType.UNDEFINED
        maxWidth_type = runtimeType(maxWidth)
        thisSerializer.writeInt8(maxWidth_type)
        if ((RuntimeType.UNDEFINED) != (maxWidth_type)) {
            const maxWidth_value = maxWidth!
            thisSerializer.writeNumber(maxWidth_value)
        }
        ArkUIGeneratedNativeModule._CanvasRenderer_strokeText(this.peer!.ptr, text, x, y, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    private getTransform_serialize(): Matrix2D {
        const retval = ArkUIGeneratedNativeModule._CanvasRenderer_getTransform(this.peer!.ptr)
        const obj: Matrix2D = Matrix2DInternal.fromPtr(retval)
        return obj
    }
    private resetTransform_serialize(): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_resetTransform(this.peer!.ptr)
    }
    private rotate_serialize(angle: number): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_rotate(this.peer!.ptr, angle)
    }
    private scale_serialize(x: number, y: number): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_scale(this.peer!.ptr, x, y)
    }
    private setTransform0_serialize(a: number, b: number, c: number, d: number, e: number, f: number): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_setTransform0(this.peer!.ptr, a, b, c, d, e, f)
    }
    private setTransform1_serialize(transform?: Matrix2D): void {
        const thisSerializer: Serializer = Serializer.hold()
        let transform_type: int32 = RuntimeType.UNDEFINED
        transform_type = runtimeType(transform)
        thisSerializer.writeInt8(transform_type)
        if ((RuntimeType.UNDEFINED) != (transform_type)) {
            const transform_value = transform!
            thisSerializer.writeMatrix2D(transform_value)
        }
        ArkUIGeneratedNativeModule._CanvasRenderer_setTransform1(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    private transform_serialize(a: number, b: number, c: number, d: number, e: number, f: number): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_transform(this.peer!.ptr, a, b, c, d, e, f)
    }
    private translate_serialize(x: number, y: number): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_translate(this.peer!.ptr, x, y)
    }
    private setPixelMap_serialize(value?: PixelMap): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value = value!
            thisSerializer.writePixelMap(value_value)
        }
        ArkUIGeneratedNativeModule._CanvasRenderer_setPixelMap(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    private transferFromImageBitmap_serialize(bitmap: ImageBitmap): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_transferFromImageBitmap(this.peer!.ptr, toPeerPtr(bitmap))
    }
    private saveLayer_serialize(): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_saveLayer(this.peer!.ptr)
    }
    private restoreLayer_serialize(): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_restoreLayer(this.peer!.ptr)
    }
    private reset_serialize(): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_reset(this.peer!.ptr)
    }
    private getGlobalAlpha_serialize(): number {
        const retval = ArkUIGeneratedNativeModule._CanvasRenderer_getGlobalAlpha(this.peer!.ptr)
        return retval
    }
    private setGlobalAlpha_serialize(globalAlpha: number): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_setGlobalAlpha(this.peer!.ptr, globalAlpha)
    }
    private getGlobalCompositeOperation_serialize(): string {
        const retval = ArkUIGeneratedNativeModule._CanvasRenderer_getGlobalCompositeOperation(this.peer!.ptr)
        return retval
    }
    private setGlobalCompositeOperation_serialize(globalCompositeOperation: string): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_setGlobalCompositeOperation(this.peer!.ptr, globalCompositeOperation)
    }
    private setFillStyle_serialize(fillStyle: string | number | CanvasGradient | CanvasPattern): void {
        const thisSerializer: Serializer = Serializer.hold()
        let fillStyle_type: int32 = RuntimeType.UNDEFINED
        fillStyle_type = runtimeType(fillStyle)
        if (RuntimeType.STRING == fillStyle_type) {
            thisSerializer.writeInt8(0)
            const fillStyle_0 = unsafeCast<string>(fillStyle)
            thisSerializer.writeString(fillStyle_0)
        }
        else if (RuntimeType.NUMBER == fillStyle_type) {
            thisSerializer.writeInt8(1)
            const fillStyle_1 = unsafeCast<number>(fillStyle)
            thisSerializer.writeNumber(fillStyle_1)
        }
        else if (((RuntimeType.OBJECT) == (fillStyle_type)) && (fillStyle instanceof CanvasGradient)) {
            thisSerializer.writeInt8(2)
            const fillStyle_2 = unsafeCast<CanvasGradient>(fillStyle)
            thisSerializer.writeCanvasGradient(fillStyle_2)
        }
        else if (RuntimeType.OBJECT == fillStyle_type) {
            thisSerializer.writeInt8(3)
            const fillStyle_3 = unsafeCast<CanvasPattern>(fillStyle)
            thisSerializer.writeCanvasPattern(fillStyle_3)
        }
        ArkUIGeneratedNativeModule._CanvasRenderer_setFillStyle(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    private setStrokeStyle_serialize(strokeStyle: string | number | CanvasGradient | CanvasPattern): void {
        const thisSerializer: Serializer = Serializer.hold()
        let strokeStyle_type: int32 = RuntimeType.UNDEFINED
        strokeStyle_type = runtimeType(strokeStyle)
        if (RuntimeType.STRING == strokeStyle_type) {
            thisSerializer.writeInt8(0)
            const strokeStyle_0 = unsafeCast<string>(strokeStyle)
            thisSerializer.writeString(strokeStyle_0)
        }
        else if (RuntimeType.NUMBER == strokeStyle_type) {
            thisSerializer.writeInt8(1)
            const strokeStyle_1 = unsafeCast<number>(strokeStyle)
            thisSerializer.writeNumber(strokeStyle_1)
        }
        else if (((RuntimeType.OBJECT) == (strokeStyle_type)) && (strokeStyle instanceof CanvasGradient)) {
            thisSerializer.writeInt8(2)
            const strokeStyle_2 = unsafeCast<CanvasGradient>(strokeStyle)
            thisSerializer.writeCanvasGradient(strokeStyle_2)
        }
        else if (RuntimeType.OBJECT == strokeStyle_type) {
            thisSerializer.writeInt8(3)
            const strokeStyle_3 = unsafeCast<CanvasPattern>(strokeStyle)
            thisSerializer.writeCanvasPattern(strokeStyle_3)
        }
        ArkUIGeneratedNativeModule._CanvasRenderer_setStrokeStyle(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    private getFilter_serialize(): string {
        const retval = ArkUIGeneratedNativeModule._CanvasRenderer_getFilter(this.peer!.ptr)
        return retval
    }
    private setFilter_serialize(filter: string): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_setFilter(this.peer!.ptr, filter)
    }
    private getImageSmoothingEnabled_serialize(): boolean {
        const retval = ArkUIGeneratedNativeModule._CanvasRenderer_getImageSmoothingEnabled(this.peer!.ptr)
        return retval
    }
    private setImageSmoothingEnabled_serialize(imageSmoothingEnabled: boolean): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_setImageSmoothingEnabled(this.peer!.ptr, +imageSmoothingEnabled)
    }
    private getImageSmoothingQuality_serialize(): ImageSmoothingQuality {
        const retval = ArkUIGeneratedNativeModule._CanvasRenderer_getImageSmoothingQuality(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setImageSmoothingQuality_serialize(imageSmoothingQuality: ImageSmoothingQuality): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_setImageSmoothingQuality(this.peer!.ptr, imageSmoothingQuality)
    }
    private getLineCap_serialize(): CanvasLineCap {
        const retval = ArkUIGeneratedNativeModule._CanvasRenderer_getLineCap(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setLineCap_serialize(lineCap: CanvasLineCap): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_setLineCap(this.peer!.ptr, lineCap)
    }
    private getLineDashOffset_serialize(): number {
        const retval = ArkUIGeneratedNativeModule._CanvasRenderer_getLineDashOffset(this.peer!.ptr)
        return retval
    }
    private setLineDashOffset_serialize(lineDashOffset: number): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_setLineDashOffset(this.peer!.ptr, lineDashOffset)
    }
    private getLineJoin_serialize(): CanvasLineJoin {
        const retval = ArkUIGeneratedNativeModule._CanvasRenderer_getLineJoin(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setLineJoin_serialize(lineJoin: CanvasLineJoin): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_setLineJoin(this.peer!.ptr, lineJoin)
    }
    private getLineWidth_serialize(): number {
        const retval = ArkUIGeneratedNativeModule._CanvasRenderer_getLineWidth(this.peer!.ptr)
        return retval
    }
    private setLineWidth_serialize(lineWidth: number): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_setLineWidth(this.peer!.ptr, lineWidth)
    }
    private getMiterLimit_serialize(): number {
        const retval = ArkUIGeneratedNativeModule._CanvasRenderer_getMiterLimit(this.peer!.ptr)
        return retval
    }
    private setMiterLimit_serialize(miterLimit: number): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_setMiterLimit(this.peer!.ptr, miterLimit)
    }
    private getShadowBlur_serialize(): number {
        const retval = ArkUIGeneratedNativeModule._CanvasRenderer_getShadowBlur(this.peer!.ptr)
        return retval
    }
    private setShadowBlur_serialize(shadowBlur: number): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_setShadowBlur(this.peer!.ptr, shadowBlur)
    }
    private getShadowColor_serialize(): string {
        const retval = ArkUIGeneratedNativeModule._CanvasRenderer_getShadowColor(this.peer!.ptr)
        return retval
    }
    private setShadowColor_serialize(shadowColor: string): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_setShadowColor(this.peer!.ptr, shadowColor)
    }
    private getShadowOffsetX_serialize(): number {
        const retval = ArkUIGeneratedNativeModule._CanvasRenderer_getShadowOffsetX(this.peer!.ptr)
        return retval
    }
    private setShadowOffsetX_serialize(shadowOffsetX: number): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_setShadowOffsetX(this.peer!.ptr, shadowOffsetX)
    }
    private getShadowOffsetY_serialize(): number {
        const retval = ArkUIGeneratedNativeModule._CanvasRenderer_getShadowOffsetY(this.peer!.ptr)
        return retval
    }
    private setShadowOffsetY_serialize(shadowOffsetY: number): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_setShadowOffsetY(this.peer!.ptr, shadowOffsetY)
    }
    private getDirection_serialize(): CanvasDirection {
        const retval = ArkUIGeneratedNativeModule._CanvasRenderer_getDirection(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setDirection_serialize(direction: CanvasDirection): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_setDirection(this.peer!.ptr, direction)
    }
    private getFont_serialize(): string {
        const retval = ArkUIGeneratedNativeModule._CanvasRenderer_getFont(this.peer!.ptr)
        return retval
    }
    private setFont_serialize(font: string): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_setFont(this.peer!.ptr, font)
    }
    private getTextAlign_serialize(): CanvasTextAlign {
        const retval = ArkUIGeneratedNativeModule._CanvasRenderer_getTextAlign(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setTextAlign_serialize(textAlign: CanvasTextAlign): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_setTextAlign(this.peer!.ptr, textAlign)
    }
    private getTextBaseline_serialize(): CanvasTextBaseline {
        const retval = ArkUIGeneratedNativeModule._CanvasRenderer_getTextBaseline(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setTextBaseline_serialize(textBaseline: CanvasTextBaseline): void {
        ArkUIGeneratedNativeModule._CanvasRenderer_setTextBaseline(this.peer!.ptr, textBaseline)
    }
}
