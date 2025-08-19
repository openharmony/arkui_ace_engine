/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
// HANDWRITTEN, DO NOT REGENERATE

import { int32 } from "@koalaui/compat"
import { UIContext } from "@ohos/arkui/UIContext"
import { UIContextImpl } from "../handwritten/UIContextImpl";
import { UIContextUtil } from "../handwritten/UIContextUtil"

const DIFF: number = 1e-10
const INT32_MAX: number = 2147483647
const PIXEL_SIZE: number = 4
export function getCanvasDensity(peerPtr: CanvasRenderer): number {
    return ArkUIAniModule._CanvasRenderer_GetCanvasDensity(peerPtr.peer!.ptr)
}
export function getSystemDensity(): number {
    return ArkUIAniModule._GetSystemDensity()
}
export function convertDimensionStrToNumber(value: string): number {
    const regex : RegExp = new RegExp('/^(-?\d*\.?\d+)(px|vp)?$/', 'i')
    const match: RegExpMatchArray | null = value.match(regex)
    if (!match) {
        return 0
    }
    let numericValue : number = 0
    let unitPart : string = ''
    if (match.length > 1) {
        numericValue = parseFloat(match[1]!);
    }
    if (match.length > 2) {
        unitPart = match[2]!;
    }
    if (unitPart === 'px' || !unitPart) {
        return numericValue;
    }
    if (unitPart === 'vp') {
        return numericValue * getSystemDensity();
    }
    return 0;
}
export function hookCreateImageData(peerPtr: CanvasRenderer, sw: number, sh: number): ImageData {
    const density = getCanvasDensity(peerPtr)
    const width_value: number = sw * density + DIFF
    const height_value: number = sh * density + DIFF
    if ((width_value > INT32_MAX) || (height_value > INT32_MAX) ||
        ((width_value > 0) && (height_value > (INT32_MAX / width_value / PIXEL_SIZE)))) {
        const resObj = new ImageData(0, 0)
        return resObj
    }
    const width_cast: int32 = width_value as int32
    const height_cast: int32 = height_value as int32
    const length: int32 = width_cast * height_cast * PIXEL_SIZE
    const arrayBuffer: ArrayBuffer = new ArrayBuffer(length)
    const uint8View = new Uint8Array(arrayBuffer)
    uint8View.fill(0xffffffff)
    const data: Uint8ClampedArray = new Uint8ClampedArray(arrayBuffer)
    const resObj: ImageData = new ImageData(width_cast, height_cast, data, LengthMetricsUnit.PX)
    return resObj
}
export function hookCreateImageData(peerPtr: CanvasRenderer, imagedata: ImageData): ImageData {
    const width_cast: int32 = imagedata.width as int32
    const height_cast: int32 = imagedata.height as int32
    const length: int32 = width_cast * height_cast * PIXEL_SIZE
    const arrayBuffer: ArrayBuffer = new ArrayBuffer(length)
    const uint8View = new Uint8Array(arrayBuffer)
    uint8View.fill(0xffffffff)
    const data: Uint8ClampedArray = new Uint8ClampedArray(arrayBuffer)
    const resObj: ImageData = new ImageData(width_cast, height_cast, data, LengthMetricsUnit.PX)
    return resObj
}
export function hookGetImageData(peerPtr: CanvasRenderer, sx: number, sy: number, sw: number, sh: number): ImageData {
    const data: Uint8ClampedArray = ArkUIAniModule._CanvasRenderer_GetImageData(peerPtr.peer!.ptr, sx, sy, sw, sh)
    const density = getCanvasDensity(peerPtr)
    const width_value: number = sw * density + DIFF
    const height_value: number = sh * density + DIFF
    if ((!data) || (width_value > INT32_MAX) || (height_value > INT32_MAX) ||
        ((width_value > 0) && (height_value > (INT32_MAX / width_value / PIXEL_SIZE)))) {
        const resObj = new ImageData(0, 0)
        return resObj
    }
    const width_cast: int32 = width_value as int32
    const height_cast: int32 = height_value as int32
    const resObj: ImageData = new ImageData(width_cast, height_cast, data, LengthMetricsUnit.PX)
    return resObj
}
export function hookPutImageData(peerPtr: CanvasRenderer, imagedata: ImageData, dx: number | string, dy: number | string): void {
    let dx_type: int32 = RuntimeType.UNDEFINED
    let dy_type: int32 = RuntimeType.UNDEFINED
    dx_type = runtimeType(dx)
    dy_type = runtimeType(dy)
    let dx_val: number = (dx_type == RuntimeType.STRING) ? convertDimensionStrToNumber(dx as string) : (dx as number)
    let dy_val: number = (dy_type == RuntimeType.STRING) ? convertDimensionStrToNumber(dy as string) : (dy as number)
    ArkUIAniModule._CanvasRenderer_PutImageData0(peerPtr.peer!.ptr, imagedata.data, dx_val, dy_val, imagedata.width as int32, imagedata.height as int32)
}
export function hookPutImageData(peerPtr: CanvasRenderer, imagedata: ImageData, dx: number | string, dy: number | string, dirtyX: number | string, dirtyY: number | string, dirtyWidth: number | string, dirtyHeight: number | string): void {

    let dx_type: int32 = RuntimeType.UNDEFINED
    let dy_type: int32 = RuntimeType.UNDEFINED
    let dirtyX_type: int32 = RuntimeType.UNDEFINED
    let dirtyY_type: int32 = RuntimeType.UNDEFINED
    let dirtyWidth_type: int32 = RuntimeType.UNDEFINED
    let dirtyHeight_type: int32 = RuntimeType.UNDEFINED
    dx_type = runtimeType(dx)
    dy_type = runtimeType(dy)
    dirtyX_type = runtimeType(dirtyX)
    dirtyY_type = runtimeType(dirtyY)
    dirtyWidth_type = runtimeType(dirtyWidth)
    dirtyHeight_type = runtimeType(dirtyHeight)
    let dx_val: number = (dx_type == RuntimeType.STRING) ? convertDimensionStrToNumber(dx as string) : (dx as number)
    let dy_val: number = (dy_type == RuntimeType.STRING) ? convertDimensionStrToNumber(dy as string) : (dy as number)
    let dirtyX_val: number = (dirtyX_type == RuntimeType.STRING) ? convertDimensionStrToNumber(dirtyX as string) : (dirtyX as number)
    let dirtyY_val: number = (dirtyY_type == RuntimeType.STRING) ? convertDimensionStrToNumber(dirtyY as string) : (dirtyY as number)
    let dirtyWidth_val: number = (dirtyWidth_type == RuntimeType.STRING) ? convertDimensionStrToNumber(dirtyWidth as string) : (dirtyWidth as number)
    let dirtyHeight_val: number = (dirtyHeight_type == RuntimeType.STRING) ? convertDimensionStrToNumber(dirtyHeight as string) : (dirtyHeight as number)
    ArkUIAniModule._CanvasRenderer_PutImageData1(peerPtr.peer!.ptr, imagedata.data, dx_val, dy_val, imagedata.width as int32, imagedata.height as int32, dirtyX_val, dirtyY_val, dirtyWidth_val, dirtyHeight_val)
}
export function hookSetPixelMap(peerPtr: CanvasRenderer, pixelMap?: PixelMap): void {
    let pixelMap_type: int32 = RuntimeType.UNDEFINED
    pixelMap_type = runtimeType(pixelMap)
    if ((RuntimeType.UNDEFINED) !== pixelMap_type) {
        const pixelMap_cast = pixelMap as PixelMap
        ArkUIAniModule._CanvasRenderer_SetPixelMap(peerPtr.peer!.ptr, pixelMap_cast)
    }
}
export function hookGetPixelMap(peerPtr: CanvasRenderer, sx: number, sy: number, sw: number, sh: number): PixelMap {
    const obj: PixelMap = ArkUIAniModule._CanvasRenderer_GetPixelMap(peerPtr.peer!.ptr, sx, sy, sw, sh)
    return obj
}
export function hookDrawImage(peerPtr: CanvasRenderer, image: ImageBitmap | PixelMap, dx: number, dy: number): void {
    let image_type: int32 = RuntimeType.UNDEFINED
    image_type = runtimeType(image)
    if (TypeChecker.isImageBitmap(image, false, false)) {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeInt8(0 as int32)
        const image_0 = image as ImageBitmap
        thisSerializer.writeImageBitmap(image_0)
        ArkUIGeneratedNativeModule._CanvasRenderer_drawImage0(peerPtr.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length(), dx, dy)
        thisSerializer.release()
    }
    else if ((RuntimeType.UNDEFINED) != (image_type)) {
        const pixelMap = image as PixelMap
        ArkUIAniModule._CanvasRenderer_DrawPixelMap0(peerPtr.peer!.ptr, pixelMap, dx, dy)
    }
}
export function hookDrawImage(peerPtr: CanvasRenderer, image: ImageBitmap | PixelMap, dx: number, dy: number, dw: number, dh: number): void {
    let image_type: int32 = RuntimeType.UNDEFINED
    image_type = runtimeType(image)
    if (TypeChecker.isImageBitmap(image, false, false)) {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeInt8(0 as int32)
        const image_0 = image as ImageBitmap
        thisSerializer.writeImageBitmap(image_0)
        ArkUIGeneratedNativeModule._CanvasRenderer_drawImage1(peerPtr.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length(), dx, dy, dw, dh)
        thisSerializer.release()
    }
    else if ((RuntimeType.UNDEFINED) != (image_type)) {
        const pixelMap = image as PixelMap
        ArkUIAniModule._CanvasRenderer_DrawPixelMap1(peerPtr.peer!.ptr, pixelMap, dx, dy, dw, dh)
    }
}
export function hookDrawImage(peerPtr: CanvasRenderer, image: ImageBitmap | PixelMap, sx: number, sy: number, sw: number, sh: number, dx: number, dy: number, dw: number, dh: number): void {
    let image_type: int32 = RuntimeType.UNDEFINED
    image_type = runtimeType(image)
    if (TypeChecker.isImageBitmap(image, false, false)) {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeInt8(0 as int32)
        const image_0 = image as ImageBitmap
        thisSerializer.writeImageBitmap(image_0)
        ArkUIGeneratedNativeModule._CanvasRenderer_drawImage2(peerPtr.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length(), sx, sy, sw, sh, dx, dy, dw, dh)
        thisSerializer.release()
    }
    else if ((RuntimeType.UNDEFINED) != (image_type)) {
        const pixelMap = image as PixelMap
        ArkUIAniModule._CanvasRenderer_DrawPixelMap2(peerPtr.peer!.ptr, pixelMap, sx, sy, sw, sh, dx, dy, dw, dh)
    }
}
export function hookGetContext(peerPtr: OffscreenCanvas, contextType: string, options?: RenderingContextSettings): OffscreenCanvasRenderingContext2D {
    return peerPtr.getContext2d(options)
}
export function hookGetCanvas(peerPtr: DrawingRenderingContext): drawing.Canvas{
    return ArkUIAniModule._DrawingRenderingContext_GetCanvas(peerPtr.peer!.ptr)
}
export function hookGetCanvas(peerPtr: CanvasRenderingContext2D): FrameNode {
    const context: UIContextImpl = UIContextUtil.getOrCreateCurrentUIContext() as UIContextImpl
    const nodeId: number = ArkUIAniModule._CanvasRenderingContext_GetCanvasId(peerPtr.peer!.ptr) as number
    return context.getFrameNodeByNodeId(nodeId) as FrameNode
}
export function hookOn(peerPtr: CanvasRenderingContext2D, type: string, callback_: Callback<void>): void {
    if (type == "onAttach") {
        peerPtr.onOnAttach(callback_)
    } else if (type == "onDetach") {
        peerPtr.onOnDetach(callback_)
    }
}
export function hookOff(peerPtr: CanvasRenderingContext2D, type: string, callback_?: Callback<void>): void {
    if (type == "offAttach") {
        peerPtr.offOnAttach(callback_)
    } else if (type == "offDetach") {
        peerPtr.offOnDetach(callback_)
    }
}
export class ImageBitmapInternal {
    public static fromPtr(ptr: KPointer): ImageBitmap {
        const obj: ImageBitmap = new ImageBitmap(undefined, undefined)
        obj.peer = new Finalizable(ptr, ImageBitmap.getFinalizer())
        return obj
    }
}
export class ImageBitmap implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get height(): number {
        return this.getHeight()
    }
    get width(): number {
        return this.getWidth()
    }
    static ctor_imagebitmap(src: PixelMap | string, unit?: LengthMetricsUnit): KPointer {
        let src_type: int32 = RuntimeType.UNDEFINED
        src_type = runtimeType(src)
        let unit_type: int32 = RuntimeType.UNDEFINED
        unit_type = runtimeType(unit) 
        if ((RuntimeType.STRING) == (src_type)) {
            const str = src as string
            if ((RuntimeType.UNDEFINED) != (unit_type)) {
                const unit_cast = unit as LengthMetricsUnit
                return ArkUIAniModule._ImageBitmap_Construct0(str, unit_cast)
            } else {
                return ArkUIAniModule._ImageBitmap_Construct0(str, 0)
            }
        } else {
            const pixelMap = src as PixelMap
            if ((RuntimeType.UNDEFINED) != (unit_type)) {
                const unit_cast = unit as LengthMetricsUnit
                return ArkUIAniModule._ImageBitmap_Construct1(pixelMap, unit_cast)
            } else {
                return ArkUIAniModule._ImageBitmap_Construct1(pixelMap, 0)
            }
        }
    }
    constructor(src?: PixelMap | string, unit?: LengthMetricsUnit) {
        if ((src) != (undefined)) {
            const ctorPtr: KPointer = ImageBitmap.ctor_imagebitmap((src)!, unit)
            this.peer = new Finalizable(ctorPtr, ImageBitmap.getFinalizer())
        }
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._ImageBitmap_getFinalizer()
    }
    public close(): void {
        this.close_serialize()
        return
    }
    private getHeight(): number {
        return this.getHeight_serialize()
    }
    private getWidth(): number {
        return this.getWidth_serialize()
    }
    private close_serialize(): void {
        ArkUIGeneratedNativeModule._ImageBitmap_close(this.peer!.ptr)
    }
    private getHeight_serialize(): number {
        const retval = ArkUIGeneratedNativeModule._ImageBitmap_getHeight(this.peer!.ptr)
        return retval
    }
    private getWidth_serialize(): number {
        const retval = ArkUIGeneratedNativeModule._ImageBitmap_getWidth(this.peer!.ptr)
        return retval
    }
}
export class ImageData {
    private data_val: Uint8ClampedArray = new Uint8ClampedArray()
    private finalWidth: int32 = 0
    private finalHeight: int32 = 0
    private unit_val: LengthMetricsUnit = LengthMetricsUnit.DEFAULT

