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
