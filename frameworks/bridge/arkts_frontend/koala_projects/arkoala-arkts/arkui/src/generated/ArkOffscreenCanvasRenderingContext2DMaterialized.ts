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
import { RenderingContextSettings, RenderingContextSettingsInternal } from "./ArkRenderingContextSettingsMaterialized"
import { LengthMetricsUnit } from "./ArkUnitsInterfaces"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export class OffscreenCanvasRenderingContext2DInternal {
    public static fromPtr(ptr: KPointer): OffscreenCanvasRenderingContext2D {
        const obj : OffscreenCanvasRenderingContext2D = new OffscreenCanvasRenderingContext2D(undefined, undefined, undefined)
        obj.peer = new Finalizable(ptr, OffscreenCanvasRenderingContext2D.getFinalizer())
        return obj
    }
}
export class OffscreenCanvasRenderingContext2D extends CanvasRenderer implements MaterializedBase {
    static ctor_offscreencanvasrenderingcontext2d(width: number, height: number, settings?: RenderingContextSettings): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        let settings_type : int32 = RuntimeType.UNDEFINED
        settings_type = runtimeType(settings)
        thisSerializer.writeInt8(settings_type as int32)
        if ((RuntimeType.UNDEFINED) != (settings_type)) {
            const settings_value  = settings!
            thisSerializer.writeRenderingContextSettings(settings_value)
        }
        const retval  = ArkUIGeneratedNativeModule._OffscreenCanvasRenderingContext2D_ctor(width, height, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    constructor(width?: number, height?: number, settings?: RenderingContextSettings) {
        super()
        if (((width) !== (undefined)) || ((height) !== (undefined)) || ((settings) !== (undefined)))
        {
            const ctorPtr : KPointer = OffscreenCanvasRenderingContext2D.ctor_offscreencanvasrenderingcontext2d((width)!, (height)!, (settings)!)
            this.peer = new Finalizable(ctorPtr, OffscreenCanvasRenderingContext2D.getFinalizer())
        }
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._OffscreenCanvasRenderingContext2D_getFinalizer()
    }
    public toDataURL(type?: string, quality?: float32): string {
        const type_casted = type as (string | undefined)
        const quality_casted = quality as (float32 | undefined)
        return this.toDataURL_serialize(type_casted, quality_casted)
    }
    public transferToImageBitmap(): ImageBitmap {
        return this.transferToImageBitmap_serialize()
    }
    private toDataURL_serialize(type?: string, quality?: float32): string {
        const thisSerializer : Serializer = Serializer.hold()
        let type_type : int32 = RuntimeType.UNDEFINED
        type_type = runtimeType(type)
        thisSerializer.writeInt8(type_type as int32)
        if ((RuntimeType.UNDEFINED) != (type_type)) {
            const type_value  = type!
            thisSerializer.writeString(type_value)
        }
        let quality_type : int32 = RuntimeType.UNDEFINED
        quality_type = runtimeType(quality)
        thisSerializer.writeInt8(quality_type as int32)
        if ((RuntimeType.UNDEFINED) != (quality_type)) {
            const quality_value  = quality!
            thisSerializer.writeFloat32(quality_value)
        }
        const retval  = ArkUIGeneratedNativeModule._OffscreenCanvasRenderingContext2D_toDataURL(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private transferToImageBitmap_serialize(): ImageBitmap {
        const retval  = ArkUIGeneratedNativeModule._OffscreenCanvasRenderingContext2D_transferToImageBitmap(this.peer!.ptr)
        const obj : ImageBitmap = ImageBitmapInternal.fromPtr(retval)
        return obj
    }
}
