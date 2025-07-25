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
import { PixelMap, PixelMapInternal } from "./ArkPixelMapMaterialized"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export class ImageBitmapInternal {
    public static fromPtr(ptr: KPointer): ImageBitmap {
        const obj : ImageBitmap = new ImageBitmap(undefined)
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
    static ctor_imagebitmap(src: string): KPointer {
        const retval  = ArkUIGeneratedNativeModule._ImageBitmap_ctor(src)
        return retval
    }
    constructor(src?: string) {
        if ((src) !== (undefined))
        {
            const ctorPtr : KPointer = ImageBitmap.ctor_imagebitmap((src)!)
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
        const retval  = ArkUIGeneratedNativeModule._ImageBitmap_getHeight(this.peer!.ptr)
        return retval
    }
    private getWidth_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._ImageBitmap_getWidth(this.peer!.ptr)
        return retval
    }
}
