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

import { LengthMetricsUnit } from "./ArkUnitsInterfaces"
import { ImageBitmap, ImageBitmapInternal } from "./ArkImageBitmapMaterialized"
import { RenderingContextSettings, RenderingContextSettingsInternal } from "./ArkRenderingContextSettingsMaterialized"
import { OffscreenCanvasRenderingContext2D, OffscreenCanvasRenderingContext2DInternal } from "./ArkOffscreenCanvasRenderingContext2DMaterialized"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export class OffscreenCanvasInternal {
    public static fromPtr(ptr: KPointer): OffscreenCanvas {
        const obj : OffscreenCanvas = new OffscreenCanvas(undefined, undefined)
        obj.peer = new Finalizable(ptr, OffscreenCanvas.getFinalizer())
        return obj
    }
}
export class OffscreenCanvas implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get height(): number {
        return this.getHeight()
    }
    set height(height: number) {
        this.setHeight(height)
    }
    get width(): number {
        return this.getWidth()
    }
    set width(width: number) {
        this.setWidth(width)
    }
    static ctor_offscreencanvas(width: number, height: number): KPointer {
        const retval  = ArkUIGeneratedNativeModule._OffscreenCanvas_ctor(width, height)
        return retval
    }
    constructor(width?: number, height?: number) {
        if (((width) !== (undefined)) || ((height) !== (undefined)))
        {
            const ctorPtr : KPointer = OffscreenCanvas.ctor_offscreencanvas((width)!, (height)!)
            this.peer = new Finalizable(ctorPtr, OffscreenCanvas.getFinalizer())
        }
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._OffscreenCanvas_getFinalizer()
    }
    public transferToImageBitmap(): ImageBitmap {
        return this.transferToImageBitmap_serialize()
    }
    public getContext2d(options?: RenderingContextSettings): OffscreenCanvasRenderingContext2D {
        const options_casted = options as (RenderingContextSettings | undefined)
        return this.getContext2d_serialize(options_casted)
    }
    private getHeight(): number {
        return this.getHeight_serialize()
    }
    private setHeight(height: number): void {
        const height_casted = height as (number)
        this.setHeight_serialize(height_casted)
        return
    }
    private getWidth(): number {
        return this.getWidth_serialize()
    }
    private setWidth(width: number): void {
        const width_casted = width as (number)
        this.setWidth_serialize(width_casted)
        return
    }
    getContext(contextType: string, options: RenderingContextSettings): OffscreenCanvasRenderingContext2D {
        throw new Error("TBD")
    }
    private transferToImageBitmap_serialize(): ImageBitmap {
        const retval  = ArkUIGeneratedNativeModule._OffscreenCanvas_transferToImageBitmap(this.peer!.ptr)
        const obj : ImageBitmap = ImageBitmapInternal.fromPtr(retval)
        return obj
    }
    private getContext2d_serialize(options?: RenderingContextSettings): OffscreenCanvasRenderingContext2D {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeRenderingContextSettings(options_value)
        }
        const retval  = ArkUIGeneratedNativeModule._OffscreenCanvas_getContext2d(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : OffscreenCanvasRenderingContext2D = OffscreenCanvasRenderingContext2DInternal.fromPtr(retval)
        return obj
    }
    private getHeight_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._OffscreenCanvas_getHeight(this.peer!.ptr)
        return retval
    }
    private setHeight_serialize(height: number): void {
        ArkUIGeneratedNativeModule._OffscreenCanvas_setHeight(this.peer!.ptr, height)
    }
    private getWidth_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._OffscreenCanvas_getWidth(this.peer!.ptr)
        return retval
    }
    private setWidth_serialize(width: number): void {
        ArkUIGeneratedNativeModule._OffscreenCanvas_setWidth(this.peer!.ptr, width)
    }
}
