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
import { Area, Length, Position } from "./ArkUnitsInterfaces"
import { Resource } from "./ArkResourceInterfaces"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, isInstanceOf } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { isResource, isPadding } from "./../utils"
import { Deserializer, createDeserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ArkUIGeneratedNativeModule } from "./ArkUIGeneratedNativeModule"
export interface SwipeGestureEvent {
    angle: number
    speed: number
}
export class SwipeGestureEventInternal extends BaseGestureEventInternal implements MaterializedBase,SwipeGestureEvent {
    get angle(): number {
        return this.getAngle()
    }
    set angle(angle: number) {
        this.setAngle(angle)
    }
    get speed(): number {
        return this.getSpeed()
    }
    set speed(speed: number) {
        this.setSpeed(speed)
    }
    static ctor_swipegestureevent(): KPointer {
        const retval = ArkUIGeneratedNativeModule._SwipeGestureEvent_ctor()
        return retval
    }
     constructor() {
        super()
        const ctorPtr: KPointer = SwipeGestureEventInternal.ctor_swipegestureevent()
        this.peer = new Finalizable(ctorPtr, SwipeGestureEventInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._SwipeGestureEvent_getFinalizer()
    }
    private getAngle(): number {
        return this.getAngle_serialize()
    }
    private setAngle(angle: number): void {
        const angle_casted = angle as (number)
        this?.setAngle_serialize(angle_casted)
        return
    }
    private getSpeed(): number {
        return this.getSpeed_serialize()
    }
    private setSpeed(speed: number): void {
        const speed_casted = speed as (number)
        this?.setSpeed_serialize(speed_casted)
        return
    }
    private getAngle_serialize(): number {
        const retval = ArkUIGeneratedNativeModule._SwipeGestureEvent_getAngle(this.peer!.ptr)
        return retval
    }
    private setAngle_serialize(angle: number): void {
        ArkUIGeneratedNativeModule._SwipeGestureEvent_setAngle(this.peer!.ptr, angle)
    }
    private getSpeed_serialize(): number {
        const retval = ArkUIGeneratedNativeModule._SwipeGestureEvent_getSpeed(this.peer!.ptr)
        return retval
    }
    private setSpeed_serialize(speed: number): void {
        ArkUIGeneratedNativeModule._SwipeGestureEvent_setSpeed(this.peer!.ptr, speed)
    }
    public static fromPtr(ptr: KPointer): SwipeGestureEventInternal {
        const obj: SwipeGestureEventInternal = new SwipeGestureEventInternal()
        obj.peer = new Finalizable(ptr, SwipeGestureEventInternal.getFinalizer())
        return obj
    }
}
