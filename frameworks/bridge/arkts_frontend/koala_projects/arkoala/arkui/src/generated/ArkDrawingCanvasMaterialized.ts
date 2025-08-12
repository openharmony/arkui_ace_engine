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

import { PixelMap, PixelMapInternal } from "./ArkPixelMapMaterialized"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, isInstanceOf } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { isResource, isPadding } from "./../utils"
import { Deserializer, createDeserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ArkUIGeneratedNativeModule } from "./ArkUIGeneratedNativeModule"
export class DrawingCanvasInternal {
    public static fromPtr(ptr: KPointer): DrawingCanvas {
        const obj: DrawingCanvas = new DrawingCanvas(undefined)
        obj.peer = new Finalizable(ptr, DrawingCanvas.getFinalizer())
        return obj
    }
}
export class DrawingCanvas implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_drawingcanvas(pixelmap: PixelMap): KPointer {
        const retval = ArkUIGeneratedNativeModule._DrawingCanvas_ctor(toPeerPtr(pixelmap))
        return retval
    }
     constructor(pixelmap?: PixelMap) {
        if ((pixelmap) !== (undefined))
        {
            const ctorPtr: KPointer = DrawingCanvas.ctor_drawingcanvas((pixelmap)!)
            this.peer = new Finalizable(ctorPtr, DrawingCanvas.getFinalizer())
        }
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._DrawingCanvas_getFinalizer()
    }
    public drawRect(left: number, top: number, right: number, bottom: number): void {
        const left_casted = left as (number)
        const top_casted = top as (number)
        const right_casted = right as (number)
        const bottom_casted = bottom as (number)
        this?.drawRect_serialize(left_casted, top_casted, right_casted, bottom_casted)
        return
    }
    private drawRect_serialize(left: number, top: number, right: number, bottom: number): void {
        ArkUIGeneratedNativeModule._DrawingCanvas_drawRect(this.peer!.ptr, left, top, right, bottom)
    }
}
