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
export class TextTimerControllerInternal {
    public static fromPtr(ptr: KPointer): TextTimerController {
        const obj : TextTimerController = new TextTimerController()
        obj.peer = new Finalizable(ptr, TextTimerController.getFinalizer())
        return obj
    }
}
export class TextTimerController implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_texttimercontroller(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._TextTimerController_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = TextTimerController.ctor_texttimercontroller()
        this.peer = new Finalizable(ctorPtr, TextTimerController.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._TextTimerController_getFinalizer()
    }
    public start(): undefined {
        return this.start_serialize()
    }
    public pause(): undefined {
        return this.pause_serialize()
    }
    public reset(): undefined {
        return this.reset_serialize()
    }
    private start_serialize(): undefined {
        const retval  = ArkUIGeneratedNativeModule._TextTimerController_start(this.peer!.ptr)
        return retval
    }
    private pause_serialize(): undefined {
        const retval  = ArkUIGeneratedNativeModule._TextTimerController_pause(this.peer!.ptr)
        return retval
    }
    private reset_serialize(): undefined {
        const retval  = ArkUIGeneratedNativeModule._TextTimerController_reset(this.peer!.ptr)
        return retval
    }
}
