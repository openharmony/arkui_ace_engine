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

import { SerializerBase, DeserializerBase, CallbackResource, InteropNativeModule, MaterializedBase, Tags, RuntimeType, runtimeType, toPeerPtr, nullptr, KPointer, NativeBuffer, KSerializerBuffer, KUint8ArrayPtr, Finalizable, registerCallback, wrapCallback, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { CallbackKind } from "./peers/CallbackKind"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
export class image_PixelMap_serializer {
    public static write(buffer: SerializerBase, value: image.PixelMap): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): image.PixelMap {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return image.PixelMapInternal.fromPtr(ptr)
    }
}
export namespace image {
    export interface PixelMap {
        isEditable: boolean
        isStrideAlignment: boolean
        readPixelsToBufferSync(dst: NativeBuffer): void
        writeBufferToPixels(src: NativeBuffer): void
    }
    export class PixelMapInternal implements MaterializedBase,image.PixelMap {
        peer?: Finalizable | undefined = undefined
        public getPeer(): Finalizable | undefined {
            return this.peer
        }
        isEditable: boolean
        isStrideAlignment: boolean
        constructor(peerPtr: KPointer) {
            this.peer = new Finalizable(peerPtr, PixelMapInternal.getFinalizer())
            this.isEditable = this.getIsEditable()
            this.isStrideAlignment = this.getIsStrideAlignment()
        }
        constructor() {
            this(PixelMapInternal.construct())
        }
        static construct(): KPointer {
            const retval  = ArkUIGeneratedNativeModule._image_PixelMap_construct()
            return retval
        }
        static getFinalizer(): KPointer {
            return ArkUIGeneratedNativeModule._image_PixelMap_getFinalizer()
        }
        public static fromPtr(ptr: KPointer): PixelMapInternal {
            return new PixelMapInternal(ptr)
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
            const thisSerializer : SerializerBase = SerializerBase.hold()
            thisSerializer.writeBuffer(dst)
            ArkUIGeneratedNativeModule._image_PixelMap_readPixelsToBufferSync(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
            thisSerializer.release()
        }
        private writeBufferToPixels_serialize(src: NativeBuffer): void {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            thisSerializer.writeBuffer(src)
            ArkUIGeneratedNativeModule._image_PixelMap_writeBufferToPixels(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
            thisSerializer.release()
        }
        private getIsEditable_serialize(): boolean {
            const retval  = ArkUIGeneratedNativeModule._image_PixelMap_getIsEditable(this.peer!.ptr)
            return retval
        }
        private getIsStrideAlignment_serialize(): boolean {
            const retval  = ArkUIGeneratedNativeModule._image_PixelMap_getIsStrideAlignment(this.peer!.ptr)
            return retval
        }
    }
    export enum ResolutionQuality {
        LOW = 1,
        MEDIUM = 2,
        HIGH = 3
    }
}
