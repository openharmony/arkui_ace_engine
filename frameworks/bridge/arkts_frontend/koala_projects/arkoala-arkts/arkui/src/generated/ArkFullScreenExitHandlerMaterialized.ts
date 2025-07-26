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
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export class FullScreenExitHandlerInternal {
    public static fromPtr(ptr: KPointer): FullScreenExitHandler {
        const obj : FullScreenExitHandler = new FullScreenExitHandler()
        obj.peer = new Finalizable(ptr, FullScreenExitHandler.getFinalizer())
        return obj
    }
}
export class FullScreenExitHandler implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_fullscreenexithandler(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._FullScreenExitHandler_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = FullScreenExitHandler.ctor_fullscreenexithandler()
        this.peer = new Finalizable(ctorPtr, FullScreenExitHandler.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._FullScreenExitHandler_getFinalizer()
    }
    public exitFullScreen(): void {
        this.exitFullScreen_serialize()
        return
    }
    private exitFullScreen_serialize(): void {
        ArkUIGeneratedNativeModule._FullScreenExitHandler_exitFullScreen(this.peer!.ptr)
    }
}
