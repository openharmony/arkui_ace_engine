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

import { PatternLockChallengeResult } from "./ArkPatternLockInterfaces"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, isInstanceOf } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { isResource, isPadding } from "./../utils"
import { Deserializer, createDeserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ArkUIGeneratedNativeModule } from "./ArkUIGeneratedNativeModule"
export class PatternLockControllerInternal {
    public static fromPtr(ptr: KPointer): PatternLockController {
        const obj: PatternLockController = new PatternLockController()
        obj.peer = new Finalizable(ptr, PatternLockController.getFinalizer())
        return obj
    }
}
export class PatternLockController implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_patternlockcontroller(): KPointer {
        const retval = ArkUIGeneratedNativeModule._PatternLockController_ctor()
        return retval
    }
     constructor() {
        const ctorPtr: KPointer = PatternLockController.ctor_patternlockcontroller()
        this.peer = new Finalizable(ctorPtr, PatternLockController.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._PatternLockController_getFinalizer()
    }
    public reset(): undefined {
        return this.reset_serialize()
    }
    public setChallengeResult(result: PatternLockChallengeResult): void {
        const result_casted = result as (PatternLockChallengeResult)
        this?.setChallengeResult_serialize(result_casted)
        return
    }
    private reset_serialize(): undefined {
        const retval = ArkUIGeneratedNativeModule._PatternLockController_reset(this.peer!.ptr)
        return retval
    }
    private setChallengeResult_serialize(result: PatternLockChallengeResult): void {
        ArkUIGeneratedNativeModule._PatternLockController_setChallengeResult(this.peer!.ptr, result)
    }
}
