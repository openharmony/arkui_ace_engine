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

import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export interface PixelMap {
    readonly isEditable: boolean
    readonly isStrideAlignment: boolean
    readPixelsToBufferSync(dst: NativeBuffer): void
    writeBufferToPixels(src: NativeBuffer): void
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
        const retval  = ArkUIGeneratedNativeModule._PixelMap_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = PixelMapInternal.ctor_pixelmap()
        this.peer = new Finalizable(ctorPtr, PixelMapInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._PixelMap_getFinalizer()
    }
    public readPixelsToBufferSync(dst: NativeBuffer): void {
        const dst_casted = dst as (NativeBuffer)
        this.readPixelsToBufferSync_serialize(dst_casted)
        return
    }
    public writeBufferToPixels(src: NativeBuffer): void {
        const src_casted = src as (NativeBuffer)
        this.writeBufferToPixels_serialize(src_casted)
        return
    }
    private getIsEditable(): boolean {
        return this.getIsEditable_serialize()
    }
    private getIsStrideAlignment(): boolean {
        return this.getIsStrideAlignment_serialize()
    }
    private readPixelsToBufferSync_serialize(dst: NativeBuffer): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeBuffer(dst)
        ArkUIGeneratedNativeModule._PixelMap_readPixelsToBufferSync(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private writeBufferToPixels_serialize(src: NativeBuffer): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeBuffer(src)
        ArkUIGeneratedNativeModule._PixelMap_writeBufferToPixels(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getIsEditable_serialize(): boolean {
        const retval  = ArkUIGeneratedNativeModule._PixelMap_getIsEditable(this.peer!.ptr)
        return retval
    }
    private getIsStrideAlignment_serialize(): boolean {
        const retval  = ArkUIGeneratedNativeModule._PixelMap_getIsStrideAlignment(this.peer!.ptr)
        return retval
    }
    public static fromPtr(ptr: KPointer): PixelMapInternal {
        const obj : PixelMapInternal = new PixelMapInternal()
        obj.peer = new Finalizable(ptr, PixelMapInternal.getFinalizer())
        return obj
    }
}