    get data(): Uint8ClampedArray {
        return this.data_val
    }
    get height(): int32 {
        return this.finalHeight
    }
    get width(): int32 {
        return this.finalWidth
    }
    constructor(width: number, height: number, data?: Uint8ClampedArray, unit?: LengthMetricsUnit) {
        if (width == undefined || height == undefined) {
            return
        }
        if (width < 0.0 || height < 0.0) {
            return
        }
        if (unit != undefined) {
            this.unit_val = unit
        }
        const density = this.GetDensity()
        let width_value: number = width * density + DIFF
        let height_value: number = height * density + DIFF
        if ((width_value > INT32_MAX) || (height_value > INT32_MAX) ||
            ((width_value > 0) && (height_value > (INT32_MAX / width_value / PIXEL_SIZE)))) {
            return
        }
        this.finalWidth = width_value as int32
        this.finalHeight = height_value as int32
        const length: int32 = this.finalWidth * this.finalHeight * PIXEL_SIZE
        if (data == undefined) {
            this.data_val = new Uint8ClampedArray(length)
        } else {
            if (this.unit_val == LengthMetricsUnit.PX && data.length != length) {
                return
            }
            this.data_val = data
        }
    }
    private GetDensity(): number {
        const density = getSystemDensity()
        if ((this.unit_val == LengthMetricsUnit.DEFAULT) && density !== 0.0) {
            return density
        } else {
            return 1.0
        }
    }
}
