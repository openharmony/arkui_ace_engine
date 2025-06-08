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

import { BaseGestureEvent, BaseGestureEventInternal } from "./ArkBaseGestureEventMaterialized"
import { BaseEvent, BaseEventInternal } from "./ArkBaseEventMaterialized"
import { EventTarget, SourceType, SourceTool } from "./ArkCommonInterfaces"
import { FingerInfo } from "./ArkGestureInterfaces"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export interface RotationGestureEvent {
    angle: number
}
export class RotationGestureEventInternal extends BaseGestureEventInternal implements MaterializedBase,RotationGestureEvent {
    get angle(): number {
        return this.getAngle()
    }
    set angle(angle: number) {
        this.setAngle(angle)
    }
    static ctor_rotationgestureevent(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._RotationGestureEvent_ctor()
        return retval
    }
    constructor() {
        super()
        const ctorPtr : KPointer = RotationGestureEventInternal.ctor_rotationgestureevent()
        this.peer = new Finalizable(ctorPtr, RotationGestureEventInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._RotationGestureEvent_getFinalizer()
    }
    private getAngle(): number {
        return this.getAngle_serialize()
    }
    private setAngle(angle: number): void {
        const angle_casted = angle as (number)
        this.setAngle_serialize(angle_casted)
        return
    }
    private getAngle_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._RotationGestureEvent_getAngle(this.peer!.ptr)
        return retval
    }
    private setAngle_serialize(angle: number): void {
        ArkUIGeneratedNativeModule._RotationGestureEvent_setAngle(this.peer!.ptr, angle)
    }
    public static fromPtr(ptr: KPointer): RotationGestureEventInternal {
        const obj : RotationGestureEventInternal = new RotationGestureEventInternal()
        obj.peer = new Finalizable(ptr, RotationGestureEventInternal.getFinalizer())
        return obj
    }
}
