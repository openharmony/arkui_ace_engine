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

import { CanvasRenderer, CanvasRendererInternal } from "./ArkCanvasRendererMaterialized"
import { CanvasPath, CanvasPathInternal } from "./ArkCanvasPathMaterialized"
import { CanvasGradient, CanvasGradientInternal } from "./ArkCanvasGradientMaterialized"
import { CanvasPattern, CanvasPatternInternal } from "./ArkCanvasPatternMaterialized"
import { ImageSmoothingQuality, CanvasLineCap, CanvasLineJoin, CanvasDirection, CanvasTextAlign, CanvasTextBaseline, CanvasFillRule, TextMetrics } from "./ArkCanvasInterfaces"
import { ImageBitmap, ImageBitmapInternal } from "./ArkImageBitmapMaterialized"
import { PixelMap, PixelMapInternal } from "./ArkPixelMapMaterialized"
import { Path2D, Path2DInternal } from "./ArkPath2DMaterialized"
import { ImageData, ImageDataInternal } from "./ArkImageDataMaterialized"
import { Matrix2D, Matrix2DInternal } from "./ArkMatrix2DMaterialized"
import { FrameNode, FrameNodeInternal } from "./ArkFrameNodeMaterialized"
import { RenderingContextSettings, RenderingContextSettingsInternal } from "./ArkRenderingContextSettingsMaterialized"
import { LengthMetricsUnit, Position, Length } from "./ArkUnitsInterfaces"
import { ImageAnalyzerConfig, ImageAnalyzerType } from "./ArkImageCommonInterfaces"
import { UIContext } from "./ArkCommonInterfaces"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, isInstanceOf } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { isResource, isPadding } from "./../utils"
import { Deserializer, createDeserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ArkUIGeneratedNativeModule } from "./ArkUIGeneratedNativeModule"
export class CanvasRenderingContext2DInternal {
    public static fromPtr(ptr: KPointer): CanvasRenderingContext2D {
        const obj: CanvasRenderingContext2D = new CanvasRenderingContext2D(undefined)
        obj.peer = new Finalizable(ptr, CanvasRenderingContext2D.getFinalizer())
        return obj
    }
}
export class CanvasRenderingContext2D extends CanvasRenderer implements MaterializedBase {
    get height(): number {
        return this.getHeight()
    }
    get width(): number {
        return this.getWidth()
    }
    get canvas(): FrameNode {
        return this.getCanvas()
    }
    static ctor_canvasrenderingcontext2d(settings?: RenderingContextSettings): KPointer {
        const thisSerializer: Serializer = Serializer.hold()
        let settings_type: int32 = RuntimeType.UNDEFINED
        settings_type = runtimeType(settings)
        thisSerializer.writeInt8(settings_type)
        if ((RuntimeType.UNDEFINED) != (settings_type)) {
            const settings_value = settings!
            thisSerializer.writeRenderingContextSettings(settings_value)
        }
        const retval = ArkUIGeneratedNativeModule._CanvasRenderingContext2D_ctor(thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
     constructor(settings?: RenderingContextSettings) {
        super()
        const ctorPtr: KPointer = CanvasRenderingContext2D.ctor_canvasrenderingcontext2d((settings)!)
        this.peer = new Finalizable(ctorPtr, CanvasRenderingContext2D.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._CanvasRenderingContext2D_getFinalizer()
    }
    public toDataURL(type?: string, quality?: float32): string {
        const type_casted = type as (string | undefined)
        const quality_casted = quality as (float32 | undefined)
        return this.toDataURL_serialize(type_casted, quality_casted)
    }
    public startImageAnalyzer(config: ImageAnalyzerConfig): Promise<void> {
        const config_casted = config as (ImageAnalyzerConfig)
        return this.startImageAnalyzer_serialize(config_casted)
    }
    public stopImageAnalyzer(): void {
        this?.stopImageAnalyzer_serialize()
        return
    }
    public onOnAttach(callback_: (() => void)): void {
        const callback__casted = callback_ as ((() => void))
        this?.onOnAttach_serialize(callback__casted)
        return
    }
    public offOnAttach(callback_?: (() => void)): void {
        const callback__casted = callback_ as ((() => void) | undefined)
        this?.offOnAttach_serialize(callback__casted)
        return
    }
    public onOnDetach(callback_: (() => void)): void {
        const callback__casted = callback_ as ((() => void))
        this?.onOnDetach_serialize(callback__casted)
        return
    }
    public offOnDetach(callback_?: (() => void)): void {
        const callback__casted = callback_ as ((() => void) | undefined)
        this?.offOnDetach_serialize(callback__casted)
        return
    }
    private getHeight(): number {
        return this.getHeight_serialize()
    }
    private getWidth(): number {
        return this.getWidth_serialize()
    }
    private getCanvas(): FrameNode {
        return this.getCanvas_serialize()
    }
    on(type: string, callback_: (() => void)): void {
        throw new Error("TBD")
    }
    off(type: string, callback_: (() => void)): void {
        throw new Error("TBD")
    }
    private toDataURL_serialize(type?: string, quality?: float32): string {
        const thisSerializer: Serializer = Serializer.hold()
        let type_type: int32 = RuntimeType.UNDEFINED
        type_type = runtimeType(type)
        thisSerializer.writeInt8(type_type)
        if ((RuntimeType.UNDEFINED) != (type_type)) {
            const type_value = type!
            thisSerializer.writeString(type_value)
        }
        let quality_type: int32 = RuntimeType.UNDEFINED
        quality_type = runtimeType(quality)
        thisSerializer.writeInt8(quality_type)
        if ((RuntimeType.UNDEFINED) != (quality_type)) {
            const quality_value = quality!
            thisSerializer.writeFloat32(quality_value)
        }
        const retval = ArkUIGeneratedNativeModule._CanvasRenderingContext2D_toDataURL(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private startImageAnalyzer_serialize(config: ImageAnalyzerConfig): Promise<void> {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeImageAnalyzerConfig(config)
        const retval = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._CanvasRenderingContext2D_startImageAnalyzer(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private stopImageAnalyzer_serialize(): void {
        ArkUIGeneratedNativeModule._CanvasRenderingContext2D_stopImageAnalyzer(this.peer!.ptr)
    }
    private onOnAttach_serialize(callback_: (() => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(callback_)
        ArkUIGeneratedNativeModule._CanvasRenderingContext2D_onOnAttach(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    private offOnAttach_serialize(callback_?: (() => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        let callback__type: int32 = RuntimeType.UNDEFINED
        callback__type = runtimeType(callback_)
        thisSerializer.writeInt8(callback__type)
        if ((RuntimeType.UNDEFINED) != (callback__type)) {
            const callback__value = callback_!
            thisSerializer.holdAndWriteCallback(callback__value)
        }
        ArkUIGeneratedNativeModule._CanvasRenderingContext2D_offOnAttach(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    private onOnDetach_serialize(callback_: (() => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(callback_)
        ArkUIGeneratedNativeModule._CanvasRenderingContext2D_onOnDetach(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    private offOnDetach_serialize(callback_?: (() => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        let callback__type: int32 = RuntimeType.UNDEFINED
        callback__type = runtimeType(callback_)
        thisSerializer.writeInt8(callback__type)
        if ((RuntimeType.UNDEFINED) != (callback__type)) {
            const callback__value = callback_!
            thisSerializer.holdAndWriteCallback(callback__value)
        }
        ArkUIGeneratedNativeModule._CanvasRenderingContext2D_offOnDetach(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    private getHeight_serialize(): number {
        const retval = ArkUIGeneratedNativeModule._CanvasRenderingContext2D_getHeight(this.peer!.ptr)
        return retval
    }
    private getWidth_serialize(): number {
        const retval = ArkUIGeneratedNativeModule._CanvasRenderingContext2D_getWidth(this.peer!.ptr)
        return retval
    }
    private getCanvas_serialize(): FrameNode {
        const retval = ArkUIGeneratedNativeModule._CanvasRenderingContext2D_getCanvas(this.peer!.ptr)
        const obj: FrameNode = FrameNodeInternal.fromPtr(retval)
        return obj
    }
}
