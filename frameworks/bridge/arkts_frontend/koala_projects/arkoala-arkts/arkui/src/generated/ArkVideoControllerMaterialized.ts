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

import { SeekMode } from "./ArkVideoInterfaces"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export class VideoControllerInternal {
    public static fromPtr(ptr: KPointer): VideoController {
        const obj : VideoController = new VideoController()
        obj.peer = new Finalizable(ptr, VideoController.getFinalizer())
        return obj
    }
}
export class VideoController implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_videocontroller(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._VideoController_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = VideoController.ctor_videocontroller()
        this.peer = new Finalizable(ctorPtr, VideoController.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._VideoController_getFinalizer()
    }
    public start(): undefined {
        return this.start_serialize()
    }
    public pause(): undefined {
        return this.pause_serialize()
    }
    public stop(): undefined {
        return this.stop_serialize()
    }
    public setCurrentTime(value: number, seekMode?: SeekMode): undefined {
        const value_type = runtimeType(value)
        const seekMode_type = runtimeType(seekMode)
        if (RuntimeType.UNDEFINED == seekMode_type) {
            const value_casted = value as (number)
            return this.setCurrentTime0_serialize(value_casted)
        }
        if (TypeChecker.isSeekMode(seekMode)) {
            const value_casted = value as (number)
            const seekMode_casted = seekMode as (SeekMode)
            return this.setCurrentTime1_serialize(value_casted, seekMode_casted)
        }
        throw new Error("Can not select appropriate overload")
    }
    public requestFullscreen(value: boolean): undefined {
        const value_casted = value as (boolean)
        return this.requestFullscreen_serialize(value_casted)
    }
    public exitFullscreen(): undefined {
        return this.exitFullscreen_serialize()
    }
    public reset(): void {
        this.reset_serialize()
        return
    }
    private start_serialize(): undefined {
        const retval  = ArkUIGeneratedNativeModule._VideoController_start(this.peer!.ptr)
        return retval
    }
    private pause_serialize(): undefined {
        const retval  = ArkUIGeneratedNativeModule._VideoController_pause(this.peer!.ptr)
        return retval
    }
    private stop_serialize(): undefined {
        const retval  = ArkUIGeneratedNativeModule._VideoController_stop(this.peer!.ptr)
        return retval
    }
    private setCurrentTime0_serialize(value: number): undefined {
        const retval  = ArkUIGeneratedNativeModule._VideoController_setCurrentTime0(this.peer!.ptr, value)
        return retval
    }
    private requestFullscreen_serialize(value: boolean): undefined {
        const retval  = ArkUIGeneratedNativeModule._VideoController_requestFullscreen(this.peer!.ptr, value ? 1 : 0)
        return retval
    }
    private exitFullscreen_serialize(): undefined {
        const retval  = ArkUIGeneratedNativeModule._VideoController_exitFullscreen(this.peer!.ptr)
        return retval
    }
    private setCurrentTime1_serialize(value: number, seekMode: SeekMode): undefined {
        const retval  = ArkUIGeneratedNativeModule._VideoController_setCurrentTime1(this.peer!.ptr, value, seekMode.valueOf())
        return retval
    }
    private reset_serialize(): void {
        ArkUIGeneratedNativeModule._VideoController_reset(this.peer!.ptr)
    }
}
