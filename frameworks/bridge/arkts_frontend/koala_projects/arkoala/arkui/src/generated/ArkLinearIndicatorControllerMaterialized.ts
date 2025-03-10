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

import { LinearIndicatorStartOptions } from "./ArkLinearindicatorInterfaces"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, isInstanceOf } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { isResource, isPadding } from "./../utils"
import { Deserializer, createDeserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ArkUIGeneratedNativeModule } from "./ArkUIGeneratedNativeModule"
export class LinearIndicatorControllerInternal {
    public static fromPtr(ptr: KPointer): LinearIndicatorController {
        const obj: LinearIndicatorController = new LinearIndicatorController()
        obj.peer = new Finalizable(ptr, LinearIndicatorController.getFinalizer())
        return obj
    }
}
export class LinearIndicatorController implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_linearindicatorcontroller(): KPointer {
        const retval = ArkUIGeneratedNativeModule._LinearIndicatorController_ctor()
        return retval
    }
     constructor() {
        const ctorPtr: KPointer = LinearIndicatorController.ctor_linearindicatorcontroller()
        this.peer = new Finalizable(ctorPtr, LinearIndicatorController.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._LinearIndicatorController_getFinalizer()
    }
    public setProgress(index: number, progress: number): void {
        const index_casted = index as (number)
        const progress_casted = progress as (number)
        this?.setProgress_serialize(index_casted, progress_casted)
        return
    }
    public start(options?: LinearIndicatorStartOptions): void {
        const options_casted = options as (LinearIndicatorStartOptions | undefined)
        this?.start_serialize(options_casted)
        return
    }
    public pause(): void {
        this?.pause_serialize()
        return
    }
    public stop(): void {
        this?.stop_serialize()
        return
    }
    private setProgress_serialize(index: number, progress: number): void {
        ArkUIGeneratedNativeModule._LinearIndicatorController_setProgress(this.peer!.ptr, index, progress)
    }
    private start_serialize(options?: LinearIndicatorStartOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        let options_type: int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value = options!
            thisSerializer.writeLinearIndicatorStartOptions(options_value)
        }
        ArkUIGeneratedNativeModule._LinearIndicatorController_start(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    private pause_serialize(): void {
        ArkUIGeneratedNativeModule._LinearIndicatorController_pause(this.peer!.ptr)
    }
    private stop_serialize(): void {
        ArkUIGeneratedNativeModule._LinearIndicatorController_stop(this.peer!.ptr)
    }
}
