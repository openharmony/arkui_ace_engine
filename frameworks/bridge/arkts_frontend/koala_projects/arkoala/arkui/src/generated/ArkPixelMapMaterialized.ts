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

import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, isInstanceOf } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { isResource, isPadding } from "./../utils"
import { Deserializer, createDeserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ArkUIGeneratedNativeModule } from "./ArkUIGeneratedNativeModule"
export interface PixelMap {
    readonly isEditable: boolean
    readonly isStrideAlignment: boolean
    readPixelsToBufferSync(dst: ArrayBuffer): void
    writeBufferToPixels(src: ArrayBuffer): void
}
export class PixelMapInternal implements MaterializedBase,PixelMap {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get isEditable(): boolean {
        return this.getIsEditable()
    }
    get isStrideAlignment(): boolean {
        return this.getIsStrideAlignment()
    }
    static ctor_pixelmap(): KPointer {
        const retval = ArkUIGeneratedNativeModule._PixelMap_ctor()
        return retval
    }
     constructor() {
        const ctorPtr: KPointer = PixelMapInternal.ctor_pixelmap()
        this.peer = new Finalizable(ctorPtr, PixelMapInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._PixelMap_getFinalizer()
    }
    public readPixelsToBufferSync(dst: ArrayBuffer): void {
        const dst_casted = dst as (ArrayBuffer)
        this?.readPixelsToBufferSync_serialize(dst_casted)
        return
    }
    public writeBufferToPixels(src: ArrayBuffer): void {
        const src_casted = src as (ArrayBuffer)
        this?.writeBufferToPixels_serialize(src_casted)
        return
    }
    private getIsEditable(): boolean {
        return this.getIsEditable_serialize()
    }
    private getIsStrideAlignment(): boolean {
        return this.getIsStrideAlignment_serialize()
    }
    private readPixelsToBufferSync_serialize(dst: ArrayBuffer): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeBuffer(dst)
        ArkUIGeneratedNativeModule._PixelMap_readPixelsToBufferSync(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    private writeBufferToPixels_serialize(src: ArrayBuffer): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeBuffer(src)
        ArkUIGeneratedNativeModule._PixelMap_writeBufferToPixels(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    private getIsEditable_serialize(): boolean {
        const retval = ArkUIGeneratedNativeModule._PixelMap_getIsEditable(this.peer!.ptr)
        return retval
    }
    private getIsStrideAlignment_serialize(): boolean {
        const retval = ArkUIGeneratedNativeModule._PixelMap_getIsStrideAlignment(this.peer!.ptr)
        return retval
    }
    public static fromPtr(ptr: KPointer): PixelMapInternal {
        const obj: PixelMapInternal = new PixelMapInternal()
        obj.peer = new Finalizable(ptr, PixelMapInternal.getFinalizer())
        return obj
    }
}
