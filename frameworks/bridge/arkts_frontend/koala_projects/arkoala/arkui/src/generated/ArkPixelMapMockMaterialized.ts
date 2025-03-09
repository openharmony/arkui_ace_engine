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
export interface PixelMapMock {
    release(): void
}
export class PixelMapMockInternal implements MaterializedBase,PixelMapMock {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_pixelmapmock(): KPointer {
        const retval = ArkUIGeneratedNativeModule._PixelMapMock_ctor()
        return retval
    }
     constructor() {
        const ctorPtr: KPointer = PixelMapMockInternal.ctor_pixelmapmock()
        this.peer = new Finalizable(ctorPtr, PixelMapMockInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._PixelMapMock_getFinalizer()
    }
    public release(): void {
        this?.release_serialize()
        return
    }
    private release_serialize(): void {
        ArkUIGeneratedNativeModule._PixelMapMock_release(this.peer!.ptr)
    }
    public static fromPtr(ptr: KPointer): PixelMapMockInternal {
        const obj: PixelMapMockInternal = new PixelMapMockInternal()
        obj.peer = new Finalizable(ptr, PixelMapMockInternal.getFinalizer())
        return obj
    }
}
